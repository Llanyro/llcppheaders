//////////////////////////////////////////////
//	type_traits.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TYPETRAITS_INCOMPLETE_HPP_)
	#if LLANYLIB_TYPETRAITS_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_TYPETRAITS_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "type_traits.hpp(incomplete) version error!"
		#else
			#error "type_traits.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPETRAITS_INCOMPLETE_MAYOR_ || LLANYLIB_TYPETRAITS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TYPETRAITS_INCOMPLETE_HPP_)
	#define LLANYLIB_TYPETRAITS_INCOMPLETE_HPP_
	#define LLANYLIB_TYPETRAITS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_TYPETRAITS_INCOMPLETE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/types.hpp>
#else
	#include "../types/types.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace traits {

template <class T, class = void>
class HasValueType;
template<class T>
class HasValueType<T, ::std::void_t<typename T::value_type>>;
template <class T, class = void>
class HasValueConstant;
template<class T>
class HasValueConstant<T, ::std::void_t<decltype(T::value)>>;
template <class T, class = void>
class HasLLCPPValueType;
template<class T>
class HasLLCPPValueType<T, ::std::void_t<typename T::T>>;
template <class T, class = void>
class HasLLCPPValueConstant;
template<class T>
class HasLLCPPValueConstant<T, ::std::void_t<decltype(T::value)>>;

template<class _T>
class TypeContainer;
template<class _T, class _U>
class DoubleTypeContainer;
template<class _T, _T _VALUE, class _U>
class IntegralConstantContainer;

template<class _T, class _U, _T _FIRST, _U _SECOND>
class DoubleConstantContainer;

template<ll_bool_t VALUE, class U>
using BoolConstantContainer = ::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, VALUE, U>;

template<class T = ::llcpp::Emptyclass>
using TrueContainerEmptyClass = ::llcpp::meta::traits::BoolConstantContainer<::llcpp::LL_TRUE, T>;
template<class T = ::llcpp::Emptyclass>
using FalseContainerEmptyClass = ::llcpp::meta::traits::BoolConstantContainer<::llcpp::LL_FALSE, T>;

template<class U, class T, T EXP1, T EXP2>
using IsSameTypeExpresion = ::llcpp::meta::traits::BoolConstantContainer<EXP1 == EXP2, U>;
template<class U, class T, T EXP1, T EXP2>
using IsNotSameTypeExpresion = ::llcpp::meta::traits::BoolConstantContainer<EXP1 != EXP2, U>;

template<ll_bool_t VALUE, class U, U VALUE2>
using BoolDoubleConstantContainer			= ::llcpp::meta::traits::DoubleConstantContainer<ll_bool_t, U, VALUE, VALUE2>;

template<class T, class U, class W, W VALUE2>
using IsSameDoubleTypeContainer				= ::llcpp::meta::traits::BoolDoubleConstantContainer<::std::is_same_v<T, U>, W, VALUE2>;
template<class T, class U, class W, W VALUE2>
using IsNotSameDoubleTypeContainer			= ::llcpp::meta::traits::BoolDoubleConstantContainer<!::std::is_same_v<T, U>, W, VALUE2>;

template<class T, T VALUE = T{}>
using TrueConstantContainerEmptyClass		= ::llcpp::meta::traits::BoolDoubleConstantContainer<::llcpp::LL_TRUE, T, VALUE>;
template<class T, T VALUE = T{}>
using FalseConstantContainerEmptyClass		= ::llcpp::meta::traits::BoolDoubleConstantContainer<::llcpp::LL_FALSE, T, VALUE>;

template<class U, class T, T EXP1, T EXP2, U VALUE2>
using IsSameDoubleTypeExpresion				= ::llcpp::meta::traits::BoolDoubleConstantContainer<EXP1 == EXP2, U, VALUE2>;
template<class U, class T, T EXP1, T EXP2, U VALUE2>
using IsNotSameDoubleTypeExpresion			= ::llcpp::meta::traits::BoolDoubleConstantContainer<EXP1 != EXP2, U, VALUE2>;

template<ll_bool_t _CONDITION, class _T, class _U>
class Conditional;
template<class _T, class _U>
class Conditional<::llcpp::LL_FALSE, _T, _U>;

template<ll_bool_t _CONDITION, class _T, class _U, _T _ELEM_1, _U _ELEM_2>
class ConditionalValue;
template<class _T, class _U, _T _ELEM_1, _U _ELEM_2>
class ConditionalValue<::llcpp::LL_FALSE, _T, _U, _ELEM_1, _ELEM_2>;
template<class _T, class _U, class _OnEqual = llcpp::Emptyclass>
class CompareConditional;

template<class _T>
class RangeChecker;

} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TYPETRAITS_HPP_)
	#if LLANYLIB_TYPETRAITS_MAYOR_ != 12 || LLANYLIB_TYPETRAITS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "type_traits.hpp version error!"
		#else
			#error "type_traits.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPETRAITS_MAYOR_ || LLANYLIB_TYPETRAITS_MINOR_

#else
	#define LLANYLIB_TYPETRAITS_HPP_
	#define LLANYLIB_TYPETRAITS_MAYOR_ 12
	#define LLANYLIB_TYPETRAITS_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/types.hpp>
#else
	#include "../types/types.hpp"
#endif // LL_LIB_PATHS

#if defined(__LL_WINDOWS_SYSTEM)
	#include <type_traits>
#elif defined(__LL_MINGW)
	#include <type_traits>
	//#include <utility>
#elif defined(__LL_POSIX_SYSTEM)
#elif defined(__LL_UNIX_SYSTEM)
#else
#endif // __LL_WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace traits {

#pragma region StandardChecker
template <class T, class = void>
class HasValueType : public ::std::false_type {};
template<class T>
class HasValueType<T, ::std::void_t<typename T::value_type>> : public ::std::true_type {};
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t has_value_type_v = ::llcpp::meta::traits::HasValueType<T>::value;

template <class T, ll_bool_t MAYUS_MODE, class = void>
class HasValueConstant : public ::std::false_type {};
template<class T, ll_bool_t MAYUS_MODE>
class HasValueConstant<T, MAYUS_MODE, ::std::void_t<decltype(T::value)>> : public ::std::true_type {};
template<class T>
class HasValueConstant<T, ::llcpp::LL_TRUE, ::std::void_t<decltype(T::VALUE)>> : public ::std::true_type {};
template<class T, ll_bool_t MAYUS_MODE = ::llcpp::LL_FALSE>
__LL_VAR_INLINE__ constexpr ll_bool_t has_value_constant_v = ::llcpp::meta::traits::HasValueConstant<T, MAYUS_MODE>::value;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_integral_constant_container_v =
	::llcpp::meta::traits::has_value_type_v<T> && ::llcpp::meta::traits::has_value_constant_v<T>;

template <class T, class = void>
class HasValueTypeU : public ::std::false_type {};
template<class T>
class HasValueTypeU<T, ::std::void_t<typename T::U>> : public ::std::true_type {};
// Non-standard functionality | Llanylib standard
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t has_value_type_u_v = ::llcpp::meta::traits::HasValueTypeU<T>::value;


template <class T, class = void>
class HasMyType : public ::std::false_type {};
template<class T>
class HasMyType<T, ::std::void_t<typename T::_MyType>> : public ::std::true_type {};
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t has_mytype_v = ::llcpp::meta::traits::HasMyType<T>::value;

template <class T, class = void>
class HasSize : public ::std::false_type {};
template<class T>
class HasSize<T, ::std::void_t<decltype(T::N)>> : public ::std::true_type {};
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t has_size_v = ::llcpp::meta::traits::HasSize<T>::value;

#pragma endregion
#pragma region HashChecker
template <class T, class = void>
class HasHashType : public ::std::false_type {};
template<class T>
class HasHashType<T, ::std::void_t<typename T::Hash>> : public ::std::true_type {};
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t has_hash_type_v = ::llcpp::meta::traits::HasHashType<T>::value;

