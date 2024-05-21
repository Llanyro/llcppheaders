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
		#if defined(LL_REAL_CXX23)
			#warning "algorithm.hpp version error!"
		#else
			#error "algorithm.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ALGORITHM_MAYOR_ || LLANYLIB_ALGORITHM_MINOR_

#else !defined(LLANYLIB_ALGORITHM_HPP_)
#define LLANYLIB_ALGORITHM_HPP_
#define LLANYLIB_ALGORITHM_MAYOR_ 5
#define LLANYLIB_ALGORITHM_MINOR_ 0

#include "ArrayPair.hpp"
#include "common.hpp"
#include "cityhash.hpp"

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
    #if defined(__LL_SPECTRE_FUNCTIONS__)
		#pragma warning(disable:5045) // Security Spectre mitigation [SECURITY]
    #endif // __LL_UNSECURE_FUNCTIONS__
#endif // WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace algorithm {

constexpr len_t MAX_LIST_SIZE = static_cast<len_t>(-1);
constexpr len_t npos = MAX_LIST_SIZE;

#pragma region Comparators
template<class T, class U, class result_t, result_t NULL_RESULT>
class CompareData {
	// Assersts
	public:
		static_assert(traits::is_basic_type_v<result_t>, "Result type must be a basic type!");

	// Class types
	public:
		using __t = traits::template_types<T>;
		using __u = traits::template_types<U>;
		using __CompareData = traits::template_types<CompareData<T, U, result_t, NULL_RESULT>>;

	// Other internal objects
	public:
		template<class result_type, result_type NULL_RESULT>
		using __CompareDataOtherResult = traits::template_types<CompareData<T, U, result_type, NULL_RESULT>>;

	protected:
		__t::cptr value1;	// Value 1 of the result given
		__u::cptr value2;	// Value 2 of the result given
		result_t result;	// Result of comparation
	protected:
		constexpr void simpleClear() __LL_EXCEPT__ {
			this->result = NULL_RESULT;
			this->value1 = LL_NULLPTR;
			this->value2 = LL_NULLPTR;
		}
	public:
		constexpr CompareData(const result_t result) __LL_EXCEPT__
			: CompareData(LL_NULLPTR, LL_NULLPTR, result) {}
		constexpr CompareData(__t::cptr value1, __u::cptr value2, const result_t result) __LL_EXCEPT__
			: value1(value1), value2(value2), result(result) {}
		constexpr ~CompareData() __LL_EXCEPT__ {}

		constexpr CompareData(__CompareData::cref other) __LL_EXCEPT__
			: value1(other.value1), value2(other.value2), result(other.result) {}
		constexpr __CompareData::ref operator=(__CompareData::cref other) __LL_EXCEPT__ {
			this->value1 = other.value1;
			this->value2 = other.value2;
			this->result = other.result;
			return *this;
		}

		constexpr CompareData(__CompareData::move other) __LL_EXCEPT__
			: value1(other.value1), value2(other.value2), result(other.result)
		{ other.__CompareData::type::simpleClear(); }
		constexpr __CompareData::ref operator=(__CompareData::move other) __LL_EXCEPT__ {
			this->value1 = other.value1;
			this->value2 = other.value2;
			this->result = other.result;
			other.__CompareData::type::simpleClear();
			return *this;
		}

		__LL_NODISCARD__ operator __CompareData::cptr() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ operator __CompareData::ptr() __LL_EXCEPT__ = delete;

		__LL_NODISCARD__ constexpr __t::cptr getValue1() __LL_EXCEPT__ { return this->value1; }
		__LL_NODISCARD__ constexpr __u::cptr getValue2() __LL_EXCEPT__ { return this->value2; }
		__LL_NODISCARD__ constexpr result_t getResult() const __LL_EXCEPT__ { return this->result; }
};

template<class T, class U, class result_t, result_t NULL_RESULT, ll_bool_t GET_DATA>
using CompareConditional = std::conditional_t<GET_DATA, CompareData<T, U, result_t, NULL_RESULT>, result_t>;
template<class T, class U, ll_bool_t GET_DATA>
using CompareConditionalCmpT = CompareConditional<T, U, cmp_t, 0, GET_DATA>;
template<class T, class U, ll_bool_t GET_DATA>
using CompareConditionalBool = CompareConditional<T, U, ll_bool_t, LL_FALSE, GET_DATA>;

