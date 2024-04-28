//////////////////////////////////////////////
//	StringView.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_STRINGVIEW_HPP_) // Guard && version protector
	#if LLANYLIB_STRINGVIEW_MAYOR_ != 5 || LLANYLIB_STRINGVIEW_MINOR_ < 0
		#error "StringView.hpp version error!"
	#endif // LLANYLIB_STRINGVIEW_MAYOR_ || LLANYLIB_STRINGVIEW_MINOR_

#else !defined(LLANYLIB_STRINGVIEW_HPP_)
#define LLANYLIB_STRINGVIEW_HPP_
#define LLANYLIB_STRINGVIEW_MAYOR_ 5
#define LLANYLIB_STRINGVIEW_MINOR_ 0

#include "algorithm.hpp"

namespace llcpp {

template<len_t N, class T = ll_char_t>
class LL_SHARED_LIB StringView {
	// Assersts
	public:
		static_assert(N >= 1, "String cannot have a size of 0");
		static_assert(traits::is_char_type_v<T>, "Type must be a char type");

	// Class types
	public:
		using type = llcpp::traits::template_types<T>;
		using __StringView = llcpp::traits::template_types<StringView<N, T>>;
		using __StrPair = traits::get_by_char_type_t<T, StrPair, uStrPair, wStrPair>;

	// Algorithm objects
	public:
		template<ll_bool_t GET_DATA, class U>
		using cmp = algorithm::compare_cluster<typename type::raw, U, GET_DATA>;
		template<ll_bool_t GET_DATA>
		using cmp_self = algorithm::compare_cluster<typename type::raw, typename type::raw, GET_DATA>;
		using find = algorithm::finders_cluster<typename type::raw>;

		template<class W>
		using eq_compare_func = typename cmp<LL_FALSE, W>::fun_compare;

	// Other internal objects
	protected:
		template<len_t N> struct SizeConversor {
			static constexpr ll_bool_t IS_EMPTY = (N == 1);
			static constexpr len_t ARR_SIZE = IS_EMPTY ? N : N - 1;
		};
		using __sizes = SizeConversor<N>;
		template<len_t N2> using __sizes_other = SizeConversor<N2>;

		template<len_t N2>
		using __StringViewOtherSize = traits::template_types<StringView<N2, T>>;


	protected:
		type::cptr __data;

	public:
		constexpr StringView() __LL_EXCEPT__ = delete;
		constexpr ~StringView() __LL_EXCEPT__ {}

		constexpr StringView(type::ctype (&__data)[N]) __LL_EXCEPT__ : __data(__data) {}
		constexpr __StringView::ref operator=(type::ctype (&__data)[N]) __LL_EXCEPT__ {
			this->__data = __data;
			return *this;
		}

		constexpr StringView(__StringView::cref other) __LL_EXCEPT__ : __data(other.__data) {}
		constexpr __StringView::ref operator=(__StringView::cref other) __LL_EXCEPT__ {
			this->__data = other.__data;
			return *this;
		}

		constexpr StringView(__StringView::move) __LL_EXCEPT__ = delete;
		constexpr __StringView::ref operator=(__StringView::move) __LL_EXCEPT__ = delete;

		__LL_NODISCARD__ constexpr operator len_t() const __LL_EXCEPT__ {
			return __sizes::ARR_SIZE;
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

		__LL_NODISCARD__ constexpr operator __StrPair() const __LL_EXCEPT__ {
			return __StrPair(this->__data, this->operator len_t());
		}
		__LL_NODISCARD__ constexpr operator type::cptr() const __LL_EXCEPT__ { return this->__data; }
		__LL_NODISCARD__ constexpr type::cptr get(const len_t pos = 0ull) const __LL_EXCEPT__ {
			return this->__data + pos;
		}
		__LL_NODISCARD__ constexpr type::cref operator[] (const len_t pos) const __LL_EXCEPT__ {
			return this->__data[pos];
		}


		#pragma region Compare
	public:
		template<ll_bool_t GET_DATA, class U>
		using CompareResult = typename cmp<GET_DATA, U>::CompareResult;

		template<ll_bool_t GET_DATA, class W>
		using cmp_compare_func = typename cmp<GET_DATA, W>::fun_compare;

		template<ll_bool_t GET_DATA>
		using CompareResultNoFunc = typename CompareResult<GET_DATA, typename type::type>;


		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const U (&arr)[N], cmp_compare_func<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			static_assert(traits::is_char_type_v<traits::template_types<U>::raw>, "Type must be a char type");
			return cmp<GET_DATA, U>::compare(this->begin(), arr, this->operator len_t(), compareFunc);
		}
		template<ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultNoFunc<GET_DATA> compare(type::ctype (&arr)[N]) const __LL_EXCEPT__ {
			return cmp_self<GET_DATA>::compare(this->begin(), arr, this->operator len_t());
		}

