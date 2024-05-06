//////////////////////////////////////////////
//	ArrayView.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ARRAYVIEW_HPP_) // Guard && version protector
	#if LLANYLIB_ARRAYVIEW_MAYOR_ != 5 || LLANYLIB_ARRAYVIEW_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "ArrayView.hpp version error!"
		#else
			#error "ArrayView.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ARRAYVIEW_MAYOR_ || LLANYLIB_ARRAYVIEW_MINOR_

#else !defined(LLANYLIB_ARRAYVIEW_HPP_)
#define LLANYLIB_ARRAYVIEW_HPP_
#define LLANYLIB_ARRAYVIEW_MAYOR_ 5
#define LLANYLIB_ARRAYVIEW_MINOR_ 0

#include "algorithm.hpp"

namespace llcpp {

template<class T, len_t N>
class LL_SHARED_LIB ArrayView {
	#pragma region Assersts
	public:
		static_assert(N > 0, "Array cannot have a size of 0");
	#pragma endregion
	#pragma region ClassTypes
	public:
		using type = traits::template_types<T>;
		using __ArrayView = traits::template_types<ArrayView<T, N>>;
		using __ArrayPair = ArrayPair<T>;
		using csubarr = std::pair<typename type::cptr, typename type::cptr>;

	#pragma endregion
	#pragma region OtherClassTypes
	// Algorithm objects
	public:
		template<ll_bool_t GET_DATA, class U>
		using __cmp = algorithm::compare_cluster<typename type::raw, U, GET_DATA>;
		template<ll_bool_t POSITION>
		using __find = algorithm::finders_cluster<typename type::raw, POSITION>;

	// Other internal objects
	protected:
		template<class U>
		using __ArrayViewOtherType = traits::template_types<ArrayView<U, N>>;
		//template<len_t N2>
		//using __ArrayViewOtherSize = traits::template_types<ArrayView<T, N2>>;
	#pragma endregion
	#pragma region Attributes
	protected:
		type::cptr _data;
	#pragma endregion
	#pragma region Functions
	public:
		#pragma region Contructors
		constexpr ArrayView() __LL_EXCEPT__ = delete;
		constexpr ~ArrayView() __LL_EXCEPT__ {}

		constexpr ArrayView(type::ctype(&arr)[N]) __LL_EXCEPT__ : _data(arr) {}
		constexpr __ArrayView::ref operator=(type::ctype(&arr)[N]) __LL_EXCEPT__ {
			this->_data = arr;
			return *this;
		}

		#pragma endregion
		#pragma region CopyMove
		constexpr ArrayView(__ArrayView::cref other) __LL_EXCEPT__ : _data(other._data) {}
		constexpr __ArrayView::ref operator=(__ArrayView::cref other) __LL_EXCEPT__ {
			this->_data = other._data;
			return *this;
		}

		constexpr ArrayView(__ArrayView::move) __LL_EXCEPT__ = delete;
		constexpr __ArrayView::ref operator=(__ArrayView::move) __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename __ArrayView::cptr() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename __ArrayView::ptr() __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename __ArrayView::move() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr operator len_t() const __LL_EXCEPT__ { return N; }
		__LL_NODISCARD__ constexpr len_t size() const __LL_EXCEPT__ { return this->operator len_t(); }
		__LL_NODISCARD__ constexpr len_t len() const __LL_EXCEPT__ { return this->operator len_t(); }
		__LL_NODISCARD__ constexpr ll_bool_t empty() const __LL_EXCEPT__ {
			return this->operator len_t() == 0;
		}
		__LL_NODISCARD__ constexpr operator ll_bool_t() const __LL_EXCEPT__ {
			return !this->empty() && static_cast<ll_bool_t>(this->_data);
		}

		__LL_NODISCARD__ constexpr operator typename __ArrayPair() const __LL_EXCEPT__ {
			return __ArrayPair(this->_data, this->operator len_t());
		}
		__LL_NODISCARD__ constexpr operator type::cptr() const __LL_EXCEPT__ { return this->_data; }
		__LL_NODISCARD__ constexpr type::cptr get(const len_t pos) const __LL_EXCEPT__ {
			return this->_data + pos;
		}
		__LL_NODISCARD__ constexpr csubarr get(const len_t _begin, const len_t _end) const __LL_EXCEPT__ {
			return csubarr{ this->get(_begin) , this->get(_end) };
		}
		__LL_NODISCARD__ constexpr csubarr substr(const len_t _begin, const len_t _end) const __LL_EXCEPT__ {
			return this->get(_begin, _end);
		}
		__LL_NODISCARD__ constexpr type::cref operator[] (const len_t pos) const __LL_EXCEPT__ {
			return this->_data[pos];
		}
		#ifdef LL_REAL_CXX23
		__LL_NODISCARD__ constexpr csubarr operator[](const len_t _begin, const len_t _end) const __LL_EXCEPT__ {
			return this->substr(_begin, _end);
		}

		#endif // LL_REAL_CXX23

		#pragma region Compare
	public:
		template<ll_bool_t GET_DATA, class U>
		using CompareResult = typename __cmp<GET_DATA, U>::CompareResult;
		template<ll_bool_t GET_DATA, class U>
		using CompareResultBool = typename __cmp<GET_DATA, U>::CompareResultBool;
		template<ll_bool_t GET_DATA, class W>
		using CompareFunc = typename __cmp<GET_DATA, W>::CompareFunc;
		template<ll_bool_t GET_DATA, class W>
		using CompareFuncBool = typename __cmp<GET_DATA, W>::CompareFuncBool;

