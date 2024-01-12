/*
 *	lloperations.hpp
 *
 *	Created on: Jun 25, 2023
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLCPP_HEADER_LLOPERATIONS_HPP_
#define LLCPP_HEADER_LLOPERATIONS_HPP_

#include "llanytypeslib.hpp"

namespace llcpp {
namespace header {
namespace operations {

/*!
 *	@template True
 *	@brief Gets min value of 2 given values
 *
 *	@efficiency O(1)
 *	@time T(1)
 *	@memory M(1)
 *	@const eval
 *	@throw False
 *
 *	@param[in] v1 Object 1 to compare
 *	@param[in] v2 Object 2 to compare
 * 
 *	@templateparam T item type
 *
 *	@return Min value of 2 given values
 *
 *	@thread_safety This function may be called from any thread.
 *	@thread_protection This function is not protexted by mutex.
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup header
 *	@ingroup operations
 */
template<class __T>
__LL_NODISCARD__ LL_SHARED_LIB __LL_CONSTEXPR__ __T min(const __T v1, const __T v2) __LL_EXCEPT__ {
	 return (v1 > v2) ? v2 : v1;
}
/*!
 *	@template True
 *	@brief Gets max value of 2 given values
 *
 *	@efficiency O(1)
 *	@time T(1)
 *	@memory M(1)
 *	@const eval
 *	@throw False
 *
 *	@param[in] v1 Object 1 to compare
 *	@param[in] v2 Object 2 to compare
 * 
 *	@templateparam T item type
 *
 *	@return Max value of 2 given values
 *
 *	@thread_safety This function may be called from any thread.
 *	@thread_protection This function is not protexted by mutex.
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup header
 *	@ingroup operations
 */
template<class __T>
__LL_NODISCARD__ LL_SHARED_LIB __LL_CONSTEVAL__ __T max(const __T v1, const __T v2) __LL_EXCEPT__ {
	 return (v1 > v2) ? v1 : v2;
}

/*!
 *	@template True
 *	@brief Gets a value between 2 values
 * 
 *	By giving a ranged values, this function will calculate the value that "val" should have to not
 *	get out of bounds of minVal and maxVal
 *	Ex:
 *		 [0, 100] (val: 10) -> 10	| inbounds
 *		 [0, 100] (val: 101) -> 100	| outbounds
 *		 [0, 100] (val: -1) -> 0	| outbounds
 *
 *	@efficiency O(1)
 *	@time T(1)
 *	@memory M(1)
 *	@const eval
 *	@throw False
 *
 *	@param[in] minVal Min value that val can have
 *	@param[in] val Actual value of val
 *	@param[in] maxVal Max value that val can have
 *
 *	@templateparam T item type
 * 
 *	@return Value inbounds of "val"
 *
 *	@thread_safety This function may be called from any thread.
 *	@thread_protection This function is not protexted by mutex.
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup header
 *	@ingroup operations
 */
template<class __T>
__LL_NODISCARD__ LL_SHARED_LIB __LL_CONSTEVAL__ __T minMax(const __T minVal, const __T val, const __T maxVal) __LL_EXCEPT__ {
	 return min(max(minVal, val),maxVal);
}
/*!
 *	@template True
 *	@brief Checks if value is between 2 values
 *
 *	@efficiency O(1)
 *	@time T(1)
 *	@memory M(1)
 *	@const expr
 *	@throw False
 *
 *	@param[in] val Value to check 
 *
 *	@templateparam T item type
 *	@templateparam minVal Min value of range
 *	@templateparam maxVal Max value of range
 *
 *	@return Min value of 2 given values
 *
 *	@thread_safety This function may be called from any thread.
 *	@thread_protection This function is not protexted by mutex.
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup header
 *	@ingroup operations
 */
template<class __T, __T minVal, __T maxVal>
__LL_NODISCARD__ LL_SHARED_LIB __LL_CONSTEXPR__ ll_bool_t isBetween(const __T val) __LL_EXCEPT__ {
	 return (minVal <= val && val <= maxVal);
}

/*!
 *	@template True
 *	@brief Compares 2 objects with operator-()
 *
 *	@efficiency O(1)
 *	@time T(1)
 *	@memory M(1)
 *	@const expr
 *	@throw False
 *
 *	@param[in] a Item 1 to compare
 *	@param[in] a Item 2 to compare
 *
 *	@templateparam T item type
 *
 *	@return Value of sub b to a
 *
 *	@thread_safety This function may be called from any thread.
 *	@thread_protection This function is not protexted by mutex.
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup header
 *	@ingroup operations
 */
template<class __T>
__LL_NODISCARD__ LL_SHARED_LIB __LL_CONSTEXPR__ i32 comparei32(const void* a, const void* b) __LL_EXCEPT__ {
	 return *reinterpret_cast<const __T*>(a) - *reinterpret_cast<const __T*>(b);
}
/*!
 *	@template True
 *	@brief Compares 2 objects with operator==()
 *
 *	@efficiency O(1)
 *	@time T(1)
 *	@memory M(1)
 *	@const eval
 *	@throw False
 *
 *	@param[in] a Item 1 to compare
 *	@param[in] a Item 2 to compare
 *
 *	@templateparam T item type
 *
 *	@return If a is equal to b
 *
 *	@thread_safety This function may be called from any thread.
 *	@thread_protection This function is not protexted by mutex.
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup header
 *	@ingroup operations
 */
template<class __T>
__LL_NODISCARD__ LL_SHARED_LIB __LL_CONSTEVAL__ ll_bool_t compareBool(const void* a, const void* b) __LL_EXCEPT__ {
	 return *reinterpret_cast<const __T*>(a) == *reinterpret_cast<const __T*>(b);
}

//template<class __T>
//__LL_CONSTEVAL__ T abs(const __T& v1, const __T& v2) __LL_EXCEPT__ {
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

} // namespace operations
} // namespace header
} // namespace llcpp

#endif // LLCPP_HEADER_LLOPERATIONS_HPP_
