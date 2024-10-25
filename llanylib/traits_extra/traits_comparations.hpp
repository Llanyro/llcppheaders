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

//#include "traits_signature.hpp"
//#include "traits_primitive_types.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<
	class _T,
	class _U = _T,
	class _Boolean = llcpp::meta::Boolean,
	class _ExtraFunctions = llcpp::Emptyclass
>
class IsComparable : public llcpp::meta::Cluster, public _ExtraFunctions {
	#pragma region Types
	public:
		// Class related
		using _MyType			= IsComparable;					// This class with template
		using ExtraFunctions	= _ExtraFunctions;				// Type of inherited class with extra function
		using Cluster			= llcpp::meta::Cluster;			// This is a cluster type class

		// Types and enums
		using T					= _T;							// Element to compare by
		using U					= _U;							// Element to compare to
		using Boolean			= _Boolean;						// Boolean class Type
		using TWrapper			= traits::PrimitiveWrapper<T>;	// Provides primitive wrapper if primitive type
		using t_cinput			= traits::cinput<T>;
		using u_cinput			= traits::cinput<U>;
		
		// Signarures
		using BoolSignature			= ll_bool_t(TWrapper::*)(u_cinput) const noexcept;
		using BooleanSignature		= Boolean(TWrapper::*)(u_cinput) const noexcept;
		using BoolExtraSignature	= ll_bool_t(ExtraFunctions::*)(t_cinput, u_cinput) const noexcept;
		using BooleanExtraSignature	= Boolean(ExtraFunctions::*)(t_cinput, u_cinput) const noexcept;

	#pragma endregion
	#pragma region Expresions
		#pragma region TypeExpresions
	public:
		static constexpr ll_bool_t HAS_EQ_SIGNATURE_BOOL =
			traits::signature::has_operator_eq_function_v<TWrapper, BoolSignature>;
		static constexpr ll_bool_t HAS_EQ_SIGNATURE_BOOLEAN =
			traits::signature::has_operator_eq_function_v<TWrapper, BooleanSignature>;

		static constexpr ll_bool_t HAS_NEQ_SIGNATURE_BOOL =
			traits::signature::has_operator_no_eq_function_v<TWrapper, BoolSignature>;
		static constexpr ll_bool_t HAS_NEQ_SIGNATURE_BOOLEAN =
			traits::signature::has_operator_no_eq_function_v<TWrapper, BooleanSignature>;

		static constexpr ll_bool_t IS_COMPARABLE_EQ =
			HAS_EQ_SIGNATURE_BOOL || HAS_EQ_SIGNATURE_BOOLEAN;
		static constexpr ll_bool_t IS_COMPARABLE_NEQ =
			HAS_NEQ_SIGNATURE_BOOL || HAS_NEQ_SIGNATURE_BOOLEAN;

		#pragma endregion
		#pragma region ClassExpresions
	public:
		static constexpr ll_bool_t HAS_EQ_SIGNATURE_BOOL_EXTRA =
			traits::signature::has_compare_eq_function_v<ExtraFunctions, BoolExtraSignature>;
		static constexpr ll_bool_t HAS_EQ_SIGNATURE_BOOLEAN_EXTRA =
			traits::signature::has_compare_eq_function_v<ExtraFunctions, BooleanExtraSignature>;

		static constexpr ll_bool_t HAS_NEQ_SIGNATURE_BOOL_EXTRA =
			traits::signature::has_compare_no_eq_function_v<ExtraFunctions, BoolExtraSignature>;
		static constexpr ll_bool_t HAS_NEQ_SIGNATURE_BOOLEAN_EXTRA =
			traits::signature::has_compare_no_eq_function_v<ExtraFunctions, BooleanExtraSignature>;

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

