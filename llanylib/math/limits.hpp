//////////////////////////////////////////////
//	limits.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_MATHLIMITS_HPP_) // Guard && version protector
	#if LLANYLIB_MATHLIMITS_MAYOR_ != 10 || LLANYLIB_MATHLIMITS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "limits.hpp version error!"
		#else
			#error "limits.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_MATHLIMITS_MAYOR_ || LLANYLIB_MATHLIMITS_MINOR_

#else !defined(LLANYLIB_MATHLIMITS_HPP_)
#define LLANYLIB_MATHLIMITS_HPP_
#define LLANYLIB_MATHLIMITS_MAYOR_ 10
#define LLANYLIB_MATHLIMITS_MINOR_ 0

#include "../traits/traits_type_update.hpp"

namespace llcpp {
namespace meta {
namespace math {

template<class T>
__LL_VAR_INLINE__ constexpr T MAX_VALUE =
	traits::conditional_value_simple_v<
		std::is_unsigned_v<T>,
		T,
		T(-1),
		((MAX_VALUE<traits::type_signed<T, llcpp::FALSE>>) >> 1)
	>;

template<class T>
__LL_VAR_INLINE__ constexpr T MIN_VALUE = MAX_VALUE<T> + 1;

template<class T>
__LL_VAR_INLINE__ constexpr T ZERO_VALUE = traits::type_selection<llcpp::Emptyclass>::get_conincidence<
	T,
	traits::double_type_container<i8,	std::integral_constant<i8, 0>>,
	traits::double_type_container<i16,	std::integral_constant<i16, 0>>,
	traits::double_type_container<i32,	std::integral_constant<i32, 0>>,
	traits::double_type_container<i64,	std::integral_constant<i64, 0ll>>,
	//traits::double_type_container<i128, std::integral_constant<i128, llcpp::ZERO_I128>>,
	//traits::double_type_container<i256, std::integral_constant<i256, llcpp::ZERO_I256>>,

	traits::double_type_container<u8,	std::integral_constant<u8, 0u>>,
	traits::double_type_container<u16,	std::integral_constant<u16, 0u>>,
	traits::double_type_container<u32,	std::integral_constant<u32, 0u>>,
	traits::double_type_container<u64,	std::integral_constant<u64, 0ull>>,
	//traits::double_type_container<u128,	std::integral_constant<u128, llcpp::ZERO_U128>>,
	//traits::double_type_container<u256,	std::integral_constant<u256, llcpp::ZERO_U256>>,

	traits::double_type_container<f32,	std::integral_constant<f32, 0.0f>>,
	traits::double_type_container<f64,	std::integral_constant<f64, 0.0>>,
	traits::double_type_container<f128,	std::integral_constant<f128, 0.0l>>,

	traits::double_type_container<ll_bool_t, std::integral_constant<ll_bool_t, llcpp::FALSE>>
>::value;

} // namespace math
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_MATHLIMITS_HPP_
