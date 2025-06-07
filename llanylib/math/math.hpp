//////////////////////////////////////////////
//	math.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_MATH_INCOMPLETE_HPP_)
	#if LLANYLIB_MATH_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_MATH_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "math.hpp(incomplete) version error!"
		#else
			#error "math.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_MATH_INCOMPLETE_MAYOR_ || LLANYLIB_MATH_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_MATH_INCOMPLETE_HPP_)
	#define LLANYLIB_MATH_INCOMPLETE_HPP_
	#define LLANYLIB_MATH_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_MATH_INCOMPLETE_MINOR_ 0

#elif defined(LLANYLIB_MATH_HPP_)
	#if LLANYLIB_MATH_MAYOR_ != 12 || LLANYLIB_MATH_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "math.hpp version error!"
		#else
			#error "math.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_MATH_MAYOR_ || LLANYLIB_MATH_MINOR_

#else
	#define LLANYLIB_MATH_HPP_
	#define LLANYLIB_MATH_MAYOR_ 12
	#define LLANYLIB_MATH_MINOR_ 0

#include "is_even.hpp"	// Includes is_odd.hpp

namespace llcpp {
namespace meta {
namespace math {

#if __LL_INCLUDE_KATS == 1
namespace kat {

struct KeyValue {
	i32 value;
	ll_bool_t expected;
	::llcpp::string point;
};

constexpr KeyValue IS_ODD_VALUES[] = {
	{ 0, ::llcpp::LL_FALSE, "0" },
};

template<usize POSITION>
__LL_NODISCARD__ constexpr ::llcpp::string is_working_is_odd_generic_kat() noexcept {
	constexpr auto& VAL = IS_ODD_VALUES[POSITION];
	constexpr ll_bool_t VALUE =
		::llcpp::meta::math::is_odd<decltype(KeyValue::value)>(VAL.value);
	__LL_KAT_GENERIC_CONSTEXPR(VALUE, "");
	return nullptr;
}

__LL_NODISCARD__ constexpr ::llcpp::string is_working_is_odd_kat() noexcept {
	return nullptr;
}
__LL_NODISCARD__ constexpr ::llcpp::string is_working_is_even_kat() noexcept {
	return nullptr;
}


__LL_KAT_FUNCTION(
	is_working_is_even_kat,
	::llcpp::meta::MATH::kat::IS_WORKING_IS_ODD,
	"'Is even'" __LL_IS_NOT_WORKING_STR
);

__LL_NODISCARD__ constexpr ::llcpp::string math_kats() noexcept {
	::llcpp::string result = ::llcpp::meta::math::kat::is_working_is_even_kat();
	if(result) return result;
	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::math::kat::math_kats() == LL_NULLPTR, "math KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace math
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_MATH_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_MATH_EXTRA_HPP_)
		#if LLANYLIB_MATH_EXTRA_MAYOR_ != 12 || LLANYLIB_MATH_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "math.hpp(extra) version error!"
			#else
				#error "math.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_MATH_EXTRA_MAYOR_ || LLANYLIB_MATH_EXTRA_MINOR_

	#else
		#define LLANYLIB_MATH_EXTRA_HPP_
		#define LLANYLIB_MATH_EXTRA_MAYOR_ 12
		#define LLANYLIB_MATH_EXTRA_MINOR_ 0

	#endif // LLANYLIB_MATH_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
