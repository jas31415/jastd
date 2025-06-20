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
#include <exception>

// jastd headers
#include "string.hpp"

using namespace jastd;

// Exception thrown for faulty specific command line interface arguments
class cli_argument_error : public std::runtime_error
{
public:
	explicit cli_argument_error(const string98& cli_arg) : std::runtime_error(cli_arg) {}
    virtual ~cli_argument_error() throw() {}
};

// Exception thrown for faulty a command line interface command
class cli_command_error : public std::runtime_error
{
public:
	explicit cli_command_error(const string98& cli_cmd) : std::runtime_error(cli_cmd) {}
    virtual ~cli_command_error() throw() {}
};

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

	std::cout << "Welcome to the unit tester for jastd!\n";
	PrintHelp();
	std::cout << std::endl;
	
	while (!state.doQuit)
	{
		state.arguments = FetchNewArguments();
		try
		{
			state.argumentFlags = DetermineArgumentFlags(state.arguments);
		}
		catch (cli_argument_error& exception)
		{
			std::cout << "'" << exception.what() << "' is not a valid argument.\n" << std::endl;
			continue;
		}
		catch (cli_command_error& exception)
		{
			std::cout << "'" << exception.what() << "' is not a valid command.\n" << std::endl;
			continue;
		}
		ExecuteCommands(state);
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
				else throw cli_argument_error(ARGUMENT);
			break;
			case TEST:
				if (ARGUMENT.match_any(VARARGS("-s", "--select")))
				{
					flags |= SELECT;
					continue;
				}
			case LIST:
				if 		(ARGUMENT.match_any(VARARGS("-e", "--everything")))	flags |= EVERYTHING;
				else if (ARGUMENT.match_any(VARARGS("-a", "--available")))	flags |= AVAILABLE;
				else throw cli_argument_error(ARGUMENT);
			break;
			default:
				throw cli_command_error(concat(arguments[0], arguments.size(), " "));
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
		break;
		case TEST | EVERYTHING:
		break;
		case TEST | AVAILABLE:
		break;
		case LIST | EVERYTHING:
		break;
		case LIST | AVAILABLE:
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
			throw cli_command_error(concat(state.arguments[0], state.arguments.size(), " "));
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
	const string98 helpMsg =
	"Consider the following\n"
	"> test <-e | --everything>\t\t\t\tPerforms unit tests on all headers\n"
	"> test <-a | --available>\t\t\t\tPerforms unit tests on all headers available in this C++ Standard version\n"
	"> test <-s | --select> <header1> [<header2> ...]\tPerforms unit tests on each header listed\n"
	"> list <-e | --everything>\t\t\t\tLists all headers\n"
	"> list <-a | --available>\t\t\t\tLists all headers available in this C++ Standard version\n"
	"> std\t\t\t\t\t\t\tShows the C++ Standard version currently being used\n"
	"> jastd\t\t\t\t\t\t\tShows the jastd version currently being used\n"
	"> help\t\t\t\t\t\t\tShows this menu\n"
	"> quit\t\t\t\t\t\t\tCloses this program";
	std::cout << helpMsg << '\n';
}
