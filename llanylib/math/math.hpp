//////////////////////////////////////////////
//	math.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_MATH_INCOMPLETE_HPP_)
	#if LLANYLIB_MATH_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_MATH_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "math.hpp(incomplete) version error!"
		#else
			#error "math.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_MATH_INCOMPLETE_MAYOR_ || LLANYLIB_MATH_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_MATH_INCOMPLETE_HPP_)
	#define LLANYLIB_MATH_INCOMPLETE_HPP_
	#define LLANYLIB_MATH_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_MATH_INCOMPLETE_MINOR_ 0

#elif defined(LLANYLIB_MATH_HPP_)
	#if LLANYLIB_MATH_MAYOR_ != 12 || LLANYLIB_MATH_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "math.hpp version error!"
		#else
			#error "math.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_MATH_MAYOR_ || LLANYLIB_MATH_MINOR_

#else
	#define LLANYLIB_MATH_HPP_
	#define LLANYLIB_MATH_MAYOR_ 12
	#define LLANYLIB_MATH_MINOR_ 0

#include "is_even.hpp"	// Includes is_odd.hpp

#endif // LLANYLIB_MATH_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_MATH_EXTRA_HPP_)
		#if LLANYLIB_MATH_EXTRA_MAYOR_ != 12 || LLANYLIB_MATH_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "math.hpp(extra) version error!"
			#else
				#error "math.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_MATH_EXTRA_MAYOR_ || LLANYLIB_MATH_EXTRA_MINOR_

	#else
		#define LLANYLIB_MATH_EXTRA_HPP_
		#define LLANYLIB_MATH_EXTRA_MAYOR_ 12
		#define LLANYLIB_MATH_EXTRA_MINOR_ 0

	#endif // LLANYLIB_MATH_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
