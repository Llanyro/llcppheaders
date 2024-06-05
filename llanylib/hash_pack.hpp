//////////////////////////////////////////////
//	hash_pack.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.3							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASHPACKS_HPP_) // Guard && version protector
	#if LLANYLIB_HASHPACKS_MAYOR_ != 7 || LLANYLIB_HASHPACKS_MINOR_ < 3
		#if defined(LL_REAL_CXX23)
			#warning "hash_pack.hpp version error!"
		#else
			#error "hash_pack.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASHPACKS_MAYOR_ || LLANYLIB_HASHPACKS_MINOR_

#else !defined(LLANYLIB_HASHPACKS_HPP_)
#define LLANYLIB_HASHPACKS_HPP_
#define LLANYLIB_HASHPACKS_MAYOR_ 7
#define LLANYLIB_HASHPACKS_MINOR_ 3

#include "hash_types.hpp"

#include <optional>

namespace llcpp {
namespace meta {
namespace hash {

__LL_VAR_INLINE__ constexpr hash::OptionalHash32 INVALID_HASH32 = std::nullopt;
__LL_VAR_INLINE__ constexpr hash::OptionalHash64 INVALID_HASH64 = std::nullopt;
__LL_VAR_INLINE__ constexpr hash::OptionalHash128 INVALID_HASH128 = std::nullopt;

class Hash32FunctionPack {
	private:
		hash::Hash32Function hash32Function;
		hash::wHash32Function whash32Function;
		hash::StrPairHash32Function strPairHash32Function;
		hash::wStrPairHash32Function wstrPairHash32Function;
		hash::StrHash32Function strHash32Function;
		hash::wStrHash32Function wstrHash32Function;
		hash::RecursiveHash32Function recursiveHash32Function;
		hash::StrTypeidHash32Function strTypeidHash32Function;
		hash::wStrTypeidHash32Function wstrTypeidHash32Function;
	public:
	#pragma region Functions
		#pragma region Constructors
		constexpr Hash32FunctionPack() __LL_EXCEPT__ = delete;
		constexpr Hash32FunctionPack(
			hash::Hash32Function hash32Function,
			hash::wHash32Function whash32Function,
			hash::StrPairHash32Function strPairHash32Function,
			hash::wStrPairHash32Function wstrPairHash32Function,
			hash::StrHash32Function strHash32Function,
			hash::wStrHash32Function wstrHash32Function,
			hash::RecursiveHash32Function recursiveHash32Function,
			hash::StrTypeidHash32Function strTypeidHash32Function,
			hash::wStrTypeidHash32Function wstrTypeidHash32Function
		) __LL_EXCEPT__
			: hash32Function(hash32Function)
			, whash32Function(whash32Function)
			, strPairHash32Function(strPairHash32Function)
			, wstrPairHash32Function(wstrPairHash32Function)
			, strHash32Function(strHash32Function)
			, wstrHash32Function(wstrHash32Function)
			, recursiveHash32Function(recursiveHash32Function)
			, strTypeidHash32Function(strTypeidHash32Function)
			, wstrTypeidHash32Function(wstrTypeidHash32Function)
		{}
		constexpr ~Hash32FunctionPack() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr Hash32FunctionPack(const Hash32FunctionPack& other) __LL_EXCEPT__
			: Hash32FunctionPack(
				other.hash32Function,
				other.whash32Function,
				other.strPairHash32Function,
				other.wstrPairHash32Function,
				other.strHash32Function,
				other.wstrHash32Function,
				other.recursiveHash32Function,
				other.strTypeidHash32Function,
				other.wstrTypeidHash32Function
			) {}
		constexpr Hash32FunctionPack& operator=(const Hash32FunctionPack& other) __LL_EXCEPT__ {
			this->hash32Function = other.hash32Function;
			this->whash32Function = other.whash32Function;
			this->strPairHash32Function = other.strPairHash32Function;
			this->wstrPairHash32Function = other.wstrPairHash32Function;
			this->strHash32Function = other.strHash32Function;
			this->wstrHash32Function = other.wstrHash32Function;
			this->recursiveHash32Function = other.recursiveHash32Function;
			this->strTypeidHash32Function = other.strTypeidHash32Function;
			this->wstrTypeidHash32Function = other.wstrTypeidHash32Function;
			return *this;
		}

