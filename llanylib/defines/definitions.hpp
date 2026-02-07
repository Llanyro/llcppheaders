//////////////////////////////////////////////
//	definitions.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 15.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DEFINITIONS_HPP_) // Guard && version protector
	#if LLANYLIB_DEFINITIONS_MAYOR_ != 15 || LLANYLIB_DEFINITIONS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "definitions.hpp version error!"
		#else
			#error "definitions.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_DEFINITIONS_MAYOR_ || LLANYLIB_DEFINITIONS_MINOR_

#elif !defined(LLANYLIB_DEFINITIONS_HPP_)
	#define LLANYLIB_DEFINITIONS_HPP_
	#define LLANYLIB_DEFINITIONS_MAYOR_ 15
	#define LLANYLIB_DEFINITIONS_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include "os.hpp"
#else
	#include <llanylib/defines/os.hpp>
#endif // LL_LIB_PATHS

#pragma region CommonEnvMacros

// If any compiler macro is not defined here, should be defined below for each compiler

#define __LL_FALLTHROUGH__	[[fallthrough]]
#define __LL_NODISCARD__	[[nodiscard]]
#define __LL_NORETURN__		[[noreturn]]
#define __LL_LIKELY__		[[likely]]
#define __LL_UNLIKELY__		[[unlikely]]
#define __LL_VAR_INLINE__	inline
#define LL_NULLPTR nullptr
//#define __LL_DEPRECATED__ // This is deprecated (12.0 and lower), each file has its own macro (15.0 and higher) 
#define __LL_MACRO_WRAPPER__(somtething) do { somtething } while(0)
// Macro that must be included in all functions at the beginning
// Commonly used to check is function is called or exited
#if !defined(__LL_FUNCTION_INIT__)
	#define __LL_FUNCTION_INIT__ __LL_MACRO_WRAPPER__(LL_IGNORE();)
#endif // __LL_FUNCTION_INIT__
#define __LL_FUNCTION_INIT_ENABLER__(condition) if constexpr (condition) __LL_FUNCTION_INIT__
#define __LL_FAILURE_EXECUTION__ -1
#define __LL_SUCCESS_EXECUTION__ 0

#define EXTERN_C_FUNC extern "C"
//#define LL_SHARED_LIB_FUNC extern "C" LL_SHARED_LIB

#define __LL_L L
#define __LL_u u
#define __LL_U U

#if __LL_REAL_CXX17 == 1
	#define __LLC17_CONSTEXPR constexpr
#else
	#define __LLC17_CONSTEXPR
#endif // __LL_REAL_CXX17

#if __LL_REAL_CXX20 == 1
	#define __LLC20_CONSTEXPR constexpr
#else
	#define __LLC20_CONSTEXPR
#endif // __LL_REAL_CXX17

#if defined(__LL_WINDOWS_SYSTEM)
	#define __LL_UNSECURE_FUNCTIONS__
	#define __LL_SPECTRE_FUNCTIONS__
	#define __LL_NO_UNIQUE_ADDRESS__ [[msvc::no_unique_address]]
	#define __LL_INLINE__ __forceinline
	#define __LL_FUNCNAME__ __FUNCSIG__
	#define __MSVC_CDECL __cdecl
	#define __STD_SIZE_T unsigned long long
#elif defined(__LL_MINGW)
	#define __LL_UNSECURE_FUNCTIONS__
	#define __LL_SPECTRE_FUNCTIONS__
	#define __LL_NO_UNIQUE_ADDRESS__ [[msvc::no_unique_address]]
	#define __LL_INLINE__ inline
	#define __LL_FUNCNAME__ __PRETTY_FUNCTION__
	#define __MSVC_CDECL
	#define __STD_SIZE_T unsigned long long
#elif defined(__LL_POSIX_SYSTEM) || defined(__LL_UNIX_SYSTEM)
	#define __LL_NO_UNIQUE_ADDRESS__ [[no_unique_address]]
	#define __LL_INLINE__ inline
	#define __LL_FUNCNAME__ __PRETTY_FUNCTION__
	#define __MSVC_CDECL
	#define __STD_SIZE_T long unsigned int
#else
	#define __LL_NO_UNIQUE_ADDRESS__ [[no_unique_address]]
	#define __LL_INLINE__ inline
	#define __MSVC_CDECL
	#define __STD_SIZE_T unsigned long
#endif // __LL_WINDOWS_SYSTEM || __LL_MINGW || __LL_POSIX_SYSTEM || __LL_UNIX_SYSTEM

#pragma endregion
#pragma region DefaultLibDefinitions
// Char formatting macro helper
// 0: No prefix Char
// 1: Wide char prefix
// 2: char16_t prefix
// 3: char32_t prefix
#if defined(UNICODE)
	#define __LL_USE_WIDE_CHAR UNICODE
	#if UNICODE == 1
		#define __LL_STRING_PREFIX __LL_L
	#else
		#define __LL_STRING_PREFIX
	#endif // UNICODE
