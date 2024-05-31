//////////////////////////////////////////////
//	Hash64.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASH64_HPP_) // Guard && version protector
	#if LLANYLIB_HASH64_MAYOR_ != 7 || LLANYLIB_HASH64_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Hash64.hpp version error!"
		#else
			#error "Hash64.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASH64_MAYOR_ || LLANYLIB_HASH64_MINOR_

#else !defined(LLANYLIB_HASH64_HPP_)
#define LLANYLIB_HASH64_HPP_
#define LLANYLIB_HASH64_MAYOR_ 7
#define LLANYLIB_HASH64_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace meta {
namespace hash {

class Hash64 {
	private:
		ui64 value;
	public:
		constexpr Hash64() __LL_EXCEPT__ : value(ZERO_UI64) {}
		constexpr Hash64(const ui64 value) __LL_EXCEPT__ : value(value) {}
		constexpr ~Hash64() __LL_EXCEPT__ {}

		constexpr Hash64(const Hash64& other) __LL_EXCEPT__ : value(other.value) {}
		constexpr Hash64& operator=(const Hash64& other) __LL_EXCEPT__ {
			this->value = other.value;
			return *this;
		}

		constexpr Hash64(Hash64&& other) __LL_EXCEPT__ : Hash64(other) { other.Hash64::clear(); }
		constexpr Hash64& operator=(Hash64&& other) __LL_EXCEPT__ {
			Hash64::operator=(other);
			other.Hash64::clear();
			return *this;
		}

		__LL_NODISCARD__ constexpr operator typename const Hash64*() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename Hash64*() __LL_EXCEPT__ = delete;

		__LL_NODISCARD__ constexpr ui64 get() const __LL_EXCEPT__ { return this->value; }

		constexpr void clear() __LL_EXCEPT__ { this->value = ZERO_UI64; }
};

// Hash 128 + combine

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASH64_HPP_
