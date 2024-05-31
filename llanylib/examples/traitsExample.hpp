//////////////////////////////////////////////
//	traitsExample.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#include "../traits.hpp"

#if !defined(LLANYLIB_EXAMPLES_TRAITSEXAMPLE_HPP_) && defined(LL_TRAITS_TEST)
#define LLANYLIB_EXAMPLES_TRAITSEXAMPLE_HPP_

namespace llcpp {
namespace meta {
namespace traits {

///////////////////////////////////////////////// Conditional for chars types /////////////////////////////////////////////////

using get_by_char_type_res_1 = traits::get_by_char_type_t<ll_char_t, i8, i32, void>;
using get_by_char_type_res_2 = traits::get_by_char_type_t<ll_uchar_t, i8, i32, void>;
using get_by_char_type_res_3 = traits::get_by_char_type_t<ll_wchar_t, i8, i32, void>;

static_assert(std::is_same_v<get_by_char_type_res_1, i8>, "Error changed value");
static_assert(std::is_same_v<get_by_char_type_res_2, void>, "Error changed value");
static_assert(std::is_same_v<get_by_char_type_res_3, i32>, "Error changed value");

///////////////////////////////////////////////// Getting types /////////////////////////////////////////////////

using get_raw_type_test_1 = traits::type_conversor<int>::to_raw_t;
using get_raw_type_test_2 = traits::type_conversor<int*****>::to_raw_t;
using get_raw_type_test_3 = traits::type_conversor<int&>::to_raw_t;
using get_raw_type_test_4 = traits::type_conversor<int&&>::to_raw_t;

using get_raw_type_test_5 = traits::type_conversor<const int>::to_raw_t;
using get_raw_type_test_6 = traits::type_conversor<const int*****>::to_raw_t;
using get_raw_type_test_7 = traits::type_conversor<const int&>::to_raw_t;
using get_raw_type_test_8 = traits::type_conversor<const int&&>::to_raw_t;

static_assert(std::is_same_v<get_raw_type_test_1, int>, "Error changed value");
static_assert(std::is_same_v<get_raw_type_test_2, int>, "Error changed value");
static_assert(std::is_same_v<get_raw_type_test_3, int>, "Error changed value");
static_assert(std::is_same_v<get_raw_type_test_4, int>, "Error changed value");
static_assert(std::is_same_v<get_raw_type_test_5, int>, "Error changed value");
static_assert(std::is_same_v<get_raw_type_test_6, int>, "Error changed value");
static_assert(std::is_same_v<get_raw_type_test_7, int>, "Error changed value");
static_assert(std::is_same_v<get_raw_type_test_8, int>, "Error changed value");

using get_const_type_test_1 = traits::type_conversor<int>::to_const_t;
using get_const_type_test_2 = traits::type_conversor<int&>::to_const_t;
using get_const_type_test_3 = traits::type_conversor<int*>::to_const_t;
using get_const_type_test_4 = traits::type_conversor<int&&>::to_const_t;
using get_const_type_test_5 = traits::type_conversor<int**>::to_const_t;
using get_const_type_test_6 = traits::type_conversor<int* const * const>::to_const_t;

static_assert(std::is_same_v<get_const_type_test_1, const int>, "Error changed value");
static_assert(std::is_same_v<get_const_type_test_2, const int&>, "Error changed value");
static_assert(std::is_same_v<get_const_type_test_3, const int*>, "Error changed value");
static_assert(std::is_same_v<get_const_type_test_4, const int&&>, "Error changed value");
static_assert(std::is_same_v<get_const_type_test_5, const int**>, "Error changed value");
static_assert(std::is_same_v<get_const_type_test_6, const int* const* const>, "Error changed value");

using get_reference_type_test_1 = traits::type_conversor<int>::to_reference_t;
using get_reference_type_test_2 = traits::type_conversor<float>::to_reference_t;
using get_reference_type_test_3 = traits::type_conversor<traits::TestClass>::to_reference_all_t;
using get_reference_type_test_4 = traits::type_conversor<traits::TestClassThrow>::to_reference_all_t;
using get_reference_type_test_5 = traits::type_conversor<int*>::to_reference_all_t;
using get_reference_type_test_6 = traits::type_conversor<float*>::to_reference_all_t;
using get_reference_type_test_7 = traits::type_conversor<traits::TestClass*>::to_reference_all_t;
using get_reference_type_test_8 = traits::type_conversor<traits::TestClassThrow*>::to_reference_all_t;

static_assert(std::is_same_v<get_reference_type_test_1, int>, "Error changed value");
static_assert(std::is_same_v<get_reference_type_test_2, float>, "Error changed value");
static_assert(std::is_same_v<get_reference_type_test_3, traits::TestClass&>, "Error changed value");
static_assert(std::is_same_v<get_reference_type_test_4, traits::TestClassThrow&>, "Error changed value");
static_assert(std::is_same_v<get_reference_type_test_5, int*&>, "Error changed value");
static_assert(std::is_same_v<get_reference_type_test_6, float*&>, "Error changed value");
static_assert(std::is_same_v<get_reference_type_test_7, traits::TestClass*&>, "Error changed value");
static_assert(std::is_same_v<get_reference_type_test_8, traits::TestClassThrow*&>, "Error changed value");

using get_const_reference_type_test_1 = traits::type_conversor<int>::to_const_reference_t;
using get_const_reference_type_test_2 = traits::type_conversor<float>::to_const_reference_t;
using get_const_reference_type_test_3 = traits::type_conversor<traits::TestClass>::to_const_reference_t;
using get_const_reference_type_test_4 = traits::type_conversor<traits::TestClassThrow>::to_const_reference_t;
using get_const_reference_type_test_9 = traits::type_conversor<int[5]>::to_const_reference_t;
using get_const_reference_type_test_5 = traits::type_conversor<int*>::to_const_reference_all_t;
using get_const_reference_type_test_6 = traits::type_conversor<float*>::to_const_reference_all_t;
using get_const_reference_type_test_7 = traits::type_conversor<traits::TestClass*>::to_const_reference_all_t;
using get_const_reference_type_test_8 = traits::type_conversor<traits::TestClassThrow*>::to_const_reference_all_t;
using get_const_reference_type_test_10 = traits::type_conversor<int[5]>::to_const_reference_all_t;

static_assert(std::is_same_v<get_const_reference_type_test_1, const int>, "Error changed value");
static_assert(std::is_same_v<get_const_reference_type_test_2, const float>, "Error changed value");
static_assert(std::is_same_v<get_const_reference_type_test_3, const traits::TestClass&>, "Error changed value");
static_assert(std::is_same_v<get_const_reference_type_test_4, const traits::TestClassThrow&>, "Error changed value");
static_assert(std::is_same_v<get_const_reference_type_test_9, const int[5]>, "Error changed value");
static_assert(std::is_same_v<get_const_reference_type_test_5, const int*&>, "Error changed value");
static_assert(std::is_same_v<get_const_reference_type_test_6, const float*&>, "Error changed value");
static_assert(std::is_same_v<get_const_reference_type_test_7, const traits::TestClass*&>, "Error changed value");
static_assert(std::is_same_v<get_const_reference_type_test_8, const traits::TestClassThrow*&>, "Error changed value");
static_assert(std::is_same_v<get_const_reference_type_test_10, const int(&)[5]>, "Error changed value");

using get_promote_type_test_01 = traits::type_conversor<i8>::promote_t;
using get_promote_type_test_02 = traits::type_conversor<i16>::promote_t;
using get_promote_type_test_03 = traits::type_conversor<i32>::promote_t;
using get_promote_type_test_04 = traits::type_conversor<i64>::promote_t;
using get_promote_type_test_05 = traits::type_conversor<ui8>::promote_t;
using get_promote_type_test_06 = traits::type_conversor<ui16>::promote_t;
using get_promote_type_test_07 = traits::type_conversor<ui32>::promote_t;
using get_promote_type_test_08 = traits::type_conversor<ui64>::promote_t;
using get_promote_type_test_09 = traits::type_conversor<f32>::promote_t;
using get_promote_type_test_10 = traits::type_conversor<f64>::promote_t;
using get_promote_type_test_11 = traits::type_conversor<f128>::promote_t;
using get_promote_type_test_12 = traits::type_conversor<i8>::demote_t;
using get_promote_type_test_13 = traits::type_conversor<i16>::demote_t;
using get_promote_type_test_14 = traits::type_conversor<i32>::demote_t;
using get_promote_type_test_15 = traits::type_conversor<i64>::demote_t;
using get_promote_type_test_16 = traits::type_conversor<ui8>::demote_t;
using get_promote_type_test_17 = traits::type_conversor<ui16>::demote_t;
using get_promote_type_test_18 = traits::type_conversor<ui32>::demote_t;
using get_promote_type_test_19 = traits::type_conversor<ui64>::demote_t;
using get_promote_type_test_20 = traits::type_conversor<f32>::demote_t;
using get_promote_type_test_21 = traits::type_conversor<f64>::demote_t;
using get_promote_type_test_22 = traits::type_conversor<f128>::demote_t;
using get_promote_type_test_23 = traits::type_conversor<traits::TestClass>::promote_t;
using get_promote_type_test_24 = traits::type_conversor<traits::TestClass>::demote_t;

static_assert(std::is_same_v<get_promote_type_test_01, i16>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_02, i32>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_03, i64>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_04, i128>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_05, ui16>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_06, ui32>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_07, ui64>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_08, ui128>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_09, f64>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_10, f128>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_11, f128>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_12, i8>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_13, i8>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_14, i16>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_15, i32>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_16, ui8>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_17, ui8>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_18, ui16>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_19, ui32>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_20, f32>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_21, f32>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_22, f64>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_23, traits::TestClass>, "Error changed value");
static_assert(std::is_same_v<get_promote_type_test_24, traits::TestClass>, "Error changed value");

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
constexpr ll_bool_t nothrow_copy_test_4 = traits::is_nothrow_copyable_v<traits::TestClass>;
constexpr ll_bool_t nothrow_copy_test_5 = traits::is_nothrow_copyable_v<traits::TestClass*>;
constexpr ll_bool_t nothrow_copy_test_6 = traits::is_nothrow_copyable_v<traits::TestClass**>;
constexpr ll_bool_t nothrow_copy_test_7 = traits::is_nothrow_copyable_v<traits::TestClassThrow>;
constexpr ll_bool_t nothrow_copy_test_8 = traits::is_nothrow_copyable_v<traits::TestClassThrow*>;
constexpr ll_bool_t nothrow_copy_test_9 = traits::is_nothrow_copyable_v<traits::TestClassThrow**>;

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
constexpr ll_bool_t nothrow_swappeable_test_4 = traits::is_nothrow_swappeable_v<traits::TestClass>;
constexpr ll_bool_t nothrow_swappeable_test_5 = traits::is_nothrow_swappeable_v<traits::TestClass*>;
constexpr ll_bool_t nothrow_swappeable_test_6 = traits::is_nothrow_swappeable_v<traits::TestClass**>;
constexpr ll_bool_t nothrow_swappeable_test_7 = traits::is_nothrow_swappeable_v<traits::TestClassThrow>;
constexpr ll_bool_t nothrow_swappeable_test_8 = traits::is_nothrow_swappeable_v<traits::TestClassThrow*>;
constexpr ll_bool_t nothrow_swappeable_test_9 = traits::is_nothrow_swappeable_v<traits::TestClassThrow**>;

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
static_assert(!checker_test_3, "Error changed value");
static_assert( checker_test_4, "Error changed value");
static_assert( checker_test_5, "Error changed value");
static_assert(!checker_test_6, "Error changed value");
static_assert(!checker_test_7, "Error changed value");
static_assert(!checker_test_8, "Error changed value");
static_assert(!checker_test_9, "Error changed value");

///////////////////////////////////////////////// Example strings /////////////////////////////////////////////////


template <class... Args>
constexpr len_t teas() {
	return parameter_pack_operations<Args...>::size;
}

constexpr len_t teas_1 = teas<>();
constexpr len_t teas_2 = teas<int>();
constexpr len_t teas_3 = teas<int, char, char*>();

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXAMPLES_TRAITSEXAMPLE_HPP_
