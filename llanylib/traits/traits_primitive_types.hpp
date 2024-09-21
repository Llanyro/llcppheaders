//////////////////////////////////////////////
//	traits_primitive_types.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSPRIMITIVETYPES_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSPRIMITIVETYPES_MAYOR_ != 10 || LLANYLIB_TRAITSPRIMITIVETYPES_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_primitive_types.hpp version error!"
		#else
			#error "traits_primitive_types.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSPRIMITIVETYPES_MAYOR_ || LLANYLIB_TRAITSPRIMITIVETYPES_MINOR_

#else !defined(LLANYLIB_TRAITSPRIMITIVETYPES_HPP_)
#define LLANYLIB_TRAITSPRIMITIVETYPES_HPP_
#define LLANYLIB_TRAITSPRIMITIVETYPES_MAYOR_ 10
#define LLANYLIB_TRAITSPRIMITIVETYPES_MINOR_ 0

#include "traits_checker.hpp"

namespace llcpp {
namespace meta {
namespace traits {

// Empty dummy class to use with primitive types
// Its usefull to use in function checkers with primitive types
template<class _T>
class PrimitiveClass {
	#pragma region Types
	public:
		// Class related
		using _MyType			= PrimitiveClass;

		// Types and enums
		using T					= _T;

		template<class U>
		using OrdeningByType	=
			traits::conditional_t<
				std::is_floating_point_v<T> || std::is_floating_point_v<U>,
				std::partial_ordering,
				std::strong_ordering
			>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_basic_type_v<T>,
			"Type must be a basic/primitive type");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr PrimitiveClass() noexcept {}
		constexpr ~PrimitiveClass() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr PrimitiveClass(const PrimitiveClass&) noexcept {}
		constexpr PrimitiveClass& operator=(const PrimitiveClass&) noexcept { return *this; }
		constexpr PrimitiveClass(PrimitiveClass&&) noexcept {}
		constexpr PrimitiveClass& operator=(PrimitiveClass&&) noexcept { return *this; }

		constexpr PrimitiveClass(const T&) noexcept {}
		constexpr PrimitiveClass& operator=(const T&) noexcept { return *this; }
		constexpr PrimitiveClass(T&&) noexcept {}
		constexpr PrimitiveClass& operator=(T&&) noexcept { return *this; }

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const PrimitiveClass*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator PrimitiveClass*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
#define __LL_PRIMITIVE_U_TYPE_CHECK(type, result) \
	static_assert(traits::is_basic_type_v<type>, \
	"Type must be a basic/primitive type"); \
	return result

		template<class U>
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const U) const noexcept {
			__LL_PRIMITIVE_U_TYPE_CHECK(U, llcpp::FALSE);
		}
		template<class U>
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const U) const noexcept {
			__LL_PRIMITIVE_U_TYPE_CHECK(U, llcpp::TRUE);
		}
		template<class U>
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const U) const noexcept {
			__LL_PRIMITIVE_U_TYPE_CHECK(U, llcpp::FALSE);
		}
		template<class U>
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const U) const noexcept {
			__LL_PRIMITIVE_U_TYPE_CHECK(U, llcpp::TRUE);
		}
		template<class U>
		__LL_NODISCARD__ constexpr OrdeningByType<U> operator<=>(const U) const noexcept {
			__LL_PRIMITIVE_U_TYPE_CHECK(U, OrdeningByType<U>());
		}
		template<class U>
		__LL_NODISCARD__ constexpr c_cmp_t compare(const U) const noexcept {
			__LL_PRIMITIVE_U_TYPE_CHECK(U, llcpp::ZERO_CMP);
		}

#undef __LL_PRIMITIVE_U_TYPE_CHECK

		#pragma endregion

	#pragma endregion
};

template<class T>
using T_PrimitiveClass = traits::conditional_t<std::is_class_v<T>, T, traits::PrimitiveClass<T>>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSPRIMITIVETYPES_HPP_
