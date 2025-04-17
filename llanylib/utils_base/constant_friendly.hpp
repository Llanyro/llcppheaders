//////////////////////////////////////////////
//	constant_friendly.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_CONSTANTFRIENDLY_HPP_) // Guard && version protector
	#if LLANYLIB_CONSTANTFRIENDLY_MAYOR_ != 11 || LLANYLIB_CONSTANTFRIENDLY_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "constant_friendly.hpp version error!"
		#else
			#error "constant_friendly.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONSTANTFRIENDLY_MAYOR_ || LLANYLIB_CONSTANTFRIENDLY_MINOR_

#else
	#define LLANYLIB_CONSTANTFRIENDLY_HPP_
	#define LLANYLIB_CONSTANTFRIENDLY_MAYOR_ 11
	#define LLANYLIB_CONSTANTFRIENDLY_MINOR_ 0

#include "../types/types.hpp"

namespace std {
EXTERN_C_FUNC void* __MSVC_CDECL memcpy(void* dst, const void* src, __STD_SIZE_T bytes);

#if defined(__LL_WINDOWS_SYSTEM)
	EXTERN_C_FUNC unsigned short		__MSVC_CDECL _byteswap_ushort(unsigned short);
	EXTERN_C_FUNC unsigned long			__MSVC_CDECL _byteswap_ulong(unsigned long);
	EXTERN_C_FUNC unsigned long long	__MSVC_CDECL _byteswap_uint64(unsigned long long);

	#define __LL_BWAP16 ::std::_byteswap_ushort
	#define __LL_BWAP32 ::std::_byteswap_ulong
	#define __LL_BWAP64 ::std::_byteswap_uint64
#elif defined(__LL_MINGW) || defined(__LL_POSIX_SYSTEM) || defined(__LL_UNIX_SYSTEM)
	EXTERN_C_FUNC unsigned short		__bswap_16(unsigned short);
	EXTERN_C_FUNC unsigned int			__bswap_32(unsigned int);
	EXTERN_C_FUNC unsigned long long	__bswap_64(unsigned long long);

	#define __LL_BWAP16 ::std::__bswap_16
	#define __LL_BWAP32 ::std::__bswap_32
	#define __LL_BWAP64 ::std::__bswap_64
#endif // OS

} // namespace std

namespace llcpp {
namespace meta {
namespace utils {

__LL_NODISCARD__ constexpr u16 bytes_swap_16(const u16 x)  noexcept {
	if consteval {
		// Source from glibc
		return ((u16) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)));
	}
	else {
		return __LL_BWAP16(x);
	}
}
__LL_NODISCARD__ constexpr u32 bytes_swap_32(const u32 x)  noexcept {
	if consteval {
		// Source from glibc
		return ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8) |
				(((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24));
	}
	else {
		return __LL_BWAP32(x);
	}
}
__LL_NODISCARD__ constexpr u64 bytes_swap_64(const u64 x) noexcept {
	if consteval {
		// Source from glibc
		return ((((x) & 0xff00000000000000ull) >> 56)
			| (((x) & 0x00ff000000000000ull) >> 40)
			| (((x) & 0x0000ff0000000000ull) >> 24)
			| (((x) & 0x000000ff00000000ull) >> 8)
			| (((x) & 0x00000000ff000000ull) << 8)
			| (((x) & 0x0000000000ff0000ull) << 24)
			| (((x) & 0x000000000000ff00ull) << 40)
			| (((x) & 0x00000000000000ffull) << 56));
	}
	else {
		return __LL_BWAP64(x);
	}
}

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CONSTANTFRIENDLY_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
