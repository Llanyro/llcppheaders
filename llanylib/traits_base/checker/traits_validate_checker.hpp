//////////////////////////////////////////////
//	traits_validate_checker.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TRAITSVALIDATECHECKER_INCOMPLETE_HPP_)
	#if LLANYLIB_TRAITSVALIDATECHECKER_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TRAITSVALIDATECHECKER_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_validate_checker.hpp(incomplete) version error!"
		#else
			#error "traits_validate_checker.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSVALIDATECHECKER_INCOMPLETE_MAYOR_ || LLANYLIB_TRAITSVALIDATECHECKER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TRAITSVALIDATECHECKER_INCOMPLETE_HPP_)
	#define LLANYLIB_TRAITSVALIDATECHECKER_INCOMPLETE_HPP_
	#define LLANYLIB_TRAITSVALIDATECHECKER_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_TRAITSVALIDATECHECKER_INCOMPLETE_MINOR_ 0


#include "../traits_signature.hpp"
#include "../traits_type_wrapper.hpp"

class ValidationChecker;

#elif defined(LLANYLIB_TRAITSVALIDATECHECKER_HPP_)
	#if LLANYLIB_TRAITSVALIDATECHECKER_MAYOR_ != 11 || LLANYLIB_TRAITSVALIDATECHECKER_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_validate_checker.hpp version error!"
		#else
			#error "traits_validate_checker.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TRAITSVALIDATECHECKER_MAYOR_ || LLANYLIB_TRAITSVALIDATECHECKER_MINOR_

#else
	#define LLANYLIB_TRAITSVALIDATECHECKER_HPP_
	#define LLANYLIB_TRAITSVALIDATECHECKER_MAYOR_ 11
	#define LLANYLIB_TRAITSVALIDATECHECKER_MINOR_ 0

#include "../traits_signature.hpp"
#include "../traits_type_wrapper.hpp"

namespace llcpp {
namespace meta {
namespace traits {

// Checks if any type is a Validable/Invalidable type
// Enums by type:
//	Valid:		Type is always valid
//	Invalid:	Type is always invalid
//	ToCheck:	User needs to check in execution time calling isValid()
//	Unknown:	User cannot check via this standard if object is valid or not
//	Error:		Type maybe is Valid and Invalid at he same, time, so none of the applies
class ValidationChecker {
	#pragma region Types
	public:
		// Class related
		using _MyType	= ValidationChecker;

		// Types and enums
		/// Do not change order
		enum class ValidType : u8 { Valid, Invalid, ToCheck, Unknown, Error };
		template<ll_bool_t _VALUE, class U>
		using ValidTypeContainer = ::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, _TYPE, U>;

	private:
		template<class WrappedT, class SignatureIsValid, class Signature>
		using SignatureCheck = ::llcpp::meta::traits::SignatureCheckerBySignature<WrappedT, SignatureIsValid, Signature>;

	#pragma endregion
	#pragma region Functions
	public:
		// Process type to get if is a always valid class or other
		template<class T>
		__LL_NODISCARD__ static constexpr _MyType::ValidType getValidType() noexcept {
			using WrappedT					= ::llcpp::meta::traits::PrimitiveWrapper<T>;
			constexpr ll_bool_t IS_VALID	= ::std::is_base_of_v<::llcpp::AlwaysValid, WrappedT>;
			constexpr ll_bool_t IS_INVALID	= ::std::is_base_of_v<::llcpp::AlwaysInvalid, WrappedT>;

			if constexpr (IS_VALID && IS_INVALID) {
				static_assert(IS_VALID && IS_INVALID,
					"A class has AlwaysValid and AlwaysInvalid attributes!");
				return _MyType::ValidType::Error;
			}
			else if constexpr (IS_VALID)
				return _MyType::ValidType::Valid;
			else if constexpr (IS_INVALID)
				return _MyType::ValidType::Invalid;
			else {
				using Signature = ::llcpp::meta::traits::SigCN<_MyType::ValidType>;
				using SignatureIsValid = ::llcpp::meta::traits::signatures::GetIsValid;

				if constexpr (SignatureCheck<WrappedT, Signature, SignatureIsValid>::IS_VALID)
					return _MyType::ValidType::ToCheck;
				else return _MyType::ValidType::Unknown;
			}
		}
		template<class T>
		__LL_NODISCARD__ static constexpr ll_bool_t hasValidAttribute() noexcept {
			constexpr u8 result = static_cast<u8>(_MyType::getValidType<T>());
			constexpr u8 MIN = static_cast<u8>(_MyType::ValidType::Valid);
			constexpr u8 MAX = static_cast<u8>(_MyType::ValidType::ToCheck);
			return result >= MIN && result <= MAX;
		}
		template<class T>
		__LL_NODISCARD__ static constexpr ll_bool_t isValid() noexcept {
			constexpr _MyType::ValidType t = _MyType::getValidType<T>();
			return t == _MyType::ValidType::Invalid || t == _MyType::ValidType::Valid;
		}

