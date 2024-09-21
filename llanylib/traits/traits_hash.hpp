//////////////////////////////////////////////
//	traits_hash.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSHASH_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSHASH_MAYOR_ != 10 || LLANYLIB_TRAITSHASH_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_hash.hpp version error!"
		#else
			#error "traits_hash.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSHASH_MAYOR_ || LLANYLIB_TRAITSHASH_MINOR_

#else !defined(LLANYLIB_TRAITSHASH_HPP_)
#define LLANYLIB_TRAITSHASH_HPP_
#define LLANYLIB_TRAITSHASH_MAYOR_ 10
#define LLANYLIB_TRAITSHASH_MINOR_ 0

#include "traits_checker.hpp"

namespace llcpp {
namespace meta {
namespace traits {

namespace __traits__ {

template<class _ClassToCheck>
struct get_hash_function_type {
	// Class related
	using _MyType		= get_hash_function_type;

	// Types and enums
	using ClassToCheck	= _ClassToCheck;
	using T_Class		= traits::T_Class<_ClassToCheck>;

	// Asserts
	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_constructor_checker_v<ClassToCheck>,
		"constructor_checker<ClassToCheck> detected an invalid class type!");
	static_assert(std::is_class_v<ClassToCheck>,
		"ClassToCheck is not a class!");

	// Functions
	template<class>
	static constexpr auto test(auto(T_Class::* _)() noexcept) noexcept ->
		traits::true_type<std::invoke_result_t<decltype(_), T_Class>>;
	template<class>
	static constexpr auto test(...) noexcept -> traits::false_type<void>;

	using container = decltype(_MyType::test<T_Class>(&T_Class::hash));
	using type = typename container::U;
};
template<class _ClassToCheck>
struct get_hash_function_type_const {
	// Class related
	using _MyType		= get_hash_function_type_const;

	// Types and enums
	using ClassToCheck	= _ClassToCheck;
	using T_Class		= traits::T_Class<_ClassToCheck>;

	// Asserts
	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_constructor_checker_v<ClassToCheck>,
		"class_checker<ClassToCheck> detected an invalid class type!");
	static_assert(std::is_class_v<ClassToCheck>,
		"ClassToCheck is not a class!");

	// Functions
	template<class>
	static constexpr auto test(auto(T_Class::* _)() const noexcept) noexcept ->
		traits::true_type<std::invoke_result_t<decltype(_), T_Class>>;
	template<class>
	static constexpr auto test(...) noexcept -> traits::false_type<void>;

	using container = decltype(_MyType::test<T_Class>(&T_Class::hash));
	using type = typename container::U;
};

} // namespace __traits__

namespace hash {

// Returns hash type by calling hash function
template<class _ClassToCheck>
struct get_hash_function_type {
	// Class related
	using _MyType						= get_hash_function_type;
	using _get_hash_function_type		= traits::__traits__::get_hash_function_type<_ClassToCheck>;
	using _get_hash_function_type_const = traits::__traits__::get_hash_function_type_const<_ClassToCheck>;

	// Types and enums
	using ClassToCheck	= _ClassToCheck;
	using _type			= typename _get_hash_function_type::type;
	using _type_const	= typename _get_hash_function_type_const::type;

	using type = traits::conditional_t<!std::is_same_v<_type, void>, _type, _type_const>;
	static_assert(!std::is_same_v<type, void>, "T::hash() cannot return void!");
};

//template<class _ClassToCheck>
//struct get_hash_function_type<_ClassToCheck*> {
//	using ClassToCheck	= _ClassToCheck*;
//	using container		= traits::double_type_container<std::false_type, void>;
//	using type			= container::U;
//};

template<class ClassToCheck>
using get_hash_function_type_t = get_hash_function_type<ClassToCheck>::type;

//template<class _ClassToCheck, class HashType>
//struct get_hash_function {
//	using ClassToCheck = _ClassToCheck;
//	using container		= traits::double_type_container<std::true_type, void(ClassToCheck::*)() noexcept>;
//	using c_container	= traits::double_type_container<std::true_type, void(ClassToCheck::*)() const noexcept>;
//	using type			= container::U;
//	using ctype			= c_container::U;
//
//	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
//		"type_checker<ClassToCheck> detected an invalid type!");
//	static_assert(traits::is_valid_class_checker_v<ClassToCheck>,
//		"class_checker<ClassToCheck> detected an invalid class type!");
//};

} // namespace hash
} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSHASH_HPP_
