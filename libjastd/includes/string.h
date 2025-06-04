#pragma once
#include <string>
#include "macros.h"

namespace jastd
{
	/*
		jastd std::string wrapper for C++98
	*/
	class string98 : public std::string
	{
	public:
		explicit string98();
		string98(const char* str_literal);
		string98(const std::string& str);

		string98 substr(char delim, size_t pos = 0) const;
		bool match_any(const string98& strs, size_t count) const;
		bool match_all(const string98& strs, size_t count) const;
	};

#if MIN_USING_CPP(11)
	/*
		jastd std::string wrapper for C++11
	*/
	class string11 : public std::string
	{
	public:
		explicit string11();
		string11(const char* str_literal);
		string11(const std::string& str);

		string11 substr(char delim, size_t pos = 0) const;
		bool match_any(const string11& strs, size_t count) const;
		bool match_all(const string11& strs, size_t count) const;
	};
#endif /* 11 */

	DEFINE_GENERIC_TYPE(string)
}