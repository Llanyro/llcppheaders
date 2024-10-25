//////////////////////////////////////////////
//	traits_primitive_types.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TRAITSPRIMITIVETYPES_HPP_) // Guard && version protector
	#if LLANYLIB_TRAITSPRIMITIVETYPES_MAYOR_ != 10 || LLANYLIB_TRAITSPRIMITIVETYPES_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_primitive_types.hpp version error!"
		#else
			#error "traits_primitive_types.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_TRAITSPRIMITIVETYPES_MAYOR_ || LLANYLIB_TRAITSPRIMITIVETYPES_MINOR_

#else !defined(LLANYLIB_TRAITSPRIMITIVETYPES_HPP_)
#define LLANYLIB_TRAITSPRIMITIVETYPES_HPP_
#define LLANYLIB_TRAITSPRIMITIVETYPES_MAYOR_ 10
#define LLANYLIB_TRAITSPRIMITIVETYPES_MINOR_ 0

#include "../math/limits.hpp"
#include "../traits/traits_checker.hpp"

#include <compare>

namespace llcpp {
namespace meta {
namespace traits {

// Empty dummy class to use with primitive types
// Its usefull to use in function checkers with primitive types
template<class _T>
class PrimitiveBase {
	#pragma region Types
	public:
		// Class related
		using _MyType			= PrimitiveBase;

		// Types and enums
		using T					= _T;

		using Big_u8			= traits::type_bigger_of_two<T, u8>;
		using Big_u16			= traits::type_bigger_of_two<T, u16>;
		using Big_u32			= traits::type_bigger_of_two<T, u32>;
		using Big_u64			= traits::type_bigger_of_two<T, u64>;
		using Big_i8			= traits::type_bigger_of_two<T, i8>;
		using Big_i16			= traits::type_bigger_of_two<T, i16>;
		using Big_i32			= traits::type_bigger_of_two<T, i32>;
		using Big_i64			= traits::type_bigger_of_two<T, i64>;
		using Big_f32			= traits::type_bigger_of_two<T, f32>;
		using Big_f64			= traits::type_bigger_of_two<T, f64>;
		using Big_f128			= traits::type_bigger_of_two<T, f128>;
		using Big_bool			= traits::type_bigger_of_two<T, ll_bool_t>;

		using OrdeningByType	=
			traits::conditional_t<
				std::is_floating_point_v<T>,
				std::partial_ordering,
				std::strong_ordering
			>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr T ZERO_VALUE = math::ZERO_VALUE<T>;
		static constexpr T ZERO_C_CMP_VALUE = math::ZERO_VALUE<c_cmp_t>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(meta::traits::is_basic_type_v<T>,
			"Type must be a basic/primitive type");
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Attributes
	protected:
		T primitive;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr PrimitiveBase() noexcept : primitive(_MyType::ZERO_VALUE) {}
		constexpr ~PrimitiveBase() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr PrimitiveBase(const PrimitiveBase& other) noexcept
			: primitive(std::forward<const T&>(other.primitive)) {}
		constexpr PrimitiveBase& operator=(const PrimitiveBase& other) noexcept {
			this->primitive = std::forward<const T&>(other.primitive);
			return *this;
		}
		constexpr PrimitiveBase(PrimitiveBase&& other) noexcept
			: primitive(std::forward<T&&>(other.primitive))
		{ other.clear(); }
		constexpr PrimitiveBase& operator=(PrimitiveBase&& other) noexcept {
			this->primitive = std::forward<T&&>(other.primitive);
			other.clear();
			return *this;
		}

