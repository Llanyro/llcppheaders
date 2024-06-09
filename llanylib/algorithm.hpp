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
		using CompareData_t = CompareData<T, U, result_t, _NULL_RESULT_>;
		static constexpr result_t NULL_RESULT = _NULL_RESULT_;

	protected:
		const T* value1;	// Value 1 of the result given
		const U* value2;	// Value 2 of the result given
		result_t result;	// Result of comparation
	protected:
		constexpr void simpleClear() noexcept {
			this->result = NULL_RESULT;
			this->value1 = LL_NULLPTR;
			this->value2 = LL_NULLPTR;
		}
	public:
		constexpr CompareData() noexcept : CompareData(NULL_RESULT) {}
		constexpr CompareData(const result_t result) noexcept
			: CompareData(LL_NULLPTR, LL_NULLPTR, result) {}
		constexpr CompareData(const T* value1, const U* value2, const result_t result) noexcept
			: value1(value1), value2(value2), result(result) {}
		constexpr ~CompareData() noexcept {}

		constexpr CompareData(const CompareData_t& other) noexcept
			: value1(other.value1), value2(other.value2), result(other.result) {}
		constexpr CompareData_t& operator=(const CompareData_t& other) noexcept {
			this->value1 = other.value1;
			this->value2 = other.value2;
			this->result = other.result;
			return *this;
		}

		constexpr CompareData(CompareData_t&& other) noexcept
			: value1(other.value1), value2(other.value2), result(other.result)
		{ other.simpleClear(); }
		constexpr CompareData_t& operator=(CompareData_t&& other) noexcept {
			this->value1 = other.value1;
			this->value2 = other.value2;
			this->result = other.result;
			other.simpleClear();
			return *this;
		}

		__LL_NODISCARD__ operator const CompareData_t*() const noexcept = delete;
		__LL_NODISCARD__ operator CompareData_t*() noexcept = delete;

		__LL_NODISCARD__ constexpr const T* getValue1() noexcept { return this->value1; }
		__LL_NODISCARD__ constexpr const U* getValue2() noexcept { return this->value2; }
		__LL_NODISCARD__ constexpr result_t getResult() const noexcept { return this->result; }
};

template<class T, class U, class result_t, result_t NULL_RESULT, ll_bool_t GET_DATA>
using CompareConditional = std::conditional_t<GET_DATA, algorithm::CompareData<T, U, result_t, NULL_RESULT>, result_t>;
template<class T, class U, ll_bool_t GET_DATA>
using CompareConditionalCmpT = CompareConditional<T, U, cmp_t, 0, GET_DATA>;
template<class T, class U, ll_bool_t GET_DATA>
using CompareConditionalBool = CompareConditional<T, U, ll_bool_t, LL_FALSE, GET_DATA>;

#pragma endregion

struct Cmp {
	__LL_NODISCARD__ static constexpr ll_bool_t compareBool(const int, const char) noexcept {
		return LL_FALSE;
	}
	__LL_NODISCARD__ static constexpr cmp_t compare(const int, const char) noexcept {
		return LL_FALSE;
	}
	__LL_NODISCARD__ static constexpr void set(int&, const char) noexcept {

	}
	__LL_NODISCARD__ static constexpr void swap(int&, int&) noexcept {
	}
	//__LL_NODISCARD__ static constexpr void swap(int&, char&) noexcept {
	//}
};

//template<class T, class U = T, ll_bool_t GET_DATA = LL_FALSE>
template<class T, class Comparator, class U = T, ll_bool_t GET_DATA = LL_FALSE>
struct compare_cluster {
	static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
	static_assert(!std::is_const_v<T>, "Const type is forbidden!");

	using cinput_t = traits::cinput<T>;
	using cinput_u = traits::cinput<U>;
	using CompareFunc = fnc_clss::Compare<cinput_t, cinput_u> noexcept;
	using CompareFuncBool = fnc_clss::CompareBool<cinput_t, cinput_u> noexcept;