#pragma endregion
#pragma region Pair
template <class T, class = void>
class HasPairFirst : public ::std::false_type {};
template<class T>
class HasPairFirst<T, ::std::void_t<decltype(T::first)>> : public ::std::true_type {};
template <class T, class = void>
class HasPairSecond : public ::std::false_type {};
template<class T>
class HasPairSecond<T, ::std::void_t<decltype(T::second)>> : public ::std::true_type {};

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t has_pair_first_v = ::llcpp::meta::traits::HasPairFirst<T>::value;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t has_pair_second_v = ::llcpp::meta::traits::HasPairSecond<T>::value;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_pair_v =
	::llcpp::meta::traits::has_pair_first_v<T>
	&& ::llcpp::meta::traits::has_pair_second_v<T>;

#pragma endregion
#pragma region LlanycppCheckers
template <class T, class U, class = void>
class HasContainerType : public ::std::false_type {};
template<class T, class U>
class HasContainerType<T, U, ::std::void_t<typename T::contain_value_type<U>>> : public ::std::true_type {};

template<class T, class U>
__LL_VAR_INLINE__ constexpr ll_bool_t has_contain_value_type_v = ::llcpp::meta::traits::HasContainerType<T, U>::value;

template <class T, class U, class = void>
class HasContainerTypeU : public ::std::false_type {};
template<class T, class U>
class HasContainerTypeU<T, U, ::std::void_t<typename T::contain_value_type_u<U>>> : public ::std::true_type {};

template<class T, class U>
__LL_VAR_INLINE__ constexpr ll_bool_t has_contain_value_type_u_v = ::llcpp::meta::traits::HasContainerTypeU<T, U>::value;

#pragma endregion
#pragma region Containers
template<class _T>
class TypeContainer {
	public:
		// Class related
		using _MyType				= TypeContainer;	// standard
		template<class W = _T>							// Contains new type in this container
		using contain_value_type	= typename ::llcpp::meta::traits::TypeContainer<W>;

		// Types and enums
		using T						= _T;
		using type					= T;	// standard
		using value_type			= T;	// standard
};
template<class T>
using type_container_t = typename ::llcpp::meta::traits::TypeContainer<T>::value_type;

template<class _T, class _U>
class DoubleTypeContainer {
	public:
		// Class related
		using _MyType		= DoubleTypeContainer;	// standard
		template<class W = _T>	// Contains new type in this container
		using contain_value_type = typename ::llcpp::meta::traits::DoubleTypeContainer<W, _U>;

		// Types and enums
		using T				= _T;
		using U				= _U;
		using type			= T;	// standard
		using value_type	= T;	// standard
};
template<class T, class U>
using double_type_container_t = typename ::llcpp::meta::traits::DoubleTypeContainer<T, U>::T;
template<class T, class U>
using double_type_container_u = typename ::llcpp::meta::traits::DoubleTypeContainer<T, U>::U;

// Can contain 2 types an one constant
template<class _T, _T _VALUE, class _U = ::llcpp::Emptyclass>
class IntegralConstantContainer {
	public:
		// Class related
		using _MyType		= IntegralConstantContainer;	// standard

		// Types and enums
		using T				= _T;
		using U				= _U;
		using type			= T;	// standard
		using value_type	= T;	// standard

	public:
		// Expresions
		static constexpr value_type VALUE = _VALUE;
		static constexpr value_type value = _VALUE;	// standard
};

template<class T, T VALUE, class U = ::llcpp::Emptyclass>
using integral_constant_container_t = typename ::llcpp::meta::traits::IntegralConstantContainer<T, VALUE, U>::T;
template<class T, T VALUE, class U = ::llcpp::Emptyclass>
using integral_constant_container_u = typename ::llcpp::meta::traits::IntegralConstantContainer<T, VALUE, U>::U;
template<class T, T VALUE, class U = ::llcpp::Emptyclass>
__LL_VAR_INLINE__ constexpr T integral_constant_container_v =
	::llcpp::meta::traits::IntegralConstantContainer<T, VALUE, U>::VALUE;

template<class _T, class _U, _T _FIRST, _U _SECOND>
class DoubleConstantContainer {
	public:
		// Class related
		using _MyType		= DoubleConstantContainer;	// standard

		// Types and enums
		using T				= _T;
		using U				= _U;
		using type			= T;	// standard
		using value_type	= T;	// standard

	public:
		// Expresions
		static constexpr T FIRST	= _FIRST;
		static constexpr U SECOND	= _SECOND;

		static constexpr value_type VALUE = FIRST;
		static constexpr value_type value = FIRST;	// standard
};

template<class T, class U, T FIRST, U SECOND>
using double_constant_container_t = typename ::llcpp::meta::traits::DoubleConstantContainer<T, U, FIRST, SECOND>::T;
template<class T, class U, T FIRST, U SECOND>
using double_constant_container_u = typename ::llcpp::meta::traits::DoubleConstantContainer<T, U, FIRST, SECOND>::U;
template<class T, class U, T FIRST, U SECOND>
__LL_VAR_INLINE__ constexpr T double_constant_container_first =
	::llcpp::meta::traits::DoubleConstantContainer<T, U, FIRST, SECOND>::FIRST;
template<class T, class U, T FIRST, U SECOND>
__LL_VAR_INLINE__ constexpr T double_constant_container_second =
	::llcpp::meta::traits::DoubleConstantContainer<T, U, FIRST, SECOND>::SECOND;

#pragma endregion
#pragma region LogicContainers
#pragma region SimpleContainers
template<ll_bool_t VALUE, class U>
using BoolConstantContainer = ::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, VALUE, U>;

template<class T, class U, class W>
using IsSameTypeContainer = ::llcpp::meta::traits::BoolConstantContainer<::std::is_same_v<T, U>, W>;
template<class T, class U, class W>
using IsNotSameTypeContainer = ::llcpp::meta::traits::BoolConstantContainer<!::std::is_same_v<T, U>, W>;

template<class T = ::llcpp::Emptyclass>
using TrueContainerEmptyClass = ::llcpp::meta::traits::BoolConstantContainer<::llcpp::LL_TRUE, T>;
template<class T = ::llcpp::Emptyclass>
using FalseContainerEmptyClass = ::llcpp::meta::traits::BoolConstantContainer<::llcpp::LL_FALSE, T>;

template<class U, class T, T EXP1, T EXP2>
using IsSameTypeExpresion = ::llcpp::meta::traits::BoolConstantContainer<EXP1 == EXP2, U>;
template<class U, class T, T EXP1, T EXP2>
using IsNotSameTypeExpresion				= ::llcpp::meta::traits::BoolConstantContainer<EXP1 != EXP2, U>;

#pragma endregion
#pragma region DoubleContainers
template<ll_bool_t VALUE, class U, U VALUE2>
using BoolDoubleConstantContainer			= ::llcpp::meta::traits::DoubleConstantContainer<ll_bool_t, U, VALUE, VALUE2>;

template<class T, class U, class W, W VALUE2>
using IsSameDoubleTypeContainer				= ::llcpp::meta::traits::BoolDoubleConstantContainer<::std::is_same_v<T, U>, W, VALUE2>;
template<class T, class U, class W, W VALUE2>
using IsNotSameDoubleTypeContainer			= ::llcpp::meta::traits::BoolDoubleConstantContainer<!::std::is_same_v<T, U>, W, VALUE2>;

template<class T, T VALUE = T{}>
using TrueConstantContainerEmptyClass		= ::llcpp::meta::traits::BoolDoubleConstantContainer<::llcpp::LL_TRUE, T, VALUE>;
template<class T, T VALUE = T{}>
using FalseConstantContainerEmptyClass		= ::llcpp::meta::traits::BoolDoubleConstantContainer<::llcpp::LL_FALSE, T, VALUE>;

template<class U, class T, T EXP1, T EXP2, U VALUE2>
using IsSameDoubleTypeExpresion				= ::llcpp::meta::traits::BoolDoubleConstantContainer<EXP1 == EXP2, U, VALUE2>;
template<class U, class T, T EXP1, T EXP2, U VALUE2>
using IsNotSameDoubleTypeExpresion			= ::llcpp::meta::traits::BoolDoubleConstantContainer<EXP1 != EXP2, U, VALUE2>;

#pragma endregion
#pragma endregion
#pragma region Conditional
template<ll_bool_t _CONDITION, class _T, class _U>
class Conditional {
	public:
		// Class related
		using _MyType		= Conditional;	// standard

