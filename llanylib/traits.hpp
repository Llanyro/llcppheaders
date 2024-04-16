//////////////////////////////////////////////
//	traits.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 4.2							//
//////////////////////////////////////////////

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
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_char_type_v = std::_Is_any_of_v<std::remove_const_t<T>, ll_char_t, ll_uchar_t, ll_wchar_t>;

// Returns a type with reference if object is not basic type
// Is only used when type parameter will be const
template<class T>
using get_object_reference_t = std::conditional_t<traits::is_basic_type_v<T>, T, std::add_lvalue_reference_t<T>>;

#pragma region CharConditional
template<class T, class TypeChar, class TypeUChar, class TypeWChar>
struct get_by_char_type {
	template <class U>
	struct __internal__struct__ { using _val = void; };
	template<> struct __internal__struct__<ll_char_t> { using _val = TypeChar; };
	template<> struct __internal__struct__<ll_uchar_t> { using _val = TypeUChar; };
	template<> struct __internal__struct__<ll_wchar_t> { using _val = TypeWChar; };
	using value = __internal__struct__<std::remove_const_t<T>>::_val;
};

template<class T, class TypeChar, class TypeUChar, class TypeWChar>
using get_by_char_type_t = get_by_char_type<T, TypeChar, TypeUChar, TypeWChar>::value;

#pragma endregion
#pragma region FunctionCheckers
#pragma region DefinesAndStructs
template <class T, class OperatorType>
struct has_type_operator {
    template <class U>
	static auto test(U* p) -> decltype(p->operator OperatorType(), std::true_type{});
    template <class U>
	static auto test(const U* p) -> decltype(p->operator OperatorType(), std::true_type{});
	template <class>
	static auto test(...) ->
		std::conditional_t<
			traits::is_basic_type_v<T>,
			std::bool_constant<std::is_same_v<T, OperatorType>>,
			std::false_type
		>;
	using val = decltype(test<T>(nullptr));
};

template <class T, class OperatorType>
using has_type_operator_t = has_type_operator<T, OperatorType>::val;
template <class T, class OperatorType>
__LL_VAR_INLINE__ constexpr ll_bool_t has_type_operator_v = has_type_operator_t<T, OperatorType>::value;


