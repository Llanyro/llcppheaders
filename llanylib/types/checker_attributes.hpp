//////////////////////////////////////////////
//	checker_attributes.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_HPP_)
	#if LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "checker_attributes.hpp(incomplete) version error!"
		#else
			#error "checker_attributes.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MAYOR_ || LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_HPP_)
	#define LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_HPP_
	#define LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_CHECKERATTRIBUTES_INCOMPLETE_MINOR_ 0

#include "types.hpp"

namespace llcpp {
namespace meta {
namespace attributes {

struct checker_attributes_t;

} // namespace attributes
} // namespace meta
} // namespace llcpp


#elif defined(LLANYLIB_CHECKERATTRIBUTES_HPP_)
	#if LLANYLIB_CHECKERATTRIBUTES_MAYOR_ != 12 || LLANYLIB_CHECKERATTRIBUTES_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "checker_attributes.hpp version error!"
		#else
			#error "checker_attributes.hpp version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CHECKERATTRIBUTES_MAYOR_ || LLANYLIB_CHECKERATTRIBUTES_MINOR_

#else
	#define LLANYLIB_CHECKERATTRIBUTES_HPP_
	#define LLANYLIB_CHECKERATTRIBUTES_MAYOR_ 12
	#define LLANYLIB_CHECKERATTRIBUTES_MINOR_ 0

#include "types.hpp"

namespace llcpp {
namespace meta {
namespace attributes {

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
	ll_bool_t IGNORE_ASSIGNABLE			: 1;
	ll_bool_t IGNORE_NOEXCEPT_DESTRUCT	: 1;

	constexpr ll_bool_t operator==(const _MyType& other) const noexcept {
		return
			this->IGNORE_POINTER == other.IGNORE_POINTER
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
