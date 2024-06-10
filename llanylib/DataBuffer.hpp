//////////////////////////////////////////////
//	DataBuffer.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DATABUFFER_HPP_) // Guard && version protector
	#if LLANYLIB_DATABUFFER_MAYOR_ != 8 || LLANYLIB_DATABUFFER_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "DataBuffer.hpp version error!"
		#else
			#error "DataBuffer.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_DATABUFFER_MAYOR_ || LLANYLIB_DATABUFFER_MINOR_

#else !defined(LLANYLIB_DATABUFFER_HPP_)
#define LLANYLIB_DATABUFFER_HPP_
#define LLANYLIB_DATABUFFER_MAYOR_ 8
#define LLANYLIB_DATABUFFER_MINOR_ 0

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

	__LL_NODISCARD__ void* allocate(const len_t bytes) noexcept {
		return LL_NULLPTR;
	}
	__LL_NODISCARD__ void deallocate(void*& mem) noexcept {
		mem = LL_NULLPTR;
	}
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

constexpr auto asdafa1 = traits::is_nothrow_copyable_v<AllocatorDummy>;
constexpr auto asdafa2 = traits::is_nothrow_swappeable_v<AllocatorDummy>;

template<class Allocator = AllocatorDummy, len_t INCREMENT = 1024ull, class ConversorType = ll_char_t>
class DataBuffer : public Allocator {
	#pragma region Assert
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
		using AllocateFunc = void*(Allocator::*)(const len_t) noexcept;
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
	#pragma endregion
	protected:
		void* mem;
		len_t len_filled;
		len_t length;
	protected:
		void updateFilled(const len_t bytes) noexcept { this->len_filled = bytes; }
		void updateEnd(const len_t bytes) noexcept { this->length = bytes; }
		void advanceEnd(const len_t bytes) noexcept { this->length += bytes; }
		// This requires this class is invalid to copy it
		void copyOther(const DataBuffer& other) noexcept {
			len_t size = other.len();
			this->mem = this->allocate(size);
			this->updateFilled(other.filled_len());
			this->updateEnd(size);
			this->memcopy(other.begin(), this->begin(), size);
		}
		void simpleClear() noexcept {
			this->mem = LL_NULLPTR;
			this->len_filled = ZERO_UI64;
			this->length = ZERO_UI64;
		}
	public:
		#pragma region Constructors
		DataBuffer() noexcept
			: Allocator(), mem(LL_NULLPTR), len_filled(ZERO_UI64), length(ZERO_UI64) {
			this->mem = this->allocate(INCREMENT);
			this->updateFilled(0ull);
			this->updateEnd(INCREMENT);
		}
		~DataBuffer() noexcept { this->invalidate(); }

		DataBuffer(const DataBuffer& other) noexcept
			: Allocator(other), mem(LL_NULLPTR), len_filled(ZERO_UI64), length(ZERO_UI64)
		{ this->copyOther(other); }
		DataBuffer& operator=(const DataBuffer& other) noexcept {
			Allocator::operator=(other);
			this->invalidate();
			this->copyOther(other);
			return *this;
		}
		DataBuffer(DataBuffer&& other) noexcept
			: Allocator(std::move(other)), mem(other.mem), len_filled(other.len_filled), length(other.length)
		{ other.simpleClear(); }
		DataBuffer& operator=(DataBuffer&& other) noexcept {
			Allocator::operator=(std::move(other));
			this->invalidate();
			this->mem = other.mem;
			this->len_filled = other.len_filled;
			this->length = other.length;
			other.simpleClear();
			return *this;
		}

		#pragma endregion
		#pragma region Getters
		#pragma region Data
		template<class T = ConversorType> T* get(const len_t byte_position) noexcept {
			return this->begin<T>() + byte_position;
		}
		template<class T = ConversorType> T* begin() noexcept { return reinterpret_cast<T>(this->mem); }
		template<class T = ConversorType> T* filled() noexcept { return this->get<T>(this->len_filled); }
		template<class T = ConversorType> T* end() noexcept { return this->get<T>(this->length); }

