/*
 *	array.hpp
 *
 *	Created on: Sep 27, 2021
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLANYLIB_VECTOR_HPP_
#define LLANYLIB_VECTOR_HPP_

#include "definitions.hpp"
#include "traits.hpp"

namespace llcpp {
namespace vector {

template<class T>
__LL_NODISCARD__ constexpr i8 compare_arrays(const T* v1, const T* v2, len_t size) __LL_EXCEPT__ {
	static_assert(traits::has_no_equal_operator_v<T>, "Error, <T> object has no operator!=()");
	static_assert(traits::has_greater_operator_v<T>, "Error, <T> object has no operator>()");

	for (; 0 < size; --size, ++v1, ++v2)
		if (*v1 != *v2)
			return *v1 > *v2 ? 1 : -1;
	return 0;
}
template<class T>
__LL_NODISCARD__ constexpr ll_bool_t equals(const T* v1, const len_t size1, const T* v2, const len_t size2) __LL_EXCEPT__ {
	return (size1 == size2) ? compare_arrays<T>(v1, v2, size1) == 0 : LL_FALSE;
}
template<class T, len_t size1, len_t size2 = size1>
__LL_NODISCARD__ constexpr ll_bool_t equals(const T* v1, const T* v2) __LL_EXCEPT__ {
	return (size1 == size2) ? compare_arrays<T>(v1, v2, size1) == 0 : LL_FALSE;
}
template<class T, len_t size1, len_t size2>
__LL_NODISCARD__ constexpr ll_bool_t equals(const T (&v1)[size1], const T (&v2)[size2]) __LL_EXCEPT__ {
	return (size1 == size2) ? compare_arrays<T>(v1, v2, size1) == 0 : LL_FALSE;
}

} // namespace vector
} // namespace llcpp

#endif // LLANYLIB_VECTOR_HPP_