#elif !defined(__LL_USE_WIDE_CHAR)
	#define __LL_USE_WIDE_CHAR 0
	#define __LL_STRING_PREFIX
#elif __LL_USE_WIDE_CHAR < 0
	#undef __LL_USE_WIDE_CHAR
	#define __LL_USE_WIDE_CHAR 0
	#define __LL_STRING_PREFIX
#elif __LL_USE_WIDE_CHAR == 1
	#define __LL_STRING_PREFIX __LL_L
#elif __LL_USE_WIDE_CHAR == 2
	#define __LL_STRING_PREFIX __LL_u
#elif __LL_USE_WIDE_CHAR == 3
	#define __LL_STRING_PREFIX __LL_U
#elif __LL_USE_WIDE_CHAR > 3
	#undef __LL_USE_WIDE_CHAR
	#define __LL_USE_WIDE_CHAR 3
	#define __LL_STRING_PREFIX __LL_U
#endif // __LL_USE_WIDE_CHAR

// Uses LL_IGNORE function with C++20 standard using "auto..." or template<Args...>
// Values: [0-1]
//	1: auto
//	0: template
#if !defined(__LL_USE_IGNORE_AUTO__)
	#define __LL_USE_IGNORE_AUTO__ __LL_REAL_CXX20
#elif __LL_USE_IGNORE_AUTO__ < 0
	#undef __LL_USE_IGNORE_AUTO__
	#define __LL_USE_IGNORE_AUTO__ 0
#elif __LL_USE_IGNORE_AUTO__ > 1
	#undef __LL_USE_IGNORE_AUTO__
	#define __LL_USE_IGNORE_AUTO__ 1
#endif // __LL_USE_IGNORE_AUTO__

#pragma endregion
#pragma region Kats
// 
#define __LL_IS_NOT_WORKING_STR " is not working properly!"

#pragma region StaticKats
// Enables or disables static kats (compile-time kats)
// Values: [0-1]
//	0: Disable
//	1: Enable
#if !defined(__LL_STATIC_KATS)
	#define __LL_STATIC_KATS 1
#elif __LL_STATIC_KATS < 0
	#undef __LL_STATIC_KATS
	#define __LL_STATIC_KATS 0
#elif __LL_STATIC_KATS > 1
	#undef __LL_STATIC_KATS
	#define __LL_STATIC_KATS 1
#endif // __LL_STATIC_KATS

// Enables or disables all kats types (compile-time kats)
// Values: [0-1]
//	0: Disable
//	1: Enable
#if !defined(__LL_INCLUDE_KATS)
	#define __LL_INCLUDE_KATS 1
#elif __LL_INCLUDE_KATS < 0
	#undef __LL_INCLUDE_KATS
	#define __LL_INCLUDE_KATS 0
#elif __LL_INCLUDE_KATS > 1
	#undef __LL_INCLUDE_KATS
	#define __LL_INCLUDE_KATS 1
#endif // __LL_INCLUDE_KATS

#if __LL_INCLUDE_KATS == 1
#define __LL_KAT_GENERIC(VALUE, STR)								\
	do {															\
		if (!(VALUE)) {												\
			if constexpr (::llcpp::LL_STATIC_KATS)					\
				static_assert(VALUE, STR);							\
			return __LL_STRING_PREFIX STR;							\
		}															\
	} while(0)

#define __LL_KAT_FUNCTION(NAME, CONDITION, ERROR_STRING)			\
	__LL_NODISCARD__ constexpr ::llcpp::string NAME() noexcept {	\
		__LL_KAT_GENERIC(CONDITION, ERROR_STRING);					\
		return nullptr;												\
	}

#define __LL_KAT_GENERIC_CONSTEXPR(VALUE, STR)						\
	do {															\
		if constexpr (!(VALUE)) {									\
			if constexpr (::llcpp::LL_STATIC_KATS)					\
				static_assert(VALUE, STR);							\
			return __LL_STRING_PREFIX STR;							\
		}															\
	} while(0)

#define __LL_KAT_FUNCTION_CONSTEXPR(NAME, CONDITION, ERROR_STRING)	\
	__LL_NODISCARD__ constexpr ::llcpp::string NAME() noexcept {	\
		__LL_KAT_GENERIC_CONSTEXPR(CONDITION, ERROR_STRING);		\
		return nullptr;												\
	}


#endif // __LL_INCLUDE_KATS


#pragma endregion

#pragma endregion
#pragma region ConceptsStrictness
#if !defined(__LL_STRICT_CONVERTIBLE)
	#define __LL_STRICT_CONVERTIBLE 1
#elif __LL_STRICT_CONVERTIBLE < 0
	#undef __LL_STRICT_CONVERTIBLE
	#define __LL_STRICT_CONVERTIBLE 0
