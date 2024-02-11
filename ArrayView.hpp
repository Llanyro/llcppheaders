/*
 *	ArrayView.hpp
 *
 *	Created on: Sep 27, 2021
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLCPP_HEADER_ARRAYVIEW_HPP_
#define LLCPP_HEADER_ARRAYVIEW_HPP_

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

constexpr const int v[3] = {10, 9, 6};
constexpr const int v2[3] = { 10, 9, 6 };
constexpr const int v3[3] = { 10, 9, 5 };
constexpr const int v4[4] = { 10, 9, 6, 0 };

constexpr auto arrview = ArrayView(v);
constexpr auto arrview2 = ArrayView(v2);
constexpr auto arrview3 = ArrayView(v3);
constexpr auto arrview4 = ArrayView(v4);

constexpr ArrayView HOLA_WORLD = "Hola world!";

constexpr auto stringview = ArrayView("Hola mundo");
constexpr auto stringview2 = ArrayView(HOLA_WORLD);

constexpr const ll_char_t stringview_char = stringview2[2];

void a() {

	constexpr ll_bool_t string_bool = stringview.operator==(stringview2);
	constexpr ll_bool_t string_bool2 = stringview.operator==(stringview);

	constexpr ll_bool_t b = llcpp::vector::equals(v, v2);
	constexpr ll_bool_t b2 = llcpp::vector::equals({10}, v2);

	constexpr ll_bool_t b3 = arrview2.operator==(arrview);
	constexpr ll_bool_t b3_1 = arrview3.operator==(arrview);
	constexpr ll_bool_t b3_2 = arrview4.operator==(arrview);
	constexpr ll_bool_t b3_3 = arrview2.operator==(arrview);

	constexpr ll_bool_t b3_4 = arrview3.operator==(v);
	constexpr ll_bool_t b3_5 = arrview3.operator==(v2);
	constexpr ll_bool_t b3_6 = arrview3.operator==(v4);

	constexpr ll_bool_t b3_7 = arrview.operator==(v);
	constexpr ll_bool_t b3_8 = arrview.operator==(v2);
	constexpr ll_bool_t b3_9 = arrview.operator==(v3);
	constexpr ll_bool_t b3_10 = arrview.operator==(v4);

	constexpr ll_bool_t b4 = llcpp::vector::equals(v, v3);
	constexpr ll_bool_t b5 = llcpp::vector::equals(v2, v3);
	constexpr ll_bool_t b6 = llcpp::vector::equals(v, v4);
	constexpr ll_bool_t b7 = llcpp::vector::equals(v2, v4);
	constexpr ll_bool_t b7 = llcpp::vector::equals(v3, v4);
}


} // namespace llcpp

#endif /* LLCPP_HEADER_ARRAYVIEW_HPP_ */
