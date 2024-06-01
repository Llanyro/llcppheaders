//////////////////////////////////////////////
//	Typeid.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPEID_HPP_) // Guard && version protector
	#if LLANYLIB_TYPEID_MAYOR_ != 7 || LLANYLIB_TYPEID_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Typeid.hpp version error!"
		#else
			#error "Typeid.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_TYPEID_MAYOR_ || LLANYLIB_TYPEID_MINOR_

#else !defined(LLANYLIB_TYPEID_HPP_)
#define LLANYLIB_TYPEID_HPP_
#define LLANYLIB_TYPEID_MAYOR_ 7
#define LLANYLIB_TYPEID_MINOR_ 0

#include "ArrayPair.hpp"
#include "Hash64.hpp"

namespace llcpp {
namespace meta {

// Requires a char type to fit software chars: char, wchar...
template<class T>
class Typeid {
	public:
		static_assert(traits::is_char_type_v<T>, "Type must be a char type");
		using NameType = meta::ArrayPair<T>;
		using HashFunction = hash::OptionalHash64(*)(const NameType&);
		using __Typeid = traits::template_types<Typeid<T>>;
	private:
		hash::Hash64 name_hash;
		NameType name;
	private:
		constexpr void simpleClear() __LL_EXCEPT__ { this->name_hash.clear(); }
	public:
		#pragma region Contructors
		constexpr Typeid() __LL_EXCEPT__ = delete;
		constexpr ~Typeid() __LL_EXCEPT__ {}

		constexpr Typeid(const NameType& name, HashFunction hashFunction) __LL_EXCEPT__
			: name_hash(), name(name) {
			auto h = hashFunction(this->name);
			if (h.has_value()) this->name_hash = *h;
		}
		constexpr Typeid(NameType&& name, HashFunction hashFunction) __LL_EXCEPT__
			: name_hash(), name(std::move(name)) {
			auto h = hashFunction(this->name);
			if (h.has_value()) this->name_hash = *h;
		}

		constexpr Typeid(const meta::StringView& name, HashFunction hashFunction) __LL_EXCEPT__
			: name_hash(), name(name) {
			auto h = hashFunction(this->name);
			if (h.has_value()) this->name_hash = *h;
		}
		constexpr Typeid(StringView&& name, HashFunction hashFunction) __LL_EXCEPT__
			: name_hash(), name(std::move(name)) {
			auto h = hashFunction(this->name);
			if (h.has_value()) this->name_hash = *h;
		}

		#pragma endregion
		#pragma region CopyMove
		constexpr Typeid(__Typeid::cref other) __LL_EXCEPT__
			: name_hash(other.name_hash), name(other.name) {}
		constexpr __Typeid::ref operator=(__Typeid::cref other) __LL_EXCEPT__ {
			this->name_hash = other.name_hash;
			this->name = other.name;
			return *this;
		}
		constexpr Typeid(__Typeid::move other) __LL_EXCEPT__
			: name_hash(std::move(other.name_hash))
			, name(std::move(other.name))
		{ other.Typeid::simpleClear(); }
		constexpr __Typeid::ref operator=(__Typeid::move other) __LL_EXCEPT__ {
			this->name_hash = other.name_hash;
			this->name = std::move(other.name);
			other.Typeid::simpleClear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator const Typeid* () const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator Typeid* () __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr const hash::Hash64& hash() const __LL_EXCEPT__ {
			return this->name_hash;
		}
		__LL_NODISCARD__ constexpr const NameType& getName() const __LL_EXCEPT__ {
			return this->name;
		}

		#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPEID_HPP_
