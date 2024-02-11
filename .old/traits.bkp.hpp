/*
*	traits.hpp
*
*	Created on: Feb 28, 2022
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
*/

#ifndef LLCPP_HEADER_TRAITS_HPP_
#define LLCPP_HEADER_TRAITS_HPP_

#include "types.hpp"
#include "traits_test_class.hpp"

#include <type_traits>

namespace llcpp {
namespace traits {

/*
ll_bool_t c_f() {}

using t = decltype(TestClass::clear_s);
using t2 = decltype(c_f);

template<class T>
using Temp = ll_bool_t(T::*)();

static_assert(std::is_same_v<decltype(TestClass::clear_s), Temp<TestClass>>, "No");

template<class T>
constexpr ll_bool_t is_same_function_decl = std::is_same_v<decltype(T::clear_s), decltype(Temp<T>)>;

constexpr ll_bool_t is_same_function_decl2 = is_same_function_decl<TestClassBase>;

*/


//template<class T, class Allocator = std::nullptr_t>
//inline constexpr ll_bool_t is_pointer_with_allocator_v = std::is_pointer_v<T> && !std::is_same_v<Allocator, std::nullptr_t>;
//
//template<class T, class Allocator = std::nullptr_t>
//using type_or_pack_allocator = std::conditional<
//	is_pointer_with_allocator_v<T, Allocator>,
//	std::pair<T, Allocator>,
//	T
//>;
//
//template<class T, class Allocator = std::nullptr_t>
//using type_or_pack_allocator_t = type_or_pack_allocator<T, Allocator>::type;

/*
ll_bool_t c_f() {}

using t = decltype(TestClass::clear_s);
using t2 = decltype(c_f);

template<class T>
using Temp = ll_bool_t(T::*)();

static_assert(std::is_same_v<decltype(TestClass::clear_s), Temp<TestClass>>, "No");

template<class T>
constexpr ll_bool_t is_same_function_decl = std::is_same_v<decltype(T::clear_s), decltype(Temp<T>)>;

constexpr ll_bool_t is_same_function_decl2 = is_same_function_decl<TestClassBase>;

*/

//constexpr ll_bool_t s = is_pointer_with_allocator_v<int*>;

/*class Patata {
	protected:
		int a;
	public:
		constexpr Patata() = default;
		constexpr Patata(int b) : a(b) {}
		constexpr ~Patata() = default;
};

constexpr const Patata p[5] = { 1, 2, 3, 4, 5 };
constexpr const Patata p2[5] = { 1, 2, 3, 4, 5 }; */

/*constexpr auto arrviewPatata = ArrayView(p);
constexpr auto arrviewPatata2 = ArrayView(p2);

constexpr ll_bool_t arr_bool = arrviewPatata.operator==(arrviewPatata2);*/

/*template<len_t N, len_t RES_N = N / 2, class T = ui64[RES_N]>
constexpr T string_to_value_impl2(const char (&c)[N]) {
	ui64 value{};


	return
		*c
		? is_digit(*c)
			? string_to_value_impl(c + 1, (*c - '0') + value * 10)
			: throw "Compile time error: not a digit"
		: value;
}*/

/*

constexpr ll_bool_t a_a = is_digit('b');
constexpr ui64 a_2 = string_to_value("2738438947");

constexpr ui64 myceil(const f64 v) {
	return static_cast<ui64>(v);
}

constexpr ui64 aprox(const f64 v) {
	return static_cast<ui64>(v + 0.5f);
}

constexpr ui64 value_n = 999 * 999;
constexpr ui64 value_1 = myceil(9.9);
constexpr ui64 value_2 = myceil(9.5);

constexpr ui64 value_3 = maxCharacters(sizeof(int), false);
constexpr ui64 value_4 = maxCharacters(sizeof(ui64), false);
constexpr ui64 value_5 = maxCharacters(sizeof(ui128), false);
constexpr ui64 value_6 = maxCharacters(sizeof(ui256), false);
*/

/*
template<class T>
constexpr ui64 datatype_number_chars() {
	return
		std::is_unsigned_v<T>
		? 1
		: 0;
	ceil()
}

template<class T>
constexpr ui64 datatype_number_chars_v = datatype_number_chars<T>();
*/

/*
template<class T, len_t N = datatype_number_chars_v<T>>
constexpr ll_bool_t value_to_string(const T value, ll_char_t (&arr)[N]) {
	arr[0] = 'c';

	return true;
}

constexpr ui64 p1 = sizeof(int) ;
constexpr ui64 p2 = datatype_number_chars_v<int>;
constexpr ui64 p3 = datatype_number_chars_v<int>;
constexpr ui64 p4 = datatype_number_chars_v<int>;
constexpr ui64 p5 = datatype_number_chars_v<int>;
constexpr ui64 p = datatype_number_chars_v<int>;
constexpr ll_char_t aasdfas[datatype_number_chars_v<ui64>];
constexpr ll_bool_t c_3 = value_to_string(100ull, aasdfas);


constexpr ui64 a = string_to_value("9999999999999999999999999999999999999999");

#define VAL_0 "0"
#define VAL_1 "1"
#define VAL_2 "2"
#define VAL_3 "3"
#define VAL_4 "4"
#define VAL_5 "5"
#define VAL_6 "6"
#define VAL_7 "7"
#define VAL_8 "8"
#define VAL_9 "9"




constexpr ll_string_t get_str(100);

void test_traits() {
	ll_char_t vec[datatype_number_chars_v<int>]{};
	ll_char_t& vecref = vec[0];




}*/


} // namespace traits
} // namespace llcpp

