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

#include "types_base_extra.hpp"

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

#include "types_base_extra.hpp"

namespace llcpp {
namespace meta {

class Boolean {
	#pragma region Types
	public:
		// Class related
		using _MyType = Boolean;

		// Types and enums
		enum class enum_bool : u8 {
			FALSE	= false,
			TRUE	= true,
			UNKNOWN,
			INVALID
		};

	#pragma endregion
	#pragma region Attributes
	private:
		enum_bool value;

	#pragma endregion
	#pragma region Functions
		#pragma region Private
	private:
		constexpr void simpleClear() noexcept { this->value = enum_bool::UNKNOWN; }

		#pragma endregion
		#pragma region Constructor
	public:
		constexpr Boolean() noexcept : value(enum_bool::UNKNOWN) {}
		constexpr ~Boolean() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Boolean(const Boolean& other) noexcept : value(other.value) {}
		constexpr Boolean& operator=(const Boolean& other) noexcept {
			this->value = other.value;
			return *this;
		}
		constexpr Boolean(Boolean&& other) noexcept : value(other.value) { other.simpleClear(); }
		constexpr Boolean& operator=(Boolean&& other) noexcept {
			this->value = other.value;
			other.simpleClear();
			return *this;
		}

		constexpr Boolean(const enum_bool value) noexcept : value(value) {}
		constexpr enum_bool operator=(const enum_bool value) noexcept {
			this->value = value;
			return value;
		}

		constexpr Boolean(const ll_bool_t value) noexcept
			: value(static_cast<enum_bool>(value)) {}
		constexpr ll_bool_t operator=(const ll_bool_t value) noexcept {
			this->value = static_cast<enum_bool>(value);
			return value;
		}

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
		__LL_NODISCARD__ constexpr explicit operator ll_bool_t() const noexcept {
			return this->value == enum_bool::TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t get_bool() const noexcept {
			return this->operator ll_bool_t();
		}

		__LL_NODISCARD__ constexpr explicit operator enum_bool() const noexcept {
			return this->value;
		}
		__LL_NODISCARD__ constexpr enum_bool get_Boolean() const noexcept {
			return this->operator enum_bool();
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Boolean& other) const noexcept {
			return this->value == other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Boolean& other) const noexcept {
			return this->value != other.value;
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ll_bool_t value) const noexcept {
			return this->value == static_cast<enum_bool>(value);
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const ll_bool_t value) const noexcept {
			return this->value != static_cast<enum_bool>(value);
		}

		#pragma endregion

	#pragma endregion
};

} // namespace meta

__LL_VAR_INLINE__ constexpr meta::Boolean BOOLEAN_FALSE			= llcpp::FALSE;
__LL_VAR_INLINE__ constexpr meta::Boolean BOOLEAN_TRUE			= llcpp::TRUE;
__LL_VAR_INLINE__ constexpr meta::Boolean BOOLEAN_INVALID		= meta::Boolean::enum_bool::INVALID;
__LL_VAR_INLINE__ constexpr meta::Boolean BOOLEAN_UNKNOWN_BOOL	= meta::Boolean::enum_bool::UNKNOWN;

} // namespace llcpp

#endif // LLANYLIB_BOOLEAN_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
