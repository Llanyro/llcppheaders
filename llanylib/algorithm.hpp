//////////////////////////////////////////////
//	algorithm.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ALGORITHM_HPP_) // Guard && version protector
	#if LLANYLIB_ALGORITHM_MAYOR_ != 9 || LLANYLIB_ALGORITHM_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "algorithm.hpp version error!"
		#else
			#error "algorithm.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ALGORITHM_MAYOR_ || LLANYLIB_ALGORITHM_MINOR_

#else !defined(LLANYLIB_ALGORITHM_HPP_)
#define LLANYLIB_ALGORITHM_HPP_
#define LLANYLIB_ALGORITHM_MAYOR_ 9
#define LLANYLIB_ALGORITHM_MINOR_ 0

#include "ArrayPair.hpp"
#include "math.hpp"
#include "common.hpp"

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#if defined(__LL_SPECTRE_FUNCTIONS__)
		#pragma warning(disable:5045) // Security Spectre mitigation [SECURITY]
	#endif // __LL_UNSECURE_FUNCTIONS__
#endif // WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace algorithm {

#pragma region Comparators
template<class _T, class _U, class _result_t, _result_t _NULL_RESULT_>
class CompareData {
	#pragma region Types
	public:
		using _MyType		= CompareData;
		using T				= _T;
		using U				= _U;
		using result_t		= _result_t;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr result_t NULL_RESULT = _NULL_RESULT_;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_ignore_pointer_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(traits::is_valid_type_checker_ignore_pointer_v<U>,
			"type_checker<U> detected an invalid type!");
		static_assert(traits::is_basic_type_v<result_t>,
			"Result type must be a basic/primitive type! "
			"Comment this error if you want to use other custom type.");

	#pragma endregion
	#pragma region Attributes
	private:
		const T* value1;	// Value 1 of the result given
		const U* value2;	// Value 2 of the result given
		result_t result;	// Result of comparation

	#pragma endregion
	#pragma region Functions
		#pragma region Private
	private:
		constexpr void simpleClear(const result_t& result = NULL_RESULT) noexcept {
			this->result = result;
			this->value1 = LL_NULLPTR;
			this->value2 = LL_NULLPTR;
		}
		constexpr void simpleClear(result_t&& result) noexcept {
			this->result = std::forward<result_t&&>(result);
			this->value1 = LL_NULLPTR;
			this->value2 = LL_NULLPTR;
		}

		#pragma endregion
		#pragma region Contructor
	public:
		constexpr CompareData() noexcept : CompareData(NULL_RESULT) {}
		constexpr ~CompareData() noexcept {}

		constexpr CompareData(const T* value1, const U* value2, const result_t& result) noexcept
			: value1(value1), value2(value2), result(result) {}
		constexpr CompareData(const T* value1, const U* value2, result_t&& result) noexcept
			: value1(value1), value2(value2), result(std::forward<result_t&&>(result)) {}

		constexpr CompareData(const result_t& result) noexcept
			: CompareData(LL_NULLPTR, LL_NULLPTR, result) {}
		constexpr CompareData& operator=(const result_t& result) noexcept {
			this->simpleClear();
			this->result = result;
			return *this;
		}
		constexpr CompareData(result_t&& result) noexcept
			: CompareData(LL_NULLPTR, LL_NULLPTR, std::forward<result_t&&>(result)) {}
		constexpr CompareData& operator=(result_t&& result) noexcept {
			this->simpleClear();
			this->result = std::forward<result_t&&>(result);
			return *this;
		}

		#pragma endregion
		#pragma region CopyMove
	public:
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
	public:
		__LL_NODISCARD__ constexpr operator const CompareData*() const noexcept = delete;
		__LL_NODISCARD__ constexpr operator CompareData*() noexcept = delete;

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr const T* getValue1() const noexcept { return this->value1; }
		__LL_NODISCARD__ constexpr const U* getValue2() const noexcept { return this->value2; }
		__LL_NODISCARD__ constexpr const result_t& getResult() const noexcept { return this->result; }
		__LL_NODISCARD__ constexpr void clear() noexcept { this->simpleClear(); }

		#pragma endregion
	#pragma endregion
};

template<class T, class U, class result_t, result_t NULL_RESULT, ll_bool_t GET_DATA>
using CompareConditional = std::conditional_t<GET_DATA, algorithm::CompareData<T, U, result_t, NULL_RESULT>, result_t>;
template<class T, class U, ll_bool_t GET_DATA>
using CompareConditionalCmpT = algorithm::CompareConditional<T, U, cmp_t, ZERO_CMP, GET_DATA>;
template<class T, class U, ll_bool_t GET_DATA>
using CompareConditionalBool = algorithm::CompareConditional<T, U, ll_bool_t, llcpp::FALSE, GET_DATA>;

template<class T, class U = T, ll_bool_t GET_DATA = llcpp::FALSE>
__LL_NODISCARD__ constexpr CompareConditionalBool<T, U, GET_DATA> compareConversor(const CompareConditionalCmpT<T, U, GET_DATA>& res) noexcept {
	if constexpr (GET_DATA)
		return CompareConditionalBool<T, U, GET_DATA>(res.getValue1(), res.getValue2(), res.getResult() == ZERO_CMP);
	else return res == ZERO_CMP;
}
template<class T, class U = T, ll_bool_t GET_DATA = llcpp::FALSE>
__LL_NODISCARD__ constexpr CompareConditionalBool<T, U, GET_DATA> compareConversor(CompareConditionalCmpT<T, U, GET_DATA>&& res) noexcept {
	if constexpr (GET_DATA)
		return CompareConditionalBool<T, U, GET_DATA>(res.getValue1(), res.getValue2(), res.getResult() == ZERO_CMP);
	else return res == ZERO_CMP;
}

#pragma endregion

template<class _T, class _U = _T>
class CompareDefault {
	#pragma region Types
	public:
		using _MyType		= CompareDefault;
		using T				= _T;
		using U				= _U;
		using is_comparable = traits::is_comparable<T, U>;

	#pragma endregion
	#pragma region Assert
	public:
		static_assert(is_comparable::IS_COMPARABLE_EQ, "Types are not comparables!");
		static_assert(is_comparable::IS_COMPARABLE_NEQ, "Types are not comparables!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr CompareDefault() noexcept {}
		constexpr ~CompareDefault() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr CompareDefault(const CompareDefault&) noexcept {}
		constexpr CompareDefault& operator=(const CompareDefault&) noexcept { return *this; }
		constexpr CompareDefault(CompareDefault&&) noexcept {}
		constexpr CompareDefault& operator=(CompareDefault&&) noexcept { return *this; }

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const CompareDefault*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator CompareDefault*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr cmp_t compare(traits::cinput<T> a, traits::cinput<U> b) const noexcept {
			if constexpr (traits::is_basic_type_v<>)
				return static_cast<cmp_t>(a - b);
			else if constexpr (traits::common::has_compare_function_v<>) {

			}
		}
		__LL_NODISCARD__ constexpr ll_bool_t compareBool(traits::cinput<T> a, traits::cinput<U> b) const noexcept {
			return is_comparable::is_same_value(a, b);
		}

		#pragma endregion

	#pragma endregion
};

template<class _T, class _U = _T>
class ManipulatorDefault {
	#pragma region Types
	public:
		using _MyType	= ManipulatorDefault;
		using T			= _T;
		using U			= _U;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr ManipulatorDefault() noexcept {}
		constexpr ~ManipulatorDefault() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ManipulatorDefault(const ManipulatorDefault&) noexcept {}
		constexpr ManipulatorDefault& operator=(const ManipulatorDefault&) noexcept { return *this; }
		constexpr ManipulatorDefault(ManipulatorDefault&&) noexcept {}
		constexpr ManipulatorDefault& operator=(ManipulatorDefault&&) noexcept { return *this; }

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const ManipulatorDefault*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator ManipulatorDefault*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr void swap(T& a, U& b) const noexcept {
			T tmp = a;
			a = b;
			b = tmp;
		}
		__LL_NODISCARD__ constexpr void copy(T& a, traits::cinput<U> b) const noexcept {
			a = b;
		}
		__LL_NODISCARD__ constexpr void move(T& a, U& b) const noexcept {
			a = std::move(b);
		}

		#pragma endregion
	#pragma endregion
};

template<class _T, class _U = _T, class _Comparator = algorithm::CompareDefault<_T, _U>>
class ComparatorChecker : public _Comparator {
	#pragma region Types
	public:
		using _MyType				= ComparatorChecker;
		using Comparator			= _Comparator;
		using T						= _T;
		using U						= _U;
		using cinput_t				= traits::cinput<T>;
		using cinput_u				= traits::cinput<U>;
		using CompareSignature		= cmp_t(Comparator::*)(cinput_t, cinput_u) const noexcept;
		using CompareSignatureBool	= ll_bool_t(Comparator::*)(cinput_t, cinput_u) const noexcept;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_ignore_pointer_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(traits::is_valid_type_checker_ignore_pointer_v<U>,
			"type_checker<U> detected an invalid type!");
		static_assert(traits::is_valid_type_checker_v<Comparator>,
			"type_checker<Comparator> detected an invalid type!");
		static_assert(traits::is_valid_class_checker_v<Comparator>,
			"class_checker<Comparator> detected an invalid class type!");

		static_assert(traits::common::has_compare_function_v<Comparator, CompareSignature>,
			"Comparator::compare() const noexcept is required by default! Non const function is optional");
		static_assert(traits::common::has_compareBool_function_v<Comparator, CompareSignatureBool>,
			"Comparator::compare() const noexcept is required by default! Non const function is optional");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr ComparatorChecker() noexcept : Comparator() {}
		template<class... Args>
		constexpr ComparatorChecker(Args&&... args) noexcept
			: Comparator(std::forward<Args>(args)...) {}
		constexpr ~ComparatorChecker() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ComparatorChecker(const ComparatorChecker& other) noexcept
			: Comparator(std::forward<const Comparator&>(other)) {}
		constexpr ComparatorChecker& operator=(const ComparatorChecker& other) noexcept {
			Comparator::operator=(std::forward<const Comparator&>(other));
			return *this;
		}
		constexpr ComparatorChecker(ComparatorChecker&& other) noexcept
			: Comparator(std::forward<Comparator&&>(other)) {}
		constexpr ComparatorChecker& operator=(ComparatorChecker&& other) noexcept {
			Comparator::operator=(std::forward<Comparator&&>(other));
			return *this;
		}

