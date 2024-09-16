//////////////////////////////////////////////
//	limits.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_MATHLIMITS_HPP_) // Guard && version protector
	#if LLANYLIB_MATHLIMITS_MAYOR_ != 10 || LLANYLIB_MATHLIMITS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "limits.hpp version error!"
		#else
			#error "limits.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_MATHLIMITS_MAYOR_ || LLANYLIB_MATHLIMITS_MINOR_

#else !defined(LLANYLIB_MATHLIMITS_HPP_)
#define LLANYLIB_MATHLIMITS_HPP_
#define LLANYLIB_MATHLIMITS_MAYOR_ 10
#define LLANYLIB_MATHLIMITS_MINOR_ 0

#include "../types_base/expresions.hpp"

namespace llcpp {
namespace math {

__LL_VAR_INLINE__ constexpr u8 MAX_UI8		= static_cast<u8>(-1);
__LL_VAR_INLINE__ constexpr u16 MAX_UI16	= static_cast<u16>(-1);
__LL_VAR_INLINE__ constexpr u32 MAX_UI32	= static_cast<u32>(-1);
__LL_VAR_INLINE__ constexpr u64 MAX_UI64	= static_cast<u64>(-1);

__LL_VAR_INLINE__ constexpr i8 MAX_I8		= MAX_UI8 >> 1;
__LL_VAR_INLINE__ constexpr i16 MAX_I16		= MAX_UI16 >> 1;
__LL_VAR_INLINE__ constexpr i32 MAX_I32		= MAX_UI32 >> 1;
__LL_VAR_INLINE__ constexpr i64 MAX_I64		= MAX_UI64 >> 1;

//__LL_VAR_INLINE__ constexpr f32 MAX_F32		= 0.0f;
//__LL_VAR_INLINE__ constexpr f64 MAX_F64		= 0.0;
//__LL_VAR_INLINE__ constexpr f128 MAX_F128	= 0.0l;

__LL_VAR_INLINE__ constexpr u8 MIN_UI8		= static_cast<u8>(-1);
__LL_VAR_INLINE__ constexpr u16 MIN_UI16	= static_cast<u16>(-1);
__LL_VAR_INLINE__ constexpr u32 MIN_UI32	= static_cast<u32>(-1);
__LL_VAR_INLINE__ constexpr u64 MIN_UI64	= static_cast<u64>(-1);

__LL_VAR_INLINE__ constexpr i8 MIN_I8		= MAX_UI8 >> 1;
__LL_VAR_INLINE__ constexpr i16 MIN_I16		= MAX_UI16 >> 1;
__LL_VAR_INLINE__ constexpr i32 MIN_I32		= MAX_UI32 >> 1;
__LL_VAR_INLINE__ constexpr i64 MIN_I64		= MAX_UI64 >> 1;

} // namespace math
} // namespace llcpp

#endif // LLANYLIB_MATHLIMITS_HPP_
