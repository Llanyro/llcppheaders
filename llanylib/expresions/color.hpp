//////////////////////////////////////////////
//	color.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_EXPRESIONS_COLOR_HPP_) // Guard && version protector
	#if LLANYLIB_EXPRESIONS_COLOR_MAYOR_ != 9 || LLANYLIB_EXPRESIONS_COLOR_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "color.hpp version error!"
		#else
			#error "color.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_EXPRESIONS_COLOR_MAYOR_ || LLANYLIB_EXPRESIONS_COLOR_MINOR_

#else !defined(LLANYLIB_EXPRESIONS_COLOR_HPP_)
#define LLANYLIB_EXPRESIONS_COLOR_HPP_
#define LLANYLIB_EXPRESIONS_COLOR_MAYOR_ 9
#define LLANYLIB_EXPRESIONS_COLOR_MINOR_ 0

#include "../types.hpp"

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4365) // ignore xmemory/atomic libs warnings
	#include <string_view>
	#pragma warning(pop)
#else
	#include <string_view>
#endif // WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace color {

__LL_VAR_INLINE__ constexpr std::string_view RESET = "\033[0m";
__LL_VAR_INLINE__ constexpr std::string_view BLACK = "\033[30m";
__LL_VAR_INLINE__ constexpr std::string_view RED = "\033[31m";
__LL_VAR_INLINE__ constexpr std::string_view GREEN = "\033[32m";
__LL_VAR_INLINE__ constexpr std::string_view YELLOW = "\033[33m";
__LL_VAR_INLINE__ constexpr std::string_view BLUE = "\033[34m";
__LL_VAR_INLINE__ constexpr std::string_view MAGENTA = "\033[35m";
__LL_VAR_INLINE__ constexpr std::string_view CYAN = "\033[36m";
__LL_VAR_INLINE__ constexpr std::string_view WHITE = "\033[37m";

__LL_VAR_INLINE__ constexpr std::string_view BG_RESET = "\033[49m";
__LL_VAR_INLINE__ constexpr std::string_view BG_BLACK = "\033[40m";
__LL_VAR_INLINE__ constexpr std::string_view BG_RED = "\033[41m";
__LL_VAR_INLINE__ constexpr std::string_view BG_GREEN = "\033[42m";
__LL_VAR_INLINE__ constexpr std::string_view BG_YELLOW = "\033[43m";
__LL_VAR_INLINE__ constexpr std::string_view BG_BLUE = "\033[44m";
__LL_VAR_INLINE__ constexpr std::string_view BG_MAGENTA = "\033[45m";
__LL_VAR_INLINE__ constexpr std::string_view BG_CYAN = "\033[46m";
__LL_VAR_INLINE__ constexpr std::string_view BG_WHITE = "\033[47m";

__LL_VAR_INLINE__ constexpr std::string_view DEBUG_WARNING = BG_YELLOW;
__LL_VAR_INLINE__ constexpr std::string_view DEBUG_ERROR = BG_RED;
__LL_VAR_INLINE__ constexpr std::string_view DEBUG_MESSAGE = BG_CYAN;

namespace wide {

__LL_VAR_INLINE__ constexpr std::wstring_view RESET = L"\033[0m";
__LL_VAR_INLINE__ constexpr std::wstring_view BLACK = L"\033[30m";
__LL_VAR_INLINE__ constexpr std::wstring_view RED = L"\033[31m";
__LL_VAR_INLINE__ constexpr std::wstring_view GREEN = L"\033[32m";
__LL_VAR_INLINE__ constexpr std::wstring_view YELLOW = L"\033[33m";
__LL_VAR_INLINE__ constexpr std::wstring_view BLUE = L"\033[34m";
__LL_VAR_INLINE__ constexpr std::wstring_view MAGENTA = L"\033[35m";
__LL_VAR_INLINE__ constexpr std::wstring_view CYAN = L"\033[36m";
__LL_VAR_INLINE__ constexpr std::wstring_view WHITE = L"\033[37m";

__LL_VAR_INLINE__ constexpr std::wstring_view BG_RESET = L"\033[49m";
__LL_VAR_INLINE__ constexpr std::wstring_view BG_BLACK = L"\033[40m";
__LL_VAR_INLINE__ constexpr std::wstring_view BG_RED = L"\033[41m";
__LL_VAR_INLINE__ constexpr std::wstring_view BG_GREEN = L"\033[42m";
__LL_VAR_INLINE__ constexpr std::wstring_view BG_YELLOW = L"\033[43m";
__LL_VAR_INLINE__ constexpr std::wstring_view BG_BLUE = L"\033[44m";
__LL_VAR_INLINE__ constexpr std::wstring_view BG_MAGENTA = L"\033[45m";
__LL_VAR_INLINE__ constexpr std::wstring_view BG_CYAN = L"\033[46m";
__LL_VAR_INLINE__ constexpr std::wstring_view BG_WHITE = L"\033[47m";

__LL_VAR_INLINE__ constexpr std::wstring_view DEBUG_WARNING = BG_YELLOW;
__LL_VAR_INLINE__ constexpr std::wstring_view DEBUG_ERROR = BG_RED;
__LL_VAR_INLINE__ constexpr std::wstring_view DEBUG_MESSAGE = BG_CYAN;

} // namespace wide
} // namespace color
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXPRESIONS_COLOR_HPP_
