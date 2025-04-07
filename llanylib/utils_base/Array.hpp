//////////////////////////////////////////////
//	Array.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ARRAY_INCOMPLETE_HPP_)
	#if LLANYLIB_ARRAY_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ARRAY_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Array.hpp(incomplete) version error!"
		#else
			#error "Array.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAY_INCOMPLETE_MAYOR_ || LLANYLIB_ARRAY_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ARRAY_INCOMPLETE_HPP_)
	#define LLANYLIB_ARRAY_INCOMPLETE_HPP_
	#define LLANYLIB_ARRAY_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ARRAY_INCOMPLETE_MINOR_ 0

#include "../types_base/ValidType.hpp"
#undef LLANYLIB_INCOMPLETE_HPP_
#include "../traits_base/traits_checker.hpp"
#define LLANYLIB_INCOMPLETE_HPP_

namespace llcpp {
namespace meta {
namespace utils {

template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
class Array;
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
class ConstArray;

template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
using Str = ::llcpp::meta::utils::Array<ll_char_t, _TYPE_CHECKER>;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
using wStr = ::llcpp::meta::utils::Array<ll_wchar_t, _TYPE_CHECKER>;

template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
using ConstStr = ::llcpp::meta::utils::ConstArray<ll_char_t, _TYPE_CHECKER>;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
using ConstwStr = ::llcpp::meta::utils::ConstArray<ll_wchar_t, _TYPE_CHECKER>;

#pragma region Builders
#pragma region Array
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER, class _T, usize _N>
__LL_NODISCARD__ constexpr Array<_T, _TYPE_CHECKER> make_Array(_T(&_array)[_N]) noexcept;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER, usize _N>
__LL_NODISCARD__ constexpr Array<ll_char_t, _TYPE_CHECKER> make_Array(const ll_char_t(&_array)[_N]) noexcept;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER, usize _N>
__LL_NODISCARD__ constexpr Array<ll_wchar_t, _TYPE_CHECKER> make_Array(const ll_wchar_t(&_array)[_N]) noexcept;

#pragma endregion
#pragma region ConstArray

template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER, class _T, usize _N>
__LL_NODISCARD__ constexpr ConstArray<_T, _TYPE_CHECKER> make_ConstArray(_T(&_array)[_N]) noexcept;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER, usize _N>
__LL_NODISCARD__ constexpr ConstArray<ll_char_t, _TYPE_CHECKER> make_ConstArray(const ll_char_t(&_array)[_N]) noexcept;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER, usize _N>
__LL_NODISCARD__ constexpr ConstArray<ll_wchar_t, _TYPE_CHECKER> make_ConstArray(const ll_wchar_t(&_array)[_N]) noexcept;
#pragma endregion

#pragma endregion

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ARRAY_HPP_)
	#if LLANYLIB_ARRAY_MAYOR_ != 12 || LLANYLIB_ARRAY_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Array.hpp version error!"
		#else
			#error "Array.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAY_MAYOR_ || LLANYLIB_ARRAY_MINOR_

#else
	#define LLANYLIB_ARRAY_HPP_
	#define LLANYLIB_ARRAY_MAYOR_ 12
	#define LLANYLIB_ARRAY_MINOR_ 0

#include "../traits_base/type_traits_extended.hpp"
#include "../traits_base/checker.hpp"
#include "Exceptions.hpp"
#include "PointerIterator.hpp"

#pragma region Macros

#define CHECK_POSITION_DEBUG_EXCEPTION \
	if constexpr (::llcpp::DEBUG || ::llcpp::EXCEPTIONS) { \
		if (!this->inRange(position)) { \
			if constexpr (::llcpp::DEBUG) \
				__debug_error_out_of_range(position, "position", this->length()); \
			if constexpr (::llcpp::EXCEPTIONS) \
				(void)LOG_EXCEPTION(::llcpp::misc::Errors::OutOfRange); \
		} \
	}

#define CHECK_POSITIONS_DEBUG_EXCEPTION \
	if constexpr (::llcpp::DEBUG || ::llcpp::EXCEPTIONS) { \
		if (!this->inRange(first)) { \
			if constexpr (::llcpp::DEBUG) \
				__debug_error_out_of_range(first, "first", this->length()); \
			if constexpr (::llcpp::EXCEPTIONS) \
				(void)LOG_EXCEPTION_TAG("first", ::llcpp::misc::Errors::OutOfRange); \
		} \
		if (!this->inRange(last)) { \
			if constexpr (::llcpp::DEBUG) \
				__debug_error_out_of_range(last, "last", this->length()); \
			if constexpr (::llcpp::EXCEPTIONS) \
				(void)LOG_EXCEPTION_TAG("last", ::llcpp::misc::Errors::OutOfRange); \
		} \
	}

#define CHECK_RESET_VALIDATION \
	if constexpr (::llcpp::DEBUG || ::llcpp::EXCEPTIONS) { \
		if (!mem) { \
			if constexpr (::llcpp::DEBUG) \
				__debug_error_not_nullptr_str("mem"); \
			if constexpr (::llcpp::EXCEPTIONS) \
				(void)LOG_EXCEPTION_TAG("mem", ::llcpp::misc::Errors::NullptrProvided); \
		} \
		if (!mem_end) { \
			if constexpr (::llcpp::DEBUG) \
				__debug_error_not_nullptr_str("mem_end"); \
			if constexpr (::llcpp::EXCEPTIONS) \
				(void)LOG_EXCEPTION_TAG("mem_end", ::llcpp::misc::Errors::NullptrProvided); \
		} \
		if (mem > mem_end) { \
			if constexpr (::llcpp::DEBUG) \
				__debug_error_begin_smaller("mem > mem_end", mem, mem_end); \
			if constexpr (::llcpp::EXCEPTIONS) \
				(void)LOG_EXCEPTION_TAG("mem > mem_end", ::llcpp::misc::Errors::NullptrProvided); \
		} \
	}

#pragma endregion

namespace llcpp {
namespace meta {
namespace utils {

template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
class Array;

template<class _T,
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PAV
>
class ConstArray {
	#pragma region Types
	public:
		// Class related
		using _MyType	= ConstArray;
		using Array		= ::llcpp::meta::utils::Array<_T, _TYPE_CHECKER>;

