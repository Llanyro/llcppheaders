//////////////////////////////////////////////
//	hash_types.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.3							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHTYPES_HPP_) // Guard && version protector
	#if LLANYLIB_HASHTYPES_MAYOR_ != 7 || LLANYLIB_HASHTYPES_MINOR_ < 3
		#if defined(LL_REAL_CXX23)
			#warning "hash_types.hpp version error!"
		#else
			#error "hash_types.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASHTYPES_MAYOR_ || LLANYLIB_HASHTYPES_MINOR_

#else !defined(LLANYLIB_HASHTYPES_HPP_)
#define LLANYLIB_HASHTYPES_HPP_
#define LLANYLIB_HASHTYPES_MAYOR_ 7
#define LLANYLIB_HASHTYPES_MINOR_ 3

#include "hash_algorithm.hpp"

#include <optional>

namespace llcpp {
namespace meta {
namespace hash {

class Hash32 {
	private:
		ui32 value;
	public:
		#pragma region Constructors
		constexpr Hash32() __LL_EXCEPT__ : value(ZERO_UI32) {}
		constexpr Hash32(const ui32 value) __LL_EXCEPT__ : value(value) {}
		constexpr ~Hash32() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr Hash32(const Hash32& other) __LL_EXCEPT__ : value(other.value) {}
		constexpr Hash32& operator=(const Hash32& other) __LL_EXCEPT__ {
			this->value = other.value;
			return *this;
		}

