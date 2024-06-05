//////////////////////////////////////////////
//	hash_algorithm.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.3							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHALGORITHM_HPP_) // Guard && version protector
	#if LLANYLIB_HASHALGORITHM_MAYOR_ != 7 || LLANYLIB_HASHALGORITHM_MINOR_ < 3
		#if defined(LL_REAL_CXX23)
			#warning "hash_algorithm.hpp version error!"
		#else
			#error "hash_algorithm.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASHALGORITHM_MAYOR_ || LLANYLIB_HASHALGORITHM_MINOR_

#else !defined(LLANYLIB_HASHALGORITHM_HPP_)
#define LLANYLIB_HASHALGORITHM_HPP_
#define LLANYLIB_HASHALGORITHM_MAYOR_ 7
#define LLANYLIB_HASHALGORITHM_MINOR_ 3

#include "traits.hpp"

namespace llcpp {
namespace meta {
namespace hash {

struct combine {
	// 8 bits
	static constexpr ui8 kMul8 = 0x7;
	static constexpr ui8 llshift8 = 3;
	static constexpr ui8 combine8 = 0x29;

	// 32 bits
	static constexpr ui32 kMul32 = 0x1b873593u; // 0x7fffffff;
	static constexpr ui8 llshift32 = 23;
	static constexpr ui32 combine32 = 0xcc9e2d51u; // 0x7fffffbb;

	// 64 bits
	static constexpr ui64 kMul64 = 0x9ddfea08eb382d69ull;
	static constexpr ui8 llshift64 = 47;
	static constexpr ui64 combine64 = 0xc3a5c85c97cb3171ull;

	// Murmur-inspired hashing.
	#pragma region Murmur
	#pragma region 8
	__LL_NODISCARD__ static constexpr ui8 murmur8Combine(const ui8 value1, const ui8 value2) __LL_EXCEPT__ {
		ui8 a = (value1 ^ value2) * combine::kMul8;
		a ^= (a >> combine::llshift8);
		ui8 b = (value2 ^ a) * combine::kMul8;
		b ^= (b >> combine::llshift8);
		b *= combine::kMul8;
		return b;
	}
	// Value in in left position
	__LL_NODISCARD__ static constexpr ui8 murmur8Combine_l(const ui8 value) __LL_EXCEPT__ {
		return combine::murmur8Combine(value, combine::combine8);
	}
	// Value in in right position
	__LL_NODISCARD__ static constexpr ui8 murmur8Combine_r(const ui8 value) __LL_EXCEPT__ {
		return combine::murmur8Combine(combine::combine8, value);
	}

	#pragma endregion
	#pragma region 32
	__LL_NODISCARD__ static constexpr ui32 murmur32Combine(const ui32 value1, const ui32 value2) __LL_EXCEPT__ {
		ui32 a = (value1 ^ value2) * combine::kMul32;
		a ^= (a >> combine::llshift32);
		ui32 b = (value2 ^ a) * combine::kMul32;
		b ^= (b >> combine::llshift32);
		b *= combine::kMul32;
		return b;
	}
	// Value in in left position
	__LL_NODISCARD__ static constexpr ui32 murmur32Combine_l(const ui32 value) __LL_EXCEPT__ {
		return combine::murmur32Combine(value, combine::combine32);
	}
	// Value in in right position
	__LL_NODISCARD__ static constexpr ui32 murmur32Combine_r(const ui32 value) __LL_EXCEPT__ {
		return combine::murmur32Combine(combine::combine32, value);
	}

	#pragma endregion
	#pragma region 64
	__LL_NODISCARD__ static constexpr ui64 murmur64Combine(const ui64 value1, const ui64 value2) __LL_EXCEPT__ {
		ui64 a = (value1 ^ value2) * combine::kMul64;
		a ^= (a >> combine::llshift64);
		ui64 b = (value2 ^ a) * combine::kMul64;
		b ^= (b >> combine::llshift64);
		b *= combine::kMul64;
		return b;
	}
	// Value in in left position
	__LL_NODISCARD__ static constexpr ui64 murmur64Combine_l(const ui64 value) __LL_EXCEPT__ {
		return combine::murmur64Combine(value, combine::combine64);
	}
	// Value in in right position
	__LL_NODISCARD__ static constexpr ui64 murmur64Combine_r(const ui64 value) __LL_EXCEPT__ {
		return combine::murmur64Combine(combine::combine64, value);
	}

	#pragma endregion

	#pragma endregion
	#pragma region Combine
	#pragma region Template
	template<class T, ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr T simpleCombine(const T value1, const T value2, const ui8 shift) __LL_EXCEPT__ {
		if constexpr (IS_REVERSE) return value1 ^ (value2 << shift);
		else return value1 ^ (value2 >> shift);
	}

