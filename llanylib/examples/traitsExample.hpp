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

constexpr ll_bool_t test_1_obj2 = traits::has_type_operator_v<TestClassBase, ll_bool_t>;
constexpr ll_bool_t test_1_obj = traits::has_type_operator_v<TestClass, ll_bool_t>;
constexpr ll_bool_t test_1_obj3 = traits::has_type_operator_v<TestClassNoCopy, ll_bool_t>;
constexpr ll_bool_t test_1_int = traits::has_type_operator_v<int, ll_bool_t>;
constexpr ll_bool_t test_2_obj = traits::has_clear_v<TestClass>;
constexpr ll_bool_t test_2_int = traits::has_clear_v<int>;
constexpr ll_bool_t test_2_obj = traits::has_swap_v<TestClass>;
constexpr ll_bool_t test_2_int = traits::has_swap_v<int>;

constexpr ll_bool_t test_1_int = has_type_operator_v<int, int>;

constexpr ll_bool_t test_copy_operator_int = std::is_copy_assignable_v<int>;
constexpr ll_bool_t test_copy_operator_class = std::is_copy_assignable_v<TestClass>;
constexpr ll_bool_t test_copy_operator_class_bad = std::is_copy_assignable_v<TestClassBad>;
constexpr ll_bool_t test_copy_operator_class_private_copy = std::is_copy_assignable_v<TestClassPrivateCopy>;
constexpr ll_bool_t test_copy_operator_class_no_copy = std::is_copy_assignable_v<TestClassNoCopy>;

static_assert(test_copy_operator_int);
static_assert(test_copy_operator_class);
static_assert(test_copy_operator_class_bad);
static_assert(!test_copy_operator_class_private_copy);
static_assert(!test_copy_operator_class_no_copy);


constexpr ll_bool_t ex = traits::is_nothrow_copyable_v<int>;
constexpr ll_bool_t ex = traits::is_nothrow_copyable_v<int*>;
constexpr ll_bool_t ex = traits::is_nothrow_copyable_v<int**>;
constexpr ll_bool_t ex = traits::is_nothrow_copyable_v<llcpp::traits::TestClass>;
constexpr ll_bool_t ex = traits::is_nothrow_copyable_v<llcpp::traits::TestClass*>;
constexpr ll_bool_t ex = traits::is_nothrow_copyable_v<llcpp::traits::TestClass**>;
constexpr ll_bool_t ex = traits::is_nothrow_copyable_v<llcpp::traits::TestClassThrow>;
constexpr ll_bool_t ex = traits::is_nothrow_copyable_v<llcpp::traits::TestClassThrow*>;
constexpr ll_bool_t ex = traits::is_nothrow_copyable_v<llcpp::traits::TestClassThrow**>;

} // namespace llcpp
} // namespace traits

#endif // LLANYLIB_EXAMPLES_TRAITSEXAMPLE_HPP_
