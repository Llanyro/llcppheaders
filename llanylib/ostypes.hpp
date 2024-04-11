/*
 *	ostypes.hpp
 *
 *	Author: Francisco Julio Ruiz Fernandez
 *	Author: llanyro
 *
 *	Version: 4.2
 */

#if defined(LLANYLIB_OSTYPES_HPP_) // Guard && version protector
	#if LLANYLIB_OSTYPES_MAYOR_ != 4 || LLANYLIB_OSTYPES_MINOR_ < 2
		#error "types.hpp version error!"
	#endif // LLANYLIB_OSTYPES_MAYOR_ || LLANYLIB_OSTYPES_MINOR_

#else !defined(LLANYLIB_OSTYPES_HPP_)
#define LLANYLIB_OSTYPES_HPP_
#define LLANYLIB_OSTYPES_MAYOR_ 4
#define LLANYLIB_OSTYPES_MINOR_ 2

#include "definitions.hpp"
#include "types.hpp"

#if defined(WINDOWS_SYSTEM)
	using ll_pid_t = ll_ulong_t;
#elif defined(POSIX_SYSTEM) || defined(UNIX_SYSTEM)
	using ll_pid_t = i32;
#else
	using ll_pid_t = i32;
#endif

#endif // LLANYLIB_OSTYPES_HPP_
