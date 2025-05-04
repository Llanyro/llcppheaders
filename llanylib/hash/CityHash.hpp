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
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "CityHash.hpp(incomplete) version error!"
		#else
			#error "CityHash.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CITYHASH_INCOMPLETE_MAYOR_ || LLANYLIB_CITYHASH_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CITYHASH_INCOMPLETE_HPP_)
	#define LLANYLIB_CITYHASH_INCOMPLETE_HPP_
	#define LLANYLIB_CITYHASH_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_CITYHASH_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_CITYHASH_HPP_)
	#if LLANYLIB_CITYHASH_MAYOR_ != 12 || LLANYLIB_CITYHASH_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "CityHash.hpp version error!"
		#else
			#error "CityHash.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CITYHASH_MAYOR_ || LLANYLIB_CITYHASH_MINOR_

#else
	#define LLANYLIB_CITYHASH_HPP_
	#define LLANYLIB_CITYHASH_MAYOR_ 12
	#define LLANYLIB_CITYHASH_MINOR_ 0

#include "../traits/ValidationChecker.hpp"
#include "../traits_base/checker.hpp"

#include "../concepts/hash.hpp"

#include "../utils_base/bits.hpp"
#include "../utils_base/Exceptions.hpp"

#include "Algorithm.hpp"
#include "hash_macros.hpp"

