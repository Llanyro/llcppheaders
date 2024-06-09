//////////////////////////////////////////////
//	cityhash.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// This port is based on CityHash wich authors are Geoff Pike and Jyrki Alakuijala			//
// This port only tries to have a precompiled hash function of precompiled data				//
//////////////////////////////////////////////////////////////////////////////////////////////

#if defined(LLANYLIB_CITYHASH_HPP_) // Guard && version protector
	#if LLANYLIB_CITYHASH_MAYOR_ != 8 || LLANYLIB_CITYHASH_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "cityhash.hpp version error!"
		#else
			#error "cityhash.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_CITYHASH_MAYOR_ || LLANYLIB_CITYHASH_MINOR_

#else !defined(LLANYLIB_CITYHASH_HPP_)
#define LLANYLIB_CITYHASH_HPP_
#define LLANYLIB_CITYHASH_MAYOR_ 8
#define LLANYLIB_CITYHASH_MINOR_ 0

#include "bits.hpp"
#include "hash_pack.hpp"
#include "ArrayPair.hpp"

#if defined(WORDS_BIGENDIAN)
#define ui32_in_expected_order(x) (bits::bytes_swap_32(x))
#define ui64_in_expected_order(x) (bits::bytes_swap_64(x))
#else
#define ui32_in_expected_order(x) (x)
#define ui64_in_expected_order(x) (x)
#endif

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
    #if defined(__LL_SPECTRE_FUNCTIONS__)
		#pragma warning(disable:5045) // Security Spectre mitigation [SECURITY]
    #endif // __LL_UNSECURE_FUNCTIONS__
#endif // WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace hash {
namespace city {

struct CityHash {
	public:
		// Some primes between 2^63 and 2^64 for various uses.
		static constexpr ui64 k0 = 0xc3a5c85c97cb3127ull;
		static constexpr ui64 k1 = 0xb492b66fbe98f273ull;
		static constexpr ui64 k2 = 0x9ae16a3b2f90404full;

		// Magic numbers for 32-bit hashing.  Copied from Murmur3.
		static constexpr ui32 c1 = 0xcc9e2d51;
		static constexpr ui32 c2 = 0x1b873593;

