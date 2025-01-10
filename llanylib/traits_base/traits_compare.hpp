//////////////////////////////////////////////
//	traits_comparations.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSCOMPARE_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSCOMPARE_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TRAITSCOMPARE_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_comparations.hpp(incomplete) version error!"
		#else
			#error "traits_comparations.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSCOMPARE_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSCOMPARE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSCOMPARE_INCOMPLETE_HPP_)
	#define LLANYLIB_TRAITSCOMPARE_INCOMPLETE_HPP_
	#define LLANYLIB_TRAITSCOMPARE_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_TRAITSCOMPARE_INCOMPLETE_MINOR_ 0

#include "traits_signature.hpp"
#include "traits_type_wrapper.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<
	class _T,
	class _U = _T,
	class _Boolean = ll_bool_t,
	class _ExtraFunctions = ::llcpp::Emptyclass
>
class IsComparable;

template<
	class _T,
	class _U = _T,
	class _Orderning = ::llcpp::meta::StandardComparation,
	class _ExtraFunctions = ::llcpp::Emptyclass
>
class IsDifferenciable;

} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TRAITSCOMPARE_HPP_)
	#if LLANYLIB_TRAITSCOMPARE_MAYOR_ != 11 || LLANYLIB_TRAITSCOMPARE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_comparations.hpp version error!"
		#else
			#error "traits_comparations.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSCOMPARE_MAYOR_ || LLANYLIB_TRAITSCOMPARE_MINOR_

#else
	#define LLANYLIB_TRAITSCOMPARE_HPP_
	#define LLANYLIB_TRAITSCOMPARE_MAYOR_ 11
	#define LLANYLIB_TRAITSCOMPARE_MINOR_ 0

#include "checker/traits_validate_checker.hpp"

