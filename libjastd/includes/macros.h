#pragma once

// C++ standard versions
#define CPP98 199711L // C++98 macro value
#define CPP11 201103L // C++11 macro value
#define CPP14 201402L // C++14 macro value
#define CPP17 201703L // C++17 macro value
#define CPP20 202002L // C++20 macro value
#define CPP23 202302L // C++23 macro value
#define CPP26 202400L // C++26 macro value (they might change this later lol)

// @returns  If C++ standard version is the same as `ver`
#define USING_STD(ver) __cplusplus == ver
// @returns  If C++ standard version is the same as `ver` or older 
#define USING_STD_MINIMUM(ver) __cplusplus >= ver

// cross-standard compatbility hacks
#if USING_STD(CPP98)

	#define nullptr NULL

	// jastd generic type for std::string wrappers
	#define DEFINE_GENERIC_TYPE(type) typedef type##98 type;

#endif /* 98 */
#if USING_STD(CPP11)

	// jastd generic type for std::string wrappers
	#define DEFINE_GENERIC_TYPE(type) typedef type##11 type;

#endif /* 11 */
