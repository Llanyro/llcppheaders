//////////////////////////////////////////////
//	hash_pack.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHPACKS_HPP_) // Guard && version protector
	#if LLANYLIB_HASHPACKS_MAYOR_ != 8 || LLANYLIB_HASHPACKS_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "hash_pack.hpp version error!"
		#else
			#error "hash_pack.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASHPACKS_MAYOR_ || LLANYLIB_HASHPACKS_MINOR_

#else !defined(LLANYLIB_HASHPACKS_HPP_)
#define LLANYLIB_HASHPACKS_HPP_
#define LLANYLIB_HASHPACKS_MAYOR_ 8
#define LLANYLIB_HASHPACKS_MINOR_ 0

#include "hash_types.hpp"

namespace llcpp {
namespace meta {
namespace hash {

template<class HashType = hash::Hash64>
class LL_SHARED_LIB HashGeneratorDummy {
	#pragma region Types
	public:
		using OptionalHash = std::optional<HashType>;
		using Hash = HashType;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr HashGeneratorDummy() noexcept {}
		constexpr ~HashGeneratorDummy() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr HashGeneratorDummy(const HashGeneratorDummy&) noexcept {}
		constexpr HashGeneratorDummy& operator=(const HashGeneratorDummy&) noexcept { return *this; }
		constexpr HashGeneratorDummy(HashGeneratorDummy&&) noexcept {}
		constexpr HashGeneratorDummy& operator=(HashGeneratorDummy&&) noexcept { return *this; }

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const HashGeneratorDummy* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator HashGeneratorDummy* () noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr OptionalHash hash(ll_string_t s, const len_t n) const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr OptionalHash hash(ll_wstring_t s, const len_t n) const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr OptionalHash hash(const std::string& s) const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr OptionalHash hash(const std::wstring& s) const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr OptionalHash hash(const meta::StrPair& s) const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr OptionalHash hash(const meta::wStrPair& s) const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr OptionalHash hash(const meta::Str& s) const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr OptionalHash hash(const meta::wStr& s) const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr OptionalHash hash(const HashType& h) const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr OptionalHash hash(const void* o, const meta::StrTypeid& id) const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr OptionalHash hash(const void* o, const meta::wStrTypeid& id) const noexcept {
			return std::nullopt;
		}

		#pragma endregion

	#pragma endregion
};

template<class HashType = hash::Hash64, class HashGenerator = hash::HashGeneratorDummy<HashType>>
class HashGeneratorChecker : public hash::HashChecker<HashType>, public HashGenerator {
	#pragma region Types
	public:
		using HashChecker = hash::HashChecker<HashType>;
		using OptionalHash = HashChecker::OptionalHash;
		using Hash = HashChecker::Hash;

		using HashConstFunction = OptionalHash(HashGenerator::*)(ll_string_t, len_t) const noexcept;
		using wHashConstFunction = OptionalHash(HashGenerator::*)(ll_wstring_t, len_t) const noexcept;
		using StringPairHashConstFunction = OptionalHash(HashGenerator::*)(const std::string&) const noexcept;
		using wStringPairHashConstFunction = OptionalHash(HashGenerator::*)(const std::wstring&) const noexcept;
		using StrPairHashConstFunction = OptionalHash(HashGenerator::*)(const meta::StrPair&) const noexcept;
		using wStrPairHashConstFunction = OptionalHash(HashGenerator::*)(const meta::wStrPair&) const noexcept;
		using StrHashConstFunction = OptionalHash(HashGenerator::*)(const meta::Str&) const noexcept;
		using wStrHashConstFunction = OptionalHash(HashGenerator::*)(const meta::wStr&) const noexcept;
		using RecursiveHashConstFunction = OptionalHash(HashGenerator::*)(const HashType&) const noexcept;
		using StrTypeidHashConstFunction = OptionalHash(HashGenerator::*)(const void*, const StrTypeid&) const noexcept;
		using wStrTypeidHashConstFunction = OptionalHash(HashGenerator::*)(const void*, const wStrTypeid&) const noexcept;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(std::is_nothrow_constructible_v<HashGenerator>, "HashGenerator needs a noexcept constructor!");
		static_assert(std::is_nothrow_destructible_v<HashGenerator>, "HashGenerator needs a noexcept destructor!");
		static_assert(std::is_copy_constructible_v<HashGenerator>, "HashGenerator needs a noexcept copy constructor!");
		static_assert(std::is_copy_assignable_v<HashGenerator>, "HashGenerator needs a noexcept copy asignable!");
		static_assert(std::is_move_constructible_v<HashGenerator>, "HashGenerator needs a noexcept move constructor!");
		static_assert(std::is_move_assignable_v<HashGenerator>, "HashGenerator needs a noexcept move asignable!");

