//////////////////////////////////////////////
//	traits_type_update.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSTYPEUPDATE_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSTYPEUPDATE_MAYOR_ != 10 || LLANYLIB_TRAITSTYPEUPDATE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_type_update.hpp version error!"
		#else
			#error "traits_type_update.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSTYPEUPDATE_MAYOR_ || LLANYLIB_TRAITSTYPEUPDATE_MINOR_

#else !defined(LLANYLIB_TRAITSTYPEUPDATE_HPP_)
#define LLANYLIB_TRAITSTYPEUPDATE_HPP_
#define LLANYLIB_TRAITSTYPEUPDATE_MAYOR_ 10
#define LLANYLIB_TRAITSTYPEUPDATE_MINOR_ 0

#include "traits_selection.hpp"

namespace llcpp {
namespace meta {
namespace traits {

struct type_update_t {
	// Class related
	using _MyType = type_update_t;

	// Attributes
	ll_bool_t REMOVE_POINTER	: 1;
	ll_bool_t REMOVE_CONST		: 1;
	ll_bool_t REMOVE_VOLATILE	: 1;
	ll_bool_t REMOVE_ARRAY		: 1;
	ll_bool_t REMOVE_REFERENCE	: 1;
};

namespace update {

__LL_VAR_INLINE__ constexpr traits::type_update_t REMOVE_CONSTS		= { llcpp::FALSE, llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr traits::type_update_t REMOVE_POINTERS	= { llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr traits::type_update_t REMOVE_ARRAYS		= { llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::TRUE,  llcpp::FALSE };
__LL_VAR_INLINE__ constexpr traits::type_update_t RAW_TYPE			= { llcpp::TRUE,  llcpp::TRUE,  llcpp::TRUE,  llcpp::TRUE,  llcpp::TRUE  };

} // namespace update

template<class _T, traits::type_update_t _ATTRIBUTES>
constexpr auto type_modifier() {
	if constexpr (std::is_array_v<_T>) {
		// Remove array from type
		using type_edited = traits::array_type_t<_T>;
		using packed_type = decltype(traits::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_ARRAY)
			return traits::type_container<unpacked_type>{};
		else return traits::type_container<unpacked_type[traits::array_size<_T>]>{};
	}
	else if constexpr (std::is_reference_v<_T>) {
		// Remove reference from type
		using type_edited	= std::remove_reference_t<_T>;
		using packed_type	= decltype(traits::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_REFERENCE)
			return traits::type_container<unpacked_type>{};
		else return traits::type_container<unpacked_type&>{};
	}
	else if constexpr (std::is_pointer_v<_T>) {
		// Remove pointer from type
		using type_edited	= std::remove_pointer_t<_T>;
		using packed_type	= decltype(traits::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_POINTER)
			return traits::type_container<unpacked_type>{};
		else return traits::type_container<unpacked_type*>{};
	}
	else if constexpr (std::is_const_v<_T>) {
		// Remove const from type
		using type_edited	= std::remove_const_t<_T>;
		using packed_type	= decltype(traits::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_CONST)
			return traits::type_container<unpacked_type>{};
		else return traits::type_container<const unpacked_type>{};
	}
	else if constexpr (std::is_volatile_v<_T>) {
		// Remove const from type
		using type_edited	= std::remove_volatile_t<_T>;
		using packed_type	= decltype(traits::type_modifier<type_edited, _ATTRIBUTES>());
		using unpacked_type = typename packed_type::T;
		if constexpr (_ATTRIBUTES.REMOVE_CONST)
			return traits::type_container<unpacked_type>{};
		else return traits::type_container<volatile unpacked_type>{};
	}
	else return traits::type_container<_T>{};
}

template<class _T, traits::type_update_t _ATTRIBUTES>
using type_modifier_t = decltype(type_modifier<_T, _ATTRIBUTES>())::T;

template<class T, ll_bool_t PROMOTE = llcpp::TRUE>
using type_promotion = traits::type_selection<llcpp::Emptyclass>::get_conincidence<
	T,
	traits::double_type_container<i8,	traits::conditional_t<PROMOTE, i16, i8>>,
	traits::double_type_container<i16,	traits::conditional_t<PROMOTE, i32, i8>>,
	traits::double_type_container<i32,	traits::conditional_t<PROMOTE, i64, i16>>,
	traits::double_type_container<i64,	traits::conditional_t<PROMOTE, i128, i32>>,
	traits::double_type_container<i128, traits::conditional_t<PROMOTE, i256, i64>>,
	traits::double_type_container<i256, traits::conditional_t<PROMOTE, i256, i128>>,

	traits::double_type_container<u8,	traits::conditional_t<PROMOTE, u16, u8>>,
	traits::double_type_container<u16,	traits::conditional_t<PROMOTE, u32, u8>>,
	traits::double_type_container<u32,	traits::conditional_t<PROMOTE, u64, u16>>,
	traits::double_type_container<u64,	traits::conditional_t<PROMOTE, u128, u32>>,
	traits::double_type_container<u128,	traits::conditional_t<PROMOTE, u256, u64>>,
	traits::double_type_container<u256,	traits::conditional_t<PROMOTE, u256, u128>>,

	traits::double_type_container<f32,	traits::conditional_t<PROMOTE, f64, f32>>,
	traits::double_type_container<f64,	traits::conditional_t<PROMOTE, f128, f32>>,
	traits::double_type_container<f128,	traits::conditional_t<PROMOTE, f128, f64>>
>;

template<class T, ll_bool_t SIGNALIZE = llcpp::TRUE>
using type_signed = traits::type_selection<llcpp::Emptyclass>::get_conincidence<
	T,
	traits::double_type_container<i8,	traits::conditional_t<SIGNALIZE, i8, u8>>,
	traits::double_type_container<i16,	traits::conditional_t<SIGNALIZE, i16, u16>>,
	traits::double_type_container<i32,	traits::conditional_t<SIGNALIZE, i32, u32>>,
	traits::double_type_container<i64,	traits::conditional_t<SIGNALIZE, i64, u64>>,
	traits::double_type_container<i128, traits::conditional_t<SIGNALIZE, i128, u128>>,
	traits::double_type_container<i256, traits::conditional_t<SIGNALIZE, i256, u256>>,

	traits::double_type_container<u8,	traits::conditional_t<SIGNALIZE, i8, u8>>,
	traits::double_type_container<u16,	traits::conditional_t<SIGNALIZE, i16, u16>>,
	traits::double_type_container<u32,	traits::conditional_t<SIGNALIZE, i32, u32>>,
	traits::double_type_container<u64,	traits::conditional_t<SIGNALIZE, i64, u64>>,
	traits::double_type_container<u128,	traits::conditional_t<SIGNALIZE, i128, u128>>,
	traits::double_type_container<u256,	traits::conditional_t<SIGNALIZE, i256, u256>>
>;

// Get type of math operation type
template<class T, class U>
using type_bigger_of_two = traits::conditional_t<(sizeof(T) > sizeof(U)), T, U>;
template<class T, class U>
using type_smaller_of_two = traits::conditional_t<(sizeof(T) < sizeof(U)), T, U>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSTYPEUPDATE_HPP_
