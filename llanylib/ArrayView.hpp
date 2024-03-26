/*
 *	ArrayView.hpp
 *
 *	Author: Francisco Julio Ruiz Fernandez
 *	Author: llanyro
 *
 *	Version: 4.2
 */

#if defined(LLANYLIB_ARRAYVIEW_HPP_) // Guard && version protector
	#if LLANYLIB_ARRAYVIEW_MAYOR_ != 4 || LLANYLIB_ARRAYVIEW_MINOR_ < 2
		#error "ArrayView.hpp version error!"
	#endif // LLANYLIB_ARRAYVIEW_MAYOR_ || LLANYLIB_ARRAYVIEW_MINOR_

#else !defined(LLANYLIB_ARRAYVIEW_HPP_)
#define LLANYLIB_ARRAYVIEW_HPP_
#define LLANYLIB_ARRAYVIEW_MAYOR_ 4
#define LLANYLIB_ARRAYVIEW_MINOR_ 2

#include "algorithm.hpp"

namespace llcpp {

template<class T, len_t SIZE>
class LL_SHARED_LIB ArrayView {
	private:
		using __internal__ArrayView__ = ArrayView<T, SIZE>;
	public:
		static_assert(SIZE > 0, "Array cannot have a size of 0");
	public:
		__LL_CLASS_TEMPLATE_TYPE__(T);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__ArrayView__, ArrayView);
		using __type_raw = std::remove_const_t<__type>;
	protected:
		__ptr data;
		ll_bool_t ignoreLastElement;	// Usefull on literal strings like: "Hello world"
	public:
		constexpr ArrayView() __LL_EXCEPT__ = delete;
		constexpr ~ArrayView() __LL_EXCEPT__ {}

		constexpr ArrayView(__type (&data)[SIZE]) __LL_EXCEPT__
			: data(data), ignoreLastElement(LL_FALSE) {}
		constexpr ArrayView(__type (&data)[SIZE], const ll_bool_t ignoreLastElement) __LL_EXCEPT__
			: data(data), ignoreLastElement(ignoreLastElement) {}
		constexpr __ref_ArrayView operator=(__type(&data)[SIZE]) __LL_EXCEPT__ {
			this->data = data;
			this->ignoreLastElement = LL_FALSE;
			return *this;
		}

		constexpr ArrayView(__cref_ArrayView other) __LL_EXCEPT__
			: data(other.data), ignoreLastElement(other.ignoreLastElement) {}
		constexpr __ref_ArrayView operator=(__cref_ArrayView other) __LL_EXCEPT__ {
			this->data = other.data;
			this->ignoreLastElement = other.ignoreLastElement;
			return *this;
		}

		constexpr ArrayView(__move_ArrayView) __LL_EXCEPT__ = delete;
		constexpr __ref_ArrayView operator=(__move_ArrayView) __LL_EXCEPT__ = delete;

		__LL_NODISCARD__ constexpr operator __cptr() const __LL_EXCEPT__ { return this->data; }
		__LL_NODISCARD__ constexpr __cptr get(const len_t pos = 0ull) const __LL_EXCEPT__ {
			return this->data + pos;
		}

		__LL_NODISCARD__ constexpr operator len_t() const __LL_EXCEPT__ {
			return this->ignoreLastElement ? SIZE - 1 : SIZE;
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
			return !this->empty() && static_cast<ll_bool_t>(this->data);
		}

		__LL_NODISCARD__ constexpr __cref operator[] (const len_t pos) const __LL_EXCEPT__ {
			return this->data[pos];
		}

		#pragma region Algorithm
		#pragma region Compare
		template<ll_bool_t GET_DATA = LL_FALSE, len_t size2, class U = std::conditional_t<GET_DATA, algorithm::CompareData<T>, cmp_t>>
		__LL_NODISCARD__ constexpr U compare(__type(&_array)[size2], fnc_clss::Compare<T> cmp) const __LL_EXCEPT__ {
			static_assert(SIZE == size2, "Size of both ArrayView needs to be same size");
			return algorithm::compare<T, GET_DATA, U>(this->begin(), _array, SIZE, cmp);
		}
		template<ll_bool_t GET_DATA = LL_FALSE, len_t size2, class U = std::conditional_t<GET_DATA, algorithm::CompareData<T>, cmp_t>>
		__LL_NODISCARD__ constexpr U compare(__type(&_array)[size2]) const __LL_EXCEPT__ {
			static_assert(SIZE == size2, "Size of both ArrayView needs to be same size");
			return algorithm::compare<T, GET_DATA, U>(this->begin(), _array, SIZE);
		}

		template<ll_bool_t GET_DATA = LL_FALSE, class U = std::conditional_t<GET_DATA, algorithm::CompareData<T>, cmp_t>>
		__LL_NODISCARD__ constexpr U compare(__cref_ArrayView other, fnc_clss::Compare<T> cmp) const __LL_EXCEPT__ {
			return algorithm::compare<T, GET_DATA, U>(this->begin(), other.begin(), SIZE, cmp);
		}
		template<ll_bool_t GET_DATA = LL_FALSE, class U = std::conditional_t<GET_DATA, algorithm::CompareData<T>, cmp_t>>
		__LL_NODISCARD__ constexpr U compare(__cref_ArrayView other) const __LL_EXCEPT__ {
			return algorithm::compare<T, GET_DATA, U>(this->begin(), other.begin(), SIZE);
		}

