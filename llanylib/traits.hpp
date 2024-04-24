//////////////////////////////////////////////
//	traits.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITS_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITS_MAYOR_ != 5 || LLANYLIB_TRAITS_MINOR_ < 0
		#error "traits.hpp version error!"
	#endif // LLANYLIB_TRAITS_MAYOR_ || LLANYLIB_TRAITS_MINOR_

#else !defined(LLANYLIB_TRAITS_HPP_)
#define LLANYLIB_TRAITS_HPP_
#define LLANYLIB_TRAITS_MAYOR_ 5
#define LLANYLIB_TRAITS_MINOR_ 0

#define LL_TRAITS_TEST

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
__LL_VAR_INLINE__ constexpr ll_bool_t is_basic_bigger_type_v = std::_Is_any_of_v<std::remove_const_t<T>, i128, i256, ui128, ui256>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_floating_type_v = std::_Is_any_of_v<std::remove_const_t<T>, f32, f64>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_floating_bigger_type_v = std::_Is_any_of_v<std::remove_const_t<T>, f128>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_char_type_v = std::_Is_any_of_v<std::remove_const_t<T>, ll_char_t, ll_uchar_t, ll_wchar_t>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_strpair_type_v = std::_Is_any_of_v<std::remove_const_t<T>, StrPair, uStrPair, wStrPair>;

// Returns a type with reference if object is not basic type
// Is only used when type parameter will be const
template<class T>
using get_object_reference_t = std::conditional_t<traits::is_basic_type_v<T>, T, std::add_lvalue_reference_t<T>>;
template<class T>
using get_const_object_reference_t = std::conditional_t<traits::is_basic_type_v<T>, const T, const std::add_lvalue_reference_t<T>>;

template<class T>
struct type_container {
	using value = T;
};

template<class T>
struct type_conversor {
	struct to_raw {
		static constexpr auto test() {
			if constexpr (std::is_reference_v<T>)
				return type_conversor<std::remove_reference_t<T>>::to_raw::test();
			else if constexpr (std::is_pointer_v<T>)
				return type_conversor<std::remove_pointer_t<T>>::to_raw::test();
			else if constexpr (std::is_const_v<T>)
				return type_conversor<std::remove_const_t<T>>::to_raw::test();
			else return traits::type_container<T>{};
		}
		using value = decltype(test())::value;
	};
	struct to_const {
		static constexpr auto test() {
			if constexpr (std::is_reference_v<T>) {
				using __type = decltype(type_conversor<std::remove_reference_t<T>>::to_const::test())::value;
				if constexpr (std::is_lvalue_reference_v<T>)
					return traits::type_container<std::add_lvalue_reference_t<__type>>{};
				else if constexpr (std::is_rvalue_reference_v<T>)
					return traits::type_container<std::add_rvalue_reference_t<__type>>{};
			}
			else if constexpr (std::is_const_v<T>) {
				using __type = decltype(type_conversor<std::remove_const_t<T>>::to_const::test())::value;
				return traits::type_container<const __type>{};
			}
			else if constexpr (std::is_pointer_v<T>) {
				using __type = decltype(type_conversor<std::remove_pointer_t<T>>::to_const::test())::value;
				return traits::type_container<std::add_pointer_t<__type>>{};
			}
			else return traits::type_container<const T>{};
		}
		using value = decltype(test())::value;
	};
	template<ll_bool_t ALL>
	struct to_reference {
		static constexpr auto test() {
			using __raw_type = type_conversor<T>::to_raw_t;

			if constexpr (std::is_pointer_v<T> || !traits::is_basic_type_v<__raw_type> || ALL)
				return traits::type_container<std::add_lvalue_reference_t<T>>{};
			else return traits::type_container<T>{};
		}
		using value = decltype(test())::value;
	};
	template<ll_bool_t ALL>
	struct to_const_reference {
		static constexpr auto test() {
			using __raw_type = type_conversor<T>::to_raw_t;
			using __const_type = type_conversor<T>::to_const_t;
			if constexpr (std::is_pointer_v<__raw_type> || !traits::is_basic_type_v<__raw_type> || ALL)
				return traits::type_container<std::add_lvalue_reference_t<__const_type>>{};
			else return traits::type_container<__const_type>{};
		}
		using value = decltype(test())::value;
	};
	struct to_movement {
		static constexpr auto test() {
			if constexpr (std::is_reference_v<T>) {
				using __noreference = std::remove_reference_t<T>;
				return traits::type_container<__noreference&&>{};
			}
			else return traits::type_container<T&&>{};
		}
		using value = decltype(test())::value;
	};
	struct get_ptr_remove_reference {
		static constexpr auto test() {
			if constexpr (std::is_reference_v<T>) {
				using __noreference = std::remove_reference_t<T>;
				return traits::type_container<__noreference*>{};
			}
			else return traits::type_container<T*>{};
		}
		using value = decltype(test())::value;
	};
	struct get_const_ptr_remove_reference {
		static constexpr auto test() {
			return traits::type_container<type_conversor<get_ptr_remove_reference_t>::to_const_t>{};
		}
		using value = decltype(test())::value;
	};
	template<ll_bool_t promote>
	struct type_promotion {
		template<ll_bool_t promote>
		struct __type_promotion { using value = T; };

