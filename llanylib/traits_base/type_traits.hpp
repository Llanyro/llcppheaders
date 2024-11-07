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
struct type_container;
template<class _T, class _U>
struct double_type_container;

// SFINAE checker for signatures
template<class _U, class _Signature, _Signature A>
struct SignatureChecker;

template<class _T, class _U, _T _VALUE>
struct integral_constant_container;

template<ll_bool_t _CONDITION, class _T, class _U>
struct conditional;
template<class _T, class _U>
struct conditional<llcpp::FALSE, _T, _U>;

template<ll_bool_t _CONDITION, class _T, class _U, _T _ELEM_1, _U _ELEM_2>
struct conditional_value;
template<class _T, class _U, _T _ELEM_1, _U _ELEM_2>
struct conditional_value<llcpp::FALSE, _T, _U, _ELEM_1, _ELEM_2>;

template<class _T, class _U, class _OnEqual = llcpp::Emptyclass>
struct compare_conditional;

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
using i128 = std::pair<i64, i64>;
using i256 = std::pair<i128, i128>;

using u128 = std::pair<u64, u64>;
using u256 = std::pair<u128, u128>;

namespace meta {
namespace traits {

template<class _T>
struct type_container {
	// Class related
	using _MyType	= type_container;

	// Types and enums
	using T			= _T;
};
template<class _T, class _U>
struct double_type_container {
	// Class related
	using _MyType	= double_type_container;

	// Types and enums
	using T			= _T;
	using U			= _U;
};

// SFINAE checker for signatures
template<class _U, class _Signature, _Signature A>
struct SignatureChecker {};

template<class _T, class _U, _T _VALUE>
struct integral_constant_container {
	// Class related
	using _MyType			= integral_constant_container;
	using integral_constant	= std::integral_constant<_T, _VALUE>;
	using container			= traits::type_container<_U>;

	// Types and enums
	using T					= _T;
	using U					= _U;

	// Expresions
	static constexpr T VALUE = integral_constant::value;
};

template<ll_bool_t _VALUE, class _U>
using bool_constant_container = traits::integral_constant_container<ll_bool_t, _U, _VALUE>;

template<class _U>
using true_type = traits::bool_constant_container<llcpp::TRUE, _U>;
template<class _U>
using false_type = traits::bool_constant_container<llcpp::FALSE, _U>;

#pragma region Conditional
template<ll_bool_t _CONDITION, class _T, class _U>
struct conditional {
	// Class related
	using _MyType	= conditional;

	// Types and enums
	using type		= _T;
	using T			= _T;
	using U			= _U;

	// Expresions
	static constexpr ll_bool_t CONDITION	= _CONDITION;
};
template<class _T, class _U>
struct conditional<llcpp::FALSE, _T, _U> {
	// Class related
	using _MyType	= conditional;

	// Types and enums
	using type		= _U;
	using T			= _T;
	using U			= _U;

	// Expresions
	static constexpr ll_bool_t CONDITION	= llcpp::FALSE;
};
template<ll_bool_t CONDITION, class T, class U>
using conditional_t = conditional<CONDITION, T, U>::type;

template<ll_bool_t _CONDITION, class _T, class _U, _T _ELEM_1, _U _ELEM_2>
struct conditional_value {
	// Class related
	using _MyType	= conditional_value;

	// Types and enums
	using type		= _T;
	using T			= _T;
	using U			= _U;

	// Expresions
	static constexpr ll_bool_t CONDITION 	= _CONDITION;
	static constexpr _T VALUE				= _ELEM_1;
	static constexpr _T ELEM_1				= _ELEM_1;
	static constexpr _U ELEM_2				= _ELEM_2;
};
template<class _T, class _U, _T _ELEM_1, _U _ELEM_2>
struct conditional_value<llcpp::FALSE, _T, _U, _ELEM_1, _ELEM_2> {
	// Class related
	using _MyType	= conditional_value;

	// Types and enums
	using type		= _U;
	using T			= _T;
	using U			= _U;

	// Expresions
	static constexpr ll_bool_t CONDITION	= _CONDITION;
	static constexpr _U VALUE				= _ELEM_2;
	static constexpr _T ELEM_1				= _ELEM_1;
	static constexpr _U ELEM_2				= _ELEM_2;
};

template<bool CONDITION, class _T, class _U, _T _ELEM_1, _U _ELEM_2>
__LL_VAR_INLINE__ constexpr traits::conditional_t<CONDITION, _T, _U> conditional_value_v = conditional_value<CONDITION, _T, _U, _ELEM_1, _ELEM_2>::VALUE;
template<bool CONDITION, class _T, _T _ELEM_1, _T _ELEM_2>
__LL_VAR_INLINE__ constexpr _T conditional_value_simple_v = conditional_value<CONDITION, _T, _T, _ELEM_1, _ELEM_2>::VALUE;

template<class _T, class _U, class _OnEqual = llcpp::Emptyclass>
struct compare_conditional {
	public:
		// Class related
		using _MyType	= compare_conditional;

		// Types and enums
		using T			= _T;
		using U			= _U;
		using OnEqual	= _OnEqual;

		// Comparation expresions
		static constexpr ll_bool_t BIGGER_COMPARE		= sizeof(T) > sizeof(U);
		static constexpr ll_bool_t BIGGER_EQ_COMPARE	= sizeof(T) >= sizeof(U);
		static constexpr ll_bool_t SMALLER_COMPARE		= sizeof(T) < sizeof(U);
		static constexpr ll_bool_t SMALLER_EQ_COMPARE	= sizeof(T) <= sizeof(U);
		static constexpr ll_bool_t EQ_COMPARE			= sizeof(T) < sizeof(U);

	private:
		using __bigger	= traits::conditional_t<BIGGER_COMPARE, T, U>;
		using __smaller	= traits::conditional_t<SMALLER_COMPARE, T, U>;

	public:
		using bigger		= traits::conditional_t<EQ_COMPARE, OnEqual, __bigger>;
		using smaller		= traits::conditional_t<EQ_COMPARE, OnEqual, __smaller>;

		// Returrns first type on bigger or equal
		using bigger_eq		= traits::conditional_t<BIGGER_EQ_COMPARE, T, U>;
		// Returrns first type on smaller or equal
		using smaller_eq	= traits::conditional_t<SMALLER_EQ_COMPARE, T, U>;
};

template<class T, class U, class OnEqual = llcpp::Emptyclass>
using type_bigger_of_two_t = traits::compare_conditional<T, U, OnEqual>::bigger;

template<class T, class U, class OnEqual = llcpp::Emptyclass>
using type_smaller_of_two_t = traits::compare_conditional<T, U, OnEqual>::smaller;

#pragma endregion

// [TOFIX]
namespace dev {

struct Testing {
	int a;
	virtual ~Testing() {}
};

template<class _T>
struct test_a {
	// Class related
	using _MyType	= test_a;

	// Types and enums
	using T			= _T;

	// Expresions
	static constexpr ll_bool_t IS_VIRTUAL	= std::has_virtual_destructor_v<T>;
	static constexpr u64 SIZEOF				= sizeof(T);
	static constexpr u64 SIZEOF_OFFSET		= (IS_VIRTUAL ? sizeof(void*) : 0);
	static constexpr u64 REAL_SIZEOF		= SIZEOF - SIZEOF_OFFSET;
};

} // namespace dev

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPETRAITS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
