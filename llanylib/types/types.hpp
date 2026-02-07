//////////////////////////////////////////////
//	types.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 15.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPESBASE_HPP_) // Guard && version protector
	#if LLANYLIB_TYPESBASE_MAYOR_ != 15 || LLANYLIB_TYPESBASE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "types.hpp version error!"
		#else
			#error "types.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPESBASE_MAYOR_ || LLANYLIB_TYPESBASE_MINOR_

#elif !defined(LLANYLIB_TYPESBASE_HPP_)
	#define LLANYLIB_TYPESBASE_HPP_
	#define LLANYLIB_TYPESBASE_MAYOR_ 15
	#define LLANYLIB_TYPESBASE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include "../defines/expresions.hpp"
#else
	#include <llanylib/defines/expresions.hpp>
#endif // LL_LIB_PATHS

#if defined(__LL_WINDOWS_SYSTEM)
	#include <cstdint>
	#include <cuchar>
#elif defined(__LL_MINGW)
#elif defined(__LL_POSIX_SYSTEM)
#elif defined(__LL_UNIX_SYSTEM)
#else
#endif // __LL_WINDOWS_SYSTEM

#pragma region StandardIncompleteTypes

#if defined(__LL_WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4643) // ignore fordward declaration of some c++ classes
#endif // __LL_WINDOWS_SYSTEM

namespace std {
struct strong_ordering;
struct partial_ordering;
struct weak_ordering;
template <class _Fty>
class function;
template <class T1, class T2>
struct pair;
namespace filesystem {
class directory_entry;
} // namespace filesystem

} // namespace std

#if defined(__LL_WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // __LL_WINDOWS_SYSTEM

#pragma endregion

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
#undef __cpp_char8_t
#if defined(__cpp_char8_t)
	#define __LL_8BIT_CHAR ::std::char8_t
	#define __LL_8BIT_CHAR_EX , __LL_8BIT_CHAR
#else
	#define __LL_8BIT_CHAR
	#define __LL_8BIT_CHAR_EX
#endif // __cpp_char8_t

using ll_wchar_t		= wchar_t;
using ll_bool_t			= bool;
enum class LoopResult { Conntinue, Error, Ok, BeginError, Unknown };

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

using ll_char16_t		= char16_t;
using ll_char32_t		= char32_t;

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

#define __LL_INTEGRAL_CHAR_TYPES	ll_char_t, ll_uchar_t, ll_wchar_t, ll_char16_t, ll_char32_t __LL_8BIT_CHAR_EX
#define __LL_INTEGRAL_TYPES			u8, u16, u32, u64, i8, i16, i32, i64, ll_bool_t, __LL_INTEGRAL_CHAR_TYPES

#pragma endregion
#pragma region LibaryCustom

#if __LL_USE_WIDE_CHAR == 0
	using char_type	= ll_char_t;	// Default char type by program propiedies (char, wchar, ...)
#elif __LL_USE_WIDE_CHAR == 1
	using char_type	= ll_wchar_t;	// Default char type by program propiedies (char, wchar, ...)
#elif __LL_USE_WIDE_CHAR == 2
	using char_type	= ll_char16_t;	// Default char type by program propiedies (char, wchar, ...)
#elif __LL_USE_WIDE_CHAR == 3
	using char_type	= ll_char32_t;	// Default char type by program propiedies (char, wchar, ...)
#endif // __LL_USE_WIDE_CHAR

using string				= const char_type*;
using c_cmp_t				= i32;					// Old type in comparations, compatible with C libs

using ll_ustring_t			= const ll_uchar_t*;	// Used to point to non editable unsigned strings 
using ll_string_t			= const ll_char_t*;		// Used to point to non editable strings
using ll_wstring_t			= const ll_wchar_t*;	// Used to point to non editable strings
using ll_string16_t			= const ll_char16_t*;	// Used to point to non editable strings
using ll_string32_t			= const ll_char32_t*;	// Used to point to non editable strings
using ll_lib_t				= void*;				// Handle for dynamic library linked/shared objects
//using len_t				= void;
using StandardComparation	= ::std::strong_ordering;

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
#pragma region Hash
using Hash8			= u8;		// 8 bits Hash
using Hash16		= u16;		// 16 bits Hash
using Hash32		= u32;		// 32 bits Hash
using Hash64		= u64;		// 64 bits Hash
using StandardHash	= usize;	// Hash by system prop

#pragma endregion
#pragma endregion
#pragma region Tags

// This class and all classes that inherits from this, should be always a valid class
//	It doesnt matter the situation (clear, move, etc)
// All objects should keep in a valid state
struct AlwaysValidTag												{ using _MyType = AlwaysValidTag; };
// This class and all classes that inherits from this, can never be valid objects
// All objects should keep in an invalid/unchecked state
struct AlwaysInvalidTag												{ using _MyType = AlwaysInvalidTag; };
// Null class
// Its purpose is to be a 'void' class type object
struct Emptyclass : public ::llcpp::AlwaysInvalidTag				{ using _MyType = Emptyclass; };
// This class is a base thet does not inherits from anything
// Can be used to be inherited if any error is detected 
//	like inherit from AlwaysValidTag and AlwaysInvalidTag at the same time
struct DummyClass													{ using _MyType = DummyClass; };
// When using incomplete lib && some type is not possible to exist but using complete lib
//	this type will be used
struct UndefinedIncompleteObject : public ::llcpp::AlwaysInvalidTag	{ using _MyType = UndefinedIncompleteObject; };
// Clusters are templates that shares same position as interfaces
// That means:
//	- Interfaces are classes that shares the same group of funtions to make a generic use of classes
//	- Clusters are interfaces, but has no virtual methods, since they can be used as constexpr (metaprogramming)
// Other differences are:
//	CPP file:
//		Interfaces should have a CPP file
//		Clusters are full template classes, so they cant have it
//	Virtual:
//		Interfaces destructor should be virtual
//		Clusters cannot have virtual methods (its not permited in metaprogramming)
//	Inheritance:
//		Interfaces are inherited from objects that overrides its virtual functions
//		Clusters inherit from classes that gives them functions that they need to work
//	Functions:
//		Interfaces can have any type of functions
//		Clusters can only have const functions (by llanystandard)
struct ClusterTag													{ using _MyType = ClusterTag; };
// HalfClusters are similar to clusters but has a few differences
// HalfClusters should inherit also from an object
// The object inherited usually is edited by HalfCluster's functions
//	So, the main difference its that HalfClusters can have "no const" functions that enable
//	inherited object edition Ex: llcpp::meta::linked::FunctionalNode
class HalfClusterTag												{ using _MyType = HalfClusterTag; };

