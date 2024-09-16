//////////////////////////////////////////////
//	Typeid.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPEID_HPP_) // Guard && version protector
	#if LLANYLIB_TYPEID_MAYOR_ != 9 || LLANYLIB_TYPEID_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Typeid.hpp version error!"
		#else
			#error "Typeid.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_TYPEID_MAYOR_ || LLANYLIB_TYPEID_MINOR_

#else !defined(LLANYLIB_TYPEID_HPP_)
#define LLANYLIB_TYPEID_HPP_
#define LLANYLIB_TYPEID_MAYOR_ 9
#define LLANYLIB_TYPEID_MINOR_ 0

#include "ArrayPair.hpp"
#include "hash_types.hpp"

namespace llcpp {
namespace meta {

// Requires a char type to fit software chars: char, wchar...
template<class _CharType, class _HashType>
class Typeid {
	#pragma region Types
	public:
		// Class related
		using _MyType	= Typeid;

		// Types and enums
		using CharType	= _CharType;
		using HashType	= _HashType;
		using NameType = meta::ArrayPair<CharType>;

		template<class HashGenerator>
		using HashNameTypeFunction		= HashType(HashGenerator::*)(const NameType&) noexcept;
		template<class HashGenerator>
		using HashNameTypeConstFunction = HashType(HashGenerator::*)(const NameType&) const noexcept;

		template<class HashGenerator>
		using HashCharTypeFunction		= HashType(HashGenerator::*)(const CharType*, len_t) noexcept;
		template<class HashGenerator>
		using HashCharTypeConstFunction = HashType(HashGenerator::*)(const CharType*, len_t) const noexcept;

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
		constexpr Typeid() noexcept : hash_name(), name() {}
		constexpr ~Typeid() noexcept {}

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
			: hash_name(std::forward<HashType&&>(other.hash_name))
			, name(std::forward<NameType&&>(other.name))
		{}
		constexpr Typeid& operator=(Typeid&& other) noexcept {
			this->hash_name = std::forward<HashType&&>(other.hash_name);
			this->name = std::forward<NameType&&>(other.name);
			return *this;
		}

		constexpr Typeid(const NameType& name, const HashType& hash_name) noexcept
			: name(name)
			, hash_name(hash_name)
		{}
		constexpr Typeid(const NameType& name, HashType&& hash_name) noexcept
			: name(name)
			, hash_name(std::forward<HashType&&>(hash_name))
		{}
		constexpr Typeid(NameType&& name, const HashType& hash_name) noexcept
			: name(std::forward<NameType&&>(name))
			, hash_name(hash_name)
		{}
		constexpr Typeid(NameType&& name, HashType&& hash_name) noexcept
			: name(std::forward<NameType&&>(name))
			, hash_name(std::forward<HashType&&>(hash_name))
		{}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Typeid* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Typeid* () noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr const hash::Hash64& hash() const noexcept { return this->hash_name; }
		__LL_NODISCARD__ constexpr const NameType& getName() const noexcept { return this->name; }

		constexpr void reset(const NameType& name, const HashType& hash_name) noexcept {
			this->name = name;
			this->hash_name = hash_name;
		}
		constexpr void reset(const NameType& name, HashType&& hash_name) noexcept {
			this->name = name;
			this->hash_name = std::forward<HashType&&>(hash_name);
		}
		constexpr void reset(NameType&& name, const HashType& hash_name) noexcept {
			this->name = std::forward<NameType&&>(name);
			this->hash_name = hash_name;
		}
		constexpr void reset(NameType&& name, HashType&& hash_name) noexcept {
			this->name = std::forward<NameType&&>(name);
			this->hash_name = std::forward<HashType&&>(hash_name);
		}

	private:
		template<class HashGenerator>
		constexpr void reset_impl(const NameType& name, HashGenerator& gen) noexcept {
			using HashName = HashNameTypeFunction<HashGenerator>;
			using HashNameConst = HashNameTypeConstFunction<HashGenerator>;
			using HashChar = HashCharTypeFunction<HashGenerator>;
			using HashCharConst = HashCharTypeConstFunction<HashGenerator>;
			constexpr ll_bool_t HAS_ARRAY_HASH =
				traits::common::has_hash_function_v<HashGenerator, HashName>
				|| traits::common::has_hash_function_v<HashGenerator, HashNameConst>;
			constexpr ll_bool_t HAS_CHAR_HASH =
				traits::common::has_hash_function_v<HashGenerator, HashChar>
				|| traits::common::has_hash_function_v<HashGenerator, HashCharConst>;

			static_assert(HAS_ARRAY_HASH || HAS_CHAR_HASH,
				"This function requires by HashGenerator a hash function to generate a hash of an "
				"NameType or a CharType"
				);
			if constexpr (HAS_ARRAY_HASH)
				this->hash_name = gen.hash(name);
			else if constexpr (HAS_CHAR_HASH)
				this->hash_name = gen.hash(name.begin(), name.lenght());
		}
	public:
		template<class HashGenerator>
		constexpr void reset(const NameType& name, HashGenerator& gen) noexcept {
			this->reset_impl(name, gen);
			this->name = name;
		}
		template<class HashGenerator>
		constexpr void reset(NameType&& name, HashGenerator& gen) noexcept {
			this->reset_impl(name, gen);
			this->name = std::forward<NameType&&>(name);
		}

		#pragma endregion
	#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPEID_HPP_
