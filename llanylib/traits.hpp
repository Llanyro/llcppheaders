//////////////////////////////////////////////
//	traits.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITS_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITS_MAYOR_ != 9 || LLANYLIB_TRAITS_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "traits.hpp version error!"
		#else
			#error "traits.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_TRAITS_MAYOR_ || LLANYLIB_TRAITS_MINOR_

#else !defined(LLANYLIB_TRAITS_HPP_)
#define LLANYLIB_TRAITS_HPP_
#define LLANYLIB_TRAITS_MAYOR_ 9
#define LLANYLIB_TRAITS_MINOR_ 0

#define LL_TRAITS_TEST

#include "types.hpp"

#if defined(LL_TRAITS_TEST)
	#include "examples/traits_test_class.hpp"
#endif

#include <type_traits>

namespace llcpp {
namespace meta {
namespace traits {

#pragma region TraitsTypesAndCheckers
template<class _T>
struct type_container {
	using _MyType	= type_container;
	using T			= _T;
};
template<class _T, class _U>
struct double_type_container {
	using _MyType	= double_type_container;
	using T			= _T;
	using U			= _U;
};

// SFINAE checker for signatures
template<class _U, class _Signature, _Signature> struct SignatureChecker {};

// Standard checker for types in this lib
template<class _T, ll_bool_t _IGNORE_POINTER = llcpp::FALSE, ll_bool_t _IGNORE_ARRAY = llcpp::FALSE, ll_bool_t _IGNORE_VOLATILE = llcpp::FALSE>
struct type_checker {
	using _MyType	= type_checker;
	using T			= _T;

	static constexpr ll_bool_t IGNORE_POINTER	= _IGNORE_POINTER;
	static constexpr ll_bool_t IGNORE_ARRAY		= _IGNORE_ARRAY;
	static constexpr ll_bool_t IGNORE_VOLATILE	= _IGNORE_VOLATILE;

	static constexpr ll_bool_t POINTER = (IGNORE_POINTER || !std::is_pointer_v<T>);
	static constexpr ll_bool_t ARRAY = (IGNORE_ARRAY || !std::is_array_v<T>);
	static constexpr ll_bool_t VOLATILE = (IGNORE_VOLATILE || !std::is_volatile_v<T>);

	static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
	static_assert(!std::is_const_v<T>, "Const type is forbidden!");

	static_assert(POINTER, "Pointer type is forbidden!");
	static_assert(ARRAY, "Array type is forbidden!");
	static_assert(VOLATILE, "Volatile type is forbidden!");

	static constexpr ll_bool_t is_valid_v =
		!std::is_const_v<T> &&
		!std::is_reference_v<T> &&
		ARRAY &&
		VOLATILE &&
		POINTER;
};

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_type_checker_v = 
	traits::type_checker<T>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_type_checker_ignore_pointer_v = 
	traits::type_checker<T, llcpp::TRUE, llcpp::FALSE, llcpp::FALSE>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_type_checker_ignore_array_v = 
	traits::type_checker<T, llcpp::FALSE, llcpp::TRUE, llcpp::FALSE>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_type_checker_ignore_pa_v = 
	traits::type_checker<T, llcpp::TRUE, llcpp::TRUE, llcpp::FALSE>::is_valid_v;

// Standard checker for classes and objects
// Checks contruction / destruction and other operations needed
template<class _T>
struct constructor_checker {
	using _MyType	= constructor_checker;
	using T			= _T;

	static_assert(std::is_nothrow_constructible_v<T>, "T needs a noexcept constructor!");
	static_assert(std::is_nothrow_destructible_v<T>, "T needs a noexcept destructor!");
	static_assert(std::is_copy_constructible_v<T>, "T needs a noexcept copy constructor!");
	static_assert(std::is_copy_assignable_v<T>, "T needs a noexcept copy asignable!");
	static_assert(std::is_move_constructible_v<T>, "T needs a noexcept move constructor!");
	static_assert(std::is_move_assignable_v<T>, "T needs a noexcept move asignable!");

	static constexpr ll_bool_t is_valid_v =
		std::is_nothrow_constructible_v<T>
		&& std::is_nothrow_destructible_v<T>
		&& std::is_copy_constructible_v<T>
		&& std::is_copy_assignable_v<T>
		&& std::is_move_constructible_v<T>
		&& std::is_move_assignable_v<T>;
};

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_v = 
	traits::constructor_checker<T>::is_valid_v;

// Standard checker for classes in this lib
template<class _T>
struct class_checker : public traits::constructor_checker<_T> {
	using _MyType				= class_checker;
	using T						= _T;
	using constructor_checker	= traits::constructor_checker<T>;

