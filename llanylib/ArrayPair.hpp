//////////////////////////////////////////////
//	ArrayPair.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ARRAYPAIR_HPP_) // Guard && version protector
	#if LLANYLIB_ARRAYPAIR_MAYOR_ != 9 || LLANYLIB_ARRAYPAIR_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "ArrayPair.hpp version error!"
		#else
			#error "ArrayPair.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ARRAYPAIR_MAYOR_ || LLANYLIB_ARRAYPAIR_MINOR_

#else !defined(LLANYLIB_ARRAYPAIR_HPP_)
#define LLANYLIB_ARRAYPAIR_HPP_
#define LLANYLIB_ARRAYPAIR_MAYOR_ 9
#define LLANYLIB_ARRAYPAIR_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace meta {

template<class T>
class Array;

template<class _T>
class ArrayPair {
	#pragma region Types
	public:
		// Class related
		using _MyType	= ArrayPair;
		using Array		= Array<_T>;

		// Types
		using T			= _T;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_ignore_pa_v<T>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Attributes
	private:
		const T* mem;
		const T* mem_end;

	#pragma endregion
	#pragma region Functions
		#pragma region Private
	private:
		constexpr void simpleClear() noexcept {
			this->mem = LL_NULLPTR;
			this->mem_end = LL_NULLPTR;
		}

		#pragma endregion
		#pragma region Constructors
	public:
		constexpr ArrayPair() noexcept = delete;
		constexpr ArrayPair(const T* mem, const T* mem_end) noexcept : mem(mem), mem_end(mem_end) {}
		constexpr ArrayPair(const T* mem, const len_t len) noexcept : ArrayPair(mem, mem + len) {}
		constexpr ~ArrayPair() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ArrayPair(const ArrayPair& other) noexcept
			: mem(other.mem), mem_end(other.mem_end) {}
		constexpr ArrayPair& operator=(const ArrayPair& other) noexcept {
			this->mem = other.mem;
			this->mem_end = other.mem_end;
			return *this;
		}
		constexpr ArrayPair(ArrayPair&& other) noexcept
			: mem(other.mem), mem_end(other.mem_end){ other.simpleClear(); }
		constexpr ArrayPair& operator=(ArrayPair&& other) noexcept {
			this->mem = other.mem;
			this->mem_end = other.mem_end;
			other.simpleClear();
			return *this;
		}

