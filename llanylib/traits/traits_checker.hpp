//////////////////////////////////////////////
//	traits_checker.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSCHECKER_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSCHECKER_MAYOR_ != 10 || LLANYLIB_TRAITSCHECKER_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_checker.hpp version error!"
		#else
			#error "traits_checker.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSCHECKER_MAYOR_ || LLANYLIB_TRAITSCHECKER_MINOR_

#else !defined(LLANYLIB_TRAITSCHECKER_HPP_)
#define LLANYLIB_TRAITSCHECKER_HPP_
#define LLANYLIB_TRAITSCHECKER_MAYOR_ 10
#define LLANYLIB_TRAITSCHECKER_MINOR_ 0

#include "traits_base.hpp"

namespace llcpp {
namespace meta {
namespace traits {

// Standard checker for types in this lib
template<
	class _T,
	ll_bool_t _IGNORE_POINTER = llcpp::FALSE,
	ll_bool_t _IGNORE_ARRAY = llcpp::FALSE,
	ll_bool_t _IGNORE_VOLATILE = llcpp::FALSE
>
struct type_checker {
	// Class related
	using _MyType	= type_checker;

	// Types and enums
	using T			= _T;

	// Expresions
	static constexpr ll_bool_t IGNORE_POINTER	= _IGNORE_POINTER;
	static constexpr ll_bool_t IGNORE_ARRAY		= _IGNORE_ARRAY;
	static constexpr ll_bool_t IGNORE_VOLATILE	= _IGNORE_VOLATILE;
	static constexpr ll_bool_t POINTER			= (IGNORE_POINTER	|| !std::is_pointer_v<T>);
	static constexpr ll_bool_t ARRAY			= (IGNORE_ARRAY		|| !std::is_array_v<T>);
	static constexpr ll_bool_t VOLATILE			= (IGNORE_VOLATILE	|| !std::is_volatile_v<T>);
	static constexpr ll_bool_t is_valid_v =
		!std::is_const_v<T> &&
		!std::is_reference_v<T> &&
		ARRAY &&
		VOLATILE &&
		POINTER;

	// Asserts
	static_assert(!std::is_reference_v<T>,	"Reference type is forbidden!");
	static_assert(!std::is_const_v<T>,		"Const type is forbidden!");
	static_assert(POINTER,					"Pointer type is forbidden!");
	static_assert(ARRAY,					"Array type is forbidden!");
	static_assert(VOLATILE,					"Volatile type is forbidden!");
};

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_type_checker_v = 
	traits::type_checker<T>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_type_checker_ignore_pointer_v = 
	traits::type_checker<T, llcpp::TRUE, llcpp::FALSE, llcpp::FALSE>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_type_checker_ignore_array_v = 
	traits::type_checker<T, llcpp::FALSE, llcpp::TRUE, llcpp::FALSE>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_type_checker_ignore_pa_v = 
	traits::type_checker<T, llcpp::TRUE, llcpp::TRUE, llcpp::FALSE>::is_valid_v;

// Standard checker for classes and objects
// Checks contruction / destruction and other operations needed
template<
	class _T,
	ll_bool_t _IGNORE_CONSTRUCTIBLE = llcpp::FALSE,
	ll_bool_t _IGNORE_COPY_CONSTRUCTIBLE = llcpp::FALSE,
	ll_bool_t _IGNORE_COPY_ASSIGNABLE = llcpp::FALSE,
	ll_bool_t _IGNORE_MOVE_CONSTRUCTIBLE = llcpp::FALSE,
	ll_bool_t _IGNORE_MOVE_ASSIGNABLE = llcpp::FALSE
>
struct constructor_checker {
	// Class related
	using _MyType	= constructor_checker;

	// Types and enums
	using T			= _T;

	// Expresions
	static constexpr ll_bool_t IGNORE_CONSTRUCTIBLE			= _IGNORE_CONSTRUCTIBLE;
	static constexpr ll_bool_t IGNORE_COPY_CONSTRUCTIBLE	= _IGNORE_COPY_CONSTRUCTIBLE;
	static constexpr ll_bool_t IGNORE_COPY_ASSIGNABLE		= _IGNORE_COPY_ASSIGNABLE;
	static constexpr ll_bool_t IGNORE_MOVE_CONSTRUCTIBLE	= _IGNORE_MOVE_CONSTRUCTIBLE;
	static constexpr ll_bool_t IGNORE_MOVE_ASSIGNABLE		= _IGNORE_MOVE_ASSIGNABLE;

	static constexpr ll_bool_t CONSTRUCTIBLE		= IGNORE_CONSTRUCTIBLE || std::is_nothrow_constructible_v<T>;
	static constexpr ll_bool_t COPY_CONSTRUCTIBLE	= IGNORE_COPY_CONSTRUCTIBLE || std::is_nothrow_copy_constructible_v<T>;
	static constexpr ll_bool_t COPY_ASSIGNABLE		= IGNORE_COPY_ASSIGNABLE || std::is_nothrow_copy_assignable_v<T>;
	static constexpr ll_bool_t MOVE_CONSTRUCTIBLE	= IGNORE_MOVE_CONSTRUCTIBLE || std::is_nothrow_move_constructible_v<T>;
	static constexpr ll_bool_t MOVE_ASSIGNABLE		= IGNORE_MOVE_ASSIGNABLE || std::is_nothrow_move_assignable_v<T>;