	static_assert(std::is_class_v<T>, "T needs to be a class!");

	static constexpr ll_bool_t is_valid_v =  constructor_checker::is_valid_v && std::is_class_v<T>;
};

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_class_checker_v = traits::class_checker<T>::is_valid_v;

// SFINAE to check if object has a function
// Follow any class that this inherites to check how to do a new checker 
template<class _Base>
struct _has_common : public _Base {
	using _MyType		= _has_common;
	using Base			= _Base;
	using ClassToCheck	= typename Base::ClassToCheck;

	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<ClassToCheck>,
		"class_checker<ClassToCheck> detected an invalid class type!");

	using type = decltype(Base::template test<ClassToCheck>(LL_NULLPTR));
};

#pragma endregion
#pragma region BasicExpresions
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_empty_object_v = std::_Is_any_of_v<std::remove_cv_t<T>, llcpp::Emptyclass, llcpp::EmptyStruct>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_basic_type_v = std::is_arithmetic_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_basic_bigger_type_v = std::_Is_any_of_v<std::remove_cv_t<T>, i128, i256, ui128, ui256>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_floating_type_v = std::is_floating_point_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_floating_bigger_type_v = std::_Is_any_of_v<std::remove_cv_t<T>, f128>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_char_type_v = std::_Is_any_of_v<std::remove_cv_t<T>, ll_char_t, ll_wchar_t>;

template<class>
__LL_VAR_INLINE__ constexpr len_t array_size = ZERO_UI64;
template<class T, len_t N>
__LL_VAR_INLINE__ constexpr len_t array_size<T[N]> = N;

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_of_a_basic_type_v = (traits::is_basic_type_v<Args> || ...);
template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_all_of_a_basic_type_v = (traits::is_basic_type_v<Args> && ...);

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_of_a_floating_type_v = (traits::is_floating_type_v<Args> || ...);
template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_all_of_a_floating_type_v = (traits::is_floating_type_v<Args> && ...);

#pragma endregion
#pragma region IntegralConstant
template<class _T, class _U, _T VALUE>
struct integral_constant_container {
	using _MyType			= integral_constant_container;
	using T					= _T;
	using U					= _U;
	using integral_constant = std::integral_constant<T, VALUE>;
	using container			= traits::type_container<U>;
};

template<ll_bool_t VALUE, class U>
using bool_constant_container = traits::integral_constant_container<ll_bool_t, U, VALUE>;

template<class U>
using true_type  = traits::bool_constant_container<llcpp::TRUE, U>;
template<class U>
using false_type = traits::bool_constant_container<llcpp::FALSE, U>;

#pragma endregion
#pragma region Types
template<class T>
using input = std::conditional_t<traits::is_basic_type_v<T> || std::is_pointer_v<T>, T, T&>;
template<class T>
using cinput = std::conditional_t<traits::is_basic_type_v<T> || std::is_pointer_v<T>, const T, const T&>;

template<class _T, ll_bool_t _promote>
struct type_promotion {
	using _MyType	= type_promotion;
	using T			= _T;

	static constexpr ll_bool_t promote = _promote;

	static_assert(traits::is_valid_type_checker_v<T>, "type_checker<T> detected an invalid type!");

	template<ll_bool_t promote> struct __type_promotion { using type = T; };
	template<> struct __type_promotion<llcpp::TRUE> {
		template<class U> struct promote_type { using type = U; };
		template<> struct promote_type<i8> { using type = i16; };
		template<> struct promote_type<i16> { using type = i32; };
		template<> struct promote_type<i32> { using type = i64; };
		template<> struct promote_type<i64> { using type = i128; };
		template<> struct promote_type<i128> { using type = i256; };
		template<> struct promote_type<ui8> { using type = ui16; };
		template<> struct promote_type<ui16> { using type = ui32; };
		template<> struct promote_type<ui32> { using type = ui64; };
		template<> struct promote_type<ui64> { using type = ui128; };
		template<> struct promote_type<ui128> { using type = ui256; };
		template<> struct promote_type<f32> { using type = f64; };
		template<> struct promote_type<f64> { using type = f128; };
		using type = promote_type<T>::type;
	};
	template<> struct __type_promotion<llcpp::FALSE> {
		template<class U> struct promote_type { using type = U; };
		template<> struct promote_type<i16> { using type = i8; };
		template<> struct promote_type<i32> { using type = i16; };
		template<> struct promote_type<i64> { using type = i32; };
		template<> struct promote_type<i128> { using type = i64; };
		template<> struct promote_type<i256> { using type = i128; };
		template<> struct promote_type<ui16> { using type = ui8; };
		template<> struct promote_type<ui32> { using type = ui16; };
		template<> struct promote_type<ui64> { using type = ui32; };
		template<> struct promote_type<ui128> { using type = ui64; };
		template<> struct promote_type<ui256> { using type = ui128; };
		template<> struct promote_type<f64> { using type = f32; };
		template<> struct promote_type<f128> { using type = f64; };
		using type = promote_type<T>::type;
	};

