//////////////////////////////////////////////
//	Array.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ARRAY_INCOMPLETE_HPP_)
	#if LLANYLIB_ARRAY_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_ARRAY_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Array.hpp(incomplete) version error!"
		#else
			#error "Array.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAY_INCOMPLETE_MAYOR_ || LLANYLIB_ARRAY_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ARRAY_INCOMPLETE_HPP_)
	#define LLANYLIB_ARRAY_INCOMPLETE_HPP_
	#define LLANYLIB_ARRAY_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_ARRAY_INCOMPLETE_MINOR_ 0

#undef LLANYLIB_INCOMPLETE_HPP_
#include "../traits_base/traits_checker.hpp"
#define LLANYLIB_INCOMPLETE_HPP_

namespace llcpp {
namespace meta {

template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
class Array;
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
class ConstArray;

template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
using Str = Array<ll_char_t, _TYPE_CHECKER>;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
using wStr = Array<ll_wchar_t, _TYPE_CHECKER>;

template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
using ConstStr = ConstArray<ll_char_t, _TYPE_CHECKER>;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
using ConstwStr = ConstArray<ll_wchar_t, _TYPE_CHECKER>;

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

} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ARRAY_HPP_)
	#if LLANYLIB_ARRAY_MAYOR_ != 11 || LLANYLIB_ARRAY_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Array.hpp version error!"
		#else
			#error "Array.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAY_MAYOR_ || LLANYLIB_ARRAY_MINOR_

#else
	#define LLANYLIB_ARRAY_HPP_
	#define LLANYLIB_ARRAY_MAYOR_ 11
	#define LLANYLIB_ARRAY_MINOR_ 0

#include "../traits_base/traits_checker.hpp"

namespace llcpp {
namespace meta {

template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
class Array;

template<class _T,
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PA
>
class ConstArray {
	#pragma region Types
	public:
		// Class related
		using _MyType	= ConstArray;
		using Array		= ::llcpp::meta::Array<_T, _TYPE_CHECKER>;

		// Types
		using T					= _T;
		using const_reference	= ::llcpp::meta::traits::cinput<T>;
		using const_pointer		= const T*;
		using const_iterator	= const_pointer;

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
			this->setMem(::llcpp::NULL_VALUE<const_pointer>);
			this->setMemEnd(::llcpp::NULL_VALUE<const_pointer>);
		}
		constexpr void setMem(const_pointer mem) noexcept { this->mem = mem; }
		constexpr void setMemEnd(const_pointer mem_end) noexcept { this->mem_end = mem_end; }

		#pragma endregion
		#pragma region Constructors
	public:
		constexpr ConstArray() noexcept = delete;
		explicit constexpr ConstArray(const_pointer mem, const_pointer mem_end) noexcept
			: mem(mem)
			, mem_end(mem_end)
		{}
		explicit constexpr ConstArray(const_pointer mem, const usize len) noexcept
			: ConstArray(mem, mem + len)
		{}
		constexpr ~ConstArray() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ConstArray(const ConstArray& other) noexcept
			: mem(other.mem), mem_end(other.mem_end) {}
		constexpr ConstArray& operator=(const ConstArray& other) noexcept {
			this->setMem(other.begin());
			this->setMemEnd(other.end());
			return *this;
		}
		constexpr ConstArray(ConstArray&& other) noexcept
			: mem(other.mem), mem_end(other.mem_end){ other.simpleClear(); }
		constexpr ConstArray& operator=(ConstArray&& other) noexcept {
			this->setMem(other.begin());
			this->setMemEnd(other.end());
			other.simpleClear();
			return *this;
		}

		constexpr ConstArray(volatile const ConstArray& other) noexcept;
		constexpr ConstArray& operator=(volatile const ConstArray& other) noexcept;
		constexpr ConstArray(volatile ConstArray&& other) noexcept;
		constexpr ConstArray& operator=(volatile ConstArray&& other) noexcept;

		constexpr ConstArray(const Array& other) noexcept;
		constexpr ConstArray& operator=(const Array& other) noexcept;
		constexpr ConstArray(Array&& other) noexcept;
		constexpr ConstArray& operator=(Array&& other) noexcept;

