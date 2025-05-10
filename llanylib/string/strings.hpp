//////////////////////////////////////////////
//	strings.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_STRINGS_HPP_) // Guard && version protector
	#if LLANYLIB_STRINGS_MAYOR_ != 12 || LLANYLIB_STRINGS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "strings.hpp version error!"
		#else
			#error "strings.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_STRINGS_MAYOR_ || LLANYLIB_STRINGS_MINOR_

#else
	#define LLANYLIB_STRINGS_HPP_
	#define LLANYLIB_STRINGS_MAYOR_ 12
	#define LLANYLIB_STRINGS_MINOR_ 0

#include "../traits_base/type_traits.hpp"

#include "../utils/ArrayBase.hpp"

#define __LL_GENERIC_CHAR_GENERATOR(name, character)								\
	template <class T>																\
	__LL_VAR_INLINE__ constexpr T name = ::llcpp::ZERO_VALUE<T>;					\
	template <>																		\
	__LL_VAR_INLINE__ constexpr ll_char_t name<ll_char_t> = character;				\
	template <>																		\
	__LL_VAR_INLINE__ constexpr ll_uchar_t name<ll_uchar_t> = character;			\
	template <>																		\
	__LL_VAR_INLINE__ constexpr ll_wchar_t name<ll_wchar_t> = __LL_L##character;	\
	template <>																		\
	__LL_VAR_INLINE__ constexpr ll_char16_t name<ll_char16_t> = __LL_u##character;	\
	template <>																		\
	__LL_VAR_INLINE__ constexpr ll_char32_t name<ll_char32_t> = __LL_U##character

#define __LL_GENERIC_STRING_GENERATOR(name, string)								\
	__LL_VAR_INLINE__ constexpr ll_char_t CHAR_##name[] = string;				\
	__LL_VAR_INLINE__ constexpr ll_uchar_t UCHAR_##name[] = string;				\
	__LL_VAR_INLINE__ constexpr ll_wchar_t WCHAR_##name[] = __LL_L##string;		\
	__LL_VAR_INLINE__ constexpr ll_char16_t CHAR16_##name[] = __LL_u##string;	\
	__LL_VAR_INLINE__ constexpr ll_char32_t CHAR32_##name[] = __LL_U##string