		// Types and enums
		using T				= _T;
		using U				= _U;
		using type			= T;	// standard
		using value_type	= T;	// standard

	public:
		// Expresions
		static constexpr ll_bool_t CONDITION	= _CONDITION;
};
template<class _T, class _U>
class Conditional<::llcpp::LL_FALSE, _T, _U> {
	public:
		// Class related
		using _MyType		= Conditional;	// standard

		// Types and enums
		using T				= _T;
		using U				= _U;
		using type			= U;	// standard
		using value_type	= U;	// standard

	public:
		// Expresions
		static constexpr ll_bool_t CONDITION	= ::llcpp::LL_FALSE;
};

template<ll_bool_t CONDITION, class T, class U>
using conditional_t = typename ::llcpp::meta::traits::Conditional<CONDITION, T, U>::type;

template<ll_bool_t _CONDITION, class _T, class _U, _T _ELEM_1, _U _ELEM_2>
class ConditionalValue {
	public:
		// Class related
		using _MyType		= ConditionalValue;	// standard

		// Types and enums
		using T				= _T;
		using U				= _U;
		using type			= T;	// standard
		using value_type	= T;	// standard

	public:
		// Expresions
		static constexpr ll_bool_t CONDITION 	= _CONDITION;
		static constexpr _T ELEM_1				= _ELEM_1;
		static constexpr _U ELEM_2				= _ELEM_2;

		static constexpr value_type VALUE		= _ELEM_1;
		static constexpr value_type value		= VALUE;	// standard

};
template<class _T, class _U, _T _ELEM_1, _U _ELEM_2>
class ConditionalValue<::llcpp::LL_FALSE, _T, _U, _ELEM_1, _ELEM_2> {
	public:
		// Class related
		using _MyType		= ConditionalValue;	// standard

		// Types and enums
		using T				= _T;
		using U				= _U;
		using type			= U;	// standard
		using value_type	= U;	// standard

	public:
		// Expresions
		static constexpr ll_bool_t CONDITION	= ::llcpp::LL_FALSE;
		static constexpr _T ELEM_1				= _ELEM_1;
		static constexpr _U ELEM_2				= _ELEM_2;

		static constexpr value_type VALUE		= _ELEM_2;
		static constexpr value_type value		= VALUE;	// standard
};

template<ll_bool_t CONDITION, class T, class U, T ELEM_1, U ELEM_2>
__LL_VAR_INLINE__ constexpr auto conditional_value_v = ConditionalValue<CONDITION, T, U, ELEM_1, ELEM_2>::VALUE;
template<ll_bool_t CONDITION, class T, T ELEM_1, T ELEM_2>
__LL_VAR_INLINE__ constexpr auto conditional_value_simple_v = ConditionalValue<CONDITION, T, T, ELEM_1, ELEM_2>::VALUE;
template<ll_bool_t CONDITION, ll_bool_t ELEM_1, ll_bool_t ELEM_2>
__LL_VAR_INLINE__ constexpr auto conditional_value_bool_v = ConditionalValue<CONDITION, ll_bool_t, ll_bool_t, ELEM_1, ELEM_2>::VALUE;

template<class _T, class _U, class _OnEqual = ::llcpp::Emptyclass>
class CompareConditional {
	public:
		// Class related
		using _MyType	= CompareConditional;	// standard

		// Types and enums
		using T			= _T;
		using U			= _U;
		using OnEqual	= _OnEqual;

	public:
		// Comparation expresions
		static constexpr ll_bool_t BIGGER_COMPARE		= sizeof(T) > sizeof(U);
		static constexpr ll_bool_t BIGGER_EQ_COMPARE	= sizeof(T) >= sizeof(U);
		static constexpr ll_bool_t SMALLER_COMPARE		= sizeof(T) < sizeof(U);
		static constexpr ll_bool_t SMALLER_EQ_COMPARE	= sizeof(T) <= sizeof(U);
		static constexpr ll_bool_t EQ_COMPARE			= sizeof(T) == sizeof(U);

	private:
		using __bigger	= ::llcpp::meta::traits::conditional_t<_MyType::BIGGER_COMPARE, T, U>;
		using __smaller	= ::llcpp::meta::traits::conditional_t<_MyType::SMALLER_COMPARE, T, U>;

	public:
		using bigger		= ::llcpp::meta::traits::conditional_t<_MyType::EQ_COMPARE, OnEqual, __bigger>;
		using smaller		= ::llcpp::meta::traits::conditional_t<_MyType::EQ_COMPARE, OnEqual, __smaller>;

		// Returrns first type on bigger or equal
		using bigger_eq		= ::llcpp::meta::traits::conditional_t<_MyType::BIGGER_EQ_COMPARE, T, U>;
		// Returrns first type on smaller or equal
		using smaller_eq	= ::llcpp::meta::traits::conditional_t<_MyType::SMALLER_EQ_COMPARE, T, U>;
};

template<class T, class U, class OnEqual = ::llcpp::Emptyclass>
using type_bigger_of_two_t = typename ::llcpp::meta::traits::CompareConditional<T, U, OnEqual>::bigger;
template<class T, class U, class OnEqual = llcpp::Emptyclass>
using type_smaller_of_two_t = typename ::llcpp::meta::traits::CompareConditional<T, U, OnEqual>::smaller;

#pragma endregion
#pragma region Disjunction
template<class T, class OnNotFound, class... Args>
using GetFirstCoincidence = ::std::disjunction<
	::llcpp::meta::traits::IsSameTypeContainer<T, typename Args::T, typename Args::U>...,
	::llcpp::meta::traits::TrueContainerEmptyClass<OnNotFound>
>;

/*template<class T, class TypeChar, class TypeWChar, class TypeChar16, class TypeChar32>
using GetByCharType = typename ::llcpp::meta::traits::GetFirstCoincidence<
	::llcpp::meta::traits::DoubleTypeContainer<ll_char_t, TypeChar>,
	::llcpp::meta::traits::DoubleTypeContainer<ll_wchar_t, TypeWChar>
	//::llcpp::meta::traits::DoubleTypeContainer<char16_t, TypeChar16>,
	//::llcpp::meta::traits::DoubleTypeContainer<char32_t, TypeChar32>
>;

template<class T, class... Args>
using get_first_coincidence_u = typename ::llcpp::meta::traits::GetFirstCoincidence<T, Args...>::U;

template<class T, class TypeChar, class TypeWChar>
using get_by_char_type_u = typename ::llcpp::meta::traits::GetByCharType<T, TypeChar, TypeWChar>::U;*/

#pragma endregion
#pragma region Conjunction
template<class T, class OnNotFound, class... Args>
using GetFirstDifference = ::std::conjunction<
	::llcpp::meta::traits::IsSameTypeContainer<T, typename Args::T, typename Args::U>...,
	::llcpp::meta::traits::TrueContainerEmptyClass<OnNotFound>
>;

template<class T, class OnNotFound, class... Args>
using get_first_difference_u = GetFirstCoincidence<T, OnNotFound, Args...>::U;

