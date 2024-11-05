//////////////////////////////////////////////
//	traits_parameter_pack.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_parameter_pack.hpp(incomplete) version error!"
		#else
			#error "traits_parameter_pack.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_HPP_)
#define LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_HPP_
#define LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_TRAITSPARAMETERPACK_INCOMPLETE_MINOR_ 0

#include "type_traits.hpp"

namespace llcpp {
namespace meta {
namespace traits {
namespace __traits__ {

template<class _T, class... uArgs>
struct FirstType;
template<class _T>
struct FirstType<_T>;

} // namespace __traits__

template <class... Args>
struct parameter_pack_operations;
template <class T>
struct parameter_pack_operations<T>;
template <>
struct parameter_pack_operations<>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TRAITSPARAMETERPACK_HPP_)
	#if LLANYLIB_TRAITSPARAMETERPACK_MAYOR_ != 11 || LLANYLIB_TRAITSPARAMETERPACK_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_parameter_pack.hpp version error!"
		#else
			#error "traits_parameter_pack.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSPARAMETERPACK_MAYOR_ || LLANYLIB_TRAITSPARAMETERPACK_MINOR_

#else
#define LLANYLIB_TRAITSPARAMETERPACK_HPP_
#define LLANYLIB_TRAITSPARAMETERPACK_MAYOR_ 11
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
	static constexpr u64 SIZE					= sizeof...(Args);
	static constexpr ll_bool_t EMPTY			= (size == llcpp::ZERO_U64);
	static constexpr ll_bool_t HAS_A_POINTER	= (std::is_pointer_v<Args> || ...);
	static constexpr ll_bool_t HAS_AN_ARRAY		= (std::is_array_v<Args> || ...);
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
	static constexpr u64 SIZE					= 1ull;
	static constexpr ll_bool_t EMPTY			= llcpp::FALSE;
	static constexpr ll_bool_t HAS_A_POINTER	= std::is_pointer_v<T>;
	static constexpr ll_bool_t HAS_AN_ARRAY		= std::is_array_v<T>;
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
	static constexpr u64 SIZE					= 0ull;
	static constexpr ll_bool_t EMPTY			= llcpp::TRUE;
	static constexpr ll_bool_t HAS_A_POINTER	= llcpp::FALSE;
	static constexpr ll_bool_t HAS_AN_ARRAY		= llcpp::FALSE;
};

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSPARAMETERPACK_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
