//////////////////////////////////////////////
//	expresions.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPESEXPRESIONS_HPP_) // Guard && version protector
	#if LLANYLIB_TYPESEXPRESIONS_MAYOR_ != 10 || LLANYLIB_TYPESEXPRESIONS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "expresions.hpp version error!"
		#else
			#error "expresions.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TYPESEXPRESIONS_MAYOR_ || LLANYLIB_TYPESEXPRESIONS_MINOR_

#else !defined(LLANYLIB_TYPESEXPRESIONS_HPP_)
#define LLANYLIB_TYPESEXPRESIONS_HPP_
#define LLANYLIB_TYPESEXPRESIONS_MAYOR_ 10
#define LLANYLIB_TYPESEXPRESIONS_MINOR_ 0

#include "types_base_extra.hpp"

namespace llcpp {

//__LL_VAR_INLINE__ constexpr u8 ZERO_U8	= 0u;
//__LL_VAR_INLINE__ constexpr u16 ZERO_U16	= 0u;
//__LL_VAR_INLINE__ constexpr u32 ZERO_U32	= 0u;
//__LL_VAR_INLINE__ constexpr u64 ZERO_U64	= 0ull;
//
//__LL_VAR_INLINE__ constexpr i8 ZERO_I8		= 0;
//__LL_VAR_INLINE__ constexpr i16 ZERO_I16	= 0;
//__LL_VAR_INLINE__ constexpr i32 ZERO_I32	= 0;
//__LL_VAR_INLINE__ constexpr i64 ZERO_I64	= 0ll;
//
//__LL_VAR_INLINE__ constexpr f32 ZERO_F32	= 0.0f;
//__LL_VAR_INLINE__ constexpr f64 ZERO_F64	= 0.0;
//__LL_VAR_INLINE__ constexpr f128 ZERO_F128	= 0.0l;
//
//__LL_VAR_INLINE__ constexpr c_cmp_t ZERO_CMP	= ZERO_I32;

__LL_VAR_INLINE__ constexpr ll_bool_t FALSE		= false;
__LL_VAR_INLINE__ constexpr ll_bool_t TRUE		= true;

__LL_VAR_INLINE__ constexpr meta::Boolean BOOLEAN_FALSE			= FALSE;
__LL_VAR_INLINE__ constexpr meta::Boolean BOOLEAN_TRUE			= TRUE;
__LL_VAR_INLINE__ constexpr meta::Boolean BOOLEAN_INVALID		= meta::Boolean::enum_bool::INVALID;
__LL_VAR_INLINE__ constexpr meta::Boolean BOOLEAN_UNKNOWN_BOOL	= meta::Boolean::enum_bool::UNKNOWN;

namespace meta {
namespace functional {

__LL_VAR_INLINE__ constexpr meta::function_attributes_t CLASSIC				= { llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr meta::function_attributes_t CONST				= { llcpp::TRUE,  llcpp::FALSE };
__LL_VAR_INLINE__ constexpr meta::function_attributes_t NOEXCEPTION			= { llcpp::FALSE, llcpp::TRUE };
__LL_VAR_INLINE__ constexpr meta::function_attributes_t CONSTNOEXCEPTION	= { llcpp::TRUE,  llcpp::TRUE };

} // namespace functional
namespace algorithm {

__LL_VAR_INLINE__ constexpr u64 MAX_LIST_SIZE	= static_cast<u64>(-1);
__LL_VAR_INLINE__ constexpr u64 npos			= MAX_LIST_SIZE;

} // namespace algorithm
} // namespace meta

template<class... Args> __LL_INLINE__ constexpr void IGNORE(Args&&...) {}
template<class T>		__LL_INLINE__ constexpr void IGNORE(T&&...) {}
template<class>			__LL_INLINE__ constexpr void IGNORE() {}

} // namespace llcpp

#endif // LLANYLIB_TYPESEXPRESIONS_HPP_