#pragma endregion
#pragma region PrimitiveUpdate
template<class T, class OnNotFound = T, ll_bool_t PROMOTE = ::llcpp::LL_TRUE>
using TypePromotion = typename ::llcpp::meta::traits::GetFirstCoincidence<
	T, OnNotFound,
	::llcpp::meta::traits::DoubleTypeContainer<i8,		::llcpp::meta::traits::conditional_t<PROMOTE, i16, i8>>,
	::llcpp::meta::traits::DoubleTypeContainer<i16,		::llcpp::meta::traits::conditional_t<PROMOTE, i32, i8>>,
	::llcpp::meta::traits::DoubleTypeContainer<i32,		::llcpp::meta::traits::conditional_t<PROMOTE, i64, i16>>,
	::llcpp::meta::traits::DoubleTypeContainer<i64,		::llcpp::meta::traits::conditional_t<PROMOTE, i128, i32>>,
	::llcpp::meta::traits::DoubleTypeContainer<i128,	::llcpp::meta::traits::conditional_t<PROMOTE, i256, i64>>,
	::llcpp::meta::traits::DoubleTypeContainer<i256,	::llcpp::meta::traits::conditional_t<PROMOTE, i256, i128>>,

	::llcpp::meta::traits::DoubleTypeContainer<u8,		::llcpp::meta::traits::conditional_t<PROMOTE, u16, u8>>,
	::llcpp::meta::traits::DoubleTypeContainer<u16,		::llcpp::meta::traits::conditional_t<PROMOTE, u32, u8>>,
	::llcpp::meta::traits::DoubleTypeContainer<u32,		::llcpp::meta::traits::conditional_t<PROMOTE, u64, u16>>,
	::llcpp::meta::traits::DoubleTypeContainer<u64,		::llcpp::meta::traits::conditional_t<PROMOTE, u128, u32>>,
	::llcpp::meta::traits::DoubleTypeContainer<u128,	::llcpp::meta::traits::conditional_t<PROMOTE, u256, u64>>,
	::llcpp::meta::traits::DoubleTypeContainer<u256,	::llcpp::meta::traits::conditional_t<PROMOTE, u256, u128>>,

	::llcpp::meta::traits::DoubleTypeContainer<f32,		::llcpp::meta::traits::conditional_t<PROMOTE, f64, f32>>,
	::llcpp::meta::traits::DoubleTypeContainer<f64,		::llcpp::meta::traits::conditional_t<PROMOTE, f128, f32>>,
	::llcpp::meta::traits::DoubleTypeContainer<f128,	::llcpp::meta::traits::conditional_t<PROMOTE, f128, f64>>
>::U;

template<class T, class OnNotFound = T, ll_bool_t SIGNALIZE = ::llcpp::LL_TRUE>
using TypeSigned = typename ::llcpp::meta::traits::GetFirstCoincidence<
	T, OnNotFound,
	::llcpp::meta::traits::DoubleTypeContainer<i8,		::llcpp::meta::traits::conditional_t<SIGNALIZE, i8, u8>>,
	::llcpp::meta::traits::DoubleTypeContainer<i16,		::llcpp::meta::traits::conditional_t<SIGNALIZE, i16, u16>>,
	::llcpp::meta::traits::DoubleTypeContainer<i32,		::llcpp::meta::traits::conditional_t<SIGNALIZE, i32, u32>>,
	::llcpp::meta::traits::DoubleTypeContainer<i64,		::llcpp::meta::traits::conditional_t<SIGNALIZE, i64, u64>>,
	::llcpp::meta::traits::DoubleTypeContainer<i128,	::llcpp::meta::traits::conditional_t<SIGNALIZE, i128, u128>>,
	::llcpp::meta::traits::DoubleTypeContainer<i256,	::llcpp::meta::traits::conditional_t<SIGNALIZE, i256, u256>>,

	::llcpp::meta::traits::DoubleTypeContainer<u8,		::llcpp::meta::traits::conditional_t<SIGNALIZE, i8, u8>>,
	::llcpp::meta::traits::DoubleTypeContainer<u16,		::llcpp::meta::traits::conditional_t<SIGNALIZE, i16, u16>>,
	::llcpp::meta::traits::DoubleTypeContainer<u32,		::llcpp::meta::traits::conditional_t<SIGNALIZE, i32, u32>>,
	::llcpp::meta::traits::DoubleTypeContainer<u64,		::llcpp::meta::traits::conditional_t<SIGNALIZE, i64, u64>>,
	::llcpp::meta::traits::DoubleTypeContainer<u128,	::llcpp::meta::traits::conditional_t<SIGNALIZE, i128, u128>>,
	::llcpp::meta::traits::DoubleTypeContainer<u256,	::llcpp::meta::traits::conditional_t<SIGNALIZE, i256, u256>>
>::U;

template<class T, class OnNotFound = T, ll_bool_t PROMOTE = ::llcpp::LL_TRUE>
using type_promotion_u =	::llcpp::meta::traits::TypePromotion<T, OnNotFound, PROMOTE>;
template<class T, class OnNotFound = T>
using type_promote_u =		::llcpp::meta::traits::TypePromotion<T, OnNotFound, ::llcpp::LL_TRUE>;
template<class T, class OnNotFound = T>
using type_demote_u =		::llcpp::meta::traits::TypePromotion<T, OnNotFound, ::llcpp::LL_FALSE>;

template<class T, class OnNotFound = T, ll_bool_t SIGNALIZE = ::llcpp::LL_TRUE>
using type_signed_u =		::llcpp::meta::traits::TypeSigned<T, OnNotFound, SIGNALIZE>;
template<class T, class OnNotFound = T>
using type_signalize_u =	::llcpp::meta::traits::TypeSigned<T, OnNotFound, ::llcpp::LL_TRUE>;
template<class T, class OnNotFound = T>
using type_unsignalize_u =	::llcpp::meta::traits::TypeSigned<T, OnNotFound, ::llcpp::LL_FALSE>;

template<class CompareType, class BaseTypeSigned>
__LL_VAR_INLINE__ constexpr ll_bool_t is_same_su_v =
	::std::is_same_v<CompareType, ::llcpp::meta::traits::type_signalize_u<BaseTypeSigned>> ||
	::std::is_same_v<CompareType, ::llcpp::meta::traits::type_unsignalize_u<BaseTypeSigned>>;

#pragma endregion
#pragma region Limits
template<class _T>
class RangeChecker {
	public:
		// Class related
		using _MyType		= RangeChecker;	// standard

		// Types and enums
		using T				= _T;
		using type			= T;
		using value_type	= T;
		using T_unsigned	= ::llcpp::meta::traits::type_unsignalize_u<T, ::llcpp::Emptyclass>;

	protected:
		template<class U>
		static constexpr T protector() noexcept {
			if constexpr (::std::is_same_v<T, U>)
				return T(-1);
			else {
				using TT = ::llcpp::meta::traits::RangeChecker<U>;
				return TT::MAX_VALUE >> 1;
			}
		}
		static constexpr auto minProt(T max) noexcept {
			T min = -max - 1;
			return min;
		}

	public:
		// Expresions
		static constexpr T MAX_VALUE =
			::llcpp::meta::traits::conditional_value_simple_v<
				::std::is_unsigned_v<T>,
				T,
				_MyType::protector<T>(),
				_MyType::protector<T_unsigned>()
			>;

		static constexpr T MIN_VALUE = _MyType::minProt(_MyType::MAX_VALUE);

	public:
		// Asserts
		static_assert(::std::is_integral_v<T>,
			"Integral type only!");
		static_assert(!::std::is_floating_point_v<T>,
			"Type cannot be floating point! Results are valid but not correct!");
		static_assert(!::std::is_same_v<T_unsigned, ::llcpp::Emptyclass>,
			"Could not unsignalize U type provided");
};

#pragma endregion
#pragma region SystemSize
// Type getter by size
template<ll_bool_t SIGNED, u8 P_SIZE = sizeof(void*)>
using TypeBySize = typename ::std::disjunction<
	::llcpp::meta::traits::IsSameTypeExpresion<::llcpp::meta::traits::conditional_t<SIGNED, i8,		u8>,	u8, P_SIZE, sizeof(u8)>,
	::llcpp::meta::traits::IsSameTypeExpresion<::llcpp::meta::traits::conditional_t<SIGNED, i16,	u16>,	u8, P_SIZE, sizeof(u16)>,
	::llcpp::meta::traits::IsSameTypeExpresion<::llcpp::meta::traits::conditional_t<SIGNED, i32,	u32>,	u8, P_SIZE, sizeof(u32)>,
	::llcpp::meta::traits::IsSameTypeExpresion<::llcpp::meta::traits::conditional_t<SIGNED, i64,	u64>,	u8, P_SIZE, sizeof(u64)>,
	::llcpp::meta::traits::IsSameTypeExpresion<::llcpp::meta::traits::conditional_t<SIGNED, i128,	u128>,	u8, P_SIZE, sizeof(u128)>,
	::llcpp::meta::traits::IsSameTypeExpresion<::llcpp::meta::traits::conditional_t<SIGNED, i256,	u256>,	u8, P_SIZE, sizeof(u256)>,
	::llcpp::meta::traits::TrueContainerEmptyClass<::llcpp::Emptyclass>
