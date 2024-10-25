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

struct EmptyStruct	{ using _MyType = EmptyStruct; };
class Emptyclass	{ using _MyType = Emptyclass; };

enum class Position : u8 {
	Idle	= 0,
	Unknown = static_cast<u8>(-1),

	// Base
	Left			= (1 << 0),
	Right			= (1 << 1),
	Up				= (1 << 2),
	Down			= (1 << 3),
	Front			= (1 << 4),
	Back			= (1 << 5),

	// Pair Combinations
	LeftUp			= Left	| Up,
	LeftDown		= Left	| Down,
	LeftFront		= Left	| Front,
	LeftBack		= Left	| Back,

	RightUp			= Right	| Up,
	RightDown		= Right	| Down,
	RightFront		= Right	| Front,
	RightBack		= Right	| Back,

	UpFront			= Up	| Front,
	UpBack			= Up	| Back,
	DownFront		= Down	| Front,
	DownBack		= Down	| Back,

	// Triple Combinations
	LeftUpFront		= Left	| Up	| Front,
	LeftUpBack		= Left	| Up	| Back,
	LeftDownFront	= Left	| Down	| Front,
	LeftDownBack	= Left	| Down	| Back,

	RightUpFront	= Right | Up	| Front,
	RightUpBack		= Right | Up	| Back,
	RightDownFront	= Right | Down	| Front,
	RightDownBack	= Right | Down	| Back
};

namespace meta {

struct function_attributes_t {
	// Class related
	using _MyType = function_attributes_t;

	// Attributes
	ll_bool_t CONST			: 1;
	ll_bool_t NOEXCEPTION	: 1;
};

using StandardComparation = std::strong_ordering;

template<class T>
class ConstArray;
template<class T>
class Array;

using ConstStr	= ConstArray<ll_char_t>;
using ConstwStr	= ConstArray<ll_wchar_t>;
using Str		= Array<ll_char_t>;
using wStr		= Array<ll_wchar_t>;

template<class T, u64 _EXTENSION, ll_bool_t _IS_SIGNED>
class Integer;

} // namespace meta

//using len_t	= meta::traits::Integer<1>;	// Used to count things (natural number)

// Unsigned
using u128 = std::pair<u64, u64>;
using u256 = std::pair<u128, u128>;

// Signed
using i128 = std::pair<i64, i64>;
using i256 = std::pair<i128, i128>;

// Floating-point
using f256 = std::pair<f128, f128>;

} // namespace llcpp

#endif // LLANYLIB_TYPESBASEEXTRA_HPP_
