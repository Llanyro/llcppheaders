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


template<class Allocator, len_t INCREMENT = 1024ull, class ConversorType = ll_char_t>
class DataBuffer : public Allocator {
	#pragma region Assert
	public:
		static_assert(!std::is_reference_v<Allocator>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<Allocator>, "Const type is forbidden!");
		static_assert(!std::is_pointer_v<Allocator>, "Pointer type is forbidden!");
		static_assert(!std::is_array_v<Allocator>, "Array type is forbidden!");
		static_assert(std::is_class_v<Allocator>, "Allocator needs to be a class!");

		using AllocateFunc = void*(Allocator::*)(const len_t bytes) noexcept;
		using DeallocateFunc = void(Allocator::*)(void*& mem) noexcept;
		using ReallocateFunc = ll_bool_t(Allocator::*)(void*& mem, const len_t bytes) noexcept;
		using MemCopyFunc = void(Allocator::*)(const void* src, void* dst, const len_t bytes) noexcept;
		using MemMoveFunc = void(Allocator::*)(void* src, void* dst, const len_t bytes) noexcept;

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
	protected:
		void* mem;
		void* mem_filled;
		void* mem_end;
	protected:
		void updateFilled(const len_t bytes) noexcept { this->mem_filled = this->get(bytes); }
		void updateEnd(const len_t bytes) noexcept { this->mem_end = this->get(bytes); }
		void advanceFilled(const len_t bytes) noexcept { this->mem_filled = this->filled<>() + bytes; }
		void advanceEnd(const len_t bytes) noexcept {
			this->mem_end = this->end<>() + bytes;
		}
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
			this->mem_filled = LL_NULLPTR;
			this->mem_end = LL_NULLPTR;
		}
	public:
		#pragma region Constructors
		DataBuffer() noexcept
			: Allocator(), mem(LL_NULLPTR), mem_filled(LL_NULLPTR), mem_end(LL_NULLPTR) {
			this->mem = this->allocate(INCREMENT);
			this->updateFilled(0ull);
			this->updateEnd(INCREMENT);
		}
		~DataBuffer() noexcept { this->invalidate(); }

		DataBuffer(const DataBuffer& other) noexcept
			: Allocator(), mem(LL_NULLPTR), mem_filled(LL_NULLPTR), mem_end(LL_NULLPTR)
		{ this->copyOther(other); }
		DataBuffer& operator=(const DataBuffer& other) noexcept {
			this->invalidate();
			this->copyOther(other);
			return *this;
		}
		DataBuffer(DataBuffer&& other) noexcept
			: Allocator(), mem(other.mem), mem_filled(other.mem_filled), mem_end(other.mem_end)
		{ other.simpleClear(); }
		DataBuffer& operator=(DataBuffer&& other) noexcept {
			this->invalidate();
			this->mem = other.mem;
			this->mem_filled = other.mem_filled;
			this->mem_end = other.mem_end;
			other.simpleClear();
			return *this;
		}

		#pragma endregion
		#pragma region Getters
		#pragma region Data
		void* begin() noexcept { return this->mem; }
		void* end() noexcept { return this->mem_end; }
		void* filled() noexcept { return this->mem_filled; }
		void* get(const len_t byte_position) noexcept {
			return static_cast<ConversorType*>(this->mem) + byte_position;
		}

		template<class T = ConversorType> T* begin() noexcept { return reinterpret_cast<T*>(this->mem); }
		template<class T = ConversorType> T* end() noexcept { return reinterpret_cast<T*>(this->mem); }
		template<class T = ConversorType> T* filled() noexcept { return reinterpret_cast<T*>(this->mem_filled); }
		template<class T = ConversorType> T* get(const len_t byte_position) noexcept {
			return this->begin<T>() + byte_position;
		}

		const void* begin() const noexcept { return this->mem; }
		const void* end() const noexcept { return this->mem_end; }
		const void* filled() const noexcept { return this->mem_filled; }
		const void* get(const len_t byte_position) const noexcept {
			return static_cast<ConversorType*>(this->mem) + byte_position;
		}

		template<class T = ConversorType> const T* begin() const noexcept { return reinterpret_cast<T*>(this->mem); }
		template<class T = ConversorType> const T* end() const noexcept { return reinterpret_cast<T*>(this->mem); }
		template<class T = ConversorType> const T* filled() const noexcept { return reinterpret_cast<T*>(this->mem_filled); }
		template<class T = ConversorType> const T* get(const len_t byte_position) const noexcept {
			return this->begin<T>() + byte_position;
		}

		#pragma endregion
		#pragma region Size
		__LL_NODISCARD__ len_t len() const noexcept { return this->end<>() - this->begin<>(); }
		__LL_NODISCARD__ len_t size() const noexcept { return this->len(); }
		__LL_NODISCARD__ len_t count() const noexcept { return this->len(); }

		__LL_NODISCARD__ len_t filled_len() const noexcept { return this->filled<>() - this->begin<>(); }
		__LL_NODISCARD__ len_t filled_size() const noexcept { return this->filled_len(); }
		__LL_NODISCARD__ len_t filled_count() const noexcept { return this->filled_len(); }

		#pragma endregion
		#pragma region SizeAvaible
		__LL_NODISCARD__ len_t avaible() const noexcept { return this->end<>() - this->filled<>(); }
		__LL_NODISCARD__ ll_bool_t avaible(const len_t bytes) const noexcept { return bytes < this->avaible(); }

		#pragma endregion

		#pragma endregion
		#pragma region DataManagement
		__LL_NODISCARD__ ll_bool_t push_back_copy(const void* mem, const len_t bytes) noexcept {
			if (!this->avaible(bytes)) {
				if (!this->reallocate(this->mem, this->len() + INCREMENT)) return LL_FALSE;
				else this->advanceEnd(INCREMENT);
			}
			this->memcopy(mem, this->filled(), bytes);
			this->advanceFilled(bytes);
			return LL_TRUE;
		}
		__LL_NODISCARD__ ll_bool_t push_back_move(void* mem, const len_t bytes) noexcept {
			if (!this->avaible(bytes)) {
				if (!this->reallocate(this->mem, this->len() + INCREMENT)) return LL_FALSE;
				else this->advanceEnd(INCREMENT);
			}
			this->memmove(mem, this->filled(), bytes);
			this->advanceFilled(bytes);
			return LL_TRUE;
		}
		void remove_data(const len_t bytes_to_remove) noexcept {
			if (this->filled_len() > bytes_to_remove)
				this->mem_filled = this->filled<>() - bytes_to_remove;
			else this->mem_filled = this->begin();
		}
		void invalidate() noexcept {
			this->deallocate(this->mem);
			this->mem_filled = LL_NULLPTR;
			this->mem_end = LL_NULLPTR;
		}
		ll_bool_t reserve(const len_t bytes) noexcept {
			if (!this->reallocate(this->mem, this->len() + bytes)) return LL_FALSE;
			else this->advanceEnd(bytes);
			return LL_TRUE;
		}

		#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_DATABUFFER_HPP_
