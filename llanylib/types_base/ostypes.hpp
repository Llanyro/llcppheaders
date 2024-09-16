//////////////////////////////////////////////
//	ostypes.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_OSTYPES_HPP_) // Guard && version protector
	#if LLANYLIB_OSTYPES_MAYOR_ != 10 || LLANYLIB_OSTYPES_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "ostypes.hpp version error!"
		#else
			#error "ostypes.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_OSTYPES_MAYOR_ || LLANYLIB_OSTYPES_MINOR_

#else !defined(LLANYLIB_OSTYPES_HPP_)
#define LLANYLIB_OSTYPES_HPP_
#define LLANYLIB_OSTYPES_MAYOR_ 10
#define LLANYLIB_OSTYPES_MINOR_ 0

#include "types_base.hpp"

#if defined(__LL_WINDOWS_SYSTEM)
	using ll_pid_t = llcpp::u32;
#elif defined(__LL_POSIX_SYSTEM) || defined(__LL_UNIX_SYSTEM)
	using ll_pid_t = llcpp::i32;
#else
	using ll_pid_t = llcpp::i32;
#endif // __LL_WINDOWS_SYSTEM || __LL_POSIX_SYSTEM || __LL_UNIX_SYSTEM

#endif // LLANYLIB_OSTYPES_HPP_
