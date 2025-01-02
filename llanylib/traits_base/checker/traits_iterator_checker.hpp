//////////////////////////////////////////////
//	traits_object_checker.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CHECKERITERATOR_INCOMPLETE_HPP_)
	#if LLANYLIB_CHECKERITERATOR_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_CHECKERITERATOR_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_object_checker.hpp(incomplete) version error!"
		#else
			#error "traits_object_checker.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CHECKERITERATOR_INCOMPLETE_MAYOR_ || LLANYLIB_CHECKERITERATOR_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CHECKERITERATOR_INCOMPLETE_HPP_)
#define LLANYLIB_CHECKERITERATOR_INCOMPLETE_HPP_
#define LLANYLIB_CHECKERITERATOR_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_CHECKERITERATOR_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_CHECKERITERATOR_HPP_)
	#if LLANYLIB_CHECKERITERATOR_MAYOR_ != 11 || LLANYLIB_CHECKERITERATOR_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_object_checker.hpp version error!"
		#else
			#error "traits_object_checker.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CHECKERITERATOR_MAYOR_ || LLANYLIB_CHECKERITERATOR_MINOR_

#else
#define LLANYLIB_CHECKERITERATOR_HPP_
#define LLANYLIB_CHECKERITERATOR_MAYOR_ 11
#define LLANYLIB_CHECKERITERATOR_MINOR_ 0

#include "../traits_signature.hpp"
#include "../traits_type_wrapper.hpp"

#include <array>

using List = std::array<int, 5>;
using Container = List::iterator;

namespace llcpp {
namespace meta {
namespace traits {

namespace __traits__ {

enum class IteratorType : u8 {
	ClassType,
	Pointer,
	Array,
	Primitive,
	Unknown
};

template<::llcpp::meta::traits::__traits__::IteratorType IT, ll_bool_t _BOOL>
using Double = ::llcpp::meta::traits::DoubleConstantContainer<::llcpp::meta::traits::__traits__::IteratorType, ll_bool_t, IT, _BOOL>;

template<class T, ll_bool_t USE_CONST_IF>
constexpr auto getIteratorType() {
	namespace __t__ = ::llcpp::meta::traits::__traits__;
	if constexpr (::std::is_pointer_v<T>)
		return __t__::Double<__t__::IteratorType::Pointer, ::std::is_const_v<::std::remove_pointer_t<T>>>;
	else if constexpr (::std::is_array_v<T>)
		return __t__::Double<__t__::IteratorType::Array, ::std::is_const_v<::llcpp::meta::traits::array_type_t<T>>>;
	else if constexpr (::std::is_class_v<T>)
		return __t__::Double<__t__::IteratorType::ClassType, USE_CONST_IF>;
	else if constexpr (::std::is_array_v<T>)
		return IteratorType::Array;
	else return IteratorType::Primitive;
}

} // namespace __traits__

template<
	class _T,
	::llcpp::meta::traits::__traits__::IteratorType _ITERATOR_TYPE,
	ll_bool_t CONST_MODE
>
class IsIterator : public ::llcpp::meta::Cluster {
	#pragma region Types
	public:
		// Class related
		using _MyType	= IsIterator;				// This class with template
		using Cluster	= ::llcpp::meta::Cluster;	// This is a cluster type class

		// Types and enums
		using T			= _T;						// Element to compare by

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ::llcpp::meta::traits::__traits__::IteratorType ITERATOR_TYPE = _ITERATOR_TYPE;
		static constexpr ll_bool_t IS_ITERATOR = ::llcpp::FALSE;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr IsIterator() noexcept : Cluster() {}
		constexpr ~IsIterator() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr IsIterator(const IsIterator&) = delete;
		constexpr IsIterator& operator=(const IsIterator&) = delete;
		constexpr IsIterator(IsIterator&&) = delete;
		constexpr IsIterator& operator=(IsIterator&&) = delete;
		constexpr IsIterator(const volatile IsIterator&) = delete;
		constexpr IsIterator& operator=(const volatile IsIterator&) = delete;
		constexpr IsIterator(volatile IsIterator&&) = delete;
		constexpr IsIterator& operator=(volatile IsIterator&&) = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const IsIterator*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator IsIterator*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr Boolean isSameValue(t_cinput t, u_cinput u) const noexcept {
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

		#pragma endregion

	#pragma endregion
};

template<class _T>
class IsIterator<_T, ::llcpp::meta::traits::__traits__::IteratorType::Pointer, ::std::is_const_v<::std::remove_pointer_t<_T>>> : public ::llcpp::meta::Cluster {
	#pragma region Types
	public:
		// Class related
		using _MyType	= IsIterator;				// This class with template
		using Cluster	= ::llcpp::meta::Cluster;	// This is a cluster type class

