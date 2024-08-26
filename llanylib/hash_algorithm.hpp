//////////////////////////////////////////////
//	hash_algorithm.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHALGORITHM_HPP_) // Guard && version protector
	#if LLANYLIB_HASHALGORITHM_MAYOR_ != 9 || LLANYLIB_HASHALGORITHM_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "hash_algorithm.hpp version error!"
		#else
			#error "hash_algorithm.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASHALGORITHM_MAYOR_ || LLANYLIB_HASHALGORITHM_MINOR_

#else !defined(LLANYLIB_HASHALGORITHM_HPP_)
#define LLANYLIB_HASHALGORITHM_HPP_
#define LLANYLIB_HASHALGORITHM_MAYOR_ 9
#define LLANYLIB_HASHALGORITHM_MINOR_ 0

#include "traits.hpp"

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#if defined(__LL_SPECTRE_FUNCTIONS__)
		#pragma warning(disable:5045) // Security Spectre mitigation [SECURITY]
	#endif // __LL_UNSECURE_FUNCTIONS__
#endif

namespace llcpp {
namespace meta {
namespace hash {
namespace algorithm {
namespace __algorithm__ {
// 8 bits
__LL_VAR_INLINE__ constexpr ui8 kMul8 = 0x7;
__LL_VAR_INLINE__ constexpr ui8 llshift8 = 3;
__LL_VAR_INLINE__ constexpr ui8 combine8 = 0x29;

// 32 bits
__LL_VAR_INLINE__ constexpr ui32 kMul32 = 0x1b873593u; // 0x7fffffff;
__LL_VAR_INLINE__ constexpr ui8 llshift32 = 23;
__LL_VAR_INLINE__ constexpr ui32 combine32 = 0xcc9e2d51u; // 0x7fffffbb;

// 64 bits
__LL_VAR_INLINE__ constexpr ui64 kMul64 = 0x9ddfea08eb382d69ull;
__LL_VAR_INLINE__ constexpr ui8 llshift64 = 47;
__LL_VAR_INLINE__ constexpr ui64 combine64 = 0xc3a5c85c97cb3171ull;

} // namespace __algorithm__

// Murmur-inspired hashing.
#pragma region Murmur
#pragma region 8
__LL_NODISCARD__ constexpr ui8 murmur8Combine(const ui8 value1, const ui8 value2) noexcept {
	ui8 a = static_cast<ui8>((value1 ^ value2) * hash::algorithm::__algorithm__::kMul8);
	a ^= (a >> hash::algorithm::__algorithm__::llshift8);
	ui8 b = static_cast<ui8>((value2 ^ a) * hash::algorithm::__algorithm__::kMul8);
	b ^= (b >> hash::algorithm::__algorithm__::llshift8);
	b *= hash::algorithm::__algorithm__::kMul8;
	return b;
}
// Value in in left position
__LL_NODISCARD__ constexpr ui8 murmur8Combine_l(const ui8 value) noexcept {
	return meta::hash::algorithm::murmur8Combine(value, hash::algorithm::__algorithm__::combine8);
}
// Value in in right position
__LL_NODISCARD__ constexpr ui8 murmur8Combine_r(const ui8 value) noexcept {
	return meta::hash::algorithm::murmur8Combine(hash::algorithm::__algorithm__::combine8, value);
}

#pragma endregion
#pragma region 32
__LL_NODISCARD__ constexpr ui32 murmur32Combine(const ui32 value1, const ui32 value2) noexcept {
	ui32 a = (value1 ^ value2) * hash::algorithm::__algorithm__::kMul32;
	a ^= (a >> hash::algorithm::__algorithm__::llshift32);
	ui32 b = (value2 ^ a) * hash::algorithm::__algorithm__::kMul32;
	b ^= (b >> hash::algorithm::__algorithm__::llshift32);
	b *= hash::algorithm::__algorithm__::kMul32;
	return b;
}
// Value in in left position
__LL_NODISCARD__ constexpr ui32 murmur32Combine_l(const ui32 value) noexcept {
	return meta::hash::algorithm::murmur32Combine(value, hash::algorithm::__algorithm__::combine32);
}
// Value in in right position
__LL_NODISCARD__ constexpr ui32 murmur32Combine_r(const ui32 value) noexcept {
	return meta::hash::algorithm::murmur32Combine(hash::algorithm::__algorithm__::combine32, value);
}

#pragma endregion
#pragma region 64
__LL_NODISCARD__ constexpr ui64 murmur64Combine(const ui64 value1, const ui64 value2) noexcept {
	ui64 a = (value1 ^ value2) * hash::algorithm::__algorithm__::kMul64;
	a ^= (a >> hash::algorithm::__algorithm__::llshift64);
	ui64 b = (value2 ^ a) * hash::algorithm::__algorithm__::kMul64;
	b ^= (b >> hash::algorithm::__algorithm__::llshift64);
	b *= hash::algorithm::__algorithm__::kMul64;
	return b;
}
// Value in in left position
__LL_NODISCARD__ constexpr ui64 murmur64Combine_l(const ui64 value) noexcept {
	return meta::hash::algorithm::murmur64Combine(value, hash::algorithm::__algorithm__::combine64);
}
// Value in in right position
__LL_NODISCARD__ constexpr ui64 murmur64Combine_r(const ui64 value) noexcept {
	return meta::hash::algorithm::murmur64Combine(hash::algorithm::__algorithm__::combine64, value);
}

#pragma endregion

#pragma endregion
#pragma region Combine
#pragma region Template
// IS_REVERSE means that shift is left if true
//		or shift right if false
template<class T, ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr T simpleCombine(const T value1, const T value2, const ui8 shift) noexcept {
	if constexpr (IS_REVERSE) return static_cast<T>(value1 ^ (value2 << shift));
	else return static_cast<T>(value1 ^ (value2 >> shift));
}

#pragma endregion
#pragma region 8
// Value in in left position + user shift
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui8 simple8Combine_l(const ui8 value, const ui8 shift) noexcept {
	return meta::hash::algorithm::simpleCombine<ui8, IS_REVERSE>(value, hash::algorithm::__algorithm__::combine8, shift);
}
// Value in in right position + user shift
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui8 simple8Combine_r(const ui8 value, const ui8 shift) noexcept {
	return meta::hash::algorithm::simpleCombine<ui8, IS_REVERSE>(hash::algorithm::__algorithm__::combine8, value, shift);
}
// Values + no shift
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui8 simple8Combine_noshift(const ui8 value1, const ui8 value2) noexcept {
	return meta::hash::algorithm::simpleCombine<ui8, IS_REVERSE>(value1, value2, hash::algorithm::__algorithm__::llshift8);
}
// Value in in left position
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui8 simple8Combine_l(const ui8 value) noexcept {
	return meta::hash::algorithm::simple8Combine_l<IS_REVERSE>(value, hash::algorithm::__algorithm__::llshift8);
}
// Value in in right position
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui8 simple8Combine_r(const ui8 value) noexcept {
	return meta::hash::algorithm::simple8Combine_r<IS_REVERSE>(value, hash::algorithm::__algorithm__::llshift8);
}

#pragma endregion
#pragma region 32
// Value in in left position + user shift
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui32 simple32Combine_l(const ui32 value, const ui32 shift) noexcept {
	return meta::hash::algorithm::simpleCombine<ui32, IS_REVERSE>(value, hash::algorithm::__algorithm__::combine32, shift);
}
// Value in in right position + user shift
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui32 simple32Combine_r(const ui32 value, const ui32 shift) noexcept {
	return meta::hash::algorithm::simpleCombine<ui32, IS_REVERSE>(hash::algorithm::__algorithm__::combine32, value, shift);
}
// Values + no shift
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui32 simple32Combine_noshift(const ui32 value1, const ui32 value2) noexcept {
	return meta::hash::algorithm::simpleCombine<ui32, IS_REVERSE>(value1, value2, hash::algorithm::__algorithm__::llshift32);
}
// Value in in left position
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui32 simple32Combine_l(const ui32 value) noexcept {
	return meta::hash::algorithm::simple32Combine_l<IS_REVERSE>(value, hash::algorithm::__algorithm__::llshift32);
}
// Value in in right position
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui32 simple32Combine_r(const ui32 value) noexcept {
	return meta::hash::algorithm::simple32Combine_r<IS_REVERSE>(value, hash::algorithm::__algorithm__::llshift32);
}

#pragma endregion
#pragma region 64
// Value in in left position + user shift
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui64 simple64Combine_l(const ui64 value, const ui64 shift) noexcept {
	return meta::hash::algorithm::simpleCombine<ui64, IS_REVERSE>(value, hash::algorithm::__algorithm__::combine64, shift);
}
// Value in in right position + user shift
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui64 simple64Combine_r(const ui64 value, const ui64 shift) noexcept {
	return meta::hash::algorithm::simpleCombine<ui64, IS_REVERSE>(hash::algorithm::__algorithm__::combine64, value, shift);
}
// Values + no shift
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui64 simple64Combine_noshift(const ui64 value1, const ui64 value2) noexcept {
	return meta::hash::algorithm::simpleCombine<ui64, IS_REVERSE>(value1, value2, hash::algorithm::__algorithm__::llshift64);
}
// Value in in left position
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui64 simple64Combine_l(const ui64 value) noexcept {
	return meta::hash::algorithm::simple64Combine_l<IS_REVERSE>(value, hash::algorithm::__algorithm__::llshift64);
}
// Value in in right position
template<ll_bool_t IS_REVERSE = llcpp::FALSE>
__LL_NODISCARD__ constexpr ui64 simple64Combine_r(const ui64 value) noexcept {
	return meta::hash::algorithm::simple64Combine_r<IS_REVERSE>(value, hash::algorithm::__algorithm__::llshift64);
}

#pragma endregion

#pragma endregion

} // namespace algorithm
} // namespace hash
} // namespace meta
} // namespace llcpp

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#endif // LLANYLIB_HASHALGORITHM_HPP_