		constexpr ArrayPair(const Array& other) noexcept;
		constexpr ArrayPair& operator=(const Array& other) noexcept;
		constexpr ArrayPair(Array&& other) noexcept;
		constexpr ArrayPair& operator=(Array&& other) noexcept;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const ArrayPair* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator ArrayPair* () noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
	public:
		__LL_NODISCARD__ constexpr const T* get(const len_t position) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			return this->mem + position;
		}
		__LL_NODISCARD__ constexpr const T* get_s(const len_t position) const noexcept {
			return this->inRange(position) ? this->mem + position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr ArrayPair get(const len_t first, const len_t last) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
			if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
#endif // _DEBUG

			return ArrayPair(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr ArrayPair get_s(const len_t first, const len_t last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ArrayPair(this->get(first), this->get(last))
				: ArrayPair(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr const T* rget(const len_t position) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			return this->mem_end - position;
		}
		__LL_NODISCARD__ constexpr const T* rget_s(const len_t position) const noexcept {
			return this->inRange(position) ? this->mem_end - position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr ArrayPair rget(const len_t first, const len_t last) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
			if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
#endif // _DEBUG

			return ArrayPair(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr ArrayPair rget_s(const len_t first, const len_t last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ArrayPair(this->rget(first), this->rget(last))
				: ArrayPair(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr ArrayPair substr(const len_t first, const len_t last) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
			if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
#endif // _DEBUG

			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr ArrayPair substr_s(const len_t first, const len_t last) const noexcept {
			return this->get_s(first, last);
		}

		// No-secure function
		__LL_NODISCARD__ constexpr const T& operator[](const len_t position) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			return *this->get(position);
		}
		// Non-standard operator
		__LL_NODISCARD__ constexpr const T& operator^(const len_t position) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			return *this->rget(position);
		}
#if defined(LL_REAL_CXX23)
		// No-secure function
		__LL_NODISCARD__ constexpr ArrayPair operator[](const len_t first, const len_t last) const noexcept {
			return this->substr(first, last);
		}

#endif // LL_REAL_CXX23

		#pragma endregion
		#pragma region Countable
	public:
		__LL_NODISCARD__ constexpr len_t lenght() const noexcept {
			return static_cast<len_t>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr len_t size() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr len_t count() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr ll_bool_t inRange(const len_t position) const noexcept {
			return position < this->lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const len_t position) const noexcept {
			return this->inRange(position);
		}

		#pragma endregion
		#pragma region std
	public:
		__LL_NODISCARD__ constexpr const T* data() const noexcept {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr const T* begin() const noexcept {
			return this->get(ZERO_UI64);
		}
		__LL_NODISCARD__ constexpr const T* end() const noexcept {
			return this->mem_end;
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			return this->lenght() == ZERO_UI64;
		}

		#pragma endregion
		#pragma region Other
	public:
		__LL_NODISCARD__ constexpr ll_bool_t isValid() const noexcept {
			return (this->begin() < this->end()) && !this->empty();
		}
		constexpr void clear() noexcept { this->simpleClear(); }

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

template<class _T>
class Array {
	#pragma region Types
	public:
		// Class related
		using _MyType	= Array;
		using ArrayPair = meta::ArrayPair<_T>;

		// Types
		using T			= _T;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_ignore_pa_v<T>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Attributes
	private:
		T* mem;
		T* mem_end;

	#pragma endregion
	#pragma region Functions
		#pragma region Functions
	private:
		constexpr void simpleClear() noexcept {
			this->mem = LL_NULLPTR;
			this->mem_end = LL_NULLPTR;
		}

		#pragma endregion
		#pragma region Constructors
	public:
		constexpr Array() noexcept = delete;
		constexpr Array(T* mem, T* mem_end) noexcept : mem(mem), mem_end(mem_end) {}
		constexpr Array(T* mem, const len_t len) noexcept : Array(mem, mem + len) {}
		constexpr ~Array() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Array(const Array& other) noexcept : Array(other.mem, other.mem_end) {}
		constexpr Array& operator=(const Array& other) noexcept {
			this->mem = other.mem;
			this->mem_end = other.mem_end;
			return *this;
		}
		constexpr Array(Array&& other) noexcept : Array(other) { other.simpleClear(); }
		constexpr Array& operator=(Array&& other) noexcept {
			Array::operator=(other);
			other.simpleClear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const Array* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator Array* () noexcept { return this; }
		__LL_NODISCARD__ constexpr operator ArrayPair() const noexcept {
			return ArrayPair(*this);
		}
		__LL_NODISCARD__ constexpr ArrayPair operator()() const noexcept {
			return this->operator ArrayPair();
		}
		__LL_NODISCARD__ constexpr ArrayPair to_ArrayPair() const noexcept {
			return this->operator ArrayPair();
		}

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
	public:
		__LL_NODISCARD__ constexpr T* get(const len_t position) noexcept {
#if defined(_DEBUG)
			if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			return this->mem + position;
		}
		__LL_NODISCARD__ constexpr const T* get(const len_t position) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			return this->mem + position;
		}
		__LL_NODISCARD__ constexpr T* get_s(const len_t position) noexcept {
			return this->inRange(position) ? this->mem + position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const T* get_s(const len_t position) const noexcept {
			return this->inRange(position) ? this->mem + position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr Array get(const len_t first, const len_t last) noexcept {
#if defined(_DEBUG)
			if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
			if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
#endif // _DEBUG

			return Array(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr ArrayPair get(const len_t first, const len_t last) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
			if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
#endif // _DEBUG

			return ArrayPair(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr Array get_s(const len_t first, const len_t last) noexcept {
			return (this->inRange(first) && this->inRange(last))
				? Array(this->get(first), this->get(last))
				: Array(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr ArrayPair get_s(const len_t first, const len_t last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ArrayPair(this->get(first), this->get(last))
				: ArrayPair(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr T* rget(const len_t position) noexcept {
#if defined(_DEBUG)
			if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			return this->mem_end - position;
		}
		__LL_NODISCARD__ constexpr const T* rget(const len_t position) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			return this->mem_end - position;
		}
		__LL_NODISCARD__ constexpr T* rget_s(const len_t position) noexcept {
			return this->inRange(position) ? this->mem_end - position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const T* rget_s(const len_t position) const noexcept {
			return this->inRange(position) ? this->mem_end - position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr Array rget(const len_t first, const len_t last) noexcept {
#if defined(_DEBUG)
			if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
			if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
#endif // _DEBUG

			return Array(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr ArrayPair rget(const len_t first, const len_t last) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
			if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
#endif // _DEBUG

			return ArrayPair(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr Array rget_s(const len_t first, const len_t last) noexcept {
			return (this->inRange(first) && this->inRange(last))
				? Array(this->rget(first), this->rget(last))
				: Array(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr ArrayPair rget_s(const len_t first, const len_t last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ArrayPair(this->rget(first), this->rget(last))
				: ArrayPair(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr Array substr(const len_t first, const len_t last) noexcept {
#if defined(_DEBUG)
			if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
			if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
#endif // _DEBUG

			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr ArrayPair substr(const len_t first, const len_t last) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
			if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
#endif // _DEBUG

			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr Array substr_s(const len_t first, const len_t last) noexcept {
			return this->get_s(first, last);
		}
		__LL_NODISCARD__ constexpr ArrayPair substr_s(const len_t first, const len_t last) const noexcept {
			return this->get_s(first, last);
		}
		__LL_NODISCARD__ constexpr T& operator[](const len_t position) noexcept {
#if defined(_DEBUG)
			if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			return *this->get(position);
		}
		__LL_NODISCARD__ constexpr const T& operator[](const len_t position) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			return *this->get(position);
		}
		__LL_NODISCARD__ constexpr T& operator^(const len_t position) noexcept {
#if defined(_DEBUG)
			if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			return *this->rget(position);
		}
		__LL_NODISCARD__ constexpr const T& operator^(const len_t position) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			return *this->rget(position);
		}

#if defined(LL_REAL_CXX23)
		__LL_NODISCARD__ constexpr Array operator[](const len_t first, const len_t last) noexcept {
#if defined(_DEBUG)
			if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
			if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
#endif // _DEBUG

			return this->substr(first, last);
		}
		__LL_NODISCARD__ constexpr ArrayPair operator[](const len_t first, const len_t last) const noexcept {
#if defined(_DEBUG)
			if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
			if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
#endif // _DEBUG

			return this->substr(first, last);
		}

#endif // LL_REAL_CXX23

		#pragma endregion
		#pragma region Countable
	public:
		__LL_NODISCARD__ constexpr len_t lenght() const noexcept {
			return static_cast<len_t>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr len_t size() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr len_t count() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr ll_bool_t inRange(const len_t position) const noexcept {
			return position < this->lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const len_t position) const noexcept {
			return this->inRange(position);
		}

		#pragma endregion
		#pragma region std
	public:
		__LL_NODISCARD__ constexpr T* data() noexcept {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr const T* data() const noexcept {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr T* begin() noexcept {
			return this->get(ZERO_UI64);
		}
		__LL_NODISCARD__ constexpr const T* begin() const noexcept {
			return this->get(ZERO_UI64);
		}
		__LL_NODISCARD__ constexpr T* rbegin() noexcept {
			return this->mem_end - 1;
		}
		__LL_NODISCARD__ constexpr const T* rbegin() const noexcept {
			return this->mem_end - 1;
		}
		__LL_NODISCARD__ constexpr T* end() noexcept {
			return this->mem_end;
		}
		__LL_NODISCARD__ constexpr const T* end() const noexcept {
			return this->mem_end;
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			return this->lenght() == ZERO_UI64;
		}

		#pragma endregion
		#pragma region Other
	public:
		__LL_NODISCARD__ constexpr ll_bool_t isValid() const noexcept {
			return !this->empty() && (this->begin() < this->end());
		}
		constexpr void clear() noexcept { this->simpleClear(); }
		constexpr void makeInvalid() noexcept {
			this->mem = LL_NULLPTR;
			this->mem_end = LL_NULLPTR;
		}
		#pragma endregion

		#pragma endregion

	#pragma endregion
};

#pragma region Array_ArrayPair_Compatibility
template<class T>
__LL_INLINE__ constexpr ArrayPair<T>::ArrayPair(const Array& other) noexcept
	: mem(other.begin()), mem_end(other.end()) {}
template<class T>
__LL_INLINE__ constexpr ArrayPair<T>& ArrayPair<T>::operator=(const Array& other) noexcept {
	this->mem = other.mem;
	this->mem_end = other.mem_end;
	return *this;
}
template<class T>
__LL_INLINE__ constexpr ArrayPair<T>::ArrayPair(Array&& other) noexcept
	: mem(other.begin()), mem_end(other.end()) {}
template<class T>
__LL_INLINE__ constexpr ArrayPair<T>& ArrayPair<T>::operator=(Array&& other) noexcept {
	this->mem = other.mem;
	this->mem_end = other.mem_end;
	other.simpleClear();
	return *this;
}

#pragma endregion
#pragma region Builders
template<class T, len_t N>
__LL_NODISCARD__ constexpr Array<T> make_Array(T(&_array)[N]) noexcept {
	return Array<T>(_array, _array + N);
}
template<class T, len_t N>
__LL_NODISCARD__ constexpr ArrayPair<T> make_ArrayPair(const T(&_array)[N]) noexcept {
	return ArrayPair<T>(_array, _array + N);
}
template<len_t N>
__LL_NODISCARD__ constexpr ArrayPair<ll_char_t> make_ArrayPair(const ll_char_t(&_array)[N]) noexcept {
	return ArrayPair<ll_char_t>(_array, _array + N - 1);
}
template<len_t N>
__LL_NODISCARD__ constexpr ArrayPair<ll_wchar_t> make_ArrayPair(const ll_wchar_t(&_array)[N]) noexcept {
	return ArrayPair<ll_wchar_t>(_array, _array + N - 1);
}

#pragma endregion

namespace traits {
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_strpair_type_v = std::_Is_any_of_v<T, StrPair, wStrPair>;
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_str_type_v = std::_Is_any_of_v<T, Str, wStr>;
} // namespace traits

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAYPAIR_HPP_
