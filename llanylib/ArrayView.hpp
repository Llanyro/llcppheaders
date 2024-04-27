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
	private:
		template<len_t N2>
		using ArrayViewOtherSize = ArrayView<T, N2>;
		template<len_t N2>
		using __cref_ArrayViewOtherSize = const ArrayViewOtherSize<N2>&;
	public:
		static_assert(N > 0, "Array cannot have a size of 0");
	public:
		using type = llcpp::traits::template_types<T>;
		using __ArrayView = llcpp::traits::template_types<ArrayView<T, N>>;
	protected:
		type::ptr __data;
	public:
		constexpr ArrayView() __LL_EXCEPT__ = delete;
		constexpr ~ArrayView() __LL_EXCEPT__ {}

		constexpr ArrayView(type::type (&__data)[N]) __LL_EXCEPT__ : __data(__data) {}
		constexpr __ArrayView::ref operator=(type::type (&__data)[N]) __LL_EXCEPT__ {
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

		__LL_NODISCARD__ constexpr operator ArrayPair<type::type>() const __LL_EXCEPT__ {
			return ArrayPair<type::type>(this->__data, N);
		}
		__LL_NODISCARD__ constexpr operator type::cptr() const __LL_EXCEPT__ { return this->__data; }
		__LL_NODISCARD__ constexpr type::cptr get(const len_t pos = 0ull) const __LL_EXCEPT__ {
			return this->__data + pos;
		}
		__LL_NODISCARD__ constexpr type::cref operator[] (const len_t pos) const __LL_EXCEPT__ {
			return this->__data[pos];
		}

		#pragma region Algorithm
		#pragma region Compare
		template<ll_bool_t GET_DATA = LL_FALSE, class CompareResult = std::conditional_t<GET_DATA, algorithm::CompareData<__type, cmp_t>, cmp_t>>
		__LL_NODISCARD__ constexpr CompareResult compare(type::type (&__array)[N], fnc_clss::Compare<__type> cmp) const __LL_EXCEPT__ {
			return algorithm::compare<__type, GET_DATA, CompareResult>(this->begin(), __array, this->len(), cmp);
		}
		template<ll_bool_t GET_DATA = LL_FALSE, class CompareResult = std::conditional_t<GET_DATA, algorithm::CompareData<__type, cmp_t>, cmp_t>>
		__LL_NODISCARD__ constexpr CompareResult compare(type::type (&__array)[N]) const __LL_EXCEPT__ {
			return algorithm::compare<__type, GET_DATA, CompareResult>(this->begin(), __array, this->len());
		}

		template<ll_bool_t GET_DATA = LL_FALSE, class CompareResult = std::conditional_t<GET_DATA, algorithm::CompareData<__type, cmp_t>, cmp_t>>
		__LL_NODISCARD__ constexpr CompareResult compare(__cref_ArrayView other, fnc_clss::Compare<__type> cmp) const __LL_EXCEPT__ {
			return algorithm::compare<__type, GET_DATA, CompareResult>(this->begin(), other.begin(), this->len(), cmp);
		}
		template<ll_bool_t GET_DATA = LL_FALSE, class CompareResult = std::conditional_t<GET_DATA, algorithm::CompareData<__type, cmp_t>, cmp_t>>
		__LL_NODISCARD__ constexpr CompareResult compare(__cref_ArrayView other) const __LL_EXCEPT__ {
			return algorithm::compare<__type, GET_DATA, CompareResult>(this->begin(), other.begin(), this->len());
		}

		#pragma endregion
		#pragma region Equals
		#pragma region Func
		template<len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(type::type (&__array)[N2], fnc_clss::Compare<__type> cmp) const __LL_EXCEPT__ {
			return algorithm::equals<__type>(this->begin(), N, __array, N2, cmp);
		}
		template<len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(type::type (&__array)[N2]) const __LL_EXCEPT__ {
			return algorithm::equals<__type>(this->begin(), N, __array, N2);
		}
		__LL_NODISCARD__ constexpr ll_bool_t equals(__cref_ArrayView other, fnc_clss::Compare<__type> cmp) const __LL_EXCEPT__ {
			return algorithm::equals<__type, N>(this->begin(), other.begin(), cmp);
		}
		__LL_NODISCARD__ constexpr ll_bool_t equals(__cref_ArrayView other) const __LL_EXCEPT__ {
			return algorithm::equals<__type, N>(this->begin(), other.begin());
		}
		template<len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(__cref_ArrayViewOtherSize<N2> other, fnc_clss::Compare<__type> cmp) const __LL_EXCEPT__ {
			return algorithm::equals<__type>(this->begin(), N, other.begin(), N2, cmp);
		}
		template<len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(__cref_ArrayViewOtherSize<N2> other) const __LL_EXCEPT__ {
			return algorithm::equals<__type>(this->begin(), N, other.begin(), N2);
		}

		#pragma endregion
		#pragma region Operator
		template<len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(type::type (&__array)[N2]) const __LL_EXCEPT__ {
			return this->equals<N2>(__array);
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__cref_ArrayView other) const __LL_EXCEPT__ {
			return this->equals<N>(other);
		}
		template<len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__cref_ArrayViewOtherSize<N2> other) const __LL_EXCEPT__ {
			return this->equals<N2>(other);
		}

		#pragma endregion
		#pragma endregion
		#pragma region StartsWith
		template<ll_bool_t GET_DATA = LL_FALSE, class CompareResult = algorithm::CompareConditionalBool<__type, GET_DATA>, len_t N2>
		__LL_NODISCARD__ constexpr CompareResult starts_with(type::type (&__array)[N2], fnc_clss::Compare<__type> cmp) const __LL_EXCEPT__ {
			return algorithm::starts_with<__type, GET_DATA, CompareResult>(this->begin(), __array, N, N2, cmp);
		}
		template<ll_bool_t GET_DATA = LL_FALSE, class CompareResult = algorithm::CompareConditionalBool<__type, GET_DATA>, len_t N2>
		__LL_NODISCARD__ constexpr CompareResult starts_with(type::type (&__array)[N2]) const __LL_EXCEPT__ {
			return algorithm::starts_with<__type, GET_DATA, CompareResult>(this->begin(), __array, N, N2);
		}

		template<ll_bool_t GET_DATA = LL_FALSE, class CompareResult = algorithm::CompareConditionalBool<__type, GET_DATA>, len_t N2>
		__LL_NODISCARD__ constexpr CompareResult starts_with(__cref_ArrayViewOtherSize<N2> other, fnc_clss::Compare<__type> cmp) const __LL_EXCEPT__ {
			return algorithm::starts_with<__type, GET_DATA, CompareResult>(this->begin(), other.begin(), N, N2, cmp);
		}
		template<ll_bool_t GET_DATA = LL_FALSE, class CompareResult = algorithm::CompareConditionalBool<__type, GET_DATA>, len_t N2>
		__LL_NODISCARD__ constexpr CompareResult starts_with(__cref_ArrayViewOtherSize<N2> other) const __LL_EXCEPT__ {
			return algorithm::starts_with<__type, GET_DATA, CompareResult>(this->begin(), other.begin(), N, N2);
		}

		#pragma endregion
		#pragma region EndsWith
		template<ll_bool_t GET_DATA = LL_FALSE, class CompareResult = algorithm::CompareConditionalBool<__type, GET_DATA>, len_t N2>
		__LL_NODISCARD__ constexpr CompareResult ends_with(type::type (&__array)[N2], fnc_clss::Compare<__type> cmp) const __LL_EXCEPT__ {
			return algorithm::ends_with<__type, GET_DATA, CompareResult>(this->begin(), __array, N, N2, cmp);
		}
		template<ll_bool_t GET_DATA = LL_FALSE, class CompareResult = algorithm::CompareConditionalBool<__type, GET_DATA>, len_t N2>
		__LL_NODISCARD__ constexpr CompareResult ends_with(type::type (&__array)[N2]) const __LL_EXCEPT__ {
			return algorithm::ends_with<__type, GET_DATA, CompareResult>(this->begin(), __array, N, N2);
		}

		template<ll_bool_t GET_DATA = LL_FALSE, class CompareResult = algorithm::CompareConditionalBool<__type, GET_DATA>, len_t N2>
		__LL_NODISCARD__ constexpr CompareResult ends_with(__cref_ArrayViewOtherSize<N2> other, fnc_clss::Compare<__type> cmp) const __LL_EXCEPT__ {
			return algorithm::ends_with<__type, GET_DATA, CompareResult>(this->begin(), other.begin(), N, N2, cmp);
		}
		template<ll_bool_t GET_DATA = LL_FALSE, class CompareResult = algorithm::CompareConditionalBool<__type, GET_DATA>, len_t N2>
		__LL_NODISCARD__ constexpr CompareResult ends_with(__cref_ArrayViewOtherSize<N2> other) const __LL_EXCEPT__ {
			return algorithm::ends_with<__type, GET_DATA, CompareResult>(this->begin(), other.begin(), N, N2);
		}

		#pragma endregion
		#pragma region Find
		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr const T* find(
			const U object,
			fnc_clss::CompareBool<__type> cmp,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::find<__type, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr const T* find(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::find<__type, U>(this->get(__begin), this->get(__end), object);
		}

		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr len_t find_pos(
			const U object,
			fnc_clss::CompareBool<__type> cmp,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::find_pos<__type, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr len_t find_pos(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::find_pos<__type, U>(this->get(__begin), this->get(__end), object);
		}

		#pragma endregion
		#pragma region rFind
		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr const T* rfind(
			const U object,
			fnc_clss::CompareBool<__type> cmp,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::rfind<__type, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr const T* rfind(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::rfind<__type, U>(this->get(__begin), this->get(__end), object);
		}

		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr len_t rfind_pos(
			const U object,
			fnc_clss::CompareBool<__type> cmp,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::rfind_pos<__type, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr len_t rfind_pos(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::rfind_pos<__type, U>(this->get(__begin), this->get(__end), object);
		}

		#pragma endregion
		#pragma region Other
		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr ll_bool_t all(
			const U object,
			fnc_clss::CompareBool<__type> cmp,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::all<__type, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr ll_bool_t all(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::all<__type, U>(this->get(__begin), this->get(__end), object);
		}

		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr ll_bool_t any(
			const U object,
			fnc_clss::CompareBool<__type> cmp,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::any<__type, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr ll_bool_t any(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::any<__type, U>(this->get(__begin), this->get(__end), object);
		}

		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr ll_bool_t none(
			const U object,
			fnc_clss::CompareBool<__type> cmp,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::none<__type, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr ll_bool_t none(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = N
		) const __LL_EXCEPT__ {
			return algorithm::none<__type, U>(this->get(__begin), this->get(__end), object);
		}

		#pragma endregion
		#pragma region BinarySearch
		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr const T* binarysearch(const U object) const __LL_EXCEPT__ {
			return this->end();// algorithm::binarysearch<__type, U>(this->get(__begin), this->get(__end), object);
		}
		template<class U = traits::get_object_reference_t<__type>>
		__LL_NODISCARD__ constexpr len_t binarysearch_pos(const U object) const __LL_EXCEPT__ {
			return algorithm::npos; //algorithm::binarysearch_pos<__type, U>(this->get(__begin), this->get(__end), object);
		}

		#pragma endregion

		#pragma endregion
		#pragma region std
		__LL_NODISCARD__ constexpr __cptr data() const __LL_EXCEPT__ {
			return this->get();
		}
		__LL_NODISCARD__ constexpr __cptr begin() const __LL_EXCEPT__ {
			return this->get();
		}
		__LL_NODISCARD__ constexpr __cptr end() const __LL_EXCEPT__ {
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
