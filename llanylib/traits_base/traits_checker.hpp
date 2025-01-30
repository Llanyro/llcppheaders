//////////////////////////////////////////////
//	traits_checker.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSCHECKER_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSCHECKER_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TRAITSCHECKER_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_checker.hpp(incomplete) version error!"
		#else
			#error "traits_checker.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSCHECKER_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSCHECKER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSCHECKER_INCOMPLETE_HPP_)
	#define LLANYLIB_TRAITSCHECKER_INCOMPLETE_HPP_
	#define LLANYLIB_TRAITSCHECKER_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_TRAITSCHECKER_INCOMPLETE_MINOR_ 0

#include "traits_base.hpp"
#undef LLANYLIB_INCOMPLETE_HPP_
#include "../types_base/checker_attributes.hpp"
#define LLANYLIB_INCOMPLETE_HPP_

namespace llcpp {
namespace meta {
namespace traits {

template<class _T, ::llcpp::meta::attributes::checker_attributes_t _ATTRIBUTES>
class TypeChecker;

template<class _T, ::llcpp::meta::attributes::checker_attributes_t _ATTRIBUTES>
class ConstructorChecker;

} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TRAITSCHECKER_HPP_)
	#if LLANYLIB_TRAITSCHECKER_MAYOR_ != 11 || LLANYLIB_TRAITSCHECKER_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_checker.hpp version error!"
		#else
			#error "traits_checker.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSCHECKER_MAYOR_ || LLANYLIB_TRAITSCHECKER_MINOR_

#else
	#define LLANYLIB_TRAITSCHECKER_HPP_
	#define LLANYLIB_TRAITSCHECKER_MAYOR_ 11
	#define LLANYLIB_TRAITSCHECKER_MINOR_ 0

#include "traits_base.hpp"
#include "../types_base/checker_attributes.hpp"

namespace llcpp {
namespace meta {
namespace traits {

#pragma region TypeChecker
// Standard checker for types in this lib
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _ATTRIBUTES>
class TypeChecker {
	public:
		// Class related
		using _MyType		= TypeChecker;

		// Types and enums
		using T				= _T;
		using type			= T;
		using value_type	= T;

	public:
		// Expresions
		static constexpr ::llcpp::meta::attributes::checker_attributes_t ATTRIBUTES	= _ATTRIBUTES;
		static constexpr ll_bool_t CONST			= (ATTRIBUTES.IGNORE_CONST		|| !::std::is_const_v<T>);
		static constexpr ll_bool_t REFERENCE		= (ATTRIBUTES.IGNORE_REFERENCE	|| !::std::is_reference_v<T>);
		static constexpr ll_bool_t POINTER			= (ATTRIBUTES.IGNORE_POINTER	|| !::std::is_pointer_v<T>);
		static constexpr ll_bool_t ARRAY			= (ATTRIBUTES.IGNORE_ARRAY		|| !::std::is_array_v<T>);
		static constexpr ll_bool_t VOLATILE			= (ATTRIBUTES.IGNORE_VOLATILE	|| !::std::is_volatile_v<T>);
		static constexpr ll_bool_t is_valid_v = CONST && REFERENCE && ARRAY && VOLATILE && POINTER;

	public:
		// Asserts
		static_assert(REFERENCE,"Reference type is forbidden!");
		static_assert(CONST,	"Const type is forbidden!");
		static_assert(POINTER,	"Pointer type is forbidden!");
		static_assert(ARRAY,	"Array type is forbidden!");
		static_assert(VOLATILE,	"Volatile type is forbidden!");
};

template<
	class T,
	::llcpp::meta::attributes::checker_attributes_t ATTRIBUTES =
		::llcpp::meta::attributes::checker::DEFAULT
>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_type_checker_v =
	::llcpp::meta::traits::TypeChecker<T, ATTRIBUTES>::is_valid_v;

#pragma endregion
#pragma region ClassChecker
// Standard checker for classes and objects
// Checks contruction / destruction and other operations needed
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _ATTRIBUTES>
class ConstructorChecker {
	public:
		// Class related
		using _MyType		= ConstructorChecker;

		// Types and enums
		using T				= _T;
		using type			= T;
		using value_type	= T;

	public:
		// Expresions
		static constexpr ::llcpp::meta::attributes::checker_attributes_t ATTRIBUTES = _ATTRIBUTES;
		static constexpr ll_bool_t CONSTRUCTIBLE		= (ATTRIBUTES.IGNORE_CONSTRUCTIBLE		|| std::is_nothrow_constructible_v<T>);
		static constexpr ll_bool_t COPY_CONSTRUCTIBLE	= (ATTRIBUTES.IGNORE_COPY_CONSTRUCTIBLE	|| std::is_nothrow_copy_constructible_v<T>);
		static constexpr ll_bool_t COPY_ASSIGNABLE		= (ATTRIBUTES.IGNORE_COPY_ASSIGNABLE	|| std::is_nothrow_copy_assignable_v<T>);
		static constexpr ll_bool_t MOVE_CONSTRUCTIBLE	= (ATTRIBUTES.IGNORE_MOVE_CONSTRUCTIBLE	|| std::is_nothrow_move_constructible_v<T>);
		static constexpr ll_bool_t MOVE_ASSIGNABLE		= (ATTRIBUTES.IGNORE_MOVE_ASSIGNABLE	|| std::is_nothrow_move_assignable_v<T>);
		static constexpr ll_bool_t NOEXCEPT_DESTRUCT	= (ATTRIBUTES.IGNORE_NOEXCEPT_DESTRUCT	|| std::is_nothrow_destructible_v<T>);

		static constexpr ll_bool_t is_valid_v =
			CONSTRUCTIBLE
			&& NOEXCEPT_DESTRUCT
			&& COPY_CONSTRUCTIBLE
			&& COPY_ASSIGNABLE
			&& MOVE_CONSTRUCTIBLE
			&& MOVE_ASSIGNABLE;

	public:
		// Asserts
		static_assert(CONSTRUCTIBLE,						"T needs a noexcept constructor!");
		static_assert(NOEXCEPT_DESTRUCT,					"T needs a noexcept destructor!");
		static_assert(COPY_CONSTRUCTIBLE,					"T needs a noexcept copy constructor!");
		static_assert(COPY_ASSIGNABLE,						"T needs a noexcept copy asignable!");
		static_assert(MOVE_CONSTRUCTIBLE,					"T needs a noexcept move constructor!");
		static_assert(MOVE_ASSIGNABLE,						"T needs a noexcept move asignable!");
};

template<class T, ::llcpp::meta::attributes::checker_attributes_t ATTRIBUTES = ::llcpp::meta::attributes::checker::DEFAULT>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_constructor_checker_v =
	::llcpp::meta::traits::ConstructorChecker<T, ATTRIBUTES>::is_valid_v;

#pragma endregion

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSCHECKER_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
