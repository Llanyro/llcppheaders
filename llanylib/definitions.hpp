/*
 *	definitions.hpp
 * 
 *	Author: Francisco Julio Ruiz Fernandez
 *	Author: llanyro
 *
 *	Version: 4.2
 */

#if defined(LLANYLIB_DEFINITIONS_HPP_) // Guard && version protector
	#if LLANYLIB_DEFINITIONS_MAYOR_ != 4 || LLANYLIB_DEFINITIONS_MINOR_ < 2
		#error "definitions.hpp version error!"
	#endif // LLANYLIB_DEFINITIONS_MAYOR_ || LLANYLIB_DEFINITIONS_MINOR_

#else !defined(LLANYLIB_DEFINITIONS_HPP_)
#define LLANYLIB_DEFINITIONS_HPP_
#define LLANYLIB_DEFINITIONS_MAYOR_ 4
#define LLANYLIB_DEFINITIONS_MINOR_ 2

#include "os.hpp"

// Sets more env definitions by OS
#if defined(WINDOWS_SYSTEM)
	#define __LL_NODISCARD__ _NODISCARD
	#define __LL_UNSECURE_FUNCTIONS__
	#define __LL_SPECTRE_FUNCTIONS__
	#define __LL_INLINE__ __forceinline
	#define __LL_VAR_INLINE__ inline
#elif defined(POSIX_SYSTEM) || defined(UNIX_SYSTEM)
	#define __LL_NODISCARD__ NODISCARD
	#define __LL_INLINE__ inline
	#define __LL_VAR_INLINE__ inline
#else
	#define __LL_NODISCARD__ [[nodiscard]]
	#define __LL_INLINE__ inline
	#define __LL_VAR_INLINE__ inline
#endif

// Definitions
#define __LL_EXCEPT__ noexcept(true)
#define LL_NULLPTR nullptr

// Adds basic types for classes
#define __LL_CLASS_TEMPLATE_TYPE__(__type__) \
	using __type = __type__; \
	using __ctype = const __type__; \
	using __ptr = __type__*; \
	using __cptr = const __type__ *; \
	using __ref = __type__&; \
	using __cref = const __type__ &; \
	using __move = __type__&&; \
	using __ptrref = __type__*&

// Adds basic types with indentifiers for classes
#define __LL_CLASS_TEMPLATE_TYPES__(__type__, id) \
	using __type##id## = __type__; \
	using __ctype##id## = const __type__; \
	using __ptr##id## = __type__*; \
	using __cptr##id## = const __type__ *; \
	using __ref##id## = __type__&; \
	using __cref##id## = const __type__ &; \
	using __move##id## = __type__&&; \
	using __ptrref##id## = __type__*&

#define __LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__type__, name) \
	using __##name## = __type__; \
	using __ptr_##name## = __type__*; \
	using __cptr_##name## = const __type__ *; \
	using __ref_##name## = __type__&; \
	using __cref_##name## = const __type__ &; \
	using __move_##name## = __type__&&; \
	using __ptrref_##name## = __type__*&

#endif // LLANYLIB_DEFINITIONS_HPP_
