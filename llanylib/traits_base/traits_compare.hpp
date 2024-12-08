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

#include "../types_base/Boolean.hpp"
#include "../types_base/Cluster.hpp"
#include "traits_signature.hpp"
#include "traits_type_wrapper.hpp"

#include <string_view>
#include <typeinfo>
#include <compare>

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
		constexpr ll_bool_t operator!=(const u8 a) const noexcept { return this->a != a; }

		constexpr ll_bool_t compareEQ(const ASDF& a, const u8 aa) const noexcept { return a.a == aa; }
		constexpr ll_bool_t compareNEQ(const ASDF& a, const u8 aa) const noexcept { return a.a == aa; }
};

// IsComparable<> is a simple version of IsDifferenciable<>
//	This requires only 2-4 functions (operator==, operator!= || compareEQ, compareNEQ)
// Priority:
//	1. operator==	|| operator!=
//	2. compareEQ	|| compareNEQ
template<
	class _T,
	class _U = _T,
	class _Boolean = ll_bool_t,
	class _ExtraFunctions = ::llcpp::Emptyclass
>
class IsComparable : public ::llcpp::meta::Cluster, public _ExtraFunctions {
	#pragma region Types
	public:
		// Class related
		using _MyType				= IsComparable;				// This class with template
		using ExtraFunctions		= _ExtraFunctions;			// Type of inherited class with extra function
		using Cluster				= ::llcpp::meta::Cluster;	// This is a cluster type class

		// Types and enums
		using T						= _T;											// Element to compare by
		using U						= _U;											// Element to compare to
		using WrappedT				= ::llcpp::meta::traits::PrimitiveWrapper<T>;	// T wrapped if primitive
		using Boolean				= _Boolean;										// Boolean user type
		using t_cinput				= ::llcpp::meta::traits::cinput<T>;				// T type as const type
		using u_cinput				= ::llcpp::meta::traits::cinput<U>;				// U type as const type

		// Signature types prep
		template<class Signature, class Function>
		using SignatureCheck_T		= ::llcpp::meta::traits::SignatureCheckerBySignature<WrappedT, Signature, Function>;
		template<class Signature, class Function>
		using SignatureCheck_E		= ::llcpp::meta::traits::SignatureCheckerBySignature<ExtraFunctions, Signature, Function>;

		// Signatures
		using OperatorEQ			= ::llcpp::meta::traits::signatures::GetOperatorEQ;
		using OperatorNEQ			= ::llcpp::meta::traits::signatures::GetOperatorNEQ;
		using CompareEQ				= ::llcpp::meta::traits::signatures::GetCompareEQ;
		using CompareNEQ			= ::llcpp::meta::traits::signatures::GetCompareNEQ;

		// Signarure containers
		using ClassSignature_T		= ::llcpp::meta::traits::SigCN<Boolean, u_cinput>;
		using ClassSignature_E		= ::llcpp::meta::traits::SigCN<Boolean, t_cinput, u_cinput>;

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
		static constexpr ll_bool_t HAS_OPERATOR_EQ_BOOL		= OperatorEQCheck::IS_VALID;
		static constexpr ll_bool_t HAS_OPERATOR_NEQ_BOOL	= OperatorNEQCheck::IS_VALID;
		static constexpr ll_bool_t HAS_FUNCTION_EQ_BOOL		= FunctionEQCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_FUNCTION_NEQ_BOOL	= FunctionNEQCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_EQ_BOOL_EXTRA		= FunctionEQCheck_E::IS_VALID;
		static constexpr ll_bool_t HAS_NEQ_BOOL_EXTRA		= FunctionNEQCheck_E::IS_VALID;

