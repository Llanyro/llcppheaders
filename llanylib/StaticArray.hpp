//////////////////////////////////////////////
//	StaticArray.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_STATICARRAY_HPP_) // Guard && version protector
	#if LLANYLIB_STATICARRAY_MAYOR_ != 7 || LLANYLIB_STATICARRAY_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "StaticArray.hpp version error!"
		#else
			#error "StaticArray.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_STATICARRAY_MAYOR_ || LLANYLIB_STATICARRAY_MINOR_

#else !defined(LLANYLIB_STATICARRAY_HPP_)
#define LLANYLIB_STATICARRAY_HPP_
#define LLANYLIB_STATICARRAY_MAYOR_ 7
#define LLANYLIB_STATICARRAY_MINOR_ 0

#include "algorithm.hpp"

namespace llcpp {
namespace meta {

template<class T, len_t N, T NULL_ITEM>
class StaticArray : public meta::Array<T> {
	#pragma region ClassTypes
	public:
		using type = traits::template_types<T>;
		using __StaticArray = traits::template_types<meta::StaticArray<T, N, NULL_ITEM>>;
		using __Array = traits::template_types<meta::Array<T>>;
		using __ArrayPair = traits::template_types<ArrayPair<T>>;

	public:
		using __data = algorithm::data_manipulation_cluster<typename type::raw>;
		template<ll_bool_t GET_DATA, class U>
		using __cmp = algorithm::compare_cluster<typename type::raw, U, GET_DATA>;
		template<ll_bool_t POSITION>
		using __find = algorithm::finders_cluster<typename type::raw, POSITION>;

	#pragma endregion
	#pragma region Attributes
	protected:
		type::type mem_array[N];
	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr StaticArray() __LL_EXCEPT__ : __Array::type(LL_NULLPTR, LL_NULLPTR), mem_array() {
			this->mem = this->mem_array;
			this->mem_end = this->mem_array + N;
		}
		constexpr StaticArray(typename type::cinput object) __LL_EXCEPT__
			: StaticArray() { this->fill<typename type::type>(object); }
		constexpr ~StaticArray() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr StaticArray(__StaticArray::cref other) __LL_EXCEPT__ : StaticArray() {
			this->copy<typename type::type>(other.mem_array);
		}
		constexpr __StaticArray::ref operator=(__StaticArray::cref other) __LL_EXCEPT__ {
			this->copy<typename type::type>(other.mem_array);
			return *this;
		}
		constexpr StaticArray(__StaticArray::move other) __LL_EXCEPT__ : StaticArray(other) {
			other.clear();
		}
		constexpr __StaticArray::ref operator=(__StaticArray::move other) __LL_EXCEPT__ {
			__StaticArray::type::operator=(other);
			other.__StaticArray::type::clear();
			return *this;
		}
		
		constexpr StaticArray(__Array::cref other) __LL_EXCEPT__ : StaticArray() {
			this->copy<typename type::type>(other.begin(), other.len());
		}
		constexpr __StaticArray::ref operator=(__Array::cref other) __LL_EXCEPT__ {
			this->copy<typename type::type>(other.begin(), other.len());
			return *this;
		}
		constexpr StaticArray(__Array::move) __LL_EXCEPT__ = delete;
		constexpr __StaticArray::ref operator=(__Array::move) __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator typename __StaticArray::ptr() __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename __StaticArray::cptr() const __LL_EXCEPT__ = delete;

		#pragma endregion

		#pragma region Compare
	public:
		template<ll_bool_t GET_DATA, class U>
		using CompareResult = typename __cmp<GET_DATA, U>::CompareResult;
		template<ll_bool_t GET_DATA, class U>
		using CompareResultBool = typename __cmp<GET_DATA, U>::CompareResultBool;
		template<ll_bool_t GET_DATA, class U>
		using CompareFunc = typename __cmp<GET_DATA, U>::CompareFunc;
		template<ll_bool_t GET_DATA, class U>
		using CompareFuncBool = typename __cmp<GET_DATA, U>::CompareFuncBool;

		#pragma region Compare
	public:
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(typename W::cptr arr, const len_t size, CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			if (this->len() != size)
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(typename W::cptr arr, const len_t size) const __LL_EXCEPT__ {
			if (this->len() != size)
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->len());
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(typename W::ctype(&arr)[N2], CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			if (this->len() != N2)
				return CompareResult<GET_DATA, U>(-2);
			return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(typename W::ctype(&arr)[N2]) const __LL_EXCEPT__ {
			if (this->len() != N2)
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->len());
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const ArrayPair<U>& arr, CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			if (this->len() != arr.len())
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			if (this->len() != arr.len())
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len());
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const Array<U>& arr, CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			if (this->len() != arr.len())
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const Array<U>& arr) const __LL_EXCEPT__ {
			if (this->len() != arr.len())
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len());
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, ll_bool_t IS_STRINGVIEW = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const ArrayView<U, IS_STRINGVIEW>& arr, CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			if (this->len() != arr.len())
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, ll_bool_t IS_STRINGVIEW = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const ArrayView<U, IS_STRINGVIEW>& arr) const __LL_EXCEPT__ {
			if (this->len() != arr.len())
				return CompareResult<GET_DATA, U>(-2);
			else return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len());
		}

