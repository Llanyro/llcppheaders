//////////////////////////////////////////////
//	type_traits.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TYPETRAITS_INCOMPLETE_HPP_)
	#if LLANYLIB_TYPETRAITS_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TYPETRAITS_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "type_traits.hpp(incomplete) version error!"
		#else
			#error "type_traits.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPETRAITS_INCOMPLETE_MAYOR_ || LLANYLIB_TYPETRAITS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TYPETRAITS_INCOMPLETE_HPP_)
#define LLANYLIB_TYPETRAITS_INCOMPLETE_HPP_
#define LLANYLIB_TYPETRAITS_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_TYPETRAITS_INCOMPLETE_MINOR_ 0

#include "../types_base/types_base_extra.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<class _T>
class TypeContainer;
template<class _T, class _U>
class DoubleTypeContainer;
template<class _T, _T _VALUE, class _U>
class IntegralConstantContainer;

template<ll_bool_t _CONDITION, class _T, class _U>
class Conditional;
template<class _T, class _U>
class Conditional<llcpp::FALSE, _T, _U>;

template<ll_bool_t _CONDITION, class _T, class _U, _T _ELEM_1, _U _ELEM_2>
class ConditionalValue;
template<class _T, class _U, _T _ELEM_1, _U _ELEM_2>
class ConditionalValue<llcpp::FALSE, _T, _U, _ELEM_1, _ELEM_2>;
template<class _T, class _U, class _OnEqual = llcpp::Emptyclass>
class CompareConditional;

template<class _T>
class RangeChecker;

} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TYPETRAITS_HPP_)
	#if LLANYLIB_TYPETRAITS_MAYOR_ != 11 || LLANYLIB_TYPETRAITS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "type_traits.hpp version error!"
		#else
			#error "type_traits.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPETRAITS_MAYOR_ || LLANYLIB_TYPETRAITS_MINOR_

#else
#define LLANYLIB_TYPETRAITS_HPP_
#define LLANYLIB_TYPETRAITS_MAYOR_ 11
#define LLANYLIB_TYPETRAITS_MINOR_ 0

#include "../types_base/types_base_extra.hpp"

#include <type_traits>

namespace llcpp {

// [TOFIX]
// Update types to Integer
using i128 = ::std::pair<i64, i64>;
using i256 = ::std::pair<i128, i128>;

using u128 = ::std::pair<u64, u64>;
using u256 = ::std::pair<u128, u128>;

namespace meta {
namespace traits {

#pragma region Containers
template<class _T>
class TypeContainer {
	public:
		// Class related
		using _MyType	= TypeContainer;

		// Types and enums
		using T			= _T;
};
template<class _T>
using type_container_t = ::llcpp::meta::traits::TypeContainer<_T>::T;

template<class _T, class _U>
class DoubleTypeContainer {
	public:
		// Class related
		using _MyType	= DoubleTypeContainer;

		// Types and enums
		using T			= _T;
		using U			= _U;
};
template<class _T, class _U>
using double_type_container_t = ::llcpp::meta::traits::DoubleTypeContainer<_T, _U>::T;
template<class _T, class _U>
using double_type_container_u = ::llcpp::meta::traits::DoubleTypeContainer<_T, _U>::U;

template<class _T, _T _VALUE, class _U>
class IntegralConstantContainer {
	public:
		// Class related
		using _MyType			= IntegralConstantContainer;

		// Types and enums
		using T					= _T;
		using U					= _U;

	public:
		// Expresions
		static constexpr T VALUE = _VALUE;
		static constexpr T value = _VALUE;	// used in standard
};

template<class _T, _T _VALUE, class _U>
using integral_constant_container_t = ::llcpp::meta::traits::IntegralConstantContainer<_T, _VALUE, _U>::T;
template<class _T, _T _VALUE, class _U>
using integral_constant_container_u = ::llcpp::meta::traits::IntegralConstantContainer<_T, _VALUE, _U>::U;
template<class _T, _T _VALUE, class _U>
__LL_VAR_INLINE__ constexpr _T integral_constant_container_v = traits::IntegralConstantContainer<_T, _VALUE, _U>::VALUE;

#pragma endregion
#pragma region LogicContainers

template<class T, class U, class W>
using IsSameTypeContainer = ::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, ::std::is_same_v<T, U>, W>;
template<class T, class U, class W>
using IsNotSameTypeContainer = ::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, !::std::is_same_v<T, U>, W>;

#pragma endregion
#pragma region Conditional
template<ll_bool_t _CONDITION, class _T, class _U>
class Conditional {
	public:
		// Class related
		using _MyType	= Conditional;

