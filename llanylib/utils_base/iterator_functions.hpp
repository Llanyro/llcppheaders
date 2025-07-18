//////////////////////////////////////////////
//	iterator_functions.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ITERATORFUNCTIONS_INCOMPLETE_HPP_)
	#if LLANYLIB_ITERATORFUNCTIONS_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ITERATORFUNCTIONS_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "iterator_functions.hpp(incomplete) version error!"
		#else
			#error "iterator_functions.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ITERATORFUNCTIONS_INCOMPLETE_MAYOR_ || LLANYLIB_ITERATORFUNCTIONS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ITERATORFUNCTIONS_INCOMPLETE_HPP_)
	#define LLANYLIB_ITERATORFUNCTIONS_INCOMPLETE_HPP_
	#define LLANYLIB_ITERATORFUNCTIONS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ITERATORFUNCTIONS_INCOMPLETE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/concepts/concepts.hpp>
#else
	#include "../concepts/concepts.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace utils {

template<ll_bool_t REVERSE = ::llcpp::LL_FALSE, ll_bool_t NEGATIVE = ::llcpp::LL_FALSE, class T, class U>
__LL_NODISCARD__ constexpr T operateAricmetic(const T val, const U add) noexcept;

template<class _T, ll_bool_t _IS_REVERSED = ::llcpp::LL_FALSE>
class PointerIterator;

template<class U, ll_bool_t __IS_REVERSED>
__LL_NODISCARD__ constexpr ll_bool_t is_pointer_iterator(const PointerIterator<U, __IS_REVERSED>& it) noexcept;
template<class>
__LL_NODISCARD__ constexpr ll_bool_t is_pointer_iterator(...) noexcept;

template<class Iterator1, class Iterator2>
__LL_NODISCARD__ constexpr isize itertator_distance(const Iterator1& it1, const Iterator2& it2) noexcept;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ITERATORFUNCTIONS_HPP_)
	#if LLANYLIB_ITERATORFUNCTIONS_MAYOR_ != 12 || LLANYLIB_ITERATORFUNCTIONS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "iterator_functions.hpp version error!"
		#else
			#error "iterator_functions.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ITERATORFUNCTIONS_MAYOR_ || LLANYLIB_ITERATORFUNCTIONS_MINOR_

#else
	#define LLANYLIB_ITERATORFUNCTIONS_HPP_
	#define LLANYLIB_ITERATORFUNCTIONS_MAYOR_ 12
	#define LLANYLIB_ITERATORFUNCTIONS_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/concepts/concepts.hpp>
#else
	#include "../concepts/concepts.hpp"
#endif // LL_LIB_PATHS

#if defined(__LL_WINDOWS_SYSTEM)
#elif defined(__LL_MINGW)
	#include <algorithm>
#elif defined(__LL_POSIX_SYSTEM)
#elif defined(__LL_UNIX_SYSTEM)
#else
#endif // __LL_WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace utils {

template<ll_bool_t REVERSE = ::llcpp::LL_FALSE, ll_bool_t NEGATIVE = ::llcpp::LL_FALSE, class T, class U>
__LL_NODISCARD__ constexpr T operateAricmetic(const T val, const U add) noexcept {
	__LL_FUNCTION_INIT__;
	if constexpr (!REVERSE && !NEGATIVE)
		return val + add;
	else if constexpr (REVERSE && !NEGATIVE)
		return val - add;
	else if constexpr (REVERSE && NEGATIVE)
		return val + add;
	else return val - add;
}

template<class _T, ll_bool_t _IS_REVERSED = ::llcpp::LL_FALSE>
class PointerIterator;

template<class U, ll_bool_t __IS_REVERSED>
__LL_NODISCARD__ constexpr ll_bool_t is_pointer_iterator(const PointerIterator<U, __IS_REVERSED>& it) noexcept { return ::llcpp::LL_TRUE; }
template<class>
__LL_NODISCARD__ constexpr ll_bool_t is_pointer_iterator(...) noexcept { return ::llcpp::LL_FALSE; }

template<class Iterator1, class Iterator2>
__LL_NODISCARD__ constexpr isize itertator_distance(const Iterator1& it1, const Iterator2& it2) noexcept {
	if constexpr (::std::is_pointer_v<Iterator1> && ::std::is_pointer_v<Iterator2>)
		return it1 - it2;
	else if constexpr (::std::is_pointer_v<Iterator1>)
		return it1 - &(*it2);		// Get object, then get its address
	else if constexpr (::std::is_pointer_v<Iterator2> && ::llcpp::meta::concepts::signature::HasDistance<Iterator1, Iterator2, isize>)
		return it1.distance(it2);	// Use class builtin distance function 
	else if constexpr (::std::is_pointer_v<Iterator2>)
		return &(*it1) - it2;		// Get object, then get its address
	else if constexpr (::std::is_same_v<Iterator1, Iterator2>)
		return static_cast<isize>(::std::distance(it1, it2));
	else {
		static_assert(::std::is_same_v<Iterator1, Iterator2>,
			"Cannot measure distance");
		return 0ll;
	}
}

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ITERATORFUNCTIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
