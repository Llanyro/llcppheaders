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
		__LL_NODISCARD__ constexpr OptionalHash hash(const hash::Hash32& h) const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr OptionalHash hash(const hash::Hash64& h) const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr OptionalHash hash(const hash::Hash128& h) const noexcept {
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
		
		using RecursiveHash128ConstFunction = OptionalHash(HashGenerator::*)(const hash::Hash128&) const noexcept;
		using RecursiveHash64ConstFunction = OptionalHash(HashGenerator::*)(const hash::Hash64&) const noexcept;
		using RecursiveHash32ConstFunction = OptionalHash(HashGenerator::*)(const hash::Hash32&) const noexcept;
		
		using RecursiveHashConstFunction = std::conditional_t<!std::_Is_any_of_v<HashType, Hash32, Hash64, Hash128>,
			OptionalHash(HashGenerator::*)(const HashType&) const noexcept,
			void
		>;

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

		static_assert(hash_traits::has_hash_function_v<HashGenerator, HashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash_traits::has_hash_function_v<HashGenerator, wHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash_traits::has_hash_function_v<HashGenerator, StringPairHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash_traits::has_hash_function_v<HashGenerator, wStringPairHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash_traits::has_hash_function_v<HashGenerator, StrPairHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash_traits::has_hash_function_v<HashGenerator, wStrPairHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash_traits::has_hash_function_v<HashGenerator, StrHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash_traits::has_hash_function_v<HashGenerator, wStrHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		
		static_assert(hash_traits::has_hash_function_v<HashGenerator, RecursiveHash128ConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash_traits::has_hash_function_v<HashGenerator, RecursiveHash64ConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash_traits::has_hash_function_v<HashGenerator, RecursiveHash32ConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		
		static_assert(std::is_same_v<RecursiveHashConstFunction, void> || hash_traits::has_hash_function_v<HashGenerator, RecursiveHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		
		static_assert(hash_traits::has_hash_function_v<HashGenerator, StrTypeidHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash_traits::has_hash_function_v<HashGenerator, wStrTypeidHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");

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

#define __LL_HASHFUNCTIONPACK_B2A_ASSERT__(type) \
	static_assert(HashFunctionPack::is_convertible_v<type>, "Invalid type to hash. Type is not convertible to array.")

#define __LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__(num) \
	static_assert(num != ZERO_UI64, "Cannot hash 0 elements");

template<class HashType = hash::Hash64, class HashGenerator = hash::HashGeneratorDummy<HashType>>
class LL_SHARED_LIB HashFunctionPack : public hash::HashGeneratorChecker<HashType, HashGenerator> {
	#pragma region Types
	public:
		using HashGeneratorChecker = hash::HashGeneratorChecker<HashType, HashGenerator>;
		using OptionalHash = HashGeneratorChecker::OptionalHash;
		using Hash = HashGeneratorChecker::Hash;

	#pragma endregion
	#pragma region Expresions
	public:
		template<class T>
		static constexpr ll_bool_t is_convertible_v = std::_Is_any_of_v<T, i8, ui8, i16, ui16, i32, ui32, i64, ui64, ll_wchar_t>;
	public:
		// Is for being used in auto mode in check_valid_types, hashArray()
		template<class T>
		static constexpr ll_bool_t is_valid_v = traits::has_simple_type_operator_v<HashType, T>;

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
		// Uses bitwise operators: [ ">>", "&" ]
		// Basic type to char array
		// If type has 7 bytes, array will be of 7
		template<class U, class W = meta::traits::cinput<U>>
		__LL_NODISCARD__ constexpr void b2a(ll_char_t*& buffer, W value) const noexcept {
			__LL_HASHFUNCTIONPACK_B2A_ASSERT__(U);
			constexpr len_t N = sizeof(U);
			constexpr len_t BYTES = (N << 3) - 8;
			len_t byte = BYTES;
			for (len_t i{}; i < N; ++i, ++buffer, byte -= 8)
				*buffer = static_cast<ui8>(value >> byte) & 0xff;
		}

		template<class U, class W = meta::traits::cinput<U>>
		__LL_NODISCARD__ constexpr OptionalHash hashValue(W value) noexcept {
			__LL_HASHFUNCTIONPACK_B2A_ASSERT__(U);
			constexpr len_t BUFFERLEN = sizeof(U);
			ll_char_t buffer[BUFFERLEN]{};
			ll_char_t* buffer_begin = buffer;
			HashFunctionPack::b2a<U, W>(buffer_begin, value);
			return this->hash(buffer, BUFFERLEN);
		}
		template<class U, class W = meta::traits::cinput<U>>
		__LL_NODISCARD__ constexpr OptionalHash hashValue(W value) const noexcept {
			__LL_HASHFUNCTIONPACK_B2A_ASSERT__(U);
			constexpr len_t BUFFERLEN = sizeof(U);
			ll_char_t buffer[BUFFERLEN]{};
			ll_char_t* buffer_begin = buffer;
			HashFunctionPack::b2a<U, W>(buffer_begin, value);
			return this->hash(buffer, BUFFERLEN);
		}

		template<len_t N, class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const T* values) noexcept {
			__LL_HASHFUNCTIONPACK_B2A_ASSERT__(T);
			__LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__(N);
			if constexpr (N == 1) return this->hashValue<T>(*values);
			else {
				constexpr len_t BUFFERLEN = sizeof(T) * N;
				ll_char_t buffer[BUFFERLEN]{};
				ll_char_t* i = buffer;
				for (const T* data_end = values + N; values < data_end; ++values)
					this->b2a<T>(i, *values);
				return this->hash(buffer, BUFFERLEN);
			}
		}
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const T* values) const noexcept {
			__LL_HASHFUNCTIONPACK_B2A_ASSERT__(T);
			__LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__(N);
			if constexpr (N == 1) return this->hashValue<T>(*values);
			else {
				constexpr len_t BUFFERLEN = sizeof(T) * N;
				ll_char_t buffer[BUFFERLEN]{};
				ll_char_t* i = buffer;
				for (const T* data_end = values + N; values < data_end; ++values)
					this->b2a<T>(i, *values);
				return this->hash(buffer, BUFFERLEN);
			}
		}

		template<class T, len_t N>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const T(&_values)[N]) noexcept {
			__LL_HASHFUNCTIONPACK_B2A_ASSERT__(T);
			__LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__(N);
			if constexpr (N == 1) return this->hashValue<T>(*values);
			else {
				constexpr len_t BUFFERLEN = sizeof(T) * N;
				ll_char_t buffer[BUFFERLEN]{};
				ll_char_t* i = buffer;
				const T* values = _values;
				for (const T* data_end = values + N; values < data_end; ++values)
					this->b2a<T>(i, *values);
				return this->hash(buffer, BUFFERLEN);
			}
		}
		template<class T, len_t N>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const T(&_values)[N]) const noexcept {
			__LL_HASHFUNCTIONPACK_B2A_ASSERT__(T);
			__LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__(N);
			if constexpr (N == 1) return this->hashValue<T>(*values);
			else {
				constexpr len_t BUFFERLEN = sizeof(T) * N;
				ll_char_t buffer[BUFFERLEN]{};
				ll_char_t* i = buffer;
				const T* values = _values;
				for (const T* data_end = values + N; values < data_end; ++values)
					this->b2a<T>(i, *values);
				return this->hash(buffer, BUFFERLEN);
			}
		}


		template<len_t N>
		__LL_NODISCARD__ constexpr OptionalHash hashArray(const HashType(&hashes)[N]) noexcept {
			using U = traits::check_valid_types<HashFunctionPack, void>::type<
				ui8, ui16, ui32, ui64, i8, i16, i32, i64>;
			static_assert(!std::is_same_v<U, void>,
				"HashType should return one of above types!");
			__LL_HASHFUNCTIONPACK_B2A_ASSERT__(U);

			constexpr len_t BUFFERLEN = sizeof(ui64) * N;
			ll_char_t buffer[BUFFERLEN]{};
			ll_char_t* i = buffer;
			const HashType* arr = hashes;
			for (const HashType* data_end = arr + N; arr < data_end; ++arr)
				this->b2a<U>(i, arr->operator U());
			return this->hash(buffer, BUFFERLEN);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr OptionalHash hashArray(const HashType(&hashes)[N]) const noexcept {
			using U = traits::check_valid_types<HashFunctionPack, void>::type<
				ui8, ui16, ui32, ui64, i8, i16, i32, i64>;
			static_assert(!std::is_same_v<U, void>,
				"HashType should return one of above types!");
			__LL_HASHFUNCTIONPACK_B2A_ASSERT__(U);

			constexpr len_t BUFFERLEN = sizeof(ui64) * N;
			ll_char_t buffer[BUFFERLEN]{};
			ll_char_t* i = buffer;
			const HashType* arr = hashes;
			for (const HashType* data_end = arr + N; arr < data_end; ++arr)
				this->b2a<U>(i, arr->operator U());
			return this->hash(buffer, BUFFERLEN);
		}

		#pragma endregion

	#pragma endregion
};

#undef __LL_HASHFUNCTIONPACK_B2A_ASSERT__
#undef __LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__

template<class HashType = hash::Hash64, class HashGenerator = hash::HashGeneratorDummy<HashType>>
class LL_SHARED_LIB HashFunctionPackNoConstexpr : public hash::HashGeneratorChecker<HashType, HashGenerator> {
	#pragma region Types
	public:
		using HashGeneratorChecker = hash::HashGeneratorChecker<HashType, HashGenerator>;
		using OptionalHash = HashGeneratorChecker::OptionalHash;
		using Hash = HashGeneratorChecker::Hash;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr HashFunctionPackNoConstexpr() noexcept : HashGeneratorChecker() {}
		template<class... Args>
		constexpr HashFunctionPackNoConstexpr(Args&&... args) noexcept : HashGeneratorChecker(std::forward<Args>(args)...) {}
		constexpr ~HashFunctionPackNoConstexpr() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr HashFunctionPackNoConstexpr(const HashFunctionPackNoConstexpr& other) noexcept : HashGeneratorChecker(other) {}
		constexpr HashFunctionPackNoConstexpr& operator=(const HashFunctionPackNoConstexpr& other) noexcept {
			HashGeneratorChecker::operator=(other);
			return *this;
		}
		constexpr HashFunctionPackNoConstexpr(HashFunctionPackNoConstexpr&& other) noexcept : HashGeneratorChecker(std::move(other)) {}
		constexpr HashFunctionPackNoConstexpr& operator=(HashFunctionPackNoConstexpr&& other) noexcept {
			HashGeneratorChecker::operator=(std::move(other));
			return *this;
		}

		constexpr HashFunctionPackNoConstexpr(const HashGeneratorChecker& other) noexcept : HashGeneratorChecker(other) {}
		constexpr HashFunctionPackNoConstexpr& operator=(const HashGeneratorChecker& other) noexcept {
			HashGeneratorChecker::operator=(other);
			return *this;
		}
		constexpr HashFunctionPackNoConstexpr(HashGeneratorChecker&& other) noexcept : HashGeneratorChecker(std::move(other)) {}
		constexpr HashFunctionPackNoConstexpr& operator=(HashGeneratorChecker&& other) noexcept {
			HashGeneratorChecker::operator=(std::move(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const HashFunctionPackNoConstexpr* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator HashFunctionPackNoConstexpr* () noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		#pragma region HashValue
		template<class U, class W = meta::traits::cinput<U>>
		__LL_NODISCARD__ constexpr OptionalHash hashValue(W value) noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(&value), sizeof(U));
		}
		template<class U, class W = meta::traits::cinput<U>>
		__LL_NODISCARD__ constexpr OptionalHash hashValue(W value) const noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(&value), sizeof(U));
		}

		#pragma endregion
		#pragma region HashValues
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const T* values) noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(values), sizeof(T) * N);
		}
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const T* values) const noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(values), sizeof(T) * N);
		}
		template<class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const T* values, const len_t size) noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(values), sizeof(T) * size);
		}
		template<class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const T* values, const len_t size) const noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(values), sizeof(T) * size);
		}
		template<class T, len_t N>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const T(&values)[N]) noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(values), sizeof(T) * N);
		}
		template<class T, len_t N>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const T(&values)[N]) const noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(values), sizeof(T) * N);
		}
		template<class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const ArrayPair<T>& arr) noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(arr.begin()), sizeof(T) * arr.len());
		}
		template<class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const ArrayPair<T>& arr) const noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(arr.begin()), sizeof(T) * arr.len());
		}
		template<class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const Array<T>& arr) noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(arr.begin()), sizeof(T) * arr.len());
		}
		template<class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const Array<T>& arr) const noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(arr.begin()), sizeof(T) * arr.len());
		}

		#pragma endregion

		#pragma endregion
	#pragma endregion
};

template<class HashGenerator = hash::HashGeneratorDummy<hash::Hash32>>
using Hash32FunctionPack = HashFunctionPackBase<hash::Hash32, HashGenerator>;
template<class HashGenerator = hash::HashGeneratorDummy<hash::Hash64>>
using Hash64FunctionPack = HashFunctionPackBase<hash::Hash64, HashGenerator>;
template<class HashGenerator = hash::HashGeneratorDummy<hash::Hash128>>
using Hash128FunctionPack = HashFunctionPackBase<hash::Hash128, HashGenerator>;

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASHPACKS_HPP_
