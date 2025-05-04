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
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "defines.hpp version error!"
		#else
			#error "defines.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
	#endif // LLANYLIB_DEFINES_MAYOR_ || LLANYLIB_DEFINES_MINOR_

#elif !defined(LLANYLIB_DEFINES_HPP_)
	#define LLANYLIB_DEFINES_HPP_
	#define LLANYLIB_DEFINES_MAYOR_ 10
	#define LLANYLIB_DEFINES_MINOR_ 0

	#include "defines/expresions.hpp"

#endif // LLANYLIB_DEFINES_HPP_
