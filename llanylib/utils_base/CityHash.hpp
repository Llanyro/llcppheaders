//////////////////////////////////////////////
//	CityHash.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CITYHASH_INCOMPLETE_HPP_)
	#if LLANYLIB_CITYHASH_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_CITYHASH_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "CityHash.hpp(incomplete) version error!"
		#else
			#error "CityHash.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CITYHASH_INCOMPLETE_MAYOR_ || LLANYLIB_CITYHASH_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CITYHASH_INCOMPLETE_HPP_)
	#define LLANYLIB_CITYHASH_INCOMPLETE_HPP_
	#define LLANYLIB_CITYHASH_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_CITYHASH_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_CITYHASH_HPP_)
	#if LLANYLIB_CITYHASH_MAYOR_ != 12 || LLANYLIB_CITYHASH_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "CityHash.hpp version error!"
		#else
			#error "CityHash.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CITYHASH_MAYOR_ || LLANYLIB_CITYHASH_MINOR_

#else
	#define LLANYLIB_CITYHASH_HPP_
	#define LLANYLIB_CITYHASH_MAYOR_ 12
	#define LLANYLIB_CITYHASH_MINOR_ 0

#include "../types_base/types_base_extra.hpp"

#include "Hash.hpp"
#include "bits.hpp"

#if defined(WORDS_BIGENDIAN)
	#define u32_in_expected_order(x) (bits::bytes_swap_32(x))
	#define u64_in_expected_order(x) (bits::bytes_swap_64(x))
#else
	#define u32_in_expected_order(x) (x)
	#define u64_in_expected_order(x) (x)
#endif

namespace llcpp {
namespace meta {
namespace utils {

class CityHash : public ::llcpp::AlwaysValidTag {
	#pragma region Types
	public:
		// Class related
		using _MyType	= CityHash;
		using ValidTag	= ::llcpp::AlwaysValidTag;

		// Types and enums
		using Hash128p	= ::llcpp::meta::pair<u64, u64>;	// Simple struct hash 128
		using Hash64	= ::llcpp::meta::hash::Hash64;

	#pragma endregion
	#pragma region Expressions
	public:
		// Some primes between 2^63 and 2^64 for various uses.
		static constexpr u64 k0 = 0xc3a5c85c97cb3127ull;
		static constexpr u64 k1 = 0xb492b66fbe98f273ull;
		static constexpr u64 k2 = 0x9ae16a3b2f90404full;

		// Magic numbers for 32-bit hashing.  Copied from Murmur3.
		static constexpr u32 c1 = 0xcc9e2d51;
		static constexpr u32 c2 = 0x1b873593;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr CityHash() noexcept = default;
		constexpr ~CityHash() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr CityHash(const CityHash& other) noexcept = default;
		constexpr CityHash& operator=(const CityHash& other) noexcept = default;
		constexpr CityHash(CityHash&& other) noexcept = default;
		constexpr CityHash& operator=(CityHash&& other) noexcept = default;

