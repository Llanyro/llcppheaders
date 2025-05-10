//////////////////////////////////////////////
//	is_odd.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ISODD_INCOMPLETE_HPP_)
	#if LLANYLIB_ISODD_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ISODD_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "is_odd.hpp(incomplete) version error!"
		#else
			#error "is_odd.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ISODD_INCOMPLETE_MAYOR_ || LLANYLIB_ISODD_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ISODD_INCOMPLETE_HPP_)
	#define LLANYLIB_ISODD_INCOMPLETE_HPP_
	#define LLANYLIB_ISODD_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ISODD_INCOMPLETE_MINOR_ 0

#include "../../concepts/concepts.hpp"

namespace llcpp {
namespace meta {
namespace math {	

template<class T>
__LL_NODISCARD__ constexpr ll_bool_t is_odd(::llcpp::meta::traits::cinput<T> value) noexcept;

} // namespace math
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ISODD_HPP_)
	#if LLANYLIB_ISODD_MAYOR_ != 12 || LLANYLIB_ISODD_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "is_odd.hpp version error!"
		#else
			#error "is_odd.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ISODD_MAYOR_ || LLANYLIB_ISODD_MINOR_

#else
	#define LLANYLIB_ISODD_HPP_
	#define LLANYLIB_ISODD_MAYOR_ 12
	#define LLANYLIB_ISODD_MINOR_ 0

#include "../../concepts/concepts.hpp"

namespace llcpp {
namespace meta {
namespace math {
namespace __math__ {

template<class T>
__LL_NODISCARD__ constexpr ll_bool_t is_odd_primitive(const T value) noexcept {
	return static_cast<ll_bool_t>(value & 1);
}

template<class T>
__LL_NODISCARD__ constexpr ll_bool_t is_odd_pair(const T& value) noexcept {
	return ::llcpp::meta::math::is_odd<decltype(value.second)>(value.second);
}

template<class T>
__LL_NODISCARD__ constexpr ll_bool_t is_odd_pointer(const T value) noexcept {
#if __LL_CONSTEVAL_ENABLED == 1
		if consteval {
#endif // __LL_CONSTEVAL_ENABLED
		static_assert(!::std::is_pointer_v<T>,
			"This type cannot be constevaluate in C++ lower than C++26");
#if __LL_CONSTEVAL_ENABLED == 1
		}
		else {
			// [TODO] [TOFIX]
			return ::llcpp::meta::math::is_odd<usize>(reinterpret_cast<usize>(value));
		}
#endif // __LL_CONSTEVAL_ENABLED
}

template<class T>
__LL_NODISCARD__ constexpr ll_bool_t is_odd_floating_point(const T value) noexcept {
	static_assert(!::llcpp::meta::traits::is_floating_type_v<T>,
		"Cannot operate with floating-point! A recommendation is casting it to a class or integral type");
	return llcpp::FALSE;
}

template<class T, ll_bool_t IGNORE_BITWISE = ::llcpp::LL_FALSE>
__LL_NODISCARD__ constexpr ll_bool_t is_odd_class(const T& value) noexcept {
	// Needs to be comparable using bitwise with any primitive
	if constexpr (::llcpp::meta::concepts::signature::HasOperatorBitwiseANDWithPrimitives<T> && !IGNORE_BITWISE) {
		using ReturnType = decltype(value & 1u);
		// Result type needs to be convertible to bool
		if constexpr (::std::is_convertible_v<ReturnType, ll_bool_t>)
			return static_cast<ll_bool_t>(value & 1u);
		else {
			//static_assert(::std::is_convertible_v<ReturnType, ll_bool_t>,
			//	"Result of (value & 1) should result in a convertible type to ll_bool_t");
			return ::llcpp::meta::math::__math__::is_odd_class<T, ::llcpp::LL_TRUE>(value);
		}
	}
	// If class has not operator& or ir ignored
	// We can go a slower way
	else if constexpr (::llcpp::meta::concepts::signature::HasOperatorModulusWithPrimitives<T>) {
		using ReturnType = decltype(value % 2);
		if constexpr (::llcpp::meta::concepts::signature::HasOperatorEqual<ReturnType>)
			return (value % 2) == 0u;
		else if constexpr (::llcpp::meta::traits::is_pair_v<T>) {
			auto val = value % 2u;
			return val.first == 0 && val.second == 0u;
		}
		else {
			static_assert(::llcpp::meta::traits::is_pair_v<T>,
				"(value % 2) is not comparable with 0");
			return ::llcpp::meta::math::__math__::is_odd_class<T, ::llcpp::LL_TRUE>(value);
		}
	}
}

} // namespace __math__

template<class T>
__LL_NODISCARD__ constexpr ll_bool_t is_odd(::llcpp::meta::traits::cinput<T> value) noexcept {
	// If is primitive, its a trivial case
	if constexpr (::llcpp::meta::traits::is_primitive_v<T>)
		return ::llcpp::meta::math::__math__::is_odd_primitive<T>(value);
	// If its a pair, ir pair-like struct, we call this function again with the lower value
	else if constexpr (::llcpp::meta::traits::is_pair_v<T>)
		return ::llcpp::meta::math::__math__::is_odd_pair<T>(value);
	// If is pointer, we can only use this on runtime or using any new c++26 feature
	else if constexpr (::std::is_pointer_v<T>)
		return ::llcpp::meta::math::__math__::is_odd_pointer<T>(value);
	// Floating points cannot be checked
	else if constexpr (::llcpp::meta::traits::is_floating_type_v<T>)
		return ::llcpp::meta::math::__math__::is_odd_floating_point<T>(value);
	// A class can be checked if it follow the rules of primitive values
	else if constexpr (::std::is_class_v<T>)
		return ::llcpp::meta::math::__math__::is_odd_class<T>(value);
	else {
		static_assert(!::llcpp::meta::traits::is_floating_type_v<T>,
			"Unknown type to check if its odd");
		return ::llcpp::LL_FALSE;
	}
}

static_assert(is_odd<int>(9)								== ::llcpp::LL_TRUE,	"This should be odd");
static_assert(is_odd<usize>(999999999ull)					== ::llcpp::LL_TRUE,	"This should be odd");
static_assert(is_odd<::llcpp::meta::pair<int>>({ 9, 9 })	== ::llcpp::LL_TRUE,	"This should be odd");
static_assert(is_odd<::llcpp::meta::pair<int>>({ 9, 2 })	== ::llcpp::LL_FALSE,	"This is not odd");

} // namespace math
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ISODD_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
