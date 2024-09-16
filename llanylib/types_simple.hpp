//////////////////////////////////////////////
//	types_simple.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPESSIMPLE_HPP_) // Guard && version protector
	#if LLANYLIB_TYPESSIMPLE_MAYOR_ != 10 || LLANYLIB_TYPESSIMPLE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "types_simple.hpp version error!"
		#else
			#error "types_simple.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TYPESSIMPLE_MAYOR_ || LLANYLIB_TYPESSIMPLE_MINOR_

#else !defined(LLANYLIB_TYPESSIMPLE_HPP_)
#define LLANYLIB_TYPESSIMPLE_HPP_
#define LLANYLIB_TYPESSIMPLE_MAYOR_ 10
#define LLANYLIB_TYPESSIMPLE_MINOR_ 0

#include "types_base/expresions.hpp"

#endif // LLANYLIB_TYPESSIMPLE_HPP_
