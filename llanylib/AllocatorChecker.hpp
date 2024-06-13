//////////////////////////////////////////////
//	AllocatorChecker.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ALLOCATORCHECKER_HPP_) // Guard && version protector
	#if LLANYLIB_ALLOCATORCHECKER_MAYOR_ != 8 || LLANYLIB_ALLOCATORCHECKER_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "AllocatorChecker.hpp version error!"
		#else
			#error "AllocatorChecker.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ALLOCATORCHECKER_MAYOR_ || LLANYLIB_ALLOCATORCHECKER_MINOR_

#else !defined(LLANYLIB_ALLOCATORCHECKER_HPP_)
#define LLANYLIB_ALLOCATORCHECKER_HPP_
#define LLANYLIB_ALLOCATORCHECKER_MAYOR_ 8
#define LLANYLIB_ALLOCATORCHECKER_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace meta {

namespace __internal__ {

template<class T>
constexpr void destruct_vector(T* begin, const T* end) noexcept(std::is_nothrow_destructible_v<T>) {
	__LL_ASSERT_VAR_NULL__(begin, "begin");
	__LL_ASSERT_VAR_NULL__(end, "end");
	__LL_ASSERT_B_LOWER_THAN_A__(begin, end, "begin", "end");

	for (; begin < end; ++begin) begin->~T();
}
template<class T>
constexpr void destruct_vector(T* begin, const len_t size) noexcept(std::is_nothrow_destructible_v<T>) {
	destruct_vector<T>(begin, begin + size);
}
template<class T>
__LL_NODISCARD__ constexpr ll_bool_t destruct_vector_s(T* begin, const T* end) noexcept(std::is_nothrow_destructible_v<T>) {
	if (!begin || !end || end <= begin) return LL_FALSE;
	for (; begin < end; ++begin) begin->~T();
	return LL_TRUE;
}
template<class T>
__LL_NODISCARD__ constexpr ll_bool_t destruct_vector_s(T* begin, const len_t size) noexcept(std::is_nothrow_destructible_v<T>) {
	return destruct_vector_s<T>(begin, begin + size);
}

template<class T, class... Args>
constexpr void construct_vector(T* begin, const T* end, const Args&... args) noexcept(std::is_nothrow_destructible_v<T>) {
	__LL_ASSERT_VAR_NULL__(begin, "begin");
	__LL_ASSERT_VAR_NULL__(end, "end");
	__LL_ASSERT_B_LOWER_THAN_A__(begin, end, "begin", "end");

	for (; begin < end; ++begin) new (begin) T(std::forward<const Args>(args)...);
}
template<class T, class... Args>
constexpr void construct_vector(T* begin, const len_t size, const Args&... args) noexcept(std::is_nothrow_destructible_v<T>) {
	construct_vector<T>(begin, begin + size, std::forward<const Args>(args)...);
}
template<class T, class... Args>
__LL_NODISCARD__ constexpr ll_bool_t construct_vector_s(T* begin, const T* end, const Args&... args) noexcept(std::is_nothrow_destructible_v<T>) {
	if (!begin || !end || end <= begin) return LL_FALSE;
	for (; begin < end; ++begin) new (begin) T(std::forward<const Args>(args)...);
	return LL_TRUE;
}
template<class T, class... Args>
__LL_NODISCARD__ constexpr ll_bool_t construct_vector_s(T* begin, const len_t size, const Args&... args) noexcept(std::is_nothrow_destructible_v<T>) {
	return construct_vector_s<T>(begin, begin + size, std::forward<const Args>(args)...);
}

} // __internal__


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

	public:
		AllocatorChecker() noexcept : Allocator() {}
		~AllocatorChecker() noexcept {}

		AllocatorChecker(const AllocatorChecker& other) noexcept : Allocator(other) {}
		AllocatorChecker& operator=(const AllocatorChecker& other) noexcept {
			Allocator::operator=(other);
			return *this;
		}
		AllocatorChecker(AllocatorChecker&& other) noexcept : Allocator(std::move(other)) {}
		AllocatorChecker& operator=(AllocatorChecker&& other) noexcept {
			Allocator::operator=(std::move(other));
			return *this;
		}

		__LL_NODISCARD__ operator const AllocatorChecker*() const noexcept { return *this; }
		__LL_NODISCARD__ operator AllocatorChecker*() noexcept { return *this; }
};

template<class T, class Allocator = AllocatorDummy>
class AllocatorCheckerTyped : public AllocatorChecker<Allocator> {
	public:
		static_assert(!std::is_array_v<T>, "This class does not support array type");

		static_assert(std::is_nothrow_constructible_v<T>, "Type needs a noexcept constructor!");
		static_assert(std::is_nothrow_destructible_v<T>, "Type needs a noexcept destructor!");
		static_assert(std::is_copy_constructible_v<T>, "Type needs a noexcept copy constructor!");
		static_assert(std::is_copy_assignable_v<T>, "Type needs a noexcept copy asignable!");
		static_assert(std::is_move_constructible_v<T>, "Type needs a noexcept move constructor!");
		static_assert(std::is_move_assignable_v<T>, "Type needs a noexcept move asignable!");

		using AllocatorCheckerBase = meta::AllocatorChecker<Allocator>;
	public:
		AllocatorCheckerTyped() noexcept : AllocatorCheckerBase() {}
		~AllocatorCheckerTyped() noexcept {}