		#pragma endregion
		#pragma region Equals
	public:
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(typename W::cptr arr, const len_t size, CompareFunc<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr, size, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(typename W::cptr arr, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr, size);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(typename W::ctype(&arr)[N2], CompareFunc<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals<N2>(*this, arr, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(typename W::ctype(&arr)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals<N2>(*this, arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayPair<U>& arr, CompareFunc<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const Array<U>& arr, CompareFunc<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const Array<U>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, ll_bool_t IS_STRINGVIEW = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayView<U, IS_STRINGVIEW>& arr, CompareFunc<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, ll_bool_t IS_STRINGVIEW = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayView<U, IS_STRINGVIEW>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(*this, arr);
		}

		#pragma endregion
		#pragma region Operators
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(typename W::ctype(&arr)[N2]) const __LL_EXCEPT__ {
			return this->equals<U, GET_DATA, N2, W>(arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			return this->equals<U, GET_DATA>(arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const Array<U>& arr) const __LL_EXCEPT__ {
			return this->equals<U, GET_DATA>(arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, ll_bool_t IS_STRINGVIEW = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const ArrayView<U, IS_STRINGVIEW>& arr) const __LL_EXCEPT__ {
			return this->equals<U, GET_DATA>(arr);
		}

		template<len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(typename type::ctype(&arr)[N2]) const __LL_EXCEPT__ {
			return this->equals<typename type::type, LL_FALSE, N2, type>(arr);
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__ArrayPair::cref arr) const __LL_EXCEPT__ {
			return this->equals<typename type::type, LL_FALSE>(arr);
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__Array::cref arr) const __LL_EXCEPT__ {
			return this->equals<typename type::type, LL_FALSE>(arr);
		}

		#pragma endregion
		#pragma region StartsWith
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(typename W::cptr needle, const len_t size, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle, size, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(typename W::cptr needle, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle, size);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(typename W::ctype(&needle)[N2], CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with<N2>(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(typename W::ctype(&needle)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with<N2>(*this, needle);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayPair<U>& needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayPair<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const Array<U>& needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const Array<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayView<U>& needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayView<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, needle);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(typename W::cinput needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, &needle, 1, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(typename W::cinput needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(*this, &needle, 1);
		}


		#pragma endregion
		#pragma region EndsWith
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(typename W::cptr needle, const len_t size, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle, size, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(typename W::cptr needle, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle, size);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(typename W::ctype(&needle)[N2], CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with<N2>(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(typename W::ctype(&needle)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with<N2>(*this, needle);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayPair<U>& needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayPair<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const Array<U>& needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const Array<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayView<U>& needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayView<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, needle);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(typename W::cinput needle, CompareFuncBool<GET_DATA, U> cmp) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, &needle, 1, cmp);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(typename W::cinput needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(*this, &needle, 1);
		}

		#pragma endregion

		#pragma endregion
		#pragma region Finders
	public:
		template<ll_bool_t POSITION>
		using FindResult = __find<POSITION>::FindResult;
		// [TOFIX]
		template<class W>
		using FindFunc = fnc_clss::CompareBool<typename type::input, W>;

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> find(typename W::cinput object, FindFunc<typename W::cinput> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::find<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> find(typename W::cinput object) const __LL_EXCEPT__ {
			return __find<POSITION>::find<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> rfind(typename W::cinput object, FindFunc<typename W::cinput> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::rfind<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> rfind(typename W::cinput object) const __LL_EXCEPT__ {
			return __find<POSITION>::rfind<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> contains(typename W::cinput object, FindFunc<typename W::cinput> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::contains<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> contains(typename W::cinput object) const __LL_EXCEPT__ {
			return __find<POSITION>::contains<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> all(typename W::cinput object, FindFunc<typename W::cinput> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::all<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> all(typename W::cinput object) const __LL_EXCEPT__ {
			return __find<POSITION>::all<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> any(typename W::cinput object, FindFunc<typename W::cinput> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::any<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> any(typename W::cinput object) const __LL_EXCEPT__ {
			return __find<POSITION>::any<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> none(typename W::cinput object, FindFunc<typename W::cinput> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::none<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>>
		__LL_NODISCARD__ constexpr FindResult<POSITION> none(typename W::cinput object) const __LL_EXCEPT__ {
			return __find<POSITION>::none<U, W>(this->begin(), this->end(), object);
		}

		#pragma endregion

		#pragma region Reverse
	public:
		using SwapFunc = typename __data::SwapFunc;

		constexpr void reverse(SwapFunc swap, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			__data::reverse(this->get(first), this->get(last), swap);
		}
		constexpr void reverse(const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			__data::reverse(this->get(first), this->get(last));
		}

		#pragma endregion
		#pragma region Fill
	public:
		// [TOFIX]
		template<class W>
		//using FillFunc = typename __data::FillFunc<W>;
		using FillFunc = fnc_clss::SetFunction<typename type::type, W>;

		template<class U, class W = traits::template_types<U>>
		constexpr void fill(typename W::cinput object, FillFunc<typename W::cinput> setFunc, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			__data::fill<U, W>(this->get(first), this->get(last), object, setFunc);
		}
		template<class U, class W = traits::template_types<U>>
		constexpr void fill(typename W::cinput object, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			__data::fill<U, W>(this->get(first), this->get(last), object);
		}

		#pragma endregion
		#pragma region Copy
	public:
		template<class U, class W = traits::template_types<U>>
		constexpr void copy(W::cptr src, const len_t size, FillFunc<typename W::type> setFunc, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			len_t this_size = last - first;
			if (!setFunc || size != this_size) return;
			__data::copy<U, W>(src, this->get(first), this_size, setFunc);
		}
		template<class U, class W = traits::template_types<U>>
		constexpr void copy(W::cptr src, const len_t size, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			len_t this_size = last - first;
			if (size != this_size) return;
			__data::copy<U, W>(src, this->get(first), N);
		}
		template<class U, class W = traits::template_types<U>, len_t N2>
		constexpr void copy(W::ctype(&src)[N2], FillFunc<typename W::type> setFunc, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			len_t this_size = last - first;
			if (!setFunc || N2 != this_size) return;
			__data::copy<U, W>(src, this->get(first), N2, setFunc);
		}
		template<class U, class W = traits::template_types<U>, len_t N2>
		constexpr void copy(W::ctype(&src)[N2], const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			len_t this_size = last - first;
			if (N2 != this_size) return;
			__data::copy<U, W>(src, this->get(first), N2);
		}

		#pragma endregion
		#pragma region Shift
		//constexpr void fill(const len_t first, const len_t last, len_t num, typename W::cinput null, SwapFunc swap, FillFunc<typename W::cinput> setFunc) __LL_EXCEPT__ {

		//constexpr void shiftLeft(const len_t num, SwapFunc swap, FillFunc<typename type::cinput> setFunc, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
		constexpr void shiftLeft(const len_t num, SwapFunc swap, FillFunc<typename type::cinput> setFunc, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			__data::shiftLeft<type::type>(this->get(first), last - first, 0, num, NULL_ITEM, setFunc, setFunc);
		}
		constexpr void shiftLeft(const len_t num, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			__data::shiftLeft<type::type>(this->get(first), last - first, 0, num, NULL_ITEM);
		}
		constexpr void shifRight(const len_t num, SwapFunc swap, FillFunc<typename type::cinput> setFunc, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			__data::shifRight<type::type>(this->get(first), last - first, 0, num, NULL_ITEM, setFunc, setFunc);
		}
		constexpr void shifRight(const len_t num, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			__data::shifRight<type::type>(this->get(first), last - first, 0, num, NULL_ITEM);
		}

		#pragma endregion
		#pragma region Qsort
		// WIP

		#pragma endregion
		#pragma region Other
		template<class U, class W = traits::template_types<U>>
		constexpr void clear(typename W::cinput null, FillFunc<typename W::type> setFunc) __LL_EXCEPT__ {
			this->fill<U, W>(null, setFunc);
		}
		template<class U, class W = traits::template_types<U>>
		constexpr void clear(typename W::cinput null) __LL_EXCEPT__ {
			this->fill<U, W>(null);
		}
		constexpr void clear() __LL_EXCEPT__ {
			this->fill<type::type>(NULL_ITEM);
		}

		#pragma endregion

	#pragma endregion
};

constexpr int testing() {
	StaticArray<ll_int_t, 10, 0> arr;
	decltype(arr)::FillFunc<const ll_char_t> f = [](ll_int_t& a, const ll_char_t b) -> void {
		a = b;
	};
	arr.fill<ll_char_t>(5, f);
	arr.clear();
	arr[9] = 8;
	arr.shifRight(9);
	arr.reverse();
	return arr[0];
}

constexpr int val = testing();

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_STATICARRAY_HPP_
