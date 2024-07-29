//////////////////////////////////////////////
//	hash_types.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHTYPES_HPP_) // Guard && version protector
	#if LLANYLIB_HASHTYPES_MAYOR_ != 8 || LLANYLIB_HASHTYPES_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "hash_types.hpp version error!"
		#else
			#error "hash_types.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASHTYPES_MAYOR_ || LLANYLIB_HASHTYPES_MINOR_

#else !defined(LLANYLIB_HASHTYPES_HPP_)
#define LLANYLIB_HASHTYPES_HPP_
#define LLANYLIB_HASHTYPES_MAYOR_ 8
#define LLANYLIB_HASHTYPES_MINOR_ 0

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
		constexpr Hash32() noexcept : value(ZERO_UI32) {}
		constexpr Hash32(const ui32 value) noexcept : value(value) {}
		constexpr ~Hash32() noexcept {}

		#pragma endregion
		#pragma region CopyMove
		constexpr Hash32(const Hash32& other) noexcept : value(other.value) {}
		constexpr Hash32& operator=(const Hash32& other) noexcept {
			this->value = other.value;
			return *this;
		}

		constexpr Hash32(Hash32&& other) noexcept : Hash32(other) { other.Hash32::clear(); }
		constexpr Hash32& operator=(Hash32&& other) noexcept {
			Hash32::operator=(other);
			other.Hash32::clear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename const Hash32*() const noexcept = delete;
		__LL_NODISCARD__ constexpr operator typename Hash32*() noexcept = delete;

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Other
		__LL_NODISCARD__ constexpr operator ui32() const noexcept { return this->value; }
		__LL_NODISCARD__ constexpr ui32 get() const noexcept { return this->value; }

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Hash32& other) const noexcept {
			return this->value == other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Hash32& other) const noexcept {
			return !this->operator==(other);
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator>(const Hash32& other) const noexcept {
			return this->value > other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const Hash32& other) const noexcept {
			return this->value >= other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const Hash32& other) const noexcept {
			return this->value < other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const Hash32& other) const noexcept {
			return this->value <= other.value;
		}

		constexpr void clear() noexcept { this->value = ZERO_UI32; }

		#pragma endregion
		#pragma region CombineAndHash
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_l(const ui32 value, const ui8 shift) const noexcept {
			return hash::combine::simpleCombine<ui32, IS_REVERSE>(this->value, value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_r(const ui32 value, const ui8 shift) const noexcept {
			return hash::combine::simpleCombine<ui32, IS_REVERSE>(value, this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_l_noshift(const ui32 value) const noexcept {
			return hash::combine::simple32Combine_noshift<IS_REVERSE>(this->value, value);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_r_noshift(const ui32 value) const noexcept {
			return hash::combine::simple32Combine_noshift<IS_REVERSE>(value, this->value);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_l(const ui8 shift) const noexcept {
			return hash::combine::simple32Combine_l<IS_REVERSE>(this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_r(const ui8 shift) const noexcept {
			return hash::combine::simple32Combine_r<IS_REVERSE>(this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_l() const noexcept {
			return hash::combine::simple32Combine_l<IS_REVERSE>(this->value);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_r() const noexcept {
			return hash::combine::simple32Combine_r<IS_REVERSE>(this->value);
		}

		__LL_NODISCARD__ constexpr hash::Hash32 mur_l(const ui32 value) const noexcept {
			return hash::combine::murmur32Combine(this->value, value);
		}
		__LL_NODISCARD__ constexpr hash::Hash32 mur_r(const ui32 value) const noexcept {
			return hash::combine::murmur32Combine(value, this->value);
		}
		__LL_NODISCARD__ constexpr hash::Hash32 mur_l() const noexcept {
			return hash::combine::murmur32Combine_l(this->value);
		}
		__LL_NODISCARD__ constexpr hash::Hash32 mur_r() const noexcept {
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
		constexpr Hash64() noexcept : value(ZERO_UI64) {}
		constexpr Hash64(const ui64 value) noexcept : value(value) {}
		constexpr ~Hash64() noexcept {}

		#pragma endregion
		#pragma region CopyMove
		constexpr Hash64(const Hash64& other) noexcept : value(other.value) {}
		constexpr Hash64& operator=(const Hash64& other) noexcept {
			this->value = other.value;
			return *this;
		}

		constexpr Hash64(Hash64&& other) noexcept : Hash64(other) { other.Hash64::clear(); }
		constexpr Hash64& operator=(Hash64&& other) noexcept {
			Hash64::operator=(other);
			other.Hash64::clear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename const Hash64*() const noexcept = delete;
		__LL_NODISCARD__ constexpr operator typename Hash64*() noexcept = delete;

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Other
		__LL_NODISCARD__ constexpr operator ui64() const noexcept { return this->value; }
		__LL_NODISCARD__ constexpr ui64 get() const noexcept { return this->value; }

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Hash64& other) const noexcept {
			return this->value == other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Hash64& other) const noexcept {
			return !this->operator==(other);
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator>(const Hash64& other) const noexcept {
			return this->value > other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const Hash64& other) const noexcept {
			return this->value >= other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const Hash64& other) const noexcept {
			return this->value < other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const Hash64& other) const noexcept {
			return this->value <= other.value;
		}

		constexpr void clear() noexcept { this->value = ZERO_UI64; }

		#pragma endregion
		#pragma region CombineAndHash
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l(const ui64 value, const ui8 shift) const noexcept {
			return hash::combine::simpleCombine<ui64, IS_REVERSE>(this->value, value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r(const ui64 value, const ui8 shift) const noexcept {
			return hash::combine::simpleCombine<ui64, IS_REVERSE>(value, this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l_noshift(const ui64 value) const noexcept {
			return hash::combine::simple64Combine_noshift<IS_REVERSE>(this->value, value);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r_noshift(const ui64 value) const noexcept {
			return hash::combine::simple64Combine_noshift<IS_REVERSE>(value, this->value);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l(const ui8 shift) const noexcept {
			return hash::combine::simple64Combine_l<IS_REVERSE>(this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r(const ui8 shift) const noexcept {
			return hash::combine::simple64Combine_r<IS_REVERSE>(this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l() const noexcept {
			return hash::combine::simple64Combine_l<IS_REVERSE>(this->value);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r() const noexcept {
			return hash::combine::simple64Combine_r<IS_REVERSE>(this->value);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 mur_l(const ui64 value) const noexcept {
			return hash::combine::murmur64Combine(this->value, value);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 mur_r(const ui64 value) const noexcept {
			return hash::combine::murmur64Combine(value, this->value);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 mur_l() const noexcept {
			return hash::combine::murmur64Combine_l(this->value);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 mur_r() const noexcept {
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
		constexpr Hash128() noexcept : low(ZERO_UI64), high(ZERO_UI64) {}
		constexpr Hash128(const ui64 low, const ui64 high) noexcept
			: low(low), high(high) {}
		constexpr ~Hash128() noexcept {}

		#pragma endregion
		#pragma region CopyMove
		constexpr Hash128(const Hash128& other) noexcept
			: low(other.low), high(other.high) {}
		constexpr Hash128& operator=(const Hash128& other) noexcept {
			this->low = other.low;
			this->high = other.high;
			return *this;
		}
		constexpr Hash128(Hash128&& other) noexcept
			: low(other.low), high(other.high) { other.Hash128::clear(); }
		constexpr Hash128& operator=(Hash128&& other) noexcept {
			this->low = other.low;
			this->high = other.high;
			other.Hash128::clear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator const Hash128* () const noexcept = delete;
		__LL_NODISCARD__ constexpr operator Hash128* () noexcept = delete;

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Other
		__LL_NODISCARD__ constexpr ui64 getLow() const noexcept { return this->low; }
		__LL_NODISCARD__ constexpr ui64 getHigh() const noexcept { return this->high; }

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Hash128& other) const noexcept {
			return ((this->high == other.high) && (this->low == other.low));
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Hash128& other) const noexcept {
			return !this->operator==(other);
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator>(const Hash128& other) const noexcept {
			if (this->high > other.high) return LL_TRUE;
			else if (this->high < other.high) return LL_FALSE;
			else return this->low > other.low;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const Hash128& other) const noexcept {
			if (this->high > other.high) return LL_TRUE;
			else if (this->high < other.high) return LL_FALSE;
			else return this->low >= other.low;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const Hash128& other) const noexcept {
			if (this->high < other.high) return LL_TRUE;
			else if (this->high > other.high) return LL_FALSE;
			else return this->low < other.low;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const Hash128& other) const noexcept {
			if (this->high < other.high) return LL_TRUE;
			else if (this->high > other.high) return LL_FALSE;
			else return this->low <= other.low;
		}

		__LL_NODISCARD__ constexpr ui64& operator[](const len_t pos) noexcept {
			return (pos == ZERO_UI64) ? this->low : this->high;
		}
		__LL_NODISCARD__ constexpr ui64 operator[](const len_t pos) const noexcept {
			return (pos == ZERO_UI64) ? this->low : this->high;
		}

		constexpr void clear() noexcept {
			this->low = ZERO_UI64;
			this->high = ZERO_UI64;
		}

		#pragma endregion
		#pragma region CombineAndHash
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l(const ui8 shift) const noexcept {
			return hash::combine::simpleCombine<ui64, IS_REVERSE>(this->low, this->high, shift);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r(const ui8 shift) const noexcept {
			return hash::combine::simpleCombine<ui64, IS_REVERSE>(this->high, this->low, shift);
		}

		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l() const noexcept {
			return hash::combine::simple64Combine_noshift<IS_REVERSE>(this->low, this->high);
		}
		template<ll_bool_t IS_REVERSE = LL_FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r() const noexcept {
			return hash::combine::simple64Combine_noshift<IS_REVERSE>(this->high, this->low);
		}

		// Low left, high right
		__LL_NODISCARD__ constexpr hash::Hash64 mur_l() const noexcept {
			return hash::combine::murmur64Combine(this->low, this->high);
		}
		// Low right, high left
		__LL_NODISCARD__ constexpr hash::Hash64 mur_r() const noexcept {
			return hash::combine::murmur64Combine(this->high, this->low);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 toHash64() const noexcept {
			return hash::Hash64(this->mur_l());
		}
		__LL_NODISCARD__ constexpr operator ui64() const noexcept { return this->toHash64(); }

		#pragma endregion

		#pragma endregion
};

__LL_VAR_INLINE__ constexpr hash::OptionalHash32 INVALID_HASH32 = std::nullopt;
__LL_VAR_INLINE__ constexpr hash::OptionalHash64 INVALID_HASH64 = std::nullopt;
__LL_VAR_INLINE__ constexpr hash::OptionalHash128 INVALID_HASH128 = std::nullopt;

template<class HashType>
class HashChecker {
	#pragma region Types
	public:
		using OptionalHash = std::optional<HashType>;
		using Hash = HashType;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(hash::__::is_hash_type_v<HashType>,
			"Needs to be a valid hash type! If you want to use your own hash objects comment this assert");

		static_assert(!std::is_reference_v<HashType>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<HashType>, "Const type is forbidden!");

		static_assert(std::is_nothrow_constructible_v<HashType>, "HashType needs a noexcept constructor!");
		static_assert(std::is_nothrow_destructible_v<HashType>, "HashType needs a noexcept destructor!");
		static_assert(std::is_copy_constructible_v<HashType>, "HashType needs a noexcept copy constructor!");
		static_assert(std::is_copy_assignable_v<HashType>, "HashType needs a noexcept copy asignable!");
		static_assert(std::is_move_constructible_v<HashType>, "HashType needs a noexcept move constructor!");
		static_assert(std::is_move_assignable_v<HashType>, "HashType needs a noexcept move asignable!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr HashChecker() noexcept {}
		constexpr ~HashChecker() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr HashChecker(const HashChecker&) noexcept {}
		constexpr HashChecker& operator=(const HashChecker&) noexcept { return *this; }
		constexpr HashChecker(HashChecker&&) noexcept {}
		constexpr HashChecker& operator=(HashChecker&&) noexcept { return *this; }

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const HashChecker* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator HashChecker* () noexcept { return this; }

		#pragma endregion

	#pragma endregion
};

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASHTYPES_HPP_
