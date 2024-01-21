/*
*	llanytypesbase.hpp
*
*	Created on: Feb 28, 2022
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
*/

#ifndef LLCPP_HEADER_LLANYTYPESBASE_HPP_
#define LLCPP_HEADER_LLANYTYPESBASE_HPP_

#include <utility>
#include <type_traits>

#pragma region IncludesByDefines

#if defined(_DEBUG)
#include <assert.h>
#define LL_ASSERT(condition, message) assert(condition && message)
#else
#define LL_ASSERT(condition, message)
#endif // _DEBUG

#pragma endregion

#pragma region OS
#if defined(_WIN32) || defined(_WIN64)
	#define WINDOWS_SYSTEM
#elif defined(__unix__)
	#if defined(__linux__)
		#define POSIX_SYSTEM
	#else
		#define UNIX_SYSTEM
	#endif // __linux__
#else
	#error Unknown system
	#define UNKNOWN_SYSTEM
#endif // _WIN32 || _WIN64 || __unix__

/// Win dll
#if defined(WINDOWS_SYSTEM)
	#if defined(LL_DLL_BUILD)
		#define LL_SHARED_LIB __declspec(dllexport)
	#else
		//#define LL_SHARED_LIB __declspec(dllimport)
		#define LL_SHARED_LIB
	#endif // LL_DLL_BUILD
#elif defined(POSIX_SYSTEM) || defined(UNIX_SYSTEM)
	#if defined(LL_DLL_BUILD)
		// Does not works (?) not tested
		#define LL_SHARED_LIB extern "C++"
	#else
		#define LL_SHARED_LIB
	#endif // LL_DLL_BUILD
#else
#define LL_SHARED_LIB
#endif // WINDOWS_SYSTEM || POSIX_SYSTEM || UNIX_SYSTEM


// Disables del pesao de windows
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

#pragma endregion

#if defined(WINDOWS_SYSTEM)
#pragma warning(push)
#pragma warning(disable:4365) // ignore conversion from long to ui32 (signed/unsigned mismatch)

#endif // WINDOWS_SYSTEM

// Added here to fix inline error /W4
#include <functional>

#if defined(WINDOWS_SYSTEM)
#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#pragma region GeneralTypes

/*
32 bits
char 		Bytes 1 : -128 to 127												-> 255
short 		Bytes 2 : -32,768 to 32,767											-> 65,535
int 		Bytes 4 : -2,147,483,648 to 2,147,483,647							-> 4,294,967,295
long 		Bytes 4 : -2,147,483,648 to 2,147,483,647							-> 4,294,967,295
long long	Bytes 8 : -9,223,372,036,854,775,808 to 9,223,372,036,854,775,808	-> 18,446,744,073,709,551,615

64 bits
char 		Bytes 1 : -128 to 127												-> 255
short 		Bytes 2 : -32,768 to 32,767											-> 65,535
int 		Bytes 4 : -2,147,483,648 to 2,147,483,647							-> 4,294,967,295
long 		Bytes 8 : -9,223,372,036,854,775,808 to 9,223,372,036,854,775,808	-> 18,446,744,073,709,551,615
long long	Bytes 8 : -9,223,372,036,854,775,808 to 9,223,372,036,854,775,808	-> 18,446,744,073,709,551,615

32 & 64 bits
float		Bytes 4 :
double		Bytes 8 :
long double	Bytes 16:
*/

// Signed
typedef char ll_char_t;						// Signed
typedef short ll_short_t;					// Signed
typedef int ll_int_t;						// Signed
typedef long ll_long_t;						// Signed
typedef long long ll_longlong_t;			// Signed

typedef unsigned char ll_uchar_t;			// Unsigned
typedef unsigned short ll_ushort_t;			// Unsigned
typedef unsigned int ll_uint_t;				// Unsigned
typedef unsigned long ll_ulong_t;			// Unsigned
typedef unsigned long long ll_ulonglong_t;	// Unsigned

// Flotantes
typedef float ll_float_t;
typedef double ll_double_t;
typedef long double ll_ldouble_t;

typedef bool ll_bool_t;

// Bits
typedef ll_char_t ll_int8_t;
typedef ll_uchar_t ll_uint8_t;
typedef ll_short_t ll_int16_t;
typedef ll_ushort_t ll_uint16_t;
typedef ll_int_t ll_int32_t;
typedef ll_uint_t ll_uint32_t;

