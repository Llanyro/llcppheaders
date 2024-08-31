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

// Simplified Signed
using i128				= llcpp::simplest_container<i64>;
using i256				= llcpp::simplest_container<i128>;

// Simplified Unsigned
using ui128				= llcpp::simplest_container<ui64>;
using ui256				= llcpp::simplest_container<ui128>;

// BytesTypes
using size_bytes128_t	= ui128;
using size_bytes256_t	= ui256;

using b128				= size_bytes128_t;
using b256				= size_bytes256_t;

namespace llcpp {

__LL_INLINE__ constexpr void IGNORE(...) {}

#pragma region Expresions
constexpr ui8 ZERO_UI8 = 0u;
constexpr ui16 ZERO_UI16 = 0u;
constexpr ui32 ZERO_UI32 = 0u;
constexpr ui64 ZERO_UI64 = 0ull;

constexpr i8 ZERO_I8 = 0;
constexpr i16 ZERO_I16 = 0;
constexpr i32 ZERO_I32 = 0;
constexpr i64 ZERO_I64 = 0ll;

constexpr f32 ZERO_F32 = 0.0f;
constexpr f64 ZERO_F64 = 0.0;
constexpr f128 ZERO_F128 = 0.0l;

constexpr cmp_t ZERO_CMP = ZERO_I32;

__LL_VAR_INLINE__ constexpr Boolean BOOLEAN_FALSE = false;
__LL_VAR_INLINE__ constexpr Boolean BOOLEAN_TRUE = true;
__LL_VAR_INLINE__ constexpr Boolean BOOLEAN_INVALID = Boolean::enum_bool::INVALID;
__LL_VAR_INLINE__ constexpr Boolean BOOLEAN_UNKNOWN_BOOL = Boolean::enum_bool::UNKNOWN;

__LL_VAR_INLINE__ constexpr ll_bool_t FALSE = false;
__LL_VAR_INLINE__ constexpr ll_bool_t TRUE = true;

namespace meta {
namespace algorithm {

constexpr len_t MAX_LIST_SIZE = static_cast<len_t>(-1);
constexpr len_t npos = MAX_LIST_SIZE;

} // namespace algorithm
} // namespace meta

#pragma endregion
#pragma region Types
namespace meta {

#pragma endregion

namespace functional {

using Compare			= cmp_t(*)(const void* __t1, const void* __t2) noexcept;
using CompareBool		= ll_bool_t(*)(const void* __t1, const void* __t2) noexcept;
using CompareExtra		= cmp_t(*)(const void* __t1, const void* __t2, void* __extra__) noexcept;
using CompareBoolExtra	= ll_bool_t(*)(const void* __t1, const void* __t2, void* __extra__) noexcept;

namespace classic {
template<class T, class U = T>  using Compare		= cmp_t(*)(T __t1, U __t2) noexcept;
template<class T, class U = T>  using CompareBool	= ll_bool_t(*)(T __t1, U __t2) noexcept;
template<class T, class U = T>  using SwapFunction	= void(*)(T& __t1, U& __t2) noexcept;
template<class T, class U = T&> using SetFunction	= void(*)(T& __t1, U __t2) noexcept;

} // namespace classic
namespace lambda {

template<class T, class U = T>  using Compare		= std::function<cmp_t(T __t1, U __t2)>;
template<class T, class U = T>  using CompareBool	= std::function<ll_bool_t(T __t1, U __t2)>;
template<class T, class U = T>  using SwapFunction	= std::function<void(T& __t1, U& __t2)>;
template<class T, class U = T&> using SetFunction	= std::function<void(T& __t1, U __t2)>;

template<class T> using SearchFunction				= std::function<cmp_t(T __t1)>;
template<class T> using SearchFunctionBool			= std::function<ll_bool_t(T __t1)>;

} // namespace lambda
} // namespace functional
} // namespace meta

namespace fnc_clss = meta::functional::classic;
namespace fnc_lmb = meta::functional::lambda;

} // namespace llcpp

#endif // LLANYLIB_TYPES_HPP_
