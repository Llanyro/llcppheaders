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

/************************************* Base transformation *************************************/
constexpr ui64 transform_to_base_res = transformToBaseV3(30ul, 8);

constexpr ui64 transform_to_base_8_res_1 = transformTo8(30u);
constexpr ui64 transform_to_base_8_res_2 = transformTo8(31u);
constexpr ui64 transform_to_base_8_res_3 = transformTo8(32u);
constexpr ui64 transform_to_base_8_res_4 = transformTo8(33u);

static_assert(transform_to_base_8_res_1 == 32, "Error changed value");
static_assert(transform_to_base_8_res_2 == 32, "Error changed value");
static_assert(transform_to_base_8_res_3 == 32, "Error changed value");
static_assert(transform_to_base_8_res_4 == 40, "Error changed value");

constexpr ui64 transform_to_base_32_res_1 = transformTo32(30u);
constexpr ui64 transform_to_base_32_res_2 = transformTo32(31u);
constexpr ui64 transform_to_base_32_res_3 = transformTo32(32u);
constexpr ui64 transform_to_base_32_res_4 = transformTo32(33u);

static_assert(transform_to_base_32_res_1 == 32, "Error changed value");
static_assert(transform_to_base_32_res_2 == 32, "Error changed value");
static_assert(transform_to_base_32_res_3 == 32, "Error changed value");
static_assert(transform_to_base_32_res_4 == 64, "Error changed value");

constexpr ui64 transform_to_base_64_res_1 = transformTo64(30u);
constexpr ui64 transform_to_base_64_res_2 = transformTo64(31u);
constexpr ui64 transform_to_base_64_res_3 = transformTo64(32u);
constexpr ui64 transform_to_base_64_res_4 = transformTo64(33u);

static_assert(transform_to_base_64_res_1 == 64, "Error changed value");
static_assert(transform_to_base_64_res_2 == 64, "Error changed value");
static_assert(transform_to_base_64_res_3 == 64, "Error changed value");
static_assert(transform_to_base_64_res_4 == 64, "Error changed value");

/************************************* Type division *************************************/

template<class T, class U>
constexpr __LL_NODISCARD__ ll_bool_t cmp(const ByteExtender<T>& b, const U l, const U h) __LL_EXCEPT__ {
	return b.h == h && b.l == l;
}

/**************** UI16 ****************/

constexpr auto ui16_div_result_0 = ui16Divisor::div(10);
constexpr auto ui16_div_result_1 = ui16Divisor::div(256 * 2);

static_assert(cmp(ui16_div_result_0, 10, 0), "Error changed value");
static_assert(cmp(ui16_div_result_1, 0, 02), "Error changed value");

/**************** I16 ****************/

constexpr auto i16_div_result_0 = i16Divisor::div(10);
constexpr auto i16_div_result_1 = i16Divisor::div(255);
constexpr auto i16_div_result_2 = i16Divisor::div(256 * 2);

static_assert(cmp(i16_div_result_0, 10, 0), "Error changed value");
static_assert(cmp(i16_div_result_1, 127, 1), "Error changed value");
static_assert(cmp(i16_div_result_2, 0, 4), "Error changed value");

/**************** UI32 ****************/

constexpr auto ui32_div_result_0 = ui32Divisor::div(10);
constexpr auto ui32_div_result_1 = ui32Divisor::div(256 * 2);
constexpr auto ui32_div_result_2 = ui32Divisor::div(65535);
constexpr auto ui32_div_result_3 = ui32Divisor::div(65535 * 2);
constexpr auto ui32_div_result_4 = ui32Divisor::div(4294967295);

static_assert(cmp(ui32_div_result_0, 10, 0), "Error changed value");
static_assert(cmp(ui32_div_result_1, 512, 0), "Error changed value");
static_assert(cmp(ui32_div_result_2, 65535, 0), "Error changed value");
static_assert(cmp(ui32_div_result_3, 65534, 1), "Error changed value");
static_assert(cmp(ui32_div_result_4, 65535, 65535), "Error changed value");

/**************** I32 ****************/

constexpr auto i32_div_result_0 = i32Divisor::div(10);
constexpr auto i32_div_result_1 = i32Divisor::div(256 * 2);
constexpr auto i32_div_result_2 = i32Divisor::div(65535);
constexpr auto i32_div_result_3 = i32Divisor::div(65535 * 2);
constexpr auto i32_div_result_4 = i32Divisor::div(2147483647);

static_assert(cmp(i32_div_result_0, 10u, 0u), "Error changed value");
static_assert(cmp(i32_div_result_1, 512u, 0u), "Error changed value");
static_assert(cmp(i32_div_result_2, 32767u, 1u), "Error changed value");
static_assert(cmp(i32_div_result_3, 32766u, 3u), "Error changed value");
static_assert(cmp(i32_div_result_4, 32767u, 65535u), "Error changed value");

/**************** UI64 ****************/

constexpr auto ui64_div_result_0 = ui64Divisor::div(10ull);
constexpr auto ui64_div_result_1 = ui64Divisor::div(256ull * 2);
constexpr auto ui64_div_result_2 = ui64Divisor::div(65535ull);
constexpr auto ui64_div_result_3 = ui64Divisor::div(65535ull * 2);
constexpr auto ui64_div_result_4 = ui64Divisor::div(4294967295ull);
constexpr auto ui64_div_result_5 = ui64Divisor::div(4294967295 * 2);
constexpr auto ui64_div_result_6 = ui64Divisor::div(18446744073709551615);

static_assert(cmp(ui64_div_result_0, 10ull, 0ull), "Error changed value");
static_assert(cmp(ui64_div_result_1, 512ull, 0ull), "Error changed value");
static_assert(cmp(ui64_div_result_2, 65535ull, 0ull), "Error changed value");
static_assert(cmp(ui64_div_result_3, 131070ull, 0ull), "Error changed value");
static_assert(cmp(ui64_div_result_4, 4294967295ull, 0ull), "Error changed value");
static_assert(cmp(ui64_div_result_5, 4294967294ull, 1ull), "Error changed value");
static_assert(cmp(ui64_div_result_6, 4294967295ull, 4294967295ull), "Error changed value");

/**************** I64 ****************/

constexpr auto i64_div_result_0 = i64Divisor::div(10ll);
constexpr auto i64_div_result_1 = i64Divisor::div(256ll * 2);
constexpr auto i64_div_result_2 = i64Divisor::div(65535ll);
constexpr auto i64_div_result_3 = i64Divisor::div(65535ll * 2);
constexpr auto i64_div_result_4 = i64Divisor::div(4294967295ll);
constexpr auto i64_div_result_5 = i64Divisor::div(4294967295ll * 2);
constexpr auto i64_div_result_6 = i64Divisor::div(9223372036854775807);

static_assert(cmp(i64_div_result_0, 10ull, 0ull), "Error changed value");
static_assert(cmp(i64_div_result_1, 512ull, 0ull), "Error changed value");
static_assert(cmp(i64_div_result_2, 65535ull, 0ull), "Error changed value");
static_assert(cmp(i64_div_result_3, 131070ull, 0ull), "Error changed value");
static_assert(cmp(i64_div_result_4, 2147483647ull, 1ull), "Error changed value");
static_assert(cmp(i64_div_result_5, 2147483646ull, 3ull), "Error changed value");
static_assert(cmp(i64_div_result_6, 2147483647ull, 4294967295ull), "Error changed value");

} // namespace bits
} // namespace traits

#endif // LLANYLIB_EXAMPLES_BITSEXAMPLE_HPP_