		// Types
		using T					= _T;
		using type				= T;
		using value_type		= T;
		using const_reference	= ::llcpp::meta::traits::cinput<T>;
		using const_pointer		= const T*;
		using const_iterator	= const_pointer;
		using const_riterator	= ::llcpp::meta::utils::PointerIterator<const T, ::llcpp::TRUE>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = _TYPE_CHECKER;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<T, TYPE_CHECKER>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Attributes
	private:
		const_pointer mem;
		const_pointer mem_end;

	#pragma endregion
	#pragma region Functions
		#pragma region Private
	private:
		constexpr void simpleClear() noexcept {
			this->setMem(::llcpp::NULL_VALUE<decltype(this->mem)>);
			this->setMemEnd(::llcpp::NULL_VALUE<decltype(this->mem_end)>);
		}
		constexpr void setMem(const_pointer mem) noexcept { this->mem = mem; }
		constexpr void setMemEnd(const_pointer mem_end) noexcept { this->mem_end = mem_end; }

		#pragma endregion
		#pragma region Constructors
	public:
		constexpr ConstArray() noexcept
			: mem(::llcpp::NULL_VALUE<T>)
			, mem_end(::llcpp::NULL_VALUE<T>)
		{}
		explicit constexpr ConstArray(const_pointer mem, const_pointer mem_end) noexcept
			: mem(mem)
			, mem_end(mem_end)
		{}
		explicit constexpr ConstArray(const_pointer mem, const usize len) noexcept
			: ConstArray(mem, mem + len)
		{}
		template<usize N>
		explicit constexpr ConstArray(const T (&v)[N]) noexcept
			: ConstArray(v, v + N)
		{}
		constexpr ~ConstArray() noexcept {
			if constexpr (::llcpp::CLEAR_POINTERS_ON_DESTRUCTION)
				this->simpleClear();
		}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ConstArray(const ConstArray& other) noexcept
			: ConstArray(other.mem, other.mem_end)
		{}
		constexpr ConstArray& operator=(const ConstArray& other) noexcept {
			this->setMem(other.begin());
			this->setMemEnd(other.end());
			return *this;
		}
		constexpr ConstArray(ConstArray&& other) noexcept
			: ConstArray(other.mem, other.mem_end)
		{ other.simpleClear(); }
		constexpr ConstArray& operator=(ConstArray&& other) noexcept {
			this->setMem(other.begin());
			this->setMemEnd(other.end());
			other.simpleClear();
			return *this;
		}

