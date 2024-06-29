//////////////////////////////////////////////
//	algorithm.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ALGORITHM_HPP_) // Guard && version protector
	#if LLANYLIB_ALGORITHM_MAYOR_ != 8 || LLANYLIB_ALGORITHM_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "algorithm.hpp version error!"
		#else
			#error "algorithm.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ALGORITHM_MAYOR_ || LLANYLIB_ALGORITHM_MINOR_

#else !defined(LLANYLIB_ALGORITHM_HPP_)
#define LLANYLIB_ALGORITHM_HPP_
#define LLANYLIB_ALGORITHM_MAYOR_ 8
#define LLANYLIB_ALGORITHM_MINOR_ 0

#include "ArrayPair.hpp"
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
		static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<T>, "Const type is forbidden!");

	// Class types
	public:
		static constexpr result_t NULL_RESULT = _NULL_RESULT_;

	protected:
		const T* value1;	// Value 1 of the result given
		const U* value2;	// Value 2 of the result given
		result_t result;	// Result of comparation
	protected:
		constexpr void simpleClear(const result_t& result = NULL_RESULT) noexcept {
			this->result = result;
			this->value1 = LL_NULLPTR;
			this->value2 = LL_NULLPTR;
		}
		constexpr void simpleClear(result_t&& result) noexcept {
			this->result = std::move(result);
			this->value1 = LL_NULLPTR;
			this->value2 = LL_NULLPTR;
		}
	public:
		#pragma region Contructor
		constexpr CompareData() noexcept : CompareData(NULL_RESULT) {}
		constexpr ~CompareData() noexcept {}

		constexpr CompareData(const T* value1, const U* value2, const result_t& result) noexcept
			: value1(value1), value2(value2), result(result) {}
		constexpr CompareData(const T* value1, const U* value2, result_t&& result) noexcept
			: value1(value1), value2(value2), result(std::move(result)) {}

		constexpr CompareData(const result_t& result) noexcept
			: CompareData(LL_NULLPTR, LL_NULLPTR, result) {}
		constexpr CompareData& operator=(const result_t& result) noexcept {
			this->simpleClear();
			this->result = result;
			return *this;
		}
		constexpr CompareData(result_t&& result) noexcept
			: CompareData(LL_NULLPTR, LL_NULLPTR, std::move(result)) {}
		constexpr CompareData& operator=(result_t&& result) noexcept {
			this->simpleClear();
			this->result = std::move(result);
			return *this;
		}

		#pragma endregion
		#pragma region CopyMove
		constexpr CompareData(const CompareData& other) noexcept
			: value1(other.value1), value2(other.value2), result(other.result) {}
		constexpr CompareData& operator=(const CompareData& other) noexcept {
			this->value1 = other.value1;
			this->value2 = other.value2;
			this->result = other.result;
			return *this;
		}

		constexpr CompareData(CompareData&& other) noexcept
			: value1(other.value1), value2(other.value2), result(other.result)
		{
			other.simpleClear();
		}
		constexpr CompareData& operator=(CompareData&& other) noexcept {
			this->value1 = other.value1;
			this->value2 = other.value2;
			this->result = other.result;
			other.simpleClear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ operator const CompareData*() const noexcept = delete;
		__LL_NODISCARD__ operator CompareData*() noexcept = delete;

		#pragma endregion

		__LL_NODISCARD__ constexpr const T* getValue1() const noexcept { return this->value1; }
		__LL_NODISCARD__ constexpr const U* getValue2() const noexcept { return this->value2; }
		__LL_NODISCARD__ constexpr result_t getResult() const noexcept { return this->result; }
		__LL_NODISCARD__ constexpr void clear() noexcept { this->simpleClear(); }
};

template<class T, class U, class result_t, result_t NULL_RESULT, ll_bool_t GET_DATA>
using CompareConditional = std::conditional_t<GET_DATA, algorithm::CompareData<T, U, result_t, NULL_RESULT>, result_t>;
template<class T, class U, ll_bool_t GET_DATA>
using CompareConditionalCmpT = CompareConditional<T, U, cmp_t, ZERO_CMP, GET_DATA>;
template<class T, class U, ll_bool_t GET_DATA>
using CompareConditionalBool = CompareConditional<T, U, ll_bool_t, LL_FALSE, GET_DATA>;

template<class T, class U = T, ll_bool_t GET_DATA = LL_FALSE>
__LL_NODISCARD__ constexpr CompareConditionalBool<T, U, GET_DATA> compareConversor(CompareConditionalCmpT<T, U, GET_DATA>&& res) noexcept {
	if constexpr (GET_DATA)
		return CompareConditionalBool<T, U, GET_DATA>(res.getValue1(), res.getValue2(), res.getResult() == ZERO_CMP);
	else return res == ZERO_CMP;
}
template<class T, class U = T, ll_bool_t GET_DATA = LL_FALSE>
__LL_NODISCARD__ constexpr CompareConditionalBool<T, U, GET_DATA> compareConversor(const CompareConditionalCmpT<T, U, GET_DATA>& res) noexcept {
	if constexpr (GET_DATA)
		return CompareConditionalBool<T, U, GET_DATA>(res.getValue1(), res.getValue2(), res.getResult() == ZERO_CMP);
	else return res == ZERO_CMP;
}

#pragma endregion

template<class T, class U>
struct CompareDefault {
	__LL_NODISCARD__ constexpr cmp_t compare(traits::cinput<T> a, traits::cinput<U> b) const noexcept {
		return a - b;
	}
	__LL_NODISCARD__ constexpr ll_bool_t compareBool(traits::cinput<T> a, traits::cinput<U> b) const noexcept {
		return a == b;
	}
};