	using type = __type_promotion<promote>::type;
};

#pragma endregion
#pragma region MyRegion
//template<class _Checker, class _VoidType = void>
//struct check_valid_types {
//	using Checker	= _Checker;
//	using VoidType	= _VoidType;
//
//	static_assert(traits::is_valid_type_checker_v<Checker>,
//		"type_checker<Checker> detected an invalid type!");
//	static_assert(traits::is_valid_class_checker_v<Checker>,
//		"class_checker<Checker> detected an invalid class type!");
//
//	template<class T>
//	static constexpr auto get_first() noexcept ->
//		std::conditional_t<Checker::is_valid_v<T>, T, VoidType>;
//	template<class T, class... Args>
//	static constexpr auto get_first() noexcept ->
//		std::conditional_t<Checker::is_valid_v<T>, T, decltype(get_first<Args...>())>;
//	template<class... Args>
//	using type = decltype(get_first<Args...>());
//};

#define __LL_GENERIC_CHECKER__(name, checker) \
	struct is_valid_##name##_checker { \
		template<class T> \
		static constexpr ll_bool_t is_valid_v = ##checker##<T>; \
	}

#pragma endregion
#pragma region CharConditional
template<class _T, class _TypeChar, class _TypeWChar, class _ExtraType = void>
struct get_by_char_type {
	using _MyType	= get_by_char_type;
	using T			= _T;
	using TypeChar	= _TypeChar;
	using TypeWChar = _TypeWChar;
	using ExtraType = _ExtraType;

	static_assert(traits::is_valid_type_checker_v<T>,
		"type_checker<U> detected an invalid type!");

	template <class U> struct __struct__ { using _val = ExtraType; };
	template<> struct __struct__<ll_char_t> { using _val = TypeChar; };
	template<> struct __struct__<ll_wchar_t> { using _val = TypeWChar; };

	using type = __struct__<T>::_val;
};

template<class T, class TypeChar, class TypeWChar, class ExtraType = void>
using get_by_char_type_t = traits::get_by_char_type<T, TypeChar, TypeWChar, ExtraType>::type;

#pragma endregion
#pragma region FunctionalReflector
template<class _ClassToCheck, class _OperatorType, class _Signature>
struct has_type_operator {
	using _MyType		= has_type_operator;
	using ClassToCheck	= _ClassToCheck;
	using OperatorType	= _OperatorType;
	using Signature		= _Signature;
	template<Signature SIG>
	using checker		= traits::SignatureChecker<ClassToCheck, Signature, SIG>;

	template<ll_bool_t, ll_bool_t> struct SFINAE { using type = std::false_type; };
	template<> struct SFINAE<llcpp::TRUE, llcpp::TRUE> { using type = std::true_type; };

	using type_default_result =
		typename SFINAE<traits::is_basic_type_v<ClassToCheck>, std::is_same_v<ClassToCheck, OperatorType>>::type;

	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");

	template<class _U>
	static constexpr auto test(checker<&_U::operator OperatorType>*) noexcept	-> std::true_type;
	template<class _U> static constexpr auto test(...) noexcept					-> type_default_result;

	using type = decltype(_MyType::test<ClassToCheck>(LL_NULLPTR));
};
template<class ClassToCheck, class OperatorType, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_type_operator_v =
	traits::has_type_operator<ClassToCheck, OperatorType, Signature>::type::value;
template<class ClassToCheck, class OperatorType, class __ = std::conditional_t<std::is_class_v<ClassToCheck>, ClassToCheck, llcpp::Emptyclass>>
__LL_VAR_INLINE__ constexpr ll_bool_t has_simple_type_operator_v =
	traits::has_type_operator_v<ClassToCheck, OperatorType, OperatorType(__::*)() const noexcept>;

#pragma endregion
#pragma region SwapChecker
template<class _T>
struct is_nothrow_swappeable {
	using _MyType	= is_nothrow_swappeable;
	using T			= _T;

