//////////////////////////////////////////////
//	traits_signature.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSSIGNATURE_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSSIGNATURE_MAYOR_ != 10 || LLANYLIB_TRAITSSIGNATURE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_signature.hpp version error!"
		#else
			#error "traits_signature.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSSIGNATURE_MAYOR_ || LLANYLIB_TRAITSSIGNATURE_MINOR_

#else !defined(LLANYLIB_TRAITSSIGNATURE_HPP_)
#define LLANYLIB_TRAITSSIGNATURE_HPP_
#define LLANYLIB_TRAITSSIGNATURE_MAYOR_ 10
#define LLANYLIB_TRAITSSIGNATURE_MINOR_ 0

#include "traits_checker.hpp"

namespace llcpp {
namespace meta {
namespace traits {
namespace __traits__ {

#pragma region Internal
// SFINAE to check if object has a function
// Follow any class that this inherites to check how to do a new checker 
template<class _Base>
struct has_common_signature : public _Base {
	// Class related
	using _MyType		= has_common_signature;
	using Base			= _Base;
	using ClassToCheck	= typename Base::ClassToCheck;

	// Types and enums
	using type			= decltype(Base::template test<ClassToCheck>(LL_NULLPTR));

	// Asserts
	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_constructor_checker_v<ClassToCheck>,
		"constructor_checker<ClassToCheck> detected an invalid class type!");
	static_assert(std::is_class_v<ClassToCheck>,
		"ClassToCheck is not a class!");
};
template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args>
struct return_common {
	// Class related
	using _MyType				= return_common;

	// Types and enums
	using ClassToCheck			= _ClassToCheck;

	// Expresions
	static constexpr meta::function_attributes_t ATTRIBUTES = _ATTRIBUTES;

	// Asserts
	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_constructor_checker_v<ClassToCheck>,
		"constructor_checker<ClassToCheck> detected an invalid class type!");
	static_assert(std::is_class_v<ClassToCheck>,
		"ClassToCheck is not a class!");

	template<class _, std::enable_if_t<!ATTRIBUTES.CONST && !ATTRIBUTES.NOEXCEPTION, int> = 0>
	static constexpr auto test(auto(ClassToCheck::* f)(Args...)) noexcept					-> std::_Invoke_result_t<decltype(f), ClassToCheck, Args...>;
	template<class _, std::enable_if_t<!ATTRIBUTES.CONST && ATTRIBUTES.NOEXCEPTION, int> = 0>
	static constexpr auto test(auto(ClassToCheck::* f)(Args...) noexcept) noexcept			-> std::_Invoke_result_t<decltype(f), ClassToCheck, Args...>;
	template<class _, std::enable_if_t<ATTRIBUTES.CONST && !ATTRIBUTES.NOEXCEPTION, int> = 0>
	static constexpr auto test(auto(ClassToCheck::* f)(Args...) const) noexcept				-> std::_Invoke_result_t<decltype(f), ClassToCheck, Args...>;
	template<class _, std::enable_if_t<ATTRIBUTES.CONST && ATTRIBUTES.NOEXCEPTION, int> = 0>
	static constexpr auto test(auto(ClassToCheck::* f)(Args...) const noexcept) noexcept	-> std::_Invoke_result_t<decltype(f), ClassToCheck, Args...>;
	template<class _>
	static constexpr auto test(...) noexcept												-> llcpp::Emptyclass;
};

} // namespace __traits__

#pragma endregion
#pragma region TypeOperator
namespace signature {

template<class _ClassToCheck, class _OperatorType, class _Signature>
struct has_type_operator {
	// Class related
	using _MyType		= has_type_operator;

	// Types and enums
	using ClassToCheck	= _ClassToCheck;
	using OperatorType	= _OperatorType;
	using Signature		= _Signature;
	template<ll_bool_t, ll_bool_t> struct SFINAE { using type = std::false_type; };
	template<> struct SFINAE<llcpp::TRUE, llcpp::TRUE> { using type = std::true_type; };
	using type_default_result =
		typename SFINAE<traits::is_basic_type_v<ClassToCheck>, std::is_same_v<ClassToCheck, OperatorType>>::type;

