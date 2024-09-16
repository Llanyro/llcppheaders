//////////////////////////////////////////////
//	types.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPES_HPP_) // Guard && version protector
	#if LLANYLIB_TYPES_MAYOR_ != 9 || LLANYLIB_TYPES_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "types.hpp version error!"
		#else
			#error "types.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_TYPES_MAYOR_ || LLANYLIB_TYPES_MINOR_

#else !defined(LLANYLIB_TYPES_HPP_)
#define LLANYLIB_TYPES_HPP_
#define LLANYLIB_TYPES_MAYOR_ 9
#define LLANYLIB_TYPES_MINOR_ 0

#include "Boolean.hpp"
#include "SimplestContainer.hpp"
#include "Cluster.hpp"

// Simplified Signed
using i128				= llcpp::meta::simplest_container<i64>;
using i256				= llcpp::meta::simplest_container<i128>;

// Simplified Unsigned
using ui128				= llcpp::meta::simplest_container<ui64>;
using ui256				= llcpp::meta::simplest_container<ui128>;

// BytesTypes
using size_bytes128_t	= ui128;
using size_bytes256_t	= ui256;

using b128				= size_bytes128_t;
using b256				= size_bytes256_t;

using f256				= llcpp::meta::simplest_container<f128>;

namespace llcpp {

#pragma region BasicTypeExpresions

__LL_VAR_INLINE__ constexpr ui128 ZERO_UI128 = ui128(ZERO_UI64, ZERO_UI64);
__LL_VAR_INLINE__ constexpr ui256 ZERO_UI256 = ui256(ZERO_UI128, ZERO_UI128);
__LL_VAR_INLINE__ constexpr i128 ZERO_I128 = i128(ZERO_I64, ZERO_I64);
__LL_VAR_INLINE__ constexpr i256 ZERO_I256 = i256(ZERO_I128, ZERO_I128);
__LL_VAR_INLINE__ constexpr f256 ZERO_F256 = f256(ZERO_F128, ZERO_F128);

#pragma endregion

namespace meta {

namespace hash {

template<class _T, _T _NULL_HASH>
class Hash;

using Hash8 = Hash<ui8, llcpp::ZERO_UI8>;
using Hash16 = Hash<ui16, llcpp::ZERO_UI16>;
using Hash32 = Hash<ui32, llcpp::ZERO_UI32>;
using Hash64 = Hash<ui64, llcpp::ZERO_UI64>;
using Hash128 = Hash<ui128, llcpp::ZERO_UI128>;
using Hash256 = Hash<ui256, llcpp::ZERO_UI256>;

using StandardHash = Hash64;

} // namespace hash

template<class CharType, class HashType>
class Typeid;
using StrTypeid		= Typeid<ll_char_t, hash::StandardHash>;
using wStrTypeid	= Typeid<ll_wchar_t, hash::StandardHash>;

} // namespace llcpp

#endif // LLANYLIB_TYPES_HPP_