		AllocatorCheckerTyped(const AllocatorCheckerTyped& other) noexcept : AllocatorCheckerBase(other) {}
		AllocatorCheckerTyped& operator=(const AllocatorCheckerTyped& other) noexcept {
			AllocatorCheckerBase::operator=(other);
			return *this;
		}
		AllocatorCheckerTyped(AllocatorCheckerTyped&& other) noexcept : AllocatorCheckerBase(std::move(other)) {}
		AllocatorCheckerTyped& operator=(AllocatorCheckerTyped&& other) noexcept {
			AllocatorCheckerBase::operator=(std::move(other));
			return *this;
		}

		__LL_NODISCARD__ operator const AllocatorCheckerTyped*() const noexcept { return *this; }
		__LL_NODISCARD__ operator AllocatorCheckerTyped*() noexcept { return *this; }
	public:
		// Does not constructs any object!
		__LL_NODISCARD__ T* allocate(const len_t lenght) noexcept {
			return reinterpret_cast<T*>(Allocator::allocate(lenght * sizeof(T)));
		}
		// Does not destructs any object!
		__LL_NODISCARD__ void deallocate(T*& mem) noexcept {
			Allocator::deallocate(reinterpret_cast<void*&>(mem));
		}
		// Does not constructs any object!
		// Does not destructs any object!
		__LL_NODISCARD__ ll_bool_t reallocate(T*& mem, const len_t lenght) noexcept {
			return Allocator::reallocate(reinterpret_cast<void*&>(mem), sizeof(T) * lenght);
		}
		// Only copy vector bytes
		__LL_NODISCARD__ void memcopy(const T* src, T* dst, const len_t lenght) noexcept {
			Allocator::memcopy(src, dst, lenght * sizeof(T));
		}
		// Only move vector bytes
		__LL_NODISCARD__ void memmove(T* src, T* dst, const len_t bytes) noexcept {
			Allocator::memmove(src, dst, bytes);
		}

		// Constructs all objects!
		__LL_NODISCARD__ T* allocateConstruct(const len_t lenght) noexcept {
			void* mem = Allocator::allocate(lenght * sizeof(T));
			if (mem) return new (mem) T[lenght];
			else return LL_NULLPTR;
		}
		// Destructs all objects and frees the vector
		__LL_NODISCARD__ void deallocate(T*& mem, T*& end) noexcept {
			__internal__::destruct_vector<T>(mem, end);
			Allocator::deallocate(reinterpret_cast<void*&>(mem));
			end = LL_NULLPTR;
		}
		// Destructs all objects and frees the vector
		__LL_NODISCARD__ ll_bool_t deallocate_s(T*& mem, const T* end) noexcept {
			if (!__internal__::destruct_vector_s<T>(mem, end)) return LL_FALSE;
			Allocator::deallocate(reinterpret_cast<void*&>(mem));
			return LL_TRUE;
		}
		// Constructs all new objects
		// Destructs all exceed objects
		__LL_NODISCARD__ ll_bool_t reallocate(T*& mem, const len_t old_size, const len_t new_size) noexcept {
			if (old_size == new_size) return LL_TRUE;
			else if (old_size > new_size) {
				__internal__::destruct_vector<T>(mem + new_size, mem + old_size);
				return Allocator::reallocate(reinterpret_cast<void*&>(mem), sizeof(T) * new_size);
			}
			else {
				if (!Allocator::reallocate(reinterpret_cast<void*&>(mem), sizeof(T) * new_size))
					return LL_FALSE;
				new (mem + old_size) T[new_size - old_size];
				return LL_TRUE;
			}
		}
		// Does not constructs all new objects
		// Destructs all exceed objects
		__LL_NODISCARD__ ll_bool_t reallocate_destruct(T*& mem, const len_t old_size, const len_t new_size) noexcept {
			if (old_size == new_size) return LL_TRUE;
			else if (old_size > new_size)
				__internal__::destruct_vector<T>(mem + new_size, mem + old_size);
			return Allocator::reallocate(reinterpret_cast<void*&>(mem), sizeof(T) * new_size);
		}
		// Copies objects with copy constructor
		__LL_NODISCARD__ void memcopy_contructor(const T* src, T* dst, const len_t lenght) noexcept {
			if constexpr (traits::is_basic_type_v<T> || std::is_pointer_v<T>)
				AllocatorCheckerTyped::memcopy(src, dst, lenght);
			else {
				const T* end = src + lenght;
				for (; src < end; ++src, ++dst)
					new (dst) T(*src);
			}
		}
		// Copies objects with copy operator
		__LL_NODISCARD__ void memcopy_operator(const T* src, T* dst, const len_t lenght) noexcept {
			if constexpr (traits::is_basic_type_v<T> || std::is_pointer_v<T>)
				AllocatorCheckerTyped::memcopy(src, dst, lenght);
			else {
				const T* end = src + lenght;
				for (; src < end; ++src, ++dst)
					*dst = *src;
			}
		}
		// Moves objects with move constructor
		__LL_NODISCARD__ void memmove_contructor(T* src, T* dst, const len_t lenght) noexcept {
			if constexpr (traits::is_basic_type_v<T> || std::is_pointer_v<T>)
				AllocatorCheckerTyped::memmove(src, dst, lenght);
			else {
				const T* end = src + lenght;
				for (; src < end; ++src, ++dst)
					new (dst) T(std::move(*src));
			}
		}
		// Moves objects with move operator
		__LL_NODISCARD__ void memmove_operator(T* src, T* dst, const len_t lenght) noexcept {
			if constexpr (traits::is_basic_type_v<T> || std::is_pointer_v<T>)
				AllocatorCheckerTyped::memcopy(src, dst, lenght);
			else {
				const T* end = src + lenght;
				for (; src < end; ++src, ++dst)
					*dst = std::move(*src);
			}
		}
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ALLOCATORCHECKER_HPP_