		static_assert(traits::is_valid_type_checker_v<ExtraFunctions>,
			"type_checker<ExtraFunctions> detected an invalid type!");
		static_assert(traits::is_valid_constructor_checker_v<ExtraFunctions>,
			"constructor_checker<ExtraFunctions> detected an invalid type!");
		static_assert(std::is_class_v<ExtraFunctions>,
			"ExtraFunctions is not a class!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr IsComparable() noexcept
			: Cluster()
			, ExtraFunctions()
		{}
		template<class... Args>
		constexpr IsComparable(Args&&... args) noexcept
			: Cluster()
			, ExtraFunctions(std::forward<Args>(args)...)
		{}
		constexpr ~IsComparable() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr IsComparable(const IsComparable& other) noexcept
			: Cluster()
			, ExtraFunctions(std::forward<const ExtraFunctions&>(other))
		{}
		constexpr IsComparable& operator=(const IsComparable& other) noexcept {
			ExtraFunctions::operator=(std::forward<const ExtraFunctions&>(other));
			return *this;
		}
		constexpr IsComparable(IsComparable&& other) noexcept
			: Cluster()
			, ExtraFunctions(std::forward<ExtraFunctions&&>(other))
		{}
		constexpr IsComparable& operator=(IsComparable&& other) noexcept {
			ExtraFunctions::operator=(std::forward<ExtraFunctions&&>(other));
			return *this;
		}
		constexpr IsComparable(const volatile IsComparable&) = delete;
		constexpr IsComparable& operator=(const volatile IsComparable&) = delete;
		constexpr IsComparable(volatile IsComparable&&) = delete;
		constexpr IsComparable& operator=(volatile IsComparable&&) = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const IsComparable*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator IsComparable*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		using compare_eq_type = traits::type_selection<void>::get_conincidence_condition<
			traits::bool_constant_container<HAS_EQ_SIGNATURE_BOOL, ll_bool_t>,
			traits::bool_constant_container<HAS_EQ_SIGNATURE_BOOLEAN, Boolean>,
			traits::bool_constant_container<HAS_EQ_SIGNATURE_BOOL_EXTRA, ll_bool_t>,
			traits::bool_constant_container<HAS_EQ_SIGNATURE_BOOLEAN_EXTRA, Boolean>
		>;
		using compare_neq_type = traits::type_selection<void>::get_conincidence_condition<
			traits::bool_constant_container<HAS_NEQ_SIGNATURE_BOOL, ll_bool_t>,
			traits::bool_constant_container<HAS_NEQ_SIGNATURE_BOOLEAN, Boolean>,
			traits::bool_constant_container<HAS_NEQ_SIGNATURE_BOOL_EXTRA, ll_bool_t>,
			traits::bool_constant_container<HAS_NEQ_SIGNATURE_BOOLEAN_EXTRA, Boolean>
		>;

		__LL_NODISCARD__ constexpr compare_eq_type is_same_value(t_cinput t, u_cinput u) const noexcept {
			static_assert(!std::is_same_v<compare_eq_type, void>,
				"Types are not comparables!");

			if constexpr (IS_COMPARABLE_EQ)
				return (t == u);
			else if constexpr (IS_COMPARABLE_EQ_EXTRA)
				return ExtraFunctions::compare_eq(t, u);
			else {}
		}
		__LL_NODISCARD__ constexpr compare_neq_type is_not_same_value(t_cinput t, u_cinput u) const noexcept {
			static_assert(!std::is_same_v<compare_eq_type, void>,
				"Types are not comparables!");

			if constexpr (IS_COMPARABLE_EQ)
				return (t != u);
			else if constexpr (IS_COMPARABLE_EQ_EXTRA)
				return ExtraFunctions::compare_no_eq(t, u);
			else {}
		}

		#pragma endregion

	#pragma endregion
};

template<
	class _T,
	class _U = _T,
	class _ExtraFunctions = llcpp::Emptyclass,
	class _Orderning = traits::return_detection::return_sgtrong_ordening_function_easy_t<traits::PrimitiveWrapper<_T>, _U>
>
struct IsDifferenciable : public llcpp::meta::Cluster, public _ExtraFunctions {
	#pragma region Types
	public:
		// Class related
		using _MyType			= IsDifferenciable;				// This class with template
		using ExtraFunctions	= _ExtraFunctions;				// Type of inherited class with extra function
		using Cluster			= llcpp::meta::Cluster;			// This is a cluster type class

		// Types and enums
		using T					= _T;							// Element to compare by
		using U					= _U;							// Element to compare to
		using TWrapper			= traits::PrimitiveWrapper<T>;	// Provides primitive wrapper if primitive type
		using Orderning			= _Orderning;
		using t_cinput			= traits::cinput<T>;
		using u_cinput			= traits::cinput<U>;
		