#elif __LL_STRICT_CONVERTIBLE > 1
	#undef __LL_STRICT_CONVERTIBLE
	#define __LL_STRICT_CONVERTIBLE 1
#endif // __LL_STRICT_CONVERTIBLE

#if !defined(__LL_STRICT_CONVERTIBLE_OPERATOR)
	#define __LL_STRICT_CONVERTIBLE_OPERATOR 1
#elif __LL_STRICT_CONVERTIBLE_OPERATOR < 0
	#undef __LL_STRICT_CONVERTIBLE_OPERATOR
	#define __LL_STRICT_CONVERTIBLE_OPERATOR 0
#elif __LL_STRICT_CONVERTIBLE_OPERATOR > 1
	#undef __LL_STRICT_CONVERTIBLE_OPERATOR
	#define __LL_STRICT_CONVERTIBLE_OPERATOR 1
#endif // __LL_STRICT_CONVERTIBLE_OPERATOR

#if !defined(__LL_STRICT_VALID_FUNCTIONS)
	#define __LL_STRICT_VALID_FUNCTIONS 1
#elif __LL_STRICT_VALID_FUNCTIONS < 0
	#undef __LL_STRICT_VALID_FUNCTIONS
	#define __LL_STRICT_VALID_FUNCTIONS 0
#elif __LL_STRICT_VALID_FUNCTIONS > 1
	#undef __LL_STRICT_VALID_FUNCTIONS
	#define __LL_STRICT_VALID_FUNCTIONS 1
#endif // __LL_STRICT_VALID_FUNCTIONS

#if !defined(__LL_STRICT_GENERIC_FUNCTIONS)
	#define __LL_STRICT_GENERIC_FUNCTIONS 1
#elif __LL_STRICT_GENERIC_FUNCTIONS < 0
	#undef __LL_STRICT_GENERIC_FUNCTIONS
	#define __LL_STRICT_GENERIC_FUNCTIONS 0
#elif __LL_STRICT_GENERIC_FUNCTIONS > 1
	#undef __LL_STRICT_GENERIC_FUNCTIONS
	#define __LL_STRICT_GENERIC_FUNCTIONS 1
#endif // __LL_STRICT_GENERIC_FUNCTIONS

#pragma endregion
#pragma region Logger
#define __LL_LOG_ERROR__	0
#define __LL_LOG_WARNING__	__LL_LOG_ERROR__	+ 1
#define __LL_LOG_INFO__		__LL_LOG_WARNING__	+ 1
#define __LL_LOG_COMMNET__	__LL_LOG_INFO__		+ 1

#if !defined(__LL_LOG__)
	// Max debug type
	// All logs with a number lower that this, is gonna get printed
	#define __LL_LOG__ __LL_LOG_COMMNET__
#endif // __LL_DEBUG__

#pragma region Error
#if !defined(__debug_error_out_of_range)
	#define __debug_error_out_of_range(var_str, var, min, max) __LL_MACRO_WRAPPER__(LL_IGNORE();)
#endif // __debug_error_out_of_range

#if !defined(__debug_error_unexpexted_result)
	#define __debug_error_unexpexted_result(value, expected) __LL_MACRO_WRAPPER__(LL_IGNORE();)
#endif // __debug_error_unexpexted_result

#if !defined(__debug_error_expexted_result)
	#define __debug_error_expexted_result(value, expected) __LL_MACRO_WRAPPER__(LL_IGNORE();)
#endif // __debug_error_unexpexted_result

#if !defined(__debug_error_expexted_false)
	#define __debug_error_unexpexted_true(value) __LL_MACRO_WRAPPER__(LL_IGNORE();)
#endif // __debug_error_unexpexted_result

#if !defined(__debug_error_expexted_true)
	#define __debug_error_expexted_true(value) __LL_MACRO_WRAPPER__(LL_IGNORE();)
#endif // __debug_error_unexpexted_result

#pragma endregion
#pragma region Contructor_Destructor
#if !defined(__LL_DEFAULT_CONSTRUCTOR_LOG)
	#define __LL_DEFAULT_CONSTRUCTOR_LOG 1
#elif __LL_DEFAULT_CONSTRUCTOR_LOG < 0
	#undef __LL_DEFAULT_CONSTRUCTOR_LOG
	#define __LL_DEFAULT_CONSTRUCTOR_LOG 0
#elif __LL_DEFAULT_CONSTRUCTOR_LOG > 1
	#undef __LL_DEFAULT_CONSTRUCTOR_LOG
	#define __LL_DEFAULT_CONSTRUCTOR_LOG 1
#endif // __LL_DEFAULT_CONSTRUCTOR_LOG

#if !defined(__LL_DESTRUCTOR_LOG)
	#define __LL_DESTRUCTOR_LOG 1
#elif __LL_DESTRUCTOR_LOG < 0
	#undef __LL_DESTRUCTOR_LOG
	#define __LL_DESTRUCTOR_LOG 0