		constexpr PrimitiveBase(const T& primitive) noexcept
			: primitive(std::forward<const T&>(primitive)) {}
		constexpr PrimitiveBase& operator=(const T& primitive) noexcept {
			this->primitive = std::forward<const T&>(primitive);
			return *this;
		}
		constexpr PrimitiveBase(T&& primitive) noexcept
			: primitive(std::forward<T&&>(primitive))
		{ primitive = _MyType::ZERO_VALUE; }
		constexpr PrimitiveBase& operator=(T&& primitive) noexcept {
			this->primitive = std::forward<T&&>(primitive);
			primitive = _MyType::ZERO_VALUE;
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const PrimitiveBase*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator PrimitiveBase*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Comparations
	public:
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const u8) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const u16) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const u32) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const u64) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const i8) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const i16) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const i32) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const i64) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const f32) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const f64) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const f128) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const ll_bool_t) const noexcept { return llcpp::FALSE; }

		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const u8) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const u16) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const u32) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const u64) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const i8) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const i16) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const i32) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const i64) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const f32) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const f64) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const f128) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const ll_bool_t) const noexcept { return llcpp::TRUE; }

		__LL_NODISCARD__ constexpr ll_bool_t operator>(const u8) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const u16) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const u32) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const u64) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const i8) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const i16) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const i32) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const i64) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const f32) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const f64) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const f128) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const ll_bool_t) const noexcept { return llcpp::TRUE; }

		__LL_NODISCARD__ constexpr ll_bool_t operator<(const u8) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const u16) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const u32) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const u64) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const i8) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const i16) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const i32) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const i64) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const f32) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const f64) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const f128) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const ll_bool_t) const noexcept { return llcpp::FALSE; }

		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const u8) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const u16) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const u32) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const u64) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const i8) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const i16) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const i32) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const i64) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const f32) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const f64) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const f128) const noexcept { return llcpp::TRUE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const ll_bool_t) const noexcept { return llcpp::TRUE; }

		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const u8) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const u16) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const u32) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const u64) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const i8) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const i16) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const i32) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const i64) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const f32) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const f64) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const f128) const noexcept { return llcpp::FALSE; }
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const ll_bool_t) const noexcept { return llcpp::FALSE; }

		__LL_NODISCARD__ constexpr c_cmp_t compare(const u8) const noexcept { return ZERO_C_CMP_VALUE; }
		__LL_NODISCARD__ constexpr c_cmp_t compare(const u16) const noexcept { return ZERO_C_CMP_VALUE; }
		__LL_NODISCARD__ constexpr c_cmp_t compare(const u32) const noexcept { return ZERO_C_CMP_VALUE; }
		__LL_NODISCARD__ constexpr c_cmp_t compare(const u64) const noexcept { return ZERO_C_CMP_VALUE; }
		__LL_NODISCARD__ constexpr c_cmp_t compare(const i8) const noexcept { return ZERO_C_CMP_VALUE; }
		__LL_NODISCARD__ constexpr c_cmp_t compare(const i16) const noexcept { return ZERO_C_CMP_VALUE; }
		__LL_NODISCARD__ constexpr c_cmp_t compare(const i32) const noexcept { return ZERO_C_CMP_VALUE; }
		__LL_NODISCARD__ constexpr c_cmp_t compare(const i64) const noexcept { return ZERO_C_CMP_VALUE; }
		__LL_NODISCARD__ constexpr c_cmp_t compare(const f32) const noexcept { return ZERO_C_CMP_VALUE; }
		__LL_NODISCARD__ constexpr c_cmp_t compare(const f64) const noexcept { return ZERO_C_CMP_VALUE; }
		__LL_NODISCARD__ constexpr c_cmp_t compare(const f128) const noexcept { return ZERO_C_CMP_VALUE; }
		__LL_NODISCARD__ constexpr c_cmp_t compare(const ll_bool_t) const noexcept { return ZERO_C_CMP_VALUE; }

		__LL_NODISCARD__ constexpr OrdeningByType operator<=>(const u8) const noexcept { return OrdeningByType(); }
		__LL_NODISCARD__ constexpr OrdeningByType operator<=>(const u16) const noexcept { return OrdeningByType(); }
		__LL_NODISCARD__ constexpr OrdeningByType operator<=>(const u32) const noexcept { return OrdeningByType(); }
		__LL_NODISCARD__ constexpr OrdeningByType operator<=>(const u64) const noexcept { return OrdeningByType(); }
		__LL_NODISCARD__ constexpr OrdeningByType operator<=>(const i8) const noexcept { return OrdeningByType(); }
		__LL_NODISCARD__ constexpr OrdeningByType operator<=>(const i16) const noexcept { return OrdeningByType(); }
		__LL_NODISCARD__ constexpr OrdeningByType operator<=>(const i32) const noexcept { return OrdeningByType(); }
		__LL_NODISCARD__ constexpr OrdeningByType operator<=>(const i64) const noexcept { return OrdeningByType(); }
		__LL_NODISCARD__ constexpr std::partial_ordering operator<=>(const f32) const noexcept { return std::partial_ordering(); }
		__LL_NODISCARD__ constexpr std::partial_ordering operator<=>(const f64) const noexcept { return std::partial_ordering(); }
		__LL_NODISCARD__ constexpr std::partial_ordering operator<=>(const f128) const noexcept { return std::partial_ordering(); }
		__LL_NODISCARD__ constexpr OrdeningByType operator<=>(const ll_bool_t) const noexcept { return OrdeningByType(); }

		#pragma endregion
		#pragma region Operations
		__LL_NODISCARD__ constexpr Big_u8 operator+(const u8 value) const noexcept { return this->primitive + value; }
		__LL_NODISCARD__ constexpr Big_u16 operator+(const u16 value) const noexcept { return this->primitive + value; }
		__LL_NODISCARD__ constexpr Big_u32 operator+(const u32 value) const noexcept { return this->primitive + value; }
		__LL_NODISCARD__ constexpr Big_u64 operator+(const u64 value) const noexcept { return this->primitive + value; }
		__LL_NODISCARD__ constexpr Big_i8 operator+(const i8 value) const noexcept { return this->primitive + value; }
		__LL_NODISCARD__ constexpr Big_i16 operator+(const i16 value) const noexcept { return this->primitive + value; }
		__LL_NODISCARD__ constexpr Big_i32 operator+(const i32 value) const noexcept { return this->primitive + value; }
		__LL_NODISCARD__ constexpr Big_i64 operator+(const i64 value) const noexcept { return this->primitive + value; }
		__LL_NODISCARD__ constexpr Big_f32 operator+(const f32 value) const noexcept { return this->primitive + value; }
		__LL_NODISCARD__ constexpr Big_f64 operator+(const f64 value) const noexcept { return this->primitive + value; }
		__LL_NODISCARD__ constexpr Big_f128 operator+(const f128 value) const noexcept { return this->primitive + value; }
		__LL_NODISCARD__ constexpr Big_bool operator+(const ll_bool_t value) const noexcept { return this->primitive + value; }

		__LL_NODISCARD__ constexpr PrimitiveBase& operator+=(const u8 value) noexcept { this->primitive += value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator+=(const u16 value) noexcept { this->primitive += value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator+=(const u32 value) noexcept { this->primitive += value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator+=(const u64 value) noexcept { this->primitive += value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator+=(const i8 value) noexcept { this->primitive += value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator+=(const i16 value) noexcept { this->primitive += value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator+=(const i32 value) noexcept { this->primitive += value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator+=(const i64 value) noexcept { this->primitive += value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator+=(const f32 value) noexcept { this->primitive += value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator+=(const f64 value) noexcept { this->primitive += value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator+=(const f128 value) noexcept { this->primitive += value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator+=(const ll_bool_t value) noexcept { this->primitive += value; return *this; }

		__LL_NODISCARD__ constexpr Big_u8 operator-(const u8 value) const noexcept { return this->primitive - value; }
		__LL_NODISCARD__ constexpr Big_u16 operator-(const u16 value) const noexcept { return this->primitive - value; }
		__LL_NODISCARD__ constexpr Big_u32 operator-(const u32 value) const noexcept { return this->primitive - value; }
		__LL_NODISCARD__ constexpr Big_u64 operator-(const u64 value) const noexcept { return this->primitive - value; }
		__LL_NODISCARD__ constexpr Big_i8 operator-(const i8 value) const noexcept { return this->primitive - value; }
		__LL_NODISCARD__ constexpr Big_i16 operator-(const i16 value) const noexcept { return this->primitive - value; }
		__LL_NODISCARD__ constexpr Big_i32 operator-(const i32 value) const noexcept { return this->primitive - value; }
		__LL_NODISCARD__ constexpr Big_i64 operator-(const i64 value) const noexcept { return this->primitive - value; }
		__LL_NODISCARD__ constexpr Big_f32 operator-(const f32 value) const noexcept { return this->primitive - value; }
		__LL_NODISCARD__ constexpr Big_f64 operator-(const f64 value) const noexcept { return this->primitive - value; }
		__LL_NODISCARD__ constexpr Big_f128 operator-(const f128 value) const noexcept { return this->primitive - value; }
		__LL_NODISCARD__ constexpr Big_bool operator-(const ll_bool_t value) const noexcept { return this->primitive - value; }

		__LL_NODISCARD__ constexpr PrimitiveBase& operator-=(const u8 value) noexcept { this->primitive -= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator-=(const u16 value) noexcept { this->primitive -= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator-=(const u32 value) noexcept { this->primitive -= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator-=(const u64 value) noexcept { this->primitive -= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator-=(const i8 value) noexcept { this->primitive -= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator-=(const i16 value) noexcept { this->primitive -= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator-=(const i32 value) noexcept { this->primitive -= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator-=(const i64 value) noexcept { this->primitive -= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator-=(const f32 value) noexcept { this->primitive -= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator-=(const f64 value) noexcept { this->primitive -= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator-=(const f128 value) noexcept { this->primitive -= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator-=(const ll_bool_t value) noexcept { this->primitive -= value; return *this; }

		__LL_NODISCARD__ constexpr Big_u8 operator*(const u8 value) const noexcept { return this->primitive * value; }
		__LL_NODISCARD__ constexpr Big_u16 operator*(const u16 value) const noexcept { return this->primitive * value; }
		__LL_NODISCARD__ constexpr Big_u32 operator*(const u32 value) const noexcept { return this->primitive * value; }
		__LL_NODISCARD__ constexpr Big_u64 operator*(const u64 value) const noexcept { return this->primitive * value; }
		__LL_NODISCARD__ constexpr Big_i8 operator*(const i8 value) const noexcept { return this->primitive * value; }
		__LL_NODISCARD__ constexpr Big_i16 operator*(const i16 value) const noexcept { return this->primitive * value; }
		__LL_NODISCARD__ constexpr Big_i32 operator*(const i32 value) const noexcept { return this->primitive * value; }
		__LL_NODISCARD__ constexpr Big_i64 operator*(const i64 value) const noexcept { return this->primitive * value; }
		__LL_NODISCARD__ constexpr Big_f32 operator*(const f32 value) const noexcept { return this->primitive * value; }
		__LL_NODISCARD__ constexpr Big_f64 operator*(const f64 value) const noexcept { return this->primitive * value; }
		__LL_NODISCARD__ constexpr Big_f128 operator*(const f128 value) const noexcept { return this->primitive * value; }
		__LL_NODISCARD__ constexpr Big_bool operator*(const ll_bool_t value) const noexcept { return this->primitive * value; }

		__LL_NODISCARD__ constexpr PrimitiveBase& operator*=(const u8 value) noexcept { this->primitive *= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator*=(const u16 value) noexcept { this->primitive *= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator*=(const u32 value) noexcept { this->primitive *= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator*=(const u64 value) noexcept { this->primitive *= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator*=(const i8 value) noexcept { this->primitive *= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator*=(const i16 value) noexcept { this->primitive *= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator*=(const i32 value) noexcept { this->primitive *= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator*=(const i64 value) noexcept { this->primitive *= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator*=(const f32 value) noexcept { this->primitive *= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator*=(const f64 value) noexcept { this->primitive *= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator*=(const f128 value) noexcept { this->primitive *= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator*=(const ll_bool_t value) noexcept { this->primitive *= value; return *this; }

		__LL_NODISCARD__ constexpr Big_u8 operator/(const u8 value) const noexcept { return this->primitive / value; }
		__LL_NODISCARD__ constexpr Big_u16 operator/(const u16 value) const noexcept { return this->primitive / value; }
		__LL_NODISCARD__ constexpr Big_u32 operator/(const u32 value) const noexcept { return this->primitive / value; }
		__LL_NODISCARD__ constexpr Big_u64 operator/(const u64 value) const noexcept { return this->primitive / value; }
		__LL_NODISCARD__ constexpr Big_i8 operator/(const i8 value) const noexcept { return this->primitive / value; }
		__LL_NODISCARD__ constexpr Big_i16 operator/(const i16 value) const noexcept { return this->primitive / value; }
		__LL_NODISCARD__ constexpr Big_i32 operator/(const i32 value) const noexcept { return this->primitive / value; }
		__LL_NODISCARD__ constexpr Big_i64 operator/(const i64 value) const noexcept { return this->primitive / value; }
		__LL_NODISCARD__ constexpr Big_f32 operator/(const f32 value) const noexcept { return this->primitive / value; }
		__LL_NODISCARD__ constexpr Big_f64 operator/(const f64 value) const noexcept { return this->primitive / value; }
		__LL_NODISCARD__ constexpr Big_f128 operator/(const f128 value) const noexcept { return this->primitive / value; }
		__LL_NODISCARD__ constexpr Big_bool operator/(const ll_bool_t value) const noexcept { return this->primitive / value; }

		__LL_NODISCARD__ constexpr PrimitiveBase& operator/=(const u8 value) noexcept { this->primitive /= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator/=(const u16 value) noexcept { this->primitive /= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator/=(const u32 value) noexcept { this->primitive /= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator/=(const u64 value) noexcept { this->primitive /= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator/=(const i8 value) noexcept { this->primitive /= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator/=(const i16 value) noexcept { this->primitive /= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator/=(const i32 value) noexcept { this->primitive /= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator/=(const i64 value) noexcept { this->primitive /= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator/=(const f32 value) noexcept { this->primitive /= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator/=(const f64 value) noexcept { this->primitive /= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator/=(const f128 value) noexcept { this->primitive /= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator/=(const ll_bool_t value) noexcept { this->primitive /= value; return *this; }

		#pragma endregion
		#pragma region Conversions
		__LL_NODISCARD__ constexpr explicit operator u8() const noexcept { return static_cast<u8>(this->primitive); }
		__LL_NODISCARD__ constexpr explicit operator u16() const noexcept { return static_cast<u16>(this->primitive); }
		__LL_NODISCARD__ constexpr explicit operator u32() const noexcept { return static_cast<u32>(this->primitive); }
		__LL_NODISCARD__ constexpr explicit operator u64() const noexcept { return static_cast<u64>(this->primitive); }
		__LL_NODISCARD__ constexpr explicit operator i8() const noexcept { return static_cast<i8>(this->primitive); }
		__LL_NODISCARD__ constexpr explicit operator i16() const noexcept { return static_cast<i16>(this->primitive); }
		__LL_NODISCARD__ constexpr explicit operator i32() const noexcept { return static_cast<i32>(this->primitive); }
		__LL_NODISCARD__ constexpr explicit operator i64() const noexcept { return static_cast<i64>(this->primitive); }
		__LL_NODISCARD__ constexpr explicit operator f32() const noexcept { return static_cast<f32>(this->primitive); }
		__LL_NODISCARD__ constexpr explicit operator f64() const noexcept { return static_cast<f64>(this->primitive); }
		__LL_NODISCARD__ constexpr explicit operator f128() const noexcept { return static_cast<f128>(this->primitive); }
		__LL_NODISCARD__ constexpr explicit operator ll_bool_t() const noexcept { return static_cast<ll_bool_t>(this->primitive); }

		#pragma endregion

	public:
		constexpr void clear() noexcept { this->primitive = ZERO_VALUE; }
		__LL_NODISCARD__ constexpr T& getPrimitive() noexcept { return this->primitive; }
		__LL_NODISCARD__ constexpr const T& getPrimitive() const noexcept { return this->primitive; }

		#pragma endregion

	#pragma endregion
};

template<class _T>
class PrimitiveFloating : public PrimitiveBase<_T> {
	#pragma region Types
	public:
		// Class related
		using _MyType		= PrimitiveFloating;
		using PrimitiveBase	= PrimitiveBase<_T>;

		// Types and enums
		using T					= _T;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_floating_type_v<T>,
			"Type must be a floating-point type");
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr PrimitiveFloating() noexcept : PrimitiveBase() {}
		constexpr ~PrimitiveFloating() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr PrimitiveFloating(const PrimitiveFloating& other) noexcept
			: PrimitiveBase(std::forward<const PrimitiveBase&>(other)) {}
		constexpr PrimitiveFloating& operator=(const PrimitiveFloating& other) noexcept {
			PrimitiveBase::operator=(std::forward<const PrimitiveBase&>(other));
			return *this;
		}
		constexpr PrimitiveFloating(PrimitiveFloating&& other) noexcept
			: PrimitiveBase(std::forward<const PrimitiveBase&>(other)) {}
		constexpr PrimitiveFloating& operator=(PrimitiveFloating&& other) noexcept {
			return *this;
		}

		constexpr PrimitiveFloating(const T& primitive) noexcept
			: PrimitiveBase(std::forward<const T&>(primitive)) {}
		constexpr PrimitiveFloating& operator=(const T& primitive) noexcept {
			PrimitiveBase::operator=(std::forward<const T&>(primitive));
			return *this;
		}
		constexpr PrimitiveFloating(T&& primitive) noexcept
			: PrimitiveBase(std::forward<T&&>(primitive)) {}
		constexpr PrimitiveFloating& operator=(T&& primitive) noexcept {
			PrimitiveBase::operator=(std::forward<T&&>(primitive));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const PrimitiveFloating*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator PrimitiveFloating*() noexcept { return this; }

		#pragma endregion

	#pragma endregion
};

template<class _T>
class PrimitiveInteger : public PrimitiveBase<_T> {
	#pragma region Types
	public:
		// Class related
		using _MyType		= PrimitiveInteger;
		using PrimitiveBase = PrimitiveBase<_T>;

		// Types and enums
		using T				= _T;

		using Big_u8		= PrimitiveBase::Big_u8;
		using Big_u16		= PrimitiveBase::Big_u16;
		using Big_u32		= PrimitiveBase::Big_u32;
		using Big_u64		= PrimitiveBase::Big_u64;
		using Big_i8		= PrimitiveBase::Big_i8;
		using Big_i16		= PrimitiveBase::Big_i16;
		using Big_i32		= PrimitiveBase::Big_i32;
		using Big_i64		= PrimitiveBase::Big_i64;
		using Big_f32		= PrimitiveBase::Big_f32;
		using Big_f64		= PrimitiveBase::Big_f64;
		using Big_f128		= PrimitiveBase::Big_f128;
		using Big_bool		= PrimitiveBase::Big_bool;

		using Small_u8		= traits::type_smaller_of_two<T, u8>;
		using Small_u16		= traits::type_smaller_of_two<T, u16>;
		using Small_u32		= traits::type_smaller_of_two<T, u32>;
		using Small_u64		= traits::type_smaller_of_two<T, u64>;
		using Small_i8		= traits::type_smaller_of_two<T, i8>;
		using Small_i16		= traits::type_smaller_of_two<T, i16>;
		using Small_i32		= traits::type_smaller_of_two<T, i32>;
		using Small_i64		= traits::type_smaller_of_two<T, i64>;
		using Small_f32		= traits::type_smaller_of_two<T, f32>;
		using Small_f64		= traits::type_smaller_of_two<T, f64>;
		using Small_f128	= traits::type_smaller_of_two<T, f128>;
		using Small_bool	= traits::type_smaller_of_two<T, ll_bool_t>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(std::is_integral_v<T>,
			"Type must be a integral type");
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr PrimitiveInteger() noexcept : PrimitiveBase() {}
		constexpr ~PrimitiveInteger() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr PrimitiveInteger(const PrimitiveInteger& other) noexcept
			: PrimitiveBase(std::forward<const PrimitiveBase&>(other)) {}
		constexpr PrimitiveInteger& operator=(const PrimitiveInteger& other) noexcept {
			PrimitiveBase::operator=(std::forward<const PrimitiveBase&>(other));
			return *this;
		}
		constexpr PrimitiveInteger(PrimitiveInteger&& other) noexcept
			: PrimitiveBase(std::forward<const PrimitiveBase&>(other)) {}
		constexpr PrimitiveInteger& operator=(PrimitiveInteger&& other) noexcept {
			return *this;
		}

		constexpr PrimitiveInteger(const T& primitive) noexcept
			: PrimitiveBase(std::forward<const T&>(primitive)) {}
		constexpr PrimitiveInteger& operator=(const T& primitive) noexcept {
			PrimitiveBase::operator=(std::forward<const T&>(primitive));
			return *this;
		}
		constexpr PrimitiveInteger(T&& primitive) noexcept
			: PrimitiveBase(std::forward<T&&>(primitive)) {}
		constexpr PrimitiveInteger& operator=(T&& primitive) noexcept {
			PrimitiveBase::operator=(std::forward<T&&>(primitive));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const PrimitiveInteger*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator PrimitiveInteger*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr Small_u8 operator%(const u8 value) const noexcept { return this->primitive % value; }
		__LL_NODISCARD__ constexpr Small_u16 operator%(const u16 value) const noexcept { return this->primitive % value; }
		__LL_NODISCARD__ constexpr Small_u32 operator%(const u32 value) const noexcept { return this->primitive % value; }
		__LL_NODISCARD__ constexpr Small_u64 operator%(const u64 value) const noexcept { return this->primitive % value; }
		__LL_NODISCARD__ constexpr Small_i8 operator%(const i8 value) const noexcept { return this->primitive % value; }
		__LL_NODISCARD__ constexpr Small_i16 operator%(const i16 value) const noexcept { return this->primitive % value; }
		__LL_NODISCARD__ constexpr Small_i32 operator%(const i32 value) const noexcept { return this->primitive % value; }
		__LL_NODISCARD__ constexpr Small_i64 operator%(const i64 value) const noexcept { return this->primitive % value; }
		__LL_NODISCARD__ constexpr Small_bool operator%(const ll_bool_t value) const noexcept { return this->primitive % value; }

		__LL_NODISCARD__ constexpr PrimitiveBase& operator%=(const u8 value) noexcept { this->primitive %= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator%=(const u16 value) noexcept { this->primitive %= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator%=(const u32 value) noexcept { this->primitive %= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator%=(const u64 value) noexcept { this->primitive %= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator%=(const i8 value) noexcept { this->primitive %= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator%=(const i16 value) noexcept { this->primitive %= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator%=(const i32 value) noexcept { this->primitive %= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator%=(const i64 value) noexcept { this->primitive %= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator%=(const ll_bool_t value) noexcept { this->primitive %= value; return *this; }

		__LL_NODISCARD__ constexpr Small_u8 operator&(const u8 value) const noexcept { return this->primitive & value; }
		__LL_NODISCARD__ constexpr Small_u16 operator&(const u16 value) const noexcept { return this->primitive & value; }
		__LL_NODISCARD__ constexpr Small_u32 operator&(const u32 value) const noexcept { return this->primitive & value; }
		__LL_NODISCARD__ constexpr Small_u64 operator&(const u64 value) const noexcept { return this->primitive & value; }
		__LL_NODISCARD__ constexpr Small_i8 operator&(const i8 value) const noexcept { return this->primitive & value; }
		__LL_NODISCARD__ constexpr Small_i16 operator&(const i16 value) const noexcept { return this->primitive & value; }
		__LL_NODISCARD__ constexpr Small_i32 operator&(const i32 value) const noexcept { return this->primitive & value; }
		__LL_NODISCARD__ constexpr Small_i64 operator&(const i64 value) const noexcept { return this->primitive & value; }
		__LL_NODISCARD__ constexpr Small_bool operator&(const ll_bool_t value) const noexcept { return this->primitive & value; }

		__LL_NODISCARD__ constexpr PrimitiveBase& operator&=(const u8 value) noexcept { this->primitive &= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator&=(const u16 value) noexcept { this->primitive &= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator&=(const u32 value) noexcept { this->primitive &= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator&=(const u64 value) noexcept { this->primitive &= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator&=(const i8 value) noexcept { this->primitive &= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator&=(const i16 value) noexcept { this->primitive &= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator&=(const i32 value) noexcept { this->primitive &= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator&=(const i64 value) noexcept { this->primitive &= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator&=(const ll_bool_t value) noexcept { this->primitive &= value; return *this; }

		__LL_NODISCARD__ constexpr Small_u8 operator|(const u8 value) const noexcept { return this->primitive | value; }
		__LL_NODISCARD__ constexpr Small_u16 operator|(const u16 value) const noexcept { return this->primitive | value; }
		__LL_NODISCARD__ constexpr Small_u32 operator|(const u32 value) const noexcept { return this->primitive | value; }
		__LL_NODISCARD__ constexpr Small_u64 operator|(const u64 value) const noexcept { return this->primitive | value; }
		__LL_NODISCARD__ constexpr Small_i8 operator|(const i8 value) const noexcept { return this->primitive | value; }
		__LL_NODISCARD__ constexpr Small_i16 operator|(const i16 value) const noexcept { return this->primitive | value; }
		__LL_NODISCARD__ constexpr Small_i32 operator|(const i32 value) const noexcept { return this->primitive | value; }
		__LL_NODISCARD__ constexpr Small_i64 operator|(const i64 value) const noexcept { return this->primitive | value; }
		__LL_NODISCARD__ constexpr Small_bool operator|(const ll_bool_t value) const noexcept { return this->primitive | value; }

		__LL_NODISCARD__ constexpr PrimitiveBase& operator|=(const u8 value) noexcept { this->primitive |= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator|=(const u16 value) noexcept { this->primitive |= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator|=(const u32 value) noexcept { this->primitive |= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator|=(const u64 value) noexcept { this->primitive |= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator|=(const i8 value) noexcept { this->primitive |= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator|=(const i16 value) noexcept { this->primitive |= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator|=(const i32 value) noexcept { this->primitive |= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator|=(const i64 value) noexcept { this->primitive |= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator|=(const ll_bool_t value) noexcept { this->primitive |= value; return *this; }

		__LL_NODISCARD__ constexpr Small_u8 operator^(const u8 value) const noexcept { return this->primitive ^ value; }
		__LL_NODISCARD__ constexpr Small_u16 operator^(const u16 value) const noexcept { return this->primitive ^ value; }
		__LL_NODISCARD__ constexpr Small_u32 operator^(const u32 value) const noexcept { return this->primitive ^ value; }
		__LL_NODISCARD__ constexpr Small_u64 operator^(const u64 value) const noexcept { return this->primitive ^ value; }
		__LL_NODISCARD__ constexpr Small_i8 operator^(const i8 value) const noexcept { return this->primitive ^ value; }
		__LL_NODISCARD__ constexpr Small_i16 operator^(const i16 value) const noexcept { return this->primitive ^ value; }
		__LL_NODISCARD__ constexpr Small_i32 operator^(const i32 value) const noexcept { return this->primitive ^ value; }
		__LL_NODISCARD__ constexpr Small_i64 operator^(const i64 value) const noexcept { return this->primitive ^ value; }
		__LL_NODISCARD__ constexpr Small_bool operator^(const ll_bool_t value) const noexcept { return this->primitive ^ value; }

		__LL_NODISCARD__ constexpr PrimitiveBase& operator^=(const u8 value) noexcept { this->primitive ^= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator^=(const u16 value) noexcept { this->primitive ^= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator^=(const u32 value) noexcept { this->primitive ^= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator^=(const u64 value) noexcept { this->primitive ^= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator^=(const i8 value) noexcept { this->primitive ^= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator^=(const i16 value) noexcept { this->primitive ^= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator^=(const i32 value) noexcept { this->primitive ^= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator^=(const i64 value) noexcept { this->primitive ^= value; return *this; }
		__LL_NODISCARD__ constexpr PrimitiveBase& operator^=(const ll_bool_t value) noexcept { this->primitive ^= value; return *this; }

		#pragma endregion

	#pragma endregion
};


template<class T>
using PrimitiveWrapperSelection = traits::conditional_t<
	traits::is_floating_type_v<T>,
	traits::PrimitiveFloating<T>,
	traits::PrimitiveInteger<T>
>;

template<class T>
using PrimitiveWrapper = traits::conditional_t<std::is_class_v<T>, T, traits::PrimitiveWrapperSelection<T>>;

} // namespace traits
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TRAITSPRIMITIVETYPES_HPP_
