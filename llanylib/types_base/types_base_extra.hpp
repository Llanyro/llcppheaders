//////////////////////////////////////////////
//	types_base_extra.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_HPP_)
	#if LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "types_base_extra.hpp(incomplete) version error!"
		#else
			#error "types_base_extra.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_MAYOR_ || LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_HPP_)
#define LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_HPP_
#define LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_TYPESBASEEXTRA_INCOMPLETE_MINOR_ 0

#include "types_base.hpp"

namespace llcpp {

struct EmptyStruct;
class Emptyclass;

namespace meta {

using StandardComparation = std::strong_ordering;

} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TYPESBASEEXTRA_HPP_)
	#if LLANYLIB_TYPESBASEEXTRA_MAYOR_ != 11 || LLANYLIB_TYPESBASEEXTRA_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "types_base_extra.hpp version error!"
		#else
			#error "types_base_extra.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TYPESBASEEXTRA_MAYOR_ || LLANYLIB_TYPESBASEEXTRA_MINOR_

#else
#define LLANYLIB_TYPESBASEEXTRA_HPP_
#define LLANYLIB_TYPESBASEEXTRA_MAYOR_ 11
#define LLANYLIB_TYPESBASEEXTRA_MINOR_ 0

#include "types_base.hpp"

namespace llcpp {

class Emptyclass				{ public: using _MyType = Emptyclass; };
// When using incomplete lib && some type is not possible to exist but using complete lib
//	this type will be used
class UndefinedIncompleteObject	{ public: using _MyType = UndefinedIncompleteObject; };

using Void						= ::llcpp::Emptyclass;

namespace meta {

using StandardComparation		= ::std::strong_ordering;

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPESBASEEXTRA_HPP_

#if !defined(LLANYLIB_TYPESEXPRESIONS_EXTRA_HPP_) && !defined(LLANYLIB_ERROR_HPP_)
#define LLANYLIB_TYPESEXPRESIONS_EXTRA_HPP_

namespace llcpp {

__LL_VAR_INLINE__ constexpr ll_bool_t FALSE		= false;
__LL_VAR_INLINE__ constexpr ll_bool_t TRUE		= true;

template<class... Args> __LL_INLINE__ constexpr void IGNORE(Args&&...)	{}
template<class T>		__LL_INLINE__ constexpr void IGNORE(T&&...)		{}
template<class>			__LL_INLINE__ constexpr void IGNORE()			{}

namespace meta {
namespace algorithm {

__LL_VAR_INLINE__ constexpr u64 MAX_LIST_SIZE	= static_cast<u64>(-1);
__LL_VAR_INLINE__ constexpr u64 npos			= ::llcpp::meta::algorithm::MAX_LIST_SIZE;

} // namespace algorithm
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TYPESEXPRESIONS_EXTRA_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
