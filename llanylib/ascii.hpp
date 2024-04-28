//////////////////////////////////////////////
//	ascii.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ASCII_HPP_) // Guard && version protector
	#if LLANYLIB_ASCII_MAYOR_ != 5 || LLANYLIB_ASCII_MINOR_ < 0
		#error "ascii.hpp version error!"
	#endif // LLANYLIB_ASCII_MAYOR_ || LLANYLIB_ASCII_MINOR_

#else !defined(LLANYLIB_ASCII_HPP_)
#define LLANYLIB_ASCII_HPP_
#define LLANYLIB_ASCII_MAYOR_ 5
#define LLANYLIB_ASCII_MINOR_ 0

#include "StringView.hpp"

namespace llcpp {
namespace ascii {

constexpr ui8 MAYUS_MINUS_DIFF = 'a' - 'A';

constexpr auto ALPHABET_MINUS_CHARS = make_StringView("abcdefghijklmnopqrstuvwxyz");
constexpr auto ALPHABET_MAYUS_CHARS = make_StringView("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
constexpr auto ALPHABET_NUMS_CHARS = make_StringView("0123456789");
constexpr auto ALPHABET_MAYUS_MINUS_CHARS = make_StringView("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
constexpr auto ALPHABET_CHARS = make_StringView("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
constexpr auto SPECIAL_CHARS = make_StringView("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
constexpr auto ALL_VISIBLE_CHARS = make_StringView("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");

constexpr auto NULLPTR = make_StringView("nullptr");

constexpr auto TRUE_STR = make_StringView("True");
constexpr auto FALSE_STR = make_StringView("False");

} // namespace ascii
} // namespace llcpp

#endif // LLANYLIB_ASCII_HPP_
