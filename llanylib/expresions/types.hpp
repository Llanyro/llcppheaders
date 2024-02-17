/*
 *	types.hpp
 *
 *	Created on: Feb 28, 2022
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLANYLIB_EXPRESIONS_TYPES_HPP_
#define LLANYLIB_EXPRESIONS_TYPES_HPP_

#include "../types.hpp"

namespace llcpp {

constexpr ll_bool_t LL_TRUE = true;
constexpr ll_bool_t LL_FALSE = false;

constexpr ui8 ZERO_UI8 = 0u;
constexpr ui16 ZERO_UI16 = 0u;
constexpr ui32 ZERO_UI32 = 0u;
constexpr ui64 ZERO_UI64 = 0ull;

constexpr i8 ZERO_I8 = 0;
constexpr i16 ZERO_I16 = 0;
constexpr i32 ZERO_I32 = 0;
constexpr i64 ZERO_I64 = 0ll;

constexpr f32 ZERO_F32 = 0.0f;
constexpr f64 ZERO_F64 = 0.0;
constexpr f128 ZERO_F128 = 0.0l;

} // namespace llcpp

#endif // LLANYLIB_EXPRESIONS_TYPES_HPP_
