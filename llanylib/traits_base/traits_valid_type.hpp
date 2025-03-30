//////////////////////////////////////////////
//	traits_valid_type.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_valid_type.hpp(incomplete) version error!"
		#else
			#error "traits_valid_type.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_HPP_)
	#define LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_HPP_
	#define LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_TRAITSVALIDTYPE_HPP_)
	#if LLANYLIB_TRAITSVALIDTYPE_MAYOR_ != 11 || LLANYLIB_TRAITSVALIDTYPE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_valid_type.hpp version error!"
		#else
			#error "traits_valid_type.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSVALIDTYPE_MAYOR_ || LLANYLIB_TRAITSVALIDTYPE_MINOR_

#else
	#define LLANYLIB_TRAITSVALIDTYPE_HPP_
	#define LLANYLIB_TRAITSVALIDTYPE_MAYOR_ 11
	#define LLANYLIB_TRAITSVALIDTYPE_MINOR_ 0

#include "type_traits.hpp"
#include "../types_base/ValidType.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<
	::llcpp::meta::ValidType _TYPE,
	class OnValidAttr,
	class OnInvalidAttr,
	class OnToCheck,
	class OnUnknown,
	class OnError
>
using type_by_valid_type_t = ::std::disjunction<
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::Valid,		OnValidAttr>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::Invalid,	OnInvalidAttr>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::ToCheck,	OnToCheck>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::Unknown,	OnUnknown>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::Error,		OnError>,
	::llcpp::meta::traits::TrueContainerEmptyClass
>::U;

} // namespace traits
} // namespace meta
} // namespace llcpp


#endif // LLANYLIB_TRAITSVALIDTYPE_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_TRAITSVALIDTYPE_EXTRA_HPP_)
		#if LLANYLIB_TRAITSVALIDTYPE_EXTRA_MAYOR_ != 11 || LLANYLIB_TRAITSVALIDTYPE_EXTRA_MINOR_ < 0
			#if defined(__LL_REAL_CXX23)
				#warning "traits_valid_type.hpp(extra) version error!"
			#else
				#error "traits_valid_type.hpp(extra) version error!"
			#endif // __LL_REAL_CXX23
		#endif // LLANYLIB_TRAITSVALIDTYPE_EXTRA_MAYOR_ || LLANYLIB_TRAITSVALIDTYPE_EXTRA_MINOR_

	#else
		#define LLANYLIB_TRAITSVALIDTYPE_EXTRA_HPP_
		#define LLANYLIB_TRAITSVALIDTYPE_EXTRA_MAYOR_ 11
		#define LLANYLIB_TRAITSVALIDTYPE_EXTRA_MINOR_ 0

	#endif // LLANYLIB_TRAITSVALIDTYPE_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