		template<class U, ll_bool_t GET_DATA = LL_FALSE, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr CompareResult<GET_DATA, U> compare(const StringView<N, U>& arr, cmp_compare_func<GET_DATA, W> compareFunc) const __LL_EXCEPT__ {
			return cmp<GET_DATA, U>::compare(this->begin(), arr.begin(), this->operator len_t(), compareFunc);
		}
		template<ll_bool_t GET_DATA = LL_FALSE>
		__LL_NODISCARD__ constexpr CompareResultNoFunc<GET_DATA> compare(const StringView<N, typename type::type>& arr) const __LL_EXCEPT__ {
			return cmp_self<GET_DATA>::compare(this->begin(), arr.begin(), this->operator len_t());
		}

		#pragma endregion
		/*#pragma region Equals
		template<class U, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const U (&arr)[N2], eq_compare_func<W> compareFunc) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals<N, N2>(this->begin(), arr, compareFunc);
		}
		template<class U, len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const U (&arr)[N2]) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals<N, N2>(this->begin(), arr);
		}

		template<class U, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const U* arr, const len_t size, eq_compare_func<W> compareFunc) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals(this->begin(), this->operator len_t(), arr, size, compareFunc);
		}
		template<class U>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const U* arr, const len_t size) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals(this->begin(), this->operator len_t(), arr, size);
		}

		template<class U, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const ArrayView<U, N2>& arr, eq_compare_func<W> compareFunc) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals<N, N2>(this->begin(), arr.begin(), compareFunc);
		}
		template<class U, class W = traits::template_types<U>::cinput, len_t N2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const ArrayView<U, N>& arr) const __LL_EXCEPT__ {
			return cmp<LL_FALSE, U>::equals<N, N2>(this->begin(), arr.begin());
		}

		template<class U, class W = traits::template_types<U>::cinput>
		__LL_NODISCARD__ constexpr ll_bool_t equals(const ArrayPair<U>& arr, eq_compare_func<W> compareFunc) const __LL_EXCEPT__ {
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

		#pragma endregion*/
		#pragma endregion





	/*public:

	protected:
		template<len_t N>
		struct SizeConversor {
			static constexpr ll_bool_t IS_EMPTY = (N == 1);
			static constexpr len_t ARR_SIZE = IS_EMPTY ? N : N - 1;
		};
		using STypes = SizeConversor<N>;
		template<len_t N2> using STypesOther = SizeConversor<N2>;

		template<len_t N2>
		using __StringViewOther = llcpp::traits::template_types<StringView<N2, T>>;

		//using __internal__ArrayView__ = ArrayView<T, STypes::ARR_SIZE>;
		//template<len_t N2>
		//using ArrayViewOtherSize = ArrayView<T, N2>;
		//template<len_t N2>
		//using __cref_ArrayViewOtherSize = const ArrayViewOtherSize<N2>&;
	protected:
		type::cptr __data;
	protected:
		template<len_t N2>
		static constexpr __ptr convert(type::type (&__array)[N2]) {
			return const_cast<__ptr>(__array);
		}
		*/
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


template<len_t N, class T = ll_char_t>
constexpr StringView<N, T> make_StringView(const T(&__data)[N]) {
	return StringView<N, T>(__data);
}

} // namespace llcpp

#endif // LLANYLIB_STRINGVIEW_HPP_
