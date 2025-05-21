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

#include "types.hpp"

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

#include "types.hpp"

namespace llcpp {

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
		constexpr Boolean() noexcept : value(_MyType::enum_bool::Unknown) {}
		constexpr ~Boolean() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Boolean(const Boolean& other) noexcept : value(other.value) {}
		constexpr Boolean& operator=(const Boolean& other) noexcept {
			this->set(other.value);
			return *this;
		}
		constexpr Boolean(Boolean&& other) noexcept : value(other.value) { other.clear(); }
		constexpr Boolean& operator=(Boolean&& other) noexcept {
			this->set(other.value);
			other.clear();
			return *this;
		}

		constexpr Boolean(const enum_bool value) noexcept : value(value) {}
		constexpr Boolean operator=(const enum_bool value) noexcept {
			this->set(value);
			return *this;
		}

		constexpr Boolean(const ll_bool_t value) noexcept : value(_MyType::convert(value)) {}
		constexpr Boolean operator=(const ll_bool_t value) noexcept {
			this->set(value);
			return *this;
		}

		//constexpr Boolean(const volatile enum_bool value) noexcept = delete;
		//constexpr Boolean operator=(const volatile enum_bool value) noexcept = delete;
		//constexpr Boolean(const volatile ll_bool_t value) noexcept = delete;
		//constexpr Boolean operator=(const volatile ll_bool_t value) noexcept = delete;

		constexpr Boolean(const volatile Boolean&) = delete;
		constexpr Boolean& operator=(const volatile Boolean&) = delete;
		constexpr Boolean(volatile Boolean&&) = delete;
		constexpr Boolean& operator=(volatile Boolean&&) = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Boolean*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Boolean*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ static constexpr ll_bool_t convert(const enum_bool value) noexcept {
			return value == enum_bool::True;
		}
		__LL_NODISCARD__ static constexpr enum_bool convert(const ll_bool_t value) noexcept {
			return static_cast<enum_bool>(value);
		}

		constexpr void set(const ll_bool_t value) noexcept { this->value = _MyType::convert(value); }
		constexpr void set(const enum_bool value) noexcept { this->value = value; }

		__LL_NODISCARD__ constexpr explicit operator ll_bool_t() const noexcept {
			return _MyType::convert(value);
		}
		__LL_NODISCARD__ constexpr ll_bool_t as_bool() const noexcept {
			return this->operator ll_bool_t();
		}

		__LL_NODISCARD__ constexpr explicit operator enum_bool() const noexcept {
			return this->value;
		}
		__LL_NODISCARD__ constexpr enum_bool as_enum() const noexcept {
			return this->operator enum_bool();
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Boolean& other) const noexcept {
			return this->value == other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Boolean& other) const noexcept {
			return this->value != other.value;
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ll_bool_t value) const noexcept {
			return this->value == _MyType::convert(value);
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const ll_bool_t value) const noexcept {
			return this->value != _MyType::convert(value);
		}

		constexpr void clear() noexcept { this->set(_MyType::enum_bool::Unknown); }

		#pragma endregion

	#pragma endregion
};

