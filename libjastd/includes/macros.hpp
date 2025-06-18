#pragma once

// jastd version number
#define JASTD_V_STR "1.0.0"

// i know this looks ugly but it's rather efficient
#if __cplusplus == 199711L
# define CPP_V 98
#elif __cplusplus == 201103L
# define CPP_V 11
#elif __cplusplus == 201402L
# define CPP_V 14
#elif __cplusplus == 201703L
# define CPP_V 17
#elif __cplusplus == 202002L
# define CPP_V 20
#elif __cplusplus == 202302L
# define CPP_V 23
#elif __cplusplus == 202400L // if this doesn't work, double check the __cplusplus value for C++26
# define CPP_V 26
#endif

// @brief  A developer friendly macro for determing if a colloquial C++ version is being used.
// @returns  If the colloquial C++ version number is equal to `ver_num`.
#define USING_CPP(ver_num) CPP_V == ver_num

// @brief  A developer friendly macro for determining if a colloquial C++ version or its previous versions are being used.
// @returns  If the colloquial C++ version number is the equal to or larger than `ver_num`.
#define MIN_USING_CPP(ver_num) USING_CPP(98) ? USING_CPP(ver_num) : CPP_V >= ver_num

// cross-standard compatbility hacks
#if USING_CPP(98)
# define nullptr NULL
# define TYPEDEF_GENERIC(type) typedef type##98 type;

// A macro that automates the upsetting variadic syntax
# define VARARGS(...) _NARG(__VA_ARGS__), ##__VA_ARGS__
# define _NARG(...) _NARG_(__VA_ARGS__, _RSEQ_N())
# define _NARG_(...) _ARG_N(__VA_ARGS__)
# define _ARG_N( \
	_1, _2, _3, _4, _5, _6, _7, _8, _9,_10,  \
	_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
	_21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
	_31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
	_41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
	_51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
	_61,_62,_63,N,...) N
# define _RSEQ_N() \
	63,62,61,60,                   \
	59,58,57,56,55,54,53,52,51,50, \
	49,48,47,46,45,44,43,42,41,40, \
	39,38,37,36,35,34,33,32,31,30, \
	29,28,27,26,25,24,23,22,21,20, \
	19,18,17,16,15,14,13,12,11,10, \
	9,8,7,6,5,4,3,2,1,0	
	// [jas31415]: if you're looking to blame someone for the code above, blame C++98, not me XD
#endif /* 98 */
#if USING_CPP(11)
# define TYPEDEF_GENERIC(type) typedef type##11 type;
#endif /* 11 */
