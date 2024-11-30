//////////////////////////////////////////////
//	traits_signature.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSSIGNATURE_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSSIGNATURE_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TRAITSSIGNATURE_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_signature.hpp(incomplete) version error!"
		#else
			#error "traits_signature.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSSIGNATURE_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSSIGNATURE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSSIGNATURE_INCOMPLETE_HPP_)
#define LLANYLIB_TRAITSSIGNATURE_INCOMPLETE_HPP_
#define LLANYLIB_TRAITSSIGNATURE_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_TRAITSSIGNATURE_INCOMPLETE_MINOR_ 0


#include "traits_checker.hpp"
#undef LLANYLIB_INCOMPLETE_HPP_
#include "../types_base/functional_attributes.hpp"
#define LLANYLIB_INCOMPLETE_HPP_

namespace llcpp {
namespace meta {
namespace traits {
namespace __traits__ {

// Container example to being used in SignatureContainer to fill data with an parameter pack
class SignatureDummy;

template<class _Getter>
class FunctionGetterBase;

} // namespace __traits__
namespace signatures {

#define GENERIC_FUNCTION_GETTER_SIGNATURE_INCOMPLETE(function, name)	\
	class __FunctionGetter##name##;										\
	using FunctionGetter##name## =										\
		::llcpp::meta::traits::__traits__::FunctionGetterBase<			\
		::llcpp::meta::traits::signatures::__FunctionGetter##name##>

GENERIC_FUNCTION_GETTER_SIGNATURE_INCOMPLETE(dummy, Dummy);
GENERIC_FUNCTION_GETTER_SIGNATURE_INCOMPLETE(swap, Swap);

} // namespace signatures

template<
	::llcpp::meta::attributes::function_attributes_t _ATTRIBUTES
		= ::llcpp::meta::attributes::functional::CLASSIC,
	class _ReturnType = void, class... _FunctionArguments
>
class SignatureContainer;

template<
	class _ClassToCheck,
	::llcpp::meta::attributes::function_attributes_t _ATTRIBUTES =
		::llcpp::meta::attributes::functional::CONSTNOEXCEPTION,
	class _FunctionGetter =
		::llcpp::meta::traits::signatures::FunctionGetterDummy,
	class... _FunctionArguments
>
class SignatureChecker;

template<
	class _ClassToCheck,
	::llcpp::meta::attributes::function_attributes_t _ATTRIBUTES =
		::llcpp::meta::attributes::functional::CONSTNOEXCEPTION,
	class _FunctionGetter =
		::llcpp::meta::traits::signatures::FunctionGetterDummy,
	class _ReturnType = void, class... _FunctionArguments
>
class SignatureCheckerWithReturn;

template<
	class _ClassToCheck,
	class _SignatureContainer,
	class _FunctionGetter = ::llcpp::meta::traits::signatures::FunctionGetterDummy
>
class SignatureCheckerBySignature;

} // namespace traits
} // namespace meta
} // namespace llcpp


#elif defined(LLANYLIB_TRAITSSIGNATURE_HPP_)
	#if LLANYLIB_TRAITSSIGNATURE_MAYOR_ != 11 || LLANYLIB_TRAITSSIGNATURE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_signature.hpp version error!"
		#else
			#error "traits_signature.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSSIGNATURE_MAYOR_ || LLANYLIB_TRAITSSIGNATURE_MINOR_

#else
#define LLANYLIB_TRAITSSIGNATURE_HPP_
#define LLANYLIB_TRAITSSIGNATURE_MAYOR_ 11
#define LLANYLIB_TRAITSSIGNATURE_MINOR_ 0

#include "traits_checker.hpp"
#include "../types_base/functional_attributes.hpp"

namespace llcpp {
namespace meta {
namespace traits {
namespace __traits__ {

// Container example to being used in SignatureContainer to fill data with an parameter pack
class SignatureDummy {
	public:
		// Class related
		using _MyType		= SignatureDummy;

