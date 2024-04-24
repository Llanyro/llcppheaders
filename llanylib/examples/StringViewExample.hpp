//////////////////////////////////////////////
//	StringViewExample.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#ifndef LLANYLIB_EXAMPLES_STRINGVIEWEXAMPLE_HPP_
#define LLANYLIB_EXAMPLES_STRINGVIEWEXAMPLE_HPP_

#include "../StringView.hpp"
#include "algorithmExample.hpp"

namespace llcpp {

///////////////////////////////////////////////// ArrayView Storage /////////////////////////////////////////////////

constexpr auto stringview_01 = StringView(algorithm::str1);
constexpr auto stringview_02 = StringView(algorithm::str2);
constexpr auto stringview_03 = StringView(algorithm::str3);
constexpr auto stringview_04 = StringView(algorithm::str4);
constexpr auto stringview_05 = StringView("");
constexpr auto stringview_06 = StringView("A");
constexpr auto stringview_07 = StringView("Hello");
constexpr auto stringview_08 = StringView("Hello world");
constexpr auto stringview_09 = StringView("Holo");

constexpr StringView HOLA_WORLD = algorithm::str4;

///////////////////////////////////////////////// Compare /////////////////////////////////////////////////

constexpr cmp_t compare_01 = stringview_07.compare("Hello");
constexpr cmp_t compare_02 = stringview_07.compare("Holla");
constexpr cmp_t compare_03 = stringview_07.compare("?????");
constexpr cmp_t compare_04 = stringview_06.compare("H");
constexpr cmp_t compare_05 = stringview_05.compare("");

constexpr auto compare_01_res = stringview_07.compare<true>("Hello");
constexpr auto compare_02_res = stringview_07.compare<true>("Holla");
constexpr auto compare_03_res = stringview_07.compare<true>("?????");
constexpr auto compare_04_res = stringview_06.compare<true>("H");
constexpr auto compare_05_res = stringview_05.compare<true>("");

static_assert(compare_01 == 00, "Error changed value");
static_assert(compare_02 == -1, "Error changed value");
static_assert(compare_03 == 01, "Error changed value");
static_assert(compare_04 == -1, "Error changed value");
static_assert(compare_05 == 00, "Error changed value");

static_assert(compare_01_res.result == 00, "Error changed value");
static_assert(compare_02_res.result == -1, "Error changed value");
static_assert(compare_03_res.result == 01, "Error changed value");
static_assert(compare_04_res.result == -1, "Error changed value");
static_assert(compare_05_res.result == 00, "Error changed value");

///////////////////////////////////////////////// Equals /////////////////////////////////////////////////

constexpr ll_bool_t equals_01 = stringview_07.equals("Hello");
constexpr ll_bool_t equals_02 = stringview_07.equals("Holla");
constexpr ll_bool_t equals_03 = stringview_01.equals(stringview_01);
constexpr ll_bool_t equals_04 = stringview_01.equals(stringview_02);
constexpr ll_bool_t equals_05 = stringview_03.equals(stringview_04);
constexpr ll_bool_t equals_06 = stringview_05.equals(stringview_06);

static_assert(equals_01 ==  LL_TRUE, "Error changed value");
static_assert(equals_02 == LL_FALSE, "Error changed value");
static_assert(equals_03 ==  LL_TRUE, "Error changed value");
static_assert(equals_04 == LL_FALSE, "Error changed value");
static_assert(equals_05 == LL_FALSE, "Error changed value");
static_assert(equals_06 == LL_FALSE, "Error changed value");

///////////////////////////////////////////////// Operator== /////////////////////////////////////////////////

constexpr ll_bool_t operator_eq_01 = stringview_07 == "Hello";
constexpr ll_bool_t operator_eq_02 = stringview_07 == "Holla";
constexpr ll_bool_t operator_eq_03 = stringview_01 == stringview_01;
constexpr ll_bool_t operator_eq_04 = stringview_01 == stringview_02;
constexpr ll_bool_t operator_eq_05 = stringview_03 == stringview_04;
constexpr ll_bool_t operator_eq_06 = stringview_05 == stringview_06;

static_assert(operator_eq_01 ==  LL_TRUE, "Error changed value");
static_assert(operator_eq_02 == LL_FALSE, "Error changed value");
static_assert(operator_eq_03 ==  LL_TRUE, "Error changed value");
static_assert(operator_eq_04 == LL_FALSE, "Error changed value");
static_assert(operator_eq_05 == LL_FALSE, "Error changed value");
static_assert(operator_eq_06 == LL_FALSE, "Error changed value");

///////////////////////////////////////////////// starstwith /////////////////////////////////////////////////

constexpr ll_bool_t starts_with_01 = stringview_06.starts_with("A");
constexpr ll_bool_t starts_with_02 = stringview_05.starts_with("A");
constexpr ll_bool_t starts_with_03 = stringview_05.starts_with("");
constexpr ll_bool_t starts_with_04 = stringview_01.starts_with(stringview_05);
constexpr ll_bool_t starts_with_05 = stringview_01.starts_with(stringview_06);
constexpr ll_bool_t starts_with_06 = stringview_01.starts_with(stringview_09);
constexpr ll_bool_t starts_with_07 = stringview_01.starts_with("Holo");

constexpr auto starts_with_01_res = stringview_06.starts_with<true>("A");
constexpr auto starts_with_02_res = stringview_05.starts_with<true>("A");
constexpr auto starts_with_03_res = stringview_05.starts_with<true>("");
constexpr auto starts_with_04_res = stringview_01.starts_with<true>(stringview_05);
constexpr auto starts_with_05_res = stringview_01.starts_with<true>(stringview_06);
constexpr auto starts_with_06_res = stringview_01.starts_with<true>(stringview_09);
constexpr auto starts_with_07_res = stringview_01.starts_with<true>("Holo");

static_assert(starts_with_01 ==  LL_TRUE, "Error changed value");
static_assert(starts_with_02 == LL_FALSE, "Error changed value");
static_assert(starts_with_03 ==  LL_TRUE, "Error changed value");
static_assert(starts_with_04 == LL_FALSE, "Error changed value");
static_assert(starts_with_05 == LL_FALSE, "Error changed value");
static_assert(starts_with_06 ==  LL_TRUE, "Error changed value");
static_assert(starts_with_07 ==  LL_TRUE, "Error changed value");

static_assert(starts_with_01_res.result ==  LL_TRUE, "Error changed value");
static_assert(starts_with_02_res.result == LL_FALSE, "Error changed value");
static_assert(starts_with_03_res.result ==  LL_TRUE, "Error changed value");
static_assert(starts_with_04_res.result == LL_FALSE, "Error changed value");
static_assert(starts_with_05_res.result == LL_FALSE, "Error changed value");
static_assert(starts_with_06_res.result ==  LL_TRUE, "Error changed value");
static_assert(starts_with_07_res.result ==  LL_TRUE, "Error changed value");

///////////////////////////////////////////////// endswith /////////////////////////////////////////////////

constexpr ll_bool_t ends_with_01 = stringview_01.ends_with("*");
constexpr ll_bool_t ends_with_02 = stringview_02.ends_with("?");
constexpr ll_bool_t ends_with_03 = stringview_03.ends_with("z");
constexpr ll_bool_t ends_with_04 = stringview_05.ends_with("");
constexpr ll_bool_t ends_with_05 = stringview_06.ends_with("A");
constexpr ll_bool_t ends_with_06 = stringview_01.ends_with('*');
constexpr ll_bool_t ends_with_07 = stringview_02.ends_with('?');
constexpr ll_bool_t ends_with_08 = stringview_03.ends_with('z');
constexpr ll_bool_t ends_with_09 = stringview_05.ends_with('\0');
constexpr ll_bool_t ends_with_10 = stringview_06.ends_with('A');


constexpr auto ends_with_01 = stringview_01.ends_with<true>("*");
constexpr auto ends_with_02 = stringview_02.ends_with<true>("?");
constexpr auto ends_with_03 = stringview_03.ends_with<true>("z");
constexpr auto ends_with_04 = stringview_05.ends_with<true>("");
constexpr auto ends_with_05 = stringview_06.ends_with<true>("A");
constexpr auto ends_with_06 = stringview_01.ends_with<true>('*');
constexpr auto ends_with_07 = stringview_02.ends_with<true>('?');
constexpr auto ends_with_08 = stringview_03.ends_with<true>('z');
constexpr auto ends_with_09 = stringview_05.ends_with<true>('\0');
constexpr auto ends_with_10 = stringview_06.ends_with<true>('A');


static_assert(ends_with_01 ==  LL_TRUE, "Error changed value");
static_assert(ends_with_02 ==  LL_TRUE, "Error changed value");
static_assert(ends_with_03 ==  LL_TRUE, "Error changed value");
static_assert(ends_with_04 ==  LL_TRUE, "Error changed value");
static_assert(ends_with_05 ==  LL_TRUE, "Error changed value");
static_assert(ends_with_06 ==  LL_TRUE, "Error changed value");
static_assert(ends_with_07 ==  LL_TRUE, "Error changed value");
static_assert(ends_with_08 ==  LL_TRUE, "Error changed value");
static_assert(ends_with_09 ==  LL_TRUE, "Error changed value");
static_assert(ends_with_10 ==  LL_TRUE, "Error changed value");

///////////////////////////////////////////////// find /////////////////////////////////////////////////

constexpr len_t find_pos_01 = stringview_01.find_pos('*');
constexpr len_t find_pos_02 = stringview_02.find_pos('?');
constexpr len_t find_pos_03 = stringview_05.find_pos('\0');
constexpr len_t find_pos_04 = stringview_06.find_pos('A');
constexpr len_t find_pos_05 = stringview_05.find_pos('?');
constexpr len_t find_pos_06 = stringview_06.find_pos('n');

constexpr auto find_01 = stringview_01.find('*');
constexpr auto find_02 = stringview_02.find('?');
constexpr auto find_03 = stringview_05.find('\0');
constexpr auto find_04 = stringview_06.find('A');
constexpr auto find_05 = stringview_05.find('?');
constexpr auto find_06 = stringview_06.find('n');

static_assert(find_pos_01 == 13, "Error changed value");
static_assert(find_pos_02 == 13, "Error changed value");
static_assert(find_pos_03 == 00, "Error changed value");
static_assert(find_pos_04 == 00, "Error changed value");
static_assert(find_pos_05 == algorithm::npos, "Error changed value");
static_assert(find_pos_06 == algorithm::npos, "Error changed value");

static_assert(*find_01 == '*', "Error changed value");
static_assert(*find_02 == '?', "Error changed value");
static_assert(*find_03 == '\0', "Error changed value");
static_assert(*find_04 == 'A', "Error changed value");
static_assert( find_05 == stringview_05.end(), "Error changed value");
static_assert( find_06 == stringview_06.end(), "Error changed value");

///////////////////////////////////////////////// rfind /////////////////////////////////////////////////

constexpr len_t rfind_pos_01 = stringview_01.rfind_pos('*');
constexpr len_t rfind_pos_02 = stringview_02.rfind_pos('?');
constexpr len_t rfind_pos_03 = stringview_05.rfind_pos('\0');
constexpr len_t rfind_pos_04 = stringview_06.rfind_pos('A');
constexpr len_t rfind_pos_05 = stringview_05.rfind_pos('?');
constexpr len_t rfind_pos_06 = stringview_06.rfind_pos('n');

constexpr auto rfind_01 = stringview_01.rfind('*');
constexpr auto rfind_02 = stringview_02.rfind('?');
constexpr auto rfind_03 = stringview_05.rfind('\0');
constexpr auto rfind_04 = stringview_06.rfind('A');
constexpr auto rfind_05 = stringview_05.rfind('?');
constexpr auto rfind_06 = stringview_06.rfind('n');

static_assert(rfind_pos_01 == 13, "Error changed value");
static_assert(rfind_pos_02 == 13, "Error changed value");
static_assert(rfind_pos_03 == 00, "Error changed value");
static_assert(rfind_pos_04 == 00, "Error changed value");
static_assert(rfind_pos_05 == algorithm::npos, "Error changed value");
static_assert(rfind_pos_06 == algorithm::npos, "Error changed value");

static_assert(*rfind_01 == '*', "Error changed value");
static_assert(*rfind_02 == '?', "Error changed value");
static_assert(*rfind_03 == '\0', "Error changed value");
static_assert(*rfind_04 == 'A', "Error changed value");
static_assert( rfind_05 == stringview_05.end(), "Error changed value");
static_assert( rfind_06 == stringview_06.end(), "Error changed value");

} // namespace llcpp

#endif // LLANYLIB_EXAMPLES_STRINGVIEWEXAMPLE_HPP_
