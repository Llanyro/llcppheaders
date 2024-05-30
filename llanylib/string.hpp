//////////////////////////////////////////////
//	string.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_STRING_HPP_) // Guard && version protector
	#if LLANYLIB_STRING_MAYOR_ != 7 || LLANYLIB_STRING_MINOR_ < 0
		#error "string.hpp version error!"
	#endif // LLANYLIB_STRING_MAYOR_ || LLANYLIB_STRING_MINOR_

#else !defined(LLANYLIB_STRING_HPP_)

#error "This is in WIP. Wait to Release 7"

#define LLANYLIB_STRING_HPP_
#define LLANYLIB_STRING_MAYOR_ 7
#define LLANYLIB_STRING_MINOR_ 0

#include "algorithm.hpp"

namespace llcpp {
namespace string {
















namespace __internal__ {

#pragma region string_to_value
template<class T>
__LL_NODISCARD__ constexpr T string_to_value(ll_string_t str, T val) __LL_EXCEPT__ { return val; }

#define STRING_TO_UNSIGNED_VALUE_BODY(ZERO_VALUE, type) \
	if (!str) return ZERO_VALUE; \
	else if (*str == '\0') return val; \
	//																						val times 10
	else if (is_digit(*str)) return string_to_value<type>(str + 1, dctdn(*str) + ((val << 3) + (val << 1))); \
	else return val;

#define STRING_TO_SIGNED_VALUE_BODY(ZERO_VALUE, type) \
	if (!str) return ZERO_VALUE; \
	else if (*str == '\0') return val; \
	else if(*str == '-')  return -string_to_value<type>(str + 1, val); \
	else if (is_digit(*str)) return string_to_value<type>(str + 1, dctdn(*str) + ((val << 3) + (val << 1))); \
	else return val;


template<>
__LL_NODISCARD__ constexpr ui8 string_to_value(ll_string_t str, ui8 val) __LL_EXCEPT__ {
	STRING_TO_UNSIGNED_VALUE_BODY(ZERO_UI8, ui8);
}
template<>
__LL_NODISCARD__ constexpr ui16 string_to_value(ll_string_t str, const ui16 val) __LL_EXCEPT__ {
	STRING_TO_UNSIGNED_VALUE_BODY(ZERO_UI16, ui16);
}
template<>
__LL_NODISCARD__ constexpr ui32 string_to_value(ll_string_t str, const ui32 val) __LL_EXCEPT__ {
	STRING_TO_UNSIGNED_VALUE_BODY(ZERO_UI32, ui32);
}
template<>
__LL_NODISCARD__ constexpr ui64 string_to_value(ll_string_t str, const ui64 val) __LL_EXCEPT__ {
	STRING_TO_UNSIGNED_VALUE_BODY(ZERO_UI64, ui64);
}
template<>
__LL_NODISCARD__ constexpr i8 string_to_value(ll_string_t str, const i8 val) __LL_EXCEPT__ {
	STRING_TO_SIGNED_VALUE_BODY(ZERO_I8, i8);
}
template<>
__LL_NODISCARD__ constexpr i16 string_to_value(ll_string_t str, const i16 val) __LL_EXCEPT__ {
	STRING_TO_SIGNED_VALUE_BODY(ZERO_I16, i16);
}
template<>
__LL_NODISCARD__ constexpr i32 string_to_value(ll_string_t str, const i32 val) __LL_EXCEPT__ {
	STRING_TO_SIGNED_VALUE_BODY(ZERO_I32, i32);
}
template<>
__LL_NODISCARD__ constexpr i64 string_to_value(ll_string_t str, const i64 val) __LL_EXCEPT__ {
	STRING_TO_SIGNED_VALUE_BODY(ZERO_I64, i64);
}

#undef STRING_TO_UNSIGNED_VALUE_BODY
#undef STRING_TO_SIGNED_VALUE_BODY

#pragma endregion

} // namespace __internal__

#pragma region Other
__LL_NODISCARD__ constexpr i8 digit_char_to_decimal_number(const i8 c) __LL_EXCEPT__ { return c - '0'; }
__LL_NODISCARD__ constexpr i8 dctdn(const i8 c) __LL_EXCEPT__ { return digit_char_to_decimal_number(c); }
__LL_NODISCARD__ constexpr ll_bool_t is_digit(const i8 c) __LL_EXCEPT__ { return c <= '9' && c >= '0'; }

#pragma endregion
#pragma region string_to_value
template<class T>
__LL_NODISCARD__ constexpr T string_to_value(ll_string_t c) __LL_EXCEPT__ {
	return __internal__::string_to_value<T>(c, 0);
}
template<>
__LL_NODISCARD__ constexpr i8 string_to_value(ll_string_t c) __LL_EXCEPT__ {
	return __internal__::string_to_value<i8>(c, ZERO_I8);
}
template<>
__LL_NODISCARD__ constexpr i16 string_to_value(ll_string_t c) __LL_EXCEPT__ {
	return __internal__::string_to_value<i16>(c, ZERO_I16);
}
template<>
__LL_NODISCARD__ constexpr i32 string_to_value(ll_string_t c) __LL_EXCEPT__ {
	return __internal__::string_to_value<i32>(c, ZERO_I32);
}
template<>
__LL_NODISCARD__ constexpr i64 string_to_value(ll_string_t c) __LL_EXCEPT__ {
	return __internal__::string_to_value<i64>(c, ZERO_I64);
}
template<>
__LL_NODISCARD__ constexpr ui8 string_to_value(ll_string_t c) __LL_EXCEPT__ {
	return __internal__::string_to_value<ui8>(c, ZERO_UI8);
}
template<>
__LL_NODISCARD__ constexpr ui16 string_to_value(ll_string_t c) __LL_EXCEPT__ {
	return __internal__::string_to_value<ui16>(c, ZERO_UI16);
}
template<>
__LL_NODISCARD__ constexpr ui32 string_to_value(ll_string_t c) __LL_EXCEPT__ {
	return __internal__::string_to_value<ui32>(c, ZERO_UI32);
}
template<>
__LL_NODISCARD__ constexpr ui64 string_to_value(ll_string_t c) __LL_EXCEPT__ {
	return __internal__::string_to_value<ui64>(c, ZERO_UI64);
}

#pragma endregion
#pragma region Compare
__LL_NODISCARD__ constexpr ll_bool_t equals(ll_string_t v1, const len_t size1, ll_string_t v2, const len_t size2) __LL_EXCEPT__ {
	return algorithm::equals<ll_char_t>(v1, size1, v2, size2);
}
template<len_t size1, len_t size2 = size1>
__LL_NODISCARD__ constexpr ll_bool_t equals(ll_string_t v1, ll_string_t v2) __LL_EXCEPT__ {
	return algorithm::equals<ll_char_t>(v1, size1, v2, size2);
}
template<len_t N1, len_t N2>
__LL_NODISCARD__ constexpr ll_bool_t equals(const ll_char_t (&v1)[N1], const ll_char_t (&v2)[N2]) __LL_EXCEPT__ {
	return algorithm::equals<ll_char_t>(v1, N1, v2, N2);
}

#pragma endregion
#pragma region Other
template<class T>
constexpr ui64 number_of_chars_to_display_value() {
	constexpr ui64 bits = sizeof(T) << 3;
	ui64 maxChars = bits / 3 + (bits % 3 == ZERO_UI64 ? 0 : 1);
	if constexpr (!std::is_unsigned_v<T>) return maxChars + 1;
	else return maxChars;
}
template<class T>
constexpr ui64 number_of_chars_to_display_value_v = number_of_chars_to_display_value<T>();

#pragma endregion

//constexpr ll_bool_t is_digit_b = is_digit('b');
//constexpr ui64 string_to_value_2738438947 = string_to_value<ui64>("2738438947");
//constexpr ui64 string_to_value_null = string_to_value<ui64>(nullptr);
//constexpr ui64 string_to_value_2_738438947 = string_to_value<ui64>("2_738438947");
//constexpr i64 string_to_value_minus_2738438947 = string_to_value<i64>("-2738438947");

} // namespace string
} // namespace llcpp

#endif // LLANYLIB_STRING_HPP_
