//////////////////////////////////////////////
//	string.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_EXPRESIONS_STRING_HPP_) // Guard && version protector
	#if LLANYLIB_EXPRESIONS_STRING_MAYOR_ != 8 || LLANYLIB_EXPRESIONS_STRING_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "string.hpp version error!"
		#else
			#error "string.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_EXPRESIONS_STRING_MAYOR_ || LLANYLIB_EXPRESIONS_STRING_MINOR_

#else !defined(LLANYLIB_EXPRESIONS_STRING_HPP_)
#define LLANYLIB_EXPRESIONS_STRING_HPP_
#define LLANYLIB_EXPRESIONS_STRING_MAYOR_ 8
#define LLANYLIB_EXPRESIONS_STRING_MINOR_ 0

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
namespace string {

__LL_VAR_INLINE__ constexpr std::string_view NULLPTR = "nullptr";
__LL_VAR_INLINE__ constexpr std::string_view TRUE_STR = "True";
__LL_VAR_INLINE__ constexpr std::string_view FALSE_STR = "False";

__LL_VAR_INLINE__ constexpr std::string_view INVALID_POINTER = "[invalid pointer]: ";
__LL_VAR_INLINE__ constexpr std::string_view NOT_NULL_POINTER = "[not null pointer]: ";
__LL_VAR_INLINE__ constexpr std::string_view OUT_OF_RANGE = "[out of range]: ";

namespace wide {

__LL_VAR_INLINE__ constexpr std::wstring_view NULLPTR = L"nullptr";
__LL_VAR_INLINE__ constexpr std::wstring_view TRUE_STR = L"True";
__LL_VAR_INLINE__ constexpr std::wstring_view FALSE_STR = L"False";

__LL_VAR_INLINE__ constexpr std::wstring_view INVALID_POINTER = L"[invalid pointer]: ";
__LL_VAR_INLINE__ constexpr std::wstring_view NOT_NULL_POINTER = L"[not null pointer]: ";
__LL_VAR_INLINE__ constexpr std::wstring_view OUT_OF_RANGE = L"[out of range]: ";

} // namespace wide
} // namespace string
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXPRESIONS_STRING_HPP_
