//////////////////////////////////////////////
//	GenericFunctions.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CONCEPTSGENERICFUNCTIONS_INCOMPLETE_HPP_)
	#if LLANYLIB_CONCEPTSGENERICFUNCTIONS_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_CONCEPTSGENERICFUNCTIONS_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "GenericFunctions.hpp(incomplete) version error!"
		#else
			#error "GenericFunctions.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONCEPTSGENERICFUNCTIONS_INCOMPLETE_MAYOR_ || LLANYLIB_CONCEPTSGENERICFUNCTIONS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CONCEPTSGENERICFUNCTIONS_INCOMPLETE_HPP_)
	#define LLANYLIB_CONCEPTSGENERICFUNCTIONS_INCOMPLETE_HPP_
	#define LLANYLIB_CONCEPTSGENERICFUNCTIONS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_CONCEPTSGENERICFUNCTIONS_INCOMPLETE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/concepts/concepts.hpp>
#else
	#include "concepts.hpp"
#endif // LL_LIB_PATHS

#elif defined(LLANYLIB_CONCEPTSGENERICFUNCTIONS_HPP_)
	#if LLANYLIB_CONCEPTSGENERICFUNCTIONS_MAYOR_ != 12 || LLANYLIB_CONCEPTSGENERICFUNCTIONS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "GenericFunctions.hpp version error!"
		#else
			#error "GenericFunctions.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONCEPTSGENERICFUNCTIONS_MAYOR_ || LLANYLIB_CONCEPTSGENERICFUNCTIONS_MINOR_

#else
	#define LLANYLIB_CONCEPTSGENERICFUNCTIONS_HPP_
	#define LLANYLIB_CONCEPTSGENERICFUNCTIONS_MAYOR_ 12
	#define LLANYLIB_CONCEPTSGENERICFUNCTIONS_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/concepts/concepts.hpp>
#else
	#include "concepts.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace concepts {
namespace signature {

template<class T, class ReturnType = ::llcpp::Emptyclass, class... Args>
concept HasCleaner = requires (T t, Args&... args) {
	{ t.__cleaner(::std::forward<Args&>(args)...) } noexcept -> ::llcpp::meta::concepts::base::IsGenericFunctionsSameOrVoid<ReturnType>;
};
template<class T, class ReturnType = void, class... Args>
concept HasInvalidator = requires (T& t, Args&... args) {
	{ t.__invalidate(::std::forward<Args&>(args)...) } noexcept -> ::llcpp::meta::concepts::base::IsGenericFunctionsSameOrVoid<ReturnType>;
};
template<class T, class ReturnType = void, class... Args>
concept HasCopyator = requires (T& t, Args&... args) {
	{ t.__copy(::std::forward<Args&>(args)...) } noexcept -> ::llcpp::meta::concepts::base::IsGenericFunctionsSameOrVoid<ReturnType>;
};
template<class T, class ReturnType = void, class... Args>
concept HasMoveator = requires (T& t, Args&... args) {
	{ t.__move(::std::forward<Args&>(args)...) } noexcept -> ::llcpp::meta::concepts::base::IsGenericFunctionsSameOrVoid<ReturnType>;
};

} // namespace signature
} // namespace concepts
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CONCEPTSGENERICFUNCTIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
