//////////////////////////////////////////////
//	traits_three_way_compare.hpp			//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSTHREEWAYCOMPARE_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSTHREEWAYCOMPARE_MAYOR_ != 10 || LLANYLIB_TRAITSTHREEWAYCOMPARE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_three_way_compare.hpp version error!"
		#else
			#error "traits_three_way_compare.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSTHREEWAYCOMPARE_MAYOR_ || LLANYLIB_TRAITSTHREEWAYCOMPARE_MINOR_

#else !defined(LLANYLIB_TRAITSTHREEWAYCOMPARE_HPP_)
#define LLANYLIB_TRAITSTHREEWAYCOMPARE_HPP_
#define LLANYLIB_TRAITSTHREEWAYCOMPARE_MAYOR_ 10
#define LLANYLIB_TRAITSTHREEWAYCOMPARE_MINOR_ 0

#include "traits_checker.hpp"
//#include "traits_primitive_types.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<class _T, class _U, ll_bool_t IS_CLASS>
struct get_three_way_comparasion_return {
	#pragma region Types
	public:
		// Class related
		using _MyType	= get_three_way_comparasion_return;

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
		static_assert(std::is_class_v<T>,
			"T is not a class!");

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

template<class _T, class _U>
struct get_three_way_comparasion_return<_T, _U, llcpp::FALSE> {
	#pragma region Types
	public:
		// Class related
		using _MyType	= get_three_way_comparasion_return;

		// Types
		using T			= _T;
		using U			= _U;
		using t_cinput	= traits::cinput<T>;
		using u_cinput	= traits::cinput<U>;

		// Type if basic type
		using no_function_type = std::conditional_t<
			!traits::is_all_of_a_basic_type_v<T, U>,
			traits::false_type<llcpp::Emptyclass>,
			std::conditional_t<
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
		static_assert(!std::is_class_v<T>,
			"T is not a class!");

	#pragma endregion
	#pragma region Functions
	public:
		using container = no_function_type;
		using type = typename container::U;

	#pragma endregion
};

/*template<class _T, class _U>
struct get_three_way_comparasion_return {
	#pragma region Types
	public:
		// Class related
		using _MyType	= get_three_way_comparasion_return;

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
		static_assert(std::is_class_v<T>,
			"T is not a class!");

	#pragma endregion
	#pragma region Functions
	public:
		template<class>
		static constexpr auto test(auto(T::* _)(u_cinput) const noexcept) noexcept ->
			traits::true_type<std::invoke_result_t<decltype(_), T>>;
		//template<class>
		//static constexpr auto test(...) noexcept -> traits::false_type<llcpp::Emptyclass>;

		using container = decltype(_MyType::test<T>(&T::operator<=>));
		using type = typename container::U;

	#pragma endregion
};*/

template<class T, class U>
using get_three_way_comparasion_return_t =
	traits::get_three_way_comparasion_return<T, U, std::is_class_v<T>>::type;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSTHREEWAYCOMPARE_HPP_
