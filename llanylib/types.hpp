//////////////////////////////////////////////
//	types.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPES_HPP_) // Guard && version protector
	#if LLANYLIB_TYPES_MAYOR_ != 8 || LLANYLIB_TYPES_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "types.hpp version error!"
		#else
			#error "types.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_TYPES_MAYOR_ || LLANYLIB_TYPES_MINOR_

#else !defined(LLANYLIB_TYPES_HPP_)
#define LLANYLIB_TYPES_HPP_
#define LLANYLIB_TYPES_MAYOR_ 8
#define LLANYLIB_TYPES_MINOR_ 0

#include "definitions.hpp"

namespace llcpp {

template<class T>
struct ByteExtender {
	T l;
	T h;
};

struct EmptyStruct {};

} // namespace llcpp

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
using ll_bool_t = bool;
using ll_wchar_t = wchar_t;

// Simplified Signed
using i8 = ll_char_t;
using i16 = ll_short_t;
using i32 = ll_int_t;
using i64 = ll_longlong_t;
using i128 = llcpp::ByteExtender<i64>;
using i256 = llcpp::ByteExtender<i128>;

// Simplified Unsigned
using ui8 = ll_uchar_t;
using ui16 = ll_ushort_t;
using ui32 = ll_uint_t;
using ui64 = ll_ulonglong_t;
using ui128 = llcpp::ByteExtender<ui64>;
using ui256 = llcpp::ByteExtender<ui128>;

// Simplified Floating-point
using f32 = ll_float_t;
using f64 = ll_double_t;
using f128 = ll_longdouble_t;

#pragma endregion
#pragma region LibaryCustom
using len_t = ui64;							// Used to cound things (natural number)
using cmp_t = i32;							// Default type in comparations

using ll_string_t = const ll_char_t*;		// Used to point to non editable strings
using ll_wstring_t = const ll_wchar_t*;		// Used to point to non editable strings
/// [DEPRECATED] Unsigned char sometimes crashes Visual Studio IntelliSense
using ll_ustring_t = const ll_uchar_t*;		// Used to point to non editable unsigned strings 

using ll_lib_t = void*;						// Handle for dynamic library linked/shared objects

#pragma region BytesTypes
using size_bytes8_t = ui8;
using size_bytes16_t = ui16;
using size_bytes32_t = ui32;
using size_bytes64_t = ui64;
using size_bytes128_t = ui128;

using b8 = size_bytes8_t;
using b16 = size_bytes16_t;
using b32 = size_bytes32_t;
using b64 = size_bytes64_t;
using b128 = size_bytes128_t;

#pragma endregion

#pragma endregion
#pragma region StandardIncompleteTypes

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4643) // ignore fordward declaration of some c++ classes
#endif // WINDOWS_SYSTEM