		constexpr Hash32(Hash32&& other) __LL_EXCEPT__ : Hash32(other) { other.Hash32::clear(); }
		constexpr Hash32& operator=(Hash32&& other) __LL_EXCEPT__ {
			Hash32::operator=(other);
			other.Hash32::clear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename const Hash32*() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename Hash32*() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Other
		__LL_NODISCARD__ constexpr operator ui32() const __LL_EXCEPT__ { return this->value; }
		__LL_NODISCARD__ constexpr ui32 get() const __LL_EXCEPT__ { return this->value; }

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Hash32& other) const __LL_EXCEPT__ {
			return this->value == other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Hash32& other) const __LL_EXCEPT__ {
			return !this->operator==(other);
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator>(const Hash32& other) const __LL_EXCEPT__ {
			return this->value > other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const Hash32& other) const __LL_EXCEPT__ {
			return this->value >= other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const Hash32& other) const __LL_EXCEPT__ {
			return this->value < other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const Hash32& other) const __LL_EXCEPT__ {
			return this->value <= other.value;
		}

		constexpr void clear() __LL_EXCEPT__ { this->value = ZERO_UI32; }

		#pragma endregion
		#pragma region CombineAndHash
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_l(const ui32 value, const ui8 shift) const __LL_EXCEPT__ {
			return hash::combine::simpleCombine<ui32, IS_REVERSE>(this->value, value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_r(const ui32 value, const ui8 shift) const __LL_EXCEPT__ {
			return hash::combine::simpleCombine<ui32, IS_REVERSE>(value, this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_l_noshift(const ui32 value) const __LL_EXCEPT__ {
			return hash::combine::simple32Combine_noshift<IS_REVERSE>(this->value, value);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_r_noshift(const ui32 value) const __LL_EXCEPT__ {
			return hash::combine::simple32Combine_noshift<IS_REVERSE>(value, this->value);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_l(const ui8 shift) const __LL_EXCEPT__ {
			return hash::combine::simple32Combine_l<IS_REVERSE>(this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_r(const ui8 shift) const __LL_EXCEPT__ {
			return hash::combine::simple32Combine_r<IS_REVERSE>(this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_l() const __LL_EXCEPT__ {
			return hash::combine::simple32Combine_l<IS_REVERSE>(this->value);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_r() const __LL_EXCEPT__ {
			return hash::combine::simple32Combine_r<IS_REVERSE>(this->value);
		}

		__LL_NODISCARD__ constexpr hash::Hash32 mur_l(const ui32 value) const __LL_EXCEPT__ {
			return hash::combine::murmur32Combine(this->value, value);
		}
		__LL_NODISCARD__ constexpr hash::Hash32 mur_r(const ui32 value) const __LL_EXCEPT__ {
			return hash::combine::murmur32Combine(value, this->value);
		}
		__LL_NODISCARD__ constexpr hash::Hash32 mur_l() const __LL_EXCEPT__ {
			return hash::combine::murmur32Combine_l(this->value);
		}
		__LL_NODISCARD__ constexpr hash::Hash32 mur_r() const __LL_EXCEPT__ {
			return hash::combine::murmur32Combine_r(this->value);
		}

		#pragma endregion

		#pragma endregion
};

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

		__LL_NODISCARD__ constexpr ll_bool_t operator>(const Hash64& other) const __LL_EXCEPT__ {
			return this->value > other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const Hash64& other) const __LL_EXCEPT__ {
			return this->value >= other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const Hash64& other) const __LL_EXCEPT__ {
			return this->value < other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const Hash64& other) const __LL_EXCEPT__ {
			return this->value <= other.value;
		}

		constexpr void clear() __LL_EXCEPT__ { this->value = ZERO_UI64; }

		#pragma endregion
		#pragma region CombineAndHash
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l(const ui64 value, const ui8 shift) const __LL_EXCEPT__ {
			return hash::combine::simpleCombine<ui64, IS_REVERSE>(this->value, value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r(const ui64 value, const ui8 shift) const __LL_EXCEPT__ {
			return hash::combine::simpleCombine<ui64, IS_REVERSE>(value, this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l_noshift(const ui64 value) const __LL_EXCEPT__ {
			return hash::combine::simple64Combine_noshift<IS_REVERSE>(this->value, value);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r_noshift(const ui64 value) const __LL_EXCEPT__ {
			return hash::combine::simple64Combine_noshift<IS_REVERSE>(value, this->value);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l(const ui8 shift) const __LL_EXCEPT__ {
			return hash::combine::simple64Combine_l<IS_REVERSE>(this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r(const ui8 shift) const __LL_EXCEPT__ {
			return hash::combine::simple64Combine_r<IS_REVERSE>(this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l() const __LL_EXCEPT__ {
			return hash::combine::simple64Combine_l<IS_REVERSE>(this->value);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r() const __LL_EXCEPT__ {
			return hash::combine::simple64Combine_r<IS_REVERSE>(this->value);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 mur_l(const ui64 value) const __LL_EXCEPT__ {
			return hash::combine::murmur64Combine(this->value, value);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 mur_r(const ui64 value) const __LL_EXCEPT__ {
			return hash::combine::murmur64Combine(value, this->value);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 mur_l() const __LL_EXCEPT__ {
			return hash::combine::murmur64Combine_l(this->value);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 mur_r() const __LL_EXCEPT__ {
			return hash::combine::murmur64Combine_r(this->value);
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

		__LL_NODISCARD__ constexpr ll_bool_t operator>(const Hash128& other) const __LL_EXCEPT__ {
			if (this->high > other.high) return LL_TRUE;
			else if (this->high < other.high) return LL_FALSE;
			else return this->low > other.low;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const Hash128& other) const __LL_EXCEPT__ {
			if (this->high > other.high) return LL_TRUE;
			else if (this->high < other.high) return LL_FALSE;
			else return this->low >= other.low;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const Hash128& other) const __LL_EXCEPT__ {
			if (this->high < other.high) return LL_TRUE;
			else if (this->high > other.high) return LL_FALSE;
			else return this->low < other.low;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const Hash128& other) const __LL_EXCEPT__ {
			if (this->high < other.high) return LL_TRUE;
			else if (this->high > other.high) return LL_FALSE;
			else return this->low <= other.low;
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
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l(const ui8 shift) const __LL_EXCEPT__ {
			return hash::combine::simpleCombine<ui64, IS_REVERSE>(this->low, this->high, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r(const ui8 shift) const __LL_EXCEPT__ {
			return hash::combine::simpleCombine<ui64, IS_REVERSE>(this->high, this->low, shift);
		}

		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l() const __LL_EXCEPT__ {
			return hash::combine::simple64Combine_noshift<IS_REVERSE>(this->low, this->high);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r() const __LL_EXCEPT__ {
			return hash::combine::simple64Combine_noshift<IS_REVERSE>(this->high, this->low);
		}

		// Low left, high right
		__LL_NODISCARD__ constexpr hash::Hash64 mur_l() const __LL_EXCEPT__ {
			return hash::combine::murmur64Combine(this->low, this->high);
		}
		// Low right, high left
		__LL_NODISCARD__ constexpr hash::Hash64 mur_r() const __LL_EXCEPT__ {
			return hash::combine::murmur64Combine(this->high, this->low);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 toHash64() const __LL_EXCEPT__ {
			return hash::Hash64(this->mur_l());
		}
		__LL_NODISCARD__ constexpr operator ui64() const __LL_EXCEPT__ { return this->toHash64(); }

		#pragma endregion

		#pragma endregion
};

__LL_VAR_INLINE__ constexpr hash::OptionalHash32 INVALID_HASH32 = std::nullopt;
__LL_VAR_INLINE__ constexpr hash::OptionalHash64 INVALID_HASH64 = std::nullopt;
__LL_VAR_INLINE__ constexpr hash::OptionalHash128 INVALID_HASH128 = std::nullopt;

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASHTYPES_HPP_
