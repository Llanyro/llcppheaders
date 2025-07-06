//////////////////////////////////////////////
//	Boolean.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_BOOLEAN_INCOMPLETE_HPP_)
	#if LLANYLIB_BOOLEAN_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_BOOLEAN_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Boolean.hpp(incomplete) version error!"
		#else
			#error "Boolean.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_BOOLEAN_INCOMPLETE_MAYOR_ || LLANYLIB_BOOLEAN_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_BOOLEAN_INCOMPLETE_HPP_)
	#define LLANYLIB_BOOLEAN_INCOMPLETE_HPP_
	#define LLANYLIB_BOOLEAN_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_BOOLEAN_INCOMPLETE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/types.hpp>
#else
	#include "types.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {

class Boolean;

} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_BOOLEAN_HPP_)
	#if LLANYLIB_BOOLEAN_MAYOR_ != 12 || LLANYLIB_BOOLEAN_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Boolean.hpp version error!"
		#else
			#error "Boolean.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_BOOLEAN_MAYOR_ || LLANYLIB_BOOLEAN_MINOR_

#else
	#define LLANYLIB_BOOLEAN_HPP_
	#define LLANYLIB_BOOLEAN_MAYOR_ 12
	#define LLANYLIB_BOOLEAN_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/types.hpp>
#else
	#include "types.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {

class Boolean : public ::llcpp::AlwaysValidTag {
	#pragma region Types
	public:
		// Class related
		using _MyType = Boolean;
		using ValidTag				= ::llcpp::AlwaysValidTag;

		// Types and enums
		enum class enum_bool : u8 {
			False	= ::llcpp::LL_FALSE,
			True	= ::llcpp::LL_TRUE,
			Invalid,
			Unknown
		};

	#pragma endregion
	#pragma region Attributes
	private:
		enum_bool value;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr Boolean() noexcept
			: value(_MyType::enum_bool::Unknown)
		{ __LL_FUNCTION_INIT__; }
		constexpr ~Boolean() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Boolean(const Boolean& other) noexcept
			: value(other.value)
		{ __LL_FUNCTION_INIT__; }
		constexpr Boolean& operator=(const Boolean& other) noexcept {
			__LL_FUNCTION_INIT__;
			this->set(other.value);
			return *this;
		}
		constexpr Boolean(Boolean&& other) noexcept
			: value(other.value)
		{
			__LL_FUNCTION_INIT__;
			other.clear();
		}
		constexpr Boolean& operator=(Boolean&& other) noexcept {
			__LL_FUNCTION_INIT__;
			this->set(other.value);
			other.clear();
			return *this;
		}

		constexpr Boolean(const enum_bool value) noexcept
			: value(value)
		{ __LL_FUNCTION_INIT__; }
		constexpr Boolean& operator=(const enum_bool value) noexcept {
			__LL_FUNCTION_INIT__;
			this->set(value);
			return *this;
		}

		constexpr Boolean(const ll_bool_t value) noexcept
			: value(_MyType::convert(value))
		{ __LL_FUNCTION_INIT__; }
		constexpr Boolean& operator=(const ll_bool_t value) noexcept {
			__LL_FUNCTION_INIT__;
			this->set(value);
			return *this;
		}

		//constexpr Boolean(const volatile enum_bool value) noexcept = delete;
		//constexpr Boolean operator=(const volatile enum_bool value) noexcept = delete;
		//constexpr Boolean(const volatile ll_bool_t value) noexcept = delete;
		//constexpr Boolean operator=(const volatile ll_bool_t value) noexcept = delete;

		constexpr Boolean(const volatile Boolean&) noexcept = delete;
		constexpr Boolean& operator=(const volatile Boolean&) noexcept = delete;
		constexpr Boolean(volatile Boolean&&) noexcept = delete;
		constexpr Boolean& operator=(volatile Boolean&&) noexcept= delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Boolean*() const noexcept {
			__LL_FUNCTION_INIT__;
			return this;
		}
		__LL_NODISCARD__ constexpr explicit operator Boolean*() noexcept {
			__LL_FUNCTION_INIT__;
			return this;
		}

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ static constexpr ll_bool_t convert(const enum_bool value) noexcept {
			__LL_FUNCTION_INIT__;
			return value == enum_bool::True;
		}
		__LL_NODISCARD__ static constexpr enum_bool convert(const ll_bool_t value) noexcept {
			__LL_FUNCTION_INIT__;
			return static_cast<enum_bool>(value);
		}

