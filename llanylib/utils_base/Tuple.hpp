//////////////////////////////////////////////
//	Tuple.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TUPLE_INCOMPLETE_HPP_)
	#if LLANYLIB_TUPLE_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TUPLE_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Tuple.hpp(incomplete) version error!"
		#else
			#error "Tuple.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TUPLE_INCOMPLETE_MAYOR_ || LLANYLIB_TUPLE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TUPLE_INCOMPLETE_HPP_)
	#define LLANYLIB_TUPLE_INCOMPLETE_HPP_
	#define LLANYLIB_TUPLE_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_TUPLE_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_TUPLE_HPP_)
	#if LLANYLIB_TUPLE_MAYOR_ != 11 || LLANYLIB_TUPLE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Tuple.hpp version error!"
		#else
			#error "Tuple.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TUPLE_MAYOR_ || LLANYLIB_TUPLE_MINOR_

#else
	#define LLANYLIB_TUPLE_HPP_
	#define LLANYLIB_TUPLE_MAYOR_ 11
	#define LLANYLIB_TUPLE_MINOR_ 0

#include "../traits_base/traits_parameter_pack.hpp"

namespace llcpp {
namespace meta {
namespace utils {

template<class... Args>
class ParameterPackObjects {

};

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TUPLE_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_TUPLE_EXTRA_HPP_)
		#if LLANYLIB_TUPLE_EXTRA_MAYOR_ != 11 || LLANYLIB_TUPLE_EXTRA_MINOR_ < 0
			#if defined(__LL_REAL_CXX23)
				#warning "Tuple.hpp(extra) version error!"
			#else
				#error "Tuple.hpp(extra) version error!"
			#endif // __LL_REAL_CXX23
		#endif // LLANYLIB_TUPLE_EXTRA_MAYOR_ || LLANYLIB_TUPLE_EXTRA_MINOR_

	#else
		#define LLANYLIB_TUPLE_EXTRA_HPP_
		#define LLANYLIB_TUPLE_EXTRA_MAYOR_ 11
		#define LLANYLIB_TUPLE_EXTRA_MINOR_ 0

	#endif // LLANYLIB_TUPLE_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
