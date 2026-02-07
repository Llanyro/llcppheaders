//////////////////////////////////////////////
//	Comparations.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 15.0							//
//////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//														Comparations Macros																//
//	LLANYHEADERS_COMPARATIONS_COMPARE_ITERATOR_WITH_LESS_OPERATOR_ : Set to 1 to use '<' comparator instead '!='						//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(LLANYLIB_COMPARATIONS_EQUALS_COMPARE_LESS_NOT_EQ_)
	#define LLANYLIB_COMPARATIONS_EQUALS_COMPARE_LESS_NOT_EQ_ 0
#endif

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_COMPARATIONS_INCOMPLETE_HPP_)
	#if LLANYLIB_COMPARATIONS_INCOMPLETE_MAYOR_ != 15 || LLANYLIB_COMPARATIONS_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Comparations.hpp(incomplete) version error!"
		#else
			#error "Comparations.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_COMPARATIONS_INCOMPLETE_MAYOR_ || LLANYLIB_COMPARATIONS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_COMPARATIONS_INCOMPLETE_HPP_)
	#define LLANYLIB_COMPARATIONS_INCOMPLETE_HPP_
	#define LLANYLIB_COMPARATIONS_INCOMPLETE_MAYOR_ 15
	#define LLANYLIB_COMPARATIONS_INCOMPLETE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include "types.hpp"
#else
	#include <llanylib/types/types.hpp>
#endif // LL_LIB_PATHS

namespace llcpp {
namespace comparations {

enum class Comparations : u8;
__LL_NODISCARD__ constexpr ll_bool_t is_similar_char(const i8 v1, i8 v2) noexcept;

template<class It1, class It2, class It3>
__LL_NODISCARD__ static constexpr ll_bool_t equals(It1 collection1_begin, It2 collection1_end,  It3 collection2_begin) noexcept;

} // namespace comparations
} // namespace llcpp

#elif defined(LLANYLIB_COMPARATIONS_HPP_)
	#if LLANYLIB_COMPARATIONS_MAYOR_ != 15 || LLANYLIB_COMPARATIONS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Comparations.hpp version error!"
		#else
			#error "Comparations.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_COMPARATIONS_MAYOR_ || LLANYLIB_COMPARATIONS_MINOR_

#else
	#define LLANYLIB_COMPARATIONS_HPP_
	#define LLANYLIB_COMPARATIONS_MAYOR_ 15
	#define LLANYLIB_COMPARATIONS_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include "types.hpp"
#else
	#include <llanylib/types/types.hpp>
#endif // LL_LIB_PATHS

namespace llcpp {
namespace comparations {

enum class Comparations : u8 {
	Equals,
	Similar,
};

__LL_NODISCARD__ constexpr ll_bool_t is_similar_char(const i8 v1, const i8 v2) noexcept {
	constexpr u8 MAYUS_MINUS_DIFF = ('a' - 'A');
	if (v1 > v2)		return v1 == (v2 + MAYUS_MINUS_DIFF);
	else if (v1 < v2)	return v1 == (v2 - MAYUS_MINUS_DIFF);
	else				return ::llcpp::LL_TRUE;
}

// Compare 2 collections of data from begin (It1) to end (It2)
// Does not check collection (2) has same number of elements that first one (1)
template<class It1, class It2, class It3>
__LL_NODISCARD__ static constexpr ll_bool_t equals(It1 collection1_begin, It2 collection1_end,  It3 collection2_begin) noexcept {
	__LL_FUNCTION_INIT__;
#if LLANYHEADERS_COMPARATIONS_COMPARE_ITERATOR_WITH_LESS_OPERATOR_ == 1
	for(; collection1_begin < collection1_end;	++collection1_begin, ++collection2_begin)
#else
	for(; collection1_begin != collection1_end; ++collection1_begin, ++collection2_begin)
#endif // LLANYHEADERS_COMPARATIONS_COMPARE_ITERATOR_WITH_LESS_OPERATOR_
		if(*collection1_begin != *collection2_begin)
			return ::llcpp::LL_FALSE;
	return ::llcpp::LL_TRUE;
}

} // namespace comparations
} // namespace llcpp

#endif // LLANYLIB_COMPARATIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