/*
#include "lloperations.hpp"

template<class T>
T* generateMem(const len_t);
template<class T>
void realloceMem(T*&, const len_t);
template<class T>
ll_bool_t copymem(T* dst, const T* src, const len_t);
template<class T>
void freemem(T*&);


struct Result {
	public:
		using Num = ui64;
		using LastNum = i64;
	public:
		Num result;
		ll_bool_t carry;
};

constexpr Result sumNumbersWithCarry(const ui8 v1, const ui8 v2, const ui8 carry) {
	Result result = { v1 + v2, false };

	result.carry = (result.result <= llcpp::header::operations::min(v1, v2));

	if (carry) {
		++result.result;
		if (!result.result) ++result.carry;
	}

	return result;
}

class Integer {
	public:
		using Num = Result::Num;
		using LastNum = Result::LastNum;
	protected:
		Num* numbers;
		len_t len;
	protected:
		Integer() __LL_EXCEPT__ : numbers(LL_NULLPTR), len(0ull) {}
		void clear() __LL_EXCEPT__ { freemem(this->numbers); }
		void copy(const Integer& other) __LL_EXCEPT__ {
			realloceMem<Num>(this->numbers, other.len);
			this->len = other.len;
			copymem<Num>(this->numbers, other.numbers, other.len);
		}
	public:
		template<class T>
		Integer(const T value) : number() {}
		~Integer() { this->clear(); }


		Integer(const Integer& other) __LL_EXCEPT__ : Integer() { this->copy(other); }
		Integer(const Integer&& other) __LL_EXCEPT__ : number(std::move(other.number)) {}

		Integer(const Integer& other, const Integer& other2)
			: number(
				other2.getNumberGroups() > other.getNumberGroups()
				? other2.getNumberGroups() + 1
				: other.getNumberGroups() + 1
			) {}


		Integer operator+=(const Integer& other) const {
			Integer result(*this, other);

			ll_bool_t firstIsBigger = this->getNumberGroups() > other.getNumberGroups();
			ui64 minSize = firstIsBigger ? this->getNumberGroups() : other.getNumberGroups();
			ui64 diffSize =
				firstIsBigger
				? this->getNumberGroups() - other.getNumberGroups()
				: other.getNumberGroups() - this->getNumberGroups();

			Result operation{};

			for (ui64 i{}; i < minSize; ++i) {
				operation = sumNumbersWithCarry(this->number[i], other.number[i], operation.carry);
				result.number[i] = operation.result;
			}
			




		}

		Integer operator+(const Integer& other) const {

		}

};
*/


#endif /* LLCPP_HEADER_TRAITS_HPP_ */
