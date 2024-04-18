//////////////////////////////////////////////
//	algorithm.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 4.2							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ALGORITHM_HPP_) // Guard && version protector
	#if LLANYLIB_ALGORITHM_MAYOR_ != 4 || LLANYLIB_ALGORITHM_MINOR_ < 2
		#error "algorithm.hpp version error!"
	#endif // LLANYLIB_ALGORITHM_MAYOR_ || LLANYLIB_ALGORITHM_MINOR_

#else !defined(LLANYLIB_ALGORITHM_HPP_)
#define LLANYLIB_ALGORITHM_HPP_
#define LLANYLIB_ALGORITHM_MAYOR_ 4
#define LLANYLIB_ALGORITHM_MINOR_ 2

#include "traits.hpp"
#include "common.hpp"

namespace llcpp {
namespace algorithm {

constexpr len_t MAX_LIST_SIZE = static_cast<len_t>(-1);
constexpr len_t npos = MAX_LIST_SIZE;

template<class T, class result_t>
struct CompareData {
	len_t position;		// Position of comparation data
	T value1;			// Value 1 of the result given
	T value2;			// Value 2 of the result given
	result_t result;	// Result of comparation
};

template<class T, class U, ll_bool_t GET_DATA>
using CompareConditional = std::conditional_t<GET_DATA, CompareData<T, U>, U>;
template<class T, ll_bool_t GET_DATA>
using CompareConditionalCmpT = CompareConditional<T, cmp_t, GET_DATA>;
template<class T, ll_bool_t GET_DATA>
using CompareConditionalBool = CompareConditional<T, ll_bool_t, GET_DATA>;

#pragma region Comparators
#pragma region CompareSimple
template<class T, ll_bool_t GET_DATA = LL_FALSE, class CompareResult = CompareConditionalCmpT<T, GET_DATA>>
__LL_NODISCARD__ constexpr CompareResult compare(const T* v1, const T* v2, len_t size, fnc_clss::Compare<T> cmp) __LL_EXCEPT__ {
	const T* begin = v1;
	for (; 0 < size; --size, ++v1, ++v2) {
		cmp_t result = cmp(*v1, *v2);
		if (result != 0) {
			if constexpr (GET_DATA)
				return CompareResult{ static_cast<len_t>(v1 - begin), *v1, *v2, result };
			else return result;
		}
	}
	if constexpr (GET_DATA) {
		CompareResult __{};
		__.position = size;
		__.result = 0ull;
		return __;
	}
	else return 0;
}
template<class T, ll_bool_t GET_DATA = LL_FALSE, class CompareResult = CompareConditionalCmpT<T, GET_DATA>>
__LL_NODISCARD__ constexpr CompareResult compare(const T* v1, const T* v2, len_t size) __LL_EXCEPT__ {
	static_assert(traits::has_no_equal_operator_v<T>, "Error, <T> object has no operator!=()");
	static_assert(traits::has_greater_operator_v<T>, "Error, <T> object has no operator>()");
	return compare<T, GET_DATA, CompareResult>(v1, v2, size, common::compare_with_operators);
}

#pragma region Proxy
template<class T>
__LL_NODISCARD__ constexpr ll_bool_t equals(const T* v1, const len_t size1, const T* v2, const len_t size2, fnc_clss::Compare<T> cmp) __LL_EXCEPT__ {
	return (size1 == size2) ? compare<T>(v1, v2, size1, cmp) == 0 : LL_FALSE;
}
template<class T, len_t N1, len_t N2 = N1>
__LL_NODISCARD__ constexpr ll_bool_t equals(const T* v1, const T* v2, fnc_clss::Compare<T> cmp) __LL_EXCEPT__ {
	return (N1 == N2) ? compare<T>(v1, v2, N1, cmp) == 0 : LL_FALSE;
}
template<class T, len_t N1, len_t N2>
__LL_NODISCARD__ constexpr ll_bool_t equals(const T(&v1)[N1], const T(&v2)[N2], fnc_clss::Compare<T> cmp) __LL_EXCEPT__ {
	return (N1 == N2) ? compare<T>(v1, v2, N1, cmp) == 0 : LL_FALSE;
}

template<class T>
__LL_NODISCARD__ constexpr ll_bool_t equals(const T* v1, const len_t size1, const T* v2, const len_t size2) __LL_EXCEPT__ {
	return (size1 == size2) ? compare<T>(v1, v2, size1) == 0 : LL_FALSE;
}
template<class T, len_t N1, len_t N2 = N1>
__LL_NODISCARD__ constexpr ll_bool_t equals(const T* v1, const T* v2) __LL_EXCEPT__ {
	return (N1 == N2) ? compare<T>(v1, v2, N1) == 0 : LL_FALSE;
}
template<class T, len_t N1, len_t N2>
__LL_NODISCARD__ constexpr ll_bool_t equals(const T(&v1)[N1], const T(&v2)[N2]) __LL_EXCEPT__ {
	return (N1 == N2) ? compare<T>(v1, v2, N1) == 0 : LL_FALSE;
}

#pragma endregion
#pragma endregion
#pragma region StartsWith
// str size needs to be bigger or equal to needle
template<class T, ll_bool_t GET_DATA = LL_FALSE, class CompareResult = CompareConditionalBool<T, GET_DATA>>
__LL_NODISCARD__ constexpr CompareResult starts_with_impl(const T* str, const T* needle, len_t size, fnc_clss::CompareBool<T> cmp) {
	const T* begin = str;
	for (; 0 < size; --size, ++str, ++needle) {
		ll_bool_t result = cmp(*str, *needle);
		if (!result) {
			if constexpr (GET_DATA)
				return CompareResult{ static_cast<len_t>(str - begin), *str, *needle, result };
			else return result;
		}
	}
	if constexpr (GET_DATA) {
		CompareResult __{};
		__.position = size;
		__.result = LL_TRUE;
		return __;
	}
	else return LL_TRUE;
}
template<class T, ll_bool_t GET_DATA = LL_FALSE, class CompareResult = CompareConditionalBool<T, GET_DATA>>
__LL_NODISCARD__ constexpr CompareResult starts_with_impl(const T* str, const T* needle, len_t size) {
	return starts_with_impl<T, LL_FALSE>(str, needle, size, common::simple_equals);
}
template<class T, ll_bool_t GET_DATA = LL_FALSE, class CompareResult = CompareConditionalBool<T, GET_DATA>>
__LL_NODISCARD__ constexpr CompareResult starts_with(const T* str, const T* needle, const len_t size1, const len_t size2, fnc_clss::CompareBool<T> cmp) {
	if (size1 < size2) {
		if constexpr (GET_DATA) {
			CompareResult __{};
			__.position = 0ull;
			__.result = LL_FALSE;
			return __;
		}
		else return LL_FALSE;
	}
	return starts_with_impl<T, GET_DATA, CompareResult>(str, needle, size2, cmp);
}
template<class T, ll_bool_t GET_DATA = LL_FALSE, class CompareResult = CompareConditionalBool<T, GET_DATA>>
__LL_NODISCARD__ constexpr CompareResult starts_with(const T* str, const T* needle, const len_t size1, const len_t size2) {
	return starts_with<T, GET_DATA, CompareResult>(str, needle, size1, size2, common::simple_equals);
}
template<class T, ll_bool_t GET_DATA = LL_FALSE, class CompareResult = CompareConditionalBool<T, GET_DATA>, len_t N1, len_t N2>
__LL_NODISCARD__ constexpr CompareResult starts_with(const T(&str)[N1], const T(&needle)[N2], fnc_clss::CompareBool<T> cmp) {
	return starts_with<T, GET_DATA, CompareResult>(str, needle, N1, N2, cmp);
}
template<class T, ll_bool_t GET_DATA = LL_FALSE, class CompareResult = CompareConditionalBool<T, GET_DATA>, len_t N1, len_t N2>
__LL_NODISCARD__ constexpr CompareResult starts_with(const T(&str)[N1], const T(&needle)[N2]) {
	return starts_with<T, GET_DATA, CompareResult>(str, needle, N1, N2, common::simple_equals);
}

#pragma endregion
#pragma region EndsWith
template<class T, ll_bool_t GET_DATA = LL_FALSE, class CompareResult = CompareConditionalBool<T, GET_DATA>>
__LL_NODISCARD__ constexpr CompareResult ends_with(const T* str, const T* needle, const len_t size1, const len_t size2, fnc_clss::CompareBool<T> cmp) {
	if (size1 < size2) {
		if constexpr (GET_DATA) {
			CompareResult __{};
			__.position = 0ull;
			__.result = LL_FALSE;
			return __;
		}
		else return LL_FALSE;
	}
	return starts_with_impl<T, GET_DATA, CompareResult>((str + size1) - size2, needle, size2, cmp);
}
template<class T, ll_bool_t GET_DATA = LL_FALSE, class CompareResult = CompareConditionalBool<T, GET_DATA>>
__LL_NODISCARD__ constexpr CompareResult ends_with(const T* str, const T* needle, const len_t size1, const len_t size2) {
	return ends_with<T, GET_DATA, CompareResult>(str, needle, size1, size2, common::simple_equals);
}
template<class T, ll_bool_t GET_DATA = LL_FALSE, class CompareResult = CompareConditionalBool<T, GET_DATA>, len_t N1, len_t N2>
__LL_NODISCARD__ constexpr CompareResult ends_with(const T(&str)[N1], const T(&needle)[N2], fnc_clss::CompareBool<T> cmp) {
	return ends_with<T, GET_DATA, CompareResult>(str, needle, N1, N2, cmp);
}
template<class T, ll_bool_t GET_DATA = LL_FALSE, class CompareResult = CompareConditionalBool<T, GET_DATA>, len_t N1, len_t N2>
__LL_NODISCARD__ constexpr CompareResult ends_with(const T(&str)[N1], const T(&needle)[N2]) {
	return ends_with<T, GET_DATA, CompareResult>(str, needle, N1, N2, common::simple_equals);
}

#pragma endregion
#pragma endregion
#pragma region Finders
#pragma region Find
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr const T* find(const T* begin, const T* end, const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	LL_ASSERT(begin, "[begin] cannot be nullptr. find(const T* begin, const T* end, const U object)");
	LL_ASSERT(end, "[end] cannot be nullptr. find(const T* begin, const T* end, const U object)");

	for (; begin < end; ++begin)
		if(cmp(*begin, object)) return begin;
	return end;
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr const T* find(const T* begin, const T* end, const U object) __LL_EXCEPT__ {
	static_assert(traits::has_equal_operator_v<T>, "Error, <T> object has no operator==()");
	return find<T, U>(begin, end, object, common::simple_equals);
}

#pragma region Proxy
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr len_t find_pos(const T* begin, const T* end, const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	const T* pos = find<T, U>(begin, end, object, cmp);
	return (pos != end) ? pos - begin : npos;
}
template<class T, class U = traits::get_object_reference_t<T>, len_t N>
__LL_NODISCARD__ constexpr const T* find(const T(&v)[N], const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	return find<T, U>(v, v + N, object, cmp);
}
template<class T, class U = traits::get_object_reference_t<T>, len_t N>
__LL_NODISCARD__ constexpr len_t find_pos(const T(&v)[N], const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	return find_pos<T, U>(v, v + N, object, cmp);
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr T* find(const ArrayPair<T> arr, const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	return find<T, U>(arr.begin(), arr.end(), object, cmp);
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr len_t find_pos(const ArrayPair<T> arr, const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	return find_pos<T, U>(arr.begin(), arr.end(), object, cmp);
}

template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr len_t find_pos(const T* begin, const T* end, const U object) __LL_EXCEPT__ {
	const T* pos = find<T, U>(begin, end, object);
	return (pos != end) ? pos - begin : npos;
}
template<class T, class U = traits::get_object_reference_t<T>, len_t N>
__LL_NODISCARD__ constexpr const T* find(const T (&v)[N], const U object) __LL_EXCEPT__ {
	return find<T, U>(v, v + N, object);
}
template<class T, class U = traits::get_object_reference_t<T>, len_t N>
__LL_NODISCARD__ constexpr len_t find_pos(const T(&v)[N], const U object) __LL_EXCEPT__ {
	return find_pos<T, U>(v, v + N, object);
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr T* find(const ArrayPair<T> arr, const U object) __LL_EXCEPT__ {
	return find<T, U>(arr.begin(), arr.end(), object);
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr len_t find_pos(const ArrayPair<T> arr, const U object) __LL_EXCEPT__ {
	return find_pos<T, U>(arr.begin(), arr.end(), object);
}

#pragma endregion
#pragma endregion
#pragma region rFind
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr const T* rfind(const T* begin, const T* end, const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	LL_ASSERT(begin, "[begin] cannot be nullptr. rfind(const T* begin, const T* end, const U object)");
	LL_ASSERT(end, "[end] cannot be nullptr. rfind(const T* begin, const T* end, const U object)");

	for (const T* i = end - 1; i > begin; --i)
		if (cmp(*i, object)) return i;
	return cmp(*begin, object) ? begin : end;
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr const T* rfind(const T* begin, const T* end, const U object) __LL_EXCEPT__ {
	static_assert(traits::has_equal_operator_v<T>, "Error, <T> object has no operator==()");
	return rfind<T, U>(begin, end, object, common::simple_equals);
}

#pragma region Proxy
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr len_t rfind_pos(const T* begin, const T* end, const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	const T* pos = rfind<T, U>(begin, end, object, cmp);
	return (pos != end) ? pos - begin : npos;
}
template<class T, class U = traits::get_object_reference_t<T>, len_t N>
__LL_NODISCARD__ constexpr const T* rfind(const T(&v)[N], const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	return rfind<T, U>(v, v + N, object, cmp);
}
template<class T, class U = traits::get_object_reference_t<T>, len_t N>
__LL_NODISCARD__ constexpr len_t rfind_pos(const T(&v)[N], const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	return rfind_pos<T, U>(v, v + N, object, cmp);
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr T* rfind(const ArrayPair<T> arr, const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	return rfind<T, U>(arr.begin(), arr.end(), object, cmp);
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr len_t rfind_pos(const ArrayPair<T> arr, const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	return rfind_pos<T, U>(arr.begin(), arr.end(), object, cmp);
}

template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr len_t rfind_pos(const T* begin, const T* end, const U object) __LL_EXCEPT__ {
	const T* pos = rfind<T, U>(begin, end, object);
	return (pos != end) ? pos - begin : npos;
}
template<class T, class U = traits::get_object_reference_t<T>, len_t N>
__LL_NODISCARD__ constexpr const T* rfind(const T(&v)[N], const U object) __LL_EXCEPT__ {
	return rfind<T, U>(v, v + N, object);
}
template<class T, class U = traits::get_object_reference_t<T>, len_t N>
__LL_NODISCARD__ constexpr len_t rfind_pos(const T(&v)[N], const U object) __LL_EXCEPT__ {
	return rfind_pos<T, U>(v, v + N, object);
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr T* rfind(const ArrayPair<T> arr, const U object) __LL_EXCEPT__ {
	return rfind<T, U>(arr.begin(), arr.end(), object);
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr len_t rfind_pos(const ArrayPair<T> arr, const U object) __LL_EXCEPT__ {
	return rfind_pos<T, U>(arr.begin(), arr.end(), object);
}

#pragma endregion
#pragma endregion
#pragma region Other
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr ll_bool_t all(const T* begin, const T* end, const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	LL_ASSERT(begin, "[begin] cannot be nullptr. all(const T* begin, const T* end, const U object)");
	LL_ASSERT(end, "[end] cannot be nullptr. all(const T* begin, const T* end, const U object)");

	for (; begin < end; ++begin)
		if (!cmp(*begin, object)) return LL_FALSE;
	return LL_TRUE;
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr ll_bool_t all(const T* begin, const T* end, const U object) __LL_EXCEPT__ {
	static_assert(traits::has_equal_operator_v<T>, "Error, <T> object has no operator==()");
	return all<T, U>(begin, end, object, common::simple_equals);
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr ll_bool_t any(const T* begin, const T* end, const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	return static_cast<ll_bool_t>(find<T, U>(begin, end, object, cmp));
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr ll_bool_t any(const T* begin, const T* end, const U object) __LL_EXCEPT__ {
	return static_cast<ll_bool_t>(find<T, U>(begin, end, object));
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr ll_bool_t none(const T* begin, const T* end, const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	return !static_cast<ll_bool_t>(find<T, U>(begin, end, object, cmp));
}
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr ll_bool_t none(const T* begin, const T* end, const U object) __LL_EXCEPT__ {
	return !static_cast<ll_bool_t>(find<T, U>(begin, end, object));
}

#pragma endregion
#pragma region BinarySearch
/// <summary>
/// Unstable
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="U"></typeparam>
/// <param name="begin"></param>
/// <param name="end"></param>
/// <param name="object"></param>
/// <returns></returns>
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr const T* binarysearch(const T* begin, const T* end, const U object) {
	static_assert(traits::has_equal_operator_v<T>, "Error, <T> object has no operator==()");
	static_assert(traits::has_greater_operator_v<T>, "Error, <T> object has no operator>()");
	LL_ASSERT(begin, "[begin] cannot be nullptr. rfind(const T* begin, const T* end, const U object)");
	LL_ASSERT(end, "[end] cannot be nullptr. rfind(const T* begin, const T* end, const U object)");

	len_t low = 0ull;
	len_t high = end - begin;
	while (low <= high) {
		len_t mid = ((high + low) / 2);
		if(begin[mid] == object) return begin + mid;
		else if(begin[mid] > object) high = mid;
		else low = mid + 1;
	}
	return end;
}

// This is recommended to use with objects types
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr const T* binarysearch(const T* begin, const T* end, const U object, fnc_clss::CompareBool<T> cmp) {
	LL_ASSERT(begin, "[begin] cannot be nullptr. rfind(const T* begin, const T* end, const U object)");
	LL_ASSERT(end, "[end] cannot be nullptr. rfind(const T* begin, const T* end, const U object)");

	len_t low = 0ull;
	len_t high = end - begin;
	while (low <= high) {
		len_t mid = ((high - low) / 2);
		cmp_t res = cmp(begin[mid], object);
		if (res == 0) return begin + mid;
		else if (res > 0) high = mid;
		else low = mid + 1;
	}
	return end;
}

#pragma region ClassicProxy
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr len_t binarysearch_pos(const T* begin, const T* end, const U object) __LL_EXCEPT__ {
	const T* pos = binarysearch<T, U>(begin, end, object);
	return (pos != end) ? pos - begin : npos;
}
template<class T, class U = traits::get_object_reference_t<T>, len_t N>
__LL_NODISCARD__ constexpr const T* binarysearch(const T(&v)[N], const U object) __LL_EXCEPT__ {
	return binarysearch<T, U>(v, v + N, object);
}
template<class T, class U = traits::get_object_reference_t<T>, len_t N>
__LL_NODISCARD__ constexpr len_t binarysearch_pos(const T(&v)[N], const U object) __LL_EXCEPT__ {
	return binarysearch_pos<T, U>(v, v + N, object);
}

#pragma endregion
#pragma region ExtendexProxy
template<class T, class U = traits::get_object_reference_t<T>>
__LL_NODISCARD__ constexpr len_t binarysearch_pos(const T* begin, const T* end, const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	const T* pos = binarysearch<T, U>(begin, end, object, cmp);
	return (pos != end) ? pos - begin : npos;
}
template<class T, class U = traits::get_object_reference_t<T>, len_t N>
__LL_NODISCARD__ constexpr const T* binarysearch(const T(&v)[N], const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	return binarysearch<T, U>(v, v + N, object, cmp);
}
template<class T, class U = traits::get_object_reference_t<T>, len_t N>
__LL_NODISCARD__ constexpr len_t binarysearch_pos(const T(&v)[N], const U object, fnc_clss::CompareBool<T> cmp) __LL_EXCEPT__ {
	return binarysearch_pos<T, U>(v, v + N, object, cmp);
}

#pragma endregion
#pragma endregion

#pragma endregion
#pragma region DataManipulation
template<class T>
constexpr void reverse(T* begin, T* end, fnc_clss::SwapFunction<T> swap) __LL_EXCEPT__ {
	LL_ASSERT(begin, "[begin] cannot be nullptr. reverse(T* begin, T* end, ReveseSwapFunction<T> revSwap)");
	LL_ASSERT(end, "[end] cannot be nullptr. reverse(T* begin, T* end, ReveseSwapFunction<T> revSwap)");
	LL_ASSERT(begin < end, "[begin < end] begin of array needs to be lower value than end. reverse(T* begin, T* end, ReveseSwapFunction<T> revSwap)");

	for (; begin < end; ++begin, --end)
		swap(*begin, *end);
}
template<class T>
constexpr void reverse(T* begin, T* end) __LL_EXCEPT__ {
	reverse<T>(begin, end, common::simple_swap);
}
template<class T, len_t N>
constexpr void reverse(T(&v)[N]) __LL_EXCEPT__ {
	return reverse<T>(v, v + N - 1);
}
template<class T, len_t N>
constexpr void reverse(T(&v)[N], fnc_clss::SwapFunction<T> revSwap) __LL_EXCEPT__ {
	return reverse<T>(v, v + N - 1, revSwap);
}

template<class T, class U = traits::get_object_reference_t<T>>
constexpr void fill(T* begin, T* end, const U object) {
	for (; begin < end; ++begin) *begin = object;
}
template<class T, len_t N, class U = traits::get_object_reference_t<T>>
constexpr void fill(T(&v)[N], const U object) __LL_EXCEPT__ {
	return fill<T, U>(v, v + N, object);
}

// Num => number of positions to move
template<class T, class U = traits::get_object_reference_t<T>>
constexpr void shiftLeft(T* begin, T* end, const len_t num, const U null, fnc_clss::SwapFunction<T> swap) __LL_EXCEPT__ {
	//len_t size = end - begin;
	//LL_ASSERT(size > num, "[num] num is greater than the array size");

	--end;
	for (T* i = end - num; i > begin; --i, --end)
		swap(*end, *i);
	swap(*begin, *(begin + num));

	fill<T, U>(begin, begin + num, null);
}
template<class T, class U = traits::get_object_reference_t<T>>
constexpr void shiftLeft(T* begin, T* end, const len_t num, const U null) __LL_EXCEPT__ {
	shiftLeft<T, U>(begin, end, num, null, common::simple_swap);
}

template<class T, class U = traits::get_object_reference_t<T>>
constexpr void shifRight(T* begin, T* end, const len_t num, const U null, fnc_clss::SwapFunction<T> swap) __LL_EXCEPT__ {
	//len_t size = end - begin;
	//LL_ASSERT(size > num, "[num] num is greater than the array size");

	for (T* i = begin + num; i < end; ++i, ++begin)
		swap(*begin, *i);

	fill<T, U>(end - num, end, null);
}
template<class T, class U = traits::get_object_reference_t<T>>
constexpr void shifRight(T* begin, T* end, const len_t num, const U null) __LL_EXCEPT__ {
	shifRight<T, U>(begin, end, num, null, common::simple_swap);
}

#pragma endregion

} // namespace algorithm
} // namespace llcpp

#endif // LLANYLIB_ALGORITHM_HPP_