		constexpr ConstArray(const Array& other) noexcept;
		constexpr ConstArray& operator=(const Array& other) noexcept;
		constexpr ConstArray(Array&& other) noexcept;
		constexpr ConstArray& operator=(Array&& other) noexcept;

		constexpr ConstArray(volatile const ConstArray& other) noexcept = delete;
		constexpr ConstArray& operator=(volatile const ConstArray& other) noexcept = delete;
		constexpr ConstArray(volatile ConstArray&& other) noexcept = delete;
		constexpr ConstArray& operator=(volatile ConstArray&& other) noexcept = delete;

		constexpr ConstArray(volatile const Array& other) noexcept = delete;
		constexpr ConstArray& operator=(volatile const Array& other) noexcept = delete;
		constexpr ConstArray(volatile Array&& other) noexcept = delete;
		constexpr ConstArray& operator=(volatile Array&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const ConstArray*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator ConstArray*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
	public:
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr const_pointer get(const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return this->begin() + position;
		}
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr ConstArray get(const usize first, const usize last) const noexcept {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return ConstArray(this->get(first), this->get(last));
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr const_riterator rget(const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return this->rend() + position;
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr ConstArray substr(const usize first, const usize last) const noexcept {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return this->get(first, last);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr const_reference operator[](const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return *this->get(position);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		// Non-standard operator
		__LL_NODISCARD__ constexpr const_reference operator^(const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return *this->rget(position);
		}
#if __LL_REAL_CXX23 == 1
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr ConstArray operator[](const usize first, const usize last) const noexcept {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return this->substr(first, last);
		}

#endif // __LL_REAL_CXX23

		#pragma endregion
		#pragma region Countable
	public:
		__LL_NODISCARD__ constexpr usize lenght() const noexcept {
			return static_cast<usize>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr usize size() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr usize count() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr ll_bool_t inRange(const usize position) const noexcept {
			return position < this->lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t inRange(const_pointer data) const noexcept {
			return this->begin() <= data && data <= this->end();
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const usize position) const noexcept {
			return this->inRange(position);
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const_pointer data) const noexcept {
			return this->inRange(data);
		}

		#pragma endregion
		#pragma region std
	public:
		__LL_NODISCARD__ constexpr const_pointer data() const noexcept { return this->mem; }
		__LL_NODISCARD__ constexpr const_iterator begin() const noexcept { return this->data(); }
		__LL_NODISCARD__ constexpr const_iterator end() const noexcept { return this->mem_end; }

		__LL_NODISCARD__ constexpr const_iterator rbegin() const noexcept { return this->mem - 1; }
		__LL_NODISCARD__ constexpr const_riterator rend() const noexcept { return this->mem_end; }
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			return this->begin() == this->end();
		}

		#pragma endregion
		#pragma region Other
	public:
		__LL_NODISCARD__ constexpr ::llcpp::meta::ValidType validationType() const noexcept {
			return this->begin() <= this->end() ? ::llcpp::meta::ValidType::Valid : ::llcpp::meta::ValidType::Invalid;
		}
		constexpr void clear() noexcept { this->simpleClear(); }
		__LL_NODISCARD__ constexpr ll_bool_t resetValidation(const_pointer mem, const_pointer mem_end) noexcept {
			CHECK_RESET_VALIDATION;
			this->setMem(mem);
			this->setMemEnd(mem_end);
		}

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

template<
	class _T,
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PAV
>
class Array {
	#pragma region Types
	public:
		// Class related
		using _MyType	= Array;
		using ConstArray = ::llcpp::meta::utils::ConstArray<_T, _TYPE_CHECKER>;

		// Types
		using T					= _T;
		using type				= T;
		using value_type		= T;
		using reference			= ::llcpp::meta::traits::input<T>;
		using const_reference	= ::llcpp::meta::traits::cinput<T>;
		using pointer			= T*;
		using const_pointer		= const T*;
		using iterator			= pointer;
		using riterator			= ::llcpp::meta::utils::PointerIterator<T, ::llcpp::TRUE>;
		using const_iterator	= const_pointer;
		using const_riterator	= ::llcpp::meta::utils::PointerIterator<const T, ::llcpp::TRUE>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = _TYPE_CHECKER;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<T, TYPE_CHECKER>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Attributes
	private:
		pointer mem;
		pointer mem_end;

	#pragma endregion
	#pragma region Functions
		#pragma region Functions
	private:
		constexpr void simpleClear() noexcept {
			this->setMem(::llcpp::NULL_VALUE<decltype(this->mem)>);
			this->setMemEnd(::llcpp::NULL_VALUE<decltype(this->mem_end)>);
		}
		constexpr void setMem(const_pointer mem) noexcept { this->mem = const_cast<pointer>(mem); }
		constexpr void setMemEnd(const_pointer mem_end) noexcept { this->mem_end = const_cast<pointer>(mem_end); }

		#pragma endregion
		#pragma region Constructors
	public:
		constexpr Array() noexcept = delete;
		constexpr Array(T* mem, T* mem_end) noexcept
			: mem(mem)
			, mem_end(mem_end)
		{}
		constexpr Array(T* mem, const usize len) noexcept
			: Array(mem, mem + len)
		{}
		template<usize N>
		explicit constexpr Array(T(&v)[N]) noexcept
			: Array(v, v + N)
		{}
		constexpr ~Array() noexcept {
			if constexpr (::llcpp::CLEAR_POINTERS_ON_DESTRUCTION)
				this->simpleClear();
		}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Array(const Array& other) noexcept
			: Array(other.mem, other.mem_end)
		{}
		constexpr Array& operator=(const Array& other) noexcept {
			this->setMem(other.begin());
			this->setMemEnd(other.end());
			return *this;
		}
		constexpr Array(Array&& other) noexcept
			: Array(other)
		{ other.simpleClear(); }
		constexpr Array& operator=(Array&& other) noexcept {
			this->setMem(other.begin());
			this->setMemEnd(other.end());
			other.simpleClear();
			return *this;
		}

		constexpr Array(volatile const Array& other) noexcept = delete;
		constexpr Array& operator=(volatile const Array& other) noexcept = delete;
		constexpr Array(volatile Array&& other) noexcept = delete;
		constexpr Array& operator=(volatile Array&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Array* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Array* () noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator ConstArray() const noexcept {
			return ConstArray(*this);
		}
		__LL_NODISCARD__ constexpr ConstArray operator()() const noexcept {
			return this->operator ConstArray();
		}
		__LL_NODISCARD__ constexpr ConstArray to_ConstArray() const noexcept {
			return this->operator ConstArray();
		}

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
	public:
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr pointer get(const usize position) noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return this->begin() + position;
		}
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr const_pointer get(const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return this->begin() + position;
		}
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr Array get(const usize first, const usize last) noexcept {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return Array(this->get(first), this->get(last));
		}
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr ConstArray get(const usize first, const usize last) const noexcept {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return ConstArray(this->get(first), this->get(last));
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr riterator rget(const usize position) noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return this->rend() + position;
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr const_riterator rget(const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return this->rend() + position;
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr Array substr(const usize first, const usize last) noexcept {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return this->get(first, last);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr ConstArray substr(const usize first, const usize last) const noexcept {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return this->get(first, last);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr reference operator[](const usize position) noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return *this->get(position);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr const_reference operator[](const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return *this->get(position);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		// Non-standard operator
		__LL_NODISCARD__ constexpr reference operator^(const usize position) noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return *this->rget(position);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		// Non-standard operator
		__LL_NODISCARD__ constexpr const_reference operator^(const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return *this->rget(position);
		}
#if __LL_REAL_CXX23 == 1
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr Array operator[](const usize first, const usize last) noexcept {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return this->substr(first, last);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr ConstArray operator[](const usize first, const usize last) const noexcept {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return this->substr(first, last);
		}

#endif // __LL_REAL_CXX23

		#pragma endregion
		#pragma region Countable
	public:
		__LL_NODISCARD__ constexpr usize lenght() const noexcept {
			return static_cast<usize>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr usize size() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr usize count() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr ll_bool_t inRange(const usize position) const noexcept {
			return position < this->lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t inRange(const_pointer data) const noexcept {
			return this->begin() <= data && data <= this->end();
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const usize position) const noexcept {
			return this->inRange(position);
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const_pointer data) const noexcept {
			return this->inRange(data);
		}

		#pragma endregion
		#pragma region std
	public:
		__LL_NODISCARD__ constexpr pointer data() noexcept { return this->mem; }
		__LL_NODISCARD__ constexpr const_pointer data() const noexcept { return this->mem; }
		__LL_NODISCARD__ constexpr iterator begin() noexcept { return this->data(); }
		__LL_NODISCARD__ constexpr const_iterator begin() const noexcept { return this->data(); }
		__LL_NODISCARD__ constexpr iterator end() noexcept { return this->mem_end; }
		__LL_NODISCARD__ constexpr const_iterator end() const noexcept { return this->mem_end; }

		__LL_NODISCARD__ constexpr iterator rbegin() noexcept { return this->data(); }
		__LL_NODISCARD__ constexpr const_iterator rbegin() const noexcept { return this->data(); }
		__LL_NODISCARD__ constexpr riterator rend() noexcept { return this->mem_end; }
		__LL_NODISCARD__ constexpr const_riterator rend() const noexcept { return this->mem_end; }
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept { return this->begin() == this->end(); }

		#pragma endregion
		#pragma region Other
	public:
		__LL_NODISCARD__ constexpr ::llcpp::meta::ValidType validationType() const noexcept {
			return this->begin() <= this->end() ? ::llcpp::meta::ValidType::Valid : ::llcpp::meta::ValidType::Invalid;
		}
		constexpr void clear() noexcept { this->simpleClear(); }
		constexpr void makeInvalid() noexcept { this->simpleClear(); }
		constexpr void setMem(pointer mem) noexcept { this->mem = mem; }
		constexpr void setMemEnd(pointer mem_end) noexcept { this->mem_end = mem_end; }
		__LL_NODISCARD__ constexpr ll_bool_t resetValidation(pointer mem, pointer mem_end) noexcept {
			CHECK_RESET_VALIDATION;
			this->setMem(mem);
			this->setMemEnd(mem_end);
		}

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

#pragma region Array_ConstArray_Compatibility
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
__LL_INLINE__ constexpr ::llcpp::meta::utils::ConstArray<_T, _TYPE_CHECKER>::ConstArray(const Array& other) noexcept
	: mem(other.begin()), mem_end(other.end()) {}
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
__LL_INLINE__ constexpr ::llcpp::meta::utils::ConstArray<_T, _TYPE_CHECKER>& ::llcpp::meta::utils::ConstArray<_T, _TYPE_CHECKER>::operator=(const Array& other) noexcept {
	this->setMem(other.begin());
	this->setMemEnd(other.end());
	return *this;
}
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
__LL_INLINE__ constexpr ::llcpp::meta::utils::ConstArray<_T, _TYPE_CHECKER>::ConstArray(Array&& other) noexcept
	: mem(other.begin()), mem_end(other.end())
{
	// This is valid wile clear calls only simpleClear
	other.clear();
}
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
__LL_INLINE__ constexpr ::llcpp::meta::utils::ConstArray<_T, _TYPE_CHECKER>& ::llcpp::meta::utils::ConstArray<_T, _TYPE_CHECKER>::operator=(Array&& other) noexcept {
	this->setMem(other.begin());
	this->setMemEnd(other.end());
	// This is valid wile clear calls only simpleClear
	other.clear();
	return *this;
}

#pragma endregion
#pragma region StringTypes
template<::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = ::llcpp::meta::attributes::checker::IGNORE_PA>
using Str = ::llcpp::meta::utils::Array<ll_char_t, TYPE_CHECKER>;
template<::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = ::llcpp::meta::attributes::checker::IGNORE_PA>
using wStr = ::llcpp::meta::utils::Array<ll_wchar_t, TYPE_CHECKER>;

template<::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = ::llcpp::meta::attributes::checker::IGNORE_PA>
using ConstStr = ::llcpp::meta::utils::ConstArray<ll_char_t, TYPE_CHECKER>;
template<::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = ::llcpp::meta::attributes::checker::IGNORE_PA>
using ConstwStr = ::llcpp::meta::utils::ConstArray<ll_wchar_t, TYPE_CHECKER>;

namespace traits {

template<class T, ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = ::llcpp::meta::attributes::checker::IGNORE_PA>
__LL_VAR_INLINE__ constexpr ll_bool_t is_string_type_v =
	::std::_Is_any_of_v<
		T,
		::llcpp::meta::utils::ConstStr<TYPE_CHECKER>,
		::llcpp::meta::utils::ConstwStr<TYPE_CHECKER>
	>;

template<class T, ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = ::llcpp::meta::attributes::checker::IGNORE_PA>
__LL_VAR_INLINE__ constexpr ll_bool_t is_str_type_v =
	::std::_Is_any_of_v<
		T,
		::llcpp::meta::utils::Str<TYPE_CHECKER>,
		::llcpp::meta::utils::wStr<TYPE_CHECKER>
	>;

// [TODO]
/*template<class T>
using ArrayWrapper = traits::conditional_t<
	::std::is_array_v<T>,
	meta::Array<traits::array_type_t<T>>,
	T
>;*/

} // namespace traits

#pragma endregion
#pragma region Builders
#pragma region Array
template<
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PA,
	class _T, usize _N
>
__LL_NODISCARD__ constexpr Array<_T, _TYPE_CHECKER> make_Array(_T(&_array)[_N]) noexcept {
	return Array<_T, _TYPE_CHECKER>(_array, _array + _N);
}
template<
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
	::llcpp::meta::attributes::checker::IGNORE_PA,
	class _T, usize _N
>
__LL_NODISCARD__ constexpr ConstArray<_T, _TYPE_CHECKER> make_ConstArray(const _T(&_array)[_N]) noexcept {
	return ConstArray<_T, _TYPE_CHECKER>(_array, _array + _N);
}

#pragma endregion
#pragma region String
template<
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PA,
	class _T, usize _N
>
__LL_NODISCARD__ constexpr ::llcpp::meta::utils::Str<_TYPE_CHECKER> make_String(ll_char_t(&_array)[_N]) noexcept {
	return ::llcpp::meta::utils::Str<_TYPE_CHECKER>(_array, _array + _N - 1);
}
template<
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PA,
	class _T, usize _N
>
__LL_NODISCARD__ constexpr ::llcpp::meta::utils::wStr<_TYPE_CHECKER> make_String(ll_wchar_t(&_array)[_N]) noexcept {
	return ::llcpp::meta::utils::wStr<_TYPE_CHECKER>(_array, _array + _N - 1);
}

#pragma endregion
#pragma region ConstString
template<
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PA,
	class _T, usize _N
>
__LL_NODISCARD__ constexpr ::llcpp::meta::utils::Str<_TYPE_CHECKER> make_ConstString(const ll_char_t(&_array)[_N]) noexcept {
	return ::llcpp::meta::utils::ConstStr<_TYPE_CHECKER>(_array, _array + _N - 1);
}
template<
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PA,
	class _T, usize _N
>
__LL_NODISCARD__ constexpr ::llcpp::meta::utils::wStr<_TYPE_CHECKER> make_ConstString(const ll_wchar_t(&_array)[_N]) noexcept {
	return ::llcpp::meta::utils::ConstwStr<_TYPE_CHECKER>(_array, _array + _N - 1);
}

#pragma endregion

#pragma endregion

#undef CHECK_POSITION_DEBUG_EXCEPTION
#undef CHECK_POSITIONS_DEBUG_EXCEPTION
#undef CHECK_RESET_VALIDATION

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAY_HPP_
