//////////////////////////////////////////////
//	is_even.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ISEVEN_INCOMPLETE_HPP_)
	#if LLANYLIB_ISEVEN_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ISEVEN_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "is_even.hpp(incomplete) version error!"
		#else
			#error "is_even.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ISEVEN_INCOMPLETE_MAYOR_ || LLANYLIB_ISEVEN_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ISEVEN_INCOMPLETE_HPP_)
	#define LLANYLIB_ISEVEN_INCOMPLETE_HPP_
	#define LLANYLIB_ISEVEN_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ISEVEN_INCOMPLETE_MINOR_ 0

#include "is_even.hpp"

namespace llcpp {
namespace meta {
namespace math {	

template<class T>
__LL_NODISCARD__ constexpr ll_bool_t is_even(::llcpp::meta::traits::cinput<T> value) noexcept;

} // namespace math
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ISEVEN_HPP_)
	#if LLANYLIB_ISEVEN_MAYOR_ != 12 || LLANYLIB_ISEVEN_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "is_even.hpp version error!"
		#else
			#error "is_even.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ISEVEN_MAYOR_ || LLANYLIB_ISEVEN_MINOR_

#else
	#define LLANYLIB_ISEVEN_HPP_
	#define LLANYLIB_ISEVEN_MAYOR_ 12
	#define LLANYLIB_ISEVEN_MINOR_ 0

#include "is_odd.hpp"

namespace llcpp {
namespace meta {
namespace math {

template<class T>
__LL_NODISCARD__ constexpr ll_bool_t is_even(::llcpp::meta::traits::cinput<T> value) noexcept {
	return !::llcpp::meta::math::is_odd<T>(value);
}

static_assert(is_even<int>(9)								== ::llcpp::LL_FALSE,	"This should be odd");
static_assert(is_even<usize>(999999999ull)					== ::llcpp::LL_FALSE,	"This should be odd");
static_assert(is_even<::llcpp::meta::pair<int>>({ 9, 9 })	== ::llcpp::LL_FALSE,	"This should be odd");
static_assert(is_even<::llcpp::meta::pair<int>>({ 9, 2 })	== ::llcpp::LL_TRUE,	"This is not odd");

} // namespace math
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ISEVEN_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