	static_assert(traits::is_valid_type_checker_v<T>,
		"type_checker<T> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<T>,
		"class_checker<T> detected an invalid class type!");

	static constexpr auto test() noexcept {
		if constexpr (std::is_pointer_v<T> || traits::is_basic_type_v<T>)
			return std::true_type{};
		else if constexpr (std::is_array_v<T>)
			return is_nothrow_swappeable<std::remove_extent_t<T>>::test();
		// Already includes basic types
		else if constexpr (std::is_move_constructible_v<T> && std::is_move_assignable_v<T>) {
			if constexpr (std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>)
				return std::true_type{};
			else return std::false_type{};
		}
		else return std::false_type{};
	}
	using type = decltype(test());
};
template<class T>
using is_nothrow_swappeable_t = is_nothrow_swappeable<T>::type;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_nothrow_swappeable_v = is_nothrow_swappeable_t<T>::value;

#pragma endregion
#pragma region CopyChecker
template<class _T>
struct is_nothrow_copyable {
	using _MyType	= is_nothrow_copyable;
	using T			= _T;

	static_assert(traits::is_valid_type_checker_v<T>,
		"type_checker<T> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<T>,
		"class_checker<T> detected an invalid class type!");

	static constexpr auto test() noexcept {
		if constexpr (std::is_pointer_v<T>) {
			using __noptr = std::remove_pointer_t<T>;
			if constexpr (std::is_pointer_v<__noptr>) return std::false_type{};
			else return is_nothrow_copyable<__noptr>::test();
		}
		else if constexpr (std::is_array_v<T>) {
			return is_nothrow_copyable<std::remove_extent_t<T>>::test();
		}
		// Already includes basic types
		else if constexpr (std::is_copy_assignable_v<T> && std::is_nothrow_copy_assignable_v<T>)
			return std::true_type{};
		else return std::false_type{};
	}
	using type = decltype(test());
};
template<class T>
using is_nothrow_copyable_t = is_nothrow_copyable<T>::type;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_nothrow_copyable_v = is_nothrow_copyable_t<T>::value;

#pragma endregion
#pragma region ParameterPacks
template <class... Args>
struct parameter_pack_operations {
	template<class T, class... uArgs>
	struct FirstType {
		using type = T;
		using next = FirstType<uArgs...>;
	};
	template<class T>
	struct FirstType<T> {
		using type = T;
		using next = EmptyStruct;
	};

	using pack_first = typename FirstType<Args...>;
	using get_first_type = typename FirstType<Args...>::type;
	static constexpr len_t size = sizeof...(Args);
	static constexpr ll_bool_t empty = (size == ZERO_UI64);
	static constexpr ll_bool_t has_a_pointer = (std::is_pointer_v<Args> || ...);
	static constexpr ll_bool_t has_a_array = (std::is_array_v<Args> || ...);
};
template <class T>
struct parameter_pack_operations<T> {
	using FirstType = parameter_pack_operations<int, int>::FirstType<T>;

	using pack_first = typename FirstType;
	using get_first_type = typename pack_first::type;
	static constexpr len_t size = 1ull;
	static constexpr ll_bool_t empty = llcpp::FALSE;
	static constexpr ll_bool_t has_a_pointer = std::is_pointer_v<T>;
	static constexpr ll_bool_t has_a_array = std::is_array_v<T>;
};
template <>
struct parameter_pack_operations<> {
	using FirstType = parameter_pack_operations<int, int>::FirstType<void>;