namespace llcpp {
namespace meta {
namespace characters {

__LL_GENERIC_CHAR_GENERATOR(A, 'A');
__LL_GENERIC_CHAR_GENERATOR(B, 'B');
__LL_GENERIC_CHAR_GENERATOR(MINUS, '-');
__LL_GENERIC_CHAR_GENERATOR(PLUS, '+');

} // namespace strings
namespace strings {

__LL_GENERIC_STRING_GENERATOR(NUMBERS,								"0123456789");
__LL_GENERIC_STRING_GENERATOR(ALPHABET_MAYUS,						"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
__LL_GENERIC_STRING_GENERATOR(ALPHABET_MINUS,						"abcdefghijklmnopqrstuvwxyz");
__LL_GENERIC_STRING_GENERATOR(SPECIAL,								"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");

__LL_GENERIC_STRING_GENERATOR(ALPHABET_MAYUS_MINUS,					"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
__LL_GENERIC_STRING_GENERATOR(ALPHABET_MAYUS_MINUS_NUMBERS,			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
__LL_GENERIC_STRING_GENERATOR(ALPHABET_MAYUS_MINUS_NUMBERS_SPECIAL, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");

} // namespace strings
namespace color {

__LL_GENERIC_STRING_GENERATOR(RESET,		"\033[0m");
__LL_GENERIC_STRING_GENERATOR(BLACK,		"\033[30m");
__LL_GENERIC_STRING_GENERATOR(RED,			"\033[31m");
__LL_GENERIC_STRING_GENERATOR(GREEN,		"\033[32m");
__LL_GENERIC_STRING_GENERATOR(YELLOW,		"\033[33m");
__LL_GENERIC_STRING_GENERATOR(BLUE,			"\033[34m");
__LL_GENERIC_STRING_GENERATOR(MAGENTA,		"\033[35m");
__LL_GENERIC_STRING_GENERATOR(CYAN,			"\033[36m");
__LL_GENERIC_STRING_GENERATOR(WHITE,		"\033[37m");

__LL_GENERIC_STRING_GENERATOR(BG_RESET, 	"\033[49m");
__LL_GENERIC_STRING_GENERATOR(BG_BLACK, 	"\033[40m");
__LL_GENERIC_STRING_GENERATOR(BG_RED, 		"\033[41m");
__LL_GENERIC_STRING_GENERATOR(BG_GREEN, 	"\033[42m");
__LL_GENERIC_STRING_GENERATOR(BG_YELLOW, 	"\033[43m");
__LL_GENERIC_STRING_GENERATOR(BG_BLUE, 		"\033[44m");
__LL_GENERIC_STRING_GENERATOR(BG_MAGENTA, 	"\033[45m");
__LL_GENERIC_STRING_GENERATOR(BG_CYAN, 		"\033[46m");
__LL_GENERIC_STRING_GENERATOR(BG_WHITE, 	"\033[47m");

} // namespace color
} // namespace meta
} // namespace llcpp

#undef __LL_GENERIC_CHAR_GENERATOR
#undef __LL_GENERIC_STRING_GENERATOR

#endif // LLANYLIB_STRINGS_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_ARRAYBASE_HPP_)

#define __LL_GENERIC_ARRAY_GENERATOR(name, namesp)																							\
	template<class T>																														\
	__LL_VAR_INLINE__ constexpr T name					= ::llcpp::ZERO_VALUE<T>;															\
	template<>																																\
	__LL_VAR_INLINE__ constexpr auto name<ll_char_t>	= ::llcpp::meta::utils::cStr<>  ARR_PREP(::llcpp::meta::namesp::CHAR_##name);		\
	template<>																																\
	__LL_VAR_INLINE__ constexpr auto name<ll_uchar_t>	= ::llcpp::meta::utils::cuStr<> ARR_PREP(::llcpp::meta::namesp::UCHAR_##name);		\
	template<>																																\
	__LL_VAR_INLINE__ constexpr auto name<ll_wchar_t>	= ::llcpp::meta::utils::cwStr<> ARR_PREP(::llcpp::meta::namesp::WCHAR_##name);		\
	template<>																																\
	__LL_VAR_INLINE__ constexpr auto name<ll_char16_t>	= ::llcpp::meta::utils::cStr16<> ARR_PREP(::llcpp::meta::namesp::CHAR16_##name);	\
	template<>																																\
	__LL_VAR_INLINE__ constexpr auto name<ll_char32_t>	= ::llcpp::meta::utils::cStr32<> ARR_PREP(::llcpp::meta::namesp::CHAR32_##name)

namespace llcpp {
namespace meta {
namespace arrays {

__LL_GENERIC_ARRAY_GENERATOR(NUMBERS,								strings);
__LL_GENERIC_ARRAY_GENERATOR(ALPHABET_MAYUS,						strings);
__LL_GENERIC_ARRAY_GENERATOR(ALPHABET_MINUS,						strings);
__LL_GENERIC_ARRAY_GENERATOR(SPECIAL,								strings);

__LL_GENERIC_ARRAY_GENERATOR(ALPHABET_MAYUS_MINUS,					strings);
__LL_GENERIC_ARRAY_GENERATOR(ALPHABET_MAYUS_MINUS_NUMBERS,			strings);
__LL_GENERIC_ARRAY_GENERATOR(ALPHABET_MAYUS_MINUS_NUMBERS_SPECIAL,	strings);

namespace color {

__LL_GENERIC_ARRAY_GENERATOR(RESET,			color);
__LL_GENERIC_ARRAY_GENERATOR(BLACK,			color);
__LL_GENERIC_ARRAY_GENERATOR(RED,			color);
__LL_GENERIC_ARRAY_GENERATOR(GREEN,			color);
__LL_GENERIC_ARRAY_GENERATOR(YELLOW,		color);
__LL_GENERIC_ARRAY_GENERATOR(BLUE,			color);
__LL_GENERIC_ARRAY_GENERATOR(MAGENTA,		color);
__LL_GENERIC_ARRAY_GENERATOR(CYAN,			color);
__LL_GENERIC_ARRAY_GENERATOR(WHITE,			color);

__LL_GENERIC_ARRAY_GENERATOR(BG_RESET,		color);
__LL_GENERIC_ARRAY_GENERATOR(BG_BLACK,		color);
__LL_GENERIC_ARRAY_GENERATOR(BG_RED,		color);
__LL_GENERIC_ARRAY_GENERATOR(BG_GREEN,		color);
__LL_GENERIC_ARRAY_GENERATOR(BG_YELLOW,		color);
__LL_GENERIC_ARRAY_GENERATOR(BG_BLUE,		color);
__LL_GENERIC_ARRAY_GENERATOR(BG_MAGENTA,	color);
__LL_GENERIC_ARRAY_GENERATOR(BG_CYAN,		color);
__LL_GENERIC_ARRAY_GENERATOR(BG_WHITE,		color);

} // namespace color
} // namespace arrays
} // namespace meta
} // namespace llcpp

#undef __LL_GENERIC_ARRAY_GENERATOR

	#endif // LLANYLIB_ARRAYBASE_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
