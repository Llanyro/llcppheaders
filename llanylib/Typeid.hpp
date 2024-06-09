//////////////////////////////////////////////
//	Typeid.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPEID_HPP_) // Guard && version protector
	#if LLANYLIB_TYPEID_MAYOR_ != 8 || LLANYLIB_TYPEID_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Typeid.hpp version error!"
		#else
			#error "Typeid.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_TYPEID_MAYOR_ || LLANYLIB_TYPEID_MINOR_

#else !defined(LLANYLIB_TYPEID_HPP_)
#define LLANYLIB_TYPEID_HPP_
#define LLANYLIB_TYPEID_MAYOR_ 8
#define LLANYLIB_TYPEID_MINOR_ 0

#include "ArrayPair.hpp"
#include "hash_types.hpp"

namespace llcpp {
namespace meta {

// Requires a char type to fit software chars: char, wchar...
template<class T>
class Typeid {
	public:
		static_assert(traits::is_char_type_v<T>, "Type must be a char type");
		using NameType = meta::ArrayPair<T>;
		using HashFunction = hash::OptionalHash64(*)(const NameType&) noexcept;
	private:
		hash::Hash64 name_hash;
		NameType name;
	private:
		constexpr void simpleClear() noexcept { this->name_hash.clear(); }
	public:
		#pragma region Contructors
		constexpr Typeid() noexcept = delete;
		constexpr ~Typeid() noexcept {}

		constexpr Typeid(const NameType& name, HashFunction hashFunction) noexcept
			: name_hash(), name(name) {
			auto h = hashFunction(this->name);
			if (h.has_value()) this->name_hash = *h;
		}
		constexpr Typeid(NameType&& name, HashFunction hashFunction) noexcept
			: name_hash(), name(std::move(name)) {
			auto h = hashFunction(this->name);
			if (h.has_value()) this->name_hash = *h;
		}

		#pragma endregion
		#pragma region CopyMove
		constexpr Typeid(const Typeid& other) noexcept
			: name_hash(other.name_hash), name(other.name) {}
		constexpr Typeid& operator=(const Typeid& other) noexcept {
			this->name_hash = other.name_hash;
			this->name = other.name;
			return *this;
		}
		constexpr Typeid(Typeid&& other) noexcept
			: name_hash(std::move(other.name_hash))
			, name(std::move(other.name))
		{ other.simpleClear(); }
		constexpr Typeid& operator=(Typeid&& other) noexcept {
			this->name_hash = other.name_hash;
			this->name = std::move(other.name);
			other.simpleClear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator const Typeid*() const noexcept = delete;
		__LL_NODISCARD__ constexpr operator Typeid*() noexcept = delete;

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr const hash::Hash64& hash() const noexcept {
			return this->name_hash;
		}
		__LL_NODISCARD__ constexpr const NameType& getName() const noexcept {
			return this->name;
		}

		#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPEID_HPP_
