//////////////////////////////////////////////
//	traits_base.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSBASE_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSBASE_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_TRAITSBASE_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "traits_base.hpp(incomplete) version error!"
		#else
			#error "traits_base.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSBASE_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSBASE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSBASE_INCOMPLETE_HPP_)
	#define LLANYLIB_TRAITSBASE_INCOMPLETE_HPP_
	#define LLANYLIB_TRAITSBASE_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_TRAITSBASE_INCOMPLETE_MINOR_ 0

#include "type_traits.hpp"

#elif defined(LLANYLIB_TRAITSBASE_HPP_)
	#if LLANYLIB_TRAITSBASE_MAYOR_ != 12 || LLANYLIB_TRAITSBASE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "traits_base.hpp version error!"
		#else
			#error "traits_base.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSBASE_MAYOR_ || LLANYLIB_TRAITSBASE_MINOR_

#else
	#define LLANYLIB_TRAITSBASE_HPP_
	#define LLANYLIB_TRAITSBASE_MAYOR_ 12
	#define LLANYLIB_TRAITSBASE_MINOR_ 0

#include "type_traits.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<class T, class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_of_v =
#if __LL_REAL_CXX17 == 1
	(::std::is_same_v<T, Args> || ...);
#else
	::std::disjunction_v<::std::is_same_v<T, Args>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_empty_object_v = ::llcpp::meta::traits::is_any_of_v<T, ::llcpp::Emptyclass>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_empty_type_v = ::std::is_same_v<T, void> || ::llcpp::meta::traits::is_empty_object_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_primitive_v = ::std::is_integral_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_primitive_big_v = ::llcpp::meta::traits::is_any_of_v<T, i128, i256, u128, u256>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_primitive_v = ::llcpp::meta::traits::is_primitive_v<T> || ::llcpp::meta::traits::is_primitive_big_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_floating_type_v = ::std::is_floating_point_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_floating_bigger_type_v = ::llcpp::meta::traits::is_any_of_v<T, f128>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_floating_v = ::llcpp::meta::traits::is_floating_type_v<T> || ::llcpp::meta::traits::is_floating_bigger_type_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_char_type_v = ::llcpp::meta::traits::is_any_of_v<T, ll_char_t, ll_wchar_t>;

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_of_a_basic_type_v =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::traits::is_primitive_v<Args> || ...);
#else
	::std::disjunction_v<::llcpp::meta::traits::is_primitive_v<Args>...>;
#endif // __LL_REAL_CXX17 == 1

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_all_of_a_basic_type_v =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::traits::is_any_primitive_v<Args> || ...);
#else
	::std::disjunction_v<::llcpp::meta::traits::is_any_primitive_v<Args>...>;
#endif // __LL_REAL_CXX17 == 1

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_of_a_floating_type_v =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::traits::is_floating_type_v<Args> || ...);
#else
	::std::disjunction_v<::llcpp::meta::traits::is_floating_type_v<Args>...>;
#endif // __LL_REAL_CXX17 == 1

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_all_of_a_floating_type_v =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::traits::is_any_floating_v<Args> || ...);
#else
	::std::disjunction_v<::llcpp::meta::traits::is_any_floating_v<Args>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_trivial_v =
	::llcpp::meta::traits::is_any_primitive_v<T>
	|| ::llcpp::meta::traits::is_any_floating_v<T>;

// [TOCHECK] [TODO]
//template<class _T>
//__LL_VAR_INLINE__ constexpr ll_bool_t is_raw_type =
//	::llcpp::meta::traits::is_primitive_v<_T>
//	|| ::std::is_class_v<_T>;

template<class T>
using array_type_t = ::std::remove_extent_t<T>;
template<class T>
using input = ::llcpp::meta::traits::conditional_t<::std::is_class_v<T> && !::std::is_pointer_v<T>, T&, T>;
//template<class T>
//using input = ::llcpp::meta::traits::conditional_t<::std::is_pointer_v<T>, T, T&>;
template<class T>
using cinput = ::llcpp::meta::traits::conditional_t<::std::is_class_v<T> && !::std::is_pointer_v<T>, const T&, const T>;

template<class T>
using pointer_t			= T*;
template<class T>
using const_pointer_t	= T*;

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
