/*
 * lllibbits.h
 *
 *  Created on: Nov 26, 2020
 *      Author: llanyro
 */

#ifndef LLCPP_HEADER_LLLIBBITS_H_
#define LLCPP_HEADER_LLLIBBITS_H_

#include "llanytypeslib.hpp"

namespace llcpp {
typedef ll_uchar_t ll_bitarray_t;
typedef ll_uchar_t ll_bits_t;
typedef ll_uchar_t ll_byte_t;
	
namespace header {
namespace bit {

template<class T, ui8 pos>
constexpr void set(T& value) { value |= static_cast<T>(1 << pos); }
template<class T, ui8 pos>
constexpr ui8 get(T value) { return (value >> pos) & 1; }
template<class T, ui8 pos>
constexpr void clear(T& value) { value &= ~(1 << pos); }
template<class T, ui8 base>
constexpr T transformToBaseV2(T value) { return (value & (0xFFFFFFFFFFFFFFFF - base - 1)) + base; }

template<class T>
constexpr T transformTo64(T value) { return transformToBaseV2<T, 64>(value); }
template<class T>
constexpr T transformTo32(T value) { return transformToBaseV2<T, 32>(value); }
template<class T>
constexpr T transformTo8(T value) { return transformToBaseV2<T, 8>(value); }

// Sets bit pos 0
template<class T>
constexpr void set(T& value) { set<T, 0>(value); }
// Gets bit pos 0
template<class T>
constexpr ui8 get(T value) { return get<T, 0>(value); }
// Clear bit pos 0
template<class T>
constexpr void clear(T& value) { return clear<T, 0>(value); }

constexpr ui8 BITARRAY_LEN = 8;

} /* namespace bit */
} /* namespace header */
} /* namespace llcpp */

namespace bits = llcpp::header::bit;

#endif /* LLCPP_HEADER_LLLIBBITS_H_ */
