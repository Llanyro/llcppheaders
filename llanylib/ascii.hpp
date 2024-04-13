//////////////////////////////////////////////
//	ascii.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 4.2							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ASCII_HPP_) // Guard && version protector
	#if LLANYLIB_ASCII_MAYOR_ != 4 || LLANYLIB_ASCII_MINOR_ < 2
		#error "ascii.hpp version error!"
	#endif // LLANYLIB_ASCII_MAYOR_ || LLANYLIB_ASCII_MINOR_

#else !defined(LLANYLIB_ASCII_HPP_)
#define LLANYLIB_ASCII_HPP_
#define LLANYLIB_ASCII_MAYOR_ 4
#define LLANYLIB_ASCII_MINOR_ 2

#include "StringView.hpp"

namespace llcpp {
namespace ascii {

constexpr ui8 MAYUS_MINUS_DIFF = 'a' - 'A';

constexpr auto ALPHABET_MINUS_CHARS = StringView("abcdefghijklmnopqrstuvwxyz");
constexpr auto ALPHABET_MAYUS_CHARS = StringView("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
constexpr auto ALPHABET_NUMS_CHARS = StringView("0123456789");
constexpr auto ALPHABET_MAYUS_MINUS_CHARS = StringView("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
constexpr auto ALPHABET_CHARS = StringView("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
constexpr auto SPECIAL_CHARS = StringView("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
constexpr auto ALL_VISIBLE_CHARS = StringView("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");

constexpr auto NULLPTR = StringView("nullptr");

constexpr auto TRUE_STR = StringView("True");
constexpr auto FALSE_STR = StringView("False");

} // namespace ascii
} // namespace llcpp

#endif // LLANYLIB_ASCII_HPP_
