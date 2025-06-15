//////////////////////////////////////////////
//	type_modifier.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "type_modifier.hpp(incomplete) version error!"
		#else
			#error "type_modifier.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_HPP_)
#define LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_HPP_
#define LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MAYOR_ 12
#define LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/traits_base/type_traits.hpp>
	#undef LLANYLIB_INCOMPLETE_HPP_
	#include <llanylib/types/type_update.hpp>
	#define LLANYLIB_INCOMPLETE_HPP_
#else
	#include "type_traits.hpp"
	#undef LLANYLIB_INCOMPLETE_HPP_
	#include "../types/type_update.hpp"
	#define LLANYLIB_INCOMPLETE_HPP_
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace traits {

struct type_update_t;
struct attribute_counter;

template<class _T, ::llcpp::meta::attributes::type_update_t _ATTRIBUTES>
constexpr auto type_modifier();

} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TRAITSTYPEMODIFIER_HPP_)
	#if LLANYLIB_TRAITSTYPEMODIFIER_MAYOR_ != 12 || LLANYLIB_TRAITSTYPEMODIFIER_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "type_modifier.hpp version error!"
		#else
			#error "type_modifier.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSTYPEMODIFIER_MAYOR_ || LLANYLIB_TRAITSTYPEMODIFIER_MINOR_

#else
#define LLANYLIB_TRAITSTYPEMODIFIER_HPP_
#define LLANYLIB_TRAITSTYPEMODIFIER_MAYOR_ 12
#define LLANYLIB_TRAITSTYPEMODIFIER_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/traits_base/type_traits_extended.hpp>
	#include <llanylib/types/type_update.hpp>
#else
	#include "type_traits_extended.hpp"
	#include "../types/type_update.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace traits {
namespace __traits__ {

template<class _T, ::llcpp::meta::attributes::type_update_t _ATTRIBUTES>
constexpr auto type_modifier() noexcept;

} // namespace __traits__

template<class T, ::llcpp::meta::attributes::type_update_t ATTRIBUTES>
using type_modifier_t = decltype(::llcpp::meta::traits::__traits__::type_modifier<T, ATTRIBUTES>())::T;

template<class T>
using raw_type_t = ::llcpp::meta::traits::type_modifier_t<T, ::llcpp::meta::attributes::update::RAW_TYPE>;

