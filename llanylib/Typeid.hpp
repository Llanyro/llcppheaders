//////////////////////////////////////////////
//	Typeid.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPEID_HPP_) // Guard && version protector
	#if LLANYLIB_TYPEID_MAYOR_ != 8 || LLANYLIB_TYPEID_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Typeid.hpp version error!"
		#else
			#error "Typeid.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_TYPEID_MAYOR_ || LLANYLIB_TYPEID_MINOR_

#else !defined(LLANYLIB_TYPEID_HPP_)
#define LLANYLIB_TYPEID_HPP_
#define LLANYLIB_TYPEID_MAYOR_ 8
#define LLANYLIB_TYPEID_MINOR_ 0

#include "ArrayPair.hpp"
#include "hash_types.hpp"

namespace llcpp {
namespace meta {

// Requires a char type to fit software chars: char, wchar...
template<class CharType, class HashType>
class Typeid {
	#pragma region Types
	public:
		using NameType = meta::ArrayPair<CharType>;
		using OptionalHash = std::optional<HashType>;

		template<class HashGenerator>
		using HashNameTypeFunction = OptionalHash(HashGenerator::*)(const NameType&) noexcept;
		template<class HashGenerator>
		using HashNameTypeConstFunction = OptionalHash(HashGenerator::*)(const NameType&) const noexcept;

		template<class HashGenerator>
		using HashCharTypeFunction = OptionalHash(HashGenerator::*)(const CharType*, len_t) noexcept;
		template<class HashGenerator>
		using HashCharTypeConstFunction = OptionalHash(HashGenerator::*)(const CharType*, len_t) const noexcept;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_char_type_v<CharType>, "Type must be a char type");

		static_assert(!std::is_reference_v<CharType>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<CharType>, "Const type is forbidden!");

		static_assert(!std::is_reference_v<HashType>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<HashType>, "Const type is forbidden!");

		static_assert(std::is_nothrow_constructible_v<HashType>, "HashType needs a noexcept constructor!");
		static_assert(std::is_nothrow_destructible_v<HashType>, "HashType needs a noexcept destructor!");
		static_assert(std::is_copy_constructible_v<HashType>, "HashType needs a noexcept copy constructor!");
		static_assert(std::is_copy_assignable_v<HashType>, "HashType needs a noexcept copy asignable!");
		static_assert(std::is_move_constructible_v<HashType>, "HashType needs a noexcept move constructor!");
		static_assert(std::is_move_assignable_v<HashType>, "HashType needs a noexcept move asignable!");

	#pragma endregion
	#pragma region Attributes
	private:
		HashType hash_name;
		NameType name;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		Typeid() noexcept : hash_name(), name() {}
		~Typeid() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Typeid(const Typeid& other) noexcept
			: hash_name(other.hash_name), name(other.name) {}
		constexpr Typeid& operator=(const Typeid& other) noexcept {
			this->hash_name = other.hash_name;
			this->name = other.name;
			return *this;
		}
		constexpr Typeid(Typeid&& other) noexcept
			: hash_name(std::move(other.hash_name))
			, name(std::move(other.name))
		{}
		constexpr Typeid& operator=(Typeid&& other) noexcept {
			this->hash_name = std::move(other.hash_name);
			this->name = std::move(other.name);
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ operator const Typeid* () const noexcept { return this; }
		__LL_NODISCARD__ operator Typeid* () noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr const hash::Hash64& hash() const noexcept {
			return this->hash_name;
		}
		__LL_NODISCARD__ constexpr const NameType& getName() const noexcept {
			return this->name;
		}

		__LL_NODISCARD__ constexpr void reset(const NameType& name, const HashType& hash_name) noexcept {
			this->name = name;
			this->hash_name = hash_name;
		}
		__LL_NODISCARD__ constexpr void reset(const NameType& name, HashType&& hash_name) noexcept {
			this->name = name;
			this->hash_name = std::move(hash_name);
		}
		__LL_NODISCARD__ constexpr void reset(NameType&& name, const HashType& hash_name) noexcept {
			this->name = std::move(name);
			this->hash_name = hash_name;
		}
		__LL_NODISCARD__ constexpr void reset(NameType&& name, HashType&& hash_name) noexcept {
			this->name = std::move(name);
			this->hash_name = std::move(hash_name);
		}

		template<class HashGenerator>
		__LL_NODISCARD__ constexpr ll_bool_t reset(const NameType& name, HashGenerator& gen) noexcept {
			using HashName = HashNameTypeFunction<HashGenerator>;
			using HashNameConst = HashNameTypeConstFunction<HashGenerator>;
			using HashChar = HashCharTypeFunction<HashGenerator>;
			using HashCharConst = HashCharTypeConstFunction<HashGenerator>;

			OptionalHash result;

			if constexpr (hash::traits::has_any_hash_function<HashGenerator, HashName, HashNameConst>)
				result = gen.hash(name);
			else if constexpr (hash::traits::has_any_hash_function<HashGenerator, HashChar, HashCharConst>)
				result = gen.hash(name);
			else return LL_FALSE;

			if (result.has_value()) this->hash_name = *result;
			else this->hash_name = HashType();
			this->name = name;
		}
		template<class HashGenerator>
		__LL_NODISCARD__ constexpr ll_bool_t reset(NameType&& name, HashGenerator& gen) noexcept {
			using HashName = HashNameTypeFunction<HashGenerator>;
			using HashNameConst = HashNameTypeConstFunction<HashGenerator>;
			using HashChar = HashCharTypeFunction<HashGenerator>;
			using HashCharConst = HashCharTypeConstFunction<HashGenerator>;

			OptionalHash result;

			if constexpr (hash::traits::has_any_hash_function<HashGenerator, HashName, HashNameConst>)
				result = gen.hash(name);
			else if constexpr (hash::traits::has_any_hash_function<HashGenerator, HashChar, HashCharConst>)
				result = gen.hash(name);
			else return LL_FALSE;

			if (result.has_value()) this->hash_name = *result;
			else this->hash_name = HashType();
			this->name = std::move(name);
		}

		#pragma endregion
	#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPEID_HPP_
