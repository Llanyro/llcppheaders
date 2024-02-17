/*
 *	ascii.hpp
 *
 *	Created on: Sep 27, 2021
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLANYLIB_EXPRESIONS_ASCII_HPP_
#define LLANYLIB_EXPRESIONS_ASCII_HPP_

#include "../ArrayView.hpp"

namespace llcpp {
namespace ascii {

constexpr ui8 MAYUS_MINUS_DIFF = 'a' - 'A';

constexpr ArrayView ALPHABET_MINUS_CHARS = "abcdefghijklmnopqrstuvwxyz";
constexpr ArrayView ALPHABET_MAYUS_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
constexpr ArrayView ALPHABET_NUMS_CHARS = "0123456789";
constexpr ArrayView ALPHABET_MAYUS_MINUS_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
constexpr ArrayView ALPHABET_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
constexpr ArrayView SPECIAL_CHARS = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
constexpr ArrayView ALL_VISIBLE_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

constexpr ArrayView NULLPTR = "nullptr";

constexpr ArrayView TRUE_STR = "True";
constexpr ArrayView FALSE_STR = "False";

//template<ll_bool_t test>
//constexpr auto arr = std::conditional<test, TRUE_STR, FALSE_STR>;

} // namespace ascii
} // namespace llcpp

#endif // LLANYLIB_EXPRESIONS_ASCII_HPP_
