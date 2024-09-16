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

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPETRAITS_HPP_
