//////////////////////////////////////////////
//	ClusterEnum.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CLUSTERENUM_INCOMPLETE_HPP_)
	#if LLANYLIB_CLUSTERENUM_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_CLUSTERENUM_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "ClusterEnum.hpp(incomplete) version error!"
		#else
			#error "ClusterEnum.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CLUSTERENUM_INCOMPLETE_MAYOR_ || LLANYLIB_CLUSTERENUM_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CLUSTERENUM_INCOMPLETE_HPP_)
#define LLANYLIB_CLUSTERENUM_INCOMPLETE_HPP_
#define LLANYLIB_CLUSTERENUM_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_CLUSTERENUM_INCOMPLETE_MINOR_ 0

#include "types_base.hpp"

namespace llcpp {
namespace meta {

enum class ClusterType : u8;

} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_CLUSTERENUM_HPP_)
	#if LLANYLIB_CLUSTERENUM_MAYOR_ != 11 || LLANYLIB_CLUSTERENUM_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "ClusterEnum.hpp version error!"
		#else
			#error "ClusterEnum.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CLUSTERENUM_MAYOR_ || LLANYLIB_CLUSTERENUM_MINOR_

#else
#define LLANYLIB_CLUSTERENUM_HPP_
#define LLANYLIB_CLUSTERENUM_MAYOR_ 11
#define LLANYLIB_CLUSTERENUM_MINOR_ 0

#include "types_base.hpp"

namespace llcpp {
namespace meta {

enum class ClusterType : u8 {
	Cluster,
	Half,

	Unknown = static_cast<u8>(-1)
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CLUSTERENUM_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
