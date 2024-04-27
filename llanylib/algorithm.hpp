//////////////////////////////////////////////
//	algorithm.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ALGORITHM_HPP_) // Guard && version protector
	#if LLANYLIB_ALGORITHM_MAYOR_ != 5 || LLANYLIB_ALGORITHM_MINOR_ < 0
		#error "algorithm.hpp version error!"
	#endif // LLANYLIB_ALGORITHM_MAYOR_ || LLANYLIB_ALGORITHM_MINOR_

#else !defined(LLANYLIB_ALGORITHM_HPP_)
#define LLANYLIB_ALGORITHM_HPP_
#define LLANYLIB_ALGORITHM_MAYOR_ 5
#define LLANYLIB_ALGORITHM_MINOR_ 0

#include "type_traits.hpp"
#include "common.hpp"

namespace llcpp {
namespace algorithm {

constexpr len_t MAX_LIST_SIZE = static_cast<len_t>(-1);
constexpr len_t npos = MAX_LIST_SIZE;

#pragma region Comparators
template<class T, class U, class result_t, result_t NULL_RESULT>
class CompareData {
	public:
		using __t = traits::template_types<T>;
		using __u = traits::template_types<U>;
		using __CompareData = traits::template_types<CompareData<T, U, result_t, NULL_RESULT>>;
		static_assert(traits::is_basic_type_v<result_t>, "Result type must be a basic type!");
	protected:
		__t::type value1;	// Value 1 of the result given
		__u::type value2;	// Value 2 of the result given
		len_t position;		// Position of comparation data
		result_t result;	// Result of comparation
	protected:
		constexpr void simpleClear() __LL_EXCEPT__ {
			this->position = npos;
			this->result = NULL_RESULT;

			if constexpr (std::is_pointer_v<__t::type>)
				this->value1 = LL_NULLPTR;
			if constexpr (std::is_pointer_v<__u::type>)
				this->value2 = LL_NULLPTR;
		}
	public:
		constexpr CompareData(const len_t position, const result_t result) __LL_EXCEPT__
			: value1(), value2(), position(position), result(result) {}
		constexpr CompareData(__t::cinput value1, __u::cinput value2, const len_t position, const result_t result) __LL_EXCEPT__
			: value1(value1)
			, value2(value2)
			, position(position)
			, result(result)
		{}
		constexpr CompareData(__t::move value1, __u::cinput value2, const len_t position, const result_t result) __LL_EXCEPT__
			: value1(std::move(value1))
			, value2(value2)
			, position(position)
			, result(result)
		{ if constexpr (std::is_pointer_v<__t::type>) value1 = LL_NULLPTR; }
		constexpr CompareData(__t::cinput value1, __u::move value2, const len_t position, const result_t result) __LL_EXCEPT__
			: value1(value1)
			, value2(std::move(value2))
			, position(position)
			, result(result)
		{ if constexpr (std::is_pointer_v<__u::type>) value2 = LL_NULLPTR; }
		constexpr CompareData(__t::move value1, __u::move value2, const len_t position, const result_t result) __LL_EXCEPT__
			: value1(std::move(value1))
			, value2(std::move(value2))
			, position(position)
			, result(result)
		{
			if constexpr (std::is_pointer_v<__t::type>) this->value1 = LL_NULLPTR;
			if constexpr (std::is_pointer_v<__u::type>) this->value2 = LL_NULLPTR;
		}
		constexpr ~CompareData() __LL_EXCEPT__ {}

		constexpr CompareData(__CompareData::cref other) __LL_EXCEPT__
			: value1(other.value1), value2(other.value2)
			, position(other.position), result(other.result) {}
		constexpr __CompareData::ref operator=(__CompareData::cref other) __LL_EXCEPT__ {
			this->value1 = other.value1;
			this->value2 = other.value2;
			this->position = other.position;
			this->result = other.result;
			return *this;
		}
		constexpr CompareData(__CompareData::move other) __LL_EXCEPT__
			: value1(std::move(other.value1)), value2(std::move(other.value2))
			, position(other.position), result(other.result) { other.simpleClear(); }
		constexpr __CompareData::ref operator=(__CompareData::move other) __LL_EXCEPT__ {
			this->value1 = std::move(other.value1);
			this->value2 = std::move(other.value2);
			this->position = other.position;
			this->result = other.result;
			other.simpleClear();
			return *this;
		}

