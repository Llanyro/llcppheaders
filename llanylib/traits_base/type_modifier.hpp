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

#include "type_traits.hpp"
#include "../types/type_update.hpp"

namespace llcpp {
namespace meta {
namespace traits {
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
		using edited_type	= ::llcpp::meta::traits::TypeContainer<unpacked_type[::llcpp::meta::traits::array_size<_T>]>;
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
	namespace traits_func = ::llcpp::meta::traits;
	namespace traits_priv = ::llcpp::meta::traits::__traits__;

	if constexpr (::std::is_array_v<_T>) {
		// Remove array from type
		using type_edited = traits_func::array_type_t<_T>;
		using packed_type = decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::value_type;
		if constexpr (_ATTRIBUTES.REMOVE_ARRAY)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<unpacked_type[traits_func::array_size<_T>]>{};
	}
	else if constexpr (::std::is_reference_v<_T>) {
		// Remove reference from type
		using type_edited	= ::std::remove_reference_t<_T>;
		using packed_type	= decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::value_type;
		if constexpr (_ATTRIBUTES.REMOVE_REFERENCE)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<unpacked_type&>{};
	}
	else if constexpr (::std::is_pointer_v<_T>) {
		// Remove pointer from type
		using type_edited	= ::std::remove_pointer_t<_T>;
		using packed_type	= decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::value_type;
		if constexpr (_ATTRIBUTES.REMOVE_POINTER)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<unpacked_type*>{};
	}
	else if constexpr (::std::is_const_v<_T>) {
		// Remove const from type
		using type_edited	= ::std::remove_const_t<_T>;
		using packed_type	= decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::value_type;
		if constexpr (_ATTRIBUTES.REMOVE_CONST)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<const unpacked_type>{};
	}
	else if constexpr (::std::is_volatile_v<_T>) {
		// Remove const from type
		using type_edited	= ::std::remove_volatile_t<_T>;
		using packed_type	= decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::value_type;
		if constexpr (_ATTRIBUTES.REMOVE_CONST)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<volatile unpacked_type>{};
	}
	else if constexpr (::llcpp::meta::traits::has_contain_value_type_v<_T, _T> && ::llcpp::meta::traits::has_value_type_v<_T>) {
		// Remove const from type
		using type_edited	= typename _T::value_type;
		using packed_type	= decltype(traits_priv::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::value_type;
		if constexpr (_ATTRIBUTES.REMOVE_CONTAINER)
			return traits_func::TypeContainer<unpacked_type>{};
		else return traits_func::TypeContainer<typename _T::contain_value_type<unpacked_type>>{};
	}
	else return traits_func::TypeContainer<_T>{};
}

template<class _T, u8 LEVEL = ::llcpp::MAX_VALUE<u8>>
constexpr auto remove_container_absolute() noexcept {
	if constexpr (LEVEL == ::llcpp::ZERO_VALUE<decltype(LEVEL)>)
		return traits_func::TypeContainer<_T>{};
	else {
		namespace traits_func = ::llcpp::meta::traits;
		namespace traits_priv = ::llcpp::meta::traits::__traits__;
	
		if constexpr (::llcpp::meta::traits::has_value_type_v<_T>) {
			// Remove const from type
			using type_edited	= typename _T::value_type;
			using packed_type	= decltype(traits_priv::remove_container_absolute<type_edited, LEVEL - 1>());
			return traits_func::TypeContainer<typename packed_type::value_type>{};
		}
		else return traits_func::TypeContainer<_T>{};
	}
}

} // namespace __traits__

template<class T, ::llcpp::meta::attributes::type_update_t ATTRIBUTES>
using type_modifier_t = decltype(::llcpp::meta::traits::__traits__::type_modifier<T, ATTRIBUTES>())::T;

template<class T>
using raw_type_t = ::llcpp::meta::traits::type_modifier_t<T, ::llcpp::meta::attributes::update::RAW_TYPE>;

//using t = type_modifier_t<const char**, ::llcpp::meta::attributes::update::RAW_TYPE>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSTYPEMODIFIER_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
