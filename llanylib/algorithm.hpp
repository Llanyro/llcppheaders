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

#include "ArrayPair.hpp"
#include "common.hpp"
#include "math.hpp"

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
template<class T, class U, class result_t, result_t _NULL_RESULT_>
class CompareData {
	// Assersts
	public:
		static_assert(traits::is_basic_type_v<result_t>, "Result type must be a basic type!");

	// Class types
	public:
		using __t = traits::template_types<T>;
		using __u = traits::template_types<U>;
		using __CompareData = traits::template_types<CompareData<T, U, result_t, _NULL_RESULT_>>;
		static constexpr result_t NULL_RESULT = _NULL_RESULT_;

	// Other internal objects
	public:
		template<class result_type, result_type NULL_RESULT2>
		using __CompareDataOtherResult = traits::template_types<CompareData<T, U, result_type, NULL_RESULT2>>;

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
		constexpr CompareData() __LL_EXCEPT__ : CompareData(NULL_RESULT) {}
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
using CompareConditional = std::conditional_t<GET_DATA, algorithm::CompareData<T, U, result_t, NULL_RESULT>, result_t>;
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
	using __ArrayPair_t = meta::ArrayPair<typename __t::type>;
	using __ArrayPair_u = meta::ArrayPair<typename __u::type>;
	using __Array_t = meta::Array<typename __t::type>;
	using __Array_u = meta::Array<typename __u::type>;

	#pragma region Compare
	__LL_NODISCARD__ static constexpr CompareResult compare(__t::cptr str1, __u::cptr str2, len_t size, CompareFunc cmp) __LL_EXCEPT__ {
		if (static_cast<const void*>(str1) == static_cast<const void*>(str2)) {
			if constexpr (GET_DATA) return CompareResult(ZERO_I32);
			else return ZERO_I32;
		}
		else if (!str1) {
			if constexpr (GET_DATA) return CompareResult(-1);
			else return -1;
		}
		else if(!str2){
			if constexpr (GET_DATA) return CompareResult(1);
			else return 1;
		}

		__LL_ASSERT_VAR_NULL__(cmp, "cmp");

		typename __t::cptr begin = str1;
		for (; size > ZERO_UI64; --size, ++str1, ++str2) {
			cmp_t result = cmp(*str1, *str2);
			if (result != ZERO_I32) {
				if constexpr (GET_DATA)
					return CompareResult(str1, str2, result);
				else return result;
			}
		}
		if constexpr (GET_DATA) return CompareResult(ZERO_I32);
		else return ZERO_I32;
	}
	__LL_NODISCARD__ static constexpr CompareResult compare(__t::cptr str1, __u::cptr str2, len_t size) __LL_EXCEPT__ {
		return __cmp::compare(str1, str2, size, common::compare_with_operators<__t::cinput, __u::cinput>);
	}

