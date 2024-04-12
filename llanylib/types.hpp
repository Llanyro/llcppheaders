//////////////////////////////////////////////
//	types.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 4.2							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPES_HPP_) // Guard && version protector
	#if LLANYLIB_TYPES_MAYOR_ != 4 || LLANYLIB_TYPES_MINOR_ < 2
		#error "types.hpp version error!"
	#endif // LLANYLIB_TYPES_MAYOR_ || LLANYLIB_TYPES_MINOR_

#else !defined(LLANYLIB_TYPES_HPP_)
#define LLANYLIB_TYPES_HPP_
#define LLANYLIB_TYPES_MAYOR_ 4
#define LLANYLIB_TYPES_MINOR_ 2

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
using ll_wstring_t = const __wchar_t*;		// Used to point to non editable strings
using ll_ustring_t = const ll_uchar_t*;		// Used to point to non editable unsigned strings

using ll_lib_t = void*;						// Handle for dynamic library linked/shared objects

struct StrPair {
	ll_string_t str;
	len_t len;
};

struct wStrPair {
	ll_wstring_t str;
	len_t len;
};

template<class T>
struct ArrayPair {
	const T* data;
	len_t len;
};


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
using string  = basic_string<char, char_traits<char>, allocator<char>>;
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

namespace functional {

/*!
 *	@template False
 *	@brief Function type to compare 2 objects
 *
 *	This needs to return a value to check if object __t1 is same to object __t2
 *	The implementation of this function needs to return:
 *		 0 if both are the same
 *		-1 if __t1 smaller
 *		 1 if __t1 is bigger
 * 
 *	@param[in] __t1 First object to compare
 *	@param[in] __t2 Second object to compare
 *
 *	@return Comparacion result
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
using Compare = cmp_t(*)(const void* __t1, const void* __t2);
/*!
 *	@template False
 *	@brief Function type to compare 2 objects
 *
 *	@param[in] __t1 First object to compare
 *	@param[in] __t2 Second object to compare
 *
 *	@return True if __t1 is same as __t2
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
using CompareBool = ll_bool_t(*)(const void* __t1, const void* __t2);

/*!
 *	@template False
 *	@brief Function type to compare 2 objects
 *
 *	This needs to return a value to check if object __t1 is same to object __t2
 *	The implementation of this function needs to return:
 *		 0 if both are the same
 *		-1 if __t1 smaller
 *		 1 if __t1 is bigger
 * 
 *	@param[in] __t1 First object to compare
 *	@param[in] __t2 Second object to compare
 *	@param[in] __extra__ Extra data to being used by user
 *
 *	@return Comparacion result
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
using CompareExtra = cmp_t(*)(const void* __t1, const void* __t2, void* __extra__);
/*!
 *	@template False
 *	@brief Function type to compare 2 objects
 *
 *	@param[in] __t1 First object to compare
 *	@param[in] __t2 Second object to compare
 *	@param[in] __extra__ Extra data to being used by user
 *
 *	@return True if __t1 is same as __t2
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
using CompareBoolExtra = ll_bool_t(*)(const void* __t1, const void* __t2, void* __extra__);

namespace classic {
/*!
 *	@template True
 *	@brief Function type to compare 2 objects
 *
 *	This needs to return a value to check if object __t1 is same to object __t2
 *	The implementation of this function needs to return:
 *		 0 if both are the same
 *		-1 if __t1 smaller
 *		 1 if __t1 is bigger
 * 
 *	@param[in] __t1 First object to compare
 *	@param[in] __t2 Second object to compare
 *
 *	@return Comparacion result
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
template<class T>
using Compare = cmp_t(*)(const T& __t1, const T& __t2);
/*!
 *	@template True
 *	@brief Function type to compare 2 objects
 *
 *	@param[in] __t1 First object to compare
 *	@param[in] __t2 Second object to compare
 *
 *	@return True if __t1 is same as __t2
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
template<class T>
using CompareBool = ll_bool_t(*)(const T& __t1, const T& __t2);
/*!
 *	@template True
 *	@brief Swaps 2 objects
 *
 *	@param[in] __t1 First object to swap
 *	@param[in] __t2 Second object to swap
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref swap
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
template<class T>
using SwapFunction = void(*)(T& __t1, T& __t2);

} // namespace classic
namespace lambda {

/*!
 *	@template True
 *	@brief Function type to compare 2 objects
 *
 *	This needs to return a value to check if object __t1 is same to object __t2
 *	The implementation of this function needs to return:
 *		 0 if both are the same
 *		-1 if __t1 smaller
 *		 1 if __t1 is bigger
 * 
 *	@param[in] __t1 First object to compare
 *	@param[in] __t2 Second object to compare
 *
 *	@return Comparacion result
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
template<class T>
using SearchFunctioni32 = std::function<i32(const T& __t1)>;
/*!
 *	@template True
 *	@brief Function type to compare 2 objects
 *
 *	@param[in] __t1 First object to compare
 *	@param[in] __t2 Second object to compare
 *
 *	@return True if __t1 is same as __t2
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
template<class T>
using SearchFunctionBool = std::function<ll_bool_t(const T& __t1)>;
/*!
 *	@template True
 *	@brief Swaps 2 objects
 *
 *	@param[in] __t1 First object to swap
 *	@param[in] __t2 Second object to swap
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref swap
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
template<class T>
using SwapFunction = std::function<void(T& __t1, T& __t2)>;

} // namespace lambda
} // namespace functional

namespace fnc_clss = functional::classic;
namespace fnc_lmb = functional::lambda;

} // namespace llcpp

#endif // LLANYLIB_TYPES_HPP_
