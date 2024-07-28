//////////////////////////////////////////////
//	traits.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITS_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITS_MAYOR_ != 8 || LLANYLIB_TRAITS_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "traits.hpp version error!"
		#else
			#error "traits.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_TRAITS_MAYOR_ || LLANYLIB_TRAITS_MINOR_

#else !defined(LLANYLIB_TRAITS_HPP_)
#define LLANYLIB_TRAITS_HPP_
#define LLANYLIB_TRAITS_MAYOR_ 8
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
struct type_container { using T = _T; };

// Standard checker for types in this lib
template<class _T, ll_bool_t _IGNORE_POINTER = llcpp::LL_FALSE, ll_bool_t _IGNORE_VOLATILE = llcpp::LL_FALSE>
struct type_checker {
	using T = _T;

	static constexpr ll_bool_t IGNORE_POINTER = _IGNORE_POINTER;
	static constexpr ll_bool_t IGNORE_VOLATILE = _IGNORE_VOLATILE;

	static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
	static_assert(!std::is_array_v<T>, "Array type is forbidden!");
	static_assert(!std::is_volatile_v<T>, "Array type is forbidden!");
	static_assert(!std::is_pointer_v<T>, "Pointer type is forbidden!");

	static constexpr ll_bool_t is_valid_v = 
		   !std::is_reference_v<T>
		&& !std::is_array_v<T>
		&& (IGNORE_VOLATILE || !std::is_volatile_v<T>)
		&& (IGNORE_POINTER || !std::is_pointer_v<T>);
};

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_type_checker_v = 
	traits::type_checker<T>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_type_checker_ignore_pointer_v = 
	traits::type_checker<T, llcpp::LL_TRUE>::is_valid_v;

// Standard checker for classes and objects
// Checks contruction / destruction and other operations needed
template<class _T>
struct constructor_checker {
	using T = _T;

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
	using T = _T;
	using constructor_checker = traits::constructor_checker<T>;

	static_assert(std::is_class_v<T>, "T needs to be a class!");

	static constexpr ll_bool_t is_valid_v =  constructor_checker::is_valid_v && std::is_class_v<T>;
};

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_class_checker_v = traits::class_checker<T>::is_valid_v;

#pragma endregion
#pragma region BasicExpresions
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

#pragma endregion
#pragma region IntegralConstant
template<class _T, class _U, _T VALUE>
struct integral_constant_container {
	using T = _T;
	using U = _U;

	using integral_constant = std::integral_constant<T, VALUE>;
	using container = traits::type_container<U>;
	using type = integral_constant_container;
};

template<ll_bool_t VALUE, class U>
using bool_constant_container = traits::integral_constant_container<ll_bool_t, U, VALUE>;

template<class U>
using true_type  = traits::bool_constant_container<llcpp::LL_TRUE, U>;
template<class U>
using false_type = traits::bool_constant_container<llcpp::LL_FALSE, U>;

#pragma endregion
#pragma region Types
template<class T>
using input = std::conditional_t<traits::is_basic_type_v<T> || std::is_pointer_v<T>, T, T&>;
template<class T>
using cinput = std::conditional_t<traits::is_basic_type_v<T> || std::is_pointer_v<T>, const T, const T&>;

template<class _T, ll_bool_t _promote>
struct type_promotion {
	using T = _T;
	static constexpr ll_bool_t promote = _promote;

	static_assert(traits::is_valid_type_checker_v<T>, "type_checker<T> detected an invalid type!");

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

	using value = __type_promotion<promote>::value;
};

#pragma endregion
#pragma region MyRegion
template<class _Checker, class _VoidType = void>
struct check_valid_types {
	using Checker	= _Checker;
	using VoidType	= _VoidType;

	static_assert(traits::is_valid_type_checker_v<Checker>,
		"type_checker<Checker> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<Checker>,
		"class_checker<Checker> detected an invalid class type!");

	template<class T>
	static constexpr auto get_first() noexcept -> std::conditional_t<Checker::is_valid_v<T>, T, VoidType>;
	template<class T, class... Args>
	static constexpr auto get_first() noexcept -> std::conditional_t<Checker::is_valid_v<T>, T, decltype(get_first<Args...>())>;
	template<class... Args>
	using type = decltype(get_first<Args...>());
};

