//////////////////////////////////////////////
//	expresions.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 15.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DEFINITIONSEXPRESIONS_HPP_) // Guard && version protector
	#if LLANYLIB_DEFINITIONSEXPRESIONS_MAYOR_ != 15 || LLANYLIB_DEFINITIONSEXPRESIONS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "expresions.hpp version error!"
		#else
			#error "expresions.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_DEFINITIONSEXPRESIONS_MAYOR_ || LLANYLIB_DEFINITIONSEXPRESIONS_MINOR_

#elif !defined(LLANYLIB_DEFINITIONSEXPRESIONS_HPP_)
	#define LLANYLIB_DEFINITIONSEXPRESIONS_HPP_
	#define LLANYLIB_DEFINITIONSEXPRESIONS_MAYOR_ 15
	#define LLANYLIB_DEFINITIONSEXPRESIONS_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include "definitions.hpp"
#else
	#include <llanylib/defines/definitions.hpp>
#endif // LL_LIB_PATHS

namespace llcpp {

#pragma region DefaultDefinitions

#if defined(LL_STATIC_KATS)
	#undef LL_STATIC_KATS
#endif // LL_STATIC_KATS

#if defined(LL_INCLUDE_KATS)
	#undef LL_INCLUDE_KATS
#endif // LL_INCLUDE_KATS

#if defined(LL_USE_WIDE_CHAR)
	#undef LL_USE_WIDE_CHAR
#endif // LL_USE_WIDE_CHAR

__LL_VAR_INLINE__ constexpr bool LL_STATIC_KATS						= __LL_STATIC_KATS;
__LL_VAR_INLINE__ constexpr bool LL_INCLUDE_KATS					= __LL_INCLUDE_KATS;
__LL_VAR_INLINE__ constexpr bool LL_USE_WIDE_CHAR					= __LL_USE_WIDE_CHAR;

#pragma endregion
#pragma region C++Version

#if defined(LL_REAL_CXX17)
	#undef LL_REAL_CXX17
#endif // LL_REAL_CXX17

#if defined(LL_REAL_CXX20)
	#undef LL_REAL_CXX20
#endif // LL_REAL_CXX20

#if defined(LL_REAL_CXX23)
	#undef LL_REAL_CXX23
#endif // LL_REAL_CXX23

__LL_VAR_INLINE__ constexpr bool LL_REAL_CXX17 = __LL_REAL_CXX17;
__LL_VAR_INLINE__ constexpr bool LL_REAL_CXX20 = __LL_REAL_CXX20;
__LL_VAR_INLINE__ constexpr bool LL_REAL_CXX23 = __LL_REAL_CXX23;

#pragma endregion
#pragma region EndianCheck

#if defined(LL_LITTLE_ENDIAN)
	#undef LL_LITTLE_ENDIAN
#endif // LL_LITTLE_ENDIAN

constexpr bool isLittleEndian() {
	#if __LL_REAL_CXX26 == 1
		int v = 1;
		return *reinterpret_cast<char*>(&v) == 0x1;
	#else
		return __LL_LITTLE_ENDIAN;
	#endif // __LL_REAL_CXX26
}

__LL_VAR_INLINE__ constexpr bool LL_LITTLE_ENDIAN = isLittleEndian();

#pragma endregion
#pragma region OSCheck

#if defined(LL_OS_SYSTEM)
	#undef LL_OS_SYSTEM
#endif // LL_OS_SYSTEM

enum class OSEnum { Windows, Posix, Unix, STM32, ESP32, MinGW, Unknown };

#if defined(__LL_WINDOWS_SYSTEM)
	__LL_VAR_INLINE__ constexpr ::llcpp::OSEnum LL_OS_SYSTEM = ::llcpp::OSEnum::Windows;
#elif defined(__LL_MINGW)
	__LL_VAR_INLINE__ constexpr ::llcpp::OSEnum LL_OS_SYSTEM = ::llcpp::OSEnum::MinGW;
#elif defined(__LL_POSIX_SYSTEM)
	__LL_VAR_INLINE__ constexpr ::llcpp::OSEnum LL_OS_SYSTEM = ::llcpp::OSEnum::Posix;
#elif defined(__LL_UNIX_SYSTEM)
	__LL_VAR_INLINE__ constexpr ::llcpp::OSEnum LL_OS_SYSTEM = ::llcpp::OSEnum::Unix;
#elif defined(__LL_STM32_SYSTEM)
	__LL_VAR_INLINE__ constexpr ::llcpp::OSEnum LL_OS_SYSTEM = ::llcpp::OSEnum::STM32;
#else
	__LL_VAR_INLINE__ constexpr ::llcpp::OSEnum LL_OS_SYSTEM = ::llcpp::OSEnum::Unknown;
#endif // __LL_WINDOWS_SYSTEM || __LL_POSIX_SYSTEM || __LL_UNIX_SYSTEM

#pragma endregion
#pragma region SystemBased

#if defined(LL_BITS_SYSTEM)
	#undef LL_BITS_SYSTEM
#endif // LL_BITS_SYSTEM

#if defined(LL_BITS_SYSTEM_64)
	#undef LL_BITS_SYSTEM_64
#endif // LL_BITS_SYSTEM_64

#if defined(LL_BITS_SYSTEM_32)
	#undef LL_BITS_SYSTEM_32
#endif // LL_BITS_SYSTEM_32

#if defined(LL_BITS_SYSTEM_16)
	#undef LL_BITS_SYSTEM_16
#endif // LL_BITS_SYSTEM_16

#if defined(LL_BITS_SYSTEM_8)
	#undef LL_BITS_SYSTEM_8
#endif // LL_BITS_SYSTEM_8

__LL_VAR_INLINE__ constexpr unsigned char LL_BITS_SYSTEM	= __LL_WORD;
__LL_VAR_INLINE__ constexpr bool LL_BITS_SYSTEM_64			= LL_BITS_SYSTEM == 64u;
__LL_VAR_INLINE__ constexpr bool LL_BITS_SYSTEM_32			= LL_BITS_SYSTEM == 32u;
__LL_VAR_INLINE__ constexpr bool LL_BITS_SYSTEM_16			= LL_BITS_SYSTEM == 16u;
__LL_VAR_INLINE__ constexpr bool LL_BITS_SYSTEM_8			= LL_BITS_SYSTEM == 8u;
// Assert to check if system is really well defined
static_assert(sizeof(void*) * 8 == LL_BITS_SYSTEM, "Word bit missmatch!");

#pragma endregion
#pragma region DLLDeinitions

#if defined(LL_DLL)
	#undef LL_DLL
#endif // LL_DLL

__LL_VAR_INLINE__ constexpr bool LL_DLL = __LL_DLL_BUILD;

#pragma endregion
#pragma region Logs

#if defined(LL_LOG)
	#undef LL_LOG
#endif // LL_LOG

#if defined(LL_LOG_ERROR)
	#undef LL_LOG_ERROR
#endif // LL_LOG_ERROR

#if defined(LL_LOG_WARNING)
	#undef LL_LOG_WARNING
#endif // LL_LOG_WARNING

#if defined(LL_LOG_INFO)
	#undef LL_LOG_INFO
#endif // LL_LOG_INFO

#if defined(LL_LOG_COMMNET)
	#undef LL_LOG_COMMNET
#endif // LL_LOG_COMMNET

__LL_VAR_INLINE__ constexpr unsigned char LL_LOG					= __LL_LOG__;
__LL_VAR_INLINE__ constexpr unsigned char LL_LOG_ERROR				= __LL_LOG_ERROR__;
__LL_VAR_INLINE__ constexpr unsigned char LL_LOG_WARNING			= __LL_LOG_WARNING__;
__LL_VAR_INLINE__ constexpr unsigned char LL_LOG_INFO				= __LL_LOG_INFO__;
__LL_VAR_INLINE__ constexpr unsigned char LL_LOG_COMMNET			= __LL_LOG_COMMNET__;

#pragma endregion
#pragma region Behabiour

#if defined(LL_DEFAULT_CONSTRUCTOR_LOG)
	#undef LL_DEFAULT_CONSTRUCTOR_LOG
#endif // LL_DEFAULT_CONSTRUCTOR_LOG

#if defined(LL_DESTRUCTOR_LOG)
	#undef LL_DESTRUCTOR_LOG
#endif // LL_DESTRUCTOR_LOG

#if defined(LL_COPY_CONSTRUCTOR_LOG)
	#undef LL_COPY_CONSTRUCTOR_LOG
#endif // LL_COPY_CONSTRUCTOR_LOG

#if defined(LL_COPY_ASSIGMENT_LOG)
	#undef LL_COPY_ASSIGMENT_LOG
#endif // LL_COPY_ASSIGMENT_LOG

#if defined(LL_MOVE_CONSTRUCTOR_LOG)
	#undef LL_MOVE_CONSTRUCTOR_LOG
#endif // LL_MOVE_CONSTRUCTOR_LOG

#if defined(LL_MOVE_CONSTRUCTOR_LOG)
	#undef LL_MOVE_CONSTRUCTOR_LOG
#endif // LL_MOVE_CONSTRUCTOR_LOG

#if defined(LL_RANDOM_SECURE)
	#undef LL_RANDOM_SECURE
#endif // LL_RANDOM_SECURE

#if defined(LL_CLEAR_SECURE)
	#undef LL_CLEAR_SECURE
#endif // LL_CLEAR_SECURE

#if defined(LL_CLEAR_POINTERS_ON_DESTRUCTION)
	#undef LL_CLEAR_POINTERS_ON_DESTRUCTION
#endif // LL_CLEAR_POINTERS_ON_DESTRUCTION

#if defined(LL_REFERENCE_OPERATOR_LOG)
	#undef LL_REFERENCE_OPERATOR_LOG
#endif // LL_REFERENCE_OPERATOR_LOG

#if defined(LL_RANDOM_SECURE_LOG)
	#undef LL_RANDOM_SECURE_LOG
#endif // LL_RANDOM_SECURE_LOG

#if defined(LL_CLEAR_SECURE_LOG)
	#undef LL_CLEAR_SECURE_LOG
#endif // LL_CLEAR_SECURE_LOG



#if defined(LLANYLIB_INTERNAL_GET_LOG)
	#undef LLANYLIB_INTERNAL_GET_LOG
#endif // LLANYLIB_INTERNAL_GET_LOG

// Clears all data in object to null/random values
__LL_VAR_INLINE__ constexpr bool LL_DEFAULT_CONSTRUCTOR_LOG			= __LL_DEFAULT_CONSTRUCTOR_LOG;

// Clears all data in object to null/random values
__LL_VAR_INLINE__ constexpr bool LL_DESTRUCTOR_LOG					= __LL_DESTRUCTOR_LOG;

// Clears all data in object to null/random values
__LL_VAR_INLINE__ constexpr bool LL_RANDOM_SECURE					= __LL_RANDOM_SECURE;

// Clears all data in object to null/random values
__LL_VAR_INLINE__ constexpr bool LL_CLEAR_SECURE					= __LL_CLEAR_SECURE;

// Sets pointer to nullptr
__LL_VAR_INLINE__ constexpr bool LL_CLEAR_POINTERS_ON_DESTRUCTION	= __LL_CLEAR_POINTERS_ON_DESTRUCTION;

// Activates logs for references class functions
__LL_VAR_INLINE__ constexpr bool LL_REFERENCE_OPERATOR_LOG			= __LL_REFERENCE_OPERATOR_LOG;

// Enables logs in copy constructor
__LL_VAR_INLINE__ constexpr bool LL_COPY_CONSTRUCTOR_LOG			= __LL_COPY_CONSTRUCTOR_LOG;

// Enables logs in copy assigment
__LL_VAR_INLINE__ constexpr bool LL_COPY_ASSIGMENT_LOG				= __LL_COPY_ASSIGMENT_LOG;

// Enables logs in copy constructor
__LL_VAR_INLINE__ constexpr bool LL_MOVE_CONSTRUCTOR_LOG			= __LL_MOVE_CONSTRUCTOR_LOG;

// Enables logs in copy assigment
__LL_VAR_INLINE__ constexpr bool LL_MOVE_ASSIGMENT_LOG				= __LL_MOVE_ASSIGMENT_LOG;

// 
__LL_VAR_INLINE__ constexpr bool LL_RANDOM_SECURE_LOG				= __LL_RANDOM_SECURE_LOG;

// 
__LL_VAR_INLINE__ constexpr bool LL_CLEAR_SECURE_LOG				= __LL_CLEAR_SECURE_LOG;




// Activates logs for all internal getters in classes
__LL_VAR_INLINE__ constexpr bool LLANYLIB_INTERNAL_GET_LOG			= __LLANYLIB_INTERNAL_GET_LOG;

// Activates logs for all getters in classes
__LL_VAR_INLINE__ constexpr bool LLANYLIB_GET_LOG					= __LLANYLIB_GET_LOG;

// Activates logs for all setters in classes
__LL_VAR_INLINE__ constexpr bool LLANYLIB_SET_LOG					= __LLANYLIB_SET_LOG;



#pragma endregion
// Deprecated or [TOCHECK]
#pragma region Ungrouped
/*
#if defined(LL_EXCEPTIONS)
	#undef LL_EXCEPTIONS
#endif // LL_EXCEPTIONS

#if defined(LL_BOOL_RANGE_CHECK)
	#undef LL_BOOL_RANGE_CHECK
#endif // LL_BOOL_RANGE_CHECK

#if defined(LL_STATIC_KATS)
	#undef LL_STATIC_KATS
#endif // LL_STATIC_KATS

#if defined(LL_INCLUDE_KATS)
	#undef LL_INCLUDE_KATS
#endif // LL_INCLUDE_KATS

#if defined(LL_USE_WIDE_CHAR)
	#undef LL_USE_WIDE_CHAR
#endif // LL_USE_WIDE_CHAR

#if defined(LL_IGNORE_WARNING_STATIC_ASSERTS)
	#undef LL_IGNORE_WARNING_STATIC_ASSERTS
#endif // LL_IGNORE_WARNING_STATIC_ASSERTS

__LL_VAR_INLINE__ constexpr bool LL_EXCEPTIONS						= __LL_EXCEPTIONS;
__LL_VAR_INLINE__ constexpr bool LL_BOOL_RANGE_CHECK				= __LL_BOOL_RANGE_CHECK;
__LL_VAR_INLINE__ constexpr bool LL_IGNORE_WARNING_STATIC_ASSERTS	= __LL_IGNORE_WARNING_STATIC_ASSERTS__;
*/

#pragma endregion

} // namespace llcpp

#endif // LLANYLIB_DEFINITIONSEXPRESIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
