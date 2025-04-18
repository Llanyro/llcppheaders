//////////////////////////////////////////////
//	valid_type.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_VALID_TYPE_HPP_) // Guard && version protector
	#if LLANYLIB_VALID_TYPE_MAYOR_ != 12 || LLANYLIB_VALID_TYPE_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "valid_type.hpp version error!"
		#else
			#error "valid_type.hpp version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_VALID_TYPE_MAYOR_ || LLANYLIB_VALID_TYPE_MINOR_

#else
	#define LLANYLIB_VALID_TYPE_HPP_
	#define LLANYLIB_VALID_TYPE_MAYOR_ 12
	#define LLANYLIB_VALID_TYPE_MINOR_ 0

#include "concepts.hpp"

#include "../traits_base/valid_type.hpp"

namespace llcpp {
namespace meta {
namespace concepts {
namespace signature {

template<class T>
concept HasValidationType = requires (T t) {
	{ t.validationType() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<::llcpp::meta::ValidType>;
};

} // namespace signature
} // namespace concepts
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_VALID_TYPE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
