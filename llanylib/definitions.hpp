//////////////////////////////////////////////
//	definitions.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DEFINITIONS_HPP_) // Guard && version protector
	#if LLANYLIB_DEFINITIONS_MAYOR_ != 5 || LLANYLIB_DEFINITIONS_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "definitions.hpp version error!"
		#else
			#error "definitions.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_DEFINITIONS_MAYOR_ || LLANYLIB_DEFINITIONS_MINOR_

#else !defined(LLANYLIB_DEFINITIONS_HPP_)
#define LLANYLIB_DEFINITIONS_HPP_
#define LLANYLIB_DEFINITIONS_MAYOR_ 5
#define LLANYLIB_DEFINITIONS_MINOR_ 0

#include "os.hpp"

enum class OSEnum { Windows, Posix, Unix, Other };

// Sets more env definitions by OS
#if defined(WINDOWS_SYSTEM)
	#define __LL_NODISCARD__ _NODISCARD
	#define __LL_UNSECURE_FUNCTIONS__
	#define __LL_SPECTRE_FUNCTIONS__
	#define __LL_INLINE__ __forceinline
	#define __LL_VAR_INLINE__ inline
	__LL_VAR_INLINE__ constexpr OSEnum OS_SYSTEM = OSEnum::Windows;
#elif defined(POSIX_SYSTEM) || defined(UNIX_SYSTEM)
	#define __LL_NODISCARD__ NODISCARD
	#define __LL_INLINE__ inline
	#define __LL_VAR_INLINE__ inline
	#if defined(POSIX_SYSTEM)
		__LL_VAR_INLINE__ constexpr OSEnum OS_SYSTEM = OSEnum::Posix;
	#else
		__LL_VAR_INLINE__ constexpr OSEnum OS_SYSTEM = OSEnum::Unix;
	#endif // defined(POSIX_SYSTEM)
#else
	#define __LL_NODISCARD__ [[nodiscard]]
	#define __LL_INLINE__ inline
	#define __LL_VAR_INLINE__ inline
	__LL_VAR_INLINE__ constexpr OSEnum OS_SYSTEM = OSEnum::Other;
#endif

// Definitions
#define __LL_EXCEPT__ noexcept(true)
#define LL_NULLPTR nullptr
//#define LL_SHARED_LIB_FUNC extern "C" LL_SHARED_LIB

#define __LL_VAR_ZERO_ASSERT__(var, varstr) LL_ASSERT(var > 0, "[" varstr "] cannot be 0. " __FUNCSIG__)
#define __LL_VAR_NULL_ASSERT__(var, varstr) LL_ASSERT(var, "[" varstr "] cannot be nullptr." __FUNCSIG__)

#endif // LLANYLIB_DEFINITIONS_HPP_