	#pragma region Equals
	#pragma region Ptr
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr str1, const len_t size1, __u::cptr str2, const len_t size2, CompareFunc cmp) __LL_EXCEPT__ {
		if (size1 != size2) {
			if constexpr (GET_DATA)
				return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}
		CompareResult res = __cmp::compare(str1, str2, size1, cmp);
		if constexpr (GET_DATA)
			return CompareResultBool(res.getValue1(), res.getValue2(), res.getResult() == ZERO_I32);
		else return res == ZERO_I32;
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr str1, const len_t size1, __u::cptr str2, const len_t size2) __LL_EXCEPT__ {
		if (size1 != size2) {
			if constexpr (GET_DATA)
				return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}
		CompareResult res = __cmp::compare(str1, str2, size1);
		if constexpr (GET_DATA)
			return CompareResultBool(res.getValue1(), res.getValue2(), res.getResult() == ZERO_I32);
		else return res == ZERO_I32;
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr str1, const len_t size1, const __ArrayPair_u& str2, CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1, size1, str2.begin(), str2.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr str1, const len_t size1, const __ArrayPair_u& str2) __LL_EXCEPT__ {
		return __cmp::equals(str1, size1, str2.begin(), str2.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr str1, const len_t size1, const __Array_u& str2, CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1, size1, str2.begin(), str2.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::cptr str1, const len_t size1, const __Array_u& str2) __LL_EXCEPT__ {
		return __cmp::equals(str1, size1, str2.begin(), str2.size());
	}

	#pragma endregion
	#pragma region DefaultArray
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&str1)[N], __u::cptr str2, const len_t size2, CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1, N, str2, size2, cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&str1)[N], __u::cptr str2, const len_t size2) __LL_EXCEPT__ {
		return __cmp::equals(str1, N, str2, size2);
	}
	template<len_t N, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&str1)[N], __u::ctype(&str2)[N2], CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1, N, str2, N2, cmp);
	}
	template<len_t N, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&str1)[N], __u::ctype(&str2)[N2]) __LL_EXCEPT__ {
		return __cmp::equals(str1, N, str2, N2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&str1)[N], const __ArrayPair_u& str2, CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1, N, str2.begin(), str2.size(), cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&str1)[N], const __ArrayPair_u& str2) __LL_EXCEPT__ {
		return __cmp::equals(str1, N, str2.begin(), str2.size());
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&str1)[N], const __Array_u& str2, CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1, N, str2.begin(), str2.size(), cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(__t::ctype(&str1)[N], const __Array_u& str2) __LL_EXCEPT__ {
		return __cmp::equals(str1, N, str2.begin(), str2.size());
	}

	#pragma endregion
	#pragma region ArrayPair
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& str1, __u::cptr str2, const len_t size2, CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2, size2, cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& str1, __u::cptr str2, const len_t size2) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& str1, __u::ctype(&str2)[N], CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2, N, cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& str1, __u::ctype(&str2)[N]) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& str1, const __ArrayPair_u& str2, CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2.begin(), str2.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& str1, const __ArrayPair_u& str2) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& str1, const __Array_u& str2, CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2.begin(), str2.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& str1, const __Array_u& str2) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}

	#pragma endregion
	#pragma region Array
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __Array_t& str1, __u::cptr str2, const len_t size2, CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2, size2, cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __Array_t& str1, __u::cptr str2, const len_t size2) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __Array_t& str1, __u::ctype(&str2)[N], CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2, N, cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __Array_t& str1, __u::ctype(&str2)[N]) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __Array_t& str1, const __ArrayPair_u& str2, CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2.begin(), str2.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __Array_t& str1, const __ArrayPair_u& str2) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __Array_t& str1, const __Array_u& str2, CompareFunc cmp) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2.begin(), str2.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __Array_t& str1, const __Array_u& str2) __LL_EXCEPT__ {
		return __cmp::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}

	#pragma endregion

	#pragma endregion
	#pragma endregion
	#pragma region StartsWith
	// str size needs to be bigger or equal to needle
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with_impl(__t::cptr str, __u::cptr needle, len_t size, CompareFuncBool cmp) {
		if (static_cast<const void*>(str) == static_cast<const void*>(needle)) {
			if constexpr (GET_DATA) return CompareResultBool(LL_TRUE);
			else return LL_TRUE;
		}
		else if (!str || !needle) {
			if constexpr (GET_DATA) return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}

		__LL_ASSERT_VAR_NULL__(cmp, "cmp");

		for (; 0 < size; --size, ++str, ++needle) {
			ll_bool_t result = cmp(*str, *needle);
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

	#pragma region Ptr
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::cptr str, const len_t size1, __u::cptr needle, const len_t size2, CompareFuncBool cmp) {
		if (size1 < size2 || (size1 != size2 && size2 == ZERO_UI64)) {
			if constexpr (GET_DATA)
				return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}
		else return __cmp::starts_with_impl(str, needle, size2, cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::cptr str, const len_t size1, __u::cptr needle, const len_t size2) {
		return __cmp::starts_with(str, size1, needle, size2, common::simple_equals<__t::cinput, __u::cinput>);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::cptr str, const len_t size1, __u::ctype(&needle)[N], CompareFuncBool cmp) {
		return __cmp::starts_with(str, size1, needle, N, cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::cptr str, const len_t size1, __u::ctype(&needle)[N]) {
		return __cmp::starts_with(str, size1, needle, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::cptr str, const len_t size1, const __ArrayPair_u& needle, CompareFuncBool cmp) {
		return __cmp::starts_with(str, size1, needle.begin(), needle.len(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::cptr str, const len_t size1, const __ArrayPair_u& needle) {
		return __cmp::starts_with(str, size1, needle.begin(), needle.len());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::cptr str, const len_t size1, const __Array_u& needle, CompareFuncBool cmp) {
		return __cmp::starts_with(str, size1, needle.begin(), needle.len(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::cptr str, const len_t size1, const __Array_u& needle) {
		return __cmp::starts_with(str, size1, needle.begin(), needle.len());
	}

	#pragma endregion
	#pragma region DefaultArray
	template<len_t N, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::ctype(&str)[N], __u::ctype(&needle)[N2], CompareFuncBool cmp) {
		return __cmp::starts_with(str, N, needle, N2, cmp);
	}
	template<len_t N, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::ctype(&str)[N], __u::ctype(&needle)[N2]) {
		return __cmp::starts_with(str, N, needle, N2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::ctype(&str)[N], __u::cptr needle, const len_t size2, CompareFuncBool cmp) {
		return __cmp::starts_with(str, N, needle, size2, cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::ctype(&str)[N], __u::cptr needle, const len_t size2) {
		return __cmp::starts_with(str, N, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::ctype(&str)[N], const __ArrayPair_u& needle, CompareFuncBool cmp) {
		return __cmp::starts_with(str, N, needle.begin(), needle.len(), cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::ctype(&str)[N], const __ArrayPair_u& needle) {
		return __cmp::starts_with(str, N, needle.begin(), needle.len());
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::ctype(&str)[N], const __Array_u& needle, CompareFuncBool cmp) {
		return __cmp::starts_with(str, N, needle.begin(), needle.len(), cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(__t::ctype(&str)[N], const __Array_u& needle) {
		return __cmp::starts_with(str, N, needle.begin(), needle.len());
	}

	#pragma endregion
	#pragma region ArrayPair
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& str, __u::cptr needle, len_t size, CompareFuncBool cmp) {
		return __cmp::starts_with(str.begin(), str.size(), needle, size, cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& str, __u::cptr needle, len_t size) {
		return __cmp::starts_with(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& str, __u::ctype(&needle)[N], CompareFuncBool cmp) {
		return __cmp::starts_with(str.begin(), str.size(), needle, needle.size(), cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& str, __u::ctype(&needle)[N]) {
		return __cmp::starts_with(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& str, const __ArrayPair_u& needle, CompareFuncBool cmp) {
		return __cmp::starts_with(str.begin(), str.size(), needle.begin(), needle.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& str, const __ArrayPair_u& needle) {
		return __cmp::starts_with(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& str, const __Array_u& needle, CompareFuncBool cmp) {
		return __cmp::starts_with(str.begin(), str.size(), needle.begin(), needle.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& str, const __Array_u& needle) {
		return __cmp::starts_with(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion
	#pragma region Array
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __Array_t& str, __u::cptr needle, len_t size, CompareFuncBool cmp) {
		return __cmp::starts_with(str.begin(), str.size(), needle, size, cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __Array_t& str, __u::cptr needle, len_t size) {
		return __cmp::starts_with(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __Array_t& str, __u::ctype(&needle)[N], CompareFuncBool cmp) {
		return __cmp::starts_with(str.begin(), str.size(), needle, N, cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __Array_t& str, __u::ctype(&needle)[N]) {
		return __cmp::starts_with(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __Array_t& str, const __ArrayPair_u& needle, CompareFuncBool cmp) {
		return __cmp::starts_with(str.begin(), str.size(), needle.begin(), needle.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __Array_t& str, const __ArrayPair_u& needle) {
		return __cmp::starts_with(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __Array_t& str, const __Array_u& needle, CompareFuncBool cmp) {
		return __cmp::starts_with(str.begin(), str.size(), needle.begin(), needle.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __Array_t& str, const __Array_u& needle) {
		return __cmp::starts_with(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion

	#pragma endregion
	#pragma region EndsWith
	#pragma region Ptr
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::cptr str, const len_t size1, __u::cptr needle, const len_t size2, CompareFuncBool cmp) {
		if (size1 < size2 || (size1 != size2 && size2 == ZERO_UI64)) {
			if constexpr (GET_DATA)
				return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}
		else return __cmp::starts_with_impl((str + size1) - size2, needle, size2, cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::cptr str, const len_t size1, __u::cptr needle, const len_t size2) {
		return __cmp::ends_with(str, size1, needle, size2, common::simple_equals<__t::cinput, __u::cinput>);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::cptr str, const len_t size1, __u::ctype(&needle)[N], CompareFuncBool cmp) {
		return __cmp::ends_with(str, size1, needle, N, cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::cptr str, const len_t size1, __u::ctype(&needle)[N]) {
		return __cmp::ends_with(str, size1, needle, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::cptr str, const len_t size1, const __ArrayPair_u& needle, CompareFuncBool cmp) {
		return __cmp::ends_with(str, size1, needle.begin(), needle.len(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::cptr str, const len_t size1, const __ArrayPair_u& needle) {
		return __cmp::ends_with(str, size1, needle.begin(), needle.len());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::cptr str, const len_t size1, const __Array_u& needle, CompareFuncBool cmp) {
		return __cmp::ends_with(str, size1, needle.begin(), needle.len(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::cptr str, const len_t size1, const __Array_u& needle) {
		return __cmp::ends_with(str, size1, needle.begin(), needle.len());
	}

	#pragma endregion
	#pragma region DefaultArray
	template<len_t N, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::ctype(&str)[N], __u::ctype(&needle)[N2], CompareFuncBool cmp) {
		return __cmp::ends_with(str, N, needle, N2, cmp);
	}
	template<len_t N, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::ctype(&str)[N], __u::ctype(&needle)[N2]) {
		return __cmp::ends_with(str, N, needle, N2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::ctype(&str)[N], __u::cptr needle, const len_t size2, CompareFuncBool cmp) {
		return __cmp::ends_with(str, N, needle, size2, cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::ctype(&str)[N], __u::cptr needle, const len_t size2) {
		return __cmp::ends_with(str, N, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::ctype(&str)[N], const __ArrayPair_u& needle, CompareFuncBool cmp) {
		return __cmp::ends_with(str, N, needle.begin(), needle.len(), cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::ctype(&str)[N], const __ArrayPair_u& needle) {
		return __cmp::ends_with(str, N, needle.begin(), needle.len());
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::ctype(&str)[N], const __Array_u& needle, CompareFuncBool cmp) {
		return __cmp::ends_with(str, N, needle.begin(), needle.len(), cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(__t::ctype(&str)[N], const __Array_u& needle) {
		return __cmp::ends_with(str, N, needle.begin(), needle.len());
	}

	#pragma endregion
	#pragma region ArrayPair
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& str, __u::cptr needle, len_t size, CompareFuncBool cmp) {
		return __cmp::ends_with(str.begin(), str.size(), needle, size, cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& str, __u::cptr needle, len_t size) {
		return __cmp::ends_with(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& str, __u::ctype(&needle)[N], CompareFuncBool cmp) {
		return __cmp::ends_with(str.begin(), str.size(), needle, needle.size(), cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& str, __u::ctype(&needle)[N]) {
		return __cmp::ends_with(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& str, const __ArrayPair_u& needle, CompareFuncBool cmp) {
		return __cmp::ends_with(str.begin(), str.size(), needle.begin(), needle.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& str, const __ArrayPair_u& needle) {
		return __cmp::ends_with(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& str, const __Array_u& needle, CompareFuncBool cmp) {
		return __cmp::ends_with(str.begin(), str.size(), needle.begin(), needle.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& str, const __Array_u& needle) {
		return __cmp::ends_with(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion
	#pragma region Array
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __Array_t& str, __u::cptr needle, len_t size, CompareFuncBool cmp) {
		return __cmp::ends_with(str.begin(), str.size(), needle, size, cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __Array_t& str, __u::cptr needle, len_t size) {
		return __cmp::ends_with(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __Array_t& str, __u::ctype(&needle)[N], CompareFuncBool cmp) {
		return __cmp::ends_with(str.begin(), str.size(), needle, N, cmp);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __Array_t& str, __u::ctype(&needle)[N]) {
		return __cmp::ends_with(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __Array_t& str, const __ArrayPair_u& needle, CompareFuncBool cmp) {
		return __cmp::ends_with(str.begin(), str.size(), needle.begin(), needle.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __Array_t& str, const __ArrayPair_u& needle) {
		return __cmp::ends_with(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __Array_t& str, const __Array_u& needle, CompareFuncBool cmp) {
		return __cmp::ends_with(str.begin(), str.size(), needle.begin(), needle.size(), cmp);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __Array_t& str, const __Array_u& needle) {
		return __cmp::ends_with(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion

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
	using __ArrayPair_t = meta::ArrayPair<typename __t::type>;
	using __Array_t = meta::Array<typename __t::type>;

	#pragma region Find
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult find(__t::cptr begin, __t::cptr end, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin || !cmp) {
			if constexpr (POSITION) return npos;
			else return end;
			//throw "Find error values";
		}

		for (typename __t::cptr data = begin; data < end; ++data)
			if (cmp(*data, object)) {
				if constexpr (POSITION) return data - begin;
				else return data;
			}
		if constexpr (POSITION) return npos;
		else return end;
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult find(__t::cptr begin, __t::cptr end, typename W::cinput object) __LL_EXCEPT__ {
		return __find::find<U, W>(begin, end, object, common::simple_equals<typename __t::cinput, U>);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult find(__t::ctype(&data)[N], typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::find<U, W>(data, data + N, object, cmp);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult find(__t::ctype (&data)[N], typename W::cinput object) __LL_EXCEPT__ {
		return __find::find<U, W>(data, data + N, object);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult find(const __ArrayPair_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::find<U, W>(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult find(const __ArrayPair_t& arr, typename W::cinput object) __LL_EXCEPT__ {
		return __find::find<U, W>(arr.begin(), arr.end(), object);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult find(const __Array_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::find<U, W>(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult find(const __Array_t& arr, typename W::cinput object) __LL_EXCEPT__ {
		return __find::find<U, W>(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region rFind
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult rfind(__t::cptr begin, __t::cptr end, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin || !cmp) {
			if constexpr (POSITION) return npos;
			else return end;
		}

		for (typename __t::cptr data = end - 1; data > begin; --data)
			if (cmp(*data, object)) {
				if constexpr (POSITION) return data - begin;
				else return data;
			}

		if constexpr (POSITION) return cmp(*begin, object) ? 0 : npos;
		else return cmp(*begin, object) ? begin : end;
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult rfind(__t::cptr begin, __t::cptr end, typename W::cinput object) __LL_EXCEPT__ {
		return __find::rfind<U, W>(begin, end, object, common::simple_equals<typename __t::cinput, U>);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult rfind(__t::ctype (&data)[N], typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::rfind<U, W>(data, data + N, object, cmp);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult rfind(__t::ctype (&data)[N], typename W::cinput object) __LL_EXCEPT__ {
		return __find::rfind<U, W>(data, data + N, object);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult rfind(const __ArrayPair_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::rfind<U, W>(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult rfind(const __ArrayPair_t& arr, typename W::cinput object) __LL_EXCEPT__ {
		return __find::rfind<U, W>(arr.begin(), arr.end(), object);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult rfind(const __Array_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::rfind<U, W>(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr FindResult rfind(const __Array_t& arr, typename W::cinput object) __LL_EXCEPT__ {
		return __find::rfind<U, W>(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Contains
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(__t::cptr begin, __t::cptr end, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		if constexpr (POSITION) return __find::find<U, W>(begin, end, object, cmp) != npos;
		else return __find::find<U, W>(begin, end, object, cmp) != end;
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(__t::cptr begin, __t::cptr end, typename W::cinput object) __LL_EXCEPT__ {
		if constexpr (POSITION) return __find::find<U, W>(begin, end, object) != npos;
		else return __find::find<U, W>(begin, end, object) != end;
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(__t::ctype(&data)[N], typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::contains<U, W>(data, data + N, object, cmp);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(__t::ctype(&data)[N], typename W::cinput object) __LL_EXCEPT__ {
		return __find::contains<U, W>(data, data + N, object);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(const __ArrayPair_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::contains<U, W>(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(const __ArrayPair_t& arr, typename W::cinput object) __LL_EXCEPT__ {
		return __find::contains<U, W>(arr.begin(), arr.end(), object);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(const __Array_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::contains<U, W>(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(const __Array_t& arr, typename W::cinput object) __LL_EXCEPT__ {
		return __find::contains<U, W>(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Other
	#pragma region All
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::cptr begin, __t::cptr end, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		if (!begin || !end || end <= begin) return LL_FALSE;

		__LL_ASSERT_VAR_NULL__(cmp, "cmp");

		for (; begin < end; ++begin)
			if (!cmp(*begin, object))
				return LL_FALSE;
		return LL_TRUE;
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::cptr begin, __t::cptr end, typename W::cinput object) __LL_EXCEPT__ {
		return __find::all<U, W>(begin, end, object, common::simple_equals<typename __t::cinput, U>);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::ctype (&data)[N], typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::all<U, W>(data, data + N, object, cmp);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t all(__t::ctype (&data)[N], typename W::cinput object) __LL_EXCEPT__ {
		return __find::all<U, W>(data, data + N, object);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t all(const __ArrayPair_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::all<U, W>(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t all(const __ArrayPair_t& arr, typename W::cinput object) __LL_EXCEPT__ {
		return __find::all<U, W>(arr.begin(), arr.end(), object);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t all(const __Array_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::all<U, W>(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t all(const __Array_t& arr, typename W::cinput object) __LL_EXCEPT__ {
		return __find::all<U, W>(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Any
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::cptr begin, __t::cptr end, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return static_cast<ll_bool_t>(__find::find<U, W>(begin, end, object, cmp));
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::cptr begin, __t::cptr end, typename W::cinput object) __LL_EXCEPT__ {
		return static_cast<ll_bool_t>(__find::find<U, W>(begin, end, object));
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::ctype (&data)[N], typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::any<U, W>(data, data + N, object, cmp);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t any(__t::ctype (&data)[N], typename W::cinput object) __LL_EXCEPT__ {
		return __find::any<U, W>(data, data + N, object);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t any(const __ArrayPair_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::any<U, W>(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t any(const __ArrayPair_t& arr, typename W::cinput object) __LL_EXCEPT__ {
		return __find::any<U, W>(arr.begin(), arr.end(), object);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t any(const __Array_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::any<U, W>(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t any(const __Array_t& arr, typename W::cinput object) __LL_EXCEPT__ {
		return __find::any<U, W>(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region None
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::cptr begin, __t::cptr end, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return !static_cast<ll_bool_t>(__find::find<U, W>(begin, end, object, cmp));
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::cptr begin, __t::cptr end, typename W::cinput object) __LL_EXCEPT__ {
		return !static_cast<ll_bool_t>(__find::find<U, W>(begin, end, object));
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::ctype (&data)[N], typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::none<U, W>(data, data + N, object, cmp);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t none(__t::ctype (&data)[N], typename W::cinput object) __LL_EXCEPT__ {
		return __find::none<U, W>(data, data + N, object);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t none(const __ArrayPair_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::none<U, W>(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t none(const __ArrayPair_t& arr, typename W::cinput object) __LL_EXCEPT__ {
		return __find::none<U, W>(arr.begin(), arr.end(), object);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t none(const __Array_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::none<U, W>(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr ll_bool_t none(const __Array_t& arr, typename W::cinput object) __LL_EXCEPT__ {
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
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(__t::cptr begin, __t::cptr end, typename W::cinput object) {
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
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(__t::cptr begin, __t::cptr end, typename W::cinput object, CompareFunc<typename W::cinput> cmp) {
		__LL_ASSERT_VAR_NULL__(cmp, "cmp");

		len_t low = ZERO_UI64;
		len_t high = end - begin;
		while (low <= high) {
			len_t mid = ((high - low) >> 1);
			cmp_t res = cmp(begin[mid], object);
			if (res == ZERO_I32) return begin + mid;
			else if (res > 0) high = mid;
			else low = mid + 1;
		}
		return end;
	}

	#pragma region Proxy
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(__t::cptr begin, __t::cptr end, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		typename __t::cptr pos = __find::binarysearch(begin, end, object, cmp);
		return (pos != end) ? pos - begin : npos;
	}
	template<class U, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(__t::cptr begin, __t::cptr end, typename W::cinput object) __LL_EXCEPT__ {
		typename __t::cptr pos = __find::binarysearch(begin, end, object);
		return (pos != end) ? pos - begin : npos;
	}

	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(__t::ctype (&data)[N], typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !cmp) return data + N;
		return __find::binarysearch(data, data + N, object, cmp);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(__t::ctype (&data)[N], typename W::cinput object) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) return data + N;
		return __find::binarysearch(data, data + N, object);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(__t::ctype (&data)[N], typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64 || !cmp) return data + N;
		return __find::binarysearch_pos(data, data + N, object, cmp);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(__t::ctype (&data)[N], typename W::cinput object) __LL_EXCEPT__ {
		if (!data || N == ZERO_UI64) return data + N;
		return __find::binarysearch_pos(data, data + N, object);
	}

	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(const __ArrayPair_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::binarysearch(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr __t::cptr binarysearch(const __ArrayPair_t& arr, typename W::cinput object) __LL_EXCEPT__ {
		return __find::binarysearch(arr.begin(), arr.end(), object);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(const __ArrayPair_t& arr, typename W::cinput object, CompareFuncBool<typename W::cinput> cmp) __LL_EXCEPT__ {
		return __find::binarysearch_pos(arr.begin(), arr.end(), object, cmp);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	__LL_NODISCARD__ static constexpr len_t binarysearch_pos(const __ArrayPair_t& arr, typename W::cinput object) __LL_EXCEPT__ {
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
	using __Array_t = meta::Array<typename __t::type>;

	#pragma region Reverse
	static constexpr void reverse(__t::ptr arr, __t::ptr end, SwapFunc swap) __LL_EXCEPT__ {
		if (!arr || !end || end <= arr || !swap) return;
		for (; arr < end; ++arr, --end)
			swap(*arr, *end);
	}
	static constexpr void reverse(__t::ptr arr, __t::ptr end) __LL_EXCEPT__ {
		__data::reverse(arr, end, common::simple_swap<typename __t::type>);
	}
	template<len_t N>
	static constexpr void reverse(__t::type(&arr)[N]) __LL_EXCEPT__ {
		__data::reverse(arr, arr + N - 1);
	}
	template<len_t N>
	static constexpr void reverse(__t::type(&arr)[N], SwapFunc swap) __LL_EXCEPT__ {
		__data::reverse(arr, arr + N - 1, swap);
	}
	static constexpr void reverse(__Array_t& arr, SwapFunc swap) __LL_EXCEPT__ {
		__data::reverse(arr.begin(), arr.end(), swap);
	}
	static constexpr void reverse(__Array_t& arr) __LL_EXCEPT__ {
		__data::reverse(arr.begin(), arr.end());
	}

	#pragma endregion
	#pragma region Fillers
	template<class U, class W = traits::template_types<U>>
	static constexpr void fill(__t::ptr dst, __t::ptr end, typename W::cinput object, FillFunc<typename W::cinput> setFunc) {
		if (!dst || !end || end <= dst || !setFunc) return;
		for (; dst <= end; ++dst) setFunc(*dst, object);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void fill(__t::ptr dst, __t::ptr end, typename W::cinput object) {
		__data::fill<U, W>(dst, end, object, common::simple_set<typename __t::type, typename W::cinput>);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	static constexpr void fill(__t::type(&dst)[N], typename W::cinput object, FillFunc<typename W::cinput> setFunc) __LL_EXCEPT__ {
		__data::fill<U, W>(dst, dst + N - 1, object, setFunc);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	static constexpr void fill(__t::type(&dst)[N], typename W::cinput object) __LL_EXCEPT__ {
		__data::fill<U, W>(dst, dst + N - 1, object);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void fill(__Array_t& dst, typename W::cinput object, FillFunc<typename W::cinput> setFunc) __LL_EXCEPT__ {
		__data::fill<U, W>(dst.begin(), dst.end(), object, setFunc);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void fill(__Array_t& dst, typename W::cinput object) __LL_EXCEPT__ {
		__data::fill<U, W>(dst.begin(), dst.end(), object);
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
	template<class U, class W = traits::template_types<U>>
	static constexpr void copy(const meta::ArrayPair<U>& src, __t::ptr dst, const len_t size, FillFunc<typename W::cinput> setFunc) {
		__data::copy<U, W>(src.begin(), dst, math::min<len_t>(src.len(), size), setFunc);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void copy(const meta::ArrayPair<U>& src, __t::ptr dst, const len_t size) {
		__data::copy<U, W>(src.begin(), dst, math::min<len_t>(src.len(), size));
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void copy(const meta::ArrayPair<U>& src, __Array_t& dst, FillFunc<typename W::cinput> setFunc) {
		__data::copy<U, W>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()), setFunc);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void copy(const meta::ArrayPair<U>& src, __Array_t& dst) {
		__data::copy<U, W>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void copy(const meta::Array<U>& src, __Array_t& dst, FillFunc<typename W::cinput> setFunc) {
		__data::copy<U, W>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()), setFunc);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void copy(const meta::Array<U>& src, __Array_t& dst) {
		__data::copy<U, W>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	static constexpr void copy(typename W::ctype(&src)[N], __t::ptr dst, const len_t size, FillFunc<typename W::cinput> setFunc) {
		__data::copy<U, W>(src, dst, math::min<len_t>(N, size), setFunc);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	static constexpr void copy(typename W::ctype(&src)[N], __t::ptr dst, const len_t size) {
		__data::copy<U, W>(src, dst, math::min<len_t>(N, size));
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	static constexpr void copy(typename W::ctype(&src)[N], __Array_t& dst, FillFunc<typename W::cinput> setFunc) {
		__data::copy<U, W>(src, dst.begin(), math::min<len_t>(N, dst.len()), setFunc);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	static constexpr void copy(typename W::ctype(&src)[N], __Array_t& dst) {
		__data::copy<U, W>(src, dst.begin(), math::min<len_t>(N, dst.len()));
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
	template<class U, len_t N, class W = traits::template_types<U>>
	static constexpr void shiftLeft(__t::type(&arr)[N], const len_t first, const len_t num, typename W::cinput null, FillFunc<typename __t::cinput> moveFunc, FillFunc<typename W::cinput> setNullFunc) __LL_EXCEPT__ {
		__data::shiftLeft<U, W>(arr, N, first, num, null, moveFunc, setNullFunc);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	static constexpr void shiftLeft(__t::type(&arr)[N], const len_t first, const len_t num, typename W::cinput null) __LL_EXCEPT__ {
		__data::shiftLeft<U, W>(arr, N, first, num, null);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void shiftLeft(__Array_t& arr, const len_t first, const len_t num, typename W::cinput null, FillFunc<typename __t::cinput> moveFunc, FillFunc<typename W::cinput> setNullFunc) __LL_EXCEPT__ {
		__data::shiftLeft<U, W>(arr.begin(), arr.len(), first, num, null, moveFunc, setNullFunc);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void shiftLeft(__Array_t& arr, const len_t first, const len_t num, typename W::cinput null) __LL_EXCEPT__ {
		__data::shiftLeft<U, W>(arr.begin(), arr.len(), first, num, null);
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
	template<class U, len_t N, class W = traits::template_types<U>>
	static constexpr void shifRight(__t::type(&arr)[N], const len_t first, const len_t num, typename W::cinput null, FillFunc<typename __t::cinput> moveFunc, FillFunc<typename W::cinput> setNullFunc) __LL_EXCEPT__ {
		__data::shifRight<U, W>(arr, N, first, num, null, moveFunc, setNullFunc);
	}
	template<class U, len_t N, class W = traits::template_types<U>>
	static constexpr void shifRight(__t::type(&arr)[N], const len_t first, const len_t num, typename W::cinput null) __LL_EXCEPT__ {
		__data::shifRight<U, W>(arr, N, first, num, null);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void shifRight(__Array_t& arr, const len_t first, const len_t num, typename W::cinput null, FillFunc<typename __t::cinput> moveFunc, FillFunc<typename W::cinput> setNullFunc) __LL_EXCEPT__ {
		__data::shifRight<U, W>(arr.begin(), arr.len(), first, num, null, moveFunc, setNullFunc);
	}
	template<class U, class W = traits::template_types<U>>
	static constexpr void shifRight(__Array_t& arr, const len_t first, const len_t num, typename W::cinput null) __LL_EXCEPT__ {
		__data::shifRight<U, W>(arr.begin(), arr.len(), first, num, null);
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
