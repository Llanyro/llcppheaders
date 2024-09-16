//////////////////////////////////////////////
//	traits_comparations.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSCOMPARATION_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSCOMPARATION_MAYOR_ != 10 || LLANYLIB_TRAITSCOMPARATION_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_comparations.hpp version error!"
		#else
			#error "traits_comparations.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSCOMPARATION_MAYOR_ || LLANYLIB_TRAITSCOMPARATION_MINOR_

#else !defined(LLANYLIB_TRAITSCOMPARATION_HPP_)
#define LLANYLIB_TRAITSCOMPARATION_HPP_
#define LLANYLIB_TRAITSCOMPARATION_MAYOR_ 10
#define LLANYLIB_TRAITSCOMPARATION_MINOR_ 0

#include "traits_three_way_compare.hpp"
#include "traits_signature.hpp"
#include "traits_primitive_types.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<class _T, class _U = _T, class _Boolean = llcpp::meta::Boolean, class _ExtraFunctions = llcpp::Emptyclass>
class is_comparable : public llcpp::meta::Cluster, public _ExtraFunctions {
	#pragma region Types
	public:
		// Class related
		using _MyType			= is_comparable;				// This class with template
		using ExtraFunctions	= _ExtraFunctions;				// Type of inherited class with extra function
		using Cluster			= llcpp::meta::Cluster;			// Flag to 

		// Types and enums
		using T					= _T;							// Element to compare by
		using U					= _U;							// Element to compare to
		using Boolean			= _Boolean;						// Boolean class Type
		using T_PrimitiveClass	= traits::T_PrimitiveClass<T>;	// Provides primitive wrapper if primitive type
		using t_cinput			= traits::cinput<T>;
		using u_cinput			= traits::cinput<U>;
		
		// Signarures
		using BoolSignature		= ll_bool_t(T_PrimitiveClass::*)(u_cinput) const noexcept;
		using BooleanSignature	= Boolean(T_PrimitiveClass::*)(u_cinput) const noexcept;

		using BoolExtraSignature	= ll_bool_t(ExtraFunctions::*)(t_cinput, u_cinput) const noexcept;
		using BooleanExtraSignature	= Boolean(ExtraFunctions::*)(t_cinput, u_cinput) const noexcept;

	#pragma endregion
	#pragma region Expresions
		#pragma region TypeExpresions
	public:
		static constexpr ll_bool_t HAS_EQ_SIGNATURE_BOOL =
			traits::common::has_operator_eq_function_v<T_PrimitiveClass, BoolSignature>;
		static constexpr ll_bool_t HAS_EQ_SIGNATURE_BOOLEAN =
			traits::common::has_operator_eq_function_v<T_PrimitiveClass, BooleanSignature>;

		static constexpr ll_bool_t HAS_NEQ_SIGNATURE_BOOL =
			traits::common::has_operator_no_eq_function_v<T_PrimitiveClass, BoolSignature>;
		static constexpr ll_bool_t HAS_NEQ_SIGNATURE_BOOLEAN =
			traits::common::has_operator_no_eq_function_v<T_PrimitiveClass, BooleanSignature>;

		static constexpr ll_bool_t IS_COMPARABLE_EQ =
			HAS_EQ_SIGNATURE_BOOL || HAS_EQ_SIGNATURE_BOOLEAN;
		static constexpr ll_bool_t IS_COMPARABLE_NEQ =
			HAS_NEQ_SIGNATURE_BOOL || HAS_NEQ_SIGNATURE_BOOLEAN;

		#pragma endregion
		#pragma region ClassExpresions
	public:
		static constexpr ll_bool_t HAS_EQ_SIGNATURE_BOOL_EXTRA =
			traits::common::has_compare_eq_function_v<T_PrimitiveClass, BoolSignature>;
		static constexpr ll_bool_t HAS_EQ_SIGNATURE_BOOLEAN_EXTRA =
			traits::common::has_compare_eq_function_v<T_PrimitiveClass, BooleanSignature>;

		static constexpr ll_bool_t HAS_NEQ_SIGNATURE_BOOL_EXTRA =
			traits::common::has_compare_no_eq_function_v<T_PrimitiveClass, BoolSignature>;
		static constexpr ll_bool_t HAS_NEQ_SIGNATURE_BOOLEAN_EXTRA =
			traits::common::has_compare_no_eq_function_v<T_PrimitiveClass, BooleanSignature>;

