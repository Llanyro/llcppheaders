//////////////////////////////////////////////
//	Position.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_POSITION_INCOMPLETE_HPP_)
	#if LLANYLIB_POSITION_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_POSITION_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Position.hpp(incomplete) version error!"
		#else
			#error "Position.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_POSITION_INCOMPLETE_MAYOR_ || LLANYLIB_POSITION_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_POSITION_INCOMPLETE_HPP_)
	#define LLANYLIB_POSITION_INCOMPLETE_HPP_
	#define LLANYLIB_POSITION_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_POSITION_INCOMPLETE_MINOR_ 0

#include "types.hpp"

namespace llcpp {
namespace misc {

enum class Position : u8;

} // namespace misc
} // namespace llcpp

#elif defined(LLANYLIB_POSITION_HPP_)
	#if LLANYLIB_POSITION_MAYOR_ != 12 || LLANYLIB_POSITION_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Position.hpp version error!"
		#else
			#error "Position.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_POSITION_MAYOR_ || LLANYLIB_POSITION_MINOR_

#else
	#define LLANYLIB_POSITION_HPP_
	#define LLANYLIB_POSITION_MAYOR_ 12
	#define LLANYLIB_POSITION_MINOR_ 0

#include "types.hpp"

namespace llcpp {
namespace misc {

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

} // namespace misc
} // namespace llcpp

#endif // LLANYLIB_POSITION_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
