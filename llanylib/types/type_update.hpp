//////////////////////////////////////////////
//	type_update.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TYPEUPDATE_INCOMPLETE_HPP_)
	#if LLANYLIB_TYPEUPDATE_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_TYPEUPDATE_INCOMPLETE_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "type_update.hpp(incomplete) version error!"
		#else
			#error "type_update.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPEUPDATE_INCOMPLETE_MAYOR_ || LLANYLIB_TYPEUPDATE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TYPEUPDATE_INCOMPLETE_HPP_)
	#define LLANYLIB_TYPEUPDATE_INCOMPLETE_HPP_
	#define LLANYLIB_TYPEUPDATE_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_TYPEUPDATE_INCOMPLETE_MINOR_ 0

#include "types.hpp"

namespace llcpp {
namespace meta {
namespace traits {

struct type_update_t;

} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TYPEUPDATE_HPP_)
	#if LLANYLIB_TYPEUPDATE_MAYOR_ != 12 || LLANYLIB_TYPEUPDATE_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "type_update.hpp version error!"
		#else
			#error "type_update.hpp version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPEUPDATE_MAYOR_ || LLANYLIB_TYPEUPDATE_MINOR_

#else
	#define LLANYLIB_TYPEUPDATE_HPP_
	#define LLANYLIB_TYPEUPDATE_MAYOR_ 12
	#define LLANYLIB_TYPEUPDATE_MINOR_ 0

#include "types.hpp"

namespace llcpp {
namespace meta {
namespace attributes {

struct type_update_t {
	// Class related
	using _MyType = type_update_t;

	// Attributes
	ll_bool_t REMOVE_POINTER	: 1;
	ll_bool_t REMOVE_CONST		: 1;
	ll_bool_t REMOVE_VOLATILE	: 1;
	ll_bool_t REMOVE_ARRAY		: 1;
	ll_bool_t REMOVE_REFERENCE	: 1;
	ll_bool_t REMOVE_CONTAINER	: 1;

	constexpr ll_bool_t operator==(const _MyType& other) const noexcept {
		return
			this->REMOVE_POINTER == other.REMOVE_POINTER
			&& this->REMOVE_CONST == other.REMOVE_CONST
			&& this->REMOVE_VOLATILE == other.REMOVE_VOLATILE
			&& this->REMOVE_ARRAY == other.REMOVE_ARRAY
			&& this->REMOVE_REFERENCE == other.REMOVE_REFERENCE
			&& this->REMOVE_CONTAINER == other.REMOVE_CONTAINER;
	}

	template<ll_bool_t REMOVE_POINTER, ll_bool_t REMOVE_CONST, ll_bool_t REMOVE_VOLATILE, ll_bool_t REMOVE_ARRAY, ll_bool_t REMOVE_REFERENCE, ll_bool_t REMOVE_CONTAINER>
	static constexpr _MyType CUSTOM = { REMOVE_POINTER, REMOVE_CONST, REMOVE_VOLATILE, REMOVE_ARRAY, REMOVE_REFERENCE, REMOVE_CONTAINER };
};

namespace update {

using _MyType = ::llcpp::meta::attributes::type_update_t::_MyType;

//														Pointer				Const			Volatile		Array			Reference
__LL_VAR_INLINE__ constexpr _MyType REMOVE_CONSTS	= { ::llcpp::LL_FALSE, ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType REMOVE_POINTERS	= { ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType REMOVE_ARRAYS	= { ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType REMOVE_VOLATILE	= { ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_TRUE,  ::llcpp::LL_FALSE, ::llcpp::LL_FALSE, ::llcpp::LL_FALSE };
__LL_VAR_INLINE__ constexpr _MyType RAW_TYPE		= { ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE,  ::llcpp::LL_TRUE  };

} // namespace update

} // namespace attributes
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPEUPDATE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
