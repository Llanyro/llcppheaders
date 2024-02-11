/*
 *	os.hpp
 *
 *	Created on: Jan 28, 2024
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLCPP_HEADER_OS_HPP_
#define LLCPP_HEADER_OS_HPP_

#if defined(__cplusplus)
	#if __STDC_HOSTED__ != 1
		#error "Not a hosted implementation"
	#endif

	#if __cplusplus >= 202302L
		#define DIRECTIVE_WARNING
	#endif
#endif



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
		#define LL_SHARED_LIB extern "C++"
	#else
		#define LL_SHARED_LIB
	#endif // LL_DLL_BUILD
#else
	#if defined(LL_DLL_BUILD)
		#define LL_SHARED_LIB extern "C++"
	#else
		#define LL_SHARED_LIB
	#endif // LL_DLL_BUILD
#endif // WINDOWS_SYSTEM || POSIX_SYSTEM || UNIX_SYSTEM

#if defined(__x86_64__) || defined(__ILP32__)
	constexpr unsigned char __BITS_SYSTEM__ = 32u;
#else
	constexpr unsigned char __BITS_SYSTEM__ = 64u;
#endif // __x86_64__ || __ILP32__


// Creates a definition to use assert by condition and message
#if defined(_DEBUG)
	#include <assert.h>
	#define LL_ASSERT(condition, message) assert(condition && message)
#else
	#define LL_ASSERT(condition, message)
#endif // _DEBUG



// Disables some warnings of compiler
#if defined(WINDOWS_SYSTEM)
	//#pragma warning(disable:6029)

	//#pragma warning(disable:6011)
	//#pragma warning(disable:4996)


	//#pragma warning(disable:4244)
	//#pragma warning(disable:6031)

	// Socket
	//#pragma warning(disable:4309)
	//#pragma warning(disable:4477)
	//#pragma warning(disable:26439)

	// Wall
	//#pragma warning(disable:4464)
	//#pragma warning(disable:6387)	// Pointer could be nullptr
	//#pragma warning(disable:5045) // Security mitigation
	//#pragma warning(disable:4710) // Function not inlined
	//#pragma warning(disable:4706) // assignment within conditional expression if( (result = value)) {}
	#pragma warning(disable:4711) // Function inlined
	#pragma warning(disable:4458) // parameter hides class member (just use "this->" to call member)
	#pragma warning(disable:4514) // Function not used removed
	#pragma warning(disable:4464) // relative include path contains '..'

	#pragma warning(disable:4251) // Exporting in dll a class that contains stl objects
#endif // WINDOWS_SYSTEM

#endif /* LLCPP_HEADER_OS_HPP_ */