#define __LL_GENERIC_CHECKER__(name, checker) \
	struct is_valid_##name##_checker { \
		template<class T> \
		static constexpr ll_bool_t is_valid_v = ##checker##<T>; \
	}

#pragma endregion
#pragma region CharConditional
template<class _T, class _TypeChar, class _TypeWChar, class _ExtraType = void>
struct get_by_char_type {
	using T			= _T;
	using TypeChar	= _TypeChar;
	using TypeWChar = _TypeWChar;
	using ExtraType = _ExtraType;

	static_assert(traits::is_valid_type_checker_v<T>, "type_checker<T> detected an invalid type!");

	template <class U>
	struct __struct__ { using _val = ExtraType; };
	template<> struct __struct__<ll_char_t> { using _val = TypeChar; };
	template<> struct __struct__<ll_wchar_t> { using _val = TypeWChar; };
	using value = __struct__<T>::_val;
};

template<class T, class TypeChar, class TypeWChar, class ExtraType = void>
using get_by_char_type_t = traits::get_by_char_type<T, TypeChar, TypeWChar, ExtraType>::value;

#pragma endregion
#pragma region FunctionalReflector
template<class _ClassToCheck, class _OperatorType, class _Signature>
struct has_type_operator {
	using ClassToCheck	= _ClassToCheck;
	using OperatorType	= _OperatorType;
	using Signature		= _Signature;

	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<ClassToCheck>,
		"class_checker<ClassToCheck> detected an invalid class type!");

	using type_default_result =
		std::conditional_t<
			traits::is_basic_type_v<ClassToCheck> && std::is_same_v<ClassToCheck, OperatorType>,
			std::true_type,
			std::false_type
		>;
	template<class U>
	static constexpr auto test(Signature) noexcept -> std::true_type;
	template<class U>
	static constexpr auto test(...) noexcept -> type_default_result;
	using type = decltype(has_type_operator::test<ClassToCheck>(&ClassToCheck::operator OperatorType));
};

template<class ClassToCheck, class OperatorType, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_type_operator_v = traits::has_type_operator<ClassToCheck, OperatorType, Signature>::type::value;
template<class ClassToCheck, class OperatorType>
__LL_VAR_INLINE__ constexpr ll_bool_t has_simple_type_operator_v =
	traits::has_type_operator<ClassToCheck, OperatorType, OperatorType(ClassToCheck::*)() const noexcept>::type::value;

#pragma endregion
#pragma region SwapChecker
template<class _T>
struct is_nothrow_swappeable {
	using T = _T;

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
	using val = decltype(test());
};
template<class T>
using is_nothrow_swappeable_t = is_nothrow_swappeable<T>::val;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_nothrow_swappeable_v = is_nothrow_swappeable_t<T>::value;

#pragma endregion
#pragma region CopyChecker
template<class _T>
struct is_nothrow_copyable {
	using T = _T;

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
	using val = decltype(test());
};
template<class T>
using is_nothrow_copyable_t = is_nothrow_copyable<T>::val;
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
	static constexpr ll_bool_t empty = LL_FALSE;
	static constexpr ll_bool_t has_a_pointer = std::is_pointer_v<T>;
	static constexpr ll_bool_t has_a_array = std::is_array_v<T>;
};
template <>
struct parameter_pack_operations<> {
	using FirstType = parameter_pack_operations<int, int>::FirstType<void>;

	using pack_first = FirstType;
	using get_first_type = pack_first::type;
	static constexpr len_t size = ZERO_UI64;
	static constexpr ll_bool_t empty = LL_TRUE;
	static constexpr ll_bool_t has_a_pointer = LL_FALSE;
	static constexpr ll_bool_t has_a_array = LL_FALSE;
};

#pragma endregion

namespace common {

template<class _ClassToCheck, class _Signature>
struct has_hash_function{
	using ClassToCheck	= _ClassToCheck;
	using Signature		= _Signature;

	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<ClassToCheck>,
		"class_checker<ClassToCheck> detected an invalid class type!");

