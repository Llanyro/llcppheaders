//////////////////////////////////////////////
//	ArrayBase.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ARRAYBASE_INCOMPLETE_HPP_)
	#if LLANYLIB_ARRAYBASE_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ARRAYBASE_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "ArrayBase.hpp(incomplete) version error!"
		#else
			#error "ArrayBase.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAYBASE_INCOMPLETE_MAYOR_ || LLANYLIB_ARRAYBASE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ARRAYBASE_INCOMPLETE_HPP_)
	#define LLANYLIB_ARRAYBASE_INCOMPLETE_HPP_
	#define LLANYLIB_ARRAYBASE_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ARRAYBASE_INCOMPLETE_MINOR_ 0

#include <llanylib/traits_base/checker.hpp>
#include <llanylib/utils/Tuple.hpp>
#include <llanylib/utils/PointerIterator.hpp>
#include <llanylib/utils/Exceptions.hpp>

namespace llcpp {
namespace meta {
namespace utils {

template<
	class _T,
	ll_bool_t _ENABLE_NO_CONST		= ::llcpp::LL_TRUE,				// Enables no const functions to edit array
	ll_bool_t _USE_OBJECT_ITERATOR	= ::llcpp::LL_FALSE,			// Uses PointerIterator instead pointers
	usize _N						= ::llcpp::ZERO_VALUE<usize>,	// Store array size/store en array pointer
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_CPAV
>
class ArrayBase;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ARRAYBASE_HPP_)
	#if LLANYLIB_ARRAYBASE_MAYOR_ != 12 || LLANYLIB_ARRAYBASE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "ArrayBase.hpp version error!"
		#else
			#error "ArrayBase.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAYBASE_MAYOR_ || LLANYLIB_ARRAYBASE_MINOR_

#else
	#define LLANYLIB_ARRAYBASE_HPP_
	#define LLANYLIB_ARRAYBASE_MAYOR_ 12
	#define LLANYLIB_ARRAYBASE_MINOR_ 0

#include <llanylib/traits_base/checker.hpp>
#include <llanylib/utils/Tuple.hpp>
#include <llanylib/utils/PointerIterator.hpp>
#include <llanylib/utils/Exceptions.hpp>

#define CHECK_RESET_VALIDATION_1(mem)																	\
	if constexpr (::llcpp::LL_DEBUG || ::llcpp::LL_EXCEPTIONS) {										\
		if (!mem) {																						\
			if constexpr (::llcpp::LL_DEBUG)															\
				__debug_error_not_nullptr_str("mem");													\
			if constexpr (::llcpp::LL_EXCEPTIONS)														\
				(void)LOG_EXCEPTION_TAG("mem", ::llcpp::misc::Errors::NullptrProvided);					\
		}																								\
	}

#define CHECK_RESET_VALIDATION_2(mem, mem_end)															\
	if constexpr (::llcpp::LL_DEBUG || ::llcpp::LL_EXCEPTIONS) {										\
		if (!mem) {																						\
			if constexpr (::llcpp::LL_DEBUG)															\
				__debug_error_not_nullptr_str("mem");													\
			if constexpr (::llcpp::LL_EXCEPTIONS)														\
				(void)LOG_EXCEPTION_TAG("mem", ::llcpp::misc::Errors::NullptrProvided);					\
		}																								\
		if constexpr (!SIZED_ARRAY) {																	\
			if (!mem_end) {																				\
				if constexpr (::llcpp::LL_DEBUG)														\
					__debug_error_not_nullptr_str("mem_end");											\
				if constexpr (::llcpp::LL_EXCEPTIONS)													\
					(void)LOG_EXCEPTION_TAG("mem_end", ::llcpp::misc::Errors::NullptrProvided);			\
			}																							\
			if (mem > mem_end) {																		\
				if constexpr (::llcpp::LL_DEBUG)														\
					__debug_error_begin_smaller("mem > mem_end", mem, mem_end);							\
				if constexpr (::llcpp::LL_EXCEPTIONS)													\
					(void)LOG_EXCEPTION_TAG("mem > mem_end", ::llcpp::misc::Errors::NullptrProvided);	\
			}																							\
		}																								\
	}

namespace llcpp {
namespace meta {
namespace utils {

template<
	class _T,
	ll_bool_t _ENABLE_NO_CONST		= ::llcpp::LL_TRUE,				// Enables no const functions to edit array
	ll_bool_t _USE_OBJECT_ITERATOR	= ::llcpp::LL_FALSE,			// Uses PointerIterator instead pointers
	usize _N						= ::llcpp::ZERO_VALUE<usize>,	// Store array size/store en array pointer
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_CPAV
>
class ArrayBase {
	#pragma region Types
	public:
		// Class related
		using _MyType		= ArrayBase;
		template<ll_bool_t __USE_OBJECT_ITERATOR, usize __N>
		using ArrayItSize	= ArrayBase<_T, _ENABLE_NO_CONST, __USE_OBJECT_ITERATOR, __N, _TYPE_CHECKER>;

