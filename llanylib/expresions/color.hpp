//////////////////////////////////////////////
//	color.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.3							//
//////////////////////////////////////////////

#if defined(LLANYLIB_EXPRESIONS_COLOR_HPP_) // Guard && version protector
	#if LLANYLIB_EXPRESIONS_COLOR_MAYOR_ != 7 || LLANYLIB_EXPRESIONS_COLOR_MINOR_ < 3
		#if defined(LL_REAL_CXX23)
			#warning "color.hpp version error!"
		#else
			#error "color.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_EXPRESIONS_COLOR_MAYOR_ || LLANYLIB_EXPRESIONS_COLOR_MINOR_

#else !defined(LLANYLIB_EXPRESIONS_COLOR_HPP_)
#define LLANYLIB_EXPRESIONS_COLOR_HPP_
#define LLANYLIB_EXPRESIONS_COLOR_MAYOR_ 7
#define LLANYLIB_EXPRESIONS_COLOR_MINOR_ 3

#include "../ArrayView.hpp"

namespace llcpp {
namespace meta {
namespace color {

__LL_VAR_INLINE__ constexpr auto RESET = make_StringView("\033[0m");
__LL_VAR_INLINE__ constexpr auto BLACK = make_StringView("\033[30m");
__LL_VAR_INLINE__ constexpr auto RED = make_StringView("\033[31m");
__LL_VAR_INLINE__ constexpr auto GREEN = make_StringView("\033[32m");
__LL_VAR_INLINE__ constexpr auto YELLOW = make_StringView("\033[33m");
__LL_VAR_INLINE__ constexpr auto BLUE = make_StringView("\033[34m");
__LL_VAR_INLINE__ constexpr auto MAGENTA = make_StringView("\033[35m");
__LL_VAR_INLINE__ constexpr auto CYAN = make_StringView("\033[36m");
__LL_VAR_INLINE__ constexpr auto WHITE = make_StringView("\033[37m");

__LL_VAR_INLINE__ constexpr auto BG_RESET = make_StringView("\033[49m");
__LL_VAR_INLINE__ constexpr auto BG_BLACK = make_StringView("\033[40m");
__LL_VAR_INLINE__ constexpr auto BG_RED = make_StringView("\033[41m");
__LL_VAR_INLINE__ constexpr auto BG_GREEN = make_StringView("\033[42m");
__LL_VAR_INLINE__ constexpr auto BG_YELLOW = make_StringView("\033[43m");
__LL_VAR_INLINE__ constexpr auto BG_BLUE = make_StringView("\033[44m");
__LL_VAR_INLINE__ constexpr auto BG_MAGENTA = make_StringView("\033[45m");
__LL_VAR_INLINE__ constexpr auto BG_CYAN = make_StringView("\033[46m");
__LL_VAR_INLINE__ constexpr auto BG_WHITE = make_StringView("\033[47m");

__LL_VAR_INLINE__ constexpr auto DEBUG_WARNING = BG_YELLOW;
__LL_VAR_INLINE__ constexpr auto DEBUG_ERROR = BG_RED;
__LL_VAR_INLINE__ constexpr auto DEBUG_MESSAGE = BG_CYAN;

namespace wide {

__LL_VAR_INLINE__ constexpr auto RESET = make_StringView(L"\033[0m");
__LL_VAR_INLINE__ constexpr auto BLACK = make_StringView(L"\033[30m");
__LL_VAR_INLINE__ constexpr auto RED = make_StringView(L"\033[31m");
__LL_VAR_INLINE__ constexpr auto GREEN = make_StringView(L"\033[32m");
__LL_VAR_INLINE__ constexpr auto YELLOW = make_StringView(L"\033[33m");
__LL_VAR_INLINE__ constexpr auto BLUE = make_StringView(L"\033[34m");
__LL_VAR_INLINE__ constexpr auto MAGENTA = make_StringView(L"\033[35m");
__LL_VAR_INLINE__ constexpr auto CYAN = make_StringView(L"\033[36m");
__LL_VAR_INLINE__ constexpr auto WHITE = make_StringView(L"\033[37m");

__LL_VAR_INLINE__ constexpr auto BG_RESET = make_StringView(L"\033[49m");
__LL_VAR_INLINE__ constexpr auto BG_BLACK = make_StringView(L"\033[40m");
__LL_VAR_INLINE__ constexpr auto BG_RED = make_StringView(L"\033[41m");
__LL_VAR_INLINE__ constexpr auto BG_GREEN = make_StringView(L"\033[42m");
__LL_VAR_INLINE__ constexpr auto BG_YELLOW = make_StringView(L"\033[43m");
__LL_VAR_INLINE__ constexpr auto BG_BLUE = make_StringView(L"\033[44m");
__LL_VAR_INLINE__ constexpr auto BG_MAGENTA = make_StringView(L"\033[45m");
__LL_VAR_INLINE__ constexpr auto BG_CYAN = make_StringView(L"\033[46m");
__LL_VAR_INLINE__ constexpr auto BG_WHITE = make_StringView(L"\033[47m");

__LL_VAR_INLINE__ constexpr auto DEBUG_WARNING = BG_YELLOW;
__LL_VAR_INLINE__ constexpr auto DEBUG_ERROR = BG_RED;
__LL_VAR_INLINE__ constexpr auto DEBUG_MESSAGE = BG_CYAN;

} // namespace wide
} // namespace color
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXPRESIONS_COLOR_HPP_
