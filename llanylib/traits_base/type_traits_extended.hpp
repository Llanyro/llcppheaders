//////////////////////////////////////////////
//	type_traits_extended.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSBASE_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSBASE_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_TRAITSBASE_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "type_traits_extended.hpp(incomplete) version error!"
		#else
			#error "type_traits_extended.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSBASE_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSBASE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSBASE_INCOMPLETE_HPP_)
	#define LLANYLIB_TRAITSBASE_INCOMPLETE_HPP_
	#define LLANYLIB_TRAITSBASE_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_TRAITSBASE_INCOMPLETE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/traits_base/type_traits.hpp>
#else
	#include "type_traits.hpp"
#endif // LL_LIB_PATHS

#elif defined(LLANYLIB_TRAITSBASE_HPP_)
	#if LLANYLIB_TRAITSBASE_MAYOR_ != 12 || LLANYLIB_TRAITSBASE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "type_traits_extended.hpp version error!"
		#else
			#error "type_traits_extended.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSBASE_MAYOR_ || LLANYLIB_TRAITSBASE_MINOR_

#else
	#define LLANYLIB_TRAITSBASE_HPP_
	#define LLANYLIB_TRAITSBASE_MAYOR_ 12
	#define LLANYLIB_TRAITSBASE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/traits_base/type_traits.hpp>
#else
	#include "type_traits.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace traits {

template<class T, class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_of_v =
#if __LL_REAL_CXX17 == 1
	(::std::is_same_v<T, Args> || ...);
#else
	::std::disjunction_v<::std::is_same_v<T, Args>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_empty_object_v = ::llcpp::meta::traits::is_any_of_v<T, ::llcpp::Emptyclass>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_empty_type_v = ::std::is_same_v<T, void> || ::llcpp::meta::traits::is_empty_object_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_primitive_v = ::std::is_integral_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_primitive_big_v = ::llcpp::meta::traits::is_any_of_v<T, i128, i256, u128, u256>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_primitive_v = ::llcpp::meta::traits::is_primitive_v<T> || ::llcpp::meta::traits::is_primitive_big_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_floating_type_v = ::std::is_floating_point_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_floating_bigger_type_v = ::llcpp::meta::traits::is_any_of_v<T, f128>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_floating_v = ::llcpp::meta::traits::is_floating_type_v<T> || ::llcpp::meta::traits::is_floating_bigger_type_v<T>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_char_type_v = ::llcpp::meta::traits::is_any_of_v<T, ll_char_t, ll_uchar_t, ll_wchar_t, char16_t, char32_t>;

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_of_a_basic_type_v =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::traits::is_primitive_v<Args> || ...);
#else
	::std::disjunction_v<::llcpp::meta::traits::is_primitive_v<Args>...>;
#endif // __LL_REAL_CXX17 == 1

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_all_of_a_basic_type_v =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::traits::is_any_primitive_v<Args> || ...);
#else
	::std::disjunction_v<::llcpp::meta::traits::is_any_primitive_v<Args>...>;
#endif // __LL_REAL_CXX17 == 1

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_any_of_a_floating_type_v =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::traits::is_floating_type_v<Args> || ...);
#else
	::std::disjunction_v<::llcpp::meta::traits::is_floating_type_v<Args>...>;
#endif // __LL_REAL_CXX17 == 1

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_all_of_a_floating_type_v =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::traits::is_any_floating_v<Args> || ...);
#else
	::std::disjunction_v<::llcpp::meta::traits::is_any_floating_v<Args>...>;
#endif // __LL_REAL_CXX17 == 1

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_trivial_v =
	::llcpp::meta::traits::is_any_primitive_v<T>
	|| ::llcpp::meta::traits::is_any_floating_v<T>;

// [TOCHECK] [TODO]
//template<class _T>
//__LL_VAR_INLINE__ constexpr ll_bool_t is_raw_type =
//	::llcpp::meta::traits::is_primitive_v<_T>
//	|| ::std::is_class_v<_T>;

