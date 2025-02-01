//////////////////////////////////////////////
//	Container.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_CONTAINER_INCOMPLETE_HPP_)
	#if LLANYLIB_CONTAINER_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_CONTAINER_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Container.hpp(incomplete) version error!"
		#else
			#error "Container.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONTAINER_INCOMPLETE_MAYOR_ || LLANYLIB_CONTAINER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_CONTAINER_INCOMPLETE_HPP_)
	#define LLANYLIB_CONTAINER_INCOMPLETE_HPP_
	#define LLANYLIB_CONTAINER_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_CONTAINER_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_CONTAINER_HPP_)
	#if LLANYLIB_CONTAINER_MAYOR_ != 11 || LLANYLIB_CONTAINER_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Container.hpp version error!"
		#else
			#error "Container.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_CONTAINER_MAYOR_ || LLANYLIB_CONTAINER_MINOR_

#else
	#define LLANYLIB_CONTAINER_HPP_
	#define LLANYLIB_CONTAINER_MAYOR_ 11
	#define LLANYLIB_CONTAINER_MINOR_ 0

#include "../traits_base/type_traits.hpp"

namespace llcpp {
namespace meta {
namespace utils {

template<class _T>
class Container {
	#pragma region Types
	public:
		// Class related
		using _MyType = Container;		// This class with template

		// Types and enums
		using T = _T;

	#pragma endregion
	#pragma region Attributes
	private:
		T obj;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr Container() noexcept
			: obj()
		{}
		template<class... Args>
		constexpr Container(Args&&... args) noexcept
			: obj(::std::forward<Args>(args)...)
		{}
		constexpr ~Container() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Container(const Container& other) noexcept
			: obj(::std::forward<const T&>(other.obj))
		{}
		constexpr Container& operator=(const Container& other) noexcept {
			this->obj == ::std::forward<const T&>(other);
			return *this;
		}
		constexpr Container(Container&& other) noexcept
			: obj(::std::forward<T&&>(other))
		{}
		constexpr Container& operator=(Container&& other) noexcept {
			this->obj = ::std::forward<T&&>(other);
			return *this;
		}
		constexpr Container(const volatile Container&) = delete;
		constexpr Container& operator=(const volatile Container&) = delete;
		constexpr Container(volatile Container&&) = delete;
		constexpr Container& operator=(volatile Container&&) = delete;

		constexpr Container(const T& obj) noexcept
			: obj(::std::forward<const T&>(obj))
		{}
		constexpr Container& operator=(const T& obj) noexcept {
			this->obj == ::std::forward<const T&>(obj);
			return *this;
		}
		constexpr Container(T&& obj) noexcept
			: obj(::std::forward<T&&>(obj))
		{}
		constexpr Container& operator=(T&& obj) noexcept {
			this->obj = ::std::forward<T&&>(obj);
			return *this;
		}
		constexpr Container(const volatile T&) = delete;
		constexpr Container& operator=(const volatile T&) = delete;
		constexpr Container(volatile T&&) = delete;
		constexpr Container& operator=(volatile T&&) = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Container*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Container*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:


		#pragma endregion

	#pragma endregion
};

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CONTAINER_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_CONTAINER_EXTRA_HPP_)
		#if LLANYLIB_CONTAINER_EXTRA_MAYOR_ != 11 || LLANYLIB_CONTAINER_EXTRA_MINOR_ < 0
			#if defined(__LL_REAL_CXX23)
				#warning "Container.hpp(extra) version error!"
			#else
				#error "Container.hpp(extra) version error!"
			#endif // __LL_REAL_CXX23
		#endif // LLANYLIB_CONTAINER_EXTRA_MAYOR_ || LLANYLIB_CONTAINER_EXTRA_MINOR_

	#else
		#define LLANYLIB_CONTAINER_EXTRA_HPP_
		#define LLANYLIB_CONTAINER_EXTRA_MAYOR_ 11
		#define LLANYLIB_CONTAINER_EXTRA_MINOR_ 0

	#endif // LLANYLIB_CONTAINER_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
