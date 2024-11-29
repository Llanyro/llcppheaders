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
class FirstType;
template<class _T>
class FirstType<_T>;

} // namespace __traits__

template <class... Args>
class ParameterPackOperations;
template <class T>
class ParameterPackOperations<T>;
template <>
class ParameterPackOperations<>;

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

template<class _T, class... _Args>
class FirstType {
	public:
		// Class related
		using _MyType	= FirstType;

		// Types and enums
		using T			= _T;
		using Next		= ::llcpp::meta::traits::__traits__::FirstType<_Args...>;
};
template<class _T>
class FirstType<_T> {
	public:
		// Class related
		using _MyType	= FirstType;

		// Types and enums
		using T			= _T;
		using Next		= ::llcpp::Emptyclass;
};

} // namespace __traits__

template<class... _Args>
class ParameterPackOperations {
	public:
		// Class related
		using _MyType			= ParameterPackOperations;

		using FirstType		= ::llcpp::meta::traits::__traits__::FirstType<_Args...>;
		using PackFirst		= FirstType;
		using pack_first_t	= PackFirst::T;

	public:
		// Expresions
		static constexpr u64 SIZE					= sizeof...(_Args);
		static constexpr ll_bool_t EMPTY			= (SIZE == ::llcpp::ZERO_VALUE<u64>);
		static constexpr ll_bool_t HAS_A_POINTER	= (::std::is_pointer_v<_Args> || ...);
		static constexpr ll_bool_t HAS_AN_ARRAY		= (::std::is_array_v<_Args> || ...);
};
template<class T>
class ParameterPackOperations<T> {
	public:
		// Class related
		using _MyType			= ParameterPackOperations;

		// Types and enums
		using FirstType			= ::llcpp::meta::traits::__traits__::FirstType<T>;
		using PackFirst			= FirstType;
		using get_first_type	= PackFirst::T;

	public:
		// Expresions
		static constexpr u64 SIZE					= 1ull;
		static constexpr ll_bool_t EMPTY			= ::llcpp::FALSE;
		static constexpr ll_bool_t HAS_A_POINTER	= ::std::is_pointer_v<T>;
		static constexpr ll_bool_t HAS_AN_ARRAY		= ::std::is_array_v<T>;
};
template <>
class ParameterPackOperations<> {
	public:
		// Class related
		using _MyType		= ParameterPackOperations;

		// Types and enums
		using FirstType		= ::llcpp::meta::traits::__traits__::FirstType<void>;
		using PackFirst		= FirstType;
		using pack_first_t	= PackFirst::T;

	public:
		// Expresions
		static constexpr u64 SIZE					= ::llcpp::ZERO_VALUE<u64>;
		static constexpr ll_bool_t EMPTY			= ::llcpp::TRUE;
		static constexpr ll_bool_t HAS_A_POINTER	= ::llcpp::FALSE;
		static constexpr ll_bool_t HAS_AN_ARRAY		= ::llcpp::FALSE;
};

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSPARAMETERPACK_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
