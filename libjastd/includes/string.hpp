#pragma once
#include <string>
#include <vector>
#include "macros.hpp"

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
		
		operator const char*();

		string98 substr(char delim, size_t pos = 0) const;
		string98 substr(size_t pos, size_t count = npos) const;		
		bool match(const string98& str) const;
		bool match_any(int count, const string98& str, ...) const;
		bool match_any(const string98& strs, size_t count) const;
		bool match_all(int count, const string98& str, ...) const;
		bool match_all(const string98& strs, size_t count) const;
		string98 trim(char c) const;
		string98 trim_l(char c) const;
		string98 trim_r(char c) const;
		std::vector<string98> split(char delim, bool keep_delim = false) const;
		int occurs(char c) const;
		// string98 copy() const;
		// to do: implement character categories for trimming all whitespaces
	};
	
#if USING_CPP(98)

	template<class param_t>
	std::string to_string(const param_t& param);
	template<class str_t, class param_t>
	str_t to_string(const param_t& param);
	
#endif /* 98 */

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
		bool match(const string11& str) const;
		bool match_any(const string11& strs, size_t count) const;
		bool match_all(const string11& strs, size_t count) const;
	};

#endif /* 11 ... */

	// jastd generic typedef for std::string
	TYPEDEF_GENERIC(string)
}

// i'm not adding src/ to the includes folders
// aside of my suspicion that this will result in unresolved paths...
// ... i don't want to clog up the includes with all the template files
#include "../src/string.tpp"