		constexpr ComparatorChecker(const Comparator& other) noexcept
			: Comparator(std::forward<const Comparator&>(other)) {}
		constexpr ComparatorChecker& operator=(const Comparator& other) noexcept {
			Comparator::operator=(std::forward<const Comparator&>(other));
			return *this;
		}
		constexpr ComparatorChecker(Comparator&& other) noexcept
			: Comparator(std::forward<Comparator&&>(other)) {}
		constexpr ComparatorChecker& operator=(Comparator&& other) noexcept {
			Comparator::operator=(std::forward<Comparator&&>(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const ComparatorChecker* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator ComparatorChecker* () noexcept { return this; }

		#pragma endregion

	#pragma endregion
};

template<class _T, class _U = _T, ll_bool_t GET_DATA = llcpp::FALSE, class _Comparator = algorithm::CompareDefault<_T, _U>>
class CompareCluster : public algorithm::ComparatorChecker<_T, _U, _Comparator> {
	#pragma region Types
	public:
		using _MyType			= CompareCluster;
		using T					= _T;
		using U					= _U;
		using Comparator		= _Comparator;
		using ComparatorChecker	= algorithm::ComparatorChecker<T, U, Comparator>;
		using cinput_t			= ComparatorChecker::cinput_t;
		using cinput_u			= ComparatorChecker::cinput_u;
		using CompareResult		= CompareConditionalCmpT<T, U, GET_DATA>;
		using CompareResultBool	= CompareConditionalBool<T, U, GET_DATA>;
		using ArrayPair_t		= meta::ArrayPair<T>;
		using ArrayPair_u		= meta::ArrayPair<U>;
		using Array_t			= meta::Array<T>;
		using Array_u			= meta::Array<U>;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr CompareCluster() noexcept : ComparatorChecker() {}
		template<class... Args>
		constexpr CompareCluster(Args&&... args) noexcept
			: ComparatorChecker(std::forward<Args>(args)...) {}
		constexpr ~CompareCluster() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr CompareCluster(const CompareCluster& other) noexcept
			: ComparatorChecker(std::forward<const ComparatorChecker&>(other)) {}
		constexpr CompareCluster& operator=(const CompareCluster& other) noexcept {
			ComparatorChecker::operator=(std::forward<const ComparatorChecker&>(other));
			return *this;
		}
		constexpr CompareCluster(CompareCluster&& other) noexcept
			: ComparatorChecker(std::forward<ComparatorChecker&&>(other)) {}
		constexpr CompareCluster& operator=(CompareCluster&& other) noexcept {
			ComparatorChecker::operator=(std::forward<ComparatorChecker&&>(other));
			return *this;
		}

		constexpr CompareCluster(const ComparatorChecker& other) noexcept
			: ComparatorChecker(std::forward<const ComparatorChecker&>(other)) {}
		constexpr CompareCluster& operator=(const ComparatorChecker& other) noexcept {
			ComparatorChecker::operator=(std::forward<const ComparatorChecker&>(other));
			return *this;
		}
		constexpr CompareCluster(ComparatorChecker&& other) noexcept
			: ComparatorChecker(std::forward<ComparatorChecker&&>(other)) {}
		constexpr CompareCluster& operator=(ComparatorChecker&& other) noexcept {
			ComparatorChecker::operator=(std::forward<ComparatorChecker&&>(other));
			return *this;
		}

		constexpr CompareCluster(const Comparator& other) noexcept
			: ComparatorChecker(std::forward<const Comparator&>(other)) {}
		constexpr CompareCluster& operator=(const Comparator& other) noexcept {
			ComparatorChecker::operator=(std::forward<const Comparator&>(other));
			return *this;
		}
		constexpr CompareCluster(Comparator&& other) noexcept
			: ComparatorChecker(std::forward<Comparator&&>(other)) {}
		constexpr CompareCluster& operator=(Comparator&& other) noexcept {
			ComparatorChecker::operator=(std::forward<Comparator&&>(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const CompareCluster*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator CompareCluster*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region ComparatorOverrride
		__LL_NODISCARD__ constexpr cmp_t compare(cinput_t a, cinput_u b) const noexcept {
			return Comparator::compare(std::forward<cinput_t>(a), std::forward<cinput_u>(b));
		}
		__LL_NODISCARD__ constexpr cmp_t compare(cinput_t a, cinput_u b) noexcept {
			return Comparator::compare(std::forward<cinput_t>(a), std::forward<cinput_u>(b));
		}

		__LL_NODISCARD__ constexpr ll_bool_t compareBool(cinput_t a, cinput_u b) const noexcept {
			return Comparator::compareBool(std::forward<cinput_t>(a), std::forward<cinput_u>(b));
		}
		__LL_NODISCARD__ constexpr ll_bool_t compareBool(cinput_t a, cinput_u b) noexcept {
			return Comparator::compareBool(std::forward<cinput_t>(a), std::forward<cinput_u>(b));
		}

		#pragma endregion
		#pragma region Compare
		#pragma region CompareBase
	public:
		// Returns llcpp::FALSE if check not pass
		__LL_NODISCARD__ static constexpr ll_bool_t compareCheck(const T* _array1, const U* _array2, CompareResult& res) noexcept {
			if (static_cast<const void*>(_array1) == static_cast<const void*>(_array2)) {
				res = ZERO_CMP;
				return llcpp::LL_FALSE;
			}
			else if (!_array1 || !_array2) {
				res = ((!_array1) ? -1 : 1);
				return llcpp::LL_FALSE;
			}

			return llcpp::LL_TRUE;
		}
		__LL_NODISCARD__ constexpr CompareResult compare(const T* _array1, const U* _array2, len_t size) noexcept {
			CompareResult res(ZERO_CMP);
			if (!this->compareCheck(_array1, _array2, res)) return res;

			for (; size > ZERO_UI64; --size, ++_array1, ++_array2) {
				cmp_t result = this->compare(*_array1, *_array2);
				if (result != ZERO_CMP) {
					if constexpr (GET_DATA) 
						res = CompareResult(_array1, _array2, result);
					else res = result;
					break;
				}
			}

			return res;
		}
		__LL_NODISCARD__ constexpr CompareResult compare(const T* _array1, const U* _array2, len_t size) const noexcept {
			CompareResult res(ZERO_CMP);
			if (!this->compareCheck(_array1, _array2, res)) return res;

			for (; size > ZERO_UI64; --size, ++_array1, ++_array2) {
				cmp_t result = this->compare(*_array1, *_array2);
				if (result != ZERO_CMP) {
					if constexpr (GET_DATA)
						res = CompareResult(_array1, _array2, result);
					else res = result;
					break;
				}
			}

			return res;
		}
		__LL_NODISCARD__ constexpr CompareResultBool compareBool(const T* _array1, const U* _array2, len_t size) noexcept {
			CompareResultBool res(LL_FALSE);
			if (!this->compareCheck(_array1, _array2, res)) return res;

			for (; size > ZERO_UI64; --size, ++_array1, ++_array2) {
				ll_bool_t result = this->compareBool(*_array1, *_array2);
				if (!result) {
					if constexpr (GET_DATA) 
						res = CompareResultBool(_array1, _array2, result);
					else res = result;
					break;
				}
			}

			return res;
		}
		__LL_NODISCARD__ constexpr CompareResultBool compareBool(const T* _array1, const U* _array2, len_t size) const noexcept {
			CompareResultBool res(LL_FALSE);
			if (!this->compareCheck(_array1, _array2, res)) return res;

			for (; size > ZERO_UI64; --size, ++_array1, ++_array2) {
				ll_bool_t result = this->compareBool(*_array1, *_array2);
				if (!result) {
					if constexpr (GET_DATA)
						res = CompareResultBool(_array1, _array2, result);
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
	public:
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T* _array1, const len_t size1, const U* _array2, const len_t size2) noexcept {
			if (size1 != size2) return CompareResultBool(LL_FALSE);
			else return compareConversor<T, U, GET_DATA>(this->compare(_array1, _array2, size1));
		}
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T* _array1, const len_t size1, const ArrayPair_u& _array2) noexcept {
			return this->equals(_array1, size1, _array2.begin(), _array2.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T* _array1, const len_t size1, const Array_u& _array2) noexcept {
			return this->equals(_array1, size1, _array2.begin(), _array2.size());
		}

		#pragma endregion
		#pragma region Const
	public:
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T* _array1, const len_t size1, const U* _array2, const len_t size2) const noexcept {
			if (size1 != size2) return CompareResultBool(LL_FALSE);
			else return compareConversor<T, U, GET_DATA>(this->compare(_array1, _array2, size1));
		}
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T* _array1, const len_t size1, const ArrayPair_u& _array2) const noexcept {
			return this->equals(_array1, size1, _array2.begin(), _array2.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T* _array1, const len_t size1, const Array_u& _array2) const noexcept {
			return this->equals(_array1, size1, _array2.begin(), _array2.size());
		}

		#pragma endregion

		#pragma endregion
		#pragma region DefaultArray
		#pragma region NonConst
	public:
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&_array1)[N], const U* _array2, const len_t size2) noexcept {
			return this->equals(_array1, N, _array2, size2);
		}
		template<len_t N, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&_array1)[N], const U(&_array2)[N2]) noexcept {
			return this->equals(_array1, N, _array2, N2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&_array1)[N], const ArrayPair_u& _array2) noexcept {
			return this->equals(_array1, N, _array2.begin(), _array2.size());
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&_array1)[N], const Array_u& _array2) noexcept {
			return this->equals(_array1, N, _array2.begin(), _array2.size());
		}

		#pragma endregion
		#pragma region Const
	public:
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&_array1)[N], const U* _array2, const len_t size2) const noexcept {
			return this->equals(_array1, N, _array2, size2);
		}
		template<len_t N, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&_array1)[N], const U(&_array2)[N2]) const noexcept {
			return this->equals(_array1, N, _array2, N2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&_array1)[N], const ArrayPair_u& _array2) const noexcept {
			return this->equals(_array1, N, _array2.begin(), _array2.size());
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool equals(const T(&_array1)[N], const Array_u& _array2) const noexcept {
			return this->equals(_array1, N, _array2.begin(), _array2.size());
		}

		#pragma endregion

		#pragma endregion
		#pragma region ArrayPair
		#pragma region NoConst
	public:
		__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& _array1, const U* _array2, const len_t size2) noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2, size2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& _array1, const U(&_array2)[N]) noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& _array1, const ArrayPair_u& _array2) noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2.begin(), _array2.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& _array1, const Array_u& _array2) noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2.begin(), _array2.size());
		}

		#pragma endregion
		#pragma region Const
	public:
		__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& _array1, const U* _array2, const len_t size2) const noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2, size2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& _array1, const U(&_array2)[N]) const noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& _array1, const ArrayPair_u& _array2) const noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2.begin(), _array2.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool equals(const ArrayPair_t& _array1, const Array_u& _array2) const noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2.begin(), _array2.size());
		}

		#pragma endregion

		#pragma endregion
		#pragma region Array
		#pragma region NoConst
	public:
		__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& _array1, const U* _array2, const len_t size2) noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2, size2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& _array1, const U(&_array2)[N]) noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& _array1, const ArrayPair_u& _array2) noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2.begin(), _array2.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& _array1, const Array_u& _array2) noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2.begin(), _array2.size());
		}

		#pragma endregion
		#pragma region Const
	public:
		__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& _array1, const U* _array2, const len_t size2) const noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2, size2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& _array1, const U(&_array2)[N]) const noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& _array1, const ArrayPair_u& _array2) const noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2.begin(), _array2.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool equals(const Array_t& _array1, const Array_u& _array2) const noexcept {
			return this->equals(_array1.begin(), _array1.size(), _array2.begin(), _array2.size());
		}

		#pragma endregion

		#pragma endregion

		#pragma endregion
		#pragma endregion
		#pragma region StartsWith
	public:
		// Returns llcpp::FALSE if check not pass
		__LL_NODISCARD__ constexpr ll_bool_t startsWithImmpementationCheck(const T* _array, const U* needle, CompareResultBool& res) const noexcept {
			if (static_cast<const void*>(_array) == static_cast<const void*>(needle)) {
				res = llcpp::LL_TRUE;
				return llcpp::LL_FALSE;
			}
			else if (!_array || !needle) {
				res = llcpp::LL_FALSE;
				return llcpp::LL_FALSE;
			}
			return llcpp::LL_TRUE;
		}
		// _array size needs to be bigger or equal to needle
		__LL_NODISCARD__ constexpr CompareResultBool startsWithImmpementation(const T* _array, const U* needle, len_t size) noexcept {
			CompareResultBool res(LL_TRUE);
			if (!this->startsWithImmpementationCheck(_array, needle, res)) return res;

			for (; 0 < size; --size, ++_array, ++needle) {
				ll_bool_t result = this->compareBool(*_array, *needle);
				if (!result) {
					if constexpr (GET_DATA)
						res = CompareResultBool(_array, needle, result);
					else res = result;
					break;
				}
			}
			return res;
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWithImmpementation(const T* _array, const U* needle, len_t size) const noexcept {
			CompareResultBool res(LL_TRUE);
			if (!this->startsWithImmpementationCheck(_array, needle, res)) return res;

			for (; 0 < size; --size, ++_array, ++needle) {
				ll_bool_t result = this->compareBool(*_array, *needle);
				if (!result) {
					if constexpr (GET_DATA)
						res = CompareResultBool(_array, needle, result);
					else res = result;
					break;
				}
			}
			return res;
		}

		#pragma region Ptr
		#pragma region NoConst
	public:
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* _array, const len_t size1, const U* needle, const len_t size2) noexcept {
			if (size1 < size2 || (size1 != size2 && size2 == ZERO_UI64)) return CompareResultBool(LL_FALSE);
			else return this->startsWithImmpementation(_array, needle, size2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* _array, const len_t size1, const U(&needle)[N]) noexcept {
			return this->startsWith(_array, size1, needle, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* _array, const len_t size1, const ArrayPair_u& needle) noexcept {
			return this->startsWith(_array, size1, needle.begin(), needle.len());
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* _array, const len_t size1, const Array_u& needle) noexcept {
			return this->startsWith(_array, size1, needle.begin(), needle.len());
		}

		#pragma endregion
		#pragma region Const
	public:
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* _array, const len_t size1, const U* needle, const len_t size2) const noexcept {
			if (size1 < size2 || (size1 != size2 && size2 == ZERO_UI64)) return CompareResultBool(LL_FALSE);
			else return this->startsWithImmpementation(_array, needle, size2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* _array, const len_t size1, const U(&needle)[N]) const noexcept {
			return this->startsWith(_array, size1, needle, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* _array, const len_t size1, const ArrayPair_u& needle) const noexcept {
			return this->startsWith(_array, size1, needle.begin(), needle.len());
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T* _array, const len_t size1, const Array_u& needle) const noexcept {
			return this->startsWith(_array, size1, needle.begin(), needle.len());
		}

		#pragma endregion

		#pragma endregion
		#pragma region DefaultArray
		#pragma region NoConst
	public:
		template<len_t N, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&_array)[N], const U(&needle)[N2]) noexcept {
			return this->startsWith(_array, N, needle, N2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&_array)[N], const U* needle, const len_t size2) noexcept {
			return this->startsWith(_array, N, needle, size2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&_array)[N], const ArrayPair_u& needle) noexcept {
			return this->startsWith(_array, N, needle.begin(), needle.len());
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&_array)[N], const Array_u& needle) noexcept {
			return this->startsWith(_array, N, needle.begin(), needle.len());
		}

		#pragma endregion
		#pragma region Const
	public:
		template<len_t N, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&_array)[N], const U(&needle)[N2]) const noexcept {
			return this->startsWith(_array, N, needle, N2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&_array)[N], const U* needle, const len_t size2) const noexcept {
			return this->startsWith(_array, N, needle, size2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&_array)[N], const ArrayPair_u& needle) const noexcept {
			return this->startsWith(_array, N, needle.begin(), needle.len());
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const T(&_array)[N], const Array_u& needle) const noexcept {
			return this->startsWith(_array, N, needle.begin(), needle.len());
		}

		#pragma endregion

		#pragma endregion
		#pragma region ArrayPair
		#pragma region NoConst
	public:
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& _array, const U* needle, len_t size) noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle, size);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& _array, const U(&needle)[N]) noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& _array, const ArrayPair_u& needle) noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& _array, const Array_u& needle) noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}

		#pragma endregion
		#pragma region Const
	public:
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& _array, const U* needle, len_t size) const noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle, size);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& _array, const U(&needle)[N]) const noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& _array, const ArrayPair_u& needle) const noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const ArrayPair_t& _array, const Array_u& needle) const noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}

		#pragma endregion

		#pragma endregion
		#pragma region Array
		#pragma region NoConst
	public:
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& _array, const U* needle, len_t size) noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle, size);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& _array, const U(&needle)[N]) noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& _array, const ArrayPair_u& needle) noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& _array, const Array_u& needle) noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}

		#pragma endregion
		#pragma region Const
	public:
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& _array, const U* needle, len_t size) const noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle, size);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& _array, const U(&needle)[N]) const noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& _array, const ArrayPair_u& needle) const noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool startsWith(const Array_t& _array, const Array_u& needle) const noexcept {
			return this->startsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}

		#pragma endregion

		#pragma endregion

		#pragma endregion
		#pragma region EndsWith
		#pragma region Ptr
		#pragma region NoConst
	public:
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* _array, const len_t size1, const U* needle, const len_t size2) noexcept {
			if (size1 < size2 || (size1 != size2 && size2 == ZERO_UI64)) return CompareResultBool(LL_FALSE);
			else return this->startsWithImmpementation((_array + size1) - size2, needle, size2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* _array, const len_t size1, const U(&needle)[N]) noexcept {
			return this->endsWith(_array, size1, needle, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* _array, const len_t size1, const ArrayPair_u& needle) noexcept {
			return this->endsWith(_array, size1, needle.begin(), needle.len());
		}
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* _array, const len_t size1, const Array_u& needle) noexcept {
			return this->endsWith(_array, size1, needle.begin(), needle.len());
		}

		#pragma endregion
		#pragma region Const
	public:
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* _array, const len_t size1, const U* needle, const len_t size2) const noexcept {
			if (size1 < size2 || (size1 != size2 && size2 == ZERO_UI64)) return CompareResultBool(LL_FALSE);
			else return this->startsWithImmpementation((_array + size1) - size2, needle, size2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* _array, const len_t size1, const U(&needle)[N]) const noexcept {
			return this->endsWith(_array, size1, needle, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* _array, const len_t size1, const ArrayPair_u& needle) const noexcept {
			return this->endsWith(_array, size1, needle.begin(), needle.len());
		}
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T* _array, const len_t size1, const Array_u& needle) const noexcept {
			return this->endsWith(_array, size1, needle.begin(), needle.len());
		}

		#pragma endregion

		#pragma endregion
		#pragma region DefaultArray
		#pragma region NoConst
	public:
		template<len_t N, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&_array)[N], const U(&needle)[N2]) noexcept {
			return this->endsWith(_array, N, needle, N2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&_array)[N], const U* needle, const len_t size2) noexcept {
			return this->endsWith(_array, N, needle, size2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&_array)[N], const ArrayPair_u& needle) noexcept {
			return this->endsWith(_array, N, needle.begin(), needle.len());
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&_array)[N], const Array_u& needle) noexcept {
			return this->endsWith(_array, N, needle.begin(), needle.len());
		}

		#pragma endregion
		#pragma region Const
	public:
		template<len_t N, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&_array)[N], const U(&needle)[N2]) const noexcept {
			return this->endsWith(_array, N, needle, N2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&_array)[N], const U* needle, const len_t size2) const noexcept {
			return this->endsWith(_array, N, needle, size2);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&_array)[N], const ArrayPair_u& needle) const noexcept {
			return this->endsWith(_array, N, needle.begin(), needle.len());
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const T(&_array)[N], const Array_u& needle) const noexcept {
			return this->endsWith(_array, N, needle.begin(), needle.len());
		}

		#pragma endregion

		#pragma endregion
		#pragma region ArrayPair
		#pragma region NoConst
	public:
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& _array, const U* needle, len_t size) noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle, size);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& _array, const U(&needle)[N]) noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& _array, const ArrayPair_u& needle) noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& _array, const Array_u& needle) noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}

		#pragma endregion
		#pragma region Const
	public:
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& _array, const U* needle, len_t size) const noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle, size);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& _array, const U(&needle)[N]) const noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& _array, const ArrayPair_u& needle) const noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const ArrayPair_t& _array, const Array_u& needle) const noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}

		#pragma endregion

		#pragma endregion
		#pragma region Array
		#pragma region NoConst
	public:
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& _array, const U* needle, len_t size) noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle, size);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& _array, const U(&needle)[N]) noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& _array, const ArrayPair_u& needle) noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& _array, const Array_u& needle) noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}

		#pragma endregion
		#pragma region Const
	public:
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& _array, const U* needle, len_t size) const noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle, size);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& _array, const U(&needle)[N]) const noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle, N);
		}
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& _array, const ArrayPair_u& needle) const noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}
		__LL_NODISCARD__ constexpr CompareResultBool endsWith(const Array_t& _array, const Array_u& needle) const noexcept {
			return this->endsWith(_array.begin(), _array.size(), needle.begin(), needle.size());
		}

		#pragma endregion

		#pragma endregion

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