		// Types and enums
		using type		= _T;
		using T			= _T;
		using U			= _U;

	public:
		// Expresions
		static constexpr ll_bool_t CONDITION	= _CONDITION;
};
template<class _T, class _U>
class Conditional<::llcpp::FALSE, _T, _U> {
	public:
		// Class related
		using _MyType	= Conditional;

		// Types and enums
		using type		= _U;
		using T			= _T;
		using U			= _U;

	public:
		// Expresions
		static constexpr ll_bool_t CONDITION	= llcpp::FALSE;
};
template<ll_bool_t CONDITION, class T, class U>
using conditional_t = ::llcpp::meta::traits::Conditional<CONDITION, T, U>::type;

template<ll_bool_t _CONDITION, class _T, class _U, _T _ELEM_1, _U _ELEM_2>
class ConditionalValue {
	public:
		// Class related
		using _MyType	= ConditionalValue;

		// Types and enums
		using type		= _T;
		using T			= _T;
		using U			= _U;

	public:
		// Expresions
		static constexpr ll_bool_t CONDITION 	= _CONDITION;
		static constexpr _T VALUE				= _ELEM_1;
		static constexpr _T ELEM_1				= _ELEM_1;
		static constexpr _U ELEM_2				= _ELEM_2;
};
template<class _T, class _U, _T _ELEM_1, _U _ELEM_2>
class ConditionalValue<llcpp::FALSE, _T, _U, _ELEM_1, _ELEM_2> {
	public:
		// Class related
		using _MyType	= ConditionalValue;

		// Types and enums
		using type		= _U;
		using T			= _T;
		using U			= _U;

	public:
		// Expresions
		static constexpr ll_bool_t CONDITION	= llcpp::FALSE;
		static constexpr _U VALUE				= _ELEM_2;
		static constexpr _T ELEM_1				= _ELEM_1;
		static constexpr _U ELEM_2				= _ELEM_2;
};
template<ll_bool_t CONDITION, class _T, class _U, _T _ELEM_1, _U _ELEM_2>
__LL_VAR_INLINE__ constexpr auto conditional_value_v = ConditionalValue<CONDITION, _T, _U, _ELEM_1, _ELEM_2>::VALUE;
template<ll_bool_t CONDITION, class _T, _T _ELEM_1, _T _ELEM_2>
__LL_VAR_INLINE__ constexpr auto conditional_value_simple_v = ConditionalValue<CONDITION, _T, _T, _ELEM_1, _ELEM_2>::VALUE;

template<class _T, class _U, class _OnEqual = ::llcpp::Emptyclass>
class CompareConditional {
	public:
		// Class related
		using _MyType	= CompareConditional;

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
		static constexpr ll_bool_t EQ_COMPARE			= sizeof(T) < sizeof(U);

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
using type_bigger_of_two_t = ::llcpp::meta::traits::CompareConditional<T, U, OnEqual>::bigger;
template<class T, class U, class OnEqual = llcpp::Emptyclass>
using type_smaller_of_two_t = ::llcpp::meta::traits::CompareConditional<T, U, OnEqual>::smaller;

#pragma endregion
#pragma region Disjunction
template<class T, class... Args>
using GetFirstCoincidence = std::disjunction<
	::llcpp::meta::traits::IsSameTypeContainer<T, typename Args::T, typename Args::U>...,
	::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, ::llcpp::TRUE, llcpp::Emptyclass>
>;

template<class T, class TypeChar, class TypeWChar>
using GetByCharType = GetFirstCoincidence<
	::llcpp::meta::traits::DoubleTypeContainer<ll_char_t, TypeChar>,
	::llcpp::meta::traits::DoubleTypeContainer<ll_wchar_t, TypeWChar>
>;

template<class T, class... Args>
using get_first_coincidence_u = ::llcpp::meta::traits::GetFirstCoincidence<T, Args...>::U;

template<class T, class TypeChar, class TypeWChar>
using get_by_char_type_u = ::llcpp::meta::traits::GetByCharType<T, TypeChar, TypeWChar>::U;

#pragma endregion
#pragma region Conjunction
template<class T, class... Args>
using GetFirstDifference = std::conjunction<
	::llcpp::meta::traits::IsSameTypeContainer<T, typename Args::T, typename Args::U>...,
	::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, ::llcpp::TRUE, llcpp::Emptyclass>
>;

template<class T, class... Args>
using get_first_difference_u = GetFirstCoincidence<T, Args...>::U;

#pragma endregion
#pragma region PrimitiveUpdate
template<class T, ll_bool_t PROMOTE = ::llcpp::TRUE>
using TypePromotion = ::llcpp::meta::traits::GetFirstCoincidence<
	T,
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
>;

template<class T, ll_bool_t SIGNALIZE = ::llcpp::TRUE>
using TypeSigned = ::llcpp::meta::traits::GetFirstCoincidence<
	T,
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
>;

template<class T, ll_bool_t PROMOTE = ::llcpp::TRUE>
using type_promotion_u =	::llcpp::meta::traits::TypePromotion<T, PROMOTE>;
template<class T>
using type_promote_u =		::llcpp::meta::traits::TypePromotion<T, ::llcpp::TRUE>;
template<class T>
using type_demote_u =		::llcpp::meta::traits::TypePromotion<T, ::llcpp::FALSE>;

template<class T, ll_bool_t SIGNALIZE = ::llcpp::TRUE>
using type_signed_u =		::llcpp::meta::traits::TypeSigned<T, SIGNALIZE>;
template<class T>
using type_signalize_u =	::llcpp::meta::traits::TypeSigned<T, ::llcpp::TRUE>;
template<class T>
using type_unsignalize_u =	::llcpp::meta::traits::TypeSigned<T, ::llcpp::FALSE>;

#pragma endregion
#pragma region Limits
template<class _T>
class RangeChecker {
	public:
		// Class related
		using _MyType	= RangeChecker;

