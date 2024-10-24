//////////////////////////////////////////////
//	traits_selection.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSSELECTION_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSSELECTION_MAYOR_ != 10 || LLANYLIB_TRAITSSELECTION_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_selection.hpp version error!"
		#else
			#error "traits_selection.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSSELECTION_MAYOR_ || LLANYLIB_TRAITSSELECTION_MINOR_

#else !defined(LLANYLIB_TRAITSSELECTION_HPP_)
#define LLANYLIB_TRAITSSELECTION_HPP_
#define LLANYLIB_TRAITSSELECTION_MAYOR_ 10
#define LLANYLIB_TRAITSSELECTION_MINOR_ 0

#include "type_traits.hpp"

namespace llcpp {
namespace meta {
namespace traits {

// Returns a type that coincides with one given
// get_conincidence<X, Args..> where:
//	X		-> Type to find
//	Args... -> all arguments to find stored in a traits::double_type_container<T, U> where:
//		T -> type to compare with X
//		U -> type to return if X is same type as T
template<class _VoidType = llcpp::Emptyclass>
struct type_selection {
	// Class related
	using _MyType	= type_selection;

	// Types and enums
	using VoidType	= _VoidType;

	// Functions
	template<class X, class T, class... Args>
	__LL_NODISCARD__ static constexpr auto get_by_type() noexcept {
		// [TOFIX]
		// Insert here a static_assert to check if args are double containers type
		if constexpr (std::is_same_v<typename T::T, X>)
			return traits::type_container<typename T::U>{};
		else return _MyType::get_by_type<X, Args...>();
	}
	template<class X, class T>
	__LL_NODISCARD__ static constexpr auto get_by_type() noexcept {
		if constexpr (std::is_same_v<typename T::T, X>)
			return traits::type_container<typename T::U>{};
		else return traits::type_container<VoidType>{};
	}
	template<class X>
	__LL_NODISCARD__ static constexpr auto get_by_type() noexcept {
		return traits::type_container<VoidType>{};
	}
	template<class X, class... Args>
	using get_conincidence = decltype(_MyType::get_by_type<X, Args...>())::T;

	template<class T, class... Args>
	__LL_NODISCARD__ static constexpr auto get_by_condition() noexcept {
		// [TOFIX]
		// Insert here a static_assert to check if args are double containers type
		if constexpr (T::VALUE)
			return traits::type_container<typename T::U>{};
		else return _MyType::get_by_condition<Args...>();
	}
	template<class T>
	__LL_NODISCARD__ static constexpr auto get_by_condition() noexcept {
		if constexpr (T::VALUE)
			return traits::type_container<typename T::U>{};
		else return traits::type_container<VoidType>{};
	}
	template<class... Args>
	using get_conincidence_condition = decltype(_MyType::get_by_condition<Args...>())::T;

	// Functions
	template<class X, class T, class... Args>
	__LL_NODISCARD__ static constexpr auto get_first_difference_f() noexcept {
		// [TOFIX]
		// Insert here a static_assert to check if args are double containers type
		if constexpr (!std::is_same_v<typename T::T, X>)
			return traits::type_container<typename T::U>{};
		else return _MyType::get_by_type<X, Args...>();
	}
	template<class X, class T>
	__LL_NODISCARD__ static constexpr auto get_first_difference_f() noexcept {
		if constexpr (!std::is_same_v<typename T::T, X>)
			return traits::type_container<typename T::U>{};
		else return traits::type_container<VoidType>{};
	}
	template<class X>
	__LL_NODISCARD__ static constexpr auto get_first_difference_f() noexcept {
		return traits::type_container<VoidType>{};
	}
	template<class X, class... Args>
	using get_first_difference = decltype(_MyType::get_first_difference_f<X, Args...>())::T;
};

template<class T, class TypeChar, class TypeWChar, class ExtraType = void>
using get_by_char_type_t = traits::type_selection<ExtraType>::get_conincidence<
	T,
	traits::double_type_container<ll_char_t, TypeChar>,
	traits::double_type_container<ll_wchar_t, TypeWChar>
>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSSELECTION_HPP_