#if defined(__x86_64__) && !defined(__ILP32__)
typedef ll_long_t ll_int64_t;
typedef ll_ulong_t ll_uint64_t;
#else
typedef ll_longlong_t ll_int64_t;
typedef ll_ulonglong_t ll_uint64_t;
#endif

typedef std::pair<ll_uint64_t, ll_uint64_t> ll_uint128_t;
typedef std::pair<ll_int64_t, ll_int64_t> ll_int128_t;
#pragma endregion

// More like rust
#pragma region Standard
typedef ll_char_t i8;
typedef ll_short_t i16;
typedef ll_int_t i32;

typedef ll_uchar_t ui8;
typedef ll_ushort_t ui16;
typedef ll_uint_t ui32;

#if defined(__x86_64__) && !defined(__ILP32__)
typedef ll_long_t i64;
typedef ll_ulong_t ui64;
#else
typedef ll_longlong_t i64;
typedef ll_ulonglong_t ui64;
#endif

typedef float f32;
typedef double f64;
//typedef long double f64;

typedef ll_uint128_t ui128;
typedef ll_int128_t i128;

#pragma endregion

// Types by OS
#pragma region OSTypes
#if defined(WINDOWS_SYSTEM)
// Process ID
typedef ll_ulong_t ll_pid_t;
// Socket descriptor
typedef ui32 ll_socket_t;
// Generic Handle in windows
typedef void* WindowsHandle;

// Handle in share memory module
typedef WindowsHandle ll_share_memory_handle_t;

//#define INVALID_HANDLE_VALUE ((ll_share_memory_handle_t)(ll_longlong_t)-1)
#define INVALID_SHARE_HANDLE ((ll_share_memory_handle_t)(ll_longlong_t)-1)
#define __LL_NODISCARD__ _NODISCARD
#define __LL_CONSTEXPR__ constexpr
#define __LL_CLASSEXPR__ constexpr
#define __LL_CONSTEVAL__ consteval
//#define __LL_INLINE__ inline
#define __LL_EXCEPT__ noexcept
//#define __LL_RESTRICT__ restrict
#define __LL_UNSECURE_FUNCTIONS__
#define __LL_SPECTRE_FUNCTIONS__

#elif defined(POSIX_SYSTEM) || defined(UNIX_SYSTEM)
// Process ID
typedef i32 ll_pid_t;
// Socket descriptor
typedef i32 ll_socket_t;


// Handle in share memory module
typedef i32 ll_share_memory_handle_t;

// Value of invalid socket
constexpr ll_socket_t INVALID_SOCKET = -1;
// Value of invalid share memory handle
constexpr ll_share_memory_handle_t INVALID_SHARE_HANDLE = -1;

#define __LL_NODISCARD__ _NODISCARD
#else
#define __LL_NODISCARD__

#endif
#pragma endregion

// Lib types or rename types
#pragma region NonGeneralTypes1
typedef ui64 len_t;		// Used to cound things (natural number)

typedef const ll_char_t* ll_string_t;		// Used to point to non editable strings
typedef const ll_uchar_t* ll_ustring_t;		// Used to point to non editable unsigned strings


/// Tipos para control de bytes
typedef ui8 size_bytes8_t;		// Used to count bytes
typedef ui16 size_bytes16_t;	// Used to count bytes
typedef ui32 size_bytes32_t;	// Used to count bytes
typedef ui64 size_bytes64_t;	// Used to count bytes

typedef size_bytes8_t b8;		// Used to count bytes
typedef size_bytes16_t b16;		// Used to count bytes
typedef size_bytes32_t b32;		// Used to count bytes
typedef size_bytes64_t b64;		// Used to count bytes

#pragma endregion

#pragma region Definitions
#define LL_NULLPTR nullptr
// Easy enabler for template functions
#define ENABLE_FUNCTION_PARAM(condition) typename = typename std::enable_if<condition>::type

// Adds basic types in template classes
#define __LL_CLASS_TEMPLATE_TYPE__(__type__) \
	using __type = __type__; \
	using __ctype = const __type__; \
	using __ptr = __type__*; \
	using __cptr = const __type__ *; \
	using __ref = __type__&; \
	using __cref = const __type__ &; \
	using __move = __type__&&; \
	using __ptrref = __type__*&

// Adds basic types with indentifiers in template classes
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

#pragma endregion

#endif /* LLCPP_HEADER_LLANYTYPESBASE_HPP_ */