template<class T>
using input = ::llcpp::meta::traits::conditional_t<::std::is_class_v<T> && !::std::is_pointer_v<T>, T&, T>;
template<class T>
using ref_or_ptr = ::llcpp::meta::traits::conditional_t<::std::is_pointer_v<T> || ::llcpp::meta::traits::is_trivial_v<T>, T, T&>;
template<class T>
using cinput = ::llcpp::meta::traits::conditional_t<::std::is_class_v<T> && !::std::is_pointer_v<T>, const T&, const T>;

template<class T>
using pointer_t			= T*;
template<class T>
using const_pointer_t	= T*;

template<class T, class U>
__LL_VAR_INLINE__ constexpr ll_bool_t  is_same_no_const_conversion_v =
	::std::is_same_v<T, U> || (::std::is_const_v<T> && ::std::is_same_v<::std::remove_const_t<T>, U>);

template<class T, class U>
__LL_VAR_INLINE__ constexpr ll_bool_t  is_same_or_const_conversion_v =
	::std::is_const_v<U> && ::std::is_same_v<T, ::std::remove_const_t<U>>;

template<class T, class U>
__LL_VAR_INLINE__ constexpr ll_bool_t  is_same_any_const_conversion_v =
	::std::is_same_v<T, U> || ::std::is_same_v<::std::remove_const_t<T>, ::std::remove_const_t<U>>;

