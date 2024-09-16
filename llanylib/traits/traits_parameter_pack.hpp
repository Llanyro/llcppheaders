//////////////////////////////////////////////
//	traits_parameter_pack.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSPARAMETERPACK_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSPARAMETERPACK_MAYOR_ != 10 || LLANYLIB_TRAITSPARAMETERPACK_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_parameter_pack.hpp version error!"
		#else
			#error "traits_parameter_pack.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSPARAMETERPACK_MAYOR_ || LLANYLIB_TRAITSPARAMETERPACK_MINOR_

#else !defined(LLANYLIB_TRAITSPARAMETERPACK_HPP_)
#define LLANYLIB_TRAITSPARAMETERPACK_HPP_
#define LLANYLIB_TRAITSPARAMETERPACK_MAYOR_ 10
#define LLANYLIB_TRAITSPARAMETERPACK_MINOR_ 0

#include "type_traits.hpp"

namespace llcpp {
namespace meta {
namespace traits {
namespace __traits__ {

template<class _T, class... uArgs>
struct FirstType {
	// Class related
	using _MyType	= FirstType;

	// Types and enums
	using T			= _T;
	using next		= FirstType<uArgs...>;
};
template<class _T>
struct FirstType<_T> {
	// Class related
	using _MyType	= FirstType;

	// Types and enums
	using T			= _T;
	using next		= llcpp::EmptyStruct;
};

} // namespace __traits__

template <class... Args>
struct parameter_pack_operations {
	// Class related
	using _MyType			= parameter_pack_operations;

	using pack_first		= typename traits::__traits__::FirstType<Args...>;
	using get_first_type	= typename traits::__traits__::FirstType<Args...>::T;

	// Expresions
	static constexpr u64 size					= sizeof...(Args);
	static constexpr ll_bool_t empty			= (size == llcpp::ZERO_UI64);
	static constexpr ll_bool_t has_a_pointer	= (std::is_pointer_v<Args> || ...);
	static constexpr ll_bool_t has_a_array		= (std::is_array_v<Args> || ...);
};
template <class T>
struct parameter_pack_operations<T> {
	// Class related
	using _MyType			= parameter_pack_operations;

	// Types and enums
	using FirstType			= traits::__traits__::FirstType<T>;
	using pack_first		= typename FirstType;
	using get_first_type	= typename pack_first::T;

	// Expresions
	static constexpr u64 size					= 1ull;
	static constexpr ll_bool_t empty			= llcpp::FALSE;
	static constexpr ll_bool_t has_a_pointer	= std::is_pointer_v<T>;
	static constexpr ll_bool_t has_a_array		= std::is_array_v<T>;
};
template <>
struct parameter_pack_operations<> {
	// Class related
	using _MyType			= parameter_pack_operations;

	// Types and enums
	using FirstType			= traits::__traits__::FirstType<void>;
	using pack_first		= FirstType;
	using get_first_type	= pack_first::T;

	// Expresions
	static constexpr u64 size					= llcpp::ZERO_UI64;
	static constexpr ll_bool_t empty			= llcpp::TRUE;
	static constexpr ll_bool_t has_a_pointer	= llcpp::FALSE;
	static constexpr ll_bool_t has_a_array		= llcpp::FALSE;
};

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSPARAMETERPACK_HPP_