template<class T, class U>
struct ManipulatorDefault {
	__LL_NODISCARD__ constexpr void swap(T& a, U& b) noexcept {
		T tmp = a;
		a = b;
		b = tmp;
	}
	__LL_NODISCARD__ constexpr void copy(T& a, traits::cinput<U> b) noexcept {
		a = b;
	}
	__LL_NODISCARD__ constexpr void move(T& a, U& b) noexcept {
		a = std::move(b);
	}
};

template<class T, class U = T, class Comparator = CompareDefault<T, U>, ll_bool_t GET_DATA = LL_FALSE>
struct compare_cluster : public Comparator {
	#pragma region Types
	public:
		using func = traits::member_function_traits<decltype(&Comparator::compare)>;

		using cinput_t = traits::cinput<T>;
		using cinput_u = traits::cinput<U>;

		using CompareFunc = cmp_t(Comparator::*)(cinput_t, cinput_u) noexcept;
		using CompareFuncConst = cmp_t(Comparator::*)(cinput_t, cinput_u) const noexcept;
		using CompareFuncStatic = cmp_t(*)(cinput_t, cinput_u) noexcept;

		using CompareFuncBool = ll_bool_t(Comparator::*)(cinput_t, cinput_u) noexcept;
		using CompareFuncBoolConst = ll_bool_t(Comparator::*)(cinput_t, cinput_u) const noexcept;
		using CompareFuncBoolStatic = ll_bool_t(*)(cinput_t, cinput_u) noexcept;

		using CompareResult = CompareConditionalCmpT<T, U, GET_DATA>;
		using CompareResultBool = CompareConditionalBool<T, U, GET_DATA>;
		using ArrayPair_t = meta::ArrayPair<T>;
		using ArrayPair_u = meta::ArrayPair<U>;
		using Array_t = meta::Array<T>;
		using Array_u = meta::Array<U>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t COMPARE_CLASS_FUNCTION_AVAIBLE = std::is_same_v<CompareFunc, decltype(&Comparator::compare)>;
		static constexpr ll_bool_t COMPARE_CLASS_CONST_FUNCTION_AVAIBLE = std::is_same_v<CompareFuncConst, decltype(&Comparator::compare)>;
		static constexpr ll_bool_t COMPARE_FUNCTION_AVAIBLE = COMPARE_CLASS_FUNCTION_AVAIBLE || COMPARE_CLASS_CONST_FUNCTION_AVAIBLE;

