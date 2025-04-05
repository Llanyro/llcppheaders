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
		#if defined(__LL_REAL_CXX23)
			#warning "type_modifier.hpp(incomplete) version error!"
		#else
			#error "type_modifier.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_HPP_)
#define LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_HPP_
#define LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MAYOR_ 12
#define LLANYLIB_TRAITSTYPEMODIFIER_INCOMPLETE_MINOR_ 0

#include "type_traits.hpp"
#undef LLANYLIB_INCOMPLETE_HPP_
#include "../types/type_update.hpp"
#define LLANYLIB_INCOMPLETE_HPP_

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
		#if defined(__LL_REAL_CXX23)
			#warning "type_modifier.hpp version error!"
		#else
			#error "type_modifier.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSTYPEMODIFIER_MAYOR_ || LLANYLIB_TRAITSTYPEMODIFIER_MINOR_

#else
#define LLANYLIB_TRAITSTYPEMODIFIER_HPP_
#define LLANYLIB_TRAITSTYPEMODIFIER_MAYOR_ 12
#define LLANYLIB_TRAITSTYPEMODIFIER_MINOR_ 0

#include "type_traits.hpp"
#include "../types/type_update.hpp"

namespace llcpp {
namespace meta {
namespace traits {
namespace __traits__ {

// [TODO]
// 	Use a data container to count type attributes
// 	So user can select how many attributes wants to remove or add...
// [TOFIX]
struct attribute_counter_t {
	// Class related
	using _MyType		= attribute_counter_t;

	// Types and enums
	using AttributeType	= u8;

	// Attributes
	AttributeType REMOVE_POINTER	: 1;
	AttributeType REMOVE_CONST		: 1;
	AttributeType REMOVE_VOLATILE	: 1;
	AttributeType REMOVE_ARRAY		: 1;
	AttributeType REMOVE_REFERENCE	: 1;

