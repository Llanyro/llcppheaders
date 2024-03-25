/*
 *	color.hpp
 *
 *	Author: Francisco Julio Ruiz Fernandez
 *	Author: llanyro
 *
 *	Version: 4.2
 */

#ifndef LLANYLIB_EXPRESIONS_COLOR_HPP_
#define LLANYLIB_EXPRESIONS_COLOR_HPP_

#include "../ArrayView.hpp"

namespace llcpp {
namespace color {

// Text colors
constexpr ArrayView RESET = "\033[0m";
constexpr ArrayView BLACK = "\033[30m";
constexpr ArrayView RED = "\033[31m";
constexpr ArrayView GREEN = "\033[32m";
constexpr ArrayView YELLOW = "\033[33m";
constexpr ArrayView BLUE = "\033[34m";
constexpr ArrayView MAGENTA = "\033[35m";
constexpr ArrayView CYAN = "\033[36m";
constexpr ArrayView WHITE = "\033[37m";

// Background colors
constexpr ArrayView BG_RESET = "\033[49m";
constexpr ArrayView BG_BLACK = "\033[40m";
constexpr ArrayView BG_RED = "\033[41m";
constexpr ArrayView BG_GREEN = "\033[42m";
constexpr ArrayView BG_YELLOW = "\033[43m";
constexpr ArrayView BG_BLUE = "\033[44m";
constexpr ArrayView BG_MAGENTA = "\033[45m";
constexpr ArrayView BG_CYAN = "\033[46m";
constexpr ArrayView BG_WHITE = "\033[47m";

} // namespace color
} // namespace llcpp

#endif // LLANYLIB_EXPRESIONS_COLOR_HPP_