		// Types and enums
		template<class... _FunctionArguments>
		using FillObject	= void;
};

template<class _Getter>
class FunctionGetterBase : public _Getter {
	public:
		// Class related
		using _MyType	= FunctionGetterBase;
		using Getter	= _Getter;

	public:
		// Types and enums
		template<class ClassToCheck, class... FunctionArguments>
		using ReturnType = decltype(Getter::template get_return_type<ClassToCheck, FunctionArguments...>(LL_NULLPTR));

		template<class ClassToCheck, class... FunctionArguments>
		using FunctionData = traits::IntegralConstantContainer<
			::llcpp::meta::attributes::function_attributes_t,
			::llcpp::meta::attributes::function_attributes_t::CUSTOM<
				::std::is_const_v<ClassToCheck>,
				decltype(Getter::template get_noexcept<ClassToCheck, FunctionArguments...>(LL_NULLPTR))::value
			>,
			decltype(Getter::template get_return_type<ClassToCheck, FunctionArguments...>(LL_NULLPTR))
		>;
};

} // namespace __traits__
namespace signatures {

#define GENERIC_FUNCTION_GETTER_SIGNATURE(function, name)																						\
	class __FunctionGetter##name## {																											\
		public:																																	\
			using _MyType = __FunctionGetter##name##;																							\
		protected:																																\
			template<class, class>																												\
			static constexpr auto get_return_type(...) noexcept			-> llcpp::Emptyclass;													\
			template<class T, class... FunctionArguments>																									\
			static constexpr auto get_return_type(T* c) noexcept		-> decltype(c->##function##(::std::declval<FunctionArguments>()...));				\
			template<class, class>																												\
			static constexpr auto get_noexcept(...) noexcept			-> std::false_type;														\
			template<class T, class... FunctionArguments>																									\
			static constexpr auto get_noexcept(T* c) noexcept			-> std::bool_constant<noexcept(c->dummy(::std::declval<FunctionArguments>()...))>;	\
	};																																			\
	using FunctionGetter##name## =																												\
		::llcpp::meta::traits::__traits__::FunctionGetterBase<																					\
		::llcpp::meta::traits::signatures::__FunctionGetter##name##>

GENERIC_FUNCTION_GETTER_SIGNATURE(dummy, Dummy);
GENERIC_FUNCTION_GETTER_SIGNATURE(swap, Swap);

} // namespace signatures

template<
	class _ClassToCheck,
	::llcpp::meta::attributes::function_attributes_t _ATTRIBUTES,
	class _FunctionGetter,	class... _FunctionArguments
>
class SignatureChecker;

#pragma region SignatureType

template<
	::llcpp::meta::attributes::function_attributes_t _ATTRIBUTES
		= ::llcpp::meta::attributes::functional::CLASSIC,
	class _ReturnType = void, class... _FunctionArguments
>
class SignatureContainer {
	public:
		// Class related
		using _MyType		= SignatureContainer;
		using ReturnType	= _ReturnType;

	public:
		// Expresions
		::llcpp::meta::attributes::function_attributes_t ATTRIBUTES = _ATTRIBUTES;

	public:
		// Asseerts
		static_assert(!::std::is_same_v<ReturnType, llcpp::Emptyclass>,
			"Return type cannot be llcpp::Emptyclass");

