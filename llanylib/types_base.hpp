//////////////////////////////////////////////
//	types_base.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPESBASE_HPP_) // Guard && version protector
	#if LLANYLIB_TYPESBASE_MAYOR_ != 9 || LLANYLIB_TYPESBASE_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "types_base.hpp version error!"
		#else
			#error "types_base.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_TYPESBASE_MAYOR_ || LLANYLIB_TYPESBASE_MINOR_

#else !defined(LLANYLIB_TYPESBASE_HPP_)
#define LLANYLIB_TYPESBASE_HPP_
#define LLANYLIB_TYPESBASE_MAYOR_ 9
#define LLANYLIB_TYPESBASE_MINOR_ 0

#include "definitions.hpp"

#pragma region Standard
/*
 *	32 bits
 *	char 		Bytes 1 : -128 to 127												-> 255
 *	short 		Bytes 2 : -32,768 to 32,767											-> 65,535
 *	int 		Bytes 4 : -2,147,483,648 to 2,147,483,647							-> 4,294,967,295
 *	long 		Bytes 4 : -2,147,483,648 to 2,147,483,647							-> 4,294,967,295
 *	long long	Bytes 8 : -9,223,372,036,854,775,808 to 9,223,372,036,854,775,808	-> 18,446,744,073,709,551,615
 *
 *	64 bits
 *	char 		Bytes 1 : -128 to 127												-> 255
 *	short 		Bytes 2 : -32,768 to 32,767											-> 65,535
 *	int 		Bytes 4 : -2,147,483,648 to 2,147,483,647							-> 4,294,967,295
 *	long 		Bytes 8 : -9,223,372,036,854,775,808 to 9,223,372,036,854,775,808	-> 18,446,744,073,709,551,615
 *	long long	Bytes 8 : -9,223,372,036,854,775,808 to 9,223,372,036,854,775,808	-> 18,446,744,073,709,551,615
 *
 *	32 & 64 bits
 *	float		Bytes 4 :
 *	double		Bytes 8 :
 *	long double	Bytes 16:
*/
// Signed
using ll_char_t = char;
using ll_short_t = short;
using ll_int_t = int;
using ll_long_t = long;
using ll_longlong_t = long long;

// Unsigned
using ll_uchar_t = unsigned char;
using ll_ushort_t = unsigned short;
using ll_uint_t = unsigned int;
using ll_ulong_t = unsigned long;
using ll_ulonglong_t = unsigned long long;

// Floating-point
using ll_float_t = float;
using ll_double_t = double;
using ll_longdouble_t = long double;

// Other
using ll_wchar_t = wchar_t;

// Simplified Signed
using i8 = ll_char_t;
using i16 = ll_short_t;
using i32 = ll_int_t;
using i64 = ll_longlong_t;

// Simplified Unsigned
using ui8 = ll_uchar_t;
using ui16 = ll_ushort_t;
using ui32 = ll_uint_t;
using ui64 = ll_ulonglong_t;

// Simplified Floating-point
using f32 = ll_float_t;
using f64 = ll_double_t;
using f128 = ll_longdouble_t;

#pragma endregion
#pragma region LibaryCustom
using len_t = ui64;							// Used to cound things (natural number)
using cmp_t = i32;							// Old type in comparations, compatible with C libs

using ll_string_t = const ll_char_t*;		// Used to point to non editable strings
using ll_wstring_t = const ll_wchar_t*;		// Used to point to non editable strings
/// [DEPRECATED] Unsigned char sometimes crashes Visual Studio IntelliSense
///					using traits
using ll_ustring_t = const ll_uchar_t*;		// Used to point to non editable unsigned strings 

using ll_lib_t = void*;						// Handle for dynamic library linked/shared objects

#pragma region BytesTypes
using size_bytes8_t = ui8;
using size_bytes16_t = ui16;
using size_bytes32_t = ui32;
using size_bytes64_t = ui64;

using b8 = size_bytes8_t;
using b16 = size_bytes16_t;
using b32 = size_bytes32_t;
using b64 = size_bytes64_t;

#pragma endregion

#pragma endregion
#pragma region StandardIncompleteTypes

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4643) // ignore fordward declaration of some c++ classes
#endif // WINDOWS_SYSTEM

namespace std {
struct strong_ordering;
struct partial_ordering;

template <class _Ty>
class allocator;
template <class _Elem>
struct char_traits;
template <class _Elem, class _Traits, class _Alloc>
class basic_string;
template <class _Elem, class _Traits>
class basic_string_view;

using string  = basic_string<char, char_traits<char>, allocator<char>>;
using wstring  = basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t>>;
using string_view = basic_string_view<char, char_traits<char>>;
using wstring_view = basic_string_view<wchar_t, char_traits<wchar_t>>;

template <class _Fty>
class function;
//template <class _Ty, class _Alloc = allocator<_Ty>>
//class vector;
//template <class _Ty, class _Alloc = allocator<_Ty>>
//class list;

template <class T1, class T2>
struct pair;

template <class _Ty>
class optional;

namespace filesystem {
class directory_entry;
} // namespace filesystem

} // namespace std

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#pragma endregion

namespace llcpp {

struct EmptyStruct {};
class Emptyclass {};

namespace meta {

using StandardComparation = std::strong_ordering;

template<class T>
class ArrayPair;
template<class T>
class Array;

using StrPair	= ArrayPair<ll_char_t>;
using wStrPair	= ArrayPair<ll_wchar_t>;
using Str		= Array<ll_char_t>;
using wStr		= Array<ll_wchar_t>;

namespace hash {

class Hash32;
class Hash64;
class Hash128;

//using OptionalHash32		= std::optional<hash::Hash32>;
//using OptionalHash64		= std::optional<hash::Hash64>;
//using OptionalHash128		= std::optional<hash::Hash128>;

using StandardHash			= Hash64;
//using StandardOptionalHash	= OptionalHash64;

} // namespace hash

template<class CharType, class HashType>
class Typeid;
using StrTypeid		= Typeid<ll_char_t, hash::Hash64>;
using wStrTypeid	= Typeid<ll_wchar_t, hash::Hash64>;

} // namespace meta

} // namespace llcpp

#endif // LLANYLIB_TYPESBASE_HPP_