	static_assert(!std::is_reference_v<Comparator>, "Reference type is forbidden!");
	static_assert(!std::is_const_v<Comparator>, "Const type is forbidden!");
	static_assert(!std::is_pointer_v<Comparator>, "Pointer type is forbidden!");
	static_assert(!std::is_array_v<Comparator>, "Array type is forbidden!");
	static_assert(std::is_class_v<Comparator>, "Comparator needs to be a class!");
	static_assert(std::is_same_v<CompareFunc, decltype(&Comparator::compare)>, "Comparator::compareBool needs to be the same type as CompareFunc!");
	static_assert(std::is_same_v<CompareFuncBool, decltype(&Comparator::compareBool)>, "Comparator::compareBool needs to be the same type as CompareFuncBool!");

	using __cmp = compare_cluster<T, Comparator, U, GET_DATA>;
	using CompareResult = CompareConditionalCmpT<T, U, GET_DATA>;
	using CompareResultBool = CompareConditionalBool<T, U, GET_DATA>;
	using __ArrayPair_t = meta::ArrayPair<T>;
	using __ArrayPair_u = meta::ArrayPair<U>;
	using __Array_t = meta::Array<T>;
	using __Array_u = meta::Array<U>;

	#pragma region Compare
	__LL_NODISCARD__ static constexpr CompareResult compare(const T* str1, const U* str2, len_t size) noexcept {
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

		for (; size > ZERO_UI64; --size, ++str1, ++str2) {
			cmp_t result = Comparator::compare(*str1, *str2);
			if (result != ZERO_I32) {
				if constexpr (GET_DATA)
					return CompareResult(str1, str2, result);
				else return result;
			}
		}
		if constexpr (GET_DATA) return CompareResult(ZERO_I32);
		else return ZERO_I32;
	}

