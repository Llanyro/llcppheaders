//////////////////////////////////////////////
//	AllocatorChecker.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ALLOCATORCHECKER_HPP_) // Guard && version protector
	#if LLANYLIB_ALLOCATORCHECKER_MAYOR_ != 9 || LLANYLIB_ALLOCATORCHECKER_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "AllocatorChecker.hpp version error!"
		#else
			#error "AllocatorChecker.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ALLOCATORCHECKER_MAYOR_ || LLANYLIB_ALLOCATORCHECKER_MINOR_

#else !defined(LLANYLIB_ALLOCATORCHECKER_HPP_)
#define LLANYLIB_ALLOCATORCHECKER_HPP_
#define LLANYLIB_ALLOCATORCHECKER_MAYOR_ 9
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

class AllocatorDummy {
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr AllocatorDummy() noexcept {}
		constexpr ~AllocatorDummy() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr AllocatorDummy(const AllocatorDummy&) noexcept {}
		constexpr AllocatorDummy& operator=(const AllocatorDummy&) noexcept { return *this; }
		constexpr AllocatorDummy(AllocatorDummy&&) noexcept {}
		constexpr AllocatorDummy& operator=(AllocatorDummy&&) noexcept { return *this; }

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const AllocatorDummy*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator AllocatorDummy*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		constexpr __LL_NODISCARD__ void* allocate(const len_t bytes) noexcept { return LL_NULLPTR; }
		constexpr void deallocate(void*& mem) noexcept { mem = LL_NULLPTR; }
		constexpr __LL_NODISCARD__ ll_bool_t reallocate(void*& mem, const len_t bytes) noexcept {
			mem = LL_NULLPTR;
			return LL_FALSE;
		}
		constexpr void memcopy(const void* src, void* dst, const len_t bytes) noexcept {}
		constexpr void memmove(void* src, void* dst, const len_t bytes) noexcept {}
		constexpr void clear_data(void* mem, const len_t bytes) noexcept {}

		#pragma endregion
	#pragma endregion
};

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

template<class Allocator = AllocatorDummy>
class AllocatorChecker : public Allocator {
	#pragma region Types
	public:
		using AllocateFunc = void* (Allocator::*)(const len_t) noexcept;
		using DeallocateFunc = void(Allocator::*)(void*&) noexcept;
		using ReallocateFunc = ll_bool_t(Allocator::*)(void*&, const len_t) noexcept;
		using MemCopyFunc = void(Allocator::*)(const void*, void*, const len_t) noexcept;
		using MemMoveFunc = void(Allocator::*)(void*, void*, const len_t) noexcept;
		using ClearFunc = void(Allocator::*)(void*, const len_t) noexcept;

	#pragma endregion
	#pragma region Assets
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

	#pragma region AllocationAssets
	public:
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
		static_assert(
			std::is_same_v<ClearFunc, decltype(&Allocator::clear_data)>,
			"Allocator::clear_data needs to be the same type as ClearFunc!");

	#pragma endregion

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr AllocatorChecker() noexcept : Allocator() {}
		template<class... Args>
		constexpr AllocatorChecker(Args&&... args) noexcept : Allocator(std::forward<Args>(args)...) {}
		constexpr ~AllocatorChecker() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr AllocatorChecker(const AllocatorChecker& other) noexcept : Allocator(other) {}
		constexpr AllocatorChecker& operator=(const AllocatorChecker& other) noexcept {
			Allocator::operator=(other);
			return *this;
		}
		constexpr AllocatorChecker(AllocatorChecker&& other) noexcept : Allocator(std::move(other)) {}
		constexpr AllocatorChecker& operator=(AllocatorChecker&& other) noexcept {
			Allocator::operator=(std::move(other));
			return *this;
		}

