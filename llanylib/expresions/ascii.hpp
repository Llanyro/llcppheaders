//////////////////////////////////////////////
//	ascii.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_EXPRESIONS_ASCII_HPP_) // Guard && version protector
	#if LLANYLIB_EXPRESIONS_ASCII_MAYOR_ != 9 || LLANYLIB_EXPRESIONS_ASCII_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "ascii.hpp version error!"
		#else
			#error "ascii.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_EXPRESIONS_ASCII_MAYOR_ || LLANYLIB_EXPRESIONS_ASCII_MINOR_

#else !defined(LLANYLIB_EXPRESIONS_ASCII_HPP_)
#define LLANYLIB_EXPRESIONS_ASCII_HPP_
#define LLANYLIB_EXPRESIONS_ASCII_MAYOR_ 9
#define LLANYLIB_EXPRESIONS_ASCII_MINOR_ 0

#include "../types.hpp"
#include <string_view>

namespace llcpp {
namespace meta {
namespace ascii {

__LL_VAR_INLINE__ constexpr ui8 MAYUS_MINUS_DIFF = 'a' - 'A';

__LL_VAR_INLINE__ constexpr std::string_view ALPHABET_MINUS_CHARS = "abcdefghijklmnopqrstuvwxyz";
__LL_VAR_INLINE__ constexpr std::string_view ALPHABET_MAYUS_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
__LL_VAR_INLINE__ constexpr std::string_view ALPHABET_NUMS_CHARS = "0123456789";
__LL_VAR_INLINE__ constexpr std::string_view ALPHABET_MAYUS_MINUS_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
__LL_VAR_INLINE__ constexpr std::string_view ALPHABET_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
__LL_VAR_INLINE__ constexpr std::string_view SPECIAL_CHARS = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
__LL_VAR_INLINE__ constexpr std::string_view ALL_VISIBLE_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

namespace wide {

__LL_VAR_INLINE__ constexpr std::wstring_view ALPHABET_MINUS_CHARS = L"abcdefghijklmnopqrstuvwxyz";
__LL_VAR_INLINE__ constexpr std::wstring_view ALPHABET_MAYUS_CHARS = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
__LL_VAR_INLINE__ constexpr std::wstring_view ALPHABET_NUMS_CHARS = L"0123456789";
__LL_VAR_INLINE__ constexpr std::wstring_view ALPHABET_MAYUS_MINUS_CHARS = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
__LL_VAR_INLINE__ constexpr std::wstring_view ALPHABET_CHARS = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
__LL_VAR_INLINE__ constexpr std::wstring_view SPECIAL_CHARS = L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
__LL_VAR_INLINE__ constexpr std::wstring_view ALL_VISIBLE_CHARS = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

} // namespace wide
} // namespace ascii
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXPRESIONS_ASCII_HPP_
