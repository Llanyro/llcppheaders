//////////////////////////////////////////////
//	StandardTypeid.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_STANDARDTYPEID_HPP_) // Guard && version protector
	#if LLANYLIB_STANDARDTYPEID_MAYOR_ != 7 || LLANYLIB_STANDARDTYPEID_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "StandardTypeid.hpp version error!"
		#else
			#error "StandardTypeid.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_STANDARDTYPEID_MAYOR_ || LLANYLIB_STANDARDTYPEID_MINOR_

#else !defined(LLANYLIB_STANDARDTYPEID_HPP_)
#define LLANYLIB_STANDARDTYPEID_HPP_
#define LLANYLIB_STANDARDTYPEID_MAYOR_ 7
#define LLANYLIB_STANDARDTYPEID_MINOR_ 0

#include "reflection.hpp"
#include "StandardHash.hpp"

namespace llcpp {
namespace meta {

template<class T>
__LL_NODISCARD__ constexpr meta::StrTypeid STANDARD_TYPEID() __LL_EXCEPT__ {
	return meta::StrTypeid(traits::getName<T>(), hash::STANDARD_StrPairHash64Function);
}
template<class T>
__LL_NODISCARD__ constexpr meta::wStrTypeid STANDARD_wTYPEID() __LL_EXCEPT__ {
	return meta::wStrTypeid(traits::getwName<T>(), hash::STANDARD_wStrPairHash64Function);
}

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_STANDARDTYPEID_HPP_
