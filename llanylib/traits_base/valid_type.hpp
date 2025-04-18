//////////////////////////////////////////////
//	valid_type.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "valid_type.hpp(incomplete) version error!"
		#else
			#error "valid_type.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_HPP_)
	#define LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_HPP_
	#define LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MINOR_ 0

namespace llcpp {
namespace meta {
namespace traits {
} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TRAITSVALIDTYPE_HPP_)
	#if LLANYLIB_TRAITSVALIDTYPE_MAYOR_ != 12 || LLANYLIB_TRAITSVALIDTYPE_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "valid_type.hpp version error!"
		#else
			#error "valid_type.hpp version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSVALIDTYPE_MAYOR_ || LLANYLIB_TRAITSVALIDTYPE_MINOR_

#else
	#define LLANYLIB_TRAITSVALIDTYPE_HPP_
	#define LLANYLIB_TRAITSVALIDTYPE_MAYOR_ 12
	#define LLANYLIB_TRAITSVALIDTYPE_MINOR_ 0

#include "type_traits.hpp"
#include "../types/ValidType.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<
	::llcpp::meta::ValidType _TYPE,
	class OnValidAttr,
	class OnInvalidAttr,
	class OnToCheck,
	class OnPrimitive,
	class OnArray,
	class OnPointer,
	class OnUnknown,
	class OnError
>
using type_by_valid_type_t = ::std::disjunction<
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::Valid,		OnValidAttr>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::Invalid,	OnInvalidAttr>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::ToCheck,	OnToCheck>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::Primitive,	OnPrimitive>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::Array,		OnArray>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::Pointer,	OnPointer>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::Unknown,	OnUnknown>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::meta::ValidType::Error,		OnError>,
	::llcpp::meta::traits::TrueContainerEmptyClass
>::U;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSVALIDTYPE_HPP_