#elif __LL_DESTRUCTOR_LOG > 1
	#undef __LL_DESTRUCTOR_LOG
	#define __LL_DESTRUCTOR_LOG 1
#endif // __LL_DESTRUCTOR_LOG

#pragma endregion
#pragma region CopyMove
#if !defined(__LL_COPY_CONSTRUCTOR_LOG)
	#define __LL_COPY_CONSTRUCTOR_LOG 1
#elif __LL_COPY_CONSTRUCTOR_LOG < 0
	#undef __LL_COPY_CONSTRUCTOR_LOG
	#define __LL_COPY_CONSTRUCTOR_LOG 0
#elif __LL_COPY_CONSTRUCTOR_LOG > 1
	#undef __LL_COPY_CONSTRUCTOR_LOG
	#define __LL_COPY_CONSTRUCTOR_LOG 1
#endif // __LL_COPY_CONSTRUCTOR_LOG

#if !defined(__LL_COPY_ASSIGMENT_LOG)
	#define __LL_COPY_ASSIGMENT_LOG 1
#elif __LL_COPY_ASSIGMENT_LOG < 0
	#undef __LL_COPY_ASSIGMENT_LOG
	#define __LL_COPY_ASSIGMENT_LOG 0
#elif __LL_COPY_ASSIGMENT_LOG > 1
	#undef __LL_COPY_ASSIGMENT_LOG
	#define __LL_COPY_ASSIGMENT_LOG 1
#endif // __LL_COPY_ASSIGMENT_LOG

#if !defined(__LL_MOVE_CONSTRUCTOR_LOG)
	#define __LL_MOVE_CONSTRUCTOR_LOG 1
#elif __LL_MOVE_CONSTRUCTOR_LOG < 0
	#undef __LL_MOVE_CONSTRUCTOR_LOG
	#define __LL_MOVE_CONSTRUCTOR_LOG 0
#elif __LL_MOVE_CONSTRUCTOR_LOG > 1
	#undef __LL_MOVE_CONSTRUCTOR_LOG
	#define __LL_MOVE_CONSTRUCTOR_LOG 1
#endif // __LL_MOVE_CONSTRUCTOR_LOG

#if !defined(__LL_MOVE_ASSIGMENT_LOG)
	#define __LL_MOVE_ASSIGMENT_LOG 1
#elif __LL_MOVE_ASSIGMENT_LOG < 0
	#undef __LL_MOVE_ASSIGMENT_LOG
	#define __LL_MOVE_ASSIGMENT_LOG 0
#elif __LL_MOVE_ASSIGMENT_LOG > 1
	#undef __LL_MOVE_ASSIGMENT_LOG
	#define __LL_MOVE_ASSIGMENT_LOG 1
#endif // __LL_MOVE_ASSIGMENT_LOG

#pragma endregion
#pragma region DestructorValidationAndSecurity
#if !defined(__LL_CLEAR_SECURE_LOG)
	#define __LL_CLEAR_SECURE_LOG 1
#elif __LL_CLEAR_SECURE_LOG < 0
	#undef __LL_CLEAR_SECURE_LOG
	#define __LL_CLEAR_SECURE_LOG 0
#elif __LL_CLEAR_SECURE_LOG > 1
	#undef __LL_CLEAR_SECURE_LOG
	#define __LL_CLEAR_SECURE_LOG 1
#endif // __LL_CLEAR_SECURE_LOG

#if !defined(__LL_RANDOM_SECURE_LOG)
	#define __LL_RANDOM_SECURE_LOG 1
#elif __LL_RANDOM_SECURE_LOG < 0
	#undef __LL_RANDOM_SECURE_LOG
	#define __LL_RANDOM_SECURE_LOG 0
#elif __LL_RANDOM_SECURE_LOG > 1
	#undef __LL_RANDOM_SECURE_LOG
	#define __LL_RANDOM_SECURE_LOG 1
#endif // __LL_RANDOM_SECURE_LOG

#pragma endregion
#pragma region Reference
#if !defined(__LL_REFERENCE_OPERATOR_LOG)
	#define __LL_REFERENCE_OPERATOR_LOG 1
#elif __LL_REFERENCE_OPERATOR_LOG < 0
	#undef __LL_REFERENCE_OPERATOR_LOG
	#define __LL_REFERENCE_OPERATOR_LOG 0
#elif __LL_REFERENCE_OPERATOR_LOG > 1
	#undef __LL_REFERENCE_OPERATOR_LOG
	#define __LL_REFERENCE_OPERATOR_LOG 1
#endif // __LL_REFERENCE_OPERATOR_LOG

#pragma endregion
#pragma region GetSet
#if !defined(__LLANYLIB_INTERNAL_GET_LOG)
	#define __LLANYLIB_INTERNAL_GET_LOG 1
#elif __LLANYLIB_INTERNAL_GET_LOG < 0
	#undef __LLANYLIB_INTERNAL_GET_LOG
	#define __LLANYLIB_INTERNAL_GET_LOG 0