		template<class U>
		using contain_value_type =
			typename ::llcpp::meta::utils::ArrayBase<U, _ENABLE_NO_CONST, _USE_OBJECT_ITERATOR, _N, _TYPE_CHECKER>;

		// Types
		using T					= _T;
		using type				= T;
		using value_type		= T;

		//using reference			= ::llcpp::meta::traits::input<T>;
		using iterator			= ::llcpp::meta::traits::conditional_t<
			_USE_OBJECT_ITERATOR,
			::llcpp::meta::utils::PointerIterator<T, ::llcpp::LL_FALSE>,
			T*
		>;
		using riterator			= ::llcpp::meta::utils::PointerIterator<T, ::llcpp::LL_TRUE>;

		//using const_reference	= ::llcpp::meta::traits::cinput<T>;
		using const_iterator = ::llcpp::meta::traits::conditional_t<
			_USE_OBJECT_ITERATOR,
			::llcpp::meta::utils::ConstPointerIterator<T, ::llcpp::LL_FALSE>,
			const T*
		>;
		using reference_const_iterator = ::llcpp::meta::traits::conditional_t<
			_USE_OBJECT_ITERATOR,
			const_iterator&,
			const_iterator
		>;
		using const_riterator	= ::llcpp::meta::utils::ConstPointerIterator<T, ::llcpp::LL_TRUE>;

		using default_iterator = ::llcpp::meta::traits::conditional_t<
			_ENABLE_NO_CONST,
			iterator,
			const_iterator
		>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = _TYPE_CHECKER;
		static constexpr ll_bool_t USE_OBJECT_ITERATOR	= _USE_OBJECT_ITERATOR;
		static constexpr ll_bool_t ENABLE_NO_CONST		= _ENABLE_NO_CONST;
		static constexpr usize N						= _N;
		static constexpr ll_bool_t SIZED_ARRAY			= _N > 0;

	#pragma endregion
	#pragma region TypesExtra
	public:
		using mem_end_type	= ::llcpp::meta::traits::conditional_t<SIZED_ARRAY, ::llcpp::Emptyclass, default_iterator>;
		using ArrayTypes	= ::llcpp::meta::utils::Tuple<default_iterator, mem_end_type>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<_MyType::T, _MyType::TYPE_CHECKER>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Attributes
	private:
		ArrayTypes memory;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr ArrayBase() noexcept requires(SIZED_ARRAY)
			: memory(::llcpp::ZERO_VALUE<default_iterator>)
		{}
		constexpr ArrayBase() noexcept requires(!SIZED_ARRAY)
			: memory(::llcpp::ZERO_VALUE<default_iterator>, ::llcpp::ZERO_VALUE<default_iterator>)
		{}
		constexpr ArrayBase(default_iterator mem) noexcept requires(SIZED_ARRAY)
			: memory(mem)
		{}
		constexpr ArrayBase(default_iterator mem, default_iterator mem_end) noexcept requires(!SIZED_ARRAY)
			: memory(mem, mem_end)
		{}
		constexpr ArrayBase(default_iterator mem, const usize len) noexcept requires(!SIZED_ARRAY)
			: memory(mem, mem + len)
		{}
		template<usize N>
		constexpr ArrayBase(default_iterator (&v)[N]) noexcept requires(!SIZED_ARRAY)
			: memory(v, v + N)
		{}
		template<usize N>
		constexpr ArrayBase& operator=(default_iterator (&v)[N]) noexcept {
			this->reset(v);
			return *this;
		}
		constexpr ~ArrayBase() noexcept {
			if constexpr (::llcpp::LL_CLEAR_POINTERS_ON_DESTRUCTION)
				this->makeInvalid();
		}

