/*
	main.cpp is the file where unit tests are performed on the wrapper classes

	note for developers
		this program is not complicated but needs to compile in all standards
		thus i advise you to restrict yourself to C++98 features, and deal with deprecations using pre-processor statements
		i will leave you with a good resource for C++98 here: https://cplusplus.com/doc/oldtutorial/

	despite the library itself being formatted to match the standard library's style,
	the unit testing part of this program will be using recommended C++ formatting
*/
#include <iostream>

#include "string.h"

using namespace jastd;

/*
	flags that correspondent to different behaviors the tester should execute

	C++98 style scoped enum
*/
namespace ArgumentFlags
{
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

int main()
{
	const string welcomeMessage = "Welcome to the unit tester for jastd!";
	const string helpMessage =
		"\nConsider the following\n"
		"\ttest <-e | --everything>\t\t\tPerforms unit tests on all headers\n"
		"\ttest <-a | --available>\t\t\t\tPerforms unit tests on all headers available in this C++ Standard version\n"
		"\ttest <-s | --select> <header1> [<header2> ...]\tPerforms unit tests on each header listed\n"
		"\tlist <-e | --everything>\t\t\tLists all headers\n"
		"\tlist <-a | --available>\t\t\t\tLists all header available in this C++ Standard version\n"
		"\tstd\t\t\t\t\t\tShows the C++ Standard version currently being used\n"
		"\tjastd\t\t\t\t\t\tShows the jastd version currently being used\n"
		"\thelp\t\t\t\t\t\tShows this menu\n"
		"\tquit\t\t\t\t\t\tCloses the program\n";
	
	std::cout << welcomeMessage << helpMessage << std::endl;

	// using ArgumentFlags namespace for readability's sake
	using namespace ArgumentFlags;

	bool quit = false;
	while (!quit)
	{
		// string container for the command fetched from user input
		string command = "";

		// index where the last argument stopped, 0 if a new argument is being parsed
		size_t previousIndex = 0;

		// bitfield to tick while parsing arguments
		unsigned int argumentFlags = CLEAR;

		// request command
		std::cout << "> ";
		std::getline(std::cin, command);

		// parse arguments
		while (previousIndex < command.size())
		{
			// argument to be substringed from the command
			string argument = command.substr(' ', previousIndex);
			previousIndex += argument.size() + 1;

			// set argument flags
			argumentFlags |=
				(argument.match_any("-e", "--everything"))
					? EVERYTHING :
				(argument.match_any("-a", "--available"))
					? AVAILABLE :
				(argument.match_any("-s", "--select"))
					? SELECT :
				(argument.match("test"))
					? TEST :
				(argument.match("list"))
					? LIST :
				(argument.match("std"))
					? STANDARD_VERSION :
				(argument.match("jastd"))
					? JASTD_VERSION :
				(argument.match("help"))
					? HELP :
				(argument.match("quit"))
					? QUIT :
						CLEAR; // the flags clear when an invalid argument occured...
			
			// ...and thus it prints error message to console output
			if (argumentFlags == CLEAR)
			{
				std::cerr << "'" << argument << "' in '" << command << "' is not a recognized argument. Write 'help' to see a list of commands." << std::endl;
				break;
			}
		}

		switch (argumentFlags)
		{
			case QUIT:
				quit = true;
			break;
			// case TEST | EVERYTHING:
			// break;
		}
	}

	return 0;
}