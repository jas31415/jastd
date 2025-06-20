#include "string.hpp"
#include <cassert>
#include <cstdarg>

using namespace jastd;

/*
	jastd string98 class definitions
*/

string98::string98() : std::string() {}
string98::string98(const char *str_literal) : std::string(str_literal) {}
string98::string98(const std::string &str) : std::string(str) {}

string98::operator const char*()
{
	return this->data();
}

/**
 * 	@brief  Get a substring using a delimiter.
 * 	@param delim  Character to terminate substring at. Substring terminates at '0/' if no case of `delim` is found.
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
	assert((pos < size() || empty()) && "pos was not smaller than size()");
	return std::string::substr(pos, find(delim, pos) - pos);
}

/**
 *  @brief  Get a substring.
 *  @param pos  Index of first character. (default 0)
 *  @param count  Number of characters in substring. (default remainder)
 *  @return  The new string.
 *  @throw  std::out_of_range  If __pos > size().
 *
 *  Construct and return a new string using the `count` characters starting at `pos`.
 * 	If the string is too short, use the remainder of the characters.
 *	If `pos` is beyond the end of the string, std::out_of_range is thrown.
 */
string98 string98::substr(size_t pos, size_t count) const
{
	assert((pos < size() || empty()) && "pos was not smaller than size()");
	return std::string::substr(pos, count);
}

/**
 *  @brief  Test if strings match.
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

/**
 *  @brief  Look for any strings that match.
 *  @param count  Number of string in this array.
 *  @param str  Start of the variadic list of strings to compare to.
 *  @return  `true` if this string matches any of the string contained in variadic list.
 * 	@throw  std::out_of_range Possible if `count` exceeds the number of arguments.
 * 
 * 	Uses `count` to iterate over a variadic arguments list.
 *	If an argument matches with this string, the method returns `true`.
 *  If `count` exceeds the number of arguments passed into the list, the operation will result in unpredictable behavior.
*/
bool string98::match_any(int count, const string98& str, ...) const
{
	std::va_list args;
	va_start(args, str);

	// match result var, to be returned
	bool is_match = false;

	for (string98 arg = str; --count > 0; arg = va_arg(args, const char*))
	{
		is_match = match(arg);
		if (is_match)
		{
			break;
		}
	}

	va_end(args);

	return is_match;
}

/**
 *  @brief  Look for any strings that match.
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
	// match result var
	bool is_match = false;

	for (int idx = 0; idx < count; idx++)
	{
		is_match = match((&strs)[idx]);
		if (is_match)
		{
			break;
		}
	}

	return is_match;
}

/**
 *  @brief  Look for any strings that do not match.
 *  @param count  Number of string in this array.
 *  @param str  Start of the variadic list of strings to compare to.
 *  @return  `true` if this string matches all of the string contained in variadic list.
 * 	@throw  std::out_of_range Possible if `count` exceeds the number of arguments.
 * 
 * 	Uses `count` to iterate over a variadic arguments list.
 *	If an argument matches with this string, the method returns `true`.
 *  If `count` exceeds the number of arguments passed into the list, the operation will result in unpredictable behavior.
*/
bool string98::match_all(int count, const string98& str, ...) const
{
	std::va_list args;
	va_start(args, str);

	// match result var, to be returned
	bool is_match = true;

	for (string98 arg = str; --count > 0 && is_match; arg = va_arg(args, const char*))
	{
		is_match = match(arg);
		if (!is_match)
		{
			break;
		}
	}

	va_end(args);

	return is_match;
}

/**
 *  @brief  Look for any strings that do not match.
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
	// match result var
	bool is_match = true;

	for (int idx = 0; idx < count && is_match; idx++)
	{
		is_match = match((&strs)[idx]);
	}

	return is_match;
}

/**
 *  @brief Trim a string.
 *  @param c  The character to trim off.
 *  @return  A substring with `c` trimmed off either side.
 *  
 *  Returns a chain-call of `trim_r(char)` and `trim_l(char)`.
 */
string98 string98::trim(char c) const
{
	return trim_r(c).trim_l(c);
}

/**
 *  @brief Trim the left side of a string.
 *  @param c  The character to trim off.
 *  @return  A substring with `c` trimmed off the left side.
 *  
 *  Returns a substring that starts at the first index that isn't `c`.
 */
string98 string98::trim_l(char c) const
{
	return substr(find_first_not_of(c) % npos);
}

/**
 *  @brief Trim the right side of a string.
 *  @param c  The character to trim off.
 *  @return  A substring with `c` trimmed off the right side.
 *  
 *  Returns a substring that starts at the last index that isn't `c`.
 */
string98 string98::trim_r(char c) const
{
	return substr(0ULL, find_last_not_of(c) + 1);
}

/**
 *  @brief  Split a string up into smaller strings using a delimiter.
 *  @param delim  Character to split the string at.
 *  @param keep_delim  If the returned strings should be trimmed of the delimiter. (default true)
 *  @return  A vector of substrings.
 */
std::vector<string98> string98::split(char delim, bool keep_delim) const
{
	// return container for the strings
	std::vector<string98> retstrs;

	if (!empty())
	{
		// roughly determine nr of strings from the amount of time delim occurs
		retstrs.reserve(occurs(delim));
		
		// push the rets =]
		for (size_t pos = 0; pos < length(); pos += retstrs.back().length() + (int)!keep_delim)
		{
			retstrs.push_back(substr(delim, pos));
		}
	}

	return retstrs;
}

/**
 *  @brief  Determine the amount of times a character occurs in a string.
 *  @param c  Character to look for.
 *  @return  Number of times `c` occurs.
 * 
 *  Increments a counter for each iteration in a for loop.
 *  This loop checks for find(c), thus returning the number of occurances.
 */
int string98::occurs(char c) const
{
	int retcount = 0;
	
	for (size_t idx = 0; idx < length(); idx = find(c, idx + 1))
	{
		retcount++;
	}
	
	return retcount;
}

