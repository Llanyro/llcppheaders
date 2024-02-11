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

#define LL_TRAITS_TEST

#if defined(LL_TRAITS_TEST)
	#include "traits_test_class.hpp"
#endif

#include <type_traits>

namespace llcpp {
namespace traits {

// Easy enabler for template functions
#define ENABLE_FUNCTION_PARAM(condition) typename = typename std::enable_if<condition>::type

template<class T>
inline constexpr ll_bool_t is_basic_type_v = std::_Is_any_of_v<T, ui8, ui16, ui32, ui64, i8, i16, i32, i64, f32, f64>;

template <class T, class OperatorType>
struct has_type_operator {
    template <class U>
	static auto test(U* p) -> decltype(p->operator OperatorType(), std::true_type{});
	template <class>
	static auto test(...) -> 
		std::conditional_t<
			is_basic_type_v<T>,
			std::bool_constant<std::is_same_v<T, OperatorType>>,
			std::false_type
		>;
	using val = decltype(test<T>(nullptr));
};

template <class T, class OperatorType>
inline constexpr ll_bool_t has_type_operator_v = has_type_operator<T, OperatorType>::val::value;

#define __LL_TEMPLATE_HAS_FUNCTION_BASE__(name, function, basic_value) \
	template<class T> \
	struct has_##name## { \
		template <class U> \
		static auto test(U* p) -> decltype(##function##, std::true_type{}); \
		template <class> \
		static auto test(...) -> \
			std::conditional_t< \
				is_basic_type_v<T>, \
				std::bool_constant<basic_value>, \
				std::false_type \
			>; \
		using val = decltype(test<T>(nullptr)); \
	}; \
	template <class T> \
	inline constexpr ll_bool_t has_##name##_v = has_##name##<T>::val::value

#define __LL_TEMPLATE_HAS_FUNCTION__(name, function) __LL_TEMPLATE_HAS_FUNCTION_BASE__(name, function, LL_FALSE)
#define __TEMPLATE_HAS_SIMPLE_FUNCTION__(function) __LL_TEMPLATE_HAS_FUNCTION__(function, p->##function())

__LL_TEMPLATE_HAS_FUNCTION_BASE__(copy_operator, p->operator=(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(move_operator, p->operator=(std::move(*p)), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(three_compare_operator, p->operator<=>(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(equal_operator, p->operator==(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(no_equal_operator, p->operator!=(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(greater_operator, p->operator>(*p), LL_TRUE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(lower_operator, p->operator<(*p), LL_TRUE);

__LL_TEMPLATE_HAS_FUNCTION__(swap, p->swap(*p));
__LL_TEMPLATE_HAS_FUNCTION__(swap_s, p->swap_s(*p));
__TEMPLATE_HAS_SIMPLE_FUNCTION__(clear);

#if defined(LL_TRAITS_TEST)
//constexpr ll_bool_t test_1_obj2 = has_type_operator_v<TestClassBase, ll_bool_t>;
//constexpr ll_bool_t test_1_obj = has_type_operator_v<TestClass, ll_bool_t>;
//constexpr ll_bool_t test_1_obj3 = has_type_operator_v<TestClassNoCopy, ll_bool_t>;
//constexpr ll_bool_t test_1_int = has_type_operator_v<int, ll_bool_t>;
//constexpr ll_bool_t test_2_obj = has_clear_v<TestClass>;
//constexpr ll_bool_t test_2_int = has_clear_v<int>;
//constexpr ll_bool_t test_2_obj = has_swap_v<TestClass>;
//constexpr ll_bool_t test_2_int = has_swap_v<int>;
//
//constexpr ll_bool_t test_1_int = has_type_operator_v<int, int>;
//
//constexpr ll_bool_t test_copy_operator_int = has_copy_operator_v<int>;
//constexpr ll_bool_t test_copy_operator_class = has_copy_operator_v<TestClass>;
//constexpr ll_bool_t test_copy_operator_class_bad = has_copy_operator_v<TestClassBad>;
//constexpr ll_bool_t test_copy_operator_class_private_copy = has_copy_operator_v<TestClassPrivateCopy>;
//constexpr ll_bool_t test_copy_operator_class_no_copy = has_copy_operator_v<TestClassNoCopy>;

#endif

} // namespace traits
} // namespace llcpp

#endif /* LLCPP_HEADER_TRAITS_HPP_ */
