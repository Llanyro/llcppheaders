//////////////////////////////////////////////
//	concepts.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_CONCEPTS_HPP_) // Guard && version protector
	#if LLANYLIB_CONCEPTS_MAYOR_ != 12 || LLANYLIB_CONCEPTS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "concepts.hpp version error!"
		#else
			#error "concepts.hpp version error!"
		#endif // __LL_REAL_CXX23
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
	::llcpp::TRUE,
	::std::is_same_v<T, U> && ::std::is_same_v<U, T>
>;
	
template<class T>
concept HasValueType = ::llcpp::meta::traits::has_value_type_v<T>;
template<class T>
concept HasValueConstant = ::llcpp::meta::traits::has_value_constant_v<T>;
template<class Unit, Unit VALUE>
concept NonZeroValue = ::llcpp::meta::concepts::base::IsValidConcept<VALUE != ::llcpp::ZERO_VALUE<Unit>>;
template<class Unit, Unit VALUE>
concept ZeroValue = ::llcpp::meta::concepts::base::IsValidConcept<VALUE == ::llcpp::ZERO_VALUE<Unit>>;
// [TODO] [TOFIX]
//template<class Unit, Unit VALUE>
//concept NonMaxValue = requires { { VALUE != ::llcpp::MAX_VALUE<Unit> } noexcept; };
//template<class Unit, Unit VALUE>
//concept NonMinValue = requires { { VALUE != ::llcpp::MIN_VALUE<Unit> } noexcept; };

template<class T>
concept IsAlwaysValid = ::std::is_base_of_v<::llcpp::AlwaysValidTag, T>;
template<class T>
concept IsAlwaysInvalid = ::std::is_base_of_v<::llcpp::AlwaysInvalidTag, T>;

} // namespace base
namespace signature {

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
concept HasBegin = requires (T t) { { t.begin() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasConstBegin = requires (T t) { { t.cbegin() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasReverseBegin = requires (T t) { { t.rbegin() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasEnd = requires (T t) { { t.end() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasConstEnd = requires (T t) { { t.cend() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasReverseEnd = requires (T t) { { t.rend() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };

template<class T, class ReturnType = ::llcpp::usize>
concept HasSize = requires (T t) { { t.size() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };
template<class T, class ReturnType = ::llcpp::usize>
concept HasMaxSize = requires (T t) { { t.max_size() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };

// [TOCHECK]
// Some objects uses this operator and expects a throw if parameter is invalid
template<class T, class ReturnType = ::llcpp::Emptyclass>
concept HasOperatorArray = requires (T t) { { t[0] } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>; };

template<class T, class U, class ReturnType = ::llcpp::Emptyclass>
concept HasForeachOperation = requires (T t, U u) {
	{ t.foreachOperation(u) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class U, class W, class ReturnType = ::llcpp::Emptyclass>
concept HasForeachOperationExtra = requires (T t, U u, W w) {
	{ t.foreachOperation(u, w) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};

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
template<class T>
concept IsArrayObject = requires (T arr) {
	requires ::llcpp::meta::concepts::is_object::IsArray<T>;
	requires ::llcpp::meta::concepts::signature::HasBegin<T>;
	requires ::llcpp::meta::concepts::signature::HasConstBegin<T>;
	requires ::llcpp::meta::concepts::signature::HasReverseBegin<T>;
	requires ::llcpp::meta::concepts::signature::HasEnd<T>;
	requires ::llcpp::meta::concepts::signature::HasConstEnd<T>;
	requires ::llcpp::meta::concepts::signature::HasReverseEnd<T>;
	requires ::llcpp::meta::concepts::signature::HasSize<T>;
	requires ::llcpp::meta::concepts::signature::HasMaxSize<T>;
};

} // namespace is_object
} // namespace concepts
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CONCEPTS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
