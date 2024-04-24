//////////////////////////////////////////////
//	color.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#ifndef LLANYLIB_EXPRESIONS_COLOR_HPP_
#define LLANYLIB_EXPRESIONS_COLOR_HPP_

#include "../StringView.hpp"

namespace llcpp {
namespace color {

// Text colors
constexpr auto RESET = StringView("\033[0m");
constexpr auto BLACK = StringView("\033[30m");
constexpr auto RED = StringView("\033[31m");
constexpr auto GREEN = StringView("\033[32m");
constexpr auto YELLOW = StringView("\033[33m");
constexpr auto BLUE = StringView("\033[34m");
constexpr auto MAGENTA = StringView("\033[35m");
constexpr auto CYAN = StringView("\033[36m");
constexpr auto WHITE = StringView("\033[37m");

// Background colors
constexpr auto BG_RESET = StringView("\033[49m");
constexpr auto BG_BLACK = StringView("\033[40m");
constexpr auto BG_RED = StringView("\033[41m");
constexpr auto BG_GREEN = StringView("\033[42m");
constexpr auto BG_YELLOW = StringView("\033[43m");
constexpr auto BG_BLUE = StringView("\033[44m");
constexpr auto BG_MAGENTA = StringView("\033[45m");
constexpr auto BG_CYAN = StringView("\033[46m");
constexpr auto BG_WHITE = StringView("\033[47m");

} // namespace color
} // namespace llcpp

#endif // LLANYLIB_EXPRESIONS_COLOR_HPP_