		#pragma region Compare
	public:
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const U (&arr)[N], CompareFunc<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->operator len_t(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const U (&arr)[N]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->operator len_t());
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(__ArrayViewOtherType<U>::cref arr, CompareFunc<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->operator len_t(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(__ArrayViewOtherType<U>::cref arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->operator len_t());
		}

		#pragma endregion
		#pragma region Equals
	public:
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const U (&arr)[N2], CompareFunc<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->operator len_t(), arr, N2, compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const U (&arr)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->operator len_t(), arr, N2);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const U* arr, const len_t size, CompareFunc<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->operator len_t(), arr, size, compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const U* arr, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->operator len_t(), arr, size);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayView<U, N2>& arr, CompareFunc<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->operator len_t(), arr.begin(), arr.operator len_t(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayView<U, N2>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->operator len_t(), arr.begin(), arr.operator len_t());
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayPair<U>& arr, CompareFunc<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->operator len_t(), arr.begin(), arr.len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->operator len_t(), arr.begin(), arr.len());
		}

		#pragma endregion
		#pragma region Operators
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const U (&arr)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->operator len_t(), arr, N2);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const ArrayView<U, N2>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->operator len_t(), arr.begin(), arr.operator len_t());
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->operator len_t(), arr.begin(), arr.len());
		}
		
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator!=(const U (&arr)[N2]) const __LL_EXCEPT__ {
			return !this->operator==(arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator!=(const ArrayView<U, N2>& arr) const __LL_EXCEPT__ {
			return !this->operator==(arr);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator!=(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			return !this->operator==(arr);
		}

		template<len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(type::ctype (&arr)[N2]) const __LL_EXCEPT__ {
			return __cmp<LL_FALSE, typename type::type>::equals(this->begin(), this->operator len_t(), arr, N2);
		}
		template<len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ArrayView<typename type::type, N2>& arr) const __LL_EXCEPT__ {
			return __cmp<LL_FALSE, typename type::type>::equals(this->begin(), this->operator len_t(), arr.begin(), arr.operator len_t());
		}
		//template<>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ArrayPair<typename type::type>& arr) const __LL_EXCEPT__ {
			return __cmp<LL_FALSE, typename type::type>::equals(this->begin(), this->operator len_t(), arr.begin(), arr.len());
		}

		#pragma endregion
		#pragma region StartsWith
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const U (&needle)[N2], CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->operator len_t(), needle, N2, compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const U (&needle)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->operator len_t(), needle, N2);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const U* needle, const len_t size, CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->operator len_t(), needle, size);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const U* needle, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->operator len_t(), needle, size);
		}
		
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayView<U, N2>& needle, CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->operator len_t(), needle.begin(), needle.operator len_t(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayView<U, N>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->operator len_t(), needle.begin(), needle.operator len_t());
		}
		
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayPair<U>& needle, CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->operator len_t(), needle.begin(), needle.len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayPair<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->operator len_t(), needle.begin(), needle.len());
		}

		#pragma endregion
		#pragma region EndsWith
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const U(&needle)[N2], CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->operator len_t(), needle, N2, compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const U(&needle)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->operator len_t(), needle, N2);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const U* needle, const len_t size, CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->operator len_t(), needle, size);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const U* needle, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->operator len_t(), needle, size);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayView<U, N2>& needle, CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->operator len_t(), needle.begin(), needle.operator len_t(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayView<U, N>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->operator len_t(), needle.begin(), needle.operator len_t());
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayPair<U>& needle, CompareFuncBool<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->operator len_t(), needle.begin(), needle.len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayPair<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->operator len_t(), needle.begin(), needle.len());
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


		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> find(W object, FindFunc<W> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::find<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> find(W object) const __LL_EXCEPT__ {
			return __find<POSITION>::find<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> rfind(W object, FindFunc<W> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::rfind<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> rfind(W object) const __LL_EXCEPT__ {
			return __find<POSITION>::rfind<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> contains(W object, FindFunc<W> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::contains<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> contains(W object) const __LL_EXCEPT__ {
			return __find<POSITION>::contains<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> all(W object, FindFunc<W> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::all<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> all(W object) const __LL_EXCEPT__ {
			return __find<POSITION>::all<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> any(W object, FindFunc<W> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::any<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> any(W object) const __LL_EXCEPT__ {
			return __find<POSITION>::any<U, W>(this->begin(), this->end(), object);
		}

		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> none(W object, FindFunc<W> compareFunc) const __LL_EXCEPT__ {
			return __find<POSITION>::none<U, W>(this->begin(), this->end(), object, compareFunc);
		}
		template<class U, ll_bool_t POSITION = LL_TRUE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr FindResult<POSITION> none(W object) const __LL_EXCEPT__ {
			return __find<POSITION>::none<U, W>(this->begin(), this->end(), object);
		}

		#pragma endregion
		#pragma region std
		__LL_NODISCARD__ constexpr type::cptr data() const __LL_EXCEPT__ {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr type::cptr begin() const __LL_EXCEPT__ {
			return this->get(0ull);
		}
		__LL_NODISCARD__ constexpr type::cptr rbegin() const __LL_EXCEPT__ {
			return this->get(this->operator len_t() - 1);
		}
		__LL_NODISCARD__ constexpr type::cptr end() const __LL_EXCEPT__ {
			return this->get(this->operator len_t());
		}

		#pragma endregion
		#pragma endregion
	#pragma endregion
};

template<class T, len_t N>
constexpr ArrayView<T, N> make_ArrayView(const T (&arr)[N]) {
	return ArrayView<T, N>(arr);
}

} // namespace llcpp

#endif // LLANYLIB_ARRAYVIEW_HPP_
