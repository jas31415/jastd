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

struct AppState
{
	bool doQuit;
	std::vector<string> arguments;
	unsigned int argumentFlags;
};

// forwarded declarations
std::vector<string> FetchNewArguments();
unsigned int DetermineArgumentFlags(const std::vector<string>&);
void ExecuteAppState(AppState&);
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
		catch (std::invalid_argument& exception)
		{
			std::cout << "'" << exception.what() << "' was not a valid argument.\n" << std::endl;
			continue;
		}
		ExecuteAppState(state);
	}
	
	return 0;
}

// Flags that correspondent to different behaviors the tester should execute.
namespace ArgumentFlags
{
	enum ArgumentFlagsImpl // C++98 style scoped enum
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
std::vector<string> FetchNewArguments()
{
	string input;
	
	std::cout << "> ";
	std::getline(std::cin, input);
	
	// optimization: implement move semantics functionality
	return input.split(' ');
}

// Returns a series of argument flags determined by the parameter
unsigned int DetermineArgumentFlags(const std::vector<string>& arguments)
{
	unsigned int flags = 0;
	
	typedef std::vector<string>::const_iterator const_iterator;
	for (const_iterator it = arguments.begin(); it != arguments.end(); it++)
	{
		const string ARGUMENT = it->trim(' ');
		
		// ignore argument if it's empty
		if (ARGUMENT.empty())
		{
			continue;
		}
		
		switch (flags)
		{
			// check for command (first argument)
			case ArgumentFlags::CLEAR:
				if (ARGUMENT.match("test"))
					flags = ArgumentFlags::TEST;
				else if (ARGUMENT.match("list"))
					flags = ArgumentFlags::LIST;
				else if (ARGUMENT.match("std"))
					flags = ArgumentFlags::STANDARD_VERSION;
				else if (ARGUMENT.match("jastd"))
					flags = ArgumentFlags::JASTD_VERSION;
				else if (ARGUMENT.match("help"))
					flags = ArgumentFlags::HELP;
				else if (ARGUMENT.match("quit"))
					flags = ArgumentFlags::QUIT;
				else
					throw std::invalid_argument(ARGUMENT);
			break;
			// check for argument
			case ArgumentFlags::TEST:
				if (ARGUMENT.match_any(VARARGS("-s", "--select")))
				{
					flags |= ArgumentFlags::SELECT;
					continue;
				}
			case ArgumentFlags::LIST:
				if (ARGUMENT.match_any(VARARGS("-e", "--everything")))
					flags |= ArgumentFlags::EVERYTHING;
				else if (ARGUMENT.match_any(VARARGS("-a", "--available")))
					flags |= ArgumentFlags::AVAILABLE;
				else
					throw std::invalid_argument(ARGUMENT);
			break;
			default:
				throw std::invalid_argument(ARGUMENT);
		}
	}
	
	return flags;
}

// Performs various actions depending on the argument flags passed into it.
void ExecuteAppState(AppState& state)
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
	}
	std::cout << std::endl;
}

void PrintVersion()
{
	const string version = "jastd-" JASTD_V_STR + string(_DEBUG ? "-deb" : "");
	std::cout << version << '\n';
}

void PrintStandard()
{
	const string standard = "C++" + to_string(CPP_V);
	std::cout << standard << '\n';
}

void PrintHelp()
{
	const string helpMsg =
	"Consider the following\n"
	"- test <-e | --everything>\t\t\t\tPerforms unit tests on all headers\n"
	"- test <-a | --available>\t\t\t\tPerforms unit tests on all headers available in this C++ Standard version\n"
	"- test <-s | --select> <header1> [<header2> ...]\tPerforms unit tests on each header listed\n"
	"- list <-e | --everything>\t\t\t\tLists all headers\n"
	"- list <-a | --available>\t\t\t\tLists all headers available in this C++ Standard version\n"
	"- std\t\t\t\t\t\t\tShows the C++ Standard version currently being used\n"
	"- jastd\t\t\t\t\t\t\tShows the jastd version currently being used\n"
	"- help\t\t\t\t\t\t\tShows this menu\n"
	"- quit\t\t\t\t\t\t\tCloses this program";
	std::cout << helpMsg << '\n';
}
