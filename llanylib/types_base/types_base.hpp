//////////////////////////////////////////////
//	types_base.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPESBASE_HPP_) // Guard && version protector
	#if LLANYLIB_TYPESBASE_MAYOR_ != 11 || LLANYLIB_TYPESBASE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "types_base.hpp version error!"
		#else
			#error "types_base.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPESBASE_MAYOR_ || LLANYLIB_TYPESBASE_MINOR_

#else !defined(LLANYLIB_TYPESBASE_HPP_)
	#define LLANYLIB_TYPESBASE_HPP_
	#define LLANYLIB_TYPESBASE_MAYOR_ 11
	#define LLANYLIB_TYPESBASE_MINOR_ 0

#include "../defines.hpp"

namespace llcpp {

#pragma region Standard
//
//	32 bits
//	char 		Bytes 1 : -128 to 127												-> 255
//	short 		Bytes 2 : -32,768 to 32,767											-> 65,535
//	int 		Bytes 4 : -2,147,483,648 to 2,147,483,647							-> 4,294,967,295
//	long 		Bytes 4 : -2,147,483,648 to 2,147,483,647							-> 4,294,967,295
//	long long	Bytes 8 : -9,223,372,036,854,775,808 to 9,223,372,036,854,775,808	-> 18,446,744,073,709,551,615
//
//	64 bits
//	char 		Bytes 1 : -128 to 127												-> 255
//	short 		Bytes 2 : -32,768 to 32,767											-> 65,535
//	int 		Bytes 4 : -2,147,483,648 to 2,147,483,647							-> 4,294,967,295
//	long 		Bytes 8 : -9,223,372,036,854,775,808 to 9,223,372,036,854,775,808	-> 18,446,744,073,709,551,615
//	long long	Bytes 8 : -9,223,372,036,854,775,808 to 9,223,372,036,854,775,808	-> 18,446,744,073,709,551,615
//
//	32 & 64 bits
//	float		Bytes 4 :
//	double		Bytes 8 :
//	long double	Bytes 16:
//

/// Signed
using ll_char_t			= char;
using ll_short_t		= short;
using ll_int_t			= int;
using ll_long_t			= long;
using ll_longlong_t		= long long;

/// Unsigned
using ll_uchar_t		= unsigned char;
using ll_ushort_t		= unsigned short;
using ll_uint_t			= unsigned int;
using ll_ulong_t		= unsigned long;
using ll_ulonglong_t	= unsigned long long;

/// Floating-point
using ll_float_t		= float;
using ll_double_t		= double;
using ll_longdouble_t	= long double;

/// Other
using ll_wchar_t		= wchar_t;
using ll_bool_t			= bool;
enum class LoopResult { Conntinue, Error, Ok, BeginError };

// Simplified Signed
using i8				= ll_char_t;
using i16				= ll_short_t;
using i32				= ll_int_t;
using i64				= ll_longlong_t;

// Simplified Unsigned
using u8				= ll_uchar_t;
using u16				= ll_ushort_t;
using u32				= ll_uint_t;
using u64				= ll_ulonglong_t;

// Simplified Floating-point
using f32				= ll_float_t;
using f64				= ll_double_t;
using f128				= ll_longdouble_t;

#pragma endregion
#pragma region LibaryCustom
using c_cmp_t			= i32;					// Old type in comparations, compatible with C libs

using ll_string_t		= const ll_char_t*;		// Used to point to non editable strings
using ll_wstring_t		= const ll_wchar_t*;	// Used to point to non editable strings
/// [DEPRECATED] Unsigned char sometimes crashes Visual Studio IntelliSense using traits
using ll_ustring_t		= const ll_uchar_t*;	// Used to point to non editable unsigned strings 

using ll_lib_t			= void*;				// Handle for dynamic library linked/shared objects

//using len_t				= void;

// System size 64/32/16/8 bits
// [TOCHECK]
#if __LL_WORD == 8u
	using isize				= i8;
	using usize				= u8;
#elif __LL_WORD == 16u
	using isize				= i16;
	using usize				= u16;
#elif __LL_WORD == 32u
	using isize				= i32;
	using usize				= u32;
#elif __LL_WORD == 64u
	using isize				= i64;
	using usize				= u64;
#elif __LL_WORD == 128u
	using isize				= i128;
	using usize				= u128;
#elif __LL_WORD == 256u
	using isize				= i256;
	using usize				= u256;
#else
	#error "Invalid wordsize"
#endif // __LL_WORD

#pragma region BytesTypes
using size_bytes8_t		= u8;
using size_bytes16_t	= u16;
using size_bytes32_t	= u32;
using size_bytes64_t	= u64;

using b8				= size_bytes8_t;
using b16				= size_bytes16_t;
using b32				= size_bytes32_t;
using b64				= size_bytes64_t;

#pragma endregion

#pragma endregion

} // namespace llcpp

#pragma region StandardIncompleteTypes

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4643) // ignore fordward declaration of some c++ classes
#endif // WINDOWS_SYSTEM

namespace std {
struct strong_ordering;
struct partial_ordering;
struct weak_ordering;

template <class _Ty>
class allocator;
template <class _Elem>
struct char_traits;
template <class _Elem, class _Traits, class _Alloc>
class basic_string;
template <class _Elem, class _Traits>
class basic_string_view;

using string		= basic_string<char, char_traits<char>, allocator<char>>;
using wstring		= basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t>>;
using string_view	= basic_string_view<char, char_traits<char>>;
using wstring_view	= basic_string_view<wchar_t, char_traits<wchar_t>>;

template <class _Fty>
class function;
//template <class _Ty, class _Alloc = allocator<_Ty>>
//class vector;
//template <class _Ty, class _Alloc = allocator<_Ty>>
//class list;

template <class T1, class T2>
struct pair;

//template <class _Ty>
//class optional;

namespace filesystem {
class directory_entry;
} // namespace filesystem

} // namespace std

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#pragma endregion

#endif // LLANYLIB_TYPESBASE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
