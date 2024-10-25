//////////////////////////////////////////////
//	traits_object_checker.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSOBJECTCHECKER_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSOBJECTCHECKER_MAYOR_ != 10 || LLANYLIB_TRAITSOBJECTCHECKER_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_object_checker.hpp version error!"
		#else
			#error "traits_object_checker.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSOBJECTCHECKER_MAYOR_ || LLANYLIB_TRAITSOBJECTCHECKER_MINOR_

#else !defined(LLANYLIB_TRAITSOBJECTCHECKER_HPP_)
#define LLANYLIB_TRAITSOBJECTCHECKER_HPP_
#define LLANYLIB_TRAITSOBJECTCHECKER_MAYOR_ 10
#define LLANYLIB_TRAITSOBJECTCHECKER_MINOR_ 0

#include "traits_primitive_types.hpp"
#include "../traits/traits_signature.hpp"

#include <array>

using Container = std::array<int, 5>::iterator;

namespace llcpp {
namespace meta {
namespace traits {

template<class _ObjectType, ll_bool_t _IS_POINTER>
struct is_iterator {
	#pragma region Types
	public:
		// Class related
		using _MyType						= is_iterator;

		// Types and enums
		using ObjectType					= _ObjectType;
		using const_t						= std::is_const<ObjectType>;
		template<class T, class U>
		using const_conditional_t			= std::conditional_t<std::is_const_v<ObjectType>, T, U>;

		using __PointerReturnClassic =
			traits::return_detection::return_operator_pointer_function<ObjectType, meta::functional::CLASSIC>;
		using __PointerReturnNoexception =
			traits::return_detection::return_operator_pointer_function<ObjectType, meta::functional::NOEXCEPTION>;
		using __PointerReturnConst =
			traits::return_detection::return_operator_pointer_function<ObjectType, meta::functional::CONST>;
		using __PointerReturnConstNoexception =
			traits::return_detection::return_operator_pointer_function<ObjectType, meta::functional::CONSTNOEXCEPTION>;

		using __ArrowReturnClassic =
			traits::return_detection::return_operator_arrow_function<ObjectType, meta::functional::CLASSIC>;
		using __ArrowReturnNoexception =
			traits::return_detection::return_operator_arrow_function<ObjectType, meta::functional::NOEXCEPTION>;
		using __ArrowReturnConst =
			traits::return_detection::return_operator_arrow_function<ObjectType, meta::functional::CONST>;
		using __ArrowReturnConstNoexception =
			traits::return_detection::return_operator_arrow_function<ObjectType, meta::functional::CONSTNOEXCEPTION>;

		// Signatures
		using OperatorPreIncrement			= ObjectType&(ObjectType::*)();
		using OperatorPreIncrementNoexcept	= ObjectType&(ObjectType::*)() noexcept;
		using OperatorPosIncrement			= ObjectType(ObjectType::*)(int);
		using OperatorPosIncrementNoexcept	= ObjectType(ObjectType::*)(int) noexcept;

		using HasPreIncrement				= traits::signature::has_operator_increment_function_t<ObjectType, OperatorPreIncrement>;
		using HasPreIncrementNoexception	= traits::signature::has_operator_increment_function_t<ObjectType, OperatorPreIncrementNoexcept>;
		using HasPosIncrement				= traits::signature::has_operator_increment_function_t<ObjectType, OperatorPosIncrement>;
		using HasPosIncrementNoexception	= traits::signature::has_operator_increment_function_t<ObjectType, OperatorPosIncrementNoexcept>;

		using OperatorPointerReturn =
			const_conditional_t<__PointerReturnConst::type,
				traits::type_selection<>::get_first_difference<llcpp::Emptyclass,
					__PointerReturnClassic::type,
					__PointerReturnConst::type
				>
			>;
		using OperatorPointerReturnNoexception =
			const_conditional_t<__PointerReturnConstNoexception::type,
				traits::type_selection<>::get_first_difference<llcpp::Emptyclass,
					__PointerReturnNoexception::type,
					__PointerReturnConstNoexception::type
				>
			>;

		using OperatorArrowReturn =
			const_conditional_t<__ArrowReturnConst::type,
				traits::type_selection<>::get_first_difference<llcpp::Emptyclass,
					__ArrowReturnClassic::type,
					__ArrowReturnConst::type
				>
			>;
		using OperatorArrowReturnNoexception =
			const_conditional_t<__ArrowReturnConstNoexception::type,
				traits::type_selection<>::get_first_difference<llcpp::Emptyclass,
					__ArrowReturnNoexception::type,
					__ArrowReturnConstNoexception::type
				>
			>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t IS_POINTER = _IS_POINTER;
		static constexpr ll_bool_t IS_CONST = const_conditional_t<std::true_type, std::false_type>::value;

		static constexpr ll_bool_t IS_VALID_ITERATOR =
			(HasPreIncrement::value || HasPreIncrementNoexception::value) &&
			(HasPosIncrement::value || HasPosIncrementNoexception::value) &&
			(!std::is_same_v<OperatorPointerReturn, llcpp::Emptyclass> || !std::is_same_v<OperatorPointerReturnNoexception, llcpp::Emptyclass>) &&
			(!std::is_same_v<OperatorArrowReturn, llcpp::Emptyclass> || !std::is_same_v<OperatorArrowReturnNoexception, llcpp::Emptyclass>);

		static constexpr ll_bool_t IS_VALID_ITERATOR_NOEXCEPTION =
			HasPreIncrementNoexception::value &&
			HasPosIncrementNoexception::value &&
			!std::is_same_v<OperatorPointerReturnNoexception, llcpp::Emptyclass> &&
			!std::is_same_v<OperatorArrowReturnNoexception, llcpp::Emptyclass>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<ObjectType, traits::checker::IGNORE_CONST>,
			"type_checker<ObjectType> detected an invalid type!");

	#pragma endregion
};

template<class _ObjectType>
struct is_iterator<_ObjectType, llcpp::TRUE> {
	#pragma region Types
	public:
		// Class related
		using _MyType						= is_iterator;

		// Types and enums
		using ObjectType					= _ObjectType;
		using const_t						= std::is_const<ObjectType>;
		template<class T, class U>
		using const_conditional_t			= std::conditional_t<std::is_const_v<ObjectType>, T, U>;


	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t IS_POINTER = std::is_pointer_v<ObjectType>;
		static constexpr ll_bool_t IS_CONST = const_conditional_t<std::true_type, std::false_type>::value;
		static constexpr ll_bool_t IS_VALID_ITERATOR = std::is_pointer_v<ObjectType>;
		static constexpr ll_bool_t IS_VALID_ITERATOR_NOEXCEPTION = IS_VALID_ITERATOR;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<ObjectType, traits::checker::IGNORE_CP>,
			"type_checker<ObjectType> detected an invalid type!");

	#pragma endregion
};

template<class ObjectType>
using is_iterator_t = traits::is_iterator<ObjectType, std::is_pointer_v<ObjectType> || !std::is_class_v<ObjectType>>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSOBJECTCHECKER_HPP_
