//////////////////////////////////////////////
//	cleaner.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CONCEPTSCLEANER_INCOMPLETE_HPP_)
	#if LLANYLIB_CONCEPTSCLEANER_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_CONCEPTSCLEANER_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "cleaner.hpp(incomplete) version error!"
		#else
			#error "cleaner.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONCEPTSCLEANER_INCOMPLETE_MAYOR_ || LLANYLIB_CONCEPTSCLEANER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CONCEPTSCLEANER_INCOMPLETE_HPP_)
	#define LLANYLIB_CONCEPTSCLEANER_INCOMPLETE_HPP_
	#define LLANYLIB_CONCEPTSCLEANER_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_CONCEPTSCLEANER_INCOMPLETE_MINOR_ 0

#include <llanylib/concepts/concepts.hpp>

#elif defined(LLANYLIB_CONCEPTSCLEANER_HPP_)
	#if LLANYLIB_CONCEPTSCLEANER_MAYOR_ != 12 || LLANYLIB_CONCEPTSCLEANER_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "cleaner.hpp version error!"
		#else
			#error "cleaner.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONCEPTSCLEANER_MAYOR_ || LLANYLIB_CONCEPTSCLEANER_MINOR_

#else
	#define LLANYLIB_CONCEPTSCLEANER_HPP_
	#define LLANYLIB_CONCEPTSCLEANER_MAYOR_ 12
	#define LLANYLIB_CONCEPTSCLEANER_MINOR_ 0

#include <llanylib/concepts/concepts.hpp>
#include <llanylib/traits_base/type_traits_extended.hpp>

namespace llcpp {
namespace meta {
namespace concepts {
namespace signature {

template<class T, class ReturnType = void, class... Args>
concept HasCleaner = requires (const T t, Args... args) {
	{ t.__cleaner(::std::forward<Args>(args)...) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};
template<class T, class ReturnType = void, class... Args>
concept HasInvalidator = requires (const T t, Args... args) {
	{ t.__invalidate(::std::forward<Args>(args)...) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<ReturnType>;
};

} // namespace signature
} // namespace concepts
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CONCEPTSCLEANER_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
