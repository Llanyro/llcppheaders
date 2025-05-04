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

#include "../utils_base/ArrayBase.hpp"

#define __LL_GENERIC_CHAR_GENERATOR(name, character)						\
	template <class T>														\
	__LL_VAR_INLINE__ constexpr T name = ::llcpp::ZERO_VALUE<T>;			\
	template <>																\
	__LL_VAR_INLINE__ constexpr ll_char_t name<ll_char_t> = character;		\
	template <>																\
	__LL_VAR_INLINE__ constexpr ll_wchar_t name<ll_wchar_t> = L##character

#define __LL_GENERIC_STRING_GENERATOR(name, string)							\
	__LL_VAR_INLINE__ constexpr ll_char_t CHAR_##name[] = string;			\
	__LL_VAR_INLINE__ constexpr ll_wchar_t WCHAR_##name[] = L##string

namespace llcpp {
namespace meta {
namespace characters {

__LL_GENERIC_CHAR_GENERATOR(A, 'A');
__LL_GENERIC_CHAR_GENERATOR(B, 'B');
__LL_GENERIC_CHAR_GENERATOR(MINUS, '-');
__LL_GENERIC_CHAR_GENERATOR(PLUS, '+');

} // namespace strings
namespace strings {

__LL_GENERIC_STRING_GENERATOR(NUMBERS, "0123456789");
__LL_GENERIC_STRING_GENERATOR(ALPHABET_MAYUS, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
__LL_GENERIC_STRING_GENERATOR(ALPHABET_MINUS, "abcdefghijklmnopqrstuvwxyz");
__LL_GENERIC_STRING_GENERATOR(SPECIAL, "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");

__LL_GENERIC_STRING_GENERATOR(ALPHABET_MAYUS_MINUS, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
__LL_GENERIC_STRING_GENERATOR(ALPHABET_MAYUS_MINUS_NUMBERS, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
__LL_GENERIC_STRING_GENERATOR(ALPHABET_MAYUS_MINUS_NUMBERS_SPECIAL, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");

} // namespace strings
} // namespace meta
} // namespace llcpp

#undef __LL_GENERIC_CHAR_GENERATOR
#undef __LL_GENERIC_STRING_GENERATOR

#endif // LLANYLIB_STRINGS_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_ARRAYBASE_HPP_)

#define __LL_GENERIC_ARRAY_GENERATOR(name)																								\
	template<class T>																													\
	__LL_VAR_INLINE__ constexpr T name					= ::llcpp::ZERO_VALUE<T>;														\
	template<>																															\
	__LL_VAR_INLINE__ constexpr auto name<ll_char_t>	= ::llcpp::meta::utils::cStr<>  ARR_PREP(::llcpp::meta::strings::CHAR_##name);	\
	template<>																															\
	__LL_VAR_INLINE__ constexpr auto name<ll_wchar_t>	= ::llcpp::meta::utils::cwStr<> ARR_PREP(::llcpp::meta::strings::WCHAR_##name)

namespace llcpp {
namespace meta {
namespace arrays {

__LL_GENERIC_ARRAY_GENERATOR(NUMBERS);
__LL_GENERIC_ARRAY_GENERATOR(ALPHABET_MAYUS);
__LL_GENERIC_ARRAY_GENERATOR(ALPHABET_MINUS);
__LL_GENERIC_ARRAY_GENERATOR(SPECIAL);

__LL_GENERIC_ARRAY_GENERATOR(ALPHABET_MAYUS_MINUS);
__LL_GENERIC_ARRAY_GENERATOR(ALPHABET_MAYUS_MINUS_NUMBERS);
__LL_GENERIC_ARRAY_GENERATOR(ALPHABET_MAYUS_MINUS_NUMBERS_SPECIAL);

} // namespace arrays
} // namespace meta
} // namespace llcpp

#undef __LL_GENERIC_ARRAY_GENERATOR

	#endif // LLANYLIB_ARRAYBASE_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
