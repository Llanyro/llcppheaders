//////////////////////////////////////////////
//	pair.hpp				                //
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 10.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_PAIR_HPP_) // Guard && version protector
	#if LLANYLIB_PAIR_MAYOR_ != 10 || LLANYLIB_PAIR_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "traits_primitive_types.hpp version error!"
		#else
			#error "traits_primitive_types.hpp version error!"
		#endif // __LL_REAL_CXX23
	#endif // LLANYLIB_PAIR_MAYOR_ || LLANYLIB_PAIR_MINOR_

#else !defined(LLANYLIB_PAIR_HPP_)
#define LLANYLIB_PAIR_HPP_
#define LLANYLIB_PAIR_MAYOR_ 10
#define LLANYLIB_PAIR_MINOR_ 0

#include "../traits/traits_comparations.hpp"

namespace llcpp {
namespace meta {

template <class _T, class _U, class _ExtraFunctions>
class pair : public llcpp::meta::Cluster, public _ExtraFunctions {
	#pragma region Types
	public:
		// Class related
		using _MyType           = pair;
		using ExtraFunctions    = _ExtraFunctions;

		// Types and enums
		using T                 = _T;
		using U                 = _U;

		using cinput_t			= traits::cinput<T>;
		using cinput_u			= traits::cinput<U>;
		using is_comparable_t	= traits::is_comparable<T>;
		using is_comparable_u	= traits::is_comparable<U>;

		// Signatures
		using ClearSignature	= void(ExtraFunctions::*)(T&, U&) const noexcept;
		using T_EQSignature		= ll_bool_t(ExtraFunctions::*)(T&, T&) const noexcept;
		using U_EQSignature		= ll_bool_t(ExtraFunctions::*)(U&, U&) const noexcept;

	#pragma endregion
	#pragma region Expreions
	public:
		static constexpr ll_bool_t HAS_EQ_T = traits::common::has_operator_eq_function_v<T, T_EQSignature>;
		static constexpr ll_bool_t HAS_NEQ_T = traits::common::has_operator_no_eq_function_v<T, T_EQSignature>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_ignore_pa_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(traits::is_valid_type_checker_ignore_pa_v<U>,
			"type_checker<U> detected an invalid type!");

		static_assert(traits::is_valid_constructor_checker_v<ExtraFunctions>,
			"constructor_checker<U> detected an invalid type!");
		static_assert(std::is_class_v<T>,
			"T is not a class!");

		static_assert(traits::common::has_clear_function_v<ExtraFunctions, ClearSignature>,
			"'ExtraFunctions::clear() const noexcept' is required!");

	#pragma endregion
	#pragma region Attributes
	protected:
		T t_val;
		U u_val;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr pair() noexcept : t_val(), u_val() {}
		constexpr ~pair() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr pair(const pair& other) noexcept
			: t_val(std::forward<const T&>(other.t_val))
			, u_val(std::forward<const U&>(other.u_val))
		{}
		constexpr pair& operator=(const pair& other) noexcept {
			this->t_val = std::forward<const T&>(other.t_val);
			this->u_val = std::forward<const U&>(other.u_val);
			return *this;
		}
		constexpr pair(pair&& other) noexcept
			: t_val(std::forward<T&&>(other.t_val))
			, u_val(std::forward<U&&>(other.u_val))
		{ other.ExtraFunctions::clear(other.t_val, other.u_val) }
		constexpr pair& operator=(pair&& other) noexcept {
			this->t_val = std::forward<T&&>(other.t_val);
			this->u_val = std::forward<U&&>(other.u_val);
			other.ExtraFunctions::clear(other.t_val, other.u_val)
			return *this;
		}
		constexpr pair(const volatile pair&) = delete;
		constexpr pair& operator=(const volatile pair&) = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const pair*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator pair*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr T& first() noexcept { return this->t_val; }
		__LL_NODISCARD__ constexpr U& second() noexcept { return this->u_val; }
		__LL_NODISCARD__ constexpr const T& first() const noexcept { return this->t_val; }
		__LL_NODISCARD__ constexpr const U& second() const noexcept { return this->u_val; }

		template<class W> __LL_NODISCARD__ constexpr W& getValue() noexcept {
			static_assert(std::is_same_v<W, T> || std::is_same_v<W, U>,
				"This type is not valid!");
			return W();
		}
		template<> __LL_NODISCARD__ constexpr T& getValue<T>() noexcept { return this->t_val; }
		template<> __LL_NODISCARD__ constexpr U& getValue<U>() noexcept { return this->u_val; }

		template<class W> __LL_NODISCARD__ constexpr const W& getValue() const noexcept {
			static_assert(std::is_same_v<W, T> || std::is_same_v<W, U>,
				"This type is not valid!");
			return W();
		}
		template<> __LL_NODISCARD__ constexpr const T& getValue<T>() const noexcept { return this->t_val; }
		template<> __LL_NODISCARD__ constexpr const U& getValue<U>() const noexcept { return this->u_val; }

		__LL_NODISCARD__ constexpr ll_bool_t swap(pair& other) noexcept {
			if (this == std::addressof(other)) return llcpp::FALSE;
			std::swap(this->first, other.first);
			std::swap(this->second, other.second);
			return llcpp::TRUE;
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const pair& other) const noexcept {
			if constexpr (HAS_EQ_T) {

			}
			else if constexpr (is_comparable_t::IS_COMPARABLE_EQ)
				return is_comparable_t
			else {
				static_assert(HAS_EQ_T || is_comparable_t::IS_COMPARABLE_EQ,
					"");
			}
		}



		#pragma endregion
	#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_PAIR_HPP_
