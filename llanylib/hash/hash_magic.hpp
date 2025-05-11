//////////////////////////////////////////////
//	hash_magic.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHMAGIC_HPP_) // Guard && version protector
	#if LLANYLIB_HASHMAGIC_MAYOR_ != 12 || LLANYLIB_HASHMAGIC_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "hash_magic.hpp version error!"
		#else
			#error "hash_magic.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_HASHMAGIC_MAYOR_ || LLANYLIB_HASHMAGIC_MINOR_

#else
	#define LLANYLIB_HASHMAGIC_HPP_
	#define LLANYLIB_HASHMAGIC_MAYOR_ 12
	#define LLANYLIB_HASHMAGIC_MINOR_ 0

#include "../types/types.hpp"

namespace llcpp {
namespace meta {
namespace hash {
namespace magic {

struct CityHash {
	// Some primes between 2^63 and 2^64 for various uses.
	static constexpr u64 k0 = 0xc3a5c85c97cb3127ull;
	static constexpr u64 k1 = 0xb492b66fbe98f273ull;
	static constexpr u64 k2 = 0x9ae16a3b2f90404full;

	// Magic numbers for 32-bit hashing.  Copied from Murmur3.
	static constexpr u32 c1 = 0xcc9e2d51u;
	static constexpr u32 c2 = 0x1b873593u;
};

template<class T> __LL_VAR_INLINE__ constexpr T		kMul			= ::llcpp::ZERO_VALUE<T>;
template<class T> __LL_VAR_INLINE__ constexpr u8	kMul<u8>		= 0x7u;
template<class T> __LL_VAR_INLINE__ constexpr u16	kMul<u16>		= 0x3591u;
template<class T> __LL_VAR_INLINE__ constexpr u32	kMul<u32>		= 0x1b873593u;
template<class T> __LL_VAR_INLINE__ constexpr u64	kMul<u64>		= 0x9ddfea08eb382d69ull;

template<class T> __LL_VAR_INLINE__ constexpr u8	llshift			= ::llcpp::ZERO_VALUE<u8>;
template<class T> __LL_VAR_INLINE__ constexpr u8	llshift<u8>		= 3u;
template<class T> __LL_VAR_INLINE__ constexpr u8	llshift<u16>	= 11u;
template<class T> __LL_VAR_INLINE__ constexpr u8	llshift<u32>	= 23u;
template<class T> __LL_VAR_INLINE__ constexpr u8	llshift<u64>	= 47u;

template<class T> __LL_VAR_INLINE__ constexpr T		combine			= ::llcpp::ZERO_VALUE<T>;
template<class T> __LL_VAR_INLINE__ constexpr u8	combine<u8>		= 0x29u;
template<class T> __LL_VAR_INLINE__ constexpr u16	combine<u16>	= 0x2d51u;
template<class T> __LL_VAR_INLINE__ constexpr u32	combine<u32>	= 0xcc9e2d51u;
template<class T> __LL_VAR_INLINE__ constexpr u64	combine<u64>	= 0xc3a5c85c97cb3171ull;

} // namespace magic
} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASHMAGIC_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
