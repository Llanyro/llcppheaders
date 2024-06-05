//////////////////////////////////////////////
//	ostypes.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.3							//
//////////////////////////////////////////////

#if defined(LLANYLIB_OSTYPES_HPP_) // Guard && version protector
	#if LLANYLIB_OSTYPES_MAYOR_ != 7 || LLANYLIB_OSTYPES_MINOR_ < 3
		#if defined(LL_REAL_CXX23)
			#warning "ostypes.hpp version error!"
		#else
			#error "ostypes.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_OSTYPES_MAYOR_ || LLANYLIB_OSTYPES_MINOR_

#else !defined(LLANYLIB_OSTYPES_HPP_)
#define LLANYLIB_OSTYPES_HPP_
#define LLANYLIB_OSTYPES_MAYOR_ 7
#define LLANYLIB_OSTYPES_MINOR_ 3

#include "types.hpp"

#if defined(WINDOWS_SYSTEM)
	using ll_pid_t = ll_ulong_t;
#elif defined(POSIX_SYSTEM) || defined(UNIX_SYSTEM)
	using ll_pid_t = i32;
#else
	using ll_pid_t = i32;
#endif

#endif // LLANYLIB_OSTYPES_HPP_
