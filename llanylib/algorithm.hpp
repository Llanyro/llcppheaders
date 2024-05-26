//////////////////////////////////////////////
//	algorithm.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 6.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ALGORITHM_HPP_) // Guard && version protector
	#if LLANYLIB_ALGORITHM_MAYOR_ != 6 || LLANYLIB_ALGORITHM_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "algorithm.hpp version error!"
		#else
			#error "algorithm.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ALGORITHM_MAYOR_ || LLANYLIB_ALGORITHM_MINOR_

#else !defined(LLANYLIB_ALGORITHM_HPP_)
#define LLANYLIB_ALGORITHM_HPP_
#define LLANYLIB_ALGORITHM_MAYOR_ 6
#define LLANYLIB_ALGORITHM_MINOR_ 0

#include "common.hpp"
#include "cityhash.hpp"
#include "BasicTypeWrapper.hpp"

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
		if (static_cast<const void*>(v1) == static_cast<const void*>(v2)) {
			if constexpr (GET_DATA) return CompareResult(ZERO_I32);
			else return ZERO_I32;
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
		for (; size > ZERO_UI64; --size, ++v1, ++v2) {
			cmp_t result = compareFunc(*v1, *v2);
			if (result != ZERO_I32) {
				if constexpr (GET_DATA)
					return CompareResult(v1, v2, result);
				else return result;
			}
		}
		if constexpr (GET_DATA) return CompareResult(ZERO_I32);
		else return ZERO_I32;
	}
	__LL_NODISCARD__ static constexpr CompareResult compare(__t::cptr v1, __u::cptr v2, len_t size) __LL_EXCEPT__ {
		return __cmp::compare(v1, v2, size, common::compare_with_operators<__t::cinput, __u::cinput>);
	}

	#pragma region Equals
	#pragma region Ptr
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr v1, const len_t size1, __u::cptr v2, const len_t size2, CompareFunc compareFunc) __LL_EXCEPT__ {
		if (size1 != size2) {
			if constexpr (GET_DATA)
				return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}
		CompareResult res = __cmp::compare(v1, v2, size1, compareFunc);
		if constexpr (GET_DATA)
			return CompareResultBool(res.getValue1(), res.getValue2(), res.getResult() == ZERO_I32);
		else return res == ZERO_I32;
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr v1, const len_t size1, __u::cptr v2, const len_t size2) __LL_EXCEPT__ {
		if (size1 != size2) {
			if constexpr (GET_DATA)
				return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}
		CompareResult res = __cmp::compare(v1, v2, size1);
		if constexpr (GET_DATA)
			return CompareResultBool(res.getValue1(), res.getValue2(), res.getResult() == ZERO_I32);
		else return res == ZERO_I32;
	}
	//template<len_t N2>
	//__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr v1, const len_t size1, __u::ctype(&v2)[N2], CompareFunc compareFunc) __LL_EXCEPT__ {
	//	return __cmp::equals(v1, size1, v2, N2, compareFunc);
	//}
	//template<len_t N2>
	//__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr v1, const len_t size1, __u::ctype(&v2)[N2]) __LL_EXCEPT__ {
	//	return __cmp::equals(v1, size1, v2, N2);
	//}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr v1, const len_t size1, const __ArrayPair_u& v2, CompareFunc compareFunc) __LL_EXCEPT__ {
		return __cmp::equals(v1, size1, v2.begin(), v2.size(), compareFunc);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr v1, const len_t size1, const __ArrayPair_u& v2) __LL_EXCEPT__ {
		return __cmp::equals(v1, size1, v2.begin(), v2.size());
	}

	#pragma endregion
	#pragma region Array
	template<len_t N1>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&v1)[N1], __u::cptr v2, const len_t size2, CompareFunc compareFunc) __LL_EXCEPT__ {
		return __cmp::equals(v1, N1, v2, size2, compareFunc);
	}
	template<len_t N1>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&v1)[N1], __u::cptr v2, const len_t size2) __LL_EXCEPT__ {
		return __cmp::equals(v1, N1, v2, size2);
	}
	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&v1)[N1], __u::ctype(&v2)[N2], CompareFunc compareFunc) __LL_EXCEPT__ {
		return __cmp::equals(v1, N1, v2, N2, compareFunc);
	}
	template<len_t N1, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&v1)[N1], __u::ctype(&v2)[N2]) __LL_EXCEPT__ {
		return __cmp::equals(v1, N1, v2, N2);
	}
	template<len_t N1>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&v1)[N1], const __ArrayPair_u& v2, CompareFunc compareFunc) __LL_EXCEPT__ {
		return __cmp::equals(v1, N1, v2.begin(), v2.size(), compareFunc);
	}
	template<len_t N1>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&v1)[N1], const __ArrayPair_u& v2) __LL_EXCEPT__ {
		return __cmp::equals(v1, N1, v2.begin(), v2.size());
	}

	#pragma endregion
	#pragma region ArrayPair
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& v1, __u::cptr v2, const len_t size2, CompareFunc compareFunc) __LL_EXCEPT__ {
		return __cmp::equals(v1.begin(), v1.size(), v2, size2, compareFunc);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& v1, __u::cptr v2, const len_t size2) __LL_EXCEPT__ {
		return __cmp::equals(v1.begin(), v1.size(), v2, size2);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& v1, const __ArrayPair_u& v2, CompareFunc compareFunc) __LL_EXCEPT__ {
		return __cmp::equals(v1.begin(), v1.size(), v2.begin(), v2.size(), compareFunc);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& v1, const __ArrayPair_u& v2) __LL_EXCEPT__ {
		return __cmp::equals(v1.begin(), v1.size(), v2.begin(), v2.size());
	}
	//template<len_t N2>
	//__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& v1, const len_t size1, __u::ctype(&v2)[N2], CompareFunc compareFunc) __LL_EXCEPT__ {
	//	return __cmp::equals(v1.begin(), v1.size(), v2, N2, compareFunc);
	//}
	//template<len_t N2>
	//__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& v1, const len_t size1, __u::ctype(&v2)[N2]) __LL_EXCEPT__ {
	//	return __cmp::equals(v1.begin(), v1.size(), v2, N2);
	//}

	#pragma endregion

	#pragma endregion
	#pragma endregion
	#pragma region StartsWith
	// str size needs to be bigger or equal to needle
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with_impl(__t::cptr str, __u::cptr needle, len_t size, CompareFuncBool compareFunc) {
		if (str == needle) {
			if constexpr (GET_DATA) return CompareResultBool(LL_TRUE);
			else return LL_TRUE;
		}
		else if (!str || !needle) {
			if constexpr (GET_DATA) return CompareResultBool(LL_FALSE);
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
		return __cmp::starts_with(v1.begin(), v1.size(), v2.begin(), v2.size(), compareFunc);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& v1, const __ArrayPair_u& v2) {
		return __cmp::starts_with(v1.begin(), v1.size(), v2.begin(), v2.size());
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
		return __cmp::ends_with(v1.begin(), v1.size(), v2.begin(), v2.size(), compareFunc);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& v1, const __ArrayPair_u& v2) {
		return __cmp::ends_with(v1.begin(), v1.size(), v2.begin(), v2.size());
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
		if (!begin || !end || end <= begin || !compareFunc) {
			if constexpr (POSITION) return npos;
			else return end;
			//throw "Find error values";
		}

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
		return __find::find<U, W>(data, data + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr FindResult find(__t::ctype (&data)[N], W object) __LL_EXCEPT__ {
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
		if (!begin || !end || end <= begin || !compareFunc) {
			if constexpr (POSITION) return npos;
			else return end;
		}

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
		return __find::rfind<U, W>(data, data + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr FindResult rfind(__t::ctype (&data)[N], W object) __LL_EXCEPT__ {
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
		return __find::all<U, W>(data, data + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::ctype (&data)[N], W object) __LL_EXCEPT__ {
		return __find::all<U, W>(data, data + N, object);
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
		return __find::any<U, W>(data, data + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::ctype (&data)[N], W object) __LL_EXCEPT__ {
		return __find::any<U, W>(data, data + N, object);
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
		return __find::none<U, W>(data, data + N, object, compareFunc);
	}
	template<class U, class W = traits::template_types<U>::cinput, len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::ctype (&data)[N], W object) __LL_EXCEPT__ {
		return __find::none<U, W>(data, data + N, object);
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
			len_t mid = ((high + low) >> 1);
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
			len_t mid = ((high - low) >> 1);
			cmp_t res = compareFunc(begin[mid], object);
			if (res == ZERO_I32) return begin + mid;
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
struct data_manipulation_cluster {
	using __data = data_manipulation_cluster<T>;
	using __t = traits::template_types<T>;
	using SwapFunc = fnc_clss::SwapFunction<typename __t::type>;
	template<class W>
	using FillFunc = fnc_clss::SetFunction<typename __t::type, W>;

	#pragma region Reverse
	static constexpr void reverse(__t::ptr begin, __t::ptr end, SwapFunc swap) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin || !swap) return;
		for (; begin < end; ++begin, --end)
			swap(*begin, *end);
	}
	static constexpr void reverse(__t::ptr begin, __t::ptr end) __LL_EXCEPT__ {
		__data::reverse(begin, end, common::simple_swap<typename __t::type>);
	}
	template<len_t N>
	static constexpr void reverse(__t::type(&data)[N]) __LL_EXCEPT__ {
		__data::reverse(data, data + N - 1);
	}
	template<len_t N>
	static constexpr void reverse(__t::type(&data)[N], SwapFunc swap) __LL_EXCEPT__ {
		__data::reverse(data, data + N - 1, swap);
	}

	#pragma endregion
	#pragma region Fillers
	template<class U, class W = traits::template_types<U>>
	static constexpr void fill(__t::ptr begin, __t::ptr end, typename W::cinput object, FillFunc<typename W::cinput> setFunc) {
		if (!begin || !end || end <= begin || !setFunc) return;
		for (; begin <= end; ++begin) setFunc(*begin, object);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void fill(__t::ptr begin, __t::ptr end, typename W::cinput object) {
		__data::fill<U, W>(begin, end, object, common::simple_set<typename __t::type, typename W::cinput>);
	}
	template<class U, class W = traits::template_types<U>, len_t N>
	static constexpr void fill(__t::type(&data)[N], typename W::cinput object, FillFunc<typename W::cinput> setFunc) __LL_EXCEPT__ {
		__data::fill<U, W>(data, data + N - 1, object, setFunc);
	}
	template<class U, class W = traits::template_types<U>, len_t N>
	static constexpr void fill(__t::type(&data)[N], typename W::cinput object) __LL_EXCEPT__ {
		__data::fill<U, W>(data, data + N - 1, object);
	}

	#pragma endregion
	#pragma region Copy
	template<class U, class W = traits::template_types<U>>
	static constexpr void copy(W::cptr src, __t::ptr dst, len_t size, FillFunc<typename W::cinput> setFunc) {
		if (!src || !dst || size == ZERO_UI64 || !setFunc) return;
		for (; size > ZERO_UI64; ++src, ++dst) setFunc(*dst, *src);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void copy(W::cptr src, __t::ptr dst, len_t size) {
		__data::copy<U, W>(src, dst, size, common::simple_set<typename __t::type, typename W::cinput>);
	}
	template<class U, class W = traits::template_types<U>, len_t N>
	static constexpr void copy(W::ctype(&src)[N], __t::ptr dst, FillFunc<typename W::cinput> setFunc) {
		__data::copy<U, W>(src, dst, N, setFunc);
	}
	template<class U, class W = traits::template_types<U>, len_t N>
	static constexpr void copy(W::ctype(&src)[N], __t::ptr dst) {
		__data::copy<U, W>(src, dst, N, common::simple_set<typename __t::type, typename W::cinput>);
	}

	#pragma endregion
	#pragma region ShiftLeft
	template<class U, class W = traits::template_types<U>>
	static constexpr void shiftLeft(__t::ptr arr, const len_t size, const len_t first, len_t num, typename W::cinput null, FillFunc<typename __t::cinput> moveFunc, FillFunc<typename W::cinput> setNullFunc) __LL_EXCEPT__ {
		if (!arr || !moveFunc || !setNullFunc) return;
		if (size <= 1ull || num == ZERO_UI64 || first < ZERO_UI64 || first >= size) return;
		if (first + num >= size) num = size - first - 1ull;

		len_t size_loop = size - num;
		typename __t::ptr last = arr + size_loop;
		for (typename __t::ptr src = arr + num; arr < last; ++arr, ++src)
			moveFunc(*arr, *src);
		last += num - 1ull;
		__data::fill<U, W>(arr, last, null, setNullFunc);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void shiftLeft(__t::ptr arr, const len_t size, const len_t first, const len_t num, typename W::cinput null) __LL_EXCEPT__ {
		__data::shiftLeft<U, W>(arr, size, first, num, null, common::simple_set<typename __t::type, typename __t::cinput>, common::simple_set<typename __t::type, typename W::cinput>);
	}
	//template<class U, class W = traits::template_types<U>>
	//static constexpr void shiftLeft(__t::ptr begin, __t::ptr end, const len_t num, typename W::cinput null, SwapFunc swap) __LL_EXCEPT__ {
	//	__data::shiftLeft<U, W>(begin, end, num, null, swap, common::simple_set<typename __t::type, typename W::cinput>);
	//}
	//template<class U, class W = traits::template_types<U>>
	//static constexpr void shiftLeft(__t::ptr begin, __t::ptr end, const len_t num, typename W::cinput null, FillFunc<typename W::cinput> setFunc) __LL_EXCEPT__ {
	//	__data::shiftLeft<U, W>(begin, end, num, null, common::simple_swap<typename __t::type>, setFunc);
	//}
	//template<class U, class W = traits::template_types<U>, len_t N>
	//static constexpr void shiftLeft(__t::type(&data)[N], const len_t num, typename W::cinput null, SwapFunc swap) __LL_EXCEPT__ {
	//	__data::shiftLeft<U, W>(data, data + N, num, null, swap);
	//}
	//template<class U, class W = traits::template_types<U>, len_t N>
	//static constexpr void shiftLeft(__t::type(&data)[N], const len_t num, typename W::cinput null, FillFunc<typename W::cinput> setFunc) __LL_EXCEPT__ {
	//	__data::shiftLeft<U, W>(data, data + N, num, null, setFunc);
	//}
	template<class U, class W = traits::template_types<U>, len_t N>
	static constexpr void shiftLeft(__t::type(&data)[N], const len_t first, const len_t num, typename W::cinput null) __LL_EXCEPT__ {
		__data::shiftLeft<U, W>(data, N, first, num, null);
	}

	#pragma endregion
	#pragma region ShiftRight
	template<class U, class W = traits::template_types<U>>
	static constexpr void shifRight(__t::ptr arr, const len_t size, const len_t first, len_t num, typename W::cinput null, FillFunc<typename __t::cinput> moveFunc, FillFunc<typename W::cinput> setNullFunc) __LL_EXCEPT__ {
		if (!arr || !moveFunc || !setNullFunc) return;
		if (size <= 1ull || num == ZERO_UI64 || first < ZERO_UI64 || first >= size) return;

		len_t size_loop = first + num;
		if (size_loop >= size) num = size - first - 1ull;

		typename __t::ptr dst = arr + size - 1ull;
		typename __t::ptr last = arr + size_loop;
		for (typename __t::ptr src = dst - num; dst >= last ; --dst, --src)
			moveFunc(*dst, *src);
		__data::fill<U, W>(arr + first, --last, null, setNullFunc);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void shifRight(__t::ptr arr, const len_t size, const len_t first, const len_t num, typename W::cinput null) __LL_EXCEPT__ {
		__data::shifRight<U, W>(arr, size, first, num, null, common::simple_set<typename __t::type, typename __t::cinput>, common::simple_set<typename __t::type, typename W::cinput>);
	}
	//template<class U, class W = traits::template_types<U>>
	//static constexpr void shifRight(__t::ptr begin, __t::ptr end, const len_t num, typename W::cinput null, SwapFunc swap) __LL_EXCEPT__ {
	//	__data::shifRight<U, W>(begin, end, num, null, swap, common::simple_set<typename __t::type, U>);
	//}
	//template<class U, class W = traits::template_types<U>>
	//static constexpr void shifRight(__t::ptr begin, __t::ptr end, const len_t num, typename W::cinput null, FillFunc<typename W::cinput> setFunc) __LL_EXCEPT__ {
	//	__data::shifRight<U, W>(begin, end, num, null, common::simple_swap<typename __t::type>, setFunc);
	//}
	//template<class U, class W = traits::template_types<U>, len_t N>
	//static constexpr void shifRight(__t::type(&data)[N], const len_t num, typename W::cinput null, SwapFunc swap) __LL_EXCEPT__ {
	//	__data::shifRight<U, W>(data, data + N, num, null, swap, common::simple_set<typename __t::type, U>);
	//}
	//template<class U, class W = traits::template_types<U>, len_t N>
	//static constexpr void shifRight(__t::type(&data)[N], const len_t num, typename W::cinput null, FillFunc<typename W::cinput> setFunc) __LL_EXCEPT__ {
	//	__data::shifRight<U, W>(data, data + N, num, null, common::simple_swap<typename __t::type>, setFunc);
	//}
	template<class U, class W = traits::template_types<U>, len_t N>
	static constexpr void shifRight(__t::type(&data)[N], const len_t first, const len_t num, typename W::cinput null) __LL_EXCEPT__ {
		__data::shiftLeft<U, W>(data, N, first, num, null);
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
			for (; (left < right) && cmp(*left, *piv) <= ZERO_I32; ++left);
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
	template<class T, class U = traits::template_types<T>, len_t N>
	static constexpr void quicksort(T(&arr)[N]) {
		quicksort<T, U>(arr, arr, arr + (N - 1));
	}

	#pragma endregion
};

#pragma region HashCluster

// Hash modes:
//	1. Copy all object data into a string and hash that data
//	2. Copy all object Hash into a string and hash all the hashes
//	3. Add to any method TypeId to hash
//		3.1: Use type as raw data to hash
//		3.2: Use type hash to hash
//		3.3: Use both
//	
struct hash_cluster {
	public:
		enum class HashVersion {
			// Converts objects to chars in a contiguous vector
			// Then using CityHash hash all vector
			// Objects are transformed to chars using a function in the object class
			// The function signature is: constexpr void convertToChars(ll_char_t** buffer, HashV1Status** errors, const len_t size) const __LL_EXCEPT__;
			// If you need an example go to BasicTypeWrapper, it has that function implemented and explained
			V1,
			// Hashes every object one by one
			// Then hashes the generated hash vector
			// Objects are transformed to chars using a function in the object class
			// The function signature is: constexpr operator llcpp::meta::Hash() const __LL_EXCEPT__;
			V2
		};
		enum class HashV1Status {
			Ok,
			ErrorPointer,
			CustomFunctionInternalError,
			ErrorNoFunctionAvaible
		};

		static constexpr ll_char_t** NULL_CHAR_CONVERTIBLE = LL_NULLPTR;
		static constexpr HashV1Status** NULL_ERROR = LL_NULLPTR;
		static constexpr ui8** NULL_ERROR2 = LL_NULLPTR;
	protected:
		//template<HashVersion VERSION, class U, class W = traits::template_types<U>>
		//static void genericPointerTemplateHash(ll_char_t*& mem, HashV1Status*& errors, W::cinput object) __LL_EXCEPT__;
		//// This function does not accepts pointers!
		//template<class U, class W = traits::template_types<U>>
		//static void genericPointerTemplateHash<HashVersion::V1, U, W>(ll_char_t*& buffer, HashV1Status*& errors, W::cinput object) __LL_EXCEPT__;


};

__LL_TEMPLATE_HAS_FUNCTION_BASE__(convert_to_chars, p->convertToChars(hash_cluster::NULL_CHAR_CONVERTIBLE, hash_cluster::NULL_ERROR, ZERO_UI64), LL_FALSE);
__LL_TEMPLATE_HAS_FUNCTION_BASE__(convert_to_chars2, p->convertToChars2(hash_cluster::NULL_CHAR_CONVERTIBLE, hash_cluster::NULL_ERROR2, ZERO_UI64), LL_FALSE);

#pragma region Protected
//template<hash_cluster::HashVersion VERSION, class U, class W>
//__LL_INLINE__ void hash_cluster::genericPointerTemplateHash(ll_char_t*& mem, HashV1Status*& error, W::cinput object) __LL_EXCEPT__ {
//	*error++ = LL_TRUE;
//}
//// This function does not accepts pointers!
//template<class U, class W>
//__LL_INLINE__ void hash_cluster::genericPointerTemplateHash<hash_cluster::HashVersion::V1, U, W>(ll_char_t*& buffer, HashV1Status*& error, W::cinput object) {
//	if constexpr (traits::is_pointer_v<U>) {
//		*error++ = LL_TRUE;
//		mem += sizeof(U);
//	}
//	else if constexpr (traits::is_basic_type_v<U>)
//		BasicTypeWrapper<U>::convertToChars(&buffer, &error, sizeof(U), object);
//	else if constexpr (std::is_same_v<U, meta::Hash>)
//		BasicTypeWrapper<decltype(object.value)>::convertToChars(&buffer, &error, sizeof(U), object.value);
//	else if constexpr (algorithm::has_convert_to_chars_v<U>) {
//		object.convertToChars(buffer);
//	}
//	else {
//
//	}
//}

#pragma endregion
#pragma region Public

#pragma endregion



/*struct has_cluster {

	protected:



		template<class T>
		static constexpr void hash(ll_char_t*& mem, ll_bool_t*& err, const T& object) __LL_EXCEPT__ {
			if constexpr (traits::is_pointer_v<T>) {

			}
				*err++ = LL_TRUE;
			else if constexpr (traits::is_basic_type_v<T>) {
				ll_string_t data = reinterpret_cast<ll_string_t>(&object);
				ll_string_t end = data + sizeof(T);
				for (; data < end; ++data, ++mem) *mem = *data;
				*err++ = LL_FALSE;
			}
			else if constexpr (std::is_same_v<T, Hash>)
				getHashes(mem, err, object.value);
			else if constexpr (traits::has_type_operator_v<T, meta::Hash>)
				getHashes(mem, err, object.operator meta::Hash());
			else getHashes(mem, err, meta::city::CityHash64<T>(object));
		}

	public:
		template<class U, HashVersion VERSION = HashVersion::V1, class W = traits::template_types<U>>
		__LL_NODISCARD__ static constexpr Hash hash(W::cinput object) {
			if constexpr (std::is_pointer_v<typename W::type>) {
				using __noptr = std::remove_pointer_t<typename W::type>;
				return has_cluster::hash<__noptr, VERSION>(*object);
			}
			else if constexpr (std::is_same_v<typename W::type, meta::Hash>)
				return object;
			else if constexpr (VERSION == HashVersion::V1) {
				if constexpr (traits::has_convert_to_chars_v<typename W::type> || traits::is_basic_type_v<typename W::type>) {
					constexpr len_t BUFFERLEN = sizeof(typename W::type);
					ll_char_t buffer[BUFFERLEN]{};

					if constexpr (traits::is_basic_type_v<typename W::type>)
						has_cluster::convertToChars<typename W::type>(buffer, object);
					else object.convertToChars(buffer);

					return meta::city::CityHash::cityHash64(buffer, BUFFERLEN);
				}
			}
			else if constexpr (VERSION == HashVersion::V2) {
				if constexpr (traits::has_type_operator_v<typename W::type, meta::Hash>)
					return object.operator meta::Hash();
				else if constexpr (traits::is_basic_type_v<typename W::type>)
					return has_cluster::hash<U, HashVersion::V1, W>(object);
			}
			return meta::Hash();
		}
		template<class T, len_t N, HashVersion VERSION = HashVersion::V1>
		__LL_NODISCARD__ static constexpr Hash hash(const T* arr) {
			if constexpr (VERSION == HashVersion::V1) {
				using U = std::conditional_t<std::is_pointer_v<T>, std::remove_pointer_t<T>, T>;
				auto generic_hash = [](const U& arr, ll_char_t* buffer) -> void {
					if constexpr (traits::is_basic_type_v<U>)
						has_cluster::convertToChars<U>(buffer, arr);
					else if constexpr (std::is_same_v<U, meta::Hash>)
						has_cluster::convertToChars<decltype(arr.value)>(buffer, arr.value);
					else arr.convertToChars(buffer);
				};

				if constexpr (std::is_pointer_v<T>) {
					using __noptr = std::remove_pointer_t<T>;
					if constexpr (!traits::has_convert_to_chars_v<T> && !traits::is_basic_type_v<T> && !std::is_same_v<T, meta::Hash>)
						return meta::Hash();

					constexpr len_t BUFFERLEN = sizeof(__noptr) * N;
					ll_char_t buffer[BUFFERLEN]{};

					ll_char_t* i = buffer;
					for (const T* data_end = arr + N; arr < data_end; ++arr, i += sizeof(__noptr))
						generic_hash(**arr, buffer);

					return meta::city::CityHash::cityHash64(buffer, BUFFERLEN);
				}
				else if constexpr (traits::has_convert_to_chars_v<T> || traits::is_basic_type_v<T> || std::is_same_v<T, meta::Hash>) {
					constexpr len_t BUFFERLEN = sizeof(T) * N;
					ll_char_t buffer[BUFFERLEN]{};

					ll_char_t* i = buffer;
					for (const T* data_end = arr + N; arr < data_end; ++arr, i += sizeof(T))
						generic_hash(*arr, buffer);

					return meta::city::CityHash::cityHash64(buffer, BUFFERLEN);
				}
			}
			else if constexpr (VERSION == HashVersion::V2) {

			}
			return meta::Hash();
		}
		template<class T, len_t N>
		__LL_NODISCARD__ static constexpr Hash hash(const T(&arr)[N]) {
			const T* ptr = arr;
			return has_cluster::hash<T, N>(ptr);
			// This is the same
			///return has_cluster::hash<T, N>(&*arr);
		}
		template<class T, len_t N>
		__LL_NODISCARD__ static constexpr Hash hash(const ArrayPair<T>& arr) {
			return has_cluster::hash<T, N>(arr.begin());
		}

	public:
		__LL_NODISCARD__ static constexpr Hash hash(ll_char_t object) {
			return meta::city::CityHash::cityHash64(&object, 1);
		}
		__LL_NODISCARD__ static constexpr Hash hash(ll_string_t arr, const len_t size) {
			if (!arr || size == ZERO_UI64) return meta::Hash();
			else return meta::city::CityHash::cityHash64(arr, size);
		}
		template<len_t N>
		__LL_NODISCARD__ static constexpr Hash hash(const ll_char_t(&arr)[N]) {
			if (!arr || N == ZERO_UI64) return meta::Hash();
			else return meta::city::CityHash::cityHash64(arr, N);
		}
		__LL_NODISCARD__ static constexpr Hash hash(const ArrayPair<ll_char_t>& arr) {
			if (arr.empty()) return meta::Hash();
			else return meta::city::CityHash::cityHash64(arr.begin(), arr.size());
		}
	public:
		template<class... Args, len_t NUM_ARGS = sizeof...(Args)>
		__LL_NODISCARD__ static constexpr Hash hash(ll_bool_t(&err)[NUM_ARGS], const Args&... args) {
			using pack = traits::parameter_pack_operations<Args...>;
			if constexpr (pack::size == 1ull)
				return has_cluster::hash<Args>(args);
			if constexpr (!pack::empty) {
				ll_char_t buffer[pack::sizeof_hash_version]{};



			}
			else return meta::Hash();
		}
};*/


#pragma endregion





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
