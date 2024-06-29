//////////////////////////////////////////////
//	reflection.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_REFLECTION_HPP_) // Guard && version protector
	#if LLANYLIB_REFLECTION_MAYOR_ != 8 || LLANYLIB_REFLECTION_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "reflection.hpp version error!"
		#else
			#error "reflection.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_REFLECTION_MAYOR_ || LLANYLIB_REFLECTION_MINOR_

#else !defined(LLANYLIB_REFLECTION_HPP_)
#define LLANYLIB_REFLECTION_HPP_
#define LLANYLIB_REFLECTION_MAYOR_ 8
#define LLANYLIB_REFLECTION_MINOR_ 0

#include "Typeid.hpp"

#include "algorithm.hpp"

#include <string_view>

namespace llcpp {
namespace meta {
namespace traits {
namespace __internal__ {

template<class T>
__LL_NODISCARD__ constexpr const T* getNamePart1(const std::basic_string_view<T, std::char_traits<T>>& funcName) noexcept {
	constexpr len_t NUM_TEMPLATES_BEFORE_TYPE = 1ull;

	// Ignore the first template argument
	// Then when we found other template we continue processing the string to get the end of the type
	struct TempStruct {
		T ch; int num; using cinput = TempStruct&;
		__LL_NODISCARD__ static constexpr ll_bool_t compareBool(const T c, TempStruct& t) noexcept {
			if (t.num == NUM_TEMPLATES_BEFORE_TYPE) return t.ch == c;
			else if (t.ch == c) ++t.num;
			return LL_FALSE;
		}
		__LL_NODISCARD__ static constexpr cmp_t compare(const T c, TempStruct& t) noexcept {
			return c == t.ch;
		}
	};

	TempStruct t1 = { '<', 0 };
	return algorithm::finders_cluster<T, TempStruct&, TempStruct, LL_FALSE>().find(
		funcName.data(), funcName._Unchecked_end(), t1) + 1;
}
template<class T>
__LL_NODISCARD__ constexpr const T* getNamePart2(const T* res, const T* end) noexcept {
	// We try to figure out the end of the type we have
	// This checks the type start '<' and the end '>' and takes all types and templates types
	len_t found{};
	for (const T* i = res; i < end; ++i) {
		if (*i == '<') ++found;
		else if (*i == '>') {
			if (found > 0) --found;
			else
				return i;
		}
	}
	return LL_NULLPTR;
}
template<class T>
__LL_NODISCARD__ constexpr const T* getNamePart3(const std::basic_string_view<T, std::char_traits<T>>& class_string, const T* res, const T* res2) noexcept {
	struct TempStruct {
		__LL_NODISCARD__ static constexpr ll_bool_t compareBool(const T c, const T d) noexcept {
			return c == d;
		}
	};

	ll_bool_t isClass = algorithm::compare_cluster<T, TempStruct, T, LL_FALSE>::starts_with(
		res,
		static_cast<len_t>(res2 - res),
		class_string.data(),
		class_string.size()
	);
	return isClass ? (res + class_string.size()) : res;
}

} // namespace __internal__

template<class T>
__LL_NODISCARD__ constexpr meta::StrPair getName(ll_bool_t REMOVE_CLASS_STR = LL_TRUE) noexcept {
	//__FUNCSIG__;
	//__PRETTY_FUNCTION__;
	//__FUNCDNAME__;
	std::string_view funcName = __FUNCSIG__;
	ll_string_t res = __internal__::getNamePart1<ll_char_t>(funcName);
	ll_string_t res2 = __internal__::getNamePart2<ll_char_t>(res, funcName._Unchecked_end());
	if (REMOVE_CLASS_STR) {
		std::string_view class_string = "class ";
		//res = __internal__::getNamePart3(class_string, res, res2);
	}
	return meta::StrPair(res, res2);
}
template<class T>
__LL_NODISCARD__ constexpr meta::wStrPair getwName(ll_bool_t REMOVE_CLASS_STR = LL_TRUE) noexcept {
	std::wstring_view funcName = L"" __FUNCSIG__;
	ll_wstring_t res = __internal__::getNamePart1<ll_wchar_t>(funcName);
	ll_wstring_t res2 = __internal__::getNamePart2<ll_wchar_t>(res, funcName._Unchecked_end());
	if (REMOVE_CLASS_STR) {
		std::wstring_view class_string = L"class ";
		res = __internal__::getNamePart3(class_string, res, res2);
	}
	return meta::wStrPair(res, res2);
}

template<class T>
__LL_NODISCARD__ constexpr meta::StrTypeid getStrTypeId(hash::StrPairHash64Function hashFunction) noexcept {
	return meta::StrTypeid(traits::getName<T>(), hashFunction);
}
template<class T>
__LL_NODISCARD__ constexpr meta::wStrTypeid getwStrTypeid(hash::wStrPairHash64Function hashFunction) noexcept {
	return meta::wStrTypeid(traits::getwName<T>(), hashFunction);
}

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_REFLECTION_HPP_
