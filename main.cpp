/*
	main.cpp is the file where the unit tester lives

	note for developers
		this program is not complicated but needs to compile in all standards
		thus i advise you to restrict yourself to C++98 features, and deal with deprecations using pp directives
		i will leave you with a good resource for C++98 here: https://cplusplus.com/doc/oldtutorial/

	despite the library itself being formatted to match the standard library's style,
	the unit testing part of this program will be using recommended C++ formatting
*/
#include <iostream>

#include "string.hpp"

using namespace jastd;

// flags that correspondent to different behaviors the tester should execute
namespace ArgumentFlags
{
	enum ArgumentFlagsImpl // C++98 style scoped enum
	{
		CLEAR				= 0b0000000000,
		TEST				= 0b0000000001,
		LIST				= 0b0000000010,
		EVERYTHING			= 0b0000000100,
		AVAILABLE			= 0b0000001000,
		SELECT				= 0b0000010000,
		STANDARD_VERSION	= 0b0000100000,
		JASTD_VERSION		= 0b0001000000,
		HELP				= 0b0010000000,
		QUIT				= 0b0100000000,
		INVALID				= 0b1000000000
	};
};

int main()
{
	const string welcomeMessage = "Welcome to the unit tester for jastd!\n";
	const string helpMessage =
		"Consider the following\n"
		"- test <-e | --everything>\t\t\t\tPerforms unit tests on all headers\n"
		"- test <-a | --available>\t\t\t\tPerforms unit tests on all headers available in this C++ Standard version\n"
		"- test <-s | --select> <header1> [<header2> ...]\tPerforms unit tests on each header listed\n"
		"- list <-e | --everything>\t\t\t\tLists all headers\n"
		"- list <-a | --available>\t\t\t\tLists all headers available in this C++ Standard version\n"
		"- std\t\t\t\t\t\t\tShows the C++ Standard version currently being used\n"
		"- jastd\t\t\t\t\t\t\tShows the jastd version currently being used\n"
		"- help\t\t\t\t\t\t\tShows this menu\n"
		"- quit\t\t\t\t\t\t\tCloses this program\n";
	
	std::cout << welcomeMessage + helpMessage << std::endl;

	bool quit = false;
	while (!quit)
	{
		// bitfield to tick while parsing arguments
		unsigned int argumentFlags = ArgumentFlags::CLEAR;
		
		// string container for the command fetched from user input
		string command = "";

		// request command
		std::cout << "> ";
		std::getline(std::cin, command);

		// arguments to be substringed from the command
		std::vector<string> arguments = command.split(' ');

		// typedeffing this because the for loop already looks horrendous without the auto keyword
		typedef std::vector<string>::const_iterator vciter;
		
		using namespace ArgumentFlags;

		// parse arguments
		if (!arguments.empty())
		{
			for (vciter argumentIterator = arguments.begin();
				argumentIterator != arguments.end();
				argumentIterator++)
			{
				const string& argument = argumentIterator->trim(' ');

				// discard argument if empty
				if (argument.empty())
				{
					continue;
				}

				// handle argument setting logic
				switch (argumentFlags)
				{
					// this will be at the start of parsing
					case CLEAR:
						if (argument.match("test"))
							argumentFlags |= TEST;
						else if (argument.match("list"))
							argumentFlags |= LIST;
						else if (argument.match("std"))
							argumentFlags |= STANDARD_VERSION;
						else if (argument.match("jastd"))
							argumentFlags |= JASTD_VERSION;
						else if (argument.match("help"))
							argumentFlags |= HELP;
						else if (argument.match("quit"))
							argumentFlags |= QUIT;
					break;
					// this will be at the second parsing attempt
					// these will all be invalid if not alone
					case JASTD_VERSION:
					case STANDARD_VERSION:
					case HELP:
					case QUIT:
						argumentFlags = INVALID;
					break;
				}
			}
		}
		
		// execute behavior coherent to the flagged states
		switch (argumentFlags)
		{
			// case TEST | EVERYTHING:
			// break;
			case STANDARD_VERSION:
				std::cout << "C++" + to_string(CPP_V) + '\n';
			break;
			case JASTD_VERSION:
			{
				const string debugPostfix = _DEBUG ? "-deb" : "";
				std::cout << "jastd-" JASTD_V_STR + debugPostfix + '\n';
			}
			break;
			case HELP:
				std::cout << helpMessage + '\n';
			break;
			case QUIT:
				quit = true;
			break;
			default:
				std::cerr << "'" + command + "' is not a valid command. Write 'help' to see a list of commands.\n";
			break;
			// cases without behavior
			case CLEAR:;
			case INVALID:;
		}

		// to make space between commands and clear buffer
		// refrain from using std::endl; anywhere else
		std::cout << std::endl;
	}

	return 0;
}