	protected:
		template<class T>
		__LL_NODISCARD__ static constexpr T unalignedLoad(ll_string_t p) noexcept {
			T result{};
			for (ui8 i{}; i < sizeof(T); ++i)
				result |= static_cast<T>(p[i]) << (i << 3);
			return result;
		}
		__LL_NODISCARD__ static constexpr ui64 fetch64(ll_string_t p) noexcept {
			return ui64_in_expected_order(unalignedLoad<ui64>(p));
		}
		__LL_NODISCARD__ static constexpr ui32 fetch32(ll_string_t p) noexcept {
			return ui32_in_expected_order(unalignedLoad<ui32>(p));
		}
		// Bitwise right rotate.  Normally this will compile to a single
		// instruction, especially if the shift is a manifest constant.
		// [OPTIMIZE?]
		__LL_NODISCARD__ static constexpr ui64 rotate(const ui64 val, const i8 /*i32*/ shift) noexcept {
			// Avoid shifting by 64: doing so yields an undefined result.
			return shift == ZERO_I8 ? val : ((val >> shift) | (val << (64 - shift)));
		}
		__LL_NODISCARD__ static constexpr ui64 shiftMix(const ui64 val) noexcept {
			return val ^ (val >> 47);
		}
		__LL_NODISCARD__ static constexpr ui64 hashLen16(const ui64 u, const ui64 v, const ui64 mul) noexcept {
			// Murmur-inspired hashing.
			ui64 a = (u ^ v) * mul;
			a ^= (a >> 47);
			ui64 b = (v ^ a) * mul;
			b ^= (b >> 47);
			b *= mul;
			return b;
		}
		__LL_NODISCARD__ static constexpr ui64 hashLen0to16(ll_string_t s, const len_t len) noexcept {
			if (len >= 8) {
				ui64 mul = k2 + (len << 1);
				ui64 a = fetch64(s) + k2;
				ui64 b = fetch64(s + len - 8);
				ui64 c = rotate(b, 37) * mul + a;
				ui64 d = (rotate(a, 25) + b) * mul;
				return CityHash::hashLen16(c, d, mul);
			}
			if (len >= 4) {
				ui64 mul = k2 + (len << 1);
				ui64 a = fetch32(s);
				return hashLen16(len + (a << 3), fetch32(s + len - 4), mul);
			}
			if (len > 0) {
				ui8 a = static_cast<ui8>(s[0]);
				ui8 b = static_cast<ui8>(s[len >> 1]);
				ui8 c = static_cast<ui8>(s[len - 1]);
				ui32 y = static_cast<ui32>(a) + (static_cast<ui32>(b) << 8);
				ui32 z = static_cast<ui32>(len) + (static_cast<ui32>(c) << 2);
				return shiftMix(y * k2 ^ z * k0) * k2;
			}
			return k2;
		}
		// This probably works well for 16-byte strings as well, but it may be overkill
		// in that case.
		__LL_NODISCARD__ static constexpr ui64 hashLen17to32(ll_string_t s, const len_t len) noexcept {
			ui64 mul = k2 + (len << 1);
			ui64 a = fetch64(s) * k1;
			ui64 b = fetch64(s + 8);
			ui64 c = fetch64(s + len - 8) * mul;
			ui64 d = fetch64(s + len - 16) * k2;
			return hashLen16(rotate(a + b, 43) + rotate(c, 30) + d, a + rotate(b + k2, 18) + c, mul);
		}
		// Return an 8-byte hash for 33 to 64 bytes.
		__LL_NODISCARD__ static constexpr ui64 hashLen33to64(ll_string_t s, const len_t len) noexcept {
			ui64 mul = k2 + (len << 1);
			ui64 a = fetch64(s) * k2;
			ui64 b = fetch64(s + 8);
			ui64 c = fetch64(s + len - 24);
			ui64 d = fetch64(s + len - 32);
			ui64 e = fetch64(s + 16) * k2;
			ui64 f = fetch64(s + 24) * 9;
			ui64 g = fetch64(s + len - 8);
			ui64 h = fetch64(s + len - 16) * mul;
			ui64 u = rotate(a + g, 43) + (rotate(b, 30) + c) * 9;
			ui64 v = ((a + g) ^ d) + f + 1;
			ui64 w = bits::bytes_swap_64((u + v) * mul) + h;
			ui64 x = rotate(e + f, 42) + c;
			ui64 y = (bits::bytes_swap_64((v + w) * mul) + g) * mul;
			ui64 z = e + f + c;
			a = bits::bytes_swap_64((x + z) * mul + y) + b;
			b = shiftMix((z + a) * mul + d + h) * mul;
			return b + x;
		}
		// Return a 16-byte hash for 48 bytes.  Quick and dirty.
		// Callers do best to use "random-looking" values for a and b.
		__LL_NODISCARD__ static constexpr hash::Hash128 weakHashLen32WithSeeds(const ui64 w, const ui64 x, const ui64 y, const ui64 z, ui64 a, ui64 b) noexcept {
			a += w;
			b = rotate(b + a + z, 21);
			ui64 c = a;
			// [OPTIMIZE?]
			a += x;
			a += y;
			b += rotate(a, 44);
			return { a + z, b + c };
		}
		// Return a 16-byte hash for s[0] ... s[31], a, and b.  Quick and dirty.
		__LL_NODISCARD__ static constexpr hash::Hash128 weakHashLen32WithSeeds(ll_string_t s, const ui64 a, const ui64 b) noexcept {
			return weakHashLen32WithSeeds(
				fetch64(s), fetch64(s + 8),
				fetch64(s + 16), fetch64(s + 24),
				a, b);
		}
	public:
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 cityHash64(ll_string_t s, len_t len) noexcept {
#if defined(LL_REAL_CXX23)
			if not consteval {
				throw "This is only constevaluated!";
				return hash::INVALID_HASH64;
			}
#endif

			if (!s) return hash::INVALID_HASH64;

			if (len <= 32) {
				if (len <= 16) return hash::Hash64(hashLen0to16(s, len));
				else return hash::Hash64(hashLen17to32(s, len));
			}
			else if (len <= 64) return hash::Hash64(hashLen33to64(s, len));

			// For strings over 64 bytes we hash the end first, and then as we
			// loop we keep 56 bytes of state: v, w, x, y, and z.
			ui64 x = fetch64(s + len - 40);
			ui64 y = fetch64(s + len - 16) + fetch64(s + len - 56);
			ui64 z = hash::Hash128(fetch64(s + len - 48) + len, fetch64(s + len - 24));
			hash::Hash128 v = weakHashLen32WithSeeds(s + len - 64, len, z);
			hash::Hash128 w = weakHashLen32WithSeeds(s + len - 32, y + k1, x);
			x = x * k1 + fetch64(s);

			// Decrease len to the nearest multiple of 64, and operate on 64-byte chunks.
			len = (len - 1) & ~static_cast<len_t>(63);
			do {
				x = rotate(x + y + v.getLow() + fetch64(s + 8), 37) * k1;
				y = rotate(y + v.getHigh() + fetch64(s + 48), 42) * k1;
				x ^= w.getHigh();
				y += v.getLow() + fetch64(s + 40);
				z = rotate(z + w.getLow(), 33) * k1;
				v = weakHashLen32WithSeeds(s, v.getHigh() * k1, x + w.getLow());
				w = weakHashLen32WithSeeds(s + 32, z + w.getHigh(), y + fetch64(s + 16));
				std::swap(z, x);
				s += 64;
				len -= 64;
			} while (len != ZERO_UI64);
			return hash::Hash128(
				hash::Hash128(v.getLow(), w.getLow()) + shiftMix(y) * k1 + z,
				hash::Hash128(v.getHigh(), w.getHigh()) + x
			).hash::Hash128::toHash64();
		}
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 cityHash64(const meta::StrPair& s) noexcept {
			if (s.empty()) return hash::INVALID_HASH64;
			else return city::CityHash::cityHash64(s.begin(), s.len());
		}
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 cityHash64(const meta::Str& s) noexcept {
			if (s.empty()) return hash::INVALID_HASH64;
			else return city::CityHash::cityHash64(s.begin(), s.len());
		}
		template<len_t N>
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 cityHash64(const ll_char_t(&s)[N]) noexcept {
			if (!s) return hash::INVALID_HASH64;
			else return city::CityHash::cityHash64(s, N - 1);
		}
		// Only admits hash::basic_type_hash::is_convertible_v<>
		// Returns hash::INVALID_HASH64 if invalid type or hash error
		template<class U, class W = traits::cinput<U>>
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 cityHash64(W value) noexcept {
			return hash::basic_type_hash::hashValue<U, W>(value, city::CityHash::cityHash64);
		}
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 cityHash64(const hash::Hash64& hash) noexcept {
			return hash::basic_type_hash::hashValue<ui64>(hash.get(), city::CityHash::cityHash64);
		}
};

} // namespace city
} // namespace hash
} // namespace meta
} // namespace llcpp

#undef ui32_in_expected_order
#undef ui64_in_expected_order

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#endif // LLANYLIB_CITYHASH_HPP_
