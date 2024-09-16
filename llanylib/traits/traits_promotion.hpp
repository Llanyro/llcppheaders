//////////////////////////////////////////////
//	traits.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSPROMOTION_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSPROMOTION_MAYOR_ != 10 || LLANYLIB_TRAITSPROMOTION_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits.hpp version error!"
		#else
			#error "traits.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSPROMOTION_MAYOR_ || LLANYLIB_TRAITSPROMOTION_MINOR_

#else !defined(LLANYLIB_TRAITSPROMOTION_HPP_)
#define LLANYLIB_TRAITSPROMOTION_HPP_
#define LLANYLIB_TRAITSPROMOTION_MAYOR_ 10
#define LLANYLIB_TRAITSPROMOTION_MINOR_ 0

#define LL_TRAITSPROMOTION_TEST

#include "traits_checker.hpp"

namespace llcpp {
namespace meta {
namespace traits {
namespace __traits__ {

template<class _T, ll_bool_t _PROMOTE>
struct type_promotion {
	// Class related
	using _MyType = type_promotion;

	// Types and enums
	using T = _T;

	template<class _U> struct promote_type	{ using type = _U; };
	template<> struct promote_type<i8>		{ using type = std::conditional_t<_PROMOTE, i16, i8>; };
	template<> struct promote_type<i16>		{ using type = std::conditional_t<_PROMOTE, i32, i8>; };
	template<> struct promote_type<i32>		{ using type = std::conditional_t<_PROMOTE, i64, i16>; };
	template<> struct promote_type<i64>		{ using type = std::conditional_t<_PROMOTE, i128, i32>; };
	template<> struct promote_type<i128>	{ using type = std::conditional_t<_PROMOTE, i256, i64>; };
	template<> struct promote_type<i256>	{ using type = std::conditional_t<_PROMOTE, i256, i128>; };

	template<> struct promote_type<u8>		{ using type = std::conditional_t<_PROMOTE, u16, u8>; };
	template<> struct promote_type<u16>	{ using type = std::conditional_t<_PROMOTE, u32, u8>; };
	template<> struct promote_type<u32>	{ using type = std::conditional_t<_PROMOTE, u64, u16>; };
	template<> struct promote_type<u64>	{ using type = std::conditional_t<_PROMOTE, u128, u32>; };
	template<> struct promote_type<u128>	{ using type = std::conditional_t<_PROMOTE, u256, u64>; };
	template<> struct promote_type<u256>	{ using type = std::conditional_t<_PROMOTE, u256, u128>; };

	template<> struct promote_type<f32>		{ using type = std::conditional_t<_PROMOTE, f64, f32>; };
	template<> struct promote_type<f64>		{ using type = std::conditional_t<_PROMOTE, f128, f32>; };
	template<> struct promote_type<f128>	{ using type = std::conditional_t<_PROMOTE, f128, f64>; };

	using type = promote_type<_T>::type;

	// Expresions
	static constexpr ll_bool_t PROMOTE = _PROMOTE;
};

} // namespace __traits__

template<class _T, ll_bool_t _PROMOTE>
struct type_promotion {
	// Class related
	using _MyType	= type_promotion;

	// Types and enums
	using T			= _T;
	using type		= traits::__traits__::type_promotion<_T, _PROMOTE>::type;

	// Expresions
	static constexpr ll_bool_t PROMOTE = _PROMOTE;

	// Asserts
	static_assert(traits::is_valid_type_checker_v<_T>,
		"type_checker<T> detected an invalid type!");
};

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSPROMOTION_HPP_
