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
		static constexpr auto test() __LL_EXCEPT__ {
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
		static constexpr auto test() __LL_EXCEPT__ {
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
		static constexpr auto test() __LL_EXCEPT__ {
			using __raw_type = type_conversor<T>::to_raw_t;

			if constexpr (std::is_pointer_v<T> || std::is_array_v<T> || !traits::is_basic_type_v<__raw_type> || ALL)
				return traits::type_container<std::add_lvalue_reference_t<T>>{};
			else return traits::type_container<T>{};
		}
		using value = typename decltype(test())::value;
	};
	template<ll_bool_t ALL> struct to_const_reference {
		static constexpr auto test() __LL_EXCEPT__ {
			using __raw_type = type_conversor<T>::to_raw_t;
			using __const_type = type_conversor<T>::to_const_t;
			if constexpr (ALL || !(std::is_pointer_v<T> || std::is_array_v<T> || traits::is_basic_type_v<__raw_type>))
				return traits::type_container<std::add_lvalue_reference_t<__const_type>>{};
			else return traits::type_container<__const_type>{};
		}
		using value = typename decltype(test())::value;
	};
	struct to_movement {
		static constexpr auto test() __LL_EXCEPT__ {
			if constexpr (std::is_reference_v<T>) {
				using __noreference = std::remove_reference_t<T>;
				return traits::type_container<__noreference&&>{};
			}
			else return traits::type_container<T&&>{};
		}
		using value = typename decltype(test())::value;
	};
	struct get_ptr_remove_reference {
		static constexpr auto test() __LL_EXCEPT__ {
			if constexpr (std::is_reference_v<T>) {
				using __noreference = std::remove_reference_t<T>;
				return traits::type_container<__noreference*>{};
			}
			else return traits::type_container<T*>{};
		}
		using value = typename decltype(test())::value;
	};
	struct get_const_ptr_remove_reference {
		static constexpr auto test() __LL_EXCEPT__ {
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
		static constexpr auto test() __LL_EXCEPT__ {
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

template<class Func>
struct member_function_traits {
	using return_type = void;
	using instance_type = EmptyStruct;
	static constexpr len_t argument_count = ZERO_UI64;
};
template<class Return, class Object, class... Args>
struct member_function_traits<Return(Object::*)(Args...)> {
	using return_type = Return;
	using instance_type = Object;
	static constexpr len_t argument_count = sizeof...(Args);
};
template<class Return, class Object, class... Args>
struct member_function_traits<Return(Object::*)(Args...) __LL_EXCEPT__> {
	using return_type = Return;
	using instance_type = Object;
	static constexpr len_t argument_count = sizeof...(Args);
};
//template<class Return, class Object, class... Args>
//struct member_function_traits<Return(Object::*)(Args...) const> {
//	using return_type = Return;
//	using instance_type = Object;
//	static constexpr len_t argument_count = sizeof...(Args);
//};
//template<class Return, class Object, class... Args>
//struct member_function_traits<Return(Object::*)(Args...) const __LL_EXCEPT__> {
//	using return_type = Return;
//	using instance_type = Object;
//	static constexpr len_t argument_count = sizeof...(Args);
//};



namespace internal_has_functional {

enum class HasFunctionResult { True, False, Unknown };

template<HasFunctionResult _Val>
struct operation_result { static constexpr HasFunctionResult value = _Val; };
using operation_true = operation_result<HasFunctionResult::True>;
using operation_false = operation_result<HasFunctionResult::False>;
using operation_unknown = operation_result<HasFunctionResult::Unknown>;

template<class T = operation_unknown, class U = void>
struct operation_container {
	using result = T;
	using value = U;
};

template<class U = void>
using operation_container_true = operation_container<operation_true, U>;
template<class U = void>
using operation_container_false = operation_container<operation_false, U>;
using operation_container_unknown = operation_container<operation_unknown>;

using op_unknown = operation_container_unknown;

template<
	class _Tbase = operation_container_unknown,
	class _Tconst = operation_container_unknown,
	class _Tstatic = operation_container_unknown,
	class _Texcept = operation_container_unknown,
	class _Tbasic_type = operation_container_unknown
>
struct has_function_results {
	using result_base = _Tbase;
	using result_const = _Tconst;
	using result_static = _Tstatic;
	using result_except = _Texcept;
	using result_basic_type = _Tbasic_type;
};

template<class _Tbasic_type = operation_container_unknown>
using has_function_results_basic_type = has_function_results<op_unknown, op_unknown, op_unknown, op_unknown, _Tbasic_type>;

} // namespace internal_has_functional

template <class T, class OperatorType>
struct has_type_operator {
	using _has_type_operator = has_type_operator;
	using HasFunctionResult = internal_has_functional::HasFunctionResult;
	using op_unknown = internal_has_functional::op_unknown;

	using type_default_result =
		internal_has_functional::has_function_results_basic_type<
			std::conditional_t<
				traits::is_basic_type_v<T> && std::is_same_v<T, OperatorType>,
				internal_has_functional::operation_container_true<T>,
				internal_has_functional::operation_container_false<T>
			>
		>;

	template <class U>
	using FunctionSignature = OperatorType(U::*)();
	template <class U>
	using FunctionSignatureExcept = OperatorType(U::*)() __LL_EXCEPT__;

	template <class U>
	static constexpr auto test_noconst(U* p) __LL_EXCEPT__ {
		using FunctionType = decltype(&U::operator OperatorType);
		using BaseClassType = member_function_traits<FunctionType>::instance_type;

		using operation_const = internal_has_functional::operation_container_false<FunctionType>;
		using operation_static = internal_has_functional::operation_container_false<FunctionType>;

		using operation_base = std::conditional_t<
			std::is_same_v<FunctionType, FunctionSignature<BaseClassType>> || std::is_same_v<FunctionType, FunctionSignatureExcept<BaseClassType>>,
			internal_has_functional::operation_container_true<FunctionType>,
			internal_has_functional::operation_container_false<FunctionType>
		>;
		using operation_except = std::conditional_t<
			std::is_same_v<FunctionType, FunctionSignatureExcept<BaseClassType>>,
			internal_has_functional::operation_container_true<FunctionType>,
			internal_has_functional::operation_container_false<FunctionType>
		>;
		return internal_has_functional::has_function_results<operation_base, operation_const, operation_static, operation_except, op_unknown>{};
	}
	template <class>
	static constexpr auto test_noconst(...) __LL_EXCEPT__-> type_default_result;

	template <class U>
	using FunctionSignatureConst = OperatorType(U::*)() const;
	template <class U>
	using FunctionSignatureExceptConst = OperatorType(U::*)() const __LL_EXCEPT__;

	template <class U>
	static constexpr auto test_const(const U* p) __LL_EXCEPT__ {
		using FunctionType = decltype(&U::operator OperatorType);
		using BaseClassType = member_function_traits<FunctionType>::instance_type;

		using operation_base = internal_has_functional::operation_container_false<FunctionType>;
		using operation_static = internal_has_functional::operation_container_false<FunctionType>;

		using operation_const = std::conditional_t<
			std::is_same_v<FunctionType, FunctionSignatureConst<BaseClassType>> || std::is_same_v<FunctionType, FunctionSignatureExceptConst<BaseClassType>>,
			internal_has_functional::operation_container_true<FunctionType>,
			internal_has_functional::operation_container_false<FunctionType>
		>;
		using operation_except = std::conditional_t<
			std::is_same_v<FunctionType, FunctionSignatureExceptConst<BaseClassType>>,
			internal_has_functional::operation_container_true<FunctionType>,
			internal_has_functional::operation_container_false<FunctionType>
		>;
		return internal_has_functional::has_function_results<operation_base, operation_const, operation_static, operation_except, op_unknown>{};
	}
	template <class>
	static constexpr auto test_const(...) __LL_EXCEPT__-> type_default_result;

	static constexpr ll_bool_t check_const() __LL_EXCEPT__ {
		if constexpr (traits::is_basic_type_v<T>)
			return std::is_same_v<T, OperatorType>;
		else {
			using const_result = decltype(test_const<T>(nullptr));
			if constexpr (const_result::result_basic_type::result::value != HasFunctionResult::Unknown)
				return LL_FALSE;
			else if constexpr (const_result::result_base::result::value != HasFunctionResult::False)
				return LL_FALSE;
			else if constexpr (const_result::result_const::result::value != HasFunctionResult::True)
				return LL_FALSE;
			else if constexpr (const_result::result_except::result::value != HasFunctionResult::False)
				return LL_FALSE;
			else if constexpr (const_result::result_static::result::value != HasFunctionResult::False)
				return LL_FALSE;
			return LL_TRUE;
		}
	}
	static constexpr ll_bool_t check_const_except() __LL_EXCEPT__ {
		using const_result = decltype(test_const<T>(nullptr));
		if constexpr (const_result::result_basic_type::result::value != HasFunctionResult::Unknown)
			return LL_FALSE;
		else if constexpr (const_result::result_base::result::value != HasFunctionResult::False)
			return LL_FALSE;
		else if constexpr (const_result::result_const::result::value != HasFunctionResult::True)
			return LL_FALSE;
		else if constexpr (const_result::result_except::result::value != HasFunctionResult::True)
			return LL_FALSE;
		else if constexpr (const_result::result_static::result::value != HasFunctionResult::False)
			return LL_FALSE;
		return LL_TRUE;
	}
	static constexpr ll_bool_t check_base() __LL_EXCEPT__ {
		using no_const_result = decltype(test_noconst<T>(nullptr));
		if constexpr (no_const_result::result_basic_type::result::value != HasFunctionResult::Unknown)
			return LL_FALSE;
		else if constexpr (no_const_result::result_base::result::value != HasFunctionResult::True)
			return LL_FALSE;
		else if constexpr (no_const_result::result_const::result::value != HasFunctionResult::False)
			return LL_FALSE;
		else if constexpr (no_const_result::result_except::result::value != HasFunctionResult::False)
			return LL_FALSE;
		else if constexpr (no_const_result::result_static::result::value != HasFunctionResult::False)
			return LL_FALSE;
		return LL_TRUE;
	}
	static constexpr ll_bool_t check_base_except() __LL_EXCEPT__ {
		using no_const_result = decltype(test_noconst<T>(nullptr));
		if constexpr (no_const_result::result_basic_type::result::value != HasFunctionResult::Unknown)
			return LL_FALSE;
		else if constexpr (no_const_result::result_base::result::value != HasFunctionResult::True)
			return LL_FALSE;
		else if constexpr (no_const_result::result_const::result::value != HasFunctionResult::False)
			return LL_FALSE;
		else if constexpr (no_const_result::result_except::result::value != HasFunctionResult::True)
			return LL_FALSE;
		else if constexpr (no_const_result::result_static::result::value != HasFunctionResult::False)
			return LL_FALSE;
		return LL_TRUE;
	}
};

template <class T, class OperatorType>
__LL_VAR_INLINE__ constexpr ll_bool_t has_type_operator_base_v = has_type_operator<T, OperatorType>::check_base();
template <class T, class OperatorType>
__LL_VAR_INLINE__ constexpr ll_bool_t has_type_operator_base_except_v = has_type_operator<T, OperatorType>::check_base_except();

template <class T, class OperatorType>
__LL_VAR_INLINE__ constexpr ll_bool_t has_type_operator_const_v = has_type_operator<T, OperatorType>::check_const();
template <class T, class OperatorType>
__LL_VAR_INLINE__ constexpr ll_bool_t has_type_operator_const_except_v = has_type_operator<T, OperatorType>::check_const_except();


#define __LL_TEMPLATE_HAS_FUNCTION_BASE__(name, function, basic_value) \
	template <class T, class ReturnType, class... SignarureArgs> \
	struct has_##name## { \
		using _has_##name## = has_##name##; \
		using HasFunctionResult = internal_has_functional::HasFunctionResult; \
		using op_unknown = internal_has_functional::op_unknown; \
		 \
		using type_default_result =  \
			internal_has_functional::has_function_results_basic_type< \
				std::conditional_t< \
					traits::is_basic_type_v<T> && basic_value, \
					internal_has_functional::operation_container_true<T>, \
					internal_has_functional::operation_container_false<T> \
				> \
			>; \
		 \
		template <class U> \
		using FunctionSignature = ReturnType(U::*)(SignarureArgs...); \
		template <class U> \
		using FunctionSignatureExcept = ReturnType(U::*)(SignarureArgs...) __LL_EXCEPT__; \
		template <class U> \
		using FunctionSignatureStatic = ReturnType(*)(SignarureArgs...); \
		template <class U> \
		using FunctionSignatureExceptStatic = ReturnType(*)(SignarureArgs...) __LL_EXCEPT__; \
	 \
		template <class U> \
		static constexpr auto test_noconst(U* p) __LL_EXCEPT__ { \
			using FunctionType = decltype(&U::function); \
			using BaseClassType = member_function_traits<FunctionType>::instance_type; \
			 \
			using operation_const = internal_has_functional::operation_container_false<FunctionType>; \
			 \
			using operation_base = std::conditional_t< \
				std::is_same_v<FunctionType, FunctionSignature<BaseClassType>> || std::is_same_v<FunctionType, FunctionSignatureExcept<BaseClassType>>, \
				internal_has_functional::operation_container_true<FunctionType>, \
				internal_has_functional::operation_container_false<FunctionType> \
			>; \
			using operation_static = std::conditional_t< \
				std::is_same_v<FunctionType, FunctionSignatureStatic<BaseClassType>> || std::is_same_v<FunctionType, FunctionSignatureExceptStatic<BaseClassType>>, \
				internal_has_functional::operation_container_true<FunctionType>, \
				internal_has_functional::operation_container_false<FunctionType> \
			>; \
			using operation_except = std::conditional_t< \
				std::is_same_v<FunctionType, FunctionSignatureExcept<BaseClassType>> || std::is_same_v<FunctionType, FunctionSignatureExceptStatic<BaseClassType>>, \
				internal_has_functional::operation_container_true<FunctionType>, \
				internal_has_functional::operation_container_false<FunctionType> \
			>; \
			return internal_has_functional::has_function_results<operation_base, operation_const, operation_static, operation_except, op_unknown>{}; \
		} \
		template <class> \
		static constexpr auto test_noconst(...) __LL_EXCEPT__-> type_default_result; \
		 \
		template <class U> \
		using FunctionSignatureConst = ReturnType(U::*)(SignarureArgs...) const; \
		template <class U> \
		using FunctionSignatureExceptConst = ReturnType(U::*)(SignarureArgs...) const __LL_EXCEPT__; \
		 \
		template <class U> \
		static constexpr auto test_const(const U* p) __LL_EXCEPT__ { \
			using FunctionType = decltype(&U::function); \
			using BaseClassType = member_function_traits<FunctionType>::instance_type; \
			 \
			using operation_base = internal_has_functional::operation_container_false<FunctionType>; \
			using operation_static = internal_has_functional::operation_container_false<FunctionType>; \
			 \
			using operation_const = std::conditional_t< \
				std::is_same_v<FunctionType, FunctionSignatureConst<BaseClassType>> || std::is_same_v<FunctionType, FunctionSignatureExceptConst<BaseClassType>>, \
				internal_has_functional::operation_container_true<FunctionType>, \
				internal_has_functional::operation_container_false<FunctionType> \
			>; \
			using operation_except = std::conditional_t< \
				std::is_same_v<FunctionType, FunctionSignatureExceptConst<BaseClassType>>, \
				internal_has_functional::operation_container_true<FunctionType>, \
				internal_has_functional::operation_container_false<FunctionType> \
			>; \
			return internal_has_functional::has_function_results<operation_base, operation_const, operation_static, operation_except, op_unknown>{}; \
		} \
		template <class> \
		static constexpr auto test_const(...) __LL_EXCEPT__-> type_default_result; \
		 \
		 \
		static constexpr ll_bool_t check_static() __LL_EXCEPT__ { \
			using no_const_result = decltype(test_noconst<T>(nullptr)); \
			if constexpr (no_const_result::result_basic_type::result::value != HasFunctionResult::Unknown) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_base::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_const::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_except::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_static::result::value != HasFunctionResult::True) \
				return LL_FALSE; \
			return LL_TRUE; \
		} \
		static constexpr ll_bool_t check_static_except() __LL_EXCEPT__ { \
			using no_const_result = decltype(test_noconst<T>(nullptr)); \
			if constexpr (no_const_result::result_basic_type::result::value != HasFunctionResult::Unknown) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_base::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_const::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_except::result::value != HasFunctionResult::True) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_static::result::value != HasFunctionResult::True) \
				return LL_FALSE; \
			return LL_TRUE; \
		} \
		static constexpr ll_bool_t check_const() __LL_EXCEPT__ { \
			using const_result = decltype(test_const<T>(nullptr)); \
			if constexpr (const_result::result_basic_type::result::value != HasFunctionResult::Unknown) \
				return LL_FALSE; \
			else if constexpr (const_result::result_base::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			else if constexpr (const_result::result_const::result::value != HasFunctionResult::True) \
				return LL_FALSE; \
			else if constexpr (const_result::result_except::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			else if constexpr (const_result::result_static::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			return LL_TRUE; \
		} \
		static constexpr ll_bool_t check_const_except() __LL_EXCEPT__ { \
			using const_result = decltype(test_const<T>(nullptr)); \
			if constexpr (const_result::result_basic_type::result::value != HasFunctionResult::Unknown) \
				return LL_FALSE; \
			else if constexpr (const_result::result_base::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			else if constexpr (const_result::result_const::result::value != HasFunctionResult::True) \
				return LL_FALSE; \
			else if constexpr (const_result::result_except::result::value != HasFunctionResult::True) \
				return LL_FALSE; \
			else if constexpr (const_result::result_static::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			return LL_TRUE; \
		} \
		static constexpr ll_bool_t check_base() __LL_EXCEPT__ { \
			using no_const_result = decltype(test_noconst<T>(nullptr)); \
			if constexpr (no_const_result::result_basic_type::result::value != HasFunctionResult::Unknown) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_base::result::value != HasFunctionResult::True) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_const::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_except::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_static::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			return LL_TRUE; \
		} \
		static constexpr ll_bool_t check_base_except() __LL_EXCEPT__ { \
			using no_const_result = decltype(test_noconst<T>(nullptr)); \
			if constexpr (no_const_result::result_basic_type::result::value != HasFunctionResult::Unknown) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_base::result::value != HasFunctionResult::True) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_const::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_except::result::value != HasFunctionResult::True) \
				return LL_FALSE; \
			else if constexpr (no_const_result::result_static::result::value != HasFunctionResult::False) \
				return LL_FALSE; \
			return LL_TRUE; \
		} \
	}; \
	 \
	template <class T, class ReturnType, class... SignarureArgs> \
	__LL_VAR_INLINE__ constexpr ll_bool_t has_##name##_static_v = has_##name##<T, ReturnType, SignarureArgs...>::check_static(); \
	template <class T, class ReturnType, class... SignarureArgs> \
	__LL_VAR_INLINE__ constexpr ll_bool_t has_##name##_static_except_v = has_##name##<T, ReturnType, SignarureArgs...>::check_static_except(); \
	 \
	template <class T, class ReturnType, class... SignarureArgs> \
	__LL_VAR_INLINE__ constexpr ll_bool_t has_##name##_base_v = has_##name##<T, ReturnType, SignarureArgs...>::check_base(); \
	template <class T, class ReturnType, class... SignarureArgs> \
	__LL_VAR_INLINE__ constexpr ll_bool_t has_##name##_base_except_v = has_##name##<T, ReturnType, SignarureArgs...>::check_base_except(); \
	 \
	template <class T, class ReturnType, class... SignarureArgs> \
	__LL_VAR_INLINE__ constexpr ll_bool_t has_##name##_const_v = has_##name##<T, ReturnType, SignarureArgs...>::check_const(); \
	template <class T, class ReturnType, class... SignarureArgs> \
	__LL_VAR_INLINE__ constexpr ll_bool_t has_##name##_const_except_v = has_##name##<T, ReturnType, SignarureArgs...>::check_const_except();

__LL_TEMPLATE_HAS_FUNCTION_BASE__(swap, swap, LL_FALSE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(clear, clear, LL_FALSE);

#pragma endregion
#pragma region SwapChecker
template<class T>
struct is_nothrow_swappeable {
	static constexpr auto test() __LL_EXCEPT__ {
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
	static constexpr auto test() __LL_EXCEPT__ {
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
