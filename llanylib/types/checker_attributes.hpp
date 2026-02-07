//////////////////////////////////////////////
//	checker_attributes.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 13.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_HPP_)
	#if LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MAYOR_ != 13 || LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "checker_attributes.hpp(incomplete) version error!"
		#else
			#error "checker_attributes.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MAYOR_ || LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_HPP_)
	#define LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_HPP_
	#define LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MAYOR_ 13
	#define LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/Comparations.hpp>
#else
	#include "Comparations.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace attributes {

struct checker_attributes_t;

} // namespace attributes
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_CHECKERATTRIBUTES_HPP_)
	#if LLANYLIB_CHECKERATTRIBUTES_MAYOR_ != 13 || LLANYLIB_CHECKERATTRIBUTES_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "checker_attributes.hpp version error!"
		#else
			#error "checker_attributes.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CHECKERATTRIBUTES_MAYOR_ || LLANYLIB_CHECKERATTRIBUTES_MINOR_

#else
	#define LLANYLIB_CHECKERATTRIBUTES_HPP_
	#define LLANYLIB_CHECKERATTRIBUTES_MAYOR_ 13
	#define LLANYLIB_CHECKERATTRIBUTES_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include "Comparations.hpp"
#else
	#include <llanylib/types/Comparations.hpp>
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace attributes {

struct checker_attributes_t {
	// Class related
	// Class related
	using _MyType		= checker_attributes_t;
	using T				= ll_bool_t;
	using type			= ll_bool_t;
	using value_type	= ll_bool_t;

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
	ll_bool_t IGNORE_ASSIGNABLE			: 1;
	ll_bool_t IGNORE_NOEXCEPT_DESTRUCT	: 1;

	template<::llcpp::comparations::Comparations CMP>
	__LL_NODISCARD__ constexpr ll_bool_t compare(const checker_attributes_t& other) const noexcept {
		if constexpr (CMP == ::llcpp::comparations::Comparations::Equals)
			return this->equals(other);
		else {
			static_assert(CMP == ::llcpp::comparations::Comparations::Equals,
				"Invalid compare value for this class");
			return ::llcpp::LL_FALSE;
		}
	}

	__LL_NODISCARD__ constexpr ll_bool_t equals(const checker_attributes_t& other) const noexcept {
		return this->operator==(other);
	}
	__LL_NODISCARD__ constexpr ll_bool_t operator==(const checker_attributes_t& other) const noexcept {
		return this->IGNORE_POINTER == other.IGNORE_POINTER
			&& this->IGNORE_ARRAY == other.IGNORE_ARRAY
			&& this->IGNORE_VOLATILE == other.IGNORE_VOLATILE
			&& this->IGNORE_CONST == other.IGNORE_CONST
			&& this->IGNORE_REFERENCE == other.IGNORE_REFERENCE

			&& this->IGNORE_CONSTRUCTIBLE == other.IGNORE_CONSTRUCTIBLE
			&& this->IGNORE_COPY_CONSTRUCTIBLE == other.IGNORE_COPY_CONSTRUCTIBLE
			&& this->IGNORE_COPY_ASSIGNABLE == other.IGNORE_COPY_ASSIGNABLE
			&& this->IGNORE_MOVE_CONSTRUCTIBLE == other.IGNORE_MOVE_CONSTRUCTIBLE
			&& this->IGNORE_MOVE_ASSIGNABLE == other.IGNORE_MOVE_ASSIGNABLE
			&& this->IGNORE_ASSIGNABLE == other.IGNORE_ASSIGNABLE
			&& this->IGNORE_NOEXCEPT_DESTRUCT == other.IGNORE_NOEXCEPT_DESTRUCT;
	}

	template<ll_bool_t IGNORE_POINTER, ll_bool_t IGNORE_ARRAY, ll_bool_t IGNORE_VOLATILE, ll_bool_t IGNORE_CONST, ll_bool_t IGNORE_REFERENCE>
	static constexpr _MyType CUSTOM_P1 = { IGNORE_POINTER, IGNORE_ARRAY, IGNORE_VOLATILE, IGNORE_CONST, IGNORE_REFERENCE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
	template<ll_bool_t IGNORE_CONSTRUCTIBLE, ll_bool_t IGNORE_COPY_CONSTRUCTIBLE, ll_bool_t IGNORE_COPY_ASSIGNABLE, ll_bool_t IGNORE_MOVE_CONSTRUCTIBLE, ll_bool_t IGNORE_MOVE_ASSIGNABLE, ll_bool_t IGNORE_ASSIGNABLE, ll_bool_t IGNORE_NOEXCEPT_DESTRUCT>
	static constexpr _MyType CUSTOM_P2 = { ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, IGNORE_CONSTRUCTIBLE, IGNORE_COPY_CONSTRUCTIBLE, IGNORE_COPY_ASSIGNABLE, IGNORE_MOVE_CONSTRUCTIBLE, IGNORE_MOVE_ASSIGNABLE, IGNORE_ASSIGNABLE, IGNORE_NOEXCEPT_DESTRUCT };
};

namespace checker {

using _MyType = ::llcpp::meta::attributes::checker_attributes_t::_MyType;

//															Pointer				Array			Volatile			Const		 		Reference			Construct		CopyConstruct	 	CopyAssign		 MoveConstruct	 		MoveAssig		 Noexcept destructible
__LL_VAR_INLINE__ constexpr _MyType DEFAULT			= { ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_POINTER	= { ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_ARRAY	= { ::llcpp::LL_FALSE, ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_CONST	= { ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_TRUE,	::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_VOLATILE	= { ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_PA		= { ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_PV		= { ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_PAV		= { ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_CPAV		= { ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_CPA		= { ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_TRUE,	::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_CP		= { ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_TRUE,	::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_CPV		= { ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE,	::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType IGNORE_DESTRUCT = { ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_TRUE  };

} // namespace checker

} // namespace attributes
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CHECKERATTRIBUTES_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
