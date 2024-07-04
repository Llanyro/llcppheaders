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

#pragma region Types
template<class T>
struct type_container { using value = T; };

template<class T, class U, T VALUE>
struct integral_constant_container {
	using integral_constant = std::integral_constant<T, VALUE>;
	using container = type_container<U>;
};

template<ll_bool_t VALUE, class U>
using bool_constant_container = integral_constant_container<ll_bool_t, U, VALUE>;

template<class U>
using true_type  = bool_constant_container<LL_TRUE, U>;
template<class U>
using false_type = bool_constant_container<LL_FALSE, U>;

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
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_hash_type_v = std::_Is_any_of_v<std::remove_cv_t<T>, hash::Hash32, hash::Hash64, hash::Hash128>;
template<class>
__LL_VAR_INLINE__ constexpr len_t array_size = ZERO_UI64;
template<class T, len_t N>
__LL_VAR_INLINE__ constexpr len_t array_size<T[N]> = N;

template<class T>
using input = std::conditional_t<traits::is_basic_type_v<T> || std::is_pointer_v<T>, T, T&>;
template<class T>
using cinput = std::conditional_t<traits::is_basic_type_v<T> || std::is_pointer_v<T>, const T, const T&>;


template<class T>
struct type_conversor {
	struct to_raw {
		static constexpr auto test() noexcept {
			if constexpr (std::is_reference_v<T>)
				return type_conversor<std::remove_reference_t<T>>::to_raw::test();
			else if constexpr (std::is_pointer_v<T>)
				return type_conversor<std::remove_pointer_t<T>>::to_raw::test();
			else if constexpr (std::is_array_v<T>) {
				T _{};
				return type_conversor<decltype(*_)>::to_raw::test();
			}
			else if constexpr (std::is_const_v<T>)
				return type_conversor<std::remove_const_t<T>>::to_raw::test();
			else return traits::type_container<T>{};
		}
		using value = typename decltype(test())::value;
	};
	struct to_const {
		static constexpr auto test() noexcept {
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
		using value = typename decltype(test())::value;
	};
	template<ll_bool_t ALL> struct to_reference {
		static constexpr auto test() noexcept {
			using __raw_type = type_conversor<T>::to_raw_t;

			if constexpr (std::is_pointer_v<T> || std::is_array_v<T> || !traits::is_basic_type_v<__raw_type> || ALL)
				return traits::type_container<std::add_lvalue_reference_t<T>>{};
			else return traits::type_container<T>{};
		}
		using value = typename decltype(test())::value;
	};
	template<ll_bool_t ALL> struct to_const_reference {
		static constexpr auto test() noexcept {
			using __raw_type = type_conversor<T>::to_raw_t;
			using __const_type = type_conversor<T>::to_const_t;
			if constexpr (ALL || !(std::is_pointer_v<T> || std::is_array_v<T> || traits::is_basic_type_v<__raw_type>))
				return traits::type_container<std::add_lvalue_reference_t<__const_type>>{};
			else return traits::type_container<__const_type>{};
		}
		using value = typename decltype(test())::value;
	};
	struct to_movement {
		static constexpr auto test() noexcept {
			if constexpr (std::is_reference_v<T>) {
				using __noreference = std::remove_reference_t<T>;
				return traits::type_container<__noreference&&>{};
			}
			else return traits::type_container<T&&>{};
		}
		using value = typename decltype(test())::value;
	};
	struct get_ptr_remove_reference {
		static constexpr auto test() noexcept {
			if constexpr (std::is_reference_v<T>) {
				using __noreference = std::remove_reference_t<T>;
				return traits::type_container<__noreference*>{};
			}
			else return traits::type_container<T*>{};
		}
		using value = typename decltype(test())::value;
	};
	struct get_const_ptr_remove_reference {
		static constexpr auto test() noexcept {
			return traits::type_container<type_conversor<get_ptr_remove_reference::value>::to_const_t>{};
		}
		using value = typename decltype(test())::value;
	};
	template<ll_bool_t promote> struct type_promotion {
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
	struct array_to_type {
		static constexpr auto test() noexcept {
			if constexpr (std::is_array_v<T>) {
				T _{};
				return traits::type_container<std::remove_reference_t<decltype(*_)>>{};
			}
			else return traits::type_container<T>{};
		}
		using value = typename decltype(test())::value;
	};

	// Gets raw type, no pointers, no references (rvalue || lvalue)
	using to_raw_t = to_raw::value;
	// Removes all attributes, adds const, and restores all attributes
	using to_const_t = to_const::value;
	// Adds a lvalue reference if type is not a basic type of a basic bigger type
	// If all is true, all types would get a reference
	using to_reference_t = to_reference<LL_FALSE>::value;
	using to_reference_all_t = to_reference<LL_TRUE>::value;
	// Adds a const lvalue reference if type is not a basic type of a basic bigger type
	// If all is true, all types would get a const reference
	using to_const_reference_t = to_const_reference<LL_FALSE>::value;
	using to_const_reference_all_t = to_const_reference<LL_TRUE>::value;
	// Adds a rvalue reference
	using to_movement_t = to_movement::value;
	// Get a ptr type, and removes reference if it has
	using get_ptr_remove_reference_t = get_ptr_remove_reference::value;
	// Get a const ptr type, and removes reference if it has
	//using _t = get_cptr_remove_reference;
	/// [TOFIX] This breaks something...
	//using get_const_ptr_remove_reference_t = get_const_ptr_remove_reference::value;
	// Promote a type to a bigger or smaller type
	using promote_t = type_promotion<LL_TRUE>::value;
	using demote_t = type_promotion<LL_FALSE>::value;

	using array_to_type_t = array_to_type::value;
};

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
using get_by_char_type_t = get_by_char_type<T, TypeChar, TypeWChar, ExtraType>::value;

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
__LL_VAR_INLINE__ constexpr ll_bool_t has_type_operator_v = has_type_operator<ClassToCheck, OperatorType, Signature>::type::value;

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
	__LL_VAR_INLINE__ constexpr ll_bool_t has_##name##_function_v = has_##name##_function<ClassToCheck, Signature>::type::value;



#pragma endregion

//template<class ClassType, class FuncType>
//struct get_class_function {
//	static constexpr auto test(const ClassType* p) noexcept -> void;
//	static constexpr auto test(...) noexcept -> void;
//
//
//	using value = 
//};

#pragma endregion
#pragma region SwapChecker
template<class T>
struct is_nothrow_swappeable {
	static constexpr auto test() noexcept {
		if constexpr (std::is_pointer_v<T> || traits::is_basic_type_v<T>)
			return std::true_type{};
		else if constexpr (std::is_array_v<T>) {
			using arr_type = traits::type_conversor<T>::array_to_type_t;
			return is_nothrow_swappeable<arr_type>::test();
		}
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
			using arr_type = traits::type_conversor<T>::array_to_type_t;
			return is_nothrow_copyable<arr_type>::test();
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
