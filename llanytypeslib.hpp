/*
 * llanytypeslib.h
 *
 *  Created on: Feb 28, 2022
 *      Author: llanyro
 */

#ifndef LLCPP_HEADER_LLANYTYPESLIB_HPP_
#define LLCPP_HEADER_LLANYTYPESLIB_HPP_

#include <utility>
#include <type_traits>

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
long double	Bytes 16: �?
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
#pragma endregion

// More like rust
#pragma region Standard
typedef ll_char_t i8;
typedef ll_uchar_t ui8;

typedef ll_short_t i16;
typedef ll_ushort_t ui16;
typedef ll_int_t i32;
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
typedef ll_uint128_t uint128;
typedef ll_uint128_t ui128;

#pragma endregion

#pragma region NonGeneralTypes1
typedef ll_uchar_t hex;		// Usado para guardar el valor numerico de un Hexadecimal

typedef ll_uint64_t len_t; 		// Usado para posiciones de listas y tamanios de listas -> es decir: cantidades de datos
typedef ll_uint32_t medlen_t; 	// Usado para posiciones de listas y tamanios de listas -> es decir: cantidades de datos

/// Tipos para control de bytes
typedef ll_uint8_t size_bytes8_t;	// Used to store the size of a object or memory
typedef ll_uint16_t size_bytes16_t;	// Used to store the size of a object or memory
typedef ll_uint32_t size_bytes32_t;	// Used to store the size of a object or memory
typedef ll_uint64_t size_bytes64_t;	// Used to store the size of a object or memory

typedef size_bytes8_t s_b8_t;	// Used to store the size of a object or memory
typedef size_bytes16_t s_b16_t;	// Used to store the size of a object or memory
typedef size_bytes32_t s_b32_t;	// Used to store the size of a object or memory
typedef size_bytes64_t s_b64_t;	// Used to store the size of a object or memory
typedef size_bytes64_t b64;		// Use to count number of bytes in ui64

typedef ll_char_t ll_bytes_t;
typedef ll_uchar_t ll_ubytes_t;

typedef ll_int8_t ll_singleton_priority_t;
typedef ll_singleton_priority_t ll_singleton_prio_t;

typedef void* ll_any_t;

//typedef char const* const ll_constchar_t;
//typedef void ll_void_t;
typedef const ll_char_t* ll_string_t;
typedef const ll_uchar_t* ll_ustring_t;

// For pointer to libs (Handle)
typedef void* ll_lib_t;

// Standard value hash
typedef ui64 ll_hash_t;

#pragma endregion

#pragma region DEFINES
#define LL_TRUE true
#define LL_FALSE false
#define LL_NULLPTR nullptr
#define TRUE_STRING "True"
#define FALSE_STRING "False"
#define GET_BOOL_STR(a) ((a) ? TRUE_STRING : FALSE_STRING)

#pragma endregion

#pragma region IncludesByDefines

#if defined(_DEBUG)
#include <assert.h>
#else
#define assert
#endif // _DEBUG

#pragma endregion

#pragma region TypesFunctions
typedef i32 (*i32Compare)(const void*, const void*);
typedef ll_bool_t (*boolCompare)(const void*, const void*);
typedef i32 (*i32CompareChar)(const char*, const char*);
/*
* History and information
* This function inheritances from Compare_int (now i32Compare)
*	Compare_int is a function of general comparations
*	Compare_int compares 2 objects and return a int
*		0 -> Same item
*		1 -> a > b
*	   -1 -> a < b
*	That means, that this function compares 2 items
*	But sometimes is not enough, sometimes we need more data
*	So this function poposes a solution, a third data, that can contains an struct or other data (int, char, ...)
*/
typedef i32 (*i32CompareExtra)(const void*, const void*, void*);

#pragma endregion



#if defined(_WIN32) or defined(_WIN64)
#define WINDOWS_SYSTEM
#endif // _WIN32


/// Win dll
#if defined(WINDOWS_SYSTEM)
    //#define LL_DLL_BUILD
    #if defined(LL_DLL_BUILD)
        #define LL_SHARED_LIB __declspec(dllexport)
    #else
        //#define LL_SHARED_LIB __declspec(dllimport)
    #endif
#endif // WINDOWS_SYSTEM

// If we are not in windows, we dont need to export anything
#if !defined(LL_SHARED_LIB)
    #define LL_SHARED_LIB
#endif // LL_SHARED_LIB

/*
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


#ifdef __cplusplus
}
#endif // __cplusplus
*/

// Disables del pesao de windows
#if defined(WINDOWS_SYSTEM)
#pragma warning(disable:6029)

#pragma warning(disable:6011)
#pragma warning(disable:6387)
#pragma warning(disable:4996)


#pragma warning(disable:4244)
#pragma warning(disable:6031)

// Socket
#pragma warning(disable:4309)
#pragma warning(disable:4477)
#pragma warning(disable:26439)

// Wall
#pragma warning(disable:4464)


#endif // defined(WINDOWS_SYSTEM)

#if defined(WINDOWS_SYSTEM)
typedef ll_ulong_t ll_pid_t;
#elif defined(__unix__)
typedef int ll_pid_t;
#endif

#endif /* LLCPP_HEADER_LLANYTYPESLIB_HPP_ */
