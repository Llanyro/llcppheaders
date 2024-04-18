//////////////////////////////////////////////
//	common.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 4.2							//
//////////////////////////////////////////////

#if defined(LLANYLIB_COMMON_HPP_) // Guard && version protector
	#if LLANYLIB_COMMON_MAYOR_ != 4 || LLANYLIB_COMMON_MINOR_ < 2
		#error "common.hpp version error!"
	#endif // LLANYLIB_COMMON_MAYOR_ || LLANYLIB_COMMON_MINOR_

#else !defined(LLANYLIB_COMMON_HPP_)
#define LLANYLIB_COMMON_HPP_
#define LLANYLIB_COMMON_MAYOR_ 4
#define LLANYLIB_COMMON_MINOR_ 2

#include "types.hpp"

namespace llcpp {
namespace common {

template<class T>
constexpr void simple_swap(T& v1, T& v2) {
	T tmp = v1;
	v1 = v2;
	v2 = tmp;
}

template<class T>
constexpr cmp_t compare_with_operators(const T& v1, const T& v2) {
	if (v1 == v2) return 0;
	else if (v1 > v2) return 1;
	else return -1;
}

template<class T>
constexpr ll_bool_t simple_equals(const T& v1, const T& v2) {
	return v1 == v2;
}

} // namespace common
} // namespace llcpp

#endif // LLANYLIB_COMMON_HPP_
