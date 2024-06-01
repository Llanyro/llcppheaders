//////////////////////////////////////////////
//	StandardRandom.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_STANDARDRANDOM_HPP_) // Guard && version protector
	#if LLANYLIB_STANDARDRANDOM_MAYOR_ != 7 || LLANYLIB_STANDARDRANDOM_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "StandardRandom.hpp version error!"
		#else
			#error "StandardRandom.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_STANDARDRANDOM_MAYOR_ || LLANYLIB_STANDARDRANDOM_MINOR_

#else !defined(LLANYLIB_STANDARDRANDOM_HPP_)
#define LLANYLIB_STANDARDRANDOM_HPP_
#define LLANYLIB_STANDARDRANDOM_MAYOR_ 7
#define LLANYLIB_STANDARDRANDOM_MINOR_ 0

#include "StandardHash.hpp"
#include "Random.hpp"

namespace llcpp {
namespace meta {

__LL_NODISCARD__ constexpr Random STANDARD_RANDOM() {
	return Random("Seed", hash::STANDARD_HASH_FUNCTION_PACK);
}
template<class T>
__LL_NODISCARD__ constexpr Random STANDARD_RANDOM(const T& seed) {
	return Random(seed, hash::STANDARD_HASH_FUNCTION_PACK);
}
template<class T>
__LL_NODISCARD__ constexpr Random STANDARD_RANDOM(T&& seed) {
	return Random(std::move(seed), hash::STANDARD_HASH_FUNCTION_PACK);
}

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_STANDARDRANDOM_HPP_
