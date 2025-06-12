//////////////////////////////////////////////
//	PointerIterator.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_POINTERITERATOR_INCOMPLETE_HPP_)
	#if LLANYLIB_POINTERITERATOR_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_POINTERITERATOR_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "PointerIterator.hpp(incomplete) version error!"
		#else
			#error "PointerIterator.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_POINTERITERATOR_INCOMPLETE_MAYOR_ || LLANYLIB_POINTERITERATOR_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_POINTERITERATOR_INCOMPLETE_HPP_)
	#define LLANYLIB_POINTERITERATOR_INCOMPLETE_HPP_
	#define LLANYLIB_POINTERITERATOR_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_POINTERITERATOR_INCOMPLETE_MINOR_ 0

#include <llanylib/traits_base/type_traits.hpp>
#include <llanylib/traits/ValidationChecker.hpp>
#include <llanylib/utils_base/GenericFunctions.hpp>

namespace llcpp {
namespace meta {
namespace utils {

template<class _T, ll_bool_t _IS_REVERSED = ::llcpp::LL_FALSE>
class PointerIterator;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_POINTERITERATOR_HPP_)
	#if LLANYLIB_POINTERITERATOR_MAYOR_ != 12 || LLANYLIB_POINTERITERATOR_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "PointerIterator.hpp version error!"
		#else
			#error "PointerIterator.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_POINTERITERATOR_MAYOR_ || LLANYLIB_POINTERITERATOR_MINOR_

#else
	#define LLANYLIB_POINTERITERATOR_HPP_
	#define LLANYLIB_POINTERITERATOR_MAYOR_ 12
	#define LLANYLIB_POINTERITERATOR_MINOR_ 0

#include <llanylib/traits_base/type_traits.hpp>
#include <llanylib/traits/ValidationChecker.hpp>
#include <llanylib/utils_base/GenericFunctions.hpp>

#if defined(__LL_MINGW)
	#include <memory>	// To use ::std::addressof
#endif // __LL_MINGW

namespace llcpp {
namespace meta {
namespace utils {

template<class _T, ll_bool_t _IS_REVERSED = ::llcpp::LL_FALSE>
class PointerIterator {
	#pragma region Types
	public:
		// Class related
		using _MyType		= PointerIterator;

		// Types and enums
		using T				= _T;
		using type			= T;
		using value_type	= T;

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
		constexpr void setMem(T* mem) noexcept { this->mem = mem; }

		#pragma endregion
		#pragma region Constructors
	public:
		// By default is invalid class
		constexpr PointerIterator() noexcept
			: PointerIterator(::llcpp::NULL_VALUE<T>)
		{}
		constexpr PointerIterator(T* mem) noexcept
			: mem(mem)
		{}
		constexpr ~PointerIterator() noexcept {
			if constexpr (::llcpp::LL_CLEAR_POINTERS_ON_DESTRUCTION)
				this->makeInvalid();
		}