		static constexpr ll_bool_t IS_COMPARABLE_EQ			= HAS_OPERATOR_EQ_BOOL || HAS_FUNCTION_EQ_BOOL;
		static constexpr ll_bool_t IS_COMPARABLE_NEQ		= HAS_OPERATOR_NEQ_BOOL || HAS_FUNCTION_NEQ_BOOL;
		static constexpr ll_bool_t IS_COMPARABLE_EQ_EXTRA	= HAS_EQ_BOOL_EXTRA;
		static constexpr ll_bool_t IS_COMPARABLE_NEQ_EXTRA	= HAS_NEQ_BOOL_EXTRA;

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
		__LL_NODISCARD__ constexpr Boolean isSameValue(t_cinput t, u_cinput u) const noexcept {
			static_assert(IS_COMPARABLE_EQ || IS_COMPARABLE_EQ_EXTRA,
				"Types are not comparables!");

			if constexpr (HAS_OPERATOR_EQ_BOOL)
				return (t == u);
			else if constexpr (HAS_FUNCTION_EQ_BOOL)
				return t.compareEQ(u);
			else if constexpr (HAS_EQ_BOOL_EXTRA)
				return ExtraFunctions::compareEQ(t, u);
			else return ::llcpp::ZERO_VALUE<Boolean>;
		}
		__LL_NODISCARD__ constexpr Boolean isNotSameValue(t_cinput t, u_cinput u) const noexcept {
			static_assert(IS_COMPARABLE_NEQ || IS_COMPARABLE_NEQ_EXTRA,
				"Types are not comparables!");

			if constexpr (HAS_OPERATOR_NEQ_BOOL)
				return (t != u);
			else if constexpr (HAS_FUNCTION_NEQ_BOOL)
				return t.compareNEQ(u);
			else if constexpr (HAS_NEQ_BOOL_EXTRA)
				return ExtraFunctions::compareNEQ(t, u);
			else return ::llcpp::ZERO_VALUE<Boolean>;
		}

		#pragma endregion

	#pragma endregion
};

template<
	class _T,
	class _U = _T,
	class _Orderning = ::llcpp::meta::StandardComparation,
	class _ExtraFunctions = ::llcpp::Emptyclass
>
class IsDifferenciable : public ::llcpp::meta::Cluster, public _ExtraFunctions {
	#pragma region Types
	public:
		// Class related
		using _MyType				= IsDifferenciable;			// This class with template
		using ExtraFunctions		= _ExtraFunctions;			// Type of inherited class with extra function
		using Cluster				= ::llcpp::meta::Cluster;	// This is a cluster type class

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

		// Signatures
		using OperatorCompare		= ::llcpp::meta::traits::signatures::GetOperatorCompare;
		using Compare				= ::llcpp::meta::traits::signatures::GetCompare;
		using StrongCompare			= ::llcpp::meta::traits::signatures::GetStrongCompare;
		using PartialCompare		= ::llcpp::meta::traits::signatures::GetPartialCompare;
		using WeakCompare			= ::llcpp::meta::traits::signatures::GetWeakCompare;

		// Signarure containers
		using ClassSignature_T		= ::llcpp::meta::traits::SigCN<Orderning, u_cinput>;
		using ClassSignature_E		= ::llcpp::meta::traits::SigCN<Orderning, t_cinput, u_cinput>;

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
		static constexpr ll_bool_t HAS_C_SIGNATURE = CSignatureCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_C_SIGNATURE = CSignatureCheck_T::IS_VALID;
		static constexpr ll_bool_t HAS_CPP_SIGNATURE = CPPSignatureCheck_T::IS_VALID;

		static constexpr ll_bool_t HAS_C_SIGNATURE_EXTRA = CSignatureCheck_E::IS_VALID;
		static constexpr ll_bool_t HAS_CPP_SIGNATURE_EXTRA = CPPSignatureCheck_E::IS_VALID;

		static constexpr ll_bool_t IS_C_COMPARABLE = HAS_C_SIGNATURE || HAS_C_SIGNATURE_EXTRA;
		static constexpr ll_bool_t IS_CPP_COMPARABLE = HAS_CPP_SIGNATURE || HAS_CPP_SIGNATURE_EXTRA;

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
		__LL_NODISCARD__ constexpr Orderning diff(t_cinput t, u_cinput u) const noexcept {
			static_assert(IS_CPP_COMPARABLE,
				"Types are not comparables!");

			if constexpr (HAS_CPP_SIGNATURE)
				return (t <=> u);
			else if constexpr (HAS_CPP_SIGNATURE_EXTRA)
				return ExtraFunctions::compare(t, u);
			else return ::llcpp::ZERO_VALUE<Orderning>;
		}

		#pragma endregion

	#pragma endregion
};

constexpr auto i1 = IsDifferenciable<int, char>().diff(1, 1)._Value;
using asdffffffff = IsDifferenciable<int, char>::FunctionCompareCheck_E::IS_VALID;
constexpr auto i2 = IsComparable<int, char>().isSameValue(1, 1);
constexpr auto i3 = IsComparable<int, char>().isSameValue(3, 1);

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSCOMPARE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