		#pragma endregion
		#pragma region CopyMove
	public:
		// [TOCHECK] [TODO] [TOFIX]
		constexpr ArrayBase(const ArrayBase& other) noexcept
			: memory(::std::forward<const ArrayTypes&>(other.memory))
		{}
		// [TOCHECK] [TODO] [TOFIX]
		constexpr ArrayBase& operator=(const ArrayBase& other) noexcept {
			this->memory = ::std::forward<const ArrayTypes&>(other.memory);
			return *this;
		}
		constexpr ArrayBase(ArrayBase&& other) noexcept
			: ArrayBase(::std::forward<ArrayTypes&&>(other.memory))
		{ other.makeInvalid(); }
		constexpr ArrayBase& operator=(ArrayBase&& other) noexcept {
			this->memory = ::std::forward<ArrayTypes&&>(other.memory);
			other.makeInvalid();
			return *this;
		}

		/*// For arrays with differnte props
		// [TOCHECK] [TODO] [TOFIX]
		template<ll_bool_t __USE_OBJECT_ITERATOR, usize __N>
		constexpr ArrayBase(const ArrayItSize<__USE_OBJECT_ITERATOR, __N>& other) noexcept requires(SIZED_ARRAY)
			: ArrayBase(other.begin())
		{}
		template<ll_bool_t __USE_OBJECT_ITERATOR, usize __N>
		constexpr ArrayBase(const ArrayItSize<__USE_OBJECT_ITERATOR, __N>& other) noexcept requires(!SIZED_ARRAY)
			: ArrayBase(other.begin(), other.end())
		{}
		// [TOCHECK] [TODO] [TOFIX]
		template<ll_bool_t __USE_OBJECT_ITERATOR, usize __N>
		constexpr ArrayBase& operator=(const ArrayItSize<__USE_OBJECT_ITERATOR, __N>& other) noexcept {
			if constexpr (SIZED_ARRAY)
				this->memory = other.begin();
			else this->memory = ArrayTypes(other.begin(), other.end());
			return *this;
		}
		template<ll_bool_t __USE_OBJECT_ITERATOR, usize __N>
		constexpr ArrayBase(ArrayItSize<__USE_OBJECT_ITERATOR, __N>&& other) noexcept
			: ArrayBase(::std::forward<ArrayTypes&&>(other.memory))
		{ other.makeInvalid(); }
		template<ll_bool_t __USE_OBJECT_ITERATOR, usize __N>
		constexpr ArrayBase& operator=(ArrayItSize<__USE_OBJECT_ITERATOR, __N>&& other) noexcept {
			this->memory = ::std::forward<ArrayTypes&&>(other.memory);
			other.makeInvalid();
			return *this;
		}

		template< ll_bool_t __USE_OBJECT_ITERATOR = USE_OBJECT_ITERATOR, usize __N = N>
		constexpr ArrayBase(ArrayBase<T, ENABLE_NO_CONST, __USE_OBJECT_ITERATOR, __N, TYPE_CHECKER>&& other) noexcept requires(SIZED_ARRAY)
			: ArrayBase(other.begin())
		{ other.makeInvalid(); }
		template< ll_bool_t __USE_OBJECT_ITERATOR = USE_OBJECT_ITERATOR, usize __N = N>
		constexpr ArrayBase(ArrayBase<T, ENABLE_NO_CONST, __USE_OBJECT_ITERATOR, __N, TYPE_CHECKER>&& other) noexcept requires(!SIZED_ARRAY)
			: ArrayBase(other.begin(), other.end())
		{ other.makeInvalid(); }
		template< ll_bool_t __USE_OBJECT_ITERATOR = USE_OBJECT_ITERATOR, usize __N = N>
		constexpr ArrayBase& operator=(ArrayBase<T, ENABLE_NO_CONST, __USE_OBJECT_ITERATOR, __N, TYPE_CHECKER>&& other) noexcept {
			if constexpr (SIZED_ARRAY) this->resetValidation(other.begin());
			else this->resetValidation(other.begin() other.end());
			other.makeInvalid();
			return *this;
		}*/

