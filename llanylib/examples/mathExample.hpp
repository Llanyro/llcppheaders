//////////////////////////////////////////////
//	mathExample.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#include "../math.hpp"

#if !defined(LLANYLIB_EXAMPLES_MATHEXAMPLE_)
#define LLANYLIB_EXAMPLES_MATHEXAMPLE_

namespace llcpp {
namespace math {

constexpr auto res1 = is_even<int>(9);
constexpr auto res2 = is_even<int>(8);
constexpr auto res3 = is_odd<int>(9);
constexpr auto res4 = is_odd<int>(8);

} // namespace math
} // namespace llcpp

#endif // LLANYLIB_EXAMPLES_MATHEXAMPLE_
