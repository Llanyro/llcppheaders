//////////////////////////////////////////////
//	Errors.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ERRORS_INCOMPLETE_HPP_)
	#if LLANYLIB_ERRORS_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ERRORS_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Errors.hpp(incomplete) version error!"
		#else
			#error "Errors.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ERRORS_INCOMPLETE_MAYOR_ || LLANYLIB_ERRORS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ERRORS_INCOMPLETE_HPP_)
	#define LLANYLIB_ERRORS_INCOMPLETE_HPP_
	#define LLANYLIB_ERRORS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ERRORS_INCOMPLETE_MINOR_ 0

#include "types.hpp"

namespace llcpp {
namespace misc {

enum class Errors : u8;

} // namespace misc
} // namespace llcpp

#elif defined(LLANYLIB_ERRORS_HPP_)
	#if LLANYLIB_ERRORS_MAYOR_ != 12 || LLANYLIB_ERRORS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Errors.hpp version error!"
		#else
			#error "Errors.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ERRORS_MAYOR_ || LLANYLIB_ERRORS_MINOR_

#else
	#define LLANYLIB_ERRORS_HPP_
	#define LLANYLIB_ERRORS_MAYOR_ 12
	#define LLANYLIB_ERRORS_MINOR_ 0

#include "types.hpp"

namespace llcpp {
namespace misc {

enum class Errors : i32 {
	Ok = 0,

	OutOfRange,			// Same as out of bounds
	OutOfRangeBegin,	// Same as out of bounds
	OutOfRangeEnd,		// Same as out of bounds
	NullptrProvided,	// Parameter nullptr provided by user

};

} // namespace misc
} // namespace llcpp

#endif // LLANYLIB_ERRORS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