#elif __LLANYLIB_INTERNAL_GET_LOG > 1
	#undef __LLANYLIB_INTERNAL_GET_LOG
	#define __LLANYLIB_INTERNAL_GET_LOG 1
#endif // __LLANYLIB_INTERNAL_GET_LOG

#if !defined(__LLANYLIB_GET_LOG)
	#define __LLANYLIB_GET_LOG 1
#elif __LLANYLIB_GET_LOG < 0
	#undef __LLANYLIB_GET_LOG
	#define __LLANYLIB_GET_LOG 0
#elif __LLANYLIB_GET_LOG > 1
	#undef __LLANYLIB_GET_LOG
	#define __LLANYLIB_GET_LOG 1
#endif // __LLANYLIB_GET_LOG

#if !defined(__LLANYLIB_SET_LOG)
	#define __LLANYLIB_SET_LOG 1
#elif __LLANYLIB_SET_LOG < 0
	#undef __LLANYLIB_SET_LOG
	#define __LLANYLIB_SET_LOG 0
#elif __LLANYLIB_SET_LOG > 1
	#undef __LLANYLIB_SET_LOG
	#define __LLANYLIB_SET_LOG 1
#endif // __LLANYLIB_SET_LOG

#pragma endregion

#pragma endregion
#pragma region Asserts
#define __LL_ASSERT_VAR_ZERO__(var, var_str)	LL_ASSERT(var > 0,			__LL_STRING_PREFIX "[" var_str __LL_STRING_PREFIX "] cannot be 0. "			__LL_FUNCNAME__)
#define __LL_ASSERT_VAR_NULL__(var, var_str)	LL_ASSERT(var,				__LL_STRING_PREFIX "[" var_str __LL_STRING_PREFIX "] cannot be nullptr."	__LL_FUNCNAME__)
#define __LL_ASSERT_LIST_EMPTY__(var, var_str)	LL_ASSERT(!var.empty(),		__LL_STRING_PREFIX "[" var_str __LL_STRING_PREFIX "] cannot be empty."		__LL_FUNCNAME__)
#define __LL_ASSERT_B_LOWER_THAN_A__(var_a, var_b, var_a_str, var_b_str) \
												LL_ASSERT(var_a < var_b,	__LL_STRING_PREFIX "[" var_a_str __LL_STRING_PREFIX " < " var_b_str \
																			__LL_STRING_PREFIX "] " var_a_str __LL_STRING_PREFIX " cannot be lower or equal to " var_b_str \
																			__LL_STRING_PREFIX "." __LL_FUNCNAME__)

#pragma endregion
#pragma region CommonCode
#pragma region GetSet
#define LL_STANDARD_BASE_GET_SET(vartype, varname, internal_body, const_internal_body, set_copy_body, set_move_body)	\
	protected:																											\
		__LL_NODISCARD__ vartype & getInternal() noexcept internal_body													\
		__LL_NODISCARD__ const vartype & getInternal() const noexcept const_internal_body								\
	public:																												\
		void set(const vartype & varname) noexcept set_copy_body														\
		void set(vartype && varname) noexcept set_move_body

#pragma region GetSetHeader
#define LL_STANDARD_GET_COPY_SET_HEADERS(vartype, varname)		\
	LL_STANDARD_BASE_GET_SET(vartype, varname, ;, ;, ;, ;)		\
	public:														\
		__LL_NODISCARD__ vartype get() const noexcept

#define LL_STANDARD_GET_REFERENCE_SET_HEADERS(vartype, varname)	\
	LL_STANDARD_BASE_GET_SET(vartype, varname, ;, ;, ;, ;)		\
	public:														\
		__LL_NODISCARD__ const vartype & get() const noexcept

#pragma endregion
#pragma region GetSetTemplate
#define LL_GET_INTERNAL_BODY(varname, get_log)	\
	{											\
		__LL_FUNCTION_INIT_ENABLER__(get_log);	\
		return this->varname;					\
	}

#define LL_SET_COPY_INTERNAL_BODY(varname, set_log, useforward)			\
	{																	\
		__LL_FUNCTION_INIT_ENABLER__(set_log);							\
		if constexpr (useforward)										\
			::llcpp::forward_copy<useforward>(this->varname, varname);	\
		else this->varname = varname;									\
	}

#define LL_SET_MOVE_INTERNAL_BODY(varname, set_log, useforward)			\
	{																	\
		__LL_FUNCTION_INIT_ENABLER__(set_log);							\
		if constexpr (useforward)										\
			::llcpp::forward_move<useforward>(this->varname, varname);	\
		else this->varname = varname;									\
	}

