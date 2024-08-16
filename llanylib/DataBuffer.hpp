//////////////////////////////////////////////
//	DataBuffer.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DATABUFFER_HPP_) // Guard && version protector
	#if LLANYLIB_DATABUFFER_MAYOR_ != 9 || LLANYLIB_DATABUFFER_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "DataBuffer.hpp version error!"
		#else
			#error "DataBuffer.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_DATABUFFER_MAYOR_ || LLANYLIB_DATABUFFER_MINOR_

#else !defined(LLANYLIB_DATABUFFER_HPP_)
#define LLANYLIB_DATABUFFER_HPP_
#define LLANYLIB_DATABUFFER_MAYOR_ 9
#define LLANYLIB_DATABUFFER_MINOR_ 0

#include "AllocatorChecker.hpp"

namespace llcpp {
namespace meta {

template<class Allocator = AllocatorDummy, len_t INCREMENT = 1024ull, class ConversorType = ll_char_t>
class DataBuffer : public AllocatorChecker<Allocator> {
	public:
		using AllocatorCheckerBase = AllocatorChecker<Allocator>;
		template<class T>
		using MoveOrAllocator = void(Allocator::*)(T*, void*, const len_t) noexcept;
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
			: AllocatorCheckerBase(), mem(LL_NULLPTR), len_filled(ZERO_UI64), length(ZERO_UI64) {
			this->mem = this->allocate(INCREMENT);
			this->updateFilled(0ull);
			this->updateEnd(INCREMENT);
		}
		~DataBuffer() noexcept { this->invalidate(); }

