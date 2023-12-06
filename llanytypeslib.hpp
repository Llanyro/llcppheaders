/*
 * llanytypeslib.hpp
 *
 *  Created on: Feb 28, 2022
 *      Author: llanyro
 */

#ifndef LLCPP_HEADER_LLANYTYPESLIB_HPP_
#define LLCPP_HEADER_LLANYTYPESLIB_HPP_

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
#if defined(_WIN32) or defined(_WIN64)
#define WINDOWS_SYSTEM
#elif defined(__unix__)
#if defined(__linux__)
#define POSIX_SYSTEM
#else
#define UNIX_SYSTEM
#endif // 
#endif // _WIN32

/// Win dll
#if defined(WINDOWS_SYSTEM)
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

// Disables del pesao de windows
#if defined(WINDOWS_SYSTEM)
#pragma warning(disable:6029)

#pragma warning(disable:6011)
#pragma warning(disable:6387)
#pragma warning(disable:4996)


#pragma warning(disable:4251)
#pragma warning(disable:4244)
#pragma warning(disable:6031)

// Socket
#pragma warning(disable:4309)
#pragma warning(disable:4477)
#pragma warning(disable:26439)

// Wall
//#pragma warning(disable:4464)
#pragma warning(disable:4458) // parameter hides class member (just use "this->" to call member)
#pragma warning(disable:5045) // Security mitigation
#pragma warning(disable:4710) // Function not inlined
#pragma warning(disable:4711) // Function inlined
#pragma warning(disable:4514) // Function not used removed

#endif // defined(WINDOWS_SYSTEM)

#pragma endregion

// Added here to fix inline error /W4
#include <functional>

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
#define __LL_CONSTEXPR__ consteval
#define __LL_INLINE__ inline

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
typedef ui64 len_t;     // Used to cound things (natural number)

typedef const ll_char_t* ll_string_t;       // Used to point to non editable strings
typedef const ll_uchar_t* ll_ustring_t;     // Used to point to non editable unsigned strings


/// Tipos para control de bytes
typedef ui8 size_bytes8_t;      // Used to count bytes
typedef ui16 size_bytes16_t;	// Used to count bytes
typedef ui32 size_bytes32_t;	// Used to count bytes
typedef ui64 size_bytes64_t;	// Used to count bytes

typedef size_bytes8_t b8;	    // Used to count bytes
typedef size_bytes16_t b16;	    // Used to count bytes
typedef size_bytes32_t b32;	    // Used to count bytes
typedef size_bytes64_t b64;	    // Used to count bytes

#pragma endregion

namespace llcpp {

// Stores a string
class LL_SHARED_LIB StrPair {
    public:
        ll_string_t str;
        len_t len;

        constexpr StrPair() : str(nullptr), len(0ull) {}
        constexpr StrPair(ll_string_t str, const len_t len) : str(str), len(len) {}
        StrPair(const StrPair& other) : str(other.str), len(other.len) {}
        StrPair(StrPair&& other) : str(other.str), len(other.len) { other.clear(); }
        StrPair& operator=(const StrPair& other) {
            this->len = other.len;
            this->str = other.str;
            return *this;
        }
        StrPair& operator=(StrPair&& other) {
            this->len = other.len;
            this->str = other.str;
            other.clear();
            return *this;
        }

        __LL_NODISCARD__ ll_bool_t operator==(ll_string_t str) const {
            return str == this->str;
        }
        __LL_NODISCARD__ ll_bool_t operator==(const StrPair& str) const {
            return
                this->str == str.str &&
                this->len == str.len;
        }
        __LL_NODISCARD__ ll_bool_t operator!=(ll_string_t str) const {
            return !this->operator==(str);
        }
        __LL_NODISCARD__ ll_bool_t operator!=(const StrPair& str) const {
            return !this->operator==(str);
        }
        __LL_NODISCARD__ operator ll_bool_t() const { return this->str && this->len > 0; }

