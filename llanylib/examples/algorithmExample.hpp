/*
 *	algorithmExample.hpp
 *
 *	Created on: Sep 27, 2021
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#include "../algorithm.hpp"

#if !defined(LLANYLIB_EXAMPLES_ALGORITHMEXAMPLE_HPP_)
#define LLANYLIB_EXAMPLES_ALGORITHMEXAMPLE_HPP_

namespace llcpp {
namespace algorithm {

/************************************* Example strings *************************************/

constexpr ll_char_t str[15] = "Holoooo, asdf*";
constexpr ll_char_t str2[15] = "Holoooo, asdf?";
constexpr ll_char_t str3[27] = "abcdefghijklmnopqrstuvwxyz";

/************************************* Compare && Equals *************************************/

constexpr i8 cmp1 = compare(str, str2, 16);
constexpr CompareData<ll_char_t> cmp2 = compare<ll_char_t, LL_TRUE>(str, str2, 16);

constexpr ll_bool_t cmp_b_1 = equals(str, str2);

/************************************* Finders *************************************/

constexpr len_t find_pos_1 = find_pos(str, ',');
constexpr len_t find_pos_2 = find_pos(str, '*');
constexpr len_t find_pos_3 = find_pos(str2, '?');

constexpr auto find_ptr_1 = find(str, ',');
constexpr auto find_ptr_2 = find(str, str + 15, '*');
constexpr auto find_ptr_3 = find(str2, str2 + 15, '?');

constexpr len_t rfind_pos_1 = rfind_pos(str, ',');
constexpr len_t rfind_pos_2 = rfind_pos(str, '*');
constexpr len_t rfind_pos_3 = rfind_pos(str2, '?');
constexpr len_t rfind_pos_4 = rfind_pos(str2, '\0');

constexpr auto rfind_ptr_1 = rfind(str, ',');
constexpr auto rfind_ptr_2 = rfind(str, '*');
constexpr auto rfind_ptr_3 = rfind(str2, '?');
constexpr auto rfind_ptr_4 = rfind(str2, '\0');

//constexpr auto binarysearch_ptr_1 = binarysearch<ll_char_t>(str3, 'b');
//constexpr auto binarysearch_ptr_1 = binarysearch<ll_char_t>(str3, 'c');
//constexpr auto binarysearch_ptr_1 = binarysearch<ll_char_t>(str3, 'd');
//constexpr auto binarysearch_ptr_2 = binarysearch<ll_char_t>(str3, 'y');

/************************************* Reverse *************************************/

constexpr len_t reverse_example(int pos) {
	len_t block[10]{};
	for (len_t i{}; i < 10; ++i)
		block[i] = i;
	reverse<len_t>(block);
	return block[pos];
}

constexpr len_t reverse_0 = reverse_example(0);
constexpr len_t reverse_1 = reverse_example(1);
constexpr len_t reverse_2 = reverse_example(2);
constexpr len_t reverse_3 = reverse_example(3);
constexpr len_t reverse_4 = reverse_example(4);
constexpr len_t reverse_5 = reverse_example(5);
constexpr len_t reverse_6 = reverse_example(6);

/************************************* Fill *************************************/

constexpr len_t fill_example(int pos) {
	len_t block[10]{};
	for (len_t i{}; i < 10; ++i) block[i] = i;

	fill<len_t>(block, 7);

	return block[pos];
}

constexpr len_t fill_0 = fill_example(0);
constexpr len_t fill_1 = fill_example(1);
constexpr len_t fill_2 = fill_example(2);
constexpr len_t fill_3 = fill_example(3);
constexpr len_t fill_4 = fill_example(4);
constexpr len_t fill_5 = fill_example(5);
constexpr len_t fill_6 = fill_example(6);
constexpr len_t fill_7 = fill_example(9);

/************************************* Shift left *************************************/

constexpr len_t shift_left_example(int pos) {
	len_t block[10]{};
	for (len_t i{}; i < 10; ++i) block[i] = i;

	shiftLeft<len_t>(block, block + 10, 5, 999);

	return block[pos];
}

