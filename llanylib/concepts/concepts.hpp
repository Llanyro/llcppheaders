//////////////////////////////////////////////
//	concepts.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CONCEPTS_INCOMPLETE_HPP_)
	#if LLANYLIB_CONCEPTS_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_CONCEPTS_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "concepts.hpp(incomplete) version error!"
		#else
			#error "concepts.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONCEPTS_INCOMPLETE_MAYOR_ || LLANYLIB_CONCEPTS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CONCEPTS_INCOMPLETE_HPP_)
	#define LLANYLIB_CONCEPTS_INCOMPLETE_HPP_
	#define LLANYLIB_CONCEPTS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_CONCEPTS_INCOMPLETE_MINOR_ 0

#include <llanylib/traits_base/type_traits_extended.hpp>

namespace llcpp {
namespace meta {
namespace concepts {
namespace base {

template<ll_bool_t VALUE>
concept IsValidConcept = VALUE;

template<class T, class U>
concept FristBiggerSize		= sizeof(T) > sizeof(U);
template<class T, class U>
concept FristSmallerSize	= sizeof(T) < sizeof(U);
template<class T, class U>
concept EqualSize			= sizeof(T) == sizeof(U);

} // namespace base
} // namespace concepts
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_CONCEPTS_HPP_)
	#if LLANYLIB_CONCEPTS_MAYOR_ != 12 || LLANYLIB_CONCEPTS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "concepts.hpp version error!"
		#else
			#error "concepts.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONCEPTS_MAYOR_ || LLANYLIB_CONCEPTS_MINOR_

#else
	#define LLANYLIB_CONCEPTS_HPP_
	#define LLANYLIB_CONCEPTS_MAYOR_ 12
	#define LLANYLIB_CONCEPTS_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/traits_base/type_traits_extended.hpp>
#else
	#include "../traits_base/type_traits_extended.hpp"
#endif // LL_LIB_PATHS

#if defined(__LL_WINDOWS_SYSTEM)
	#include <concepts>
#elif defined(__LL_MINGW)
	#include <concepts>
	#include <utility>
#elif defined(__LL_POSIX_SYSTEM)
#elif defined(__LL_UNIX_SYSTEM)
#else
#endif // __LL_WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace concepts {
namespace base {

template<ll_bool_t VALUE>
concept IsValidConcept = VALUE;

__LL_VAR_INLINE__ constexpr ll_bool_t STRICT_CONVERTIBLE			= __LL_STRICT_CONVERTIBLE;
__LL_VAR_INLINE__ constexpr ll_bool_t STRICT_CONVERTIBLE_OPERATOR	= __LL_STRICT_CONVERTIBLE_OPERATOR;
__LL_VAR_INLINE__ constexpr ll_bool_t STRICT_VALID_FUNCTIONS		= __LL_STRICT_VALID_FUNCTIONS;
__LL_VAR_INLINE__ constexpr ll_bool_t STRICT_GENERIC_FUNCTIONS		= __LL_STRICT_GENERIC_FUNCTIONS;

enum class ConvertibleMode : u8 {
	Default,
	Operator,
	ValidFunctions,
	GenericFunctions,