namespace __traits__ {

/*
// 	Use a data container to count type attributes
// 	So user can select how many attributes wants to remove or add...
struct attribute_counter_t {
	// Class related
	using _MyType		= attribute_counter_t;

	// Types and enums
	using AttributeType	= u8;

	// Attributes
	AttributeType REMOVE_POINTER;
	AttributeType REMOVE_CONST;
	AttributeType REMOVE_VOLATILE;
	AttributeType REMOVE_ARRAY;
	AttributeType REMOVE_REFERENCE;

	static constexpr void reduceIfNotMin(AttributeType& v) noexcept {
		if (v != ::llcpp::MIN_VALUE<AttributeType>)
			--v;
	}
	__LL_NODISCARD__ static constexpr ll_bool_t isValid(const AttributeType& v) noexcept {
		return v > 0;
	}
	__LL_NODISCARD__ static constexpr ll_bool_t removeOrUpdateType(AttributeType& attr) noexcept {
		if (_MyType::isValid(attr)) {
			_MyType::reduceIfNotMin(attr);
			return ::llcpp::LL_TRUE;
		}
		else return ::llcpp::LL_FALSE;
	}
};

template<class _T>
__LL_NODISCARD__ constexpr auto type_modifier_flex(::llcpp::meta::traits::__traits__::attribute_counter_t& modifier) noexcept {
	if constexpr (::std::is_array_v<_T>) {
		// Remove array from type
		using type_edited = ::llcpp::meta::traits::array_type_t<_T>;
		// Pack rest of parameters
		using packed_type = decltype(::llcpp::meta::traits::__traits__::type_modifier_flex<type_edited>(modifier));
		// Unpack type returned
		using unpacked_type = typename packed_type::T;
		// Type with atturibute added again
		using edited_type	= ::llcpp::meta::traits::TypeContainer<unpacked_type[::llcpp::array_size<_T>]>;
		// Choose between new type generated with this type or without by attribute
		return ::llcpp::meta::traits::__traits__::attribute_counter_t::removeOrUpdateType<packed_type, edited_type>(modifier.REMOVE_ARRAY);
	}
	else if constexpr (::std::is_reference_v<_T>) {
		// Remove reference from type
		using type_edited = ::std::remove_reference_t<_T>;
		// Pack rest of parameters
		using packed_type = decltype(::llcpp::meta::traits::__traits__::type_modifier_flex<type_edited>(modifier));
		// Unpack type returned
		using unpacked_type = typename packed_type::T;
		// Type with atturibute added again
		using edited_type	= ::llcpp::meta::traits::TypeContainer<unpacked_type&>;
		// Choose between new type generated with this type or without by attribute
		return ::llcpp::meta::traits::__traits__::attribute_counter_t::removeOrUpdateType<packed_type, edited_type>(modifier.REMOVE_REFERENCE);
	}
	else if constexpr (::std::is_pointer_v<_T>) {
		// Remove reference from type
		using type_edited = ::std::remove_pointer_t<_T>;
		// Pack rest of parameters
		using packed_type = decltype(::llcpp::meta::traits::__traits__::type_modifier_flex<type_edited>(modifier));
		// Type with atturibute added again
		if (modifier.removeOrUpdateType(modifier.REMOVE_POINTER))
			return ::llcpp::meta::traits::TypeContainer<typename packed_type::T*>{};
		else return packed_type{};
	}
	/*else if constexpr (::std::is_const_v<_T>) {
		// Remove const from type
		using type_edited = ::std::remove_const_t<_T>;
		using packed_type = decltype(::llcpp::meta::traits::__traits__::type_modifier_flex<type_edited>(modifier));
		using unpacked_type = typename packed_type::T;

		using removed_type	= ::llcpp::meta::traits::TypeContainer<unpacked_type>;
		using edited_type	= ::llcpp::meta::traits::TypeContainer<const unpacked_type>;

		return attribute_counter_t::removeOrUpdateType<removed_type, edited_type>(modifier.REMOVE_CONST);
	}
	else if constexpr (::std::is_volatile_v<_T>) {
		// Remove const from type
		using type_edited = ::std::remove_volatile_t<_T>;
		using packed_type = decltype(::llcpp::meta::traits::__traits__::type_modifier_flex<type_edited>(modifier));
		using unpacked_type = typename packed_type::T;

		using removed_type	= ::llcpp::meta::traits::TypeContainer<unpacked_type>;
		using edited_type	= ::llcpp::meta::traits::TypeContainer<volatile unpacked_type>;

		return attribute_counter_t::removeOrUpdateType<removed_type, edited_type>(modifier.REMOVE_VOLATILE);
	}
	* /
	else return ::llcpp::meta::traits::TypeContainer<_T>{};
}
template<class _T, ::llcpp::meta::attributes::type_update_t ATTRIBUTES>
constexpr auto type_modifier() noexcept {
	::llcpp::meta::traits::__traits__::attribute_counter_t modifier = {  255, 255, 255, 255, 255 };
	return ::llcpp::meta::traits::__traits__::type_modifier_flex<_T>(modifier);
}

constexpr auto a = type_modifier<const char**, ::llcpp::meta::attributes::update::RAW_TYPE>();

constexpr auto asdafa() noexcept {
	u8 aa = 9;
	return attribute_counter_t::removeOrUpdateType<int, char>(aa);
}

constexpr auto asdf = asdafa();
*/
// Removes type attributes by a given struct
// If value is max value, value will not be reduced
template<class _T, ::llcpp::meta::attributes::type_update_t _ATTRIBUTES>
constexpr auto type_modifier() noexcept {
	if constexpr (::std::is_array_v<_T>) {
		constexpr auto sss = ::llcpp::array_size<_T>;
		// Remove array from type
		using type_edited = ::llcpp::meta::traits::array_type_t<_T>;
		using unpacked_type = ::llcpp::meta::traits::type_modifier_t<type_edited, _ATTRIBUTES>;
		if constexpr (_ATTRIBUTES.REMOVE_ARRAY)
			return ::llcpp::meta::traits::TypeContainer<unpacked_type>{};
		else return ::llcpp::meta::traits::TypeContainer<unpacked_type[sss]>{};
	}
	else if constexpr (::std::is_reference_v<_T>) {
		// Remove reference from type
		using type_edited	= ::std::remove_reference_t<_T>;
		using unpacked_type = ::llcpp::meta::traits::type_modifier_t<type_edited, _ATTRIBUTES>;
	if constexpr (_ATTRIBUTES.REMOVE_REFERENCE)
			return ::llcpp::meta::traits::TypeContainer<unpacked_type>{};
		else return ::llcpp::meta::traits::TypeContainer<unpacked_type&>{};
	}
	else if constexpr (::std::is_pointer_v<_T>) {
		// Remove pointer from type
		using type_edited	= ::std::remove_pointer_t<_T>;
		using unpacked_type = ::llcpp::meta::traits::type_modifier_t<type_edited, _ATTRIBUTES>;
		if constexpr (_ATTRIBUTES.REMOVE_POINTER)
			return ::llcpp::meta::traits::TypeContainer<unpacked_type>{};
		else return ::llcpp::meta::traits::TypeContainer<unpacked_type*>{};
	}
	else if constexpr (::std::is_const_v<_T>) {
		// Remove const from type
		using type_edited	= ::std::remove_const_t<_T>;
		using unpacked_type = ::llcpp::meta::traits::type_modifier_t<type_edited, _ATTRIBUTES>;
		if constexpr (_ATTRIBUTES.REMOVE_CONST)
			return ::llcpp::meta::traits::TypeContainer<unpacked_type>{};
		else return ::llcpp::meta::traits::TypeContainer<const unpacked_type>{};
	}
	else if constexpr (::std::is_volatile_v<_T>) {
		// Remove const from type
		using type_edited	= ::std::remove_volatile_t<_T>;
		using unpacked_type = ::llcpp::meta::traits::type_modifier_t<type_edited, _ATTRIBUTES>;
		if constexpr (_ATTRIBUTES.REMOVE_CONST)
			return ::llcpp::meta::traits::TypeContainer<unpacked_type>{};
		else return ::llcpp::meta::traits::TypeContainer<volatile unpacked_type>{};
	}
	else if constexpr (::llcpp::meta::traits::has_contain_value_type_v<_T, _T> && ::llcpp::meta::traits::has_value_type_v<_T>) {
		// Remove const from type
		using type_edited	= typename _T::value_type;
		using unpacked_type = ::llcpp::meta::traits::type_modifier_t<type_edited, _ATTRIBUTES>;
		if constexpr (_ATTRIBUTES.REMOVE_CONTAINER)
			return ::llcpp::meta::traits::TypeContainer<unpacked_type>{};
		else return ::llcpp::meta::traits::TypeContainer<typename _T::contain_value_type<unpacked_type>>{};
	}
	else return ::llcpp::meta::traits::TypeContainer<_T>{};
}

template<class _T, u8 LEVEL = ::llcpp::MAX_VALUE<u8>>
constexpr auto remove_container_absolute() noexcept {
	if constexpr (LEVEL == ::llcpp::ZERO_VALUE<decltype(LEVEL)> || ::llcpp::meta::traits::has_value_type_v<_T>)
		return ::llcpp::meta::traits::TypeContainer<_T>{};
	else {
		namespace traits_priv = ::llcpp::meta::traits::__traits__;
	
		// Remove const from type
		using type_edited	= typename _T::value_type;
		using packed_type	= decltype(traits_priv::remove_container_absolute<type_edited, LEVEL - 1>());
		using unpacked_type	= typename packed_type::value_type;
		return ::llcpp::meta::traits::TypeContainer<unpacked_type>{};
	}
}

} // namespace __traits__

