//////////////////////////////////////////////
//	valid_type.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_HPP_)
	#if LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "valid_type.hpp(incomplete) version error!"
		#else
			#error "valid_type.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_MAYOR_ || LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_HPP_)
	#define LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_HPP_
	#define LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_MINOR_ 0

#include "../traits_base/valid_type.hpp"

#include "concepts.hpp"

#elif defined(LLANYLIB_CONCEPTSVALIDTYPE_HPP_)
	#if LLANYLIB_CONCEPTSVALIDTYPE_MAYOR_ != 12 || LLANYLIB_CONCEPTSVALIDTYPE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "valid_type.hpp version error!"
		#else
			#error "valid_type.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONCEPTSVALIDTYPE_MAYOR_ || LLANYLIB_CONCEPTSVALIDTYPE_MINOR_

#else
	#define LLANYLIB_CONCEPTSVALIDTYPE_HPP_
	#define LLANYLIB_CONCEPTSVALIDTYPE_MAYOR_ 12
	#define LLANYLIB_CONCEPTSVALIDTYPE_MINOR_ 0

#include "../traits_base/valid_type.hpp"

#include "concepts.hpp"

namespace llcpp {
namespace meta {
namespace concepts {
namespace signature {

template<class T>
concept HasValidationType = requires (T t) {
	{ t.validationType() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<::llcpp::misc::ValidType>;
};

} // namespace signature
} // namespace concepts
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CONCEPTSVALIDTYPE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
