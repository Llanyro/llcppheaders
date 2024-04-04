/*
 *	traits.hpp
 *
 *	Author: Francisco Julio Ruiz Fernandez
 *	Author: llanyro
 *
 *	Version: 4.2
 */

#if defined(LLANYLIB_TRAITS_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITS_MAYOR_ != 4 || LLANYLIB_TRAITS_MINOR_ < 2
		#error "traits.hpp version error!"
	#endif // LLANYLIB_TRAITS_MAYOR_ || LLANYLIB_TRAITS_MINOR_

#else !defined(LLANYLIB_TRAITS_HPP_)
#define LLANYLIB_TRAITS_HPP_
#define LLANYLIB_TRAITS_MAYOR_ 4
#define LLANYLIB_TRAITS_MINOR_ 2

#define LL_TRAITS_TEST

#include "definitions.hpp"
#include "types.hpp"

#if defined(LL_TRAITS_TEST)
	#include "examples/traits_test_class.hpp"
#endif

#include <type_traits>

namespace llcpp {
namespace traits {

// Easy enabler for template functions
#define ENABLE_FUNCTION_PARAM(condition, ret) class __ret__ = ret, typename = std::enable_if_t<__is_void_type__, __ret__>

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_basic_type_v = std::_Is_any_of_v<std::remove_const_t<T>, ui8, ui16, ui32, ui64, i8, i16, i32, i64, f32, f64>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_basic_type_or_ptr_v = is_basic_type_v<T> || std::is_pointer_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_floating_type_v = std::_Is_any_of_v<std::remove_const_t<T>, f32, f64>;

// Returns a type with reference if object is not basic type
template<class T>
using get_object_reference_t = std::conditional_t<traits::is_basic_type_v<T>, T, T&>;

template <class T, class OperatorType>
struct has_type_operator {
    template <class U>
	static auto test(U* p) -> decltype(p->operator OperatorType(), std::true_type{});
	template <class>
	static auto test(...) ->
		std::conditional_t<
			is_basic_type_v<T>,
			std::bool_constant<std::is_same_v<T, OperatorType>>,
			std::false_type
		>;
	using val = decltype(test<T>(nullptr));
};

template <class T, class OperatorType>
__LL_VAR_INLINE__ constexpr ll_bool_t has_type_operator_v = has_type_operator<T, OperatorType>::val::value;

#define __LL_TEMPLATE_HAS_FUNCTION_BASE__(name, function, basic_value) \
	template<class T> \
	struct has_##name## { \
		template <class U> \
		static auto test(U* p) -> decltype(##function##, std::true_type{}); \
		template <class> \
		static auto test(...) -> \
			std::conditional_t< \
				is_basic_type_v<T>, \
				std::bool_constant<basic_value>, \
				std::false_type \
			>; \
		using val = decltype(test<T>(nullptr)); \
	}; \
	template <class T> \
	__LL_VAR_INLINE__ constexpr ll_bool_t has_##name##_v = has_##name##<T>::val::value

#define __LL_TEMPLATE_HAS_FUNCTION__(name, function) __LL_TEMPLATE_HAS_FUNCTION_BASE__(name, function, LL_FALSE)
#define __TEMPLATE_HAS_SIMPLE_FUNCTION__(function) __LL_TEMPLATE_HAS_FUNCTION__(function, p->##function())

__LL_TEMPLATE_HAS_FUNCTION_BASE__(copy_operator, p->operator=(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(move_operator, p->operator=(std::move(*p)), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(three_compare_operator, p->operator<=>(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(equal_operator, p->operator==(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(no_equal_operator, p->operator!=(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(greater_operator, p->operator>(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(lower_operator, p->operator<(*p), LL_TRUE);

__LL_TEMPLATE_HAS_FUNCTION__(swap, p->swap(*p));
__LL_TEMPLATE_HAS_FUNCTION__(swap_s, p->swap_s(*p));
__TEMPLATE_HAS_SIMPLE_FUNCTION__(clear);

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_nothrow_constructible_v =
	std::is_pointer_v<T> ||
	traits::is_basic_type_v<T> ||
	noexcept(T());
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_nothrow_destructible_v =
	std::is_pointer_v<T> ||
	traits::is_basic_type_v<T> ||
	noexcept(std::declval<T>().~T());

#pragma region TypeConversions
template<class T, ll_bool_t promote>
struct promote_type {
	using __type = T;
	static constexpr ll_bool_t isPromoted = promote;
};

#pragma region Unsigned
template<ll_bool_t promote>
struct promote_type<ui64, promote> {
	using __type = std::conditional_t<promote, ui128, ui32>;
	static constexpr ll_bool_t isPromoted = promote;
};

template<ll_bool_t promote>
struct promote_type<ui32, promote> {
	using __type = std::conditional_t<promote, ui64, ui16>;
	static constexpr ll_bool_t isPromoted = promote;
};

template<ll_bool_t promote>
struct promote_type<ui16, promote> {
	using __type = std::conditional_t<promote, ui32, ui8>;
	static constexpr ll_bool_t isPromoted = promote;
};

template<ll_bool_t promote>
struct promote_type<ui8, promote> {
	using __type = std::conditional_t<promote, ui16, ui8>;
	static constexpr ll_bool_t isPromoted = promote;
};

#pragma endregion
#pragma region Floating-point
template<ll_bool_t promote>
struct promote_type<f64, promote> {
	using __type = std::conditional_t<promote, f128, f32>;
	static constexpr ll_bool_t isPromoted = promote;
};

template<ll_bool_t promote>
struct promote_type<f32, promote> {
	using __type = std::conditional_t<promote, f64, f32>;
	static constexpr ll_bool_t isPromoted = promote;
};

#pragma endregion

#pragma endregion

template<class T>
using get_smaller_type_u = promote_type<T, LL_FALSE>::__type;

template<class T>
using get_bigger_type_u = promote_type<T, LL_TRUE>;

template<class T>
using get_smaller_type_t = 
	std::conditional_t<
		std::is_unsigned_v<T>,
		get_smaller_type_u<T>,
		std::make_signed_t<get_smaller_type_u<std::make_unsigned_t<T>>>
	>;

template<class T>
using get_bigger_type_t = 
	std::conditional_t<
		std::is_unsigned_v<T>,
		get_bigger_type_u<T>,
		std::make_signed_t<get_bigger_type_u<std::make_unsigned_t<T>>>
	>;

template<class ReturnType, class ObjectType>
constexpr ReturnType operatorTypeCall(const ObjectType& object) __LL_EXCEPT__ {
	if constexpr (std::is_pointer_v<ObjectType>) {
		using __noptr = std::remove_pointer_t<ObjectType>;

		if constexpr (std::is_pointer_v<__noptr>)
			return static_cast<ReturnType>(object);
		else if constexpr (has_type_operator_v<__noptr, ReturnType>) {
			if constexpr (is_basic_type_v<__noptr>) return *object;
			else return object->operator ReturnType();
		}
		else if constexpr (is_basic_type_v<__noptr>)
			return static_cast<ReturnType>(*object);
		else return LL_FALSE;
	}
	else if constexpr (has_type_operator_v<ObjectType, ReturnType>) {
		if constexpr (is_basic_type_v<ObjectType>) return object;
		else return object.operator ReturnType();
	}
	else if constexpr (is_basic_type_v<ObjectType>)
		return static_cast<ReturnType>(object);
	else return LL_FALSE;
}

using Testinng1 = std::add_lvalue_reference_t<void>;
using Testinng2 = std::add_rvalue_reference_t<void>;

using Testinng3 = std::add_lvalue_reference_t<int>;
using Testinng4 = std::add_rvalue_reference_t<int>;



} // namespace traits
} // namespace llcpp

#endif // LLANYLIB_TRAITS_HPP_
