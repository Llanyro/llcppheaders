//////////////////////////////////////////////
//	hash.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_HASH_INCOMPLETE_HPP_)
	#if LLANYLIB_HASH_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_HASH_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "hash.hpp(incomplete) version error!"
		#else
			#error "hash.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_HASH_INCOMPLETE_MAYOR_ || LLANYLIB_HASH_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_HASH_INCOMPLETE_HPP_)
	#define LLANYLIB_HASH_INCOMPLETE_HPP_
	#define LLANYLIB_HASH_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_HASH_INCOMPLETE_MINOR_ 0

#elif defined(LLANYLIB_HASH_HPP_)
	#if LLANYLIB_HASH_MAYOR_ != 12 || LLANYLIB_HASH_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "hash.hpp version error!"
		#else
			#error "hash.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_HASH_MAYOR_ || LLANYLIB_HASH_MINOR_

#else
	#define LLANYLIB_HASH_HPP_
	#define LLANYLIB_HASH_MAYOR_ 12
	#define LLANYLIB_HASH_MINOR_ 0

#include "concepts.hpp"

namespace llcpp {
namespace meta {
namespace concepts {
namespace hash {

template<class Array, class byte>
concept IsValidArray = requires (Array arr) {
	requires
		::llcpp::meta::concepts::signature::HasBegin<Array, byte*>
		|| ::llcpp::meta::concepts::signature::HasBegin<Array, const byte*>;
	requires
		::llcpp::meta::concepts::signature::HasSize<Array, usize>
		|| ::llcpp::meta::concepts::signature::HasSize<Array, usize>;
};

} // namespace hash
} // namespace concepts
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASH_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