		// Types and enums
		using T			= _T;

	public:
		// Expresions
		static constexpr T MAX_VALUE =
			traits::conditional_value_simple_v<
				::std::is_unsigned_v<T>,
				T,
				T(-1),
				((RangeChecker<traits::type_signed_u<T, ::llcpp::FALSE>>::MAX_VALUE) >> 1)
			>;

		static constexpr T MIN_VALUE = _MyType::MAX_VALUE + 1;

	public:
		// Asserts
		static_assert(!::std::is_floating_point_v<T>,
			"Type cannot be floating point! Results are valid but not correct!");
};

#pragma endregion

// [TOFIX]
namespace dev {

class Testing {
	int a;
	virtual ~Testing() {}
};

template<class _T>
class test_a {
	// Class related
	using _MyType	= test_a;

	// Types and enums
	using T			= _T;

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
__LL_VAR_INLINE__ constexpr T MAX_VALUE		= ::llcpp::meta::traits::RangeChecker<T>::MAX_VALUE;
template<class T>
__LL_VAR_INLINE__ constexpr T MIN_VALUE		= ::llcpp::meta::traits::RangeChecker<T>::MIN_VALUE;
template<class T>
__LL_VAR_INLINE__ constexpr T ZERO_VALUE	= T{};

#pragma endregion

} // namespace llcpp

#endif // LLANYLIB_TYPETRAITS_HPP_

#if !defined(LLANYLIB_TYPETRAITS_EXTRA_HPP_) && !defined(LLANYLIB_ERROR_HPP_)
#define LLANYLIB_TYPETRAITS_EXTRA_HPP_

namespace llcpp {
namespace meta {
namespace traits {

template<ll_bool_t _VALUE, class _U>
using BoolConstant		= ::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, _VALUE, _U>;
template<class _U>
using BoolTrueConstant	= ::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, ::llcpp::TRUE, _U>;
template<class _U>
using BoolFalseConstant = ::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, ::llcpp::FALSE, _U>;
template<class _U>
using TrueType			= ::llcpp::meta::traits::BoolConstant<llcpp::TRUE, _U>;
template<class _U>
using FalseType			= ::llcpp::meta::traits::BoolConstant<llcpp::FALSE, _U>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPETRAITS_EXTRA_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
