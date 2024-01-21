/*
*	llanytypeslib.hpp
*
*	Created on: Feb 28, 2022
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
*/

#ifndef LLCPP_HEADER_LLANYTYPESLIB_HPP_
#define LLCPP_HEADER_LLANYTYPESLIB_HPP_

//#include "llanytypesbase.hpp" // Already includes "llanytypesbase.hpp"
#include "StrPair.hpp" // Already includes "llanytypesbase.hpp"

namespace llcpp {

namespace functional {

/*!
 *	@template False
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
typedef i32 (*Comparei32)(const void* __t1, const void* __t2);
/*!
 *	@template False
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
typedef ll_bool_t (*CompareBool)(const void* __t1, const void* __t2);

/*!
 *	@template False
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
 *	@param[in] __extra__ Extra data to being used by user
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
typedef i32 (*Comparei32Extra)(const void* __t1, const void* __t2, void* __extra__);
/*!
 *	@template False
 *	@brief Function type to compare 2 objects
 *
 *	@param[in] __t1 First object to compare
 *	@param[in] __t2 Second object to compare
 *	@param[in] __extra__ Extra data to being used by user
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
typedef ll_bool_t (*CompareBoolExtra)(const void* __t1, const void* __t2, void* __extra__);

namespace classic {
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
template<class __T>
using SearchFunctioni32 = i32(*)(const __T& __t1, const __T& __t2);
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
template<class __T>
using SearchFunctionBool = ll_bool_t(*)(const __T& __t1, const __T& __t2);

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
template<class __T>
using SwapFunction = void(*)(const __T& __t1, const __T& __t2);

} // namespace classic

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
template<class __T> using SearchFunctioni32 = std::function<i32(const __T& __t1)>;
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
template<class __T> using SearchFunctionBool = std::function<ll_bool_t(const __T& __t1)>;

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
template<class __T>
using SwapFunction = std::function<void(__T& __t1, __T& __t2)>;

} // namespace lambda

} // namespace functional

#pragma region GenralExpresions
template<class __T, len_t __N>
__LL_NODISCARD__ constexpr StrPair pair_str(__T (&str)[__N]) __LL_EXCEPT__ {
	return llcpp::StrPair{ str, __N - 1 };
}
/*!
 *	@template True
 *	@brief Check if type inherits from other class
 *
 *	@param[in] v Pointer of class to check
 *
 *	@return If class __T inherits from T2 true sis returned
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
template<class __U, class __T>
__LL_NODISCARD__ constexpr ll_bool_t isSubType(const __T* v) __LL_EXCEPT__ {
	return static_cast<ll_bool_t>(dynamic_cast<const __U*>(v));
}

constexpr ll_bool_t LL_TRUE = true;
constexpr ll_bool_t LL_FALSE = false;

constexpr ll_string_t TRUE_STRING = "True";
constexpr ll_string_t FALSE_STRING = "False";

//constexpr StrPair TRUE_STR_PAIR = pair_str("True");
//constexpr StrPair FALSE_STR_PAIR = pair_str("False");

#pragma endregion

namespace traits {

struct TestClassBase {
	operator bool() const {
		return false;
	}
	void swap(TestClassBase& other) {}
	ll_bool_t swap_s(TestClassBase& other) {}
	void clear() {}
	ll_bool_t clear_s() {}
	int operator<=>(const TestClassBase& other) const { return 0; }
};

struct TestClass : public TestClassBase {};

struct TestClassBad {
	void swap(TestClass& other) {}
	ll_bool_t swap_s(TestClass& other) {}
	void clear() {}
	ll_bool_t clear_s() {}
};

struct TestClassPrivateCopy {
	private:
		TestClassPrivateCopy& operator=(const TestClassPrivateCopy&) = delete;
		TestClassPrivateCopy& operator=(TestClassPrivateCopy&&) = delete;
};

struct TestClassNoCopy {
	TestClassNoCopy& operator=(const TestClassNoCopy&) = delete;
	TestClassNoCopy& operator=(TestClassNoCopy&&) = delete;
};

template<class __T>
inline constexpr ll_bool_t is_basic_type_v = std::_Is_any_of_v<__T, ui8, ui16, ui32, ui64, i8, i16, i32, i64, f32, f64>;

template <class __T, class __V>
struct has_type_operator {
    template <class __U, ENABLE_FUNCTION_PARAM(!is_basic_type_v<__U>)>
    static auto test(__U* p) -> decltype(p->operator __V(), std::true_type{});

	template <class __U, ENABLE_FUNCTION_PARAM(is_basic_type_v<__U>)>
	static auto test(__U* p) ->std::false_type;
	
	template <class>
	static auto test(...) -> std::false_type;

	using val = decltype(test<__T>(nullptr));

};

template <class __T, class __V>
inline constexpr ll_bool_t has_type_operator_v = has_type_operator<__T, __V>::val::value;

#define __TEMPLATE_HAS_FUNCTION__(name, function) \
template <class __T> \
struct has_##name## { \
	template <class __U, ENABLE_FUNCTION_PARAM(!is_basic_type_v<__U>)> \
	static auto test(__U* p) -> decltype(##function##, std::true_type{}); \
	template <class __U, ENABLE_FUNCTION_PARAM(is_basic_type_v<__U>)> \
	static auto test(__U* p)->std::false_type; \
	template <class> \
	static auto test(...)->std::false_type; \
	static constexpr ll_bool_t value = decltype(test<__T>(nullptr))::value; \
	using val = decltype(test<__T>(nullptr)); \
}; \
template <class __T> \
inline constexpr ll_bool_t has_##name##_v = has_##name##<__T>::val::value

#define __TEMPLATE_HAS_SIMPLE_FUNCTION__(function) __TEMPLATE_HAS_FUNCTION__(function, p->##function##())
/*
ll_bool_t c_f() {}

using t = decltype(TestClass::clear_s);
using t2 = decltype(c_f);

template<class T>
using Temp = ll_bool_t(T::*)();

static_assert(std::is_same_v<decltype(TestClass::clear_s), Temp<TestClass>>, "No");

template<class T>
constexpr ll_bool_t is_same_function_decl = std::is_same_v<decltype(T::clear_s), decltype(Temp<T>)>;

constexpr ll_bool_t is_same_function_decl2 = is_same_function_decl<TestClassBase>;

*/


__TEMPLATE_HAS_FUNCTION__(swap, p->swap(*p));
__TEMPLATE_HAS_FUNCTION__(swap_s, p->swap_s(*p));
__TEMPLATE_HAS_FUNCTION__(copy_operator, p->operator=(*p));
__TEMPLATE_HAS_FUNCTION__(move_operator, p->operator=(std::move(*p)));
__TEMPLATE_HAS_SIMPLE_FUNCTION__(clear);


__TEMPLATE_HAS_FUNCTION__(compare_operator, p->operator<=>(*p));


//constexpr ll_bool_t test_1_obj2 = has_type_operator_v<TestClassBase, ll_bool_t>;
//constexpr ll_bool_t test_1_obj = has_type_operator_v<TestClass, ll_bool_t>;
//constexpr ll_bool_t test_1_int = has_type_operator_v<int, ll_bool_t>;
//
//constexpr ll_bool_t test_2_obj = has_clear_v<TestClass>;
//constexpr ll_bool_t test_2_int = has_clear_v<int>;
//
//constexpr ll_bool_t test_2_obj = has_swap_v<TestClass>;
//constexpr ll_bool_t test_2_int = has_swap_v<int>;

} // namespace traits

/*!
 *	@template True
 *	@brief Gets a string of a bool
 *
 *	Gives a user a string that represents the bool provided
 *	true will be : "True"
 *	false will be: "False"
 *
 *	@param[in] v Bool value
 *
 *	@return String that represents bool value
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
//__LL_NODISCARD__ constexpr ll_string_t getBoolString(const ll_bool_t v) {
//	return v ? TRUE_STRING : FALSE_STRING;
//}
/*!
 *	@template True
 *	@brief Gets a StrPair of a bool
 *
 *	Gives a user a string that represents the bool provided
 *	true will be : { "True", 4 }
 *	false will be: { "False", 5 }
 *
 *	@param[in] v Bool value
 *
 *	@return StrPair that represents bool value
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
//__LL_NODISCARD__ constexpr StrPair getBoolStringPair(const ll_bool_t v) {
//	return v ? TRUE_STR_PAIR : FALSE_STR_PAIR;
//}

template<class __T, len_t N>
__LL_NODISCARD__ constexpr len_t arraySize(__T const (&a)[N]) { return N; }

namespace enums {

/*!
 *	@template True
 *	@brief Casts an enum to given type
 *
 *	This is the same to do as static_cast<__T>
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
__LL_NODISCARD__ __LL_CONSTEXPR__ ValueType asType(const EnumClass enumValue) {
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

#endif /* LLCPP_HEADER_LLANYTYPESLIB_HPP_ */
