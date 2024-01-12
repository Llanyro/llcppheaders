/*
*	lllibbits.h
*
*	Created on: Nov 26, 2020
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
*/

#ifndef LLCPP_HEADER_LLLIBBITS_H_
#define LLCPP_HEADER_LLLIBBITS_H_

#include "llanytypeslib.hpp"

namespace llcpp {
typedef ll_uchar_t ll_bitarray_t;
typedef ll_uchar_t ll_bits_t;
typedef ll_uchar_t ll_byte_t;
	
namespace header {
namespace bit {
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
template<class __T, ui8 pos>
LL_SHARED_LIB __LL_CONSTEVAL__ void set(__T& value) noexcept {
	value |= static_cast<__T>(1 << pos);
}
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
template<class __T, ui8 pos>
__LL_NODISCARD__ LL_SHARED_LIB __LL_CONSTEVAL__ ui8 get(__T value) noexcept {
	return (value >> pos) & 1;
}
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
template<class __T, ui8 pos>
LL_SHARED_LIB __LL_CONSTEVAL__ void clear(__T& value) noexcept {
	value &= ~(1 << pos);
}

#pragma region BaseTransformation
template<class __T, ui8 base>
__LL_NODISCARD__ LL_SHARED_LIB __LL_CONSTEVAL__ __T transformToBaseV2(__T value) noexcept {
	return (value & (0xFFFFFFFFFFFFFFFF - base - 1)) + base;
}
template<class __T>
__LL_NODISCARD__ LL_SHARED_LIB __LL_CONSTEVAL__ __T transformTo64(__T value) noexcept {
	return transformToBaseV2<__T, 64>(value);
}
template<class __T>
__LL_NODISCARD__ LL_SHARED_LIB __LL_CONSTEVAL__ __T transformTo32(__T value) noexcept {
	return transformToBaseV2<__T, 32>(value);
}
template<class __T>
__LL_NODISCARD__ LL_SHARED_LIB __LL_CONSTEVAL__ __T transformTo8(__T value) noexcept {
	return transformToBaseV2<__T, 8>(value);
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
template<class __T>
LL_SHARED_LIB __LL_CONSTEVAL__ void set(T& value) noexcept {
	set<T, 0>(value);
}
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
template<class __T>
__LL_NODISCARD__ LL_SHARED_LIB __LL_CONSTEVAL__ ui8 get(T value) noexcept {
	return get<T, 0>(value);
}
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
template<class __T>
LL_SHARED_LIB __LL_CONSTEVAL__ void clear(T& value) noexcept {
	return clear<T, 0>(value);
}
#pragma endregion

} // namespace bit
} // namespace header
} // namespace llcpp

#endif // LLCPP_HEADER_LLLIBBITS_H_
