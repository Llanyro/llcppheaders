//////////////////////////////////////////////
//	reflection.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_REFLECTION_HPP_) // Guard && version protector
	#if LLANYLIB_REFLECTION_MAYOR_ != 7 || LLANYLIB_REFLECTION_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "reflection.hpp version error!"
		#else
			#error "reflection.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_REFLECTION_MAYOR_ || LLANYLIB_REFLECTION_MINOR_

#else !defined(LLANYLIB_REFLECTION_HPP_)
#define LLANYLIB_REFLECTION_HPP_
#define LLANYLIB_REFLECTION_MAYOR_ 7
#define LLANYLIB_REFLECTION_MINOR_ 0

#include "Typeid.hpp"
#include "ArrayView.hpp"

namespace llcpp {
namespace meta {
namespace traits {
namespace __internal__ {

template<class T>
__LL_NODISCARD__ constexpr const T* getNamePart1(const meta::ArrayView<T, LL_TRUE>& funcName) {
	using Str = meta::ArrayView<T, LL_TRUE>;
	constexpr len_t NUM_TEMPLATES_BEFORE_TYPE = 1;

	// Ignore the first template argument
	// Then when we found other template we continue processing the string to get the end of the type
	struct TempStruct { T ch; int num; using cinput = TempStruct&; };
	auto f = [](const T c, TempStruct& t) -> ll_bool_t {
		if (t.num == NUM_TEMPLATES_BEFORE_TYPE) return t.ch == c;
		else if (t.ch == c) ++t.num;
		return LL_FALSE;
	};
	TempStruct t1 = { '<', 0 };
	return funcName.find<TempStruct, LL_FALSE, TempStruct>(t1, f) + 1;
}
template<class ClassStr>
__LL_NODISCARD__ constexpr ClassStr getNamePart2(ClassStr res, ClassStr end) {
	// We try to figure out the end of the type we have
	// This checks the type start '<' and the end '>' and takes all types and templates types
	len_t found{};
	for (ClassStr i = res; i < end; ++i) {
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
__LL_NODISCARD__ constexpr const T* getNamePart3(const meta::ArrayView<T, LL_TRUE>& classString, const T* res, const T* res2) {
	meta::StringView classString = meta::make_StringView("class ");
	meta::algorithm::compare_cluster<T> cmp;
	ll_bool_t isClass = cmp.starts_with(res,
		static_cast<len_t>(res2 - res),
		classString.begin(),
		classString.size()
	);
	return isClass ? (res + classString.size()) : res;
}

} // namespace __internal__

template<class T>
__LL_NODISCARD__ constexpr meta::StrPair getName(ll_bool_t REMOVE_CLASS_STR = LL_TRUE) __LL_EXCEPT__ {
	//__FUNCSIG__;
	//__PRETTY_FUNCTION__;
	//__FUNCDNAME__;
	meta::StringView funcName = meta::make_StringView(__FUNCSIG__);
	ll_string_t res = __internal__::getNamePart1(funcName);
	ll_string_t res2 = __internal__::getNamePart2(res, funcName.end());
	if (REMOVE_CLASS_STR) {
		meta::StringView classString = meta::make_StringView("class ");
		res = __internal__::getNamePart3(classString, res, res2);
	}
	return meta::StrPair(res, res2);
}
template<class T>
__LL_NODISCARD__ constexpr meta::wStrPair getwName(ll_bool_t REMOVE_CLASS_STR = LL_TRUE) __LL_EXCEPT__ {
	meta::wStringView funcName = meta::make_StringView(L"" __FUNCSIG__);
	ll_wstring_t res = __internal__::getNamePart1(funcName);
	ll_wstring_t res2 = __internal__::getNamePart2(res, funcName.end());
	if (REMOVE_CLASS_STR) {
		meta::wStringView classString = meta::make_StringView(L"class ");
		res = __internal__::getNamePart3(classString, res, res2);
	}
	return meta::wStrPair(res, res2);
}

template<class T>
__LL_NODISCARD__ constexpr meta::StrTypeid getStrTypeId(hash::StrPairHash64Function hashFunction) __LL_EXCEPT__ {
	return meta::StrTypeid(traits::getName<T>(), hashFunction);
}
template<class T>
__LL_NODISCARD__ constexpr meta::wStrTypeid getwStrTypeid(hash::wStrPairHash64Function hashFunction) __LL_EXCEPT__ {
	return meta::wStrTypeid(traits::getwName<T>(), hashFunction);
}

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_REFLECTION_HPP_