>::U;

using uSize = ::llcpp::meta::traits::TypeBySize<::llcpp::LL_FALSE>;
using iSize = ::llcpp::meta::traits::TypeBySize<::llcpp::LL_TRUE>;

static_assert(!::std::is_same_v<uSize, ::llcpp::Emptyclass>, "Unknown size type");
static_assert(!::std::is_same_v<iSize, ::llcpp::Emptyclass>, "Unknown size type");

static_assert(::std::is_same_v<uSize, usize>, "Missmatch system size");
static_assert(::std::is_same_v<iSize, isize>, "Missmatch system size");

#pragma endregion

// [TOFIX]
namespace dev {

/*
template <class T, class = void>
class HasPointerType : public ::std::false_type {};
template<class T>
class HasPointerType<T, ::std::void_t<decltype(::std::declval<T>().*)>> : public ::std::true_type {};
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t has_pointer_type_v = ::llcpp::meta::traits::HasPointerType<T>::value;

class ASDF { int* val; };
class QWERT {
	public:
		int* val;
		constexpr QWERT() noexcept : val(new int) {}
};
class QWERT2 {
	public:
		int val;
		constexpr QWERT2() noexcept : val() {}
};
class QWERT3 {
	public:
		int* val;
		QWERT3() noexcept : val(new int) {}
};
class QWERT4 {
	public:
		int val;
		QWERT4() noexcept : val() {}
};

constexpr auto asdf1 = ::std::is_trivial_v<int>;
constexpr auto asdf2 = ::std::is_trivial_v<ASDF>;
constexpr auto asdf3 = ::std::is_trivial_v<QWERT>;
constexpr auto asdf4 = ::std::is_trivial_v<QWERT2>;
constexpr auto asdf5 = ::std::is_trivial_v<QWERT3>;
constexpr auto asdf6 = ::std::is_trivial_v<QWERT4>;

constexpr auto asdf_1 = ::std::is_standard_layout_v<int>;
constexpr auto asdf_2 = ::std::is_standard_layout_v<ASDF>;
constexpr auto asdf_3 = ::std::is_standard_layout_v<QWERT>;
constexpr auto asdf_4 = ::std::is_standard_layout_v<QWERT2>;
constexpr auto asdf_5 = ::std::is_standard_layout_v<QWERT3>;
constexpr auto asdf_6 = ::std::is_standard_layout_v<QWERT4>;
*/

class Testing {
	int a;
	virtual ~Testing() {}
};

template<class _T>
class test_a {
	public:
		// Class related
		using _MyType	= test_a;	// standard

		// Types and enums
		using T			= _T;
		using type			= T;	// standard
		using value_type	= T;	// standard

		// Expresions
		static constexpr ll_bool_t IS_VIRTUAL	= ::std::has_virtual_destructor_v<T>;
		static constexpr u64 SIZEOF				= sizeof(T);
		static constexpr u64 SIZEOF_OFFSET		= (IS_VIRTUAL ? sizeof(void*) : 0);
		static constexpr u64 REAL_SIZEOF		= SIZEOF - SIZEOF_OFFSET;
};

} // namespace dev
} // namespace traits
} // namespace meta

#pragma region LimitsPt2
// Proxy of MAX_VALUE in ::llcpp::meta::traits
template<class T>
__LL_VAR_INLINE__ constexpr T	MAX_VALUE		= ::llcpp::meta::traits::RangeChecker<T>::MAX_VALUE;
template<class T>
__LL_VAR_INLINE__ constexpr T	MIN_VALUE		= ::llcpp::meta::traits::RangeChecker<T>::MIN_VALUE;
#pragma endregion

namespace meta {
namespace traits {

template<class T, T VALUE>
__LL_VAR_INLINE__ constexpr ll_bool_t is_zero_value_v		= (VALUE == ::llcpp::ZERO_VALUE<T>);
template<class T, T VALUE>
__LL_VAR_INLINE__ constexpr ll_bool_t is_non_zero_value_v	= (VALUE == ::llcpp::ZERO_VALUE<T>);
template<class T, T VALUE>
__LL_VAR_INLINE__ constexpr ll_bool_t is_max_value_v		= (VALUE == ::llcpp::MAX_VALUE<T>);
template<class T, T VALUE>
__LL_VAR_INLINE__ constexpr ll_bool_t is_min_value_v		= (VALUE == ::llcpp::MIN_VALUE<T>);

#if __LL_INCLUDE_KATS == 1
namespace kat {
template<class _T, class _U>
struct KATstruct {
	using T								= _T;
	using value_type					= T;
	using type							= T;
	using Hash							= T;
	using U								= _U;
	template<class U>
	using contain_value_type			= KATstruct<U, _U>;
	template<class U>
	using contain_value_type_u			= KATstruct<U, _U>;

	static constexpr value_type value	= value_type();
	static constexpr value_type first	= value_type();
	static constexpr U second			= U();
};
template<class _T, class _U, _T T_VALUE, _U U_VALUE>
struct KATIntegralstruct {
	using T								= _T;
	using value_type					= T;
	using type							= T;
	using Hash							= T;
	using U								= _U;

	static constexpr value_type VALUE	= T_VALUE;
	static constexpr value_type value	= T_VALUE;
	static constexpr value_type first	= T_VALUE;
	static constexpr U second			= U_VALUE;

