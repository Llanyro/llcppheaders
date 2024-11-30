//////////////////////////////////////////////
//	traits_type_modifier.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_type_modifier.hpp(incomplete) version error!"
		#else
			#error "traits_type_modifier.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_HPP_)
#define LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_HPP_
#define LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MINOR_ 0

#include "traits_selection.hpp"
#undef LLANYLIB_INCOMPLETE_HPP_
#include "../types_base/type_update.hpp"
#define LLANYLIB_INCOMPLETE_HPP_

namespace llcpp {
namespace meta {
namespace traits {

struct type_update_t;
struct attribute_counter;

template<class _T, ::llcpp::meta::attributes::type_update_t _ATTRIBUTES>
constexpr auto type_modifier();

} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TRAITSTYPEMODIFIER_HPP_)
	#if LLANYLIB_TRAITSTYPEMODIFIER_MAYOR_ != 11 || LLANYLIB_TRAITSTYPEMODIFIER_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_type_modifier.hpp version error!"
		#else
			#error "traits_type_modifier.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSTYPEMODIFIER_MAYOR_ || LLANYLIB_TRAITSTYPEMODIFIER_MINOR_

#else
#define LLANYLIB_TRAITSTYPEMODIFIER_HPP_
#define LLANYLIB_TRAITSTYPEMODIFIER_MAYOR_ 11
#define LLANYLIB_TRAITSTYPEMODIFIER_MINOR_ 0

#include "traits_base.hpp"
#include "../types_base/type_update.hpp"

namespace llcpp {
namespace meta {
namespace traits {
namespace __traits__ {

	// [TODO]
// 	Use a data container to count type attributes
// 	So user can select how many attributes wants to remove or add...
// [TOFIX]
struct attribute_counter_t {
	// Class related
	using _MyType = attribute_counter_t;

	// Attributes
	ll_bool_t REMOVE_POINTER	: 1;
	ll_bool_t REMOVE_CONST		: 1;
	ll_bool_t REMOVE_VOLATILE	: 1;
	ll_bool_t REMOVE_ARRAY		: 1;
	ll_bool_t REMOVE_REFERENCE	: 1;
};

template<class _T, ::llcpp::meta::attributes::type_update_t _ATTRIBUTES>
constexpr auto type_modifier() {
	namespace traits_func = ::llcpp::meta::traits;
	if constexpr (::std::is_array_v<_T>) {
		// Remove array from type
		using type_edited = traits_func::array_type_t<_T>;
		using packed_type = decltype(traits_func::__traits__::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_ARRAY)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<unpacked_type[traits_func::array_size<_T>]>{};
	}
	else if constexpr (::std::is_reference_v<_T>) {
		// Remove reference from type
		using type_edited	= ::std::remove_reference_t<_T>;
		using packed_type	= decltype(traits_func::__traits__::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_REFERENCE)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<unpacked_type&>{};
	}
	else if constexpr (::std::is_pointer_v<_T>) {
		// Remove pointer from type
		using type_edited	= ::std::remove_pointer_t<_T>;
		using packed_type	= decltype(traits_func::__traits__::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_POINTER)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<unpacked_type*>{};
	}
	else if constexpr (::std::is_const_v<_T>) {
		// Remove const from type
		using type_edited	= ::std::remove_const_t<_T>;
		using packed_type	= decltype(traits_func::__traits__::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_CONST)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<const unpacked_type>{};
	}
	else if constexpr (::std::is_volatile_v<_T>) {
		// Remove const from type
		using type_edited	= ::std::remove_volatile_t<_T>;
		using packed_type	= decltype(traits_func::__traits__::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_CONST)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<volatile unpacked_type>{};
	}
	else return traits_func::TypeContainer<_T>{};
}

} // namespace __traits__

template<class T, ::llcpp::meta::attributes::type_update_t ATTRIBUTES>
using type_modifier_t = decltype(::llcpp::meta::traits::__traits__::type_modifier<T, ATTRIBUTES>())::T;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSTYPEMODIFIER_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
