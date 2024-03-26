/*
 *	Array.hpp
 *
 *	Author: Francisco Julio Ruiz Fernandez
 *	Author: llanyro
 *
 *	Version: 4.2
 */

#if defined(LLANYLIB_ARRAY_HPP_) // Guard && version protector
	#if LLANYLIB_ARRAY_MAYOR_ != 4 || LLANYLIB_ARRAY_MINOR_ < 2
		#error "Array.hpp version error!"
	#endif // LLANYLIB_ARRAY_MAYOR_ || LLANYLIB_ARRAY_MINOR_

#else !defined(LLANYLIB_ARRAY_HPP_)
#define LLANYLIB_ARRAY_HPP_
#define LLANYLIB_ARRAY_MAYOR_ 4
#define LLANYLIB_ARRAY_MINOR_ 2

#include "ArrayView.hpp"

namespace llcpp {

template<class T, len_t SIZE>
class LL_SHARED_LIB Array : public ArrayView<T, SIZE> {
	private:
		using __internal__ArrayView__ = ArrayView<T, SIZE>;
		using __internal__Array__ = Array<T, SIZE>;
	public:
		__LL_CLASS_TEMPLATE_TYPE__(T);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__Array__, Array);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__ArrayView__, ArrayView);
		using __type_raw = __ArrayView::__type_raw;
	public:
		constexpr Array() __LL_EXCEPT__ = delete;
		constexpr ~Array() __LL_EXCEPT__ {}

		constexpr Array(__type (&data)[SIZE]) __LL_EXCEPT__ : __ArrayView(data) {}
		constexpr __ref_Array operator=(__type (&data)[SIZE]) __LL_EXCEPT__ {
			__ArrayView::operator=(data);
			return *this;
		}

		constexpr Array(__cref_Array other) __LL_EXCEPT__ : __ArrayView(other) {}
		constexpr __ref_Array operator=(__cref_Array other) __LL_EXCEPT__ {
			__ArrayView::operator=(other);
			return *this;
		}

		constexpr Array(__move_Array) __LL_EXCEPT__ = delete;
		constexpr __ref_Array operator=(__move_Array) __LL_EXCEPT__ = delete;

		__LL_NODISCARD__ constexpr operator __ptr() __LL_EXCEPT__ { return this->data; }
		__LL_NODISCARD__ constexpr __ptr get() __LL_EXCEPT__ { return this->data; }
		__LL_NODISCARD__ constexpr __ptr get(const len_t pos) __LL_EXCEPT__ { return this->data + pos; }

		__LL_NODISCARD__ constexpr __ref operator[] (const len_t pos) __LL_EXCEPT__ {
			return this->data[pos];
		}

		#pragma region Algorithm_DataManipulation
		constexpr void reverse(
			fnc_clss::SwapFunction<T> swap,
			const len_t __begin = 0ull,
			const len_t __end = SIZE - 1
		) __LL_EXCEPT__ {
			algorithm::reverse<T>(this->get(__begin), this->get(__end), swap);
		}
		constexpr void reverse(
			const len_t __begin = 0ull,
			const len_t __end = SIZE - 1
		) __LL_EXCEPT__ {
			algorithm::reverse<T>(this->get(__begin), this->get(__end));
		}

		template<class U = traits::get_object_reference_t<T>>
		constexpr void fill(
			const U object,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) __LL_EXCEPT__ {
			algorithm::fill<T, U>(this->get(__begin), this->get(__end), object);
		}

		template<class U = traits::get_object_reference_t<T>>
		constexpr void shiftLeft(
			const len_t num,
			const U null,
			fnc_clss::SwapFunction<T> swap,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) __LL_EXCEPT__ {
			algorithm::shiftLeft<T, U>(this->get(__begin), this->get(__end), num, null, swap);
		}
		template<class U = traits::get_object_reference_t<T>>
		constexpr void shiftLeft(
			const len_t num,
			const U null,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) __LL_EXCEPT__ {
			algorithm::shiftLeft<T, U>(this->get(__begin), this->get(__end), num, null);
		}

		template<class U = traits::get_object_reference_t<T>>
		constexpr void shifRight(
			const len_t num,
			const U null,
			fnc_clss::SwapFunction<T> swap,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) __LL_EXCEPT__ {
			algorithm::shifRight<T, U>(this->get(__begin), this->get(__end), num, null, swap);
		}
		template<class U = traits::get_object_reference_t<T>>
		constexpr void shifRight(
			const len_t num,
			const U null,
			const len_t __begin = 0ull,
			const len_t __end = SIZE
		) __LL_EXCEPT__ {
			algorithm::shifRight<T, U>(this->get(__begin), this->get(__end), num, null);
		}

		#pragma endregion
		#pragma region std
		__LL_NODISCARD__ constexpr __ptr begin() __LL_EXCEPT__ {
			return this->get();
		}
		__LL_NODISCARD__ constexpr __ptr end() __LL_EXCEPT__ {
			return this->get(this->operator len_t());
		}

		#pragma endregion
};

} // namespace llcpp

#endif // LLANYLIB_ARRAY_HPP_
