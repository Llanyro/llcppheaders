//////////////////////////////////////////////
//	Boolean.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_BOOLEAN_HPP_) // Guard && version protector
	#if LLANYLIB_BOOLEAN_MAYOR_ != 9 || LLANYLIB_BOOLEAN_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Boolean.hpp version error!"
		#else
			#error "Boolean.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_BOOLEAN_MAYOR_ || LLANYLIB_BOOLEAN_MINOR_

#else !defined(LLANYLIB_BOOLEAN_HPP_)
#define LLANYLIB_BOOLEAN_HPP_
#define LLANYLIB_BOOLEAN_MAYOR_ 9
#define LLANYLIB_BOOLEAN_MINOR_ 0

#include "types_base.hpp"

using ll_bool_t = bool;

namespace llcpp {

class Boolean {
	#pragma region Types
	public:
		// Class related
		using _MyType = Boolean;

		// Types and enums
		enum class enum_bool : ui8 {
			FALSE = false,
			TRUE = true,
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

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Boolean& other) noexcept {
			return this->value == other.value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Boolean& other) noexcept {
			return this->value != other.value;
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ll_bool_t value) noexcept {
			return this->value == static_cast<enum_bool>(value);
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const ll_bool_t value) noexcept {
			return this->value != static_cast<enum_bool>(value);
		}

		#pragma endregion

	#pragma endregion
};

} // namespace llcpp

#endif // LLANYLIB_BOOLEAN_HPP_
