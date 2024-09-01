//////////////////////////////////////////////
//	hash_tools.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHTOOLS_HPP_) // Guard && version protector
	#if LLANYLIB_HASHTOOLS_MAYOR_ != 9 || LLANYLIB_HASHTOOLS_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "hash_tools.hpp version error!"
		#else
			#error "hash_tools.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASHTOOLS_MAYOR_ || LLANYLIB_HASHTOOLS_MINOR_

#else !defined(LLANYLIB_HASHTOOLS_HPP_)
#define LLANYLIB_HASHTOOLS_HPP_
#define LLANYLIB_HASHTOOLS_MAYOR_ 9
#define LLANYLIB_HASHTOOLS_MINOR_ 0

#include "hash_pack.hpp"
#include "reflection.hpp"

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4365) // ignore conversion mismatch [TOCHECK]
#endif // WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace hash {

#if defined(__LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__)
#define __LL_HASHTOOL_HASHARRAY_ASSERT__(num) __LL_HASHFUNCTIONPACK_HASHVALUES_ASSERT__(num)
#else
#define __LL_HASHTOOL_HASHARRAY_ASSERT__(num) static_assert(num != ZERO_UI64, "Cannot hash 0 elements");
#endif

template<class HashType = hash::Hash64, class HashGenerator = hash::HashGeneratorDummy<HashType>>
class HashTool : public hash::HashFunctionPack<HashType, HashGenerator> {
	#pragma region Types
	public:
		using HashFunctionPack = hash::HashFunctionPack<HashType, HashGenerator>;
		using OptionalHash = HashFunctionPack::OptionalHash;
		using Hash = HashFunctionPack::Hash;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr HashTool() noexcept : HashChecker(), HashFunctionPack() {}
		template<class... Args>
		constexpr HashTool(Args&&... args) noexcept
			: HashChecker(), HashFunctionPack(std::forward<Args>(args)...) {}
		constexpr ~HashTool() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr HashTool(const HashTool& other) noexcept : HashFunctionPack(other) {}
		constexpr HashTool& operator=(const HashTool& other) noexcept {
			HashFunctionPack::operator=(other);
			return *this;
		}
		constexpr HashTool(HashTool&& other) noexcept
			: HashFunctionPack(std::move(other)) {}
		constexpr HashTool& operator=(HashTool&& other) noexcept {
			HashChecker::operator=(std::move(other));
			HashGenerator::operator=(std::move(other));
			return *this;
		}