		template<> struct __type_promotion<LL_TRUE> {
			template<class U> struct promote_type { using value = U; };
			template<> struct promote_type<i8> { using value = i16; };
			template<> struct promote_type<i16> { using value = i32; };
			template<> struct promote_type<i32> { using value = i64; };
			template<> struct promote_type<i64> { using value = i128; };
			template<> struct promote_type<i128> { using value = i256; };
			template<> struct promote_type<ui8> { using value = ui16; };
			template<> struct promote_type<ui16> { using value = ui32; };
			template<> struct promote_type<ui32> { using value = ui64; };
			template<> struct promote_type<ui64> { using value = ui128; };
			template<> struct promote_type<ui128> { using value = ui256; };
			template<> struct promote_type<f32> { using value = f64; };
			template<> struct promote_type<f64> { using value = f128; };
			using value = promote_type<T>::value;
		};
		template<> struct __type_promotion<LL_FALSE> {
			template<class U> struct promote_type { using value = U; };
			template<> struct promote_type<i16> { using value = i8; };
			template<> struct promote_type<i32> { using value = i16; };
			template<> struct promote_type<i64> { using value = i32; };
			template<> struct promote_type<i128> { using value = i64; };
			template<> struct promote_type<i256> { using value = i128; };
			template<> struct promote_type<ui16> { using value = ui8; };
			template<> struct promote_type<ui32> { using value = ui16; };
			template<> struct promote_type<ui64> { using value = ui32; };
			template<> struct promote_type<ui128> { using value = ui64; };
			template<> struct promote_type<ui256> { using value = ui128; };
			template<> struct promote_type<f64> { using value = f32; };
			template<> struct promote_type<f128> { using value = f64; };
			using value = promote_type<T>::value;
		};

		static constexpr ll_bool_t isPromoted = promote;
		using value = __type_promotion<promote>::value;
	};

	// Gets raw type, no pointers, no references (rvalue || lvalue)
	using to_raw_t = to_raw::value;
	// Removes all attributes, adds const, and restores all attributes
	using to_const_t = to_const::value;
	// Adds a lvalue reference if type is not a basic type of a basic bigger type
	// If all is true, all types would get a reference
	template<ll_bool_t ALL = LL_FALSE>
	using to_reference_t = to_reference<ALL>::value;
	// Adds a const lvalue reference if type is not a basic type of a basic bigger type
	// If all is true, all types would get a const reference
	template<ll_bool_t ALL = LL_FALSE>
	using to_const_reference_t = to_const_reference<ALL>::value;
	// Adds a rvalue reference
	using to_movement_t = to_movement::value;
	// Get a ptr type, and removes reference if it has
	using get_ptr_remove_reference_t = get_ptr_remove_reference::value;
	// Get a const ptr type, and removes reference if it has
	//using _t = get_cptr_remove_reference;
	//using get_const_ptr_remove_reference_t = get_const_ptr_remove_reference::value;
	// Promote a type to a bigger or smaller type
	template<ll_bool_t promote>
	using promote_t = type_promotion<promote>::value;
};

#pragma region Other
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
#pragma endregion
#pragma region FunctionCheckers
#pragma region DefinesAndStructs
template <class T, class OperatorType>
struct has_type_operator {
    template <class U>
	static constexpr auto test(U* p) -> decltype(p->operator OperatorType(), std::true_type{});
    template <class U>
	static constexpr auto test(const U* p) -> decltype(p->operator OperatorType(), std::true_type{});
	template <class>
	static constexpr auto test(...) ->
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
		static constexpr auto test(U* p) -> decltype(##function##, std::true_type{}); \
		template <class U> \
		static constexpr auto test(const U* p) -> decltype(##function##, std::true_type{}); \
		template <class> \
		static constexpr auto test(...) -> \
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
	static constexpr auto test() {
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
	static constexpr auto test() {
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
	static constexpr auto test() {
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

//template<class T, class U>
//using is_same_const_t =
//	std::conditional_t<
//		(std::is_pointer_v<T> || std::is_pointer_v<U>) && !(std::is_pointer_v<T> && std::is_pointer_v<U>),
//		std::false_type,
//		std::conditional_t<
//			std::is_same_v<
//				std::remove_const_t<std::remove_pointer_t<T>>,
//				std::remove_const_t<std::remove_pointer_t<U>>
//			>,
//			std::true_type,
//			std::false_type
//		>
//	>;
//
//template<class T, class U>
//__LL_VAR_INLINE__ constexpr ll_bool_t is_same_const_v = is_same_const_t<T, U>::value;

//template<class T>
//__LL_VAR_INLINE__ constexpr ll_bool_t is_nothrow_constructible_v =
//	std::is_pointer_v<T> ||
//	traits::is_basic_type_v<T> ||
//	noexcept(T());
//template<class T>
//__LL_VAR_INLINE__ constexpr ll_bool_t is_nothrow_destructible_v =
//	std::is_pointer_v<T> ||
//	traits::is_basic_type_v<T> ||
//	noexcept(std::declval<T>().~T());

#pragma endregion
#pragma region Functions
template<class ReturnType, class ObjectType, ReturnType NULL_VAL>
static constexpr ReturnType operatorTypeCall(const ObjectType& object) __LL_EXCEPT__ {
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
		else return NULL_VAL;
	}
	else if constexpr (traits::has_type_operator_v<ObjectType, ReturnType>) {
		if constexpr (traits::is_basic_type_v<ObjectType>) return object;
		//else return object.operator ReturnType();
		else return object;
	}
	else if constexpr (traits::is_basic_type_v<ObjectType>)
		return static_cast<ReturnType>(object);
	else return NULL_VAL;
}

#pragma endregion

} // namespace traits
} // namespace llcpp

#endif // LLANYLIB_TRAITS_HPP_