		constexpr ArrayBase(const volatile ArrayBase& other) noexcept = delete;
		constexpr ArrayBase& operator=(const volatile ArrayBase& other) noexcept = delete;
		constexpr ArrayBase(volatile ArrayBase&& other) noexcept = delete;
		constexpr ArrayBase& operator=(volatile ArrayBase&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const ArrayBase*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator ArrayBase*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region std
	public:
		__LL_NODISCARD__ constexpr iterator data() noexcept requires(ENABLE_NO_CONST) { return this->memory.getFirst(); }
		__LL_NODISCARD__ constexpr const_iterator data() const noexcept { return this->memory.getFirst(); }

		__LL_NODISCARD__ constexpr iterator begin() noexcept requires(ENABLE_NO_CONST) { return this->data(); }
		__LL_NODISCARD__ constexpr const_iterator begin() const noexcept { return this->data(); }

		__LL_NODISCARD__ constexpr iterator end() noexcept requires(ENABLE_NO_CONST) {
			if constexpr (SIZED_ARRAY)
				return this->begin() + this->size();
			else return this->memory.getSecond().getFirst();
		}
		__LL_NODISCARD__ constexpr const_iterator end() const noexcept {
			if constexpr (SIZED_ARRAY)
				return this->begin() + this->size();
			else return this->memory.getSecond().getFirst();
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			if constexpr (SIZED_ARRAY)
				return this->size() == ::llcpp::ZERO_VALUE<decltype(this->size())>;
			else return this->begin() == this->end();
		}

		#pragma endregion
		#pragma region Countable
	public:
		__LL_NODISCARD__ constexpr usize size() const noexcept {
			if constexpr (SIZED_ARRAY) return _MyType::N;
			else return static_cast<usize>(this->end() - this->begin());
		}

		#pragma endregion
		#pragma region Other
	protected:
		// Does not include reset
		template<class ExtraCleaner>
		constexpr void clearPriv(const ExtraCleaner& extra) noexcept {
			::llcpp::meta::utils::Cleaner cleaner;
			(void)cleaner.process(this->begin(), this->end(), extra);
		}

	public:
		__LL_NODISCARD__ constexpr ::llcpp::misc::ValidType validationType() const noexcept {
			return this->begin() <= this->end() ? ::llcpp::misc::ValidType::Valid : ::llcpp::misc::ValidType::Invalid;
		}
		__LL_NODISCARD__ constexpr ll_bool_t reset(default_iterator mem) noexcept requires(SIZED_ARRAY) {
			CHECK_RESET_VALIDATION_1(mem);
			this->memory.getFirst() = mem;
			return ::llcpp::LL_TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t reset(default_iterator mem, default_iterator mem_end) noexcept requires(!SIZED_ARRAY) {
			CHECK_RESET_VALIDATION_2(mem, mem_end);
			this->memory.getFirst() = mem;
			this->memory.getSecond().getFirst() = mem_end;
			return ::llcpp::LL_TRUE;
		}
		template<usize N>
		__LL_NODISCARD__ constexpr ll_bool_t reset(default_iterator (&v)[N]) noexcept {
			this->memory.getFirst() = v;
			if constexpr (!SIZED_ARRAY) this->memory.getSecond().getFirst() = (v + N);
			return ::llcpp::LL_TRUE;
		}
		// Clears buffers data and reset class
		template<class ExtraCleaner = ::llcpp::meta::utils::Cleaner>
		constexpr void clear() noexcept {
			ExtraCleaner extra;
			this->clear(extra);
		}
		// Clears buffers data and reset class with a provided class
		template<class ExtraCleaner = ::llcpp::meta::utils::Cleaner>
		constexpr void clear(const ExtraCleaner& extra) noexcept {
			this->clearPriv(extra);
		}
		// Invalidates iterators of fifo
		template<class ExtraInvalidator>
		constexpr void makeInvalid() noexcept {
			ExtraInvalidator extra;
			this->makeInvalid(extra);
		}
		// Invalidates iterators of fifo with a provided class
		template<class ExtraInvalidator>
		constexpr void makeInvalid(const ExtraInvalidator& extra) noexcept {
			::llcpp::meta::utils::Invalidator invalidator;
			(void)invalidator.process(this->memory.getFirst(), extra);
			if constexpr (SIZED_ARRAY)
				(void)invalidator.process(this->memory.getSecond().getFirst(), extra);
		}
		// Invalidates iterators and objects of fifo
		template<class ExtraInvalidatorCleaner>
		constexpr void makeInvalidClear() noexcept {
			ExtraInvalidatorCleaner extra;
			this->makeInvalidClear(extra);
		}
		// Invalidates iterators and objects of fifo
		template<class ExtraInvalidatorCleaner>
		constexpr void makeInvalidClear(const ExtraInvalidatorCleaner& extra) noexcept {
			this->clearPriv(extra);
			this->makeInvalid(extra);
		}

		__LL_NODISCARD__ constexpr ll_bool_t inRange(const usize position) const noexcept {
			return position < this->size();
		}
		__LL_NODISCARD__ constexpr ll_bool_t inRange(reference_const_iterator data) const noexcept {
			if constexpr (SIZED_ARRAY)
				return static_cast<usize>(data - this->begin()) < this->size();
			else return this->begin() <= data && data <= this->end();
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const usize position) const noexcept {
			return this->inRange(position);
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(reference_const_iterator data) const noexcept {
			return this->inRange(data);
		}

		#pragma endregion
		#pragma endregion

	#pragma endregion
};

#define ARR_PREP(arr) (arr, arr + ::llcpp::array_size<decltype(arr)>)
#define ARR_PREP_SIZE(arr) (arr, ::llcpp::array_size<decltype(arr)>)

} // namespace utils
} // namespace meta
} // namespace llcpp

#undef CHECK_RESET_VALIDATION_1
#undef CHECK_RESET_VALIDATION_2

#endif // LLANYLIB_ARRAYBASE_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_ARRAYBASE_EXTRA_HPP_)
		#if LLANYLIB_ARRAYBASE_EXTRA_MAYOR_ != 12 || LLANYLIB_ARRAYBASE_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "qwerty.hpp(extra) version error!"
			#else
				#error "qwerty.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_ARRAYBASE_EXTRA_MAYOR_ || LLANYLIB_ARRAYBASE_EXTRA_MINOR_