//using t = type_modifier_t<const char**, ::llcpp::meta::attributes::update::RAW_TYPE>;

#if __LL_INCLUDE_KATS == 1
namespace kat {

using too_long_type_t = const int* const*[5];
using raw_long_type_t = ::llcpp::meta::traits::raw_type_t<too_long_type_t>;
using no_const_type_t = int**[5];
using no_array_type_t = const int* const*;

#pragma region Simple
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_RAW_TYPE = ::std::is_same_v<raw_long_type_t, int>;
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_raw_type_kat,
	::llcpp::meta::traits::kat::IS_WORKING_RAW_TYPE,
	"Type modifier raw" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr auto NO_CONST_ATTR = ::llcpp::meta::attributes::update::REMOVE_CONSTS;
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_NO_CONST_TYPE =
	::std::is_same_v<::llcpp::meta::traits::type_modifier_t<too_long_type_t, NO_CONST_ATTR>, no_const_type_t>;
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_remove_consts_kat,
	::llcpp::meta::traits::kat::IS_WORKING_NO_CONST_TYPE,
	"Type modifier no const" __LL_IS_NOT_WORKING_STR
);

// [TODO] [TOFIX] [TOCHECK]
__LL_VAR_INLINE__ constexpr auto NO_ARRAYS_ATTR = ::llcpp::meta::attributes::update::REMOVE_ARRAYS;
using FixAttr = ::llcpp::meta::traits::type_modifier_t<too_long_type_t, NO_ARRAYS_ATTR>;
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_NO_ARRAY_TYPE =
	::std::is_same_v<FixAttr, no_array_type_t>;
//__LL_KAT_FUNCTION_CONSTEXPR(
//	is_working_remove_arrays_kat,
//	::llcpp::meta::traits::kat::IS_WORKING_NO_ARRAY_TYPE,
//	"Type modifier no arrays" __LL_IS_NOT_WORKING_STR
//);

#pragma endregion
#pragma region Mixed

#pragma endregion

__LL_NODISCARD__ constexpr ::llcpp::string type_modifier_kats() noexcept {
	::llcpp::string result = ::llcpp::meta::traits::kat::is_working_raw_type_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_remove_consts_kat();
	if(result) return result;
	//result = ::llcpp::meta::traits::kat::is_working_remove_arrays_kat();
	//if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::traits::kat::type_modifier_kats() == LL_NULLPTR, "Type modifier KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSTYPEMODIFIER_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