#define LL_STANDARD_GET_COPY_SET_TEMPLATE(vartype, varname, useforward, get_log, set_log)	\
	LL_STANDARD_BASE_GET_SET(																\
		vartype, varname,																	\
		LL_GET_INTERNAL_BODY(varname, get_log),												\
		LL_GET_INTERNAL_BODY(varname, get_log),												\
		LL_SET_COPY_INTERNAL_BODY(varname, set_log, useforward),							\
		LL_SET_MOVE_INTERNAL_BODY(varname, set_log, useforward),							\
	)																						\
	public:																					\
		__LL_NODISCARD__ vartype get() const noexcept										\
		LL_GET_INTERNAL_BODY(varname, get_log)


#define LL_STANDARD_GET_REFERENCE_SET_TEMPLATE(vartype, varname, useforward, get_log, set_log)	\
	LL_STANDARD_BASE_GET_SET(																	\
		vartype, varname,																		\
		LL_GET_INTERNAL_BODY(varname, get_log),													\
		LL_GET_INTERNAL_BODY(varname, get_log),													\
		LL_SET_COPY_INTERNAL_BODY(varname, set_log, useforward),								\
		LL_SET_MOVE_INTERNAL_BODY(varname, set_log, useforward),								\
	)																							\
	public:																						\
		__LL_NODISCARD__ const vartype & get() const noexcept									\
		LL_GET_INTERNAL_BODY(varname, get_log)

#pragma endregion

#pragma endregion
#pragma region Contructor
// Includes:
//	* Default destructor
//	* Default copy
//	* Default copy assigment
//	* Default move
//	* Default move assigment
//	* Operator class type (const/no const)
#define LL_DEFAULT_RULE_OF_6_NO_CONSTRUCTOR(classname, reference_operator)							\
	__LL_NODISCARD__ constexpr explicit operator const classname*() const noexcept {				\
		__LL_FUNCTION_INIT_ENABLER__(reference_operator);											\
		return this;																				\
	}																								\
	__LL_NODISCARD__ constexpr explicit operator classname*() noexcept {							\
		__LL_FUNCTION_INIT_ENABLER__(reference_operator);											\
		return this;																				\
	}																								\
	constexpr classname (const classname&) noexcept = default;										\
	constexpr classname& operator=(const classname&) noexcept = default;							\
	constexpr classname (classname&&) noexcept = default;											\
	constexpr classname& operator=(classname&&) noexcept = default;									\
	constexpr classname(const volatile classname&) noexcept = delete;								\
	constexpr classname& operator=(const volatile classname&) noexcept = delete;					\
	constexpr classname(volatile classname&&) noexcept = delete;									\
	constexpr classname& operator=(volatile classname&&) noexcept = delete;							\
	constexpr ~classname () noexcept = default

// Includes:
//	* Constructor wuith all primitive parameters as error data
//		Constructor does includes __LL_FUNCTION_INIT__
#define LL_DEFAULT_RULE_OF_6_WITH_ERROR_DATA(classname, reference_operator)	\
	constexpr classname () noexcept { __LL_FUNCTION_INIT__; }				\
	LL_DEFAULT_RULE_OF_6_NO_CONSTRUCTOR(classname, reference_operator)

// Includes:
//	* Default contructor
//		Constructor does not includes __LL_FUNCTION_INIT__
#define LL_DEFAULT_RULE_OF_6_CLEAR(classname, reference_operator)			\
	constexpr classname () noexcept = default;								\
	LL_DEFAULT_RULE_OF_6_NO_CONSTRUCTOR(classname, reference_operator)

#pragma endregion
#pragma region DestructorValidationAndSecurity
#define LL_DEF_VALIDATIONTYPE		validationType
#define LL_DEF_RESET				reset
#define LL_DEF_CLEAR				clear
#define LL_DEF_CLEAR_SECURE			clearSecure
#define LL_DEF_RANDOM_SECURE		randomSecure
#define LL_DEF_MAKE_INVALID			makeInvalid
#define LL_DEF_MAKE_INVALID_CLEAR	makeInvalidClear
#define LL_DEF_MAKE_INVALID_RANDOM	makeInvalidByRandom

// Add functionality to standard clear class on standard destruction
#define LL_DEFAULT_DESTRUCTOR_ALWAYS_VALID(random_secure, clear_secure)	\
	if constexpr (random_secure)										\
		this->LL_DEF_RANDOM_SECURE();									\
	else if constexpr (clear_secure)									\
		this->LL_DEF_CLEAR_SECURE()

// Add functionality to standard clear class on standard destruction
#define LL_DEFAULT_DESTRUCTOR_INVALIDATOR(random_secure, clear_secure, pointer_clear)	\
	LL_DEFAULT_DESTRUCTOR_ALWAYS_VALID(random_secure, clear_secure);					\
	else if constexpr (pointer_clear)													\
		this->LL_DEF_MAKE_INVALID()

#pragma endregion

#define EXIT_ON_FAILURE_IMPL(value, expected, result)		\
	if (value != expected) {								\
		__debug_error_unexpexted_result(value, expected);	\
		return result;										\
	}

