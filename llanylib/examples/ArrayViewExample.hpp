/*
 *	ArrayViewExample.hpp
 *
 *	Created on: Sep 27, 2021
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLANYLIB_EXAMPLES_ARRAYVIEWEXAMPLE_HPP_
#define LLANYLIB_EXAMPLES_ARRAYVIEWEXAMPLE_HPP_

#include "../ArrayView.hpp"

namespace llcpp {

constexpr const int v[3] = { 10, 9, 6 };
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
	constexpr ll_bool_t b2 = llcpp::vector::equals({ 10 }, v2);

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

#endif // LLANYLIB_EXAMPLES_ARRAYVIEWEXAMPLE_HPP_
