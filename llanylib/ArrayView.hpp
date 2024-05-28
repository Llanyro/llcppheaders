//////////////////////////////////////////////
//	ArrayView.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 6.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ARRAYVIEW_HPP_) // Guard && version protector
	#if LLANYLIB_ARRAYVIEW_MAYOR_ != 6 || LLANYLIB_ARRAYVIEW_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "ArrayView.hpp version error!"
		#else
			#error "ArrayView.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ARRAYVIEW_MAYOR_ || LLANYLIB_ARRAYVIEW_MINOR_

#else !defined(LLANYLIB_ARRAYVIEW_HPP_)
#define LLANYLIB_ARRAYVIEW_HPP_
#define LLANYLIB_ARRAYVIEW_MAYOR_ 6
#define LLANYLIB_ARRAYVIEW_MINOR_ 0

#include "algorithm.hpp"

namespace llcpp {
namespace meta {

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
		type::cptr mem;
	#pragma endregion
	#pragma region Functions
	public:
		#pragma region Contructors
		constexpr ArrayView() __LL_EXCEPT__ = delete;
		constexpr ~ArrayView() __LL_EXCEPT__ {}

		constexpr ArrayView(type::ctype(&arr)[N]) __LL_EXCEPT__ : mem(arr) {}
		constexpr __ArrayView::ref operator=(type::ctype(&arr)[N]) __LL_EXCEPT__ {
			this->mem = arr;
			return *this;
		}

		#pragma endregion
		#pragma region CopyMove
		constexpr ArrayView(__ArrayView::cref other) __LL_EXCEPT__ : mem(other.mem) {}
		constexpr __ArrayView::ref operator=(__ArrayView::cref other) __LL_EXCEPT__ {
			this->mem = other.mem;
			return *this;
		}

		constexpr ArrayView(__ArrayView::move) __LL_EXCEPT__ = delete;
		constexpr __ArrayView::ref operator=(__ArrayView::move) __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename __ArrayView::cptr() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename __ArrayView::ptr() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
		__LL_NODISCARD__ constexpr type::cptr get(const len_t pos) const __LL_EXCEPT__ {
			return this->mem + pos;
		}
		__LL_NODISCARD__ constexpr __ArrayPair get(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return __ArrayPair(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr __ArrayPair substr(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr type::cref operator[] (const len_t pos) const __LL_EXCEPT__ {
			return *this->get(pos);
		}
#if defined(LL_REAL_CXX23)
		__LL_NODISCARD__ constexpr __ArrayPair operator[](const len_t first, const len_t last) const __LL_EXCEPT__ {
			return this->substr(first, last);
		}

#endif // LL_REAL_CXX23
		__LL_NODISCARD__ constexpr operator __ArrayPair() const __LL_EXCEPT__ {
			return __ArrayPair(this->begin(), this->end());
		}

		#pragma endregion
		#pragma region Countable
		__LL_NODISCARD__ constexpr len_t len() const __LL_EXCEPT__ { return N; }
		__LL_NODISCARD__ constexpr len_t size() const __LL_EXCEPT__ { return this->len(); }
		__LL_NODISCARD__ constexpr len_t count() const __LL_EXCEPT__ { return this->len(); }

		#pragma endregion
		#pragma region std
		__LL_NODISCARD__ constexpr type::cptr data() const __LL_EXCEPT__ {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr type::cptr begin() const __LL_EXCEPT__ {
			return this->get(ZERO_UI64);
		}
		__LL_NODISCARD__ constexpr type::cptr rbegin() const __LL_EXCEPT__ {
			return this->get(this->len() - 1);
		}
		__LL_NODISCARD__ constexpr type::cptr end() const __LL_EXCEPT__ {
			return this->get(this->len());
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const __LL_EXCEPT__ {
			return this->len() == ZERO_UI64;
		}

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
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const U (&arr)[N], CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const U (&arr)[N]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::compare(this->begin(), arr, this->len());
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(__ArrayViewOtherType<U>::cref arr, CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(__ArrayViewOtherType<U>::cref arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->len());
		}

		#pragma endregion
		#pragma region Equals
	public:
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const U (&arr)[N2], CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr, N2, compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const U (&arr)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr, N2);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const U* arr, const len_t size, CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr, size, compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const U* arr, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr, size);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayView<U, N2>& arr, CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr.begin(), arr.len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayView<U, N2>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr.begin(), arr.len());
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayPair<U>& arr, CompareFunc<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr.begin(), arr.len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> equals(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr.begin(), arr.len());
		}

		#pragma endregion
		#pragma region Operators
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const U (&arr)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr, N2);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const ArrayView<U, N2>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr.begin(), arr.len());
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> operator==(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::equals(this->begin(), this->len(), arr.begin(), arr.len());
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
			return __cmp<LL_FALSE, typename type::type>::equals(this->begin(), this->len(), arr, N2);
		}
		template<len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ArrayView<typename type::type, N2>& arr) const __LL_EXCEPT__ {
			return __cmp<LL_FALSE, typename type::type>::equals(this->begin(), this->len(), arr.begin(), arr.len());
		}
		//template<>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ArrayPair<typename type::type>& arr) const __LL_EXCEPT__ {
			return __cmp<LL_FALSE, typename type::type>::equals(this->begin(), this->len(), arr.begin(), arr.len());
		}

		#pragma endregion
		#pragma region StartsWith
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const U (&needle)[N2], CompareFuncBool<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle, N2, compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const U (&needle)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle, N2);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const U* needle, const len_t size, CompareFuncBool<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle, size);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const U* needle, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle, size);
		}
		
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayView<U, N2>& needle, CompareFuncBool<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle.begin(), needle.len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayView<U, N>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle.begin(), needle.len());
		}
		
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayPair<U>& needle, CompareFuncBool<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle.begin(), needle.len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> starts_with(const ArrayPair<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::starts_with(this->begin(), this->len(), needle.begin(), needle.len());
		}

		#pragma endregion
		#pragma region EndsWith
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const U(&needle)[N2], CompareFuncBool<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle, N2, compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const U(&needle)[N2]) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle, N2);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const U* needle, const len_t size, CompareFuncBool<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle, size);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const U* needle, const len_t size) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle, size);
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayView<U, N2>& needle, CompareFuncBool<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle.begin(), needle.len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayView<U, N>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle.begin(), needle.len());
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayPair<U>& needle, CompareFuncBool<GET_DATA, U> compareFunc) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle.begin(), needle.len(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResultBool<GET_DATA, U> ends_with(const ArrayPair<U>& needle) const __LL_EXCEPT__ {
			return __cmp<GET_DATA, U>::ends_with(this->begin(), this->len(), needle.begin(), needle.len());
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
		#pragma region Other
		__LL_NODISCARD__ constexpr ll_bool_t isValid() const __LL_EXCEPT__ {
			return !this->empty() && this->begin();
		}
		__LL_NODISCARD__ constexpr operator hash::Hash64() const __LL_EXCEPT__ {
			return hash::Hash64();
			// [TOFIX]
			//return algorithm::has_cluster::hash<T, __sizes::ARR_SIZE>(this->begin());
			//return meta::StandardHashFunctions(*this);
		}

		#pragma endregion
		#pragma endregion
	#pragma endregion
};

template<class T, len_t N>
constexpr ArrayView<T, N> make_ArrayView(const T(&arr)[N]) {
	return ArrayView<T, N>(arr);
}

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAYVIEW_HPP_
