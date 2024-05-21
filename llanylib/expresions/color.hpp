//////////////////////////////////////////////
//	color.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_COLOR_HPP_) // Guard && version protector
	#if LLANYLIB_COLOR_MAYOR_ != 5 || LLANYLIB_COLOR_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "color.hpp version error!"
		#else
			#error "color.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_COLOR_MAYOR_ || LLANYLIB_COLOR_MINOR_

#else !defined(LLANYLIB_COLOR_HPP_)
#define LLANYLIB_COLOR_HPP_
#define LLANYLIB_COLOR_MAYOR_ 5
#define LLANYLIB_COLOR_MINOR_ 0

#include "../StringView.hpp"

namespace llcpp {
namespace meta {
namespace color {

constexpr auto RESET = make_StringView("\033[0m");
constexpr auto BLACK = make_StringView("\033[30m");
constexpr auto RED = make_StringView("\033[31m");
constexpr auto GREEN = make_StringView("\033[32m");
constexpr auto YELLOW = make_StringView("\033[33m");
constexpr auto BLUE = make_StringView("\033[34m");
constexpr auto MAGENTA = make_StringView("\033[35m");
constexpr auto CYAN = make_StringView("\033[36m");
constexpr auto WHITE = make_StringView("\033[37m");

constexpr auto BG_RESET = make_StringView("\033[49m");
constexpr auto BG_BLACK = make_StringView("\033[40m");
constexpr auto BG_RED = make_StringView("\033[41m");
constexpr auto BG_GREEN = make_StringView("\033[42m");
constexpr auto BG_YELLOW = make_StringView("\033[43m");
constexpr auto BG_BLUE = make_StringView("\033[44m");
constexpr auto BG_MAGENTA = make_StringView("\033[45m");
constexpr auto BG_CYAN = make_StringView("\033[46m");
constexpr auto BG_WHITE = make_StringView("\033[47m");

constexpr auto DEBUG_WARNING = BG_YELLOW;
constexpr auto DEBUG_ERROR = BG_RED;
constexpr auto DEBUG_MESSAGE = BG_CYAN;

namespace wide {

constexpr auto RESET = make_StringView(L"\033[0m");
constexpr auto BLACK = make_StringView(L"\033[30m");
constexpr auto RED = make_StringView(L"\033[31m");
constexpr auto GREEN = make_StringView(L"\033[32m");
constexpr auto YELLOW = make_StringView(L"\033[33m");
constexpr auto BLUE = make_StringView(L"\033[34m");
constexpr auto MAGENTA = make_StringView(L"\033[35m");
constexpr auto CYAN = make_StringView(L"\033[36m");
constexpr auto WHITE = make_StringView(L"\033[37m");

constexpr auto BG_RESET = make_StringView(L"\033[49m");
constexpr auto BG_BLACK = make_StringView(L"\033[40m");
constexpr auto BG_RED = make_StringView(L"\033[41m");
constexpr auto BG_GREEN = make_StringView(L"\033[42m");
constexpr auto BG_YELLOW = make_StringView(L"\033[43m");
constexpr auto BG_BLUE = make_StringView(L"\033[44m");
constexpr auto BG_MAGENTA = make_StringView(L"\033[45m");
constexpr auto BG_CYAN = make_StringView(L"\033[46m");
constexpr auto BG_WHITE = make_StringView(L"\033[47m");

constexpr auto DEBUG_WARNING = BG_YELLOW;
constexpr auto DEBUG_ERROR = BG_RED;
constexpr auto DEBUG_MESSAGE = BG_CYAN;

} // namespace wide
} // namespace color
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXPRESIONS_COLOR_HPP_