		constexpr CityHash(const volatile CityHash&) = delete;
		constexpr CityHash& operator=(const volatile CityHash&) = delete;
		constexpr CityHash(volatile CityHash&&) = delete;
		constexpr CityHash& operator=(volatile CityHash&&) = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const CityHash*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator CityHash*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	protected:
		template<class T>
		__LL_NODISCARD__ static constexpr T unalignedLoad(ll_string_t p) noexcept {
			T result{};
			for (u8 i{}; i < sizeof(T); ++i)
				result |= static_cast<T>(p[i]) << (i << 3);
			return result;
		}
		__LL_NODISCARD__ static constexpr u64 fetch64(ll_string_t p) noexcept {
			return u64_in_expected_order(_MyType::unalignedLoad<u64>(p));
		}
		__LL_NODISCARD__ static constexpr u32 fetch32(ll_string_t p) noexcept {
			return u32_in_expected_order(_MyType::unalignedLoad<u32>(p));
		}
		// Bitwise right rotate.  Normally this will compile to a single
		// instruction, especially if the shift is a manifest constant.
		// [OPTIMIZE?]
		__LL_NODISCARD__ static constexpr u64 rotate(const u64 val, const i8 /*i32*/ shift) noexcept {
			// Avoid shifting by 64: doing so yields an undefined result.
			return shift ? ((val >> shift) | (val << (64 - shift))) : val;
		}
		__LL_NODISCARD__ static constexpr u64 shiftMix(const u64 val) noexcept {
			return val ^ (val >> 47);
		}
		__LL_NODISCARD__ static constexpr u64 hashLen16(const u64 u, const u64 v, const u64 mul) noexcept {
			// Murmur-inspired hashing.
			u64 a = (u ^ v) * mul;
			a ^= (a >> 47);
			u64 b = (v ^ a) * mul;
			b ^= (b >> 47);
			b *= mul;
			return b;
		}
		__LL_NODISCARD__ static constexpr u64 hashLen0to16(ll_string_t s, const usize len) noexcept {
			if (len >= 8) {
				u64 mul = k2 + (len << 1);
				u64 a = _MyType::fetch64(s) + k2;
				u64 b = _MyType::fetch64(s + len - 8);
				u64 c = _MyType::rotate(b, 37) * mul + a;
				u64 d = (_MyType::rotate(a, 25) + b) * mul;
				return _MyType::hashLen16(c, d, mul);
			}
			if (len >= 4) {
				u64 mul = k2 + (len << 1);
				u64 a = _MyType::fetch32(s);
				return _MyType::hashLen16(len + (a << 3), _MyType::fetch32(s + len - 4), mul);
			}
			if (len > 0) {
				u8 a = static_cast<u8>(s[0]);
				u8 b = static_cast<u8>(s[len >> 1]);
				u8 c = static_cast<u8>(s[len - 1]);
				u32 y = static_cast<u32>(a) + (static_cast<u32>(b) << 8);
				u32 z = static_cast<u32>(len) + (static_cast<u32>(c) << 2);
				return _MyType::shiftMix(y * k2 ^ z * k0) * k2;
			}
			return k2;
		}
		// This probably works well for 16-byte strings as well, but it may be overkill
		// in that case.
		__LL_NODISCARD__ static constexpr u64 hashLen17to32(ll_string_t s, const usize len) noexcept {
			u64 mul = k2 + (len << 1);
			u64 a = _MyType::fetch64(s) * k1;
			u64 b = _MyType::fetch64(s + 8);
			u64 c = _MyType::fetch64(s + len - 8) * mul;
			u64 d = _MyType::fetch64(s + len - 16) * k2;
			return _MyType::hashLen16(
				_MyType::rotate(a + b, 43) + _MyType::rotate(c, 30) + d,
				a + _MyType::rotate(b + k2, 18) + c,
				mul);
		}
		// Return an 8-byte hash for 33 to 64 bytes.
		__LL_NODISCARD__ static constexpr u64 hashLen33to64(ll_string_t s, const usize len) noexcept {
			u64 mul = k2 + (len << 1);
			u64 a = _MyType::fetch64(s) * k2;
			u64 b = _MyType::fetch64(s + 8);
			u64 c = _MyType::fetch64(s + len - 24);
			u64 d = _MyType::fetch64(s + len - 32);
			u64 e = _MyType::fetch64(s + 16) * k2;
			u64 f = _MyType::fetch64(s + 24) * 9;
			u64 g = _MyType::fetch64(s + len - 8);
			u64 h = _MyType::fetch64(s + len - 16) * mul;
			u64 u = _MyType::rotate(a + g, 43) + (_MyType::rotate(b, 30) + c) * 9;
			u64 v = ((a + g) ^ d) + f + 1;
			u64 w = ::llcpp::meta::bits::bytes_swap_64((u + v) * mul) + h;
			u64 x = _MyType::rotate(e + f, 42) + c;
			u64 y = (::llcpp::meta::bits::bytes_swap_64((v + w) * mul) + g) * mul;
			u64 z = e + f + c;
			a = ::llcpp::meta::bits::bytes_swap_64((x + z) * mul + y) + b;
			b = _MyType::shiftMix((z + a) * mul + d + h) * mul;
			return b + x;
		}
		// Return a 16-byte hash for 48 bytes.  Quick and dirty.
		// Callers do best to use "random-looking" values for a and b.
		__LL_NODISCARD__ static constexpr _MyType::Hash128p weakHashLen32WithSeeds(const u64 w, const u64 x, const u64 y, const u64 z, u64 a, u64 b) noexcept {
			a += w;
			b = _MyType::rotate(b + a + z, 21);
			u64 c = a;
			a += x;
			a += y;
			b += _MyType::rotate(a, 44);
			return { a + z, b + c };
		}
		// Return a 16-byte hash for s[0] ... s[31], a, and b.  Quick and dirty.
		__LL_NODISCARD__ static constexpr _MyType::Hash128p weakHashLen32WithSeeds(ll_string_t s, const u64 a, const u64 b) noexcept {
			return _MyType::weakHashLen32WithSeeds(
				_MyType::fetch64(s), _MyType::fetch64(s + 8),
				_MyType::fetch64(s + 16), _MyType::fetch64(s + 24),
				a,
				b);
		}

