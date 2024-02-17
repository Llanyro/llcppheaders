/*
 *	types_extra.hpp
 *
 *	Created on: Feb 28, 2022
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLANYLIB_TYPES_EXTRA_HPP_
#define LLANYLIB_TYPES_EXTRA_HPP_

#include "definitions.hpp"
#include "types.hpp"

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4365) // ignore conversion from long to ui32 (signed/unsigned mismatch)
#endif // WINDOWS_SYSTEM

// Added here to fix inline error /W4
#include <functional>

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

namespace llcpp {
namespace functional {
namespace lambda {

/*!
 *	@template True
 *	@brief Function type to compare 2 objects
 *
 *	This needs to return a value to check if object __t1 is same to object __t2
 *	The implementation of this function needs to return:
 *		 0 if both are the same
 *		-1 if __t1 smaller
 *		 1 if __t1 is bigger
 * 
 *	@param[in] __t1 First object to compare
 *	@param[in] __t2 Second object to compare
 *
 *	@return Comparacion result
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
template<class T>
using SearchFunctioni32 = std::function<i32(const T& __t1)>;
/*!
 *	@template True
 *	@brief Function type to compare 2 objects
 *
 *	@param[in] __t1 First object to compare
 *	@param[in] __t2 Second object to compare
 *
 *	@return True if __t1 is same as __t2
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref comparator
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
template<class T>
using SearchFunctionBool = std::function<ll_bool_t(const T& __t1)>;

/*!
 *	@template True
 *	@brief Swaps 2 objects
 *
 *	@param[in] __t1 First object to swap
 *	@param[in] __t2 Second object to swap
 *
 *	@thread_safety defined by implementation
 *	@thread_protection defined by implementation
 *
 *	@sa @ref swap
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
template<class T>
using SwapFunction = std::function<void(T& __t1, T& __t2)>;

} // namespace lambda
} // namespace functional
} // namespace llcpp

#endif // LLANYLIB_TYPES_EXTRA_HPP_