	#pragma endregion
	#pragma region 8
	// Value in in left position + user shift
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui8 simple8Combine_l(const ui8 value, const ui8 shift) __LL_EXCEPT__ {
		return combine::simpleCombine<ui8, IS_REVERSE>(value, combine::combine8, shift);
	}
	// Value in in right position + user shift
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui8 simple8Combine_r(const ui8 value, const ui8 shift) __LL_EXCEPT__ {
		return combine::simpleCombine<ui8, IS_REVERSE>(combine::combine8, value, shift);
	}
	// Values + no shift
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui8 simple8Combine_noshift(const ui8 value1, const ui8 value2) __LL_EXCEPT__ {
		return combine::simpleCombine<ui8, IS_REVERSE>(value1, value2, combine::llshift8);
	}
	// Value in in left position
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui8 simple8Combine_l(const ui8 value) __LL_EXCEPT__ {
		return combine::simple8Combine_l<IS_REVERSE>(value, combine::llshift8);
	}
	// Value in in right position
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui8 simple8Combine_r(const ui8 value) __LL_EXCEPT__ {
		return combine::simple8Combine_r<IS_REVERSE>(value, combine::llshift8);
	}

	#pragma endregion
	#pragma region 32
	// Value in in left position + user shift
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui32 simple32Combine_l(const ui32 value, const ui32 shift) __LL_EXCEPT__ {
		return combine::simpleCombine<ui32, IS_REVERSE>(value, combine::combine32, shift);
	}
	// Value in in right position + user shift
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui32 simple32Combine_r(const ui32 value, const ui32 shift) __LL_EXCEPT__ {
		return combine::simpleCombine<ui32, IS_REVERSE>(combine::combine32, value, shift);
	}
	// Values + no shift
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui32 simple32Combine_noshift(const ui32 value1, const ui32 value2) __LL_EXCEPT__ {
		return combine::simpleCombine<ui32, IS_REVERSE>(value1, value2, combine::llshift32);
	}
	// Value in in left position
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui32 simple32Combine_l(const ui32 value) __LL_EXCEPT__ {
		return combine::simple32Combine_l<IS_REVERSE>(value, combine::llshift32);
	}
	// Value in in right position
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui32 simple32Combine_r(const ui32 value) __LL_EXCEPT__ {
		return combine::simple32Combine_r<IS_REVERSE>(value, combine::llshift32);
	}

	#pragma endregion
	#pragma region 64
	// Value in in left position + user shift
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui64 simple64Combine_l(const ui64 value, const ui64 shift) __LL_EXCEPT__ {
		return combine::simpleCombine<ui64, IS_REVERSE>(value, combine::combine64, shift);
	}
	// Value in in right position + user shift
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui64 simple64Combine_r(const ui64 value, const ui64 shift) __LL_EXCEPT__ {
		return combine::simpleCombine<ui64, IS_REVERSE>(combine::combine64, value, shift);
	}
	// Values + no shift
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui64 simple64Combine_noshift(const ui64 value1, const ui64 value2) __LL_EXCEPT__ {
		return combine::simpleCombine<ui64, IS_REVERSE>(value1, value2, combine::llshift64);
	}
	// Value in in left position
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui64 simple64Combine_l(const ui64 value) __LL_EXCEPT__ {
		return combine::simple64Combine_l<IS_REVERSE>(value, combine::llshift64);
	}
	// Value in in right position
	template<ll_bool_t IS_REVERSE = LL_FALSE>
	__LL_NODISCARD__ static constexpr ui64 simple64Combine_r(const ui64 value) __LL_EXCEPT__ {
		return combine::simple64Combine_r<IS_REVERSE>(value, combine::llshift64);
	}

	#pragma endregion

	#pragma endregion
};

struct basic_type_hash {
	template<class T>
	static constexpr ll_bool_t is_convertible_v = std::_Is_any_of_v<T, i8, ui8, i16, ui16, i32, ui32, i64, ui64, ll_wchar_t>;

