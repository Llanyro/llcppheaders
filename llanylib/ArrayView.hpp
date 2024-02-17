/*
 *	ArrayView.hpp
 *
 *	Created on: Sep 27, 2021
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLANYLIB_ARRAYVIEW_HPP_
#define LLANYLIB_ARRAYVIEW_HPP_

#include "vector.hpp"

namespace llcpp {

template<class T, len_t size>
class LL_SHARED_LIB ArrayView {
	private:
		using __internal__ArrayView__ = ArrayView<T, size>;
	public:
		static_assert(size > 0, "Array cannot have a size of 0");
	public:
		__LL_CLASS_TEMPLATE_TYPE__(T);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__ArrayView__, ArrayView);
		using __type_raw = std::remove_const_t<T>;
	protected:
		__ptr data;
	public:
		constexpr ArrayView() = delete;
		constexpr ~ArrayView() __LL_EXCEPT__ {}

		constexpr ArrayView(__type (&data)[size]) __LL_EXCEPT__ : data(data) {}
		constexpr __ref_ArrayView operator=(__type (&data)[size]) __LL_EXCEPT__ {
			this->data = data;
			return *this;
		}

		constexpr ArrayView(__cref_ArrayView other) __LL_EXCEPT__ = default;
		constexpr __ref_ArrayView operator=(__cref_ArrayView other) __LL_EXCEPT__ = default;

		constexpr ArrayView(__move_ArrayView other) = delete;
		constexpr __ref_ArrayView operator=(__move_ArrayView other) = delete;

		__LL_NODISCARD__ constexpr operator __ptr() const __LL_EXCEPT__ { return this->data; }
		__LL_NODISCARD__ constexpr __ptr ptr() const __LL_EXCEPT__ { return this->data; }
		__LL_NODISCARD__ constexpr __type operator[] (const len_t pos) const __LL_EXCEPT__ { return this->data[pos]; }
		__LL_NODISCARD__ constexpr operator len_t() const __LL_EXCEPT__ { return size; }
		__LL_NODISCARD__ constexpr operator ll_bool_t() const __LL_EXCEPT__ {
			return
				static_cast<ll_bool_t>(this->data) &&
				static_cast<ll_bool_t>(size > 0);
		}

		template<len_t size2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__type(&data)[size2]) const __LL_EXCEPT__ {
			return vector::equals<T, size, size2>(this->data, data);
		}
		template<len_t size2>
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(__type(&data)[size2]) const __LL_EXCEPT__ {
			return !this->operator==(data);
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator==(__cref_ArrayView other) const __LL_EXCEPT__ {
			return vector::equals<T, size>(this->data, other.data);
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(__cref_ArrayView str) const __LL_EXCEPT__ {
			return !this->operator==(str);
		}

		template<len_t size2>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ArrayView<T, size2>& other) const __LL_EXCEPT__ {
			return vector::equals<T, size, size2>(this->data, data);
		}
		template<len_t size2>
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const ArrayView<T, size2>& str) const __LL_EXCEPT__ {
			return !this->operator==(str);
		}
};

//template<len_t size>
//using StringView = ArrayView<const ll_char_t, size>;
//template<len_t size>
//using StringView_u = ArrayView<const ll_uchar_t, size>;

} // namespace llcpp

#endif // LLANYLIB_ARRAYVIEW_HPP_