	// Functions
	template<class U>
	static constexpr auto test(Signature) noexcept -> std::true_type;
	template<class U>
	static constexpr auto test(...) noexcept -> type_default_result;
	using type = decltype(has_type_operator::test<ClassToCheck>(&ClassToCheck::operator OperatorType));
};

template<class ClassToCheck, class OperatorType, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_type_operator_v =
	signature::has_type_operator<ClassToCheck, OperatorType, Signature>::type::value;
template<class ClassToCheck, class OperatorType>
__LL_VAR_INLINE__ constexpr ll_bool_t has_simple_type_operator_v =
	signature::has_type_operator<ClassToCheck, OperatorType, OperatorType(T_Class<ClassToCheck>::*)() noexcept>::type::value;
template<class ClassToCheck, class OperatorType>
__LL_VAR_INLINE__ constexpr ll_bool_t has_simple_type_const_operator_v =
	signature::has_type_operator<ClassToCheck, OperatorType, OperatorType(T_Class<ClassToCheck>::*)() const noexcept>::type::value;

} // namespace signature

#pragma endregion
#pragma region Signature
namespace signature {

#define __LL_HAS_CUSTOM_FUNCTION_NAMED__(name, functionname)															\
	template<class _ClassToCheck, class _Signature>																		\
	struct _has_##name##_function {																						\
		using _MyType		= _has_##name##_function;																	\
		using ClassToCheck	= _ClassToCheck;																			\
		using Signature		= _Signature;																				\
		template<_Signature SIG>																						\
		using checker		= traits::SignatureChecker<_ClassToCheck, _Signature, SIG>;									\
		template<class _U>																								\
		static constexpr auto test(checker<&_U::##functionname##>*) noexcept	-> std::true_type;						\
		template<class _U> static constexpr auto test(...) noexcept				-> std::false_type;						\
	};																													\
	template<class ClassToCheck, class Signature>																		\
	using has_##name##_function =																						\
		traits::__traits__::has_common_signature<traits::signature::_has_##name##_function<ClassToCheck, Signature>>;	\
	template<class ClassToCheck, class Signature>																		\
	using has_##name##_function_t =																						\
		traits::signature::has_##name##_function<ClassToCheck, Signature>::type;										\
	template<class ClassToCheck, class Signature>																		\
	__LL_VAR_INLINE__ constexpr ll_bool_t has_##name##_function_v =														\
		traits::signature::has_##name##_function_t<ClassToCheck, Signature>::value

#define __LL_HAS_CUSTOM_FUNCTION__(name) __LL_HAS_CUSTOM_FUNCTION_NAMED__(name, name)

//////////////////////////////////////////////////////////////////////
// Do not change - Autogenerated with __LL_HAS_CUSTOM_FUNCTION__	//
// 	macros and visual studio										//
//////////////////////////////////////////////////////////////////////

#define __LL_EASY_CUSTOM_FUNCTION_ALL_1 \
	__LL_HAS_CUSTOM_FUNCTION__(hash); \
	__LL_HAS_CUSTOM_FUNCTION__(clear); \
	__LL_HAS_CUSTOM_FUNCTION__(swap); \
	__LL_HAS_CUSTOM_FUNCTION__(copy); \
	__LL_HAS_CUSTOM_FUNCTION__(move); \
	__LL_HAS_CUSTOM_FUNCTION__(compare); \
	__LL_HAS_CUSTOM_FUNCTION__(compareBool)

#define __LL_EASY_CUSTOM_FUNCTION_ALL_2 \
	__LL_HAS_CUSTOM_FUNCTION__(predestruction); \
	__LL_HAS_CUSTOM_FUNCTION__(nodeChecker); \
	__LL_HAS_CUSTOM_FUNCTION__(compareNode); \
	__LL_HAS_CUSTOM_FUNCTION__(compare_eq); \
	__LL_HAS_CUSTOM_FUNCTION__(compare_no_eq)

#define __LL_EASY_CUSTOM_FUNCTION_ALL_3 \
	__LL_HAS_CUSTOM_FUNCTION__(die); \
	__LL_HAS_CUSTOM_FUNCTION__(combine); \
	__LL_HAS_CUSTOM_FUNCTION__(compare_strong); \
	__LL_HAS_CUSTOM_FUNCTION__(begin); \
	__LL_HAS_CUSTOM_FUNCTION__(size)

#define __LL_EASY_CUSTOM_OPERATOR_ALL_1 \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(operator_eq, operator==); \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(operator_no_eq, operator!=); \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(operator_greater, operator>); \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(operator_lower, operator<); \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(operator_eq_greater, operator>=)

#define __LL_EASY_CUSTOM_OPERATOR_ALL_2 \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(operator_eq_lower, operator<=); \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(sgtrong_ordening, operator<=>); \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(operator_pointer, operator*); \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(operator_increment, operator++); \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(operator_decrement, operator--)

#define __LL_EASY_CUSTOM_OPERATOR_ALL_3 \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(bitwise_and, operator&); \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(bitwise_or, operator|); \
	__LL_HAS_CUSTOM_FUNCTION_NAMED__(bitwise_xor, operator^)

#pragma region AllSignatures

//__LL_EASY_CUSTOM_FUNCTION_ALL_1;
//__LL_EASY_CUSTOM_FUNCTION_ALL_2;
//__LL_EASY_CUSTOM_FUNCTION_ALL_3;
//__LL_EASY_CUSTOM_OPERATOR_ALL_1;
//__LL_EASY_CUSTOM_OPERATOR_ALL_2;
//__LL_EASY_CUSTOM_OPERATOR_ALL_3;

template<class _ClassToCheck, class _Signature> struct _has_hash_function {
	using _MyType = _has_hash_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::hash>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_hash_function = traits::__traits__::has_common_signature<traits::signature::_has_hash_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_hash_function_t = traits::signature::has_hash_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_hash_function_v = traits::signature::has_hash_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_clear_function {
	using _MyType = _has_clear_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::clear>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_clear_function = traits::__traits__::has_common_signature<traits::signature::_has_clear_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_clear_function_t = traits::signature::has_clear_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_clear_function_v = traits::signature::has_clear_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_swap_function {
	using _MyType = _has_swap_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::swap>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_swap_function = traits::__traits__::has_common_signature<traits::signature::_has_swap_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_swap_function_t = traits::signature::has_swap_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_swap_function_v = traits::signature::has_swap_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_copy_function {
	using _MyType = _has_copy_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::copy>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_copy_function = traits::__traits__::has_common_signature<traits::signature::_has_copy_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_copy_function_t = traits::signature::has_copy_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_copy_function_v = traits::signature::has_copy_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_move_function {
	using _MyType = _has_move_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::move>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_move_function = traits::__traits__::has_common_signature<traits::signature::_has_move_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_move_function_t = traits::signature::has_move_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_move_function_v = traits::signature::has_move_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_compare_function {
	using _MyType = _has_compare_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::compare>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_compare_function = traits::__traits__::has_common_signature<traits::signature::_has_compare_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_compare_function_t = traits::signature::has_compare_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_compare_function_v = traits::signature::has_compare_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_compareBool_function {
	using _MyType = _has_compareBool_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::compareBool>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_compareBool_function = traits::__traits__::has_common_signature<traits::signature::_has_compareBool_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_compareBool_function_t = traits::signature::has_compareBool_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_compareBool_function_v = traits::signature::has_compareBool_function_t<ClassToCheck, Signature>::value;
template<class _ClassToCheck, class _Signature> struct _has_predestruction_function {
	using _MyType = _has_predestruction_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::predestruction>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_predestruction_function = traits::__traits__::has_common_signature<traits::signature::_has_predestruction_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_predestruction_function_t = traits::signature::has_predestruction_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_predestruction_function_v = traits::signature::has_predestruction_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_nodeChecker_function {
	using _MyType = _has_nodeChecker_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::nodeChecker>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_nodeChecker_function = traits::__traits__::has_common_signature<traits::signature::_has_nodeChecker_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_nodeChecker_function_t = traits::signature::has_nodeChecker_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_nodeChecker_function_v = traits::signature::has_nodeChecker_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_compareNode_function {
	using _MyType = _has_compareNode_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::compareNode>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_compareNode_function = traits::__traits__::has_common_signature<traits::signature::_has_compareNode_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_compareNode_function_t = traits::signature::has_compareNode_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_compareNode_function_v = traits::signature::has_compareNode_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_compare_eq_function {
	using _MyType = _has_compare_eq_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::compare_eq>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_compare_eq_function = traits::__traits__::has_common_signature<traits::signature::_has_compare_eq_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_compare_eq_function_t = traits::signature::has_compare_eq_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_compare_eq_function_v = traits::signature::has_compare_eq_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_compare_no_eq_function {
	using _MyType = _has_compare_no_eq_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::compare_no_eq>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_compare_no_eq_function = traits::__traits__::has_common_signature<traits::signature::_has_compare_no_eq_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_compare_no_eq_function_t = traits::signature::has_compare_no_eq_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_compare_no_eq_function_v = traits::signature::has_compare_no_eq_function_t<ClassToCheck, Signature>::value;
template<class _ClassToCheck, class _Signature> struct _has_die_function {
	using _MyType = _has_die_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::die>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_die_function = traits::__traits__::has_common_signature<traits::signature::_has_die_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_die_function_t = traits::signature::has_die_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_die_function_v = traits::signature::has_die_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_combine_function {
	using _MyType = _has_combine_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::combine>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_combine_function = traits::__traits__::has_common_signature<traits::signature::_has_combine_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_combine_function_t = traits::signature::has_combine_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_combine_function_v = traits::signature::has_combine_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_compare_strong_function {
	using _MyType = _has_compare_strong_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::compare_strong>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_compare_strong_function = traits::__traits__::has_common_signature<traits::signature::_has_compare_strong_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_compare_strong_function_t = traits::signature::has_compare_strong_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_compare_strong_function_v = traits::signature::has_compare_strong_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_begin_function {
	using _MyType = _has_begin_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::begin>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_begin_function = traits::__traits__::has_common_signature<traits::signature::_has_begin_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_begin_function_t = traits::signature::has_begin_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_begin_function_v = traits::signature::has_begin_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_size_function {
	using _MyType = _has_size_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::size>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_size_function = traits::__traits__::has_common_signature<traits::signature::_has_size_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_size_function_t = traits::signature::has_size_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_size_function_v = traits::signature::has_size_function_t<ClassToCheck, Signature>::value;

template<class _ClassToCheck, class _Signature> struct _has_operator_eq_function {
	using _MyType = _has_operator_eq_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator==>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_operator_eq_function = traits::__traits__::has_common_signature<traits::signature::_has_operator_eq_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_operator_eq_function_t = traits::signature::has_operator_eq_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_operator_eq_function_v = traits::signature::has_operator_eq_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_operator_no_eq_function {
	using _MyType = _has_operator_no_eq_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator!=>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_operator_no_eq_function = traits::__traits__::has_common_signature<traits::signature::_has_operator_no_eq_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_operator_no_eq_function_t = traits::signature::has_operator_no_eq_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_operator_no_eq_function_v = traits::signature::has_operator_no_eq_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_operator_greater_function {
	using _MyType = _has_operator_greater_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator>>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_operator_greater_function = traits::__traits__::has_common_signature<traits::signature::_has_operator_greater_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_operator_greater_function_t = traits::signature::has_operator_greater_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_operator_greater_function_v = traits::signature::has_operator_greater_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_operator_lower_function {
	using _MyType = _has_operator_lower_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator<>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_operator_lower_function = traits::__traits__::has_common_signature<traits::signature::_has_operator_lower_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_operator_lower_function_t = traits::signature::has_operator_lower_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_operator_lower_function_v = traits::signature::has_operator_lower_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_operator_eq_greater_function {
	using _MyType = _has_operator_eq_greater_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator>=>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_operator_eq_greater_function = traits::__traits__::has_common_signature<traits::signature::_has_operator_eq_greater_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_operator_eq_greater_function_t = traits::signature::has_operator_eq_greater_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_operator_eq_greater_function_v = traits::signature::has_operator_eq_greater_function_t<ClassToCheck, Signature>::value;
template<class _ClassToCheck, class _Signature> struct _has_operator_eq_lower_function {
	using _MyType = _has_operator_eq_lower_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator<=>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_operator_eq_lower_function = traits::__traits__::has_common_signature<traits::signature::_has_operator_eq_lower_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_operator_eq_lower_function_t = traits::signature::has_operator_eq_lower_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_operator_eq_lower_function_v = traits::signature::has_operator_eq_lower_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_sgtrong_ordening_function {
	using _MyType = _has_sgtrong_ordening_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator<=>>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_sgtrong_ordening_function = traits::__traits__::has_common_signature<traits::signature::_has_sgtrong_ordening_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_sgtrong_ordening_function_t = traits::signature::has_sgtrong_ordening_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_sgtrong_ordening_function_v = traits::signature::has_sgtrong_ordening_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_operator_pointer_function {
	using _MyType = _has_operator_pointer_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator*>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_operator_pointer_function = traits::__traits__::has_common_signature<traits::signature::_has_operator_pointer_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_operator_pointer_function_t = traits::signature::has_operator_pointer_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_operator_pointer_function_v = traits::signature::has_operator_pointer_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_operator_increment_function {
	using _MyType = _has_operator_increment_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator++>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_operator_increment_function = traits::__traits__::has_common_signature<traits::signature::_has_operator_increment_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_operator_increment_function_t = traits::signature::has_operator_increment_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_operator_increment_function_v = traits::signature::has_operator_increment_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_operator_decrement_function {
	using _MyType = _has_operator_decrement_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator-->*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_operator_decrement_function = traits::__traits__::has_common_signature<traits::signature::_has_operator_decrement_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_operator_decrement_function_t = traits::signature::has_operator_decrement_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_operator_decrement_function_v = traits::signature::has_operator_decrement_function_t<ClassToCheck, Signature>::value;

template<class _ClassToCheck, class _Signature> struct _has_bitwise_and_function {
	using _MyType = _has_bitwise_and_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator&>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_bitwise_and_function = traits::__traits__::has_common_signature<traits::signature::_has_bitwise_and_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_bitwise_and_function_t = traits::signature::has_bitwise_and_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_bitwise_and_function_v = traits::signature::has_bitwise_and_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_bitwise_or_function {
	using _MyType = _has_bitwise_or_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator|>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_bitwise_or_function = traits::__traits__::has_common_signature<traits::signature::_has_bitwise_or_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_bitwise_or_function_t = traits::signature::has_bitwise_or_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_bitwise_or_function_v = traits::signature::has_bitwise_or_function_t<ClassToCheck, Signature>::value; template<class _ClassToCheck, class _Signature> struct _has_bitwise_xor_function {
	using _MyType = _has_bitwise_xor_function; using ClassToCheck = _ClassToCheck; using Signature = _Signature; template<_Signature SIG> using checker = traits::SignatureChecker<_ClassToCheck, _Signature, SIG>; template<class _U> static constexpr auto test(checker<&_U::operator^>*) noexcept -> std::true_type; template<class _U> static constexpr auto test(...) noexcept -> std::false_type;
}; template<class ClassToCheck, class Signature> using has_bitwise_xor_function = traits::__traits__::has_common_signature<traits::signature::_has_bitwise_xor_function<ClassToCheck, Signature>>; template<class ClassToCheck, class Signature> using has_bitwise_xor_function_t = traits::signature::has_bitwise_xor_function<ClassToCheck, Signature>::type; template<class ClassToCheck, class Signature> inline constexpr ll_bool_t has_bitwise_xor_function_v = traits::signature::has_bitwise_xor_function_t<ClassToCheck, Signature>::value;

#pragma endregion

template<class ClassToCheck>
__LL_VAR_INLINE__ constexpr ll_bool_t has_simple_clear_function_v =
	traits::signature::has_clear_function_v<ClassToCheck, void(ClassToCheck::*)() noexcept>;

#undef __LL_EASY_CUSTOM_FUNCTION_ALL_1
#undef __LL_EASY_CUSTOM_FUNCTION_ALL_2
#undef __LL_EASY_CUSTOM_FUNCTION_ALL_3
#undef __LL_EASY_CUSTOM_OPERATOR_ALL_1
#undef __LL_EASY_CUSTOM_OPERATOR_ALL_2
#undef __LL_EASY_CUSTOM_OPERATOR_ALL_3

} // namespace signature

#pragma endregion
#pragma region ReturnDetection
namespace return_detection {

#define __LL_RETURN_FUNCTION_NAMED__(name, functionname)														\
	template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args>						\
	struct return_##name##_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {			\
		using _MyType		= return_##name##_function;															\
		using return_common	= __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>;					\
		using ClassToCheck	= _ClassToCheck;																	\
		using type = decltype(return_common::test<int>(&ClassToCheck::##functionname##));						\
	};																											\
	template<class ClassToCheck,																				\
		meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC,										\
		class... Args																							\
	>																											\
	using return_##name##_function_t =																			\
		return_##name##_function<ClassToCheck, ATTRIBUTES, Args...>::type

#define __LL_EASY_CUSTOM_FUNCTION_ALL_1 \
	__LL_RETURN_FUNCTION_NAMED__(begin, begin); \
	__LL_RETURN_FUNCTION_NAMED__(fill, fill); \
	__LL_RETURN_FUNCTION_NAMED__(hash, hash)

#define __LL_EASY_CUSTOM_OPERATOR_ALL_1 \
	__LL_RETURN_FUNCTION_NAMED__(operator_eq, operator==); \
	__LL_RETURN_FUNCTION_NAMED__(operator_no_eq, operator!=); \
	__LL_RETURN_FUNCTION_NAMED__(operator_greater, operator>); \
	__LL_RETURN_FUNCTION_NAMED__(operator_lower, operator<); \
	__LL_RETURN_FUNCTION_NAMED__(operator_eq_greater, operator>=)

#define __LL_EASY_CUSTOM_OPERATOR_ALL_2 \
	__LL_RETURN_FUNCTION_NAMED__(operator_eq_lower, operator<=); \
	__LL_RETURN_FUNCTION_NAMED__(sgtrong_ordening, operator<=>); \
	__LL_RETURN_FUNCTION_NAMED__(operator_pointer, operator*); \
	__LL_RETURN_FUNCTION_NAMED__(operator_arrow, operator->); \
	__LL_RETURN_FUNCTION_NAMED__(operator_increment, operator++); \
	__LL_RETURN_FUNCTION_NAMED__(operator_decrement, operator--)

#define __LL_EASY_CUSTOM_OPERATOR_ALL_3 \
	__LL_RETURN_FUNCTION_NAMED__(bitwise_and, operator&); \
	__LL_RETURN_FUNCTION_NAMED__(bitwise_or, operator|); \
	__LL_RETURN_FUNCTION_NAMED__(bitwise_xor, operator^)

#pragma region AllSignatures
//__LL_EASY_CUSTOM_FUNCTION_ALL_1;
//__LL_EASY_CUSTOM_OPERATOR_ALL_1;
//__LL_EASY_CUSTOM_OPERATOR_ALL_2;
//__LL_EASY_CUSTOM_OPERATOR_ALL_3;

template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_begin_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_begin_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::begin));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_begin_function_t = return_begin_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_fill_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_fill_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::fill));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_fill_function_t = return_fill_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_hash_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_hash_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::hash));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_hash_function_t = return_hash_function<ClassToCheck, ATTRIBUTES, Args...>::type;

template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_operator_eq_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_operator_eq_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator==));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_operator_eq_function_t = return_operator_eq_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_operator_no_eq_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_operator_no_eq_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator!=));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_operator_no_eq_function_t = return_operator_no_eq_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_operator_greater_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_operator_greater_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator>));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_operator_greater_function_t = return_operator_greater_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_operator_lower_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_operator_lower_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator<));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_operator_lower_function_t = return_operator_lower_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_operator_eq_greater_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_operator_eq_greater_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator>=));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_operator_eq_greater_function_t = return_operator_eq_greater_function<ClassToCheck, ATTRIBUTES, Args...>::type;

template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_operator_eq_lower_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_operator_eq_lower_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator<=));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_operator_eq_lower_function_t = return_operator_eq_lower_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_sgtrong_ordening_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_sgtrong_ordening_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator<=>));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_sgtrong_ordening_function_t = return_sgtrong_ordening_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_operator_pointer_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_operator_pointer_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator*));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_operator_pointer_function_t = return_operator_pointer_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_operator_arrow_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_operator_arrow_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator->));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_operator_arrow_function_t = return_operator_arrow_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_operator_increment_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_operator_increment_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator++));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_operator_increment_function_t = return_operator_increment_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_operator_decrement_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_operator_decrement_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator--));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_operator_decrement_function_t = return_operator_decrement_function<ClassToCheck, ATTRIBUTES, Args...>::type;

template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_bitwise_and_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_bitwise_and_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator&));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_bitwise_and_function_t = return_bitwise_and_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_bitwise_or_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_bitwise_or_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator|));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_bitwise_or_function_t = return_bitwise_or_function<ClassToCheck, ATTRIBUTES, Args...>::type; template<class _ClassToCheck, meta::function_attributes_t _ATTRIBUTES, class... Args> struct return_bitwise_xor_function : __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...> {
	using _MyType = return_bitwise_xor_function; using return_common = __traits__::return_common<_ClassToCheck, _ATTRIBUTES, Args...>; using ClassToCheck = _ClassToCheck; using type = decltype(return_common::test<int>(&ClassToCheck::operator^));
}; template<class ClassToCheck, meta::function_attributes_t ATTRIBUTES = meta::functional::CLASSIC, class... Args > using return_bitwise_xor_function_t = return_bitwise_xor_function<ClassToCheck, ATTRIBUTES, Args...>::type;

#pragma endregion

template<class T, class U>
using return_sgtrong_ordening_function_easy_t =
	traits::return_detection::return_sgtrong_ordening_function_t<T, meta::functional::NOEXCEPTION, U>;

#undef __LL_EASY_CUSTOM_FUNCTION_ALL_1
#undef __LL_EASY_CUSTOM_OPERATOR_ALL_1
#undef __LL_EASY_CUSTOM_OPERATOR_ALL_2
#undef __LL_EASY_CUSTOM_OPERATOR_ALL_3

} // namespace return_detection

#pragma endregion

template<class Object, class T, ll_bool_t IS_CONST = llcpp::FALSE>
__LL_VAR_INLINE__ constexpr ll_bool_t is_container =
	traits::signature::has_operator_pointer_function_v<Object, traits::conditional_t<IS_CONST, const T&(Object::*)() const noexcept, T& (Object::*)() noexcept>>;
template<class Object, class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_container =
	traits::is_container<Object, T, llcpp::TRUE> || traits::is_container<Object, T, llcpp::FALSE>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSSIGNATURE_HPP_