		constexpr ConstArray(volatile const Array& other) noexcept;
		constexpr ConstArray& operator=(volatile const Array& other) noexcept;
		constexpr ConstArray(volatile Array&& other) noexcept;
		constexpr ConstArray& operator=(volatile Array&& other) noexcept;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const ConstArray*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator ConstArray*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
	public:
		__LL_NODISCARD__ constexpr const_pointer get(const usize position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return this->begin() + position;
		}
		__LL_NODISCARD__ constexpr const_pointer get_s(const usize position) const noexcept {
			return this->inRange(position) ? this->begin() + position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr ConstArray get(const usize first, const usize last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return ConstArray(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr ConstArray get_s(const usize first, const usize last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ConstArray(this->get(first), this->get(last))
				: ConstArray(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr const_pointer rget(const usize position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return this->end() - position;
		}
		__LL_NODISCARD__ constexpr const_pointer rget_s(const usize position) const noexcept {
			return this->inRange(position) ? this->end() - position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr ConstArray rget(const usize first, const usize last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return ConstArray(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr ConstArray rget_s(const usize first, const usize last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ConstArray(this->rget(first), this->rget(last))
				: ConstArray(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr ConstArray substr(const usize first, const usize last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr ConstArray substr_s(const usize first, const usize last) const noexcept {
			return this->get_s(first, last);
		}

		// No-secure function
		__LL_NODISCARD__ constexpr const_reference operator[](const usize position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return *this->get(position);
		}
		// Non-standard operator
		__LL_NODISCARD__ constexpr const_reference operator^(const usize position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return *this->rget(position);
		}
#if __LL_REAL_CXX23 == 1
		// No-secure function
		__LL_NODISCARD__ constexpr ConstArray operator[](const usize first, const usize last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

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
		__LL_NODISCARD__ constexpr const_pointer data() const noexcept {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr const_iterator begin() const noexcept {
			return this->mem;
		}
		__LL_NODISCARD__ constexpr const_iterator end() const noexcept {
			return this->mem_end;
		}
		__LL_NODISCARD__ constexpr const_iterator rbegin() const noexcept {
			return this->mem_end - 1;
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			return this->lenght() == ::llcpp::ZERO_VALUE<usize>;
		}

		#pragma endregion
		#pragma region Other
	public:
		__LL_NODISCARD__ constexpr ll_bool_t isValid() const noexcept {
			return this->begin() && (this->begin() <= this->end());
		}
		constexpr void clear() noexcept { this->simpleClear(); }
		__LL_NODISCARD__ constexpr ll_bool_t resetValidation(const_pointer mem, const_pointer mem_end) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!mem) __debug_error_not_nullptr_str("mem");
				if (!mem_end) __debug_error_not_nullptr_str("mem_end");
				if (mem > mem_end) __debug_error_begin_smaller(mem, mem_end);
			}

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
		::llcpp::meta::attributes::checker::IGNORE_PA
>
class Array {
	#pragma region Types
	public:
		// Class related
		using _MyType	= Array;
		using ConstArray = ::llcpp::meta::ConstArray<_T, _TYPE_CHECKER>;

		// Types
		using T					= _T;
		using reference			= ::llcpp::meta::traits::input<T>;
		using const_reference	= ::llcpp::meta::traits::cinput<T>;
		using pointer			= T*;
		using const_pointer		= const T*;
		using iterator			= pointer;
		using const_iterator	= const_pointer;

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
			this->setMem(::llcpp::NULL_VALUE<pointer>);
			this->setMemEnd(::llcpp::NULL_VALUE<pointer>);
		}
		constexpr void setMem(const_pointer mem) noexcept { this->mem = const_cast<pointer>(mem); }
		constexpr void setMemEnd(const_pointer mem_end) noexcept { this->mem_end = const_cast<pointer>(mem_end); }

		#pragma endregion
		#pragma region Constructors
	public:
		constexpr Array() noexcept = delete;
		constexpr Array(T* mem, T* mem_end) noexcept : mem(mem), mem_end(mem_end) {}
		constexpr Array(T* mem, const usize len) noexcept : Array(mem, mem + len) {}
		constexpr ~Array() noexcept {}

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
		__LL_NODISCARD__ constexpr pointer get(const usize position) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return this->begin() + position;
		}
		__LL_NODISCARD__ constexpr const_pointer get(const usize position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return this->begin() + position;
		}
		__LL_NODISCARD__ constexpr pointer get_s(const usize position) noexcept {
			return this->inRange(position) ? this->begin() + position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const_pointer get_s(const usize position) const noexcept {
			return this->inRange(position) ? this->begin() + position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr Array get(const usize first, const usize last) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return Array(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr ConstArray get(const usize first, const usize last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return ConstArray(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr Array get_s(const usize first, const usize last) noexcept {
			return (this->inRange(first) && this->inRange(last))
				? Array(this->get(first), this->get(last))
				: Array(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr ConstArray get_s(const usize first, const usize last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ConstArray(this->get(first), this->get(last))
				: ConstArray(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr pointer rget(const usize position) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return this->end() - position;
		}
		__LL_NODISCARD__ constexpr const_pointer rget(const usize position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return this->end() - position;
		}
		__LL_NODISCARD__ constexpr pointer rget_s(const usize position) noexcept {
			return this->inRange(position) ? this->end() - position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const_pointer rget_s(const usize position) const noexcept {
			return this->inRange(position) ? this->end() - position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr Array rget(const usize first, const usize last) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return Array(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr ConstArray rget(const usize first, const usize last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return ConstArray(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr Array rget_s(const usize first, const usize last) noexcept {
			return (this->inRange(first) && this->inRange(last))
				? Array(this->rget(first), this->rget(last))
				: Array(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr ConstArray rget_s(const usize first, const usize last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ConstArray(this->rget(first), this->rget(last))
				: ConstArray(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr Array substr(const usize first, const usize last) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr ConstArray substr(const usize first, const usize last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr Array substr_s(const usize first, const usize last) noexcept {
			return this->get_s(first, last);
		}
		__LL_NODISCARD__ constexpr ConstArray substr_s(const usize first, const usize last) const noexcept {
			return this->get_s(first, last);
		}

		// No-secure function
		__LL_NODISCARD__ constexpr reference operator[](const usize position) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return *this->get(position);
		}
		// No-secure function
		__LL_NODISCARD__ constexpr const_reference operator[](const usize position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return *this->get(position);
		}

		// Non-standard operator
		__LL_NODISCARD__ constexpr reference operator^(const usize position) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return *this->rget(position);
		}
		// Non-standard operator
		__LL_NODISCARD__ constexpr const_reference operator^(const usize position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, this->length());
			}

			return *this->rget(position);
		}

#if __LL_REAL_CXX23 == 1
		__LL_NODISCARD__ constexpr Array operator[](const usize first, const usize last) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

			return this->substr(first, last);
		}
		__LL_NODISCARD__ constexpr ConstArray operator[](const usize first, const usize last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range_str(last, "last", this->length());
			}

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
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const usize position) const noexcept {
			return this->inRange(position);
		}

		#pragma endregion
		#pragma region std
	public:
		__LL_NODISCARD__ constexpr pointer data() noexcept {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr const_iterator data() const noexcept {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr iterator begin() noexcept {
			return this->mem;
		}
		__LL_NODISCARD__ constexpr const_iterator begin() const noexcept {
			return this->mem;
		}
		__LL_NODISCARD__ constexpr iterator rbegin() noexcept {
			return this->mem_end - 1;
		}
		__LL_NODISCARD__ constexpr const_iterator rbegin() const noexcept {
			return this->mem_end - 1;
		}
		__LL_NODISCARD__ constexpr iterator end() noexcept {
			return this->mem_end;
		}
		__LL_NODISCARD__ constexpr const_iterator end() const noexcept {
			return this->mem_end;
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			return this->lenght() == ::llcpp::ZERO_VALUE<usize>;
		}

		#pragma endregion
		#pragma region Other
	public:
		__LL_NODISCARD__ constexpr ll_bool_t isValid() const noexcept {
			return this->begin() && (this->begin() <= this->end());
		}
		constexpr void clear() noexcept { this->simpleClear(); }
		constexpr void makeInvalid() noexcept { this->simpleClear(); }
		constexpr void setMem(pointer mem) noexcept { this->mem = mem; }
		constexpr void setMemEnd(pointer mem_end) noexcept { this->mem_end = mem_end; }
		__LL_NODISCARD__ constexpr ll_bool_t resetValidation(pointer mem, pointer mem_end) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!mem) __debug_error_not_nullptr_str("mem");
				if (!mem_end) __debug_error_not_nullptr_str("mem_end");
				if (mem > mem_end) __debug_error_begin_smaller(mem, mem_end);
			}

			this->setMem(mem);
			this->setMemEnd(mem_end);
		}

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

#pragma region Array_ConstArray_Compatibility
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
__LL_INLINE__ constexpr ::llcpp::meta::ConstArray<_T, _TYPE_CHECKER>::ConstArray(const Array& other) noexcept
	: mem(other.begin()), mem_end(other.end()) {}
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
__LL_INLINE__ constexpr ::llcpp::meta::ConstArray<_T, _TYPE_CHECKER>& ::llcpp::meta::ConstArray<_T, _TYPE_CHECKER>::operator=(const Array& other) noexcept {
	this->setMem(other.begin());
	this->setMemEnd(other.end());
	return *this;
}
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
__LL_INLINE__ constexpr ::llcpp::meta::ConstArray<_T, _TYPE_CHECKER>::ConstArray(Array&& other) noexcept
	: mem(other.begin()), mem_end(other.end())
{
	// This is valid wile clear calls only simpleClear
	other.clear();
}
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
__LL_INLINE__ constexpr ::llcpp::meta::ConstArray<_T, _TYPE_CHECKER>& ::llcpp::meta::ConstArray<_T, _TYPE_CHECKER>::operator=(Array&& other) noexcept {
	this->setMem(other.begin());
	this->setMemEnd(other.end());
	// This is valid wile clear calls only simpleClear
	other.clear();
	return *this;
}

#pragma endregion
#pragma region StringTypes
template<::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = ::llcpp::meta::attributes::checker::IGNORE_PA>
using Str = ::llcpp::meta::Array<ll_char_t, TYPE_CHECKER>;
template<::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = ::llcpp::meta::attributes::checker::IGNORE_PA>
using wStr = ::llcpp::meta::Array<ll_wchar_t, TYPE_CHECKER>;

template<::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = ::llcpp::meta::attributes::checker::IGNORE_PA>
using ConstStr = ::llcpp::meta::ConstArray<ll_char_t, TYPE_CHECKER>;
template<::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = ::llcpp::meta::attributes::checker::IGNORE_PA>
using ConstwStr = ::llcpp::meta::ConstArray<ll_wchar_t, TYPE_CHECKER>;

namespace traits {

template<class T, ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = ::llcpp::meta::attributes::checker::IGNORE_PA>
__LL_VAR_INLINE__ constexpr ll_bool_t is_string_type_v =
	::std::_Is_any_of_v<
		T,
		::llcpp::meta::ConstStr<TYPE_CHECKER>,
		::llcpp::meta::ConstwStr<TYPE_CHECKER>
	>;

template<class T, ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = ::llcpp::meta::attributes::checker::IGNORE_PA>
__LL_VAR_INLINE__ constexpr ll_bool_t is_str_type_v =
	::std::_Is_any_of_v<
		T,
		::llcpp::meta::Str<TYPE_CHECKER>,
		::llcpp::meta::wStr<TYPE_CHECKER>
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
	return ConstArray<_T>(_array, _array + _N);
}

#pragma endregion
#pragma region String
template<
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PA,
	class _T, usize _N
>
__LL_NODISCARD__ constexpr ::llcpp::meta::Str<_TYPE_CHECKER> make_String(ll_char_t(&_array)[_N]) noexcept {
	return ::llcpp::meta::Str<_TYPE_CHECKER>(_array, _array + _N - 1);
}
template<
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PA,
	class _T, usize _N
>
__LL_NODISCARD__ constexpr ::llcpp::meta::wStr<_TYPE_CHECKER> make_String(ll_wchar_t(&_array)[_N]) noexcept {
	return ::llcpp::meta::wStr<_TYPE_CHECKER>(_array, _array + _N - 1);
}

#pragma endregion
#pragma region ConstString
template<
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PA,
	class _T, usize _N
>
__LL_NODISCARD__ constexpr ::llcpp::meta::Str<_TYPE_CHECKER> make_ConstString(const ll_char_t(&_array)[_N]) noexcept {
	return ::llcpp::meta::ConstStr<_TYPE_CHECKER>(_array, _array + _N - 1);
}
template<
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PA,
	class _T, usize _N
>
__LL_NODISCARD__ constexpr ::llcpp::meta::wStr<_TYPE_CHECKER> make_ConstString(const ll_wchar_t(&_array)[_N]) noexcept {
	return ::llcpp::meta::ConstwStr<_TYPE_CHECKER>(_array, _array + _N - 1);
}

#pragma endregion

#pragma endregion

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAY_HPP_
