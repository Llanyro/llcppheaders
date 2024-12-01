//////////////////////////////////////////////
//	traits_comparations.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSCOMPARATION_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSCOMPARATION_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TRAITSCOMPARATION_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_comparations.hpp(incomplete) version error!"
		#else
			#error "traits_comparations.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSCOMPARATION_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSCOMPARATION_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSCOMPARATION_INCOMPLETE_HPP_)
#define LLANYLIB_TRAITSCOMPARATION_INCOMPLETE_HPP_
#define LLANYLIB_TRAITSCOMPARATION_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_TRAITSCOMPARATION_INCOMPLETE_MINOR_ 0

#include "../types_base/Boolean.hpp"
#include "../types_base/Cluster.hpp"
#include "traits_signature.hpp"
#include "traits_type_wrapper.hpp"

namespace llcpp {
namespace meta {
namespace traits {

template<
	class _T,
	class _U = _T,
	class _Boolean = llcpp::meta::Boolean,
	class _ExtraFunctions = llcpp::Emptyclass
>
class IsComparable;

template<
	class _T,
	class _U = _T,
	class _ExtraFunctions = llcpp::Emptyclass,
	class _Orderning = llcpp::UndefinedIncompleteObject
>
class IsDifferenciable;

} // namespace traits
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TRAITSCOMPARATION_HPP_)
	#if LLANYLIB_TRAITSCOMPARATION_MAYOR_ != 11 || LLANYLIB_TRAITSCOMPARATION_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_comparations.hpp version error!"
		#else
			#error "traits_comparations.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSCOMPARATION_MAYOR_ || LLANYLIB_TRAITSCOMPARATION_MINOR_

#else
#define LLANYLIB_TRAITSCOMPARATION_HPP_
#define LLANYLIB_TRAITSCOMPARATION_MAYOR_ 11
#define LLANYLIB_TRAITSCOMPARATION_MINOR_ 0

#include "../types_base/Boolean.hpp"
#include "../types_base/Cluster.hpp"
#include "traits_signature.hpp"

#include <string_view>
#include <typeinfo>

namespace llcpp {
namespace meta {
namespace traits {

class ASDF {
	public:
		int a;
		constexpr ASDF() noexcept : a(0) {}
		constexpr ASDF(int a) noexcept : a(a) {}
		constexpr ASDF(const ASDF&) noexcept : a(0) {}
		constexpr ASDF& operator=(const ASDF&) noexcept { return *this; }
		constexpr ASDF(ASDF&&) noexcept : a(0) {}
		constexpr ASDF& operator=(ASDF&&) noexcept { return *this; }
		constexpr ~ASDF() noexcept {}
		constexpr ll_bool_t operator==(const u8 a) const noexcept { return this->a == a; }
		constexpr ll_bool_t operator!=(const u8 a) const noexcept { return this->a == a; }

		constexpr ll_bool_t compareEQ(const ASDF& a, const u8 aa) const noexcept { return a.a == aa; }
		constexpr ll_bool_t compareNEQ(const ASDF& a, const u8 aa) const noexcept { return a.a == aa; }
};

template<
	class _T,
	class _U = _T,
	class _Boolean = ::llcpp::meta::Boolean,
	class _ExtraFunctions = ::llcpp::Emptyclass
>
class IsComparable : public llcpp::meta::Cluster, public _ExtraFunctions {
	#pragma region Types
	public:
		// Class related
		using _MyType			= IsComparable;					// This class with template
		using ExtraFunctions	= _ExtraFunctions;				// Type of inherited class with extra function
		using Cluster			= ::llcpp::meta::Cluster;		// This is a cluster type class

		// Types and enums
		using T			= _T;							// Element to compare by
		using U			= _U;							// Element to compare to
		using Boolean	= _Boolean;						// Boolean class Type
		using t_cinput	= ::llcpp::meta::traits::cinput<T>;
		using u_cinput	= ::llcpp::meta::traits::cinput<U>;

