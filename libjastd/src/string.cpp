#include "string.h"
#include <stdexcept>
#include <cassert>
#include <cstdarg>
#include <typeinfo>

using namespace jastd;

/*
	jastd string98 class definitions
*/

string98::string98() : std::string() {}
string98::string98(const char *str_literal) : std::string(str_literal) {}
string98::string98(const std::string &str) : std::string(str) {}

/**
 * 	@brief  Get a substring using a delimiter.
 * 	@param delim  Character to terminate substring at. Substring terminates at '0/' if no case of @a delim is found.
 *  @param pos  Position to start the substring from. (default 0)
 *  @return  The new string.
 *  @throw  std::out_of_range If `pos` > size().
 * 
 *  Constructs a new string containing all characters between index `pos` and `delim`.
 * 	If `delim` is never met, the entirety of the remaining string returns.
 *  If `pos` is larger than the size of the string, std::out_of_range is thrown.
 */
string98 string98::substr(char delim, size_t pos) const
{
	assert(pos < size() && "pos was too large");
	return std::string::substr(pos, find(' ', pos));
}

string98 string98::substr(size_t pos, size_t count) const
{
	assert (pos < size() && "pos was too large");
	return std::string::substr(pos, count);
}

/**
 *  @brief  Look at a string for a match.
 *  @param str  String to read from.
 *  @return  If this string matches with `str`.
 * 
 *	Passes `str` as argument inside of std::string::compare() and returns the boolean inverse of its result.
 *	Even though it's an unnecessary wrapping on the surface, seeing `if (!strA.compare(strB))` is not exactly intuitive.
 */
bool string98::match(const string98& str) const
{
	return !compare(str);
}

/*
	needs docu
*/
bool string98::match_any(const string98& str, ...) const
{
	// a string that for some reason takes place at the end of every params list
	const char* end_of_params = "P\200";

	// variadic arguments list
	std::va_list args;
	va_start(args, str);

	// match result var
	bool is_match = false;

	// current argument to look through
	string98 arg = str;

	do
	{
		is_match = match(arg);
		if (is_match)
		{
			break;
		}
		arg = va_arg(args, const char *);
	}
	while (!arg.substr(0ULL, (arg.size() >= 2) ? 2 : size()).match(end_of_params));

	va_end(args);

	return is_match;
}

/**
 *  @brief  Look at multiple strings for single match.
 *  @param strs  Array of strings to read from.
 *  @param count  Number of string in this array.
 *  @return  If this string matches any of the string contained at `&strs`.
 * 	@throw  std::out_of_range Possible if `count` exceeds `strs` size.
 * 
 * 	Takes the elements at `strs` and one by one passes these as argument inside of std::string::compare().
 *  If `count` exceeds the size of `strs`, it's possible that std::out_of_range is thrown.
 * 	Predicting the exception would require try-catching, so this overhead is deferred to the user (that's you).
 */
bool string98::match_any(const string98& strs, size_t count) const
{
	for (int idx = 0; idx < count; idx++)
	{
		const bool is_match = compare((&strs)[idx]) == 0;
		if (is_match)
		{
			return true;
		}
	}
	return false;
}

/*
	needs docu
*/
bool string98::match_all(const string98& str, ...) const
{
	// a string that for some reason takes place at the end of every params list
	const char* end_of_params = "P\200";

	// variadic arguments list
	std::va_list args;
	va_start(args, str);

	// match result var
	bool is_match = false;

	// current argument to look through
	string98 arg = str;

	do
	{
		is_match = match(arg);
		if (!is_match)
		{
			break;
		}
		arg = va_arg(args, const char *);
	}
	while (!arg.substr(0ULL, (arg.size() >= 2) ? 2 : size()).match(end_of_params));

	va_end(args);

	return is_match;
}

/**
 *  @brief  Look at multiple strings for a full match.
 *  @param strs  Array of strings to read from.
 *  @param count  Number of string in this array.
 *  @return  If this string matches all of the strings contained at `&strs`.
 * 	@throw  std::out_of_range If `count` exceeds `strs` size.
 *
 * 	Takes the elements at `strs` and one by one passes these as argument inside of std::string::compare().
 *  If `count` exceeds the size of `strs`, std::out_of_range will be thrown.
 * 	Predicting the exception would require try-catching, so this overhead is deferred to the user (that's you).
 */
bool string98::match_all(const string98& strs, size_t count) const
{
	for (int idx = 0; idx < count; idx++)
	{
		const bool is_match = compare((&strs)[idx]) == 0;
		if (!is_match)
		{
			return false;
		}
	}
	return true;
}