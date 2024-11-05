//////////////////////////////////////////////
//	os.hpp									//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_OS_HPP_) // Guard && version protector
	#if LLANYLIB_OS_MAYOR_ != 11 || LLANYLIB_OS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "os.hpp version error!"
		#else
			#error "os.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_OS_MAYOR_ || LLANYLIB_OS_MINOR_

#else !defined(LLANYLIB_OS_HPP_)
#define LLANYLIB_OS_HPP_
#define LLANYLIB_OS_MAYOR_ 11
#define LLANYLIB_OS_MINOR_ 0

/////////////////////////////////////////// C++ Version ///////////////////////////////////////////

#if defined(__cplusplus)
	#if __STDC_HOSTED__ != 1
		#error "Not a hosted implementation"
	#endif // __STDC_HOSTED__

	#if __cplusplus >= 199711L
		#define __LL_REAL_CXX17 1
	#else
		#define __LL_REAL_CXX17 0
	#endif // __cplusplus >= 199711L

	#if __cplusplus >= 202302L
		#define __LL_DIRECTIVE_WARNING 1
		#define __LL_REAL_CXX23 1
	#else
		#define __LL_DIRECTIVE_WARNING 0
		#define __LL_REAL_CXX23 0
	#endif // __cplusplus >= 202302L
#else
	#error "This library requires C++ (its made for it)"
#endif // __cplusplus

//////////////////////////////////////////// OS check ////////////////////////////////////////////

// Setting env by OS
#if defined(_WIN32) || defined(_WIN64)
	#define __LL_WINDOWS_SYSTEM
#elif defined(__unix__)
	#if defined(__linux__)
		#define __LL_POSIX_SYSTEM
	#else
		#define __LL_UNIX_SYSTEM
	#endif // __linux__
#else
	#define __LL_UNKNOWN_SYSTEM

	#if defined(__LL_DIRECTIVE_WARNING)
		#warning "Unknown system: Someme features may not work well or not work at all!"
	#elif !defined(__LL_UNKNOWN_SYSTEM_OK)
		#error "Unknown system: Someme features may not work well or not work at all!"
		#error "This error can be commented to compile!"
	#endif // DIRECTIVE_WARNING
#endif // _WIN32 || _WIN64 || __unix__

////////////////////////////////////////// System Based //////////////////////////////////////////

#if defined(__x86_64__) || defined(__ILP32__)
	#define __LL_WORD 32u
#else
	#define __LL_WORD 64u
#endif // __x86_64__ || __ILP32__

///////////////////////////////////////// DLL deinitions /////////////////////////////////////////

// Sets env for exporting libraries
#if defined(__LL_DLL_BUILD)
	#undef __LL_DLL_BUILD
	#define __LL_DLL_BUILD 1

	#if defined(__LL_WINDOWS_SYSTEM)
		#define __LL_SHARED_LIB __declspec(dllexport
	#else
		#define __LL_SHARED_LIB
	#endif // __LL_WINDOWS_SYSTEM
#else
	#define __LL_DLL_BUILD 0
	#define __LL_SHARED_LIB
	//__declspec(dllimport)
#endif // LL_DLL_BUILD

///////////////////////////////////////////// Assert /////////////////////////////////////////////

#if defined(__LL_WINDOWS_SYSTEM)
	// Creates a definition to use assert by condition and message
	#if defined(_DEBUG)
		#include <assert.h>
		#define __LL_ASSERT(condition, message) assert(condition && message)
		#define __LL_DEBUG 1
	#else
		#define __LL_ASSERT(condition, message)
		#define __LL_DEBUG 0

		// Windows does not load _NODISCARD in release...
		#if !defined(_NODISCARD)
			#include <vcruntime.h>
		#endif // _NODISCARD
	#endif // _DEBUG
#elif defined(POSIX_SYSTEM) || defined(UNIX_SYSTEM)

#else

#endif

//////////////////////////////////////// Warning remove ////////////////////////////////////////

// Disables some warnings of compiler
#if defined(__LL_WINDOWS_SYSTEM)
	#pragma warning(disable:4711) // Function inlined
	#pragma warning(disable:4458) // parameter hides class member (just use "this->" to call member)
	#pragma warning(disable:4514) // Function not used removed
	#pragma warning(disable:4464) // relative include path contains '..'
	#pragma warning(disable:4820) // Ignore class parameters is not multiple of 8
	#pragma warning(disable:4251) // Exporting in dll a class that contains stl objects

	#define __LL_SPECTRE_FUNCTIONS__
#endif // WINDOWS_SYSTEM

#endif // LLANYLIB_OS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
