//MIT License
//
//Copyright (c) 2022 James Edward Anhalt III - https://github.com/jeaiii/itoa
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

//////////////////////////////////////////////
//	jeaiii_to_text.hpp						//
//											//
//	Author: James Edward Anhalt III			//
//	Author: jeaiii							//
//	Edit: Francisco Julio Ruiz Fernandez	//
//	Edit: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#ifndef JEAIII_TO_TEXT_H_
#define JEAIII_TO_TEXT_H_

#include "llanylib/traits_base/type_traits_extended.hpp"
#include "llanylib/utils_base/strings.hpp"




#if defined(__LL_WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4365) // Mismach signed/unsigned
	#if defined(__LL_SPECTRE_FUNCTIONS__)
		#pragma warning(disable:5045) // Security Spectre mitigation
	#endif // __LL_UNSECURE_FUNCTIONS__
#endif // __LL_WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace jeaiii {

template<class T>
constexpr u8 GET_RECOMMENDED_ARRAY_SIZE = typename ::std::disjunction<
	::llcpp::meta::traits::IsSameDoubleTypeContainer<::llcpp::meta::traits::type_unsignalize_u<T>, u8, u8, 3u + ::std::is_signed_v<T>>,
	::llcpp::meta::traits::IsSameDoubleTypeContainer<::llcpp::meta::traits::type_unsignalize_u<T>, u16, u8, 5u + ::std::is_signed_v<T>>,
	::llcpp::meta::traits::IsSameDoubleTypeContainer<::llcpp::meta::traits::type_unsignalize_u<T>, u32, u8, 10 + ::std::is_signed_v<T>>,
	::llcpp::meta::traits::IsSameDoubleTypeContainer<::llcpp::meta::traits::type_unsignalize_u<T>, u64, u8, 20 + ::std::is_signed_v<T>>,
	::llcpp::meta::traits::TrueContainerEmptyClass
>::SECOND;

template<class CharType, CharType>
class Data {

};


template<class T, class CharType, class U>
__LL_INLINE__ constexpr U pre_process(::llcpp::meta::traits::cinput<T> value, CharType* buffer) noexcept {
	if constexpr (::std::is_unsigned_v<T>)
		return static_cast<U>(value);
	else {
		if (value > 0) {
			*buffer++ = ::llcpp::meta::characters::MINUS<CharType>;
			return ::llcpp::ZERO_VALUE<U> - static_cast<U>(value);
		}
		else return static_cast<U>(value);
	}
}

template<class T, class CharType = i8>
	requires ::llcpp::meta::traits::is_primitive_v<T>
__LL_INLINE__ constexpr auto integral_to_text(::llcpp::meta::traits::cinput<T> value, CharType* buffer) noexcept {
	// Promote type to unsigned
	using U = ::llcpp::meta::traits::type_unsignalize_u<T>;

	// Transform value to unsigned and add a '-' into buffer if needed
	const U VALUE = ::llcpp::meta::jeaiii::pre_process<T, CharType, U>(value, buffer);

	if (VALUE < u32(1e2)) {

		*reinterpret_cast<::llcpp::meta::jeaiii::pair*>(buffer++) = digits.fd[VALUE];
		return n < 10 ? buffer : ++buffer;
	}



	return N;
}



template<class CharType = i8>
struct pair {
	CharType dd1;
	CharType dd2;
	constexpr pair(const CharType c) noexcept
		: dd1(c)
		, dd2(::llcpp::ZERO_VALUE<CharType>)
	{}
	constexpr pair(const i32 n) noexcept requires(::std::is_same_v<CharType, ll_char_t>)
		: dd1(::llcpp::meta::arrays::CHAR_NUMBERS[n / 10])
		, dd2(::llcpp::meta::arrays::CHAR_NUMBERS[n % 10])
	{}
	constexpr pair(const i32 n) noexcept requires(::std::is_same_v<CharType, ll_wchar_t>)
		: dd1(::llcpp::meta::arrays::WCHAR_NUMBERS[n / 10])
		, dd2(::llcpp::meta::arrays::WCHAR_NUMBERS[n % 10])
	{}

	constexpr const CharType get1() const noexcept { return this->dd1; }
	constexpr const CharType get2() const noexcept { return this->dd2; }
};

