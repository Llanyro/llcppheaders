//////////////////////////////////////////////
//	type_id.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPEID_HPP_) // Guard && version protector
	#if LLANYLIB_TYPEID_MAYOR_ != 12 || LLANYLIB_TYPEID_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "type_id.hpp version error!"
		#else
			#error "type_id.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPEID_MAYOR_ || LLANYLIB_TYPEID_MINOR_

#elif !defined(LLANYLIB_TYPEID_HPP_)
	#define LLANYLIB_TYPEID_HPP_
	#define LLANYLIB_TYPEID_MAYOR_ 12
	#define LLANYLIB_TYPEID_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/types.hpp>
#else
	#include "types.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace utils {

template<class ArrayType = ::llcpp::string, class HashType = ::llcpp::StandardHash>
using TypeID = ::llcpp::meta::pair<ArrayType, HashType>;

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPEID_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
