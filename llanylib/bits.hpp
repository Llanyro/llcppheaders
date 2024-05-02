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
		#if defined(LL_REAL_CXX23)
			#warning "bits.hpp version error!"
		#else
			#error "bits.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_BITS_MAYOR_ || LLANYLIB_BITS_MINOR_

#else !defined(LLANYLIB_BITS_HPP_)
#define LLANYLIB_BITS_HPP_
#define LLANYLIB_BITS_MAYOR_ 5
#define LLANYLIB_BITS_MINOR_ 0

#include "definitions.hpp"

#include "traits.hpp"

#include <limits>

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
template<class T>
constexpr void set(T& value, const bit_pos pos) __LL_EXCEPT__ {
	value |= static_cast<T>(1 << pos);
}
template<class T>
__LL_NODISCARD__ constexpr ui8 get(T value, const bit_pos pos) __LL_EXCEPT__ {
	return (value >> pos) & 1;
}
template<class T>
constexpr void clear(T& value, const bit_pos pos) __LL_EXCEPT__ {
	value &= ~(1 << pos);
}

#pragma region Proxy
template<class T>
constexpr void set(T& value) __LL_EXCEPT__ { set<T, 0>(value); }
template<class T>
__LL_NODISCARD__ constexpr ui8 get(T value) __LL_EXCEPT__ { return get<T, 0>(value); }
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
template<class T, const ui8 HALF_BITS, class U = traits::type_conversor<T>::demote_t>
struct TypeDivision {
	using __type = T;
	using __type_demote = U;
	static constexpr T __HALF_BITS = HALF_BITS;
	using __ByteExtender = ByteExtender<U>;

	__LL_NODISCARD__ static constexpr __ByteExtender div(const T v) {
		return __ByteExtender {
			static_cast<U>(v & std::numeric_limits<U>::max()),
			static_cast<U>(v >> HALF_BITS)
		};
	}
};

#pragma region SpecializationTypeDivision
// [TODO]
//using i16Divisor = TypeDivision<i16, 7, i8, I8_MAX>;
//using i32Divisor = TypeDivision<i32, 15, i16, I16_MAX>;
//using i64Divisor = TypeDivision<i64, 31, i32, I32_MAX>;

// [TODO]
//using ui16Divisor = TypeDivision<ui16, 8, ui8>;
//using ui32Divisor = TypeDivision<ui32, 16, ui16>;
//using ui64Divisor = TypeDivision<ui64, 32, ui32>;

#pragma endregion

#pragma endregion

} // namespace bits
} // namespace llcpp

#endif // LLANYLIB_BITS_HPP_
