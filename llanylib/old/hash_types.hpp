//////////////////////////////////////////////
//	hash_types.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHTYPES_HPP_) // Guard && version protector
	#if LLANYLIB_HASHTYPES_MAYOR_ != 9 || LLANYLIB_HASHTYPES_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "hash_types.hpp version error!"
		#else
			#error "hash_types.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASHTYPES_MAYOR_ || LLANYLIB_HASHTYPES_MINOR_

#else !defined(LLANYLIB_HASHTYPES_HPP_)
#define LLANYLIB_HASHTYPES_HPP_
#define LLANYLIB_HASHTYPES_MAYOR_ 9
#define LLANYLIB_HASHTYPES_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace meta {
namespace hash {


//static constexpr Hash INVALID_HASH = Hash();

//template<class _T, _T _NULL_VALUE>
using _T = int;
constexpr _T _NULL_VALUE = 0;
class Hash {
	#pragma region Types
	public:
		// Class related
		using _MyType				= Hash;

		// Types and enums
		using T						= _T;
		using cinput_t				= traits::cinput<T>;
		using input_t				= traits::input<T>;
		using T_Class				= traits::T_Class<T>;

		// Signatures
		using EqualSignature		= ll_bool_t(T_Class::*)(cinput_t) const noexcept;
		using GreaterSignature		= ll_bool_t(T_Class::*)(cinput_t) const noexcept;
		using LowerSignature		= ll_bool_t(T_Class::*)(cinput_t) const noexcept;
		using EqualGreaterSignature	= ll_bool_t(T_Class::*)(cinput_t) const noexcept;
		using EqualLowerSignature	= ll_bool_t(T_Class::*)(cinput_t) const noexcept;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr T NULL_VALUE = _NULL_VALUE;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");

		static_assert(traits::common::has_operator_eq_function_v<T, EqualSignature>,
			"T::operator==(const T) const noexcept is required!");
		static_assert(traits::common::has_operator_no_eq_function_v<T, EqualSignature>,
			"T::operator!=(const T) const noexcept is required!");

	#pragma endregion
	#pragma region Attibutes
	private:
		T value;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr Hash() noexcept : value(NULL_VALUE) {}
		constexpr ~Hash() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Hash(const Hash& other) noexcept
			: value(std::forward<cinput_t>(other.value)) {}
		constexpr Hash& operator=(const Hash& other) noexcept {
			this->value = std::forward<cinput_t>(other.value);
			return *this;
		}
		constexpr Hash(Hash&& other) noexcept
			: value(std::forward<T&&>(other)) {}
		constexpr Hash& operator=(Hash&& other) noexcept {
			this->value = std::forward<T&&>(other);
			return *this;
		}