#pragma endregion

template<class T, class U = T, ll_bool_t GET_DATA = LL_FALSE>
struct compare_cluster {
	using __cmp = compare_cluster<T, U, GET_DATA>;
	using __t = traits::template_types<T>;
	using __u = traits::template_types<U>;
	using CompareResult = CompareConditionalCmpT<T, U, GET_DATA>;
	using CompareResultBool = CompareConditionalBool<T, U, GET_DATA>;
	using CompareFunc = fnc_clss::Compare<typename __t::cinput, typename __u::cinput>;
	using CompareFuncBool = fnc_clss::CompareBool<typename __t::cinput, typename __u::cinput>;
	using __ArrayPair_t = ArrayPair<typename __t::type>;
	using __ArrayPair_u = ArrayPair<typename __u::type>;

	#pragma region Compare
	__LL_NODISCARD__ static constexpr CompareResult compare(__t::cptr v1, __u::cptr v2, len_t size, CompareFunc compareFunc) __LL_EXCEPT__ {
		if (v1 == v2) {
			if constexpr (GET_DATA) return CompareResult(0);
			else return 0;
		}
		else if (!v1) {
			if constexpr (GET_DATA) return CompareResult(-1);
			else return -1;
		}
		else if(!v2){
			if constexpr (GET_DATA) return CompareResult(1);
			else return 1;
		}

		__LL_ASSERT_VAR_NULL__(compareFunc, "compareFunc");

		typename __t::cptr begin = v1;
		for (; 0 < size; --size, ++v1, ++v2) {
			cmp_t result = compareFunc(*v1, *v2);
			if (result != 0) {
				if constexpr (GET_DATA)
					return CompareResult(v1, v2, result);
				else return result;
			}
		}
		if constexpr (GET_DATA) return CompareResult(0);
		else return 0;
	}
	__LL_NODISCARD__ static constexpr CompareResult compare(__t::cptr v1, __u::cptr v2, len_t size) __LL_EXCEPT__ {
		return __cmp::compare(v1, v2, size, common::compare_with_operators<__t::cinput, __u::cinput>);
	}