		constexpr AllocatorChecker(const Allocator& other) noexcept : Allocator(other) {}
		constexpr AllocatorChecker& operator=(const Allocator& other) noexcept {
			Allocator::operator=(other);
			return *this;
		}
		constexpr AllocatorChecker(Allocator&& other) noexcept : Allocator(std::move(other)) {}
		constexpr AllocatorChecker& operator=(Allocator&& other) noexcept {
			Allocator::operator=(std::move(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const AllocatorChecker*() const noexcept { return *this; }
		__LL_NODISCARD__ constexpr operator AllocatorChecker*() noexcept { return *this; }

		#pragma endregion

	#pragma endregion
};

template<class T, class Allocator = AllocatorDummy>
class AllocatorCheckerTyped : public AllocatorChecker<Allocator> {
	#pragma region Types
	public:
		using AllocatorCheckerBase = meta::AllocatorChecker<Allocator>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(!std::is_array_v<T>, "This class does not support array type");

		static_assert(std::is_nothrow_constructible_v<T>, "Type needs a noexcept constructor!");
		static_assert(std::is_nothrow_destructible_v<T>, "Type needs a noexcept destructor!");
		static_assert(std::is_copy_constructible_v<T>, "Type needs a noexcept copy constructor!");
		static_assert(std::is_copy_assignable_v<T>, "Type needs a noexcept copy asignable!");
		static_assert(std::is_move_constructible_v<T>, "Type needs a noexcept move constructor!");
		static_assert(std::is_move_assignable_v<T>, "Type needs a noexcept move asignable!");

	#pragma endregion
	#pragma region Functions
		#pragma region Constructor
	public:
		constexpr AllocatorCheckerTyped() noexcept : AllocatorCheckerBase() {}
		template<class... Args>
		constexpr AllocatorCheckerTyped(Args&&... args) noexcept : AllocatorCheckerBase(std::forward<Args>(args)...) {}
		constexpr ~AllocatorCheckerTyped() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr AllocatorCheckerTyped(const AllocatorCheckerTyped& other) noexcept : AllocatorCheckerBase(other) {}
		constexpr AllocatorCheckerTyped& operator=(const AllocatorCheckerTyped& other) noexcept {
			AllocatorCheckerBase::operator=(other);
			return *this;
		}
		constexpr AllocatorCheckerTyped(AllocatorCheckerTyped&& other) noexcept : AllocatorCheckerBase(std::move(other)) {}
		constexpr AllocatorCheckerTyped& operator=(AllocatorCheckerTyped&& other) noexcept {
			AllocatorCheckerBase::operator=(std::move(other));
			return *this;
		}

		constexpr AllocatorCheckerTyped(const AllocatorCheckerBase& other) noexcept : AllocatorCheckerBase(other) {}
		constexpr AllocatorCheckerTyped& operator=(const AllocatorCheckerBase& other) noexcept {
			AllocatorCheckerBase::operator=(other);
			return *this;
		}
		constexpr AllocatorCheckerTyped(AllocatorCheckerBase&& other) noexcept : AllocatorCheckerBase(std::move(other)) {}
		constexpr AllocatorCheckerTyped& operator=(AllocatorCheckerBase&& other) noexcept {
			AllocatorCheckerBase::operator=(std::move(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const AllocatorCheckerTyped*() const noexcept { return *this; }
		__LL_NODISCARD__ constexpr operator AllocatorCheckerTyped*() noexcept { return *this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region AllocatorTyped
	public:
		// Does not constructs any object!
		__LL_NODISCARD__ constexpr  T* allocate(const len_t lenght) noexcept {
			return reinterpret_cast<T*>(Allocator::allocate(sizeof(T) * lenght));
		}
		// Does not destructs any object!
		constexpr void deallocate(T*& mem) noexcept {
			Allocator::deallocate(reinterpret_cast<void*&>(mem));
		}
		// Does not constructs any object!
		// Does not destructs any object!
		__LL_NODISCARD__ constexpr ll_bool_t reallocate(T*& mem, const len_t lenght) noexcept {
			return Allocator::reallocate(reinterpret_cast<void*&>(mem), sizeof(T) * lenght);
		}
		// Only copy vector bytes
		void constexpr memcopy(const T* src, T* dst, const len_t lenght) noexcept {
			Allocator::memcopy(src, dst, sizeof(T) * lenght);
		}
		// Only move vector bytes
		void constexpr memmove(T* src, T* dst, const len_t lenght) noexcept {
			Allocator::memmove(src, dst, sizeof(T) * lenght);
		}
		// Sets all bytes to 0
		void constexpr clear_data(T* mem, const len_t lenght) noexcept {
			Allocator::clear_data(mem, sizeof(T) * lenght);
		}

		#pragma endregion
		#pragma region AllocatorExtra
	public:
		// Constructs Object with arguments
		template<class... Args>
		__LL_NODISCARD__ constexpr T* allocateObject(Args&&... args) noexcept {
			void* mem = Allocator::allocate(sizeof(T));
			if (mem) return new (mem) T(std::forward<Args>(args)...);
			else return LL_NULLPTR;
		}
		// Destructs object
		constexpr void deallocateObject(T*& mem) noexcept {
			mem->~T();
			Allocator::deallocate(reinterpret_cast<void*&>(mem));
		}
		// Destructs object if pointer is not nullptr
		constexpr void deallocateObject_s(T*& mem) noexcept {
			if (mem) {
				mem->~T();
				Allocator::deallocate(reinterpret_cast<void*&>(mem));
			}
		}

		// Constructs all objects!
		__LL_NODISCARD__ constexpr T* allocateConstruct(const len_t lenght) noexcept {
			void* mem = Allocator::allocate(sizeof(T) * lenght);
			if (mem) return new (mem) T[lenght];
			else return LL_NULLPTR;
		}
		// Destructs all objects and frees the vector
		constexpr void deallocate(T*& mem, const T* end) noexcept {
			__internal__::destruct_vector<T>(mem, end);
			Allocator::deallocate(reinterpret_cast<void*&>(mem));
		}
		// Destructs all objects and frees the vector
		__LL_NODISCARD__ constexpr ll_bool_t deallocate_s(T*& mem, const T* end) noexcept {
			if (!__internal__::destruct_vector_s<T>(mem, end)) return LL_FALSE;
			Allocator::deallocate(reinterpret_cast<void*&>(mem));
			return LL_TRUE;
		}
		// Constructs all new objects
		// Destructs all exceed objects
		__LL_NODISCARD__ constexpr ll_bool_t reallocate(T*& mem, const len_t old_size, const len_t new_size) noexcept {
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
		__LL_NODISCARD__ constexpr ll_bool_t reallocate_destruct(T*& mem, const len_t old_size, const len_t new_size) noexcept {
			if (old_size == new_size) return LL_TRUE;
			else if (old_size > new_size)
				__internal__::destruct_vector<T>(mem + new_size, mem + old_size);
			return Allocator::reallocate(reinterpret_cast<void*&>(mem), sizeof(T) * new_size);
		}
		// Copies objects with copy constructor
		constexpr void memcopy_contructor(const T* src, T* dst, const len_t lenght) noexcept {
			if constexpr (traits::is_basic_type_v<T> || std::is_pointer_v<T>)
				AllocatorCheckerTyped::memcopy(src, dst, lenght);
			else {
				const T* end = src + lenght;
				for (; src < end; ++src, ++dst)
					new (dst) T(*src);
			}
		}
		// Copies objects with copy operator
		constexpr void memcopy_operator(const T* src, T* dst, const len_t lenght) noexcept {
			if constexpr (traits::is_basic_type_v<T> || std::is_pointer_v<T>)
				AllocatorCheckerTyped::memcopy(src, dst, lenght);
			else {
				const T* end = src + lenght;
				for (; src < end; ++src, ++dst)
					*dst = *src;
			}
		}
		// Moves objects with move constructor
		constexpr void memmove_contructor(T* src, T* dst, const len_t lenght) noexcept {
			if constexpr (traits::is_basic_type_v<T> || std::is_pointer_v<T>)
				AllocatorCheckerTyped::memmove(src, dst, lenght);
			else {
				const T* end = src + lenght;
				for (; src < end; ++src, ++dst)
					new (dst) T(std::move(*src));
			}
		}
		// Moves objects with move operator
		constexpr void memmove_operator(T* src, T* dst, const len_t lenght) noexcept {
			if constexpr (traits::is_basic_type_v<T> || std::is_pointer_v<T>)
				AllocatorCheckerTyped::memcopy(src, dst, lenght);
			else {
				const T* end = src + lenght;
				for (; src < end; ++src, ++dst)
					*dst = std::move(*src);
			}
		}
		// Clear all objects with its destructor
		constexpr void clear_data_destruct(T* mem, const len_t lenght) noexcept {
			__internal__::destruct_vector(mem, lenght);
		}
		// Clear all objects with its destructor
		constexpr __LL_NODISCARD__ ll_bool_t clear_data_destruct_s(T* mem, const len_t lenght) noexcept {
			return __internal__::destruct_vector_s(mem, lenght);
		}

		#pragma endregion

		#pragma endregion
	#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ALLOCATORCHECKER_HPP_
