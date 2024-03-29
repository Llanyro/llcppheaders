/*
 *	StringViewExample.hpp
 *
 *	Created on: Sep 27, 2021
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLANYLIB_EXAMPLES_STRINGVIEWEXAMPLE_HPP_
#define LLANYLIB_EXAMPLES_STRINGVIEWEXAMPLE_HPP_

#include "../StringView.hpp"
#include "algorithmExample.hpp"

namespace llcpp {

/************************************* ArrayView Storage *************************************/

constexpr auto stringview_01 = StringView(algorithm::str1);
constexpr auto stringview_02 = StringView(algorithm::str2);
constexpr auto stringview_03 = StringView(algorithm::str3);
constexpr auto stringview_04 = StringView(algorithm::str4);
constexpr auto stringview_05 = StringView("");
constexpr auto stringview_06 = StringView("A");

constexpr StringView HOLA_WORLD = algorithm::str4;

constexpr ll_bool_t res1 = stringview_06.starts_with("A");
constexpr auto res2 = stringview_06.starts_with<true>('A');

} // namespace llcpp

#endif // LLANYLIB_EXAMPLES_STRINGVIEWEXAMPLE_HPP_