		template<class T = ConversorType> const T* get(const len_t byte_position) const noexcept {
			return this->begin<T>() + byte_position;
		}
		template<class T = ConversorType> const T* begin() const noexcept { return reinterpret_cast<T>(this->mem); }
		template<class T = ConversorType> const T* filled() const noexcept { return this->get<T>(this->len_filled); }
		template<class T = ConversorType> const T* end() const noexcept { return this->get<T>(this->length); }

		#pragma endregion
		#pragma region Size
		__LL_NODISCARD__ len_t len() const noexcept { return this->length; }
		__LL_NODISCARD__ len_t size() const noexcept { return this->len(); }
		__LL_NODISCARD__ len_t count() const noexcept { return this->len(); }

		__LL_NODISCARD__ len_t filled_len() const noexcept { return this->len_filled; }
		__LL_NODISCARD__ len_t filled_size() const noexcept { return this->filled_len(); }
		__LL_NODISCARD__ len_t filled_count() const noexcept { return this->filled_len(); }

		#pragma endregion
		#pragma region SizeAvaible
		__LL_NODISCARD__ len_t avaible() const noexcept { return this->len() - this->filled_len(); }
		__LL_NODISCARD__ ll_bool_t avaible(const len_t bytes) const noexcept { return bytes < this->avaible(); }

		#pragma endregion

		#pragma endregion
		#pragma region DataManagement
		__LL_NODISCARD__ ll_bool_t _push_back_copy(const void* mem, const len_t bytes) noexcept {
			if (!this->avaible(bytes)) {
				if (!this->reallocate(this->mem, this->len() + INCREMENT)) return LL_FALSE;
				else this->advanceEnd(INCREMENT);
			}
			this->memcopy(mem, this->filled(), bytes);
			this->advanceFilled(bytes);
			return LL_TRUE;
		}
		__LL_NODISCARD__ ll_bool_t _push_back_move(void* mem, const len_t bytes) noexcept {
			if (!this->avaible(bytes)) {
				if (!this->reallocate(this->mem, this->len() + INCREMENT)) return LL_FALSE;
				else this->advanceEnd(INCREMENT);
			}
			this->memmove(mem, this->filled(), bytes);
			this->advanceFilled(bytes);
			return LL_TRUE;
		}

		template<class T>
		__LL_NODISCARD__ ll_bool_t push_back_copy(const T* mem, const len_t len) noexcept {
			return this->_push_back_copy(mem, sizeof(T) * len);
		}
		template<class T>
		__LL_NODISCARD__ ll_bool_t push_back_move(T* mem, const len_t bytes) noexcept {
			return this->_push_back_move(mem, sizeof(T) * len);
		}

		void remove_data(const len_t bytes_to_remove) noexcept {
			if (this->filled_len() > bytes_to_remove)
				this->len_filled -= bytes_to_remove;
			else this->len_filled = ZERO_UI64;
		}
		void invalidate() noexcept {
			this->deallocate(this->mem);
			this->len_filled = ZERO_UI64;
			this->length = ZERO_UI64;
		}
		ll_bool_t reserve(const len_t bytes) noexcept {
			if (!this->reallocate(this->mem, this->len() + bytes)) return LL_FALSE;
			else this->advanceEnd(bytes);
			return LL_TRUE;
		}
		ll_bool_t reserve() noexcept {
			if (!this->reallocate(this->mem, this->len() + INCREMENT)) return LL_FALSE;
			else this->advanceEnd(INCREMENT);
			return LL_TRUE;
		}
		// CAREFULL, THIS FUNCTION IS NOT SECURE!!!
		// USE AT YOUR OWN RISK
		void advanceFilled(const len_t bytes) noexcept { this->len_filled += bytes; }
		__LL_NODISCARD__ ll_bool_t advanceFilled_s(const len_t bytes) noexcept {
			this->advanceFilled(bytes);
			if (this->filled_len() <= this->len())
				return LL_TRUE;
			this->len_filled -= bytes;
			return LL_FALSE;
		}


		#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_DATABUFFER_HPP_
