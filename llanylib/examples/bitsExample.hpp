/*
 *	bitsExample.hpp
 *
 *	Created on: Sep 27, 2021
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#include "../bits.hpp"

#if !defined(LLANYLIB_EXAMPLES_BITSEXAMPLE_HPP_)
#define LLANYLIB_EXAMPLES_BITSEXAMPLE_HPP_

namespace llcpp {
namespace bits {

constexpr ui64 asdf_2_1 = transformToBaseV3(30ul, 8);

constexpr ui64 asdf_2_1 = transformTo8(30);
constexpr ui64 asdf_2_2 = transformTo8(31);
constexpr ui64 asdf_2_3 = transformTo8(32);
constexpr ui64 asdf_2_4 = transformTo8(33);

constexpr ui64 asdf_1_1 = transformTo32(30);
constexpr ui64 asdf_1_2 = transformTo32(31);
constexpr ui64 asdf_1_3 = transformTo32(32);
constexpr ui64 asdf_1_4 = transformTo32(33);

constexpr ui64 asdf_3_1 = transformTo64(30);
constexpr ui64 asdf_3_2 = transformTo64(31);
constexpr ui64 asdf_3_3 = transformTo64(32);
constexpr ui64 asdf_3_4 = transformTo64(33);

} // namespace bits
} // namespace traits

#endif // LLANYLIB_EXAMPLES_BITSEXAMPLE_HPP_