		static_assert(hash::traits::has_hash_function<HashConstFunction, HashGenerator>, "HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::traits::has_hash_function<wHashConstFunction, HashGenerator>, "HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::traits::has_hash_function<StringPairHashConstFunction, HashGenerator>, "HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::traits::has_hash_function<wStringPairHashConstFunction, HashGenerator>, "HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::traits::has_hash_function<StrPairHashConstFunction, HashGenerator>, "HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::traits::has_hash_function<wStrPairHashConstFunction, HashGenerator>, "HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::traits::has_hash_function<StrHashConstFunction, HashGenerator>, "HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::traits::has_hash_function<wStrHashConstFunction, HashGenerator>, "HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::traits::has_hash_function<RecursiveHashConstFunction, HashGenerator>, "HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::traits::has_hash_function<StrTypeidHashConstFunction, HashGenerator>, "HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::traits::has_hash_function<wStrTypeidHashConstFunction, HashGenerator>, "HashGenerator::hash() const noexcept is required by default! Non const function is optional");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr HashGeneratorChecker() noexcept : HashChecker(), HashGenerator() {}
		template<class... Args>
		constexpr HashGeneratorChecker(Args&&... args) noexcept
			: HashChecker(), HashGenerator(std::forward<Args>(args)...) {}
		constexpr ~HashGeneratorChecker() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr HashGeneratorChecker(const HashGeneratorChecker& other) noexcept
			: HashChecker(other), HashGenerator(other) {}
		constexpr HashGeneratorChecker& operator=(const HashGeneratorChecker& other) noexcept {
			HashChecker::operator=(other);
			HashGenerator::operator=(other);
			return *this;
		}
		constexpr HashGeneratorChecker(HashGeneratorChecker&& other) noexcept
			: HashChecker(std::move(other)), HashGenerator(std::move(other)) {}
		constexpr HashGeneratorChecker& operator=(HashGeneratorChecker&& other) noexcept {
			HashChecker::operator=(std::move(other));
			HashGenerator::operator=(std::move(other));
			return *this;
		}

		constexpr HashGeneratorChecker(const HashChecker& other) noexcept
			: HashChecker(other), HashGenerator() {}
		constexpr HashGeneratorChecker& operator=(const HashChecker& other) noexcept {
			HashChecker::operator=(other);
			return *this;
		}
		constexpr HashGeneratorChecker(HashChecker&& other) noexcept
			: HashChecker(std::move(other)), HashGenerator() {}
		constexpr HashGeneratorChecker& operator=(HashChecker&& other) noexcept {
			HashChecker::operator=(std::move(other));
			return *this;
		}

		constexpr HashGeneratorChecker(const HashGenerator& other) noexcept
			: HashChecker(), HashGenerator(other) {}
		constexpr HashGeneratorChecker& operator=(const HashGenerator& other) noexcept {
			HashGenerator::operator=(other);
			return *this;
		}
		constexpr HashGeneratorChecker(HashGenerator&& other) noexcept
			: HashChecker(), HashGenerator(std::move(other)) {}
		constexpr HashGeneratorChecker& operator=(HashGenerator&& other) noexcept {
			HashGenerator::operator=(std::move(other));
			return *this;
		}

		constexpr HashGeneratorChecker(const HashChecker& check, const HashGenerator& gen) noexcept
			: HashChecker(check), HashGenerator(gen) {}
		constexpr HashGeneratorChecker(const HashChecker& check, HashGenerator&& gen) noexcept
			: HashChecker(check), HashGenerator(std::move(gen)) {}
		constexpr HashGeneratorChecker(HashChecker&& check, const HashGenerator& gen) noexcept
			: HashChecker(std::move(check)), HashGenerator(gen) {}
		constexpr HashGeneratorChecker(HashChecker&& check, HashGenerator&& gen) noexcept
			: HashChecker(std::move(check)), HashGenerator(std::move(gen)) {}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const HashGeneratorChecker* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator HashGeneratorChecker* () noexcept { return this; }

		#pragma endregion

	#pragma endregion
};

template<class HashType = hash::Hash64, class HashGenerator = hash::HashGeneratorDummy<HashType>>
class LL_SHARED_LIB HashFunctionPack : public hash::HashGeneratorChecker<HashType, HashGenerator> {
	#pragma region Types
	public:
		using HashGeneratorChecker = hash::HashGeneratorChecker<HashType, HashGenerator>;
		using OptionalHash = HashGeneratorChecker::OptionalHash;
		using Hash = HashGeneratorChecker::Hash;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr HashFunctionPack() noexcept : HashGeneratorChecker() {}
		template<class... Args>
		constexpr HashFunctionPack(Args&&... args) noexcept : HashGeneratorChecker(std::forward<Args>(args)...) {}
		constexpr ~HashFunctionPack() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr HashFunctionPack(const HashFunctionPack& other) noexcept : HashGeneratorChecker(other) {}
		constexpr HashFunctionPack& operator=(const HashFunctionPack& other) noexcept {
			HashGeneratorChecker::operator=(other);
			return *this;
		}
		constexpr HashFunctionPack(HashFunctionPack&& other) noexcept : HashGeneratorChecker(std::move(other)) {}
		constexpr HashFunctionPack& operator=(HashFunctionPack&& other) noexcept {
			HashGeneratorChecker::operator=(std::move(other));
			return *this;
		}

