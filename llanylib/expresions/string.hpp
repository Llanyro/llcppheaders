//////////////////////////////////////////////
//	string.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_STRING_HPP_) // Guard && version protector
	#if LLANYLIB_STRING_MAYOR_ != 5 || LLANYLIB_STRING_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "string.hpp version error!"
		#else
			#error "string.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_STRING_MAYOR_ || LLANYLIB_STRING_MINOR_

#else !defined(LLANYLIB_STRING_HPP_)
#define LLANYLIB_STRING_HPP_
#define LLANYLIB_STRING_MAYOR_ 5
#define LLANYLIB_STRING_MINOR_ 0

#include "../StringView.hpp"

namespace llcpp {
namespace string {

constexpr auto NULLPTR = make_StringView("nullptr");
constexpr auto TRUE_STR = make_StringView("True");
constexpr auto FALSE_STR = make_StringView("False");

constexpr auto INVALID_POINTER = make_StringView("[invalid pointer]: ");

namespace wide {

constexpr auto NULLPTR = make_StringView(L"nullptr");
constexpr auto TRUE_STR = make_StringView(L"True");
constexpr auto FALSE_STR = make_StringView(L"False");

constexpr auto INVALID_POINTER = make_StringView(L"[invalid pointer]: ");

} // namespace wide
} // namespace string
} // namespace llcpp

#endif // LLANYLIB_STRING_HPP_
