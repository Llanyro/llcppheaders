//////////////////////////////////////////////
//	definitions.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.3							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DEFINITIONS_HPP_) // Guard && version protector
	#if LLANYLIB_DEFINITIONS_MAYOR_ != 7 || LLANYLIB_DEFINITIONS_MINOR_ < 3
		#if defined(LL_REAL_CXX23)
			#warning "definitions.hpp version error!"
		#else
			#error "definitions.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_DEFINITIONS_MAYOR_ || LLANYLIB_DEFINITIONS_MINOR_

#else !defined(LLANYLIB_DEFINITIONS_HPP_)
#define LLANYLIB_DEFINITIONS_HPP_
#define LLANYLIB_DEFINITIONS_MAYOR_ 7
#define LLANYLIB_DEFINITIONS_MINOR_ 3

#include "os.hpp"

namespace llcpp { enum class OSEnum { Windows, Posix, Unix, Other }; } // namespace llcpp

// Sets more env definitions by OS
#if defined(WINDOWS_SYSTEM)
	#define __LL_FALLTHROUGH__ [[fallthrough]]
	#define __LL_NODISCARD__ _NODISCARD
	#define __LL_UNSECURE_FUNCTIONS__
	#define __LL_SPECTRE_FUNCTIONS__
	#define __LL_INLINE__ __forceinline
	#define __LL_VAR_INLINE__ inline
	__LL_VAR_INLINE__ constexpr llcpp::OSEnum OS_SYSTEM = llcpp::OSEnum::Windows;
#elif defined(POSIX_SYSTEM) || defined(UNIX_SYSTEM)
	#define __LL_FALLTHROUGH__ [[fallthrough]]
	#define __LL_NODISCARD__ NODISCARD
	#define __LL_INLINE__ inline
	#define __LL_VAR_INLINE__ inline
	#if defined(POSIX_SYSTEM)
		__LL_VAR_INLINE__ constexpr OSEnum OS_SYSTEM = llcpp::OSEnum::Posix;
	#else
		__LL_VAR_INLINE__ constexpr OSEnum OS_SYSTEM = llcpp::OSEnum::Unix;
	#endif // defined(POSIX_SYSTEM)
#else
	#define __LL_FALLTHROUGH__ [[fallthrough]]
	#define __LL_NODISCARD__ [[nodiscard]]
	#define __LL_INLINE__ inline
	#define __LL_VAR_INLINE__ inline
	__LL_VAR_INLINE__ constexpr OSEnum OS_SYSTEM = llcpp::OSEnum::Other;
#endif

// Definitions
#define __LL_EXCEPT__ noexcept(true)
#define LL_NULLPTR nullptr
//#define LL_SHARED_LIB_FUNC extern "C" LL_SHARED_LIB

#define __LL_ASSERT_VAR_ZERO__(var, var_str) LL_ASSERT(var > 0, "[" var_str "] cannot be 0. " __FUNCSIG__)
#define __LL_ASSERT_VAR_NULL__(var, var_str) LL_ASSERT(var, "[" var_str "] cannot be nullptr." __FUNCSIG__)
#define __LL_ASSERT_LIST_EMPTY__(var, var_str) LL_ASSERT(!var.empty(), "[" var_str "] cannot be empty." __FUNCSIG__)
#define __LL_ASSERT_B_LOWER_THAN_A__(var_a, var_b, var_a_str, var_b_str) \
	LL_ASSERT(var_a < var_b, "[" var_a_str " < " var_b_str "] " var_a_str " cannot be lower or equal to " var_b_str "." __FUNCSIG__)

#endif // LLANYLIB_DEFINITIONS_HPP_
