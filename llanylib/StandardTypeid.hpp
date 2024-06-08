//////////////////////////////////////////////
//	StandardTypeid.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_STANDARDTYPEID_HPP_) // Guard && version protector
	#if LLANYLIB_STANDARDTYPEID_MAYOR_ != 8 || LLANYLIB_STANDARDTYPEID_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "StandardTypeid.hpp version error!"
		#else
			#error "StandardTypeid.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_STANDARDTYPEID_MAYOR_ || LLANYLIB_STANDARDTYPEID_MINOR_

#else !defined(LLANYLIB_STANDARDTYPEID_HPP_)
#define LLANYLIB_STANDARDTYPEID_HPP_
#define LLANYLIB_STANDARDTYPEID_MAYOR_ 8
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

__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_UI8 = meta::STANDARD_TYPEID<ui8>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_UI16 = meta::STANDARD_TYPEID<ui16>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_UI32 = meta::STANDARD_TYPEID<ui32>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_UI64 = meta::STANDARD_TYPEID<ui64>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_I8 = meta::STANDARD_TYPEID<i8>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_I16 = meta::STANDARD_TYPEID<i16>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_I32 = meta::STANDARD_TYPEID<i32>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_I64 = meta::STANDARD_TYPEID<i64>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_F32 = meta::STANDARD_TYPEID<f32>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_F64 = meta::STANDARD_TYPEID<f64>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_F128 = meta::STANDARD_TYPEID<f128>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_HASH32 = meta::STANDARD_TYPEID<hash::Hash32>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_HASH64 = meta::STANDARD_TYPEID<hash::Hash64>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_HASH128 = meta::STANDARD_TYPEID<hash::Hash128>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_STRTYPEID = meta::STANDARD_TYPEID<StrTypeid>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid STANDARD_TYPEID_WSTRTYPEID = meta::STANDARD_TYPEID<wStrTypeid>();

template<class T>
__LL_NODISCARD__ constexpr meta::StrTypeid FAST_TYPEID() __LL_EXCEPT__ {
	return meta::StrTypeid(traits::getName<T>(), hash::FAST_StrPairHash64Function);
}
template<class T>
__LL_NODISCARD__ constexpr meta::wStrTypeid FAST_wTYPEID() __LL_EXCEPT__ {
	return meta::wStrTypeid(traits::getwName<T>(), hash::FAST_wStrPairHash64Function);
}

__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_UI8 = meta::FAST_TYPEID<ui8>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_UI16 = meta::FAST_TYPEID<ui16>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_UI32 = meta::FAST_TYPEID<ui32>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_UI64 = meta::FAST_TYPEID<ui64>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_I8 = meta::FAST_TYPEID<i8>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_I16 = meta::FAST_TYPEID<i16>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_I32 = meta::FAST_TYPEID<i32>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_I64 = meta::FAST_TYPEID<i64>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_F32 = meta::FAST_TYPEID<f32>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_F64 = meta::FAST_TYPEID<f64>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_F128 = meta::FAST_TYPEID<f128>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_HASH32 = meta::FAST_TYPEID<hash::Hash32>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_HASH64 = meta::FAST_TYPEID<hash::Hash64>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_HASH128 = meta::FAST_TYPEID<hash::Hash128>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_STRTYPEID = meta::FAST_TYPEID<StrTypeid>();
__LL_VAR_INLINE__ constexpr meta::StrTypeid FAST_TYPEID_WSTRTYPEID = meta::FAST_TYPEID<wStrTypeid>();

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_STANDARDTYPEID_HPP_