		static constexpr ll_bool_t IS_COMPARABLE_EQ_EXTRA =
			HAS_EQ_SIGNATURE_BOOL_EXTRA || HAS_EQ_SIGNATURE_BOOLEAN_EXTRA;
		static constexpr ll_bool_t IS_COMPARABLE_NEQ_EXTRA =
			HAS_NEQ_SIGNATURE_BOOL_EXTRA || HAS_NEQ_SIGNATURE_BOOLEAN_EXTRA;

		#pragma endregion

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(traits::is_valid_type_checker_v<U>,
			"type_checker<U> detected an invalid type!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr is_comparable() noexcept : ExtraFunctions(), Cluster() {}
		constexpr ~is_comparable() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr is_comparable(const pair& other) noexcept
			: t_val(std::forward<const T&>(other.t_val))
			, u_val(std::forward<const U&>(other.u_val))
		{}
		constexpr is_comparable& operator=(const is_comparable& other) noexcept {
			this->t_val = std::forward<const T&>(other.t_val);
			this->u_val = std::forward<const U&>(other.u_val);
			return *this;
		}
		constexpr pair(pair&& other) noexcept
			: t_val(std::forward<T&&>(other.t_val))
			, u_val(std::forward<U&&>(other.u_val))
		{ other.ExtraFunctions::clear(other.t_val, other.u_val) }
		constexpr pair& operator=(pair&& other) noexcept {
			this->t_val = std::forward<T&&>(other.t_val);
			this->u_val = std::forward<U&&>(other.u_val);
			other.ExtraFunctions::clear(other.t_val, other.u_val)
			return *this;
		}
		constexpr pair(const volatile pair&) = delete;
		constexpr pair& operator=(const volatile pair&) = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const pair*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator pair*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions

	public:
		using compare_eq_type =
			std::conditional_t<T_HAS_EQ_SIGNATURE_BOOL, ll_bool_t, Boolean>;
		using compare_neq_type =
			std::conditional_t<T_HAS_NEQ_SIGNATURE_BOOL, ll_bool_t, Boolean>;

		__LL_NODISCARD__ constexpr compare_eq_type is_same_value(t_cinput t, u_cinput u) const noexcept {
			static_assert(IS_COMPARABLE_EQ, "Types are not comparables!");
			return (t == u);
		}
		__LL_NODISCARD__ constexpr compare_eq_type is_not_same_value(t_cinput t, u_cinput u) const noexcept {
			static_assert(IS_COMPARABLE_NEQ, "Types are not comparables!");
			return (t != u);
		}

	#pragma endregion
};

template<
	class _T,
	class _U = _T,
	class _Orderning = traits::get_three_way_comparasion_function_type_t<_T, _U>
>
struct is_diff {
	#pragma region Types
	public:
		// Class related
		using _MyType			= is_diff;

		// Types
		using T					= _T;
		using U					= _U;
		using Orderning			= _Orderning;
		using T_Class			= traits::T_Class<T>;

		// 
		using t_cinput			= traits::cinput<T>;
		using u_cinput			= traits::cinput<U>;
		
		// Signarures
		using T_Signature_C		= cmp_t(T_Class::*)(u_cinput) const noexcept;
		using T_Signature_CPP	= Orderning(T_Class::*)(u_cinput) const noexcept;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t T_HAS_C_SIGNATURE =
			traits::common::has_sgtrong_ordening_function_v<T_Class, T_Signature_C>;
		static constexpr ll_bool_t T_HAS_CPP_SIGNATURE =
			traits::common::has_sgtrong_ordening_function_v<T_Class, T_Signature_CPP>;

		static constexpr ll_bool_t T_U_BASIC_TYPE =
			traits::is_basic_type_v<T> && traits::is_basic_type_v<U>;

		static constexpr ll_bool_t IS_COMPARABLE =
			T_HAS_C_SIGNATURE || T_U_BASIC_TYPE
			|| T_HAS_CPP_SIGNATURE;

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
		__LL_NODISCARD__ static constexpr cmp_t diff_C(t_cinput t, u_cinput u) noexcept {
			static_assert(T_HAS_C_SIGNATURE || T_U_BASIC_TYPE, "Types are not comparables!");
			if constexpr (T_U_BASIC_TYPE) {
				if (t > u) return 1;
				else if (t < u) return -1;
				else return 0;
			}
			else return (t <=> u);
		}
		__LL_NODISCARD__ static constexpr Orderning diff_CPP(t_cinput t, u_cinput u) noexcept {
			static_assert(T_HAS_CPP_SIGNATURE || T_U_BASIC_TYPE, "Types are not comparables!");
			return (t <=> u);
		}

	#pragma endregion
};

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSCOMPARATION_HPP_
