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
		#error "ArrayView.hpp version error!"
	#endif // LLANYLIB_ARRAYVIEW_MAYOR_ || LLANYLIB_ARRAYVIEW_MINOR_

#else !defined(LLANYLIB_ARRAYVIEW_HPP_)
#define LLANYLIB_ARRAYVIEW_HPP_
#define LLANYLIB_ARRAYVIEW_MAYOR_ 5
#define LLANYLIB_ARRAYVIEW_MINOR_ 0

#include "algorithm.hpp"

namespace llcpp {

template<class T, len_t N>
class LL_SHARED_LIB ArrayView {
	public:
		using type = traits::template_types<T>;
		using __ArrayView = traits::template_types<ArrayView<T, N>>;
		using __ArrayPair = ArrayPair<type::type>;

		template<ll_bool_t GET_DATA, class U = type::type>
		using cmp = algorithm::compare_cluster<type::raw, U, GET_DATA>;
		using find = algorithm::finders_cluster<type::raw>;

		template<len_t N2>
		using __ArrayViewOtherSize = traits::template_types<ArrayView<T, N2>>;

		static_assert(N > 0, "Array cannot have a size of 0");
	protected:
		type::type* __data;
	public:
		constexpr ArrayView() __LL_EXCEPT__ = delete;
		constexpr ~ArrayView() __LL_EXCEPT__ {}

		constexpr ArrayView(T (&__data)[N]) __LL_EXCEPT__ : __data(__data) {}
		constexpr __ArrayView::ref operator=(T (&__data)[N]) __LL_EXCEPT__ {
			this->__data = __data;
			return *this;
		}

		constexpr ArrayView(__ArrayView::cref other) __LL_EXCEPT__ : __data(other.__data) {}
		constexpr __ArrayView::ref operator=(__ArrayView::cref other) __LL_EXCEPT__ {
			this->__data = other.__data;
			return *this;
		}

		constexpr ArrayView(__ArrayView::move) __LL_EXCEPT__ = delete;
		constexpr __ArrayView::ref operator=(__ArrayView::move) __LL_EXCEPT__ = delete;

		__LL_NODISCARD__ constexpr operator len_t() const __LL_EXCEPT__ {
			return N;
		}
		__LL_NODISCARD__ constexpr len_t size() const __LL_EXCEPT__ {
			return this->operator len_t();
		}
		__LL_NODISCARD__ constexpr len_t len() const __LL_EXCEPT__ {
			return this->operator len_t();
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const __LL_EXCEPT__ {
			return this->operator len_t() == 0;
		}
		__LL_NODISCARD__ constexpr operator ll_bool_t() const __LL_EXCEPT__ {
			return !this->empty() && static_cast<ll_bool_t>(this->__data);
		}

		__LL_NODISCARD__ constexpr operator __ArrayPair() const __LL_EXCEPT__ {
			return __ArrayPair(this->__data, N);
		}
		__LL_NODISCARD__ constexpr operator type::cptr() const __LL_EXCEPT__ { return this->__data; }
		__LL_NODISCARD__ constexpr type::cptr get(const len_t pos = 0ull) const __LL_EXCEPT__ {
			return this->__data + pos;
		}
		__LL_NODISCARD__ constexpr type::cref operator[] (const len_t pos) const __LL_EXCEPT__ {
			return this->__data[pos];
		}

		#pragma region Co-mpare
		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr cmp<GET_DATA, U>::CompareResult compare(const U (&arr)[N], cmp<GET_DATA, W>::fun_compare compareFunc) const __LL_EXCEPT__ {
			return cmp<GET_DATA, U>::compare(this->begin(), arr, this->operator len_t(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr cmp<GET_DATA, U>::CompareResult compare(const U (&arr)[N]) const __LL_EXCEPT__ {
			return cmp<GET_DATA, U>::compare(this->begin(), arr, this->operator len_t());
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr cmp<GET_DATA, U>::CompareResult compare(const ArrayView<U, N>& arr, cmp<GET_DATA, W>::fun_compare compareFunc) const __LL_EXCEPT__ {
			return cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->operator len_t(), compareFunc);
		}
		template<class U, ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr cmp<GET_DATA, U>::CompareResult compare(const ArrayView<U, N>& arr) const __LL_EXCEPT__ {
			return cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->operator len_t());
		}

		#pragma endregion
		#pragma region Equals
		template<class U, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const U (&arr)[N2], cmp<LL_FALSE, W>::fun_compare compareFunc) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals<N, N2>(this->begin(), arr, compareFunc);
		}
		template<class U, len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const U (&arr)[N2]) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals<N, N2>(this->begin(), arr);
		}

		template<class U, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const U* arr, const len_t size, cmp<LL_FALSE, W>::fun_compare compareFunc) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals(this->begin(), this->operator len_t(), arr, size, compareFunc);
		}
		template<class U>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const U* arr, const len_t size) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals(this->begin(), this->operator len_t(), arr, size);
		}

		template<class U, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const ArrayView<U, N2>& arr, cmp<LL_FALSE, W>::fun_compare compareFunc) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals<N, N2>(this->begin(), arr.begin(), compareFunc);
		}
		template<class U, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const ArrayView<U, N>& arr) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals<N, N2>(this->begin(), arr.begin());
		}

		template<class U, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const ArrayPair<U>& arr, cmp<LL_FALSE, W>::fun_compare compareFunc) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals(this->begin(), this->operator len_t(), arr.begin(), arr.len(), compareFunc);
		}
		template<class U, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals(this->begin(), this->operator len_t(), arr.begin(), arr.len());
		}

		#pragma region Proxy
		template<class U, len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const U(&arr)[N2]) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals<N, N2>(this->begin(), arr);
		}
		template<class U, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ArrayView<U, N>& arr) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals<N, N2>(this->begin(), arr.begin());
		}
		template<class U, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ArrayPair<U>& arr) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals(this->begin(), this->operator len_t(), arr.begin(), arr.len());
		}

		#pragma endregion
		#pragma endregion



		#pragma region std
		__LL_NODISCARD__ constexpr type::cptr data() const __LL_EXCEPT__ {
			return this->get();
		}
		__LL_NODISCARD__ constexpr type::cptr begin() const __LL_EXCEPT__ {
			return this->get();
		}
		__LL_NODISCARD__ constexpr type::cptr end() const __LL_EXCEPT__ {
			return this->get(this->operator len_t());
		}

		#pragma endregion
};

//template<len_t N>
//using StringView = ArrayView<const ll_char_t, N>;
//template<len_t N>
//using StringView_u = ArrayView<const ll_uchar_t, N>;

} // namespace llcpp

#endif // LLANYLIB_ARRAYVIEW_HPP_
