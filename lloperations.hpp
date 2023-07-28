/*
 * lloperations.hpp
 *
 *  Created on: Jun 25, 2023
 *      Author: llanyro
 */

#ifndef LLPC_HEADER_LLOPERATIONS_HPP_
#define LLPC_HEADER_LLOPERATIONS_HPP_

#include "llanytypeslib.h"

namespace llcpp {
namespace header {
namespace operations {

template<class T>
T min(const T v1, const T v2) { return (v1 > v2) ? v2 : v1; }
template<class T>
T minRef(const T& v1, const T& v2) { return (v1 > v2) ? v2 : v1; }

template<class T>
T max(const T v1, const T v2) { return (v1 > v2) ? v1 : v2; }
template<class T>
T maxRef(const T& v1, const T& v2) { return (v1 > v2) ? v1 : v2; }


template<class T>
T minMax(const T minVal, const T val, const T maxVal) { return min(max(minVal, val),maxVal); }
template<class T>
T minMaxRef(const T& minVal, const T& val, const T& maxVal) { return min(max(minVal, val), maxVal); }

template<class T, T minVal, T maxVal>
ll_bool_t isBetween(const T number) {
    return (minVal <= number && number <= maxVal);
}

/*
*   Compares 2 object by sub (-) operator
*   Works good for basic types
*/
template<class T>
i32 comparei32(const void* a, const void* b) {
    return *reinterpret_cast<const T*>(a) - *reinterpret_cast<const T*>(b);
}
/*
*   Compares 2 object by == equal operator
*   Works good for basic types and classes with == operator
*/
template<class T>
ll_bool_t compareBool(const void* a, const void* b) {
    return *reinterpret_cast<const T*>(a) == *reinterpret_cast<const T*>(b);
}

} /* namespace operations */
} /* namespace header */
} /* namespace llcpp */

namespace op = llcpp::header::operations;

#endif /* LLPC_HEADER_LLOPERATIONS_HPP_ */
