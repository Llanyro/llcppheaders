//////////////////////////////////////////////
//	types.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 6.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPES_HPP_) // Guard && version protector
	#if LLANYLIB_TYPES_MAYOR_ != 6 || LLANYLIB_TYPES_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "types.hpp version error!"
		#else
			#error "types.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_TYPES_MAYOR_ || LLANYLIB_TYPES_MINOR_

#else !defined(LLANYLIB_TYPES_HPP_)
#define LLANYLIB_TYPES_HPP_
#define LLANYLIB_TYPES_MAYOR_ 6
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
using StrPair = ArrayPair<ll_char_t>;
using wStrPair = ArrayPair<ll_wchar_t>;

// Hash container type
struct Hash {
	ui64 value;
	constexpr Hash() __LL_EXCEPT__ : value(ZERO_UI64) {}
	constexpr Hash(const ui64 value) __LL_EXCEPT__ : value(value) {}
	constexpr ~Hash() __LL_EXCEPT__ {}

	constexpr Hash(const Hash& other) __LL_EXCEPT__ : value(other.value) {}
	constexpr Hash& operator=(const Hash& other) __LL_EXCEPT__ {
		this->value = other.value;
		return *this;
	}

	constexpr Hash(Hash&& other) __LL_EXCEPT__ : Hash(other) { other.clear(); }
	constexpr Hash& operator=(Hash&& other) __LL_EXCEPT__ {
		Hash::operator=(other);
		other.clear();
		return *this;
	}

	__LL_NODISCARD__ constexpr operator typename const Hash*() const __LL_EXCEPT__ = delete;
	__LL_NODISCARD__ constexpr operator typename Hash*() __LL_EXCEPT__ = delete;

	constexpr void clear() __LL_EXCEPT__ { this->value = ZERO_UI64; }
};

using StrPairHashFunction = meta::Hash(*)(const meta::StrPair&);
using HashFunction = meta::Hash(*)(ll_string_t, const len_t);
using HashRecursiveFunction = meta::Hash(*)(const meta::Hash&);

struct HashFunctionPack {
	StrPairHashFunction strPairHashFunction;
	HashFunction hashFunction;
	HashRecursiveFunction hashRecursiveFunction;

#pragma region Functions
	#pragma region Constructors
	constexpr HashFunctionPack(
		StrPairHashFunction strPairHashFunction,
		HashFunction hashFunction,
		HashRecursiveFunction hashRecursiveFunction
	) __LL_EXCEPT__
		: strPairHashFunction(strPairHashFunction)
		, hashFunction(hashFunction)
		, hashRecursiveFunction(hashRecursiveFunction)
	{}
	constexpr HashFunctionPack() __LL_EXCEPT__
		: HashFunctionPack(LL_NULLPTR, LL_NULLPTR, LL_NULLPTR) {}
	constexpr ~HashFunctionPack() __LL_EXCEPT__ {}

	#pragma endregion
	#pragma region CopyMove
	constexpr HashFunctionPack(const HashFunctionPack& other) __LL_EXCEPT__
		: HashFunctionPack(
			other.strPairHashFunction,
			other.hashFunction,
			other.hashRecursiveFunction
		)
	{}
	constexpr HashFunctionPack& operator=(const HashFunctionPack& other) __LL_EXCEPT__ {
		this->strPairHashFunction = other.strPairHashFunction;
		this->hashFunction = other.hashFunction;
		this->hashRecursiveFunction = other.hashRecursiveFunction;
		return *this;
	}

	constexpr HashFunctionPack(HashFunctionPack&& other) __LL_EXCEPT__
		: HashFunctionPack(other)
	{ other.clear(); }
	constexpr HashFunctionPack& operator=(HashFunctionPack&& other) __LL_EXCEPT__ {
		HashFunctionPack::operator=(other);
		other.clear();
		return *this;
	}

	#pragma endregion
	#pragma region ClassReferenceOperators
	__LL_NODISCARD__ constexpr operator typename const HashFunctionPack*() const __LL_EXCEPT__ = delete;
	__LL_NODISCARD__ constexpr operator typename HashFunctionPack*() __LL_EXCEPT__ = delete;

	#pragma endregion
	#pragma region ClassFunctions
	constexpr void clear() __LL_EXCEPT__ {
		this->strPairHashFunction = LL_NULLPTR;
		this->hashFunction = LL_NULLPTR;
		this->hashRecursiveFunction = LL_NULLPTR;
	}

	#pragma region Calls
	constexpr meta::Hash call(const meta::StrPair& s) const __LL_EXCEPT__ {
		return this->strPairHashFunction(s);
	}
	constexpr meta::Hash call(ll_string_t s, const len_t n) const __LL_EXCEPT__ {
		return this->hashFunction(s, n);
	}
	constexpr meta::Hash call(const meta::Hash& h) const __LL_EXCEPT__ {
		return this->hashRecursiveFunction(h);
	}
	constexpr meta::Hash call_s(const meta::StrPair& s) const __LL_EXCEPT__ {
		return (this->strPairHashFunction) ? this->strPairHashFunction(s) : meta::Hash();
	}
	constexpr meta::Hash call_s(ll_string_t s, const len_t n) const __LL_EXCEPT__ {
		return (this->hashFunction) ? this->hashFunction(s, n) : meta::Hash();
	}
	constexpr meta::Hash call_s(const meta::Hash& h) const __LL_EXCEPT__ {
		return (this->hashRecursiveFunction) ? this->hashRecursiveFunction(h) : meta::Hash();
	}

	constexpr meta::Hash operator()(const meta::StrPair& s) const __LL_EXCEPT__ {
		return this->call(s);
	}
	constexpr meta::Hash operator()(ll_string_t s, const len_t n) const __LL_EXCEPT__ {
		return this->call(s, n);
	}
	constexpr meta::Hash operator()(const meta::Hash& h) const __LL_EXCEPT__ {
		return this->call(h);
	}

	#pragma endregion
	#pragma endregion
#pragma endregion
};

#pragma endregion

namespace functional {

using Compare = cmp_t(*)(const void* __t1, const void* __t2);
using CompareBool = ll_bool_t(*)(const void* __t1, const void* __t2);
using CompareExtra = cmp_t(*)(const void* __t1, const void* __t2, void* __extra__);
using CompareBoolExtra = ll_bool_t(*)(const void* __t1, const void* __t2, void* __extra__);

namespace classic {
template<class T, class U = T>
using Compare = cmp_t(*)(T __t1, U __t2);
template<class T, class U = T>
using CompareBool = ll_bool_t(*)(T __t1, U __t2);
template<class T, class U = T>
using SwapFunction = void(*)(T& __t1, U& __t2);
template<class T, class U = T&>
using SetFunction = void(*)(T& __t1, U __t2);

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
