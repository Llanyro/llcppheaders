//////////////////////////////////////////////
//	valid_type.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_HPP_)
	#if LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "valid_type.hpp(incomplete) version error!"
		#else
			#error "valid_type.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_MAYOR_ || LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_HPP_)
	#define LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_HPP_
	#define LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_CONCEPTSVALIDTYPE_INCOMPLETE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/concepts/concepts.hpp>
	#include <llanylib/traits_base/valid_type.hpp>
#else
	#include "../traits_base/valid_type.hpp"
	#include "concepts.hpp"
#endif // LL_LIB_PATHS

#elif defined(LLANYLIB_CONCEPTSVALIDTYPE_HPP_)
	#if LLANYLIB_CONCEPTSVALIDTYPE_MAYOR_ != 12 || LLANYLIB_CONCEPTSVALIDTYPE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "valid_type.hpp version error!"
		#else
			#error "valid_type.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONCEPTSVALIDTYPE_MAYOR_ || LLANYLIB_CONCEPTSVALIDTYPE_MINOR_

#else
	#define LLANYLIB_CONCEPTSVALIDTYPE_HPP_
	#define LLANYLIB_CONCEPTSVALIDTYPE_MAYOR_ 12
	#define LLANYLIB_CONCEPTSVALIDTYPE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/concepts/concepts.hpp>
	#include <llanylib/traits_base/valid_type.hpp>
#else
	#include "../traits_base/valid_type.hpp"
	#include "concepts.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace concepts {
namespace signature {

// validationType() must return a valid type
template<class T>
concept HasValidationType = requires (T t) {
	{ t.validationType() } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<::llcpp::ValidType>;
};

template<class T, class ReturnType = ll_bool_t>
concept HasClear = requires (T t) {
	{ t.clear() } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>;
};
template<class T, class ReturnType = ll_bool_t, class... Args>
concept HasClearOther = requires (T t, Args... args) {
	{ t.clear(::std::forward<Args>(args)...) } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ReturnType>;
};

template<class T, class ReturnType = ll_bool_t, class ReturnType = ll_bool_t>
concept HasMakeInvalid = requires (T t) {
	{ t.makeInvalid() } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ll_bool_t>;
};
template<class T, class ReturnType = ll_bool_t, class... Args>
concept HasMakeInvalidOther = requires (T t, Args... args) {
	{ t.makeInvalid(::std::forward<Args>(args)...) } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ll_bool_t>;
};

template<class T, class ReturnType = ll_bool_t>
concept HasMakeInvalidClear = requires (T t) {
	{ t.makeInvalidClear() } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ll_bool_t>;
};
template<class T, class ReturnType = ll_bool_t, class... Args>
concept HasMakeInvalidClearOther = requires (T t, Args... args) {
	{ t.makeInvalidClear(::std::forward<Args>(args)...) } noexcept -> ::llcpp::meta::concepts::base::IsStrictSameOrVoid<ll_bool_t>;
};


} // namespace signature
} // namespace concepts
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CONCEPTSVALIDTYPE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
