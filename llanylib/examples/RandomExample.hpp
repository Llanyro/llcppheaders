//////////////////////////////////////////////
//	RandomExample.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#include "../StandardRandom.hpp"

#if !defined(LLANYLIB_EXAMPLES_RANDOMEXAMPLE_)
#define LLANYLIB_EXAMPLES_RANDOMEXAMPLE_

namespace llcpp {
namespace meta {

constexpr f32 rf32_0 = STANDARD_RANDOM().rand<f32>();
constexpr f32 rf32_1 = STANDARD_RANDOM(1).rand<f32>();
constexpr f32 rf32_2 = STANDARD_RANDOM(2).rand<f32>();
constexpr f32 rf32_3 = rf32_2 + 50000;
constexpr f32 generateOtherPattern() {
	Random rd = STANDARD_RANDOM(2);
	ll_bool_t res = LL_FALSE;
	return rd.rand<f32>(&res);
}
constexpr f32 rf32_4 = generateOtherPattern();

constexpr ui64 rui64_0 = STANDARD_RANDOM().rand<ui64>();
constexpr ui64 rui64_1 = STANDARD_RANDOM("Hola mundo!").rand<ui64>();
constexpr i64 ri64_0 = STANDARD_RANDOM(rui64_0).rand<i64>();
constexpr i8 ri8_0 = STANDARD_RANDOM(rui64_0).rand<i8>();

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXAMPLES_RANDOMEXAMPLE_
