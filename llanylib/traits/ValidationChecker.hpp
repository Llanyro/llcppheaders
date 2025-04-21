//////////////////////////////////////////////
//	ValidationChecker.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_VALIDATIONCHECKER_INCOMPLETE_HPP_)
	#if LLANYLIB_VALIDATIONCHECKER_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_VALIDATIONCHECKER_INCOMPLETE_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "ValidationChecker.hpp(incomplete) version error!"
		#else
			#error "ValidationChecker.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_VALIDATIONCHECKER_INCOMPLETE_MAYOR_ || LLANYLIB_VALIDATIONCHECKER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_VALIDATIONCHECKER_INCOMPLETE_HPP_)
	#define LLANYLIB_VALIDATIONCHECKER_INCOMPLETE_HPP_
	#define LLANYLIB_VALIDATIONCHECKER_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_VALIDATIONCHECKER_INCOMPLETE_MINOR_ 0

#include "../concepts/valid_type.hpp"

namespace llcpp {
namespace meta {
namespace traits {
class ValidationChecker;
} // namespace traits
} // namespace meta
} // namespace llcpp


#elif defined(LLANYLIB_VALIDATIONCHECKER_HPP_)
	#if LLANYLIB_VALIDATIONCHECKER_MAYOR_ != 12 || LLANYLIB_VALIDATIONCHECKER_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "ValidationChecker.hpp version error!"
		#else
			#error "ValidationChecker.hpp version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_VALIDATIONCHECKER_MAYOR_ || LLANYLIB_VALIDATIONCHECKER_MINOR_

#else
	#define LLANYLIB_VALIDATIONCHECKER_HPP_
	#define LLANYLIB_VALIDATIONCHECKER_MAYOR_ 12
	#define LLANYLIB_VALIDATIONCHECKER_MINOR_ 0

#include "../concepts/valid_type.hpp"

namespace llcpp {
namespace meta {
namespace traits {

// Checks if any type is a Validable/Invalidable type
// Enums by type:
//	Valid:		Type is always valid
//	Invalid:	Type is always invalid
//	ToCheck:	User needs to check in execution time calling isValid()
//	Primitive:	Is a primitive (user decides by its value if is valid or not)
//	Array:		Is an array (user decides by its values if is valid or not)
//	Pointer:	Is a pointer (user decides by its values if is valid or not [usually nullptr is invalid])
//	Unknown:	User cannot check via this standard if object is valid or not
//	Error:		Type maybe is Valid and Invalid at he same, time, so none of them applies
class ValidationChecker {
	#pragma region Types
	public:
		// Class related
		using _MyType	= ValidationChecker;

	#pragma endregion
	#pragma region Functions
	private:
		// Process type to get if is a always valid class or other
		template<class T>
		__LL_NODISCARD__ static constexpr ::llcpp::misc::ValidType getValidType() noexcept {
			constexpr ll_bool_t IS_VALID = ::llcpp::meta::concepts::base::IsAlwaysValid<T>;
			constexpr ll_bool_t IS_INVALID = ::llcpp::meta::concepts::base::IsAlwaysInvalid<T>;

			if constexpr (::llcpp::meta::traits::is_primitive_v<T>)
				return ::llcpp::misc::ValidType::Primitive;
			else if constexpr (::std::is_array_v<T>)
				return ::llcpp::misc::ValidType::Array;
			else if constexpr (::std::is_pointer_v<T>)
				return ::llcpp::misc::ValidType::Pointer;
			else if constexpr (IS_VALID && IS_INVALID) {
				static_assert(IS_VALID && IS_INVALID,
					"A class has AlwaysValidTag and AlwaysInvalidTag attributes!");
				return ::llcpp::misc::ValidType::Error;
			}
			else if constexpr (IS_VALID)
				return ::llcpp::misc::ValidType::Valid;
			else if constexpr (IS_INVALID)
				return ::llcpp::misc::ValidType::Invalid;
			else if constexpr (::llcpp::meta::concepts::signature::HasValidationType<T>)
				return ::llcpp::misc::ValidType::ToCheck;
			else return ::llcpp::misc::ValidType::Unknown;
		}

		// Checks if valid attriute is out of bounds
		template<class T>
		__LL_NODISCARD__ static constexpr ll_bool_t hasValidAttribute() noexcept {
			constexpr u8 result = static_cast<u8>(_MyType::getValidType<T>());
			//constexpr u8 MIN = static_cast<u8>(::llcpp::misc::ValidType::Valid);
			constexpr u8 MAX = static_cast<u8>(::llcpp::misc::ValidType::Error);
			return result <= MAX;
			//return result >= MIN && result <= MAX;
		}
		// Returns true if T inherits from AlwaysValid/AlwaysInvalid
		template<class T>
		__LL_NODISCARD__ static constexpr ll_bool_t isValid() noexcept {
			switch (_MyType::getValidType<T>()) {
				case ::llcpp::misc::ValidType::Invalid:
				case ::llcpp::misc::ValidType::Valid:
					return true;
				default:
					return false;
			}
		}

	#pragma endregion
	#pragma region ExpresionsAndTypes
	public:
		template<class T>
		static constexpr ll_bool_t has_valid_attribute_v = _MyType::hasValidAttribute<T>();
		template<class T>
		static constexpr ::llcpp::misc::ValidType valid_type_v = _MyType::getValidType<T>();
		template<class T, ::llcpp::misc::ValidType _TYPE>
		static constexpr ll_bool_t is_same_valid_type_v = _MyType::getValidType<T>() == _TYPE;

		template<
			class ClassToCheck,
			class OnValidAttr,
			class OnInvalidAttr,
			class OnToCheck,
			class OnPrimitive,
			class OnArray,
			class OnPointer,
			class OnUnknown,
			class OnError
		>
		using conditional_valid_t = ::llcpp::meta::traits::type_by_valid_type_t<
			_MyType::valid_type_v<ClassToCheck>,
			OnValidAttr,
			OnInvalidAttr,
			OnToCheck,
			OnPrimitive,
			OnArray,
			OnPointer,
			OnUnknown,
			OnError
		>;
	#pragma endregion
};

// if ValidType is not included by functions or inheritance, we use user type providded
template<class ClassToCheck, class InhertiExtra>
using ValidationWrapper = 
	::llcpp::meta::traits::conditional_t<
		::llcpp::meta::traits::ValidationChecker::is_same_valid_type_v<
			ClassToCheck,
			::llcpp::misc::ValidType::Unknown
		>,
		InhertiExtra,
		::llcpp::DummyClass
	>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_VALIDATIONCHECKER_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
