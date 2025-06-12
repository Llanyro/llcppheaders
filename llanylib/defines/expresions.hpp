//////////////////////////////////////////////
//	expresions.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DEFINITIONSEXPRESIONS_HPP_) // Guard && version protector
	#if LLANYLIB_DEFINITIONSEXPRESIONS_MAYOR_ != 12 || LLANYLIB_DEFINITIONSEXPRESIONS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "expresions.hpp version error!"
		#else
			#error "expresions.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_DEFINITIONSEXPRESIONS_MAYOR_ || LLANYLIB_DEFINITIONSEXPRESIONS_MINOR_

#elif !defined(LLANYLIB_DEFINITIONSEXPRESIONS_HPP_)
	#define LLANYLIB_DEFINITIONSEXPRESIONS_HPP_
	#define LLANYLIB_DEFINITIONSEXPRESIONS_MAYOR_ 12
	#define LLANYLIB_DEFINITIONSEXPRESIONS_MINOR_ 0

#include <llanylib/defines/definitions.hpp>

namespace llcpp {

/////////////////////////////////////////// C++ Version ///////////////////////////////////////////

#pragma region MacrosRemove

#if defined(LL_REAL_CXX17)
	#undef LL_REAL_CXX17
#endif // LL_REAL_CXX17

#if defined(LL_REAL_CXX20)
	#undef LL_REAL_CXX20
#endif // LL_REAL_CXX20

#if defined(LL_REAL_CXX23)
	#undef LL_REAL_CXX23
#endif // LL_REAL_CXX23

#pragma endregion

__LL_VAR_INLINE__ constexpr bool LL_REAL_CXX17 = __LL_REAL_CXX17;
__LL_VAR_INLINE__ constexpr bool LL_REAL_CXX20 = __LL_REAL_CXX20;
__LL_VAR_INLINE__ constexpr bool LL_REAL_CXX23 = __LL_REAL_CXX23;

//////////////////////////////////////////// Endian check ////////////////////////////////////////////

#if defined(LL_BIGENDIAN)
	#undef LL_BIGENDIAN
#endif // LL_BIGENDIAN

constexpr bool isLittleEndian() {
	#if __LL_REAL_CXX26 == 1
		int v = 1;
		return *reinterpret_cast<char*>(&v) == 0x1;
	#else
		return __LL_BIGENDIAN;
	#endif // __LL_REAL_CXX26
}

__LL_VAR_INLINE__ constexpr bool LL_BIGENDIAN	= isLittleEndian();

//////////////////////////////////////////// OS check ////////////////////////////////////////////

#pragma region MacrosRemove

#if defined(LL_OS_SYSTEM)
	#undef LL_OS_SYSTEM
#endif // LL_OS_SYSTEM

#pragma endregion

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

////////////////////////////////////////// System Based //////////////////////////////////////////

#pragma region MacrosRemove

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

#pragma endregion

__LL_VAR_INLINE__ constexpr unsigned char LL_BITS_SYSTEM	= __LL_WORD;
__LL_VAR_INLINE__ constexpr bool LL_BITS_SYSTEM_64			= LL_BITS_SYSTEM == 64u;
__LL_VAR_INLINE__ constexpr bool LL_BITS_SYSTEM_32			= LL_BITS_SYSTEM == 32u;
__LL_VAR_INLINE__ constexpr bool LL_BITS_SYSTEM_16			= LL_BITS_SYSTEM == 16u;
__LL_VAR_INLINE__ constexpr bool LL_BITS_SYSTEM_8			= LL_BITS_SYSTEM == 8u;

///////////////////////////////////////// DLL deinitions /////////////////////////////////////////

#pragma region MacrosRemove

#if defined(LL_DLL)
	#undef LL_DLL
#endif // LL_DLL

#pragma endregion

__LL_VAR_INLINE__ constexpr bool LL_DLL = __LL_DLL_BUILD;

///////////////////////////////////////////// Assert /////////////////////////////////////////////

#pragma region MacrosRemove

#if defined(LL_DEBUG)
	#undef LL_DEBUG
#endif // LL_DEBUG

#if defined(LL_DEBUG_WARNING)
	#undef LL_DEBUG_WARNING
#endif // LL_DEBUG_WARNING

#if defined(LL_DEBUG_INFO)
	#undef LL_DEBUG_INFO
#endif // LL_DEBUG_INFO

#if defined(LL_DEBUG_COMMNET)
	#undef LL_DEBUG_COMMNET
#endif // LL_DEBUG_COMMNET

#if defined(LL_EXCEPTIONS)
	#undef LL_EXCEPTIONS
#endif // LL_EXCEPTIONS

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

#if defined(LL_CLEAR_POINTERS_ON_DESTRUCTION)
	#undef LL_CLEAR_POINTERS_ON_DESTRUCTION
#endif // LL_CLEAR_POINTERS_ON_DESTRUCTION

#pragma endregion

__LL_VAR_INLINE__ constexpr unsigned char LL_DEBUG					= __LL_DEBUG__;
__LL_VAR_INLINE__ constexpr unsigned char LL_DEBUG_WARNING			= __LL_DEBUG_WARNING__;
__LL_VAR_INLINE__ constexpr unsigned char LL_DEBUG_INFO				= __LL_DEBUG_INFO__;
__LL_VAR_INLINE__ constexpr unsigned char LL_DEBUG_COMMNET			= __LL_DEBUG_COMMNET__;
__LL_VAR_INLINE__ constexpr bool LL_EXCEPTIONS						= __LL_EXCEPTIONS;
__LL_VAR_INLINE__ constexpr bool LL_STATIC_KATS						= __LL_STATIC_KATS;
__LL_VAR_INLINE__ constexpr bool LL_INCLUDE_KATS					= __LL_INCLUDE_KATS;
__LL_VAR_INLINE__ constexpr bool LL_USE_WIDE_CHAR					= __LL_USE_WIDE_CHAR;
__LL_VAR_INLINE__ constexpr bool LL_IGNORE_WARNING_STATIC_ASSERTS	= __LL_IGNORE_WARNING_STATIC_ASSERTS__;

///////////////////////////////////////////// Behabiour /////////////////////////////////////////////

// Sets pointer to nullptr
__LL_VAR_INLINE__ constexpr bool LL_CLEAR_POINTERS_ON_DESTRUCTION	= __LL_CLEAR_POINTERS_ON_DESTRUCTION;
// Clears all data in object to null/random values
__LL_VAR_INLINE__ constexpr bool LL_CLEAR_SECURE					= __LL_CLEAR_SECURE;

#undef __LL_CLEAR_POINTERS_ON_DESTRUCTION

} // namespace llcpp

#endif // LLANYLIB_DEFINITIONSEXPRESIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
