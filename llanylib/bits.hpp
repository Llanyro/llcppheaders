//////////////////////////////////////////////
//	bits.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_BITS_HPP_) // Guard && version protector
	#if LLANYLIB_BITS_MAYOR_ != 8 || LLANYLIB_BITS_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "bits.hpp version error!"
		#else
			#error "bits.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_BITS_MAYOR_ || LLANYLIB_BITS_MINOR_

#else !defined(LLANYLIB_BITS_HPP_)
#define LLANYLIB_BITS_HPP_
#define LLANYLIB_BITS_MAYOR_ 8
#define LLANYLIB_BITS_MINOR_ 0

#include "traits.hpp"

#include <limits>

#undef max

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4499) // ignore static specialization [TOCHECK]
#endif // WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
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
#pragma region BytesOperations
__LL_NODISCARD__ constexpr ui32 bytes_swap_32(const ui32 value) __LL_EXCEPT__ {
	return
		((value & 0xff) << 24)
		| ((value & 0xff00) << 8)
		| ((value & 0xff0000) >> 8)
		| ((value & 0xff000000) >> 24);
}
__LL_NODISCARD__ constexpr ui64 bytes_swap_64(const ui64 value) __LL_EXCEPT__ {
	return
		((value & 0x00000000000000ffull) << 56)
		| ((value & 0x000000000000ff00ull) << 40)
		| ((value & 0x0000000000ff0000ull) << 24)
		| ((value & 0x00000000ff000000ull) << 8)
		| ((value & 0x000000ff00000000ull) >> 8)
		| ((value & 0x0000ff0000000000ull) >> 24)
		| ((value & 0x00ff000000000000ull) >> 40)
		| ((value & 0xff00000000000000ull) >> 56);
}

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
template<class T, class U = traits::type_conversor<T>::demote_t>
struct type_division {
	using __type_division = type_division<T, U>;
	using __t = T;
	using __u = U;
	using Data = ByteExtender<__u>;
	static constexpr ll_bool_t DEMOTED = !std::is_same_v<T, U>;
	static constexpr ui8 HALF_BITS = sizeof(__u) << 3;

	__LL_NODISCARD__ static constexpr Data div(const __t v) {
		return Data{
			static_cast<__u>(v & std::numeric_limits<__u>::max()),
			static_cast<__u>(v >> HALF_BITS)
		};
	}
	__LL_NODISCARD__ static constexpr __t combine(const __u low, const __u high) {
		return (static_cast<__t>(high) << HALF_BITS) | static_cast<__t>(low);
	}
	__LL_NODISCARD__ static constexpr __t combine(const Data& b) {
		return __type_division::combine(b.l, b.h);
	}
};

struct type_division_cluster {
	protected:
		#pragma region GenericSignedOrUnsigned
		template<class In, class Out>
		__LL_NODISCARD__ static constexpr Out generic64to8(const In value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			using _64 = type_division<In>;
			using _32 = type_division<typename _64::__u>;
			using _16 = type_division<typename _32::__u>;
			typename _64::Data s64 = _64::div(value);
			typename _32::Data s32 = _32::div(pattern[0] ? s64.h : s64.l);
			typename _16::Data s16 = _16::div(pattern[1] ? s32.h : s32.l);
			return (pattern[2] ? s16.h : s16.l);
		}
		template<class In, class Out>
		__LL_NODISCARD__ static constexpr Out generic64to16(const In value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			using _64 = type_division<In>;
			using _32 = type_division<typename _64::__u>;
			typename _64::Data s64 = _64::div(value);
			typename _32::Data s32 = _32::div(pattern[0] ? s64.h : s64.l);
			return (pattern[1] ? s32.h : s32.l);
		}
		template<class In, class Out>
		__LL_NODISCARD__ static constexpr Out generic64to32(const In value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			using _64 = type_division<In>;
			typename _64::Data s64 = _64::div(value);
			return (pattern[0] ? s64.h : s64.l);
		}

		template<class In, class Out>
		__LL_NODISCARD__ static constexpr Out generic32to8(const In value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			using _32 = type_division<In>;
			using _16 = type_division<typename _32::__u>;
			typename _32::Data s32 = _32::div(value);
			typename _16::Data s16 = _16::div(pattern[0] ? s32.h : s32.l);
			return (pattern[1] ? s16.h : s16.l);
		}
		template<class In, class Out>
		__LL_NODISCARD__ static constexpr Out generic32to16(const In value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			using _32 = type_division<In>;
			typename _32::Data s32 = _32::div(value);
			return (pattern[0] ? s32.h : s32.l);
		}

		template<class In, class Out>
		__LL_NODISCARD__ static constexpr Out generic16to8(const In value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			using _16 = type_division<In>;
			typename _16::Data s16 = _16::div(value);
			return (pattern[0] ? s16.h : s16.l);
		}

		#pragma endregion
	public:
		#pragma region Convert
		template<class In, class Out = In>
		__LL_NODISCARD__ static constexpr Out convert(const In value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return value;
		}

		template<>
		__LL_NODISCARD__ static constexpr ui8 convert(const ui64 value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return type_division_cluster::generic64to8<ui64, ui8>(value, pattern);
		}
		template<>
		__LL_NODISCARD__ static constexpr i8 convert(const i64 value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return type_division_cluster::generic64to8<i64, i8>(value, pattern);
		}

		template<>
		__LL_NODISCARD__ static constexpr ui16 convert(const ui64 value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return type_division_cluster::generic64to16<ui64, ui16>(value, pattern);
		}
		template<>
		__LL_NODISCARD__ static constexpr i16 convert(const i64 value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return type_division_cluster::generic64to16<i64, i16>(value, pattern);
		}

		template<>
		__LL_NODISCARD__ static constexpr ui32 convert(const ui64 value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return type_division_cluster::generic64to32<ui64, ui32>(value, pattern);
		}
		template<>
		__LL_NODISCARD__ static constexpr i32 convert(const i64 value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return type_division_cluster::generic64to32<i64, i32>(value, pattern);
		}

		template<>
		__LL_NODISCARD__ static constexpr ui8 convert(const ui32 value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return type_division_cluster::generic32to8<ui32, ui8>(value, pattern);
		}
		template<>
		__LL_NODISCARD__ static constexpr i8 convert(const i32 value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return type_division_cluster::generic32to8<i32, i8>(value, pattern);
		}

		template<>
		__LL_NODISCARD__ static constexpr ui16 convert<>(const ui32 value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return type_division_cluster::generic32to16<ui32, ui16>(value, pattern);
		}
		template<>
		__LL_NODISCARD__ static constexpr i16 convert(const i32 value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return type_division_cluster::generic32to16<i32, i16>(value, pattern);
		}

		template<>
		__LL_NODISCARD__ static constexpr ui8 convert(const ui16 value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return type_division_cluster::generic16to8<ui16, ui8>(value, pattern);
		}
		template<>
		__LL_NODISCARD__ static constexpr i8 convert(const i16 value, const ll_bool_t* pattern) __LL_EXCEPT__ {
			return type_division_cluster::generic16to8<i16, i8>(value, pattern);
		}

		#pragma endregion
};

} // namespace bits
} // namespace meta
} // namespace llcpp

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#endif // LLANYLIB_BITS_HPP_
