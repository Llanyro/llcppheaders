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
concept FristBiggerSize		= sizeof(T) > sizeof(U);
template<class T, class U>
concept FristSmallerSize	= sizeof(T) < sizeof(U);
template<class T, class U>
concept EqualSize			= sizeof(T) == sizeof(U);
template<class _From, class _To>
concept ConvertibleTo		= requires { static_cast<_To>(::std::declval<_From>()); };

template<class T>
concept HasValueType = ::llcpp::meta::traits::has_value_type_v<T>;
template<class T>
concept HasValueConstant = ::llcpp::meta::traits::has_value_constant_v<T>;
template<class T>
concept HasHashType = ::llcpp::meta::traits::has_hash_type_v<T>;

template<class Unit, Unit VALUE>
concept NonZeroValue = ::llcpp::meta::concepts::base::IsValidConcept<VALUE != ::llcpp::ZERO_VALUE<Unit>>;
template<class Unit, Unit VALUE>
concept ZeroValue = ::llcpp::meta::concepts::base::IsValidConcept<VALUE == ::llcpp::ZERO_VALUE<Unit>>;
template<class Unit, Unit VALUE>
concept NonMaxValue = requires { { VALUE != ::llcpp::MAX_VALUE<Unit> } noexcept; };
template<class Unit, Unit VALUE>
concept NonMinValue = requires { { VALUE != ::llcpp::MIN_VALUE<Unit> } noexcept; };

template<class T>
concept IsAlwaysValid = ::std::is_base_of_v<::llcpp::AlwaysValidTag, T>;
template<class T>
concept IsAlwaysInvalid = ::std::is_base_of_v<::llcpp::AlwaysInvalidTag, T>;

template<class T, ll_bool_t IGNORE_SIGNED = ::llcpp::LL_FALSE, ll_bool_t IGNORE_UNSIGNED = ::llcpp::LL_FALSE>
concept IsCharType = requires {
	requires IGNORE_SIGNED ||
		::llcpp::meta::traits::is_any_of_v<T, ll_char_t, ll_wchar_t
//		, char16_t, char32_t
//#if defined(__cpp_char8_t)
//		char8_t,
//#endif // __cpp_char8_t
		>;
	requires IGNORE_UNSIGNED || ::llcpp::meta::traits::is_any_of_v<T, ll_uchar_t>;
};

} // namespace base
namespace signature {

#pragma region Operators
// [TOCHECK]
// Some objects uses this operator and expects a throw if parameter is invalid
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorArray = requires (T t) {
	{ t[0] } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};

template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasPointerOperator = requires (T t) { { *t } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = T&>
concept HasPreIncrement = requires (T t) { { ++t } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class ReturnType = T>
concept HasPosIncrement = requires (T t) { { t++ } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class U, class ReturnType = T>
concept HasOperatorSum = requires (T t, U u) { { t + u } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class U, class ReturnType = T>
concept HasOperatorSub = requires (T t, U u) { { t - u } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class U, class ReturnType = T&>
concept HasOperatorSumSelf = requires (T t, U u) { { t += u } noexcept -> ::std::same_as<ReturnType>; };
template<class T, class U, class ReturnType = T&>
concept HasOperatorSubSelf = requires (T t, U u) { { t -= u } noexcept -> ::std::same_as<ReturnType>; };

template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseLeft = requires(const T t, u8 u) {
	{ t << u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseRight = requires(const T t, u8 u) {
	{ t >> u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseAnd = requires(const T t, U u) {
	{ t & u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};

template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseLeftEq = requires(const T t, u8 u) {
	{ t <<= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseRightEq = requires(const T t, u8 u) {
	{ t >>= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorBitwiseAndEq = requires(const T t, U u) {
	{ t &= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};

#pragma endregion
#pragma region Comparations
template<class T, class U = T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorEqual = requires (T t, U u) { { t == u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorNonEqual = requires (T t, U u) { { t != u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorGreaterEqual = requires (T t, U u) { { t >= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorGreater = requires (T t, U u) { { t > u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorLowerEqual = requires (T t, U u) { { t <= u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorLower = requires (T t, U u) { { t < u } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };

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

#pragma endregion

template<class T, class ReturnType = void>
concept HasHash = requires (const T t, ll_string_t arr, const usize s) {
	{ t.hash(arr, s) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};

template<class T, class ReturnType = void>
concept HasClear = requires (T t) { { t.clear() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = usize>
concept HasSize = requires (T t) { { t.size() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = usize>
concept HasMaxSize = requires (T t) { { t.max_size() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ll_bool_t>
concept HasEmpty = requires (T t) { { t.empty() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class U = usize, class ReturnType = ll_bool_t>
concept HasInRange = requires (T t, U u) { { t.inRange(u) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };

template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasForeachOperation = requires (T t, U u) {
	{ t.foreachOperation(u) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class W, class ReturnType = ::llcpp::Emptyclass>
concept HasForeachOperationExtra = requires (T t, U u, W w) {
	{ t.foreachOperation(u, w) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};

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
	requires ::llcpp::meta::concepts::signature::HasPosIncrement<Iterator>;
	requires ::llcpp::meta::concepts::signature::HasOperatorSum<Iterator, isize>;
	requires ::llcpp::meta::concepts::signature::HasOperatorSub<Iterator, isize>;
	requires ::llcpp::meta::concepts::signature::HasOperatorSumSelf<Iterator, isize>;
	requires ::llcpp::meta::concepts::signature::HasOperatorSubSelf<Iterator, isize>;
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