	static constexpr void reduceIfNotMax(AttributeType& v) noexcept {
		if (v != ::llcpp::MAX_VALUE<AttributeType>)
			--v;
	}
	static constexpr ll_bool_t isValid(const AttributeType& v) noexcept {
		return v > 0;
	}
	template<class removed_type, class edited_type>
	static constexpr auto removeOrUpdateType(AttributeType& attr) noexcept {
		if (_MyType::isValid(attr)) {
			_MyType::reduceIfNotMax(attr);
			return removed_type{};
		}
		else return edited_type{};
	}
};

template<class _T>
constexpr auto type_modifier_flex(::llcpp::meta::attributes::type_update_t& modifier) noexcept {
	namespace traits_func = ::llcpp::meta::traits;
	namespace traits_priv = ::llcpp::meta::traits::__traits__;

	if constexpr (::std::is_array_v<_T>) {
		// Remove array from type
		using type_edited = traits_func::array_type_t<_T>;
		using packed_type = decltype(traits_priv::type_modifier_flex<type_edited>(modifier));
		using unpacked_type = typename packed_type::T;

		using removed_type	= traits_func::TypeContainer<unpacked_type>;
		using edited_type	= traits_func::TypeContainer<unpacked_type[traits_func::array_size<_T>]>;

		return attribute_counter_t::removeOrUpdateType<removed_type, edited_type>(modifier.REMOVE_ARRAY);
	}
	else if constexpr (::std::is_reference_v<_T>) {
		// Remove reference from type
		using type_edited = ::std::remove_reference_t<_T>;
		using packed_type = decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;

		using removed_type	= traits_func::TypeContainer<unpacked_type>;
		using edited_type	= traits_func::TypeContainer<unpacked_type&>;

		return attribute_counter_t::removeOrUpdateType<removed_type, edited_type>(modifier.REMOVE_REFERENCE);
	}
	else if constexpr (::std::is_pointer_v<_T>) {
		// Remove pointer from type
		using type_edited = ::std::remove_pointer_t<_T>;
		using packed_type = decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;

		using removed_type	= traits_func::TypeContainer<unpacked_type>;
		using edited_type	= traits_func::TypeContainer<unpacked_type*>;

		return attribute_counter_t::removeOrUpdateType<removed_type, edited_type>(modifier.REMOVE_POINTER);
	}
	else if constexpr (::std::is_const_v<_T>) {
		// Remove const from type
		using type_edited = ::std::remove_const_t<_T>;
		using packed_type = decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;

		using removed_type	= traits_func::TypeContainer<unpacked_type>;
		using edited_type	= traits_func::TypeContainer<const unpacked_type>;

		return attribute_counter_t::removeOrUpdateType<removed_type, edited_type>(modifier.REMOVE_CONST);
	}
	else if constexpr (::std::is_volatile_v<_T>) {
		// Remove const from type
		using type_edited = ::std::remove_volatile_t<_T>;
		using packed_type = decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;

		using removed_type	= traits_func::TypeContainer<unpacked_type>;
		using edited_type	= traits_func::TypeContainer<volatile unpacked_type>;

		return attribute_counter_t::removeOrUpdateType<removed_type, edited_type>(modifier.REMOVE_VOLATILE);
	}
	else return traits_func::TypeContainer<_T>{};
}
template<class _T, ::llcpp::meta::attributes::type_update_t ATTRIBUTES>
constexpr auto type_modifier() noexcept {
	::llcpp::meta::attributes::type_update_t modifier = ATTRIBUTES;
	return ::llcpp::meta::traits::__traits__::type_modifier_flex<_T>(modifier);
}

constexpr auto a = type_modifier<const char**, ::llcpp::meta::attributes::update::RAW_TYPE>();

constexpr auto asdafa() noexcept {
	u8 aa = 9;
	return attribute_counter_t::removeOrUpdateType<int, char>(aa);
}

constexpr auto asdf = asdafa();

// Removes type attributes by a given struct
// If value is max value, value will not be reduced
/*template<class _T, ::llcpp::meta::attributes::type_update_t _ATTRIBUTES>
constexpr auto type_modifier() {
	namespace traits_func = ::llcpp::meta::traits;
	namespace traits_priv = ::llcpp::meta::traits::__traits__;

	if constexpr (::std::is_array_v<_T>) {
		// Remove array from type
		using type_edited = traits_func::array_type_t<_T>;
		using packed_type = decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_ARRAY)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<unpacked_type[traits_func::array_size<_T>]>{};
	}
	else if constexpr (::std::is_reference_v<_T>) {
		// Remove reference from type
		using type_edited	= ::std::remove_reference_t<_T>;
		using packed_type	= decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_REFERENCE)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<unpacked_type&>{};
	}
	else if constexpr (::std::is_pointer_v<_T>) {
		// Remove pointer from type
		using type_edited	= ::std::remove_pointer_t<_T>;
		using packed_type	= decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_POINTER)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<unpacked_type*>{};
	}
	else if constexpr (::std::is_const_v<_T>) {
		// Remove const from type
		using type_edited	= ::std::remove_const_t<_T>;
		using packed_type	= decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_CONST)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<const unpacked_type>{};
	}
	else if constexpr (::std::is_volatile_v<_T>) {
		// Remove const from type
		using type_edited	= ::std::remove_volatile_t<_T>;
		using packed_type	= decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_CONST)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<volatile unpacked_type>{};
	}
	else return traits_func::TypeContainer<_T>{};
}
*/

} // namespace __traits__

template<class T, ::llcpp::meta::attributes::type_update_t ATTRIBUTES>
using type_modifier_t = decltype(::llcpp::meta::traits::__traits__::type_modifier<T, ATTRIBUTES>())::T;

using t = type_modifier_t<const char**, ::llcpp::meta::attributes::update::RAW_TYPE>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSTYPEMODIFIER_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