		// Types and enums
		using T			= _T;						// Element to compare by

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ::llcpp::meta::traits::__traits__::IteratorType ITERATOR_TYPE = _ITERATOR_TYPE;
		static constexpr ll_bool_t IS_ITERATOR = ::llcpp::TRUE;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr IsIterator() noexcept : Cluster() {}
		constexpr ~IsIterator() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr IsIterator(const IsIterator&) = delete;
		constexpr IsIterator& operator=(const IsIterator&) = delete;
		constexpr IsIterator(IsIterator&&) = delete;
		constexpr IsIterator& operator=(IsIterator&&) = delete;
		constexpr IsIterator(const volatile IsIterator&) = delete;
		constexpr IsIterator& operator=(const volatile IsIterator&) = delete;
		constexpr IsIterator(volatile IsIterator&&) = delete;
		constexpr IsIterator& operator=(volatile IsIterator&&) = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const IsIterator*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator IsIterator*() noexcept { return this; }

		#pragma endregion

	#pragma endregion
};

template<class _T, ll_bool_t CONST_MODE>
class IsIterator<_T, ::llcpp::meta::traits::__traits__::IteratorType::ClassType, CONST_MODE> : public ::llcpp::meta::Cluster {
	#pragma region Types
	public:
		// Class related
		using _MyType				= IsIterator;						// This class with template
		using Cluster				= ::llcpp::meta::Cluster;			// This is a cluster type class

		// Types and enums
		using T						= _T;								// Element to compare by
		using cinput				= ::llcpp::meta::traits::cinput<T>;	// T type as const type reference
		using input					= ::llcpp::meta::traits::input<T>;	// T type as type reference

		// Type expresions
		static constexpr ::llcpp::meta::attributes::function_attributes_t FUNC_ATTR =
			::llcpp::meta::attributes::function_attributes_t::CUSTOM<::std::is_const_v<T>, ::llcpp::TRUE>;

		// Signature types prep
		template<class Signature, class Function>
		using SignatureCheck		= ::llcpp::meta::traits::SignatureCheckerBySignature<T, Signature, Function>;

		// Signatures
		using OperatorIncrement		= ::llcpp::meta::traits::signatures::GetOperatorIncrement;
		using OperatorDecrement		= ::llcpp::meta::traits::signatures::GetOperatorDecrement;
		using OperatorArrow			= ::llcpp::meta::traits::signatures::GetOperatorArrow;
		using OperatorReference		= ::llcpp::meta::traits::signatures::GetOperatorMult;	// Multiplication and reference operator are the same

		// Signarure containers
		using PrecrementSignature	= ::llcpp::meta::traits::SigatureNoexcept<input>;
		using PoscrementSignature	= ::llcpp::meta::traits::SigatureNoexcept<T, int>;

		// Signature increment
		using PreIncrementCheck		= SignatureCheck<PrecrementSignature, OperatorIncrement>;
		using PosIncrementCheck		= SignatureCheck<PoscrementSignature, OperatorIncrement>;

		// Signature decrement
		using PreDecrementCheck		= SignatureCheck<PrecrementSignature, OperatorDecrement>;
		using PosDecrementCheck		= SignatureCheck<PoscrementSignature, OperatorDecrement>;


		using ReferenceCheck = ::llcpp::meta::traits::SignatureChecker<
			T,
			::llcpp::meta::attributes::functional::CONSTNOEXCEPTION,
			OperatorReference
		>;
		using ReferenceCheck = ::llcpp::meta::traits::SignatureChecker<
			T,
			::llcpp::meta::attributes::functional::CONSTNOEXCEPTION,
			OperatorReference
		>;



	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ::llcpp::meta::traits::__traits__::IteratorType ITERATOR_TYPE = _ITERATOR_TYPE;
		static constexpr ll_bool_t IS_ITERATOR =
			PreIncrementCheck::IS_VALID
			&& PosIncrementCheck::IS_VALID
			&& PreDecrementCheck::IS_VALID
			&& PosDecrementCheck::IS_VALID
			&& ReferenceCheck::IS_VALID_SIGNATURE_AND_ATTRIBUTES
			;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr IsIterator() noexcept : Cluster() {}
		constexpr ~IsIterator() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr IsIterator(const IsIterator&) = delete;
		constexpr IsIterator& operator=(const IsIterator&) = delete;
		constexpr IsIterator(IsIterator&&) = delete;
		constexpr IsIterator& operator=(IsIterator&&) = delete;
		constexpr IsIterator(const volatile IsIterator&) = delete;
		constexpr IsIterator& operator=(const volatile IsIterator&) = delete;
		constexpr IsIterator(volatile IsIterator&&) = delete;
		constexpr IsIterator& operator=(volatile IsIterator&&) = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const IsIterator*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator IsIterator*() noexcept { return this; }

		#pragma endregion

	#pragma endregion
};

template<class T>
using is_iterator_t =
	::llcpp::meta::traits::IsIterator<
		T,
		::llcpp::meta::traits::__traits__::getIteratorType<T>()
	>;

constexpr auto asd = is_iterator_t<Container>::ReferenceCheck::IS_VALID_SIGNATURE_AND_ATTRIBUTES;

constexpr auto asssdas = std::is_const_v<std::remove_pointer_t<const int*>>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CHECKERITERATOR_HPP_

#if !defined(LLANYLIB_CHECKERITERATOR_EXTRA_HPP_) && !defined(LLANYLIB_ERROR_HPP_)
#define LLANYLIB_CHECKERITERATOR_EXTRA_HPP_

#endif // LLANYLIB_CHECKERITERATOR_EXTRA_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