        void clear() {
            this->len = 0;
            this->str = nullptr;
        }
};

namespace functional {

/*!
*	@template False
*	@brief Function type to compare 2 objects
*
*   This needs to return a value to check if object __a__ is same to object __b__
*   The implementation of this function needs to return:
*       0 if both are the same
*      -1 if __a__ smaller
*       1 if __a__ is bigger
* 
*	@param[in] __a__ First object to compare
*	@param[in] __b__ Second object to compare
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
typedef i32 (*Comparei32)(const void* __a__, const void* __b__);
/*!
*	@template False
*	@brief Function type to compare 2 objects
*
*	@param[in] __a__ First object to compare
*	@param[in] __b__ Second object to compare
*
*	@return True if __a__ is same as __b__
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
typedef ll_bool_t (*CompareBool)(const void* __a__, const void* __b__);

/*!
*	@template False
*	@brief Function type to compare 2 objects
*
*   This needs to return a value to check if object __a__ is same to object __b__
*   The implementation of this function needs to return:
*       0 if both are the same
*      -1 if __a__ smaller
*       1 if __a__ is bigger
* 
*	@param[in] __a__ First object to compare
*	@param[in] __b__ Second object to compare
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
typedef i32 (*Comparei32Extra)(const void* __a__, const void* __b__, void* __extra__);
/*!
*	@template False
*	@brief Function type to compare 2 objects
*
*	@param[in] __a__ First object to compare
*	@param[in] __b__ Second object to compare
*	@param[in] __extra__ Extra data to being used by user
*
*	@return True if __a__ is same as __b__
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
typedef ll_bool_t (*CompareBoolExtra)(const void* __a__, const void* __b__, void* __extra__);

namespace classic {
/*!
*	@template True
*	@brief Function type to compare 2 objects
*
*   This needs to return a value to check if object __a__ is same to object __b__
*   The implementation of this function needs to return:
*       0 if both are the same
*      -1 if __a__ smaller
*       1 if __a__ is bigger
* 
*	@param[in] __a__ First object to compare
*	@param[in] __b__ Second object to compare
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
using SearchFunctioni32 = i32(*)(const T& __a__, const T& __b__);
/*!
*	@template True
*	@brief Function type to compare 2 objects
*
*	@param[in] __a__ First object to compare
*	@param[in] __b__ Second object to compare
*
*	@return True if __a__ is same as __b__
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
using SearchFunctionBool = ll_bool_t(*)(const T& __a__, const T& __b__);



/*!
*	@template True
*	@brief Swaps 2 objects
*
*	@param[in] __a__ First object to swap
*	@param[in] __b__ Second object to swap
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
using SwapFunction = void(*)(const T& __a__, const T& __b__);

} /* namespace classic */

namespace lambda {
/*!
*	@template True
*	@brief Function type to compare 2 objects
*
*   This needs to return a value to check if object __a__ is same to object __b__
*   The implementation of this function needs to return:
*       0 if both are the same
*      -1 if __a__ smaller
*       1 if __a__ is bigger
* 
*	@param[in] __a__ First object to compare
*	@param[in] __b__ Second object to compare
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
template<class T> using SearchFunctioni32 = std::function<i32(const T& __a__)>;
/*!
*	@template True
*	@brief Function type to compare 2 objects
*
*	@param[in] __a__ First object to compare
*	@param[in] __b__ Second object to compare
*
*	@return True if __a__ is same as __b__
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
template<class T> using SearchFunctionBool = std::function<ll_bool_t(const T& __a__)>;



/*!
*	@template True
*	@brief Swaps 2 objects
*
*	@param[in] __a__ First object to swap
*	@param[in] __b__ Second object to swap
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
using SwapFunction = std::function<void(T& __a__, T& __b__)>;


} /* namespace lambda */
} /* namespace functional */

} /* namespace llcpp */

#pragma region Definitions
#define LL_NULLPTR nullptr
// Easy string to StrPair
#define PAIR_STR(str) llcpp::StrPair{str, sizeof(str) - 1}
// Easy enabler for template functions
#define ENABLE_FUNCTION_PARAM(condition) std::enable_if<condition>::type* = nullptr

#pragma endregion

namespace llcpp {

#pragma region GenralExpresions
constexpr ll_bool_t LL_TRUE = true;
constexpr ll_bool_t LL_FALSE = false;

constexpr ll_string_t TRUE_STRING = "True";
constexpr ll_string_t FALSE_STRING = "False";

constexpr StrPair TRUE_STR_PAIR = PAIR_STR("True");
constexpr StrPair FALSE_STR_PAIR = PAIR_STR("False");

#pragma endregion

/*!
*	@template True
*	@brief Check if type inherits from other class
*
*	@param[in] v Pointer of class to check
*
*	@return If class T inherits from T2 true sis returned
*
*	@constexpr True
*
*	@thread_safety This function may be called from any thread.
*
*	@sa @ref llcpp
*
*	@since Added in version 1.0.
*
*	@ingroup llcpp
*	@ingroup headers
*/
template<class T2, class T>
__LL_NODISCARD__ constexpr ll_bool_t isSubType(const T* v) { return (dynamic_cast<const T2*>(v) != LL_NULLPTR); }
/*!
*	@template True
*	@brief Gets a string of a bool
*
*   Gives a user a string that represents the bool provided
*   true will be : "True"
*   false will be: "False"
*
*	@param[in] v Bool value
*
*	@return String that represents bool value
*
*	@constexpr True
*
*	@thread_safety This function may be called from any thread.
*
*	@sa @ref llcpp
*
*	@since Added in version 1.0.
*
*	@ingroup llcpp
*	@ingroup headers
*/
__LL_NODISCARD__ constexpr ll_string_t getBoolString(const ll_bool_t v) { return v ? TRUE_STRING : FALSE_STRING; }
/*!
*	@template True
*	@brief Gets a StrPair of a bool
*
*   Gives a user a string that represents the bool provided
*   true will be : { "True", 4 }
*   false will be: { "False", 5 }
*
*	@param[in] v Bool value
*
*	@return StrPair that represents bool value
*
*	@constexpr True
*
*	@thread_safety This function may be called from any thread.
*
*	@sa @ref llcpp
*
*	@since Added in version 1.0.
*
*	@ingroup llcpp
*	@ingroup headers
*/
__LL_NODISCARD__ constexpr const StrPair& getBoolStringPair(const ll_bool_t v) { return v ? TRUE_STR_PAIR : FALSE_STR_PAIR; }

namespace enums {

/*!
*	@template True
*	@brief Casts an enum to given type
*
*   This is the same to do as static_cast<T>
*
*	@param[in] enumValue Enum value to cast
*
*	@constexpr True
*
*	@return Value as type provided
*
*	@thread_safety This function may be called from any thread.
*
*	@sa @ref llcpp
*
*	@since Added in version 1.0.
*
*	@ingroup llcpp
*	@ingroup enums
*/
template<class ValueType, class EnumClass>
__LL_NODISCARD__ constexpr ValueType asType(const EnumClass enumValue) {
    return static_cast<ValueType>(enumValue);
}

//template<class ValueType, class EnumClass, class... EnumClasses>
//constexpr ValueType enumOrOperation() {
//    return ValueType();
//}

//template<class ValueType, class EnumClass, class... EnumClasses>
//constexpr ValueType enumOrOperation(const EnumClass _enum, const EnumClasses... _enums) {
//    return asType<ValueType, EnumClass>(_enum) | enumOrOperation<ValueType, EnumClass, EnumClasses...>(_enums...);
//}

} /* namespace enums */

} /* namespace llcpp */

#endif /* LLCPP_HEADER_LLANYTYPESLIB_HPP_ */
