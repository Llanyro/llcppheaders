//////////////////////////////////////////////
//	AllocatorDummy.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ALLOCATORDUMMY_HPP_) // Guard && version protector
	#if LLANYLIB_ALLOCATORDUMMY_MAYOR_ != 8 || LLANYLIB_ALLOCATORDUMMY_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "AllocatorDummy.hpp version error!"
		#else
			#error "AllocatorDummy.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ALLOCATORDUMMY_MAYOR_ || LLANYLIB_ALLOCATORDUMMY_MINOR_

#else !defined(LLANYLIB_ALLOCATORDUMMY_HPP_)
#define LLANYLIB_ALLOCATORDUMMY_HPP_
#define LLANYLIB_ALLOCATORDUMMY_MAYOR_ 8
#define LLANYLIB_ALLOCATORDUMMY_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace meta {

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4100) // Unreferenced formal parameter
#endif // WINDOWS_SYSTEM

struct AllocatorDummy {
	AllocatorDummy() noexcept {}
	~AllocatorDummy() noexcept {}

	AllocatorDummy(const AllocatorDummy&) noexcept {}
	AllocatorDummy& operator=(const AllocatorDummy&) noexcept { return *this; }
	AllocatorDummy(AllocatorDummy&&) noexcept {}
	AllocatorDummy& operator=(AllocatorDummy&&) noexcept { return *this; }

	__LL_NODISCARD__ operator const AllocatorDummy*() const noexcept { return this; }
	__LL_NODISCARD__ operator AllocatorDummy*() noexcept { return this; }

	__LL_NODISCARD__ void* allocate(const len_t bytes) noexcept { return LL_NULLPTR; }
	__LL_NODISCARD__ void deallocate(void*& mem) noexcept { mem = LL_NULLPTR; }
	__LL_NODISCARD__ ll_bool_t reallocate(void*& mem, const len_t bytes) noexcept {
		mem = LL_NULLPTR;
		return LL_FALSE;
	}
	__LL_NODISCARD__ void memcopy(const void* src, void* dst, const len_t bytes) noexcept {}
	__LL_NODISCARD__ void memmove(void* src, void* dst, const len_t bytes) noexcept {}
};

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

template<class Allocator = AllocatorDummy>
class AllocatorChecker : public Allocator {
	public:
		static_assert(!std::is_reference_v<Allocator>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<Allocator>, "Const type is forbidden!");
		static_assert(!std::is_pointer_v<Allocator>, "Pointer type is forbidden!");
		static_assert(!std::is_array_v<Allocator>, "Array type is forbidden!");
		static_assert(std::is_class_v<Allocator>, "Allocator needs to be a class!");

		static_assert(std::is_nothrow_constructible_v<Allocator>, "Allocator needs a noexcept constructor!");
		static_assert(std::is_nothrow_destructible_v<Allocator>, "Allocator needs a noexcept destructor!");
		static_assert(std::is_copy_constructible_v<Allocator>, "Allocator needs a noexcept copy constructor!");
		static_assert(std::is_copy_assignable_v<Allocator>, "Allocator needs a noexcept copy asignable!");
		static_assert(std::is_move_constructible_v<Allocator>, "Allocator needs a noexcept move constructor!");
		static_assert(std::is_move_assignable_v<Allocator>, "Allocator needs a noexcept move asignable!");

	#pragma region AllocationFunctions
		using AllocateFunc = void* (Allocator::*)(const len_t) noexcept;
		using DeallocateFunc = void(Allocator::*)(void*&) noexcept;
		using ReallocateFunc = ll_bool_t(Allocator::*)(void*&, const len_t) noexcept;
		using MemCopyFunc = void(Allocator::*)(const void*, void*, const len_t) noexcept;
		using MemMoveFunc = void(Allocator::*)(void*, void*, const len_t) noexcept;

		static_assert(std::is_same_v<AllocateFunc, decltype(&Allocator::allocate)>,
			"Allocator::allocate needs to be the same type as AllocateFunc!");
		static_assert(
			std::is_same_v<DeallocateFunc, decltype(&Allocator::deallocate)>,
			"Allocator::deallocate needs to be the same type as DeallocateFunc!");
		static_assert(
			std::is_same_v<ReallocateFunc, decltype(&Allocator::reallocate)>,
			"Allocator::reallocate needs to be the same type as ReallocateFunc!");
		static_assert(
			std::is_same_v<MemCopyFunc, decltype(&Allocator::memcopy)>,
			"Allocator::memcopy needs to be the same type as MemCopyFunc!");
		static_assert(
			std::is_same_v<MemMoveFunc, decltype(&Allocator::memmove)>,
			"Allocator::memmove needs to be the same type as MemMoveFunc!");

	#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ALLOCATORDUMMY_HPP_