	#pragma region Equals
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr v1, const len_t size1, __u::cptr v2, const len_t size2, CompareFunc compareFunc) __LL_EXCEPT__ {
		if (size1 != size2) {
			if constexpr (GET_DATA)
				return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}
		CompareResult res = __cmp::compare(v1, v2, size1, compareFunc);
		if constexpr (GET_DATA)
			return CompareResultBool(res.getValue1(), res.getValue2(), res.getResult() == 0);
		else return res == 0;
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr v1, const len_t size1, __u::cptr v2, const len_t size2) __LL_EXCEPT__ {
		if (size1 != size2) {
			if constexpr (GET_DATA)
				return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}
		CompareResult res = __cmp::compare(v1, v2, size1);
		if constexpr (GET_DATA)
			return CompareResultBool(res.getValue1(), res.getValue2(), res.getResult() == 0);
		else return res == 0;
	}

	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype (&v1)[N1], __u::ctype (&v2)[N2], CompareFunc compareFunc) __LL_EXCEPT__ {
		return __cmp::equals(v1, N1, v2, N2, compareFunc);
	}
	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype (&v1)[N1], __u::ctype(&v2)[N2]) __LL_EXCEPT__ {
		return __cmp::equals(v1, N1, v2, N2);
	}

	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& v1, const __ArrayPair_u& v2, CompareFunc compareFunc) __LL_EXCEPT__ {
		return __cmp::equals(v1.begin(), v1.len(), v2.begin(), v2.len(), compareFunc);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& v1, const __ArrayPair_u& v2) __LL_EXCEPT__ {
		return __cmp::equals(v1.begin(), v1.len(), v2.begin(), v2.len());
	}

	#pragma endregion
	#pragma endregion
	#pragma region StartsWith
	// str size needs to be bigger or equal to needle
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with_impl(__t::cptr str, __u::cptr needle, len_t size, CompareFuncBool compareFunc) {
		if (str == needle) {
			if constexpr (GET_DATA) return CompareResult(LL_TRUE);
			else return LL_TRUE;
		}
		else if (!str || !needle) {
			if constexpr (GET_DATA) return CompareResult(LL_FALSE);
			else return LL_FALSE;
		}

		__LL_ASSERT_VAR_NULL__(compareFunc, "compareFunc");

		for (; 0 < size; --size, ++str, ++needle) {
			ll_bool_t result = compareFunc(*str, *needle);
			if (!result) {
				if constexpr (GET_DATA)
					return CompareResultBool(str, needle, result);
				else return result;
			}
		}
		if constexpr (GET_DATA) return CompareResultBool(LL_TRUE);
		else return LL_TRUE;
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with_impl(__t::cptr str, __u::cptr needle, len_t size) {
		return starts_with_impl(str, needle, size, common::simple_equals<__t::cinput, __u::cinput>);
	}

	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::cptr str, const len_t size1, __u::cptr needle, const len_t size2, CompareFuncBool compareFunc) {
		if (size1 < size2) {
			if constexpr (GET_DATA)
				return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}
		else return __cmp::starts_with_impl(str, needle, size2, compareFunc);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::cptr str, const len_t size1, __u::cptr needle, const len_t size2) {
		return __cmp::starts_with(str, size1, needle, size2, common::simple_equals<__t::cinput, __u::cinput>);
	}

	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::ctype (&str)[N1], __u::ctype (&needle)[N2], CompareFuncBool compareFunc) {
		return __cmp::starts_with(str, N1, needle, N2, compareFunc);
	}
	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::ctype (&str)[N1], __u::ctype (&needle)[N2]) {
		return __cmp::starts_with(str, N1, needle, N2);
	}

	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& v1, const __ArrayPair_u& v2, CompareFuncBool compareFunc) {
		return __cmp::starts_with(v1.begin(), v1.len(), v2.begin(), v2.len(), compareFunc);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& v1, const __ArrayPair_u& v2) {
		return __cmp::starts_with(v1.begin(), v1.len(), v2.begin(), v2.len());
	}

	#pragma endregion
	#pragma region EndsWith
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::cptr str, const len_t size1, __u::cptr needle, const len_t size2, CompareFuncBool compareFunc) {
		if (size1 < size2) {
			if constexpr (GET_DATA)
				return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}
		else return __cmp::starts_with_impl((str + size1) - size2, needle, size2, compareFunc);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::cptr str, const len_t size1, __u::cptr needle, const len_t size2) {
		return __cmp::ends_with(str, size1, needle, size2, common::simple_equals<__t::cinput, __u::cinput>);
	}

	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::ctype (&str)[N1], __u::ctype (&needle)[N2], CompareFuncBool compareFunc) {
		return __cmp::ends_with(str, N1, needle, N2, compareFunc);
	}
	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::ctype (&str)[N1], __u::ctype (&needle)[N2]) {
		return __cmp::ends_with(str, N1, needle, N2);
	}

	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& v1, const __ArrayPair_u& v2, CompareFuncBool compareFunc) {
		return __cmp::ends_with(v1.begin(), v1.len(), v2.begin(), v2.len(), compareFunc);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& v1, const __ArrayPair_u& v2) {
		return __cmp::ends_with(v1.begin(), v1.len(), v2.begin(), v2.len());
	}

	#pragma endregion
};

template<class T, ll_bool_t POSITION = LL_TRUE>
struct finders_cluster {
	using __find = finders_cluster<T, POSITION>;
	using __t = traits::template_types<T>;
	using FindResult = std::conditional_t<POSITION, len_t, typename __t::cptr>;
	template<class W>
	using CompareFunc = fnc_clss::Compare<typename __t::cinput, W>;
	template<class W>
	using CompareFuncBool = fnc_clss::CompareBool<typename __t::cinput, W>;
	using __ArrayPair_t = ArrayPair<typename __t::type>;

	#pragma region Find
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr FindResult find(__t::cptr begin, __t::cptr end, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin) {
			if constexpr (POSITION) return npos;
			else return end;
		}

		__LL_ASSERT_VAR_NULL__(compareFunc, "compareFunc");