namespace boolean {

using _MyType = ::llcpp::Boolean::_MyType;

__LL_VAR_INLINE__ constexpr _MyType BOOLEAN_FALSE	= _MyType::enum_bool::False;
__LL_VAR_INLINE__ constexpr _MyType BOOLEAN_TRUE	= _MyType::enum_bool::True;
__LL_VAR_INLINE__ constexpr _MyType BOOLEAN_INVALID	= _MyType::enum_bool::Invalid;
__LL_VAR_INLINE__ constexpr _MyType BOOLEAN_UNKNOWN	= _MyType::enum_bool::Unknown;

namespace kat {

#define __GENERICKAT(VALUE, STR)					\
	do {											\
		if (!(VALUE)) {								\
			if constexpr (::llcpp::LL_STATIC_KATS)	\
				static_assert(VALUE, STR);			\
			return STR;								\
		}											\
	} while(0)


__LL_NODISCARD__ constexpr ::llcpp::string standardKat() noexcept {
	#define LL_FALSE_EQ_FALSE			__LL_STRING_PREFIX "False needs to be equal to false"
	#define LL_TRUE_EQ_TRUE				__LL_STRING_PREFIX "True needs to be equal to true"

	constexpr ll_bool_t FALSE_EQ_FALSE	= ::llcpp::boolean::BOOLEAN_FALSE == ::llcpp::LL_FALSE;
	constexpr ll_bool_t TRUE_EQ_TRUE	= ::llcpp::boolean::BOOLEAN_TRUE == ::llcpp::LL_TRUE;

	__GENERICKAT(FALSE_EQ_FALSE,		LL_FALSE_EQ_FALSE);
	__GENERICKAT(TRUE_EQ_TRUE,			LL_TRUE_EQ_TRUE);

	#undef LL_FALSE_EQ_FALSE
	#undef LL_TRUE_EQ_TRUE

	return nullptr;
}
__LL_NODISCARD__ constexpr ::llcpp::string falseKat() noexcept {
	#define LL_FALSE_NEQ_TRUE				__LL_STRING_PREFIX "False cannot be equal to true"
	#define LL_FALSE_NEQ_INVALID			__LL_STRING_PREFIX "False cannot be equal to invalid"
	#define LL_FALSE_NEQ_UNKNOWN			__LL_STRING_PREFIX "False cannot be equal to unknonw"

	constexpr ll_bool_t FALSE_NEQ_TRUE		= ::llcpp::boolean::BOOLEAN_FALSE != ::llcpp::boolean::BOOLEAN_TRUE;
	constexpr ll_bool_t FALSE_NEQ_INVALID	= ::llcpp::boolean::BOOLEAN_FALSE != ::llcpp::boolean::BOOLEAN_INVALID;
	constexpr ll_bool_t FALSE_NEQ_UNKNOWN	= ::llcpp::boolean::BOOLEAN_FALSE != ::llcpp::boolean::BOOLEAN_UNKNOWN;

	__GENERICKAT(FALSE_NEQ_TRUE,			LL_FALSE_NEQ_TRUE);
	__GENERICKAT(FALSE_NEQ_INVALID,			LL_FALSE_NEQ_INVALID);
	__GENERICKAT(FALSE_NEQ_UNKNOWN,			LL_FALSE_NEQ_UNKNOWN);

	#undef LL_FALSE_NEQ_TRUE
	#undef LL_FALSE_NEQ_INVALID
	#undef LL_FALSE_NEQ_UNKNOWN

	return nullptr;
}
__LL_NODISCARD__ constexpr ::llcpp::string trueKat() noexcept {
	#define LL_TRUE_NEQ_FALSE				__LL_STRING_PREFIX "True cannot be equal to false"
	#define LL_TRUE_NEQ_INVALID				__LL_STRING_PREFIX "True cannot be equal to invalid"
	#define LL_TRUE_NEQ_UNKNOWN				__LL_STRING_PREFIX "True cannot be equal to unknonw"

	constexpr ll_bool_t TRUE_NEQ_FALSE		= ::llcpp::boolean::BOOLEAN_TRUE != ::llcpp::boolean::BOOLEAN_FALSE;
	constexpr ll_bool_t TRUE_NEQ_INVALID	= ::llcpp::boolean::BOOLEAN_TRUE != ::llcpp::boolean::BOOLEAN_INVALID;
	constexpr ll_bool_t TRUE_NEQ_UNKNOWN	= ::llcpp::boolean::BOOLEAN_TRUE != ::llcpp::boolean::BOOLEAN_UNKNOWN;

	__GENERICKAT(TRUE_NEQ_FALSE,			LL_TRUE_NEQ_FALSE);
	__GENERICKAT(TRUE_NEQ_INVALID,			LL_TRUE_NEQ_INVALID);
	__GENERICKAT(TRUE_NEQ_UNKNOWN,			LL_TRUE_NEQ_UNKNOWN);

	#undef LL_TRUE_NEQ_FALSE
	#undef LL_TRUE_NEQ_INVALID
	#undef LL_TRUE_NEQ_UNKNOWN

	return nullptr;
}
__LL_NODISCARD__ constexpr ::llcpp::string invalidKat() noexcept {
	#define LL_INVALID_NEQ_FALSE			__LL_STRING_PREFIX "Invalid cannot be equal to false"
	#define LL_INVALID_NEQ_TRUE				__LL_STRING_PREFIX "Invalid cannot be equal to true"
	#define LL_INVALID_NEQ_UNKNOWN			__LL_STRING_PREFIX "Invalid cannot be equal to unknonw"

	constexpr ll_bool_t INVALID_NEQ_FALSE	= ::llcpp::boolean::BOOLEAN_INVALID != ::llcpp::boolean::BOOLEAN_FALSE;
	constexpr ll_bool_t INVALID_NEQ_TRUE	= ::llcpp::boolean::BOOLEAN_INVALID != ::llcpp::boolean::BOOLEAN_TRUE;
	constexpr ll_bool_t INVALID_NEQ_UNKNOWN	= ::llcpp::boolean::BOOLEAN_INVALID != ::llcpp::boolean::BOOLEAN_UNKNOWN;

	__GENERICKAT(INVALID_NEQ_FALSE,			LL_INVALID_NEQ_FALSE);
	__GENERICKAT(INVALID_NEQ_TRUE,			LL_INVALID_NEQ_TRUE);
	__GENERICKAT(INVALID_NEQ_UNKNOWN,		LL_INVALID_NEQ_UNKNOWN);

	#undef LL_INVALID_NEQ_FALSE
	#undef LL_INVALID_NEQ_TRUE
	#undef LL_INVALID_NEQ_UNKNOWN

	return nullptr;
}
__LL_NODISCARD__ constexpr ::llcpp::string unknownKat() noexcept {
	#define LL_UNKNOWN_NEQ_FALSE	__LL_STRING_PREFIX "Unknown cannot be equal to false"
	#define LL_UNKNOWN_NEQ_TRUE		__LL_STRING_PREFIX "Unknown cannot be equal to true"
	#define LL_UNKNOWN_NEQ_UNKNOWN	__LL_STRING_PREFIX "Unknown cannot be equal to invalid"

	constexpr ll_bool_t UNKNOWN_NEQ_FALSE	= ::llcpp::boolean::BOOLEAN_UNKNOWN != ::llcpp::boolean::BOOLEAN_FALSE;
	constexpr ll_bool_t UNKNOWN_NEQ_TRUE	= ::llcpp::boolean::BOOLEAN_UNKNOWN != ::llcpp::boolean::BOOLEAN_TRUE;
	constexpr ll_bool_t UNKNOWN_NEQ_INVALID	= ::llcpp::boolean::BOOLEAN_UNKNOWN != ::llcpp::boolean::BOOLEAN_INVALID;

	__GENERICKAT(UNKNOWN_NEQ_FALSE,			LL_UNKNOWN_NEQ_FALSE);
	__GENERICKAT(UNKNOWN_NEQ_TRUE,			LL_UNKNOWN_NEQ_TRUE);
	__GENERICKAT(UNKNOWN_NEQ_INVALID,		LL_UNKNOWN_NEQ_UNKNOWN);

	#undef LL_INVALID_NEQ_FALSE
	#undef LL_INVALID_NEQ_TRUE
	#undef LL_INVALID_NEQ_UNKNOWN

	return nullptr;
}
__LL_NODISCARD__ constexpr ::llcpp::string booleanKats() noexcept {
	::llcpp::string result = ::llcpp::boolean::kat::standardKat();
	if(result) return result;
	result = ::llcpp::boolean::kat::falseKat();
	if(result) return result;
	result = ::llcpp::boolean::kat::trueKat();
	if(result) return result;
	result = ::llcpp::boolean::kat::invalidKat();
	if(result) return result;
	result = ::llcpp::boolean::kat::unknownKat();
	if(result) return result;

	return nullptr;
}

static_assert(::llcpp::boolean::kat::booleanKats() == nullptr, "Boolean KAT not OK");

#undef __GENERICKAT

} // namespace kat
} // namespace boolean
} // namespace llcpp

#endif // LLANYLIB_BOOLEAN_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
