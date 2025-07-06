//////////////////////////////////////////////
//	types_big.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPESBIG_HPP_) // Guard && version protector
	#if LLANYLIB_TYPESBIG_MAYOR_ != 12 || LLANYLIB_TYPESBIG_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "types_big.hpp version error!"
		#else
			#error "types_big.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPESBIG_MAYOR_ || LLANYLIB_TYPESBIG_MINOR_

#elif !defined(LLANYLIB_TYPESBIG_HPP_)
	#define LLANYLIB_TYPESBIG_HPP_
	#define LLANYLIB_TYPESBIG_MAYOR_ 12
	#define LLANYLIB_TYPESBIG_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/pair.hpp>
#else
	#include "pair.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {

// [TOFIX]
// Update types to Integer (array of bytes)
using i128 = ::llcpp::meta::pair<i64>;
using i256 = ::llcpp::meta::pair<i128>;
using u128 = ::llcpp::meta::pair<u64>;
using u256 = ::llcpp::meta::pair<u128>;

using Hash128		= u128;		// 128 bits Hash
using Hash256		= u256;		// 256 bits Hash

} // namespace llcpp

#endif // LLANYLIB_TYPESBIG_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
