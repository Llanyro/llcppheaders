/*
 *	bits.hpp
 *
 *	Created on: Nov 26, 2020
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLANYLIB_EXPRESIONS_BITS_HPP_
#define LLANYLIB_EXPRESIONS_BITS_HPP_

#include "../types.hpp"

namespace llcpp {
	
namespace bits {

using bit_pos = ui8;

constexpr ui8 BITARRAY_LEN = 8;

constexpr ui8 SHIFT_2  = 1;
constexpr ui8 SHIFT_4  = 2;
constexpr ui8 SHIFT_8  = 3;
constexpr ui8 SHIFT_16 = 4;
constexpr ui8 SHIFT_32 = 5;
constexpr ui8 SHIFT_64 = 6;

constexpr ui8 MASK_2  = (1 << SHIFT_2) - 1;
constexpr ui8 MASK_4  = (1 << SHIFT_4) - 1;
constexpr ui8 MASK_8  = (1 << SHIFT_8) - 1;
constexpr ui8 MASK_16 = (1 << SHIFT_16) - 1;
constexpr ui8 MASK_32 = (1 << SHIFT_32) - 1;
constexpr ui8 MASK_64 = (1 << SHIFT_64) - 1;

} // namespace bits
} // namespace llcpp

#endif // LLANYLIB_EXPRESIONS_BITS_HPP_
