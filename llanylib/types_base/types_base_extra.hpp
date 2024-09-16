//////////////////////////////////////////////
//	types_base_extra.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPESBASEEXTRA_HPP_) // Guard && version protector
	#if LLANYLIB_TYPESBASEEXTRA_MAYOR_ != 10 || LLANYLIB_TYPESBASEEXTRA_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "types_base_extra.hpp version error!"
		#else
			#error "types_base_extra.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TYPESBASEEXTRA_MAYOR_ || LLANYLIB_TYPESBASEEXTRA_MINOR_

#else !defined(LLANYLIB_TYPESBASEEXTRA_HPP_)
#define LLANYLIB_TYPESBASEEXTRA_HPP_
#define LLANYLIB_TYPESBASEEXTRA_MAYOR_ 10
#define LLANYLIB_TYPESBASEEXTRA_MINOR_ 0

#include "Boolean.hpp"
#include "Cluster.hpp"

namespace llcpp {

struct EmptyStruct {};
class Emptyclass {};

enum class Position {
	Unknown,
	Left, Right, Up, Down
};

namespace meta {

using StandardComparation = std::strong_ordering;

template<class T>
class ConstArray;
template<class T>
class Array;

using ConstStr	= ConstArray<ll_char_t>;
using ConstwStr	= ConstArray<ll_wchar_t>;
using Str		= Array<ll_char_t>;
using wStr		= Array<ll_wchar_t>;

template<u64 _EXTENSION>
class Integer;

} // namespace meta

//using len_t	= meta::traits::Integer<1>;	// Used to count things (natural number)

// Unsigned
using u128 = meta::Integer<1>;
using u256 = std::pair<u128, u128>;

// Signed
using i128 = std::pair<i64, i64>;
using i256 = std::pair<i128, i128>;

// Floating-point
using f256 = std::pair<f128, f128>;

} // namespace llcpp

#endif // LLANYLIB_TYPESBASEEXTRA_HPP_
