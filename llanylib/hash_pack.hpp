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

class Object {
	private:
		hash::Hash128 h;
	public:
		__LL_NODISCARD__ constexpr operator OptionalHash32() const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr operator OptionalHash64() const noexcept {
			return std::nullopt;
		}
		__LL_NODISCARD__ constexpr operator OptionalHash128() const noexcept {
			return std::nullopt;
		}
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
		
		using RecursiveHash32ConstFunction = OptionalHash(HashGenerator::*)(const hash::Hash32&) const noexcept;
		using RecursiveHash64ConstFunction = OptionalHash(HashGenerator::*)(const hash::Hash64&) const noexcept;
		using RecursiveHash128ConstFunction = OptionalHash(HashGenerator::*)(const hash::Hash128&) const noexcept;

		using RecursiveHashConstFunction = std::conditional_t<!std::_Is_any_of_v<HashType, Hash32, Hash64, Hash128>,
			OptionalHash(HashGenerator::*)(const HashType&) const noexcept,
			void
		>;

		using StrTypeidHashConstFunction = OptionalHash(HashGenerator::*)(const void*, const StrTypeid&) const noexcept;
		using wStrTypeidHashConstFunction = OptionalHash(HashGenerator::*)(const void*, const wStrTypeid&) const noexcept;

	#pragma endregion
	#pragma region Expresions
	public:
		template<class T>
		static constexpr ll_bool_t is_convertible_object_v = std::_Is_any_of_v<T,
			hash::Hash32, hash::Hash64, hash::Hash128, 
			meta::StrPair, meta::wStrPair, meta::Str, meta::wStr,
			std::string, std::wstring
		>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(std::is_nothrow_constructible_v<HashGenerator>, "HashGenerator needs a noexcept constructor!");
		static_assert(std::is_nothrow_destructible_v<HashGenerator>, "HashGenerator needs a noexcept destructor!");
		static_assert(std::is_copy_constructible_v<HashGenerator>, "HashGenerator needs a noexcept copy constructor!");
		static_assert(std::is_copy_assignable_v<HashGenerator>, "HashGenerator needs a noexcept copy asignable!");
		static_assert(std::is_move_constructible_v<HashGenerator>, "HashGenerator needs a noexcept move constructor!");
		static_assert(std::is_move_assignable_v<HashGenerator>, "HashGenerator needs a noexcept move asignable!");