		// Signarures
		using CSignature		= c_cmp_t(TWrapper::*)(u_cinput) const noexcept;
		using CPPSignature		= Orderning(TWrapper::*)(u_cinput) const noexcept;
		using CExtraSignature	= c_cmp_t(ExtraFunctions::*)(t_cinput, u_cinput) const noexcept;
		using CPPExtraSignature	= Orderning(ExtraFunctions::*)(t_cinput, u_cinput) const noexcept;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t HAS_C_SIGNATURE =
			traits::signature::has_compare_function_v<TWrapper, CSignature>;
		static constexpr ll_bool_t HAS_CPP_SIGNATURE =
			traits::signature::has_sgtrong_ordening_function_v<TWrapper, CPPSignature>;

		static constexpr ll_bool_t HAS_C_SIGNATURE_EXTRA =
			traits::signature::has_compare_function_v<TWrapper, CSignature>;
		static constexpr ll_bool_t HAS_CPP_SIGNATURE_EXTRA =
			traits::signature::has_compare_strong_function_v<TWrapper, CPPSignature>;

		static constexpr ll_bool_t IS_C_COMPARABLE =
			HAS_C_SIGNATURE || HAS_C_SIGNATURE_EXTRA;

		static constexpr ll_bool_t IS_CPP_COMPARABLE =
			HAS_CPP_SIGNATURE || HAS_CPP_SIGNATURE_EXTRA;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(traits::is_valid_type_checker_v<U>,
			"type_checker<U> detected an invalid type!");

		static_assert(traits::is_valid_type_checker_v<ExtraFunctions>,
			"type_checker<ExtraFunctions> detected an invalid type!");
		static_assert(traits::is_valid_constructor_checker_v<ExtraFunctions>,
			"constructor_checker<ExtraFunctions> detected an invalid type!");
		static_assert(std::is_class_v<ExtraFunctions>,
			"ExtraFunctions is not a class!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr IsDifferenciable() noexcept
			: Cluster()
			, ExtraFunctions()
		{}
		template<class... Args>
		constexpr IsDifferenciable(Args&&... args) noexcept
			: Cluster()
			, ExtraFunctions(std::forward<Args>(args)...)
		{}
		constexpr ~IsDifferenciable() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr IsDifferenciable(const IsDifferenciable& other) noexcept
			: Cluster()
			, ExtraFunctions(std::forward<const ExtraFunctions&>(other))
		{}
		constexpr IsDifferenciable& operator=(const IsDifferenciable& other) noexcept {
			ExtraFunctions::operator=(std::forward<const ExtraFunctions&>(other));
			return *this;
		}
		constexpr IsDifferenciable(IsDifferenciable&& other) noexcept
			: Cluster()
			, ExtraFunctions(std::forward<ExtraFunctions&&>(other))
		{}
		constexpr IsDifferenciable& operator=(IsDifferenciable&& other) noexcept {
			ExtraFunctions::operator=(std::forward<ExtraFunctions&&>(other));
			return *this;
		}
		constexpr IsDifferenciable(const volatile IsDifferenciable&) = delete;
		constexpr IsDifferenciable& operator=(const volatile IsDifferenciable&) = delete;
		constexpr IsDifferenciable(volatile IsDifferenciable&&) = delete;
		constexpr IsDifferenciable& operator=(volatile IsDifferenciable&&) = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const IsDifferenciable*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator IsDifferenciable*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr c_cmp_t c_diff(t_cinput t, u_cinput u) const noexcept {
			static_assert(IS_C_COMPARABLE,
				"Types are not comparables!");

			if constexpr (HAS_C_SIGNATURE) {
				if constexpr (traits::is_basic_type_v<T> && traits::is_basic_type_v<U>) {
					if (t > u) return 1;
					else if (t < u) return -1;
					else return 0;
				}
				else return (t <=> u);
			}
			else if constexpr (HAS_C_SIGNATURE_EXTRA)
				return ExtraFunctions::compare(t, u);
			else {}
		}
		__LL_NODISCARD__ constexpr Orderning diff(t_cinput t, u_cinput u) const noexcept {
			static_assert(IS_CPP_COMPARABLE,
				"Types are not comparables!");

			if constexpr (HAS_CPP_SIGNATURE)
				return (t <=> u);
			else if constexpr (HAS_CPP_SIGNATURE_EXTRA)
				return ExtraFunctions::compare_strong(t, u);
			else {}
		}

		#pragma endregion

	#pragma endregion
};

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSCOMPARATION_HPP_
