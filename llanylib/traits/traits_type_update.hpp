//////////////////////////////////////////////
//	traits_type_update.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSTYPEUPDATE_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSTYPEUPDATE_MAYOR_ != 10 || LLANYLIB_TRAITSTYPEUPDATE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_type_update.hpp version error!"
		#else
			#error "traits_type_update.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSTYPEUPDATE_MAYOR_ || LLANYLIB_TRAITSTYPEUPDATE_MINOR_

#else !defined(LLANYLIB_TRAITSTYPEUPDATE_HPP_)
#define LLANYLIB_TRAITSTYPEUPDATE_HPP_
#define LLANYLIB_TRAITSTYPEUPDATE_MAYOR_ 10
#define LLANYLIB_TRAITSTYPEUPDATE_MINOR_ 0

#include "traits_selection.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<class T, ll_bool_t PROMOTE = llcpp::TRUE>
using type_promotion = traits::type_selection<T>::get_conincidence<
	T,
	traits::double_type_container<i8,	traits::conditional_t<PROMOTE, i16, i8>>,
	traits::double_type_container<i16,	traits::conditional_t<PROMOTE, i32, i8>>,
	traits::double_type_container<i32,	traits::conditional_t<PROMOTE, i64, i16>>,
	traits::double_type_container<i64,	traits::conditional_t<PROMOTE, i128, i32>>,
	traits::double_type_container<i128, traits::conditional_t<PROMOTE, i256, i64>>,
	traits::double_type_container<i256, traits::conditional_t<PROMOTE, i256, i128>>,

	traits::double_type_container<u8,	traits::conditional_t<PROMOTE, u16, u8>>,
	traits::double_type_container<u16,	traits::conditional_t<PROMOTE, u32, u8>>,
	traits::double_type_container<u32,	traits::conditional_t<PROMOTE, u64, u16>>,
	traits::double_type_container<u64,	traits::conditional_t<PROMOTE, u128, u32>>,
	traits::double_type_container<u128,	traits::conditional_t<PROMOTE, u256, u64>>,
	traits::double_type_container<u256,	traits::conditional_t<PROMOTE, u256, u128>>,

	traits::double_type_container<f32,	traits::conditional_t<PROMOTE, f64, f32>>,
	traits::double_type_container<f64,	traits::conditional_t<PROMOTE, f128, f32>>,
	traits::double_type_container<f128,	traits::conditional_t<PROMOTE, f128, f64>>
>;

template<class T, ll_bool_t SIGNALIZE = llcpp::TRUE>
using type_signed = traits::type_selection<T>::get_conincidence <
	T,
	traits::double_type_container<i8,	traits::conditional_t<SIGNALIZE, i8, u8>>,
	traits::double_type_container<i16,	traits::conditional_t<SIGNALIZE, i16, u16>>,
	traits::double_type_container<i32,	traits::conditional_t<SIGNALIZE, i32, u32>>,
	traits::double_type_container<i64,	traits::conditional_t<SIGNALIZE, i64, u64>>,
	traits::double_type_container<i128, traits::conditional_t<SIGNALIZE, i128, u128>>,
	traits::double_type_container<i256, traits::conditional_t<SIGNALIZE, i256, u256>>,

	traits::double_type_container<u8,	traits::conditional_t<SIGNALIZE, i8, u8>>,
	traits::double_type_container<u16,	traits::conditional_t<SIGNALIZE, i16, u16>>,
	traits::double_type_container<u32,	traits::conditional_t<SIGNALIZE, i32, u32>>,
	traits::double_type_container<u64,	traits::conditional_t<SIGNALIZE, i64, u64>>,
	traits::double_type_container<u128,	traits::conditional_t<SIGNALIZE, i128, u128>>,
	traits::double_type_container<u256,	traits::conditional_t<SIGNALIZE, i256, u256>>
>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSTYPEUPDATE_HPP_
