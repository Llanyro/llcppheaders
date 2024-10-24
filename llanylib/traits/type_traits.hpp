//////////////////////////////////////////////
//	type_traits.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPETRAITS_HPP_) // Guard && version protector
	#if LLANYLIB_TYPETRAITS_MAYOR_ != 10 || LLANYLIB_TYPETRAITS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "type_traits.hpp version error!"
		#else
			#error "type_traits.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TYPETRAITS_MAYOR_ || LLANYLIB_TYPETRAITS_MINOR_

#else !defined(LLANYLIB_TYPETRAITS_HPP_)
#define LLANYLIB_TYPETRAITS_HPP_
#define LLANYLIB_TYPETRAITS_MAYOR_ 10
#define LLANYLIB_TYPETRAITS_MINOR_ 0

#include "../types_simple.hpp"

#include <type_traits>

namespace llcpp {
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
template<class _U, class _Signature, _Signature A> struct SignatureChecker {};

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
template<ll_bool_t _CONDITION, class T, class U>
struct conditional {
	// Class related
	using _MyType	= conditional;

	// Types and enums
	using type		= T;

	// Expresions
	static constexpr ll_bool_t CONDITION	= _CONDITION;
};
template<class T, class U>
struct conditional<llcpp::FALSE, T, U> {
	// Class related
	using _MyType	= conditional;

	// Types and enums
	using type		= U;

	// Expresions
	static constexpr ll_bool_t CONDITION	= llcpp::FALSE;
};
template<ll_bool_t CONDITION, class T, class U>
using conditional_t = conditional<CONDITION, T, U>::type;

template<ll_bool_t _CONDITION, class T, class U, T _ELEM_1, U _ELEM_2>
struct conditional_value {
	// Class related
	using _MyType	= conditional_value;

	// Types and enums
	using type		= T;

	// Expresions
	static constexpr ll_bool_t CONDITION 	= _CONDITION;
	static constexpr T VALUE				= _ELEM_1;
	static constexpr T ELEM_1				= _ELEM_1;
	static constexpr U ELEM_2				= _ELEM_2;
};
template<class T, class U, T _ELEM_1, U _ELEM_2>
struct conditional_value<llcpp::FALSE, T, U, _ELEM_1, _ELEM_2> {
	// Class related
	using _MyType	= conditional_value;

	// Types and enums
	using type		= U;

	// Expresions
	static constexpr ll_bool_t CONDITION	= _CONDITION;
	static constexpr U VALUE				= _ELEM_2;
	static constexpr T ELEM_1				= _ELEM_1;
	static constexpr U ELEM_2				= _ELEM_2;
};

template<bool CONDITION, class T, class U, T _ELEM_1, U _ELEM_2>
__LL_VAR_INLINE__ constexpr traits::conditional_t<CONDITION, T, U> conditional_value_v = conditional_value<CONDITION, T, U, _ELEM_1, _ELEM_2>::VALUE;
template<bool CONDITION, class T, T _ELEM_1, T _ELEM_2>
__LL_VAR_INLINE__ constexpr T conditional_value_simple_v = conditional_value<CONDITION, T, T, _ELEM_1, _ELEM_2>::VALUE;

#pragma endregion

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