	template<class __T, class __U, __T _T_VALUE, __U _U_VALUE>
	__LL_NODISCARD__ constexpr ll_bool_t operator==(const KATIntegralstruct<__T, __U, _T_VALUE, _U_VALUE>& otheer) const noexcept {
		return
			   ::std::is_same_v<_T, __T>
			&& ::std::is_same_v<_U, __U>
			&& T_VALUE == _T_VALUE
			&& U_VALUE == _U_VALUE;
	}
};
using KATIntegralstructDef1		= KATIntegralstruct<u8, f32, 'H', 9.99f>;
__LL_VAR_INLINE__ constexpr KATIntegralstructDef1 kat_integral_struct_def_1 = {};
using KATIntegralstructDef2		= KATIntegralstruct<f32, i64, 9.99f, -1>;
__LL_VAR_INLINE__ constexpr KATIntegralstructDef2 kat_integral_struct_def_2 = {};

using KATExample				= ::llcpp::meta::traits::kat::KATstruct<i32, f32>;
using SingleTypeKat				= ::llcpp::meta::traits::TypeContainer<i16>;
using DoubleTypeKat				= ::llcpp::meta::traits::DoubleTypeContainer<i8, f64>;
using IntegralKat				= ::llcpp::meta::traits::IntegralConstantContainer<i8, 'H', f32>;
using IntegralObjectKat			= ::llcpp::meta::traits::IntegralConstantContainer<KATIntegralstructDef1, kat_integral_struct_def_1, f32>;
using DoubleIntegralKat			= ::llcpp::meta::traits::DoubleConstantContainer<i8, f32, '8', 0.0f>;
using DoubleIntegralObjectKat	= ::llcpp::meta::traits::DoubleConstantContainer<KATIntegralstructDef1, KATIntegralstructDef2, kat_integral_struct_def_1, kat_integral_struct_def_2>;
using CompareConditionalBigger	= ::llcpp::meta::traits::CompareConditional<u32, i8>;
using CompareConditionalSmaller	= ::llcpp::meta::traits::CompareConditional<f32, i64>;
using CompareConditionalEqual	= ::llcpp::meta::traits::CompareConditional<f64, i64>;
using GetFirstCoincidenceEmpty	= ::llcpp::meta::traits::GetFirstCoincidence<u8, ::llcpp::Emptyclass, ::llcpp::meta::traits::DoubleTypeContainer<i8, u8>>::U;
using GetFirstCoincidenceU8		= ::llcpp::meta::traits::GetFirstCoincidence<u8, ::llcpp::Emptyclass, ::llcpp::meta::traits::DoubleTypeContainer<u8, u8>>::U;
using GetFirstDifferenceEmpty	= ::llcpp::meta::traits::GetFirstDifference<i8, ::llcpp::Emptyclass, ::llcpp::meta::traits::DoubleTypeContainer<i8, u8>>::U;
using GetFirstDifferenceU8		= ::llcpp::meta::traits::GetFirstDifference<i8, ::llcpp::Emptyclass, ::llcpp::meta::traits::DoubleTypeContainer<u8, u8>>::U;

#pragma region HasTypesConstants
__LL_KAT_FUNCTION_CONSTEXPR(
	has_value_kat,
	::llcpp::meta::traits::has_value_type_v<KATExample>,
	"KATExample has value type!"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	has_value_constant_kat,
	::llcpp::meta::traits::has_value_constant_v<KATExample>,
	"KATExample has value constant!"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	has_hash_type_kat,
	::llcpp::meta::traits::has_hash_type_v<KATExample>,
	"KATExample has hash type!"
);

#pragma endregion
#pragma region Pair
__LL_KAT_FUNCTION_CONSTEXPR(
	has_pair_first_kat,
	::llcpp::meta::traits::has_pair_first_v<KATExample>,
	"KATExample has 'first' attribute/constant!"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	has_pair_second_kat,
	::llcpp::meta::traits::has_pair_second_v<KATExample>,
	"KATExample has 'second' attribute/constant!"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_pair_kat,
	::llcpp::meta::traits::is_pair_v<KATExample>,
	"KATExample has pair attributes/constants!"
);

#pragma endregion
#pragma region Container
__LL_VAR_INLINE__ constexpr ll_bool_t HAS_CONTAINER_TYPE_KAT =
	::llcpp::meta::traits::has_contain_value_type_v<KATExample, i32>;
__LL_KAT_FUNCTION_CONSTEXPR(
	has_container_type_kat,
	::llcpp::meta::traits::kat::HAS_CONTAINER_TYPE_KAT,
	"KATExample has container type!"
);

__LL_VAR_INLINE__ constexpr ll_bool_t HAS_CONTAINER_TYPE_U_KAT =
	::llcpp::meta::traits::has_contain_value_type_u_v<KATExample, f32>;
__LL_KAT_FUNCTION_CONSTEXPR(
	has_container_type_u_kat,
	::llcpp::meta::traits::kat::HAS_CONTAINER_TYPE_U_KAT,
	"KATExample has container U type!"
);

#pragma endregion
#pragma region TypeContainer
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_TYPE_CONTAINER =
	::llcpp::meta::traits::has_value_type_v<SingleTypeKat>
	&& ::llcpp::meta::traits::has_mytype_v<SingleTypeKat>
	&& ::llcpp::meta::traits::has_contain_value_type_v<SingleTypeKat, i32>
	&& ::std::is_same_v<SingleTypeKat::value_type, SingleTypeKat::T>
	&& ::std::is_same_v<SingleTypeKat::value_type, SingleTypeKat::type>
	&& ::std::is_same_v<SingleTypeKat::value_type, i16>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_type_container_kat,
	::llcpp::meta::traits::kat::IS_WORKING_TYPE_CONTAINER,
	"Type container" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_DOUBLE_TYPE_CONTAINER =
	::llcpp::meta::traits::has_value_type_v<DoubleTypeKat>
	&& ::llcpp::meta::traits::has_mytype_v<DoubleTypeKat>
	&& ::llcpp::meta::traits::has_value_type_u_v<DoubleTypeKat>
	&& ::llcpp::meta::traits::has_contain_value_type_v<DoubleTypeKat, i32>
	&& ::std::is_same_v<DoubleTypeKat::value_type, DoubleTypeKat::T>
	&& ::std::is_same_v<DoubleTypeKat::value_type, DoubleTypeKat::type>
	&& ::std::is_same_v<DoubleTypeKat::value_type, i8>
	&& ::std::is_same_v<DoubleTypeKat::U, f64>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_double_type_container_kat,
	::llcpp::meta::traits::kat::IS_WORKING_DOUBLE_TYPE_CONTAINER,
	"Double type container" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_INTEGRAL_TYPE_CONTAINER =
	::llcpp::meta::traits::has_value_type_v<IntegralKat>
	&& ::llcpp::meta::traits::has_value_constant_v<IntegralKat, ::llcpp::LL_FALSE>	// value
	&& ::llcpp::meta::traits::has_value_constant_v<IntegralKat, ::llcpp::LL_TRUE>	// VALUE
	&& ::llcpp::meta::traits::has_mytype_v<IntegralKat>
	&& ::llcpp::meta::traits::has_value_type_u_v<IntegralKat>
//	&& ::llcpp::meta::traits::has_contain_value_type_v<IntegralKat, i32>
	&& ::std::is_same_v<IntegralKat::value_type, IntegralKat::T>
	&& ::std::is_same_v<IntegralKat::value_type, IntegralKat::type>
	&& ::std::is_same_v<IntegralKat::value_type, i8>
	&& ::std::is_same_v<IntegralKat::U, f32>
	&& IntegralKat::value == 'H'
	&& IntegralKat::value == IntegralKat::VALUE;
	
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_integral_type_container_kat,
	::llcpp::meta::traits::kat::IS_WORKING_INTEGRAL_TYPE_CONTAINER,
	"Integral type container" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_DOUBLE_INTEGRAL_TYPE_CONTAINER =
	::llcpp::meta::traits::has_value_type_v<DoubleIntegralKat>
	&& ::llcpp::meta::traits::has_value_constant_v<DoubleIntegralKat, ::llcpp::LL_FALSE>	// value
	&& ::llcpp::meta::traits::has_value_constant_v<DoubleIntegralKat, ::llcpp::LL_TRUE>	// VALUE
	&& ::llcpp::meta::traits::has_mytype_v<DoubleIntegralKat>
	&& ::llcpp::meta::traits::has_value_type_u_v<DoubleIntegralKat>
//	&& ::llcpp::meta::traits::has_contain_value_type_v<DoubleIntegralKat, i32>
	&& ::std::is_same_v<DoubleIntegralKat::value_type, DoubleIntegralKat::T>
	&& ::std::is_same_v<DoubleIntegralKat::value_type, DoubleIntegralKat::type>
	&& ::std::is_same_v<DoubleIntegralKat::value_type, i8>
	&& ::std::is_same_v<DoubleIntegralKat::U, f32>
	&& DoubleIntegralKat::FIRST		== '8'
	&& DoubleIntegralKat::SECOND	== 0.0f
	&& IntegralKat::value == IntegralKat::VALUE;
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_double_integral_type_container_kat,
	::llcpp::meta::traits::kat::IS_WORKING_DOUBLE_INTEGRAL_TYPE_CONTAINER,
	"Double integral type container" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_INTEGRAL_TYPE_CONTAINER_OBJECT =
	::llcpp::meta::traits::has_value_type_v<IntegralObjectKat>
	&& ::llcpp::meta::traits::has_value_constant_v<IntegralObjectKat, ::llcpp::LL_FALSE>	// value
	&& ::llcpp::meta::traits::has_value_constant_v<IntegralObjectKat, ::llcpp::LL_TRUE>	// VALUE
	&& ::llcpp::meta::traits::has_mytype_v<IntegralObjectKat>
	&& ::llcpp::meta::traits::has_value_type_u_v<IntegralObjectKat>
//	&& ::llcpp::meta::traits::has_contain_value_type_v<IntegralObjectKat, i32>
	&& ::std::is_same_v<IntegralObjectKat::value_type, IntegralObjectKat::T>
	&& ::std::is_same_v<IntegralObjectKat::value_type, IntegralObjectKat::type>
	&& ::std::is_same_v<IntegralObjectKat::value_type, KATIntegralstructDef1>
	&& ::std::is_same_v<IntegralObjectKat::U, f32>
	&& IntegralObjectKat::value == kat_integral_struct_def_1
	&& IntegralObjectKat::value == IntegralObjectKat::VALUE;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_integral_type_container_object_kat,
	::llcpp::meta::traits::kat::IS_WORKING_INTEGRAL_TYPE_CONTAINER_OBJECT,
	"Integral type container object" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_DOUBLE_INTEGRAL_TYPE_CONTAINER_OBJECT =
	::llcpp::meta::traits::has_value_type_v<DoubleIntegralObjectKat>
	&& ::llcpp::meta::traits::has_value_constant_v<DoubleIntegralObjectKat, ::llcpp::LL_FALSE>	// value
	&& ::llcpp::meta::traits::has_value_constant_v<DoubleIntegralObjectKat, ::llcpp::LL_TRUE>	// VALUE
	&& ::llcpp::meta::traits::has_mytype_v<DoubleIntegralObjectKat>
	&& ::llcpp::meta::traits::has_value_type_u_v<DoubleIntegralObjectKat>
//	&& ::llcpp::meta::traits::has_contain_value_type_v<DoubleIntegralObjectKat, i32>
	&& ::std::is_same_v<DoubleIntegralObjectKat::value_type, DoubleIntegralObjectKat::T>
	&& ::std::is_same_v<DoubleIntegralObjectKat::value_type, DoubleIntegralObjectKat::type>
	&& ::std::is_same_v<DoubleIntegralObjectKat::value_type, KATIntegralstructDef1>
	&& ::std::is_same_v<DoubleIntegralObjectKat::U, KATIntegralstructDef2>
	&& DoubleIntegralObjectKat::FIRST		== kat_integral_struct_def_1
	&& DoubleIntegralObjectKat::SECOND	== kat_integral_struct_def_2
	&& IntegralKat::value == IntegralKat::VALUE;
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_double_integral_type_container_object_kat,
	::llcpp::meta::traits::kat::IS_WORKING_DOUBLE_INTEGRAL_TYPE_CONTAINER_OBJECT,
	"Double integral type container object" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region Conditional
#pragma region Common
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_CONDITIONAL_TRUE =
	::std::is_same_v<::llcpp::meta::traits::conditional_t<::llcpp::LL_TRUE, u8, i16>, u8>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_conditional_true_kat,
	::llcpp::meta::traits::kat::IS_WORKING_CONDITIONAL_TRUE,
	"Conditional true" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_CONDITIONAL_FALSE =
	::std::is_same_v<::llcpp::meta::traits::conditional_t<::llcpp::LL_FALSE, u8, i16>, i16>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_conditional_false_kat,
	::llcpp::meta::traits::kat::IS_WORKING_CONDITIONAL_FALSE,
	"Conditional false" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_CONDITIONAL_VALUE_TRUE =
	::llcpp::meta::traits::conditional_value_v<::llcpp::LL_TRUE, u8, i16, 0x8, 270> == 0x8;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_conditional_value_true_kat,
	::llcpp::meta::traits::kat::IS_WORKING_CONDITIONAL_VALUE_TRUE,
	"Conditional value true" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_CONDITIONAL_VALUE_FALSE =
	::llcpp::meta::traits::conditional_value_v<::llcpp::LL_FALSE, u8, i16, 0x8, 270> == 270;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_conditional_value_false_kat,
	::llcpp::meta::traits::kat::IS_WORKING_CONDITIONAL_VALUE_FALSE,
	"Conditional value false" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region Compare
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_COMPARE_CONDITIONAL_BIGGER =
	    CompareConditionalBigger::BIGGER_COMPARE
	&&  CompareConditionalBigger::BIGGER_EQ_COMPARE
	&& !CompareConditionalBigger::SMALLER_COMPARE
	&& !CompareConditionalBigger::SMALLER_EQ_COMPARE
	&& !CompareConditionalBigger::EQ_COMPARE;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_compare_conditional_bigger_kat,
	::llcpp::meta::traits::kat::IS_WORKING_COMPARE_CONDITIONAL_BIGGER,
	"Compare conditional bigger" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_COMPARE_CONDITIONAL_SMALLER =
	   !CompareConditionalSmaller::BIGGER_COMPARE
	&& !CompareConditionalSmaller::BIGGER_EQ_COMPARE
	&&  CompareConditionalSmaller::SMALLER_COMPARE
	&&  CompareConditionalSmaller::SMALLER_EQ_COMPARE
	&& !CompareConditionalSmaller::EQ_COMPARE;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_compare_conditional_smaller_kat,
	::llcpp::meta::traits::kat::IS_WORKING_COMPARE_CONDITIONAL_SMALLER,
	"Compare conditional smaller" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_COMPARE_CONDITIONAL_EQUAL =
	   !CompareConditionalEqual::BIGGER_COMPARE
	&&  CompareConditionalEqual::BIGGER_EQ_COMPARE
	&& !CompareConditionalEqual::SMALLER_COMPARE
	&&  CompareConditionalEqual::SMALLER_EQ_COMPARE
	&&  CompareConditionalEqual::EQ_COMPARE;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_compare_conditional_equal_kat,
	::llcpp::meta::traits::kat::IS_WORKING_COMPARE_CONDITIONAL_EQUAL,
	"Compare conditional equal" __LL_IS_NOT_WORKING_STR
);

#pragma endregion

#pragma endregion
#pragma region GetFirstAnyything
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_FIRST_COINCIDENCE_EMPTY =
	::std::is_same_v<GetFirstCoincidenceEmpty, ::llcpp::Emptyclass>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_first_coincidence_empty_kat,
	::llcpp::meta::traits::kat::IS_WORKING_GET_FIRST_COINCIDENCE_EMPTY,
	"Get first coincidence empty" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_FIRST_COINCIDENCE_U8 =
	::std::is_same_v<GetFirstCoincidenceU8, u8>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_first_coincidence_u8_kat,
	::llcpp::meta::traits::kat::IS_WORKING_GET_FIRST_COINCIDENCE_U8,
	"Get first coincidence u8" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_FIRST_DIFFERENCE_EMPTY =
	::std::is_same_v<GetFirstDifferenceEmpty, ::llcpp::Emptyclass>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_first_difference_empty_kat,
	::llcpp::meta::traits::kat::IS_WORKING_GET_FIRST_DIFFERENCE_EMPTY,
	"Get first difference empty" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_FIRST_DIFFERENCE_U8 =
	::std::is_same_v<GetFirstDifferenceU8, u8>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_first_difference_u8_kat,
	::llcpp::meta::traits::kat::IS_WORKING_GET_FIRST_DIFFERENCE_U8,
	"Get first difference u8" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region TypeUpdate
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_PROMOTION =
	   ::std::is_same_v<::llcpp::meta::traits::type_promote_u<u8>,   u16>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<u16>,  u32>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<u32>,  u64>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<u64>,  u128>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<u128>, u256>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<u256>, u256>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<i8>,   i16>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<i16>,  i32>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<i32>,  i64>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<i64>,  i128>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<i128>, i256>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<i256>, i256>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<f32>,  f64>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<f64>,  f128>
	&& ::std::is_same_v<::llcpp::meta::traits::type_promote_u<f128>, f128>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_promotion_kat,
	::llcpp::meta::traits::kat::IS_WORKING_PROMOTION,
	"Type promote" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_DEMOTION =
	   ::std::is_same_v<::llcpp::meta::traits::type_demote_u<u8>,   u8>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<u16>,  u8>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<u32>,  u16>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<u64>,  u32>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<u128>, u64>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<u256>, u128>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<i8>,   i8>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<i16>,  i8>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<i32>,  i16>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<i64>,  i32>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<i128>, i64>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<i256>, i128>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<f32>,  f32>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<f64>,  f32>
	&& ::std::is_same_v<::llcpp::meta::traits::type_demote_u<f128>, f64>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_demotion_kat,
	::llcpp::meta::traits::kat::IS_WORKING_DEMOTION,
	"Type demote" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_SIGNALIZE =
	   ::std::is_same_v<::llcpp::meta::traits::type_signalize_u<u8>,   i8>
	&& ::std::is_same_v<::llcpp::meta::traits::type_signalize_u<u16>,  i16>
	&& ::std::is_same_v<::llcpp::meta::traits::type_signalize_u<u32>,  i32>
	&& ::std::is_same_v<::llcpp::meta::traits::type_signalize_u<u64>,  i64>
	&& ::std::is_same_v<::llcpp::meta::traits::type_signalize_u<u128>, i128>
	&& ::std::is_same_v<::llcpp::meta::traits::type_signalize_u<u256>, i256>
	&& ::std::is_same_v<::llcpp::meta::traits::type_signalize_u<i8>,   i8>
	&& ::std::is_same_v<::llcpp::meta::traits::type_signalize_u<i16>,  i16>
	&& ::std::is_same_v<::llcpp::meta::traits::type_signalize_u<i32>,  i32>
	&& ::std::is_same_v<::llcpp::meta::traits::type_signalize_u<i64>,  i64>
	&& ::std::is_same_v<::llcpp::meta::traits::type_signalize_u<i128>, i128>
	&& ::std::is_same_v<::llcpp::meta::traits::type_signalize_u<i256>, i256>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_signalize_kat,
	::llcpp::meta::traits::kat::IS_WORKING_SIGNALIZE,
	"Type signalize" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_UNSIGNALIZE =
	   ::std::is_same_v<::llcpp::meta::traits::type_unsignalize_u<u8>,   u8>
	&& ::std::is_same_v<::llcpp::meta::traits::type_unsignalize_u<u16>,  u16>
	&& ::std::is_same_v<::llcpp::meta::traits::type_unsignalize_u<u32>,  u32>
	&& ::std::is_same_v<::llcpp::meta::traits::type_unsignalize_u<u64>,  u64>
	&& ::std::is_same_v<::llcpp::meta::traits::type_unsignalize_u<u128>, u128>
	&& ::std::is_same_v<::llcpp::meta::traits::type_unsignalize_u<u256>, u256>
	&& ::std::is_same_v<::llcpp::meta::traits::type_unsignalize_u<i8>,   u8>
	&& ::std::is_same_v<::llcpp::meta::traits::type_unsignalize_u<i16>,  u16>
	&& ::std::is_same_v<::llcpp::meta::traits::type_unsignalize_u<i32>,  u32>
	&& ::std::is_same_v<::llcpp::meta::traits::type_unsignalize_u<i64>,  u64>
	&& ::std::is_same_v<::llcpp::meta::traits::type_unsignalize_u<i128>, u128>
	&& ::std::is_same_v<::llcpp::meta::traits::type_unsignalize_u<i256>, u256>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_unsignalize_kat,
	::llcpp::meta::traits::kat::IS_WORKING_UNSIGNALIZE,
	"Type unsignalize" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region Range
__LL_VAR_INLINE__ constexpr ll_bool_t IS_MAX_VALUE =
	   ::llcpp::MAX_VALUE<u8>	== 0xff
	&& ::llcpp::MAX_VALUE<u16>	== 0xffff
	&& ::llcpp::MAX_VALUE<u32>	== 0xffffffff
	&& ::llcpp::MAX_VALUE<u64>	== 0xffffffffffffffff
	&& ::llcpp::MAX_VALUE<i8>	== 0x7f
	&& ::llcpp::MAX_VALUE<i16>	== 0x7fff
	&& ::llcpp::MAX_VALUE<i32>	== 0x7fffffff
	&& ::llcpp::MAX_VALUE<i64>	== 0x7fffffffffffffff;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_max_value_kat,
	::llcpp::meta::traits::kat::IS_MAX_VALUE,
	"Max value"
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_MIN_VALUE =
	   ::llcpp::MIN_VALUE<u8>	== 0x0
	&& ::llcpp::MIN_VALUE<u16>	== 0x0
	&& ::llcpp::MIN_VALUE<u32>	== 0x0
	&& ::llcpp::MIN_VALUE<u64>	== 0x0
	&& ::llcpp::MIN_VALUE<i8>	== -0x80
	&& ::llcpp::MIN_VALUE<i16>	== -0x8000
	&& ::llcpp::MIN_VALUE<i32>	== -0x80000000
	&& ::llcpp::MIN_VALUE<i64>	== -0x8000000000000000;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_min_value_kat,
	::llcpp::meta::traits::kat::IS_MIN_VALUE,
	"Min value" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_ZERO_VALUE =
	   ::llcpp::ZERO_VALUE<u8>	== 0x0
	&& ::llcpp::ZERO_VALUE<u16>	== 0x0
	&& ::llcpp::ZERO_VALUE<u32>	== 0x0
	&& ::llcpp::ZERO_VALUE<u64>	== 0x0
	&& ::llcpp::ZERO_VALUE<i8>	== 0x0
	&& ::llcpp::ZERO_VALUE<i16>	== 0x0
	&& ::llcpp::ZERO_VALUE<i32>	== 0x0
	&& ::llcpp::ZERO_VALUE<i64>	== 0x0;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_zero_value_kat,
	::llcpp::meta::traits::kat::IS_ZERO_VALUE,
	"Zero value" __LL_IS_NOT_WORKING_STR
);

#pragma endregion

__LL_NODISCARD__ constexpr ::llcpp::string type_traits_kats() noexcept {
	#pragma region HasTypesConstants
	::llcpp::string result = ::llcpp::meta::traits::kat::has_value_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::has_value_constant_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::has_hash_type_kat();
	if(result) return result;

	#pragma endregion
	#pragma region Pair
	result = ::llcpp::meta::traits::kat::has_pair_first_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::has_pair_second_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_pair_kat();
	if(result) return result;

	#pragma endregion
	#pragma region Container
	result = ::llcpp::meta::traits::kat::has_container_type_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::has_container_type_u_kat();
	if(result) return result;

	#pragma endregion
	#pragma region TypeContainer
	result = ::llcpp::meta::traits::kat::is_working_type_container_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_double_type_container_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_integral_type_container_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_double_integral_type_container_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_integral_type_container_object_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_double_integral_type_container_object_kat();
	if(result) return result;

	#pragma endregion
	#pragma region Conditional
	#pragma region Common
	result = ::llcpp::meta::traits::kat::is_working_conditional_true_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_conditional_false_kat();
	if(result) return result;

	result = ::llcpp::meta::traits::kat::is_working_conditional_value_true_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_conditional_value_false_kat();
	if(result) return result;

	#pragma endregion
	#pragma region Compare
	result = ::llcpp::meta::traits::kat::is_working_compare_conditional_bigger_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_compare_conditional_smaller_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_compare_conditional_equal_kat();
	if(result) return result;

	#pragma endregion

	#pragma endregion
	#pragma region GetFirstAnyything
	result = ::llcpp::meta::traits::kat::is_working_first_coincidence_empty_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_first_coincidence_u8_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_first_difference_empty_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_first_difference_u8_kat();
	if(result) return result;

	#pragma endregion
	#pragma region GetFirstAnyything
	result = ::llcpp::meta::traits::kat::is_working_promotion_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_demotion_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_signalize_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_unsignalize_kat();
	if(result) return result;

	#pragma endregion
	#pragma region Range
	result = ::llcpp::meta::traits::kat::is_working_max_value_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_min_value_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_zero_value_kat();
	if(result) return result;

	#pragma endregion

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::traits::kat::type_traits_kats() == LL_NULLPTR, "type_traits KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS
} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPETRAITS_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_TYPETRAITS_EXTRA_HPP_)
		#if LLANYLIB_TYPETRAITS_EXTRA_MAYOR_ != 12 || LLANYLIB_TYPETRAITS_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "type_traits.hpp(extra) version error!"
			#else
				#error "type_traits.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_TYPETRAITS_EXTRA_MAYOR_ || LLANYLIB_TYPETRAITS_EXTRA_MINOR_

	#else
		#define LLANYLIB_TYPETRAITS_EXTRA_HPP_
		#define LLANYLIB_TYPETRAITS_EXTRA_MAYOR_ 12
		#define LLANYLIB_TYPETRAITS_EXTRA_MINOR_ 0

namespace llcpp {
namespace meta {
namespace traits {

template<ll_bool_t _VALUE, class _U>
using BoolConstant		= ::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, _VALUE, _U>;
template<class _U>
using BoolTrueConstant	= ::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, ::llcpp::LL_TRUE, _U>;
template<class _U>
using BoolFalseConstant = ::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, ::llcpp::LL_FALSE, _U>;
template<class _U>
using TrueType			= ::llcpp::meta::traits::BoolConstant<::llcpp::LL_TRUE, _U>;
template<class _U>
using FalseType			= ::llcpp::meta::traits::BoolConstant<::llcpp::LL_FALSE, _U>;

} // namespace traits
} // namespace meta
} // namespace llcpp

	#endif // LLANYLIB_TYPETRAITS_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
