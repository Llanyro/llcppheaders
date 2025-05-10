//////////////////////////////////////////////
//	reflection.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_REFLECTION_INCOMPLETE_HPP_)
	#if LLANYLIB_REFLECTION_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_REFLECTION_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "reflection.hpp(incomplete) version error!"
		#else
			#error "reflection.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_REFLECTION_INCOMPLETE_MAYOR_ || LLANYLIB_REFLECTION_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_REFLECTION_INCOMPLETE_HPP_)
	#define LLANYLIB_REFLECTION_INCOMPLETE_HPP_
	#define LLANYLIB_REFLECTION_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_REFLECTION_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_REFLECTION_HPP_)
	#if LLANYLIB_REFLECTION_MAYOR_ != 12 || LLANYLIB_REFLECTION_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "reflection.hpp version error!"
		#else
			#error "reflection.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_REFLECTION_MAYOR_ || LLANYLIB_REFLECTION_MINOR_

#else
	#define LLANYLIB_REFLECTION_HPP_
	#define LLANYLIB_REFLECTION_MAYOR_ 12
	#define LLANYLIB_REFLECTION_MINOR_ 0

#include "ArrayBase.hpp"
#include "IteratorUtils.hpp"

namespace llcpp {
namespace meta {
namespace utils {

template<class T, class CharType = ::llcpp::char_type>
__LL_NODISCARD__ constexpr ::llcpp::meta::utils::ConstArray<CharType> getName(ll_bool_t REMOVE_CLASS_STR = ::llcpp::LL_TRUE) noexcept {
	::llcpp::meta::utils::ConstArray<CharType> type;
	if constexpr (::std::is_same_v<CharType, ll_char_t>) {
		constexpr ll_char_t name[] = __LL_FUNCNAME__;
		type.resetValidation(name, name + sizeof(name) - 1);	// Ignore '\0'
	}
	else if constexpr (::std::is_same_v<CharType, ll_wchar_t>) {
		constexpr ll_wchar_t name[] = __LL_L __LL_FUNCNAME__;
		type.resetValidation(name, name + sizeof(name) - 1);	// Ignore '\0'
	}
	else if constexpr (::std::is_same_v<CharType, ::std::char16_t>) {
		constexpr ll_wchar_t name[] = __LL_L __LL_FUNCNAME__;
		type.resetValidation(name, name + sizeof(name) - 1);	// Ignore '\0'
	}
	else {
		static_assert(::std::is_same_v<CharType, ll_wchar_t>
			"This function can only use char and wchar. If you want to include other types add a new issue.");
		return type;
	}



	::llcpp::meta::utils::IteratorUtils<CharType*>;



	//__FUNCSIG__;
	//__PRETTY_FUNCTION__;
	//__FUNCDNAME__;
	//std::string_view funcName = __FUNCSIG__;
	//ll_string_t res = __internal__::getNamePart1<ll_char_t>(funcName);
	//ll_string_t res2 = __internal__::getNamePart2<ll_char_t>(res, funcName._Unchecked_end());
	//if (REMOVE_CLASS_STR) {
	//	std::string_view class_string = "class ";
	//	//res = __internal__::getNamePart3(class_string, res, res2);
	//}
	//return meta::StrPair(res, res2);
}

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_REFLECTION_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_REFLECTION_EXTRA_HPP_)
		#if LLANYLIB_REFLECTION_EXTRA_MAYOR_ != 12 || LLANYLIB_REFLECTION_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "reflection.hpp(extra) version error!"
			#else
				#error "reflection.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_REFLECTION_EXTRA_MAYOR_ || LLANYLIB_REFLECTION_EXTRA_MINOR_

	#else
		#define LLANYLIB_REFLECTION_EXTRA_HPP_
		#define LLANYLIB_REFLECTION_EXTRA_MAYOR_ 12
		#define LLANYLIB_REFLECTION_EXTRA_MINOR_ 0

	#endif // LLANYLIB_REFLECTION_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
