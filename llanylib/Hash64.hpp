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

namespace __internal__ {
constexpr ui64 kMul = 0x9ddfea08eb382d69ull;
constexpr ui64 kll = 0xc3a5c85c97cb3171ull;
constexpr ui8 llshift = 47;
} // namespace __internal__

// Murmur-inspired hashing.
#define __LL_MURMUR_BODY_TEMPLATE__(value1, value2) \
	ui64 a = (value1 ^ value2) * __internal__::kMul; \
	a ^= (a >> 47); \
	ui64 b = (value2 ^ a) * __internal__::kMul; \
	b ^= (b >> 47); \
	b *= __internal__::kMul; \
	return b;

class Hash64 {
	private:
		ui64 value;
	public:
		#pragma region Constructors
		constexpr Hash64() __LL_EXCEPT__ : value(ZERO_UI64) {}
		constexpr Hash64(const ui64 value) __LL_EXCEPT__ : value(value) {}
		constexpr ~Hash64() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
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

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename const Hash64*() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename Hash64*() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Other
		__LL_NODISCARD__ constexpr operator ui64() const __LL_EXCEPT__ { return this->value; }
		__LL_NODISCARD__ constexpr ui64 get() const __LL_EXCEPT__ { return this->value; }

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Hash64& other) const __LL_EXCEPT__ {
			return this->value == other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Hash64& other) const __LL_EXCEPT__ {
			return !this->operator==(other);
		}

		constexpr void clear() __LL_EXCEPT__ { this->value = ZERO_UI64; }

		#pragma endregion
		#pragma region CombineAndHash
		__LL_NODISCARD__ constexpr Hash64 combine_rl(const ui64 value, const ui8 shift) const __LL_EXCEPT__ {
			return this->value ^ (value >> shift);
		}
		__LL_NODISCARD__ constexpr Hash64 combine_rr(const ui64 value, const ui8 shift) const __LL_EXCEPT__ {
			return value ^ (this->value >> shift);
		}
		__LL_NODISCARD__ constexpr Hash64 combine_ll(const ui64 value, const ui8 shift) const __LL_EXCEPT__ {
			return this->value ^ (value << shift);
		}
		__LL_NODISCARD__ constexpr Hash64 combine_lr(const ui64 value, const ui8 shift) const __LL_EXCEPT__ {
			return value ^ (this->value << shift);
		}
		__LL_NODISCARD__ constexpr Hash64 combine_rl(const ui8 shift) const __LL_EXCEPT__ {
			return this->combine_rl(__internal__::kMul, shift);
		}
		__LL_NODISCARD__ constexpr Hash64 combine_rr(const ui8 shift) const __LL_EXCEPT__ {
			return this->combine_rr(__internal__::kMul, shift);
		}
		__LL_NODISCARD__ constexpr Hash64 combine_ll(const ui8 shift) const __LL_EXCEPT__ {
			return this->combine_ll(__internal__::kMul, shift);
		}
		__LL_NODISCARD__ constexpr Hash64 combine_lr(const ui8 shift) const __LL_EXCEPT__ {
			return this->combine_lr(__internal__::kMul, shift);
		}
		__LL_NODISCARD__ constexpr Hash64 combine_rl() const __LL_EXCEPT__ {
			return this->combine_rl(__internal__::llshift);
		}
		__LL_NODISCARD__ constexpr Hash64 combine_rr() const __LL_EXCEPT__ {
			return this->combine_rr(__internal__::llshift);
		}
		__LL_NODISCARD__ constexpr Hash64 combine_ll() const __LL_EXCEPT__ {
			return this->combine_ll(__internal__::llshift);
		}
		__LL_NODISCARD__ constexpr Hash64 combine_lr() const __LL_EXCEPT__ {
			return this->combine_lr(__internal__::llshift);
		}

		__LL_NODISCARD__ constexpr Hash64 mur_l(const ui64 value) const __LL_EXCEPT__ {
			__LL_MURMUR_BODY_TEMPLATE__(this->value, value);
		}
		__LL_NODISCARD__ constexpr Hash64 mur_r(const ui64 value) const __LL_EXCEPT__ {
			__LL_MURMUR_BODY_TEMPLATE__(value, this->value);
		}
		__LL_NODISCARD__ constexpr Hash64 mur_l() const __LL_EXCEPT__ {
			return this->mur_l(__internal__::kll);
		}
		__LL_NODISCARD__ constexpr Hash64 mur_r() const __LL_EXCEPT__ {
			return this->mur_r(__internal__::kll);
		}

		#pragma endregion

		#pragma endregion
};