		DataBuffer(const DataBuffer& other) noexcept
			: AllocatorCheckerBase(other), mem(LL_NULLPTR), len_filled(ZERO_UI64), length(ZERO_UI64)
		{ this->copyOther(other); }
		DataBuffer& operator=(const DataBuffer& other) noexcept {
			AllocatorCheckerBase::operator=(other);
			this->invalidate();
			this->copyOther(other);
			return *this;
		}
		DataBuffer(DataBuffer&& other) noexcept
			: AllocatorCheckerBase(std::move(other)), mem(other.mem), len_filled(other.len_filled), length(other.length)
		{ other.simpleClear(); }
		DataBuffer& operator=(DataBuffer&& other) noexcept {
			AllocatorCheckerBase::operator=(std::move(other));
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
		template<class T = ConversorType> T* begin() noexcept { return reinterpret_cast<T*>(this->mem); }
		template<class T = ConversorType> T* filled() noexcept { return this->get<T>(this->len_filled); }
		template<class T = ConversorType> T* end() noexcept { return this->get<T>(this->length); }

		template<class T = ConversorType> const T* get(const len_t byte_position) const noexcept {
			return this->begin<T>() + byte_position;
		}
		template<class T = ConversorType> const T* begin() const noexcept { return reinterpret_cast<T*>(this->mem); }
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
	private:
		template<class T, MoveOrAllocator<T> FUNC>
		__LL_NODISCARD__ ll_bool_t push_back_body(T* mem, const len_t bytes) noexcept {
			if (!this->avaible(bytes)) {
				if (!AllocatorCheckerBase::reallocate(this->mem, this->len() + bytes)) return llcpp::LL_FALSE;
				else this->advanceEnd(bytes);
			}
			(this->*FUNC)(mem, this->filled(), bytes);
			this->advanceFilled(bytes);
			return llcpp::LL_TRUE;
		}
	public:
		__LL_NODISCARD__ ll_bool_t _push_back_copy(const void* mem, const len_t bytes) noexcept {
			return this->push_back_body<const void, &AllocatorCheckerBase::memcopy>(mem, bytes);
		}
		__LL_NODISCARD__ ll_bool_t _push_back_move(void* mem, const len_t bytes) noexcept {
			return this->push_back_body<void, &AllocatorCheckerBase::memmove>(mem, bytes);
		}

		template<class T, len_t N>
		__LL_NODISCARD__ ll_bool_t push_back_copy(const T(&mem)[N]) noexcept {
			return this->push_back_copy<T>(mem, N);
		}
		template<class T, len_t N>
		__LL_NODISCARD__ ll_bool_t push_back_move(T(&mem)[N]) noexcept {
			return this->push_back_move<T>(mem, N);
		}

		template<class T>
		__LL_NODISCARD__ ll_bool_t push_back_copy(const T* mem, const len_t len) noexcept {
			// Copy pointers would lead in future bad behabiours
			// Ex, copy the pointer, then delete the data in other point
			// Memory will be invalidated, but this pointer not...
			if constexpr (std::is_pointer_v<T>) return llcpp::LL_FALSE;
			else if constexpr (traits::is_basic_type_v<T>)
				return this->_push_back_copy(mem, sizeof(T) * len);
			else {
				if constexpr (!std::is_array_v<T>)
					static_assert(std::is_copy_constructible_v<T>, "Class provided needs a noexcept copy constructor!");

				// Reserve size for all elemets
				len_t size_of = sizeof(T) * len;
				if (!this->avaible(size_of)) {
					if (!AllocatorCheckerBase::reallocate(this->mem, this->len() + size_of)) return llcpp::LL_FALSE;
					else this->advanceEnd(size_of);
				}

				const T* end = mem + len;

				if constexpr (std::is_array_v<T>) {
					// Copy all elements calling this function again
					using ArrType = traits::type_conversor<T>::array_to_type_t;
					for (; mem < end; ++mem)
						if (!this->push_back_copy<ArrType, traits::array_size<T>>(*mem))
							return llcpp::LL_FALSE;
				}
				else {
					// Construct all elements with copy constructor
					T* to_fill = this->filled<T>();
					for (; mem < end; ++mem, ++to_fill)
						new (to_fill) T(*mem);
					this->advanceFilled(size_of);
				}
				return llcpp::LL_TRUE;
			}
		}
		template<class T>
		__LL_NODISCARD__ ll_bool_t push_back_move(T* mem, const len_t len) noexcept {
			if constexpr (std::is_pointer_v<T> || traits::is_basic_type_v<T>)
				return this->_push_back_move(mem, sizeof(T) * len);
			else {
				if constexpr (!std::is_array_v<T>)
					static_assert(std::is_move_constructible_v<T>, "Class provided needs a noexcept move constructor!");

				len_t size_of = sizeof(T) * len;
				if (!this->avaible(size_of)) {
					if (!AllocatorCheckerBase::reallocate(this->mem, this->len() + size_of)) return llcpp::LL_FALSE;
					else this->advanceEnd(size_of);
				}

				const T* end = mem + len;

				if constexpr (std::is_array_v<T>) {
					using ArrType = traits::type_conversor<T>::array_to_type_t;
					for (; mem < end; ++mem)
						if (!this->push_back_move<ArrType, traits::array_size<T>>(*mem))
							return llcpp::LL_FALSE;
				}
				else {
					T* to_fill = this->filled<T>();
					for (; mem < end; ++mem, ++to_fill)
						new (to_fill) T(std::move(*mem));
					this->advanceFilled(size_of);
				}
				return llcpp::LL_TRUE;
			}


		}

		template<class U, class W  = traits::cinput<U>>
		__LL_NODISCARD__ ll_bool_t push_back_copy(W object) noexcept {
			// Copy pointers would lead in future bad behabiours
			// Ex, copy the pointer, then delete the data in other point
			// Memory will be invalidated, but this pointer not...
			if constexpr (std::is_pointer_v<U>) return llcpp::LL_FALSE;
			else if constexpr (std::is_array_v<U>)
				return this->push_back_copy(object, traits::array_size<U>);
			else {
				static_assert(std::is_copy_constructible_v<Allocator>, "Class provided needs a noexcept copy constructor!");
				constexpr len_t size_of = sizeof(U);
				if (!this->avaible(size_of)) {
					if (!AllocatorCheckerBase::reallocate(this->mem, this->len() + size_of)) return llcpp::LL_FALSE;
					else this->advanceEnd(size_of);
				}
				new (this->filled<ll_char_t>()) U(object);
				this->advanceFilled(size_of);
				return llcpp::LL_TRUE;
			}
		}
		template<class U>
		__LL_NODISCARD__ ll_bool_t push_back_move(U&& object) noexcept {
			if constexpr (std::is_array_v<U>)
				return this->push_back_move(object, traits::array_size<U>);
			else {
				static_assert(std::is_move_constructible_v<U>, "Class provided needs a noexcept move constructor!");
				constexpr len_t size_of = sizeof(U);
				if (!this->avaible(size_of)) {
					if (!AllocatorCheckerBase::reallocate(this->mem, this->len() + size_of)) return llcpp::LL_FALSE;
					else this->advanceEnd(size_of);
				}

				if constexpr (std::is_pointer_v<U>) {
					*this->filled<U>() = object;
					object = LL_NULLPTR;
				}
				else if constexpr (traits::is_basic_type_v<U>)
					*this->filled<U>() = object;
				else new (this->filled<void>()) U(std::move(object));

				this->advanceFilled(size_of);
				return llcpp::LL_TRUE;
			}
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
			if (!AllocatorCheckerBase::reallocate(this->mem, this->len() + bytes)) return llcpp::LL_FALSE;
			else this->advanceEnd(bytes);
			return llcpp::LL_TRUE;
		}
		ll_bool_t reserve() noexcept {
			if (!AllocatorCheckerBase::reallocate(this->mem, this->len() + INCREMENT)) return llcpp::LL_FALSE;
			else this->advanceEnd(INCREMENT);
			return llcpp::LL_TRUE;
		}
		// CAREFULL, THIS FUNCTION IS NOT SECURE!!!
		// USE AT YOUR OWN RISK
		void advanceFilled(const len_t bytes) noexcept { this->len_filled += bytes; }
		__LL_NODISCARD__ ll_bool_t advanceFilled_s(const len_t bytes) noexcept {
			this->advanceFilled(bytes);
			if (this->filled_len() <= this->len())
				return llcpp::LL_TRUE;
			this->len_filled -= bytes;
			return llcpp::LL_FALSE;
		}

		#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_DATABUFFER_HPP_
