//////////////////////////////////////////////
//	TypeID.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPEID_HPP_) && defined(LLANYLIB_TYPEID_TYPEID_HPP_)
	#if LLANYLIB_TYPEID_TYPEID_MAYOR_ != 12 || LLANYLIB_TYPEID_TYPEID_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "TypeID.hpp(incomplete) version error!"
		#else
			#error "TypeID.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPEID_TYPEID_MAYOR_ || LLANYLIB_TYPEID_TYPEID_MINOR_

#elif defined(LLANYLIB_TYPEID_HPP_) && !defined(LLANYLIB_TYPEID_TYPEID_HPP_)
	#define LLANYLIB_TYPEID_TYPEID_HPP_
	#define LLANYLIB_TYPEID_TYPEID_MAYOR_ 12
	#define LLANYLIB_TYPEID_TYPEID_MINOR_ 0


#elif defined(LLANYLIB_TYPEID_HPP_)
	#if LLANYLIB_TYPEID_MAYOR_ != 12 || LLANYLIB_TYPEID_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "TypeID.hpp version error!"
		#else
			#error "TypeID.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPEID_MAYOR_ || LLANYLIB_TYPEID_MINOR_

#else
	#define LLANYLIB_TYPEID_HPP_
	#define LLANYLIB_TYPEID_MAYOR_ 12
	#define LLANYLIB_TYPEID_MINOR_ 0

#include "../traits_base/type_traits_extended.hpp"

namespace llcpp {
namespace meta {
namespace utils {

template<class ArrayType, class HashType = u64>
using TypeID = ::std::pair<ArrayType, HashType>;

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPEID_HPP_
