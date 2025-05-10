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

#include "../traits_base/type_traits_extended.hpp"

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

#include "../traits_base/type_traits_extended.hpp"

#include <concepts>

namespace llcpp {
namespace meta {
namespace concepts {
namespace base {

template<ll_bool_t VALUE>
concept IsValidConcept = VALUE;

// Checks if U type is void/EmptyClass
// If is void return trur
// Else return true if U is same type as T
template<class U, class T>
concept IsSameOrVoid = ::llcpp::meta::traits::conditional_value_simple_v<
	::llcpp::meta::traits::is_empty_object_v<T>,
	ll_bool_t,
	::llcpp::LL_TRUE,
	::std::is_same_v<T, U> && ::std::is_same_v<U, T>
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

// [TOCHECK]
// Some objects uses this operator and expects a throw if parameter is invalid
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorArray = requires (T t) {
	{ t[0] } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorArrayExcept = requires (T t) {
	{ t[0] } -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};

template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasPointerOperator = requires (T t) { { *t } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };

template<class T, class ArrayType = ll_string_t, class SizeType = usize, class ReturnType = void>
concept HasHashArray = requires (const T t, const ArrayType arr, const SizeType s) {
	{ t.hash(arr, s) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class ReturnType = u64>
concept HasHash = requires (const T t) {
	{ t.hash() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};

template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasForeachOperation = requires (T t, U u) {
	{ t.foreachOperation(u) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class W, class ReturnType = ::llcpp::Emptyclass>
concept HasForeachOperationExtra = requires (T t, U u, W w) {
	{ t.foreachOperation(u, w) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};

#pragma region EditOperators
#pragma region SimpleMode
template<class T, class ReturnType = T&>
concept HasPreIncrement = requires (T t) { { ++t } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class ReturnType = T>
concept HasPosIncrement = requires (T t) { { t++ } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class U, class ReturnType = T>
concept HasOperatorSum = requires (const T t, const U u) { { t + u } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class U, class ReturnType = T>
concept HasOperatorSub = requires (const T t, const U u) { { t - u } noexcept -> ::std::same_as<ReturnType>; };

template<class T, class U = u8, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseLeft = requires(const T t, const U u) {
	{ t << u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U = u8, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseRight = requires(const T t, const U u) {
	{ t >> u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseAND = requires(const T t, const U u) {
	{ t & u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseOR = requires(const T t, const U u) {
	{ t | u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseXOR = requires(const T t, const U u) {
	{ t ^ u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorModulus = requires(const T t, const U u) {
	{ t % u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};

#pragma endregion
#pragma region AssignMode
template<class T, class U, class ReturnType = T&>
concept HasOperatorSumAssign = requires (T t, const U u) { { t += u } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class U, class ReturnType = T&>
concept HasOperatorSubAssign = requires (T t, const U u) { { t -= u } noexcept -> ::std::same_as<ReturnType>; };

template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseLeftAssign = requires(T t, const U u) {
	{ t <<= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseRightAssign = requires(T t, const U u) {
	{ t >>= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseANDAssign = requires(T t, const U u) {
	{ t &= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseORAssign = requires(T t, const U u) {
	{ t |= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseXORAssign = requires(T t, const U u) {
	{ t ^= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorModulusAssign = requires(T t, const U u) {
	{ t %= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
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
concept HasOperatorEqual = requires (const T t, const U u) { { t == u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorNonEqual = requires (const T t, const U u) { { t != u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorGreaterEqual = requires (const T t, const U u) { { t >= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorGreater = requires (const T t, const U u) { { t > u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorLowerEqual = requires (const T t, const U u) { { t <= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorLower = requires (const T t, const U u) { { t < u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasOperatorThreeWay = requires (const T t, const U u) { { t <=> u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = i32>
concept HasCompare = requires (const T t, const U u) { { t.compare(u) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ll_bool_t>
concept HasEquals = requires (const T t, const U u) { { t.equals(u) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };

#pragma endregion
#pragma region ConstLists
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasConstBegin = requires (const T t) { { t.begin() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasConstReverseBegin = requires (const T t) { { t.rbegin() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasConstEnd = requires (const T t) { { t.end() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasConstReverseEnd = requires (const T t) { { t.rend() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T>
concept HasConstListFunctions = requires {
	requires ::llcpp::meta::concepts::signature::HasConstBegin<T>;
	requires ::llcpp::meta::concepts::signature::HasConstReverseBegin<T>;
	requires ::llcpp::meta::concepts::signature::HasConstEnd<T>;
	requires ::llcpp::meta::concepts::signature::HasConstReverseEnd<T>;
};

#pragma endregion
#pragma region Lists
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasBegin = requires (T t) { { t.begin() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasReverseBegin = requires (T t) { { t.rbegin() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasEnd = requires (T t) { { t.end() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasReverseEnd = requires (T t) { { t.rend() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T>
concept HasListFunctions = requires {
	requires ::llcpp::meta::concepts::signature::HasBegin<T>;
	requires ::llcpp::meta::concepts::signature::HasReverseBegin<T>;
	requires ::llcpp::meta::concepts::signature::HasEnd<T>;
	requires ::llcpp::meta::concepts::signature::HasReverseEnd<T>;
};

#pragma endregion

template<class T, class ReturnType = void>
concept HasClear = requires (T t) { { t.clear() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ll_bool_t>
concept HasEmpty = requires (const T t) { { t.empty() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = usize, class ReturnType = ll_bool_t>
concept HasInRange = requires (const T t, const U u) { { t.inRange(u) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };

#pragma region Size
template<class T, class ReturnType = usize>
concept HasSize = requires (const T t) { { t.size() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = usize, class... Args>
concept HasSizeWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasSize<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasSize<T, Args, ReturnType>...>;
#endif // __LL_REAL_CXX17 == 1
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasSizeWithPrimitives = ::llcpp::meta::concepts::signature::HasSizeWith<T, ReturnType, __LL_INTEGRAL_TYPES>;

#pragma endregion
#pragma region MaxSize
template<class T, class ReturnType = usize>
concept HasMaxSize = requires (const T t) { { t.max_size() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = usize, class... Args>
concept HasMaxSizeWith =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::concepts::signature::HasMaxSize<T, Args, ReturnType> || ...);
#else
	::std::disjunction_v<::llcpp::meta::concepts::signature::HasMaxSize<T, Args, ReturnType>...>;
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
	requires ::llcpp::meta::concepts::signature::HasConstBegin<Array>;
	requires ::llcpp::meta::concepts::signature::HasReverseBegin<Array>;
	requires ::llcpp::meta::concepts::signature::HasEnd<Array>;
	requires ::llcpp::meta::concepts::signature::HasConstEnd<Array>;
	requires ::llcpp::meta::concepts::signature::HasReverseEnd<Array>;
	requires ::llcpp::meta::concepts::signature::HasSize<Array>;
	requires ::llcpp::meta::concepts::signature::HasMaxSize<Array>;
	requires ::llcpp::meta::concepts::signature::HasEmpty<Array>;
};
template<class Array, class Content = ::llcpp::Emptyclass>
concept IsConstArrayObject = requires (Array arr) {
	requires ::llcpp::meta::concepts::is_object::IsArray<Array, Content>;
	requires ::llcpp::meta::concepts::signature::HasConstBegin<Array>;
	requires ::llcpp::meta::concepts::signature::HasConstEnd<Array>;
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
