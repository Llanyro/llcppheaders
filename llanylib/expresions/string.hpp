//////////////////////////////////////////////
//	string.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_EXPRESIONS_STRING_HPP_) // Guard && version protector
	#if LLANYLIB_EXPRESIONS_STRING_MAYOR_ != 7 || LLANYLIB_EXPRESIONS_STRING_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "string.hpp version error!"
		#else
			#error "string.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_EXPRESIONS_STRING_MAYOR_ || LLANYLIB_EXPRESIONS_STRING_MINOR_

#else !defined(LLANYLIB_EXPRESIONS_STRING_HPP_)
#define LLANYLIB_EXPRESIONS_STRING_HPP_
#define LLANYLIB_EXPRESIONS_STRING_MAYOR_ 7
#define LLANYLIB_EXPRESIONS_STRING_MINOR_ 0

#include "../ArrayView.hpp"

namespace llcpp {
namespace meta {
namespace string {

constexpr auto NULLPTR = make_StringView("nullptr");
constexpr auto TRUE_STR = make_StringView("True");
constexpr auto FALSE_STR = make_StringView("False");

constexpr auto INVALID_POINTER = make_StringView("[invalid pointer]: ");
constexpr auto NOT_NULL_POINTER = make_StringView("[not null pointer]: ");
constexpr auto OUT_OF_RANGE = make_StringView("[out of range]: ");

namespace wide {

constexpr auto NULLPTR = make_StringView(L"nullptr");
constexpr auto TRUE_STR = make_StringView(L"True");
constexpr auto FALSE_STR = make_StringView(L"False");

constexpr auto INVALID_POINTER = make_StringView(L"[invalid pointer]: ");
constexpr auto NOT_NULL_POINTER = make_StringView(L"[not null pointer]: ");
constexpr auto OUT_OF_RANGE = make_StringView(L"[out of range]: ");

} // namespace wide
} // namespace string
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXPRESIONS_STRING_HPP_
