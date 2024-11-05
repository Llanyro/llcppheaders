//////////////////////////////////////////////
//	functional_attributes.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_QWERTY_INCOMPLETE_HPP_)
	#if LLANYLIB_QWERTY_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_QWERTY_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "functional_attributes.hpp(incomplete) version error!"
		#else
			#error "functional_attributes.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_QWERTY_INCOMPLETE_MAYOR_ || LLANYLIB_QWERTY_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_QWERTY_INCOMPLETE_HPP_)
#define LLANYLIB_QWERTY_INCOMPLETE_HPP_
#define LLANYLIB_QWERTY_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_QWERTY_INCOMPLETE_MINOR_ 0

#include "types_base_extra.hpp"

namespace llcpp { namespace meta { struct function_attributes_t; } } // namespace llcpp

#elif defined(LLANYLIB_QWERTY_HPP_)
	#if LLANYLIB_QWERTY_MAYOR_ != 11 || LLANYLIB_QWERTY_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "functional_attributes.hpp version error!"
		#else
			#error "functional_attributes.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_QWERTY_MAYOR_ || LLANYLIB_QWERTY_MINOR_

#else
#define LLANYLIB_QWERTY_HPP_
#define LLANYLIB_QWERTY_MAYOR_ 11
#define LLANYLIB_QWERTY_MINOR_ 0

#include "types_base_extra.hpp"

namespace llcpp {
namespace meta {

struct function_attributes_t {
	// Class related
	using _MyType = function_attributes_t;

	// Attributes
	ll_bool_t CONST			: 1;
	ll_bool_t NOEXCEPTION	: 1;
};

namespace functional {

__LL_VAR_INLINE__ constexpr meta::function_attributes_t CLASSIC				= { llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr meta::function_attributes_t CONST				= { llcpp::TRUE,  llcpp::FALSE };
__LL_VAR_INLINE__ constexpr meta::function_attributes_t NOEXCEPTION			= { llcpp::FALSE, llcpp::TRUE };
__LL_VAR_INLINE__ constexpr meta::function_attributes_t CONSTNOEXCEPTION	= { llcpp::TRUE,  llcpp::TRUE };

} // namespace functional
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_QWERTY_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