		#pragma endregion
		#pragma region CopyMove
	public:
		// [TOCHECK] [TODO] [TOFIX]
		template<ll_bool_t __IS_REVERSED>
		constexpr PointerIterator(const PointerIterator<T, __IS_REVERSED>& other) noexcept
			: PointerIterator(other.mem)
		{}
		// [TOCHECK] [TODO] [TOFIX]
		template<ll_bool_t __IS_REVERSED>
		constexpr PointerIterator& operator=(const PointerIterator<T, __IS_REVERSED>& other) noexcept {
			this->reset(other.mem);
			return *this;
		}
		template<ll_bool_t __IS_REVERSED>
		constexpr PointerIterator(PointerIterator<T, __IS_REVERSED>&& other) noexcept
			: PointerIterator(other.getPointer())
		{ other.makeInvalid(); }
		template<ll_bool_t __IS_REVERSED>
		constexpr PointerIterator& operator=(PointerIterator<T, __IS_REVERSED>&& other) noexcept {
			this->reset(other.getPointer());
			other.makeInvalid();
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
		__LL_NODISCARD__ constexpr T* getPointer() noexcept { return this->mem; }
		__LL_NODISCARD__ constexpr const T* getPointer() const noexcept { return this->mem; }

		// Returns ValidType::Valid if pointer is not nullptr
		__LL_NODISCARD__ constexpr ::llcpp::misc::ValidType validationType() const noexcept {
			return (this->mem != ::llcpp::NULL_VALUE<T>) ? ::llcpp::misc::ValidType::Valid : ::llcpp::misc::ValidType::Invalid;
		}
		// Reset pointer iterator to new mem
		constexpr void reset(T* mem) noexcept { this->setMem(mem); }
		// Clear pointer with provided cleaner type
		template<class ExtraCleaner = ::llcpp::meta::utils::Cleaner>
		constexpr void clear() noexcept {
			ExtraCleaner extra;
			this->clear(extra);
		}
		// Clear pointer with provided cleaner
		template<class ExtraCleaner = ::llcpp::meta::utils::Cleaner>
		constexpr void clear(const ExtraCleaner& extra) noexcept {
			::llcpp::meta::utils::Cleaner cleaner;
			(void)cleaner.process(this->mem, extra);
		}
		// Sets pointer to nullptr
		constexpr void makeInvalid() noexcept {
			this->mem = ::llcpp::NULL_VALUE<T>;
		}
		// Clears mem and set it to nullptr
		template<class ExtraCleaner = ::llcpp::meta::utils::Cleaner>
		constexpr void makeInvalidClear() noexcept {
			ExtraCleaner extra;
			this->makeInvalidClear(extra);
		}
		// Clears mem (wtih object privided) and set it to nullptr
		template<class ExtraCleaner = ::llcpp::meta::utils::Cleaner>
		constexpr void makeInvalidClear(const ExtraCleaner& extra) noexcept {
			this->clear(extra);
			this->makeInvalid();
		}

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

		__LL_NODISCARD__ constexpr PointerIterator operator+(const isize pos) const noexcept {
			if constexpr (_MyType::IS_REVERSED)
				return this->mem - pos;
			else return this->mem + pos;
		}
		__LL_NODISCARD__ constexpr PointerIterator operator-(const isize pos) const noexcept {
			if constexpr (_MyType::IS_REVERSED)
				return this->mem + pos;
			else return this->mem - pos;
		}

		__LL_NODISCARD__ constexpr isize distance(T* mem) const noexcept {
			return this->mem - mem;
		}
		template<ll_bool_t __IS_REVERSED>
		__LL_NODISCARD__ constexpr isize distance(const PointerIterator<T, __IS_REVERSED>& it) const noexcept {
			return this->mem - it.mem;
		}
		__LL_NODISCARD__ constexpr isize operator-(T* mem) const noexcept {
			return this->mem - mem;
		}
		template<ll_bool_t __IS_REVERSED>
		__LL_NODISCARD__ constexpr isize operator-(const PointerIterator<_T, __IS_REVERSED>& it) const noexcept {
			return this->mem - it.mem;
		}

		__LL_NODISCARD__ constexpr T& operator*() noexcept { return *this->mem; }
		__LL_NODISCARD__ constexpr T* operator->() noexcept { return ::std::addressof(*this->mem); }
		__LL_NODISCARD__ constexpr operator T* () noexcept { return this->mem; }
		__LL_NODISCARD__ constexpr operator const T* () const noexcept { return this->mem; }

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

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_QWERTY_EXTRA_HPP_)
		#if LLANYLIB_QWERTY_EXTRA_MAYOR_ != 12 || LLANYLIB_QWERTY_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "qwerty.hpp(extra) version error!"
			#else
				#error "qwerty.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_QWERTY_EXTRA_MAYOR_ || LLANYLIB_QWERTY_EXTRA_MINOR_

	#else
		#define LLANYLIB_QWERTY_EXTRA_HPP_
		#define LLANYLIB_QWERTY_EXTRA_MAYOR_ 12
		#define LLANYLIB_QWERTY_EXTRA_MINOR_ 0

namespace llcpp {
namespace meta {
namespace utils {

template<class T, ll_bool_t IS_REVERSED = ::llcpp::LL_FALSE>
using ConstPointerIterator = ::llcpp::meta::utils::PointerIterator<const T, IS_REVERSED>;

} // namespace utils
} // namespace meta
} // namespace llcpp

	#endif // LLANYLIB_QWERTY_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
