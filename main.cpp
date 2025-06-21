/*
	main.cpp is the file where the unit tester lives

	note for developers
		this program is not complicated but needs to compile in all standards
		thus i advise you to restrict yourself to C++98 features, and deal with deprecations using pp directives
		i will leave you with a good resource for C++98 here: https://cplusplus.com/doc/oldtutorial/

	despite the library itself being formatted to match the standard library's style,
	the unit testing part of this program will be using recommended C++ formatting
	*/

// C++ headers
#include <iostream>
#include <iomanip>
#include <stdexcept>

// jastd headers
#include "string.hpp"

using namespace jastd;

// Some command line interface stuff.
namespace CLI
{
	// Exception thrown for faulty specific command line interface arguments.
	class ArgumentException : public std::runtime_error
	{
	public:
		explicit ArgumentException(const string98& argument) : std::runtime_error(argument) {}
		virtual ~ArgumentException() throw() {}
	};

	// Exception thrown for faulty a command line interface command.
	class CommandException : public std::runtime_error
	{
	public:
		explicit CommandException(const string98& command) : std::runtime_error(command) {}
		virtual ~CommandException() throw() {}
	};

	// Exception thrown for valid, but unimplemented commands.
	class UnimplementedException : public std::runtime_error
	{
	public:
		explicit UnimplementedException(const string98& unimplementCommand) : std::runtime_error(unimplementCommand) {}
		virtual ~UnimplementedException() throw() {}
	};
}

struct AppState
{
	bool doQuit;
	std::vector<string98> arguments;
	unsigned int argumentFlags;
};

// forwarded declarations
std::vector<string98> FetchNewArguments();
unsigned int DetermineArgumentFlags(const std::vector<string98>&);
void ExecuteCommands(AppState&);
void PrintVersion();
void PrintStandard();
void PrintHelp();

int main()
{
	AppState state;

	std::cout << "\nWelcome to the unit tester for jastd!\n";
	std::cout << "Type 'help' for details.\n";
	std::cout << std::endl;
	
	while (!state.doQuit)
	{
		state.arguments = FetchNewArguments();
		
		try
		{
			state.argumentFlags = DetermineArgumentFlags(state.arguments);
			ExecuteCommands(state);		
		}
		catch (CLI::ArgumentException& exception)
		{
			std::cout << "'" << exception.what() << "' is not a valid argument.\n" << std::endl;
		}
		catch (CLI::CommandException& exception)
		{
			std::cout << "'" << exception.what() << "' is not a valid command.\n" << std::endl;
		}
		catch (CLI::UnimplementedException& exception)
		{
			std::cout << "'" << exception.what() << "' is a valid command, but is currently not implemented.\n" << std::endl;
		}
	}
	
	return 0;
}

// Flags that correspondent to different behaviors the tester should execute.
namespace ArgumentFlags
{
	// C++98 style scoped enum
	enum ArgumentFlagsImpl
	{
		CLEAR				= 0b00000000,
		TEST				= 0b00000001,
		LIST				= 0b00000010,
		EVERYTHING			= 0b00000100,
		AVAILABLE			= 0b00001000,
		SELECT				= 0b00010000,
		STANDARD_VERSION	= 0b00100000,
		JASTD_VERSION		= 0b01000000,
		HELP				= 0b10000000,
		QUIT				= 0b11111111
	};
};

// Requests input from the user through the cli, then splits this into separate arguments.
std::vector<string98> FetchNewArguments()
{
	string98 input;
	
	std::cout << "> ";
	std::getline(std::cin, input);
	
	// optimization: implement move semantics functionality
	return input.split(' ');
}

// Returns a series of argument flags determined by the parameter
unsigned int DetermineArgumentFlags(const std::vector<string98>& arguments)
{
	unsigned int flags = 0;
	
	typedef std::vector<string98>::const_iterator const_iterator;
	for (const_iterator it = arguments.begin(); it != arguments.end(); it++)
	{
		const string98 ARGUMENT = it->trim(' ');
		
		// ignore argument if it's empty
		if (ARGUMENT.empty())
		{
			continue;
		}
		
		using namespace ArgumentFlags;
		// otherwise do this shit to determine it
		switch (flags)
		{
			case CLEAR:
				if 		(ARGUMENT.match("test"))	flags |= TEST;
				else if (ARGUMENT.match("list"))	flags |= LIST;
				else if (ARGUMENT.match("std"))		flags |= STANDARD_VERSION;
				else if (ARGUMENT.match("jastd"))	flags |= JASTD_VERSION;
				else if (ARGUMENT.match("help"))	flags |= HELP;
				else if (ARGUMENT.match("quit"))	flags |= QUIT;
				else throw CLI::ArgumentException(ARGUMENT);
			break;
			case TEST:
				if (ARGUMENT.match_any(VARARGS("-s", "--select")))
				{
					flags |= SELECT;
				}
				else if (ARGUMENT.match_any(VARARGS("-a", "--all")))	flags |= AVAILABLE;
				else throw CLI::ArgumentException(ARGUMENT);
			break;
			default:
				throw CLI::CommandException(concat(arguments[0], arguments.size(), " "));
		}
	}
	
	return flags;
}

// Performs various actions depending on the argument flags passed into it.
void ExecuteCommands(AppState& state)
{
	using namespace ArgumentFlags;
	switch (state.argumentFlags)
	{
		case TEST | SELECT:
		case TEST | EVERYTHING:
		case TEST | AVAILABLE:
		case LIST:
			throw CLI::UnimplementedException(concat(state.arguments[0], state.arguments.size(), " "));
		break;
		case JASTD_VERSION:
			PrintVersion();
		break;
		case STANDARD_VERSION:
			PrintStandard();
		break;
		case HELP:
			PrintHelp();
		break;
		case QUIT:
			state.doQuit = true;
		break;
		default:
			throw CLI::CommandException(concat(state.arguments[0], state.arguments.size(), " "));
	}
	std::cout << std::endl;
}

void PrintVersion()
{
	const string98 version = "jastd-" JASTD_V_STR + string98(_DEBUG ? "-deb" : "");
	std::cout << version << '\n';
}

void PrintStandard()
{
	const string98 standard = "C++" + to_string(CPP_V);
	std::cout << standard << '\n';
}

void PrintHelp()
{
	const int fieldWidth = 70;
	std::cout << std::setiosflags(std::ios_base::left)
		<< "Consider the following\n"
		<< std::setw(fieldWidth)
		<< "> test <-a | --all> [-v | --version <number>]"
		<< "Performs unit tests on all headers.\n"
		<< std::setw(fieldWidth)
		<< "> test <-s | --selection> <header1> [-v | --version <number>] [...]"
		<< "Performs unit tests on each header listed, optionally from a specific C++ Standard version.\n"
		<< std::setw(fieldWidth)
		<< "> list [-v | --version <number>]"
		<< "Lists all headers, optionally in a specific C++ Standard version.\n"
		<< std::setw(fieldWidth)
		<< "> standard"
		<< "Shows the C++ Standard version currently being used.\n"
		<< std::setw(fieldWidth)
		<< "> version"
		<< "Shows the jastd version currently being used.\n"
		<< std::setw(fieldWidth)
		<< "> help"
		<< "Show this message.\n"
		<< std::setw(fieldWidth)
		<< "> quit"
		<< "Closes this program.\n";
}
