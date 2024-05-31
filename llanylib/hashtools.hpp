//////////////////////////////////////////////
//	hashtools.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHTOOLS_HPP_) // Guard && version protector
	#if LLANYLIB_HASHTOOLS_MAYOR_ != 7 || LLANYLIB_HASHTOOLS_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "hashtools.hpp version error!"
		#else
			#error "hashtools.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASHTOOLS_MAYOR_ || LLANYLIB_HASHTOOLS_MINOR_

#else !defined(LLANYLIB_HASHTOOLS_HPP_)
#define LLANYLIB_HASHTOOLS_HPP_
#define LLANYLIB_HASHTOOLS_MAYOR_ 7
#define LLANYLIB_HASHTOOLS_MINOR_ 0

#include "hash.hpp"
#include "reflection.hpp"

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4365) // ignore conversion mismatch [TOCHECK]
#endif // WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace hash {

struct basic_type_hash {
	template<class T>
	static constexpr ll_bool_t is_convertible_v = std::_Is_any_of_v<T, i8, ui8, i16, ui16, i32, ui32, i64, ui64, ll_wchar_t>;

	#pragma region UsedInTools
	template<len_t N, class T>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 hashValues(const T* values, hash::Hash64Function hashFunction) __LL_EXCEPT__ {
		if constexpr (!basic_type_hash::is_convertible_v<T> || N == ZERO_UI64)
			return hash::INVALID_HASH;
		else if constexpr (N == 1) return basic_type_hash::hashValue<T>(*values, hashFunction);
		else {
			constexpr len_t BUFFERLEN = sizeof(T) * N;
			ll_char_t buffer[BUFFERLEN]{};

			ll_char_t* i = buffer;
			for (const T* data_end = values + N; values < data_end; ++values)
				(void)basic_type_hash::conversor<T>(i, *values);
			return hashFunction(buffer, BUFFERLEN);
		}
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 hashArray(const hash::Hash64(&hashes)[N], hash::Hash64Function hashFunction) __LL_EXCEPT__ {
		constexpr len_t BUFFERLEN = sizeof(ui64) * N;
		ll_char_t buffer[BUFFERLEN]{};

		ll_char_t* i = buffer;
		const hash::Hash64* arr = hashes;
		for (const hash::Hash64* data_end = arr + N; arr < data_end; ++arr)
			(void)basic_type_hash::conversor<ui64>(i, arr->get());

		return hashFunction(buffer, BUFFERLEN);
	}

	#pragma endregion

	// Uses bitwise operators: [ ">>", "&" ]
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t conversor(ll_char_t*& buffer, typename W::cinput value) __LL_EXCEPT__ {
		constexpr len_t N = sizeof(U);
		if constexpr (!basic_type_hash::is_convertible_v<U>) {
			buffer += N;
			return LL_FALSE;
		}
		else {
			constexpr len_t BYTES = (N << 3) - 8;
			len_t byte = BYTES;
			for (len_t i{}; i < N; ++i, ++buffer, byte -= 8)
				*buffer = (value >> byte) & 0xFF;
			return LL_TRUE;
		}
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 hashValue(typename W::cinput value, hash::Hash64Function hashFunction) __LL_EXCEPT__ {
		if constexpr (!basic_type_hash::is_convertible_v<U>) return hash::INVALID_HASH;
		else {
			constexpr len_t BUFFERLEN = sizeof(U);
			ll_char_t buffer[BUFFERLEN]{};
			ll_char_t* _ = buffer;
			if(!basic_type_hash::conversor<U, W>(_, value)) return hash::INVALID_HASH;
			return hashFunction(buffer, BUFFERLEN);
		}
	}

	template<class T, class U, class V = traits::template_types<T>, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 combine_shl(typename W::cinput value1, typename V::cinput value2, const ui8 shift) __LL_EXCEPT__ {
		if constexpr (!basic_type_hash::is_convertible_v<T> || !basic_type_hash::is_convertible_v<U>)
			return hash::INVALID_HASH;
		else return value1 ^ (value2 << shift);
	}
	template<class T, class U, class V = traits::template_types<T>, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 combine_shr(typename W::cinput value1, typename V::cinput value2, const ui8 shift) __LL_EXCEPT__ {
		if constexpr (!basic_type_hash::is_convertible_v<T> || !basic_type_hash::is_convertible_v<U>)
			return hash::INVALID_HASH;
		else return value1 ^ (value2 >> shift);
	}
};

// Struct for use in HashTool in an more optimized way (for not constexpr data)
struct basic_type_hash_no_constexpr {
	template<len_t N>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 hashArray(const hash::Hash64(&hashes)[N], hash::Hash64Function hashFunction) __LL_EXCEPT__ {
		return hashFunction(reinterpret_cast<ll_string_t>(hashes), sizeof(hash::Hash64) * N);
	}
	template<len_t N, class T>
	__LL_NODISCARD__ static constexpr hash::OptionalHash64 hashValues(const T* values, hash::Hash64Function hashFunction) __LL_EXCEPT__ {
		if constexpr (!basic_type_hash::is_convertible_v<T> || N == ZERO_UI64)
			return hash::INVALID_HASH;
		else return hashFunction(reinterpret_cast<ll_string_t>(values), sizeof(T) * N);
	}
};

template<class basic_type_hash_class = basic_type_hash>
class HashTool {
	public:
		template<class T>
		static constexpr ll_bool_t is_convertible_object_v = std::_Is_any_of_v<T, hash::Hash64, meta::StrPair, meta::wStrPair, meta::Str, meta::wStr>;

	private:
		Hash64FunctionPack hashFunctionPack;
	public:
		#pragma region Constructors
		constexpr HashTool() __LL_EXCEPT__ = delete;
		constexpr HashTool(const Hash64FunctionPack& hashFunctionPack) __LL_EXCEPT__
			: hashFunctionPack(hashFunctionPack) {}
		constexpr HashTool(Hash64FunctionPack&& hashFunctionPack) __LL_EXCEPT__
			: hashFunctionPack(std::move(hashFunctionPack)) {}
		constexpr ~HashTool() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr HashTool(const HashTool& other) __LL_EXCEPT__
			: hashFunctionPack(other.hashFunctionPack) {}
		constexpr HashTool& operator=(const HashTool& other) __LL_EXCEPT__ {
			this->hashFunctionPack = other.hashFunctionPack;
			return *this;
		}

		constexpr HashTool(HashTool&& other) __LL_EXCEPT__
			: hashFunctionPack(std::move(other.hashFunctionPack)) {}
		constexpr HashTool& operator=(HashTool&& other) __LL_EXCEPT__ {
			this->hashFunctionPack = std::move(other.hashFunctionPack);
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename const HashTool*() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename HashTool*() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr const Hash64FunctionPack& getHash64FunctionPack() const __LL_EXCEPT__ {
			return this->hashFunctionPack;
		}
		__LL_NODISCARD__ constexpr Hash64FunctionPack& getHash64FunctionPack() __LL_EXCEPT__ {
			return this->hashFunctionPack;
		}
		__LL_NODISCARD__ constexpr void setHash64FunctionPack(const Hash64FunctionPack& hashFunctionPack) __LL_EXCEPT__ {
			this->hashFunctionPack = hashFunctionPack;
		}
		__LL_NODISCARD__ constexpr void setHash64FunctionPack(Hash64FunctionPack&& hashFunctionPack) __LL_EXCEPT__ {
			this->hashFunctionPack = std::move(hashFunctionPack);
		}

		#pragma endregion
	public:
		#pragma region HashArray
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashArray(const T* arr) const __LL_EXCEPT__ {
			if constexpr (N == ZERO_UI64) return hash::INVALID_HASH;
			if constexpr (std::is_pointer_v<T>) return hash::INVALID_HASH;
			// Calls defined function to hash arrays
			else if constexpr (std::is_array_v<T>) {
				using array_type_t = traits::type_conversor<T>::array_to_type_t;
				auto h = this->hashArray<traits::array_size<T>, array_type_t>(*arr++);
				// If first element hashed is invalid, other elements will be invalid too
				if (!h.has_value()) return hash::INVALID_HASH;
				
				hash::Hash64 hashes[N]{};
				// If not, we store the hash
				hashes[0] = *h;
				
				// Now, we will hash other elements
				hash::Hash64* i = hashes + 1;
				for (hash::Hash64* end = hashes + N; i < end; ++i, ++arr)
					*i = *this->hashArray<traits::array_size<T>, array_type_t>(*arr);
				
				// An then hash the hash array
				return this->hashArray<N>(hashes);
			}
			// Hashses values using a converting to chars algorithm, and hashing the string
			else if constexpr (basic_type_hash::is_convertible_v<T>)
				return basic_type_hash_class::hashValues<N, T>(arr, this->hashFunctionPack.getHash64Function());
			else if constexpr (is_convertible_object_v<T>) {
				COMMON_HASH_MODE(this->hashObject);
				auto h = this->hashObject(*arr++);
				if (!h.has_value()) return hash::INVALID_HASH;
				
				hash::Hash64 hashes[N]{};
				hashes[0] = *h;
				
				hash::Hash64* i = hashes + 1;
				for (hash::Hash64* end = hashes + N; i < end; ++i, ++arr)
					*i = *this->hashObject(*arr);
				
				return this->hashArray<N>(hashes);
			}
			else if constexpr (traits::has_type_operator_v<T, hash::OptionalHash64>) {
				auto h = (arr++)->operator hash::OptionalHash64();
				if (!h.has_value()) return hash::INVALID_HASH;

				hash::Hash64 hashes[N]{};
				hashes[0] = *h;

				hash::Hash64* i = hashes + 1;
				for (hash::Hash64* end = hashes + N; i < end; ++i, ++arr)
					*i = *arr->operator hash::OptionalHash64();

				return this->hashArray<N>(hashes);
			}
			// Hashes undefined objects
			else {
				meta::StrTypeid id = traits::getStrTypeId<T>(this->hashFunctionPack.getStrPairHash64Function());

				auto h = this->hashFunctionPack.call(arr++, id);
				if (!h.has_value()) return hash::INVALID_HASH;

				hash::Hash64 hashes[N]{};
				hashes[0] = *h;

				hash::Hash64* i = hashes + 1;
				for (hash::Hash64* end = hashes + N; i < end; ++i, ++arr)
					*i = *this->hashFunctionPack.call(arr, id);

				return this->hashArray<N>(hashes);
			}
		}
		template<class T, len_t N>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashArray(const T(&arr)[N]) const __LL_EXCEPT__ {
			return this->hashArray<N, T>(arr);
		}
		// Predefined hasheables
		template<len_t N>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashArray(const hash::Hash64(&hashes)[N]) const __LL_EXCEPT__ {
			return basic_type_hash_class::hashArray<N>(hashes, this->hashFunctionPack.getHash64Function());
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashArray(const ll_char_t(&str)[N]) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str, N);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashArray(const ll_wchar_t(&str)[N]) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str, N);
		}

		#pragma endregion
		#pragma region HashObject
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::StrPair& str) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::wStrPair& str) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::Str& str) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::wStr& str) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str);
		}
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::ArrayPair<T>& str) const __LL_EXCEPT__ {
			return this->hashArray<N, T>(str.begin());
		}
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::Array<T>& str) const __LL_EXCEPT__ {
			return this->hashArray<N, T>(str.begin());
		}
		template<class T, len_t N>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashObject(const meta::ArrayPair<T>& str, hash::Hash64* hashesh) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str);
		}

		#pragma endregion
		#pragma region HashHashArray
		template<class T, len_t N>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_hashArray(const T(&arr)[N]) const __LL_EXCEPT__ {
			return this->hash_hashArray<N, T>(arr);
		}
		// Hashes objects individually and then hash all as one
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_hashArray(const T* arr) const __LL_EXCEPT__ {
			if constexpr (N == ZERO_UI64) return hash::INVALID_HASH;

			auto h = this->hashArray<1, T>(arr++);
			if (!h.has_value()) return hash::INVALID_HASH;

			hash::Hash64 hashes[N]{};
			hashes[0] = *h;

			hash::Hash64* i = hashes + 1;
			for (hash::Hash64* end = hashes + N; i < end; ++i, ++arr)
				*i = *this->hashArray<1, T>(arr);

			return this->hashArray<N>(hashes);
		}

		#pragma endregion
		#pragma region HashHashObject
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::Hash64 hash_hashObject(const meta::ArrayPair<T>& str) const __LL_EXCEPT__ {
			return this->hash_hashArray<N, T>(str.begin());
		}
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::Hash64 hash_hashObject(const meta::Array<T>& str) const __LL_EXCEPT__ {
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
		constexpr void hashArgumentsV1Priv(HashStatus*& status, hash::Hash64*& hashes, const T& object) const __LL_EXCEPT__ {
			if constexpr (std::is_pointer_v<T>) {
				*status++ = HashStatus::ErrorPointer;
				*hashes++ = hash::Hash64();
				return;
			}

			auto h = this->hashArray<1, T>(&object);
			if (h.has_value()) {
				*status++ = HashStatus::Ok;
				*hashes++ = *h;
			}
			else {
				*status++ = HashStatus::HashTypeError;
				*hashes++ = hash::Hash64();
			}
		}
		template<class T, class... Args>
		constexpr void hashArgumentsV1Priv(HashStatus*& status, hash::Hash64*& hashes, const T& object, const Args&... args) const __LL_EXCEPT__ {
			this->hashArgumentsV1Priv(status, hashes, object);
			this->hashArgumentsV1Priv(status, hashes, args...);
		}
	public:
		template<class... Args, len_t NUM_ARGS = (sizeof...(Args) + 1)>
		__LL_NODISCARD__ constexpr hash::OptionalHash64 hashArgumentsV1(HashStatus(&_status)[NUM_ARGS], const Args&... args) const __LL_EXCEPT__ {
			using pack = traits::parameter_pack_operations<Args...>;
			HashStatus* status = _status;

			if constexpr (pack::empty) {
				*status = HashStatus::Empty;
				return hash::INVALID_HASH;
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

} // namespace hash
} // namespace meta
} // namespace llcpp

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#endif // LLANYLIB_HASHTOOLS_HPP_
