//////////////////////////////////////////////
//	Array.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 6.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ARRAY_HPP_) // Guard && version protector
	#if LLANYLIB_ARRAY_MAYOR_ != 6 || LLANYLIB_ARRAY_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Array.hpp version error!"
		#else
			#error "Array.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ARRAY_MAYOR_ || LLANYLIB_ARRAY_MINOR_

#else !defined(LLANYLIB_ARRAY_HPP_)
#define LLANYLIB_ARRAY_HPP_
#define LLANYLIB_ARRAY_MAYOR_ 6
#define LLANYLIB_ARRAY_MINOR_ 0

#include "ArrayView.hpp"

namespace llcpp {
namespace meta {

template<class T, len_t N, T NULL_ITEM>
class LL_SHARED_LIB Array : public ArrayView<T, N> {
	#pragma region Assersts
	public:
	#pragma endregion
	#pragma region ClassTypes
	public:
		using type = traits::template_types<T>;
		using __Array = traits::template_types<Array<T, N, NULL_ITEM>>;
		using __ArrayView = traits::template_types<ArrayView<T, N>>;
		using __ArrayPair = ArrayPair<T>;

	#pragma endregion
	#pragma region OtherClassTypes
	// Algorithm objects
	public:
		using __data = algorithm::data_manipulation<typename type::raw>;

	#pragma endregion
	#pragma region Attributes
	protected:
		type::type mem_array[N];
	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr Array() __LL_EXCEPT__ : __ArrayView::type(this->mem_array), mem_array() {}
		constexpr ~Array() __LL_EXCEPT__ {}
		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Array(__Array::cref other) __LL_EXCEPT__ : Array() {
			this->copy<typename type::type>(other.mem_array);
		}
		constexpr __Array::ref operator=(__Array::cref other) __LL_EXCEPT__ {
			this->copy<typename type::type>(other.mem_array);
			return *this;
		}
		constexpr Array(__Array::move other) __LL_EXCEPT__ : Array(other) {
			other.clear();
		}
		constexpr __Array::ref operator=(__Array::move other) __LL_EXCEPT__ {
			this->operator=(other);
			other.clear();
			return *this;
		}
		
		constexpr Array(__ArrayView::cref other) __LL_EXCEPT__ : Array() {
			this->copy<typename type::type>(other.begin(), other.len());
		}
		constexpr __Array::ref operator=(__ArrayView::cref other) __LL_EXCEPT__ {
			this->copy<typename type::type>(other.begin(), other.len());
			return *this;
		}
		constexpr Array(__ArrayView::move other) __LL_EXCEPT__ = delete;
		constexpr __Array::ref operator=(__ArrayView::move other) __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator typename __Array::cptr() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename __Array::ptr() __LL_EXCEPT__ = delete;
		
		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
	public:
		__LL_NODISCARD__ constexpr type::ptr get(const len_t pos) __LL_EXCEPT__ {
			return this->mem_array + pos;
		}
		__LL_NODISCARD__ constexpr type::cptr get(const len_t pos) const __LL_EXCEPT__ {
			return this->mem_array + pos;
		}
		__LL_NODISCARD__ constexpr __Array::type get(const len_t first, const len_t last) __LL_EXCEPT__ {
			typename __Array::type arr;
			arr.copy<typename type::type>(this->get(first), last - first);
			return arr;
		}
		__LL_NODISCARD__ constexpr __ArrayPair get(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return __ArrayPair(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr __Array::type substr(const len_t first, const len_t last) __LL_EXCEPT__ {
			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr __ArrayPair substr(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr type::ref operator[] (const len_t pos) __LL_EXCEPT__ {
			return *this->get(pos);
		}
		__LL_NODISCARD__ constexpr type::cref operator[] (const len_t pos) const __LL_EXCEPT__ {
			return *this->get(pos);
		}
#if defined(LL_REAL_CXX23)
		__LL_NODISCARD__ constexpr __Array::type operator[](const len_t first, const len_t last) __LL_EXCEPT__ {
			return this->substr(first, last);
		}
		__LL_NODISCARD__ constexpr __ArrayPair operator[](const len_t first, const len_t last) const __LL_EXCEPT__ {
			return this->substr(first, last);
		}

#endif // LL_REAL_CXX23

		#pragma endregion
		#pragma region std
		__LL_NODISCARD__ constexpr type::ptr data() __LL_EXCEPT__ {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr type::cptr data() const __LL_EXCEPT__ {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr type::ptr begin() __LL_EXCEPT__ {
			return this->get(ZERO_UI64);
		}
		__LL_NODISCARD__ constexpr type::cptr begin() const __LL_EXCEPT__ {
			return this->get(ZERO_UI64);
		}
		__LL_NODISCARD__ constexpr type::ptr end() __LL_EXCEPT__ {
			return this->get(this->len());
		}
		__LL_NODISCARD__ constexpr type::cptr end() const __LL_EXCEPT__ {
			return this->get(this->len());
		}

		#pragma endregion
		#pragma region Reverse
	public:
		using SwapFunc = typename __data::SwapFunc;

		constexpr void reverse(SwapFunc swap, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			__data::reverse(this->get(first), this->get(last), swap);
		}

		#pragma endregion
		#pragma region Fill
	public:
		// [TOFIX]
		template<class W>
		//using FillFunc = typename __data::FillFunc<W>;
		using FillFunc = fnc_clss::CompareBool<typename type::cinput, W>;

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
		constexpr void copy(W::cptr src, const len_t size, FillFunc<typename W::type> setFunc,
			const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			len_t this_size = last - first;
			if (!setFunc || size != this_size) return;
			__data::copy<U, W>(src, this->begin(), this_size, setFunc);
		}
		template<class U, class W = traits::template_types<U>>
		constexpr void copy(W::cptr src, const len_t size, const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			len_t this_size = last - first;
			if (size != this_size) return;
			__data::copy<U, W>(src, this->begin(), N);
		}
		template<class U, class W = traits::template_types<U>, len_t N2>
		constexpr void copy(W::ctype(&src)[N2], FillFunc<typename W::type> setFunc,
			const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			len_t this_size = last - first;
			if (!setFunc || N2 != this_size) return;
			__data::copy<U, W>(src, this->begin(), N, setFunc);
		}
		template<class U, class W = traits::template_types<U>, len_t N2>
		constexpr void copy(W::ctype(&src)[N2],
			const len_t first = ZERO_UI64, const len_t last = N - 1) __LL_EXCEPT__ {
			len_t this_size = last - first;
			if (N2 != this_size) return;
			__data::copy<U, W>(src, this->begin(), N);
		}

		#pragma endregion
		#pragma region Shift

		#pragma endregion
		#pragma region Qsort

		#pragma endregion
		#pragma region Other
		template<class U, class W = traits::template_types<U>>
		constexpr void clear(typename W::cinput null, FillFunc<typename W::type> setFunc) __LL_EXCEPT__ {
			this->fill<U, W>(null, setFunc);
		}
		template<class U, class W = traits::get_object_reference_t<U>>
		constexpr void clear(typename W::cinput null) __LL_EXCEPT__ {
			this->fill<U, W>(null);
		}
		constexpr void clear() __LL_EXCEPT__ {
			this->fill<typename type::type>(NULL_ITEM);
		}

		#pragma endregion
	#pragma endregion
};

constexpr int testing() {
	Array<int, 10, 0> arr;
	arr.fill<int>(5);
	arr.clear();
	arr[9] = 8;
	return arr[0];
}

constexpr int val = testing();

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAY_HPP_
