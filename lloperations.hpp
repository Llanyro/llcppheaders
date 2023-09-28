/*
 * lloperations.hpp
 *
 *  Created on: Jun 25, 2023
 *      Author: llanyro
 */

#ifndef LLCPP_HEADER_LLOPERATIONS_HPP_
#define LLCPP_HEADER_LLOPERATIONS_HPP_

#include "llanytypeslib.hpp"

namespace llcpp {
namespace header {
namespace operations {

template<class T>
constexpr T min(const T v1, const T v2) { return (v1 > v2) ? v2 : v1; }
template<class T>
constexpr T minRef(const T& v1, const T& v2) { return (v1 > v2) ? v2 : v1; }

template<class T>
constexpr T max(const T v1, const T v2) { return (v1 > v2) ? v1 : v2; }
template<class T>
constexpr T maxRef(const T& v1, const T& v2) { return (v1 > v2) ? v1 : v2; }


template<class T>
constexpr T minMax(const T minVal, const T val, const T maxVal) { return min(max(minVal, val),maxVal); }
template<class T>
constexpr T minMaxRef(const T& minVal, const T& val, const T& maxVal) { return min(max(minVal, val), maxVal); }

template<class T, T minVal, T maxVal>
constexpr ll_bool_t isBetween(const T number) {
    return (minVal <= number && number <= maxVal);
}

/*
*   Compares 2 object by sub (-) operator
*   Works good for basic types
*/
template<class T>
constexpr i32 comparei32(const void* a, const void* b) {
    return *reinterpret_cast<const T*>(a) - *reinterpret_cast<const T*>(b);
}
/*
*   Compares 2 object by == equal operator
*   Works good for basic types and classes with == operator
*/
template<class T>
constexpr ll_bool_t compareBool(const void* a, const void* b) {
    return *reinterpret_cast<const T*>(a) == *reinterpret_cast<const T*>(b);
}

template<class T> constexpr T abs(const T& v1, const T& v2) { return 0; }
template<> constexpr ui64 abs(const ui64& v1, const ui64& v2) { return (v1 > v2) ? v1 - v2 : v2 - v1; }
template<> constexpr ui128 abs(const ui128& v1, const ui128& v2) { return { abs(v1.first, v2.first), abs(v1.second, v2.second) }; }



} /* namespace operations */
} /* namespace header */
} /* namespace llcpp */

namespace op = llcpp::header::operations;

#endif /* LLCPP_HEADER_LLOPERATIONS_HPP_ */