		constexpr Hash(cinput_t value) noexcept
			: value(std::forward<cinput_t>(value)) {}
		constexpr Hash& operator=(cinput_t value) noexcept {
			this->value = std::forward<cinput_t>(value);
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Hash*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Hash*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr explicit operator input_t() noexcept { return this->value; }
		__LL_NODISCARD__ constexpr explicit operator cinput_t() const noexcept { return this->value; }

		__LL_NODISCARD__ constexpr input_t get() noexcept { return this->value; }
		__LL_NODISCARD__ constexpr cinput_t get() const noexcept { return this->value; }

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Hash& other) const noexcept {
			return this->value == other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Hash& other) const noexcept {
			return !this->operator==(other);
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator>(const Hash& other) const noexcept {
			return this->value > other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const Hash& other) const noexcept {
			return this->value >= other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const Hash& other) const noexcept {
			return this->value < other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const Hash& other) const noexcept {
			return this->value <= other.value;
		}

		constexpr void clear() noexcept { this->value = ZERO_UI32; }


		#pragma endregion
	#pragma endregion


};

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
		__LL_NODISCARD__ constexpr explicit operator typename const Hash32*() const noexcept = delete;
		__LL_NODISCARD__ constexpr explicit operator typename Hash32*() noexcept = delete;

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Other
		__LL_NODISCARD__ constexpr explicit operator ui32() const noexcept { return this->value; }
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
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_l(const ui32 value, const ui8 shift) const noexcept {
			return hash::algorithm::simpleCombine<ui32, IS_REVERSE>(this->value, value, shift);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_r(const ui32 value, const ui8 shift) const noexcept {
			return hash::algorithm::simpleCombine<ui32, IS_REVERSE>(value, this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_l_noshift(const ui32 value) const noexcept {
			return hash::algorithm::simple32Combine_noshift<IS_REVERSE>(this->value, value);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_r_noshift(const ui32 value) const noexcept {
			return hash::algorithm::simple32Combine_noshift<IS_REVERSE>(value, this->value);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_l(const ui8 shift) const noexcept {
			return hash::algorithm::simple32Combine_l<IS_REVERSE>(this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_r(const ui8 shift) const noexcept {
			return hash::algorithm::simple32Combine_r<IS_REVERSE>(this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_l() const noexcept {
			return hash::algorithm::simple32Combine_l<IS_REVERSE>(this->value);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash32 simpleCombine_r() const noexcept {
			return hash::algorithm::simple32Combine_r<IS_REVERSE>(this->value);
		}

		__LL_NODISCARD__ constexpr hash::Hash32 mur_l(const ui32 value) const noexcept {
			return hash::algorithm::murmur32Combine(this->value, value);
		}
		__LL_NODISCARD__ constexpr hash::Hash32 mur_r(const ui32 value) const noexcept {
			return hash::algorithm::murmur32Combine(value, this->value);
		}
		__LL_NODISCARD__ constexpr hash::Hash32 mur_l() const noexcept {
			return hash::algorithm::murmur32Combine_l(this->value);
		}
		__LL_NODISCARD__ constexpr hash::Hash32 mur_r() const noexcept {
			return hash::algorithm::murmur32Combine_r(this->value);
		}

		__LL_NODISCARD__ constexpr hash::Hash32 fastCombine(const ui32 value) const noexcept {
			return this->simpleCombine_r_noshift(value);
		}
		__LL_NODISCARD__ constexpr hash::Hash32 fastCombine() const noexcept {
			return this->simpleCombine_r();
		}
		__LL_NODISCARD__ constexpr hash::Hash32 slowcombine(const ui32 value) const noexcept {
			return this->mur_r(value);
		}
		__LL_NODISCARD__ constexpr hash::Hash32 slowCombine() const noexcept {
			return this->mur_l();
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
		__LL_NODISCARD__ constexpr explicit operator typename const Hash64*() const noexcept = delete;
		__LL_NODISCARD__ constexpr explicit operator typename Hash64*() noexcept = delete;

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Other
		__LL_NODISCARD__ constexpr explicit operator ui64() const noexcept { return this->value; }
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
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l(const ui64 value, const ui8 shift) const noexcept {
			return hash::algorithm::simpleCombine<ui64, IS_REVERSE>(this->value, value, shift);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r(const ui64 value, const ui8 shift) const noexcept {
			return hash::algorithm::simpleCombine<ui64, IS_REVERSE>(value, this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l_noshift(const ui64 value) const noexcept {
			return hash::algorithm::simple64Combine_noshift<IS_REVERSE>(this->value, value);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r_noshift(const ui64 value) const noexcept {
			return hash::algorithm::simple64Combine_noshift<IS_REVERSE>(value, this->value);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l(const ui8 shift) const noexcept {
			return hash::algorithm::simple64Combine_l<IS_REVERSE>(this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r(const ui8 shift) const noexcept {
			return hash::algorithm::simple64Combine_r<IS_REVERSE>(this->value, shift);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l() const noexcept {
			return hash::algorithm::simple64Combine_l<IS_REVERSE>(this->value);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r() const noexcept {
			return hash::algorithm::simple64Combine_r<IS_REVERSE>(this->value);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 mur_l(const ui64 value) const noexcept {
			return hash::algorithm::murmur64Combine(this->value, value);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 mur_r(const ui64 value) const noexcept {
			return hash::algorithm::murmur64Combine(value, this->value);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 mur_l() const noexcept {
			return hash::algorithm::murmur64Combine_l(this->value);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 mur_r() const noexcept {
			return hash::algorithm::murmur64Combine_r(this->value);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 fastCombine(const ui64 value) const noexcept {
			return this->simpleCombine_r_noshift(value);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 fastCombine() const noexcept {
			return this->simpleCombine_r();
		}
		__LL_NODISCARD__ constexpr hash::Hash64 slowcombine(const ui64 value) const noexcept {
			return this->mur_r(value);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 slowCombine() const noexcept {
			return this->mur_l();
		}

		#pragma endregion

		#pragma endregion
};

class Hash128 {
	private:
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
		__LL_NODISCARD__ constexpr explicit operator const Hash128* () const noexcept = delete;
		__LL_NODISCARD__ constexpr explicit operator Hash128* () noexcept = delete;

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
			if (this->high > other.high) return llcpp::TRUE;
			else if (this->high < other.high) return llcpp::FALSE;
			else return this->low > other.low;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const Hash128& other) const noexcept {
			if (this->high > other.high) return llcpp::TRUE;
			else if (this->high < other.high) return llcpp::FALSE;
			else return this->low >= other.low;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const Hash128& other) const noexcept {
			if (this->high < other.high) return llcpp::TRUE;
			else if (this->high > other.high) return llcpp::FALSE;
			else return this->low < other.low;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const Hash128& other) const noexcept {
			if (this->high < other.high) return llcpp::TRUE;
			else if (this->high > other.high) return llcpp::FALSE;
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
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l(const ui8 shift) const noexcept {
			return hash::algorithm::simpleCombine<ui64, IS_REVERSE>(this->low, this->high, shift);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r(const ui8 shift) const noexcept {
			return hash::algorithm::simpleCombine<ui64, IS_REVERSE>(this->high, this->low, shift);
		}

		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_l() const noexcept {
			return hash::algorithm::simple64Combine_noshift<IS_REVERSE>(this->low, this->high);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash64 simpleCombine_r() const noexcept {
			return hash::algorithm::simple64Combine_noshift<IS_REVERSE>(this->high, this->low);
		}

		// Low left, high right
		__LL_NODISCARD__ constexpr hash::Hash64 mur_l() const noexcept {
			return hash::algorithm::murmur64Combine(this->low, this->high);
		}
		// Low right, high left
		__LL_NODISCARD__ constexpr hash::Hash64 mur_r() const noexcept {
			return hash::algorithm::murmur64Combine(this->high, this->low);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 toHash64() const noexcept {
			return hash::Hash64(this->mur_l());
		}
		__LL_NODISCARD__ constexpr explicit operator ui64() const noexcept { return this->toHash64(); }

		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash128 simpleCombine_l(const hash::Hash128& other, const ui8 shift) const noexcept {
			return
				hash::Hash128(
					hash::algorithm::simpleCombine<ui64, IS_REVERSE>(this->low, other.low, shift),
					hash::algorithm::simpleCombine<ui64, IS_REVERSE>(this->high, other.high, shift)
				);
		}
		template<ll_bool_t IS_REVERSE = llcpp::FALSE>
		__LL_NODISCARD__ constexpr hash::Hash128 simpleCombine_r(const hash::Hash128& other, const ui8 shift) const noexcept {
			return
				hash::Hash128(
					hash::algorithm::simpleCombine<ui64, IS_REVERSE>(other.low, this->low, shift),
					hash::algorithm::simpleCombine<ui64, IS_REVERSE>(other.high, this->high, shift)
				);
		}

		__LL_NODISCARD__ constexpr hash::Hash128 mur_l(const hash::Hash128& other) const noexcept {
			return
				hash::Hash128(
					hash::algorithm::murmur64Combine(this->low, other.low),
					hash::algorithm::murmur64Combine(this->high, other.high)
				);
		}
		__LL_NODISCARD__ constexpr hash::Hash128 mur_r(const hash::Hash128& other) const noexcept {
			return
				hash::Hash128(
					hash::algorithm::murmur64Combine(other.low, this->low),
					hash::algorithm::murmur64Combine(other.high, this->high)
				);
		}

		#pragma endregion

		#pragma endregion
};

//__LL_VAR_INLINE__ constexpr hash::Hash32 INVALID_HASH32 = std::nullopt;
//__LL_VAR_INLINE__ constexpr hash::Hash64 INVALID_HASH64 = std::nullopt;
//__LL_VAR_INLINE__ constexpr hash::Hash128 INVALID_HASH128 = std::nullopt;

template<class _HashType>
class HashChecker {
	#pragma region Types
	public:
		// Class related
		using _MyType		= HashChecker;

		// Types and enums
		using HashType		= _HashType;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_hash_type_v<HashType>,
			"Needs to be a valid hash type! If you want to use your own hash objects comment this assert");

		static_assert(traits::is_valid_type_checker_v<HashType>,
			"type_checker<HashType> detected an invalid type!");
		static_assert(traits::is_valid_class_checker_v<HashType>,
			"class_checker<HashType> detected an invalid class type!");

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
		__LL_NODISCARD__ constexpr explicit operator const HashChecker*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator HashChecker*() noexcept { return this; }

		#pragma endregion

	#pragma endregion
};

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASHTYPES_HPP_
