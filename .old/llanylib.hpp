/*
 *	llanylib.hpp
 *
 *	Created on: Feb 28, 2022
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLCPP_HEADER_LLANYLIB_HPP_
#define LLCPP_HEADER_LLANYLIB_HPP_

#include "definitions.hpp"
#include "traits.hpp"

namespace llcpp {

/*!
 *	@template True
 *	@brief Check if type inherits from other class
 *
 *	@param[in] v Pointer of class to check
 *
 *	@return If class T inherits from T2 true sis returned
 *
 *	@constexpr True
 *
 *	@thread_safety This function may be called from any thread.
 *
 *	@sa @ref llcpp
 *
 *	@since Added in version 1.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
template<class BaseType, class ObjectType>
__LL_NODISCARD__ constexpr ll_bool_t isSubType(const ObjectType* v) __LL_EXCEPT__ {
	return static_cast<ll_bool_t>(dynamic_cast<const BaseType*>(v));
}

template<class T, len_t N>
__LL_NODISCARD__ constexpr len_t arraySize(T const (&a)[N]) { return N; }

//template<class T, len_t N>
//__LL_NODISCARD__ constexpr std::pair<T, len_t> toStruct(T const (&a)[N]) { return { a, N }; }

namespace enums {

/*!
 *	@template True
 *	@brief Casts an enum to given type
 *
 *	This is the same to do as static_cast<T>
 *
 *	@param[in] enumValue Enum value to cast
 *
 *	@constexpr True
 *
 *	@return Value as type provided
 *
 *	@thread_safety This function may be called from any thread.
 *
 *	@sa @ref llcpp
 *
 *	@since Added in version 1.0.
 *
 *	@ingroup llcpp
 *	@ingroup enums
 */
template<class ValueType, class EnumClass>
__LL_NODISCARD__ constexpr ValueType asType(const EnumClass enumValue) {
	return static_cast<ValueType>(enumValue);
}

//template<class ValueType, class EnumClass, class... EnumClasses>
//constexpr ValueType enumOrOperation() {
//	return ValueType();
//}

//template<class ValueType, class EnumClass, class... EnumClasses>
//constexpr ValueType enumOrOperation(const EnumClass _enum, const EnumClasses... _enums) {
//	return asType<ValueType, EnumClass>(_enum) | enumOrOperation<ValueType, EnumClass, EnumClasses...>(_enums...);
//}

} // namespace enums

} // namespace llcpp

#endif /* LLCPP_HEADER_LLANYLIB_HPP_ */