		// Signature types prep
		using FunctionEQCompare_T		= ::llcpp::meta::traits::signatures::GetOperatorEQ;
		using FunctionNEQCompare_T		= ::llcpp::meta::traits::signatures::GetOperatorEQ;
		using FunctionCompareEQ_E		= ::llcpp::meta::traits::signatures::GetCompareEQ;
		using FunctionCompareNEQ_E		= ::llcpp::meta::traits::signatures::GetCompareNEQ;

		template<class Signature, class Function>
		using SignatureCheck_T		= ::llcpp::meta::traits::SignatureCheckerBySignature<T, Signature, Function>;
		template<class Signature, class Function>
		using SignatureCheck_E		= ::llcpp::meta::traits::SignatureCheckerBySignature<ExtraFunctions, Signature, Function>;

		// Signarures
		using BoolSignature_T		= ::llcpp::meta::traits::SigCN<ll_bool_t, u_cinput>;
		using BooleanSignature_T	= ::llcpp::meta::traits::SigCN<Boolean, u_cinput>;
		using BoolSignature_E		= ::llcpp::meta::traits::SigCN<ll_bool_t, t_cinput, u_cinput>;
		using BooleanSignature_E	= ::llcpp::meta::traits::SigCN<Boolean, t_cinput, u_cinput>;

		// Signature checkers
		using BoolEQSignatureCheck_T		= SignatureCheck_T<BoolSignature_T, FunctionEQCompare_T>;
		using BoolNEQSignatureCheck_T		= SignatureCheck_T<BoolSignature_T, FunctionNEQCompare_T>;
		using BooleanEQSignatureCheck_T		= SignatureCheck_T<BooleanSignature_T, FunctionEQCompare_T>;
		using BooleanNEQSignatureCheck_T	= SignatureCheck_T<BooleanSignature_T, FunctionNEQCompare_T>;

		using BoolEQSignatureCheck_E		= SignatureCheck_E<BoolSignature_E, FunctionCompareEQ_E>;
		using BoolNEQSignatureCheck_E		= SignatureCheck_E<BoolSignature_E, FunctionCompareNEQ_E>;
		using BooleanEQSignatureCheck_E		= SignatureCheck_E<BooleanSignature_E, FunctionCompareEQ_E>;
		using BooleanNEQSignatureCheck_E	= SignatureCheck_E<BooleanSignature_E, FunctionCompareNEQ_E>;

	#pragma endregion
	#pragma region Expresions
		#pragma region TypeExpresions
	public:
		static constexpr ll_bool_t HAS_EQ_SIGNATURE_BOOL		= BoolEQSignatureCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_EQ_SIGNATURE_BOOLEAN		= BooleanEQSignatureCheck_T::IS_VALID;

		static constexpr ll_bool_t HAS_NEQ_SIGNATURE_BOOL		= BoolNEQSignatureCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_NEQ_SIGNATURE_BOOLEAN	= BooleanNEQSignatureCheck_T::IS_VALID;

		static constexpr ll_bool_t IS_COMPARABLE_EQ		= HAS_EQ_SIGNATURE_BOOL || HAS_EQ_SIGNATURE_BOOLEAN;
		static constexpr ll_bool_t IS_COMPARABLE_NEQ	= HAS_NEQ_SIGNATURE_BOOL || HAS_NEQ_SIGNATURE_BOOLEAN;

		#pragma endregion
		#pragma region ClassExpresions
	public:
		static constexpr ll_bool_t HAS_EQ_SIGNATURE_BOOL_EXTRA		= BoolEQSignatureCheck_E::IS_VALID;
		static constexpr ll_bool_t HAS_EQ_SIGNATURE_BOOLEAN_EXTRA	= BooleanEQSignatureCheck_E::IS_VALID;

		static constexpr ll_bool_t HAS_NEQ_SIGNATURE_BOOL_EXTRA		= BoolNEQSignatureCheck_E::IS_VALID;
		static constexpr ll_bool_t HAS_NEQ_SIGNATURE_BOOLEAN_EXTRA	= BooleanNEQSignatureCheck_E::IS_VALID;

