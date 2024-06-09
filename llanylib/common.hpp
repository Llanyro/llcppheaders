//////////////////////////////////////////////
//	common.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_COMMON_HPP_) // Guard && version protector
	#if LLANYLIB_COMMON_MAYOR_ != 8 || LLANYLIB_COMMON_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "common.hpp version error!"
		#else
			#error "common.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_COMMON_MAYOR_ || LLANYLIB_COMMON_MINOR_

#else !defined(LLANYLIB_COMMON_HPP_)
#define LLANYLIB_COMMON_HPP_
#define LLANYLIB_COMMON_MAYOR_ 8
#define LLANYLIB_COMMON_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace meta {
namespace common {

template<class T>
constexpr void simple_swap(T& v1, T& v2) noexcept {
	if constexpr (traits::is_basic_type_v<T> || std::is_pointer_v<T>) {
		T tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
	else {
		T tmp = std::move(v1);
		v1 = std::move(v2);
		v2 = std::move(tmp);
	}
}

template<class T, class U = T>
constexpr cmp_t compare_with_operators(T v1, U v2) noexcept {
	//static_assert(traits::has_no_equal_operator_v<T>, "Error, <T> object has no operator!=()");
	//static_assert(traits::has_greater_operator_v<T>, "Error, <T> object has no operator>()");

	if (v1 == v2) return 0;
	else if (v1 > v2) return 1;
	else return -1;
}

template<class T, class U = T>
constexpr cmp_t compare_with_operators_void(const void* _a, const void* _b) noexcept {
	__LL_ASSERT_VAR_NULL__(_a, "_a");
	__LL_ASSERT_VAR_NULL__(_b, "_b");

	//static_assert(traits::has_no_equal_operator_v<T>, "Error, <T> object has no operator!=()");
	//static_assert(traits::has_greater_operator_v<T>, "Error, <T> object has no operator>()");

	const T* a = reinterpret_cast<const T*>(_a);
	const U* b = reinterpret_cast<const U*>(_b);

	if (*a == *b) return 0;
	else if (*a > *b) return 1;
	else return -1;
}

template<class T, class U>
constexpr ll_bool_t simple_equals(T v1, U v2) noexcept {
	//static_assert(traits::has_equal_operator_v<T>, "Error, <T> object has no operator==()");
	return v1 == v2;
}
template<class T, class U = T&>
constexpr void simple_set(T& v1, U v2) noexcept { v1 = v2; }

} // namespace common
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_COMMON_HPP_
