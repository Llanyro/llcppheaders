//////////////////////////////////////////////
//	SimplestContainer.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_SIMPLESTCONTAINER_HPP_) // Guard && version protector
	#if LLANYLIB_SIMPLESTCONTAINER_MAYOR_ != 9 || LLANYLIB_SIMPLESTCONTAINER_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "SimplestContainer.hpp version error!"
		#else
			#error "SimplestContainer.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_SIMPLESTCONTAINER_MAYOR_ || LLANYLIB_SIMPLESTCONTAINER_MINOR_

#else !defined(LLANYLIB_SIMPLESTCONTAINER_HPP_)
#define LLANYLIB_SIMPLESTCONTAINER_HPP_
#define LLANYLIB_SIMPLESTCONTAINER_MAYOR_ 9
#define LLANYLIB_SIMPLESTCONTAINER_MINOR_ 0

#include "types_base.hpp"

namespace llcpp {
namespace meta {

// Similar to std::pair
// But only recomended for primitive types
// Does not use move contructor, so if you want to user no primitive types
//	you have to move them by yourself
template<class _T, class _U = _T>
struct simplest_container {
	#pragma region Types
	public:
		// Class related
		using _MyType	= simplest_container;

		// Types and enums
		using T			= _T;
		using U			= _U;

	#pragma endregion
	#pragma region Attributes
	public:
		T first;
		U second;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr simplest_container() noexcept = delete;
		constexpr simplest_container(const T first, const U second) noexcept
			: first(first), second(second) {}
		constexpr ~simplest_container() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr simplest_container(const simplest_container& other) noexcept = default;
		constexpr simplest_container& operator=(const simplest_container& other) noexcept = default;
		constexpr simplest_container(simplest_container&& other) noexcept = default;
		constexpr simplest_container& operator=(simplest_container&& other) noexcept = default;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const simplest_container*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator simplest_container*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const simplest_container& other) const noexcept {
			return this->first == other.first && this->second == other.second;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const simplest_container& other) const noexcept {
			return this->first != other.first || this->second != other.second;
		}

		#pragma endregion

	#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_SIMPLESTCONTAINER_HPP_