		__LL_NODISCARD__ constexpr __t::ref getValue1() __LL_EXCEPT__ { return this->value1; }
		__LL_NODISCARD__ constexpr __u::ref getValue2() __LL_EXCEPT__ { return this->value2; }

		__LL_NODISCARD__ constexpr __t::cref getValue1() const __LL_EXCEPT__ { return this->value1; }
		__LL_NODISCARD__ constexpr const __u::type& getValue2() const __LL_EXCEPT__ { return this->value2; }

		__LL_NODISCARD__ constexpr len_t getPos() const __LL_EXCEPT__ { return this->position; }
		__LL_NODISCARD__ constexpr result_t getResult() const __LL_EXCEPT__ { return this->result; }
};

template<class T, class U, class result_t, result_t NULL_RESULT, ll_bool_t GET_DATA>
using CompareConditional = std::conditional_t<GET_DATA, CompareData<T, U, result_t, NULL_RESULT>, result_t>;
template<class T, class U = T, ll_bool_t GET_DATA = LL_TRUE>
using CompareConditionalCmpT = CompareConditional<T, U, cmp_t, 0, GET_DATA>;
template<class T, class U = T, ll_bool_t GET_DATA = LL_TRUE>
using CompareConditionalBool = CompareConditional<T, U, ll_bool_t, LL_FALSE, GET_DATA>;


template<class T, class U = T, ll_bool_t GET_DATA = LL_FALSE>
struct compare_cluster {
	using __cmp = compare_cluster<T, U, GET_DATA>;
	using __t = traits::template_types<T>;
	using __u = traits::template_types<U>;
	using CompareResult = CompareConditionalCmpT<T, U, GET_DATA>;
	using fun_compare = fnc_clss::Compare<__t::cinput, __u::cinput>;
	using fun_comparebool = fnc_clss::CompareBool<__t::cinput, __u::cinput>;

	#pragma region Compare
	__LL_NODISCARD__ static constexpr CompareResult compare(__t::cptr v1, __u::cptr v2, len_t size, fun_compare cmp) __LL_EXCEPT__ {
		__t::cptr begin = v1;
		for (; 0 < size; --size, ++v1, ++v2) {
			cmp_t result = cmp(*v1, *v2);
			if (result != 0) {
				if constexpr (GET_DATA)
					return CompareResult(*v1, *v2, static_cast<len_t>(v1 - begin), result);
				else return result;
			}
		}
		if constexpr (GET_DATA) return CompareResult(npos, 0);
		else return 0;
	}
	__LL_NODISCARD__ static constexpr CompareResult compare(__t::cptr v1, __u::cptr v2, len_t size) __LL_EXCEPT__ {
		return __cmp::compare(v1, v2, size, common::compare_with_operators<__t::cinput, __u::cinput>);
	}

	#pragma region Equals
	__LL_NODISCARD__ static constexpr ll_bool_t equals(__t::cptr v1, const len_t size1, __u::cptr v2, const len_t size2, fun_compare cmp) __LL_EXCEPT__ {
		if (size1 != size2) return LL_FALSE;
		CompareResult res = __cmp::compare(v1, v2, size1, cmp);
		if constexpr (GET_DATA) return res.getResult() == 0;
		else return res == 0;
	}
	__LL_NODISCARD__ static constexpr ll_bool_t equals(__t::cptr v1, const len_t size1, __u::cptr v2, const len_t size2) __LL_EXCEPT__ {
		if (size1 != size2) return LL_FALSE;
		CompareResult res = __cmp::compare(v1, v2, size1);
		if constexpr (GET_DATA) return res.getResult() == 0;
		else return res == 0;
	}

