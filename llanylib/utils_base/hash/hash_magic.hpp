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
		#if defined(__LL_REAL_CXX23)
			#warning "hash_magic.hpp version error!"
		#else
			#error "hash_magic.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_HASHMAGIC_MAYOR_ || LLANYLIB_HASHMAGIC_MINOR_

#else
	#define LLANYLIB_HASHMAGIC_HPP_
	#define LLANYLIB_HASHMAGIC_MAYOR_ 12
	#define LLANYLIB_HASHMAGIC_MINOR_ 0

#include "../../types/types.hpp"

namespace llcpp {
namespace meta {
namespace utils {
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

struct Murmur {
	// 8 bits
	static constexpr u8 kMul8 = 0x7;
	static constexpr u8 llshift8 = 3;
	static constexpr u8 combine8 = 0x29;

	// 32 bits
	static constexpr u32 kMul32 = 0x1b873593u; // 0x7fffffff;
	static constexpr u8 llshift32 = 23;
	static constexpr u32 combine32 = 0xcc9e2d51u; // 0x7fffffbb;

	// 64 bits
	static constexpr u64 kMul64 = 0x9ddfea08eb382d69ull;
	static constexpr u8 llshift64 = 47;
	static constexpr u64 combine64 = 0xc3a5c85c97cb3171ull;
};

} // namespace magic
} // namespace hash
} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASHMAGIC_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
