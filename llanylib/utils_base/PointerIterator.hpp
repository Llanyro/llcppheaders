//////////////////////////////////////////////
//	PointerIterator.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_POINTERITERATOR_INCOMPLETE_HPP_)
	#if LLANYLIB_POINTERITERATOR_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_POINTERITERATOR_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "PointerIterator.hpp(incomplete) version error!"
		#else
			#error "PointerIterator.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_POINTERITERATOR_INCOMPLETE_MAYOR_ || LLANYLIB_POINTERITERATOR_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_POINTERITERATOR_INCOMPLETE_HPP_)
	#define LLANYLIB_POINTERITERATOR_INCOMPLETE_HPP_
	#define LLANYLIB_POINTERITERATOR_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_POINTERITERATOR_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_POINTERITERATOR_HPP_)
	#if LLANYLIB_POINTERITERATOR_MAYOR_ != 11 || LLANYLIB_POINTERITERATOR_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "PointerIterator.hpp version error!"
		#else
			#error "PointerIterator.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_POINTERITERATOR_MAYOR_ || LLANYLIB_POINTERITERATOR_MINOR_

#else
	#define LLANYLIB_POINTERITERATOR_HPP_
	#define LLANYLIB_POINTERITERATOR_MAYOR_ 11
	#define LLANYLIB_POINTERITERATOR_MINOR_ 0

#include "../traits_base/type_traits.hpp"

namespace llcpp {
namespace meta {
namespace utils {

template<class _T, ll_bool_t _IS_REVERSED = ::llcpp::FALSE>
class PointerIterator {
	#pragma region Types
	public:
		// Class related
		using _MyType	= PointerIterator;

		// Types
		using T					= _T;
		using type				= T;
		using value_type		= T;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t IS_REVERSED = _IS_REVERSED;

	#pragma endregion
	#pragma region Attributes
	private:
		T* mem;

	#pragma endregion
	#pragma region Functions
		#pragma region Private
	private:
		constexpr void simpleClear() noexcept { this->setMem(::llcpp::NULL_VALUE<decltype(this->mem)>); }
		constexpr void setMem(T* mem) noexcept { this->mem = mem; }

		#pragma endregion
		#pragma region Constructors
	public:
		constexpr PointerIterator() noexcept
			: PointerIterator(::llcpp::NULL_VALUE<decltype(this->mem)>)
		{}
		constexpr PointerIterator(T* mem) noexcept
			: mem(mem)
		{}
		constexpr ~PointerIterator() noexcept {
			if constexpr (::llcpp::CLEAR_POINTERS_ON_DESTRUCTION)
				this->simpleClear();
		}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr PointerIterator(const PointerIterator& other) noexcept
			: PointerIterator(other.mem)
		{}
		constexpr PointerIterator& operator=(const PointerIterator& other) noexcept {
			this->setMem(other.mem);
			return *this;
		}
		constexpr PointerIterator(PointerIterator&& other) noexcept
			: PointerIterator(other.mem)
		{ other.simpleClear(); }
		constexpr PointerIterator& operator=(PointerIterator&& other) noexcept {
			this->setMem(other.mem);
			other.simpleClear();
			return *this;
		}

		constexpr PointerIterator(volatile const PointerIterator& other) noexcept = delete;
		constexpr PointerIterator& operator=(volatile const PointerIterator& other) noexcept = delete;
		constexpr PointerIterator(volatile PointerIterator&& other) noexcept = delete;
		constexpr PointerIterator& operator=(volatile PointerIterator&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const PointerIterator*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator PointerIterator*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		constexpr PointerIterator& operator++() noexcept {
			if constexpr (_MyType::IS_REVERSED)
				--this->mem;
			else ++this->mem;
			return *this;
		}
		constexpr PointerIterator operator++(int) noexcept {
			if constexpr (_MyType::IS_REVERSED)
				return this->mem--;
			else return this->mem++;
		}

		constexpr PointerIterator& operator--() noexcept {
			if constexpr (_MyType::IS_REVERSED)
				++this->mem;
			else --this->mem;
			return *this;
		}
		constexpr PointerIterator operator--(int) noexcept {
			if constexpr (_MyType::IS_REVERSED)
				return this->mem++;
			else return this->mem--;
		}

		constexpr PointerIterator& operator+=(const isize pos) noexcept {
			if constexpr (_MyType::IS_REVERSED)
				this->mem -= pos;
			else this->mem += pos;
			return *this;
		}
		constexpr PointerIterator& operator-=(const isize pos) noexcept {
			if constexpr (_MyType::IS_REVERSED)
				this->mem += pos;
			else this->mem -= pos;
			return *this;
		}

		__LL_NODISCARD__ constexpr PointerIterator operator+(const isize pos) noexcept {
			if constexpr (_MyType::IS_REVERSED)
				return this->mem - pos;
			else return this->mem + pos;
		}
		__LL_NODISCARD__ constexpr PointerIterator operator-(const isize pos) noexcept {
			if constexpr (_MyType::IS_REVERSED)
				return this->mem + pos;
			else return this->mem - pos;
		}

		__LL_NODISCARD__ constexpr T& operator*() noexcept { return *this->mem; }
		__LL_NODISCARD__ constexpr T* operator->() noexcept { return ::std::addressof(*this->mem); }

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const T* other) const noexcept {
			return this->mem == other;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const T* other) const noexcept {
			return this->mem != other;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const T* other) const noexcept {
			return this->mem >= other;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const T* other) const noexcept {
			return this->mem <= other;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const PointerIterator& other) const noexcept {
			return this->mem == other.mem;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const PointerIterator& other) const noexcept {
			return this->mem != other.mem;
		}

		#pragma endregion

	#pragma endregion
};

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_POINTERITERATOR_HPP_