	template<len_t N1, len_t N2 = N1>
	__LL_NODISCARD__ static constexpr ll_bool_t equals(__t::cptr v1, __u::cptr v2, fun_compare cmp) __LL_EXCEPT__ {
		return __cmp::equals(v1, N1, v2, N2, cmp);
	}
	template<len_t N1, len_t N2 = N1>
	__LL_NODISCARD__ static constexpr ll_bool_t equals(__t::cptr v1, __u::cptr v2) __LL_EXCEPT__ {
		return __cmp::equals(v1, N1, v2, N2);
	}

	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr ll_bool_t equals(__t::ctype (&v1)[N1], __u::ctype (&v2)[N2], fun_compare cmp) __LL_EXCEPT__ {
		return __cmp::equals(v1, N1, v2, N2, cmp);
	}
	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr ll_bool_t equals(__t::ctype (&v1)[N1], __u::ctype(&v2)[N2]) __LL_EXCEPT__ {
		return __cmp::equals(v1, N1, v2, N2);
	}

	__LL_NODISCARD__ static constexpr ll_bool_t equals(ArrayPair<__t::type> v1, ArrayPair<__u::type> v2, fun_compare cmp) __LL_EXCEPT__ {
		return __cmp::equals(v1.begin(), v1.len(), v2.begin(), v2.len(), cmp);
	}
	__LL_NODISCARD__ static constexpr ll_bool_t equals(ArrayPair<__t::type> v1, ArrayPair<__u::type> v2) __LL_EXCEPT__ {
		return __cmp::equals(v1.begin(), v1.len(), v2.begin(), v2.len());
	}

	#pragma endregion
	#pragma endregion
	#pragma region StartsWith
	// str size needs to be bigger or equal to needle
	__LL_NODISCARD__ static constexpr CompareResult starts_with_impl(__t::cptr str, __u::cptr needle, len_t size, fun_comparebool cmp) {
		__t::cptr begin = str;
		for (; 0 < size; --size, ++str, ++needle) {
			ll_bool_t result = cmp(*str, *needle);
			if (!result) {
				if constexpr (GET_DATA)
					return CompareResult(*str, *needle, static_cast<len_t>(str - begin), result);
				else return result;
			}
		}
		if constexpr (GET_DATA) return CompareResult(npos, LL_TRUE);
		else return LL_TRUE;
	}
	__LL_NODISCARD__ static constexpr CompareResult starts_with_impl(__t::cptr str, __u::cptr needle, len_t size) {
		return starts_with_impl(str, needle, size, common::simple_equals<__t::cinput, __u::cinput>);
	}

