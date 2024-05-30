//////////////////////////////////////////////
//	hash.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_HASH_HPP_) // Guard && version protector
	#if LLANYLIB_HASH_MAYOR_ != 7 || LLANYLIB_HASH_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "hash.hpp version error!"
		#else
			#error "hash.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_HASH_MAYOR_ || LLANYLIB_HASH_MINOR_

#else !defined(LLANYLIB_HASH_HPP_)
#define LLANYLIB_HASH_HPP_
#define LLANYLIB_HASH_MAYOR_ 7
#define LLANYLIB_HASH_MINOR_ 0

#include "Hash64.hpp"

#include <optional>

namespace llcpp {
namespace meta {
namespace hash {

inline constexpr hash::OptionalHash64 INVALID_HASH = std::nullopt;

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
			return (this->hash64Function) ? this->hash64Function(s, n) : hash::INVALID_HASH;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(ll_wstring_t s, const len_t n) const __LL_EXCEPT__ {
			return (this->whash64Function) ? this->whash64Function(s, n) : hash::INVALID_HASH;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const meta::StrPair& s) const __LL_EXCEPT__ {
			return (this->strPairHash64Function) ? this->strPairHash64Function(s) : hash::INVALID_HASH;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const meta::wStrPair& s) const __LL_EXCEPT__ {
			return (this->wstrPairHash64Function) ? this->wstrPairHash64Function(s) : hash::INVALID_HASH;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const meta::Str& s) const __LL_EXCEPT__ {
			return (this->strHash64Function) ? this->strHash64Function(s) : hash::INVALID_HASH;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const meta::wStr& s) const __LL_EXCEPT__ {
			return (this->wstrHash64Function) ? this->wstrHash64Function(s) : hash::INVALID_HASH;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const hash::Hash64& h) const __LL_EXCEPT__ {
			return (this->recursiveHash64Function) ? this->recursiveHash64Function(h) : hash::INVALID_HASH;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const void* o, const meta::StrTypeid& id) const __LL_EXCEPT__ {
			return (this->strTypeidHash64Function) ? this->strTypeidHash64Function(o, id) : hash::INVALID_HASH;
		}
		__LL_NODISCARD__ constexpr hash::OptionalHash64 call_s(const void* o, const meta::wStrTypeid& id) const __LL_EXCEPT__ {
			return (this->wstrTypeidHash64Function) ? this->wstrTypeidHash64Function(o, id) : hash::INVALID_HASH;
		}

		#pragma endregion
		#pragma endregion
	#pragma endregion
};

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASH_HPP_
