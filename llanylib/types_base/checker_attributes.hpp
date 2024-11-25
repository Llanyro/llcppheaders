//////////////////////////////////////////////
//	checker_attributes.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_HPP_)
	#if LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "checker_attributes.hpp(incomplete) version error!"
		#else
			#error "checker_attributes.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MAYOR_ || LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_HPP_)
#define LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_HPP_
#define LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MINOR_ 0

#include "../types_base/types_base_extra.hpp"

namespace llcpp {
namespace meta {
namespace traits {

struct checker_attributes_t;

} // namespace traits
} // namespace meta
} // namespace llcpp


#elif defined(LLANYLIB_CHECKERATTRIBUTES_HPP_)
	#if LLANYLIB_CHECKERATTRIBUTES_MAYOR_ != 11 || LLANYLIB_CHECKERATTRIBUTES_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "checker_attributes.hpp version error!"
		#else
			#error "checker_attributes.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CHECKERATTRIBUTES_MAYOR_ || LLANYLIB_CHECKERATTRIBUTES_MINOR_

#else
#define LLANYLIB_CHECKERATTRIBUTES_HPP_
#define LLANYLIB_CHECKERATTRIBUTES_MAYOR_ 11
#define LLANYLIB_CHECKERATTRIBUTES_MINOR_ 0

#include "../types_base/types_base_extra.hpp"

namespace llcpp {
namespace meta {
namespace attributes {

struct checker_attributes_t {
	// Class related
	using _MyType						= checker_attributes_t;

	// Attributes
	ll_bool_t IGNORE_POINTER			: 1;
	ll_bool_t IGNORE_ARRAY				: 1;
	ll_bool_t IGNORE_VOLATILE			: 1;
	ll_bool_t IGNORE_CONST				: 1;
	ll_bool_t IGNORE_REFERENCE			: 1;

	ll_bool_t IGNORE_CONSTRUCTIBLE		: 1;
	ll_bool_t IGNORE_COPY_CONSTRUCTIBLE	: 1;
	ll_bool_t IGNORE_COPY_ASSIGNABLE	: 1;
	ll_bool_t IGNORE_MOVE_CONSTRUCTIBLE	: 1;
	ll_bool_t IGNORE_MOVE_ASSIGNABLE	: 1;

	template<ll_bool_t IGNORE_POINTER, ll_bool_t IGNORE_ARRAY, ll_bool_t IGNORE_VOLATILE, ll_bool_t IGNORE_CONST, ll_bool_t IGNORE_REFERENCE>
	static constexpr _MyType CUSTOM_P1 = { IGNORE_POINTER, IGNORE_ARRAY, IGNORE_VOLATILE, IGNORE_CONST, IGNORE_REFERENCE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
	template<ll_bool_t IGNORE_CONSTRUCTIBLE, ll_bool_t IGNORE_COPY_CONSTRUCTIBLE, ll_bool_t IGNORE_COPY_ASSIGNABLE, ll_bool_t IGNORE_MOVE_CONSTRUCTIBLE, ll_bool_t IGNORE_MOVE_ASSIGNABLE>
	static constexpr _MyType CUSTOM_P2 = { llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, IGNORE_CONSTRUCTIBLE, IGNORE_COPY_CONSTRUCTIBLE, IGNORE_COPY_ASSIGNABLE, IGNORE_MOVE_CONSTRUCTIBLE, IGNORE_MOVE_ASSIGNABLE };
};

namespace checker {

using _MyType = ::llcpp::meta::attributes::checker_attributes_t::_MyType;

//														Pointer			Array		Volatile		Const		 Reference		Construct	CopyConstruct CopyAssign	MoveConstruct	MoveAssig
__LL_VAR_INLINE__ constexpr _MyType DEFAULT			= { llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_POINTER	= { llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_ARRAY	= { llcpp::FALSE, llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_CONST	= { llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::TRUE,	llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_VOLATILE	= { llcpp::FALSE, llcpp::FALSE, llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_PA		= { llcpp::TRUE,  llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_CPA		= { llcpp::TRUE,  llcpp::TRUE,  llcpp::FALSE, llcpp::TRUE,	llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_CP		= { llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::TRUE,	llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_CPV		= { llcpp::TRUE,  llcpp::FALSE, llcpp::TRUE,  llcpp::TRUE,	llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };

} // namespace checker

} // namespace attributes
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CHECKERATTRIBUTES_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
