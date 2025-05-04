//////////////////////////////////////////////
//	ValidType.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_VALIDTYPE_INCOMPLETE_HPP_)
	#if LLANYLIB_VALIDTYPE_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_VALIDTYPE_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "ValidType.hpp(incomplete) version error!"
		#else
			#error "ValidType.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_VALIDTYPE_INCOMPLETE_MAYOR_ || LLANYLIB_VALIDTYPE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_VALIDTYPE_INCOMPLETE_HPP_)
	#define LLANYLIB_VALIDTYPE_INCOMPLETE_HPP_
	#define LLANYLIB_VALIDTYPE_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_VALIDTYPE_INCOMPLETE_MINOR_ 0

#include "types.hpp"

namespace llcpp {
namespace misc {

enum class ValidType : u8;

} // namespace misc
} // namespace llcpp

#elif defined(LLANYLIB_VALIDTYPE_HPP_)
	#if LLANYLIB_VALIDTYPE_MAYOR_ != 12 || LLANYLIB_VALIDTYPE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "ValidType.hpp version error!"
		#else
			#error "ValidType.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_VALIDTYPE_MAYOR_ || LLANYLIB_VALIDTYPE_MINOR_

#else
	#define LLANYLIB_VALIDTYPE_HPP_
	#define LLANYLIB_VALIDTYPE_MAYOR_ 12
	#define LLANYLIB_VALIDTYPE_MINOR_ 0

#include "types.hpp"

namespace llcpp {
namespace misc {

/// Do not change order
enum class ValidType : u8 {
	Valid,			// Class is valid
	Invalid,		// Class is invalid
	ToCheck,		// User needs to check via validationType() in runtime.
	Primitive,		// Its a primitive (floating or not)
	Array,			// Its an array
	Pointer,		// Its a pointer
	Unknown,		// Could not determine validation type.

	Error			// This one must be always last one
};

} // namespace misc
} // namespace llcpp

#endif // LLANYLIB_VALIDTYPE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
