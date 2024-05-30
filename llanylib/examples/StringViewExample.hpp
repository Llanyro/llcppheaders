//////////////////////////////////////////////
//	StringViewExample.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#ifndef LLANYLIB_EXAMPLES_STRINGVIEWEXAMPLE_HPP_
#define LLANYLIB_EXAMPLES_STRINGVIEWEXAMPLE_HPP_

#include "algorithmExample.hpp"

namespace llcpp {
namespace meta {

///////////////////////////////////////////////// ArrayView Storage /////////////////////////////////////////////////

constexpr auto stringview_01 = make_StringView(algorithm::str1);
constexpr auto stringview_02 = make_StringView(algorithm::str2);
constexpr auto stringview_03 = make_StringView(algorithm::str3);
constexpr auto stringview_04 = make_StringView(algorithm::str4);
constexpr auto stringview_05 = make_StringView("");
constexpr auto stringview_06 = make_StringView("A");
constexpr auto stringview_07 = make_StringView("Hello");
constexpr auto stringview_08 = make_StringView("Hello world");
constexpr auto stringview_09 = make_StringView("Holo");

//constexpr StringView HOLA_WORLD_STR = algorithm::str4;

///////////////////////////////////////////////// Compare /////////////////////////////////////////////////

constexpr cmp_t compare_str_01 = stringview_07.compare<ll_char_t>("Hello");
constexpr cmp_t compare_str_02 = stringview_07.compare<ll_char_t>("Holla");
constexpr cmp_t compare_str_03 = stringview_07.compare<ll_char_t>("?????");
constexpr cmp_t compare_str_04 = stringview_06.compare<ll_char_t>("H");
constexpr cmp_t compare_str_05 = stringview_05.compare<ll_char_t>("");

constexpr auto compare_str_01_res = stringview_07.compare<ll_char_t, LL_TRUE>("Hello");
constexpr auto compare_str_02_res = stringview_07.compare<ll_char_t, LL_TRUE>("Holla");
constexpr auto compare_str_03_res = stringview_07.compare<ll_char_t, LL_TRUE>("?????");
constexpr auto compare_str_04_res = stringview_06.compare<ll_char_t, LL_TRUE>("H");
constexpr auto compare_str_05_res = stringview_05.compare<ll_char_t, LL_TRUE>("");

static_assert(compare_str_01 == 00, "Error changed value");
static_assert(compare_str_02 == -1, "Error changed value");
static_assert(compare_str_03 == 01, "Error changed value");
static_assert(compare_str_04 == -1, "Error changed value");
static_assert(compare_str_05 == 00, "Error changed value");

static_assert(compare_str_01_res.getResult() == 00, "Error changed value");
static_assert(compare_str_02_res.getResult() == -1, "Error changed value");
static_assert(compare_str_03_res.getResult() == 01, "Error changed value");
static_assert(compare_str_04_res.getResult() == -1, "Error changed value");
static_assert(compare_str_05_res.getResult() == 00, "Error changed value");

///////////////////////////////////////////////// Equals /////////////////////////////////////////////////

constexpr ll_bool_t equals_str_01 = stringview_07.equals<ll_char_t>("Hello");
constexpr ll_bool_t equals_str_02 = stringview_07.equals<ll_char_t>("Holla");
constexpr ll_bool_t equals_str_03 = stringview_01.equals(stringview_01);
constexpr ll_bool_t equals_str_04 = stringview_01.equals(stringview_02);
constexpr ll_bool_t equals_str_05 = stringview_03.equals(stringview_04);
constexpr ll_bool_t equals_str_06 = stringview_05.equals(stringview_06);

static_assert( equals_str_01, "Error changed value");
static_assert(!equals_str_02, "Error changed value");
static_assert( equals_str_03, "Error changed value");
static_assert(!equals_str_04, "Error changed value");
static_assert(!equals_str_05, "Error changed value");
static_assert(!equals_str_06, "Error changed value");

///////////////////////////////////////////////// Operator== /////////////////////////////////////////////////

constexpr ll_bool_t operator_eq_01 = stringview_07 == "Hello";
constexpr ll_bool_t operator_eq_02 = stringview_07 == "Holla";
constexpr ll_bool_t operator_eq_03 = stringview_01 == stringview_01;
constexpr ll_bool_t operator_eq_04 = stringview_01 == stringview_02;
constexpr ll_bool_t operator_eq_05 = stringview_03 == stringview_04;
constexpr ll_bool_t operator_eq_06 = stringview_05 == stringview_06;

static_assert( operator_eq_01, "Error changed value");
static_assert(!operator_eq_02, "Error changed value");
static_assert( operator_eq_03, "Error changed value");
static_assert(!operator_eq_04, "Error changed value");
static_assert(!operator_eq_05, "Error changed value");
static_assert(!operator_eq_06, "Error changed value");

///////////////////////////////////////////////// starstwith /////////////////////////////////////////////////

constexpr ll_bool_t starts_with_str__01 = stringview_06.starts_with<ll_char_t>("A");
constexpr ll_bool_t starts_with_str__02 = stringview_05.starts_with<ll_char_t>("A");
constexpr ll_bool_t starts_with_str__03 = stringview_05.starts_with<ll_char_t>("");
constexpr ll_bool_t starts_with_str__04 = stringview_01.starts_with(stringview_05);
constexpr ll_bool_t starts_with_str__05 = stringview_01.starts_with(stringview_06);
constexpr ll_bool_t starts_with_str__06 = stringview_01.starts_with(stringview_09);
constexpr ll_bool_t starts_with_str__07 = stringview_01.starts_with<ll_char_t>("Holo");
constexpr ll_bool_t starts_with_str__08 = stringview_06.starts_with<ll_char_t>('A');

constexpr auto starts_with_str_01_res = stringview_06.starts_with<char, LL_TRUE>("A");
constexpr auto starts_with_str_02_res = stringview_05.starts_with<char, LL_TRUE>("A");
constexpr auto starts_with_str_03_res = stringview_05.starts_with<char, LL_TRUE>("");
constexpr auto starts_with_str_04_res = stringview_01.starts_with<char, LL_TRUE>(stringview_05);
constexpr auto starts_with_str_05_res = stringview_01.starts_with<char, LL_TRUE>(stringview_06);
constexpr auto starts_with_str_06_res = stringview_01.starts_with<char, LL_TRUE>(stringview_09);
constexpr auto starts_with_str_07_res = stringview_01.starts_with<char, LL_TRUE>("Holo");
constexpr auto starts_with_str_08_res = stringview_06.starts_with<char, LL_TRUE>('A');

static_assert( starts_with_str__01, "Error changed value");
static_assert(!starts_with_str__02, "Error changed value");
static_assert( starts_with_str__03, "Error changed value");
static_assert(!starts_with_str__04, "Error changed value");
static_assert(!starts_with_str__05, "Error changed value");
static_assert( starts_with_str__06, "Error changed value");
static_assert( starts_with_str__07, "Error changed value");
static_assert( starts_with_str__08, "Error changed value");

static_assert( starts_with_str_01_res.getResult(), "Error changed value");
static_assert(!starts_with_str_02_res.getResult(), "Error changed value");
static_assert( starts_with_str_03_res.getResult(), "Error changed value");
static_assert(!starts_with_str_04_res.getResult(), "Error changed value");
static_assert(!starts_with_str_05_res.getResult(), "Error changed value");
static_assert( starts_with_str_06_res.getResult(), "Error changed value");
static_assert( starts_with_str_07_res.getResult(), "Error changed value");
static_assert( starts_with_str_08_res.getResult(), "Error changed value");

///////////////////////////////////////////////// endswith /////////////////////////////////////////////////

constexpr ll_bool_t ends_with_str_01 = stringview_01.ends_with<ll_char_t>("*");
constexpr ll_bool_t ends_with_str_02 = stringview_02.ends_with<ll_char_t>("?");
constexpr ll_bool_t ends_with_str_03 = stringview_03.ends_with<ll_char_t>("z");
constexpr ll_bool_t ends_with_str_04 = stringview_05.ends_with<ll_char_t>("");
constexpr ll_bool_t ends_with_str_05 = stringview_06.ends_with<ll_char_t>("A");
constexpr ll_bool_t ends_with_str_06 = stringview_01.ends_with<ll_char_t>('*');
constexpr ll_bool_t ends_with_str_07 = stringview_02.ends_with<ll_char_t>('?');
constexpr ll_bool_t ends_with_str_08 = stringview_03.ends_with<ll_char_t>('z');
constexpr ll_bool_t ends_with_str_09 = stringview_05.ends_with<ll_char_t>('\0');
constexpr ll_bool_t ends_with_str_10 = stringview_06.ends_with<ll_char_t>('A');

constexpr auto ends_with_str_01_res = stringview_01.ends_with<ll_char_t, LL_TRUE>("*");
constexpr auto ends_with_str_02_res = stringview_02.ends_with<ll_char_t, LL_TRUE>("?");
constexpr auto ends_with_str_03_res = stringview_03.ends_with<ll_char_t, LL_TRUE>("z");
constexpr auto ends_with_str_04_res = stringview_05.ends_with<ll_char_t, LL_TRUE>("");
constexpr auto ends_with_str_05_res = stringview_06.ends_with<ll_char_t, LL_TRUE>("A");
constexpr auto ends_with_str_06_res = stringview_01.ends_with<ll_char_t, LL_TRUE>('*');
constexpr auto ends_with_str_07_res = stringview_02.ends_with<ll_char_t, LL_TRUE>('?');
constexpr auto ends_with_str_08_res = stringview_03.ends_with<ll_char_t, LL_TRUE>('z');
constexpr auto ends_with_str_09_res = stringview_05.ends_with<ll_char_t, LL_TRUE>('\0');
constexpr auto ends_with_str_10_res = stringview_06.ends_with<ll_char_t, LL_TRUE>('A');

static_assert( ends_with_str_01, "Error changed value");
static_assert( ends_with_str_02, "Error changed value");
static_assert( ends_with_str_03, "Error changed value");
static_assert( ends_with_str_04, "Error changed value");
static_assert( ends_with_str_05, "Error changed value");
static_assert( ends_with_str_06, "Error changed value");
static_assert( ends_with_str_07, "Error changed value");
static_assert( ends_with_str_08, "Error changed value");
static_assert(!ends_with_str_09, "Error changed value");
static_assert( ends_with_str_10, "Error changed value");

static_assert( ends_with_str_01_res.getResult(), "Error changed value");
static_assert( ends_with_str_02_res.getResult(), "Error changed value");
static_assert( ends_with_str_03_res.getResult(), "Error changed value");
static_assert( ends_with_str_04_res.getResult(), "Error changed value");
static_assert( ends_with_str_05_res.getResult(), "Error changed value");
static_assert( ends_with_str_06_res.getResult(), "Error changed value");
static_assert( ends_with_str_07_res.getResult(), "Error changed value");
static_assert( ends_with_str_08_res.getResult(), "Error changed value");
static_assert(!ends_with_str_09_res.getResult(), "Error changed value");
static_assert( ends_with_str_10_res.getResult(), "Error changed value");

///////////////////////////////////////////////// find /////////////////////////////////////////////////

constexpr len_t find_str_pos_01 = stringview_01.find<ll_char_t>('*');
constexpr len_t find_str_pos_02 = stringview_02.find<ll_char_t>('?');
constexpr len_t find_str_pos_03 = stringview_05.find<ll_char_t>('\0');
constexpr len_t find_str_pos_04 = stringview_06.find<ll_char_t>('A');
constexpr len_t find_str_pos_05 = stringview_05.find<ll_char_t>('?');
constexpr len_t find_str_pos_06 = stringview_06.find<ll_char_t>('n');

constexpr auto find_str_01 = stringview_01.find<ll_char_t, LL_FALSE>('*');
constexpr auto find_str_02 = stringview_02.find<ll_char_t, LL_FALSE>('?');
constexpr auto find_str_03 = stringview_05.find<ll_char_t, LL_FALSE>('\0');
constexpr auto find_str_04 = stringview_06.find<ll_char_t, LL_FALSE>('A');
constexpr auto find_str_05 = stringview_05.find<ll_char_t, LL_FALSE>('?');
constexpr auto find_str_06 = stringview_06.find<ll_char_t, LL_FALSE>('n');

static_assert( find_str_pos_01 == 13, "Error changed value");
static_assert( find_str_pos_02 == 13, "Error changed value");
static_assert(!find_str_pos_03 == 00, "Error changed value");
static_assert( find_str_pos_04 == 00, "Error changed value");
static_assert( find_str_pos_05 == algorithm::npos, "Error changed value");
static_assert( find_str_pos_06 == algorithm::npos, "Error changed value");

static_assert(*find_str_01 == '*', "Error changed value");
static_assert(*find_str_02 == '?', "Error changed value");
static_assert(*find_str_03 == '\0', "Error changed value");
static_assert(*find_str_04 == 'A', "Error changed value");
static_assert( find_str_05 == stringview_05.end(), "Error changed value");
static_assert( find_str_06 == stringview_06.end(), "Error changed value");

///////////////////////////////////////////////// rfind /////////////////////////////////////////////////

constexpr len_t rfind_str_pos_01 = stringview_01.rfind<ll_char_t>('*');
constexpr len_t rfind_str_pos_02 = stringview_02.rfind<ll_char_t>('?');
constexpr len_t rfind_str_pos_03 = stringview_05.rfind<ll_char_t>('\0');
constexpr len_t rfind_str_pos_04 = stringview_06.rfind<ll_char_t>('A');
constexpr len_t rfind_str_pos_05 = stringview_05.rfind<ll_char_t>('?');
constexpr len_t rfind_str_pos_06 = stringview_06.rfind<ll_char_t>('n');

constexpr auto rfind_str_01 = stringview_01.rfind<ll_char_t, LL_FALSE>('*');
constexpr auto rfind_str_02 = stringview_02.rfind<ll_char_t, LL_FALSE>('?');
constexpr auto rfind_str_03 = stringview_05.rfind<ll_char_t, LL_FALSE>('\0');
constexpr auto rfind_str_04 = stringview_06.rfind<ll_char_t, LL_FALSE>('A');
constexpr auto rfind_str_05 = stringview_05.rfind<ll_char_t, LL_FALSE>('?');
constexpr auto rfind_str_06 = stringview_06.rfind<ll_char_t, LL_FALSE>('n');

static_assert( rfind_str_pos_01 == 13, "Error changed value");
static_assert( rfind_str_pos_02 == 13, "Error changed value");
static_assert(!rfind_str_pos_03 == 00, "Error changed value");
static_assert( rfind_str_pos_04 == 00, "Error changed value");
static_assert( rfind_str_pos_05 == algorithm::npos, "Error changed value");
static_assert( rfind_str_pos_06 == algorithm::npos, "Error changed value");

static_assert(*rfind_str_01 == '*', "Error changed value");
static_assert(*rfind_str_02 == '?', "Error changed value");
static_assert(*rfind_str_03 == '\0', "Error changed value");
static_assert(*rfind_str_04 == 'A', "Error changed value");
static_assert( rfind_str_05 == stringview_05.end(), "Error changed value");
static_assert( rfind_str_06 == stringview_06.end(), "Error changed value");

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXAMPLES_STRINGVIEWEXAMPLE_HPP_