		constexpr Hash32FunctionPack(Hash32FunctionPack&& other) __LL_EXCEPT__
			: Hash32FunctionPack(other) { other.clear(); }
		constexpr Hash32FunctionPack& operator=(Hash32FunctionPack&& other) __LL_EXCEPT__ {
			Hash32FunctionPack::operator=(other);
			other.clear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename const Hash32FunctionPack*() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename Hash32FunctionPack*() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		constexpr void clear() __LL_EXCEPT__ {
			this->hash32Function = LL_NULLPTR;
			this->whash32Function = LL_NULLPTR;
			this->strPairHash32Function = LL_NULLPTR;
			this->wstrPairHash32Function = LL_NULLPTR;
			this->strHash32Function = LL_NULLPTR;
			this->wstrHash32Function = LL_NULLPTR;
			this->recursiveHash32Function = LL_NULLPTR;
			this->strTypeidHash32Function = LL_NULLPTR;
			this->wstrTypeidHash32Function = LL_NULLPTR;
		}

		#pragma region Getters
		__LL_NODISCARD__ constexpr hash::Hash32Function getHash32Function() const __LL_EXCEPT__ { return this->hash32Function; }
		__LL_NODISCARD__ constexpr hash::wHash32Function getwHash32Function() const __LL_EXCEPT__ { return this->whash32Function; }
		__LL_NODISCARD__ constexpr hash::StrPairHash32Function getStrPairHash32Function() const __LL_EXCEPT__ { return this->strPairHash32Function; }
		__LL_NODISCARD__ constexpr hash::wStrPairHash32Function getwStrPairHash32Function() const __LL_EXCEPT__ { return this->wstrPairHash32Function; }
		__LL_NODISCARD__ constexpr hash::StrHash32Function getStrHash32Function() const __LL_EXCEPT__ { return this->strHash32Function; }
		__LL_NODISCARD__ constexpr hash::wStrHash32Function getwStrHash32Function() const __LL_EXCEPT__ { return this->wstrHash32Function; }
		__LL_NODISCARD__ constexpr hash::RecursiveHash32Function getRecursiveHash32Function() const __LL_EXCEPT__ { return this->recursiveHash32Function; }
		__LL_NODISCARD__ constexpr hash::StrTypeidHash32Function getStrTypeidHash32Function() const __LL_EXCEPT__ { return this->strTypeidHash32Function; }
		__LL_NODISCARD__ constexpr hash::wStrTypeidHash32Function getwStrTypeidHash32Function() const __LL_EXCEPT__ { return this->wstrTypeidHash32Function; }

		#pragma endregion
		#pragma region Calls
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call(ll_string_t s, const len_t n) const __LL_EXCEPT__ {
			return this->hash32Function(s, n);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call(ll_wstring_t s, const len_t n) const __LL_EXCEPT__ {
			return this->whash32Function(s, n);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call(const meta::StrPair& s) const __LL_EXCEPT__ {
			return this->strPairHash32Function(s);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call(const meta::wStrPair& s) const __LL_EXCEPT__ {
			return this->wstrPairHash32Function(s);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call(const meta::Str& s) const __LL_EXCEPT__ {
			return this->strHash32Function(s);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call(const meta::wStr& s) const __LL_EXCEPT__ {
			return this->wstrHash32Function(s);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call(const hash::Hash32& h) const __LL_EXCEPT__ {
			return this->recursiveHash32Function(h);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call(const void* o, const meta::StrTypeid& id) const __LL_EXCEPT__ {
			return this->strTypeidHash32Function(o, id);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call(const void* o, const meta::wStrTypeid& id) const __LL_EXCEPT__ {
			return this->wstrTypeidHash32Function(o, id);
		}

		#pragma endregion
		#pragma region SecureCalls
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call_s(ll_string_t s, const len_t n) const __LL_EXCEPT__ {
			return (this->hash32Function) ? this->hash32Function(s, n) : hash::INVALID_HASH32;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call_s(ll_wstring_t s, const len_t n) const __LL_EXCEPT__ {
			return (this->whash32Function) ? this->whash32Function(s, n) : hash::INVALID_HASH32;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call_s(const meta::StrPair& s) const __LL_EXCEPT__ {
			return (this->strPairHash32Function) ? this->strPairHash32Function(s) : hash::INVALID_HASH32;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call_s(const meta::wStrPair& s) const __LL_EXCEPT__ {
			return (this->wstrPairHash32Function) ? this->wstrPairHash32Function(s) : hash::INVALID_HASH32;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call_s(const meta::Str& s) const __LL_EXCEPT__ {
			return (this->strHash32Function) ? this->strHash32Function(s) : hash::INVALID_HASH32;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call_s(const meta::wStr& s) const __LL_EXCEPT__ {
			return (this->wstrHash32Function) ? this->wstrHash32Function(s) : hash::INVALID_HASH32;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call_s(const hash::Hash32& h) const __LL_EXCEPT__ {
			return (this->recursiveHash32Function) ? this->recursiveHash32Function(h) : hash::INVALID_HASH32;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call_s(const void* o, const meta::StrTypeid& id) const __LL_EXCEPT__ {
			return (this->strTypeidHash32Function) ? this->strTypeidHash32Function(o, id) : hash::INVALID_HASH32;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash32 call_s(const void* o, const meta::wStrTypeid& id) const __LL_EXCEPT__ {
			return (this->wstrTypeidHash32Function) ? this->wstrTypeidHash32Function(o, id) : hash::INVALID_HASH32;
		}

		#pragma endregion
		#pragma endregion
	#pragma endregion
};

class Hash64FunctionPack {
	private:
		hash::Hash64Function hash64Function;
		hash::wHash64Function whash64Function;
		hash::StrPairHash64Function strPairHash64Function;
		hash::wStrPairHash64Function wstrPairHash64Function;
		hash::StrHash64Function strHash64Function;
		hash::wStrHash64Function wstrHash64Function;
		hash::RecursiveHash64Function recursiveHash64Function;
		hash::StrTypeidHash64Function strTypeidHash64Function;
		hash::wStrTypeidHash64Function wstrTypeidHash64Function;
	public:
	#pragma region Functions
		#pragma region Constructors
		constexpr Hash64FunctionPack() __LL_EXCEPT__ = delete;
		constexpr Hash64FunctionPack(
			hash::Hash64Function hash64Function,
			hash::wHash64Function whash64Function,
			hash::StrPairHash64Function strPairHash64Function,
			hash::wStrPairHash64Function wstrPairHash64Function,
			hash::StrHash64Function strHash64Function,
			hash::wStrHash64Function wstrHash64Function,
			hash::RecursiveHash64Function recursiveHash64Function,
			hash::StrTypeidHash64Function strTypeidHash64Function,
			hash::wStrTypeidHash64Function wstrTypeidHash64Function
		) __LL_EXCEPT__
			: hash64Function(hash64Function)
			, whash64Function(whash64Function)
			, strPairHash64Function(strPairHash64Function)
			, wstrPairHash64Function(wstrPairHash64Function)
			, strHash64Function(strHash64Function)
			, wstrHash64Function(wstrHash64Function)
			, recursiveHash64Function(recursiveHash64Function)
			, strTypeidHash64Function(strTypeidHash64Function)
			, wstrTypeidHash64Function(wstrTypeidHash64Function)
		{}
		constexpr ~Hash64FunctionPack() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr Hash64FunctionPack(const Hash64FunctionPack& other) __LL_EXCEPT__
			: Hash64FunctionPack(
				other.hash64Function,
				other.whash64Function,
				other.strPairHash64Function,
				other.wstrPairHash64Function,
				other.strHash64Function,
				other.wstrHash64Function,
				other.recursiveHash64Function,
				other.strTypeidHash64Function,
				other.wstrTypeidHash64Function
			) {}
		constexpr Hash64FunctionPack& operator=(const Hash64FunctionPack& other) __LL_EXCEPT__ {
			this->hash64Function = other.hash64Function;
			this->whash64Function = other.whash64Function;
			this->strPairHash64Function = other.strPairHash64Function;
			this->wstrPairHash64Function = other.wstrPairHash64Function;
			this->strHash64Function = other.strHash64Function;
			this->wstrHash64Function = other.wstrHash64Function;
			this->recursiveHash64Function = other.recursiveHash64Function;
			this->strTypeidHash64Function = other.strTypeidHash64Function;
			this->wstrTypeidHash64Function = other.wstrTypeidHash64Function;
			return *this;
		}

		constexpr Hash64FunctionPack(Hash64FunctionPack&& other) __LL_EXCEPT__
			: Hash64FunctionPack(other) { other.clear(); }
		constexpr Hash64FunctionPack& operator=(Hash64FunctionPack&& other) __LL_EXCEPT__ {
			Hash64FunctionPack::operator=(other);
			other.clear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename const Hash64FunctionPack*() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename Hash64FunctionPack*() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		constexpr void clear() __LL_EXCEPT__ {
			this->hash64Function = LL_NULLPTR;
			this->whash64Function = LL_NULLPTR;
			this->strPairHash64Function = LL_NULLPTR;
			this->wstrPairHash64Function = LL_NULLPTR;
			this->strHash64Function = LL_NULLPTR;
			this->wstrHash64Function = LL_NULLPTR;
			this->recursiveHash64Function = LL_NULLPTR;
			this->strTypeidHash64Function = LL_NULLPTR;
			this->wstrTypeidHash64Function = LL_NULLPTR;
		}

		#pragma region Getters
		__LL_NODISCARD__ constexpr hash::Hash64Function getHash64Function() const __LL_EXCEPT__ { return this->hash64Function; }
		__LL_NODISCARD__ constexpr hash::wHash64Function getwHash64Function() const __LL_EXCEPT__ { return this->whash64Function; }
		__LL_NODISCARD__ constexpr hash::StrPairHash64Function getStrPairHash64Function() const __LL_EXCEPT__ { return this->strPairHash64Function; }
		__LL_NODISCARD__ constexpr hash::wStrPairHash64Function getwStrPairHash64Function() const __LL_EXCEPT__ { return this->wstrPairHash64Function; }
		__LL_NODISCARD__ constexpr hash::StrHash64Function getStrHash64Function() const __LL_EXCEPT__ { return this->strHash64Function; }
		__LL_NODISCARD__ constexpr hash::wStrHash64Function getwStrHash64Function() const __LL_EXCEPT__ { return this->wstrHash64Function; }
		__LL_NODISCARD__ constexpr hash::RecursiveHash64Function getRecursiveHash64Function() const __LL_EXCEPT__ { return this->recursiveHash64Function; }
		__LL_NODISCARD__ constexpr hash::StrTypeidHash64Function getStrTypeidHash64Function() const __LL_EXCEPT__ { return this->strTypeidHash64Function; }
		__LL_NODISCARD__ constexpr hash::wStrTypeidHash64Function getwStrTypeidHash64Function() const __LL_EXCEPT__ { return this->wstrTypeidHash64Function; }

		#pragma endregion
		#pragma region Calls
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call(ll_string_t s, const len_t n) const __LL_EXCEPT__ {
			return this->hash64Function(s, n);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call(ll_wstring_t s, const len_t n) const __LL_EXCEPT__ {
			return this->whash64Function(s, n);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call(const meta::StrPair& s) const __LL_EXCEPT__ {
			return this->strPairHash64Function(s);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call(const meta::wStrPair& s) const __LL_EXCEPT__ {
			return this->wstrPairHash64Function(s);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call(const meta::Str& s) const __LL_EXCEPT__ {
			return this->strHash64Function(s);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call(const meta::wStr& s) const __LL_EXCEPT__ {
			return this->wstrHash64Function(s);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call(const hash::Hash64& h) const __LL_EXCEPT__ {
			return this->recursiveHash64Function(h);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call(const void* o, const meta::StrTypeid& id) const __LL_EXCEPT__ {
			return this->strTypeidHash64Function(o, id);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call(const void* o, const meta::wStrTypeid& id) const __LL_EXCEPT__ {
			return this->wstrTypeidHash64Function(o, id);
		}

		#pragma endregion
		#pragma region SecureCalls
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(ll_string_t s, const len_t n) const __LL_EXCEPT__ {
			return (this->hash64Function) ? this->hash64Function(s, n) : hash::INVALID_HASH64;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(ll_wstring_t s, const len_t n) const __LL_EXCEPT__ {
			return (this->whash64Function) ? this->whash64Function(s, n) : hash::INVALID_HASH64;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const meta::StrPair& s) const __LL_EXCEPT__ {
			return (this->strPairHash64Function) ? this->strPairHash64Function(s) : hash::INVALID_HASH64;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const meta::wStrPair& s) const __LL_EXCEPT__ {
			return (this->wstrPairHash64Function) ? this->wstrPairHash64Function(s) : hash::INVALID_HASH64;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const meta::Str& s) const __LL_EXCEPT__ {
			return (this->strHash64Function) ? this->strHash64Function(s) : hash::INVALID_HASH64;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const meta::wStr& s) const __LL_EXCEPT__ {
			return (this->wstrHash64Function) ? this->wstrHash64Function(s) : hash::INVALID_HASH64;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const hash::Hash64& h) const __LL_EXCEPT__ {
			return (this->recursiveHash64Function) ? this->recursiveHash64Function(h) : hash::INVALID_HASH64;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const void* o, const meta::StrTypeid& id) const __LL_EXCEPT__ {
			return (this->strTypeidHash64Function) ? this->strTypeidHash64Function(o, id) : hash::INVALID_HASH64;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const void* o, const meta::wStrTypeid& id) const __LL_EXCEPT__ {
			return (this->wstrTypeidHash64Function) ? this->wstrTypeidHash64Function(o, id) : hash::INVALID_HASH64;
		}

		#pragma endregion
		#pragma endregion
	#pragma endregion
};

class Hash128FunctionPack {
	private:
		hash::Hash128Function hash128Function;
		hash::wHash128Function whash128Function;
		hash::StrPairHash128Function strPairHash128Function;
		hash::wStrPairHash128Function wstrPairHash128Function;
		hash::StrHash128Function strHash128Function;
		hash::wStrHash128Function wstrHash128Function;
		hash::RecursiveHash128Function recursiveHash128Function;
		hash::StrTypeidHash128Function strTypeidHash128Function;
		hash::wStrTypeidHash128Function wstrTypeidHash128Function;
	public:
	#pragma region Functions
		#pragma region Constructors
		constexpr Hash128FunctionPack() __LL_EXCEPT__ = delete;
		constexpr Hash128FunctionPack(
			hash::Hash128Function hash128Function,
			hash::wHash128Function whash128Function,
			hash::StrPairHash128Function strPairHash128Function,
			hash::wStrPairHash128Function wstrPairHash128Function,
			hash::StrHash128Function strHash128Function,
			hash::wStrHash128Function wstrHash128Function,
			hash::RecursiveHash128Function recursiveHash128Function,
			hash::StrTypeidHash128Function strTypeidHash128Function,
			hash::wStrTypeidHash128Function wstrTypeidHash128Function
		) __LL_EXCEPT__
			: hash128Function(hash128Function)
			, whash128Function(whash128Function)
			, strPairHash128Function(strPairHash128Function)
			, wstrPairHash128Function(wstrPairHash128Function)
			, strHash128Function(strHash128Function)
			, wstrHash128Function(wstrHash128Function)
			, recursiveHash128Function(recursiveHash128Function)
			, strTypeidHash128Function(strTypeidHash128Function)
			, wstrTypeidHash128Function(wstrTypeidHash128Function)
		{}
		constexpr ~Hash128FunctionPack() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr Hash128FunctionPack(const Hash128FunctionPack& other) __LL_EXCEPT__
			: Hash128FunctionPack(
				other.hash128Function,
				other.whash128Function,
				other.strPairHash128Function,
				other.wstrPairHash128Function,
				other.strHash128Function,
				other.wstrHash128Function,
				other.recursiveHash128Function,
				other.strTypeidHash128Function,
				other.wstrTypeidHash128Function
			) {}
		constexpr Hash128FunctionPack& operator=(const Hash128FunctionPack& other) __LL_EXCEPT__ {
			this->hash128Function = other.hash128Function;
			this->whash128Function = other.whash128Function;
			this->strPairHash128Function = other.strPairHash128Function;
			this->wstrPairHash128Function = other.wstrPairHash128Function;
			this->strHash128Function = other.strHash128Function;
			this->wstrHash128Function = other.wstrHash128Function;
			this->recursiveHash128Function = other.recursiveHash128Function;
			this->strTypeidHash128Function = other.strTypeidHash128Function;
			this->wstrTypeidHash128Function = other.wstrTypeidHash128Function;
			return *this;
		}

		constexpr Hash128FunctionPack(Hash128FunctionPack&& other) __LL_EXCEPT__
			: Hash128FunctionPack(other) { other.clear(); }
		constexpr Hash128FunctionPack& operator=(Hash128FunctionPack&& other) __LL_EXCEPT__ {
			Hash128FunctionPack::operator=(other);
			other.clear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename const Hash128FunctionPack*() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename Hash128FunctionPack*() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		constexpr void clear() __LL_EXCEPT__ {
			this->hash128Function = LL_NULLPTR;
			this->whash128Function = LL_NULLPTR;
			this->strPairHash128Function = LL_NULLPTR;
			this->wstrPairHash128Function = LL_NULLPTR;
			this->strHash128Function = LL_NULLPTR;
			this->wstrHash128Function = LL_NULLPTR;
			this->recursiveHash128Function = LL_NULLPTR;
			this->strTypeidHash128Function = LL_NULLPTR;
			this->wstrTypeidHash128Function = LL_NULLPTR;
		}

		#pragma region Getters
		__LL_NODISCARD__ constexpr hash::Hash128Function getHash128Function() const __LL_EXCEPT__ { return this->hash128Function; }
		__LL_NODISCARD__ constexpr hash::wHash128Function getwHash128Function() const __LL_EXCEPT__ { return this->whash128Function; }
		__LL_NODISCARD__ constexpr hash::StrPairHash128Function getStrPairHash128Function() const __LL_EXCEPT__ { return this->strPairHash128Function; }
		__LL_NODISCARD__ constexpr hash::wStrPairHash128Function getwStrPairHash128Function() const __LL_EXCEPT__ { return this->wstrPairHash128Function; }
		__LL_NODISCARD__ constexpr hash::StrHash128Function getStrHash128Function() const __LL_EXCEPT__ { return this->strHash128Function; }
		__LL_NODISCARD__ constexpr hash::wStrHash128Function getwStrHash128Function() const __LL_EXCEPT__ { return this->wstrHash128Function; }
		__LL_NODISCARD__ constexpr hash::RecursiveHash128Function getRecursiveHash128Function() const __LL_EXCEPT__ { return this->recursiveHash128Function; }
		__LL_NODISCARD__ constexpr hash::StrTypeidHash128Function getStrTypeidHash128Function() const __LL_EXCEPT__ { return this->strTypeidHash128Function; }
		__LL_NODISCARD__ constexpr hash::wStrTypeidHash128Function getwStrTypeidHash128Function() const __LL_EXCEPT__ { return this->wstrTypeidHash128Function; }

		#pragma endregion
		#pragma region Calls
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call(ll_string_t s, const len_t n) const __LL_EXCEPT__ {
			return this->hash128Function(s, n);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call(ll_wstring_t s, const len_t n) const __LL_EXCEPT__ {
			return this->whash128Function(s, n);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call(const meta::StrPair& s) const __LL_EXCEPT__ {
			return this->strPairHash128Function(s);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call(const meta::wStrPair& s) const __LL_EXCEPT__ {
			return this->wstrPairHash128Function(s);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call(const meta::Str& s) const __LL_EXCEPT__ {
			return this->strHash128Function(s);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call(const meta::wStr& s) const __LL_EXCEPT__ {
			return this->wstrHash128Function(s);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call(const hash::Hash128& h) const __LL_EXCEPT__ {
			return this->recursiveHash128Function(h);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call(const void* o, const meta::StrTypeid& id) const __LL_EXCEPT__ {
			return this->strTypeidHash128Function(o, id);
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call(const void* o, const meta::wStrTypeid& id) const __LL_EXCEPT__ {
			return this->wstrTypeidHash128Function(o, id);
		}

		#pragma endregion
		#pragma region SecureCalls
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call_s(ll_string_t s, const len_t n) const __LL_EXCEPT__ {
			return (this->hash128Function) ? this->hash128Function(s, n) : hash::INVALID_HASH128;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call_s(ll_wstring_t s, const len_t n) const __LL_EXCEPT__ {
			return (this->whash128Function) ? this->whash128Function(s, n) : hash::INVALID_HASH128;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call_s(const meta::StrPair& s) const __LL_EXCEPT__ {
			return (this->strPairHash128Function) ? this->strPairHash128Function(s) : hash::INVALID_HASH128;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call_s(const meta::wStrPair& s) const __LL_EXCEPT__ {
			return (this->wstrPairHash128Function) ? this->wstrPairHash128Function(s) : hash::INVALID_HASH128;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call_s(const meta::Str& s) const __LL_EXCEPT__ {
			return (this->strHash128Function) ? this->strHash128Function(s) : hash::INVALID_HASH128;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call_s(const meta::wStr& s) const __LL_EXCEPT__ {
			return (this->wstrHash128Function) ? this->wstrHash128Function(s) : hash::INVALID_HASH128;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call_s(const hash::Hash128& h) const __LL_EXCEPT__ {
			return (this->recursiveHash128Function) ? this->recursiveHash128Function(h) : hash::INVALID_HASH128;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call_s(const void* o, const meta::StrTypeid& id) const __LL_EXCEPT__ {
			return (this->strTypeidHash128Function) ? this->strTypeidHash128Function(o, id) : hash::INVALID_HASH128;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash128 call_s(const void* o, const meta::wStrTypeid& id) const __LL_EXCEPT__ {
			return (this->wstrTypeidHash128Function) ? this->wstrTypeidHash128Function(o, id) : hash::INVALID_HASH128;
		}

		#pragma endregion
		#pragma endregion
	#pragma endregion
};

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASHPACKS_HPP_