template<class _T, class _U = _T, ll_bool_t POSITION = llcpp::FALSE, class _Comparator = algorithm::CompareDefault<_T, _U>>
struct FindersCluster : public algorithm::ComparatorChecker<_T, _U, _Comparator> {
	#pragma region Types
	public:
		using _MyType			= FindersCluster;
		using T					= _T;
		using U					= _U;
		using Comparator		= _Comparator;
		using ComparatorChecker	= algorithm::ComparatorChecker<T, U, Comparator>;
		using cinput_t			= ComparatorChecker::cinput_t;
		using cinput_u			= ComparatorChecker::cinput_u;
		using FindResult		= std::conditional_t<POSITION, len_t, const T*>;
		using ArrayPair_t		= meta::ArrayPair<T>;
		using ArrayPair_u		= meta::ArrayPair<U>;
		using Array_t			= meta::Array<T>;
		using Array_u			= meta::Array<U>;

	#pragma endregion
	#pragma region Asserts
	public:

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr FindersCluster() noexcept : ComparatorChecker() {}
		template<class... Args>
		constexpr FindersCluster(Args&&... args) noexcept
			: ComparatorChecker(std::forward<Args>(args)...) {}
		constexpr ~FindersCluster() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr FindersCluster(const FindersCluster& other) noexcept
			: ComparatorChecker(std::forward<const ComparatorChecker&>(other)) {}
		constexpr FindersCluster& operator=(const FindersCluster& other) noexcept {
			ComparatorChecker::operator=(std::forward<const ComparatorChecker&>(other));
			return *this;
		}
		constexpr FindersCluster(FindersCluster&& other) noexcept
			: ComparatorChecker(std::forward<ComparatorChecker&&>(other)) {}
		constexpr FindersCluster& operator=(FindersCluster&& other) noexcept {
			ComparatorChecker::operator=(std::forward<ComparatorChecker&&>(other));
			return *this;
		}

