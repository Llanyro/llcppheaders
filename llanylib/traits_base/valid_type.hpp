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
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "valid_type.hpp(incomplete) version error!"
		#else
			#error "valid_type.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_HPP_)
	#define LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_HPP_
	#define LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_TRAITSVALIDTYPE_INCOMPLETE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/traits_base/type_traits.hpp>
	#include <llanylib/types/ValidType.hpp>
#else
	#include "type_traits.hpp"
	#include "../types/ValidType.hpp"
#endif // LL_LIB_PATHS
	
#elif defined(LLANYLIB_TRAITSVALIDTYPE_HPP_)
	#if LLANYLIB_TRAITSVALIDTYPE_MAYOR_ != 12 || LLANYLIB_TRAITSVALIDTYPE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "valid_type.hpp version error!"
		#else
			#error "valid_type.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSVALIDTYPE_MAYOR_ || LLANYLIB_TRAITSVALIDTYPE_MINOR_

#else
	#define LLANYLIB_TRAITSVALIDTYPE_HPP_
	#define LLANYLIB_TRAITSVALIDTYPE_MAYOR_ 12
	#define LLANYLIB_TRAITSVALIDTYPE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/traits_base/type_traits.hpp>
	#include <llanylib/types/ValidType.hpp>
#else
	#include "type_traits.hpp"
	#include "../types/ValidType.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace traits {

template<
	::llcpp::ValidType _TYPE,
	class OnValidAttr,
	class OnInvalidAttr,
	class OnToCheck,
	class OnPrimitive,
	class OnArray,
	class OnPointer,
	class OnUnknown,
	class OnError,
	class OnNotFound = ::llcpp::Emptyclass
>
using type_by_valid_type_t = typename ::std::disjunction<
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::ValidType::Valid,	OnValidAttr>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::ValidType::Invalid,	OnInvalidAttr>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::ValidType::ToCheck,	OnToCheck>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::ValidType::Primitive,OnPrimitive>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::ValidType::Array,	OnArray>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::ValidType::Pointer,	OnPointer>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::ValidType::Unknown,	OnUnknown>,
	::llcpp::meta::traits::BoolConstantContainer<_TYPE == ::llcpp::ValidType::Error,	OnError>,
	::llcpp::meta::traits::TrueContainerEmptyClass<OnNotFound>
>::U;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_tag_type_v =
	   ::std::is_same_v<T, ::llcpp::AlwaysValidTag>
	|| ::std::is_same_v<T, ::llcpp::AlwaysInvalidTag>
	|| ::std::is_same_v<T, ::llcpp::DummyClass>;

#if __LL_INCLUDE_KATS == 1
namespace kat {

template<::llcpp::ValidType _TYPE>
using ValidationKat = ::llcpp::meta::traits::type_by_valid_type_t<
	_TYPE,
	::llcpp::AlwaysValidTag,
	::llcpp::AlwaysInvalidTag,
	::llcpp::DummyClass,
	::llcpp::i32,
	::llcpp::string,
	::llcpp::f128*,
	::llcpp::ClusterTag,
	void,
	::llcpp::Emptyclass
>;

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_VALID_TYPE = 
	   ::std::is_same_v<ValidationKat<::llcpp::ValidType::Valid>,		::llcpp::AlwaysValidTag>
	&& ::std::is_same_v<ValidationKat<::llcpp::ValidType::Invalid>,		::llcpp::AlwaysInvalidTag>
	&& ::std::is_same_v<ValidationKat<::llcpp::ValidType::ToCheck>,		::llcpp::DummyClass>
	&& ::std::is_same_v<ValidationKat<::llcpp::ValidType::Primitive>,	::llcpp::i32>
	&& ::std::is_same_v<ValidationKat<::llcpp::ValidType::Array>,		::llcpp::string>
	&& ::std::is_same_v<ValidationKat<::llcpp::ValidType::Pointer>,		::llcpp::f128*>
	&& ::std::is_same_v<ValidationKat<::llcpp::ValidType::Unknown>,		::llcpp::ClusterTag>
	&& ::std::is_same_v<ValidationKat<::llcpp::ValidType::Error>,		void>;
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_valid_type_kat,
	::llcpp::meta::traits::kat::IS_WORKING_VALID_TYPE,
	"'Is valid type'" __LL_IS_NOT_WORKING_STR
);

__LL_NODISCARD__ constexpr ::llcpp::string valid_type_kats() noexcept {
	::llcpp::string result = ::llcpp::meta::traits::kat::is_working_valid_type_kat();
	if(result) return result;
	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::traits::kat::valid_type_kats() == LL_NULLPTR, "valid_type (traits) KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSVALIDTYPE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
