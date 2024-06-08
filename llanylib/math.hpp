//////////////////////////////////////////////
//	math.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_MATH_HPP_) // Guard && version protector
	#if LLANYLIB_MATH_MAYOR_ != 8 || LLANYLIB_MATH_MINOR_ < 0
		#error "math.hpp version error!"
	#endif // LLANYLIB_MATH_MAYOR_ || LLANYLIB_MATH_MINOR_

#else !defined(LLANYLIB_MATH_HPP_)
#define LLANYLIB_MATH_HPP_
#define LLANYLIB_MATH_MAYOR_ 8
#define LLANYLIB_MATH_MINOR_ 0

#include "traits.hpp"

#undef min
#undef max

namespace llcpp {
namespace meta {
namespace math {

template<class U, class W = traits::cinput<U>>
__LL_NODISCARD__ constexpr ll_bool_t is_odd(W value) __LL_EXCEPT__ {
	return static_cast<ll_bool_t>(value & 1);
}
template<class U, class W = traits::cinput<U>>
__LL_NODISCARD__ constexpr ll_bool_t is_even(W value) __LL_EXCEPT__ {
	return !is_odd<U, W>(value);
}
template<class U, class W = traits::cinput<U>>
__LL_NODISCARD__ constexpr U min(W value1, W value2) __LL_EXCEPT__ {
	return (value1 > value2) ? value2 : value1;
}
template<class U, class W = traits::cinput<U>>
__LL_NODISCARD__ constexpr U max(W value1, W value2) __LL_EXCEPT__ {
	return (value1 > value2) ? value1 : value2;
}
template<class U, class W = traits::cinput<U>>
__LL_NODISCARD__ constexpr U minMax(W minVal, W value, W maxVal) __LL_EXCEPT__ {
	 return min(max(minVal, value), maxVal);
}
template<class U, class W = traits::cinput<U>>
__LL_NODISCARD__ constexpr ll_bool_t isBetween(W minVal, W value, W maxVal) __LL_EXCEPT__ {
	return (minVal <= value && value <= maxVal);
}
template<class U, U minVal, U maxVal, class W = traits::cinput<U>>
__LL_NODISCARD__ constexpr ll_bool_t isBetween(U val) __LL_EXCEPT__ {
	 return (minVal <= val && val <= maxVal);
}

template<class T>
__LL_NODISCARD__ constexpr i32 comparei32(const void* a, const void* b) __LL_EXCEPT__ {
	 return *reinterpret_cast<const T*>(a) - *reinterpret_cast<const T*>(b);
}
template<class T>
__LL_NODISCARD__ constexpr ll_bool_t compareBool(const void* a, const void* b) __LL_EXCEPT__ {
	 return *reinterpret_cast<const T*>(a) == *reinterpret_cast<const T*>(b);
}

//template<class T>
//__LL_CONSTEVAL__ T abs(const T& v1, const T& v2) __LL_EXCEPT__ {
//	 return (v1 > v2) ? v1 - v2 : v2 - v1;
//}
//template<>
//__LL_CONSTEVAL__ ui64 abs(const ui64& v1, const ui64& v2) {
//	 return (v1 > v2) ? v1 - v2 : v2 - v1;
//}
//template<>
//__LL_CONSTEVAL__ ui128 abs(const ui128& v1, const ui128& v2) __LL_EXCEPT__ {
//	 return { abs(v1.first, v2.first), abs(v1.second, v2.second) };
//}

} // namespace math
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_MATH_HPP_
