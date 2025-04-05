//////////////////////////////////////////////
//	valid_type.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_VALID_TYPE_HPP_) // Guard && version protector
	#if LLANYLIB_VALID_TYPE_MAYOR_ != 11 || LLANYLIB_VALID_TYPE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "valid_type.hpp version error!"
		#else
			#error "valid_type.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_VALID_TYPE_MAYOR_ || LLANYLIB_VALID_TYPE_MINOR_

#else
	#define LLANYLIB_VALID_TYPE_HPP_
	#define LLANYLIB_VALID_TYPE_MAYOR_ 11
	#define LLANYLIB_VALID_TYPE_MINOR_ 0

#include "concepts.hpp"

#include "../types_base/ValidType.hpp"

namespace llcpp {
namespace meta {
namespace concepts {

template<class T>
concept IsAlwaysValid = ::std::is_base_of_v<::llcpp::AlwaysValidTag, T>;
template<class T>
concept IsAlwaysInvalid = ::std::is_base_of_v<::llcpp::AlwaysInvalidTag, T>;

template<class T>
concept HasValidationType = requires (T t) {
	{ t.validationType() } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<::llcpp::meta::ValidType>;
};

} // namespace concepts

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

	#pragma endregion
	#pragma region Functions
	private:
		// Process type to get if is a always valid class or other
		template<class T>
		__LL_NODISCARD__ static constexpr ::llcpp::meta::ValidType getValidType() noexcept {
			constexpr ll_bool_t IS_VALID = ::llcpp::meta::concepts::IsAlwaysValid<T>;
			constexpr ll_bool_t IS_INVALID = ::llcpp::meta::concepts::IsAlwaysInvalid<T>;

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
			else if constexpr (::llcpp::meta::concepts::HasValidationType<T>)
				return ::llcpp::meta::ValidType::ToCheck;
			else return ::llcpp::meta::ValidType::Unknown;
		}

		// Checks if valid attriute is out of bounds
		template<class T>
		__LL_NODISCARD__ static constexpr ll_bool_t hasValidAttribute() noexcept {
			constexpr u8 result = static_cast<u8>(_MyType::getValidType<T>());
			//constexpr u8 MIN = static_cast<u8>(::llcpp::meta::ValidType::Valid);
			constexpr u8 MAX = static_cast<u8>(::llcpp::meta::ValidType::Error);
			return result <= MAX;
			//return result >= MIN && result <= MAX;
		}
		// Returns true if T inherits from AlwaysValid/AlwaysInvalid
		template<class T>
		__LL_NODISCARD__ static constexpr ll_bool_t isValid() noexcept {
			switch (_MyType::getValidType<T>()) {
				case ::llcpp::meta::ValidType::Invalid:
				case ::llcpp::meta::ValidType::Valid:
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
		static constexpr ::llcpp::meta::ValidType valid_type_v = _MyType::getValidType<T>();
		template<class T, ::llcpp::meta::ValidType _TYPE>
		static constexpr ll_bool_t is_same_valid_type_v = _MyType::getValidType<T>() == _TYPE;

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


} // namespace traits

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_VALID_TYPE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