	#else
		#define LLANYLIB_ARRAYBASE_EXTRA_HPP_
		#define LLANYLIB_ARRAYBASE_EXTRA_MAYOR_ 12
		#define LLANYLIB_ARRAYBASE_EXTRA_MINOR_ 0

namespace llcpp {
namespace meta {
namespace utils {

template<class T, ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using Array = ::llcpp::meta::utils::ArrayBase<T, ::llcpp::LL_TRUE, USE_OBJECT_ITERATOR, N>;
template<class T, ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using ConstArray = ::llcpp::meta::utils::ArrayBase<T, ::llcpp::LL_FALSE, USE_OBJECT_ITERATOR, N>;

// Ascii char string
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using Str = ::llcpp::meta::utils::Array<ll_char_t, USE_OBJECT_ITERATOR, N>;
// uString
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using uStr = ::llcpp::meta::utils::Array<ll_uchar_t, USE_OBJECT_ITERATOR, N>;
// Wide char string
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using wStr = ::llcpp::meta::utils::Array<ll_wchar_t, USE_OBJECT_ITERATOR, N>;
// String 16 bit char
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using Str16 = ::llcpp::meta::utils::Array<ll_char16_t, USE_OBJECT_ITERATOR, N>;
// String 16 bit char
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using Str32 = ::llcpp::meta::utils::Array<ll_char32_t, USE_OBJECT_ITERATOR, N>;

// Ascii char string
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using cStr = ::llcpp::meta::utils::ConstArray<ll_char_t, USE_OBJECT_ITERATOR, N>;
// uString
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using cuStr = ::llcpp::meta::utils::ConstArray<ll_uchar_t, USE_OBJECT_ITERATOR, N>;
// Wide char string
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using cwStr = ::llcpp::meta::utils::ConstArray<ll_wchar_t, USE_OBJECT_ITERATOR, N>;
// String 16 bit char
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using cStr16 = ::llcpp::meta::utils::ConstArray<ll_char16_t, USE_OBJECT_ITERATOR, N>;
// String 16 bit char
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using cStr32 = ::llcpp::meta::utils::ConstArray<ll_char32_t, USE_OBJECT_ITERATOR, N>;

// Ascii/Wide char defined by macros and OS
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using String = ::llcpp::meta::utils::Array<::llcpp::char_type, USE_OBJECT_ITERATOR, N>;
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE, usize N = ::llcpp::ZERO_VALUE<usize>>
using cString = ::llcpp::meta::utils::ConstArray<::llcpp::char_type, USE_OBJECT_ITERATOR, N>;

} // namespace utils
} // namespace meta
} // namespace llcpp

	#endif // LLANYLIB_ARRAYBASE_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
