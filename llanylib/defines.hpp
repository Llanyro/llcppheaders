//////////////////////////////////////////////
//	defines.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DEFINES_HPP_) // Guard && version protector
	#if LLANYLIB_DEFINES_MAYOR_ != 10 || LLANYLIB_DEFINES_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "defines.hpp version error!"
		#else
			#error "defines.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_DEFINES_MAYOR_ || LLANYLIB_DEFINES_MINOR_

#elif !defined(LLANYLIB_DEFINES_HPP_)
	#define LLANYLIB_DEFINES_HPP_
	#define LLANYLIB_DEFINES_MAYOR_ 10
	#define LLANYLIB_DEFINES_MINOR_ 0

	#include "defines/expresions.hpp"

#endif // LLANYLIB_DEFINES_HPP_
