//////////////////////////////////////////////
//	traits_limits.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_QWERTY_INCOMPLETE_HPP_)
	#if LLANYLIB_QWERTY_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_QWERTY_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "qwerty.hpp(incomplete) version error!"
		#else
			#error "qwerty.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_QWERTY_INCOMPLETE_MAYOR_ || LLANYLIB_QWERTY_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_QWERTY_INCOMPLETE_HPP_)
#define LLANYLIB_QWERTY_INCOMPLETE_HPP_
#define LLANYLIB_QWERTY_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_QWERTY_INCOMPLETE_MINOR_ 0

#include "traits_type_update.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<class _T>
struct RangeChecker;

} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_QWERTY_HPP_)
	#if LLANYLIB_QWERTY_MAYOR_ != 11 || LLANYLIB_QWERTY_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "qwerty.hpp version error!"
		#else
			#error "qwerty.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_QWERTY_MAYOR_ || LLANYLIB_QWERTY_MINOR_

#else
#define LLANYLIB_QWERTY_HPP_
#define LLANYLIB_QWERTY_MAYOR_ 11
#define LLANYLIB_QWERTY_MINOR_ 0

#include "traits_type_update.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<class _T>
struct RangeChecker {
	// Class related
	using _MyType	= RangeChecker;

	// Types and enums
	using T			= _T;

	// Expresions
	static constexpr T MAX_VALUE =
		traits::conditional_value_simple_v<
			std::is_unsigned_v<T>,
			T,
			T(-1),
			((RangeChecker<traits::type_signed<T, llcpp::FALSE>>::MAX_VALUE) >> 1)
		>;

	static constexpr T MIN_VALUE = _MyType::MAX_VALUE + 1;

	// Asserts
	static_assert(!std::is_floating_point_v<T>,
		"Type cannot be floating point! Results are valid but not correct!");
};

} // namespace traits

template<class T>
__LL_VAR_INLINE__ constexpr T MAX_VALUE = traits::RangeChecker<T>::MAX_VALUE;

template<class T>
__LL_VAR_INLINE__ constexpr T MIN_VALUE = traits::RangeChecker<T>::MIN_VALUE;

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_QWERTY_HPP_

#if !defined(LLANYLIB_QWERTY_EXTRA_HPP_) && !defined(LLANYLIB_ERROR_HPP_)
#define LLANYLIB_QWERTY_EXTRA_HPP_

namespace llcpp {
namespace meta {

template<class T>
__LL_VAR_INLINE__ constexpr T ZERO_VALUE = T{};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_QWERTY_EXTRA_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
