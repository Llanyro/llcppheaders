//////////////////////////////////////////////
//	type_update.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TYPEUPDATE_INCOMPLETE_HPP_)
	#if LLANYLIB_TYPEUPDATE_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TYPEUPDATE_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "type_update.hpp(incomplete) version error!"
		#else
			#error "type_update.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPEUPDATE_INCOMPLETE_MAYOR_ || LLANYLIB_TYPEUPDATE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TYPEUPDATE_INCOMPLETE_HPP_)
#define LLANYLIB_TYPEUPDATE_INCOMPLETE_HPP_
#define LLANYLIB_TYPEUPDATE_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_TYPEUPDATE_INCOMPLETE_MINOR_ 0

#include "../types_base/types_base_extra.hpp"

namespace llcpp {
namespace meta {
namespace traits {

struct type_update_t;

} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TYPEUPDATE_HPP_)
	#if LLANYLIB_TYPEUPDATE_MAYOR_ != 11 || LLANYLIB_TYPEUPDATE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "type_update.hpp version error!"
		#else
			#error "type_update.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPEUPDATE_MAYOR_ || LLANYLIB_TYPEUPDATE_MINOR_

#else
#define LLANYLIB_TYPEUPDATE_HPP_
#define LLANYLIB_TYPEUPDATE_MAYOR_ 11
#define LLANYLIB_TYPEUPDATE_MINOR_ 0

#include "../types_base/types_base_extra.hpp"

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

	constexpr ll_bool_t operator==(const _MyType& other) const noexcept {
		return
			this->REMOVE_POINTER == other.REMOVE_POINTER
			&& this->REMOVE_CONST == other.REMOVE_CONST
			&& this->REMOVE_VOLATILE == other.REMOVE_VOLATILE
			&& this->REMOVE_ARRAY == other.REMOVE_ARRAY
			&& this->REMOVE_REFERENCE == other.REMOVE_REFERENCE;
	}

	template<ll_bool_t REMOVE_POINTER, ll_bool_t REMOVE_CONST, ll_bool_t REMOVE_VOLATILE, ll_bool_t REMOVE_ARRAY, ll_bool_t REMOVE_REFERENCE>
	static constexpr _MyType CUSTOM = { REMOVE_POINTER, REMOVE_CONST, REMOVE_VOLATILE, REMOVE_ARRAY, REMOVE_REFERENCE };
};

namespace update {

using _MyType = ::llcpp::meta::attributes::type_update_t::_MyType;

//														Pointer			Const		Volatile		Array		Reference
__LL_VAR_INLINE__ constexpr _MyType REMOVE_CONSTS	= { llcpp::FALSE, llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType REMOVE_POINTERS	= { llcpp::TRUE,  llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType REMOVE_ARRAYS	= { llcpp::FALSE, llcpp::FALSE, llcpp::FALSE, llcpp::TRUE,  llcpp::FALSE };
__LL_VAR_INLINE__ constexpr _MyType RAW_TYPE		= { llcpp::TRUE,  llcpp::TRUE,  llcpp::TRUE,  llcpp::TRUE,  llcpp::TRUE  };

} // namespace update

} // namespace attributes
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPEUPDATE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
