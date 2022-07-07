/*
 * llanysimpleprint.hpp
 *
 *  Created on: Nov 16, 2020
 *      Author: llanyro
 */

#ifndef CORE_LLANYSIMPLEPRINT_HPP_
#define CORE_LLANYSIMPLEPRINT_HPP_

#include <iostream>

#define PRINT(a) std::cout << a
#define PRINT2(a, b) std::cout << a << " " << b

#define PRINTLN(a) std::cout << a << std::endl
#define PRINT2LN(a, b) std::cout << a << " " << b << std::endl

#define TAB putchar('\t')
#define LN putchar('\n')
#define ENDL LN;

#endif /* CORE_LLANYSIMPLEPRINT_HPP_ */