#define EXIT_ON_SUCCESS_IMPL(value, expected, result)		\
	if (value == expected) {								\
		__debug_error_expexted_result(value, expected);		\
		return result;										\
	}

#define EXIT_ON_FALSE_IMPL(value, result)					\
	if (!value) {											\
		__debug_error_unexpexted_false(value);				\
		return result;										\
	}

#define EXIT_ON_TRUE_IMPL(value, result)					\
	if (value) {											\
		__debug_error_expexted_true(value);					\
		return result;										\
	}


// Error control to exit a function with an error message
// Custom return
// Applies if value != expected
#define EXIT_ON_FAILURE(value, expected, result)	__LL_MACRO_WRAPPER__(EXIT_ON_FAILURE_IMPL(value, expected, result))
// Error control to exit a function with an error message
// Custom return
// Applies if value != expected
#define EXIT_ON_SUCCESS(value, expected, result)	__LL_MACRO_WRAPPER__(EXIT_ON_SUCCESS_IMPL(value, expected, result))

// Error control to exit a function with an error message
// Custom return
// Applies if (!value)
#define EXIT_ON_FALSE(value, result)				__LL_MACRO_WRAPPER__(EXIT_ON_FALSE_IMPL(value, result))
// Error control to exit a function with an error message
// Custom return
// Applies if (value)
#define EXIT_ON_TRUE(value, result)					__LL_MACRO_WRAPPER__(EXIT_ON_TRUE_IMPL(value, result))

// Error control to exit a function with an error message
// Returns __LL_FAILURE_EXECUTION__
// Applies if value != expected
#define EXIT_ON_FAILURE_BASE_C(value, expected)		EXIT_ON_FAILURE(value, expected, __LL_FAILURE_EXECUTION__)
// Error control to exit a function with an error message
// Returns __LL_FAILURE_EXECUTION__
// Applies if value == expected
#define EXIT_ON_SUCCESS_BASE_C(value, expected)		EXIT_ON_SUCCESS(value, expected, __LL_FAILURE_EXECUTION__)

// Error control to exit a function with an error message
// Returns __LL_FAILURE_EXECUTION__
// Applies if (!value)
#define EXIT_ON_FALSE_BASE_C(value, result)			EXIT_ON_FAILURE(value, __LL_FAILURE_EXECUTION__)
// Error control to exit a function with an error message
// Returns __LL_FAILURE_EXECUTION__
// Applies if (value)
#define EXIT_ON_TRUE_BASE_C(value, result)			EXIT_ON_SUCCESS(value, __LL_FAILURE_EXECUTION__)

#pragma endregion
#pragma region Behabiour
#pragma region DestructorValidationAndSecurity
#if !defined(__LL_RANDOM_SECURE)
	#define __LL_RANDOM_SECURE 0
#elif __LL_RANDOM_SECURE < 0
	#undef __LL_RANDOM_SECURE
	#define __LL_RANDOM_SECURE 0
#elif __LL_RANDOM_SECURE > 1
	#undef __LL_RANDOM_SECURE
	#define __LL_RANDOM_SECURE 1
#endif // __LL_RANDOM_SECURE

#if __LL_REAL_CXX23 == 0
	#if __LL_RANDOM_SECURE == 1
		#error "Random by mode (compilation/runtime) is disabled! Use this as your own risk. This error can be commented."
	#endif // __LL_RANDOM_SECURE
#endif // __LL_REAL_CXX23

#if !defined(__LL_CLEAR_SECURE)
	#define __LL_CLEAR_SECURE 0
#elif __LL_CLEAR_SECURE < 0
	#undef __LL_CLEAR_SECURE
	#define __LL_CLEAR_SECURE 0
#elif __LL_CLEAR_SECURE > 1
	#undef __LL_CLEAR_SECURE
	#define __LL_CLEAR_SECURE 1
#endif // __LL_CLEAR_SECURE

#if !defined(__LL_CLEAR_POINTERS_ON_DESTRUCTION)
	#define __LL_CLEAR_POINTERS_ON_DESTRUCTION 1
#elif __LL_CLEAR_POINTERS_ON_DESTRUCTION < 0
	#undef __LL_CLEAR_POINTERS_ON_DESTRUCTION
	#define __LL_CLEAR_POINTERS_ON_DESTRUCTION 0
#elif __LL_CLEAR_POINTERS_ON_DESTRUCTION > 1
	#undef __LL_CLEAR_POINTERS_ON_DESTRUCTION
	#define __LL_CLEAR_POINTERS_ON_DESTRUCTION 1
#endif // __LL_CLEAR_POINTERS_ON_DESTRUCTION

#pragma endregion

#if !defined(__LL_BOOL_RANGE_CHECK)
	#define __LL_BOOL_RANGE_CHECK 1
#elif __LL_BOOL_RANGE_CHECK < 0
	#undef __LL_BOOL_RANGE_CHECK
	#define __LL_BOOL_RANGE_CHECK 0
