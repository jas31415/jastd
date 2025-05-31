/*
	main.cpp is the file where unit tests are performed on the wrapper classes

	note for developers
		since this program is not complicated but needs to compile in all standards
		i advise you to restrict yourself to C++98 features, and deal with deprecations using pre-processor statements
		i will leave you with a good resource for C++98 here: https://cplusplus.com/doc/oldtutorial/

	despite the library itself being formatted to match the standard library's style,
	the unit testing part of this program will be using recommended C++ formatting
*/
#include <iostream>
#include <vector>

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
		"\tquit\t\t\t\t\t\tcloses the program\n";

	std::cout << welcomeMessage << helpMessage << std::endl;

	/*
		a list of valid inputs
		[0] "-e", "--everything",
		[2] "-a", "--available",
		[4] "-s", "--select",
		[6] "test", "list",
		[8] "std", "jastd",
		[10] "help", "quit"
		(i promise this will change later)
	*/
	const string registeredInputs[] =
	{
		"-e", "--everything",
		"-a", "--available",
		"-s", "--select",
		"test", "list",
		"std", "jastd",
		"help", "quit"
	};
	// use jastd::vector<string> once subset() is developed
	// const std::vector<string> registeredInputs(_regsTemp, _regsTemp + 2);

	// using ArgumentFlags namespace for readability's sake
	using namespace ArgumentFlags;

	bool quit = false;
	while (!quit)
	{
		// string container for the command fetched from user input
		string command = "";

		// the maximum argument length is 18 because the longest valid character sequence is "condition_variable", any argument longer than this would be invalid
		// const int MAX_ARGUMENT_LENGTH = 18;

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

			// set argument flags (please find a prettier way to do this lol)
			if (argument.match_any(registeredInputs[0], 2))
			{
				argumentFlags |= EVERYTHING;
			}
			else if (argument.match_any(registeredInputs[2], 2))
			{
				argumentFlags |= AVAILABLE;
			}
			else if (argument.match_any(registeredInputs[4], 2))
			{
				argumentFlags |= SELECT;
			}
			else if (!argument.compare(registeredInputs[6]))
			{
				argumentFlags |= TEST;
			}
			else if (!argument.compare(registeredInputs[7]))
			{
				argumentFlags |= LIST;
			}
			else if (!argument.compare(registeredInputs[8]))
			{
				std::cout << ~argument.compare(registeredInputs[8]) << std::endl;
				argumentFlags |= STANDARD_VERSION;
			}
			else if (!argument.compare(registeredInputs[9]))
			{
				argumentFlags |= JASTD_VERSION;
			}
			else if (!argument.compare(registeredInputs[10]))
			{
				argumentFlags |= HELP;
			}
			else if (!argument.compare(registeredInputs[11]))
			{
				argumentFlags |= QUIT;
			}
			else
			{
				std::cerr << "'" << argument << "' in '" << command << "' is not a recognized argument. Write 'help' to see a list of commands." << std::endl;
			}
		}

		switch (argumentFlags)
		{			
			case QUIT:
				quit = true;
			break;
		}
	}

	return 0;
}