	public:
		__LL_NODISCARD__ static constexpr _MyType::Hash64 cityHash64(ll_string_t s, usize len) noexcept {
#if defined(LL_REAL_CXX23)
			if not consteval {
				throw "This is only constevaluated!";
				return ::llcpp::meta::hash::INVALID_HASH<_MyType::Hash64>;
			}
#endif

			if (!s) return ::llcpp::meta::hash::INVALID_HASH<_MyType::Hash64>;

			if (len <= 32) {
				if (len <= 16) return _MyType::Hash64(_MyType::hashLen0to16(s, len));
				else return _MyType::Hash64(_MyType::hashLen17to32(s, len));
			}
			else if (len <= 64) return _MyType::Hash64(_MyType::hashLen33to64(s, len));

			// For strings over 64 bytes we hash the end first, and then as we
			// loop we keep 56 bytes of state: v, w, x, y, and z.
			u64 x = _MyType::fetch64(s + len - 40);
			u64 y = _MyType::fetch64(s + len - 16) + _MyType::fetch64(s + len - 56);
			u64 z = _MyType::Hash128p{
				_MyType::fetch64(s + len - 48) + len,
				_MyType::fetch64(s + len - 24)
			};
			HashEx v = _MyType::weakHashLen32WithSeeds(s + len - 64, len, z);
			HashEx w = _MyType::weakHashLen32WithSeeds(s + len - 32, y + k1, x);
			x = x * k1 + _MyType::fetch64(s);

			// Decrease len to the nearest multiple of 64, and operate on 64-byte chunks.
			len = (len - 1) & ~static_cast<usize>(63);
			do {
				x = _MyType::rotate(x + y + v.getLow() + _MyType::fetch64(s + 8), 37) * k1;
				y = _MyType::rotate(y + v.getHigh() + _MyType::fetch64(s + 48), 42) * k1;
				x ^= w.getHigh();
				y += v.getLow() + _MyType::fetch64(s + 40);
				z = _MyType::rotate(z + w.getLow(), 33) * k1;
				v = _MyType::weakHashLen32WithSeeds(s, v.getHigh() * k1, x + w.getLow());
				w = _MyType::weakHashLen32WithSeeds(s + 32, z + w.getHigh(), y + _MyType::fetch64(s + 16));
				std::swap(z, x);
				s += 64;
				len -= 64;
			} while (len != ::llcpp::ZERO_VALUE<decltype(len)>);
			return HashEx(
				HashEx(v.getLow(), w.getLow()) + shiftMix(y) * k1 + z,
				HashEx(v.getHigh(), w.getHigh()) + x
			).HashEx::toHash64();
		}
		__LL_NODISCARD__ static constexpr _MyType::Hash64 cityHash64(const meta::StrPair& s) noexcept {
			if (s.empty()) return ::llcpp::meta::hash::INVALID_HASH<_MyType::Hash64>;
			else return city::CityHash::cityHash64(s.begin(), s.lenght());
		}
		__LL_NODISCARD__ static constexpr _MyType::Hash64 cityHash64(const meta::Str& s) noexcept {
			if (s.empty()) return ::llcpp::meta::hash::INVALID_HASH<_MyType::Hash64>;
			else return city::CityHash::cityHash64(s.begin(), s.lenght());
		}
		template<usize N>
		__LL_NODISCARD__ static constexpr _MyType::Hash64 cityHash64(const ll_char_t(&s)[N]) noexcept {
			if (!s) return ::llcpp::meta::hash::INVALID_HASH<_MyType::Hash64>;
			else return city::CityHash::cityHash64(s, N - 1);
		}
		// Only admits hash::basic_type_hash::is_convertible_v<>
		// Returns hash::INVALID_HASH64 if invalid type or hash error
		template<class U, class W = traits::cinput<U>>
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 cityHash64(W value) noexcept {
			return hash::basic_type_hash::hashValue<U, W>(value, city::CityHash::cityHash64);
		}
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 cityHash64(const hash::Hash64& hash) noexcept {
			return hash::basic_type_hash::hashValue<u64>(hash.get(), city::CityHash::cityHash64);
		}

		#pragma endregion

	#pragma endregion
};

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CITYHASH_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_CITYHASH_EXTRA_HPP_)
		#if LLANYLIB_CITYHASH_EXTRA_MAYOR_ != 12 || LLANYLIB_CITYHASH_EXTRA_MINOR_ < 0
			#if defined(__LL_REAL_CXX23)
				#warning "CityHash.hpp(extra) version error!"
			#else
				#error "CityHash.hpp(extra) version error!"
			#endif // __LL_REAL_CXX23
		#endif // LLANYLIB_CITYHASH_EXTRA_MAYOR_ || LLANYLIB_CITYHASH_EXTRA_MINOR_

	#else
		#define LLANYLIB_CITYHASH_EXTRA_HPP_
		#define LLANYLIB_CITYHASH_EXTRA_MAYOR_ 12
		#define LLANYLIB_CITYHASH_EXTRA_MINOR_ 0

	#endif // LLANYLIB_CITYHASH_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
