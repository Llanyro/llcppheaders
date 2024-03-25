/*
 *	bits.hpp
 *
 *	Author: Francisco Julio Ruiz Fernandez
 *	Author: llanyro
 *
 *	Version: 4.2
 */

#if defined(LLANYLIB_BITS_HPP_) // Guard && version protector
	#if LLANYLIB_BITS_MAYOR_ != 4 || LLANYLIB_BITS_MINOR_ < 2
		#error "bits.hpp version error!"
	#endif // LLANYLIB_BITS_MAYOR_ || LLANYLIB_BITS_MINOR_

#else !defined(LLANYLIB_BITS_HPP_)
#define LLANYLIB_BITS_HPP_
#define LLANYLIB_BITS_MAYOR_ 4
#define LLANYLIB_BITS_MINOR_ 2

#include "definitions.hpp"

#include "traits.hpp"

namespace llcpp {
namespace bits {

using bit_pos = ui8;

constexpr ui8 BITARRAY_LEN = 8;

constexpr ui8 SHIFT_2	= 1;
constexpr ui8 SHIFT_4	= 2;
constexpr ui8 SHIFT_8	= 3;
constexpr ui8 SHIFT_16	= 4;
constexpr ui8 SHIFT_32	= 5;
constexpr ui8 SHIFT_64	= 6;
constexpr ui8 SHIFT_128 = 7;
constexpr ui8 SHIFT_256 = 8;
constexpr ui8 SHIFT_512 = 9;

constexpr ui8 MASK_2	= (1 << SHIFT_2)	- 1;
constexpr ui8 MASK_4	= (1 << SHIFT_4)	- 1;
constexpr ui8 MASK_8	= (1 << SHIFT_8)	- 1;
constexpr ui8 MASK_16	= (1 << SHIFT_16)	- 1;
constexpr ui8 MASK_32	= (1 << SHIFT_32)	- 1;
constexpr ui8 MASK_64	= (1 << SHIFT_64)	- 1;
constexpr ui8 MASK_128	= (1 << SHIFT_128)	- 1;
constexpr ui16 MASK_256 = (1 << SHIFT_256)	- 1;
constexpr ui16 MASK_512 = (1 << SHIFT_512)	- 1;

#pragma region BitOperations
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
template<class T>
constexpr void set(T& value, const bit_pos pos) __LL_EXCEPT__ {
	value |= static_cast<T>(1 << pos);
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
template<class T>
__LL_NODISCARD__ constexpr ui8 get(T value, const bit_pos pos) __LL_EXCEPT__ {
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
template<class T>
constexpr void clear(T& value, const bit_pos pos) __LL_EXCEPT__ {
	value &= ~(1 << pos);
}

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

#pragma endregion
#pragma region BaseTransformation
template<class T>
__LL_NODISCARD__ constexpr T transformToBaseV3(const T value, const ui8 base) __LL_EXCEPT__ {
	static_assert(std::is_unsigned_v<T>, "<T> needs to be a unsigned value!");
	T v1 = (value & (base - 1));
	return v1 ? (value - v1 + base) : value;
}
template<class T>
__LL_NODISCARD__ constexpr T transformTo64(const T value) __LL_EXCEPT__ {
	return transformToBaseV3<T>(value, 64);
}
template<class T>
__LL_NODISCARD__ constexpr T transformTo32(const T value) __LL_EXCEPT__ {
	return transformToBaseV3<T>(value, 32);
}
template<class T>
__LL_NODISCARD__ constexpr T transformTo8(const T value) __LL_EXCEPT__ {
	return transformToBaseV3<T>(value, 8);
}

#pragma endregion

} // namespace bits
} // namespace llcpp

#endif // LLANYLIB_BITS_HPP_
