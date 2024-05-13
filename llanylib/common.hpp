//////////////////////////////////////////////
//	common.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_COMMON_HPP_) // Guard && version protector
	#if LLANYLIB_COMMON_MAYOR_ != 5 || LLANYLIB_COMMON_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "common.hpp version error!"
		#else
			#error "common.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_COMMON_MAYOR_ || LLANYLIB_COMMON_MINOR_

#else !defined(LLANYLIB_COMMON_HPP_)
#define LLANYLIB_COMMON_HPP_
#define LLANYLIB_COMMON_MAYOR_ 5
#define LLANYLIB_COMMON_MINOR_ 0

#include "types.hpp"

namespace llcpp {
namespace common {

template<class T>
constexpr void simple_swap(T& v1, T& v2) {
	T tmp = std::move(v1);
	v1 = std::move(v2);
	v2 = std::move(tmp);
}

template<class T, class U = T>
constexpr cmp_t compare_with_operators(T v1, U v2) {
	static_assert(traits::has_no_equal_operator_v<T>, "Error, <T> object has no operator!=()");
	static_assert(traits::has_greater_operator_v<T>, "Error, <T> object has no operator>()");

	if (v1 == v2) return 0;
	else if (v1 > v2) return 1;
	else return -1;
}

template<class T, class U>
constexpr ll_bool_t simple_equals(T v1, U v2) {
	//static_assert(traits::has_equal_operator_v<T>, "Error, <T> object has no operator==()");
	return v1 == v2;
}

} // namespace common
} // namespace llcpp

#endif // LLANYLIB_COMMON_HPP_
