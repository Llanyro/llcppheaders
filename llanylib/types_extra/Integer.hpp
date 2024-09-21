//////////////////////////////////////////////
//	Integer.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INTEGER_HPP_) // Guard && version protector
	#if LLANYLIB_INTEGER_MAYOR_ != 10 || LLANYLIB_INTEGER_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Integer.hpp version error!"
		#else
			#error "Integer.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_INTEGER_MAYOR_ || LLANYLIB_INTEGER_MINOR_

#else !defined(LLANYLIB_INTEGER_HPP_)
#define LLANYLIB_INTEGER_HPP_
#define LLANYLIB_INTEGER_MAYOR_ 10
#define LLANYLIB_INTEGER_MINOR_ 0

#include "../traits/traits_type_update.hpp"
#include "../utils/algorithm.hpp"

#include <array>

namespace llcpp {
namespace meta {

template<class _T, u64 _EXTENSION, ll_bool_t _IS_SIGNED>
class Integer {
	#pragma region Types
	public:
		// Class related
		using _MyType	= Integer;

		// Types and enums
		using T			= _T;
		using low_t		= T;										// Lowest bytes of number, unsigned
		using high_t	= meta::traits::type_signed<T, _IS_SIGNED>;	// Highest part of the number signed
		using array_low = std::array<low_t, _EXTENSION>;

	#pragma endregion
	#pragma region Expresions
		static constexpr u64 EXTENSION = _EXTENSION;
		static constexpr ll_bool_t IS_SIGNED = _IS_SIGNED;
		static constexpr u64 BYTES_STORED =
			(8 * (sizeof(low) + (EXTENSION * sizeof(high))))
			//- static_cast<u8>(IS_SIGNED);
			- traits::conditional_value_v<IS_SIGNED, i8, 1, 0>;

	#pragma endregion
	#pragma region Asserts
		static_assert(EXTENSION > 0,
			"EXTENSION cannot be 0");

	#pragma endregion
	#pragma region Attributes
	private:
		array_low low;
		high_t high;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr Integer() noexcept
			: low(algorithm::make_constructed_array<array_low, low_t, EXTENSION, 0>())
			, high()
		{}
		constexpr ~Integer() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Integer(const Integer& other) noexcept
			: value(std::forward<const IC&>(other.value))
		{}
		constexpr Integer& operator=(const Integer& other) noexcept {
			meta::algorithm::DataManipulatorCluster<low>().copy()
			this->value = std::forward<const IC&>(other.value);
			return *this;
		}
		constexpr Integer(Integer&& other) noexcept
			: value(std::forward<IC&&>(other.value))
		{ other.clear(other) }
		constexpr Integer& operator=(Integer&& other) noexcept {
			this->t_val = std::forward<IC&&>(other.t_val);
			other.clear()
			return *this;
		}
		constexpr Integer(const volatile Integer&) = delete;
		constexpr Integer& operator=(const volatile Integer&) = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Integer*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Integer*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions


		#pragma endregion

	#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_INTEGER_HPP_