		static constexpr ll_bool_t IS_COMPARABLE_EQ_EXTRA	= HAS_EQ_SIGNATURE_BOOL_EXTRA || HAS_EQ_SIGNATURE_BOOLEAN_EXTRA;
		static constexpr ll_bool_t IS_COMPARABLE_NEQ_EXTRA	= HAS_NEQ_SIGNATURE_BOOL_EXTRA || HAS_NEQ_SIGNATURE_BOOLEAN_EXTRA;

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
		using compare_eq_type_t = ::std::disjunction<
			::llcpp::meta::traits::BoolConstantContainer<HAS_EQ_SIGNATURE_BOOL || HAS_EQ_SIGNATURE_BOOL_EXTRA, ll_bool_t>,
			::llcpp::meta::traits::BoolConstantContainer<HAS_EQ_SIGNATURE_BOOLEAN || HAS_EQ_SIGNATURE_BOOLEAN_EXTRA, ll_bool_t>,
			::llcpp::meta::traits::TrueContainerEmptyClass
		>::U;
		using compare_neq_type_t = ::std::disjunction<
			::llcpp::meta::traits::BoolConstantContainer<HAS_NEQ_SIGNATURE_BOOL || HAS_NEQ_SIGNATURE_BOOL_EXTRA, ll_bool_t>,
			::llcpp::meta::traits::BoolConstantContainer<HAS_NEQ_SIGNATURE_BOOLEAN || HAS_NEQ_SIGNATURE_BOOLEAN_EXTRA, ll_bool_t>,
			::llcpp::meta::traits::TrueContainerEmptyClass
		>::U;

		__LL_NODISCARD__ constexpr compare_eq_type_t is_same_value(t_cinput t, u_cinput u) const noexcept {
			static_assert(!std::is_same_v<compare_eq_type_t, ::llcpp::Emptyclass>,
				"Types are not comparables!");

			if constexpr (IS_COMPARABLE_EQ)
				return (t == u);
			else if constexpr (IS_COMPARABLE_EQ_EXTRA)
				return ExtraFunctions::compare_eq(t, u);
			else {}
		}
		__LL_NODISCARD__ constexpr compare_neq_type_t is_not_same_value(t_cinput t, u_cinput u) const noexcept {
			static_assert(!std::is_same_v<compare_neq_type_t, ::llcpp::Emptyclass>,
				"Types are not comparables!");

			if constexpr (IS_COMPARABLE_NEQ)
				return (t != u);
			else if constexpr (IS_COMPARABLE_NEQ_EXTRA)
				return ExtraFunctions::compare_no_eq(t, u);
			else {}
		}

		#pragma endregion

	#pragma endregion
};

using CompareTest = IsComparable<ASDF, u8, ::llcpp::meta::Boolean, ASDF>;

constexpr bool asdf1 = CompareTest::BoolEQSignatureCheck_T::IS_VALID;
constexpr bool asdf2 = CompareTest::BoolNEQSignatureCheck_T::IS_VALID;
constexpr bool asdf3 = CompareTest::BooleanEQSignatureCheck_T::IS_VALID;
constexpr bool asdf4 = CompareTest::BooleanNEQSignatureCheck_T::IS_VALID;
constexpr bool asdf5 = CompareTest::IS_COMPARABLE_EQ;
constexpr bool asdf6 = CompareTest::IS_COMPARABLE_NEQ;
constexpr bool asdf7 = CompareTest::IS_COMPARABLE_EQ_EXTRA;
constexpr bool asdf8 = CompareTest::IS_COMPARABLE_NEQ_EXTRA;

constexpr bool asdf8 = CompareTest().compareEQ(ASDF(0), 0x7);

/*
template<
	class _T,
	class _U = _T,
	class _ExtraFunctions = llcpp::Emptyclass,
	class _Orderning = traits::return_detection::return_sgtrong_ordening_function_easy_t<traits::PrimitiveWrapper<_T>, _U>
>
class IsDifferenciable : public llcpp::meta::Cluster, public _ExtraFunctions {
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
*/

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSCOMPARATION_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
