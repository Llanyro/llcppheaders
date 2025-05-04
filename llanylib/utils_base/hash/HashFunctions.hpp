//////////////////////////////////////////////
//	HashFunctions.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_HASHFUNCTIONS_INCOMPLETE_HPP_)
	#if LLANYLIB_HASHFUNCTIONS_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_HASHFUNCTIONS_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "HashFunctions.hpp(incomplete) version error!"
		#else
			#error "HashFunctions.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_HASHFUNCTIONS_INCOMPLETE_MAYOR_ || LLANYLIB_HASHFUNCTIONS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_HASHFUNCTIONS_INCOMPLETE_HPP_)
	#define LLANYLIB_HASHFUNCTIONS_INCOMPLETE_HPP_
	#define LLANYLIB_HASHFUNCTIONS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_HASHFUNCTIONS_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_HASHFUNCTIONS_HPP_)
	#if LLANYLIB_HASHFUNCTIONS_MAYOR_ != 12 || LLANYLIB_HASHFUNCTIONS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "HashFunctions.hpp version error!"
		#else
			#error "HashFunctions.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_HASHFUNCTIONS_MAYOR_ || LLANYLIB_HASHFUNCTIONS_MINOR_

#else
	#define LLANYLIB_HASHFUNCTIONS_HPP_
	#define LLANYLIB_HASHFUNCTIONS_MAYOR_ 12
	#define LLANYLIB_HASHFUNCTIONS_MINOR_ 0

#include "../bits.hpp"
#include "../../traits_base/checker.hpp"

namespace llcpp {
namespace meta {
namespace utils {
namespace hash {

template<class _HashAlgorithm>
	requires ::llcpp::meta::traits::is_valid_constructor_checker_v<_HashAlgorithm>
class HashFunctions : _HashAlgorithm {
	#pragma region Types
	public:
		// Class related
		using _MyType			= HashFunctions;
		using HashAlgorithm		= _HashAlgorithm;

		// Types and enums

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr HashFunctions() noexcept = default;
		template<class... Args>
		constexpr HashFunctions(Args&&... args) noexcept requires(::std::is_nothrow_constructible_v<HashAlgorithm, Args...>)
			: ValidTag()
			, HashAlgorithm(::std::forward<Args>(args)...)
		{}
		constexpr ~HashFunctions() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr HashFunctions(const HashFunctions& other) noexcept
			: ValidTag()
			, HashAlgorithm(::std::forward<const HashAlgorithm&>(other))
		{}
		constexpr HashFunctions& operator=(const HashFunctions& other) noexcept {
			HashAlgorithm::operator=(::std::forward<const HashAlgorithm&>(other));
			return *this;
		}
		constexpr HashFunctions(HashFunctions&& other) noexcept
			: ValidTag()
			, HashAlgorithm(::std::forward<HashAlgorithm&&>(other))
		{}
		constexpr HashFunctions& operator=(HashFunctions&& other) noexcept {
			HashAlgorithm::operator=(::std::forward<HashAlgorithm&&>(other));
			return *this;
		}

		constexpr HashFunctions(const volatile HashFunctions&) noexcept = delete;
		constexpr HashFunctions& operator=(const volatile HashFunctions&) noexcept = delete;
		constexpr HashFunctions(volatile HashFunctions&&) noexcept = delete;
		constexpr HashFunctions& operator=(volatile HashFunctions&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const HashFunctions*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator HashFunctions*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:


		#pragma endregion

	#pragma endregion
};

} // namespace hash
} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_HASHFUNCTIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