		constexpr HashFunctionPack(const HashGeneratorChecker& other) noexcept : HashGeneratorChecker(other) {}
		constexpr HashFunctionPack& operator=(const HashGeneratorChecker& other) noexcept {
			HashGeneratorChecker::operator=(other);
			return *this;
		}
		constexpr HashFunctionPack(HashGeneratorChecker&& other) noexcept : HashGeneratorChecker(std::move(other)) {}
		constexpr HashFunctionPack& operator=(HashGeneratorChecker&& other) noexcept {
			HashGeneratorChecker::operator=(std::move(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const HashFunctionPack* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator HashFunctionPack* () noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		// [TODO]
		/*
namespace basic_type_hash {

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_convertible_v = std::_Is_any_of_v<T, i8, ui8, i16, ui16, i32, ui32, i64, ui64, ll_wchar_t>;

#pragma region UsedInTools
template<len_t N, class T>
__LL_NODISCARD__ constexpr hash::OptionalHash64 hashValues(const T* values, hash::Hash64Function hashFunction) noexcept {
	static_assert(basic_type_hash::is_convertible_v<T>, "Invalid type to hash");
	static_assert(N != ZERO_UI64, "Cannot hash 0 elements");
	if constexpr (N == 1) return basic_type_hash::hashValue<T>(*values, hashFunction);
	else {
		constexpr len_t BUFFERLEN = sizeof(T) * N;
		ll_char_t buffer[BUFFERLEN]{};

		ll_char_t* i = buffer;
		for (const T* data_end = values + N; values < data_end; ++values)
			basic_type_hash::conversor<T>(i, *values);
		return hashFunction(buffer, BUFFERLEN);
	}
}
template<len_t N>
__LL_NODISCARD__ constexpr hash::OptionalHash64 hashArray(const hash::Hash64(&hashes)[N], hash::Hash64Function hashFunction) noexcept {
	constexpr len_t BUFFERLEN = sizeof(ui64) * N;
	ll_char_t buffer[BUFFERLEN]{};

	ll_char_t* i = buffer;
	const hash::Hash64* arr = hashes;
	for (const hash::Hash64* data_end = arr + N; arr < data_end; ++arr)
		basic_type_hash::conversor<ui64>(i, arr->get());

	return hashFunction(buffer, BUFFERLEN);
}

#pragma endregion

// Uses bitwise operators: [ ">>", "&" ]
template<class U, class W = traits::cinput<U>>
__LL_NODISCARD__ constexpr void conversor(ll_char_t*& buffer, W value) noexcept {
	static_assert(basic_type_hash::is_convertible_v<U>, "Invalid type to hash");
	constexpr len_t N = sizeof(U);
	constexpr len_t BYTES = (N << 3) - 8;
	len_t byte = BYTES;
	for (len_t i{}; i < N; ++i, ++buffer, byte -= 8)
		*buffer = static_cast<ui8>(value >> byte) & 0xff;
}
template<class U, class W = traits::cinput<U>, hash::Hash64Function HASH_FUNCTION>
__LL_NODISCARD__ constexpr hash::OptionalHash64 hashValue(W value) noexcept {
	static_assert(basic_type_hash::is_convertible_v<U>, "Invalid type to hash");
	constexpr len_t BUFFERLEN = sizeof(U);
	ll_char_t buffer[BUFFERLEN]{};
	ll_char_t* _ = buffer;
	basic_type_hash::conversor<U, W>(_, value);
	return HASH_FUNCTION(buffer, BUFFERLEN);
}

} // namespace basic_type_hash

// Struct for use in HashTool in an more optimized way (for not constexpr data)
struct basic_type_hash_no_constexpr {
	template<len_t N>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 hashArray(const hash::Hash64(&hashes)[N], hash::Hash64Function hashFunction) noexcept {
		static_assert(N != ZERO_UI64, "Cannot hash 0 elements");
		return hashFunction(reinterpret_cast<ll_string_t>(hashes), sizeof(hash::Hash64) * N);
	}
	template<len_t N, class T>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 hashValues(const T* values, hash::Hash64Function hashFunction) noexcept {
		static_assert(!basic_type_hash::is_convertible_v<T>, "Invalid type to hash");
		static_assert(N != ZERO_UI64, "Cannot hash 0 elements");
		return hashFunction(reinterpret_cast<ll_string_t>(values), sizeof(T) * N);
	}
};
*/
		#pragma endregion
	#pragma endregion
};


template<class HashGenerator = hash::HashGeneratorDummy<hash::Hash32>>
using Hash32FunctionPack = HashFunctionPack<hash::Hash32, HashGenerator>;
template<class HashGenerator = hash::HashGeneratorDummy<hash::Hash64>>
using Hash64FunctionPack = HashFunctionPack<hash::Hash64, HashGenerator>;
template<class HashGenerator = hash::HashGeneratorDummy<hash::Hash128>>
using Hash128FunctionPack = HashFunctionPack<hash::Hash128, HashGenerator>;

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASHPACKS_HPP_