#pragma endregion

#if __LL_USE_IGNORE_AUTO__ == 1
	__LL_INLINE__ constexpr void LL_IGNORE(auto...) {}
#else
	template<class... Args> __LL_INLINE__ constexpr void LL_IGNORE(Args&&...) {}
#endif // __LL_USE_IGNORE_AUTO__

// Zero value or default value returns a base type (default contructor)
template<class T>
__LL_VAR_INLINE__ constexpr T	ZERO_VALUE				= T{};
template<class T>
__LL_VAR_INLINE__ constexpr T*	ZERO_VALUE<T*>			= LL_NULLPTR;
template<class T>
__LL_VAR_INLINE__ constexpr T*	NULL_VALUE				= LL_NULLPTR;

template<class>
__LL_VAR_INLINE__ constexpr usize array_size			= ::llcpp::ZERO_VALUE<usize>;
template<class T, usize N>
__LL_VAR_INLINE__ constexpr usize array_size<T[N]>		= N;

//template<class>
//__LL_VAR_INLINE__ constexpr usize type_or_array_size = 1ull;
//template<class T, usize N>
//__LL_VAR_INLINE__ constexpr usize type_or_array_size<T[N]> = N;

__LL_VAR_INLINE__ constexpr ll_bool_t LL_FALSE			= false;
__LL_VAR_INLINE__ constexpr ll_bool_t LL_TRUE			= true;

__LL_VAR_INLINE__ constexpr i32 LL_FAILURE_EXECUTION	= __LL_FAILURE_EXECUTION__;
__LL_VAR_INLINE__ constexpr i32 LL_SUCCESS_EXECUTION	= __LL_SUCCESS_EXECUTION__;

template<ll_bool_t FORWARD, class T, class U>
constexpr void forward_copy(T t, U u) noexcept {}
template<class T, class U>
constexpr void forward_copy<::llcpp::LL_TRUE, T, U>(T t, U u) noexcept {
	t = ::std::forward<const U&>(u);
}

template<ll_bool_t FORWARD, class T, class U>
constexpr void forward_move(T t, U u) noexcept {}
template<class T, class U>
constexpr void forward_move<::llcpp::LL_TRUE, T, U>(T t, U u) noexcept {
	t = ::std::forward<U&&>(u);
}

namespace meta {
namespace algorithm {

__LL_VAR_INLINE__ constexpr usize MAX_LIST_SIZE	= static_cast<usize>(-1);
__LL_VAR_INLINE__ constexpr usize npos			= ::llcpp::meta::algorithm::MAX_LIST_SIZE;

} // namespace algorithm
} // namespace meta

#if __LL_INCLUDE_KATS == 1
namespace kat {

#pragma region ZeroValue
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_ZERO_VALUE = 
	   ::llcpp::ZERO_VALUE<u8>  == 0
	&& ::llcpp::ZERO_VALUE<u16> == 0
	&& ::llcpp::ZERO_VALUE<u32> == 0
	&& ::llcpp::ZERO_VALUE<u64> == 0
	&& ::llcpp::ZERO_VALUE<i8>  == 0
	&& ::llcpp::ZERO_VALUE<i16> == 0
	&& ::llcpp::ZERO_VALUE<i32> == 0
	&& ::llcpp::ZERO_VALUE<i64> == 0
	&& ::llcpp::ZERO_VALUE<void*> == LL_NULLPTR;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_zero_value,
	::llcpp::kat::IS_WORKING_ZERO_VALUE,
	"'::llcpp::ZERO_VALUE'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region ArraySize
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_ARRAY_SIZE = 
	   ::llcpp::array_size<u8>  == 0
	&& ::llcpp::array_size<u16> == 0
	&& ::llcpp::array_size<u32> == 0
	&& ::llcpp::array_size<u64> == 0
	&& ::llcpp::array_size<i8>  == 0
	&& ::llcpp::array_size<i16> == 0
	&& ::llcpp::array_size<i32> == 0
	&& ::llcpp::array_size<i64> == 0
	&& ::llcpp::array_size<void*> == 0
	&& ::llcpp::array_size<i32[5]> == 5;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_array_size,
	::llcpp::kat::IS_WORKING_ARRAY_SIZE,
	"'::llcpp::array_size'"
);

#pragma endregion

__LL_NODISCARD__ constexpr ::llcpp::string types_kats() noexcept {
	::llcpp::string result = ::llcpp::kat::is_working_zero_value();
	if(result) return result;
	result = ::llcpp::kat::is_working_array_size();
	if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::kat::types_kats() == LL_NULLPTR, "types.hpp KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace llcpp

#endif // LLANYLIB_TYPESBASE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
