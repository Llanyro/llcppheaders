//////////////////////////////////////////////
//	definitions.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DEFINITIONS_HPP_) // Guard && version protector
	#if LLANYLIB_DEFINITIONS_MAYOR_ != 12 || LLANYLIB_DEFINITIONS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "definitions.hpp version error!"
		#else
			#error "definitions.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_DEFINITIONS_MAYOR_ || LLANYLIB_DEFINITIONS_MINOR_

#elif !defined(LLANYLIB_DEFINITIONS_HPP_)
	#define LLANYLIB_DEFINITIONS_HPP_
	#define LLANYLIB_DEFINITIONS_MAYOR_ 12
	#define LLANYLIB_DEFINITIONS_MINOR_ 0

#include "os.hpp"

// Sets more env definitions by OS
#if defined(__LL_WINDOWS_SYSTEM)
	#define __LL_FALLTHROUGH__ [[fallthrough]]
	#define __LL_NODISCARD__ _NODISCARD
	#define __LL_NORETURN__ [[noreturn]]
	#define __LL_UNSECURE_FUNCTIONS__
	#define __LL_SPECTRE_FUNCTIONS__
	#define __LL_INLINE__ __forceinline
	#define __LL_VAR_INLINE__ inline
	#define __LL_FUNCNAME__ __FUNCSIG__
#elif defined(__LL_POSIX_SYSTEM) || defined(__LL_UNIX_SYSTEM)
	#define __LL_FALLTHROUGH__ [[fallthrough]]
	#define __LL_NODISCARD__ [[nodiscard]]
	#define __LL_NORETURN__ [[noreturn]]
	#define __LL_INLINE__ inline
	#define __LL_VAR_INLINE__ inline
	#define __LL_FUNCNAME__ __PRETTY_FUNCTION__
#else
	#define __LL_FALLTHROUGH__ [[fallthrough]]
	#define __LL_NODISCARD__ [[nodiscard]]
	#define __LL_NORETURN__ [[noreturn]]
	#define __LL_INLINE__ inline
	#define __LL_VAR_INLINE__ inline
#endif // __LL_WINDOWS_SYSTEM || __LL_POSIX_SYSTEM || __LL_UNIX_SYSTEM

// Definitions
#define LL_NULLPTR nullptr
// Undef this to activate deprecated functionality in any header
#define __LL_DEPRECATED__

#if !defined(__LL_IGNORE_WARNING_STATIC_ASSERTS__)
	#define __LL_IGNORE_WARNING_STATIC_ASSERTS__ 0
#elif __LL_IGNORE_WARNING_STATIC_ASSERTS__ != 1 && __LL_IGNORE_WARNING_STATIC_ASSERTS__ != 0
	#undef __LL_IGNORE_WARNING_STATIC_ASSERTS__
	#define __LL_IGNORE_WARNING_STATIC_ASSERTS__ 1
#endif // __LL_IGNORE_WARNING_STATIC_ASSERTS__

#if !defined(__LL_EXCEPTIONS)
	#define __LL_EXCEPTIONS 0
#elif __LL_EXCEPTIONS != 1 && __LL_EXCEPTIONS != 0
	#undef __LL_EXCEPTIONS
	#define __LL_EXCEPTIONS 1
#endif // __LL_EXCEPTIONS

#if !defined(__LL_CLEAR_POINTERS_ON_DESTRUCTION)
	#define __LL_CLEAR_POINTERS_ON_DESTRUCTION 0
#elif __LL_CLEAR_POINTERS_ON_DESTRUCTION != 1 && __LL_CLEAR_POINTERS_ON_DESTRUCTION != 0
	#undef __LL_CLEAR_POINTERS_ON_DESTRUCTION
	#define __LL_CLEAR_POINTERS_ON_DESTRUCTION 1
#endif // __LL_CLEAR_POINTERS_ON_DESTRUCTION

#if !defined(__LL_CLEAR_SECURE)
	#define __LL_CLEAR_SECURE 0
#elif __LL_CLEAR_SECURE != 1 && __LL_CLEAR_SECURE != 0
	#undef __LL_CLEAR_SECURE
	#define __LL_CLEAR_SECURE 1
