//////////////////////////////////////////////
//	bitsExample.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#include "../bits.hpp"

#if !defined(LLANYLIB_EXAMPLES_BITSEXAMPLE_HPP_)
#define LLANYLIB_EXAMPLES_BITSEXAMPLE_HPP_

namespace llcpp {
namespace bits {

///////////////////////////////////////////////// Base transformation /////////////////////////////////////////////////
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

///////////////////////////////////////////////// Type division /////////////////////////////////////////////////
/*
template<class _TypeDivision, class U, class W = traits::template_types<U>::cinput>
__LL_NODISCARD__ constexpr ll_bool_t check(W value) __LL_EXCEPT__ {
	auto val = _TypeDivision::div(value);
	return (val.h << _TypeDivision::__HALF_BITS) + val.l;
}

#pragma region UI16
static_assert(check<ui16Divisor, ui16>(10), "Error changed value");
static_assert(check<ui16Divisor, ui16>(256 * 2), "Error changed value");
static_assert(check<ui16Divisor, ui16>(std::numeric_limits<ui16>::max()), "Error changed value");

constexpr auto ui16Divisor_val0 = ui16Divisor::div(std::numeric_limits<ui16>::max());
constexpr auto ui16Divisor_val1 = std::numeric_limits<ui16>::max();

#pragma endregion
#pragma region I16

//static_assert(check<i16Divisor, i16>(10), "Error changed value");
//static_assert(check<i16Divisor, i16>(255), "Error changed value");
//static_assert(check<i16Divisor, i16>(256 * 2), "Error changed value");
//static_assert(check<i16Divisor, i16>(std::numeric_limits<i16>::max()), "Error changed value");
//
//constexpr auto ui16Divisor_val1 = i16Divisor::div(std::numeric_limits<i16>::max());
//constexpr auto ui16Divisor_val3 = std::numeric_limits<ui8>::max();
//constexpr auto ui16Divisor_val3 = std::numeric_limits<ui8>::max();
//
//constexpr auto ui16Divisor_val3 = std::numeric_limits<i16>::max();
//constexpr auto ui16Divisor_val4 = std::numeric_limits<i16>::max() & I8_MAX;
//constexpr auto ui16Divisor_val4 = ((I8_MAX << 7) * 2) + I8_MAX * 2;
//constexpr auto ui16Divisor_val5 = std::numeric_limits<i16>::max() >> 7;

#pragma endregion
#pragma region UI32
static_assert(check<ui32Divisor, ui32>(10), "Error changed value");
static_assert(check<ui32Divisor, ui32>(256 * 2), "Error changed value");
static_assert(check<ui32Divisor, ui32>(65535), "Error changed value");
static_assert(check<ui32Divisor, ui32>(65535 * 2), "Error changed value");
static_assert(check<ui32Divisor, ui32>(2147483647), "Error changed value");
static_assert(check<ui32Divisor, ui32>(4294967295u), "Error changed value");
static_assert(check<ui32Divisor, ui32>(std::numeric_limits<ui32>::max()), "Error changed value");

#pragma endregion
#pragma region I32

//static_assert(check<i32Divisor, i32>(10), "Error changed value");
//static_assert(check<i32Divisor, i32>(256 * 2), "Error changed value");
//static_assert(check<i32Divisor, i32>(65535), "Error changed value");
//static_assert(check<i32Divisor, i32>(65535 * 2), "Error changed value");
//static_assert(check<i32Divisor, i32>(2147483647), "Error changed value");
//
//constexpr auto i32_div_result_0 = i32Divisor::div(10);
//constexpr auto i32_div_result_1 = i32Divisor::div(256 * 2);
//constexpr auto i32_div_result_2 = i32Divisor::div(65535);
//constexpr auto i32_div_result_3 = i32Divisor::div(65535 * 2);
//constexpr auto i32_div_result_4 = i32Divisor::div(2147483647);

//constexpr i64 asdf1 = 2147483647 & I16_MAX;
//constexpr i64 asdf2 = (2147483647 & I32_MAX) >> 15;
////constexpr i64 asdf2 = 2147483647 >> 15;
//
//constexpr i64 asdf3 = asdf2 * asdf1;
//static_assert(asdf3 == 2147483647);
//
//
//static_assert(cmp(i32_div_result_0, 10u, 0u), "Error changed value");
//static_assert(cmp(i32_div_result_1, 512u, 0u), "Error changed value");
//static_assert(cmp(i32_div_result_2, 32767u, 1u), "Error changed value");
//static_assert(cmp(i32_div_result_3, 32766u, 3u), "Error changed value");
//static_assert(cmp(i32_div_result_4, 32767u, 65535u), "Error changed value");

#pragma endregion
#pragma region UI64
static_assert(check<ui64Divisor, ui64>(10ull), "Error changed value");
static_assert(check<ui64Divisor, ui64>(256ull * 2), "Error changed value");
static_assert(check<ui64Divisor, ui64>(65535ull), "Error changed value");
static_assert(check<ui64Divisor, ui64>(65535ull * 2), "Error changed value");
static_assert(check<ui64Divisor, ui64>(4294967295ull), "Error changed value");
static_assert(check<ui64Divisor, ui64>(4294967295 * 2), "Error changed value");
static_assert(check<ui64Divisor, ui64>(18446744073709551615), "Error changed value");


constexpr ui64 asdf = std::numeric_limits<ui32>::max();
constexpr ui64 asdf2 = asdf << 32;

constexpr ui64 asdf9 = std::numeric_limits<ui64>::max();

constexpr auto ui64_div_result_0 = ui64Divisor::div(10ull);
constexpr auto ui64_div_result_1 = ui64Divisor::div(256ull * 2);
constexpr auto ui64_div_result_2 = ui64Divisor::div(65535ull);
constexpr auto ui64_div_result_3 = ui64Divisor::div(65535ull * 2);
constexpr auto ui64_div_result_4 = ui64Divisor::div(4294967295ull);
constexpr auto ui64_div_result_5 = ui64Divisor::div(4294967295 * 2);
constexpr auto ui64_div_result_6 = ui64Divisor::div(18446744073709551615);

static_assert(cmp(ui64_div_result_0, 10ull, ZERO_UI64), "Error changed value");
static_assert(cmp(ui64_div_result_1, 512ull, ZERO_UI64), "Error changed value");
static_assert(cmp(ui64_div_result_2, 65535ull, ZERO_UI64), "Error changed value");
static_assert(cmp(ui64_div_result_3, 131070ull, ZERO_UI64), "Error changed value");
static_assert(cmp(ui64_div_result_4, 4294967295ull, ZERO_UI64), "Error changed value");
static_assert(cmp(ui64_div_result_5, 4294967294ull, 1ull), "Error changed value");
static_assert(cmp(ui64_div_result_6, 4294967295ull, 4294967295ull), "Error changed value");

#pragma endregion
#pragma region I64
//constexpr auto i64_div_result_0 = i64Divisor::div(10ll);
//constexpr auto i64_div_result_1 = i64Divisor::div(256ll * 2);
//constexpr auto i64_div_result_2 = i64Divisor::div(65535ll);
//constexpr auto i64_div_result_3 = i64Divisor::div(65535ll * 2);
//constexpr auto i64_div_result_4 = i64Divisor::div(4294967295ll);
//constexpr auto i64_div_result_5 = i64Divisor::div(4294967295ll * 2);
//constexpr auto i64_div_result_6 = i64Divisor::div(9223372036854775807);
//
//static_assert(cmp(i64_div_result_0, 10ull, ZERO_UI64), "Error changed value");
//static_assert(cmp(i64_div_result_1, 512ull, ZERO_UI64), "Error changed value");
//static_assert(cmp(i64_div_result_2, 65535ull, ZERO_UI64), "Error changed value");
//static_assert(cmp(i64_div_result_3, 131070ull, ZERO_UI64), "Error changed value");
//static_assert(cmp(i64_div_result_4, 2147483647ull, 1ull), "Error changed value");
//static_assert(cmp(i64_div_result_5, 2147483646ull, 3ull), "Error changed value");
//static_assert(cmp(i64_div_result_6, 2147483647ull, 4294967295ull), "Error changed value");

#pragma endregion
*/

} // namespace bits
} // namespace traits

#endif // LLANYLIB_EXAMPLES_BITSEXAMPLE_HPP_
