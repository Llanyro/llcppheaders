//////////////////////////////////////////////
//	hash_algorithm.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHALGORITHM_HPP_) // Guard && version protector
	#if LLANYLIB_HASHALGORITHM_MAYOR_ != 8 || LLANYLIB_HASHALGORITHM_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "hash_algorithm.hpp version error!"
		#else
			#error "hash_algorithm.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASHALGORITHM_MAYOR_ || LLANYLIB_HASHALGORITHM_MINOR_

#else !defined(LLANYLIB_HASHALGORITHM_HPP_)
#define LLANYLIB_HASHALGORITHM_HPP_
#define LLANYLIB_HASHALGORITHM_MAYOR_ 8
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
namespace combine {
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

// Murmur-inspired hashing.
#pragma region Murmur
#pragma region 8
__LL_NODISCARD__ constexpr ui8 murmur8Combine(const ui8 value1, const ui8 value2) noexcept {
	ui8 a = static_cast<ui8>((value1 ^ value2) * combine::kMul8);
	a ^= (a >> combine::llshift8);
	ui8 b = static_cast<ui8>((value2 ^ a) * combine::kMul8);
	b ^= (b >> combine::llshift8);
	b *= combine::kMul8;
	return b;
}
// Value in in left position
__LL_NODISCARD__ constexpr ui8 murmur8Combine_l(const ui8 value) noexcept {
	return combine::murmur8Combine(value, combine::combine8);
}
// Value in in right position
__LL_NODISCARD__ constexpr ui8 murmur8Combine_r(const ui8 value) noexcept {
	return combine::murmur8Combine(combine::combine8, value);
}

#pragma endregion
#pragma region 32
__LL_NODISCARD__ constexpr ui32 murmur32Combine(const ui32 value1, const ui32 value2) noexcept {
	ui32 a = (value1 ^ value2) * combine::kMul32;
	a ^= (a >> combine::llshift32);
	ui32 b = (value2 ^ a) * combine::kMul32;
	b ^= (b >> combine::llshift32);
	b *= combine::kMul32;
	return b;
}
// Value in in left position
__LL_NODISCARD__ constexpr ui32 murmur32Combine_l(const ui32 value) noexcept {
	return combine::murmur32Combine(value, combine::combine32);
}
// Value in in right position
__LL_NODISCARD__ constexpr ui32 murmur32Combine_r(const ui32 value) noexcept {
	return combine::murmur32Combine(combine::combine32, value);
}

#pragma endregion
#pragma region 64
__LL_NODISCARD__ constexpr ui64 murmur64Combine(const ui64 value1, const ui64 value2) noexcept {
	ui64 a = (value1 ^ value2) * combine::kMul64;
	a ^= (a >> combine::llshift64);
	ui64 b = (value2 ^ a) * combine::kMul64;
	b ^= (b >> combine::llshift64);
	b *= combine::kMul64;
	return b;
}
// Value in in left position
__LL_NODISCARD__ constexpr ui64 murmur64Combine_l(const ui64 value) noexcept {
	return combine::murmur64Combine(value, combine::combine64);
}
// Value in in right position
__LL_NODISCARD__ constexpr ui64 murmur64Combine_r(const ui64 value) noexcept {
	return combine::murmur64Combine(combine::combine64, value);
}

#pragma endregion

#pragma endregion
#pragma region Combine
#pragma region Template
template<class T, ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr T simpleCombine(const T value1, const T value2, const ui8 shift) noexcept {
	if constexpr (IS_REVERSE) return static_cast<T>(value1 ^ (value2 << shift));
	else return static_cast<T>(value1 ^ (value2 >> shift));
}

#pragma endregion
#pragma region 8
// Value in in left position + user shift
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui8 simple8Combine_l(const ui8 value, const ui8 shift) noexcept {
	return combine::simpleCombine<ui8, IS_REVERSE>(value, combine::combine8, shift);
}
// Value in in right position + user shift
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui8 simple8Combine_r(const ui8 value, const ui8 shift) noexcept {
	return combine::simpleCombine<ui8, IS_REVERSE>(combine::combine8, value, shift);
}
// Values + no shift
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui8 simple8Combine_noshift(const ui8 value1, const ui8 value2) noexcept {
	return combine::simpleCombine<ui8, IS_REVERSE>(value1, value2, combine::llshift8);
}
// Value in in left position
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui8 simple8Combine_l(const ui8 value) noexcept {
	return combine::simple8Combine_l<IS_REVERSE>(value, combine::llshift8);
}
// Value in in right position
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui8 simple8Combine_r(const ui8 value) noexcept {
	return combine::simple8Combine_r<IS_REVERSE>(value, combine::llshift8);
}

#pragma endregion
#pragma region 32
// Value in in left position + user shift
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui32 simple32Combine_l(const ui32 value, const ui32 shift) noexcept {
	return combine::simpleCombine<ui32, IS_REVERSE>(value, combine::combine32, shift);
}
// Value in in right position + user shift
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui32 simple32Combine_r(const ui32 value, const ui32 shift) noexcept {
	return combine::simpleCombine<ui32, IS_REVERSE>(combine::combine32, value, shift);
}
// Values + no shift
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui32 simple32Combine_noshift(const ui32 value1, const ui32 value2) noexcept {
	return combine::simpleCombine<ui32, IS_REVERSE>(value1, value2, combine::llshift32);
}
// Value in in left position
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui32 simple32Combine_l(const ui32 value) noexcept {
	return combine::simple32Combine_l<IS_REVERSE>(value, combine::llshift32);
}
// Value in in right position
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui32 simple32Combine_r(const ui32 value) noexcept {
	return combine::simple32Combine_r<IS_REVERSE>(value, combine::llshift32);
}

#pragma endregion
#pragma region 64
// Value in in left position + user shift
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui64 simple64Combine_l(const ui64 value, const ui64 shift) noexcept {
	return combine::simpleCombine<ui64, IS_REVERSE>(value, combine::combine64, shift);
}
// Value in in right position + user shift
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui64 simple64Combine_r(const ui64 value, const ui64 shift) noexcept {
	return combine::simpleCombine<ui64, IS_REVERSE>(combine::combine64, value, shift);
}
// Values + no shift
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui64 simple64Combine_noshift(const ui64 value1, const ui64 value2) noexcept {
	return combine::simpleCombine<ui64, IS_REVERSE>(value1, value2, combine::llshift64);
}
// Value in in left position
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui64 simple64Combine_l(const ui64 value) noexcept {
	return combine::simple64Combine_l<IS_REVERSE>(value, combine::llshift64);
}
// Value in in right position
template<ll_bool_t IS_REVERSE = LL_FALSE>
__LL_NODISCARD__ constexpr ui64 simple64Combine_r(const ui64 value) noexcept {
	return combine::simple64Combine_r<IS_REVERSE>(value, combine::llshift64);
}

#pragma endregion

#pragma endregion

} // namespace combine
namespace traits {

struct Test {
	void asdf() noexcept;
};
using Signature = void(Test::*)() noexcept;
using Signature2 = void(Test::*)(int) noexcept;

#pragma region 
template< typename T, typename E>
struct has_const_reference_op
{
    /* SFINAE operator-has-correct-sig :) */
    template<typename A>
    static std::true_type test(E (A::*)() const) {
        return std::true_type();
    }