#endif // __LL_CLEAR_SECURE

#if !defined(__LL_USE_WIDE_CHAR)
	#define __LL_USE_WIDE_CHAR 0
#elif __LL_USE_WIDE_CHAR != 1 && __LL_USE_WIDE_CHAR != 0
	#undef __LL_USE_WIDE_CHAR
	#define __LL_USE_WIDE_CHAR 1
#endif // __LL_USE_WIDE_CHAR


#define __LL_DEBUG_ERROR__ 0
#define __LL_DEBUG_WARNING__ __LL_DEBUG_ERROR__ + 1
#define __LL_DEBUG_INFO__ __LL_DEBUG_WARNING__ + 1
#define __LL_DEBUG_COMMNET__ __LL_DEBUG_INFO__ + 1

#if !defined(__LL_DEBUG__)
	#define __LL_DEBUG__ __LL_DEBUG_ERROR__
#endif // __LL_DEBUG__

//#define LL_SHARED_LIB_FUNC extern "C" LL_SHARED_LIB

#define __LL_ASSERT_VAR_ZERO__(var, var_str) LL_ASSERT(var > 0, "[" var_str "] cannot be 0. " __FUNCSIG__)
#define __LL_ASSERT_VAR_NULL__(var, var_str) LL_ASSERT(var, "[" var_str "] cannot be nullptr." __FUNCSIG__)
#define __LL_ASSERT_LIST_EMPTY__(var, var_str) LL_ASSERT(!var.empty(), "[" var_str "] cannot be empty." __FUNCSIG__)
#define __LL_ASSERT_B_LOWER_THAN_A__(var_a, var_b, var_a_str, var_b_str) \
	LL_ASSERT(var_a < var_b, "[" var_a_str " < " var_b_str "] " var_a_str " cannot be lower or equal to " var_b_str "." __FUNCSIG__)

// Defines for logging

#pragma region Error

#if !defined(__debug_error_exceptions_full)
	#define __debug_error_exceptions_full(str) IGNORE()
#endif

#if !defined(__debug_error_exceptions_empty)
	#define __debug_error_exceptions_full(str) IGNORE()
#endif

#if !defined(__debug_error_not_nullptr_str)
	#define __debug_error_not_nullptr_str(var_str) IGNORE()
#endif

#if !defined(__debug_error_begin_smaller)
	#define __debug_error_begin_smaller(str, begin, end) IGNORE()
#endif

#if !defined(__debug_error_out_of_range)
	#define __debug_error_out_of_range(var, var_str, len) IGNORE()
#endif


#pragma endregion
#pragma region Warning

#if !defined(__debug_warning_nullptr)
	#define __debug_warning_nullptr(var_str) IGNORE()
#endif

#if !defined(__debug_warning_out_of_range)
	#define __debug_warning_out_of_range(var, var_str, len) IGNORE()
#endif

#pragma endregion

/*
#pragma region Error

// Nullptr
#if !defined(__debug_error_nullptr_str)
	#define __debug_error_nullptr_str(var, var_str) IGNORE()
#endif

// Ranges
#if !defined(__debug_error_out_of_range)
	#define __debug_error_out_of_range(var, len) IGNORE()
#endif


// Other
#if !defined(__debug_error_zero_value_str)
	#define __debug_error_zero_value_str(var_str) IGNORE()
#endif

#pragma endregion
#pragma region Warning

// Nullptr
#if !defined(__debug_warning_not_nullptr)
	#define __debug_warning_not_nullptr(var) IGNORE()
#endif

#if !defined(__debug_warning_not_nullptr_str)
	#define __debug_warning_not_nullptr_str(var, var_str) IGNORE()
#endif

// Ranges
#if !defined(__debug_warning_out_of_range)
	#define __debug_warning_out_of_range(var, len) IGNORE()
#endif

// Other
#if !defined(__debug_warning_zero_value_str)
	#define __debug_warning_zero_value_str(var_str) IGNORE()
#endif

#if !defined(__debug_warning_invalidation_in_reset_str)
	#define __debug_warning_invalidation_in_reset_str(var_str) IGNORE()
#endif

#pragma endregion

*/

#endif // LLANYLIB_DEFINITIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
