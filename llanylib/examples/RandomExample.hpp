//////////////////////////////////////////////
//	RandomExample.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 6.0							//
//////////////////////////////////////////////

#include "../Random.hpp"

#if !defined(LLANYLIB_EXAMPLES_RANDOMEXAMPLE_)
#define LLANYLIB_EXAMPLES_RANDOMEXAMPLE_

namespace llcpp {
namespace meta {

constexpr f32 rf32_0 = Random().rand<f32>();
constexpr f32 rf32_1 = Random(1).rand<f32>();
constexpr f32 rf32_2 = Random(2).rand<f32>();
constexpr f32 rf32_3 = rf32_2 + 50000;
constexpr f32 generateOtherPattern() {
	Random rd(2);
	ll_bool_t res = LL_FALSE;
	return rd.rand<f32>(&res);
}
constexpr f32 rf32_4 = generateOtherPattern();

constexpr ui64 rui64_0 = Random().rand<ui64>();
constexpr ui64 rui64_1 = Random("Hola mundo!").rand<ui64>();
constexpr i64 ri64_0 = Random(rui64_0).rand<i64>();
constexpr i8 ri8_0 = Random(rui64_0).rand<i8>();

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXAMPLES_RANDOMEXAMPLE_
