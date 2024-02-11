/*
 *	bits.h
 *
 *	Created on: Nov 26, 2020
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLCPP_HEADER_BITS_H_
#define LLCPP_HEADER_BITS_H_

#include "definitions.hpp"
#include "traits.hpp"

namespace llcpp {
	
namespace bits {
constexpr ui8 BITARRAY_LEN = 8;

/*!
 *	@template False
 *	@brief Set a bit to 1 by given position
 *
 *	@efficiency O(1)
 *	@time T(1)
 *	@memory M(1)
 *	@const eval
 *	@throw False
 *
 *	@param[in] value Value to edit
 *
 *	@templateparam T item type
 *	@templateparam pos Bit position
 *
 *	@thread_safety This function may be called from any thread.
 *	@thread_protection This function is not protexted by mutex.
 *
 *	@sa @ref bit_operations
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup header
 *	@ingroup bit
 */
template<class T, ui8 pos>
constexpr void set(T& value) __LL_EXCEPT__ { value |= static_cast<T>(1 << pos); }
/*!
 *	@template True
 *	@brief Get bit value by given position
 *
 *	@efficiency O(1)
 *	@time T(1)
 *	@memory M(1)
 *	@const eval
 *	@throw False
 *
 *	@param[in] value Value to check
 *
 *	@templateparam T item type
 *	@templateparam pos Bit position
 *
 *	@return Bit value requested
 *
 *	@thread_safety This function may be called from any thread.
 *	@thread_protection This function is not protexted by mutex.
 *
 *	@sa @ref bit_operations
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup header
 *	@ingroup bit
 */
template<class T, ui8 pos>
__LL_NODISCARD__ constexpr ui8 get(T value) __LL_EXCEPT__ { return (value >> pos) & 1; }
/*!
 *	@template False
 *	@brief Set a bit to 0 by given position
 *
 *	@efficiency O(1)
 *	@time T(1)
 *	@memory M(1)
 *	@const eval
 *	@throw False
 *
 *	@param[in] value Value to edit
 *
 *	@templateparam T item type
 *	@templateparam pos Bit position
 *
 *	@thread_safety This function may be called from any thread.
 *	@thread_protection This function is not protexted by mutex.
 *
 *	@sa @ref bit_operations
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup header
 *	@ingroup bit
 */
template<class T, ui8 pos>
constexpr void clear(T& value) __LL_EXCEPT__ { value &= ~(1 << pos); }

#pragma region BaseTransformation
template<class T, ui8 base>
__LL_NODISCARD__ constexpr T transformToBaseV2(T value) __LL_EXCEPT__ {
	static_cast(std::is_unsigned_v<T>, "<T> needs to be a unsigned value!");
	//return (value & (0xFFFFFFFFFFFFFFFF - base - 1)) + base;
	return (value & (static_cast<T>(-1) - base - 1)) + base;
}
template<class T>
__LL_NODISCARD__ constexpr T transformTo64(T value) __LL_EXCEPT__ {
	return transformToBaseV2<T, 64>(value);
}
template<class T>
__LL_NODISCARD__ constexpr T transformTo32(T value) __LL_EXCEPT__ {
	return transformToBaseV2<T, 32>(value);
}
template<class T>
__LL_NODISCARD__ constexpr T transformTo8(T value) __LL_EXCEPT__ {
	return transformToBaseV2<T, 8>(value);
}
#pragma endregion

#pragma region Proxy
/*!
 *	@template True
 *	@brief Proxy of set<T, 0>(T& value)
 *	@proxyof set<T, 0>(T& value)
 *
 *	@templateparam T item type
 *
 *	@sa @ref bit_operations
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup header
 *	@ingroup bit
 */
template<class T>
constexpr void set(T& value) __LL_EXCEPT__ { set<T, 0>(value); }
/*!
 *	@template True
 *	@brief Proxy of get<T, 0>(T& value)
 *	@proxyof get<T, 0>(T& value)
 *
 *	@templateparam T item type
 *
 *	@sa @ref bit_operations
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup header
 *	@ingroup bit
 */
template<class T>
__LL_NODISCARD__ constexpr ui8 get(T value) __LL_EXCEPT__ { return get<T, 0>(value); }
/*!
 *	@template True
 *	@brief Proxy of clear<T, 0>(T& value)
 *	@proxyof clear<T, 0>(T& value)
 *
 *	@templateparam T item type
 *
 *	@sa @ref bit_operations
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup header
 *	@ingroup bit
 */
template<class T>
constexpr void clear(T& value) __LL_EXCEPT__ { return clear<T, 0>(value); }

#pragma endregion

} // namespace bits
} // namespace llcpp

#endif // LLCPP_HEADER_BITS_H_