namespace std {
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

#pragma region Expresions
constexpr ll_bool_t LL_TRUE = true;
constexpr ll_bool_t LL_FALSE = false;

constexpr ui8 ZERO_UI8 = 0u;
constexpr ui16 ZERO_UI16 = 0u;
constexpr ui32 ZERO_UI32 = 0u;
constexpr ui64 ZERO_UI64 = 0ull;

constexpr i8 ZERO_I8 = 0;
constexpr i16 ZERO_I16 = 0;
constexpr i32 ZERO_I32 = 0;
constexpr i64 ZERO_I64 = 0ll;

constexpr f32 ZERO_F32 = 0.0f;
constexpr f64 ZERO_F64 = 0.0;
constexpr f128 ZERO_F128 = 0.0l;
#pragma endregion
#pragma region Types
namespace meta {

template<class T>
class ArrayPair;
template<class T>
class Array;
template<class T, ll_bool_t IS_STRINGVIEW>
class ArrayView;

using StrPair = ArrayPair<ll_char_t>;
using wStrPair = ArrayPair<ll_wchar_t>;

using Str = Array<ll_char_t>;
using wStr = Array<ll_wchar_t>;

template<class T>
class Typeid;
using StrTypeid = Typeid<ll_char_t>;
using wStrTypeid = Typeid<ll_wchar_t>;

namespace hash {
class Hash32;
class Hash64;
class Hash128;
class Hash32FunctionPack;
class Hash64FunctionPack;
class Hash128FunctionPack;

using OptionalHash32 = std::optional<hash::Hash32>;
using OptionalHash64 = std::optional<hash::Hash64>;
using OptionalHash128 = std::optional<hash::Hash128>;

#pragma region 32
using Hash32Function = hash::OptionalHash32(*)(ll_string_t, len_t) noexcept;
using wHash32Function = hash::OptionalHash32(*)(ll_wstring_t, len_t) noexcept;
using StringPairHash32Function = hash::OptionalHash32(*)(const std::string&) noexcept;
using wStringPairHash32Function = hash::OptionalHash32(*)(const std::wstring&) noexcept;
using StrPairHash32Function = hash::OptionalHash32(*)(const meta::StrPair&) noexcept;
using wStrPairHash32Function = hash::OptionalHash32(*)(const meta::wStrPair&) noexcept;
using StrHash32Function = hash::OptionalHash32(*)(const meta::Str&) noexcept;
using wStrHash32Function = hash::OptionalHash32(*)(const meta::wStr&) noexcept;
using RecursiveHash32Function = hash::OptionalHash32(*)(const hash::Hash32&) noexcept;
using StrTypeidHash32Function = hash::OptionalHash32(*)(const void*, const StrTypeid&) noexcept;
using wStrTypeidHash32Function = hash::OptionalHash32(*)(const void*, const wStrTypeid&) noexcept;

#pragma endregion
#pragma region 64
using Hash64Function = hash::OptionalHash64(*)(ll_string_t, len_t) noexcept;
using wHash64Function = hash::OptionalHash64(*)(ll_wstring_t, len_t) noexcept;
using StringPairHash64Function = hash::OptionalHash64(*)(const std::string&) noexcept;
using wStringPairHash64Function = hash::OptionalHash64(*)(const std::wstring&) noexcept;
using StrPairHash64Function = hash::OptionalHash64(*)(const meta::StrPair&) noexcept;
using wStrPairHash64Function = hash::OptionalHash64(*)(const meta::wStrPair&) noexcept;
using StrHash64Function = hash::OptionalHash64(*)(const meta::Str&) noexcept;
using wStrHash64Function = hash::OptionalHash64(*)(const meta::wStr&) noexcept;
using RecursiveHash64Function = hash::OptionalHash64(*)(const hash::Hash64&) noexcept;
using StrTypeidHash64Function = hash::OptionalHash64(*)(const void*, const StrTypeid&) noexcept;
using wStrTypeidHash64Function = hash::OptionalHash64(*)(const void*, const wStrTypeid&) noexcept;

#pragma endregion
#pragma region 128
using Hash128Function = hash::OptionalHash128(*)(ll_string_t, len_t) noexcept;
using wHash128Function = hash::OptionalHash128(*)(ll_wstring_t, len_t) noexcept;
using StringPairHash128Function = hash::OptionalHash128(*)(const std::string&) noexcept;
using wStringPairHash128Function = hash::OptionalHash128(*)(const std::wstring&) noexcept;
using StrPairHash128Function = hash::OptionalHash128(*)(const meta::StrPair&) noexcept;
using wStrPairHash128Function = hash::OptionalHash128(*)(const meta::wStrPair&) noexcept;
using StrHash128Function = hash::OptionalHash128(*)(const meta::Str&) noexcept;
using wStrHash128Function = hash::OptionalHash128(*)(const meta::wStr&) noexcept;
using RecursiveHash128Function = hash::OptionalHash128(*)(const hash::Hash128&) noexcept;
using StrTypeidHash128Function = hash::OptionalHash128(*)(const void*, const StrTypeid&) noexcept;
using wStrTypeidHash128Function = hash::OptionalHash128(*)(const void*, const wStrTypeid&) noexcept;

#pragma endregion

} // namespace hash

#pragma endregion

namespace functional {

using Compare = cmp_t(*)(const void* __t1, const void* __t2) noexcept;
using CompareBool = ll_bool_t(*)(const void* __t1, const void* __t2) noexcept;
using CompareExtra = cmp_t(*)(const void* __t1, const void* __t2, void* __extra__) noexcept;
using CompareBoolExtra = ll_bool_t(*)(const void* __t1, const void* __t2, void* __extra__) noexcept;

namespace classic {
template<class T, class U = T>
using Compare = cmp_t(*)(T __t1, U __t2) noexcept;
template<class T, class U = T>
using CompareBool = ll_bool_t(*)(T __t1, U __t2) noexcept;
template<class T, class U = T>
using SwapFunction = void(*)(T& __t1, U& __t2) noexcept;
template<class T, class U = T&>
using SetFunction = void(*)(T& __t1, U __t2) noexcept;

} // namespace classic
namespace lambda {

template<class T, class U = T>
using Compare = std::function<cmp_t(T __t1, U __t2)>;
template<class T, class U = T>
using CompareBool = std::function<ll_bool_t(T __t1, U __t2)>;
template<class T, class U = T>
using SwapFunction = std::function<void(T& __t1, U& __t2)>;
template<class T, class U = T&>
using SetFunction = std::function<void(T& __t1, U __t2)>;

template<class T>
using SearchFunction = std::function<cmp_t(T __t1)>;
template<class T>
using SearchFunctionBool = std::function<ll_bool_t(T __t1)>;

} // namespace lambda
} // namespace functional
} // namespace meta

namespace fnc_clss = meta::functional::classic;
namespace fnc_lmb = meta::functional::lambda;

} // namespace llcpp

#endif // LLANYLIB_TYPES_HPP_
