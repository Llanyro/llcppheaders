//////////////////////////////////////////////
//	ascii.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_EXPRESIONS_ASCII_HPP_) // Guard && version protector
	#if LLANYLIB_EXPRESIONS_ASCII_MAYOR_ != 7 || LLANYLIB_EXPRESIONS_ASCII_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "ascii.hpp version error!"
		#else
			#error "ascii.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_EXPRESIONS_ASCII_MAYOR_ || LLANYLIB_EXPRESIONS_ASCII_MINOR_

#else !defined(LLANYLIB_EXPRESIONS_ASCII_HPP_)
#define LLANYLIB_EXPRESIONS_ASCII_HPP_
#define LLANYLIB_EXPRESIONS_ASCII_MAYOR_ 7
#define LLANYLIB_EXPRESIONS_ASCII_MINOR_ 0

#include "../ArrayView.hpp"

namespace llcpp {
namespace meta {
namespace ascii {

constexpr ui8 MAYUS_MINUS_DIFF = 'a' - 'A';

constexpr auto ALPHABET_MINUS_CHARS = make_StringView("abcdefghijklmnopqrstuvwxyz");
constexpr auto ALPHABET_MAYUS_CHARS = make_StringView("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
constexpr auto ALPHABET_NUMS_CHARS = make_StringView("0123456789");
constexpr auto ALPHABET_MAYUS_MINUS_CHARS = make_StringView("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
constexpr auto ALPHABET_CHARS = make_StringView("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
constexpr auto SPECIAL_CHARS = make_StringView("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
constexpr auto ALL_VISIBLE_CHARS = make_StringView("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");

namespace wide {

constexpr auto ALPHABET_MINUS_CHARS = make_StringView(L"abcdefghijklmnopqrstuvwxyz");
constexpr auto ALPHABET_MAYUS_CHARS = make_StringView(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
constexpr auto ALPHABET_NUMS_CHARS = make_StringView(L"0123456789");
constexpr auto ALPHABET_MAYUS_MINUS_CHARS = make_StringView(L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
constexpr auto ALPHABET_CHARS = make_StringView(L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
constexpr auto SPECIAL_CHARS = make_StringView(L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
constexpr auto ALL_VISIBLE_CHARS = make_StringView(L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");

} // namespace wide
} // namespace ascii
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXPRESIONS_ASCII_HPP_