	__LL_NODISCARD__ static constexpr CompareResult starts_with(__t::cptr str, __u::cptr needle, const len_t size1, const len_t size2, fun_comparebool cmp) {
		if (size1 < size2) {
			if constexpr (GET_DATA) return CompareResult(npos, LL_FALSE);
			else return LL_FALSE;
		}
		else return __cmp::starts_with_impl(str, needle, size2, cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResult starts_with(__t::cptr str, __u::cptr needle, const len_t size1, const len_t size2) {
		return __cmp::starts_with(str, needle, size1, size2, common::simple_equals<__t::cinput, __u::cinput>);
	}

	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResult starts_with(__t::ctype (&str)[N1], __u::ctype (&needle)[N2], fun_comparebool cmp) {
		return __cmp::starts_with(str, needle, N1, N2, cmp);
	}
	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResult starts_with(__t::ctype (&str)[N1], __u::ctype (&needle)[N2]) {
		return __cmp::starts_with(str, needle, N1, N2);
	}

	__LL_NODISCARD__ static constexpr CompareResult starts_with(ArrayPair<__t::type> v1, ArrayPair<__u::type> v2, fun_comparebool cmp) {
		return __cmp::starts_with(v1.begin(), v2.begin(), v1.len(), v2.len(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResult starts_with(ArrayPair<__t::type> v1, ArrayPair<__u::type> v2) {
		return __cmp::starts_with(v1.begin(), v2.begin(), v1.len(), v2.len());
	}

	#pragma endregion
	#pragma region EndsWith
	__LL_NODISCARD__ static constexpr CompareResult ends_with(__t::cptr str, __u::cptr needle, const len_t size1, const len_t size2, fun_comparebool cmp) {
		if (size1 < size2) {
			if constexpr (GET_DATA) return CompareResult(npos, LL_FALSE);
			else return LL_FALSE;
		}
		else return __cmp::starts_with_impl((str + size1) - size2, needle, size2, cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResult ends_with(__t::cptr str, __u::cptr needle, const len_t size1, const len_t size2) {
		return __cmp::ends_with(str, needle, size1, size2, common::simple_equals<__t::cinput, __u::cinput>);
	}
	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResult ends_with(__t::ctype (&str)[N1], __u::ctype (&needle)[N2], fun_comparebool cmp) {
		return __cmp::ends_with(str, needle, N1, N2, cmp);
	}
	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResult ends_with(__t::ctype (&str)[N1], __u::ctype (&needle)[N2]) {
		return __cmp::ends_with(str, needle, N1, N2);
	}

	__LL_NODISCARD__ static constexpr CompareResult ends_with(ArrayPair<__t::type> v1, ArrayPair<__u::type> v2, fun_comparebool cmp) {
		return __cmp::ends_with(v1.begin(), v2.begin(), v1.len(), v2.len(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResult ends_with(ArrayPair<__t::type> v1, ArrayPair<__u::type> v2) {
		return __cmp::ends_with(v1.begin(), v2.begin(), v1.len(), v2.len());
	}

	#pragma endregion
};

#pragma endregion
#pragma region Finders
template<class T>
//template<class T, class U, len_t N>
struct finders_cluster {
	using __find = finders_cluster<T>;
	//using __find = finders_cluster<T, U, N>;
	using __t = traits::template_types<T>;
	template<class U>
	using fun_comparebool = fnc_clss::CompareBool<__t::cinput, U>;

	#pragma region Find
	template<class U>
	__LL_NODISCARD__ static constexpr __t::cptr find(__t::cptr begin, __t::cptr end, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		LL_ASSERT(begin, "[begin] cannot be nullptr. find(__t::cptr begin, __t::cptr end, const U object)");
		LL_ASSERT(end, "[end] cannot be nullptr. find(__t::cptr begin, __t::cptr end, const U object)");

		for (; begin < end; ++begin)
			if(cmp(*begin, object)) return begin;
		return end;
	}
	template<class U>
	__LL_NODISCARD__ static constexpr __t::cptr find(__t::cptr begin, __t::cptr end, U object) __LL_EXCEPT__ {
		return __find::find(begin, end, object, common::simple_equals<__t::cinput, U>);
	}

	#pragma region Proxy
	template<class U>
	__LL_NODISCARD__ static constexpr len_t find_pos(__t::cptr begin, __t::cptr end, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		__t::cptr pos = __find::find(begin, end, object, cmp);
		return (pos != end) ? pos - begin : npos;
	}
	template<class U>
	__LL_NODISCARD__ static constexpr len_t find_pos(__t::cptr begin, __t::cptr end, U object) __LL_EXCEPT__ {
		__t::cptr pos = __find::find(begin, end, object);
		return (pos != end) ? pos - begin : npos;
	}

	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr __t::cptr find(__t::ctype (&v)[N], U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::find(v, v + N, object, cmp);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr __t::cptr find(__t::ctype (&v)[N], U object) __LL_EXCEPT__ {
		return __find::find(v, v + N, object);
	}


	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr len_t find_pos(__t::ctype (&v)[N], U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::find_pos(v, v + N, object, cmp);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr len_t find_pos(__t::ctype (&v)[N], U object) __LL_EXCEPT__ {
		return __find::find_pos(v, v + N, object);
	}


	template<class U>
	__LL_NODISCARD__ static constexpr __t::cptr find(const ArrayPair<T> arr, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::find(arr.begin(), arr.end(), object, cmp);
	}
	template<class U>
	__LL_NODISCARD__ static constexpr __t::cptr find(const ArrayPair<T> arr, U object) __LL_EXCEPT__ {
		return __find::find(arr.begin(), arr.end(), object);
	}

	template<class U>
	__LL_NODISCARD__ static constexpr len_t find_pos(const ArrayPair<T> arr, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::find_pos(arr.begin(), arr.end(), object, cmp);
	}
	template<class U>
	__LL_NODISCARD__ static constexpr len_t find_pos(const ArrayPair<T> arr, U object) __LL_EXCEPT__ {
		return __find::find_pos(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma endregion
	#pragma region rFind
	template<class U>
	__LL_NODISCARD__ static constexpr __t::cptr rfind(__t::cptr begin, __t::cptr end, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		LL_ASSERT(begin, "[begin] cannot be nullptr. rfind(__t::cptr begin, __t::cptr end, const U object)");
		LL_ASSERT(end, "[end] cannot be nullptr. rfind(__t::cptr begin, __t::cptr end, const U object)");

		for (__t::cptr i = end - 1; i > begin; --i)
			if (cmp(*i, object)) return i;
		return cmp(*begin, object) ? begin : end;
	}
	template<class U>
	__LL_NODISCARD__ static constexpr __t::cptr rfind(__t::cptr begin, __t::cptr end, U object) __LL_EXCEPT__ {
		return __find::rfind(begin, end, object, common::simple_equals<__t::cinput, U>);
	}

	#pragma region Proxy
	template<class U>
	__LL_NODISCARD__ static constexpr len_t rfind_pos(__t::cptr begin, __t::cptr end, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		__t::cptr pos = __find::rfind(begin, end, object, cmp);
		return (pos != end) ? pos - begin : npos;
	}
	template<class U>
	__LL_NODISCARD__ static constexpr len_t rfind_pos(__t::cptr begin, __t::cptr end, U object) __LL_EXCEPT__ {
		__t::cptr pos = __find::rfind(begin, end, object);
		return (pos != end) ? pos - begin : npos;
	}

	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr __t::cptr rfind(__t::ctype (&v)[N], U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::rfind(v, v + N, object, cmp);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr __t::cptr rfind(__t::ctype (&v)[N], U object) __LL_EXCEPT__ {
		return __find::rfind(v, v + N, object);
	}


	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr len_t rfind_pos(__t::ctype (&v)[N], U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::rfind_pos(v, v + N, object, cmp);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr len_t rfind_pos(__t::ctype (&v)[N], U object) __LL_EXCEPT__ {
		return __find::rfind_pos(v, v + N, object);
	}


	template<class U>
	__LL_NODISCARD__ static constexpr __t::cptr rfind(const ArrayPair<T> arr, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::rfind(arr.begin(), arr.end(), object, cmp);
	}
	template<class U>
	__LL_NODISCARD__ static constexpr __t::cptr rfind(const ArrayPair<T> arr, U object) __LL_EXCEPT__ {
		return __find::rfind(arr.begin(), arr.end(), object);
	}

	template<class U>
	__LL_NODISCARD__ static constexpr len_t rfind_pos(const ArrayPair<T> arr, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::rfind_pos(arr.begin(), arr.end(), object, cmp);
	}
	template<class U>
	__LL_NODISCARD__ static constexpr len_t rfind_pos(const ArrayPair<T> arr, U object) __LL_EXCEPT__ {
		return __find::rfind_pos(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma endregion
	#pragma region Other
	#pragma region All
	template<class U>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::cptr begin, __t::cptr end, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		LL_ASSERT(begin, "[begin] cannot be nullptr. all(__t::cptr begin, __t::cptr end, const U object)");
		LL_ASSERT(end, "[end] cannot be nullptr. all(__t::cptr begin, __t::cptr end, const U object)");

		for (; begin < end; ++begin)
			if (!cmp(*begin, object))
				return LL_FALSE;
		return LL_TRUE;
	}
	template<class U>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::cptr begin, __t::cptr end, U object) __LL_EXCEPT__ {
		return __find::all(begin, end, object, common::simple_equals<__t::cinput, U>);
	}

	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::ctype (&begin)[N], U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::all(begin, begin + N, object, cmp);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::ctype (&begin)[N], U object) __LL_EXCEPT__ {
		return __find::all(begin, begin + N, object);
	}
	template<class U>
	__LL_NODISCARD__ static constexpr ll_bool_t all(const ArrayPair<T> arr, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::all(arr.begin(), arr.end(), object, cmp);
	}
	template<class U>
	__LL_NODISCARD__ static constexpr ll_bool_t all(const ArrayPair<T> arr, U object) __LL_EXCEPT__ {
		return __find::all(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Any
	template<class U>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::cptr begin, __t::cptr end, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return static_cast<ll_bool_t>(__find::find(begin, end, object, cmp));
	}
	template<class U>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::cptr begin, __t::cptr end, U object) __LL_EXCEPT__ {
		return static_cast<ll_bool_t>(__find::find(begin, end, object));
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::ctype (&begin)[N], U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::any(begin, begin + N, object, cmp);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::ctype (&begin)[N], U object) __LL_EXCEPT__ {
		return __find::any(begin, begin + N, object);
	}
	template<class U>
	__LL_NODISCARD__ static constexpr ll_bool_t any(const ArrayPair<T> arr, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::any(arr.begin(), arr.end(), object, cmp);
	}
	template<class U>
	__LL_NODISCARD__ static constexpr ll_bool_t any(const ArrayPair<T> arr, U object) __LL_EXCEPT__ {
		return __find::any(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region None
	template<class U>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::cptr begin, __t::cptr end, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return !static_cast<ll_bool_t>(__find::find(begin, end, object, cmp));
	}
	template<class U>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::cptr begin, __t::cptr end, U object) __LL_EXCEPT__ {
		return !static_cast<ll_bool_t>(__find::find(begin, end, object));
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::ctype (&begin)[N], U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::none(begin, begin + N, object, cmp);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::ctype (&begin)[N], U object) __LL_EXCEPT__ {
		return __find::none(begin, begin + N, object);
	}
	template<class U>
	__LL_NODISCARD__ static constexpr ll_bool_t none(const ArrayPair<T> arr, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::none(arr.begin(), arr.end(), object, cmp);
	}
	template<class U>
	__LL_NODISCARD__ static constexpr ll_bool_t none(const ArrayPair<T> arr, U object) __LL_EXCEPT__ {
		return __find::none(arr.begin(), arr.end(), object);
	}

	#pragma endregion

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
	template<class U>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(__t::cptr begin, __t::cptr end, U object) {
		static_assert(traits::has_equal_operator_v<T>, "Error, <T> object has no operator==()");
		static_assert(traits::has_greater_operator_v<T>, "Error, <T> object has no operator>()");
		LL_ASSERT(begin, "[begin] cannot be nullptr. rfind(__t::cptr begin, __t::cptr end, const U object)");
		LL_ASSERT(end, "[end] cannot be nullptr. rfind(__t::cptr begin, __t::cptr end, const U object)");

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
	template<class U>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(__t::cptr begin, __t::cptr end, U object, fun_comparebool<U> cmp) {
		LL_ASSERT(begin, "[begin] cannot be nullptr. rfind(__t::cptr begin, __t::cptr end, const U object)");
		LL_ASSERT(end, "[end] cannot be nullptr. rfind(__t::cptr begin, __t::cptr end, const U object)");

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

	#pragma region Proxy
	template<class U>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(__t::cptr begin, __t::cptr end, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		__t::cptr pos = __find::binarysearch(begin, end, object, cmp);
		return (pos != end) ? pos - begin : npos;
	}
	template<class U>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(__t::cptr begin, __t::cptr end, U object) __LL_EXCEPT__ {
		__t::cptr pos = __find::binarysearch(begin, end, object);
		return (pos != end) ? pos - begin : npos;
	}

	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(__t::ctype (&v)[N], U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::binarysearch(v, v + N, object, cmp);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(__t::ctype (&v)[N], U object) __LL_EXCEPT__ {
		return __find::binarysearch(v, v + N, object);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(__t::ctype (&v)[N], U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::binarysearch_pos(v, v + N, object, cmp);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(__t::ctype (&v)[N], U object) __LL_EXCEPT__ {
		return __find::binarysearch_pos(v, v + N, object);
	}

	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(const ArrayPair<T> arr, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::binarysearch(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(const ArrayPair<T> arr, U object) __LL_EXCEPT__ {
		return __find::binarysearch(arr.begin(), arr.end(), object);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(const ArrayPair<T> arr, U object, fun_comparebool<U> cmp) __LL_EXCEPT__ {
		return __find::binarysearch_pos(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, len_t N>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(const ArrayPair<T> arr, U object) __LL_EXCEPT__ {
		return __find::binarysearch_pos(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma endregion
};

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
