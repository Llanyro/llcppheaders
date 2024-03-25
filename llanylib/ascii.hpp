/*
 *	ascii.hpp
 *
 *	Author: Francisco Julio Ruiz Fernandez
 *	Author: llanyro
 *
 *	Version: 4.2
 */

#if defined(LLANYLIB_ASCII_HPP_) // Guard && version protector
#if LLANYLIB_ASCII_MAYOR_ != 4 || LLANYLIB_ASCII_MINOR_ < 2
#error "ArrayView.hpp version error!"
#endif // LLANYLIB_ASCII_MAYOR_ || LLANYLIB_ASCII_MINOR_

#else !defined(LLANYLIB_ASCII_HPP_)
#define LLANYLIB_ASCII_HPP_
#define LLANYLIB_ASCII_MAYOR_ 4
#define LLANYLIB_ASCII_MINOR_ 2

#include "ArrayView.hpp"

namespace llcpp {
namespace ascii {

constexpr ui8 MAYUS_MINUS_DIFF = 'a' - 'A';

constexpr ArrayView ALPHABET_MINUS_CHARS = ArrayView("abcdefghijklmnopqrstuvwxyz", LL_TRUE);
constexpr ArrayView ALPHABET_MAYUS_CHARS = ArrayView("ABCDEFGHIJKLMNOPQRSTUVWXYZ", LL_TRUE);
constexpr ArrayView ALPHABET_NUMS_CHARS = ArrayView("0123456789", LL_TRUE);
constexpr ArrayView ALPHABET_MAYUS_MINUS_CHARS = ArrayView("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", LL_TRUE);
constexpr ArrayView ALPHABET_CHARS = ArrayView("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", LL_TRUE);
constexpr ArrayView SPECIAL_CHARS = ArrayView("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", LL_TRUE);
constexpr ArrayView ALL_VISIBLE_CHARS = ArrayView("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", LL_TRUE);

constexpr ArrayView NULLPTR = ArrayView("nullptr", LL_TRUE);

constexpr ArrayView TRUE_STR = ArrayView("True", LL_TRUE);
constexpr ArrayView FALSE_STR = ArrayView("False", LL_TRUE);

} // namespace ascii
} // namespace llcpp

#endif // LLANYLIB_ASCII_HPP_