		static constexpr ll_bool_t COMPAREBOOL_CLASS_FUNCTION_AVAIBLE = std::is_same_v<CompareFuncBool, decltype(&Comparator::compareBool)>;
		static constexpr ll_bool_t COMPAREBOOL_CLASS_CONST_FUNCTION_AVAIBLE = std::is_same_v<CompareFuncBoolConst, decltype(&Comparator::compareBool)>;
		static constexpr ll_bool_t COMPAREBOOL_FUNCTION_AVAIBLE = COMPAREBOOL_CLASS_FUNCTION_AVAIBLE || COMPAREBOOL_CLASS_CONST_FUNCTION_AVAIBLE;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<T>, "Const type is forbidden!");
		static_assert(!std::is_reference_v<Comparator>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<Comparator>, "Const type is forbidden!");
		static_assert(!std::is_pointer_v<Comparator>, "Pointer type is forbidden!");
		static_assert(!std::is_array_v<Comparator>, "Array type is forbidden!");
		static_assert(std::is_class_v<Comparator>, "Comparator needs to be a class!");

		static_assert(COMPARE_FUNCTION_AVAIBLE, "Comparator::compare is not avaible!");
		static_assert(COMPAREBOOL_FUNCTION_AVAIBLE, "Comparator::compareBool is not avaible!");

	#pragma endregion

	#pragma region Compare
	#pragma region CompareBase
	// Returns false if check not pass
	__LL_NODISCARD__ constexpr ll_bool_t compareCheck(const T* str1, const U* str2, CompareResult& res) const noexcept {
		if (static_cast<const void*>(str1) == static_cast<const void*>(str2)) {
			res = ZERO_CMP;
			return LL_FALSE;
		}
		else if (!str1 || !str2) {
			res = ((!str1) ? -1 : 1);
			return LL_FALSE;
		}

		return LL_TRUE;
	}
	__LL_NODISCARD__ constexpr CompareResult compare(const T* str1, const U* str2, len_t size) noexcept {
		CompareResult res(ZERO_CMP);
		if (!this->compareCheck(str1, str2, res)) return res;

		for (; size > ZERO_UI64; --size, ++str1, ++str2) {
			cmp_t result = Comparator::compare(*str1, *str2);
			if (result != ZERO_CMP) {
				if constexpr (GET_DATA)
					res = CompareResult(str1, str2, result);
				else res = result;
				break;
			}
		}

		return res;
	}
	__LL_NODISCARD__ constexpr CompareResult compare(const T* str1, const U* str2, len_t size) const noexcept {
		CompareResult res(ZERO_CMP);
		if (!this->compareCheck(str1, str2, res)) return res;

		for (; size > ZERO_UI64; --size, ++str1, ++str2) {
			cmp_t result = Comparator::compare(*str1, *str2);
			if (result != ZERO_CMP) {
				if constexpr (GET_DATA)
					res = CompareResult(str1, str2, result);
				else res = result;
				break;
			}
		}

		return res;
	}

	#pragma endregion
	#pragma region Equals
	#pragma region Ptr
	#pragma region NoConst
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T* str1, const len_t size1, const U* str2, const len_t size2) noexcept {
		if (size1 != size2) return CompareResultBool(LL_FALSE);
		else return compareConversor<T, U, GET_DATA>(compare_cluster::compare(str1, str2, size1));
	}
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T* str1, const len_t size1, const ArrayPair_u& str2) noexcept {
		return compare_cluster::equals(str1, size1, str2.begin(), str2.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T* str1, const len_t size1, const Array_u& str2) noexcept {
		return compare_cluster::equals(str1, size1, str2.begin(), str2.size());
	}

	#pragma endregion
	#pragma region Const
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T* str1, const len_t size1, const U* str2, const len_t size2) const noexcept {
		if (size1 != size2) return CompareResultBool(LL_FALSE);
		else return compareConversor<T, U, GET_DATA>(compare_cluster::compare(str1, str2, size1));
	}
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T* str1, const len_t size1, const ArrayPair_u& str2) const noexcept {
		return compare_cluster::equals(str1, size1, str2.begin(), str2.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T* str1, const len_t size1, const Array_u& str2) const noexcept {
		return compare_cluster::equals(str1, size1, str2.begin(), str2.size());
	}

	#pragma endregion

	#pragma endregion
	#pragma region DefaultArray
	#pragma region NonConst
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&str1)[N], const U* str2, const len_t size2) noexcept {
		return compare_cluster::equals(str1, N, str2, size2);
	}
	template<len_t N, len_t N2>
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&str1)[N], const U(&str2)[N2]) noexcept {
		return compare_cluster::equals(str1, N, str2, N2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&str1)[N], const ArrayPair_u& str2) noexcept {
		return compare_cluster::equals(str1, N, str2.begin(), str2.size());
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&str1)[N], const Array_u& str2) noexcept {
		return compare_cluster::equals(str1, N, str2.begin(), str2.size());
	}

	#pragma endregion
	#pragma region Const
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&str1)[N], const U* str2, const len_t size2) const noexcept {
		return compare_cluster::equals(str1, N, str2, size2);
	}
	template<len_t N, len_t N2>
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&str1)[N], const U(&str2)[N2]) const noexcept {
		return compare_cluster::equals(str1, N, str2, N2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&str1)[N], const ArrayPair_u& str2) const noexcept {
		return compare_cluster::equals(str1, N, str2.begin(), str2.size());
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&str1)[N], const Array_u& str2) const noexcept {
		return compare_cluster::equals(str1, N, str2.begin(), str2.size());
	}

	#pragma endregion

	#pragma endregion
	#pragma region ArrayPair
	#pragma region NoConst
	__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& str1, const U* str2, const len_t size2) noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& str1, const U(&str2)[N]) noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& str1, const ArrayPair_u& str2) noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& str1, const Array_u& str2) noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}

	#pragma endregion
	#pragma region Const
	__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& str1, const U* str2, const len_t size2) const noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& str1, const U(&str2)[N]) const noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& str1, const ArrayPair_u& str2) const noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& str1, const Array_u& str2) const noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}

	#pragma endregion

	#pragma endregion
	#pragma region Array
	#pragma region NoConst
	__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& str1, const U* str2, const len_t size2) noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& str1, const U(&str2)[N]) noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& str1, const ArrayPair_u& str2) noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& str1, const Array_u& str2) noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}

	#pragma endregion
	#pragma region Const
	__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& str1, const U* str2, const len_t size2) const noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& str1, const U(&str2)[N]) const noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& str1, const ArrayPair_u& str2) const noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& str1, const Array_u& str2) const noexcept {
		return compare_cluster::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}

	#pragma endregion

	#pragma endregion

	#pragma endregion
	#pragma endregion
	#pragma region StartsWith
	// Returns false if check not pass
	__LL_NODISCARD__ constexpr ll_bool_t startsWithImmpementationCheck(const T* str, const U* needle, CompareResultBool& res) const noexcept {
		if (static_cast<const void*>(str) == static_cast<const void*>(needle)) {
			res = LL_TRUE;
			return LL_FALSE;
		}
		else if (!str || !needle) {
			res = LL_FALSE;
			return LL_FALSE;
		}
		return LL_TRUE;
	}
	// str size needs to be bigger or equal to needle
	__LL_NODISCARD__ constexpr CompareResultBool startsWithImmpementation(const T* str, const U* needle, len_t size) noexcept {
		CompareResultBool res(LL_TRUE);
		if (!this->startsWithImmpementationCheck(str, needle, res)) return res;

		for (; 0 < size; --size, ++str, ++needle) {
			ll_bool_t result = Comparator::compareBool(*str, *needle);
			if (!result) {
				if constexpr (GET_DATA)
					res = CompareResultBool(str, needle, result);
				else res = result;
				break;
			}
		}
		return res;
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWithImmpementation(const T* str, const U* needle, len_t size) const noexcept {
		CompareResultBool res(LL_TRUE);
		if (!this->startsWithImmpementationCheck(str, needle, res)) return res;

		for (; 0 < size; --size, ++str, ++needle) {
			ll_bool_t result = Comparator::compareBool(*str, *needle);
			if (!result) {
				if constexpr (GET_DATA)
					res = CompareResultBool(str, needle, result);
				else res = result;
				break;
			}
		}
		return res;
	}

	#pragma region Ptr
	#pragma region NoConst
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* str, const len_t size1, const U* needle, const len_t size2) noexcept {
		if (size1 < size2 || (size1 != size2 && size2 == ZERO_UI64)) return CompareResultBool(LL_FALSE);
		else return compare_cluster::startsWithImmpementation(str, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* str, const len_t size1, const U(&needle)[N]) noexcept {
		return compare_cluster::startsWith(str, size1, needle, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* str, const len_t size1, const ArrayPair_u& needle) noexcept {
		return compare_cluster::startsWith(str, size1, needle.begin(), needle.len());
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* str, const len_t size1, const Array_u& needle) noexcept {
		return compare_cluster::startsWith(str, size1, needle.begin(), needle.len());
	}

	#pragma endregion
	#pragma region Const
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* str, const len_t size1, const U* needle, const len_t size2) const noexcept {
		if (size1 < size2 || (size1 != size2 && size2 == ZERO_UI64)) return CompareResultBool(LL_FALSE);
		else return compare_cluster::startsWithImmpementation(str, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* str, const len_t size1, const U(&needle)[N]) const noexcept {
		return compare_cluster::startsWith(str, size1, needle, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* str, const len_t size1, const ArrayPair_u& needle) const noexcept {
		return compare_cluster::startsWith(str, size1, needle.begin(), needle.len());
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* str, const len_t size1, const Array_u& needle) const noexcept {
		return compare_cluster::startsWith(str, size1, needle.begin(), needle.len());
	}

	#pragma endregion

	#pragma endregion
	#pragma region DefaultArray
	#pragma region NoConst
	template<len_t N, len_t N2>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&str)[N], const U(&needle)[N2]) noexcept {
		return compare_cluster::startsWith(str, N, needle, N2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&str)[N], const U* needle, const len_t size2) noexcept {
		return compare_cluster::startsWith(str, N, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&str)[N], const ArrayPair_u& needle) noexcept {
		return compare_cluster::startsWith(str, N, needle.begin(), needle.len());
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&str)[N], const Array_u& needle) noexcept {
		return compare_cluster::startsWith(str, N, needle.begin(), needle.len());
	}

	#pragma endregion
	#pragma region Const
	template<len_t N, len_t N2>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&str)[N], const U(&needle)[N2]) const noexcept {
		return compare_cluster::startsWith(str, N, needle, N2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&str)[N], const U* needle, const len_t size2) const noexcept {
		return compare_cluster::startsWith(str, N, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&str)[N], const ArrayPair_u& needle) const noexcept {
		return compare_cluster::startsWith(str, N, needle.begin(), needle.len());
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&str)[N], const Array_u& needle) const noexcept {
		return compare_cluster::startsWith(str, N, needle.begin(), needle.len());
	}

	#pragma endregion

	#pragma endregion
	#pragma region ArrayPair
	#pragma region NoConst
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& str, const U* needle, len_t size) noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& str, const U(&needle)[N]) noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& str, const ArrayPair_u& needle) noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& str, const Array_u& needle) noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion
	#pragma region Const
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& str, const U* needle, len_t size) const noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& str, const U(&needle)[N]) const noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& str, const ArrayPair_u& needle) const noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& str, const Array_u& needle) const noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion

	#pragma endregion
	#pragma region Array
	#pragma region NoConst
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& str, const U* needle, len_t size) noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& str, const U(&needle)[N]) noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& str, const ArrayPair_u& needle) noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& str, const Array_u& needle) noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion
	#pragma region Const
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& str, const U* needle, len_t size) const noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& str, const U(&needle)[N]) const noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& str, const ArrayPair_u& needle) const noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& str, const Array_u& needle) const noexcept {
		return compare_cluster::startsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion

	#pragma endregion

	#pragma endregion
	#pragma region EndsWith
	#pragma region Ptr
	#pragma region NoConst
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* str, const len_t size1, const U* needle, const len_t size2) noexcept {
		if (size1 < size2 || (size1 != size2 && size2 == ZERO_UI64)) return CompareResultBool(LL_FALSE);
		else return compare_cluster::startsWithImmpementation((str + size1) - size2, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* str, const len_t size1, const U(&needle)[N]) noexcept {
		return compare_cluster::endsWith(str, size1, needle, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* str, const len_t size1, const ArrayPair_u& needle) noexcept {
		return compare_cluster::endsWith(str, size1, needle.begin(), needle.len());
	}
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* str, const len_t size1, const Array_u& needle) noexcept {
		return compare_cluster::endsWith(str, size1, needle.begin(), needle.len());
	}

	#pragma endregion
	#pragma region Const
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* str, const len_t size1, const U* needle, const len_t size2) const noexcept {
		if (size1 < size2 || (size1 != size2 && size2 == ZERO_UI64)) return CompareResultBool(LL_FALSE);
		else return compare_cluster::startsWithImmpementation((str + size1) - size2, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* str, const len_t size1, const U(&needle)[N]) const noexcept {
		return compare_cluster::endsWith(str, size1, needle, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* str, const len_t size1, const ArrayPair_u& needle) const noexcept {
		return compare_cluster::endsWith(str, size1, needle.begin(), needle.len());
	}
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* str, const len_t size1, const Array_u& needle) const noexcept {
		return compare_cluster::endsWith(str, size1, needle.begin(), needle.len());
	}

	#pragma endregion

	#pragma endregion
	#pragma region DefaultArray
	#pragma region NoConst
	template<len_t N, len_t N2>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&str)[N], const U(&needle)[N2]) noexcept {
		return compare_cluster::endsWith(str, N, needle, N2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&str)[N], const U* needle, const len_t size2) noexcept {
		return compare_cluster::endsWith(str, N, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&str)[N], const ArrayPair_u& needle) noexcept {
		return compare_cluster::endsWith(str, N, needle.begin(), needle.len());
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&str)[N], const Array_u& needle) noexcept {
		return compare_cluster::endsWith(str, N, needle.begin(), needle.len());
	}

	#pragma endregion
	#pragma region Const
	template<len_t N, len_t N2>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&str)[N], const U(&needle)[N2]) const noexcept {
		return compare_cluster::endsWith(str, N, needle, N2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&str)[N], const U* needle, const len_t size2) const noexcept {
		return compare_cluster::endsWith(str, N, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&str)[N], const ArrayPair_u& needle) const noexcept {
		return compare_cluster::endsWith(str, N, needle.begin(), needle.len());
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&str)[N], const Array_u& needle) const noexcept {
		return compare_cluster::endsWith(str, N, needle.begin(), needle.len());
	}

	#pragma endregion

	#pragma endregion
	#pragma region ArrayPair
	#pragma region NoConst
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& str, const U* needle, len_t size) noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& str, const U(&needle)[N]) noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& str, const ArrayPair_u& needle) noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& str, const Array_u& needle) noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion
	#pragma region Const
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& str, const U* needle, len_t size) const noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& str, const U(&needle)[N]) const noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& str, const ArrayPair_u& needle) const noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& str, const Array_u& needle) const noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion

	#pragma endregion
	#pragma region Array
	#pragma region NoConst
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& str, const U* needle, len_t size) noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& str, const U(&needle)[N]) noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& str, const ArrayPair_u& needle) noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& str, const Array_u& needle) noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion
	#pragma region Const
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& str, const U* needle, len_t size) const noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& str, const U(&needle)[N]) const noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& str, const ArrayPair_u& needle) const noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& str, const Array_u& needle) const noexcept {
		return compare_cluster::endsWith(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion

	#pragma endregion

	#pragma endregion
};

template<class T, class U = T, class Comparator = CompareDefault<T, U>, ll_bool_t POSITION = LL_TRUE>
struct finders_cluster {
	static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
	static_assert(!std::is_const_v<T>, "Const type is forbidden!");

	using cinput_t = traits::cinput<T>;
	using cinput_u = traits::cinput<U>;
	using CompareFunc = fnc_clss::Compare<cinput_t, cinput_u>;
	using CompareFuncBool = fnc_clss::CompareBool<cinput_t, cinput_u>;

	static_assert(!std::is_reference_v<Comparator>, "Reference type is forbidden!");
	static_assert(!std::is_const_v<Comparator>, "Const type is forbidden!");
	static_assert(!std::is_pointer_v<Comparator>, "Pointer type is forbidden!");
	static_assert(!std::is_array_v<Comparator>, "Array type is forbidden!");
	static_assert(std::is_class_v<Comparator>, "Comparator needs to be a class!");
	static_assert(std::is_same_v<CompareFunc, decltype(&Comparator::compare)>, "Comparator::compareBool needs to be the same type as CompareFunc!");
	static_assert(std::is_same_v<CompareFuncBool, decltype(&Comparator::compareBool)>, "Comparator::compareBool needs to be the same type as CompareFuncBool!");

	using __find = finders_cluster<T, U, Comparator, POSITION>;
	using FindResult = std::conditional_t<POSITION, len_t, const T*>;
	using ArrayPair_t = meta::ArrayPair<T>;
	using ArrayPair_u = meta::ArrayPair<U>;
	using Array_t = meta::Array<T>;
	using Array_u = meta::Array<U>;

	#pragma region Find
	__LL_NODISCARD__ constexpr FindResult find(const T* begin, const T* end, cinput_u object) noexcept {
		if (!begin || !end || end <= begin) {
			if constexpr (POSITION) return npos;
			else return end;
			//throw "Find error values";
		}

		for (const T* data = begin; data < end; ++data)
			if (Comparator::compareBool(*data, object)) {
				if constexpr (POSITION) return data - begin;
				else return data;
			}
		if constexpr (POSITION) return npos;
		else return end;
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr FindResult find(const T (&data)[N], cinput_u object) noexcept {
		return __find::find(data, data + N, object);
	}
	__LL_NODISCARD__ constexpr FindResult find(const ArrayPair_t& arr, cinput_u object) noexcept {
		return __find::find(arr.begin(), arr.end(), object);
	}
	__LL_NODISCARD__ constexpr FindResult find(const Array_t& arr, cinput_u object) noexcept {
		return __find::find(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region rFind
	__LL_NODISCARD__ constexpr FindResult rfind(const T* begin, const T* end, cinput_u object) noexcept {
		if (!begin || !end || end <= begin) {
			if constexpr (POSITION) return npos;
			else return end;
		}

		for (const T* data = end - 1; data > begin; --data)
			if (Comparator::compareBool(*data, object)) {
				if constexpr (POSITION) return data - begin;
				else return data;
			}

		if constexpr (POSITION) return Comparator::compareBool(*begin, object) ? 0 : npos;
		else return Comparator::compareBool(*begin, object) ? begin : end;
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr FindResult rfind(const T (&data)[N], cinput_u object) noexcept {
		return __find::rfind(data, data + N, object);
	}
	__LL_NODISCARD__ constexpr FindResult rfind(const ArrayPair_t& arr, cinput_u object) noexcept {
		return __find::rfind(arr.begin(), arr.end(), object);
	}
	__LL_NODISCARD__ constexpr FindResult rfind(const Array_t& arr, cinput_u object) noexcept {
		return __find::rfind(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Contains
	__LL_NODISCARD__ constexpr ll_bool_t contains(const T* begin, const T* end, cinput_u object) noexcept {
		if constexpr (POSITION) return __find::find(begin, end, object) != npos;
		else return __find::find(begin, end, object) != end;
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr ll_bool_t contains(const T(&data)[N], cinput_u object) noexcept {
		return __find::contains(data, data + N, object);
	}
	__LL_NODISCARD__ constexpr ll_bool_t contains(const ArrayPair_t& arr, cinput_u object) noexcept {
		return __find::contains(arr.begin(), arr.end(), object);
	}
	__LL_NODISCARD__ constexpr ll_bool_t contains(const Array_t& arr, cinput_u object) noexcept {
		return __find::contains(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Other
	#pragma region All
	__LL_NODISCARD__ constexpr ll_bool_t all(const T* begin, const T* end, cinput_u object) noexcept {
		if (!begin || !end || end <= begin) return LL_FALSE;

		for (; begin < end; ++begin)
			if (!Comparator::compareBool(*begin, object))
				return LL_FALSE;
		return LL_TRUE;
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr ll_bool_t all(const T (&data)[N], cinput_u object) noexcept {
		return __find::all(data, data + N, object);
	}
	__LL_NODISCARD__ constexpr ll_bool_t all(const ArrayPair_t& arr, cinput_u object) noexcept {
		return __find::all(arr.begin(), arr.end(), object);
	}
	__LL_NODISCARD__ constexpr ll_bool_t all(const Array_t& arr, cinput_u object) noexcept {
		return __find::all(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Any
	__LL_NODISCARD__ constexpr ll_bool_t any(const T* begin, const T* end, cinput_u object) noexcept {
		return __find::contains(begin, end, object);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr ll_bool_t any(const T (&data)[N], cinput_u object) noexcept {
		return __find::any(data, data + N, object);
	}
	__LL_NODISCARD__ constexpr ll_bool_t any(const ArrayPair_t& arr, cinput_u object) noexcept {
		return __find::any(arr.begin(), arr.end(), object);
	}
	__LL_NODISCARD__ constexpr ll_bool_t any(const Array_t& arr, cinput_u object) noexcept {
		return __find::any(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region None
	__LL_NODISCARD__ constexpr ll_bool_t none(const T* begin, const T* end, cinput_u object) noexcept {
		return !__find::contains(begin, end, object);
	}
	template<len_t N>
	__LL_NODISCARD__ constexpr ll_bool_t none(const T (&data)[N], cinput_u object) noexcept {
		return __find::none(data, data + N, object);
	}
	__LL_NODISCARD__ constexpr ll_bool_t none(const ArrayPair_t& arr, cinput_u object) noexcept {
		return __find::none(arr.begin(), arr.end(), object);
	}
	__LL_NODISCARD__ constexpr ll_bool_t none(const Array_t& arr, cinput_u object) noexcept {
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
	//__LL_NODISCARD__ constexpr const T* binarysearch(const T* begin, const T* end, cinput_u object) noexcept {
	//	static_assert(traits::has_equal_operator_v<T>, "Error, <T> object has no operator==()");
	//	static_assert(traits::has_greater_operator_v<T>, "Error, <T> object has no operator>()");
	//	len_t low = ZERO_UI64;
	//	len_t high = end - begin;
	//	while (low <= high) {
	//		len_t mid = ((high + low) >> 1);
	//		if(begin[mid] == object) return begin + mid;
	//		else if(begin[mid] > object) high = mid;
	//		else low = mid + 1;
	//	}
	//	return end;
	//}
	//// This is recommended to use with objects types
	//__LL_NODISCARD__ constexpr const T* binarysearch(const T* begin, const T* end, cinput_u object) noexcept {
	//	len_t low = ZERO_UI64;
	//	len_t high = end - begin;
	//	while (low <= high) {
	//		len_t mid = ((high - low) >> 1);
	//		cmp_t res = Comparator::compare(begin[mid], object);
	//		if (res == ZERO_CMP) return begin + mid;
	//		else if (res > 0) high = mid;
	//		else low = mid + 1;
	//	}
	//	return end;
	//}

	#pragma region Proxy
	//__LL_NODISCARD__ constexpr len_t binarysearch_pos(const T* begin, const T* end, cinput_u object) noexcept {
	//	const T* pos = __find::binarysearch(begin, end, object);
	//	return (pos != end) ? pos - begin : npos;
	//}
	//template<len_t N>
	//__LL_NODISCARD__ constexpr const T* binarysearch(const T (&data)[N], cinput_u object) noexcept {
	//	if (!data || N == ZERO_UI64) return data + N;
	//	return __find::binarysearch(data, data + N, object);
	//}
	//template<len_t N>
	//__LL_NODISCARD__ constexpr len_t binarysearch_pos(const T (&data)[N], cinput_u object) noexcept {
	//	if (!data || N == ZERO_UI64) return data + N;
	//	return __find::binarysearch_pos(data, data + N, object);
	//}
	//__LL_NODISCARD__ constexpr const T* binarysearch(const ArrayPair_t& arr, cinput_u object) noexcept {
	//	return __find::binarysearch(arr.begin(), arr.end(), object);
	//}
	//__LL_NODISCARD__ constexpr len_t binarysearch_pos(const ArrayPair_t& arr, cinput_u object) noexcept {
	//	return __find::binarysearch_pos(arr.begin(), arr.end(), object);
	//}

	#pragma endregion
	#pragma endregion
};

template<class T, class Manipulator = ManipulatorDefault<T, T>>
struct data_manipulation_cluster {
	static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
	static_assert(!std::is_const_v<T>, "Const type is forbidden!");
	using cinput_t = traits::cinput<T>;
	using SwapFunc = fnc_clss::SwapFunction<T, T>;

	static_assert(!std::is_reference_v<Manipulator>, "Reference type is forbidden!");
	static_assert(!std::is_const_v<Manipulator>, "Const type is forbidden!");
	static_assert(!std::is_pointer_v<Manipulator>, "Pointer type is forbidden!");
	static_assert(!std::is_array_v<Manipulator>, "Array type is forbidden!");
	static_assert(std::is_class_v<Manipulator>, "Manipulator needs to be a class!");
	static_assert(std::is_same_v<SwapFunc, decltype(&Manipulator::swap)>,
		"Manipulator::swap needs to be the same type as SwapFunc!");

	using __data = data_manipulation_cluster<T, Manipulator>;
	using Array_t = meta::Array<T>;

	#pragma region Reverse
	constexpr void reverse(T* arr, T* end) noexcept {
		for (; arr < end; ++arr, --end)
			Manipulator::swap(*arr, *end);
	}
	constexpr void reverse(Array_t& arr) noexcept {
		__data::reverse(arr.begin(), arr.end());
	}
	template<len_t N>
	constexpr void reverse(T(&arr)[N]) noexcept {
		__data::reverse(arr, arr + N - 1);
	}

	constexpr ll_bool_t reverse_s(T* arr, T* end) noexcept {
		if (!arr || !end || end <= arr) return LL_FALSE;
		__data::reverse(arr, end);
		return LL_TRUE;
	}
	constexpr ll_bool_t reverse_s(Array_t& arr) noexcept {
		return __data::reverse_s(arr.begin(), arr.end());
	}
	template<len_t N>
	constexpr ll_bool_t reverse_s(T(&arr)[N]) noexcept {
		return __data::reverse(arr, arr + N - 1);
	}

	#pragma endregion
	#pragma region Fillers
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void fill(T* dst, T* end, W object) noexcept {
		using CopyFunction = fnc_clss::SetFunction<T, W>;
		static_assert(std::is_same_v<CopyFunction, decltype(&FunctionManipulator::copy)>,
			"FunctionManipulator::copy needs to be the same type as CopyFunction!");

		if (!dst || !end || end <= dst) return;
		for (; dst <= end; ++dst)
			FunctionManipulator::copy(*dst, object);
	}
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void fill(Array_t& dst, W object) noexcept {
		__data::fill<U, W, FunctionManipulator>(dst.begin(), dst.end(), object);
	}
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>, len_t N>
	constexpr void fill(T(&dst)[N], W object) noexcept {
		__data::fill<U, W, FunctionManipulator>(dst, dst + N - 1, object);
	}

	#pragma endregion
	#pragma region Copy
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void copy(const U* src, T* dst, len_t size) noexcept {
		using CopyFunction = fnc_clss::SetFunction<T, W>;
		static_assert(std::is_same_v<CopyFunction, decltype(&FunctionManipulator::copy)>,
			"FunctionManipulator::copy needs to be the same type as CopyFunction!");

		if (!src || !dst || size == ZERO_UI64) return;
		for (; size > ZERO_UI64; ++src, ++dst, --size)
			FunctionManipulator::copy(*dst, *src);
	}
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void copy(const meta::ArrayPair<U>& src, T* dst, const len_t size) noexcept {
		__data::copy<U, W, FunctionManipulator>(src.begin(), dst, math::min<len_t>(src.len(), size));
	}
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void copy(const meta::ArrayPair<U>& src, Array_t& dst) noexcept {
		__data::copy<U, W, FunctionManipulator>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
	}
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void copy(const meta::Array<U>& src, Array_t& dst) noexcept {
		__data::copy<U, W, FunctionManipulator>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
	}
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>, len_t N>
	constexpr void copy(const U(&src)[N], T* dst, const len_t size) noexcept {
		__data::copy<U, W, FunctionManipulator>(src, dst, math::min<len_t>(N, size));
	}
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>, len_t N>
	constexpr void copy(const U(&src)[N], Array_t& dst) noexcept {
		__data::copy<U, W, FunctionManipulator>(src, dst.begin(), math::min<len_t>(N, dst.len()));
	}

	#pragma endregion
	#pragma region Move
	template<class U = T, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void move(U* src, T* dst, len_t size) noexcept {
		using MoveFunction = fnc_clss::SwapFunction<T, U>;
		static_assert(std::is_same_v<MoveFunction, decltype(&FunctionManipulator::move)>,
			"FunctionManipulator::move needs to be the same type as MoveFunction!");

		if (!src || !dst || size == ZERO_UI64) return;
		for (; size > ZERO_UI64; ++src, ++dst, --size)
			FunctionManipulator::move(*dst, *src);
	}
	template<class U = T, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void move(const meta::ArrayPair<U>& src, T* dst, const len_t size) noexcept {
		__data::move<U, FunctionManipulator>(src.begin(), dst, math::min<len_t>(src.len(), size));
	}
	template<class U = T, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void move(const meta::ArrayPair<U>& src, Array_t& dst) noexcept {
		__data::move<U, FunctionManipulator>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
	}
	template<class U = T, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void move(const meta::Array<U>& src, Array_t& dst) noexcept {
		__data::move<U, FunctionManipulator>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
	}
	template<class U = T, class FunctionManipulator = CompareDefault<T, U>, len_t N>
	constexpr void move(const U(&src)[N], T* dst, const len_t size) noexcept {
		__data::move<U, FunctionManipulator>(src, dst, math::min<len_t>(N, size));
	}
	template<class U = T, class FunctionManipulator = CompareDefault<T, U>, len_t N>
	constexpr void move(const U(&src)[N], Array_t& dst) noexcept {
		__data::move<U, FunctionManipulator>(src, dst.begin(), math::min<len_t>(N, dst.len()));
	}

	#pragma endregion
	#pragma region ShiftLeft
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void shiftLeft(T* arr, const len_t size, const len_t first, len_t num, W null) noexcept {
		using CopyFunction = fnc_clss::SetFunction<T, W>;
		static_assert(std::is_same_v<CopyFunction, decltype(&FunctionManipulator::copy)>,
			"FunctionManipulator::copy needs to be the same type as CopyFunction!");

		if (!arr || size <= 1ull || num == ZERO_UI64 || first < ZERO_UI64 || first >= size) return;
		if (first + num >= size) num = size - first - 1ull;

		len_t size_loop = size - num;
		T* last = arr + size_loop;
		for (T* src = arr + num; arr < last; ++arr, ++src)
			FunctionManipulator::copy(*arr, *src);
		last += num - 1ull;
		__data::fill<U, W, FunctionManipulator>(arr, last, null);
	}
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void shiftLeft(Array_t& arr, const len_t first, const len_t num, W null) noexcept {
		__data::shiftLeft<U, W, FunctionManipulator>(arr.begin(), arr.len(), first, num, null);
	}
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>, len_t N>
	constexpr void shiftLeft(T(&arr)[N], const len_t first, const len_t num, W null) noexcept {
		__data::shiftLeft<U, W, FunctionManipulator>(arr, N, first, num, null);
	}

	#pragma endregion
	#pragma region ShiftRight
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void shifRight(T* arr, const len_t size, const len_t first, len_t num, W null) noexcept {
		using CopyFunction = fnc_clss::SetFunction<T, W>;
		static_assert(std::is_same_v<CopyFunction, decltype(&FunctionManipulator::copy)>,
			"FunctionManipulator::copy needs to be the same type as CopyFunction!");

		if (!arr || size <= 1ull || num == ZERO_UI64 || first < ZERO_UI64 || first >= size) return;

		len_t size_loop = first + num;
		if (size_loop >= size) num = size - first - 1ull;

		T* dst = arr + size - 1ull;
		T* last = arr + size_loop;
		for (T* src = dst - num; dst >= last ; --dst, --src)
			FunctionManipulator::copy(*dst, *src);
		__data::fill<U, W, FunctionManipulator>(arr + first, --last, null);
	}
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>>
	constexpr void shifRight(Array_t& arr, const len_t first, const len_t num, W null) noexcept {
		__data::shifRight<U, W, FunctionManipulator>(arr.begin(), arr.len(), first, num, null);
	}
	template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = CompareDefault<T, U>, len_t N>
	constexpr void shifRight(T(&arr)[N], const len_t first, const len_t num, W null) noexcept {
		__data::shifRight<U, W, FunctionManipulator>(arr, N, first, num, null);
	}

	#pragma endregion
	#pragma region Qsort
	//template<class T, class U = traits::template_types<T>>
	//constexpr T* qsort_div(
	//	T* arr,
	//	T* begin,
	//	T* end,
	//	fnc_clss::SwapFunction<U::type> swap,
	//	fnc_clss::Compare<U::cinput> cmp
	//) noexcept {
	//	__LL_ASSERT_VAR_NULL__(arr, "arr");
	//	__LL_ASSERT_VAR_NULL__(begin, "begin");
	//	__LL_ASSERT_VAR_NULL__(end, "end");
	//	__LL_ASSERT_VAR_NULL__(swap, "swap");
	//	__LL_ASSERT_VAR_NULL__(cmp, "cmp");
	//
	//	T* left = begin;
	//	T* right = end;
	//	T* piv = arr;
	//
	//	while (left < right) {
	//		for (; cmp(*right, *piv) > 0; --right);
	//		for (; (left < right) && cmp(*left, *piv) <= ZERO_CMP; ++left);
	//		if (left < right) swap(*left, *right);
	//	}
	//	swap(*right, *begin);
	//	return right;
	//}
	//template<class T, class U = traits::template_types<T>>
	//constexpr void quicksort(
	//	T* arr, T* begin, T* end,
	//	fnc_clss::SwapFunction<U::type> swap,
	//	fnc_clss::Compare<U::cinput> cmp
	//) {
	//	if (begin < end) {
	//		T* pivote = qsort_div<T, U>(arr, begin, end, swap, cmp);
	//		//if (pivote >= begin && pivote <= end) {
	//		quicksort<T, U>(arr, begin, pivote - 1, swap, cmp);
	//		quicksort<T, U>(arr, pivote + 1, end, swap, cmp);
	//		//}
	//	}
	//}
	//template<class T, class U = traits::template_types<T>>
	//constexpr void quicksort(T* arr, T* begin, T* end) {
	//	quicksort<T>(arr, begin, end, common::simple_swap<T>, common::compare_with_operators<T>);
	//}
	//template<class T, class U = traits::template_types<T>>
	//constexpr void quicksort(T* begin, T* end) {
	//	quicksort<T, U>(begin, begin, end);
	//}
	//template<class T, class U = traits::template_types<T>, len_t N>
	//constexpr void quicksort(T(&arr)[N]) {
	//	quicksort<T, U>(arr, arr, arr + (N - 1));
	//}

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
