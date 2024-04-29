//////////////////////////////////////////////
//	algorithmExample.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#include "../algorithm.hpp"

#if !defined(LLANYLIB_EXAMPLES_ALGORITHMEXAMPLE_HPP_)
#define LLANYLIB_EXAMPLES_ALGORITHMEXAMPLE_HPP_

namespace llcpp {
namespace algorithm {

///////////////////////////////////////////////// Example strings /////////////////////////////////////////////////

constexpr ll_char_t str1[] = "Holoooo, asdf*";
constexpr ll_char_t str2[] = "Holoooo, asdf?";
constexpr ll_char_t str3[] = "abcdefghijklmnopqrstuvwxyz";
constexpr ll_char_t str4[] = "Hola world!";

///////////////////////////////////////////////// Compare && Equals /////////////////////////////////////////////////

using cmp = compare_cluster<ll_char_t>;
using cmp_res = compare_cluster<ll_char_t, ll_char_t, LL_TRUE>;
using find = finders_cluster<ll_char_t, LL_FALSE>;
using find_pos = finders_cluster<ll_char_t, LL_TRUE>;

constexpr i8 cmp1 = cmp::compare(str1, str2, 15);
constexpr auto cmp2 = cmp_res::compare(str1, str2, 15);

static_assert(cmp1 == -1, "Error changed value");
static_assert(cmp2.getResult() == -1, "Error changed value");

constexpr ll_bool_t equals_01 = cmp::equals(str1, str2);
constexpr ll_bool_t equals_02 = cmp::equals("Holo", "Holo");
constexpr ll_bool_t equals_03 = cmp::equals("Holo", "Hi");

constexpr auto equals_04 = cmp_res::equals(str1, str2);
constexpr auto equals_05 = cmp_res::equals("Holo", "Holo");
constexpr auto equals_06 = cmp_res::equals("Holo", "Hi");

static_assert(!equals_01, "Error changed value");
static_assert( equals_02, "Error changed value");
static_assert(!equals_03, "Error changed value");

static_assert(!equals_04.getResult(), "Error changed value");
static_assert( equals_05.getResult(), "Error changed value");
static_assert(!equals_06.getResult(), "Error changed value");

///////////////////////////////////////////////// Starts with /////////////////////////////////////////////////

constexpr ll_bool_t starts_with_01 = cmp::starts_with(str1, 14, str2, 14);
constexpr ll_bool_t starts_with_02 = cmp::starts_with(str1, 13, str2, 13);
constexpr ll_bool_t starts_with_03 = cmp::starts_with(str1, "Holoo");
constexpr ll_bool_t starts_with_04 = cmp::starts_with(str1, 15, "Holoo", 4);

constexpr auto starts_with_01_res = cmp_res::starts_with(str1, 14, str2, 14);
constexpr auto starts_with_02_res = cmp_res::starts_with(str1, 13, str2, 13);
constexpr auto starts_with_03_res = cmp_res::starts_with(str1, "Holoo");
constexpr auto starts_with_04_res = cmp_res::starts_with(str1, 15, "Holoo", 4);

static_assert(!starts_with_01, "Error changed value");
static_assert( starts_with_02, "Error changed value");
static_assert(!starts_with_03, "Error changed value");
static_assert( starts_with_04, "Error changed value");

static_assert(!starts_with_01_res.getResult(), "Error changed value");
static_assert( starts_with_02_res.getResult(), "Error changed value");
static_assert(!starts_with_03_res.getResult(), "Error changed value");
static_assert( starts_with_04_res.getResult(), "Error changed value");

///////////////////////////////////////////////// Ends with /////////////////////////////////////////////////

constexpr ll_bool_t ends_with_01 = cmp::ends_with(str1, 14, str2, 14);
constexpr ll_bool_t ends_with_02 = cmp::ends_with(str1, 13, str2, 13);
constexpr ll_bool_t ends_with_03 = cmp::ends_with(str1, "asdf*");
constexpr ll_bool_t ends_with_04 = cmp::ends_with(str1, 15, "asdf*", 4);

constexpr auto ends_with_01_res = cmp_res::ends_with(str1, 14, str2, 14);
constexpr auto ends_with_02_res = cmp_res::ends_with(str1, 13, str2, 13);
constexpr auto ends_with_03_res = cmp_res::ends_with(str1, "asdf*");
constexpr auto ends_with_04_res = cmp_res::ends_with(str1, 15, "asdf*", 4);

static_assert(ends_with_01 == LL_FALSE, "Error changed value");
static_assert(ends_with_02 == LL_TRUE , "Error changed value");
static_assert(ends_with_03 == LL_TRUE , "Error changed value");	// Here is different to start_with cause the '\0' at end
static_assert(ends_with_04 == LL_FALSE, "Error changed value");	// Here is different to start_with cause the '\0' at end

static_assert(!ends_with_01_res.getResult(), "Error changed value");
static_assert( ends_with_02_res.getResult(), "Error changed value");
static_assert( ends_with_03_res.getResult(), "Error changed value");	// Here is different to start_with cause the '\0' at end
static_assert(!ends_with_04_res.getResult(), "Error changed value");	// Here is different to start_with cause the '\0' at end

///////////////////////////////////////////////// Finders /////////////////////////////////////////////////

constexpr len_t find_pos_01 = find_pos::find(str1, ',');
constexpr len_t find_pos_02 = find_pos::find(str1, '*');
constexpr len_t find_pos_03 = find_pos::find(str2, '?');

constexpr auto find_ptr_01 = find::find(str1, ',');
constexpr auto find_ptr_02 = find::find(str1, str1 + 15, '*');
constexpr auto find_ptr_03 = find::find(str2, str2 + 15, '?');

constexpr len_t rfind_pos_01 = find_pos::rfind(str1, ',');
constexpr len_t rfind_pos_02 = find_pos::rfind(str1, '*');
constexpr len_t rfind_pos_03 = find_pos::rfind(str2, '?');
constexpr len_t rfind_pos_04 = find_pos::rfind(str2, '\0');

constexpr auto rfind_ptr_01 = find::rfind(str1, ',');
constexpr auto rfind_ptr_02 = find::rfind(str1, '*');
constexpr auto rfind_ptr_03 = find::rfind(str2, '?');
constexpr auto rfind_ptr_04 = find::rfind(str2, '\0');

static_assert(find_pos_01 == 07, "Error changed value");
static_assert(find_pos_02 == 13, "Error changed value");
static_assert(find_pos_03 == 13, "Error changed value");

static_assert(*find_ptr_01 == ',', "Error changed value");
static_assert(*find_ptr_02 == '*', "Error changed value");
static_assert(*find_ptr_03 == '?', "Error changed value");

static_assert(rfind_pos_01 == 07, "Error changed value");
static_assert(rfind_pos_02 == 13, "Error changed value");
static_assert(rfind_pos_03 == 13, "Error changed value");
static_assert(rfind_pos_04 == 14, "Error changed value");

static_assert(*rfind_ptr_01 == ',', "Error changed value");
static_assert(*rfind_ptr_02 == '*', "Error changed value");
static_assert(*rfind_ptr_03 == '?', "Error changed value");
static_assert(*rfind_ptr_04 == '\0', "Error changed value");

//constexpr auto binarysearch_ptr_1 = binarysearch<ll_char_t>(str3, 'b');
//constexpr auto binarysearch_ptr_1 = binarysearch<ll_char_t>(str3, 'c');
//constexpr auto binarysearch_ptr_1 = binarysearch<ll_char_t>(str3, 'd');
//constexpr auto binarysearch_ptr_2 = binarysearch<ll_char_t>(str3, 'y');

///////////////////////////////////////////////// Reverse /////////////////////////////////////////////////

constexpr len_t reverse_example(int pos) {
	len_t block[10]{};
	for (len_t i{}; i < 10; ++i)
		block[i] = i;
	reverse<len_t>(block);
	return block[pos];
}

constexpr len_t reverse_00 = reverse_example(0);
constexpr len_t reverse_01 = reverse_example(1);
constexpr len_t reverse_02 = reverse_example(2);
constexpr len_t reverse_03 = reverse_example(3);
constexpr len_t reverse_04 = reverse_example(4);
constexpr len_t reverse_05 = reverse_example(5);
constexpr len_t reverse_06 = reverse_example(6);
constexpr len_t reverse_07 = reverse_example(7);
constexpr len_t reverse_08 = reverse_example(8);
constexpr len_t reverse_09 = reverse_example(9);

static_assert(reverse_00 == 9, "Error changed value");
static_assert(reverse_01 == 8, "Error changed value");
static_assert(reverse_02 == 7, "Error changed value");
static_assert(reverse_03 == 6, "Error changed value");
static_assert(reverse_04 == 5, "Error changed value");
static_assert(reverse_05 == 4, "Error changed value");
static_assert(reverse_06 == 3, "Error changed value");
static_assert(reverse_07 == 2, "Error changed value");
static_assert(reverse_08 == 1, "Error changed value");
static_assert(reverse_09 == 0, "Error changed value");

///////////////////////////////////////////////// Fill /////////////////////////////////////////////////

constexpr len_t fill_example(int pos, int val) {
	len_t block[10]{};
	for (len_t i{}; i < 10; ++i) block[i] = i;

	fill<len_t>(block, val);

	return block[pos];
}

constexpr len_t fill_00 = fill_example(0, 0);
constexpr len_t fill_01 = fill_example(1, 1);
constexpr len_t fill_02 = fill_example(2, 2);
constexpr len_t fill_03 = fill_example(3, 3);
constexpr len_t fill_04 = fill_example(4, 4);
constexpr len_t fill_05 = fill_example(5, 5);
constexpr len_t fill_06 = fill_example(6, 6);
constexpr len_t fill_07 = fill_example(7, 7);
constexpr len_t fill_08 = fill_example(8, 8);
constexpr len_t fill_09 = fill_example(9, 9);

static_assert(fill_00 == 0, "Error changed value");
static_assert(fill_01 == 1, "Error changed value");
static_assert(fill_02 == 2, "Error changed value");
static_assert(fill_03 == 3, "Error changed value");
static_assert(fill_04 == 4, "Error changed value");
static_assert(fill_05 == 5, "Error changed value");
static_assert(fill_06 == 6, "Error changed value");
static_assert(fill_07 == 7, "Error changed value");
static_assert(fill_08 == 8, "Error changed value");
static_assert(fill_09 == 9, "Error changed value");

///////////////////////////////////////////////// Shift left /////////////////////////////////////////////////

constexpr len_t shift_left_example(int pos) {
	len_t block[10]{};
	for (len_t i{}; i < 10; ++i) block[i] = i;

	shiftLeft<len_t>(block, block + 10, 5, 999);

	return block[pos];
}

constexpr len_t shift_left_00 = shift_left_example(0);
constexpr len_t shift_left_01 = shift_left_example(1);
constexpr len_t shift_left_02 = shift_left_example(2);
constexpr len_t shift_left_03 = shift_left_example(3);
constexpr len_t shift_left_04 = shift_left_example(4);
constexpr len_t shift_left_05 = shift_left_example(5);
constexpr len_t shift_left_06 = shift_left_example(6);
constexpr len_t shift_left_07 = shift_left_example(7);
constexpr len_t shift_left_08 = shift_left_example(8);
constexpr len_t shift_left_09 = shift_left_example(9);

static_assert(shift_left_00 == 999, "Error changed value");
static_assert(shift_left_01 == 999, "Error changed value");
static_assert(shift_left_02 == 999, "Error changed value");
static_assert(shift_left_03 == 999, "Error changed value");
static_assert(shift_left_04 == 999, "Error changed value");
static_assert(shift_left_05 == 000, "Error changed value");
static_assert(shift_left_06 == 001, "Error changed value");
static_assert(shift_left_07 == 002, "Error changed value");
static_assert(shift_left_08 == 003, "Error changed value");
static_assert(shift_left_09 == 004, "Error changed value");

///////////////////////////////////////////////// Shift right /////////////////////////////////////////////////

constexpr len_t shift_right_example(int pos) {
	len_t block[10]{};
	for (len_t i{}; i < 10; ++i) block[i] = i;

	shifRight<len_t>(block, block + 10, 5, 999);

	return block[pos];
}

constexpr len_t shift_right_00 = shift_right_example(0);
constexpr len_t shift_right_01 = shift_right_example(1);
constexpr len_t shift_right_02 = shift_right_example(2);
constexpr len_t shift_right_03 = shift_right_example(3);
constexpr len_t shift_right_04 = shift_right_example(4);
constexpr len_t shift_right_05 = shift_right_example(5);
constexpr len_t shift_right_06 = shift_right_example(6);
constexpr len_t shift_right_07 = shift_right_example(7);
constexpr len_t shift_right_08 = shift_right_example(8);
constexpr len_t shift_right_09 = shift_right_example(9);

static_assert(shift_right_00 == 005, "Error changed value");
static_assert(shift_right_01 == 006, "Error changed value");
static_assert(shift_right_02 == 007, "Error changed value");
static_assert(shift_right_03 ==   8, "Error changed value");
static_assert(shift_right_04 ==   9, "Error changed value");
static_assert(shift_right_05 == 999, "Error changed value");
static_assert(shift_right_06 == 999, "Error changed value");
static_assert(shift_right_07 == 999, "Error changed value");
static_assert(shift_right_08 == 999, "Error changed value");
static_assert(shift_right_09 == 999, "Error changed value");

//////////////////////////////////////////////////

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