#elif __LL_BOOL_RANGE_CHECK > 1
	#undef __LL_BOOL_RANGE_CHECK
	#define __LL_BOOL_RANGE_CHECK 1
#endif // __LL_BOOL_RANGE_CHECK

#pragma endregion
// Deprecated or [TOCHECK]
#pragma region Ungrouped

/*
#if !defined(__LL_IGNORE_WARNING_STATIC_ASSERTS__)
	#define __LL_IGNORE_WARNING_STATIC_ASSERTS__ 0
#elif __LL_IGNORE_WARNING_STATIC_ASSERTS__ < 0
	#undef __LL_IGNORE_WARNING_STATIC_ASSERTS__
	#define __LL_IGNORE_WARNING_STATIC_ASSERTS__ 0
#elif __LL_IGNORE_WARNING_STATIC_ASSERTS__ > 1
	#undef __LL_IGNORE_WARNING_STATIC_ASSERTS__
	#define __LL_IGNORE_WARNING_STATIC_ASSERTS__ 1
#endif // __LL_IGNORE_WARNING_STATIC_ASSERTS__

#if !defined(__LL_EXCEPTIONS)
	#define __LL_EXCEPTIONS 0
#elif __LL_EXCEPTIONS < 0
	#undef __LL_EXCEPTIONS
	#define __LL_EXCEPTIONS 0
#elif __LL_EXCEPTIONS > 1
	#undef __LL_EXCEPTIONS
	#define __LL_EXCEPTIONS 1
#endif // __LL_EXCEPTIONS

// 0: Generate a error on pointer found
// 1: Deference pointer an call again
#if !defined(__LL_CLEAR_POINTER_AS)
	#define __LL_CLEAR_POINTER_AS 0
#elif __LL_CLEAR_POINTER_AS < 0
	#undef __LL_CLEAR_POINTER_AS
	#define __LL_CLEAR_POINTER_AS 0
#elif __LL_CLEAR_POINTER_AS > 1
	#undef __LL_CLEAR_POINTER_AS
	#define __LL_CLEAR_POINTER_AS 1
#endif // __LL_CLEAR_POINTER_AS

*/

#pragma endregion
#pragma region Error

/*#if !defined(__debug_error_exceptions_full)
	#define __debug_error_exceptions_full(str) do { LL_IGNORE(); } while(0)
#endif

#if !defined(__debug_error_exceptions_empty)
	#define __debug_error_exceptions_empty(str) do { LL_IGNORE(); } while(0)
#endif

#if !defined(__debug_error_not_nullptr_str)
	#define __debug_error_not_nullptr_str(var_str) do { LL_IGNORE(); } while(0)
#endif

#if !defined(__debug_error_begin_smaller)
	#define __debug_error_begin_smaller(str, begin, end) do { LL_IGNORE(); } while(0)
#endif

#if !defined(__debug_error_parser)
	#define __debug_error_parser(str) do { LL_IGNORE(); } while(0)
#endif
*/

/*
#pragma region Error

// Nullptr
#if !defined(__debug_error_nullptr_str)
	#define __debug_error_nullptr_str(var, var_str) do { LL_IGNORE(); } while(0)
#endif

// Ranges
#if !defined(__debug_error_out_of_range)
	#define __debug_error_out_of_range(var, len) do { LL_IGNORE(); } while(0)
#endif


// Other
#if !defined(__debug_error_zero_value_str)
	#define __debug_error_zero_value_str(var_str) do { LL_IGNORE(); } while(0)
#endif

#pragma endregion
#pragma region Warning

// Nullptr
#if !defined(__debug_warning_not_nullptr)
	#define __debug_warning_not_nullptr(var) do { LL_IGNORE(); } while(0)
#endif

#if !defined(__debug_warning_not_nullptr_str)
	#define __debug_warning_not_nullptr_str(var, var_str) do { LL_IGNORE(); } while(0)
#endif

// Ranges
#if !defined(__debug_warning_out_of_range)
	#define __debug_warning_out_of_range(var, len) do { LL_IGNORE(); } while(0)
#endif

// Other
#if !defined(__debug_warning_zero_value_str)
	#define __debug_warning_zero_value_str(var_str) do { LL_IGNORE(); } while(0)
#endif

#if !defined(__debug_warning_invalidation_in_reset_str)
	#define __debug_warning_invalidation_in_reset_str(var_str) do { LL_IGNORE(); } while(0)
#endif

#pragma endregion

*/

#pragma endregion
#pragma region Warning

/*#if !defined(__debug_warning_nullptr)
	#define __debug_warning_nullptr(var_str) do { LL_IGNORE(); } while(0)
#endif

#if !defined(__debug_warning_out_of_range)
	#define __debug_warning_out_of_range(var, var_str, len) do { LL_IGNORE(); } while(0)
#endif
*/

#pragma endregion

#endif // LLANYLIB_DEFINITIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
