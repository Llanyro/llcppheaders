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

struct checker_attributes_t {
	// Class related
	using _MyType						= checker_attributes_t;

	// Attributes
	ll_bool_t IGNORE_POINTER			: 1;
	ll_bool_t IGNORE_ARRAY				: 1;
	ll_bool_t IGNORE_VOLATILE			: 1;
	ll_bool_t IGNORE_CONST				: 1;
	ll_bool_t IGNORE_REFERENCE			: 1;

	ll_bool_t IGNORE_CONSTRUCTIBLE		: 1;
	ll_bool_t IGNORE_COPY_CONSTRUCTIBLE	: 1;
	ll_bool_t IGNORE_COPY_ASSIGNABLE	: 1;
	ll_bool_t IGNORE_MOVE_CONSTRUCTIBLE	: 1;
	ll_bool_t IGNORE_MOVE_ASSIGNABLE	: 1;
};

namespace checker {
//																				Pointer			Array		Volatile		Const		 Reference		Construct	CopyConstruct CopyAssign	MoveConstruct	MoveAssig
__LL_VAR_INLINE__ constexpr traits::checker_attributes_t DEFAULT			= { llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr traits::checker_attributes_t IGNORE_POINTER		= { llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr traits::checker_attributes_t IGNORE_ARRAY		= { llcpp::FALSE, llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr traits::checker_attributes_t IGNORE_CONST		= { llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::TRUE,	llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr traits::checker_attributes_t IGNORE_VOLATILE	= { llcpp::FALSE, llcpp::FALSE, llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr traits::checker_attributes_t IGNORE_PA			= { llcpp::TRUE,  llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr traits::checker_attributes_t IGNORE_CPA			= { llcpp::TRUE,  llcpp::TRUE,  llcpp::FALSE, llcpp::TRUE,	llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr traits::checker_attributes_t IGNORE_CP			= { llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::TRUE,	llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };

} // namespace checker

// Standard checker for types in this lib
template<class _T, traits::checker_attributes_t _ATTRIBUTES>
struct type_checker {
	// Class related
	using _MyType	= type_checker;

	// Types and enums
	using T			= _T;

	// Expresions
	static constexpr traits::checker_attributes_t ATTRIBUTES = _ATTRIBUTES;
	static constexpr ll_bool_t CONST			= (ATTRIBUTES.IGNORE_CONST		|| !std::is_const_v<T>);
	static constexpr ll_bool_t REFERENCE		= (ATTRIBUTES.IGNORE_REFERENCE	|| !std::is_reference_v<T>);
	static constexpr ll_bool_t POINTER			= (ATTRIBUTES.IGNORE_POINTER	|| !std::is_pointer_v<T>);
	static constexpr ll_bool_t ARRAY			= (ATTRIBUTES.IGNORE_ARRAY		|| !std::is_array_v<T>);
	static constexpr ll_bool_t VOLATILE			= (ATTRIBUTES.IGNORE_VOLATILE	|| !std::is_volatile_v<T>);

	static constexpr ll_bool_t is_valid_v = CONST && REFERENCE && ARRAY && VOLATILE && POINTER;

	// Asserts
	static_assert(!std::is_reference_v<T>,	"Reference type is forbidden!");
	static_assert(!std::is_const_v<T>,		"Const type is forbidden!");
	static_assert(POINTER,					"Pointer type is forbidden!");
	static_assert(ARRAY,					"Array type is forbidden!");
	static_assert(VOLATILE,					"Volatile type is forbidden!");
};

template<class T, traits::checker_attributes_t ATTRIBUTES = checker::DEFAULT>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_type_checker_v = 
	traits::type_checker<T, ATTRIBUTES>::is_valid_v;

// Standard checker for classes and objects
// Checks contruction / destruction and other operations needed
template<class _T, traits::checker_attributes_t _ATTRIBUTES>
struct constructor_checker {
	// Class related
	using _MyType	= constructor_checker;

	// Types and enums
	using T			= _T;

	// Expresions
	static constexpr traits::checker_attributes_t ATTRIBUTES = _ATTRIBUTES;
	static constexpr ll_bool_t CONSTRUCTIBLE		= (ATTRIBUTES.IGNORE_CONSTRUCTIBLE		|| std::is_nothrow_constructible_v<T>);
	static constexpr ll_bool_t COPY_CONSTRUCTIBLE	= (ATTRIBUTES.IGNORE_COPY_CONSTRUCTIBLE	|| std::is_nothrow_copy_constructible_v<T>);
	static constexpr ll_bool_t COPY_ASSIGNABLE		= (ATTRIBUTES.IGNORE_COPY_ASSIGNABLE	|| std::is_nothrow_copy_assignable_v<T>);
	static constexpr ll_bool_t MOVE_CONSTRUCTIBLE	= (ATTRIBUTES.IGNORE_MOVE_CONSTRUCTIBLE	|| std::is_nothrow_move_constructible_v<T>);
	static constexpr ll_bool_t MOVE_ASSIGNABLE		= (ATTRIBUTES.IGNORE_MOVE_ASSIGNABLE	|| std::is_nothrow_move_assignable_v<T>);

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

template<class T, traits::checker_attributes_t ATTRIBUTES = checker::DEFAULT>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_v =
	traits::constructor_checker<T, ATTRIBUTES>::is_valid_v;

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
