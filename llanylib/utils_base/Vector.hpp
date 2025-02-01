//////////////////////////////////////////////
//	Vector.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_VECTOR_INCOMPLETE_HPP_)
	#if LLANYLIB_VECTOR_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_VECTOR_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Vector.hpp(incomplete) version error!"
		#else
			#error "Vector.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_VECTOR_INCOMPLETE_MAYOR_ || LLANYLIB_VECTOR_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_VECTOR_INCOMPLETE_HPP_)
	#define LLANYLIB_VECTOR_INCOMPLETE_HPP_
	#define LLANYLIB_VECTOR_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_VECTOR_INCOMPLETE_MINOR_ 0

#include "Array.hpp"

namespace llcpp {
namespace meta {

} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_VECTOR_HPP_)
	#if LLANYLIB_VECTOR_MAYOR_ != 11 || LLANYLIB_VECTOR_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Vector.hpp version error!"
		#else
			#error "Vector.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_VECTOR_MAYOR_ || LLANYLIB_VECTOR_MINOR_

#else
	#define LLANYLIB_VECTOR_HPP_
	#define LLANYLIB_VECTOR_MAYOR_ 11
	#define LLANYLIB_VECTOR_MINOR_ 0

#include "Array.hpp"

namespace llcpp {
namespace meta {

template<
	class _T,
	class _Allocator,
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_PA
>
class Vector : protected ::llcpp::meta::Array<_T, _TYPE_CHECKER> {
	#pragma region Types
	public:
		// Class related
		using _MyType			= Vector;
		using Array				= ::llcpp::meta::Array<_T, _TYPE_CHECKER>;
		using Allocator			= _Allocator;

		// Types
		using T					= Array::T;
		using reference			= Array::reference;
		using const_reference	= Array::const_reference;
		using pointer			= Array::pointer;
		using const_pointer		= Array::const_pointer;
		using iterator			= Array::iterator;
		using const_iterator	= Array::const_iterator;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = Array::TYPE_CHECKER;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<Allocator>,
			"type_checker<Allocator> detected an invalid type!");
		static_assert(::llcpp::meta::traits::is_valid_constructor_checker_v<Allocator>,
			"constructor_checker<Allocator> detected an invalid type!");
		static_assert(::std::is_class_v<Allocator>,
			"Allocator is not a class!");

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
		constexpr Vector() noexcept
			: Array(::llcpp::ZERO_VALUE<pointer>, ::llcpp::ZERO_VALUE<pointer>)
		{}
		constexpr Vector(const usize size) noexcept
			: Array(Allocator::allocate(size), this->begin() + size)
		{}
		constexpr Vector(T* mem, T* mem_end) noexcept : Array(mem, mem_end) {}
		constexpr Vector(T* mem, const usize len) noexcept : Array(mem, mem + len) {}
		constexpr ~Vector() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Vector(const Vector& other) noexcept
			: Vector(other.mem, other.mem_end)
		{}
		constexpr Vector& operator=(const Vector& other) noexcept {
			this->setMem(other.begin());
			this->setMemEnd(other.end());
			return *this;
		}
		constexpr Vector(Vector&& other) noexcept
			: Vector(other)
		{ other.simpleClear(); }
		constexpr Vector& operator=(Vector&& other) noexcept {
			this->setMem(other.begin());
			this->setMemEnd(other.end());
			other.simpleClear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Vector* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Vector* () noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator ConstVector() const noexcept {
			return ConstVector(*this);
		}
		__LL_NODISCARD__ constexpr ConstVector operator()() const noexcept {
			return this->operator ConstVector();
		}
		__LL_NODISCARD__ constexpr ConstVector to_ConstVector() const noexcept {
			return this->operator ConstVector();
		}

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
	public:
		__LL_NODISCARD__ constexpr pointer get(const usize position) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, "position", this->length());
			}

			return this->begin() + position;
		}
		__LL_NODISCARD__ constexpr const_pointer get(const usize position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, "position", this->length());
			}

			return this->begin() + position;
		}
		__LL_NODISCARD__ constexpr pointer get_s(const usize position) noexcept {
			return this->inRange(position) ? this->begin() + position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const_pointer get_s(const usize position) const noexcept {
			return this->inRange(position) ? this->begin() + position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr Vector get(const usize first, const usize last) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range(last, "last", this->length());
			}

			return Vector(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr ConstVector get(const usize first, const usize last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range(last, "last", this->length());
			}

			return ConstVector(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr Vector get_s(const usize first, const usize last) noexcept {
			return (this->inRange(first) && this->inRange(last))
				? Vector(this->get(first), this->get(last))
				: Vector(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr ConstArray get_s(const usize first, const usize last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ConstArray(this->get(first), this->get(last))
				: ConstArray(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr pointer rget(const usize position) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, "position", this->length());
			}

			return this->end() - position;
		}
		__LL_NODISCARD__ constexpr const_pointer rget(const usize position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, "position", this->length());
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
					__debug_error_out_of_range(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range(last, "last", this->length());
			}

			return Array(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr ConstArray rget(const usize first, const usize last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range(last, "last", this->length());
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
					__debug_error_out_of_range(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range(last, "last", this->length());
			}

			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr ConstArray substr(const usize first, const usize last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range(last, "last", this->length());
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
					__debug_error_out_of_range(position, "position", this->length());
			}

			return *this->get(position);
		}
		// No-secure function
		__LL_NODISCARD__ constexpr const_reference operator[](const usize position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, "position", this->length());
			}

			return *this->get(position);
		}

		// Non-standard operator
		__LL_NODISCARD__ constexpr reference operator^(const usize position) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, "position", this->length());
			}

			return *this->rget(position);
		}
		// Non-standard operator
		__LL_NODISCARD__ constexpr const_reference operator^(const usize position) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(position))
					__debug_error_out_of_range(position, "position", this->length());
			}

			return *this->rget(position);
		}

#if __LL_REAL_CXX23 == 1
		__LL_NODISCARD__ constexpr Array operator[](const usize first, const usize last) noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range(last, "last", this->length());
			}

			return this->substr(first, last);
		}
		__LL_NODISCARD__ constexpr ConstArray operator[](const usize first, const usize last) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (!this->inRange(first))
					__debug_error_out_of_range(first, "first", this->length());
				if (!this->inRange(last))
					__debug_error_out_of_range(last, "last", this->length());
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

#endif // LLANYLIB_VECTOR_HPP_
