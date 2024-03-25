/*
 *	traitsExample.hpp
 *
 *	Created on: Sep 27, 2021
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#include "../traits.hpp"

#if !defined(LLANYLIB_EXAMPLES_TRAITSEXAMPLE_HPP_) && defined(LL_TRAITS_TEST)
#define LLANYLIB_EXAMPLES_TRAITSEXAMPLE_HPP_

namespace llcpp {
namespace traits {

constexpr ll_bool_t test_1_obj2 = has_type_operator_v<TestClassBase, ll_bool_t>;
constexpr ll_bool_t test_1_obj = has_type_operator_v<TestClass, ll_bool_t>;
constexpr ll_bool_t test_1_obj3 = has_type_operator_v<TestClassNoCopy, ll_bool_t>;
constexpr ll_bool_t test_1_int = has_type_operator_v<int, ll_bool_t>;
constexpr ll_bool_t test_2_obj = has_clear_v<TestClass>;
constexpr ll_bool_t test_2_int = has_clear_v<int>;
constexpr ll_bool_t test_2_obj = has_swap_v<TestClass>;
constexpr ll_bool_t test_2_int = has_swap_v<int>;

constexpr ll_bool_t test_1_int = has_type_operator_v<int, int>;

constexpr ll_bool_t test_copy_operator_int = has_copy_operator_v<int>;
constexpr ll_bool_t test_copy_operator_class = has_copy_operator_v<TestClass>;
constexpr ll_bool_t test_copy_operator_class_bad = has_copy_operator_v<TestClassBad>;
constexpr ll_bool_t test_copy_operator_class_private_copy = has_copy_operator_v<TestClassPrivateCopy>;
constexpr ll_bool_t test_copy_operator_class_no_copy = has_copy_operator_v<TestClassNoCopy>;

} // namespace llcpp
} // namespace traits

#endif // LLANYLIB_EXAMPLES_TRAITSEXAMPLE_HPP_