class Hash128 {
	protected:
		ui64 low;
		ui64 high;
	public:
		#pragma region Constructors
		constexpr Hash128() __LL_EXCEPT__ : low(ZERO_UI64), high(ZERO_UI64) {}
		constexpr Hash128(const ui64 low, const ui64 high) __LL_EXCEPT__
			: low(low), high(high) {}
		constexpr ~Hash128() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr Hash128(const Hash128& other) __LL_EXCEPT__
			: low(other.low), high(other.high) {}
		constexpr Hash128& operator=(const Hash128& other) __LL_EXCEPT__ {
			this->low = other.low;
			this->high = other.high;
			return *this;
		}
		constexpr Hash128(Hash128&& other) __LL_EXCEPT__
			: low(other.low), high(other.high) { other.Hash128::clear(); }
		constexpr Hash128& operator=(Hash128&& other) __LL_EXCEPT__ {
			this->low = other.low;
			this->high = other.high;
			other.Hash128::clear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator const Hash128* () const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator Hash128* () __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Other
		__LL_NODISCARD__ constexpr ui64 getLow() const __LL_EXCEPT__ { return this->low; }
		__LL_NODISCARD__ constexpr ui64 getHigh() const __LL_EXCEPT__ { return this->high; }

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Hash128& other) const __LL_EXCEPT__ {
			return ((this->high == other.high) && (this->low == other.low));
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Hash128& other) const __LL_EXCEPT__ {
			return !this->operator==(other);
		}

		__LL_NODISCARD__ constexpr ui64& operator[](const len_t pos) __LL_EXCEPT__ {
			return (pos == ZERO_UI64) ? this->low : this->high;
		}
		__LL_NODISCARD__ constexpr ui64 operator[](const len_t pos) const __LL_EXCEPT__ {
			return (pos == ZERO_UI64) ? this->low : this->high;
		}

		constexpr void clear() __LL_EXCEPT__ {
			this->low = ZERO_UI64;
			this->high = ZERO_UI64;
		}

		#pragma endregion
		#pragma region CombineAndHash
		__LL_NODISCARD__ constexpr hash::Hash64 combine_rl(const ui8 shift) const __LL_EXCEPT__ {
			return this->low ^ (this->high >> shift);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 combine_rr(const ui8 shift) const __LL_EXCEPT__ {
			return this->low ^ (this->high >> shift);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 combine_ll(const ui8 shift) const __LL_EXCEPT__ {
			return this->low ^ (this->high << shift);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 combine_lr(const ui8 shift) const __LL_EXCEPT__ {
			return this->low ^ (this->high << shift);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 combine_rl() const __LL_EXCEPT__ {
			return this->combine_rl(__internal__::llshift);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 combine_rr() const __LL_EXCEPT__ {
			return this->combine_rr(__internal__::llshift);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 combine_ll() const __LL_EXCEPT__ {
			return this->combine_ll(__internal__::llshift);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 combine_lr() const __LL_EXCEPT__ {
			return this->combine_lr(__internal__::llshift);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 mur_l() const __LL_EXCEPT__ {
			__LL_MURMUR_BODY_TEMPLATE__(this->low, this->high);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 mur_r() const __LL_EXCEPT__ {
			__LL_MURMUR_BODY_TEMPLATE__(this->high, this->low);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 toHash64() const __LL_EXCEPT__ {
			return hash::Hash64(this->mur_l());
		}
		__LL_NODISCARD__ constexpr operator ui64() const __LL_EXCEPT__ { return this->toHash64(); }

		#pragma endregion

		#pragma endregion
};

#undef MURMUR_BODY_TEMPLATE

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASH64_HPP_