	static constexpr ll_bool_t is_valid_v =
		CONSTRUCTIBLE
		&& std::is_nothrow_destructible_v<T>
		&& COPY_CONSTRUCTIBLE
		&& COPY_ASSIGNABLE
		&& MOVE_CONSTRUCTIBLE
		&& MOVE_ASSIGNABLE;

	// Asserts
	static_assert(CONSTRUCTIBLE,						"T needs a noexcept constructor!");
	static_assert(std::is_nothrow_destructible_v<T>,	"T needs a noexcept destructor!");
	static_assert(COPY_CONSTRUCTIBLE,					"T needs a noexcept copy constructor!");
	static_assert(COPY_ASSIGNABLE,						"T needs a noexcept copy asignable!");
	static_assert(MOVE_CONSTRUCTIBLE,					"T needs a noexcept move constructor!");
	static_assert(MOVE_ASSIGNABLE,						"T needs a noexcept move asignable!");
};

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_v = 
	traits::constructor_checker<T>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_ignore_constructor_v = 
	traits::constructor_checker<T, llcpp::TRUE>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_ignore_copy_constructor_v = 
	traits::constructor_checker<T, llcpp::FALSE, llcpp::TRUE>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_ignore_copy_assignable_v = 
	traits::constructor_checker<T, llcpp::FALSE, llcpp::FALSE, llcpp::TRUE>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_ignore_move_constructor_v = 
	traits::constructor_checker<T, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::TRUE>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_ignore_move_assignable_v = 
	traits::constructor_checker<T, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::TRUE>::is_valid_v;


template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_ignore_copy_v = 
	traits::constructor_checker<T, llcpp::FALSE, llcpp::TRUE, llcpp::TRUE, llcpp::FALSE, llcpp::FALSE>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_ignore_move_v = 
	traits::constructor_checker<T, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::TRUE, llcpp::TRUE>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_ignore_constructors_v = 
	traits::constructor_checker<T, llcpp::TRUE, llcpp::TRUE, llcpp::FALSE, llcpp::TRUE, llcpp::FALSE>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_ignore_assignable_v = 
	traits::constructor_checker<T, llcpp::FALSE, llcpp::FALSE, llcpp::TRUE, llcpp::FALSE, llcpp::TRUE>::is_valid_v;

template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_ignore_all_v = 
	traits::constructor_checker<T, llcpp::TRUE, llcpp::TRUE, llcpp::TRUE, llcpp::TRUE, llcpp::TRUE>::is_valid_v;

/*template<class _T>
struct is_nothrow_swappeable {
	// Class related
	using _MyType = is_nothrow_swappeable;

	// Types and enums
	using T = _T;

	// Asserts
	static_assert(traits::is_valid_type_checker_v<T>,
		"type_checker<T> detected an invalid type!");
	static_assert(traits::is_valid_constructor_checker_v<T>,
		"class_checker<T> detected an invalid class type!");

	// Functions
	static constexpr auto test() noexcept {
		if constexpr (std::is_pointer_v<T> || traits::is_basic_type_v<T>)
			return std::true_type{};
		else if constexpr (std::is_array_v<T>)
			return is_nothrow_swappeable<traits::array_type_t<T>>::test();
		// Already includes basic types
		else if constexpr (std::is_move_constructible_v<T> && std::is_move_assignable_v<T>) {
			if constexpr (std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>)
				return std::true_type{};
			else return std::false_type{};
		}
		else return std::false_type{};
	}
	using type = decltype(test());
};
template<class T>
using is_nothrow_swappeable_t = is_nothrow_swappeable<T>::type;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_nothrow_swappeable_v = is_nothrow_swappeable_t<T>::value;

template<class _T>
struct is_nothrow_copyable {
	// Class related
	using _MyType = is_nothrow_copyable;

	// Types and enums
	using T = _T;

	// Asserts
	static_assert(traits::is_valid_type_checker_v<T>,
		"type_checker<T> detected an invalid type!");
	static_assert(traits::is_valid_constructor_checker_v<T>,
		"class_checker<T> detected an invalid class type!");

	// Functions
	static constexpr auto test() noexcept {
		if constexpr (std::is_pointer_v<T>) {
			using __noptr = std::remove_pointer_t<T>;
			if constexpr (std::is_pointer_v<__noptr>) return std::false_type{};
			else return is_nothrow_copyable<__noptr>::test();
		}
		else if constexpr (std::is_array_v<T>)
			return is_nothrow_copyable<traits::array_type_t<T>>::test();
		// Already includes basic types
		else if constexpr (std::is_copy_assignable_v<T> && std::is_nothrow_copy_assignable_v<T>)
			return std::true_type{};
		else return std::false_type{};
	}
	using type = decltype(test());
};
template<class T>
using is_nothrow_copyable_t = is_nothrow_copyable<T>::type;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_nothrow_copyable_v = is_nothrow_copyable_t<T>::value;*/

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSCHECKER_HPP_
