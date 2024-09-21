//////////////////////////////////////////////
//	traits.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITS_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITS_MAYOR_ != 10 || LLANYLIB_TRAITS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits.hpp version error!"
		#else
			#error "traits.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITS_MAYOR_ || LLANYLIB_TRAITS_MINOR_

#else !defined(LLANYLIB_TRAITS_HPP_)
#define LLANYLIB_TRAITS_HPP_
#define LLANYLIB_TRAITS_MAYOR_ 10
#define LLANYLIB_TRAITS_MINOR_ 0

#define LL_TRAITS_TEST

#include "types_base_extra.hpp"

#if defined(LL_TRAITS_TEST)
	#include "examples/traits_test_class.hpp"
#endif

#include <type_traits>

namespace llcpp {
namespace meta {
namespace traits {

#pragma region InternalTraits

namespace __traits__ {

#pragma region ThreeWayComparasion
/*
template<class _T, class _U>
struct get_three_way_comparasion_function_type {
	#pragma region Types
	public:
		// Class related
		using _MyType	= get_three_way_comparasion_function_type;

		// Types
		using T			= _T;
		using U			= _U;
		using t_cinput	= traits::cinput<T>;
		using u_cinput	= traits::cinput<U>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(traits::is_valid_type_checker_v<U>,
			"type_checker<U> detected an invalid type!");

	#pragma endregion
	#pragma region Functions
	public:
		template<class>
		static constexpr auto test(auto(T::* _)(u_cinput) const noexcept) noexcept ->
			traits::true_type<std::invoke_result_t<decltype(_), T>>;
		template<class>
		static constexpr auto test(...) noexcept -> traits::false_type<llcpp::Emptyclass>;

		using container = decltype(_MyType::test<T>(&T::operator<=>));
		using type = typename container::U;

	#pragma endregion
};

template<class T, class U>
struct get_three_way_comparasion_function_type {
	#pragma region Types
	public:
		// Class related
		using _MyType	= get_three_way_comparasion_function_type;

		// Types
		using T			= _T;
		using U			= _U;
		using t_cinput	= traits::cinput<T>;
		using u_cinput	= traits::cinput<U>;
		using T_Class	= traits::conditional_t<std::is_class_v<T>, T, llcpp::Emptyclass>;

		// Type if basic type
		using no_function_type = traits::conditional_t<
			!traits::is_all_of_a_basic_type_v<T, U>,
			traits::false_type<llcpp::Emptyclass>,
			traits::conditional_t<
				traits::is_any_of_a_floating_type_v<T, U>,
				traits::true_type<std::partial_ordering>,
				traits::true_type<std::strong_ordering>
			>
		>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(traits::is_valid_type_checker_v<U>,
			"type_checker<U> detected an invalid type!");

	#pragma endregion
	#pragma region Functions
	public:
		using container = no_function_type;
		using type = typename container::U;

	#pragma endregion
};
*/
#pragma endregion

} // namespace __traits__

#pragma endregion
#pragma region MyRegion
//template<class _Checker, class _VoidType = void>
//struct check_valid_types {
//	// Class related
//	using _MyType	= check_valid_types;
//
//	// Types and enums
//	using Checker	= _Checker;
//	using VoidType	= _VoidType;
//	template<class T, class _U = VoidType>
//	using return_type = traits::conditional_t<Checker::is_valid_v<T>, T, _U>;
//
//	static_assert(traits::is_valid_type_checker_v<Checker>,
//		"type_checker<Checker> detected an invalid type!");
//	static_assert(traits::is_valid_class_checker_v<Checker>,
//		"class_checker<Checker> detected an invalid class type!");
//
//	template<class T>
//	static constexpr auto get_first() noexcept -> return_type<T, VoidType>;
//	// Do not edit this function to decltype(_MyType::get_first<Args...>())
	// It will lead an error an this wont work
//	template<class T, class... Args>
//	static constexpr auto get_first() noexcept -> return_type<T, decltype(get_first<Args...>())>;
//	template<class... Args>
//	using type = decltype(_MyType::get_first<Args...>());
//};

#define __LL_GENERIC_CHECKER__(name, checker) \
	struct is_valid_##name##_checker { \
		template<class T> \
		static constexpr ll_bool_t is_valid_v = ##checker##<T>; \
	}

#pragma endregion

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITS_HPP_
