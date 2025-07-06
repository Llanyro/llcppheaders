//////////////////////////////////////////////
//	pair.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_PAIR_HPP_) // Guard && version protector
	#if LLANYLIB_PAIR_MAYOR_ != 12 || LLANYLIB_PAIR_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "pair.hpp version error!"
		#else
			#error "pair.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_PAIR_MAYOR_ || LLANYLIB_PAIR_MINOR_

#elif !defined(LLANYLIB_PAIR_HPP_)
	#define LLANYLIB_PAIR_HPP_
	#define LLANYLIB_PAIR_MAYOR_ 12
	#define LLANYLIB_PAIR_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/types.hpp>
#else
	#include "types.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {

// This is a pair struct that cannot have an empty type
//	If type is ::llcpp::Emptyclass or void no attribute will be generated
// If both are empty, stuct will be empty too (using only 1 byte of size in worst scenarios)
template<class T, class U = T>
struct pair_none_empty { T first; U second; };
template<class T>
struct pair_none_empty<T, ::llcpp::Emptyclass> { T first; };
template<class T>
struct pair_none_empty<T, void> { T first; };
template<class U>
struct pair_none_empty<::llcpp::Emptyclass, U> { U second; };
template<class U>
struct pair_none_empty<void, U> { U second; };
template<>
struct pair_none_empty<::llcpp::Emptyclass, ::llcpp::Emptyclass> {};
template<>
struct pair_none_empty<::llcpp::Emptyclass, void> {};
template<>
struct pair_none_empty<void, ::llcpp::Emptyclass> {};
template<>
struct pair_none_empty<void, void> {};

// Alias of pair_none_empty
template<class T, class U = T>
using pair_ne = ::llcpp::meta::pair_none_empty<T, U>;

// Alias of pair_none_empty
template<class T, class U = T>
using pair = ::llcpp::meta::pair_none_empty<T, U>;

template<class T>
using simplest_container = ::llcpp::meta::pair_none_empty<T, ::llcpp::Emptyclass>;

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_PAIR_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