    /* SFINAE operator-exists :) */
    template <typename A> 
    static decltype(test(&A::operator*)) 
    test(decltype(&A::operator*),void *) {
        /* Operator exists. What about sig? */
        typedef decltype(test(&A::operator*)) return_type; 
        return return_type();
    }

    /* SFINAE game over :( */
    template<typename A>
    static std::false_type test(...) {
        return std::false_type(); 
    }

    /* This will be either `std::true_type` or `std::false_type` */
    typedef decltype(test<T>(0,0)) type;

    static const bool value = type::value; /* Which is it? */
};

template<typename Sig, class HashGenerator>
struct HasUsedMemoryMethod {
	template<typename U, class W, size_t(U::*)() const> struct SFINAE {};
	template<typename U, class W> static char Test(SFINAE<U, W, &U::hash>*);
	template<typename U, class W> static int Test(...);
	static constexpr ll_bool_t has = sizeof(Test<Sig, HashGenerator>(0)) == sizeof(char);
};
#pragma endregion

template<class T, class HashGenerator>
struct get_hash_function {
	__LL_NODISCARD__ static constexpr T getHashFunction(HashGenerator* p) noexcept {
		T a = &HashGenerator::hash;
		p->*a();
		return a;
	}
	__LL_NODISCARD__ static constexpr auto getHashFunction(...) noexcept -> void {}
	using value = decltype(getHashFunction(nullptr));
};

//using result = get_hash_function<Signature, Test>::value;
__LL_VAR_INLINE__ constexpr ll_bool_t has_hash_function = HasUsedMemoryMethod<Test>::has;

// Checks if exist hash function in HashGenerator
template<class T, class HashGenerator>
//__LL_VAR_INLINE__ constexpr ll_bool_t has_hash_function = std::is_same_v<T, get_hash_function<T, HashGenerator>::value>;

template<class HashGenerator, class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t has_any_hash_function =
	std::is_same_v<T, get_hash_function<Args, HashGenerator>::value> || ...;

} // namespace traits
} // namespace hash
} // namespace meta
} // namespace llcpp

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#endif // LLANYLIB_HASHALGORITHM_HPP_
