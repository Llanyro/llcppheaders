//////////////////////////////////////////////
//	hash.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 6.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASH_HPP_) // Guard && version protector
	#if LLANYLIB_HASH_MAYOR_ != 6 || LLANYLIB_HASH_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "hash.hpp version error!"
		#else
			#error "hash.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASH_MAYOR_ || LLANYLIB_HASH_MINOR_

#else !defined(LLANYLIB_HASH_HPP_)
#define LLANYLIB_HASH_HPP_
#define LLANYLIB_HASH_MAYOR_ 6
#define LLANYLIB_HASH_MINOR_ 0

#include "Hash64.hpp"

namespace llcpp {
namespace meta {
namespace hash {

class HashFunctionPack {
	private:
		hash::HashFunction hashFunction;
		hash::wHashFunction whashFunction;

		hash::StrPairHashFunction strPairHashFunction;
		hash::wStrPairHashFunction wstrPairHashFunction;

		hash::StrHashFunction strHashFunction;
		hash::wStrHashFunction wstrHashFunction;

		hash::HashRecursiveFunction hashRecursiveFunction;

		hash::HashStrTypeidFunction hashStrTypeidFunction;
		hash::HashwStrTypeidFunction hashwStrTypeidFunction;
	public:
	#pragma region Functions
		#pragma region Constructors
		constexpr HashFunctionPack() __LL_EXCEPT__ = delete;
		constexpr HashFunctionPack(
			hash::HashFunction hashFunction,
			hash::wHashFunction whashFunction,

			hash::StrPairHashFunction strPairHashFunction,
			hash::wStrPairHashFunction wstrPairHashFunction,

			hash::StrHashFunction strHashFunction,
			hash::wStrHashFunction wstrHashFunction,

			hash::HashRecursiveFunction hashRecursiveFunction,

			hash::HashStrTypeidFunction hashStrTypeidFunction,
			hash::HashwStrTypeidFunction hashwStrTypeidFunction
		) __LL_EXCEPT__
			: hashFunction(hashFunction)
			, whashFunction(whashFunction)

			, strPairHashFunction(strPairHashFunction)
			, wstrPairHashFunction(wstrPairHashFunction)

			, strHashFunction(strHashFunction)
			, wstrHashFunction(wstrHashFunction)

			, hashRecursiveFunction(hashRecursiveFunction)

			, hashStrTypeidFunction(hashStrTypeidFunction)
			, hashwStrTypeidFunction(hashwStrTypeidFunction)
		{}
		constexpr ~HashFunctionPack() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr HashFunctionPack(const HashFunctionPack& other) __LL_EXCEPT__
			: HashFunctionPack(
				other.hashFunction,
				other.whashFunction,

				other.strPairHashFunction,
				other.wstrPairHashFunction,

				other.strHashFunction,
				other.wstrHashFunction,

				other.hashRecursiveFunction,

				other.hashStrTypeidFunction,
				other.hashwStrTypeidFunction
			) {}
		constexpr HashFunctionPack& operator=(const HashFunctionPack& other) __LL_EXCEPT__ {
			this->hashFunction = other.hashFunction;
			this->whashFunction = other.whashFunction;

			this->strPairHashFunction = other.strPairHashFunction;
			this->wstrPairHashFunction = other.wstrPairHashFunction;

			this->strHashFunction = other.strHashFunction;
			this->wstrHashFunction = other.wstrHashFunction;
			
			this->hashRecursiveFunction = other.hashRecursiveFunction;

			this->hashStrTypeidFunction = other.hashStrTypeidFunction;
			this->hashwStrTypeidFunction = other.hashwStrTypeidFunction;
			return *this;
		}

