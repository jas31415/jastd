#pragma once

// i know this looks ugly but it's rather efficient
#if __cplusplus == 199711L
#	define CPP_V 98
#elif __cplusplus == 201103L
#	define CPP_V 11
#elif __cplusplus == 201402L
#	define CPP_V 14
#elif __cplusplus == 201703L
#	define CPP_V 17
#elif __cplusplus == 202002L
#	define CPP_V 20
#elif __cplusplus == 202302L
#	define CPP_V 23
#elif __cplusplus == 202400L // they might change the __cplusplus value for C++26 later
#	define CPP_V 26
#endif

// @brief  A developer friendly macro for determining the colloquial C++ version number.
// @returns  If the colloquial C++ version number is equal to `ver_num`.
#define USING_CPP(ver_num) CPP_V == ver_num

// @brief  A developer friendly macro for determining if the colloquial C++ version number is .
// @returns  If the colloquial C++ version number is the equal to or larger than `ver_num`.
#define MIN_USING_CPP(ver_num) USING_CPP(98) ? USING_CPP(ver_num) : CPP_V >= ver_num

// cross-standard compatbility hacks
#if USING_CPP(98)

	#define nullptr NULL

	// jastd generic type for std::string wrappers
	#define DEFINE_GENERIC_TYPE(type) typedef type##98 type;

#endif /* 98 */
#if USING_CPP(11)

	// jastd generic type for std::string wrappers
	#define DEFINE_GENERIC_TYPE(type) typedef type##11 type;

#endif /* 11 */
