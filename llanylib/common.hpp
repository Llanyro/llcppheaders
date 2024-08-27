//////////////////////////////////////////////
//	common.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_COMMON_HPP_) // Guard && version protector
	#if LLANYLIB_COMMON_MAYOR_ != 9 || LLANYLIB_COMMON_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "common.hpp version error!"
		#else
			#error "common.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_COMMON_MAYOR_ || LLANYLIB_COMMON_MINOR_

#else !defined(LLANYLIB_COMMON_HPP_)
#define LLANYLIB_COMMON_HPP_
#define LLANYLIB_COMMON_MAYOR_ 9
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
		T tmp = std::forward<T&&>(v1);
		v1 = std::forward<T&&>(v2);
		v2 = std::forward<T&&>(tmp);
	}
}
template<class T, class U = T>
constexpr cmp_t compare_with_operators(T v1, U v2) noexcept {
	if (v1 == v2) return 0;
	else if (v1 > v2) return 1;
	else return -1;
}
template<class T, class U = T>
constexpr cmp_t compare_with_operators_void(const void* _a, const void* _b) noexcept {
	__LL_ASSERT_VAR_NULL__(_a, "_a");
	__LL_ASSERT_VAR_NULL__(_b, "_b");

	const T* a = reinterpret_cast<const T*>(_a);
	const U* b = reinterpret_cast<const U*>(_b);

	if (*a == *b) return 0;
	else if (*a > *b) return 1;
	else return -1;
}

template<class T, class U>
constexpr ll_bool_t simple_equals(T v1, U v2) noexcept { return v1 == v2; }
template<class T, class U = T&>
constexpr void simple_set(T& v1, U v2) noexcept { v1 = v2; }
template<class T, class U = T>
constexpr void simple_move(T& v1, U& v2) noexcept { v1 = std::move(v2); }
template<class T>
constexpr void copy_n_set(T*& dst, T*& src, T* set_val = LL_NULLPTR) noexcept {
	dst = src;
	src = set_val;
}

template<class T>
constexpr void clear_if_pointer(T& value) {
	if constexpr (std::is_pointer_v<T>)
		value = LL_NULLPTR;
}
template<class T, len_t N>
constexpr void clear_if_pointer(T(&value)[N]) {
	if constexpr (std::is_pointer_v<T>)
		for (T data = value, end = value + N; data < end; ++data)
			data = LL_NULLPTR;
}
template<class T>
constexpr void clear_if_pointer(T begin, T end) {
	if constexpr (std::is_pointer_v<T>)
		for (T data = begin; data < end; ++data)
			data = LL_NULLPTR;
}

} // namespace common
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_COMMON_HPP_
