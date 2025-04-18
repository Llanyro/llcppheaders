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
		#if defined(__LL_REAL_CXX23)
			#warning "HashFunctions.hpp(incomplete) version error!"
		#else
			#error "HashFunctions.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_HASHFUNCTIONS_INCOMPLETE_MAYOR_ || LLANYLIB_HASHFUNCTIONS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_HASHFUNCTIONS_INCOMPLETE_HPP_)
	#define LLANYLIB_HASHFUNCTIONS_INCOMPLETE_HPP_
	#define LLANYLIB_HASHFUNCTIONS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_HASHFUNCTIONS_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_HASHFUNCTIONS_HPP_)
	#if LLANYLIB_HASHFUNCTIONS_MAYOR_ != 12 || LLANYLIB_HASHFUNCTIONS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "HashFunctions.hpp version error!"
		#else
			#error "HashFunctions.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_HASHFUNCTIONS_MAYOR_ || LLANYLIB_HASHFUNCTIONS_MINOR_

#else
	#define LLANYLIB_HASHFUNCTIONS_HPP_
	#define LLANYLIB_HASHFUNCTIONS_MAYOR_ 12
	#define LLANYLIB_HASHFUNCTIONS_MINOR_ 0

#include "../bits.hpp"

namespace llcpp {
namespace meta {
namespace utils {
namespace hash {

template<class _HashAlgorithm>
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
		constexpr HashFunctions(Args&&... args) noexcept
			: ValidTag()
			, ExtraFunctions(::std::forward<Args>(args)...)
		{}
		constexpr ~HashFunctions() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr HashFunctions(const HashFunctions& other) noexcept
			: ValidTag()
			, ExtraFunctions(::std::forward<const ExtraFunctions&>(other))
		{}
		constexpr HashFunctions& operator=(const HashFunctions& other) noexcept {
			ExtraFunctions::operator=(::std::forward<const ExtraFunctions&>(other));
			return *this;
		}
		constexpr HashFunctions(HashFunctions&& other) noexcept
			: ValidTag()
			, ExtraFunctions(::std::forward<ExtraFunctions&&>(other))
		{}
		constexpr HashFunctions& operator=(HashFunctions&& other) noexcept {
			ExtraFunctions::operator=(::std::forward<ExtraFunctions&&>(other));
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
