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

#pragma region TraitsTypes
template<class T>
struct type_container { using value = T; };

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
template<class T, class U, T VALUE>
struct integral_constant_container {
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

#pragma endregion
#pragma region MyRegion
template<class Checker, class VoidType = void>
struct check_valid_types {
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
template<class T, class TypeChar, class TypeWChar, class ExtraType = void>
struct get_by_char_type {
	template <class U>
	struct __internal__struct__ { using _val = ExtraType; };
	template<> struct __internal__struct__<ll_char_t> { using _val = TypeChar; };
	template<> struct __internal__struct__<ll_wchar_t> { using _val = TypeWChar; };
	using value = __internal__struct__<std::remove_const_t<T>>::_val;
};

template<class T, class TypeChar, class TypeWChar, class ExtraType = void>
using get_by_char_type_t = traits::get_by_char_type<T, TypeChar, TypeWChar, ExtraType>::value;

#pragma endregion
#pragma region FunctionalReflector

template<class ClassToCheck, class OperatorType, class Signature>
struct has_type_operator {
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

#define __LL_TEMPLATE_HAS_FUNCTION_BASE__(name, function) \
	template<class ClassToCheck, class Signature> \
	struct has_##name##_function { \
		template<class U> \
		static constexpr auto test(Signature) noexcept -> std::true_type; \
		template<class U> \
		static constexpr auto test(...) noexcept -> std::false_type; \
		using type = decltype(has_##name##_function::test<ClassToCheck>(&ClassToCheck::##function##)); \
	}; \
	template<class ClassToCheck, class Signature> \
	__LL_VAR_INLINE__ constexpr ll_bool_t has_##name##_function_v = traits::has_##name##_function<ClassToCheck, Signature>::type::value; \

#pragma endregion
#pragma region SwapChecker
template<class T>
struct is_nothrow_swappeable {
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
template<class T>
struct is_nothrow_copyable {
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

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITS_HPP_