	#pragma endregion
	#pragma region ExpresionsAndTypes
	public:
		template<class T>
		static constexpr ll_bool_t has_valid_attribute_v = _MyType::hasValidAttribute<T>();
		template<class T>
		static constexpr _MyType::ValidType valid_type_v = _MyType::getValidType<T>();
		template<class T, _MyType::ValidType _TYPE>
		static constexpr ll_bool_t is_valid_type_v = _MyType::getValidType<T>() == _TYPE;

		template<
			_MyType::ValidType _TYPE,
			class OnValidAttr,
			class OnInvalidAttr,
			class OnToCheck,
			class OnUnknown,
			class OnError
		>
		using type_by_valid_type_t = ::std::disjunction<
			::llcpp::meta::traits::BoolConstantContainer<_TYPE == _MyType::ValidType::Valid, OnValidAttr>,
			::llcpp::meta::traits::BoolConstantContainer<_TYPE == _MyType::ValidType::Invalid, OnInvalidAttr>,
			::llcpp::meta::traits::BoolConstantContainer<_TYPE == _MyType::ValidType::ToCheck, OnToCheck>,
			::llcpp::meta::traits::BoolConstantContainer<_TYPE == _MyType::ValidType::Unknown, OnUnknown>,
			::llcpp::meta::traits::BoolConstantContainer<_TYPE == _MyType::ValidType::Error, OnError>,
			::llcpp::meta::traits::TrueContainerEmptyClass
		>::U;

		template<
			class ClassToCheck,
			class OnValidAttr,
			class OnInvalidAttr,
			class OnToCheck,
			class OnUnknown,
			class OnError
		>
		using conditional_valid_t = type_by_valid_type_t<
			_MyType::valid_type_v<ClassToCheck>,
			OnValidAttr,
			OnInvalidAttr,
			OnToCheck,
			OnUnknown,
			OnError
		>;
	#pragma endregion
};

// if ValidType is not included by functions or inheritance, we use user type providded
template<class ClassToCheck, class InhertiExtra>
using ValidationWrapper = 
	::llcpp::meta::traits::conditional_t<
		::llcpp::meta::traits::ValidationChecker::is_valid_type_v<
			ClassToCheck,
			::llcpp::meta::traits::ValidationChecker::ValidType::Unknown
		>,
		InhertiExtra,
		::llcpp::DummyClass
	>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSVALIDATECHECKER_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_TRAITSVALIDATECHECKER_EXTRA_HPP_)
		#if LLANYLIB_TRAITSVALIDATECHECKER_EXTRA_MAYOR_ != 11 || LLANYLIB_TRAITSVALIDATECHECKER_EXTRA_MINOR_ < 0
			#if defined(__LL_REAL_CXX23)
				#warning "traits_validate_checker.hpp(extra) version error!"
			#else
				#error "traits_validate_checker.hpp(extra) version error!"
			#endif // __LL_REAL_CXX23
		#endif // LLANYLIB_TRAITSVALIDATECHECKER_EXTRA_MAYOR_ || LLANYLIB_TRAITSVALIDATECHECKER_EXTRA_MINOR_

	#else
		#define LLANYLIB_TRAITSVALIDATECHECKER_EXTRA_HPP_
		#define LLANYLIB_TRAITSVALIDATECHECKER_EXTRA_MAYOR_ 11
		#define LLANYLIB_TRAITSVALIDATECHECKER_EXTRA_MINOR_ 0

	#endif // LLANYLIB_TRAITSVALIDATECHECKER_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