	template<class U>
	static constexpr auto test(Signature) noexcept -> std::true_type;
	template<class U>
	static constexpr auto test(...) noexcept -> std::false_type;
	using type = decltype(has_hash_function::test<ClassToCheck>(&ClassToCheck::hash));
};
template<class ClassToCheck, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_hash_function_v = 
	has_hash_function<ClassToCheck, Signature>::type::value;

template<class _ClassToCheck, class _Signature>
struct LL_SHARED_LIB has_clear_function {
	using ClassToCheck	= _ClassToCheck;
	using Signature		= _Signature;

	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<ClassToCheck>,
		"class_checker<ClassToCheck> detected an invalid class type!");

	template<class U>
	static constexpr auto test(Signature) noexcept -> std::true_type;
	template<class U>
	static constexpr auto test(...) noexcept -> std::false_type;
	using type = decltype(has_clear_function::test<ClassToCheck>(&ClassToCheck::clear));
};
template<class ClassToCheck, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_clear_function_v = 
	has_clear_function<ClassToCheck, Signature>::type::value;

template<class _ClassToCheck, class _Signature>
struct has_swap_function {
	using ClassToCheck	= _ClassToCheck;
	using Signature		= _Signature;

	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<ClassToCheck>,
		"class_checker<ClassToCheck> detected an invalid class type!");

	template<class U>
	static constexpr auto test(Signature) noexcept -> std::true_type;
	template<class U>
	static constexpr auto test(...) noexcept -> std::false_type;
	using type = decltype(has_swap_function::test<ClassToCheck>(&ClassToCheck::swap));
};
template<class ClassToCheck, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_swap_function_v = 
	has_swap_function<ClassToCheck, Signature>::type::value;

template<class _ClassToCheck, class _Signature>
struct has_copy_function {
	using ClassToCheck	= _ClassToCheck;
	using Signature		= _Signature;

	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<ClassToCheck>,
		"class_checker<ClassToCheck> detected an invalid class type!");

	template<class U>
	static constexpr auto test(Signature) noexcept -> std::true_type;
	template<class U>
	static constexpr auto test(...) noexcept -> std::false_type;
	using type = decltype(has_copy_function::test<ClassToCheck>(&ClassToCheck::copy));
};
template<class ClassToCheck, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_copy_function_v =
	has_copy_function<ClassToCheck, Signature>::type::value;

template<class _ClassToCheck, class _Signature>
struct has_move_function {
	using ClassToCheck	= _ClassToCheck;
	using Signature		= _Signature;

	static_assert(traits::is_valid_type_checker_v<ClassToCheck>, "type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<ClassToCheck>, "class_checker<ClassToCheck> detected an invalid class type!");

	template<class U>
	static constexpr auto test(Signature) noexcept -> std::true_type;
	template<class U>
	static constexpr auto test(...) noexcept -> std::false_type;
	using type = decltype(has_move_function::test<ClassToCheck>(&ClassToCheck::move));
};
template<class ClassToCheck, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_move_function_v =
	has_move_function<ClassToCheck, Signature>::type::value;

template<class _ClassToCheck, class _Signature>
struct has_compare_function {
	using ClassToCheck	= _ClassToCheck;
	using Signature		= _Signature;

	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<ClassToCheck>,
		"class_checker<ClassToCheck> detected an invalid class type!");

	template<class U>
	static constexpr auto test(Signature) noexcept -> std::true_type;
	template<class U>
	static constexpr auto test(...) noexcept -> std::false_type;
	using type = decltype(has_compare_function::test<ClassToCheck>(&ClassToCheck::compareBool));
};
template<class ClassToCheck, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_compare_function_v =
	has_compare_function<ClassToCheck, Signature>::type::value;

template<class _ClassToCheck, class _Signature>
struct has_compareBool_function {
	using ClassToCheck	= _ClassToCheck;
	using Signature		= _Signature;

	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<ClassToCheck>,
		"class_checker<ClassToCheck> detected an invalid class type!");

	template<class U>
	static constexpr auto test(Signature) noexcept -> std::true_type;
	template<class U>
	static constexpr auto test(...) noexcept -> std::false_type;
	using type = decltype(has_compareBool_function::test<ClassToCheck>(&ClassToCheck::compareBool));
};
template<class ClassToCheck, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_compareBool_function_v =
	has_compareBool_function<ClassToCheck, Signature>::type::value;


} // namespace common

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITS_HPP_
