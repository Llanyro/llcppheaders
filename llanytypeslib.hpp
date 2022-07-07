/*
 * llanytypeslib.hpp
 *
 *  Created on: Feb 28, 2022
 *      Author: llanyro
 */

#ifndef CORE_LLANYTYPESLIB_HPP_
#define CORE_LLANYTYPESLIB_HPP_

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

// Bits
typedef ll_char_t ll_int8_t;
typedef ll_uchar_t ll_uint8_t;
typedef ll_short_t ll_int16_t;
typedef ll_ushort_t ll_uint16_t;
typedef ll_int_t ll_int32_t;
typedef ll_uint_t ll_uint32_t;

#if defined __x86_64__ && !defined __ILP32__
typedef ll_long_t ll_int64_t;
typedef ll_ulong_t ll_uint64_t;
#else
typedef ll_longlong_t ll_int64_t;
typedef ll_ulonglong_t ll_uint64_t;
#endif
#pragma endregion


#pragma region NonGeneralTypes1
typedef bool ll_bool_t;

typedef ll_uchar_t hex;		// Usado para guardar el valor numerico de un Hexadecimal

typedef ll_uint64_t len_t; 	// Usado para posiciones de listas y tamanios de listas -> es decir: cantidades de datos

/// Tipos para control de bytes
typedef len_t size_bytes_t;
typedef size_bytes_t s_bytes_t;
typedef unsigned char bytes_t;

typedef void* dynamic;

//typedef char const* const ll_constchar_t;
//typedef void ll_void_t;
//typedef const char* ll_str_t;
//typedef const char* ll_ustr_t;


#pragma endregion


#pragma region DefFunctions
typedef ll_int_t(*Compare_int)(const void* item_a, const void* item_b);
typedef ll_bool_t(*Compare_bool)(const void* item_a, const void* item_b);
typedef ll_int_t(*CompareChar_int)(const char* caracter1, const char* caracter2);
//typedef ll_uint32_t (*Range_uint32)(const ll_uint32_t& value);
typedef void (*Destructor)(void*);
/*
* History and information
* This function inheritances from Compare_int
*	Compare_int is a function of general comparations
*	Compare_int compares 2 objects and return a int
*		0 -> Same item
*		1 -> a > b
*	   -1 -> a < b
*	That means, that this function compares 2 items
*	But sometimes is not enough, sometimes we need more data
*	So this function poposes a solution, a third data, that can contains an struct or other data (int, char, ...)
*/
typedef ll_int_t(*Compare)(const void* item_a, const void* item_b, void* extra_data);

#pragma endregion


#pragma region DEFINES
#define TRUE true
#define FALSE false

#define NULLPTR nullptr

#define TRUE_STRING "True"
#define TRUE_STRING_LEN 4
#define FALSE_STRING "False"
#define FALSE_STRING_LEN 5
#define GET_BOOL_STR(a) (a == TRUE) ? TRUE_STRING : FALSE_STRING
#pragma endregion


#endif /* CORE_LLANYTYPESLIB_HPP_ */