	#pragma region UsedInTools
	template<len_t N, class T>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 hashValues(const T* values, hash::Hash64Function hashFunction) __LL_EXCEPT__ {
		if constexpr (!basic_type_hash::is_convertible_v<T> || N == ZERO_UI64)
			return hash::INVALID_HASH64;
		else if constexpr (N == 1) return basic_type_hash::hashValue<T>(*values, hashFunction);
		else {
			constexpr len_t BUFFERLEN = sizeof(T) * N;
			ll_char_t buffer[BUFFERLEN]{};

			ll_char_t* i = buffer;
			for (const T* data_end = values + N; values < data_end; ++values)
				(void)basic_type_hash::conversor<T>(i, *values);
			return hashFunction(buffer, BUFFERLEN);
		}
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 hashArray(const hash::Hash64(&hashes)[N], hash::Hash64Function hashFunction) __LL_EXCEPT__ {
		constexpr len_t BUFFERLEN = sizeof(ui64) * N;
		ll_char_t buffer[BUFFERLEN]{};

		ll_char_t* i = buffer;
		const hash::Hash64* arr = hashes;
		for (const hash::Hash64* data_end = arr + N; arr < data_end; ++arr)
			(void)basic_type_hash::conversor<ui64>(i, arr->get());

		return hashFunction(buffer, BUFFERLEN);
	}

	#pragma endregion

	// Uses bitwise operators: [ ">>", "&" ]
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t conversor(ll_char_t*& buffer, typename W::cinput value) __LL_EXCEPT__ {
		constexpr len_t N = sizeof(U);
		if constexpr (!basic_type_hash::is_convertible_v<U>) {
			buffer += N;
			return LL_FALSE;
		}
		else {
			constexpr len_t BYTES = (N << 3) - 8;
			len_t byte = BYTES;
			for (len_t i{}; i < N; ++i, ++buffer, byte -= 8)
				*buffer = (value >> byte) & 0xff;
			return LL_TRUE;
		}
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 hashValue(typename W::cinput value, hash::Hash64Function hashFunction) __LL_EXCEPT__ {
		if constexpr (!basic_type_hash::is_convertible_v<U>) return hash::INVALID_HASH64;
		else {
			constexpr len_t BUFFERLEN = sizeof(U);
			ll_char_t buffer[BUFFERLEN]{};
			ll_char_t* _ = buffer;
			if(!basic_type_hash::conversor<U, W>(_, value)) return hash::INVALID_HASH64;
			return hashFunction(buffer, BUFFERLEN);
		}
	}

	#pragma region Combine
	template<class T, class U, class V = traits::template_types<T>, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 combine_shl(typename V::cinput value1, typename W::cinput value2, const ui8 shift) __LL_EXCEPT__ {
		if constexpr (!basic_type_hash::is_convertible_v<T> || !basic_type_hash::is_convertible_v<U>)
			return hash::INVALID_HASH64;
		else return value1 ^ (value2 << shift);
	}
	template<class T, class U, class V = traits::template_types<T>, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 combine_shr(typename V::cinput value1, typename W::cinput value2, const ui8 shift) __LL_EXCEPT__ {
		if constexpr (!basic_type_hash::is_convertible_v<T> || !basic_type_hash::is_convertible_v<U>)
			return hash::INVALID_HASH64;
		else return value1 ^ (value2 >> shift);
	}
	template<class T, class V = traits::template_types<T>>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 combine_shl(typename V::cinput value, const ui8 shift) __LL_EXCEPT__ {
		return basic_type_hash::combine_shl(value, __internal__::kll, shift);
	}
	template<class T, class U, class V = traits::template_types<T>, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 combine_shr(typename V::cinput value, const ui8 shift) __LL_EXCEPT__ {
		return basic_type_hash::combine_shr(value, __internal__::kll, shift);
	}

	#pragma endregion
	#pragma region Mur
	template<class T, class U, class V = traits::template_types<T>, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 mur(typename W::cinput value1, typename V::cinput value2) __LL_EXCEPT__ {
		if constexpr (!basic_type_hash::is_convertible_v<T> || !basic_type_hash::is_convertible_v<U>)
			return hash::INVALID_HASH64;
		else {
			ui64 a = (value1 ^ value2) * __internal__::kMul;
			a ^= (a >> 47);
			ui64 b = (value2 ^ a) * __internal__::kMul;
			b ^= (b >> 47);
			b *= __internal__::kMul;
			return b;
		}
	}
	template<class T, class V = traits::template_types<T>>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 mur_l(typename V::cinput value) __LL_EXCEPT__ {
		basic_type_hash::mur(value, __internal__::kll);
	}
	template<class T, class V = traits::template_types<T>>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 mur_r(typename V::cinput value) __LL_EXCEPT__ {
		basic_type_hash::mur(__internal__::kll, value);
	}

	#pragma endregion
};

// Struct for use in HashTool in an more optimized way (for not constexpr data)
struct basic_type_hash_no_constexpr {
	template<len_t N>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 hashArray(const hash::Hash64(&hashes)[N], hash::Hash64Function hashFunction) __LL_EXCEPT__ {
		return hashFunction(reinterpret_cast<ll_string_t>(hashes), sizeof(hash::Hash64) * N);
	}
	template<len_t N, class T>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 hashValues(const T* values, hash::Hash64Function hashFunction) __LL_EXCEPT__ {
		if constexpr (!basic_type_hash::is_convertible_v<T> || N == ZERO_UI64)
			return hash::INVALID_HASH64;
		else return hashFunction(reinterpret_cast<ll_string_t>(values), sizeof(T) * N);
	}
};

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASHALGORITHM_HPP_
