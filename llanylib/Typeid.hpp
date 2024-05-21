//////////////////////////////////////////////
//	Typeid.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPEID_HPP_) // Guard && version protector
	#if LLANYLIB_TYPEID_MAYOR_ != 5 || LLANYLIB_TYPEID_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Typeid.hpp version error!"
		#else
			#error "Typeid.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_TYPEID_MAYOR_ || LLANYLIB_TYPEID_MINOR_

#else !defined(LLANYLIB_TYPEID_HPP_)
#define LLANYLIB_TYPEID_HPP_
#define LLANYLIB_TYPEID_MAYOR_ 5
#define LLANYLIB_TYPEID_MINOR_ 0

#include "StringView.hpp"
#include "CityHash.hpp"

namespace llcpp {
namespace meta {

class Typeid {
	public:
		using HashAlgorithmClass = meta::city::CityHash;
	private:
		Hash name_hash;
		StrPair name;
	private:
		constexpr void simpleClear() __LL_EXCEPT__ { this->name_hash.clear(); }
	public:
		#pragma region Contructors
		constexpr Typeid() __LL_EXCEPT__ = delete;
		constexpr ~Typeid() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr Typeid(const Typeid& other) __LL_EXCEPT__
			: name_hash(other.name_hash), name(other.name) {}
		constexpr Typeid& operator=(const Typeid& other) __LL_EXCEPT__ {
			this->name_hash = other.name_hash;
			this->name = other.name;
			return *this;
		}
		constexpr Typeid(Typeid&& other) __LL_EXCEPT__
			: name_hash(other.name_hash), name(std::move(other.name))
		{ other.Typeid::simpleClear(); }
		constexpr Typeid& operator=(Typeid&& other) __LL_EXCEPT__ {
			this->name_hash = other.name_hash;
			this->name = std::move(other.name);
			other.Typeid::simpleClear();
			return *this;
		}

		constexpr Typeid(const StrPair& name) __LL_EXCEPT__
			: name_hash(HashAlgorithmClass::cityHash64(name.data(), name.len()))
			, name(name)
		{}
		constexpr Typeid(StrPair&& name) __LL_EXCEPT__
			: name_hash(HashAlgorithmClass::cityHash64(name.data(), name.len()).value)
			, name(std::move(name))
		{}

		template<class T, len_t N>
		constexpr Typeid(const StringView<N, T>& name) __LL_EXCEPT__
			: name_hash(name.operator meta::Hash())
			, name(name)
		{}
		template<class T, len_t N>
		constexpr Typeid(StringView<N, T>&& name) __LL_EXCEPT__
			: name_hash(HashAlgorithmClass::cityHash64(name.data(), name.len()).value)
			, name(std::move(name))
		{}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator const Typeid* () const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator Typeid* () __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr const Hash& hash() const __LL_EXCEPT__ { return this->name_hash; }
		__LL_NODISCARD__ constexpr const StrPair& getName() const __LL_EXCEPT__ { return this->name; }

		template<class T>
		__LL_NODISCARD__ static constexpr StrPair get_name(ll_bool_t REMOVE_CLASS_STR = LL_TRUE) __LL_EXCEPT__ {
			//__FUNCSIG__;
			//__PRETTY_FUNCTION__;
			//__FUNCDNAME__;
			StringView funcName = make_StringView(__FUNCSIG__);
			#pragma region FirstPart
			constexpr len_t NUM_TEMPLATES_BEFORE_TYPE = 1;
			// Ignore the first template argument
			// Then when we found other template we continue processing the string to get the end of the type
			struct TempStruct { ll_char_t ch; int num; };
			decltype(funcName)::FindFunc<TempStruct&> f = [](const char c, TempStruct& t) -> ll_bool_t {
				if (t.num == NUM_TEMPLATES_BEFORE_TYPE) return t.ch == c;
				else if(t.ch == c) {
					++t.num;
					return LL_FALSE;
				}
				else return LL_FALSE;
			};
			TempStruct t1 = { '<', 0 };
			ll_string_t res = funcName.find<TempStruct, LL_FALSE, TempStruct&>(t1, f) + 1;

			#pragma endregion
			#pragma region SecodPart
			// We try to figure out the end of the type we have
			// This checks the type start '<' and the end '>' and takes all types and templates types
			ll_string_t res2 = LL_NULLPTR;
			len_t found{};
			for (ll_string_t i = res; i < funcName.end(); ++i) {
				if (*i == '<') ++found;
				else if (*i == '>') {
					if (found > 0) --found;
					else {
						res2 = i;
						break;
					}
				}
			}
			#pragma endregion
			#pragma region ThirdPard
			// We can skip the "class" word or not
			// By default "class" word is skipped
			if (REMOVE_CLASS_STR) {
				StringView classString = make_StringView("class ");
				algorithm::compare_cluster<ll_char_t> cmp;
				ll_bool_t isClass = cmp.starts_with(res,
					static_cast<len_t>(res2 - res),
					classString.begin(),
					classString.size()
				);
				res = isClass ? (res + classString.size()) : res;
			}
			#pragma endregion
			return StrPair(res, res2);
		}
		template<class T>
		__LL_NODISCARD__ static constexpr Typeid get() __LL_EXCEPT__ {
			return Typeid(Typeid::get_name<T>());
		}
		#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPEID_HPP_
