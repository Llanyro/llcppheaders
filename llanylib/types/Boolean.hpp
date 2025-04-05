//////////////////////////////////////////////
//	Boolean.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_BOOLEAN_INCOMPLETE_HPP_)
	#if LLANYLIB_BOOLEAN_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_BOOLEAN_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Boolean.hpp(incomplete) version error!"
		#else
			#error "Boolean.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_BOOLEAN_INCOMPLETE_MAYOR_ || LLANYLIB_BOOLEAN_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_BOOLEAN_INCOMPLETE_HPP_)
	#define LLANYLIB_BOOLEAN_INCOMPLETE_HPP_
	#define LLANYLIB_BOOLEAN_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_BOOLEAN_INCOMPLETE_MINOR_ 0

#include "types.hpp"

namespace llcpp {
namespace meta {

class Boolean;

} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_BOOLEAN_HPP_)
	#if LLANYLIB_BOOLEAN_MAYOR_ != 11 || LLANYLIB_BOOLEAN_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Boolean.hpp version error!"
		#else
			#error "Boolean.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_BOOLEAN_MAYOR_ || LLANYLIB_BOOLEAN_MINOR_

#else
	#define LLANYLIB_BOOLEAN_HPP_
	#define LLANYLIB_BOOLEAN_MAYOR_ 11
	#define LLANYLIB_BOOLEAN_MINOR_ 0

#include "types.hpp"

namespace llcpp {

class Boolean : public ::llcpp::AlwaysValidTag {
	#pragma region Types
	public:
		// Class related
		using _MyType = Boolean;

		// Types and enums
		enum class enum_bool : u8 {
			False	= ::llcpp::FALSE,
			True	= ::llcpp::TRUE,
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
		constexpr ~Boolean() noexcept {}

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

		constexpr Boolean(const volatile enum_bool value) noexcept = delete;
		constexpr Boolean operator=(const volatile enum_bool value) noexcept = delete;
		constexpr Boolean(const volatile ll_bool_t value) noexcept = delete;
		constexpr Boolean operator=(const volatile ll_bool_t value) noexcept = delete;

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

__LL_VAR_INLINE__ constexpr _MyType BOOLEAN_FALSE	= ::llcpp::FALSE;
__LL_VAR_INLINE__ constexpr _MyType BOOLEAN_TRUE	= ::llcpp::TRUE;
__LL_VAR_INLINE__ constexpr _MyType BOOLEAN_INVALID	= _MyType::enum_bool::Invalid;
__LL_VAR_INLINE__ constexpr _MyType BOOLEAN_UNKNOWN	= _MyType::enum_bool::Unknown;

} // namespace boolean

} // namespace llcpp

#endif // LLANYLIB_BOOLEAN_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