		constexpr void set(const ll_bool_t value) noexcept {
			__LL_FUNCTION_INIT__;
			this->value = _MyType::convert(value);
		}
		constexpr void set(const enum_bool value) noexcept {
			__LL_FUNCTION_INIT__;
			this->value = value;
		}

		__LL_NODISCARD__ constexpr explicit operator ll_bool_t() const noexcept {
			__LL_FUNCTION_INIT__;
			return _MyType::convert(value);
		}
		__LL_NODISCARD__ constexpr ll_bool_t as_bool() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->operator ll_bool_t();
		}

		__LL_NODISCARD__ constexpr explicit operator enum_bool() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->value;
		}
		__LL_NODISCARD__ constexpr enum_bool as_enum() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->operator enum_bool();
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Boolean& other) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->value == other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Boolean& other) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->value != other.value;
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ll_bool_t value) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->value == _MyType::convert(value);
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const ll_bool_t value) const noexcept {
			__LL_FUNCTION_INIT__;
			return this->value != _MyType::convert(value);
		}

		constexpr void clear() noexcept {
			__LL_FUNCTION_INIT__;
			this->set(_MyType::enum_bool::Unknown);
		}

		#pragma endregion

	#pragma endregion
};

namespace boolean {

using _MyType = ::llcpp::meta::Boolean::_MyType;

__LL_VAR_INLINE__ constexpr _MyType BOOLEAN_FALSE	= _MyType::enum_bool::False;
__LL_VAR_INLINE__ constexpr _MyType BOOLEAN_TRUE	= _MyType::enum_bool::True;
__LL_VAR_INLINE__ constexpr _MyType BOOLEAN_INVALID	= _MyType::enum_bool::Invalid;
__LL_VAR_INLINE__ constexpr _MyType BOOLEAN_UNKNOWN	= _MyType::enum_bool::Unknown;

#if __LL_INCLUDE_KATS == 1
namespace kat {

#pragma region Standard
__LL_KAT_FUNCTION_CONSTEXPR(
	false_false_kat,
	::llcpp::meta::boolean::BOOLEAN_FALSE == ::llcpp::LL_FALSE,
	"False needs to be equal to false"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	true_true_kat,
	::llcpp::meta::boolean::BOOLEAN_TRUE == ::llcpp::LL_TRUE,
	"True needs to be equal to true"
);

#pragma endregion
#pragma region False
__LL_KAT_FUNCTION_CONSTEXPR(
	false_true_kat,
	::llcpp::meta::boolean::BOOLEAN_FALSE != ::llcpp::meta::boolean::BOOLEAN_TRUE,
	"False cannot be equal to true"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	false_invalid_kat,
	::llcpp::meta::boolean::BOOLEAN_FALSE != ::llcpp::meta::boolean::BOOLEAN_INVALID,
	"False cannot be equal to invalid"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	false_unknown_kat,
	::llcpp::meta::boolean::BOOLEAN_FALSE != ::llcpp::meta::boolean::BOOLEAN_UNKNOWN,
	"False cannot be equal to unknonw"
);

#pragma endregion
#pragma region True
__LL_KAT_FUNCTION_CONSTEXPR(
	true_false_kat,
	::llcpp::meta::boolean::BOOLEAN_TRUE != ::llcpp::meta::boolean::BOOLEAN_FALSE,
	"True cannot be equal to false"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	true_invalid_kat,
	::llcpp::meta::boolean::BOOLEAN_TRUE != ::llcpp::meta::boolean::BOOLEAN_INVALID,
	"True cannot be equal to invalid"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	true_unknown_kat,
	::llcpp::meta::boolean::BOOLEAN_TRUE != ::llcpp::meta::boolean::BOOLEAN_UNKNOWN,
	"True cannot be equal to unknonw"
);

#pragma endregion
#pragma region Invalid
__LL_KAT_FUNCTION_CONSTEXPR(
	invalid_false_kat,
	::llcpp::meta::boolean::BOOLEAN_INVALID != ::llcpp::meta::boolean::BOOLEAN_FALSE,
	"Invalid cannot be equal to false"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	invalid_true_kat,
	::llcpp::meta::boolean::BOOLEAN_INVALID != ::llcpp::meta::boolean::BOOLEAN_TRUE,
	"Invalid cannot be equal to true"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	invalid_unknown_kat,
	::llcpp::meta::boolean::BOOLEAN_INVALID != ::llcpp::meta::boolean::BOOLEAN_UNKNOWN,
	"Invalid cannot be equal to unknonw"
);

#pragma endregion
#pragma region Unknown
__LL_KAT_FUNCTION_CONSTEXPR(
	unknown_false_kat,
	::llcpp::meta::boolean::BOOLEAN_UNKNOWN != ::llcpp::meta::boolean::BOOLEAN_FALSE,
	"Unknown cannot be equal to false"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	unknown_true_kat,
	::llcpp::meta::boolean::BOOLEAN_UNKNOWN != ::llcpp::meta::boolean::BOOLEAN_TRUE,
	"Unknown cannot be equal to true"
);
__LL_KAT_FUNCTION_CONSTEXPR(
	unknown_invalid_kat,
	::llcpp::meta::boolean::BOOLEAN_UNKNOWN != ::llcpp::meta::boolean::BOOLEAN_INVALID,
	"Unknown cannot be equal to invalid"
);

#pragma endregion

__LL_NODISCARD__ constexpr ::llcpp::string boolean_kats() noexcept {
	::llcpp::string result = ::llcpp::meta::boolean::kat::false_false_kat();
	if(result) return result;
	result = ::llcpp::meta::boolean::kat::true_true_kat();
	if(result) return result;

	result = ::llcpp::meta::boolean::kat::false_true_kat();
	if(result) return result;
	result = ::llcpp::meta::boolean::kat::false_invalid_kat();
	if(result) return result;
	result = ::llcpp::meta::boolean::kat::false_unknown_kat();
	if(result) return result;

	result = ::llcpp::meta::boolean::kat::true_false_kat();
	if(result) return result;
	result = ::llcpp::meta::boolean::kat::true_invalid_kat();
	if(result) return result;
	result = ::llcpp::meta::boolean::kat::true_unknown_kat();
	if(result) return result;

	result = ::llcpp::meta::boolean::kat::invalid_false_kat();
	if(result) return result;
	result = ::llcpp::meta::boolean::kat::invalid_true_kat();
	if(result) return result;
	result = ::llcpp::meta::boolean::kat::invalid_unknown_kat();
	if(result) return result;

	result = ::llcpp::meta::boolean::kat::unknown_false_kat();
	if(result) return result;
	result = ::llcpp::meta::boolean::kat::unknown_true_kat();
	if(result) return result;
	result = ::llcpp::meta::boolean::kat::unknown_invalid_kat();
	if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::boolean::kat::boolean_kats() == LL_NULLPTR, "Boolean KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace boolean
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_BOOLEAN_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_BOOLEAN_EXTRA_HPP_)
		#if LLANYLIB_BOOLEAN_EXTRA_MAYOR_ != 12 || LLANYLIB_BOOLEAN_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "Boolean.hpp(extra) version error!"
			#else
				#error "Boolean.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_BOOLEAN_EXTRA_MAYOR_ || LLANYLIB_BOOLEAN_EXTRA_MINOR_

	#else
		#define LLANYLIB_BOOLEAN_EXTRA_HPP_
		#define LLANYLIB_BOOLEAN_EXTRA_MAYOR_ 12
		#define LLANYLIB_BOOLEAN_EXTRA_MINOR_ 0

namespace llcpp {

using Boolean = ::llcpp::meta::Boolean;

namespace boolean {

__LL_VAR_INLINE__ constexpr ::llcpp::Boolean BOOLEAN_FALSE		= ::llcpp::meta::boolean::BOOLEAN_FALSE;
__LL_VAR_INLINE__ constexpr ::llcpp::Boolean BOOLEAN_TRUE		= ::llcpp::meta::boolean::BOOLEAN_TRUE;
__LL_VAR_INLINE__ constexpr ::llcpp::Boolean BOOLEAN_INVALID	= ::llcpp::meta::boolean::BOOLEAN_INVALID;
__LL_VAR_INLINE__ constexpr ::llcpp::Boolean BOOLEAN_UNKNOWN	= ::llcpp::meta::boolean::BOOLEAN_UNKNOWN;

} // namespace boolean
} // namespace llcpp

	#endif // LLANYLIB_BOOLEAN_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