namespace llcpp {
namespace meta {
namespace traits {

// IsComparable<> is a simple version of IsDifferenciable<>
//	This requires only 2-4 functions (operator==, operator!= || compareEQ, compareNEQ)
// Priority:
//	1. operator==	|| operator!=
//	2. compareEQ	|| compareNEQ
template<
	class _T,
	class _U = _T,
	ll_bool_t _IS_NOEXCEPTION	= ::llcpp::TRUE,
	class _Boolean				= ll_bool_t,
	class _ExtraFunctions		= ::llcpp::Emptyclass
>
class IsComparable
	: public ::llcpp::ClusterTag
	, public ::llcpp::meta::traits::ValidationWrapper<_ExtraFunctions, ::llcpp::AlwaysValidTag>
	, public _ExtraFunctions {
	#pragma region Types
	public:
		// Class related
		using _MyType				= IsComparable;				// This class with template
		using ExtraFunctions		= _ExtraFunctions;			// Type of inherited class with extra function
		using ClusterTag			= ::llcpp::ClusterTag;		// This is a cluster type class

		// Types and enums
		using T						= _T;											// Element to compare by
		using U						= _U;											// Element to compare to
		using WrappedT				= ::llcpp::meta::traits::PrimitiveWrapper<T>;	// T wrapped if primitive
		using Boolean				= _Boolean;										// Boolean user type
		using t_cinput				= ::llcpp::meta::traits::cinput<T>;				// T type as const type reference
		using u_cinput				= ::llcpp::meta::traits::cinput<U>;				// U type as const type reference

		// Signature types prep
		template<class Signature, class Function>
		using SignatureCheck_T		= ::llcpp::meta::traits::SignatureCheckerBySignature<WrappedT, Signature, Function>;
		template<class Signature, class Function>
		using SignatureCheck_E		= ::llcpp::meta::traits::SignatureCheckerBySignature<ExtraFunctions, Signature, Function>;
		template<class ReturnType, class... FunctionArguments>
		using Sig					= ::llcpp::meta::traits::SignatureContainer<
			::llcpp::meta::attributes::function_attributes_t::CUSTOM<::llcpp::TRUE, _IS_NOEXCEPTION>,
			ReturnType,
			FunctionArguments...
		>;

		// Signatures
		using OperatorEQ			= ::llcpp::meta::traits::signatures::GetOperatorEQ;
		using OperatorNEQ			= ::llcpp::meta::traits::signatures::GetOperatorNEQ;
		using CompareEQ				= ::llcpp::meta::traits::signatures::GetCompareEQ;
		using CompareNEQ			= ::llcpp::meta::traits::signatures::GetCompareNEQ;

		// Signarure containers
		using ClassSignature_T		= Sig<Boolean, u_cinput>;
		using ClassSignature_E		= Sig<Boolean, t_cinput, u_cinput>;

		// Signature checkers for T (or wrapped T)
		using OperatorEQCheck		= SignatureCheck_T<ClassSignature_T, OperatorEQ>;
		using OperatorNEQCheck		= SignatureCheck_T<ClassSignature_T, OperatorNEQ>;
		using FunctionEQCheck_T		= SignatureCheck_T<ClassSignature_T, CompareEQ>;
		using FunctionNEQCheck_T	= SignatureCheck_T<ClassSignature_T, CompareNEQ>;

		// Signature checkers for ExtraFunctions
		using FunctionEQCheck_E		= SignatureCheck_E<ClassSignature_E, CompareEQ>;
		using FunctionNEQCheck_E	= SignatureCheck_E<ClassSignature_E, CompareNEQ>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t IS_NOEXCEPTION	= _IS_NOEXCEPTION;
		static constexpr ll_bool_t HAS_OPERATOR_EQ	= OperatorEQCheck::IS_VALID;
		static constexpr ll_bool_t HAS_OPERATOR_NEQ	= OperatorNEQCheck::IS_VALID;
		static constexpr ll_bool_t HAS_FUNCTION_EQ	= FunctionEQCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_FUNCTION_NEQ	= FunctionNEQCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_EQ_EXTRA		= FunctionEQCheck_E::IS_VALID;
		static constexpr ll_bool_t HAS_NEQ_EXTRA	= FunctionNEQCheck_E::IS_VALID;

		static constexpr ll_bool_t IS_COMPARABLE_EQ	=
			HAS_OPERATOR_EQ
			|| HAS_FUNCTION_EQ
			|| HAS_EQ_EXTRA;
		static constexpr ll_bool_t IS_COMPARABLE_NEQ =
			HAS_OPERATOR_NEQ
			|| HAS_FUNCTION_NEQ
			|| HAS_NEQ_EXTRA;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<U>,
			"type_checker<U> detected an invalid type!");

		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<ExtraFunctions>,
			"type_checker<ExtraFunctions> detected an invalid type!");
		static_assert(::llcpp::meta::traits::is_valid_constructor_checker_v<ExtraFunctions>,
			"constructor_checker<ExtraFunctions> detected an invalid type!");
		static_assert(::std::is_class_v<ExtraFunctions>,
			"ExtraFunctions is not a class!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr IsComparable() noexcept
			: ClusterTag()
			, ExtraFunctions()
		{}
		template<class... Args>
		constexpr IsComparable(Args&&... args) noexcept
			: ClusterTag()
			, ExtraFunctions(::std::forward<Args>(args)...)
		{}
		constexpr ~IsComparable() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr IsComparable(const IsComparable& other) noexcept
			: ClusterTag()
			, ExtraFunctions(::std::forward<const ExtraFunctions&>(other))
		{}
		constexpr IsComparable& operator=(const IsComparable& other) noexcept {
			ExtraFunctions::operator=(::std::forward<const ExtraFunctions&>(other));
			return *this;
		}
		constexpr IsComparable(IsComparable&& other) noexcept
			: ClusterTag()
			, ExtraFunctions(::std::forward<ExtraFunctions&&>(other))
		{}
		constexpr IsComparable& operator=(IsComparable&& other) noexcept {
			ExtraFunctions::operator=(::std::forward<ExtraFunctions&&>(other));
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
		__LL_NODISCARD__ constexpr Boolean isSameValue(t_cinput t, u_cinput u) const noexcept(IS_NOEXCEPTION) {
			static_assert(IS_COMPARABLE_EQ,
				"Types are not comparables!");

			if constexpr (HAS_OPERATOR_EQ)
				return (t == u);
			else if constexpr (HAS_FUNCTION_EQ)
				return t.compareEQ(u);
			else if constexpr (HAS_EQ_EXTRA)
				return ExtraFunctions::compareEQ(t, u);
			else return ::llcpp::ZERO_VALUE<Boolean>;
		}
		__LL_NODISCARD__ constexpr Boolean isNotSameValue(t_cinput t, u_cinput u) const noexcept(IS_NOEXCEPTION) {
			static_assert(IS_COMPARABLE_NEQ,
				"Types are not comparables!");

			if constexpr (HAS_OPERATOR_NEQ)
				return (t != u);
			else if constexpr (HAS_FUNCTION_NEQ)
				return t.compareNEQ(u);
			else if constexpr (HAS_NEQ_EXTRA)
				return ExtraFunctions::compareNEQ(t, u);
			else return ::llcpp::ZERO_VALUE<Boolean>;
		}

		#pragma endregion

	#pragma endregion
};

template<
	class _T,
	class _U = _T,
	ll_bool_t _IS_NOEXCEPTION	= ::llcpp::TRUE,
	class _Orderning			= ::llcpp::meta::StandardComparation,
	class _ExtraFunctions		= ::llcpp::Emptyclass
>
class IsDifferenciable
	: public ::llcpp::ClusterTag
	, public ::llcpp::meta::traits::ValidationWrapper<_ExtraFunctions, ::llcpp::AlwaysValidTag>
	, public _ExtraFunctions {
	#pragma region Types
	public:
		// Class related
		using _MyType				= IsDifferenciable;			// This class with template
		using ExtraFunctions		= _ExtraFunctions;			// Type of inherited class with extra function
		using ClusterTag			= ::llcpp::ClusterTag;		// This is a cluster type class

		// Types and enums
		using T						= _T;											// Element to compare by
		using U						= _U;											// Element to compare to
		using WrappedT				= ::llcpp::meta::traits::PrimitiveWrapper<T>;	// T wrapped if primitive
		using Orderning				= _Orderning;
		using t_cinput				= ::llcpp::meta::traits::cinput<T>;				// T type as const type
		using u_cinput				= ::llcpp::meta::traits::cinput<U>;				// U type as const type
		
		// Signature types prep
		template<class Signature, class Function>
		using SignatureCheck_T		= ::llcpp::meta::traits::SignatureCheckerBySignature<WrappedT, Signature, Function>;
		template<class Signature, class Function>
		using SignatureCheck_E		= ::llcpp::meta::traits::SignatureCheckerBySignature<ExtraFunctions, Signature, Function>;
		template<class ReturnType, class... FunctionArguments>
		using Sig					= ::llcpp::meta::traits::SignatureContainer<
			::llcpp::meta::attributes::function_attributes_t::CUSTOM<::llcpp::TRUE, _IS_NOEXCEPTION>,
			ReturnType,
			FunctionArguments...
		>;

		// Signatures
		using OperatorCompare		= ::llcpp::meta::traits::signatures::GetOperatorCompare;
		using Compare				= ::llcpp::meta::traits::signatures::GetCompare;
		using StrongCompare			= ::llcpp::meta::traits::signatures::GetStrongCompare;
		using PartialCompare		= ::llcpp::meta::traits::signatures::GetPartialCompare;
		using WeakCompare			= ::llcpp::meta::traits::signatures::GetWeakCompare;

		// Signarure containers
		using ClassSignature_T		= Sig<Orderning, u_cinput>;
		using ClassSignature_E		= Sig<Orderning, t_cinput, u_cinput>;

		// Signature checkers for T (or wrapped T)
		using OperatorCompareCheck	= SignatureCheck_T<ClassSignature_T, OperatorCompare>;
		using FunctionCompareCheck_T= SignatureCheck_T<ClassSignature_T, Compare>;
		using FunctionStrongCheck_T	= SignatureCheck_T<ClassSignature_T, StrongCompare>;
		using FunctionPartialCheck_T= SignatureCheck_T<ClassSignature_T, PartialCompare>;
		using FunctionWeakCheck_T	= SignatureCheck_T<ClassSignature_T, WeakCompare>;

		// Signature checkers for ExtraFunctions
		using FunctionCompareCheck_E= SignatureCheck_E<ClassSignature_E, Compare>;
		using FunctionStrongCheck_E	= SignatureCheck_E<ClassSignature_E, StrongCompare>;
		using FunctionPartialCheck_E= SignatureCheck_E<ClassSignature_E, PartialCompare>;
		using FunctionWeakCheck_E	= SignatureCheck_E<ClassSignature_E, WeakCompare>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t IS_NOEXCEPTION			= _IS_NOEXCEPTION;
		static constexpr ll_bool_t HAS_OPERATOR_COMPARE		= OperatorCompareCheck::IS_VALID;
		static constexpr ll_bool_t HAS_FUNCTION_COMPARE_T	= FunctionCompareCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_FUNCTION_STRONG_T	= FunctionStrongCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_FUNCTION_PARTIAL_T	= FunctionPartialCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_FUNCTION_WEAK_T		= FunctionWeakCheck_T::IS_VALID;

		static constexpr ll_bool_t HAS_FUNCTION_COMPARE_E	= FunctionCompareCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_FUNCTION_STRONG_E	= FunctionStrongCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_FUNCTION_PARTIAL_E	= FunctionPartialCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_FUNCTION_WEAK_E		= FunctionWeakCheck_T::IS_VALID;

		static constexpr ll_bool_t IS_DIFFERENCIABLE =
			HAS_OPERATOR_COMPARE
			|| HAS_FUNCTION_COMPARE_T
			|| HAS_FUNCTION_STRONG_T
			|| HAS_FUNCTION_PARTIAL_T
			|| HAS_FUNCTION_WEAK_T
			
			|| HAS_FUNCTION_COMPARE_E
			|| HAS_FUNCTION_STRONG_E
			|| HAS_FUNCTION_PARTIAL_E
			|| HAS_FUNCTION_WEAK_E;


	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<U>,
			"type_checker<U> detected an invalid type!");

		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<ExtraFunctions>,
			"type_checker<ExtraFunctions> detected an invalid type!");
		static_assert(::llcpp::meta::traits::is_valid_constructor_checker_v<ExtraFunctions>,
			"constructor_checker<ExtraFunctions> detected an invalid type!");
		static_assert(::std::is_class_v<ExtraFunctions>,
			"ExtraFunctions is not a class!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr IsDifferenciable() noexcept
			: ClusterTag()
			, ExtraFunctions()
		{}
		template<class... Args>
		constexpr IsDifferenciable(Args&&... args) noexcept
			: ClusterTag()
			, ExtraFunctions(::std::forward<Args>(args)...)
		{}
		constexpr ~IsDifferenciable() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr IsDifferenciable(const IsDifferenciable& other) noexcept
			: ClusterTag()
			, ExtraFunctions(::std::forward<const ExtraFunctions&>(other))
		{}
		constexpr IsDifferenciable& operator=(const IsDifferenciable& other) noexcept {
			ExtraFunctions::operator=(::std::forward<const ExtraFunctions&>(other));
			return *this;
		}
		constexpr IsDifferenciable(IsDifferenciable&& other) noexcept
			: ClusterTag()
			, ExtraFunctions(::std::forward<ExtraFunctions&&>(other))
		{}
		constexpr IsDifferenciable& operator=(IsDifferenciable&& other) noexcept {
			ExtraFunctions::operator=(::std::forward<ExtraFunctions&&>(other));
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
		__LL_NODISCARD__ constexpr Orderning diff(t_cinput t, u_cinput u) const noexcept(IS_NOEXCEPTION) {
			static_assert(IS_DIFFERENCIABLE,
				"Types are not differenciables!");

			if constexpr (HAS_OPERATOR_COMPARE)
				return (t <=> u);
			else if constexpr (HAS_FUNCTION_COMPARE_T)
				return t.compare(u);
			else if constexpr (HAS_FUNCTION_STRONG_T)
				return t.strongCompare(u);
			else if constexpr (HAS_FUNCTION_PARTIAL_T)
				return t.partialCompare(u);
			else if constexpr (HAS_FUNCTION_WEAK_T)
				return t.weakCompare(u);

			else if constexpr (HAS_FUNCTION_COMPARE_E)
				return ExtraFunctions::compare(t, u);
			else if constexpr (HAS_FUNCTION_STRONG_E)
				return ExtraFunctions::strongCompare(t, u);
			else if constexpr (HAS_FUNCTION_PARTIAL_E)
				return ExtraFunctions::partialCompare(t, u);
			else if constexpr (HAS_FUNCTION_WEAK_E)
				return ExtraFunctions::weakCompare(t, u);
			else return ::llcpp::ZERO_VALUE<Orderning>;
		}

		#pragma endregion

	#pragma endregion
};

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSCOMPARE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
