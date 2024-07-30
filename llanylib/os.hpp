//////////////////////////////////////////////
//	os.hpp									//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_OS_HPP_) // Guard && version protector
	#if LLANYLIB_OS_MAYOR_ != 9 || LLANYLIB_OS_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "os.hpp version error!"
		#else
			#error "os.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_OS_MAYOR_ || LLANYLIB_OS_MINOR_

#else !defined(LLANYLIB_OS_HPP_)
#define LLANYLIB_OS_HPP_
#define LLANYLIB_OS_MAYOR_ 9
#define LLANYLIB_OS_MINOR_ 0

#if defined(__cplusplus)
	#if __STDC_HOSTED__ != 1
		#error "Not a hosted implementation"
	#endif // __STDC_HOSTED__

	#if __cplusplus >= 202302L
		#define DIRECTIVE_WARNING
		#define LL_REAL_CXX23
	#endif // __cplusplus
#endif // __cplusplus


// Setting env by OS
#if defined(_WIN32) || defined(_WIN64)
	#define WINDOWS_SYSTEM
#elif defined(__unix__)
	#if defined(__linux__)
		#define POSIX_SYSTEM
	#else
		#define UNIX_SYSTEM
	#endif // __linux__
#else
	#define UNKNOWN_SYSTEM

	#if defined(DIRECTIVE_WARNING)
		#warning "Unknown system: Someme features may not work well or not work at all!"
	#elif !defined(UNKNOWN_SYSTEM_OK)
		#error "Unknown system: Someme features may not work well or not work at all!"
		#error "This error can be commented to compile!"
	#endif // DIRECTIVE_WARNING
#endif // _WIN32 || _WIN64 || __unix__

// Sets env for exporting libraries
#if defined(WINDOWS_SYSTEM)
	#if defined(LL_DLL_BUILD)
		#define LL_SHARED_LIB __declspec(dllexport)
	#else
		#define LL_SHARED_LIB //__declspec(dllimport)
	#endif // LL_DLL_BUILD
#elif defined(POSIX_SYSTEM) || defined(UNIX_SYSTEM)
	#if defined(LL_DLL_BUILD)
		#define LL_SHARED_LIB
	#else
		#define LL_SHARED_LIB
	#endif // LL_DLL_BUILD
#else
	#if defined(LL_DLL_BUILD)
		#define LL_SHARED_LIB
	#else
		#define LL_SHARED_LIB
	#endif // LL_DLL_BUILD
#endif // WINDOWS_SYSTEM || POSIX_SYSTEM || UNIX_SYSTEM

#if defined(__x86_64__) || defined(__ILP32__)
	constexpr unsigned char __BITS_SYSTEM__ = 32u;
#else
	constexpr unsigned char __BITS_SYSTEM__ = 64u;
#endif // __x86_64__ || __ILP32__

#if defined(WINDOWS_SYSTEM)
	// Creates a definition to use assert by condition and message
	#if defined(_DEBUG)
		#include <assert.h>
		#define LL_ASSERT(condition, message) assert(condition && message)
	#else
		#define LL_ASSERT(condition, message)
		
		// Windows does not load _NODISCARD in release...
		#if !defined(_NODISCARD)
			#include <vcruntime.h>
		#endif // _NODISCARD
	#endif // _DEBUG
#elif defined(POSIX_SYSTEM) || defined(UNIX_SYSTEM)

#else

#endif

// Disables some warnings of compiler
#if defined(WINDOWS_SYSTEM)
	#pragma warning(disable:4711) // Function inlined
	#pragma warning(disable:4458) // parameter hides class member (just use "this->" to call member)
	#pragma warning(disable:4514) // Function not used removed
	#pragma warning(disable:4464) // relative include path contains '..'
	#pragma warning(disable:4820) // Ignore class parameters is not multiple of 8
	#pragma warning(disable:4251) // Exporting in dll a class that contains stl objects

	#define __LL_SPECTRE_FUNCTIONS__
#endif // WINDOWS_SYSTEM

#endif // LLANYLIB_OS_HPP_