		constexpr HashFunctionPack(HashFunctionPack&& other) __LL_EXCEPT__
			: HashFunctionPack(other)
		{ other.clear(); }
		constexpr HashFunctionPack& operator=(HashFunctionPack&& other) __LL_EXCEPT__ {
			HashFunctionPack::operator=(other);
			other.clear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename const HashFunctionPack*() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename HashFunctionPack*() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		constexpr void clear() __LL_EXCEPT__ {
			this->hashFunction = LL_NULLPTR;
			this->whashFunction = LL_NULLPTR;

			this->strPairHashFunction = LL_NULLPTR;
			this->wstrPairHashFunction = LL_NULLPTR;

			this->strHashFunction = LL_NULLPTR;
			this->wstrHashFunction = LL_NULLPTR;

			this->hashRecursiveFunction = LL_NULLPTR;

			this->hashStrTypeidFunction = LL_NULLPTR;
			this->hashwStrTypeidFunction = LL_NULLPTR;
		}

		#pragma region Getters
		__LL_NODISCARD__ constexpr hash::HashFunction getHashFunction() const __LL_EXCEPT__ { return this->hashFunction; }
		__LL_NODISCARD__ constexpr hash::wHashFunction getwHashFunction() const __LL_EXCEPT__ { return this->whashFunction; }

		__LL_NODISCARD__ constexpr hash::StrPairHashFunction getStrPairHashFunction() const __LL_EXCEPT__ { return this->strPairHashFunction; }
		__LL_NODISCARD__ constexpr hash::wStrPairHashFunction getwStrPairHashFunction() const __LL_EXCEPT__ { return this->wstrPairHashFunction; }

		__LL_NODISCARD__ constexpr hash::StrHashFunction getStrHashFunction() const __LL_EXCEPT__ { return this->strHashFunction; }
		__LL_NODISCARD__ constexpr hash::wStrHashFunction getwStrHashFunction() const __LL_EXCEPT__ { return this->wstrHashFunction; }

		__LL_NODISCARD__ constexpr hash::HashRecursiveFunction getHashRecursiveFunction() const __LL_EXCEPT__ { return this->hashRecursiveFunction; }

		__LL_NODISCARD__ constexpr hash::HashStrTypeidFunction getHashStrTypeidFunction() const __LL_EXCEPT__ { return this->hashStrTypeidFunction; }
		__LL_NODISCARD__ constexpr hash::HashwStrTypeidFunction getHashwStrTypeidFunction() const __LL_EXCEPT__ { return this->hashwStrTypeidFunction; }

		#pragma endregion
		#pragma region Calls
		__LL_NODISCARD__ constexpr hash::Hash64 call(ll_string_t s, const len_t n) const __LL_EXCEPT__ {
			return this->hashFunction(s, n);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 call(ll_wstring_t s, const len_t n) const __LL_EXCEPT__ {
			return this->whashFunction(s, n);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 call(const meta::StrPair& s) const __LL_EXCEPT__ {
			return this->strPairHashFunction(s);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 call(const meta::wStrPair& s) const __LL_EXCEPT__ {
			return this->wstrPairHashFunction(s);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 call(const meta::Str& s) const __LL_EXCEPT__ {
			return this->strHashFunction(s);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 call(const meta::wStr& s) const __LL_EXCEPT__ {
			return this->wstrHashFunction(s);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 call(const hash::Hash64& h) const __LL_EXCEPT__ {
			return this->hashRecursiveFunction(h);
		}

		__LL_NODISCARD__ constexpr hash::Hash64 call(const void* o, const meta::StrTypeid& id) const __LL_EXCEPT__ {
			return this->hashStrTypeidFunction(o, id);
		}
		__LL_NODISCARD__ constexpr hash::Hash64 call(const void* o, const meta::wStrTypeid& id) const __LL_EXCEPT__ {
			return this->hashwStrTypeidFunction(o, id);
		}

		#pragma endregion
		#pragma region SecureCalls
		__LL_NODISCARD__ constexpr hash::Hash64 call_s(ll_string_t s, const len_t n) const __LL_EXCEPT__ {
			return (this->hashFunction) ? this->hashFunction(s, n) : hash::Hash64();
		}
		__LL_NODISCARD__ constexpr hash::Hash64 call_s(ll_wstring_t s, const len_t n) const __LL_EXCEPT__ {
			return (this->whashFunction) ? this->whashFunction(s, n) : hash::Hash64();
		}

		__LL_NODISCARD__ constexpr hash::Hash64 call_s(const meta::StrPair& s) const __LL_EXCEPT__ {
			return (this->strPairHashFunction) ? this->strPairHashFunction(s) : hash::Hash64();
		}
		__LL_NODISCARD__ constexpr hash::Hash64 call_s(const meta::wStrPair& s) const __LL_EXCEPT__ {
			return (this->wstrPairHashFunction) ? this->wstrPairHashFunction(s) : hash::Hash64();
		}

		__LL_NODISCARD__ constexpr hash::Hash64 call_s(const meta::Str& s) const __LL_EXCEPT__ {
			return (this->strHashFunction) ? this->strHashFunction(s) : hash::Hash64();
		}
		__LL_NODISCARD__ constexpr hash::Hash64 call_s(const meta::wStr& s) const __LL_EXCEPT__ {
			return (this->wstrHashFunction) ? this->wstrHashFunction(s) : hash::Hash64();
		}

		__LL_NODISCARD__ constexpr hash::Hash64 call_s(const hash::Hash64& h) const __LL_EXCEPT__ {
			return (this->hashRecursiveFunction) ? this->hashRecursiveFunction(h) : hash::Hash64();
		}

		__LL_NODISCARD__ constexpr hash::Hash64 call_s(const void* o, const meta::StrTypeid& id) const __LL_EXCEPT__ {
			return (this->hashStrTypeidFunction) ? this->hashStrTypeidFunction(o, id) : hash::Hash64();
		}
		__LL_NODISCARD__ constexpr hash::Hash64 call_s(const void* o, const meta::wStrTypeid& id) const __LL_EXCEPT__ {
			return (this->hashwStrTypeidFunction) ? this->hashwStrTypeidFunction(o, id) : hash::Hash64();
		}

		#pragma endregion
		#pragma endregion
	#pragma endregion
};

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASH_HPP_