	using pack_first = FirstType;
	using get_first_type = pack_first::type;
	static constexpr len_t size = ZERO_UI64;
	static constexpr ll_bool_t empty = llcpp::TRUE;
	static constexpr ll_bool_t has_a_pointer = llcpp::FALSE;
	static constexpr ll_bool_t has_a_array = llcpp::FALSE;
};

#pragma endregion

namespace common {

#define __LL_HAS_CUSTOM_FUNCTION_NAMED__(name, functionname) \
	template<class _ClassToCheck, class _Signature> \
	struct has_##name##_function { \
		using _MyType		= has_##name##_function; \
		using ClassToCheck	= _ClassToCheck; \
		using Signature		= _Signature; \
		template<Signature SIG> \
		using checker		= traits::SignatureChecker<ClassToCheck, Signature, SIG>; \
		template<class _U> \
		static constexpr auto test(checker<&_U::##functionname##>*) noexcept	-> std::true_type; \
		template<class _U> static constexpr auto test(...) noexcept				-> std::false_type; \
	}; \
	template<class ClassToCheck, class Signature> \
	using has_##name##_function_t = \
		traits::_has_common<traits::common::has_##name##_function<ClassToCheck, Signature>>; \
	template<class ClassToCheck, class Signature> \
	__LL_VAR_INLINE__ constexpr ll_bool_t has_##name##_function_v = \
		traits::common::has_##name##_function_t<ClassToCheck, Signature>::type::value;

#define __LL_HAS_CUSTOM_FUNCTION__(name) __LL_HAS_CUSTOM_FUNCTION_NAMED__(name, name)

//////////////////////////////////////////////////////////////////////
// Do not change - Autogenerated with __LL_HAS_CUSTOM_FUNCTION__	//
// 	macros and visual studio										//
//////////////////////////////////////////////////////////////////////
//__LL_HAS_CUSTOM_FUNCTION__(hash);
//__LL_HAS_CUSTOM_FUNCTION__(clear);
//__LL_HAS_CUSTOM_FUNCTION__(swap);
//__LL_HAS_CUSTOM_FUNCTION__(copy);
//__LL_HAS_CUSTOM_FUNCTION__(move);
//__LL_HAS_CUSTOM_FUNCTION__(compare);
//__LL_HAS_CUSTOM_FUNCTION__(compareBool);
//__LL_HAS_CUSTOM_FUNCTION__(predestruction);
//__LL_HAS_CUSTOM_FUNCTION__(nodeChecker);
//__LL_HAS_CUSTOM_FUNCTION__(compareNode);
//__LL_HAS_CUSTOM_FUNCTION_NAMED__(operator_eq, operator==);
//__LL_HAS_CUSTOM_FUNCTION_NAMED__(operator_no_eq, operator!=);
//__LL_HAS_CUSTOM_FUNCTION_NAMED__(sgtrong_ordening, operator<=>);
//__LL_HAS_CUSTOM_FUNCTION__(compare_eq);
//__LL_HAS_CUSTOM_FUNCTION__(compare_no_eq);
//__LL_HAS_CUSTOM_FUNCTION__(die);


template<class _ClassToCheck, class _Signature> struct has_hash_function {
    using _MyType = has_hash_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::hash>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_hash_function_t = traits::_has_common<traits::common::has_hash_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_hash_function_v = traits::common::has_hash_function_t<ClassToCheck, Signature>::type::value;
template<class _ClassToCheck, class _Signature> struct has_clear_function {
	using _MyType = has_clear_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::clear>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_clear_function_t = traits::_has_common<traits::common::has_clear_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_clear_function_v = traits::common::has_clear_function_t<ClassToCheck, Signature>::type::value;
template<class _ClassToCheck, class _Signature> struct has_swap_function {
	using _MyType = has_swap_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::swap>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_swap_function_t = traits::_has_common<traits::common::has_swap_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_swap_function_v = traits::common::has_swap_function_t<ClassToCheck, Signature>::type::value;
template<class _ClassToCheck, class _Signature> struct has_copy_function {
	using _MyType = has_copy_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::copy>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_copy_function_t = traits::_has_common<traits::common::has_copy_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_copy_function_v = traits::common::has_copy_function_t<ClassToCheck, Signature>::type::value;
template<class _ClassToCheck, class _Signature> struct has_move_function {
	using _MyType = has_move_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::move>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_move_function_t = traits::_has_common<traits::common::has_move_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_move_function_v = traits::common::has_move_function_t<ClassToCheck, Signature>::type::value;
template<class _ClassToCheck, class _Signature> struct has_compare_function {
	using _MyType = has_compare_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::compare>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_compare_function_t = traits::_has_common<traits::common::has_compare_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_compare_function_v = traits::common::has_compare_function_t<ClassToCheck, Signature>::type::value;
template<class _ClassToCheck, class _Signature> struct has_compareBool_function {
	using _MyType = has_compareBool_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::compareBool>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_compareBool_function_t = traits::_has_common<traits::common::has_compareBool_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_compareBool_function_v = traits::common::has_compareBool_function_t<ClassToCheck, Signature>::type::value;
template<class _ClassToCheck, class _Signature> struct has_predestruction_function {
	using _MyType = has_predestruction_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::predestruction>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_predestruction_function_t = traits::_has_common<traits::common::has_predestruction_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_predestruction_function_v = traits::common::has_predestruction_function_t<ClassToCheck, Signature>::type::value;;
template<class _ClassToCheck, class _Signature> struct has_nodeChecker_function {
	using _MyType = has_nodeChecker_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::nodeChecker>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_nodeChecker_function_t = traits::_has_common<traits::common::has_nodeChecker_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_nodeChecker_function_v = traits::common::has_nodeChecker_function_t<ClassToCheck, Signature>::type::value;;
template<class _ClassToCheck, class _Signature> struct has_compareNode_function {
	using _MyType = has_compareNode_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::compareNode>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_compareNode_function_t = traits::_has_common<traits::common::has_compareNode_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_compareNode_function_v = traits::common::has_compareNode_function_t<ClassToCheck, Signature>::type::value;;
template<class _ClassToCheck, class _Signature> struct has_operator_eq_function {
	using _MyType = has_operator_eq_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator==>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_operator_eq_function_t = traits::_has_common<traits::common::has_operator_eq_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_operator_eq_function_v = traits::common::has_operator_eq_function_t<ClassToCheck, Signature>::type::value;;
template<class _ClassToCheck, class _Signature> struct has_operator_no_eq_function {
	using _MyType = has_operator_no_eq_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator!=>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_operator_no_eq_function_t = traits::_has_common<traits::common::has_operator_no_eq_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_operator_no_eq_function_v = traits::common::has_operator_no_eq_function_t<ClassToCheck, Signature>::type::value;;
template<class _ClassToCheck, class _Signature> struct has_compare_eq_function {
	using _MyType = has_compare_eq_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::compare_eq>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_compare_eq_function_t = traits::_has_common<traits::common::has_compare_eq_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_compare_eq_function_v = traits::common::has_compare_eq_function_t<ClassToCheck, Signature>::type::value;;
template<class _ClassToCheck, class _Signature> struct has_compare_no_eq_function {
	using _MyType = has_compare_no_eq_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::compare_no_eq>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_compare_no_eq_function_t = traits::_has_common<traits::common::has_compare_no_eq_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_compare_no_eq_function_v = traits::common::has_compare_no_eq_function_t<ClassToCheck, Signature>::type::value;;
template<class _ClassToCheck, class _Signature> struct has_die_function {
	using _MyType = has_die_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::die>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_die_function_t = traits::_has_common<traits::common::has_die_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_die_function_v = traits::common::has_die_function_t<ClassToCheck, Signature>::type::value;;
template<class _ClassToCheck, class _Signature> struct has_sgtrong_ordening_function {
	using _MyType = has_sgtrong_ordening_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<Signature SIG> using checker = traits::SignatureChecker<ClassToCheck, Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator<=>>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_sgtrong_ordening_function_t = traits::_has_common<traits::common::has_sgtrong_ordening_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_sgtrong_ordening_function_v = traits::common::has_sgtrong_ordening_function_t<ClassToCheck, Signature>::type::value;;

template<class ClassToCheck>
__LL_VAR_INLINE__ constexpr ll_bool_t has_simple_clear_function_v =
	traits::common::has_clear_function_v<ClassToCheck, void(ClassToCheck::*)() noexcept>;

} // namespace common

  // Returns hash type by calling hash function
#pragma region HashTypeChecker
namespace hash {

template<class _ClassToCheck>
struct get_hash_function_type {
	using ClassToCheck	= _ClassToCheck;

	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<ClassToCheck>,
		"class_checker<ClassToCheck> detected an invalid class type!");

	template<class>
	static constexpr auto test(auto(ClassToCheck::* _)() noexcept) noexcept ->
		traits::double_type_container<std::true_type, std::invoke_result_t<decltype(_), ClassToCheck>>;
	template<class>
	static constexpr auto test(auto(ClassToCheck::* _)() const noexcept) noexcept ->
		traits::double_type_container<std::true_type, std::invoke_result_t<decltype(_), ClassToCheck>>;
	template<class>
	static constexpr auto test(...) noexcept ->
		traits::double_type_container<std::false_type, void>;

	using container = decltype(get_hash_function_type::test<ClassToCheck>(&ClassToCheck::hash));
	using type = container::U;
	static_assert(!std::is_same_v<type, void>, "T::hash() cannot return void!");
};

//template<class _ClassToCheck>
//struct get_hash_function_type<_ClassToCheck*> {
//	using ClassToCheck	= _ClassToCheck*;
//	using container		= traits::double_type_container<std::false_type, void>;
//	using type			= container::U;
//};

template<class ClassToCheck>
using get_hash_function_type_t = get_hash_function_type<ClassToCheck>::type;

//template<class _ClassToCheck, class HashType>
//struct get_hash_function {
//	using ClassToCheck = _ClassToCheck;
//	using container		= traits::double_type_container<std::true_type, void(ClassToCheck::*)() noexcept>;
//	using c_container	= traits::double_type_container<std::true_type, void(ClassToCheck::*)() const noexcept>;
//	using type			= container::U;
//	using ctype			= c_container::U;
//
//	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
//		"type_checker<ClassToCheck> detected an invalid type!");
//	static_assert(traits::is_valid_class_checker_v<ClassToCheck>,
//		"class_checker<ClassToCheck> detected an invalid class type!");
//};

} // namespace hash
#pragma endregion
#pragma region ThreeWayChecker
template<class _T, class _U>
struct get_three_way_comparasion_function_type {
	#pragma region Types
	public:
		// Class related
		using _MyType = get_three_way_comparasion_function_type;

		// Types
		using T = _T;
		using U = _U;

		// 
		using t_cinput = traits::cinput<T>;
		using u_cinput = traits::cinput<U>;

		// Type if basic type
		using no_function_type = std::conditional_t<
			!traits::is_all_of_a_basic_type_v<T, U>,
			llcpp::Emptyclass,
			std::conditional_t<
				traits::is_any_of_a_floating_type_v<T, U>,
				std::partial_ordering,
				std::strong_ordering
			>
		>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(traits::is_valid_type_checker_v<U>,
			"type_checker<U> detected an invalid type!");

	#pragma endregion
	#pragma region Functions
	public:
		template<class>
		static constexpr auto test(auto(T::* _)(u_cinput) noexcept) noexcept ->
			traits::double_type_container<
				std::true_type,
				std::invoke_result_t<decltype(_), T>
			>;
		template<class>
		static constexpr auto test(auto(T::* _)(u_cinput) noexcept) const noexcept ->
			traits::double_type_container<
				std::true_type,
				std::invoke_result_t<decltype(_), T>
			>;
		template<class>
		static constexpr auto test(...) noexcept ->
			traits::double_type_container<std::false_type, no_function_type>;

		using container = decltype(_MyType::test<T>(&T::operator<=>));
		using type = container::U;

	#pragma endregion
};

template<class T, class U>
using get_three_way_comparasion_function_type_t = get_three_way_comparasion_function_type<T, U>::type;

#pragma endregion
#pragma region Comparations
template<class _T, class _U = _T, class _Boolean = llcpp::Boolean>
struct is_comparable {
	#pragma region Types
	public:
		// Class related
		using _MyType				= is_comparable;

		// Types
		using T						= _T;
		using U						= _U;
		using Boolean				= _Boolean;
		using T_class				= std::conditional_t<std::is_class_v<T>, T, llcpp::Emptyclass>;
		using t_cinput				= traits::cinput<T>;
		using u_cinput				= traits::cinput<U>;
		
		// Signarures
		using T_Signature_bool		= ll_bool_t(T_class::*)(u_cinput) const noexcept;
		using T_Signature_ll_bool_t	= Boolean(T_class::*)(u_cinput) const noexcept;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t T_HAS_EQ_SIGNATURE_BOOL =
			traits::common::has_operator_eq_function_v<T, T_Signature_bool>;
		static constexpr ll_bool_t T_HAS_EQ_SIGNATURE_LL_BOOL_T =
			traits::common::has_operator_eq_function_v<T, T_Signature_ll_bool_t>;

		static constexpr ll_bool_t T_HAS_NEQ_SIGNATURE_BOOL =
			traits::common::has_operator_no_eq_function_v<T, T_Signature_bool>;
		static constexpr ll_bool_t T_HAS_NEQ_SIGNATURE_LL_BOOL_T =
			traits::common::has_operator_no_eq_function_v<T, T_Signature_ll_bool_t>;

		static constexpr ll_bool_t T_U_BASIC_TYPE =
			traits::is_basic_type_v<T> && traits::is_basic_type_v<U>;

		static constexpr ll_bool_t IS_COMPARABLE_EQ =
			T_HAS_EQ_SIGNATURE_BOOL || T_U_BASIC_TYPE
			|| T_HAS_EQ_SIGNATURE_LL_BOOL_T;
		static constexpr ll_bool_t IS_COMPARABLE_NEQ =
			T_HAS_NEQ_SIGNATURE_BOOL || T_U_BASIC_TYPE
			|| T_HAS_NEQ_SIGNATURE_LL_BOOL_T;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(traits::is_valid_type_checker_v<U>,
			"type_checker<U> detected an invalid type!");

		//static_assert(IS_COMPARABLE_EQ, "Types are not comparables!");
		//static_assert(IS_COMPARABLE_NEQ, "Types are not comparables!");

	#pragma endregion
	#pragma region Functions
	public:
		using compare_eq_type =
			std::conditional_t<T_HAS_EQ_SIGNATURE_BOOL || T_U_BASIC_TYPE, ll_bool_t, Boolean>;
		using compare_neq_type =
			std::conditional_t<T_HAS_NEQ_SIGNATURE_BOOL || T_U_BASIC_TYPE, ll_bool_t, Boolean>;

		__LL_NODISCARD__ static constexpr compare_eq_type is_same_value(t_cinput t, u_cinput u) noexcept {
			return (t == u);
		}
		__LL_NODISCARD__ static constexpr compare_eq_type is_not_same_value(t_cinput t, u_cinput u) noexcept {
			return (t != u);
		}

	#pragma endregion
};

template<
	class _T,
	class _U = _T,
	class _Orderning = get_three_way_comparasion_function_type_t<_T, _U>
>
struct is_diff {
	#pragma region Types
	public:
		// Class related
		using _MyType			= is_diff;

		// Types
		using T					= _T;
		using U					= _U;
		using Orderning			= _Orderning;
		using T_class			= std::conditional_t<std::is_class_v<T>, T, llcpp::Emptyclass>;

		// 
		using t_cinput			= traits::cinput<T>;
		using u_cinput			= traits::cinput<U>;
		
		// Signarures
		using T_Signature_C		= cmp_t(T_class::*)(u_cinput) const noexcept;
		using T_Signature_CPP	= Orderning(T_class::*)(u_cinput) const noexcept;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t T_HAS_C_SIGNATURE =
			traits::common::has_sgtrong_ordening_function_v<T, T_Signature_C>;
		static constexpr ll_bool_t T_HAS_CPP_SIGNATURE =
			traits::common::has_sgtrong_ordening_function_v<T, T_Signature_CPP>;

		static constexpr ll_bool_t T_U_BASIC_TYPE =
			traits::is_basic_type_v<T> && traits::is_basic_type_v<U>;

		static constexpr ll_bool_t IS_COMPARABLE =
			T_HAS_C_SIGNATURE || T_U_BASIC_TYPE
			|| T_HAS_CPP_SIGNATURE;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(traits::is_valid_type_checker_v<U>,
			"type_checker<U> detected an invalid type!");

	#pragma endregion
	#pragma region Functions
	public:
		__LL_NODISCARD__ static constexpr cmp_t diff_C(t_cinput t, u_cinput u) noexcept {
			static_assert(T_HAS_C_SIGNATURE || T_U_BASIC_TYPE, "Types are not comparables!");
			if constexpr (T_U_BASIC_TYPE) {
				if (t > u) return 1;
				else if (t < u) return -1;
				else return 0;
			}
			else return (t <=> u);
		}
		__LL_NODISCARD__ static constexpr Orderning diff_CPP(t_cinput t, u_cinput u) noexcept {
			static_assert(T_HAS_CPP_SIGNATURE || T_U_BASIC_TYPE, "Types are not comparables!");
			return (t <=> u);
		}

	#pragma endregion
};

//constexpr auto asdfadsd1 = is_diff<double>::diff_C(90.0, 99);
//constexpr auto asdfadsd2 = is_diff<double>::diff_CPP(90.0, 99);
//
//constexpr auto asdfadsd3 = llcpp::ZERO_I8 <=> llcpp::ZERO_I8;
//constexpr auto asdfadsd3 = llcpp::ZERO_I8 <=> llcpp::ZERO_I16;
//constexpr auto asdfadsd3 = llcpp::ZERO_I8 <=> llcpp::ZERO_I32;
//constexpr auto asdfadsd3 = llcpp::ZERO_I8 <=> llcpp::ZERO_I64;
//
//constexpr auto asdfadsd3 = llcpp::ZERO_I8 <=> llcpp::ZERO_F32;

#pragma endregion

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITS_HPP_