		for (typename __t::cptr data = begin; data < end; ++data)
			if (compareFunc(*data, object)) {
				if constexpr (POSITION) return data - begin;
				else return data;
			}
		if constexpr (POSITION) return npos;
		else return end;
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr FindResult find(__t::cptr begin, __t::cptr end, W object) __LL_EXCEPT__ {
		return __find::find<U, W>(begin, end, object, common::simple_equals<typename __t::cinput, U>);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr FindResult find(__t::ctype(&data)[N], W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !compareFunc) {
			if constexpr (POSITION) return npos;
			else return data + N;
		}
		return __find::find<U, W>(data, data + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr FindResult find(__t::ctype (&data)[N], W object) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) {
			if constexpr (POSITION) return npos;
			else return data + N;
		}
		return __find::find<U, W>(data, data + N, object);
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr FindResult find(const __ArrayPair_t& arr, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		return __find::find<U, W>(arr.begin(), arr.end(), object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr FindResult find(const __ArrayPair_t& arr, W object) __LL_EXCEPT__ {
		return __find::find<U, W>(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region rFind
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr FindResult rfind(__t::cptr begin, __t::cptr end, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin) {
			if constexpr (POSITION) return npos;
			else return end;
		}

		__LL_ASSERT_VAR_NULL__(compareFunc, "compareFunc");

		for (typename __t::cptr data = end - 1; data > begin; --data)
			if (compareFunc(*data, object)) {
				if constexpr (POSITION) return data - begin;
				else return data;
			}

		if constexpr (POSITION) return compareFunc(*begin, object) ? 0 : npos;
		else return compareFunc(*begin, object) ? begin : end;
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr FindResult rfind(__t::cptr begin, __t::cptr end, W object) __LL_EXCEPT__ {
		return __find::rfind<U, W>(begin, end, object, common::simple_equals<typename __t::cinput, U>);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr FindResult rfind(__t::ctype (&data)[N], W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !compareFunc) {
			if constexpr (POSITION) return npos;
			else return data + N;
		}
		return __find::rfind<U, W>(data, data + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr FindResult rfind(__t::ctype (&data)[N], W object) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) {
			if constexpr (POSITION) return npos;
			else return data + N;
		}
		return __find::rfind<U, W>(data, data + N, object);
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr FindResult rfind(const __ArrayPair_t& arr, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		return __find::rfind<U, W>(arr.begin(), arr.end(), object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr FindResult rfind(const __ArrayPair_t& arr, W object) __LL_EXCEPT__ {
		return __find::rfind<U, W>(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Contains
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(__t::cptr begin, __t::cptr end, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		if constexpr (POSITION) return __find::find<U, W>(begin, end, object, compareFunc) != npos;
		else return __find::find<U, W>(begin, end, object, compareFunc) != end;
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(__t::cptr begin, __t::cptr end, W object) __LL_EXCEPT__ {
		if constexpr (POSITION) return __find::find<U, W>(begin, end, object) != npos;
		else return __find::find<U, W>(begin, end, object) != end;
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(__t::ctype(&data)[N], W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		return __find::contains<U, W>(data, data + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(__t::ctype(&data)[N], W object) __LL_EXCEPT__ {
		return __find::contains<U, W>(data, data + N, object);
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(const __ArrayPair_t& arr, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		return __find::contains<U, W>(arr.begin(), arr.end(), object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(const __ArrayPair_t& arr, W object) __LL_EXCEPT__ {
		return __find::contains<U, W>(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Other
	#pragma region All
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::cptr begin, __t::cptr end, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin) return LL_FALSE;

		__LL_ASSERT_VAR_NULL__(compareFunc, "compareFunc");

		for (; begin < end; ++begin)
			if (!compareFunc(*begin, object))
				return LL_FALSE;
		return LL_TRUE;
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::cptr begin, __t::cptr end, W object) __LL_EXCEPT__ {
		return __find::all<U, W>(begin, end, object, common::simple_equals<typename __t::cinput, U>);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::ctype (&data)[N], W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !compareFunc) return LL_FALSE;
		return __find::all<U, W>(begin, begin + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::ctype (&data)[N], W object) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) return LL_FALSE;
		return __find::all<U, W>(begin, begin + N, object);
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t all(const __ArrayPair_t& arr, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		return __find::all<U, W>(arr.begin(), arr.end(), object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t all(const __ArrayPair_t& arr, W object) __LL_EXCEPT__ {
		return __find::all<U, W>(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Any
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::cptr begin, __t::cptr end, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		return static_cast<ll_bool_t>(__find::find<U, W>(begin, end, object, compareFunc));
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::cptr begin, __t::cptr end, W object) __LL_EXCEPT__ {
		return static_cast<ll_bool_t>(__find::find<U, W>(begin, end, object));
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::ctype (&data)[N], W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !compareFunc) return LL_FALSE;
		return __find::any<U, W>(begin, begin + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::ctype (&data)[N], W object) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) return LL_FALSE;
		return __find::any<U, W>(begin, begin + N, object);
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t any(const __ArrayPair_t& arr, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		return __find::any<U, W>(arr.begin(), arr.end(), object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t any(const __ArrayPair_t& arr, W object) __LL_EXCEPT__ {
		return __find::any<U, W>(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region None
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::cptr begin, __t::cptr end, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		return !static_cast<ll_bool_t>(__find::find<U, W>(begin, end, object, compareFunc));
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::cptr begin, __t::cptr end, W object) __LL_EXCEPT__ {
		return !static_cast<ll_bool_t>(__find::find<U, W>(begin, end, object));
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::ctype (&data)[N], W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !compareFunc) return LL_FALSE;
		return __find::none<U, W>(begin, begin + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::ctype (&data)[N], W object) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) return LL_FALSE;
		return __find::none<U, W>(begin, begin + N, object);
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t none(const __ArrayPair_t& arr, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		return __find::none<U, W>(arr.begin(), arr.end(), object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr ll_bool_t none(const __ArrayPair_t& arr, W object) __LL_EXCEPT__ {
		return __find::none<U, W>(arr.begin(), arr.end(), object);
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
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(__t::cptr begin, __t::cptr end, W object) {
		static_assert(traits::has_equal_operator_v<T>, "Error, <T> object has no operator==()");
		static_assert(traits::has_greater_operator_v<T>, "Error, <T> object has no operator>()");
		len_t low = ZERO_UI64;
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
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(__t::cptr begin, __t::cptr end, W object, CompareFunc<W> compareFunc) {
		__LL_ASSERT_VAR_NULL__(compareFunc, "compareFunc");

		len_t low = ZERO_UI64;
		len_t high = end - begin;
		while (low <= high) {
			len_t mid = ((high - low) / 2);
			cmp_t res = compareFunc(begin[mid], object);
			if (res == 0) return begin + mid;
			else if (res > 0) high = mid;
			else low = mid + 1;
		}
		return end;
	}

	#pragma region Proxy
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(__t::cptr begin, __t::cptr end, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		typename __t::cptr pos = __find::binarysearch(begin, end, object, compareFunc);
		return (pos != end) ? pos - begin : npos;
	}
	template<class U, class W = traits::template_types<U>::cinput>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(__t::cptr begin, __t::cptr end, W object) __LL_EXCEPT__ {
		typename __t::cptr pos = __find::binarysearch(begin, end, object);
		return (pos != end) ? pos - begin : npos;
	}

	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(__t::ctype (&data)[N], W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !compareFunc) return data + N;
		return __find::binarysearch(data, data + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(__t::ctype (&data)[N], W object) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) return data + N;
		return __find::binarysearch(data, data + N, object);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(__t::ctype (&data)[N], W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !compareFunc) return data + N;
		return __find::binarysearch_pos(data, data + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(__t::ctype (&data)[N], W object) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) return data + N;
		return __find::binarysearch_pos(data, data + N, object);
	}

	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(const __ArrayPair_t& arr, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		return __find::binarysearch(arr.begin(), arr.end(), object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(const __ArrayPair_t& arr, W object) __LL_EXCEPT__ {
		return __find::binarysearch(arr.begin(), arr.end(), object);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(const __ArrayPair_t& arr, W object, CompareFuncBool<W> compareFunc) __LL_EXCEPT__ {
		return __find::binarysearch_pos(arr.begin(), arr.end(), object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(const __ArrayPair_t& arr, W object) __LL_EXCEPT__ {
		return __find::binarysearch_pos(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma endregion
};

template<class T>
struct data_manipulation {
	using __data = data_manipulation<T>;
	using __t = traits::template_types<T>;
	using SwapFunc = fnc_clss::SwapFunction<typename __t::type>;
	template<class W>
	using FillFunc = fnc_clss::SwapFunction<typename __t::type, W>;

	#pragma region Reverse
	static constexpr void reverse(__t::ptr begin, __t::ptr end, SwapFunc swap) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin || !swap) return;
		for (; begin < end; ++begin, --end)
			swap(*begin, *end);
	}
	static constexpr void reverse(__t::ptr begin, __t::ptr end) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin) return;
		__data::reverse(begin, end, common::simple_swap<typename __t::type>);
	}
	template<len_t N>
	static constexpr void reverse(__t::type(&data)[N]) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) return;
		__data::reverse(data, data + N - 1);
	}
	template<len_t N>
	static constexpr void reverse(__t::type(&data)[N], SwapFunc revSwap) __LL_EXCEPT__ {
		if (!data || swap || N == ZERO_UI64) return;
		__data::reverse(v, data + N - 1, revSwap);
	}

	#pragma endregion
	#pragma region Fillers
	template<class U, class W = traits::get_object_reference_t<T>>
	static constexpr void fill(__t::ptr begin, __t::ptr end, W object, FillFunc<U> setFunc) {
		if (!begin || !end || end <= begin || !setFunc) return;
		for (; begin < end; ++begin) setFunc(*begin, object);
	}
	template<class U, class W = traits::get_object_reference_t<T>>
	static constexpr void fill(__t::ptr begin, __t::ptr end, W object) {
		if (!begin || !end || end <= begin) return;
		__data::fill<U, W>(begin, end, object, common::simple_set<typename __t::type, U>);
	}
	template<class U, len_t N, class W = traits::get_object_reference_t<T>>
	static constexpr void fill(__t::type(&data)[N], W object, FillFunc<U> setFunc) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !setFunc) return;
		__data::fill<U, W>(data, data + N, object, setFunc);
	}
	template<class U, len_t N, class W = traits::get_object_reference_t<T>>
	static constexpr void fill(__t::type(&data)[N], W object) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) return;
		__data::fill<U, W>(data, data + N, object);
	}

	#pragma endregion
	#pragma region ShiftLeft
	template<class U, class W = traits::get_object_reference_t<T>>
	static constexpr void shiftLeft(__t::ptr begin, __t::ptr end, const len_t num, W null, SwapFunc swap, FillFunc<U> setFunc) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin || !swap || !setFunc) return;

		--end;
		for (T* i = end - num; i > begin; --i, --end)
			swap(*end, *i);
		swap(*begin, *(begin + num));

		__data::fill<U, W>(begin, begin + num, null, setFunc);
	}
	template<class U, class W = traits::get_object_reference_t<T>>
	static constexpr void shiftLeft(__t::ptr begin, __t::ptr end, const len_t num, const U null, SwapFunc swap) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin) return;
		__data::shiftLeft<U, W>(begin, end, num, null, swap, common::simple_set<typename __t::type, U>);
	}
	template<class U, class W = traits::get_object_reference_t<T>>
	static constexpr void shiftLeft(__t::ptr begin, __t::ptr end, const len_t num, const U null, FillFunc<U> setFunc) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin) return;
		__data::shiftLeft<U, W>(begin, end, num, null, common::simple_swap<typename __t::type>, setFunc);
	}
	template<class U, class W = traits::get_object_reference_t<T>>
	static constexpr void shiftLeft(__t::ptr begin, __t::ptr end, const len_t num, const U null) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin) return;
		__data::shiftLeft<U, W>(begin, end, num, null, common::simple_swap<typename __t::type>, common::simple_set<typename __t::type, U>);
	}
	template<class U, class W = traits::get_object_reference_t<T>, len_t N>
	static constexpr void shiftLeft(__t::type(&data)[N], const len_t num, const U null, SwapFunc swap) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !swap) return;
		__data::shiftLeft<U, W>(data, data + N, num, null, swap, common::simple_set<typename __t::type, U>);
	}
	template<class U, class W = traits::get_object_reference_t<T>, len_t N>
	static constexpr void shiftLeft(__t::type(&data)[N], const len_t num, const U null, FillFunc<U> setFunc) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !setFunc) return;
		__data::shiftLeft<U, W>(data, data + N, num, null, common::simple_swap<typename __t::type>, setFunc);
	}
	template<class U, class W = traits::get_object_reference_t<T>, len_t N>
	static constexpr void shiftLeft(__t::type(&data)[N], const len_t num, const U null) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) return;
		__data::shiftLeft<U, W>(data, data + N, num, null, common::simple_swap<typename __t::type>, common::simple_set<typename __t::type, U>);
	}

	#pragma endregion
	#pragma region ShiftRight
	template<class U, class W = traits::get_object_reference_t<T>>
	static constexpr void shifRight(__t::ptr begin, __t::ptr end, const len_t num, W null, SwapFunc swap, FillFunc<U> setFunc) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin || !swap || !setFunc) return;
		for (T* i = begin + num; i < end; ++i, ++begin) swap(*begin, *i);
		__data::fill<U, W>(end - num, end, null, setFunc);
	}
	template<class U, class W = traits::get_object_reference_t<T>>
	static constexpr void shifRight(__t::ptr begin, __t::ptr end, const len_t num, const U null, SwapFunc swap) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin) return;
		__data::shifRight<U, W>(begin, end, num, null, swap, common::simple_set<typename __t::type, U>);
	}
	template<class U, class W = traits::get_object_reference_t<T>>
	static constexpr void shifRight(__t::ptr begin, __t::ptr end, const len_t num, const U null, FillFunc<U> setFunc) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin) return;
		__data::shifRight<U, W>(begin, end, num, null, common::simple_swap<typename __t::type>, setFunc);
	}
	template<class U, class W = traits::get_object_reference_t<T>>
	static constexpr void shifRight(__t::ptr begin, __t::ptr end, const len_t num, const U null) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin) return;
		__data::shifRight<U, W>(begin, end, num, null, common::simple_swap<typename __t::type>, common::simple_set<typename __t::type, U>);
	}
	template<class U, class W = traits::get_object_reference_t<T>, len_t N>
	static constexpr void shifRight(__t::type(&data)[N], const len_t num, const U null, SwapFunc swap) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !swap) return;
		__data::shifRight<U, W>(data, data + N, num, null, swap, common::simple_set<typename __t::type, U>);
	}
	template<class U, class W = traits::get_object_reference_t<T>, len_t N>
	static constexpr void shifRight(__t::type(&data)[N], const len_t num, const U null, FillFunc<U> setFunc) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !setFunc) return;
		__data::shifRight<U, W>(data, data + N, num, null, common::simple_swap<typename __t::type>, setFunc);
	}
	template<class U, class W = traits::get_object_reference_t<T>, len_t N>
	static constexpr void shifRight(__t::type(&data)[N], const len_t num, const U null) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) return;
		__data::shifRight<U, W>(data, data + N, num, null, common::simple_swap<typename __t::type>, common::simple_set<typename __t::type, U>);
	}

	#pragma endregion
	#pragma region Qsort
	template<class T, class U = traits::template_types<T>>
	static constexpr T* qsort_div(
		T* arr,
		T* begin,
		T* end,
		fnc_clss::SwapFunction<typename U::type> swap,
		fnc_clss::Compare<typename U::cinput> cmp
	) __LL_EXCEPT__ {
		__LL_ASSERT_VAR_NULL__(arr, "arr");
		__LL_ASSERT_VAR_NULL__(begin, "begin");
		__LL_ASSERT_VAR_NULL__(end, "end");
		__LL_ASSERT_VAR_NULL__(swap, "swap");
		__LL_ASSERT_VAR_NULL__(cmp, "cmp");
	
		T* left = begin;
		T* right = end;
		T* piv = arr;
	
		while (left < right) {
			for (; cmp(*right, *piv) > 0; --right);
			for (; (left < right) && cmp(*left, *piv) <= 0; ++left);
			if (left < right) swap(*left, *right);
		}
		swap(*right, *begin);
		return right;
	}
	template<class T, class U = traits::template_types<T>>
	static constexpr void quicksort(
		T* arr, T* begin, T* end,
		fnc_clss::SwapFunction<typename U::type> swap,
		fnc_clss::Compare<typename U::cinput> cmp
	) {
		if (begin < end) {
			T* pivote = qsort_div<T, U>(arr, begin, end, swap, cmp);
			//if (pivote >= begin && pivote <= end) {
			quicksort<T, U>(arr, begin, pivote - 1, swap, cmp);
			quicksort<T, U>(arr, pivote + 1, end, swap, cmp);
			//}
		}
	}
	template<class T, class U = traits::template_types<T>>
	static constexpr void quicksort(T* arr, T* begin, T* end) {
		quicksort<T>(arr, begin, end, common::simple_swap<T>, common::compare_with_operators<T>);
	}
	template<class T, class U = traits::template_types<T>>
	static constexpr void quicksort(T* begin, T* end) {
		quicksort<T, U>(begin, begin, end);
	}
	template<class T, len_t N, class U = traits::template_types<T>>
	static constexpr void quicksort(T(&arr)[N]) {
		quicksort<T, U>(arr, arr, arr + (N - 1));
	}

	#pragma endregion
};