namespace llcpp {
namespace meta {
namespace concepts {
namespace hash {

template<class Base>
concept IsValidCityHashExtra = requires (const Base t, const u64 u6, const u32 u3) {
	{ t.u64_in_expected_order(u6) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<u64>;
	{ t.u32_in_expected_order(u3) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<u32>;
	{ t.hash16bytes(u6, u6) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<u64>;
};

} // namespace hash
} // namespace concepts
namespace utils {
namespace hash {

class CityHashFunctions : public ::llcpp::AlwaysValidTag {
	public:
		using Algorithm = ::llcpp::meta::utils::hash::Algorithm<
			u64,
			::llcpp::meta::utils::hash::AlgorithmMode::Murmur
		>;

	public:
		__LL_NODISCARD__ constexpr u64 bytes_swap_64(const u64 v) const noexcept {
			return ::llcpp::meta::utils::bits::in_expected_order(v);
		}
		__LL_NODISCARD__ constexpr u32 bytes_swap_32(const u32 v) const noexcept {
			return ::llcpp::meta::utils::bits::in_expected_order(v);
		}
		__LL_NODISCARD__ constexpr u64 u64_in_expected_order(const u64 v) const noexcept {
			return ::llcpp::meta::utils::bits::in_expected_order(v);
		}
		__LL_NODISCARD__ constexpr u32 u32_in_expected_order(const u32 v) const noexcept {
			return ::llcpp::meta::utils::bits::in_expected_order(v);
		}
		__LL_NODISCARD__ constexpr u64 hash16bytes(const u64 v1, const u64 v2) const noexcept {
			return Algorithm().process(v1, v2);
		}
};

template<class _ExtraFunctions = ::llcpp::meta::utils::hash::CityHashFunctions>
	requires
		::llcpp::meta::concepts::hash::IsValidCityHashExtra<_ExtraFunctions>
		&& ::llcpp::meta::traits::is_valid_constructor_checker_v<_ExtraFunctions>
class CityHash
	: public ::llcpp::meta::traits::ValidationWrapper<_ExtraFunctions, ::llcpp::AlwaysValidTag>
	, public _ExtraFunctions
{
	#pragma region Types
	public:
		// Class related
		using _MyType			= CityHash;
		using ValidTag			= ::llcpp::meta::traits::ValidationWrapper<_ExtraFunctions, ::llcpp::AlwaysValidTag>;
		using ExtraFunctions	= _ExtraFunctions;

		// Types and enums
		using byte				= char;
		using bytearray			= const byte*;
		using Hash				= u64;
		using Hash128p			= ::llcpp::meta::pair<u64, u64>;	// Simple struct hash 128
		using CityHashMagic		= ::llcpp::meta::utils::hash::magic::CityHash;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr CityHash() noexcept = default;
		template<class... Args>
		constexpr CityHash(Args&&... args) noexcept requires(::std::is_nothrow_constructible_v<ExtraFunctions, Args...>)
			: ValidTag()
			, ExtraFunctions(::std::forward<Args>(args)...)
		{}
		constexpr ~CityHash() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr CityHash(const CityHash& other) noexcept
			: ValidTag()
			, ExtraFunctions(::std::forward<const ExtraFunctions&>(other))
		{}
		constexpr CityHash& operator=(const CityHash& other) noexcept {
			ExtraFunctions::operator=(::std::forward<const ExtraFunctions&>(other));
			return *this;
		}
		constexpr CityHash(CityHash&& other) noexcept
			: ValidTag()
			, ExtraFunctions(::std::forward<ExtraFunctions&&>(other))
		{}
		constexpr CityHash& operator=(CityHash&& other) noexcept {
			ExtraFunctions::operator=(::std::forward<ExtraFunctions&&>(other));
			return *this;
		}

		constexpr CityHash(const volatile CityHash&) noexcept = delete;
		constexpr CityHash& operator=(const volatile CityHash&) noexcept = delete;
		constexpr CityHash(volatile CityHash&&) noexcept = delete;
		constexpr CityHash& operator=(volatile CityHash&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const CityHash*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator CityHash*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	protected:
		__LL_INLINE__ static constexpr void swap(u64& x, u64& y) noexcept {
			u64 tmp = x;
			x = y;
			y = tmp;
		}
		__LL_NODISCARD__ constexpr u64 fetch64(bytearray p) const noexcept {
			return ExtraFunctions::u64_in_expected_order(::llcpp::meta::utils::bits::unaligned_load<u64>(p));
		}
		__LL_NODISCARD__ constexpr u32 fetch32(bytearray p) const noexcept {
			return ExtraFunctions::u32_in_expected_order(::llcpp::meta::utils::bits::unaligned_load<u32>(p));
		}
		// Bitwise right rotate.  Normally this will compile to a single
		// instruction, especially if the shift is a manifest constant.
		// [OPTIMIZE?]
		__LL_NODISCARD__ constexpr u64 rotate(const u64 val, const i8 /*i32*/ shift) const noexcept {
			// Avoid shifting by 64: doing so yields an undefined result.
			return shift ? ((val >> shift) | (val << (64 - shift))) : val;
		}
		__LL_NODISCARD__ constexpr u64 shiftMix(const u64 val) const noexcept {
			return val ^ (val >> 47);
		}
		__LL_NODISCARD__ constexpr u64 hashLen16(const u64 u, const u64 v, const u64 mul) const noexcept {
			// Murmur-inspired hashing.
			u64 a = (u ^ v) * mul;
			a ^= (a >> 47);
			u64 b = (v ^ a) * mul;
			b ^= (b >> 47);
			b *= mul;
			return b;
		}
		__LL_NODISCARD__ constexpr u64 hashLen0to16(bytearray s, const usize len) const noexcept {
			if (len >= 8) {
				u64 mul = CityHashMagic::k2 + (len << 1);
				u64 a = this->fetch64(s) + CityHashMagic::k2;
				u64 b = this->fetch64(s + len - 8);
				u64 c = this->rotate(b, 37) * mul + a;
				u64 d = (this->rotate(a, 25) + b) * mul;
				return this->hashLen16(c, d, mul);
			}
			if (len >= 4) {
				u64 mul = CityHashMagic::k2 + (len << 1);
				u64 a = this->fetch32(s);
				return this->hashLen16(len + (a << 3), this->fetch32(s + len - 4), mul);
			}
			if (len > 0) {
				u8 a = static_cast<u8>(s[0]);
				u8 b = static_cast<u8>(s[len >> 1]);
				u8 c = static_cast<u8>(s[len - 1]);
				u32 y = static_cast<u32>(a) + (static_cast<u32>(b) << 8);
				u32 z = static_cast<u32>(len) + (static_cast<u32>(c) << 2);
				return this->shiftMix(y * CityHashMagic::k2 ^ z * CityHashMagic::k0) * CityHashMagic::k2;
			}
			return CityHashMagic::k2;
		}
		// This probably works well for 16-byte strings as well, but it may be overkill
		// in that case.
		__LL_NODISCARD__ constexpr u64 hashLen17to32(bytearray s, const usize len) const noexcept {
			u64 mul = CityHashMagic::k2 + (len << 1);
			u64 a = this->fetch64(s) * CityHashMagic::k1;
			u64 b = this->fetch64(s + 8);
			u64 c = this->fetch64(s + len - 8) * mul;
			u64 d = this->fetch64(s + len - 16) * CityHashMagic::k2;
			return this->hashLen16(
				this->rotate(a + b, 43) + this->rotate(c, 30) + d,
				a + this->rotate(b + CityHashMagic::k2, 18) + c,
				mul);
		}
		// Return an 8-byte hash for 33 to 64 bytes.
		__LL_NODISCARD__ constexpr u64 hashLen33to64(bytearray s, const usize len) const noexcept {
			u64 mul = CityHashMagic::k2 + (len << 1);
			u64 a = this->fetch64(s) * CityHashMagic::k2;
			u64 b = this->fetch64(s + 8);
			u64 c = this->fetch64(s + len - 24);
			u64 d = this->fetch64(s + len - 32);
			u64 e = this->fetch64(s + 16) * CityHashMagic::k2;
			u64 f = this->fetch64(s + 24) * 9;
			u64 g = this->fetch64(s + len - 8);
			u64 h = this->fetch64(s + len - 16) * mul;
			u64 u = this->rotate(a + g, 43) + (this->rotate(b, 30) + c) * 9;
			u64 v = ((a + g) ^ d) + f + 1;
			u64 w = ExtraFunctions::bytes_swap_64((u + v) * mul) + h;
			u64 x = this->rotate(e + f, 42) + c;
			u64 y = (ExtraFunctions::bytes_swap_64((v + w) * mul) + g) * mul;
			u64 z = e + f + c;
			a = ExtraFunctions::bytes_swap_64((x + z) * mul + y) + b;
			b = this->shiftMix((z + a) * mul + d + h) * mul;
			return b + x;
		}
		// Return a 16-byte hash for 48 bytes.  Quick and dirty.
		// Callers do best to use "random-looking" values for a and b.
		__LL_NODISCARD__ constexpr _MyType::Hash128p weakHashLen32WithSeeds(const u64 w, const u64 x, const u64 y, const u64 z, u64 a, u64 b) const noexcept {
			a += w;
			b = this->rotate(b + a + z, 21);
			u64 c = a;
			a += x;
			a += y;
			b += this->rotate(a, 44);
			return _MyType::Hash128p{ a + z, b + c };
		}
		// Return a 16-byte hash for s[0] ... s[31], a, and b.  Quick and dirty.
		__LL_NODISCARD__ constexpr _MyType::Hash128p weakHashLen32WithSeeds(bytearray s, const u64 a, const u64 b) const noexcept {
			return this->weakHashLen32WithSeeds(
				this->fetch64(s), this->fetch64(s + 8),
				this->fetch64(s + 16), this->fetch64(s + 24),
				a,
				b);
		}

	public:
		__LL_NODISCARD__ constexpr u64 cityHash64(bytearray s, usize len) const noexcept {
			LL_NULL_STRING_EXCEPTION_CHECK(s, len);

			if (len <= 32) {
				if (len <= 16) return this->hashLen0to16(s, len);
				else return this->hashLen17to32(s, len);
			}
			else if (len <= 64) return this->hashLen33to64(s, len);

			// For strings over 64 bytes we hash the end first, and then as we
			// loop we keep 56 bytes of state: v, w, x, y, and z.
			u64 x = this->fetch64(s + len - 40);
			u64 y = this->fetch64(s + len - 16) + this->fetch64(s + len - 56);
			u64 z = ExtraFunctions::hash16bytes(
				this->fetch64(s + len - 48) + len,
				this->fetch64(s + len - 24)
			);
			_MyType::Hash128p v = this->weakHashLen32WithSeeds(s + len - 64, len, z);
			_MyType::Hash128p w = this->weakHashLen32WithSeeds(s + len - 32, y + CityHashMagic::k1, x);
			x = x * CityHashMagic::k1 + this->fetch64(s);

			// Decrease len to the nearest multiple of 64, and operate on 64-byte chunks.
			len = (len - 1) & ~static_cast<usize>(63);
			do {
				x = this->rotate(x + y + v.second + this->fetch64(s + 8), 37) * CityHashMagic::k1;
				y = this->rotate(y + v.first + this->fetch64(s + 48), 42) * CityHashMagic::k1;
				x ^= w.first;
				y += v.second + this->fetch64(s + 40);
				z = this->rotate(z + w.second, 33) * CityHashMagic::k1;
				v = this->weakHashLen32WithSeeds(s, v.first * CityHashMagic::k1, x + w.second);
				w = this->weakHashLen32WithSeeds(s + 32, z + w.first, y + this->fetch64(s + 16));
				_MyType::swap(z, x);
				s += 64;
				len -= 64;
			} while (len != ::llcpp::ZERO_VALUE<decltype(len)>);

			return
				ExtraFunctions::hash16bytes(
					ExtraFunctions::hash16bytes(v.second, w.second)
						+ this->shiftMix(y) * CityHashMagic::k1 + z,
					ExtraFunctions::hash16bytes(v.first, w.first)
						+ x
				);
		}
		template<class T>
			requires ::llcpp::meta::concepts::hash::IsValidArray<T, byte>
		__LL_NODISCARD__ constexpr u64 cityHash64(const T& s) const noexcept {
			LL_STRING_EXCEPTION_CHECK;
			return this->cityHash64(s.begin(), s.size());
		}
		template<usize N>
		__LL_NODISCARD__ constexpr u64 cityHash64(const byte(&s)[N]) const noexcept {
			return this->cityHash64(s, N);
		}

		#pragma endregion

	#pragma endregion
};

} // namespace hash
} // namespace utils
} // namespace meta
} // namespace llcpp

#undef LL_STRING_EXCEPTION_CHECK
#undef LL_NULL_STRING_EXCEPTION_CHECK

#endif // LLANYLIB_CITYHASH_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