constexpr len_t shift_left_0 = shift_left_example(0);
constexpr len_t shift_left_1 = shift_left_example(1);
constexpr len_t shift_left_2 = shift_left_example(2);
constexpr len_t shift_left_3 = shift_left_example(3);
constexpr len_t shift_left_4 = shift_left_example(4);
constexpr len_t shift_left_5 = shift_left_example(5);
constexpr len_t shift_left_6 = shift_left_example(6);
constexpr len_t shift_left_7 = shift_left_example(7);
constexpr len_t shift_left_8 = shift_left_example(8);
constexpr len_t shift_left_9 = shift_left_example(9);

/************************************* Shift right *************************************/

constexpr len_t shift_right_example(int pos) {
	len_t block[10]{};
	for (len_t i{}; i < 10; ++i) block[i] = i;

	shifRight<len_t>(block, block + 10, 5, 999);

	return block[pos];
}

constexpr len_t shift_left_0 = shift_right_example(0);
constexpr len_t shift_left_1 = shift_right_example(1);
constexpr len_t shift_left_2 = shift_right_example(2);
constexpr len_t shift_left_3 = shift_right_example(3);
constexpr len_t shift_left_4 = shift_right_example(4);
constexpr len_t shift_left_5 = shift_right_example(5);
constexpr len_t shift_left_6 = shift_right_example(6);
constexpr len_t shift_left_7 = shift_right_example(7);
constexpr len_t shift_left_8 = shift_right_example(8);
constexpr len_t shift_left_9 = shift_right_example(9);


/*************************************/

/*
#pragma region Compare

enum class CompareResult : i8 {
	Unknown,
	Same,
	FirstGreater,
	SecondGreater,

	NotSameSize,
};

template<class T>
__LL_NODISCARD__ constexpr i8 compare(const T* v1, const T* v2, len_t size) noexcept(true) {
	static_assert(traits::has_no_equal_operator_v<T>, "Error, <T> object has no operator!=()");
	static_assert(traits::has_greater_operator_v<T>, "Error, <T> object has no operator>()");

	for (; 0 < size; --size, ++v1, ++v2)
		if (*v1 != *v2)
			return *v1 > *v2 ? 1 : -1;
	return 0;
}
template<class T>
__LL_NODISCARD__ constexpr CompareResult compare(const T* v1, const T* v2, len_t size) noexcept(true) {
	static_assert(traits::has_no_equal_operator_v<T>, "Error, <T> object has no operator!=()");
	static_assert(traits::has_greater_operator_v<T>, "Error, <T> object has no operator>()");

	for (; 0 < size; --size, ++v1, ++v2)
		if (*v1 != *v2)
			return *v1 > *v2 ? CompareResult::FirstGreater : CompareResult::SecondGreater;
	return CompareResult::Same;
}
template<class T>
__LL_NODISCARD__ constexpr CompareResult compare(const T* v1, const len_t size1, const T* v2, const len_t size2) noexcept(true) {
	return (size1 == size2) ? compare<T>(v1, v2, size1) == 0 : LL_FALSE;
}
template<class T, len_t size1, len_t size2 = size1>
__LL_NODISCARD__ constexpr CompareResult compare(const T* v1, const T* v2) noexcept(true) {
	return (size1 == size2) ? compare<T>(v1, v2, size1) == 0 : LL_FALSE;
}
template<class T, len_t size1, len_t size2>
__LL_NODISCARD__ constexpr CompareResult compare(const T(&v1)[size1], const T(&v2)[size2]) noexcept(true) {
	return (size1 == size2) ? compare<T>(v1, v2, size1) == 0 : LL_FALSE;
}

#pragma endregion



template<class T, class ObjType = std::conditional_t<traits::is_basic_type_v<T>, T, T&>>
__LL_NODISCARD__ constexpr i8 contains(const T* v, len_t size, const ObjType obj) __LL_EXCEPT__ {
	static_assert(traits::has_equal_operator_v<T>, "Error, <T> object has no operator==()");

	const T* end = v + size;
	for (; v < end; ++v)
		if (*v == obj)
			return LL_TRUE;
	return LL_FALSE;
}

constexpr ll_bool_t is_any(ll_string_t str, const ll_char_t c) {
	return contains()
}
template<len_t N>
constexpr ll_bool_t is_any(const ll_char_t c, const ll_char_t(&str)[N]) {
	ll_string_t end = str + N;
	for (ll_string_t v = str; v < end; ++v)
		if ()
			return LL_FALSE;
	return c <= '9' && c >= '0';
}

*/

} // namespace algorithm
} // namespace traits

#endif // LLANYLIB_EXAMPLES_ALGORITHMEXAMPLE_HPP_