struct has_cluster {
	__LL_NODISCARD__ static constexpr Hash hash(const ArrayPair<ll_char_t>& arr) {
		if (arr.empty()) return meta::Hash();
		else return llcpp::meta::city::CityHash::cityHash64(arr.begin(), arr.len());
	}
	template<len_t N, class T>
	__LL_NODISCARD__ static constexpr Hash hash(const ArrayPair<T>& arr) {
		if constexpr (traits::has_convert_to_chars_v<T> && N != ZERO_UI64) {
			constexpr len_t BUFFERLEN = sizeof(T) * N;
			ll_char_t buffer[BUFFERLEN]{};
			ll_char_t* i = buffer;
			const T* data = arr.begin();
			const T* data_end = arr.end();
			for (; data < data_end; ++data, i += sizeof(T))
				data->convertToChars(i);
			return llcpp::meta::city::CityHash::cityHash64(buffer, BUFFERLEN);
		}
		else return meta::Hash();
	}
	template<class T, len_t N>
	__LL_NODISCARD__ static constexpr Hash hash(const T(&arr)[N]) {
		if constexpr (traits::has_convert_to_chars_v<T> && N != ZERO_UI64) {
			constexpr len_t BUFFERLEN = sizeof(T) * N;
			ll_char_t buffer[BUFFERLEN]{};
			ll_char_t* i = buffer;
			const T* data = arr;
			const T* data_end = arr + N;
			for (; data < data_end; ++data, i += sizeof(T))
				data->convertToChars(i);
			return llcpp::meta::city::CityHash::cityHash64(buffer, BUFFERLEN);
		}
		else return meta::Hash();
	}
	template<class T, len_t N>
	__LL_NODISCARD__ static constexpr Hash hash(const T* arr) {
		if constexpr (traits::has_convert_to_chars_v<T> && N != ZERO_UI64) {
			constexpr len_t BUFFERLEN = sizeof(T) * N;
			ll_char_t buffer[BUFFERLEN]{};
			ll_char_t* i = buffer;
			const T* data = arr;
			const T* data_end = arr + N;
			for (; data < data_end; ++data, i += sizeof(T))
				data->convertToChars(i);
			return llcpp::meta::city::CityHash::cityHash64(buffer, BUFFERLEN);
		}
		else return meta::Hash();
	}
	template<class T>
	__LL_NODISCARD__ static constexpr Hash hash(const T& object) {
		if constexpr (traits::has_convert_to_chars_v<T>) {
			constexpr len_t BUFFERLEN = sizeof(T);
			ll_char_t buffer[BUFFERLEN]{};
			if constexpr (traits::is_pointer_v<T>)
				object->convertToChars(buffer);
			else object.convertToChars(buffer);
			return llcpp::meta::city::CityHash::cityHash64(buffer, BUFFERLEN);
		}
		else return meta::Hash();
	}
};

///constexpr int example() {
///	int arr[] = { 0, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
///	//quicksort(arr);
///	//return arr[0];
///	int* piv = qsort_div(arr, arr, arr + 9, common::simple_swap<int>, common::compare_with_operators<int>);
///	return *piv;
///}
///constexpr int asdf1 = example();

} // namespace algorithm
} // namespace meta
} // namespace llcpp

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#endif // LLANYLIB_ALGORITHM_HPP_