		#pragma endregion
		#pragma region Equals
		template<len_t size2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(__type(&_array)[size2], fnc_clss::Compare<T> cmp) const __LL_EXCEPT__ {
			return algorithm::equals<T, SIZE, size2>(this->begin(), _array, cmp);
		}
		template<len_t size2>
		__LL_NODISCARD__ constexpr ll_bool_t equals(__type(&_array)[size2]) const __LL_EXCEPT__ {
			return algorithm::equals<T, SIZE, size2>(this->begin(), _array);
		}

		__LL_NODISCARD__ constexpr ll_bool_t equals(__cref_ArrayView other, fnc_clss::Compare<T> cmp) const __LL_EXCEPT__ {
			return algorithm::equals<T, SIZE>(this->begin(), other.begin(), cmp);
		}
		__LL_NODISCARD__ constexpr ll_bool_t equals(__cref_ArrayView other) const __LL_EXCEPT__ {
			return algorithm::equals<T, SIZE>(this->begin(), other.begin());
		}


		template<len_t size2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__type(&_array)[size2]) const __LL_EXCEPT__ {
			return algorithm::equals<T, SIZE, size2>(this->begin(), _array);
		}
		template<len_t size2>
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(__type(&_array)[size2]) const __LL_EXCEPT__ {
			return !this->operator==(_array);
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator==(__cref_ArrayView other) const __LL_EXCEPT__ {
			return algorithm::equals<T, SIZE>(this->begin(), other.begin());
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(__cref_ArrayView str) const __LL_EXCEPT__ {
			return !this->operator==(str);
		}

		template<len_t size2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ArrayView<T, size2>& other) const __LL_EXCEPT__ {
			return algorithm::equals<T, SIZE, size2>(this->begin(), other.begin());
		}
		template<len_t size2>
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const ArrayView<T, size2>& str) const __LL_EXCEPT__ {
			return !this->operator==(str);
		}

		#pragma endregion
		#pragma region Find
		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr const T* find(
			const U object,
			fnc_clss::CompareBool<T> cmp,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::find<T, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr const T* find(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::find<T, U>(this->get(__begin), this->get(__end), object);
		}

		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr len_t find_pos(
			const U object,
			fnc_clss::CompareBool<T> cmp,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::find_pos<T, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr len_t find_pos(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::find_pos<T, U>(this->get(__begin), this->get(__end), object);
		}

		#pragma endregion
		#pragma region rFind
		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr const T* rfind(
			const U object,
			fnc_clss::CompareBool<T> cmp,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::rfind<T, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr const T* rfind(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::rfind<T, U>(this->get(__begin), this->get(__end), object);
		}

		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr len_t rfind_pos(
			const U object,
			fnc_clss::CompareBool<T> cmp,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::rfind_pos<T, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr len_t rfind_pos(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::rfind_pos<T, U>(this->get(__begin), this->get(__end), object);
		}

		#pragma endregion
		#pragma region Other
		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr ll_bool_t all(
			const U object,
			fnc_clss::CompareBool<T> cmp,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::all<T, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr ll_bool_t all(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::all<T, U>(this->get(__begin), this->get(__end), object);
		}

		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr ll_bool_t any(
			const U object,
			fnc_clss::CompareBool<T> cmp,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::any<T, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr ll_bool_t any(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::any<T, U>(this->get(__begin), this->get(__end), object);
		}

		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr ll_bool_t none(
			const U object,
			fnc_clss::CompareBool<T> cmp,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::none<T, U>(this->get(__begin), this->get(__end), object, cmp);
		}
		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr ll_bool_t none(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) const __LL_EXCEPT__ {
			return algorithm::none<T, U>(this->get(__begin), this->get(__end), object);
		}

		#pragma endregion
		#pragma region BinarySearch
		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr const T* binarysearch(const U object) const __LL_EXCEPT__ {
			return this->end();// algorithm::binarysearch<T, U>(this->get(__begin), this->get(__end), object);
		}
		template<class U = traits::get_object_reference_t<T>>
		__LL_NODISCARD__ constexpr len_t binarysearch_pos(const U object) const __LL_EXCEPT__ {
			return algorithm::npos; //algorithm::binarysearch_pos<T, U>(this->get(__begin), this->get(__end), object);
		}

		#pragma endregion

		#pragma endregion
		#pragma region std
		__LL_NODISCARD__ constexpr __cptr begin() const __LL_EXCEPT__ {
			return this->get();
		}
		__LL_NODISCARD__ constexpr __cptr end() const __LL_EXCEPT__ {
			return this->get(this->operator len_t());
		}

		#pragma endregion
};

//template<len_t SIZE>
//using StringView = ArrayView<const ll_char_t, SIZE>;
//template<len_t SIZE>
//using StringView_u = ArrayView<const ll_uchar_t, SIZE>;

} // namespace llcpp

#endif // LLANYLIB_ARRAYVIEW_HPP_