#if __LL_INCLUDE_KATS == 1
namespace kat {

#pragma region Empty
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_EMPTY_OBJECT =
	    ::llcpp::meta::traits::is_empty_object_v<::llcpp::Emptyclass>	// Empty
	&& !::llcpp::meta::traits::is_empty_object_v<void>					// Classic void
	&& !::llcpp::meta::traits::is_empty_object_v<i8>					// Signed char
	&& !::llcpp::meta::traits::is_empty_object_v<u8>					// Unsigned char
	&& !::llcpp::meta::traits::is_empty_object_v<char16_t>				// char 16 bits
	&& !::llcpp::meta::traits::is_empty_object_v<char32_t>				// char 32 bits
	&& !::llcpp::meta::traits::is_empty_object_v<i32>					// Primitive signed
	&& !::llcpp::meta::traits::is_empty_object_v<u32>					// Primitive unsigned
	&& !::llcpp::meta::traits::is_empty_object_v<f32>					// Floating-point
	&& !::llcpp::meta::traits::is_empty_object_v<i128>					// Primitive big signed
	&& !::llcpp::meta::traits::is_empty_object_v<u128>					// Primitive big unsigned
	&& !::llcpp::meta::traits::is_empty_object_v<f128>					// Floating-point big
	&& !::llcpp::meta::traits::is_empty_object_v<::llcpp::DummyClass>;	// Any class
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_empty_object_kat,
	::llcpp::meta::traits::kat::IS_WORKING_IS_EMPTY_OBJECT,
	"'Is Empty object'" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_EMPTY_TYPE =
	    ::llcpp::meta::traits::is_empty_type_v<::llcpp::Emptyclass>		// Empty
	&&  ::llcpp::meta::traits::is_empty_type_v<void>					// Classic void
	&& !::llcpp::meta::traits::is_empty_type_v<i8>						// Signed char
	&& !::llcpp::meta::traits::is_empty_type_v<u8>						// Unsigned char
	&& !::llcpp::meta::traits::is_empty_type_v<char16_t>				// char 16 bits
	&& !::llcpp::meta::traits::is_empty_type_v<char32_t>				// char 32 bits
	&& !::llcpp::meta::traits::is_empty_type_v<i32>						// Primitive signed
	&& !::llcpp::meta::traits::is_empty_type_v<u32>						// Primitive unsigned
	&& !::llcpp::meta::traits::is_empty_type_v<f32>						// Floating-point
	&& !::llcpp::meta::traits::is_empty_type_v<i128>					// Primitive big signed
	&& !::llcpp::meta::traits::is_empty_type_v<u128>					// Primitive big unsigned
	&& !::llcpp::meta::traits::is_empty_type_v<f128>					// Floating-point big
	&& !::llcpp::meta::traits::is_empty_type_v<::llcpp::DummyClass>;	// Any class
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_empty_type_kat,
	::llcpp::meta::traits::kat::IS_WORKING_IS_EMPTY_TYPE,
	"'Is Empty type'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region Primitives
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_PRIMITIVE_TYPE =
	   !::llcpp::meta::traits::is_primitive_v<::llcpp::Emptyclass>		// Empty
	&& !::llcpp::meta::traits::is_primitive_v<void>						// Classic void
	&&  ::llcpp::meta::traits::is_primitive_v<i8>						// Signed char
	&&  ::llcpp::meta::traits::is_primitive_v<u8>						// Unsigned char
	&&  ::llcpp::meta::traits::is_primitive_v<char16_t>					// char 16 bits
	&&  ::llcpp::meta::traits::is_primitive_v<char32_t>					// char 32 bits
	&&  ::llcpp::meta::traits::is_primitive_v<i32>						// Primitive signed
	&&  ::llcpp::meta::traits::is_primitive_v<u32>						// Primitive unsigned
	&& !::llcpp::meta::traits::is_primitive_v<f32>						// Floating-point
	&& !::llcpp::meta::traits::is_primitive_v<i128>						// Primitive big signed
	&& !::llcpp::meta::traits::is_primitive_v<u128>						// Primitive big unsigned
	&& !::llcpp::meta::traits::is_primitive_v<f128>						// Floating-point big
	&& !::llcpp::meta::traits::is_primitive_v<::llcpp::DummyClass>;		// Any class
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_primitive_type_kat,
	::llcpp::meta::traits::kat::IS_WORKING_IS_PRIMITIVE_TYPE,
	"'Is Primitive'" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_BIG_PRIMITIVE_TYPE =
	   !::llcpp::meta::traits::is_primitive_big_v<::llcpp::Emptyclass>	// Empty
	&& !::llcpp::meta::traits::is_primitive_big_v<void>					// Classic void
	&& !::llcpp::meta::traits::is_primitive_big_v<i8>					// Signed char
	&& !::llcpp::meta::traits::is_primitive_big_v<u8>					// Unsigned char
	&& !::llcpp::meta::traits::is_primitive_big_v<char16_t>				// char 16 bits
	&& !::llcpp::meta::traits::is_primitive_big_v<char32_t>				// char 32 bits
	&& !::llcpp::meta::traits::is_primitive_big_v<i32>					// Primitive signed
	&& !::llcpp::meta::traits::is_primitive_big_v<u32>					// Primitive unsigned
	&& !::llcpp::meta::traits::is_primitive_big_v<f32>					// Floating-point
	&&  ::llcpp::meta::traits::is_primitive_big_v<i128>					// Primitive big signed
	&&  ::llcpp::meta::traits::is_primitive_big_v<u128>					// Primitive big unsigned
	&& !::llcpp::meta::traits::is_primitive_big_v<f128>					// Floating-point big
	&& !::llcpp::meta::traits::is_primitive_big_v<::llcpp::DummyClass>;	// Any class
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_big_primitive_type_kat,
	::llcpp::meta::traits::kat::IS_WORKING_IS_BIG_PRIMITIVE_TYPE,
	"'Is big primitive'" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_ANY_PRIMITIVE_TYPE =
	   !::llcpp::meta::traits::is_any_primitive_v<::llcpp::Emptyclass>	// Empty
	&& !::llcpp::meta::traits::is_any_primitive_v<void>					// Classic void
	&&  ::llcpp::meta::traits::is_any_primitive_v<i8>					// Signed char
	&&  ::llcpp::meta::traits::is_any_primitive_v<u8>					// Unsigned char
	&&  ::llcpp::meta::traits::is_any_primitive_v<char16_t>				// char 16 bits
	&&  ::llcpp::meta::traits::is_any_primitive_v<char32_t>				// char 32 bits
	&&  ::llcpp::meta::traits::is_any_primitive_v<i32>					// Primitive signed
	&&  ::llcpp::meta::traits::is_any_primitive_v<u32>					// Primitive unsigned
	&& !::llcpp::meta::traits::is_any_primitive_v<f32>					// Floating-point
	&&  ::llcpp::meta::traits::is_any_primitive_v<i128>					// Primitive big signed
	&&  ::llcpp::meta::traits::is_any_primitive_v<u128>					// Primitive big unsigned
	&& !::llcpp::meta::traits::is_any_primitive_v<f128>					// Floating-point big
	&& !::llcpp::meta::traits::is_any_primitive_v<::llcpp::DummyClass>;	// Any class
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_any_primitive_type_kat,
	::llcpp::meta::traits::kat::IS_WORKING_IS_ANY_PRIMITIVE_TYPE,
	"'Is any primitive'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region Floating-point
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_FLOATING_TYPE =
	   !::llcpp::meta::traits::is_floating_type_v<::llcpp::Emptyclass>			// Empty
	&& !::llcpp::meta::traits::is_floating_type_v<void>							// Classic void
	&& !::llcpp::meta::traits::is_floating_type_v<i8>							// Signed char
	&& !::llcpp::meta::traits::is_floating_type_v<u8>							// Unsigned char
	&& !::llcpp::meta::traits::is_floating_type_v<char16_t>						// char 16 bits
	&& !::llcpp::meta::traits::is_floating_type_v<char32_t>						// char 32 bits
	&& !::llcpp::meta::traits::is_floating_type_v<i32>							// Primitive signed
	&& !::llcpp::meta::traits::is_floating_type_v<u32>							// Primitive unsigned
	&&  ::llcpp::meta::traits::is_floating_type_v<f32>							// Floating-point
	&& !::llcpp::meta::traits::is_floating_type_v<i128>							// Primitive big signed
	&& !::llcpp::meta::traits::is_floating_type_v<u128>							// Primitive big unsigned
	&&  ::llcpp::meta::traits::is_floating_type_v<f128>							// Floating-point big
	&& !::llcpp::meta::traits::is_floating_type_v<::llcpp::DummyClass>;			// Any class
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_floating_type_kat,
	::llcpp::meta::traits::kat::IS_WORKING_IS_FLOATING_TYPE,
	"'Is floating-point'" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_BIG_FLOATING_TYPE =
	   !::llcpp::meta::traits::is_floating_bigger_type_v<::llcpp::Emptyclass>	// Empty
	&& !::llcpp::meta::traits::is_floating_bigger_type_v<void>					// Classic void
	&& !::llcpp::meta::traits::is_floating_bigger_type_v<i8>					// Signed char
	&& !::llcpp::meta::traits::is_floating_bigger_type_v<u8>					// Unsigned char
	&& !::llcpp::meta::traits::is_floating_bigger_type_v<char16_t>				// char 16 bits
	&& !::llcpp::meta::traits::is_floating_bigger_type_v<char32_t>				// char 32 bits
	&& !::llcpp::meta::traits::is_floating_bigger_type_v<i32>					// Primitive signed
	&& !::llcpp::meta::traits::is_floating_bigger_type_v<u32>					// Primitive unsigned
	&& !::llcpp::meta::traits::is_floating_bigger_type_v<f32>					// Floating-point
	&& !::llcpp::meta::traits::is_floating_bigger_type_v<i128>					// Primitive big signed
	&& !::llcpp::meta::traits::is_floating_bigger_type_v<u128>					// Primitive big unsigned
	&&  ::llcpp::meta::traits::is_floating_bigger_type_v<f128>					// Floating-point big
	&& !::llcpp::meta::traits::is_floating_bigger_type_v<::llcpp::DummyClass>;	// Any class
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_big_floating_type_kat,
	::llcpp::meta::traits::kat::IS_WORKING_IS_BIG_FLOATING_TYPE,
	"'Is big floating-point'" __LL_IS_NOT_WORKING_STR
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_ANY_FLOATING_TYPE =
	   !::llcpp::meta::traits::is_any_floating_v<::llcpp::Emptyclass>			// Empty
	&& !::llcpp::meta::traits::is_any_floating_v<void>							// Classic void
	&& !::llcpp::meta::traits::is_any_floating_v<i8>							// Signed char
	&& !::llcpp::meta::traits::is_any_floating_v<u8>							// Unsigned char
	&& !::llcpp::meta::traits::is_any_floating_v<char16_t>						// char 16 bits
	&& !::llcpp::meta::traits::is_any_floating_v<char32_t>						// char 32 bits
	&& !::llcpp::meta::traits::is_any_floating_v<i32>							// Primitive signed
	&& !::llcpp::meta::traits::is_any_floating_v<u32>							// Primitive unsigned
	&&  ::llcpp::meta::traits::is_any_floating_v<f32>							// Floating-point
	&& !::llcpp::meta::traits::is_any_floating_v<i128>							// Primitive big signed
	&& !::llcpp::meta::traits::is_any_floating_v<u128>							// Primitive big unsigned
	&&  ::llcpp::meta::traits::is_any_floating_v<f128>							// Floating-point big
	&& !::llcpp::meta::traits::is_any_floating_v<::llcpp::DummyClass>;			// Any class
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_any_floating_type_kat,
	::llcpp::meta::traits::kat::IS_WORKING_IS_ANY_FLOATING_TYPE,
	"'Is any floating-point'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_CHAR_TYPE =
	   !::llcpp::meta::traits::is_char_type_v<::llcpp::Emptyclass>			// Empty
	&& !::llcpp::meta::traits::is_char_type_v<void>							// Classic void
	&&  ::llcpp::meta::traits::is_char_type_v<i8>							// Signed char
	&&  ::llcpp::meta::traits::is_char_type_v<u8>							// Unsigned char
	&&  ::llcpp::meta::traits::is_char_type_v<char16_t>						// char 16 bits
	&&  ::llcpp::meta::traits::is_char_type_v<char32_t>						// char 32 bits
	&& !::llcpp::meta::traits::is_char_type_v<i32>							// Primitive signed
	&& !::llcpp::meta::traits::is_char_type_v<u32>							// Primitive unsigned
	&& !::llcpp::meta::traits::is_char_type_v<f32>							// Floating-point
	&& !::llcpp::meta::traits::is_char_type_v<i128>							// Primitive big signed
	&& !::llcpp::meta::traits::is_char_type_v<u128>							// Primitive big unsigned
	&& !::llcpp::meta::traits::is_char_type_v<f128>							// Floating-point big
	&& !::llcpp::meta::traits::is_char_type_v<::llcpp::DummyClass>;			// Any class
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_char_type_kat,
	::llcpp::meta::traits::kat::IS_WORKING_IS_CHAR_TYPE,
	"'Is char type'" __LL_IS_NOT_WORKING_STR
);


__LL_NODISCARD__ constexpr ::llcpp::string type_traits_extended_kats() noexcept {
	::llcpp::string result = ::llcpp::meta::traits::kat::is_working_is_empty_object_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_is_empty_type_kat();
	if(result) return result;

	result = ::llcpp::meta::traits::kat::is_working_is_primitive_type_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_is_big_primitive_type_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_is_any_primitive_type_kat();
	if(result) return result;

	result = ::llcpp::meta::traits::kat::is_working_is_floating_type_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_is_big_floating_type_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_is_any_floating_type_kat();
	if(result) return result;

	result = ::llcpp::meta::traits::kat::is_working_is_char_type_kat();
	if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::traits::kat::type_traits_extended_kats() == LL_NULLPTR, "type_traits_extended KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSBASE_HPP_

#if !defined(LLANYLIB_TRAITSBASE_EXTRA_HPP_) && !defined(LLANYLIB_ERROR_HPP_)
#define LLANYLIB_TRAITSBASE_EXTRA_HPP_

namespace llcpp {
namespace meta {
namespace traits {
	
} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSBASE_EXTRA_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