	#pragma region Equals
	#pragma region Ptr
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const T* str1, const len_t size1, const U* str2, const len_t size2) noexcept {
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
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const T* str1, const len_t size1, const __ArrayPair_u& str2) noexcept {
		return __cmp::equals(str1, size1, str2.begin(), str2.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const T* str1, const len_t size1, const __Array_u& str2) noexcept {
		return __cmp::equals(str1, size1, str2.begin(), str2.size());
	}

	#pragma endregion
	#pragma region DefaultArray
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const T(&str1)[N], const U* str2, const len_t size2) noexcept {
		return __cmp::equals(str1, N, str2, size2);
	}
	template<len_t N, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const T(&str1)[N], const U(&str2)[N2]) noexcept {
		return __cmp::equals(str1, N, str2, N2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const T(&str1)[N], const __ArrayPair_u& str2) noexcept {
		return __cmp::equals(str1, N, str2.begin(), str2.size());
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const T(&str1)[N], const __Array_u& str2) noexcept {
		return __cmp::equals(str1, N, str2.begin(), str2.size());
	}

	#pragma endregion
	#pragma region ArrayPair
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& str1, const U* str2, const len_t size2) noexcept {
		return __cmp::equals(str1.begin(), str1.size(), str2, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& str1, const U(&str2)[N]) noexcept {
		return __cmp::equals(str1.begin(), str1.size(), str2, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& str1, const __ArrayPair_u& str2) noexcept {
		return __cmp::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __ArrayPair_t& str1, const __Array_u& str2) noexcept {
		return __cmp::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}

	#pragma endregion
	#pragma region Array
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __Array_t& str1, const U* str2, const len_t size2) noexcept {
		return __cmp::equals(str1.begin(), str1.size(), str2, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __Array_t& str1, const U(&str2)[N]) noexcept {
		return __cmp::equals(str1.begin(), str1.size(), str2, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __Array_t& str1, const __ArrayPair_u& str2) noexcept {
		return __cmp::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool equals(const __Array_t& str1, const __Array_u& str2) noexcept {
		return __cmp::equals(str1.begin(), str1.size(), str2.begin(), str2.size());
	}

	#pragma endregion

	#pragma endregion
	#pragma endregion
	#pragma region StartsWith
	// str size needs to be bigger or equal to needle
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with_impl(const T* str, const U* needle, len_t size) {
		if (static_cast<const void*>(str) == static_cast<const void*>(needle)) {
			if constexpr (GET_DATA) return CompareResultBool(LL_TRUE);
			else return LL_TRUE;
		}
		else if (!str || !needle) {
			if constexpr (GET_DATA) return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}

		for (; 0 < size; --size, ++str, ++needle) {
			ll_bool_t result = Comparator::compareBool(*str, *needle);
			if (!result) {
				if constexpr (GET_DATA)
					return CompareResultBool(str, needle, result);
				else return result;
			}
		}
		if constexpr (GET_DATA) return CompareResultBool(LL_TRUE);
		else return LL_TRUE;
	}

	#pragma region Ptr
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const T* str, const len_t size1, const U* needle, const len_t size2) {
		if (size1 < size2 || (size1 != size2 && size2 == ZERO_UI64)) {
			if constexpr (GET_DATA)
				return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}
		else return __cmp::starts_with_impl(str, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const T* str, const len_t size1, const U(&needle)[N]) {
		return __cmp::starts_with(str, size1, needle, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const T* str, const len_t size1, const __ArrayPair_u& needle) {
		return __cmp::starts_with(str, size1, needle.begin(), needle.len());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const T* str, const len_t size1, const __Array_u& needle) {
		return __cmp::starts_with(str, size1, needle.begin(), needle.len());
	}

	#pragma endregion
	#pragma region DefaultArray
	template<len_t N, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const T(&str)[N], const U(&needle)[N2]) {
		return __cmp::starts_with(str, N, needle, N2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const T(&str)[N], const U* needle, const len_t size2) {
		return __cmp::starts_with(str, N, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const T(&str)[N], const __ArrayPair_u& needle) {
		return __cmp::starts_with(str, N, needle.begin(), needle.len());
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const T(&str)[N], const __Array_u& needle) {
		return __cmp::starts_with(str, N, needle.begin(), needle.len());
	}

	#pragma endregion
	#pragma region ArrayPair
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& str, const U* needle, len_t size) {
		return __cmp::starts_with(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& str, const U(&needle)[N]) {
		return __cmp::starts_with(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& str, const __ArrayPair_u& needle) {
		return __cmp::starts_with(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __ArrayPair_t& str, const __Array_u& needle) {
		return __cmp::starts_with(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion
	#pragma region Array
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __Array_t& str, const U* needle, len_t size) {
		return __cmp::starts_with(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __Array_t& str, const U(&needle)[N]) {
		return __cmp::starts_with(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __Array_t& str, const __ArrayPair_u& needle) {
		return __cmp::starts_with(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool starts_with(const __Array_t& str, const __Array_u& needle) {
		return __cmp::starts_with(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion

	#pragma endregion
	#pragma region EndsWith
	#pragma region Ptr
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const T* str, const len_t size1, const U* needle, const len_t size2) {
		if (size1 < size2 || (size1 != size2 && size2 == ZERO_UI64)) {
			if constexpr (GET_DATA)
				return CompareResultBool(LL_FALSE);
			else return LL_FALSE;
		}
		else return __cmp::starts_with_impl((str + size1) - size2, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const T* str, const len_t size1, const U(&needle)[N]) {
		return __cmp::ends_with(str, size1, needle, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const T* str, const len_t size1, const __ArrayPair_u& needle) {
		return __cmp::ends_with(str, size1, needle.begin(), needle.len());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const T* str, const len_t size1, const __Array_u& needle) {
		return __cmp::ends_with(str, size1, needle.begin(), needle.len());
	}

	#pragma endregion
	#pragma region DefaultArray
	template<len_t N, len_t N2>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const T(&str)[N], const U(&needle)[N2]) {
		return __cmp::ends_with(str, N, needle, N2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const T(&str)[N], const U* needle, const len_t size2) {
		return __cmp::ends_with(str, N, needle, size2);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const T(&str)[N], const __ArrayPair_u& needle) {
		return __cmp::ends_with(str, N, needle.begin(), needle.len());
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const T(&str)[N], const __Array_u& needle) {
		return __cmp::ends_with(str, N, needle.begin(), needle.len());
	}

	#pragma endregion
	#pragma region ArrayPair
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& str, const U* needle, len_t size) {
		return __cmp::ends_with(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& str, const U(&needle)[N]) {
		return __cmp::ends_with(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& str, const __ArrayPair_u& needle) {
		return __cmp::ends_with(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __ArrayPair_t& str, const __Array_u& needle) {
		return __cmp::ends_with(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion
	#pragma region Array
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __Array_t& str, const U* needle, len_t size) {
		return __cmp::ends_with(str.begin(), str.size(), needle, size);
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __Array_t& str, const U(&needle)[N]) {
		return __cmp::ends_with(str.begin(), str.size(), needle, N);
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __Array_t& str, const __ArrayPair_u& needle) {
		return __cmp::ends_with(str.begin(), str.size(), needle.begin(), needle.size());
	}
	__LL_NODISCARD__ static constexpr CompareResultBool ends_with(const __Array_t& str, const __Array_u& needle) {
		return __cmp::ends_with(str.begin(), str.size(), needle.begin(), needle.size());
	}

	#pragma endregion

	#pragma endregion
};

template<class T, class Comparator, class U = T, ll_bool_t POSITION = LL_TRUE>
struct finders_cluster {
	static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
	static_assert(!std::is_const_v<T>, "Const type is forbidden!");

	using cinput_t = traits::cinput<T>;
	using cinput_u = traits::cinput<U>;
	using CompareFunc = fnc_clss::Compare<cinput_t, cinput_u> noexcept;
	using CompareFuncBool = fnc_clss::CompareBool<cinput_t, cinput_u> noexcept;

	static_assert(!std::is_reference_v<Comparator>, "Reference type is forbidden!");
	static_assert(!std::is_const_v<Comparator>, "Const type is forbidden!");
	static_assert(!std::is_pointer_v<Comparator>, "Pointer type is forbidden!");
	static_assert(!std::is_array_v<Comparator>, "Array type is forbidden!");
	static_assert(std::is_class_v<Comparator>, "Comparator needs to be a class!");
	static_assert(std::is_same_v<CompareFunc, decltype(&Comparator::compare)>, "Comparator::compareBool needs to be the same type as CompareFunc!");
	static_assert(std::is_same_v<CompareFuncBool, decltype(&Comparator::compareBool)>, "Comparator::compareBool needs to be the same type as CompareFuncBool!");

	using __find = finders_cluster<T, Comparator, U, POSITION>;
	using FindResult = std::conditional_t<POSITION, len_t, const T*>;
	using __ArrayPair_t = meta::ArrayPair<T>;
	using __ArrayPair_u = meta::ArrayPair<U>;
	using __Array_t = meta::Array<T>;
	using __Array_u = meta::Array<U>;

	#pragma region Find
	__LL_NODISCARD__ static constexpr FindResult find(const T* begin, const T* end, cinput_u object) noexcept {
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
	__LL_NODISCARD__ static constexpr FindResult find(const T (&data)[N], cinput_u object) noexcept {
		return __find::find(data, data + N, object);
	}
	__LL_NODISCARD__ static constexpr FindResult find(const __ArrayPair_t& arr, cinput_u object) noexcept {
		return __find::find(arr.begin(), arr.end(), object);
	}
	__LL_NODISCARD__ static constexpr FindResult find(const __Array_t& arr, cinput_u object) noexcept {
		return __find::find(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region rFind
	__LL_NODISCARD__ static constexpr FindResult rfind(const T* begin, const T* end, cinput_u object) noexcept {
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
	__LL_NODISCARD__ static constexpr FindResult rfind(const T (&data)[N], cinput_u object) noexcept {
		return __find::rfind(data, data + N, object);
	}
	__LL_NODISCARD__ static constexpr FindResult rfind(const __ArrayPair_t& arr, cinput_u object) noexcept {
		return __find::rfind(arr.begin(), arr.end(), object);
	}
	__LL_NODISCARD__ static constexpr FindResult rfind(const __Array_t& arr, cinput_u object) noexcept {
		return __find::rfind(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Contains
	__LL_NODISCARD__ static constexpr ll_bool_t contains(const T* begin, const T* end, cinput_u object) noexcept {
		if constexpr (POSITION) return __find::find(begin, end, object) != npos;
		else return __find::find(begin, end, object) != end;
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t contains(const T(&data)[N], cinput_u object) noexcept {
		return __find::contains(data, data + N, object);
	}
	__LL_NODISCARD__ static constexpr ll_bool_t contains(const __ArrayPair_t& arr, cinput_u object) noexcept {
		return __find::contains(arr.begin(), arr.end(), object);
	}
	__LL_NODISCARD__ static constexpr ll_bool_t contains(const __Array_t& arr, cinput_u object) noexcept {
		return __find::contains(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Other
	#pragma region All
	__LL_NODISCARD__ static constexpr ll_bool_t all(const T* begin, const T* end, cinput_u object) noexcept {
		if (!begin || !end || end <= begin) return LL_FALSE;

		for (; begin < end; ++begin)
			if (!Comparator::compareBool(*begin, object))
				return LL_FALSE;
		return LL_TRUE;
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t all(const T (&data)[N], cinput_u object) noexcept {
		return __find::all(data, data + N, object);
	}
	__LL_NODISCARD__ static constexpr ll_bool_t all(const __ArrayPair_t& arr, cinput_u object) noexcept {
		return __find::all(arr.begin(), arr.end(), object);
	}
	__LL_NODISCARD__ static constexpr ll_bool_t all(const __Array_t& arr, cinput_u object) noexcept {
		return __find::all(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region Any
	__LL_NODISCARD__ static constexpr ll_bool_t any(const T* begin, const T* end, cinput_u object) noexcept {
		return static_cast<ll_bool_t>(__find::find(begin, end, object));
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t any(const T (&data)[N], cinput_u object) noexcept {
		return __find::any(data, data + N, object);
	}
	__LL_NODISCARD__ static constexpr ll_bool_t any(const __ArrayPair_t& arr, cinput_u object) noexcept {
		return __find::any(arr.begin(), arr.end(), object);
	}
	__LL_NODISCARD__ static constexpr ll_bool_t any(const __Array_t& arr, cinput_u object) noexcept {
		return __find::any(arr.begin(), arr.end(), object);
	}

	#pragma endregion
	#pragma region None
	__LL_NODISCARD__ static constexpr ll_bool_t none(const T* begin, const T* end, cinput_u object) noexcept {
		return !static_cast<ll_bool_t>(__find::find(begin, end, object));
	}
	template<len_t N>
	__LL_NODISCARD__ static constexpr ll_bool_t none(const T (&data)[N], cinput_u object) noexcept {
		return __find::none(data, data + N, object);
	}
	__LL_NODISCARD__ static constexpr ll_bool_t none(const __ArrayPair_t& arr, cinput_u object) noexcept {
		return __find::none(arr.begin(), arr.end(), object);
	}
	__LL_NODISCARD__ static constexpr ll_bool_t none(const __Array_t& arr, cinput_u object) noexcept {
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
	//__LL_NODISCARD__ static constexpr const T* binarysearch(const T* begin, const T* end, cinput_u object) {
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
	//__LL_NODISCARD__ static constexpr const T* binarysearch(const T* begin, const T* end, cinput_u object) {
	//	len_t low = ZERO_UI64;
	//	len_t high = end - begin;
	//	while (low <= high) {
	//		len_t mid = ((high - low) >> 1);
	//		cmp_t res = Comparator::compare(begin[mid], object);
	//		if (res == ZERO_I32) return begin + mid;
	//		else if (res > 0) high = mid;
	//		else low = mid + 1;
	//	}
	//	return end;
	//}

	#pragma region Proxy
	//__LL_NODISCARD__ static constexpr len_t binarysearch_pos(const T* begin, const T* end, cinput_u object) noexcept {
	//	const T* pos = __find::binarysearch(begin, end, object);
	//	return (pos != end) ? pos - begin : npos;
	//}
	//template<len_t N>
	//__LL_NODISCARD__ static constexpr const T* binarysearch(const T (&data)[N], cinput_u object) noexcept {
	//	if (!data || N == ZERO_UI64) return data + N;
	//	return __find::binarysearch(data, data + N, object);
	//}
	//template<len_t N>
	//__LL_NODISCARD__ static constexpr len_t binarysearch_pos(const T (&data)[N], cinput_u object) noexcept {
	//	if (!data || N == ZERO_UI64) return data + N;
	//	return __find::binarysearch_pos(data, data + N, object);
	//}
	//__LL_NODISCARD__ static constexpr const T* binarysearch(const __ArrayPair_t& arr, cinput_u object) noexcept {
	//	return __find::binarysearch(arr.begin(), arr.end(), object);
	//}
	//__LL_NODISCARD__ static constexpr len_t binarysearch_pos(const __ArrayPair_t& arr, cinput_u object) noexcept {
	//	return __find::binarysearch_pos(arr.begin(), arr.end(), object);
	//}

	#pragma endregion
	#pragma endregion
};

template<class T, class Comparator>
struct data_manipulation_cluster {
	static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
	static_assert(!std::is_const_v<T>, "Const type is forbidden!");
	using cinput_t = traits::cinput<T>;
	using SwapFunc = fnc_clss::SwapFunction<T> noexcept;

	static_assert(!std::is_reference_v<Comparator>, "Reference type is forbidden!");
	static_assert(!std::is_const_v<Comparator>, "Const type is forbidden!");
	static_assert(!std::is_pointer_v<Comparator>, "Pointer type is forbidden!");
	static_assert(!std::is_array_v<Comparator>, "Array type is forbidden!");
	static_assert(std::is_class_v<Comparator>, "Comparator needs to be a class!");
	static_assert(std::is_same_v<SwapFunc, decltype(&Comparator::swap)>, "Comparator::set needs to be the same type as SetFunction!");

	using __data = data_manipulation_cluster<T, Comparator>;
	template<class W>
	using FillFunc = fnc_clss::SetFunction<T, W>;
	using __Array_t = meta::Array<T>;

	#pragma region Reverse
	static constexpr void reverse(T* arr, T* end) noexcept {
		if (!arr || !end || end <= arr) return;
		for (; arr < end; ++arr, --end)
			Comparator::swap(*arr, *end);
	}
	template<len_t N>
	static constexpr void reverse(T(&arr)[N]) noexcept {
		__data::reverse(arr, arr + N - 1);
	}
	static constexpr void reverse(__Array_t& arr) noexcept {
		__data::reverse(arr.begin(), arr.end());
	}

	#pragma endregion
	#pragma region Fillers
	template<class U, class W = traits::cinput<U>>
	static constexpr void fill(T* dst, T* end, W object) {
		using SetFunction = fnc_clss::SetFunction<T, W>;
		static_assert(std::is_same_v<SetFunction, decltype(&Comparator::set)>, "Comparator::set needs to be the same type as SetFunction!");

		if (!dst || !end || end <= dst) return;
		for (; dst <= end; ++dst) Comparator::set(*dst, object);
	}
	template<class U, class W = traits::cinput<U>, len_t N>
	static constexpr void fill(T(&dst)[N], W object) noexcept {
		__data::fill(dst, dst + N - 1, object);
	}
	template<class U, class W = traits::cinput<U>>
	static constexpr void fill(__Array_t& dst, W object) noexcept {
		__data::fill(dst.begin(), dst.end(), object);
	}

	#pragma endregion
	#pragma region Copy
	template<class U, class W = traits::cinput<U>>
	static constexpr void copy(const U* src, T* dst, len_t size) {
		using SetFunction = fnc_clss::SetFunction<T, W>;
		static_assert(std::is_same_v<SetFunction, decltype(&Comparator::set)>, "Comparator::set needs to be the same type as SetFunction!");

		if (!src || !dst || size == ZERO_UI64) return;
		for (; size > ZERO_UI64; ++src, ++dst, --size) Comparator::set(*dst, *src);
	}
	template<class U, class W = traits::cinput<U>>
	static constexpr void copy(const meta::ArrayPair<U>& src, T* dst, const len_t size) {
		__data::copy(src.begin(), dst, math::min<len_t>(src.len(), size));
	}
	template<class U, class W = traits::cinput<U>>
	static constexpr void copy(const meta::ArrayPair<U>& src, __Array_t& dst) {
		__data::copy(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
	}
	template<class U, class W = traits::cinput<U>>
	static constexpr void copy(const meta::Array<U>& src, __Array_t& dst) {
		__data::copy(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
	}
	template<class U, class W = traits::cinput<U>, len_t N>
	static constexpr void copy(const U(&src)[N], T* dst, const len_t size) {
		__data::copy(src, dst, math::min<len_t>(N, size));
	}
	template<class U, class W = traits::cinput<U>, len_t N>
	static constexpr void copy(const U(&src)[N], __Array_t& dst) {
		__data::copy(src, dst.begin(), math::min<len_t>(N, dst.len()));
	}

	#pragma endregion
	#pragma region Move
	template<class U>
	static constexpr void move(U* src, T* dst, len_t size) {
		using SwapFunc = fnc_clss::SwapFunction<T, U>;
		constexpr SwapFunc swp = &Comparator::swap;
		//static_assert(std::is_same_v<SwapFunc, decltype(&Comparator::swap)>, "Comparator::set needs to be the same type as SetFunction!");

		if (!src || !dst || size == ZERO_UI64) return;
		for (; size > ZERO_UI64; ++src, ++dst, --size) Comparator::set(*dst, *src);
	}
	template<class U>
	static constexpr void move(const meta::ArrayPair<U>& src, T* dst, const len_t size) {
		__data::move(src.begin(), dst, math::min<len_t>(src.len(), size));
	}
	template<class U>
	static constexpr void move(const meta::ArrayPair<U>& src, __Array_t& dst) {
		__data::move(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
	}
	template<class U>
	static constexpr void move(const meta::Array<U>& src, __Array_t& dst) {
		__data::move(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
	}
	template<class U, len_t N>
	static constexpr void move(const U(&src)[N], T* dst, const len_t size) {
		__data::move(src, dst, math::min<len_t>(N, size));
	}
	template<class U, len_t N>
	static constexpr void move(const U(&src)[N], __Array_t& dst) {
		__data::move(src, dst.begin(), math::min<len_t>(N, dst.len()));
	}

	#pragma endregion
	#pragma region ShiftLeft
	template<class U, class W = traits::cinput<U>>
	static constexpr void shiftLeft(T* arr, const len_t size, const len_t first, len_t num, W null) noexcept {
		if (!arr) return;
		if (size <= 1ull || num == ZERO_UI64 || first < ZERO_UI64 || first >= size) return;
		if (first + num >= size) num = size - first - 1ull;

		len_t size_loop = size - num;
		T* last = arr + size_loop;
		for (T* src = arr + num; arr < last; ++arr, ++src)
			Comparator::set(*arr, *src);
		last += num - 1ull;
		__data::fill(arr, last, null);
	}
	template<class U, len_t N, class W = traits::cinput<U>>
	static constexpr void shiftLeft(T(&arr)[N], const len_t first, const len_t num, W null) noexcept {
		__data::shiftLeft(arr, N, first, num, null);
	}
	template<class U, class W = traits::cinput<U>>
	static constexpr void shiftLeft(__Array_t& arr, const len_t first, const len_t num, W null) noexcept {
		__data::shiftLeft(arr.begin(), arr.len(), first, num, null);
	}

	#pragma endregion
	#pragma region ShiftRight
	template<class U, class W = traits::cinput<U>>
	static constexpr void shifRight(T* arr, const len_t size, const len_t first, len_t num, W null) noexcept {
		if (!arr) return;
		if (size <= 1ull || num == ZERO_UI64 || first < ZERO_UI64 || first >= size) return;

		len_t size_loop = first + num;
		if (size_loop >= size) num = size - first - 1ull;

		T* dst = arr + size - 1ull;
		T* last = arr + size_loop;
		for (T* src = dst - num; dst >= last ; --dst, --src)
			Comparator::set(*dst, *src);
		__data::fill(arr + first, --last, null);
	}
	template<class U, len_t N, class W = traits::cinput<U>>
	static constexpr void shifRight(T(&arr)[N], const len_t first, const len_t num, W null) noexcept {
		__data::shifRight(arr, N, first, num, null);
	}
	template<class U, class W = traits::cinput<U>>
	static constexpr void shifRight(__Array_t& arr, const len_t first, const len_t num, W null) noexcept {
		__data::shifRight(arr.begin(), arr.len(), first, num, null);
	}

	#pragma endregion
	#pragma region Qsort
	//template<class T, class U = traits::template_types<T>>
	//static constexpr T* qsort_div(
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
	//		for (; (left < right) && cmp(*left, *piv) <= ZERO_I32; ++left);
	//		if (left < right) swap(*left, *right);
	//	}
	//	swap(*right, *begin);
	//	return right;
	//}
	//template<class T, class U = traits::template_types<T>>
	//static constexpr void quicksort(
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
	//static constexpr void quicksort(T* arr, T* begin, T* end) {
	//	quicksort<T>(arr, begin, end, common::simple_swap<T>, common::compare_with_operators<T>);
	//}
	//template<class T, class U = traits::template_types<T>>
	//static constexpr void quicksort(T* begin, T* end) {
	//	quicksort<T, U>(begin, begin, end);
	//}
	//template<class T, class U = traits::template_types<T>, len_t N>
	//static constexpr void quicksort(T(&arr)[N]) {
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