	private:
		// Private functional
		template<class T>
		static constexpr auto get_signature(T*) noexcept {
			if constexpr (ATTRIBUTES.CONST && ATTRIBUTES.NOEXCEPTION)
				return traits::TypeContainer<ReturnType(T::*)(_FunctionArguments...) const noexcept>{};
			else if constexpr (!ATTRIBUTES.CONST && ATTRIBUTES.NOEXCEPTION)
				return traits::TypeContainer<ReturnType(T::*)(_FunctionArguments...) noexcept>{};
			else if constexpr (ATTRIBUTES.CONST && !ATTRIBUTES.NOEXCEPTION)
				return traits::TypeContainer<ReturnType(T::*)(_FunctionArguments...) const>{};
			else //if constexpr (!ATTRIBUTES.CONST && !ATTRIBUTES.NOEXCEPTION)
				return traits::TypeContainer<ReturnType(T::*)(_FunctionArguments...)>{};
		}
		template<>
		static constexpr auto get_signature<void>(void*) noexcept {
			if constexpr (ATTRIBUTES.CONST && ATTRIBUTES.NOEXCEPTION)
				return traits::TypeContainer<ReturnType(*)(_FunctionArguments...) const noexcept>{};
			else if constexpr (!ATTRIBUTES.CONST && ATTRIBUTES.NOEXCEPTION)
				return traits::TypeContainer<ReturnType(*)(_FunctionArguments...) noexcept>{};
			else if constexpr (ATTRIBUTES.CONST && !ATTRIBUTES.NOEXCEPTION)
				return traits::TypeContainer<ReturnType(*)(_FunctionArguments...) const>{};
			else //if constexpr (!ATTRIBUTES.CONST && !ATTRIBUTES.NOEXCEPTION)
				return traits::TypeContainer<ReturnType(*)(_FunctionArguments...)>{};
		}

	public:
		// Signature generate by class provided
		template<class ClassType>
		using Signature = typename decltype(_MyType::get_signature<ClassType>(LL_NULLPTR))::T;
		// Fills a template with a parameter pack of signature arguments
		template<class FunctionalityContainer>
		using FillObject = typename FunctionalityContainer::template FillObject<_FunctionArguments...>;
		// Fills a template with attributes of signature arguments
		template<class FunctionalityContainer>
		using FillObjectAttr = typename FunctionalityContainer::template FillObjectAttr<_ATTRIBUTES>;
		// Fills a template with a parameter pack and attributes of signature arguments
		template<class FunctionalityContainer>
		using FillObjectAll = typename FunctionalityContainer::template FillObjectAll<_ATTRIBUTES, _FunctionArguments...>;

		template<class ClassToCheck, class FunctionGetter>
		using GetSignatureChecker =
			::llcpp::meta::traits::SignatureChecker<ClassToCheck, _ATTRIBUTES, FunctionGetter, _FunctionArguments...>;
};

template<class ReturnType, class... FunctionArguments>
using SigatureNoexcept = SignatureContainer<::llcpp::meta::attributes::functional::NOEXCEPTION, ReturnType, FunctionArguments>;

template<class ReturnType, class... FunctionArguments>
using SignatureConst = SignatureContainer<::llcpp::meta::attributes::functional::CONST, ReturnType, FunctionArguments>;

template<class ReturnType, class... FunctionArguments>
using SignatureConstNoexcept = SignatureContainer<::llcpp::meta::attributes::functional::CONSTNOEXCEPTION, ReturnType, FunctionArguments>;

// Alias for SignatureConstNoexcept
template<class ReturnType, class... FunctionArguments>
using SigCN = SignatureConstNoexcept<ReturnType, FunctionArguments>;

#pragma endregion

// Signature checker has 1 found problem:
//	Conflict primitives [float/double, i32/i64...]:
//		N functions with same name
//		The main difference is float vs double
//		Ex: dummy(float) vs dummy(double)
//		Function with double parameter will not work properly
//		If functions differ by const attribute, it works, but if both has same signature but one conflictive type
//			it will not work properly
//		
//	If user is looking for a function that is overloaded, and its only parameter is a float
template<
	class _ClassToCheck,
	::llcpp::meta::attributes::function_attributes_t _ATTRIBUTES =
		::llcpp::meta::attributes::functional::CONSTNOEXCEPTION,
	class _FunctionGetter =
		::llcpp::meta::traits::signatures::FunctionGetterDummy,
	class... _FunctionArguments
>
class SignatureChecker {
	public:
		// Class related
		using _MyType			= SignatureChecker;