		constexpr FindersCluster(const ComparatorChecker& other) noexcept
			: ComparatorChecker(std::forward<const ComparatorChecker&>(other)) {}
		constexpr FindersCluster& operator=(const ComparatorChecker& other) noexcept {
			ComparatorChecker::operator=(std::forward<const ComparatorChecker&>(other));
			return *this;
		}
		constexpr FindersCluster(ComparatorChecker&& other) noexcept
			: ComparatorChecker(std::forward<ComparatorChecker&&>(other)) {}
		constexpr FindersCluster& operator=(ComparatorChecker&& other) noexcept {
			ComparatorChecker::operator=(std::forward<ComparatorChecker&&>(other));
			return *this;
		}

		constexpr FindersCluster(const Comparator& other) noexcept
			: ComparatorChecker(std::forward<const Comparator&>(other)) {}
		constexpr FindersCluster& operator=(const Comparator& other) noexcept {
			ComparatorChecker::operator=(std::forward<const Comparator&>(other));
			return *this;
		}
		constexpr FindersCluster(Comparator&& other) noexcept
			: ComparatorChecker(std::forward<Comparator&&>(other)) {}
		constexpr FindersCluster& operator=(Comparator&& other) noexcept {
			ComparatorChecker::operator=(std::forward<Comparator&&>(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const FindersCluster*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator FindersCluster*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region ComparatorOverrride
		__LL_NODISCARD__ constexpr cmp_t compare(cinput_t a, cinput_u b) const noexcept {
			return Comparator::compare(std::forward<cinput_t>(a), std::forward<cinput_u>(b));
		}
		__LL_NODISCARD__ constexpr cmp_t compare(cinput_t a, cinput_u b) noexcept {
			return Comparator::compare(std::forward<cinput_t>(a), std::forward<cinput_u>(b));
		}

		__LL_NODISCARD__ constexpr ll_bool_t compareBool(cinput_t a, cinput_u b) const noexcept {
			return Comparator::compareBool(std::forward<cinput_t>(a), std::forward<cinput_u>(b));
		}
		__LL_NODISCARD__ constexpr ll_bool_t compareBool(cinput_t a, cinput_u b) noexcept {
			return Comparator::compareBool(std::forward<cinput_t>(a), std::forward<cinput_u>(b));
		}

		#pragma endregion
		#pragma region Find
		#pragma region Base
	public:
		__LL_NODISCARD__ static constexpr ll_bool_t findCheck(const T* begin, const T* end, FindResult& result) noexcept {
			if constexpr (POSITION) result = algorithm::npos;
			else result = end;
			if (!begin || !end || end <= begin) return llcpp::LL_FALSE;
			else return llcpp::LL_TRUE;
		}
		__LL_NODISCARD__ constexpr FindResult find(const T* begin, const T* end, cinput_u object) noexcept {
			FindResult result{};
			if (!this->findCheck(begin, end, result)) return result;

			for (const T* data = begin; data < end; ++data)
				if (this->compareBool(*data, object)) {
					if constexpr (POSITION) result = data - begin;
					else result = data;
					break;
				}
			return result;
		}
		__LL_NODISCARD__ constexpr FindResult find(const T* begin, const T* end, cinput_u object) const noexcept {
			FindResult result{};
			if (!this->findCheck(begin, end, result)) return result;

			for (const T* data = begin; data < end; ++data)
				if (this->compareBool(*data, object)) {
					if constexpr (POSITION) result = data - begin;
					else result = data;
					break;
				}
			return result;
		}

		#pragma endregion
		#pragma region NoConst
	public:
		template<len_t N>
		__LL_NODISCARD__ constexpr FindResult find(const T(&_array)[N], cinput_u object) noexcept {
			return this->find(_array, _array + N, object);
		}
		__LL_NODISCARD__ constexpr FindResult find(const ArrayPair_t& _array, cinput_u object) noexcept {
			return this->find(_array.begin(), _array.end(), object);
		}
		__LL_NODISCARD__ constexpr FindResult find(const Array_t& _array, cinput_u object) noexcept {
			return this->find(_array.begin(), _array.end(), object);
		}

		#pragma endregion
		#pragma region Const
	public:
		template<len_t N>
		__LL_NODISCARD__ constexpr FindResult find(const T(&data)[N], cinput_u object) const noexcept {
			return this->find(data, data + N, object);
		}
		__LL_NODISCARD__ constexpr FindResult find(const ArrayPair_t& _array, cinput_u object) const noexcept {
			return this->find(_array.begin(), _array.end(), object);
		}
		__LL_NODISCARD__ constexpr FindResult find(const Array_t& _array, cinput_u object) const noexcept {
			return this->find(_array.begin(), _array.end(), object);
		}

		#pragma endregion

		#pragma endregion
		#pragma region rFind
		#pragma region Base
		__LL_NODISCARD__ constexpr FindResult rfind(const T* begin, const T* end, cinput_u object) noexcept {
			FindResult result{};
			if (!this->findCheck(begin, end, result)) return result;

			for (const T* data = end - 1; data > begin; --data)
				if (this->compareBool(*data, object)) {
					if constexpr (POSITION) return data - begin;
					else return data;
				}

			if constexpr (POSITION) return this->compareBool(*begin, object) ? 0 : npos;
			else return this->compareBool(*begin, object) ? begin : end;
		}
		__LL_NODISCARD__ constexpr FindResult rfind(const T* begin, const T* end, cinput_u object) const noexcept {
			FindResult result{};
			if (!this->findCheck(begin, end, result)) return result;

			for (const T* data = end - 1; data > begin; --data)
				if (this->compareBool(*data, object)) {
					if constexpr (POSITION) return data - begin;
					else return data;
				}

			if constexpr (POSITION) return this->compareBool(*begin, object) ? 0 : npos;
			else return this->compareBool(*begin, object) ? begin : end;
		}

		#pragma endregion
		#pragma region NoConst
		template<len_t N>
		__LL_NODISCARD__ constexpr FindResult rfind(const T (&data)[N], cinput_u object) noexcept {
			return this->rfind(data, data + N, object);
		}
		__LL_NODISCARD__ constexpr FindResult rfind(const ArrayPair_t& _array, cinput_u object) noexcept {
			return this->rfind(_array.begin(), _array.end(), object);
		}
		__LL_NODISCARD__ constexpr FindResult rfind(const Array_t& _array, cinput_u object) noexcept {
			return this->rfind(_array.begin(), _array.end(), object);
		}

		#pragma endregion
		#pragma region Const
		template<len_t N>
		__LL_NODISCARD__ constexpr FindResult rfind(const T(&data)[N], cinput_u object) const noexcept {
			return this->rfind(data, data + N, object);
		}
		__LL_NODISCARD__ constexpr FindResult rfind(const ArrayPair_t& _array, cinput_u object) const noexcept {
			return this->rfind(_array.begin(), _array.end(), object);
		}
		__LL_NODISCARD__ constexpr FindResult rfind(const Array_t& _array, cinput_u object) const noexcept {
			return this->rfind(_array.begin(), _array.end(), object);
		}

		#pragma endregion
		#pragma endregion
		#pragma region Contains
		#pragma region NoConst
		__LL_NODISCARD__ constexpr ll_bool_t contains(const T* begin, const T* end, cinput_u object) noexcept {
			if constexpr (POSITION) return this->find(begin, end, object) != npos;
			else return this->find(begin, end, object) != end;
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr ll_bool_t contains(const T(&data)[N], cinput_u object) noexcept {
			return this->contains(data, data + N, object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains(const ArrayPair_t& _array, cinput_u object) noexcept {
			return this->contains(_array.begin(), _array.end(), object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains(const Array_t& _array, cinput_u object) noexcept {
			return this->contains(_array.begin(), _array.end(), object);
		}

		#pragma endregion
		#pragma region Const
		__LL_NODISCARD__ constexpr ll_bool_t contains(const T* begin, const T* end, cinput_u object) const noexcept {
			if constexpr (POSITION) return this->find(begin, end, object) != npos;
			else return this->find(begin, end, object) != end;
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr ll_bool_t contains(const T(&data)[N], cinput_u object) const noexcept {
			return this->contains(data, data + N, object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains(const ArrayPair_t& _array, cinput_u object) const noexcept {
			return this->contains(_array.begin(), _array.end(), object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains(const Array_t& _array, cinput_u object) const noexcept {
			return this->contains(_array.begin(), _array.end(), object);
		}

		#pragma endregion

		#pragma endregion
		#pragma region Other
		#pragma region All
		#pragma region NoConst
		__LL_NODISCARD__ constexpr ll_bool_t all(const T* begin, const T* end, cinput_u object) noexcept {
			if (!begin || !end || end <= begin) return llcpp::LL_FALSE;

			for (; begin < end; ++begin)
				if (!this->compareBool(*begin, object))
					return llcpp::LL_FALSE;
			return llcpp::LL_TRUE;
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr ll_bool_t all(const T (&data)[N], cinput_u object) noexcept {
			return this->all(data, data + N, object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t all(const ArrayPair_t& _array, cinput_u object) noexcept {
			return this->all(_array.begin(), _array.end(), object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t all(const Array_t& _array, cinput_u object) noexcept {
			return this->all(_array.begin(), _array.end(), object);
		}

		#pragma endregion
		#pragma region Const
		__LL_NODISCARD__ constexpr ll_bool_t all(const T* begin, const T* end, cinput_u object) const noexcept {
			if (!begin || !end || end <= begin) return llcpp::LL_FALSE;

			for (; begin < end; ++begin)
				if (!this->compareBool(*begin, object))
					return llcpp::LL_FALSE;
			return llcpp::LL_TRUE;
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr ll_bool_t all(const T (&data)[N], cinput_u object) const noexcept {
			return this->all(data, data + N, object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t all(const ArrayPair_t& _array, cinput_u object) const noexcept {
			return this->all(_array.begin(), _array.end(), object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t all(const Array_t& _array, cinput_u object) const noexcept {
			return this->all(_array.begin(), _array.end(), object);
		}

		#pragma endregion

		#pragma endregion
		#pragma region Any
		#pragma region NoConst
		__LL_NODISCARD__ constexpr ll_bool_t any(const T* begin, const T* end, cinput_u object) noexcept {
			return this->contains(begin, end, object);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr ll_bool_t any(const T (&data)[N], cinput_u object) noexcept {
			return this->any(data, data + N, object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any(const ArrayPair_t& _array, cinput_u object) noexcept {
			return this->any(_array.begin(), _array.end(), object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any(const Array_t& _array, cinput_u object) noexcept {
			return this->any(_array.begin(), _array.end(), object);
		}

		#pragma endregion
		#pragma region Const
		__LL_NODISCARD__ constexpr ll_bool_t any(const T* begin, const T* end, cinput_u object) const noexcept {
			return this->contains(begin, end, object);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr ll_bool_t any(const T (&data)[N], cinput_u object) const noexcept {
			return this->any(data, data + N, object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any(const ArrayPair_t& _array, cinput_u object) const noexcept {
			return this->any(_array.begin(), _array.end(), object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any(const Array_t& _array, cinput_u object) const noexcept {
			return this->any(_array.begin(), _array.end(), object);
		}

		#pragma endregion

		#pragma endregion
		#pragma region None
		#pragma region NoConst
		__LL_NODISCARD__ constexpr ll_bool_t none(const T* begin, const T* end, cinput_u object) noexcept {
			return !this->contains(begin, end, object);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr ll_bool_t none(const T (&data)[N], cinput_u object) noexcept {
			return this->none(data, data + N, object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none(const ArrayPair_t& _array, cinput_u object) noexcept {
			return this->none(_array.begin(), _array.end(), object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none(const Array_t& _array, cinput_u object) noexcept {
			return this->none(_array.begin(), _array.end(), object);
		}

		#pragma endregion
		#pragma region Const
		__LL_NODISCARD__ constexpr ll_bool_t none(const T* begin, const T* end, cinput_u object) const noexcept {
			return !this->contains(begin, end, object);
		}
		template<len_t N>
		__LL_NODISCARD__ constexpr ll_bool_t none(const T (&data)[N], cinput_u object) const noexcept {
			return this->none(data, data + N, object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none(const ArrayPair_t& _array, cinput_u object) const noexcept {
			return this->none(_array.begin(), _array.end(), object);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none(const Array_t& _array, cinput_u object) const noexcept {
			return this->none(_array.begin(), _array.end(), object);
		}

		#pragma endregion

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
		//		cmp_t res = this->compare(begin[mid], object);
		//		if (res == ZERO_CMP) return begin + mid;
		//		else if (res > 0) high = mid;
		//		else low = mid + 1;
		//	}
		//	return end;
		//}

		#pragma region Proxy
		//__LL_NODISCARD__ constexpr len_t binarysearch_pos(const T* begin, const T* end, cinput_u object) noexcept {
		//	const T* pos = this->binarysearch(begin, end, object);
		//	return (pos != end) ? pos - begin : npos;
		//}
		//template<len_t N>
		//__LL_NODISCARD__ constexpr const T* binarysearch(const T (&data)[N], cinput_u object) noexcept {
		//	if (!data || N == ZERO_UI64) return data + N;
		//	return this->binarysearch(data, data + N, object);
		//}
		//template<len_t N>
		//__LL_NODISCARD__ constexpr len_t binarysearch_pos(const T (&data)[N], cinput_u object) noexcept {
		//	if (!data || N == ZERO_UI64) return data + N;
		//	return this->binarysearch_pos(data, data + N, object);
		//}
		//__LL_NODISCARD__ constexpr const T* binarysearch(const ArrayPair_t& _array, cinput_u object) noexcept {
		//	return this->binarysearch(_array.begin(), _array.end(), object);
		//}
		//__LL_NODISCARD__ constexpr len_t binarysearch_pos(const ArrayPair_t& _array, cinput_u object) noexcept {
		//	return this->binarysearch_pos(_array.begin(), _array.end(), object);
		//}

		#pragma endregion
		#pragma endregion

		#pragma endregion

	#pragma endregion
};

template<class _T, class _Manipulator = algorithm::ManipulatorDefault<_T>>
class DataManipulatorCluster : public _Manipulator {
	#pragma region Types
	public:
		using _MyType				= DataManipulatorCluster;
		using T						= _T;
		using Manipulator			= _Manipulator;
		using cinput_t				= traits::cinput<T>;
		using Array_t				= meta::Array<T>;
		using SwapSignature			= void(Manipulator::*)(T&, T&) const noexcept;
		using MoveSignature			= void(Manipulator::*)(T&, T&) const noexcept;
		template<class W>
		using CopyExtraSignature	= void(*)(T&, W) noexcept;
		template<class U>
		using MoveExtraSignature	= void(*)(T&, U&) noexcept;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<T>, "Const type is forbidden!");

		static_assert(!std::is_reference_v<Manipulator>, "Manipulator reference type is forbidden!");
		static_assert(!std::is_const_v<Manipulator>, "Manipulator const type is forbidden!");
		static_assert(std::is_class_v<Manipulator>, "Manipulator needs to be a class!");
		static_assert(std::is_nothrow_constructible_v<Manipulator>, "Manipulator needs a noexcept constructor!");
		static_assert(std::is_nothrow_destructible_v<Manipulator>, "Manipulator needs a noexcept destructor!");
		static_assert(std::is_copy_constructible_v<Manipulator>, "Manipulator needs a noexcept copy constructor!");
		static_assert(std::is_copy_assignable_v<Manipulator>, "Manipulator needs a noexcept copy asignable!");
		static_assert(std::is_move_constructible_v<Manipulator>, "Manipulator needs a noexcept move constructor!");
		static_assert(std::is_move_assignable_v<Manipulator>, "Manipulator needs a noexcept move asignable!");

		static_assert(traits::common::has_swap_function_v<Manipulator, SwapSignature>,
			"Manipulator::swap() const noexcept is required by default! Non const function is optional");
		static_assert(traits::common::has_swap_function_v<Manipulator, MoveSignature>,
			"Manipulator::move() const noexcept is required by default! Non const function is optional");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr DataManipulatorCluster() noexcept : Manipulator() {}
		template<class... Args>
		constexpr DataManipulatorCluster(Args&&... args) noexcept
			: Manipulator(std::forward<Args>(args)...) {}
		constexpr ~DataManipulatorCluster() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		DataManipulatorCluster(const DataManipulatorCluster& other) noexcept
			: Manipulator(std::forward<const Manipulator&>(other)) {}
		DataManipulatorCluster& operator=(const DataManipulatorCluster& other) noexcept {
			Manipulator::operator=(std::forward<const Manipulator&>(other));
			return *this;
		}
		DataManipulatorCluster(DataManipulatorCluster&& other) noexcept
			: Manipulator(std::forward<Manipulator&&>(other)) {}
		DataManipulatorCluster& operator=(DataManipulatorCluster&& other) noexcept {
			Manipulator::operator=(std::forward<Manipulator&&>(other));
			return *this;
		}

		DataManipulatorCluster(const Manipulator& other) noexcept
			: Manipulator(std::forward<const Manipulator&>(other)) {}
		DataManipulatorCluster& operator=(const Manipulator& other) noexcept {
			Manipulator::operator=(std::forward<const Manipulator&>(other));
			return *this;
		}
		DataManipulatorCluster(Manipulator&& other) noexcept
			: Manipulator(std::forward<Manipulator&&>(other)) {}
		DataManipulatorCluster& operator=(Manipulator&& other) noexcept {
			Manipulator::operator=(std::forward<Manipulator&&>(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const DataManipulatorCluster*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator DataManipulatorCluster*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Reverse
	public:
		#pragma region Base
		constexpr void reverse(T* _array, T* end) noexcept {
			for (; _array < end; ++_array, --end)
				this->swap(*_array, *end);
		}
		constexpr void reverse(T* _array, T* end) const noexcept {
			for (; _array < end; ++_array, --end)
				this->swap(*_array, *end);
		}

		constexpr ll_bool_t reverse_s(T* _array, T* end) noexcept {
			if (!_array || !end || end <= _array) return llcpp::LL_FALSE;
			this->reverse(_array, end);
			return llcpp::LL_TRUE;
		}
		constexpr ll_bool_t reverse_s(T* _array, T* end) const noexcept {
			if (!_array || !end || end <= _array) return llcpp::LL_FALSE;
			this->reverse(_array, end);
			return llcpp::LL_TRUE;
		}

		#pragma endregion
		#pragma region NoConst
		template<len_t N>
		constexpr void reverse(T(&_array)[N]) noexcept {
			this->reverse(_array, _array + N - 1);
		}
		constexpr void reverse(Array_t& _array) noexcept {
			this->reverse(_array.begin(), _array.end());
		}
		template<len_t N>
		constexpr ll_bool_t reverse_s(T(&_array)[N]) noexcept {
			return this->reverse_s(_array, _array + N - 1);
		}
		constexpr ll_bool_t reverse_s(Array_t& _array) noexcept {
			return this->reverse_s(_array.begin(), _array.end());
		}

		#pragma endregion
		#pragma region Const
		template<len_t N>
		constexpr void reverse(T(&_array)[N]) const noexcept {
			this->reverse(_array, _array + N - 1);
		}
		constexpr void reverse(Array_t& _array) const noexcept {
			this->reverse(_array.begin(), _array.end());
		}
		template<len_t N>
		constexpr ll_bool_t reverse_s(T(&_array)[N]) const noexcept {
			return this->reverse_s(_array, _array + N - 1);
		}
		constexpr ll_bool_t reverse_s(Array_t& _array) const noexcept {
			return this->reverse_s(_array.begin(), _array.end());
		}

		#pragma endregion

		#pragma endregion
		#pragma region Fillers
	public:
		#pragma region Base
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void fill(T* dst, T* end, W object, FunctionManipulator&& man) const noexcept {
			using CopyFunction = void(FunctionManipulator::*)(T&, W) const noexcept;
			static_assert(traits::common::has_copy_function_v<FunctionManipulator, CopyFunction>,
				"FunctionManipulator::copy() const noexcept is required!");

			for (; dst < end; ++dst)
				man.copy(*dst, object);
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void fill(T* dst, T* end, W object) const noexcept {
			static_assert(std::is_nothrow_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept constructor!");
			static_assert(std::is_nothrow_destructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept destructor!");
			static_assert(std::is_copy_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept copy constructor!");
			static_assert(std::is_copy_assignable_v<FunctionManipulator>, "FunctionManipulator needs a noexcept copy asignable!");
			static_assert(std::is_move_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept move constructor!");
			static_assert(std::is_move_assignable_v<FunctionManipulator>, "FunctionManipulator needs a noexcept move asignable!");
			this->fill<U, W, FunctionManipulator>(dst, end, object, FunctionManipulator());
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr void fill(T* dst, T* end, W object) const noexcept {
			for (; dst < end; ++dst)
				COPY(*dst, object);
		}

		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t fill_s(T* dst, T* end, W object, FunctionManipulator&& man) const noexcept {
			if (!dst || !end || end <= dst) return llcpp::LL_FALSE;
			this->fill<U, W, FunctionManipulator>(dst, end, object, std::forward<FunctionManipulator>(man));
			return llcpp::LL_TRUE;
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t fill_s(T* dst, T* end, W object) const noexcept {
			if (!dst || !end || end <= dst) return llcpp::LL_FALSE;
			this->fill<U, W, FunctionManipulator>(dst, end, object);
			return llcpp::LL_TRUE;
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr ll_bool_t fill_s(T* dst, T* end, W object) const noexcept {
			if (!dst || !end || end <= dst) return llcpp::LL_FALSE;
			this->fill<U, W, COPY>(dst, end, object);
			return llcpp::LL_TRUE;
		}

		#pragma endregion
		#pragma region FunctionManipulatorAsParameter
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void fill(Array_t& dst, W object, FunctionManipulator&& man) const noexcept {
			this->fill<U, W, FunctionManipulator>(dst.begin(), dst.end(), object, std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void fill(T(&dst)[N], W object, FunctionManipulator&& man) const noexcept {
			this->fill<U, W, FunctionManipulator>(dst, dst + N - 1, object, std::forward<FunctionManipulator>(man));
		}

		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t fill_s(Array_t& dst, W object, FunctionManipulator&& man) const noexcept {
			return this->fill_s<U, W, FunctionManipulator>(dst.begin(), dst.end(), object, std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t fill_s(T(&dst)[N], W object, FunctionManipulator&& man) const noexcept {
			return this->fill_s<U, W, FunctionManipulator>(dst, dst + N - 1, object, std::forward<FunctionManipulator>(man));
		}

		#pragma endregion
		#pragma region FunctionManipulatorCreate
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void fill(Array_t& dst, W object) const noexcept {
			this->fill<U, W, FunctionManipulator>(dst.begin(), dst.end(), object);
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void fill(T(&dst)[N], W object) const noexcept {
			this->fill<U, W, FunctionManipulator>(dst, dst + N, object);
		}

		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t fill_s(Array_t& dst, W object) const noexcept {
			return this->fill_s<U, W, FunctionManipulator>(dst.begin(), dst.end(), object);
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t fill_s(T(&dst)[N], W object) const noexcept {
			return this->fill_s<U, W, FunctionManipulator>(dst, dst + N, object);
		}

		#pragma endregion
		#pragma region StaticFunction
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr void fill(Array_t& dst, W object) const noexcept {
			this->fill<U, W, COPY>(dst.begin(), dst.end(), object);
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>, len_t N>
		constexpr void fill(T(&dst)[N], W object) const noexcept {
			this->fill<U, W, COPY>(dst, dst + N, object);
		}

		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr void fill_s(Array_t& dst, W object) const noexcept {
			return this->fill_s<U, W, COPY>(dst.begin(), dst.end(), object);
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>, len_t N>
		constexpr void fill_s(T(&dst)[N], W object) const noexcept {
			return this->fill_s<U, W, COPY>(dst, dst + N, object);
		}

		#pragma endregion

		#pragma endregion
		#pragma region Copy
	public:
		#pragma region Base
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void copy(const U* src, T* dst, len_t size, FunctionManipulator&& man) const noexcept {
			using CopyFunction = void(FunctionManipulator::*)(T&, W) const noexcept;
			static_assert(traits::common::has_copy_function_v<FunctionManipulator, CopyFunction>,
				"FunctionManipulator::copy() const noexcept is required!");

			for (; size > ZERO_UI64; ++src, ++dst, --size)
				man.copy(*dst, *src);
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void copy(const U* src, T* dst, len_t size) const noexcept {
			static_assert(std::is_nothrow_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept constructor!");
			static_assert(std::is_nothrow_destructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept destructor!");
			static_assert(std::is_copy_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept copy constructor!");
			static_assert(std::is_copy_assignable_v<FunctionManipulator>, "FunctionManipulator needs a noexcept copy asignable!");
			static_assert(std::is_move_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept move constructor!");
			static_assert(std::is_move_assignable_v<FunctionManipulator>, "FunctionManipulator needs a noexcept move asignable!");
			this->copy<U, W, FunctionManipulator>(src, dst, size, FunctionManipulator());
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr void copy(const U* src, T* dst, len_t size) const noexcept {
			for (; size > ZERO_UI64; ++src, ++dst, --size)
				COPY(*dst, *src);
		}

		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t copy_s(const U* src, T* dst, len_t size, FunctionManipulator&& man) const noexcept {
			if (!src || !dst || size == ZERO_UI64) return llcpp::LL_FALSE;
			this->copy<U, W, FunctionManipulator>(src, dst, size, std::forward<FunctionManipulator>(man));
			return llcpp::LL_TRUE;
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t copy_s(const U* src, T* dst, len_t size) const noexcept {
			if (!src || !dst || size == ZERO_UI64) return llcpp::LL_FALSE;
			this->copy<U, W, FunctionManipulator>(src, dst, size);
			return llcpp::LL_TRUE;
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr ll_bool_t copy_s(const U* src, T* dst, len_t size) const noexcept {
			if (!src || !dst || size == ZERO_UI64) return llcpp::LL_FALSE;
			this->copy<U, W, COPY>(src, dst, size);
			return llcpp::LL_TRUE;
		}

		#pragma endregion
		#pragma region FunctionManipulatorAsParameter
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void copy(const meta::ArrayPair<U>& src, T* dst, const len_t size, FunctionManipulator&& man) const noexcept {
			this->copy<U, W, FunctionManipulator>(src.begin(), dst, math::min<len_t>(src.len(), size), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void copy(const meta::ArrayPair<U>& src, Array_t& dst, FunctionManipulator&& man) noexcept {
			this->copy<U, W, FunctionManipulator>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void copy(const meta::Array<U>& src, Array_t& dst, FunctionManipulator&& man) noexcept {
			this->copy<U, W, FunctionManipulator>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void copy(const U(&src)[N], T* dst, const len_t size, FunctionManipulator&& man) noexcept {
			this->copy<U, W, FunctionManipulator>(src, dst, math::min<len_t>(N, size), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void copy(const U(&src)[N], Array_t& dst, FunctionManipulator&& man) noexcept {
			this->copy<U, W, FunctionManipulator>(src, dst.begin(), math::min<len_t>(N, dst.len()), std::forward<FunctionManipulator>(man));
		}

		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t copy_s(const meta::ArrayPair<U>& src, T* dst, const len_t size, FunctionManipulator&& man) const noexcept {
			return this->copy_s<U, W, FunctionManipulator>(src.begin(), dst, math::min<len_t>(src.len(), size), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t copy_s(const meta::ArrayPair<U>& src, Array_t& dst, FunctionManipulator&& man) noexcept {
			return this->copy_s<U, W, FunctionManipulator>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t copy_s(const meta::Array<U>& src, Array_t& dst, FunctionManipulator&& man) noexcept {
			return this->copy_s<U, W, FunctionManipulator>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t copy_s(const U(&src)[N], T* dst, const len_t size, FunctionManipulator&& man) noexcept {
			return this->copy_s<U, W, FunctionManipulator>(src, dst, math::min<len_t>(N, size), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t copy_s(const U(&src)[N], Array_t& dst, FunctionManipulator&& man) noexcept {
			return this->copy_s<U, W, FunctionManipulator>(src, dst.begin(), math::min<len_t>(N, dst.len()), std::forward<FunctionManipulator>(man));
		}

		#pragma endregion
		#pragma region FunctionManipulatorCreate
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void copy(const meta::ArrayPair<U>& src, T* dst, const len_t size) const noexcept {
			this->copy<U, W, FunctionManipulator>(src.begin(), dst, math::min<len_t>(src.len(), size));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void copy(const meta::ArrayPair<U>& src, Array_t& dst) noexcept {
			this->copy<U, W, FunctionManipulator>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void copy(const meta::Array<U>& src, Array_t& dst) noexcept {
			this->copy<U, W, FunctionManipulator>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void copy(const U(&src)[N], T* dst, const len_t size) noexcept {
			this->copy<U, W, FunctionManipulator>(src, dst, math::min<len_t>(N, size));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void copy(const U(&src)[N], Array_t& dst) noexcept {
			this->copy<U, W, FunctionManipulator>(src, dst.begin(), math::min<len_t>(N, dst.len()));
		}

		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t copy_s(const meta::ArrayPair<U>& src, T* dst, const len_t size) const noexcept {
			return this->copy_s<U, W, FunctionManipulator>(src.begin(), dst, math::min<len_t>(src.len(), size));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t copy_s(const meta::ArrayPair<U>& src, Array_t& dst) noexcept {
			return this->copy_s<U, W, FunctionManipulator>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t copy_s(const meta::Array<U>& src, Array_t& dst) noexcept {
			return this->copy_s<U, W, FunctionManipulator>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t copy_s(const U(&src)[N], T* dst, const len_t size) noexcept {
			return this->copy_s<U, W, FunctionManipulator>(src, dst, math::min<len_t>(N, size));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t copy_s(const U(&src)[N], Array_t& dst) noexcept {
			return this->copy_s<U, W, FunctionManipulator>(src, dst.begin(), math::min<len_t>(N, dst.len()));
		}

		#pragma endregion
		#pragma region StaticFunction
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr void copy(const meta::ArrayPair<U>& src, T* dst, const len_t size) const noexcept {
			this->copy<U, W, COPY>(src.begin(), dst, math::min<len_t>(src.len(), size));
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr void copy(const meta::ArrayPair<U>& src, Array_t& dst) noexcept {
			this->copy<U, W, COPY>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr void copy(const meta::Array<U>& src, Array_t& dst) noexcept {
			this->copy<U, W, COPY>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>, len_t N>
		constexpr void copy(const U(&src)[N], T* dst, const len_t size) noexcept {
			this->copy<U, W, COPY>(src, dst, math::min<len_t>(N, size));
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>, len_t N>
		constexpr void copy(const U(&src)[N], Array_t& dst) noexcept {
			this->copy<U, W, COPY>(src, dst.begin(), math::min<len_t>(N, dst.len()));
		}

		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr ll_bool_t copy_s(const meta::ArrayPair<U>& src, T* dst, const len_t size) const noexcept {
			return this->copy_s<U, W, COPY>(src.begin(), dst, math::min<len_t>(src.len(), size));
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr ll_bool_t copy_s(const meta::ArrayPair<U>& src, Array_t& dst) noexcept {
			return this->copy_s<U, W, COPY>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr ll_bool_t copy_s(const meta::Array<U>& src, Array_t& dst) noexcept {
			return this->copy_s<U, W, COPY>(src.begin(), dst.begin(), math::min<len_t>(src.len(), dst.len()));
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>, len_t N>
		constexpr ll_bool_t copy_s(const U(&src)[N], T* dst, const len_t size) noexcept {
			return this->copy_s<U, W, COPY>(src, dst, math::min<len_t>(N, size));
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>, len_t N>
		constexpr ll_bool_t copy_s(const U(&src)[N], Array_t& dst) noexcept {
			return this->copy_s<U, W, COPY>(src, dst.begin(), math::min<len_t>(N, dst.len()));
		}

		#pragma endregion

		#pragma endregion
		#pragma region Move
	public:
		#pragma region Baase
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void move(U* src, T* dst, len_t size, FunctionManipulator&& man) const noexcept {
			using MoveSignaturetion = void(FunctionManipulator::*)(T&, U&) const noexcept;
			static_assert(traits::common::has_copy_function_v<FunctionManipulator, MoveSignaturetion>,
				"FunctionManipulator::move() const noexcept is required!");

			for (; size > ZERO_UI64; ++src, ++dst, --size)
				man.move(*dst, *src);
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void move(U* src, T* dst, len_t size) const noexcept {
			static_assert(std::is_nothrow_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept constructor!");
			static_assert(std::is_nothrow_destructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept destructor!");
			static_assert(std::is_copy_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept copy constructor!");
			static_assert(std::is_copy_assignable_v<FunctionManipulator>, "FunctionManipulator needs a noexcept copy asignable!");
			static_assert(std::is_move_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept move constructor!");
			static_assert(std::is_move_assignable_v<FunctionManipulator>, "FunctionManipulator needs a noexcept move asignable!");
			this->move<U, FunctionManipulator>(src.begin(), dst, math::min<len_t>(src.len(), size), FunctionManipulator());
		}
		template<class U = T, MoveExtraSignature<U> MOVE = meta::common::simple_move<T, U>>
		constexpr void move(U* src, T* dst, len_t size) const noexcept {
			for (; size > ZERO_UI64; ++src, ++dst, --size)
				COPY(*dst, *src);
		}

		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void move_s(U* src, T* dst, len_t size, FunctionManipulator&& man) const noexcept {
			if (!src || !dst || size == ZERO_UI64) return llcpp::LL_FALSE;
			this->move<U, FunctionManipulator>(src, dst, size, std::forward<FunctionManipulator>(man));
			return llcpp::LL_TRUE;
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void move_s(U* src, T* dst, len_t size) const noexcept {
			if (!src || !dst || size == ZERO_UI64) return llcpp::LL_FALSE;
			this->move<U, FunctionManipulator>(src, dst, size);
			return llcpp::LL_TRUE;
		}
		template<class U = T, MoveExtraSignature<U> MOVE = meta::common::simple_move<T, U>>
		constexpr void move_s(U* src, T* dst, len_t size) const noexcept {
			if (!src || !dst || size == ZERO_UI64) return;
			for (; size > ZERO_UI64; ++src, ++dst, --size)
				COPY(*dst, *src);
		}

		#pragma endregion
		#pragma region FunctionManipulatorAsParameter
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void move(U* src, const len_t src_size, Array_t& dst, FunctionManipulator&& man) const noexcept {
			this->move<U, FunctionManipulator>(src, dst.begin(), math::min<len_t>(src_size, dst.size()), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void move(U* src, const len_t src_size, T(&dst)[N], FunctionManipulator&& man) const noexcept {
			this->move<U, FunctionManipulator>(src, dst, math::min<len_t>(src_size, N), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void move(meta::ArrayPair<U>& src, T* dst, const len_t dst_size, FunctionManipulator&& man) const noexcept {
			this->move<U, FunctionManipulator>(src, dst.begin(), math::min<len_t>(src.size(), dst_size), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void move(U(&src)[N], T* dst, const len_t dst_size, FunctionManipulator&& man) const noexcept {
			this->move<U, FunctionManipulator>(src, dst, math::min<len_t>(N, dst_size), std::forward<FunctionManipulator>(man));
		}

		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t move_s(U* src, const len_t src_size, Array_t& dst, FunctionManipulator&& man) const noexcept {
			return this->move_s<U, FunctionManipulator>(src, dst.begin(), math::min<len_t>(src_size, dst.size()), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t move_s(U* src, const len_t src_size, T(&dst)[N], FunctionManipulator&& man) const noexcept {
			return this->move_s<U, FunctionManipulator>(src, dst, math::min<len_t>(src_size, N), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t move_s(meta::ArrayPair<U>& src, T* dst, const len_t dst_size, FunctionManipulator&& man) const noexcept {
			return this->move_s<U, FunctionManipulator>(src, dst.begin(), math::min<len_t>(src.size(), dst_size), std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t move_s(U(&src)[N], T* dst, const len_t dst_size, FunctionManipulator&& man) const noexcept {
			return this->move_s<U, FunctionManipulator>(src, dst, math::min<len_t>(N, dst_size), std::forward<FunctionManipulator>(man));
		}

		#pragma endregion
		#pragma region FunctionManipulatorCreate
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void move(U* src, const len_t src_size, Array_t& dst) const noexcept {
			this->move<U, FunctionManipulator>(src, dst.begin(), math::min<len_t>(src_size, dst.size()));
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void move(U* src, const len_t src_size, T(&dst)[N]) const noexcept {
			this->move<U, FunctionManipulator>(src, dst, math::min<len_t>(src_size, N));
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void move(meta::ArrayPair<U>& src, T* dst, const len_t dst_size) const noexcept {
			this->move<U, FunctionManipulator>(src, dst.begin(), math::min<len_t>(src.size(), dst_size));
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void move(U(&src)[N], T* dst, const len_t dst_size) const noexcept {
			this->move<U, FunctionManipulator>(src, dst, math::min<len_t>(N, dst_size));
		}

		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t move_s(U* src, const len_t src_size, Array_t& dst) const noexcept {
			return this->move_s<U, FunctionManipulator>(src, dst.begin(), math::min<len_t>(src_size, dst.size()));
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t move_s(U* src, const len_t src_size, T(&dst)[N]) const noexcept {
			return this->move_s<U, FunctionManipulator>(src, dst, math::min<len_t>(src_size, N));
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t move_s(meta::ArrayPair<U>& src, T* dst, const len_t dst_size) const noexcept {
			return this->move_s<U, FunctionManipulator>(src, dst.begin(), math::min<len_t>(src.size(), dst_size));
		}
		template<class U = T, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t move_s(U(&src)[N], T* dst, const len_t dst_size) const noexcept {
			return this->move_s<U, FunctionManipulator>(src, dst, math::min<len_t>(N, dst_size));
		}

		#pragma endregion
		#pragma region StaticFunction
		template<class U = T, MoveExtraSignature<U> MOVE = meta::common::simple_move<T, U>>
		constexpr void move(U* src, const len_t src_size, Array_t& dst) const noexcept {
			this->move<U, MOVE>(src, dst.begin(), math::min<len_t>(src_size, dst.size()), FunctionManipulator());
		}
		template<class U = T, MoveExtraSignature<U> MOVE = meta::common::simple_move<T, U>, len_t N>
		constexpr void move(U* src, const len_t src_size, T(&dst)[N]) const noexcept {
			this->move<U, MOVE>(src, dst, math::min<len_t>(src_size, N), FunctionManipulator());
		}
		template<class U = T, MoveExtraSignature<U> MOVE = meta::common::simple_move<T, U>>
		constexpr void move(meta::ArrayPair<U>& src, T* dst, const len_t dst_size) const noexcept {
			this->move<U, MOVE>(src, dst.begin(), math::min<len_t>(src.size(), dst_size), FunctionManipulator());
		}
		template<class U = T, MoveExtraSignature<U> MOVE = meta::common::simple_move<T, U>, len_t N>
		constexpr void move(U(&src)[N], T* dst, const len_t dst_size) const noexcept {
			this->move<U, MOVE>(src, dst, math::min<len_t>(N, dst_size), FunctionManipulator());
		}

		template<class U = T, MoveExtraSignature<U> MOVE = meta::common::simple_move<T, U>>
		constexpr ll_bool_t move_s(U* src, const len_t src_size, Array_t& dst) const noexcept {
			return this->move_s<U, MOVE>(src, dst.begin(), math::min<len_t>(src_size, dst.size()), FunctionManipulator());
		}
		template<class U = T, MoveExtraSignature<U> MOVE = meta::common::simple_move<T, U>, len_t N>
		constexpr ll_bool_t move_s(U* src, const len_t src_size, T(&dst)[N]) const noexcept {
			return this->move_s<U, MOVE>(src, dst, math::min<len_t>(src_size, N), FunctionManipulator());
		}
		template<class U = T, MoveExtraSignature<U> MOVE = meta::common::simple_move<T, U>>
		constexpr ll_bool_t move_s(meta::ArrayPair<U>& src, T* dst, const len_t dst_size) const noexcept {
			return this->move_s<U, MOVE>(src, dst.begin(), math::min<len_t>(src.size(), dst_size), FunctionManipulator());
		}
		template<class U = T, MoveExtraSignature<U> MOVE = meta::common::simple_move<T, U>, len_t N>
		constexpr ll_bool_t move_s(U(&src)[N], T* dst, const len_t dst_size) const noexcept {
			return this->move_s<U, MOVE>(src, dst, math::min<len_t>(N, dst_size), FunctionManipulator());
		}

		#pragma endregion

		#pragma endregion
		#pragma region ShiftLeft
	public:
		#pragma region Base
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void shiftLeft(T* _array, T* last, const len_t first, const len_t num, W null, FunctionManipulator&& man) const noexcept {
			using CopyFunction = void(FunctionManipulator::*)(T&, W) const noexcept;
			static_assert(traits::common::has_copy_function_v<FunctionManipulator, CopyFunction>,
				"FunctionManipulator::copy() const noexcept is required!");

			// First: 3
			// Num: 2
			// size: 10
			// [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
			// [0, 3, 4, 5, 6, 7, 8, 9, n, n]
			// 
			// 
			// [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
			//	   ^	 ^
			//	 begin  end
			// First element of the array to move
			T* begin = _array + first - num;
			// Last element of the array to move (some of the end of the list)
			T* end = _array + first;

			// Error -> move to shiftLeft_s
			//if (begin < _array) return;

			// Here we will use move (usually is faster than copy, and its more accurate)
			for (; end < last; ++begin, ++end)
				this->move(*begin, *end);

			// Here we will use copy
			this->fill<U, W, FunctionManipulator>(last - num, last, null, std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void shiftLeft(T* _array, T* last, const len_t first, const len_t num, W null) const noexcept {
			static_assert(std::is_nothrow_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept constructor!");
			static_assert(std::is_nothrow_destructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept destructor!");
			static_assert(std::is_copy_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept copy constructor!");
			static_assert(std::is_copy_assignable_v<FunctionManipulator>, "FunctionManipulator needs a noexcept copy asignable!");
			static_assert(std::is_move_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept move constructor!");
			static_assert(std::is_move_assignable_v<FunctionManipulator>, "FunctionManipulator needs a noexcept move asignable!");
			this->shiftLeft<U, W, FunctionManipulator>(_array, last, first, num, null, FunctionManipulator());
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr void shiftLeft(T* _array, T* last, const len_t first, const len_t num, W null) const noexcept {
			T* begin = _array + first - num;
			// Last element of the array to move (some of the end of the list)
			T* end = _array + first;

			// Error -> move to shiftLeft_s
			//if (begin < _array) return;

			// Here we will use move (usually is faster than copy, and its more accurate)
			for (; end < last; ++begin, ++end)
				Manipulator::move(*begin, *end);

			// Here we will use copy
			this->fill<U, W, COPY>(last - num, last, null);
		}

		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t shiftLeft_s(T* _array, T* last, const len_t first, const len_t num, W null, FunctionManipulator&& man) const noexcept {
			// First element in array must be first
			// And last, must be last
			if (_array > last) return llcpp::LL_FALSE;
			// Also, num cannot be 0
			if (num != ZERO_UI64) return llcpp::LL_FALSE;
			/// First: 1
			/// Num: 3
			/// size: 10
			/// [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]				->
			/// [x, x, x, x, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]	->
			/// [x, x, 1, 2, 3, 4, 5, 6, 7, 8, 9, n, n, n]	->
			/// [3, 4, 5, 6, 7, 8, 9, n, n, n]				->
			/// 
			/// 
			/// [x, x, x, x, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
			///		   ^		^
			///		begin		end
			/// First element of the array to move
			// Number of items to move to left could not be greater than the position of the first element
			// If so, we update the values
			if (num > first) first = num;
			this->shiftLeft<U, W, FunctionManipulator>(_array, last, first, num, null, std::forward<FunctionManipulator>(man));
			return llcpp::LL_TRUE;
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t shiftLeft_s(T* _array, T* last, const len_t first, const len_t num, W null) const noexcept {
			if (_array > last) return llcpp::LL_FALSE;
			if (num != ZERO_UI64) return llcpp::LL_FALSE;
			if (num > first) first = num;
			this->shiftLeft<U, W, FunctionManipulator>(_array, last, first, num, null);
			return llcpp::LL_TRUE;
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr ll_bool_t shiftLeft_s(T* _array, T* last, const len_t first, const len_t num, W null) const noexcept {
			if (_array > last) return llcpp::LL_FALSE;
			if (num != ZERO_UI64) return llcpp::LL_FALSE;
			if (num > first) first = num;
			this->shiftLeft<U, W, COPY>(_array, last, first, num, null);
			return llcpp::LL_TRUE;
		}

		#pragma endregion
		#pragma region FunctionManipulatorAsParameter
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void shiftLeft(Array_t& _array, const len_t first, const len_t num, W null, FunctionManipulator&& man) const noexcept {
			this->shiftLeft<U, W, FunctionManipulator>(_array.begin(), _array.end(), first, num, null, std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void shiftLeft(T(&_array)[N], const len_t first, const len_t num, W null, FunctionManipulator&& man) const noexcept {
			this->shiftLeft<U, W, FunctionManipulator>(_array, _array + N, first, num, null, std::forward<FunctionManipulator>(man));
		}

		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t shiftLeft_s(Array_t& _array, const len_t first, const len_t num, W null, FunctionManipulator&& man) const noexcept {
			return this->shiftLeft_s<U, W, FunctionManipulator>(_array.begin(), _array.end(), first, num, null, std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t shiftLeft_s(T(&_array)[N], const len_t first, const len_t num, W null, FunctionManipulator&& man) const noexcept {
			return this->shiftLeft_s<U, W, FunctionManipulator>(_array, _array + N, first, num, null, std::forward<FunctionManipulator>(man));
		}

		#pragma endregion
		#pragma region FunctionManipulatorCreate
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void shiftLeft(Array_t& _array, const len_t first, const len_t num, W null) const noexcept {
			this->shiftLeft<U, W, FunctionManipulator>(_array.begin(), _array.end(), first, num, null);
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void shiftLeft(T(&_array)[N], const len_t first, const len_t num, W null) const noexcept {
			this->shiftLeft<U, W, FunctionManipulator>(_array, _array + N, first, num, null);
		}

		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t shiftLeft_s(Array_t& _array, const len_t first, const len_t num, W null) const noexcept {
			return this->shiftLeft_s<U, W, FunctionManipulator>(_array.begin(), _array.end(), first, num, null);
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t shiftLeft_s(T(&_array)[N], const len_t first, const len_t num, W null) const noexcept {
			return this->shiftLeft_s<U, W, FunctionManipulator>(_array, _array + N - 1, first, num, null);
		}

		#pragma endregion
		#pragma region StaticFunction
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr void shiftLeft(Array_t& _array, const len_t first, const len_t num, W null) const noexcept {
			this->shiftLeft<U, W, COPY>(_array.begin(), _array.end(), first, num, null);
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>, len_t N>
		constexpr void shiftLeft(T(&_array)[N], const len_t first, const len_t num, W null) const noexcept {
			this->shiftLeft<U, W, COPY>(_array, _array + N, first, num, null);
		}

		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr ll_bool_t shiftLeft_s(Array_t& _array, const len_t first, const len_t num, W null) const noexcept {
			return this->shiftLeft_s<U, W, COPY>(_array.begin(), _array.end(), first, num, null);
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>, len_t N>
		constexpr ll_bool_t shiftLeft_s(T(&_array)[N], const len_t first, const len_t num, W null) const noexcept {
			return this->shiftLeft_s<U, W, COPY>(_array, _array + N, first, num, null);
		}

		#pragma endregion
		#pragma endregion
		#pragma region ShiftRight
	public:
		#pragma region Base
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void shiftRight(T* _array, T* last, const len_t first, const len_t num, W null, FunctionManipulator&& man) const noexcept {
			using CopyFunction = void(FunctionManipulator::*)(T&, W) const noexcept;
			static_assert(traits::common::has_copy_function_v<FunctionManipulator, CopyFunction>,
				"FunctionManipulator::copy() const noexcept is required!");

			// First: 3
			// Num: 2
			// size: 10
			// [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
			// [0, 1, 2, n, n, 3, 4, 5, 6, 7]
			// 
			// 
			// [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
			//			 ^	   ^	 ^	   ^
			//			begin  end	 prev  next
			// First element of the array to move
			T* next = last;
			T* prev = next - num;
			T* begin = _array + first;
			T* end = begin + num;

			for(; prev > begin; --prev, --next)
				this->move(*prev, *next);

			// Here we will use copy
			this->fill<U, W, FunctionManipulator>(begin, end, null, std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void shiftRight(T* _array, T* last, const len_t first, const len_t num, W null) const noexcept {
			static_assert(std::is_nothrow_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept constructor!");
			static_assert(std::is_nothrow_destructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept destructor!");
			static_assert(std::is_copy_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept copy constructor!");
			static_assert(std::is_copy_assignable_v<FunctionManipulator>, "FunctionManipulator needs a noexcept copy asignable!");
			static_assert(std::is_move_constructible_v<FunctionManipulator>, "FunctionManipulator needs a noexcept move constructor!");
			static_assert(std::is_move_assignable_v<FunctionManipulator>, "FunctionManipulator needs a noexcept move asignable!");
			this->shiftRight<U, W, FunctionManipulator>(_array, last, first, num, null, FunctionManipulator());
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr void shiftRight(T* _array, T* last, const len_t first, const len_t num, W null) const noexcept {
			T* next = last;
			T* prev = next - num;
			T* begin = _array + first;
			T* end = begin + num;

			for (; prev > begin; --prev, --next)
				Manipulator::move(*prev, *next);

			// Here we will use copy
			this->fill<U, W, COPY>(begin, end, null, std::forward<FunctionManipulator>(man));
		}

		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t shiftRight_s(T* _array, T* last, const len_t first, const len_t num, W null, FunctionManipulator&& man) const noexcept {
			if (_array > last) return llcpp::LL_FALSE;
			if (num != ZERO_UI64) return llcpp::LL_FALSE;
			this->shiftRight<U, W, FunctionManipulator>(_array, last, first, num, null, std::forward<FunctionManipulator>(man));
			return llcpp::LL_TRUE;
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t shiftRight_s(T* _array, T* last, const len_t first, const len_t num, W null) const noexcept {
			if (_array > last) return llcpp::LL_FALSE;
			if (num != ZERO_UI64) return llcpp::LL_FALSE;
			this->shiftRight<U, W, FunctionManipulator>(_array, last, first, num, null);
			return llcpp::LL_TRUE;
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr ll_bool_t shiftRight_s(T* _array, T* last, const len_t first, const len_t num, W null) const noexcept {
			if (_array > last) return llcpp::LL_FALSE;
			if (num != ZERO_UI64) return llcpp::LL_FALSE;
			this->shiftRight<U, W, COPY>(_array, last, first, num, null);
			return llcpp::LL_TRUE;
		}

		#pragma endregion
		#pragma region FunctionManipulatorAsParameter
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void shiftRight(Array_t& _array, const len_t first, const len_t num, W null, FunctionManipulator&& man) const noexcept {
			this->shiftRight<U, W, FunctionManipulator>(_array.begin(), _array.end(), first, num, null, std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void shiftRight(T(&_array)[N], const len_t first, const len_t num, W null, FunctionManipulator&& man) const noexcept {
			this->shiftRight<U, W, FunctionManipulator>(_array, _array + N, first, num, null, std::forward<FunctionManipulator>(man));
		}

		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t shiftRight_s(Array_t& _array, const len_t first, const len_t num, W null, FunctionManipulator&& man) const noexcept {
			return this->shiftRight_s<U, W, FunctionManipulator>(_array.begin(), _array.end(), first, num, null, std::forward<FunctionManipulator>(man));
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t shiftRight_s(T(&_array)[N], const len_t first, const len_t num, W null, FunctionManipulator&& man) const noexcept {
			return this->shiftRight_s<U, W, FunctionManipulator>(_array, _array + N, first, num, null, std::forward<FunctionManipulator>(man));
		}

		#pragma endregion
		#pragma region FunctionManipulatorCreate
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr void shiftRight(Array_t& _array, const len_t first, const len_t num, W null) const noexcept {
			this->shiftRight<U, W, FunctionManipulator>(_array.begin(), _array.end(), first, num, null);
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr void shiftRight(T(&_array)[N], const len_t first, const len_t num, W null) const noexcept {
			this->shiftRight<U, W, FunctionManipulator>(_array, _array + N, first, num, null);
		}

		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>>
		constexpr ll_bool_t shiftRight_s(Array_t& _array, const len_t first, const len_t num, W null) const noexcept {
			return this->shiftRight_s<U, W, FunctionManipulator>(_array.begin(), _array.end(), first, num, null);
		}
		template<class U = T, class W = traits::cinput<U>, class FunctionManipulator = algorithm::ManipulatorDefault<T, U>, len_t N>
		constexpr ll_bool_t shiftRight_s(T(&_array)[N], const len_t first, const len_t num, W null) const noexcept {
			return this->shiftRight_s<U, W, FunctionManipulator>(_array, _array + N - 1, first, num, null);
		}

		#pragma endregion
		#pragma region StaticFunction
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr void shiftRight(Array_t& _array, const len_t first, const len_t num, W null) const noexcept {
			this->shiftRight<U, W, COPY>(_array.begin(), _array.end(), first, num, null);
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>, len_t N>
		constexpr void shiftRight(T(&_array)[N], const len_t first, const len_t num, W null) const noexcept {
			this->shiftRight<U, W, COPY>(_array, _array + N, first, num, null);
		}

		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>>
		constexpr ll_bool_t shiftRight_s(Array_t& _array, const len_t first, const len_t num, W null) const noexcept {
			return this->shiftRight_s<U, W, COPY>(_array.begin(), _array.end(), first, num, null);
		}
		template<class U = T, class W = traits::cinput<U>, CopyExtraSignature<W> COPY = meta::common::simple_set<T, W>, len_t N>
		constexpr ll_bool_t shiftRight_s(T(&_array)[N], const len_t first, const len_t num, W null) const noexcept {
			return this->shiftRight_s<U, W, COPY>(_array, _array + N, first, num, null);
		}

		#pragma endregion
		#pragma endregion

		#pragma endregion
	
	#pragma endregion

	#pragma region Qsort
	//template<class T, class U = traits::template_types<T>>
	//constexpr T* qsort_div(
	//	T* _array,
	//	T* begin,
	//	T* end,
	//	fnc_clss::SwapSignaturetion<U::type> swap,
	//	fnc_clss::Compare<U::cinput> cmp
	//) noexcept {
	//	__LL_ASSERT_VAR_NULL__(_array, "_array");
	//	__LL_ASSERT_VAR_NULL__(begin, "begin");
	//	__LL_ASSERT_VAR_NULL__(end, "end");
	//	__LL_ASSERT_VAR_NULL__(swap, "swap");
	//	__LL_ASSERT_VAR_NULL__(cmp, "cmp");
	//
	//	T* left = begin;
	//	T* right = end;
	//	T* piv = _array;
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
	//	T* _array, T* begin, T* end,
	//	fnc_clss::SwapSignaturetion<U::type> swap,
	//	fnc_clss::Compare<U::cinput> cmp
	//) {
	//	if (begin < end) {
	//		T* pivote = qsort_div<T, U>(_array, begin, end, swap, cmp);
	//		//if (pivote >= begin && pivote <= end) {
	//		quicksort<T, U>(_array, begin, pivote - 1, swap, cmp);
	//		quicksort<T, U>(_array, pivote + 1, end, swap, cmp);
	//		//}
	//	}
	//}
	//template<class T, class U = traits::template_types<T>>
	//constexpr void quicksort(T* _array, T* begin, T* end) {
	//	quicksort<T>(_array, begin, end, common::simple_swap<T>, common::compare_with_operators<T>);
	//}
	//template<class T, class U = traits::template_types<T>>
	//constexpr void quicksort(T* begin, T* end) {
	//	quicksort<T, U>(begin, begin, end);
	//}
	//template<class T, class U = traits::template_types<T>, len_t N>
	//constexpr void quicksort(T(&_array)[N]) {
	//	quicksort<T, U>(_array, _array, _array + (N - 1));
	//}

	#pragma endregion
};

///constexpr int example() {
///	int _array[] = { 0, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
///	//quicksort(_array);
///	//return _array[0];
///	int* piv = qsort_div(_array, _array, _array + 9, common::simple_swap<int>, common::compare_with_operators<int>);
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