	Strict,
	Soft
};

template<class T, class U, ll_bool_t STRICT>
__LL_VAR_INLINE__ constexpr ll_bool_t flexible_convertible_v = ::llcpp::meta::traits::conditional_value_simple_v<
	STRICT, ll_bool_t,
	::std::is_same_v<T, U> && ::std::is_same_v<U, T>,
	std::is_convertible_v<T, U>
>;

// If T is and empty type, this returns true always
// If not, it depends of strict mode
template<class U, class T, ::llcpp::meta::concepts::base::ConvertibleMode MODE>
__LL_NODISCARD__ constexpr ll_bool_t is_same_or_void() noexcept {
	if constexpr (::llcpp::meta::traits::is_empty_object_v<T>)
		return ::llcpp::LL_TRUE;
	
	else if constexpr (MODE == ::llcpp::meta::concepts::base::ConvertibleMode::Default)
		return ::llcpp::meta::concepts::base::flexible_convertible_v<U, T, ::llcpp::meta::concepts::base::STRICT_CONVERTIBLE>;
	else if constexpr (MODE == ::llcpp::meta::concepts::base::ConvertibleMode::Operator)
		return ::llcpp::meta::concepts::base::flexible_convertible_v<U, T, ::llcpp::meta::concepts::base::STRICT_CONVERTIBLE_OPERATOR>;
	else if constexpr (MODE == ::llcpp::meta::concepts::base::ConvertibleMode::ValidFunctions)
		return ::llcpp::meta::concepts::base::flexible_convertible_v<U, T, ::llcpp::meta::concepts::base::STRICT_VALID_FUNCTIONS>;
	else if constexpr (MODE == ::llcpp::meta::concepts::base::ConvertibleMode::GenericFunctions)
		return ::llcpp::meta::concepts::base::flexible_convertible_v<U, T, ::llcpp::meta::concepts::base::STRICT_GENERIC_FUNCTIONS>;


	else if constexpr (MODE == ::llcpp::meta::concepts::base::ConvertibleMode::Strict)
		return ::llcpp::meta::concepts::base::flexible_convertible_v<U, T, ::llcpp::LL_TRUE>;
	else if constexpr (MODE == ::llcpp::meta::concepts::base::ConvertibleMode::Soft) {
		return ::llcpp::meta::concepts::base::flexible_convertible_v<U, T, ::llcpp::LL_FALSE>;
	}
	else {
		static_assert(MODE == ::llcpp::meta::concepts::base::ConvertibleMode::Soft,
			"No valid mode for this check!");
		return ::llcpp::LL_FALSE;
	}
}

// Checks if U type is void/EmptyClass
// If is void return true
// Else return true if U is same type as T
template<class U, class T>
concept IsDefaultSameOrVoid = ::llcpp::meta::concepts::base::is_same_or_void<
	U, T, ::llcpp::meta::concepts::base::ConvertibleMode::Default>();
template<class U, class T>
concept IsOperatorSameOrVoid = ::llcpp::meta::concepts::base::is_same_or_void<
	U, T, ::llcpp::meta::concepts::base::ConvertibleMode::Operator>();
template<class U, class T>
concept IsValidFunctionsSameOrVoid = ::llcpp::meta::concepts::base::is_same_or_void<
	U, T, ::llcpp::meta::concepts::base::ConvertibleMode::ValidFunctions>();
template<class U, class T>
concept IsGenericFunctionsSameOrVoid = ::llcpp::meta::concepts::base::is_same_or_void<
	U, T, ::llcpp::meta::concepts::base::ConvertibleMode::GenericFunctions>();

template<class U, class T>
concept IsStrictSameOrVoid = ::llcpp::meta::concepts::base::is_same_or_void<
	U, T, ::llcpp::meta::concepts::base::ConvertibleMode::Strict>();
template<class U, class T>
concept IsSoftSameOrVoid = ::llcpp::meta::concepts::base::is_same_or_void<
	U, T, ::llcpp::meta::concepts::base::ConvertibleMode::Soft>();

template<class U, class T, ll_bool_t IS_STRICT = ::llcpp::LL_TRUE>
concept IsStrictSelectionSameOrVoid = ::llcpp::meta::traits::conditional_value_simple_v<
	IS_STRICT, ll_bool_t,
	::llcpp::meta::concepts::base::IsStrictSameOrVoid<U, T>,
	::llcpp::meta::concepts::base::IsSoftSameOrVoid<U, T>
>;

template<class T, class U>
concept FristBiggerSize				= sizeof(T) > sizeof(U);
template<class T, class U>
concept FristSmallerSize			= sizeof(T) < sizeof(U);
template<class T, class U>
concept EqualSize					= sizeof(T) == sizeof(U);
template<class _From, class _To>
concept ConvertibleTo				= requires { static_cast<_To>(::std::declval<_From>()); };

template<class T>
concept HasValueType				= ::llcpp::meta::traits::has_value_type_v<T>;
template<class T>
concept HasValueConstant			= ::llcpp::meta::traits::has_value_constant_v<T>;
template<class T>
concept IsIntegralConstantContainer	= ::llcpp::meta::traits::is_valid_integral_constant_container_v<T>;

template<class T>
concept HasHashType					= ::llcpp::meta::traits::has_hash_type_v<T>;

template<class T>
concept HasPairFirst				= ::llcpp::meta::traits::has_pair_first_v<T>;
template<class T>
concept HasPairSecond				= ::llcpp::meta::traits::has_pair_second_v<T>;
template<class T>
concept IsPairStructure				= ::llcpp::meta::traits::is_pair_v<T>;

template<class Unit, Unit VALUE>
concept ZeroValue					= ::llcpp::meta::traits::is_zero_value_v<Unit, VALUE>;
template<class Unit, Unit VALUE>
concept NonZeroValue				= ::llcpp::meta::traits::is_non_zero_value_v<Unit, VALUE>;
template<class Unit, Unit VALUE>
concept NonMaxValue					= ::llcpp::meta::traits::is_max_value_v<Unit, VALUE>;
template<class Unit, Unit VALUE>
concept NonMinValue					= ::llcpp::meta::traits::is_min_value_v<Unit, VALUE>;

template<class T>
concept IsAlwaysValid				= ::std::is_base_of_v<::llcpp::AlwaysValidTag, T>;
template<class T>
concept IsAlwaysInvalid				= ::std::is_base_of_v<::llcpp::AlwaysInvalidTag, T>;

template<class T, ll_bool_t IGNORE_SIGNED = ::llcpp::LL_FALSE, ll_bool_t IGNORE_UNSIGNED = ::llcpp::LL_FALSE>
concept IsCharType = requires {
	requires IGNORE_SIGNED		|| ::llcpp::meta::traits::is_any_of_v<T, __LL_INTEGRAL_CHAR_TYPES>;
	requires IGNORE_UNSIGNED	|| ::llcpp::meta::traits::is_any_of_v<T, ll_uchar_t>;
};

} // namespace base
namespace signature {

// Some objects uses this operator and expects a throw if parameter is invalid
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorArray = requires (T t) {
	{ t[0] } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>;
};
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorArrayExcept = requires (T t) {
	{ t[0] } -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>;
};

template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorSquareBrackets = ::llcpp::meta::concepts::signature::HasOperatorArray<T, ReturnType>;
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorSquareBracketsExcept = ::llcpp::meta::concepts::signature::HasOperatorArrayExcept<T, ReturnType>;

template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasPointerOperator = requires (T t) { { *t } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>; };

template<class T, class ArrayType = ll_string_t, class SizeType = usize, class ReturnType = ::llcpp::Emptyclass>
concept HasHashArray = requires (T t, ArrayType arr, SizeType s) {
	{ t.hash(arr, s) } noexcept -> ::llcpp::meta::concepts::base::IsSoftSameOrVoid<ReturnType>;
};
template<class Iterator1, class Iterator2, class ReturnType = isize>
concept HasDistance = requires (Iterator1 it, Iterator2 iu) {
	{ it.distance(iu) } noexcept -> ::llcpp::meta::concepts::base::IsSoftSameOrVoid<ReturnType>;
};

template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasForeachOperation = requires (T t, U u) {
	{ t.foreachOperation(u) } noexcept -> ::llcpp::meta::concepts::base::IsSoftSameOrVoid<ReturnType>;
};
template<class T, class U, class W, class ReturnType = ::llcpp::Emptyclass>
concept HasForeachOperationExtra = requires (T t, U u, W w) {
	{ t.foreachOperation(u, w) } noexcept -> ::llcpp::meta::concepts::base::IsSoftSameOrVoid<ReturnType>;
};

template<class T, class U = T, class ReturnType = T&>
concept HasCopyAssignable = requires (T t, const U u) {
	{ t = ::std::forward<const U&>(u) } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>;
};
template<class T, class U = T, class ReturnType = T&>
concept HasMoveAssignable = requires (T t, U u) {
	{ t = ::std::forward<U&&>(u) } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>;
};

#pragma region EditOperators
#pragma region SimpleMode
template<class T, class ReturnType = T&>
concept HasPreIncrement = requires (T t) { { ++t } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class ReturnType = T>
concept HasPosIncrement = requires (T t) { { t++ } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class U, class ReturnType = T>
concept HasOperatorSum = requires (T t, U u) { { t + u } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class U, class ReturnType = T>
concept HasOperatorSub = requires (T t, U u) { { t - u } noexcept -> ::std::same_as<ReturnType>; };

template<class T, class U = u8, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseLeft = requires(T t, U u) {
	{ t << u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>;
};
template<class T, class U = u8, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseRight = requires(T t, U u) {
	{ t >> u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseAND = requires(T t, U u) {
	{ t & u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseOR = requires(T t, U u) {
	{ t | u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseXOR = requires(T t, U u) {
	{ t ^ u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorModulus = requires(T t, U u) {
	{ t % u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>;
};

#pragma endregion
#pragma region AssignMode
template<class T, class U, class ReturnType = T&>
concept HasOperatorSumAssign = requires (T t, U u) { { t += u } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class U, class ReturnType = T&>
concept HasOperatorSubAssign = requires (T t, U u) { { t -= u } noexcept -> ::std::same_as<ReturnType>; };

template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseLeftAssign = requires(T t, U u) {
	{ t <<= u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseRightAssign = requires(T t, U u) {
	{ t >>= u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseANDAssign = requires(T t, U u) {
	{ t &= u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseORAssign = requires(T t, U u) {
	{ t |= u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseXORAssign = requires(T t, U u) {
	{ t ^= u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorModulusAssign = requires(T t, U u) {
	{ t %= u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>;
};

#pragma endregion
#pragma region GenericCheckersSimpleMode
template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorSumWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorSum<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorSum<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorSubWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorSub<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorSub<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorBitwiseLeftWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorBitwiseLeft<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorBitwiseLeft<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorBitwiseRightWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorBitwiseRight<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorBitwiseRight<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorBitwiseANDWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorBitwiseAND<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorBitwiseAND<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorBitwiseXORWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorBitwiseXOR<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorBitwiseXOR<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorModulusWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorModulus<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorModulus<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

#pragma endregion
#pragma region GenericCheckersAssignMode
template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorSumAssignWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorSumAssign<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorSumAssign<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorSubAssignWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorSubAssign<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorSubAssign<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorBitwiseLefAssigntWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorBitwiseLeftAssign<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorBitwiseLeftAssign<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorBitwiseRightAssignWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorBitwiseRightAssign<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorBitwiseRightAssign<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorBitwiseANDAssignWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorBitwiseANDAssign<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorBitwiseANDAssign<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorBitwiseXORAssignWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorBitwiseXORAssign<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorBitwiseXORAssign<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasOperatorModulusAssignWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasOperatorModulusAssign<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasOperatorModulusAssign<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1

#pragma endregion
#pragma region SimpleModeWithPrimitives
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorSumWithPrimitives =
	::llcpp::meta::concepts::signature::HasOperatorSumWith<T, ReturnType, __LL_INTEGRAL_TYPES>;
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorSubWithPrimitives =
	::llcpp::meta::concepts::signature::HasOperatorSubWith<T, ReturnType, __LL_INTEGRAL_TYPES>;
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseLeftWithPrimitives =
	::llcpp::meta::concepts::signature::HasOperatorBitwiseLeftWith<T, ReturnType, __LL_INTEGRAL_TYPES>;
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseRightWithPrimitives =
	::llcpp::meta::concepts::signature::HasOperatorBitwiseRightWith<T, ReturnType, __LL_INTEGRAL_TYPES>;
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseANDWithPrimitives =
	::llcpp::meta::concepts::signature::HasOperatorBitwiseANDWith<T, ReturnType, __LL_INTEGRAL_TYPES>;
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseXORWithPrimitives =
	::llcpp::meta::concepts::signature::HasOperatorBitwiseXORWith<T, ReturnType, __LL_INTEGRAL_TYPES>;
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorModulusWithPrimitives =
	::llcpp::meta::concepts::signature::HasOperatorModulusWith<T, ReturnType, __LL_INTEGRAL_TYPES>;

#pragma endregion

#pragma endregion
#pragma region Comparations
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorEqual = requires (T t, U u) { { t == u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorNonEqual = requires (T t, U u) { { t != u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorGreaterEqual = requires (T t, U u) { { t >= u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorGreater = requires (T t, U u) { { t > u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorLowerEqual = requires (T t, U u) { { t <= u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorLower = requires (T t, U u) { { t < u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorThreeWay = requires (T t, U u) { { t <=> u } noexcept -> ::llcpp::meta::concepts::base::IsOperatorSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = i32>
concept HasCompare = requires (T t, U u) { { t.compare(u) } noexcept -> ::llcpp::meta::concepts::base::IsSoftSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasEquals = requires (T t, U u) { { t.equals(u) } noexcept -> ::llcpp::meta::concepts::base::IsSoftSameOrVoid<ReturnType>; };

#pragma endregion
#pragma region Lists
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasData = requires (T t) { { t.data() } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasBegin = requires (T t) { { t.begin() } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasReverseBegin = requires (T t) { { t.rbegin() } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasEnd = requires (T t) { { t.end() } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasReverseEnd = requires (T t) { { t.rend() } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>; };
template<class T>
concept HasListFunctions = requires {
	requires ::llcpp::meta::concepts::signature::HasBegin<T>;
	requires ::llcpp::meta::concepts::signature::HasReverseBegin<T>;
	requires ::llcpp::meta::concepts::signature::HasEnd<T>;
	requires ::llcpp::meta::concepts::signature::HasReverseEnd<T>;
};
template<class T, ll_bool_t IS_POINTER_ITERATOR = ::llcpp::LL_FALSE>
concept SameTypeBeginEnd = requires (T t) {
	requires ::llcpp::meta::concepts::signature::HasBegin<T>;
	requires ::llcpp::meta::concepts::signature::HasEnd<T>;
	requires ::std::is_same_v<
		::std::remove_cvref_t<decltype(t.begin())>,
		::std::remove_cvref_t<decltype(t.end())>
	>;
	//requires IS_POINTER_ITERATOR ||
};

#pragma endregion
template<class T, class ReturnType = ll_bool_t>
concept HasEmpty = requires (T t) { { t.empty() } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>; };
template<class T, class U = usize, class ReturnType = ll_bool_t>
concept HasInRange = requires (T t, U u) { { t.inRange(u) } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>; };

#pragma region Size
template<class T, class ReturnType = usize>
concept HasSize = requires (T t) { { t.size() } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>; };
template<class T, class... Args>
concept HasSizeWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasSize<T, Args> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasSize<T, Args>...>;
#endif // __LL_REAL_CXX17 == 1
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasSizeWithPrimitives = ::llcpp::meta::concepts::signature::HasSizeWith<T, ReturnType, __LL_INTEGRAL_TYPES>;

#pragma endregion
#pragma region MaxSize
template<class T, class ReturnType = usize>
concept HasMaxSize = requires (T t) { { t.max_size() } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>; };
template<class T, class ReturnType = usize, class... Args>
concept HasMaxSizeWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasMaxSize<T, Args> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasMaxSize<T, Args>...>;
#endif // __LL_REAL_CXX17 == 1
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasMaxSizeWithPrimitives = ::llcpp::meta::concepts::signature::HasMaxSizeWith<T, ReturnType, __LL_INTEGRAL_TYPES>;

#pragma endregion

} // namespace signature
namespace is_object {

template<class T>
concept IsConstantContainer = requires {
	requires ::llcpp::meta::concepts::base::HasValueType<T>;
	requires ::llcpp::meta::concepts::base::HasValueConstant<T>;
};

template<class Iterator, class Content = ::llcpp::Emptyclass>
concept IsIterator = requires (Iterator it) {
	requires ::llcpp::meta::concepts::signature::HasPointerOperator<Iterator, Content>;
	requires ::llcpp::meta::concepts::signature::HasPreIncrement<Iterator>;
	requires ::llcpp::meta::concepts::signature::HasPreIncrement<Iterator>;
	requires ::llcpp::meta::concepts::signature::HasPosIncrement<Iterator>;
	requires ::llcpp::meta::concepts::signature::HasOperatorSum<Iterator, isize>;
	requires ::llcpp::meta::concepts::signature::HasOperatorSub<Iterator, isize>;
	requires ::llcpp::meta::concepts::signature::HasOperatorSumAssign<Iterator, isize>;
	requires ::llcpp::meta::concepts::signature::HasOperatorSubAssign<Iterator, isize>;
};

template<class Array, class Content = ::llcpp::Emptyclass>
concept IsArray = requires (Array arr) {
	requires ::llcpp::meta::concepts::signature::HasOperatorArray<Array, Content>;
};
template<class Array, class Content = ::llcpp::Emptyclass>
concept IsArrayObject = requires (Array arr) {
	requires ::llcpp::meta::concepts::is_object::IsArray<Array, Content>;
	requires ::llcpp::meta::concepts::signature::HasBegin<Array>;
	requires ::llcpp::meta::concepts::signature::HasBegin<const Array>;
	requires ::llcpp::meta::concepts::signature::HasReverseBegin<Array>;
	requires ::llcpp::meta::concepts::signature::HasEnd<Array>;
	requires ::llcpp::meta::concepts::signature::HasEnd<const Array>;
	requires ::llcpp::meta::concepts::signature::HasReverseEnd<Array>;
	requires ::llcpp::meta::concepts::signature::HasSize<Array>;
	requires ::llcpp::meta::concepts::signature::HasMaxSize<Array>;
	requires ::llcpp::meta::concepts::signature::HasEmpty<Array>;
};
template<class Array, class Content = ::llcpp::Emptyclass>
concept IsConstArrayObject = requires (Array arr) {
	requires ::llcpp::meta::concepts::is_object::IsArray<Array, Content>;
	requires ::llcpp::meta::concepts::signature::HasBegin<const Array>;
	requires ::llcpp::meta::concepts::signature::HasEnd<const Array>;
	requires ::llcpp::meta::concepts::signature::HasSize<Array>;
	requires ::llcpp::meta::concepts::signature::HasMaxSize<Array>;
	requires ::llcpp::meta::concepts::signature::HasEmpty<Array>;
};

} // namespace is_object
} // namespace concepts
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CONCEPTS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