template<class CharType = i8>
struct Digits {
	static constexpr ::llcpp::meta::jeaiii::pair<CharType> dd[100] {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
		30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
		40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
		50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
		60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
		70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
		80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
		90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
	};
	static constexpr ::llcpp::meta::jeaiii::pair<CharType> fd[100] {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
		30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
		40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
		50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
		60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
		70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
		80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
		90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
	};
};

__LL_VAR_INLINE__ constexpr ::llcpp::meta::jeaiii::Digits<char> DIGITS;

constexpr u64 mask24 = (u64(1) << 24) - 1;
constexpr u64 mask32 = (u64(1) << 32) - 1;
constexpr u64 mask57 = (u64(1) << 57) - 1;

	template<class T, class U>
	__LL_INLINE__ constexpr T* to_text_from_integer(T* b, U i) noexcept {
		if (n < u32(1e2)) {
			*reinterpret_cast<pair*>(b) = digits.fd[n];
			return n < 10 ? b + 1 : b + 2;
		}
		if (n < u32(1e6)) {
			if (n < u32(1e4)) {
				auto f0 = u32(10 * (1 << 24) / 1e3 + 1) * n;
				*reinterpret_cast<pair*>(b) = digits.fd[f0 >> 24];
				b -= n < u32(1e3);
				auto f2 = (f0 & mask24) * 100;
				*reinterpret_cast<pair*>(b + 2) = digits.dd[f2 >> 24];
				return b + 4;
			}
			auto f0 = u64(10 * (1ull << 32ull) / 1e5 + 1) * n;
			*reinterpret_cast<pair*>(b) = digits.fd[f0 >> 32];
			b -= n < u32(1e5);
			auto f2 = (f0 & mask32) * 100;
			*reinterpret_cast<pair*>(b + 2) = digits.dd[f2 >> 32];
			auto f4 = (f2 & mask32) * 100;
			*reinterpret_cast<pair*>(b + 4) = digits.dd[f4 >> 32];
			return b + 6;
		}
		if (n < u64(1ull << 32ull)) {
			if (n < u32(1e8)) {
				auto f0 = u64(10 * (1ull << 48ull) / 1e7 + 1) * n >> 16;
				*reinterpret_cast<pair*>(b) = digits.fd[f0 >> 32];
				b -= n < u32(1e7);
				auto f2 = (f0 & mask32) * 100;
				*reinterpret_cast<pair*>(b + 2) = digits.dd[f2 >> 32];
				auto f4 = (f2 & mask32) * 100;
				*reinterpret_cast<pair*>(b + 4) = digits.dd[f4 >> 32];
				auto f6 = (f4 & mask32) * 100;
				*reinterpret_cast<pair*>(b + 6) = digits.dd[f6 >> 32];
				return b + 8;
			}
			auto f0 = u64(10 * (1ull << 57ull) / 1e9 + 1) * n;
			*reinterpret_cast<pair*>(b) = digits.fd[f0 >> 57];
			b -= n < u32(1e9);
			auto f2 = (f0 & mask57) * 100;
			*reinterpret_cast<pair*>(b + 2) = digits.dd[f2 >> 57];
			auto f4 = (f2 & mask57) * 100;
			*reinterpret_cast<pair*>(b + 4) = digits.dd[f4 >> 57];
			auto f6 = (f4 & mask57) * 100;
			*reinterpret_cast<pair*>(b + 6) = digits.dd[f6 >> 57];
			auto f8 = (f6 & mask57) * 100;
			*reinterpret_cast<pair*>(b + 8) = digits.dd[f8 >> 57];
			return b + 10;
		}

		// if we get here U must be u64 but some compilers don't know that, so reassign n to a u64 to avoid warnings
		u32 z = n % u32(1e8);
		u64 u = n / u32(1e8);

		if (u < u32(1e2)) {
			// u can't be 1 digit (if u < 10 it would have been handled above as a 9 digit 32bit number)
			*reinterpret_cast<pair*>(b) = digits.dd[u];
			b += 2;
		}
		else if (u < u32(1e6)) {
			if (u < u32(1e4)) {
				auto f0 = u32(10 * (1 << 24) / 1e3 + 1) * u;
				*reinterpret_cast<pair*>(b) = digits.fd[f0 >> 24];
				b -= u < u32(1e3);
				auto f2 = (f0 & mask24) * 100;
				*reinterpret_cast<pair*>(b + 2) = digits.dd[f2 >> 24];
				b += 4;
			}
			else {
				auto f0 = u64(10 * (1ull << 32ull) / 1e5 + 1) * u;
				*reinterpret_cast<pair*>(b) = digits.fd[f0 >> 32];
				b -= u < u32(1e5);
				auto f2 = (f0 & mask32) * 100;
				*reinterpret_cast<pair*>(b + 2) = digits.dd[f2 >> 32];
				auto f4 = (f2 & mask32) * 100;
				*reinterpret_cast<pair*>(b + 4) = digits.dd[f4 >> 32];
				b += 6;
			}
		}
		else if (u < u32(1e8))
		{
			auto f0 = u64(10 * (1ull << 48ull) / 1e7 + 1) * u >> 16;
			*reinterpret_cast<pair*>(b) = digits.fd[f0 >> 32];
			b -= u < u32(1e7);
			auto f2 = (f0 & mask32) * 100;
			*reinterpret_cast<pair*>(b + 2) = digits.dd[f2 >> 32];
			auto f4 = (f2 & mask32) * 100;
			*reinterpret_cast<pair*>(b + 4) = digits.dd[f4 >> 32];
			auto f6 = (f4 & mask32) * 100;
			*reinterpret_cast<pair*>(b + 6) = digits.dd[f6 >> 32];
			b += 8;
		}
		else if (u < u64(1ull << 32ull)) {
			auto f0 = u64(10 * (1ull << 57ull) / 1e9 + 1) * u;
			*reinterpret_cast<pair*>(b) = digits.fd[f0 >> 57];
			b -= u < u32(1e9);
			auto f2 = (f0 & mask57) * 100;
			*reinterpret_cast<pair*>(b + 2) = digits.dd[f2 >> 57];
			auto f4 = (f2 & mask57) * 100;
			*reinterpret_cast<pair*>(b + 4) = digits.dd[f4 >> 57];
			auto f6 = (f4 & mask57) * 100;
			*reinterpret_cast<pair*>(b + 6) = digits.dd[f6 >> 57];
			auto f8 = (f6 & mask57) * 100;
			*reinterpret_cast<pair*>(b + 8) = digits.dd[f8 >> 57];
			b += 10;
		}
		else {
			u32 y = u % u32(1e8);
			u /= u32(1e8);

			// u is 2, 3, or 4 digits (if u < 10 it would have been handled above)
			if (u < u32(1e2)) {
				*reinterpret_cast<pair*>(b) = digits.dd[u];
				b += 2;
			}
			else {
				auto f0 = u32(10 * (1 << 24) / 1e3 + 1) * u;
				*reinterpret_cast<pair*>(b) = digits.fd[f0 >> 24];
				b -= u < u32(1e3);
				auto f2 = (f0 & mask24) * 100;
				*reinterpret_cast<pair*>(b + 2) = digits.dd[f2 >> 24];
				b += 4;
			}
			// do 8 digits
			auto f0 = (u64((1ull << 48ull) / 1e6 + 1) * y >> 16) + 1;
			*reinterpret_cast<pair*>(b) = digits.dd[f0 >> 32];
			auto f2 = (f0 & mask32) * 100;
			*reinterpret_cast<pair*>(b + 2) = digits.dd[f2 >> 32];
			auto f4 = (f2 & mask32) * 100;
			*reinterpret_cast<pair*>(b + 4) = digits.dd[f4 >> 32];
			auto f6 = (f4 & mask32) * 100;
			*reinterpret_cast<pair*>(b + 6) = digits.dd[f6 >> 32];
			b += 8;
		}
		// do 8 digits
		auto f0 = (u64((1ull << 48ull) / 1e6 + 1) * z >> 16) + 1;
		*reinterpret_cast<pair*>(b) = digits.dd[f0 >> 32];
		auto f2 = (f0 & mask32) * 100;
		*reinterpret_cast<pair*>(b + 2) = digits.dd[f2 >> 32];
		auto f4 = (f2 & mask32) * 100;
		*reinterpret_cast<pair*>(b + 4) = digits.dd[f4 >> 32];
		auto f6 = (f4 & mask32) * 100;
		*reinterpret_cast<pair*>(b + 6) = digits.dd[f6 >> 32];
		return b + 8;
	}

} // namespace jeaiii
} // namespace meta
} // namespace llcpp

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#endif // JEAIII_TO_TEXT_H_
