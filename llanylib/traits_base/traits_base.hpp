//////////////////////////////////////////////
//	traits_base.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSBASE_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSBASE_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TRAITSBASE_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_base.hpp(incomplete) version error!"
		#else
			#error "traits_base.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSBASE_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSBASE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSBASE_INCOMPLETE_HPP_)
	#define LLANYLIB_TRAITSBASE_INCOMPLETE_HPP_
	#define LLANYLIB_TRAITSBASE_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_TRAITSBASE_INCOMPLETE_MINOR_ 0

#include "type_traits.hpp"

#elif defined(LLANYLIB_TRAITSBASE_HPP_)
	#if LLANYLIB_TRAITSBASE_MAYOR_ != 11 || LLANYLIB_TRAITSBASE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_base.hpp version error!"
		#else
			#error "traits_base.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSBASE_MAYOR_ || LLANYLIB_TRAITSBASE_MINOR_

#else
	#define LLANYLIB_TRAITSBASE_HPP_
	#define LLANYLIB_TRAITSBASE_MAYOR_ 11
	#define LLANYLIB_TRAITSBASE_MINOR_ 0

#include "type_traits.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_empty_object_v = ::std::_Is_any_of_v<T, ::llcpp::Emptyclass, ::llcpp::Void>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_empty_type_v = ::std::is_same_v<T, void> || ::llcpp::meta::traits::is_empty_object_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_basic_type_v = ::std::is_arithmetic_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_basic_bigger_type_v = ::std::_Is_any_of_v<T, i128, i256, u128, u256>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_floating_type_v = ::std::is_floating_point_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_floating_bigger_type_v = ::std::_Is_any_of_v<T, f128>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_char_type_v = ::std::_Is_any_of_v<T, ll_char_t, ll_wchar_t>;

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_of_a_basic_type_v =
	(::llcpp::meta::traits::is_basic_type_v<Args> || ...);
template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_all_of_a_basic_type_v =
	(::llcpp::meta::traits::is_basic_type_v<Args> && ...);

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_of_a_floating_type_v =
	(::llcpp::meta::traits::is_floating_type_v<Args> || ...);
template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_all_of_a_floating_type_v =
	(::llcpp::meta::traits::is_floating_type_v<Args> && ...);

template<class _T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_raw_type =
	::llcpp::meta::traits::is_basic_type_v<_T>
	|| ::std::is_class_v<_T>;

// [TOFIX]
//template<class T>
//__LL_VAR_INLINE__ constexpr ll_bool_t is_hash_type_v =
//	std::_Is_any_of_v<T, meta::hash::Hash32, meta::hash::Hash64, meta::hash::Hash128>;

template<class T>
using array_type_t = ::std::remove_extent_t<T>;
template<class T>
using input = ::llcpp::meta::traits::conditional_t<::std::is_class_v<T>, T&, T>;
template<class T>
using cinput = ::llcpp::meta::traits::conditional_t<::std::is_class_v<T>, const T&, const T>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSBASE_HPP_

#if !defined(LLANYLIB_TRAITSBASE_EXTRA_HPP_) && !defined(LLANYLIB_ERROR_HPP_)
#define LLANYLIB_TRAITSBASE_EXTRA_HPP_

namespace llcpp {
namespace meta {
namespace traits {

template<class>
__LL_VAR_INLINE__ constexpr u64 array_size = ::llcpp::ZERO_VALUE<u64>;
template<class T, u64 N>
__LL_VAR_INLINE__ constexpr u64 array_size<T[N]> = N;

template<class>
__LL_VAR_INLINE__ constexpr u64 type_or_array_size = 1ull;
template<class T, u64 N>
__LL_VAR_INLINE__ constexpr u64 type_or_array_size<T[N]> = N;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSBASE_EXTRA_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