		// Types and enums
		using ClassToCheck		= _ClassToCheck;
		using FunctionGetter	= _FunctionGetter;

		// Sets class to const if const reqired in signature
		using ClassEditedByAttributes = ::llcpp::meta::traits::conditional_t<_ATTRIBUTES.CONST, const ClassToCheck, ClassToCheck>;
		// Process data to get the container that will be processed to validate if is valid signature
		using ResultContainer = FunctionGetter::template FunctionData<ClassEditedByAttributes, _FunctionArguments...>;

	public:
		// Expresions
		static constexpr ::llcpp::meta::attributes::function_attributes_t ATTRIBUTES = _ATTRIBUTES;

	public:
		// Functional
		using ReturnType = ResultContainer::U;
		static constexpr ll_bool_t IS_VALID_SIGNATURE_AND_ATTRIBUTES =
			!std::is_same_v<ReturnType, ::llcpp::Emptyclass>
			&& (ResultContainer::VALUE == ATTRIBUTES);
	protected:
		template<class ReturnType>
		static constexpr ll_bool_t IS_VALID =
			SignatureChecker::IS_VALID_SIGNATURE_AND_ATTRIBUTES
			&& std::is_same_v<typename SignatureChecker::ReturnType, ReturnType>;
};

// This utility has some blind points
// For more info check SignatureChecker<>
template<
	class _ClassToCheck,
	::llcpp::meta::attributes::function_attributes_t _ATTRIBUTES =
		::llcpp::meta::attributes::functional::CONSTNOEXCEPTION,
	class _FunctionGetter =
		::llcpp::meta::traits::signatures::FunctionGetterDummy,
	class _ReturnType = void, class... _FunctionArguments
>
class SignatureCheckerWithReturn : public SignatureChecker<_ClassToCheck, _ATTRIBUTES, _FunctionGetter, _FunctionArguments...> {
	public:
		// Class related
		using _MyType			= SignatureCheckerWithReturn;
		using SignatureChecker	= SignatureChecker<_ClassToCheck, _ATTRIBUTES, _FunctionGetter, _FunctionArguments...>;

		// Types and enums
		using ClassToCheck		= _ClassToCheck;
		using ReturnType		= _ReturnType;
		using FunctionGetter	= _FunctionGetter;

	public:
		// Expresions
		static constexpr ::llcpp::meta::attributes::function_attributes_t ATTRIBUTES = _ATTRIBUTES;

	public:
		// Asserts
		static_assert(!::std::is_same_v<ReturnType, llcpp::Emptyclass>,
			"Return type cannot be llcpp::Emptyclass");

	public:
		// Functional
		static constexpr ll_bool_t IS_VALID = SignatureChecker::template IS_VALID<ReturnType>;
};

template<
	class _ClassToCheck,
	class _SignatureContainer,
	class _FunctionGetter = ::llcpp::meta::traits::signatures::FunctionGetterDummy
>
class SignatureCheckerBySignature : public _SignatureContainer::template GetSignatureChecker<_ClassToCheck, _FunctionGetter> {
	public:
		// Class related
		using _MyType				= SignatureCheckerBySignature;
		using SignatureContainer	= _SignatureContainer;
		using SignatureChecker		= SignatureContainer::template GetSignatureChecker<_ClassToCheck, _FunctionGetter>;

		// Types and enums
		using ClassToCheck		= _ClassToCheck;
		using ReturnType		= SignatureContainer::ReturnType;
		using FunctionGetter	= _FunctionGetter;

	public:
		// Expresions
		static constexpr ::llcpp::meta::attributes::function_attributes_t ATTRIBUTES = SignatureChecker::ATTRIBUTES;

	public:
		// Asserts

	public:
		// Functional
		static constexpr ll_bool_t IS_VALID = SignatureChecker::template IS_VALID<ReturnType>;
};

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSSIGNATURE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