#define __LL_TEMPLATE_HAS_FUNCTION_BASE__(name, function, basic_value) \
	template<class T> \
	struct has_##name## { \
		template <class U> \
		static auto test(U* p) -> decltype(##function##, std::true_type{}); \
		template <class U> \
		static auto test(const U* p) -> decltype(##function##, std::true_type{}); \
		template <class> \
		static auto test(...) -> \
			std::conditional_t< \
				traits::is_basic_type_v<T>, \
				std::bool_constant<basic_value>, \
				std::false_type \
			>; \
		using val = decltype(test<T>(nullptr)); \
	}; \
template <class T> \
using has_##name##_t = has_##name##<T>::val; \
template <class T> \
__LL_VAR_INLINE__ constexpr ll_bool_t has_##name##_v = has_##name##_t<T>::value


#define __LL_TEMPLATE_HAS_FUNCTION__(name, function) __LL_TEMPLATE_HAS_FUNCTION_BASE__(name, function, LL_FALSE)
#define __TEMPLATE_HAS_SIMPLE_FUNCTION__(function) __LL_TEMPLATE_HAS_FUNCTION__(function, p->##function())

//__LL_TEMPLATE_HAS_FUNCTION_BASE__(copy_operator, p->operator=(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(move_operator, p->operator=(std::move(*p)), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(three_compare_operator, p->operator<=>(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(equal_operator, p->operator==(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(no_equal_operator, p->operator!=(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(greater_operator, p->operator>(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(lower_operator, p->operator<(*p), LL_TRUE);

__LL_TEMPLATE_HAS_FUNCTION__(swap, p->swap(*p));
__LL_TEMPLATE_HAS_FUNCTION__(swap_s, p->swap_s(*p));
__TEMPLATE_HAS_SIMPLE_FUNCTION__(clear);

#pragma endregion
#pragma region OperatorTypeChecker
template<class ObjectType, class TypeCall>
struct operator_type_call_checker {
	static auto test() {
		if constexpr (std::is_pointer_v<ObjectType>) {
			using __noptr = std::remove_pointer_t<ObjectType>;

			if constexpr (std::is_pointer_v<__noptr>)
				return std::true_type{};
			else if constexpr (traits::has_type_operator_v<__noptr, TypeCall>)
				return std::true_type{};
			else if constexpr (traits::is_basic_type_v<__noptr>)
				return std::true_type{};
			else return std::false_type{};
		}
		else if constexpr (traits::has_type_operator_v<ObjectType, TypeCall>)
			return std::true_type{};
		else if constexpr (traits::is_basic_type_v<ObjectType>)
			return std::true_type{};
		else return std::false_type{};
	}
	using val = decltype(test());
};
template<class ObjectType, class TypeCall>
using operator_type_call_checker_t = operator_type_call_checker<ObjectType, TypeCall>::val;
template<class ObjectType, class TypeCall>
__LL_VAR_INLINE__ constexpr ll_bool_t operator_type_call_checker_v = operator_type_call_checker_t<ObjectType, TypeCall>::value;

#pragma endregion
#pragma region SwapChecker
template<class T>
struct is_nothrow_swappeable {
	static auto test() {
		if constexpr (std::is_pointer_v<T> || traits::is_basic_type_v<T>)
			return std::true_type{};
		else if constexpr (std::is_move_constructible_v<T> && std::is_move_assignable_v<T>) {
			if constexpr (std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>)
				return std::true_type{};
			else return std::false_type{};
		}
		else return std::false_type{};
	}
	using val = decltype(test());
};
template<class T>
using is_nothrow_swappeable_t = is_nothrow_swappeable<T>::val;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_nothrow_swappeable_v = is_nothrow_swappeable_t<T>::value;

#pragma endregion
#pragma region CopyChecker
template<class T>
struct is_nothrow_copyable {
	static auto test() {
		if constexpr (std::is_pointer_v<T>) {
			using __noptr = std::remove_pointer_t<T>;

			if constexpr (std::is_pointer_v<__noptr>)
				return std::false_type{};
			else if constexpr (std::is_copy_assignable_v<__noptr> && std::is_nothrow_copy_assignable_v<__noptr>)
				return std::true_type{};
			else if constexpr (traits::is_basic_type_v<__noptr>)
				return std::true_type{};
			else return std::false_type{};
		}
		else if constexpr (std::is_copy_assignable_v<T> && std::is_nothrow_copy_assignable_v<T>)
			return std::true_type{};
		else if constexpr (traits::is_basic_type_v<T>)
			return std::true_type{};
		else return std::false_type{};
	}
	using val = decltype(test());
};
template<class T>
using is_nothrow_copyable_t = is_nothrow_copyable<T>::val;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_nothrow_copyable_v = is_nothrow_copyable_t<T>::value;

#pragma endregion

template<class T, class U>
using is_same_const_t =
	std::conditional_t<
		(std::is_pointer_v<T> || std::is_pointer_v<U>) && !(std::is_pointer_v<T> && std::is_pointer_v<U>),
		std::false_type,
		std::conditional_t<
			std::is_same_v<
				std::remove_const_t<std::remove_pointer_t<T>>,
				std::remove_const_t<std::remove_pointer_t<U>>
			>,
			std::true_type,
			std::false_type
		>
	>;

template<class T, class U>
__LL_VAR_INLINE__ constexpr ll_bool_t is_same_const_v = is_same_const_t<T, U>::value;



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




#pragma endregion
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

#pragma endregion
#pragma region Functions
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

#pragma endregion

} // namespace traits
} // namespace llcpp

#endif // LLANYLIB_TRAITS_HPP_
