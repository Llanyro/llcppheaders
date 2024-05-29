//////////////////////////////////////////////
//	hashtools.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 6.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHTOOLS_HPP_) // Guard && version protector
	#if LLANYLIB_HASHTOOLS_MAYOR_ != 6 || LLANYLIB_HASHTOOLS_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "hashtools.hpp version error!"
		#else
			#error "hashtools.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASHTOOLS_MAYOR_ || LLANYLIB_HASHTOOLS_MINOR_

#else !defined(LLANYLIB_HASHTOOLS_HPP_)
#define LLANYLIB_HASHTOOLS_HPP_
#define LLANYLIB_HASHTOOLS_MAYOR_ 6
#define LLANYLIB_HASHTOOLS_MINOR_ 0

#include "hash.hpp"
#include "reflection.hpp"

namespace llcpp {
namespace meta {
namespace hash {

struct basic_type_hash {
	template<class T>
	static constexpr ll_bool_t is_convertible_v = std::_Is_any_of_v<T, i8, ui8, i16, ui16, i32, ui32, i64, ui64>;

	// Uses bitwise operators: [ ">>", "&" ]
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t conversor(ll_char_t*& buffer, typename W::cinput value) __LL_EXCEPT__ {
		constexpr len_t N = sizeof(typename W::type);
		if constexpr (!is_convertible_v<typename W::type>) {
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
	__LL_NODISCARD__ static constexpr hash::Hash64 hashValue(typename W::cinput value, hash::HashFunction hashFunction) __LL_EXCEPT__ {
		if constexpr (!traits::is_basic_type_v<typename W::type>) return hash::Hash64();
		else {
			constexpr len_t BUFFERLEN = sizeof(typename W::type);
			ll_char_t buffer[BUFFERLEN]{};
			ll_char_t* _ = buffer;
			if(!basic_type_hash::conversor<U, W>(_, value)) return hash::Hash64();
			return hashFunction(buffer, BUFFERLEN);
		}
	}
};

class Test {
	public:
		constexpr Test() {}
		constexpr ~Test() {}
		__LL_NODISCARD__ constexpr operator hash::Hash64() const __LL_EXCEPT__ { return hash::Hash64(); }
		__LL_NODISCARD__ constexpr operator hash::Hash64() __LL_EXCEPT__ { return hash::Hash64(); }
		__LL_NODISCARD__ constexpr operator ll_bool_t() const __LL_EXCEPT__ { return LL_FALSE; }
};

class HashTool {
	private:
		HashFunctionPack hashFunctionPack;
	public:
		#pragma region Constructors
		constexpr HashTool() __LL_EXCEPT__ = delete;
		constexpr HashTool(const HashFunctionPack& hashFunctionPack) __LL_EXCEPT__
			: hashFunctionPack(hashFunctionPack) {}
		constexpr HashTool(HashFunctionPack&& hashFunctionPack) __LL_EXCEPT__
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
		__LL_NODISCARD__ constexpr const HashFunctionPack& getHashFunctionPack() const __LL_EXCEPT__ {
			return this->hashFunctionPack;
		}
		__LL_NODISCARD__ constexpr HashFunctionPack& getHashFunctionPack() __LL_EXCEPT__ {
			return this->hashFunctionPack;
		}
		__LL_NODISCARD__ constexpr void setHashFunctionPack(const HashFunctionPack& hashFunctionPack) __LL_EXCEPT__ {
			this->hashFunctionPack = hashFunctionPack;
		}
		__LL_NODISCARD__ constexpr void setHashFunctionPack(HashFunctionPack&& hashFunctionPack) __LL_EXCEPT__ {
			this->hashFunctionPack = std::move(hashFunctionPack);
		}

		#pragma endregion
	public:
		#pragma region HashArray
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::Hash64 hashArray(const T* arr) const __LL_EXCEPT__ {
			if constexpr (basic_type_hash::is_convertible_v<T>) {
				constexpr len_t BUFFERLEN = sizeof(T) * N;
				ll_char_t buffer[BUFFERLEN]{};

				ll_char_t* i = buffer;
				for (const T* data_end = arr + N; arr < data_end; ++arr)
					basic_type_hash::conversor<T>(i, *arr);

				return this->hashFunctionPack.call(buffer, BUFFERLEN);
			}
			else {
				meta::StrTypeid id = traits::getStrTypeId<T>(this->hashFunctionPack.getStrPairHashFunction());
				hash::Hash64 hashes[N]{};

				hash::Hash64* i = hashes;
				for (const T* data_end = arr + N; arr < data_end; ++arr, ++i)
					*i = this->hashFunctionPack.call(arr, id);

				return this->hashArray(hashes);
			}
		}
		template<class T, len_t N>
		__LL_NODISCARD__ constexpr hash::Hash64 hashArray(const T(&arr)[N]) const __LL_EXCEPT__ {
			return this->hashArray<N, T>(arr);
		}
		// Predefined hasheables
		template<len_t N>
		__LL_NODISCARD__ constexpr hash::Hash64 hashArray(const hash::Hash64(&hashes)[N]) const __LL_EXCEPT__ {
			constexpr len_t BUFFERLEN = sizeof(ui64) * N;
			ll_char_t buffer[BUFFERLEN]{};

			ll_char_t* i = buffer;
			const hash::Hash64* arr = hashes;
			for (const hash::Hash64* data_end = arr + N; arr < data_end; ++arr)
				basic_type_hash::conversor<ui64>(i, arr->get());

			return this->hashFunctionPack.call(buffer, BUFFERLEN);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr hash::Hash64 hashArray(const ll_char_t(&str)[N]) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str, N);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr hash::Hash64 hashArray(const ll_wchar_t(&str)[N]) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str, N);
		}

