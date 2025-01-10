//////////////////////////////////////////////
//	expresions.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DEFINITIONSEXPRESIONS_HPP_) // Guard && version protector
	#if LLANYLIB_DEFINITIONSEXPRESIONS_MAYOR_ != 11 || LLANYLIB_DEFINITIONSEXPRESIONS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "expresions.hpp version error!"
		#else
			#error "expresions.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_DEFINITIONSEXPRESIONS_MAYOR_ || LLANYLIB_DEFINITIONSEXPRESIONS_MINOR_

#else !defined(LLANYLIB_DEFINITIONSEXPRESIONS_HPP_)
	#define LLANYLIB_DEFINITIONSEXPRESIONS_HPP_
	#define LLANYLIB_DEFINITIONSEXPRESIONS_MAYOR_ 11
	#define LLANYLIB_DEFINITIONSEXPRESIONS_MINOR_ 0

#include "definitions.hpp"

namespace llcpp {

/////////////////////////////////////////// C++ Version ///////////////////////////////////////////

#pragma region MacrosRemove

#if defined(REAL_CXX17)
	#undef REAL_CXX17
#endif // REAL_CXX17

#if defined(REAL_CXX23)
	#undef REAL_CXX23
#endif // REAL_CXX23

#pragma endregion

__LL_VAR_INLINE__ constexpr bool REAL_CXX17 = __LL_REAL_CXX17;
__LL_VAR_INLINE__ constexpr bool REAL_CXX23 = __LL_REAL_CXX23;

//////////////////////////////////////////// OS check ////////////////////////////////////////////

#pragma region MacrosRemove

#if defined(OS_SYSTEM)
	#undef OS_SYSTEM
#endif // OS_SYSTEM

#pragma endregion

enum class OSEnum { Windows, Posix, Unix, Unknown };

#if defined(__LL_WINDOWS_SYSTEM)
	__LL_VAR_INLINE__ constexpr llcpp::OSEnum OS_SYSTEM = llcpp::OSEnum::Windows;
#elif defined(__LL_POSIX_SYSTEM)
	__LL_VAR_INLINE__ constexpr OSEnum OS_SYSTEM = llcpp::OSEnum::Posix;
#elif defined(__LL_UNIX_SYSTEM)
	__LL_VAR_INLINE__ constexpr OSEnum OS_SYSTEM = llcpp::OSEnum::Unix;
#else
	__LL_VAR_INLINE__ constexpr OSEnum OS_SYSTEM = llcpp::OSEnum::Unknown;
#endif // __LL_WINDOWS_SYSTEM || __LL_POSIX_SYSTEM || __LL_UNIX_SYSTEM

////////////////////////////////////////// System Based //////////////////////////////////////////

#pragma region MacrosRemove

#if defined(BITS_SYSTEM)
	#undef BITS_SYSTEM
#endif // BITS_SYSTEM

#if defined(BITS_SYSTEM_64)
	#undef BITS_SYSTEM_64
#endif // BITS_SYSTEM_64

#if defined(BITS_SYSTEM_32)
	#undef BITS_SYSTEM_32
#endif // BITS_SYSTEM_32

#if defined(BITS_SYSTEM_16)
	#undef BITS_SYSTEM_16
#endif // BITS_SYSTEM_16

#if defined(BITS_SYSTEM_8)
	#undef BITS_SYSTEM_8
#endif // BITS_SYSTEM_8

#pragma endregion

__LL_VAR_INLINE__ constexpr unsigned char BITS_SYSTEM	= __LL_WORD;
__LL_VAR_INLINE__ constexpr bool BITS_SYSTEM_64			= BITS_SYSTEM == 64u;
__LL_VAR_INLINE__ constexpr bool BITS_SYSTEM_32			= BITS_SYSTEM == 32u;
__LL_VAR_INLINE__ constexpr bool BITS_SYSTEM_16			= BITS_SYSTEM == 16u;
__LL_VAR_INLINE__ constexpr bool BITS_SYSTEM_8			= BITS_SYSTEM == 8u;

///////////////////////////////////////// DLL deinitions /////////////////////////////////////////

#pragma region MacrosRemove

#if defined(DLL)
	#undef DLL
#endif // DLL

#pragma endregion

__LL_VAR_INLINE__ constexpr bool DLL = __LL_DLL_BUILD;

///////////////////////////////////////////// Assert /////////////////////////////////////////////

#pragma region MacrosRemove

#if defined(DEBUG)
	#undef DEBUG
#endif // DEBUG

#if defined(NULLPTR)
	#undef NULLPTR
#endif // NULLPTR

#pragma endregion

__LL_VAR_INLINE__ constexpr bool DEBUG = __LL_DEBUG;

//template<class T>
//__LL_VAR_INLINE__ constexpr T* NULLPTR = LL_NULLPTR;

} // namespace llcpp

#endif // LLANYLIB_DEFINITIONSEXPRESIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