		static_assert(hash::__::has_hash_function_v<HashGenerator, HashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::__::has_hash_function_v<HashGenerator, wHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::__::has_hash_function_v<HashGenerator, StringPairHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::__::has_hash_function_v<HashGenerator, wStringPairHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::__::has_hash_function_v<HashGenerator, StrPairHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::__::has_hash_function_v<HashGenerator, wStrPairHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::__::has_hash_function_v<HashGenerator, StrHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::__::has_hash_function_v<HashGenerator, wStrHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		
		static_assert(hash::__::has_hash_function_v<HashGenerator, RecursiveHash128ConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::__::has_hash_function_v<HashGenerator, RecursiveHash64ConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::__::has_hash_function_v<HashGenerator, RecursiveHash32ConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		
		static_assert(std::is_same_v<RecursiveHashConstFunction, void> || hash::__::has_hash_function_v<HashGenerator, RecursiveHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		
		static_assert(hash::__::has_hash_function_v<HashGenerator, StrTypeidHashConstFunction>,
			"HashGenerator::hash() const noexcept is required by default! Non const function is optional");
		static_assert(hash::__::has_hash_function_v<HashGenerator, wStrTypeidHashConstFunction>,
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
	private:
		template<class U = HashType>
		struct OperatorTypeChecker {
			// Is for being used in auto mode in check_valid_types, hashArray()
			template<class T>
			static constexpr ll_bool_t is_valid_v = traits::has_simple_type_operator_v<U, T>;
			using U = traits::check_valid_types<OperatorTypeChecker, void>::type<ui8, ui16, ui32, ui64, i8, i16, i32, i64>;
		};
		template<class V>
		struct HashTypeChecker {
			// Is for being used in auto mode in check_valid_types, hashArray()
			template<class T>
			static constexpr ll_bool_t is_valid_v = traits::has_simple_type_operator_v<V, T>;
			using U = traits::check_valid_types<HashTypeChecker, void>::type<OptionalHash32, OptionalHash64, OptionalHash128, OptionalHash>;
		};

	#pragma endregion
	#pragma region Expresions
	public:
		template<class T>
		static constexpr ll_bool_t is_convertible_v = std::_Is_any_of_v<T, i8, ui8, i16, ui16, i32, ui32, i64, ui64, ll_wchar_t>;

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

	private:
		// This function is the const part of "hashValue() noexcept" && "hashValue() const noexcept"
		// Both functions call this function if 
		template<class U, class W = meta::traits::cinput<U>>
		__LL_NODISCARD__ constexpr OptionalHash hashValuePriv(W value) const noexcept {
			using ObjectOptionalHash = HashTypeChecker<U>::U;
			if constexpr (!std::is_same_v<ObjectOptionalHash, void>) {
				ObjectOptionalHash h = value.operator ObjectOptionalHash();
				if constexpr (!std::is_same_v<ObjectOptionalHash, OptionalHash>)
					return h.has_value() ? this->hashValue<ui32>(h->operator ui32()) : std::nullopt;
				else return h;
			}
			else return std::nullopt;
		}
	public:
		// Generates hashes by basic types
		// Prior 32-64-128
		// Uses "operator type() const noexcept" to hash the object
		// As a last option it prior custom user hash: "operator std::optional<UserHashType>() const noexcept"
		template<class U, class W = meta::traits::cinput<U>>
		__LL_NODISCARD__ constexpr OptionalHash hashValue(W value) noexcept {
			using ObjectOptionalHash = HashTypeChecker<U>::U;
			if constexpr (!std::is_same_v<ObjectOptionalHash, void>)
				return this->hashValuePriv<U, W>(value);
			else {
				__LL_HASHFUNCTIONPACK_B2A_ASSERT__(U);
				constexpr len_t BUFFERLEN = sizeof(U);
				ll_char_t buffer[BUFFERLEN]{};
				ll_char_t* buffer_begin = buffer;
				HashFunctionPack::b2a<U, W>(buffer_begin, value);
				return this->hash(buffer, BUFFERLEN);
			}
		}
		// Generates hashes by basic types
		// Prior 32-64-128
		// Uses "operator type() const noexcept" to hash the object
		// As a last option it prior custom user hash: "operator std::optional<UserHashType>() const noexcept"
		template<class U, class W = meta::traits::cinput<U>>
		__LL_NODISCARD__ constexpr OptionalHash hashValue(W value) const noexcept {
			using ObjectOptionalHash = HashTypeChecker<U>::U;
			if constexpr (!std::is_same_v<ObjectOptionalHash, void>)
				return this->hashValuePriv<U, W>(value);
			else {
				__LL_HASHFUNCTIONPACK_B2A_ASSERT__(U);
				constexpr len_t BUFFERLEN = sizeof(U);
				ll_char_t buffer[BUFFERLEN]{};
				ll_char_t* buffer_begin = buffer;
				HashFunctionPack::b2a<U, W>(buffer_begin, value);
				return this->hash(buffer, BUFFERLEN);
			}
		}



		template<len_t N, class T>
		__LL_NODISCARD__ constexpr OptionalHash hashArray(const T* values) noexcept {
			__LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__(N);

			if constexpr (std::is_pointer_v<T>)
				return std::nullopt;
			else if constexpr (std::is_array_v<T>) {
				using ArrayType = std::remove_all_extents_t<T>;
				if constexpr (traits::is_basic_type_v<ArrayType>) {
					constexpr len_t arr_size = sizeof(T) * N;

				}



			}
			else if constexpr (traits::is_basic_type_v<T>) {

			}


			//using own_hash_type = HashTypeChecker<T>::U;
			//if constexpr (!std::is_same_v<own_hash_type, void>) {
			//	using ObjectHashType = own_hash_type::value_type;
			//	ObjectHashType hashes[N]{};
			//	ObjectHashType* data = hashes;
			//	for (ObjectHashType* end = hashes + N; data < end; ++data, ++values) {
			//		own_hash_type h = values->operator own_hash_type();
			//		if (h.has_value()) *data = *h;
			//		// If is invalid hash, we cant hash the array
			//		else return std::nullopt;
			//	}
			//	return this->hashArrayHash<N, ObjectHashType>(hashes);
			//}
			//else {
			//	__LL_HASHFUNCTIONPACK_B2A_ASSERT__(T);
			//	constexpr len_t BUFFERLEN = sizeof(T) * N;
			//	ll_char_t buffer[BUFFERLEN]{};
			//	ll_char_t* i = buffer;
			//	for (const T* data_end = values + N; values < data_end; ++values)
			//		this->b2a<T>(i, *values);
			//	return this->hash(buffer, BUFFERLEN);
			//}
		}
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr OptionalHash hashArray(const T* values) const noexcept {
			__LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__(N);
			using own_hash_type = HashTypeChecker<T>::U;
			if constexpr (!std::is_same_v<own_hash_type, void>) {
				using ObjectHashType = own_hash_type::value_type;
				ObjectHashType hashes[N]{};
				ObjectHashType* data = hashes;
				for (ObjectHashType* end = hashes + N; data < end; ++data, ++values) {
					own_hash_type h = values->operator own_hash_type();
					if (h.has_value()) *data = *h;
					// If is invalid hash, we cant hash the array
					else return std::nullopt;
				}
				return this->hashArrayHash<N, ObjectHashType>(hashes);
			}
			else {
				__LL_HASHFUNCTIONPACK_B2A_ASSERT__(T);
				constexpr len_t BUFFERLEN = sizeof(T) * N;
				ll_char_t buffer[BUFFERLEN]{};
				ll_char_t* i = buffer;
				for (const T* data_end = values + N; values < data_end; ++values)
					this->b2a<T>(i, *values);
				return this->hash(buffer, BUFFERLEN);
			}
		}

		template<len_t N, class T>
		__LL_NODISCARD__ constexpr OptionalHash hashArrayHash(const T* hashes) noexcept {
			// Check size
			__LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__(N);
		
			// Check is hash type
			static_assert(hash::__::is_hash_type_v<T> || std::is_same_v<T, HashType>,
				"T should be a library hash or a custom provided hash!");
		
			// Get operator basic_type to hash
			using U = OperatorTypeChecker<T>::U;
			// If void, no operator avaible
			static_assert(!std::is_same_v<U, void>,
				"HashType should return one of above types! Like 'T::operator ui64() const noexception'");
		
			constexpr len_t BUFFERLEN = sizeof(U) * N;
			ll_char_t buffer[BUFFERLEN]{};
			ll_char_t* i = buffer;
			for (const T* data_end = hashes + N; hashes < data_end; ++hashes)
				this->b2a<U>(i, hashes->operator U());
			return this->hash(buffer, BUFFERLEN);
		}
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr OptionalHash hashArrayHash(const T* hashes) const noexcept {
			// Check size
			__LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__(N);

			// Check is hash type
			static_assert(hash::__::is_hash_type_v<T> || std::is_same_v<T, HashType>,
				"T should be a library hash or a custom provided hash!");

			// Get operator basic_type to hash
			using U = OperatorTypeChecker<T>::U;
			// If void, no operator avaible
			static_assert(!std::is_same_v<U, void>,
				"HashType should return one of above types! Like 'T::operator ui64() const noexception'");

			constexpr len_t BUFFERLEN = sizeof(U) * N;
			ll_char_t buffer[BUFFERLEN]{};
			ll_char_t* i = buffer;
			for (const T* data_end = hashes + N; hashes < data_end; ++hashes)
				this->b2a<U>(i, hashes->operator U());
			return this->hash(buffer, BUFFERLEN);
		}

		#pragma endregion

	#pragma endregion
};

#undef __LL_HASHFUNCTIONPACK_B2A_ASSERT__
#undef __LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__
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
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const ArrayPair<T>& _array) noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(_array.begin()), sizeof(T) * _array.len());
		}
		template<class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const ArrayPair<T>& _array) const noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(_array.begin()), sizeof(T) * _array.len());
		}
		template<class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const Array<T>& _array) noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(_array.begin()), sizeof(T) * _array.len());
		}
		template<class T>
		__LL_NODISCARD__ constexpr OptionalHash hashValues(const Array<T>& _array) const noexcept {
			return this->hash(reinterpret_cast<ll_string_t>(_array.begin()), sizeof(T) * _array.len());
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
