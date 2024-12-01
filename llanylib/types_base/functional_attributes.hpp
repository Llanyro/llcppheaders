//////////////////////////////////////////////
//	functional_attributes.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_FUNCTIONALATTRIBUTES_INCOMPLETE_HPP_)
	#if LLANYLIB_FUNCTIONALATTRIBUTES_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_FUNCTIONALATTRIBUTES_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "functional_attributes.hpp(incomplete) version error!"
		#else
			#error "functional_attributes.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_FUNCTIONALATTRIBUTES_INCOMPLETE_MAYOR_ || LLANYLIB_FUNCTIONALATTRIBUTES_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_FUNCTIONALATTRIBUTES_INCOMPLETE_HPP_)
#define LLANYLIB_FUNCTIONALATTRIBUTES_INCOMPLETE_HPP_
#define LLANYLIB_FUNCTIONALATTRIBUTES_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_FUNCTIONALATTRIBUTES_INCOMPLETE_MINOR_ 0

#include "types_base_extra.hpp"

namespace llcpp {
namespace meta {

struct function_attributes_t;

} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_FUNCTIONALATTRIBUTES_HPP_)
	#if LLANYLIB_FUNCTIONALATTRIBUTES_MAYOR_ != 11 || LLANYLIB_FUNCTIONALATTRIBUTES_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "functional_attributes.hpp version error!"
		#else
			#error "functional_attributes.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_FUNCTIONALATTRIBUTES_MAYOR_ || LLANYLIB_FUNCTIONALATTRIBUTES_MINOR_

#else
#define LLANYLIB_FUNCTIONALATTRIBUTES_HPP_
#define LLANYLIB_FUNCTIONALATTRIBUTES_MAYOR_ 11
#define LLANYLIB_FUNCTIONALATTRIBUTES_MINOR_ 0

#include "types_base_extra.hpp"

namespace llcpp {
namespace meta {
namespace attributes {

struct function_attributes_t {
	// Class related
	using _MyType = function_attributes_t;

	// Attributes
	ll_bool_t CONST			: 1;
	ll_bool_t NOEXCEPTION	: 1;

	template<ll_bool_t IS_CONST, ll_bool_t IS_NOEXCEPT>
	static constexpr _MyType CUSTOM = { IS_CONST, IS_NOEXCEPT };

	constexpr ll_bool_t operator==(const _MyType& other) const noexcept {
		return this->CONST == other.CONST && this->NOEXCEPTION == other.NOEXCEPTION;
	}
};

namespace functional {

using _MyType = ::llcpp::meta::attributes::function_attributes_t::_MyType;

template<ll_bool_t IS_CONST, ll_bool_t IS_NOEXCEPT>
static constexpr _MyType CUSTOM = { IS_CONST, IS_NOEXCEPT };

//															const			noexception
__LL_VAR_INLINE__ constexpr _MyType CLASSIC				= { llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType CONST				= { llcpp::TRUE,  llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType NOEXCEPTION			= { llcpp::FALSE, llcpp::TRUE };
__LL_VAR_INLINE__ constexpr _MyType CONSTNOEXCEPTION	= { llcpp::TRUE,  llcpp::TRUE  };

} // namespace functional

} // namespace attributes
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_FUNCTIONALATTRIBUTES_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
