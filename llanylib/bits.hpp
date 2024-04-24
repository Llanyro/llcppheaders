//////////////////////////////////////////////
//	bits.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_BITS_HPP_) // Guard && version protector
	#if LLANYLIB_BITS_MAYOR_ != 5 || LLANYLIB_BITS_MINOR_ < 0
		#error "bits.hpp version error!"
	#endif // LLANYLIB_BITS_MAYOR_ || LLANYLIB_BITS_MINOR_

#else !defined(LLANYLIB_BITS_HPP_)
#define LLANYLIB_BITS_HPP_
#define LLANYLIB_BITS_MAYOR_ 5
#define LLANYLIB_BITS_MINOR_ 0

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
#pragma region TypeDivision(?)

template<class T, const ui8 HALF_BITS, class U = traits::get_smaller_type_t<T>, const U _FULL_FIRST = 0, const T _FULL_SECOND = 0>
struct TypeDivision {
	using __type = T;
	using __type_lower = U;
	static constexpr U FULL_FIRST = _FULL_FIRST;
	static constexpr T _FULL_SECOND = _FULL_SECOND;

	static constexpr ByteExtender<U> div(const T v) {
		return ByteExtender<U>{
			static_cast<U>(v & FULL_FIRST),
			static_cast<U>((v & _FULL_SECOND) >> HALF_BITS)
		};
	}
};

#pragma region SpecializationTypeDivision
constexpr i8 I8_MAX = 0x7f;
constexpr i16 I16_MAX = 0x7fff;
constexpr i32 I32_MAX = 0x7fffffff;
constexpr i64 I64_MAX = 0x7fffffffffffffff;

constexpr ui8 UI8_MAX = 0xff;
constexpr ui16 UI16_MAX = 0xffff;
constexpr ui32 UI32_MAX = 0xffffffff;
constexpr ui64 UI64_MAX = 0xffffffffffffffff;

using i16Divisor = TypeDivision<i16, 7, i8, I8_MAX, I16_MAX>;
using i32Divisor = TypeDivision<i32, 15, i16, I16_MAX, I32_MAX>;
using i64Divisor = TypeDivision<i64, 31, i32, I32_MAX, I64_MAX>;

using ui16Divisor = TypeDivision<ui16, 8, ui8, UI8_MAX, UI16_MAX>;
using ui32Divisor = TypeDivision<ui32, 16, ui16, UI16_MAX, UI32_MAX>;
using ui64Divisor = TypeDivision<ui64, 32, ui32, UI32_MAX, UI64_MAX>;

#pragma endregion

#pragma endregion

} // namespace bits
} // namespace llcpp

#endif // LLANYLIB_BITS_HPP_