		#pragma endregion
		#pragma region HashObject
		__LL_NODISCARD__ constexpr hash::Hash64 hashObject(const meta::StrPair& str) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 hashObject(const meta::wStrPair& str) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 hashObject(const meta::Str& str) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 hashObject(const meta::wStr& str) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str);
		}
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::Hash64 hashObject(const meta::ArrayPair<T>& str) const __LL_EXCEPT__ {
			return this->hashArray<N, T>(str.begin());
		}
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::Hash64 hashObject(const meta::Array<T>& str) const __LL_EXCEPT__ {
			return this->hashArray<N, T>(str.begin());
		}
		template<class T, len_t N>
		__LL_NODISCARD__ constexpr hash::Hash64 hashObject(const meta::ArrayPair<T>& str, hash::Hash64* hashesh) const __LL_EXCEPT__ {
			return this->hashFunctionPack.call(str);
		}

		#pragma endregion
		#pragma region HashHashArray
		template<class T, len_t N>
		__LL_NODISCARD__ constexpr hash::Hash64 hash_hashArray(const T(&arr)[N]) const __LL_EXCEPT__ {
			return this->hash_hashArray<N, T>(arr);
		}
		// Hashes objects individually and then hash all as one
		template<len_t N, class T>
		__LL_NODISCARD__ constexpr hash::Hash64 hash_hashArray(const T* arr) const __LL_EXCEPT__ {
			meta::StrTypeid id = traits::getStrTypeId<T>(this->hashFunctionPack.getStrPairHashFunction());
			hash::Hash64 hashes[N]{};

			hash::Hash64* i = hashes;
			for (const T* data_end = arr + N; arr < data_end; ++arr, ++i) {
				if constexpr (basic_type_hash::is_convertible_v<T>)
					*i = basic_type_hash::hashValue<T>(*arr, this->hashFunctionPack.getHashFunction());
				else *i = this->hashFunctionPack.call(arr, id);
			}

			return this->hashArray<hash::Hash64, N>(hashes);
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
};

// Hash modes:
//	1. Copy all object data into a string and hash that data
//	2. Copy all object Hash into a string and hash all the hashes
//	3. Add to any method TypeId to hash
//		3.1: Use type as raw data to hash
//		3.2: Use type hash to hash
//		3.3: Use both
//
/*class DataHashConversor {
		#pragma region General
	public:
		struct HashFormationPack {
			using FunctionObjectHasher = hash::Hash64(*)(const void*, const meta::Typeid&);

			

		};

	private:
		HashFunctionPack hashFunctionPack;
		HashFormationPack hashFormationPack;
	public:
		#pragma region Constructors
		constexpr DataHashConversor() __LL_EXCEPT__ = delete;
		constexpr DataHashConversor(const HashFunctionPack& hashFunctionPack) __LL_EXCEPT__
			: hashFunctionPack(hashFunctionPack) {}
		constexpr DataHashConversor(HashFunctionPack&& hashFunctionPack) __LL_EXCEPT__
			: hashFunctionPack(std::move(hashFunctionPack)) {}
		constexpr ~DataHashConversor() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr DataHashConversor(const DataHashConversor& other) __LL_EXCEPT__
			: hashFunctionPack(other.hashFunctionPack) {}
		constexpr DataHashConversor& operator=(const DataHashConversor& other) __LL_EXCEPT__ {
			this->hashFunctionPack = other.hashFunctionPack;
			return *this;
		}

		constexpr DataHashConversor(DataHashConversor&& other) __LL_EXCEPT__
			: hashFunctionPack(std::move(other.hashFunctionPack)) {}
		constexpr DataHashConversor& operator=(DataHashConversor&& other) __LL_EXCEPT__ {
			this->hashFunctionPack = std::move(other.hashFunctionPack);
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename const DataHashConversor*() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename DataHashConversor*() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr const HashFunctionPack& getHashFunctionPack() const __LL_EXCEPT__ {
			return this->hashFunctionPack;
		}
		__LL_NODISCARD__ constexpr HashFunctionPack& getHashFunctionPack() __LL_EXCEPT__ {
			return this->hashFunctionPack;
		}
		__LL_NODISCARD__ constexpr void setHashFunctionPack(const HashFunctionPack& hashFunctionPack) __LL_EXCEPT__ {
			this->hashFunctionPack = hashFunctionPack;
		}
		__LL_NODISCARD__ constexpr void setHashFunctionPack(HashFunctionPack&& hashFunctionPack) __LL_EXCEPT__ {
			this->hashFunctionPack = std::move(hashFunctionPack);
		}

		#pragma endregion

		#pragma endregion
		#pragma region ArrayAndObjects
	public:
		// This function hashes with V2 or V1_Object
		template<class U, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr hash::Hash64 hashData(W::cinput object) const __LL_EXCEPT__ {
			if constexpr (std::is_pointer_v<typename W::type>) return hash::Hash64();
			// if is a hash, we just hash it with a specific function
			else if constexpr (std::is_same_v<typename W::type, hash::Hash64>)
				return this->hashFunctionPack.call(object);
			// If is a char, is easyly hasheable
			else if constexpr (std::is_same_v<typename W::type, ll_char_t>)
				return this->hashFunctionPack.call(&object, 1);
			// If hash version 1 is avaible for this object
			// This means, either is a object with convertToCharsSimple() or is an aricmetic type
			else if constexpr (DataHashConversor::isHasheable<typename W::type, HashVersion::V1_Object>()) {
				constexpr len_t BUFFERLEN = sizeof(typename W::type);
				ll_char_t buffer[BUFFERLEN]{};
				if constexpr (DataHashConversor::is_convertible_v<typename W::type>)
					DataHashConversor::conversor<typename W::type, BUFFERLEN>(buffer, object);
				else object.convertToCharsSimple(buffer);
				return this->hashFunctionPack.call(buffer, BUFFERLEN);
			}
			// If hash version 2 is avaible for this object, is has operator llcpp::meta::hash::Hash64() avaible
			else if constexpr (DataHashConversor::isHasheable<typename W::type, HashVersion::V2>())
				return object.operator llcpp::meta::hash::Hash64();
			else return hash::Hash64();
		}
		template<HashVersion VERSION = HashVersion::V1, class T, len_t N>
		__LL_NODISCARD__ constexpr hash::Hash64 hashData(const T(&arr)[N]) const __LL_EXCEPT__ {
			return this->hashData<N, VERSION, T>(arr);
		}
		template<len_t N, HashVersion VERSION = HashVersion::V1, class T>
		__LL_NODISCARD__ constexpr hash::Hash64 hashData(const T* arr) const __LL_EXCEPT__ {
			if constexpr (std::is_pointer_v<T> || N == ZERO_UI64) return hash::Hash64();
			else if constexpr (std::is_array_v<T>) return this->hashData<N, VERSION, traits::type_conversor<T>::array_to_type_t>(arr);
			// If is an array of hashes
			else if constexpr (std::is_same_v<T, hash::Hash64>) {
				constexpr len_t BUFFERLEN = sizeof(ui64) * N;
				ll_char_t buffer[BUFFERLEN]{};

				ll_char_t* i = buffer;
				for (const T* data_end = arr + N; arr < data_end; ++arr)
					DataHashConversor::conversor<ui64>(i, arr->get());

				return this->hashFunctionPack.call(buffer, BUFFERLEN);
			}
			else if constexpr (std::is_same_v<T, ll_char_t>)
				return this->hashFunctionPack.call(arr, N);
			else if constexpr (!DataHashConversor::isHasheable<T, VERSION>())
				return hash::Hash64();
			else if constexpr (VERSION == HashVersion::V1 || DataHashConversor::is_convertible_v<T>) {
				constexpr len_t BUFFERLEN = sizeof(T) * N;
				ll_char_t buffer[BUFFERLEN]{};

				ll_char_t* i = buffer;
				for (const T* data_end = arr + N; arr < data_end; ++arr) {
					if constexpr (DataHashConversor::is_convertible_v<T>)
						DataHashConversor::conversor<T>(i, *arr);
					else arr->convertToChars(&i);
				}

				return this->hashFunctionPack.call(buffer, BUFFERLEN);
			}
			else if constexpr (VERSION == HashVersion::V2) {
				hash::Hash64 buffer[N]{};

				hash::Hash64* i = buffer;
				for (const T* data_end = arr + N; arr < data_end; ++arr, ++i)
					*i = arr->operator llcpp::meta::hash::Hash64();

				return this->hashData<VERSION>(buffer);
			}
			// We ignore V1_Object and others not defined
			else return hash::Hash64();
		}

		#pragma endregion
		#pragma region UndefinedArgs
	public:


		#pragma endregion

};
*/
/*
		template<class U, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr hash::Hash64 hashData(W::cinput object) const __LL_EXCEPT__ {
			if constexpr (std::is_pointer_v<typename W::type>) return hash::Hash64();
			// if is a hash, we just hash it with a specific function
			else if constexpr (std::is_same_v<typename W::type, hash::Hash64>)
				return this->hashFunctionPack.call(object);
			// If is a char, is easyly hasheable
			else if constexpr (std::is_same_v<typename W::type, ll_char_t>)
				return this->hashFunctionPack.call(&object, 1);
			// If hash version 1 is avaible for this object
			// This means, either is a object with convertToCharsSimple() or is an aricmetic type
			else if constexpr (DataHashConversor::isHasheable<typename W::type, HashVersion::V1_Object>()) {
				constexpr len_t BUFFERLEN = sizeof(typename W::type);
				ll_char_t buffer[BUFFERLEN]{};
				if constexpr (DataHashConversor::is_convertible_v<typename W::type>)
					DataHashConversor::conversor<typename W::type, BUFFERLEN>(buffer, object);
				else object.convertToCharsSimple(buffer);
				return this->hashFunctionPack.call(buffer, BUFFERLEN);
			}
			// If hash version 2 is avaible for this object, is has operator llcpp::meta::hash::Hash64() avaible
			else if constexpr (DataHashConversor::isHasheable<typename W::type, HashVersion::V2>())
				return object.operator llcpp::meta::hash::Hash64();
			else return hash::Hash64();
		}
		template<HashVersion VERSION = HashVersion::V1, class T, len_t N>
		__LL_NODISCARD__ constexpr hash::Hash64 hashData(const T(&arr)[N]) const __LL_EXCEPT__ {
			return this->hashData<N, VERSION, T>(arr);
		}
		template<len_t N, HashVersion VERSION = HashVersion::V1, class T>
		__LL_NODISCARD__ constexpr hash::Hash64 hashData(const T* arr) const __LL_EXCEPT__ {
			if constexpr (std::is_pointer_v<T> || N == ZERO_UI64) return hash::Hash64();
			else if constexpr (std::is_array_v<T>) return this->hashData<N, VERSION, traits::type_conversor<T>::array_to_type_t>(arr);
			// If is an array of hashes
			else if constexpr (std::is_same_v<T, hash::Hash64>) {
				constexpr len_t BUFFERLEN = sizeof(ui64) * N;
				ll_char_t buffer[BUFFERLEN]{};

				ll_char_t* i = buffer;
				for (const T* data_end = arr + N; arr < data_end; ++arr)
					DataHashConversor::conversor<ui64>(i, arr->get());

				return this->hashFunctionPack.call(buffer, BUFFERLEN);
			}
			else if constexpr (std::is_same_v<T, ll_char_t>)
				return this->hashFunctionPack.call(arr, N);
			else if constexpr (!DataHashConversor::isHasheable<T, VERSION>())
				return hash::Hash64();
			else if constexpr (VERSION == HashVersion::V1 || DataHashConversor::is_convertible_v<T>) {
				constexpr len_t BUFFERLEN = sizeof(T) * N;
				ll_char_t buffer[BUFFERLEN]{};

				ll_char_t* i = buffer;
				for (const T* data_end = arr + N; arr < data_end; ++arr) {
					if constexpr (DataHashConversor::is_convertible_v<T>)
						DataHashConversor::conversor<T>(i, *arr);
					else arr->convertToChars(&i);
				}

				return this->hashFunctionPack.call(buffer, BUFFERLEN);
			}
			else if constexpr (VERSION == HashVersion::V2) {
				hash::Hash64 buffer[N]{};

				hash::Hash64* i = buffer;
				for (const T* data_end = arr + N; arr < data_end; ++arr, ++i)
					*i = arr->operator llcpp::meta::hash::Hash64();

				return this->hashData<VERSION>(buffer);
			}
			// We ignore V1_Object and others not defined
			else return hash::Hash64();
		}
*/
/*class ASDAFA {
	#pragma region Enums
	public:
		enum class HashVersion : i8 {
			// Converts objects to chars in a contiguous vector
			// Then using CityHash hash all vector
			// Objects are transformed to chars using a function in the object class
			// The function signature is: constexpr void convertToChars(ll_char_t** buffer, HashV1Status** status, len_t size) const __LL_EXCEPT__;
			// If you need an example go to BasicTypeWrapper, it has that function implemented and explained
			V1,
			// Hashes every object one by one
			// Then hashes the generated hash vector
			// Objects are transformed to chars using a function in the object class
			// The function signature is: constexpr operator llcpp::meta::hash::Hash64() const __LL_EXCEPT__;
			V2,

			// Converts object to chars in a contiguous vector
			// This is only for hashing objects alone
			// The function signature is: constexpr void convertToCharsSimple(ll_char_t* buffer) const __LL_EXCEPT__;
			// Also hashes basic types
			V1_Object
		};
		enum class HashArgsVersion {
			// Same as V1 but for args
			V1_Args,
			// Same as V2 but for args
			V2_Args
		};
		enum class HashStatus : i8 {
			// All good
			Ok,

			// Args contains no arguments
			Empty,
			// Requested a invalid version
			InvalidHashVersion,
			// Is not hasheable with provided version
			ErrorIsNotHasheable,
			// Cannot hash a pointer or vector
			ErrorPointer,
			// An error ocurrend in one argument
			ErrorHashArgs,
			// Invalid version for function
			ErrorInvalidVersion,


			CustomFunctionInternalError,
			ErrorNoFunctionAvaible
		};
		struct HashSize {
			template<class T, HashVersion VERSION>
			static constexpr len_t getSize() __LL_EXCEPT__;

			len_t sizeof_;
			constexpr HashSize(const len_t sizeof_) __LL_EXCEPT__ : sizeof_(sizeof_) {}
			constexpr ~HashSize() __LL_EXCEPT__ {}

			constexpr HashSize operator&&(const HashSize& other) const __LL_EXCEPT__ {
				return HashSize(this->sizeof_ + other.sizeof_);
			}
			constexpr const HashSize& operator&&(const ll_bool_t) const __LL_EXCEPT__ { return *this; }
		};


	#pragma endregion
	#pragma region TypesAndStaticData
	public:
		template<class T>
		static constexpr ll_bool_t is_convertible_v = std::_Is_any_of_v<T, i8, ui8, i16, ui16, i32, ui32, i64, ui64>;
		// Used to make signature for HashV1
		static constexpr ll_char_t** NULL_CHAR_CONVERTIBLE = LL_NULLPTR;
		// Used to make signature for HashV1
		static constexpr HashStatus** NULL_ERROR = LL_NULLPTR;
		// Used to make signature for HashV1
		static constexpr ll_char_t* NULL_CHAR_CONVERTIBLE_SIMPLE = LL_NULLPTR;
		template<HashVersion VERSION, class... Args>
		static constexpr len_t args_sizeof = (HashSize(HashSize::getSize<Args, VERSION>()) && ...).sizeof_;
	#pragma endregion
	#pragma region StaticFunctions
	public:
		template<class T, HashVersion VERSION = HashVersion::V1>
		__LL_NODISCARD__ static constexpr ll_bool_t isHasheable() __LL_EXCEPT__;
		template<class T[], HashVersion VERSION = HashVersion::V1>
		__LL_NODISCARD__ static constexpr ll_bool_t isHasheable() __LL_EXCEPT__;
	public:
		// Converts any integral number into chars
		// Requires a memory buffer of the size of the type
		// Only accepts integral numbers
		template<class T, len_t N = sizeof(T)>
		static constexpr void conversor(ll_char_t(&buffer)[N], const T value) __LL_EXCEPT__;
		// Converts any integral number into chars
		// Useful when using a vector of not known size
		// Only accepts integral numbers
		// This is the main core of Algorithm V1 when using arrays of basic types
		template<class T>
		__LL_NODISCARD__ static constexpr ll_bool_t conversor(ll_char_t*& buffer, const T value) __LL_EXCEPT__;
		template<HashVersion VERSION>
		__LL_NODISCARD__ static constexpr HashVersion convertFromArgVersion() __LL_EXCEPT__ {
			if constexpr (VERSION == HashVersion::V1_Args) return HashVersion::V1;
			else if constexpr (VERSION == HashVersion::V2_Args) return HashVersion::V2;
			else return VERSION;
		}
	#pragma endregion
	#pragma region Class
	#pragma region Functions
	protected:
		__LL_NODISCARD__ constexpr ll_bool_t checkStatus(HashStatus* status, len_t size) const __LL_EXCEPT__ {
			for (; size > ZERO_UI64; --size, ++status)
				if (*status != HashStatus::Ok)
					return LL_FALSE;
			return LL_TRUE;
		}
		template<HashVersion VERSION, class T>
		__LL_NODISCARD__ constexpr void hashArguments(ll_char_t*& buffer, HashStatus*& status, const T& object) const __LL_EXCEPT__ {
			if constexpr (DataHashConversor::isHasheable<T, VERSION>()) {
				if constexpr (VERSION == HashVersion::V1) {
					if constexpr (DataHashConversor::is_convertible_v<T>) {
						// [TOCHECK] Check if this constexpr is valid or not
						if constexpr (DataHashConversor::conversor<T>(buffer, object))
							*status++ = HashStatus::Ok;
						else *status++ = HashStatus::ErrorPointer;
					}
					// If is not convertible (is not an aritmetic number)
					else object.convertToChars(&buffer, &status, );
				}
				else if constexpr (VERSION == HashVersion::V2) {

				}
				else *status++ = HashStatus::InvalidHashVersion;
			}
			else {
				if constexpr (traits::is_pointer_v<T>)
					*status++ = HashStatus::ErrorPointer;
				else {
					buffer += HashSize::getSize<T, VERSION>();
					*status++ = HashStatus::ErrorInvalidVersion;
				}
			}
		}
		template<HashVersion VERSION, class T, class... Args>
		__LL_NODISCARD__ constexpr void hashArguments(ll_char_t*& buffer, HashStatus*& status, const T& object, const Args&... args) const __LL_EXCEPT__ {
			this->DataHashConversor::hashArguments<VERSION>(buffer, status, object);
			this->DataHashConversor::hashArguments<VERSION>(buffer, status, args...);
		}

	public:
		#pragma region Constructors

		#pragma endregion
		#pragma region Hash
		// Last position in "status" is global status
		template<HashVersion VERSION, class... Args, len_t NUM_ARGS = (sizeof...(Args) + 1)>
		__LL_NODISCARD__ constexpr hash::Hash64 hashData(HashStatus(&_status)[NUM_ARGS], const Args&... args) const __LL_EXCEPT__ {
			using pack = traits::parameter_pack_operations<Args...>;
			HashStatus* status = _status;

			if constexpr (pack::empty) {
				*status = HashStatus::Empty;
				return hash::Hash64();
			}
			// Only one element
			//else if constexpr (pack::size == 1ull) {
			//	hash::Hash64 result;
			//	// We need to change version
			//	// Args version does not works the same as normal versions
			//	constexpr HashVersion CONVERTED_VERSION = DataHashConversor::convertFromArgVersion<VERSION>();
			//
			//	// We check if is a standard pointer like int*
			//	if constexpr (std::is_pointer_v<Args>) *status++ = HashStatus::ErrorPointer;
			//	// Check if is hasheable with converted version
			//	else if constexpr (DataHashConversor::isHasheable<Args, CONVERTED_VERSION>()) {
			//		//if constexpr (std::is_array_v<Args>)
			//		//	result = this->hashData<CONVERTED_VERSION, Args, traits::array_size<Args>>(args);
			//		//else result = this->hashData<Args>(args);
			//		//*status++ = HashStatus::Ok;
			//
			//		if constexpr (std::is_array_v<Args>) {
			//			//result = this->hashData<CONVERTED_VERSION, Args, traits::array_size<Args>>(args);
			//			*status++ = HashStatus::Empty;
			//		}
			//		else {
			//			result = this->hashData<Args>(args);
			//			*status++ = HashStatus::Ok;
			//		}
			//	}
			//	else *status++ = HashStatus::ErrorIsNotHasheable;
			//	*status = HashStatus::Ok;
			//	return result;
			//}
			else if constexpr (VERSION == HashVersion::V1_Args) {
				constexpr len_t SIZE = DataHashConversor::args_sizeof<VERSION, Args...>;
				ll_char_t _buffer[SIZE]{};
				
				// Get raw data
				ll_char_t* buffer = _buffer;
				this->DataHashConversor::hashArguments<VERSION>(buffer, status, args...);
				
				// Check all status
				*status = (this->checkStatus(status, NUM_ARGS - 1)) ? HashStatus::Ok : HashStatus::ErrorHashArgs;
				
				// Return hash generated. Even if any hash wasnt correctly generated
				return this->hashFunctionPack.call(buffer, SIZE);
				//return hash::Hash64();
			}
			else {
				*status = HashStatus::InvalidHashVersion;
				return hash::Hash64();
			}
		}

		#pragma endregion
	#pragma endregion
	#pragma endregion
};

__LL_TEMPLATE_HAS_FUNCTION_BASE__(convert_to_chars_extra, p->convertToChars(DataHashConversor::NULL_CHAR_CONVERTIBLE, DataHashConversor::NULL_ERROR, ZERO_UI64), LL_FALSE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(convert_to_chars, p->convertToChars(DataHashConversor::NULL_CHAR_CONVERTIBLE), LL_FALSE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(convert_to_chars_simple, p->convertToCharsSimple(DataHashConversor::NULL_CHAR_CONVERTIBLE_SIMPLE), LL_FALSE);

#pragma region StaticFunctions
template<class T, DataHashConversor::HashVersion VERSION>
__LL_NODISCARD__ __LL_INLINE__ static constexpr ll_bool_t DataHashConversor::isHasheable() __LL_EXCEPT__ {
	if constexpr (std::is_pointer_v<T>) return LL_FALSE;
	else if constexpr (std::is_array_v<T>)
		return DataHashConversor::isHasheable<traits::type_conversor<T>::array_to_type_t, VERSION>();
	else if constexpr (DataHashConversor::is_convertible_v<T>) return LL_TRUE;
	else if constexpr (std::is_same_v<T, hash::Hash64>) return LL_TRUE;
	else if constexpr (std::is_floating_point_v<T>) return LL_FALSE;
	else if constexpr (VERSION == HashVersion::V1) {
		if constexpr (hash::has_convert_to_chars_v<T>) return LL_TRUE;
		else return LL_FALSE;
	}
	else if constexpr (VERSION == HashVersion::V2) {
		if constexpr (traits::has_type_operator_v<T, hash::Hash64>) return LL_TRUE;
		else return LL_FALSE;
	}
	else if constexpr (VERSION == HashVersion::V1_Object) {
		if constexpr (hash::has_convert_to_chars_simple_v<T>) return LL_TRUE;
		else return LL_FALSE;
	}
	else return LL_FALSE;
}
template<class T[], DataHashConversor::HashVersion VERSION>
__LL_NODISCARD__ __LL_INLINE__ static constexpr ll_bool_t DataHashConversor::isHasheable() __LL_EXCEPT__ {
	return DataHashConversor::isHasheable<traits::type_conversor<T>::array_to_type_t, VERSION>();
}
template<class T, len_t N>
__LL_INLINE__ static constexpr void DataHashConversor::conversor(ll_char_t(&buffer)[N], const T value) __LL_EXCEPT__ {
	if constexpr (!DataHashConversor::is_convertible_v<T>) return;
	ll_char_t* mem = buffer;
	len_t byte = (N << 3) - 8;
	for (len_t i{}; i < N; ++i, ++mem, byte -= 8)
		*mem = (value >> byte) & 0xFF;
}
template<class T>
__LL_NODISCARD__ __LL_INLINE__ static constexpr ll_bool_t DataHashConversor::conversor(ll_char_t*& buffer, const T value) __LL_EXCEPT__ {
	constexpr len_t N = sizeof(T);
	if constexpr (!DataHashConversor::is_convertible_v<T>) {
		mem += N;
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

template<class T, DataHashConversor::HashVersion VERSION>
__LL_NODISCARD__ __LL_INLINE__ static constexpr len_t DataHashConversor::HashSize::getSize() __LL_EXCEPT__ {
	if constexpr (VERSION == DataHashConversor::HashVersion::V1_Args || VERSION == DataHashConversor::HashVersion::V1) {
		if constexpr (std::is_pointer_v<T>) return ZERO_UI64;
		else if constexpr (std::is_array_v<T>) return sizeof(hash::Hash64);
		else if constexpr (traits::is_basic_type_v<T>) return sizeof(T);
		else if constexpr (traits::has_type_operator_v<T, hash::Hash64>) return sizeof(hash::Hash64);
		else return ZERO_UI64;
	}
	else if constexpr (VERSION == DataHashConversor::HashVersion::V2_Args || VERSION == DataHashConversor::HashVersion::V2) {
		if constexpr (std::is_pointer_v<T>) return ZERO_UI64;
		else if constexpr (std::is_array_v<T>) return sizeof(hash::Hash64);
		else if constexpr (traits::is_basic_type_v<T>) return sizeof(hash::Hash64);
		else if constexpr (traits::has_type_operator_v<T, hash::Hash64>) return sizeof(hash::Hash64);
		else return ZERO_UI64;
	}
	else return ZERO_UI64;
}

#pragma endregion*/
//struct LastError {
//	ui64 hash;
//	DataHashConversor::HashStatus status;
//	len_t pos;
//};
///
//constexpr LastError valueget() {
//	HashFunctionPack pack(
//		[](const meta::StrPair&) -> hash::Hash64 { return hash::Hash64(999); },
//		[](ll_string_t str, len_t size) -> hash::Hash64 {
//			len_t buffer{};
//			for (; size > ZERO_UI64; --size, ++str) buffer += *str;
//			return hash::Hash64(buffer);
//		},
//		[](const hash::Hash64& h) -> hash::Hash64 { return h; },
//		[](const void*, const Typeid&) -> hash::Hash64 { return hash::Hash64(999); }
//	);
//	DataHashConversor data(pack);
//	hash::Hash64 hashes[] = { 1ull, 2ull, 3ull, 4ull, 5ull, 6ull, 7ull };
//	constexpr len_t STATUS_SIZE = 2;
//	DataHashConversor::HashStatus status[STATUS_SIZE]{};
//
//	auto result = data.hashData<DataHashConversor::HashVersion::V1_Args>(status, hashes);
//	//auto result = data.hashData<DataHashConversor::HashVersion::V1_Args>(status, *(hashes + 4), 9);
//	//auto result = data.hashData<hash::Hash64>(*hashes);
//	//auto result = data.hashData<DataHashConversor::HashVersion::V1>(hashes);
//
//	LastError err{};
//	err.hash = result.get();
//
//	for (len_t i{}; i < STATUS_SIZE; ++i)
//		if (status[i] != DataHashConversor::HashStatus::Ok) {
//			err.pos = i;
//			err.status = status[i];
//			break;
//		}
//
//	return err;
//}

constexpr hash::HashFunctionPack pack(
	[](ll_string_t str, len_t size) -> hash::Hash64 {
		len_t buffer{};
		for (; size > ZERO_UI64; --size, ++str) buffer += *str;
		return hash::Hash64(buffer);
	},
	[](ll_wstring_t str, len_t size) -> hash::Hash64 {
		len_t buffer{};
		for (; size > ZERO_UI64; --size, ++str) buffer += *str;
		return hash::Hash64(buffer);
	},
	[](const meta::StrPair&) -> hash::Hash64 { return hash::Hash64(999); },
	[](const meta::wStrPair&) -> hash::Hash64 { return hash::Hash64(999); },

	[](const meta::Str&) -> hash::Hash64 { return hash::Hash64(999); },
	[](const meta::wStr&) -> hash::Hash64 { return hash::Hash64(999); },

	[](const hash::Hash64& h) -> hash::Hash64 { return h; },

	[](const void*, const meta::StrTypeid&) -> hash::Hash64 { return hash::Hash64(888); },
	[](const void*, const meta::wStrTypeid&) -> hash::Hash64 { return hash::Hash64(888); }
);

constexpr auto valueget() {

	hash::HashTool tool(pack);
	hash::Hash64 hashes[] = { 257ul, 1ull, 2ull, 3ull, 4ull, 5ull, 6ull, 7ull };
	//return tool.hash(hashes).get();
	//return tool.hash_hash(hashes).get();
	//return tool.hash<1>(hashes).get();
	//return tool.hash_hash<1>(hashes).get();
	//return basic_type_hash::hashValue<ui64>(hashes->get(), pack.getHashFunction()).get();
	return basic_type_hash::hashValue<ui64>(888, pack.getHashFunction()).get();
	//return hash::Hash64();
}

constexpr auto val = valueget();

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASHTOOLS_HPP_