		constexpr HashTool(const HashFunctionPack& other) noexcept : HashFunctionPack(other) {}
		constexpr HashTool& operator=(const HashFunctionPack& other) noexcept {
			HashFunctionPack::operator=(other);
			return *this;
		}
		constexpr HashTool(HashFunctionPack&& other) noexcept
			: HashFunctionPack(std::move(other)) {}
		constexpr HashTool& operator=(HashFunctionPack&& other) noexcept {
			HashFunctionPack::operator=(std::move(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const HashTool* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator HashTool* () noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		#pragma region HashArray
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr OptionalHash hashArray(const T* _array) const noexcept {
			__LL_HASHTOOL_HASHARRAY_ASSERT__(N);
			if constexpr (N == ZERO_UI64) return std::nullopt;
			if constexpr (std::is_pointer_v<T>) return std::nullopt;
			// Calls defined function to hash arrays
			else if constexpr (std::is_array_v<T>) {
				using array_type_t = traits::array_type_t<T>;
				auto h = this->hashArray<traits::array_size<T>, array_type_t>(*_array++);
				// If first element hashed is invalid, other elements will be invalid too
				if (!h.has_value()) return std::nullopt;
				
				HashType hashes[N]{};
				// If not, we store the hash
				hashes[0] = *h;
				
				// Now, we will hash other elements
				HashType* i = hashes + 1;
				for (HashType* end = hashes + N; i < end; ++i, ++_array)
					*i = *this->hashArray<traits::array_size<T>, array_type_t>(*_array);
				
				// An then hash the hash array
				return this->hashArray<N>(hashes);
			}
			// Hashses values using a converting to chars algorithm, and hashing the string
			else if constexpr (HashTool::is_convertible_v<T>)
				return this->hashArray<N, T>(_array);
			else if constexpr (traits::common::is_hash_type_v<T> || std::is_same_v<T, HashType>)
				return this->hashArrayHash<N, T>(_array);
			else if constexpr (HashTool::is_convertible_object_v<T>) {
				auto h = this->hash(*_array++);
				if (!h.has_value()) return hash::INVALID_HASH64;
				
				HashType hashes[N]{};
				hashes[0] = *h;
				
				HashType* i = hashes + 1;
				for (HashType* end = hashes + N; i < end; ++i, ++_array)
					*i = *this->hashObject(*_array);
				
				return this->hashArray<N>(hashes);
			}
			//else if constexpr (traits::has_type_operator_v<T, hash::OptionalHash64>) {
			else if constexpr (traits::has_type_operator_const_v<T, hash::OptionalHash64> || traits::has_type_operator_const_except_v<T, hash::OptionalHash64>) {
				auto h = (_array++)->operator hash::OptionalHash64();
				if (!h.has_value()) return hash::INVALID_HASH64;

				hash::Hash64 hashes[N]{};
				hashes[0] = *h;

				hash::Hash64* i = hashes + 1;
				for (hash::Hash64* end = hashes + N; i < end; ++i, ++_array)
					*i = *_array->operator hash::OptionalHash64();

				return this->hashArray<N>(hashes);
			}
			// Hashes undefined objects
			else {
				meta::StrTypeid id = traits::getStrTypeId<T>(this->hashFunctionPack.getStrPairHash64Function());

				auto h = this->hashFunctionPack.call(_array++, id);
				if (!h.has_value()) return hash::INVALID_HASH64;

				hash::Hash64 hashes[N]{};
				hashes[0] = *h;

				hash::Hash64* i = hashes + 1;
				for (hash::Hash64* end = hashes + N; i < end; ++i, ++_array)
					*i = *this->hashFunctionPack.call(_array, id);

				return this->hashArray<N>(hashes);
			}
		}
		template<class T, len_t N>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashArray(const T(&_array)[N]) const noexcept {
			return this->hashArray<N, T>(_array);
		}
		// Predefined hasheables
		template<len_t N>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashArray(const hash::Hash64(&hashes)[N]) const noexcept {
			return basic_type_hash_class::hashArray<N>(hashes, this->hashFunctionPack.getHash64Function());
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashArray(const ll_char_t(&str)[N]) const noexcept {
			return this->hashFunctionPack.call(str, N);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashArray(const ll_wchar_t(&str)[N]) const noexcept {
			return this->hashFunctionPack.call(str, N);
		}

		#pragma endregion


		#pragma endregion
	#pragma endregion
};

/*
template<class basic_type_hash_class = basic_type_hash>
class HashTool {
	public:
		template<class T>
		static constexpr ll_bool_t is_convertible_object_v = std::_Is_any_of_v<T, hash::Hash64, meta::StrPair, meta::wStrPair, meta::Str, meta::wStr, std::string, std::wstring>;
	private:
		Hash64FunctionPack hashFunctionPack;
	public:
		#pragma region Constructors
		constexpr HashTool() noexcept = delete;
		constexpr HashTool(const Hash64FunctionPack& hashFunctionPack) noexcept
			: hashFunctionPack(hashFunctionPack) {}
		constexpr HashTool(Hash64FunctionPack&& hashFunctionPack) noexcept
			: hashFunctionPack(std::move(hashFunctionPack)) {}
		constexpr ~HashTool() noexcept {}

		#pragma endregion
		#pragma region CopyMove
		constexpr HashTool(const HashTool& other) noexcept
			: hashFunctionPack(other.hashFunctionPack) {}
		constexpr HashTool& operator=(const HashTool& other) noexcept {
			this->hashFunctionPack = other.hashFunctionPack;
			return *this;
		}

		constexpr HashTool(HashTool&& other) noexcept
			: hashFunctionPack(std::move(other.hashFunctionPack)) {}
		constexpr HashTool& operator=(HashTool&& other) noexcept {
			this->hashFunctionPack = std::move(other.hashFunctionPack);
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr explicit operator typename const HashTool*() const noexcept = delete;
		__LL_NODISCARD__ constexpr explicit operator typename HashTool*() noexcept = delete;

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr const Hash64FunctionPack& getHash64FunctionPack() const noexcept {
			return this->hashFunctionPack;
		}
		__LL_NODISCARD__ constexpr Hash64FunctionPack& getHash64FunctionPack() noexcept {
			return this->hashFunctionPack;
		}
		__LL_NODISCARD__ constexpr void setHash64FunctionPack(const Hash64FunctionPack& hashFunctionPack) noexcept {
			this->hashFunctionPack = hashFunctionPack;
		}
		__LL_NODISCARD__ constexpr void setHash64FunctionPack(Hash64FunctionPack&& hashFunctionPack) noexcept {
			this->hashFunctionPack = std::move(hashFunctionPack);
		}

		#pragma endregion
	public:

		#pragma region HashObject
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const std::string& str) const noexcept {
			return this->hashFunctionPack.call(str);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const std::wstring& str) const noexcept {
			return this->hashFunctionPack.call(str);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::StrPair& str) const noexcept {
			return this->hashFunctionPack.call(str);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::wStrPair& str) const noexcept {
			return this->hashFunctionPack.call(str);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::Str& str) const noexcept {
			return this->hashFunctionPack.call(str);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::wStr& str) const noexcept {
			return this->hashFunctionPack.call(str);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const hash::Hash64& h) const noexcept {
			return this->hashFunctionPack.call(h);
		}
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::ArrayPair<T>& str) const noexcept {
			return this->hashArray<N, T>(str.begin());
		}
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::Array<T>& str) const noexcept {
			return this->hashArray<N, T>(str.begin());
		}
		template<class T, len_t N>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::ArrayPair<T>& str, hash::Hash64* hashesh) const noexcept {
			return this->hashFunctionPack.call(str);
		}

		#pragma endregion
		#pragma region HashHashArray
		template<class T, len_t N>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_hashArray(const T(&_array)[N]) const noexcept {
			return this->hash_hashArray<N, T>(_array);
		}
		// Hashes objects individually and then hash all as one
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_hashArray(const T* _array) const noexcept {
			if constexpr (N == ZERO_UI64) return hash::INVALID_HASH64;

			auto h = this->hashArray<1, T>(_array++);
			if (!h.has_value()) return hash::INVALID_HASH64;

			hash::Hash64 hashes[N]{};
			hashes[0] = *h;

			hash::Hash64* i = hashes + 1;
			for (hash::Hash64* end = hashes + N; i < end; ++i, ++_array)
				*i = *this->hashArray<1, T>(_array);

			return this->hashArray<N>(hashes);
		}

		#pragma endregion
		#pragma region HashHashObject
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::Hash64 hash_hashObject(const meta::ArrayPair<T>& str) const noexcept {
			return this->hash_hashArray<N, T>(str.begin());
		}
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::Hash64 hash_hashObject(const meta::Array<T>& str) const noexcept {
			return this->hash_hashArray<N, T>(str.begin());
		}

		#pragma endregion
		#pragma region Args
	public:
		enum class HashStatus : i8 {
			// All good
			Ok,
			// Args contains no arguments
			Empty,
			// Hash type returned invalid
			HashTypeError,
			// Cannot hash a pointer or vector
			ErrorPointer
		};
	protected:
		template<class T>
		constexpr void hashArgumentsV1Priv(HashStatus*& status, hash::Hash64*& hashes, const T& object) const noexcept {
			if constexpr (std::is_pointer_v<T>) {
				*status++ = HashStatus::ErrorPointer;
				*hashes++ = hash::Hash64();
				return;
			}
			else {
				hash::OptionalHash64 h;

				if constexpr (is_convertible_object_v<T>)
					h = this->hashObject(object);
				else h = this->hashArray<1, T>(&object);
				if (h.has_value()) {
					*status++ = HashStatus::Ok;
					*hashes++ = *h;
				}
				else {
					*status++ = HashStatus::HashTypeError;
					*hashes++ = hash::Hash64();
				}
			}
		}
		template<class T, class... Args>
		constexpr void hashArgumentsV1Priv(HashStatus*& status, hash::Hash64*& hashes, const T& object, const Args&... args) const noexcept {
			this->hashArgumentsV1Priv(status, hashes, object);
			this->hashArgumentsV1Priv(status, hashes, args...);
		}
	public:
		template<class... Args, len_t NUM_ARGS = (sizeof...(Args) + 1)>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashArgumentsV1(HashStatus(&_status)[NUM_ARGS], const Args&... args) const noexcept {
			using pack = traits::parameter_pack_operations<Args...>;
			HashStatus* status = _status;

			if constexpr (pack::empty) {
				*status = HashStatus::Empty;
				return hash::INVALID_HASH64;
			}
			else {
				hash::Hash64 hashes[NUM_ARGS - 1]{};
				hash::Hash64* hashesptr = hashes;

				this->hashArgumentsV1Priv(status, hashesptr, args...);
				*status = HashStatus::Ok;

				return this->hashArray(hashes);
			}
		}
		#pragma endregion
};
*/

} // namespace hash
} // namespace meta
} // namespace llcpp

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#endif // LLANYLIB_HASHTOOLS_HPP_
