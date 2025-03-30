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

#if __LL_SIGNATURE_HELPER__ == 1
	#include "../traits_signature.hpp"
#endif // __LL_SIGNATURE_HELPER__

#include "../traits_valid_type.hpp"

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

#if __LL_SIGNATURE_HELPER__ == 1
	#include "../traits_signature.hpp"
#endif // __LL_SIGNATURE_HELPER__

#include "../traits_valid_type.hpp"

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
		template<ll_bool_t _VALUE, class U>
		using ValidTypeContainer = ::llcpp::meta::traits::IntegralConstantContainer<ll_bool_t, _VALUE, U>;

	private:
#if __LL_SIGNATURE_HELPER__ == 1
		template<class WrappedT, class SignatureIsValid, class Signature>
		using SignatureCheck = ::llcpp::meta::traits::SignatureCheckerBySignature<WrappedT, SignatureIsValid, Signature>;
#endif // __LL_SIGNATURE_HELPER__

	#pragma endregion
	#pragma region Functions
	private:
		// Process type to get if is a always valid class or other
		template<class T>
		__LL_NODISCARD__ static constexpr ::llcpp::meta::ValidType getValidType() noexcept {
			constexpr ll_bool_t IS_VALID = ::std::is_base_of_v<::llcpp::AlwaysValidTag, T>;
			constexpr ll_bool_t IS_INVALID = ::std::is_base_of_v<::llcpp::AlwaysInvalidTag, T>;

			if constexpr (::llcpp::meta::traits::is_primitive_v<T>)
				return ::llcpp::meta::ValidType::Primitive;
			else if constexpr (::std::is_array_v<T>)
				return ::llcpp::meta::ValidType::Array;
			else if constexpr (::std::is_pointer_v<T>)
				return ::llcpp::meta::ValidType::Pointer;
			else if constexpr (IS_VALID && IS_INVALID) {
				static_assert(IS_VALID && IS_INVALID,
					"A class has AlwaysValidTag and AlwaysInvalidTag attributes!");
				return ::llcpp::meta::ValidType::Error;
			}
			else if constexpr (IS_VALID)
				return ::llcpp::meta::ValidType::Valid;
			else if constexpr (IS_INVALID)
				return ::llcpp::meta::ValidType::Invalid;
#if __LL_SIGNATURE_HELPER__ == 1
			else {
				using Signature = ::llcpp::meta::traits::SigCN<::llcpp::meta::ValidType>;
				using SignatureIsValid = ::llcpp::meta::traits::signatures::GetIsValid;
				if constexpr (SignatureCheck<T, Signature, SignatureIsValid>::IS_VALID)
					return ::llcpp::meta::ValidType::ToCheck;
				else return ::llcpp::meta::ValidType::Unknown;
			}
#else
			else return ::llcpp::meta::ValidType::Unknown;
#endif // __LL_SIGNATURE_HELPER__
		}
		// Checks if valid attriute is out of bounds
		template<class T>
		__LL_NODISCARD__ static constexpr ll_bool_t hasValidAttribute() noexcept {
			constexpr u8 result = static_cast<u8>(_MyType::getValidType<T>());
			//constexpr u8 MIN = static_cast<u8>(::llcpp::meta::ValidType::Valid);
			constexpr u8 MAX = static_cast<u8>(::llcpp::meta::ValidType::ToCheck);
			return result <= MAX;
			//return result >= MIN && result <= MAX;
		}
		// Returns true if T inherits from AlwaysValid/AlwaysInvalid
		template<class T>
		__LL_NODISCARD__ static constexpr ll_bool_t isValid() noexcept {
			constexpr ::llcpp::meta::ValidType t = _MyType::getValidType<T>();
			return t == ::llcpp::meta::ValidType::Invalid || t == ::llcpp::meta::ValidType::Valid;
		}

	#pragma endregion
	#pragma region ExpresionsAndTypes
	public:
		template<class T>
		static constexpr ll_bool_t has_valid_attribute_v = _MyType::hasValidAttribute<T>();
		template<class T>
		static constexpr ::llcpp::meta::ValidType valid_type_v = _MyType::getValidType<T>();
		template<class T, ::llcpp::meta::ValidType _TYPE>
		static constexpr ll_bool_t is_valid_type_v = _MyType::getValidType<T>() == _TYPE;

		template<
			class ClassToCheck,
			class OnValidAttr,
			class OnInvalidAttr,
			class OnToCheck,
			class OnUnknown,
			class OnError
		>
		using conditional_valid_t = ::llcpp::meta::traits::type_by_valid_type_t<
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
//template<class ClassToCheck, class InhertiExtra>
//using ValidationWrapper = 
//	::llcpp::meta::traits::conditional_t<
//		::llcpp::meta::traits::ValidationChecker::is_valid_type_v<
//			ClassToCheck,
//			::llcpp::meta::traits::ValidationChecker::ValidType::Unknown
//		>,
//		InhertiExtra,
//		::llcpp::DummyClass
//	>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSVALIDATECHECKER_HPP_
