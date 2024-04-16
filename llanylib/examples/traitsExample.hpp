//////////////////////////////////////////////
//	traitsExample.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 4.2							//
//////////////////////////////////////////////

#include "../traits.hpp"

#if !defined(LLANYLIB_EXAMPLES_TRAITSEXAMPLE_HPP_) && defined(LL_TRAITS_TEST)
#define LLANYLIB_EXAMPLES_TRAITSEXAMPLE_HPP_

namespace llcpp {
namespace traits {

///////////////////////////////////////////////// Conditional for chars types /////////////////////////////////////////////////

using get_by_char_type_res_1 = traits::get_by_char_type_t<ll_char_t, i8, i16, i32>;
using get_by_char_type_res_2 = traits::get_by_char_type_t<ll_uchar_t, i8, i16, i32>;
using get_by_char_type_res_3 = traits::get_by_char_type_t<ll_wchar_t, i8, i16, i32>;

static_assert(std::is_same_v<get_by_char_type_res_1, i8 >, "Error changed value");
static_assert(std::is_same_v<get_by_char_type_res_2, i16>, "Error changed value");
static_assert(std::is_same_v<get_by_char_type_res_3, i32>, "Error changed value");

///////////////////////////////////////////////// Operator and functions checker /////////////////////////////////////////////////

constexpr ll_bool_t has_operator_or_func_res_1 = traits::has_type_operator_v<TestClassBase, ll_bool_t>;
constexpr ll_bool_t has_operator_or_func_res_2 = traits::has_type_operator_v<TestClass, ll_bool_t>;
constexpr ll_bool_t has_operator_or_func_res_3 = traits::has_type_operator_v<TestClassNoCopy, ll_bool_t>;
constexpr ll_bool_t has_operator_or_func_res_4 = traits::has_type_operator_v<int, ll_bool_t>;
constexpr ll_bool_t has_operator_or_func_res_5 = traits::has_clear_v<TestClass>;
constexpr ll_bool_t has_operator_or_func_res_6 = traits::has_clear_v<int>;
constexpr ll_bool_t has_operator_or_func_res_7 = traits::has_swap_v<TestClass>;
constexpr ll_bool_t has_operator_or_func_res_8 = traits::has_swap_v<int>;
constexpr ll_bool_t has_operator_or_func_res_9 = has_type_operator_v<int, int>;
constexpr ll_bool_t test_copy_operator_int = std::is_copy_assignable_v<int>;
constexpr ll_bool_t test_copy_operator_class = std::is_copy_assignable_v<TestClass>;
constexpr ll_bool_t test_copy_operator_class_bad = std::is_copy_assignable_v<TestClassBad>;
constexpr ll_bool_t test_copy_operator_class_private_copy = std::is_copy_assignable_v<TestClassPrivateCopy>;
constexpr ll_bool_t test_copy_operator_class_no_copy = std::is_copy_assignable_v<TestClassNoCopy>;

static_assert( has_operator_or_func_res_1,				"Error changed value");
static_assert( has_operator_or_func_res_2,				"Error changed value");
static_assert(!has_operator_or_func_res_3,				"Error changed value");
static_assert(!has_operator_or_func_res_4,				"Error changed value");
static_assert( has_operator_or_func_res_5,				"Error changed value");
static_assert(!has_operator_or_func_res_6,				"Error changed value");
static_assert( has_operator_or_func_res_7,				"Error changed value");
static_assert(!has_operator_or_func_res_8,				"Error changed value");
static_assert( has_operator_or_func_res_9,				"Error changed value");
static_assert( test_copy_operator_int,					"Error changed value");
static_assert( test_copy_operator_class,				"Error changed value");
static_assert( test_copy_operator_class_bad,			"Error changed value");
static_assert(!test_copy_operator_class_private_copy,	"Error changed value");
static_assert(!test_copy_operator_class_no_copy,		"Error changed value");

///////////////////////////////////////////////// Nothrow checkers /////////////////////////////////////////////////

constexpr ll_bool_t nothrow_copy_test_1 = traits::is_nothrow_copyable_v<int>;
constexpr ll_bool_t nothrow_copy_test_2 = traits::is_nothrow_copyable_v<int*>;
constexpr ll_bool_t nothrow_copy_test_3 = traits::is_nothrow_copyable_v<int**>;
constexpr ll_bool_t nothrow_copy_test_4 = traits::is_nothrow_copyable_v<llcpp::traits::TestClass>;
constexpr ll_bool_t nothrow_copy_test_5 = traits::is_nothrow_copyable_v<llcpp::traits::TestClass*>;
constexpr ll_bool_t nothrow_copy_test_6 = traits::is_nothrow_copyable_v<llcpp::traits::TestClass**>;
constexpr ll_bool_t nothrow_copy_test_7 = traits::is_nothrow_copyable_v<llcpp::traits::TestClassThrow>;
constexpr ll_bool_t nothrow_copy_test_8 = traits::is_nothrow_copyable_v<llcpp::traits::TestClassThrow*>;
constexpr ll_bool_t nothrow_copy_test_9 = traits::is_nothrow_copyable_v<llcpp::traits::TestClassThrow**>;

static_assert( nothrow_copy_test_1, "Error changed value");
static_assert( nothrow_copy_test_2, "Error changed value");
static_assert(!nothrow_copy_test_3, "Error changed value");
static_assert( nothrow_copy_test_4, "Error changed value");
static_assert( nothrow_copy_test_5, "Error changed value");
static_assert(!nothrow_copy_test_6, "Error changed value");
static_assert(!nothrow_copy_test_7, "Error changed value");
static_assert(!nothrow_copy_test_8, "Error changed value");
static_assert(!nothrow_copy_test_9, "Error changed value");

constexpr ll_bool_t nothrow_swappeable_test_1 = traits::is_nothrow_swappeable_v<int>;
constexpr ll_bool_t nothrow_swappeable_test_2 = traits::is_nothrow_swappeable_v<int*>;
constexpr ll_bool_t nothrow_swappeable_test_3 = traits::is_nothrow_swappeable_v<int**>;
constexpr ll_bool_t nothrow_swappeable_test_4 = traits::is_nothrow_swappeable_v<llcpp::traits::TestClass>;
constexpr ll_bool_t nothrow_swappeable_test_5 = traits::is_nothrow_swappeable_v<llcpp::traits::TestClass*>;
constexpr ll_bool_t nothrow_swappeable_test_6 = traits::is_nothrow_swappeable_v<llcpp::traits::TestClass**>;
constexpr ll_bool_t nothrow_swappeable_test_7 = traits::is_nothrow_swappeable_v<llcpp::traits::TestClassThrow>;
constexpr ll_bool_t nothrow_swappeable_test_8 = traits::is_nothrow_swappeable_v<llcpp::traits::TestClassThrow*>;
constexpr ll_bool_t nothrow_swappeable_test_9 = traits::is_nothrow_swappeable_v<llcpp::traits::TestClassThrow**>;

static_assert( nothrow_swappeable_test_1, "Error changed value");
static_assert( nothrow_swappeable_test_2, "Error changed value");
static_assert( nothrow_swappeable_test_3, "Error changed value");
static_assert( nothrow_swappeable_test_4, "Error changed value");
static_assert( nothrow_swappeable_test_5, "Error changed value");
static_assert( nothrow_swappeable_test_6, "Error changed value");
static_assert( nothrow_swappeable_test_8, "Error changed value");
static_assert(!nothrow_swappeable_test_7, "Error changed value");
static_assert( nothrow_swappeable_test_9, "Error changed value");

///////////////////////////////////////////////// Example strings /////////////////////////////////////////////////

constexpr ll_bool_t checker_test_1 = traits::operator_type_call_checker_v<int, ll_bool_t>;
constexpr ll_bool_t checker_test_2 = traits::operator_type_call_checker_v<int*, ll_bool_t>;
constexpr ll_bool_t checker_test_3 = traits::operator_type_call_checker_v<int**, ll_bool_t>;
constexpr ll_bool_t checker_test_4 = traits::operator_type_call_checker_v<TestClass, ll_bool_t>;
constexpr ll_bool_t checker_test_5 = traits::operator_type_call_checker_v<TestClass*, ll_bool_t>;
constexpr ll_bool_t checker_test_6 = traits::operator_type_call_checker_v<TestClass**, ll_bool_t>;
constexpr ll_bool_t checker_test_7 = traits::operator_type_call_checker_v<TestClassThrow, ll_bool_t>;
constexpr ll_bool_t checker_test_8 = traits::operator_type_call_checker_v<TestClassThrow*, ll_bool_t>;
constexpr ll_bool_t checker_test_9 = traits::operator_type_call_checker_v<TestClassThrow**, ll_bool_t>;

static_assert( checker_test_1, "Error changed value");
static_assert( checker_test_2, "Error changed value");
static_assert( checker_test_3, "Error changed value");
static_assert( checker_test_4, "Error changed value");
static_assert( checker_test_5, "Error changed value");
static_assert( checker_test_6, "Error changed value");
static_assert(!checker_test_7, "Error changed value");
static_assert(!checker_test_8, "Error changed value");
static_assert( checker_test_9, "Error changed value");

///////////////////////////////////////////////// Example strings /////////////////////////////////////////////////


} // namespace llcpp
} // namespace traits

#endif // LLANYLIB_EXAMPLES_TRAITSEXAMPLE_HPP_
