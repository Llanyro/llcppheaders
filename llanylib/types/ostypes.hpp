//////////////////////////////////////////////
//	ostypes.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_OSTYPES_HPP_) // Guard && version protector
	#if LLANYLIB_OSTYPES_MAYOR_ != 12 || LLANYLIB_OSTYPES_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "ostypes.hpp version error!"
		#else
			#error "ostypes.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_OSTYPES_MAYOR_ || LLANYLIB_OSTYPES_MINOR_

#elif !defined(LLANYLIB_OSTYPES_HPP_)
	#define LLANYLIB_OSTYPES_HPP_
	#define LLANYLIB_OSTYPES_MAYOR_ 12
	#define LLANYLIB_OSTYPES_MINOR_ 0

#include "types.hpp"

#if defined(__LL_WINDOWS_SYSTEM)
	using ll_pid_t = ::llcpp::u32;
#elif defined(__LL_POSIX_SYSTEM) || defined(__LL_UNIX_SYSTEM)
	using ll_pid_t = ::llcpp::i32;
#else
	using ll_pid_t = ::llcpp::i32;
#endif // __LL_WINDOWS_SYSTEM || __LL_POSIX_SYSTEM || __LL_UNIX_SYSTEM

#endif // LLANYLIB_OSTYPES_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
