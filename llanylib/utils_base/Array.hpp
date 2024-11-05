//////////////////////////////////////////////
//	Array.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#define LLANYLIB_INCOMPLETE_HPP_

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ARRAY_INCOMPLETE_HPP_)
	#if LLANYLIB_ARRAY_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_ARRAY_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Array.hpp(incomplete) version error!"
		#else
			#error "Array.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ARRAY_ERROR_HPP_
	#endif // LLANYLIB_ARRAY_INCOMPLETE_MAYOR_ || LLANYLIB_ARRAY_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ARRAY_INCOMPLETE_HPP_)
#define LLANYLIB_ARRAY_INCOMPLETE_HPP_
#define LLANYLIB_ARRAY_INCOMPLETE_MAYOR_ 11
#define LLANYLIB_ARRAY_INCOMPLETE_MINOR_ 0

#include "../traits_base/traits_checker.hpp"

namespace llcpp {
namespace meta {

template<class _T, traits::checker_attributes_t _TYPE_CHECKER>
class Array;
template<class _T, traits::checker_attributes_t _TYPE_CHECKER>
class ConstArray;

} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ARRAY_HPP_)
	#if LLANYLIB_ARRAY_MAYOR_ != 11 || LLANYLIB_ARRAY_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Array.hpp version error!"
		#else
			#error "Array.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ARRAY_ERROR_HPP_
	#endif // LLANYLIB_ARRAY_MAYOR_ || LLANYLIB_ARRAY_MINOR_

#else
#define LLANYLIB_ARRAY_HPP_
#define LLANYLIB_ARRAY_MAYOR_ 11
#define LLANYLIB_ARRAY_MINOR_ 0

#include "../traits_base/traits_checker.hpp"

namespace llcpp {
namespace meta {

template<class _T, traits::checker_attributes_t _TYPE_CHECKER>
class Array;

template<class _T, traits::checker_attributes_t _TYPE_CHECKER = traits::checker::IGNORE_PA>
class ConstArray {
	#pragma region Types
	public:
		// Class related
		using _MyType	= ConstArray;
		using Array		= meta::Array<_T, _TYPE_CHECKER>;

		// Types
		using T			= _T;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr traits::checker_attributes_t TYPE_CHECKER = _TYPE_CHECKER;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<T, TYPE_CHECKER>,
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
		constexpr ConstArray() noexcept = delete;
		constexpr ConstArray(const T* mem, const T* mem_end) noexcept : mem(mem), mem_end(mem_end) {}
		constexpr ConstArray(const T* mem, const u64 len) noexcept : ConstArray(mem, mem + len) {}
		constexpr ~ConstArray() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ConstArray(const ConstArray& other) noexcept
			: mem(other.mem), mem_end(other.mem_end) {}
		constexpr ConstArray& operator=(const ConstArray& other) noexcept {
			this->mem = other.mem;
			this->mem_end = other.mem_end;
			return *this;
		}
		constexpr ConstArray(ConstArray&& other) noexcept
			: mem(other.mem), mem_end(other.mem_end){ other.simpleClear(); }
		constexpr ConstArray& operator=(ConstArray&& other) noexcept {
			this->mem = other.mem;
			this->mem_end = other.mem_end;
			other.simpleClear();
			return *this;
		}

		constexpr ConstArray(const Array& other) noexcept;
		constexpr ConstArray& operator=(const Array& other) noexcept;
		constexpr ConstArray(Array&& other) noexcept;
		constexpr ConstArray& operator=(Array&& other) noexcept;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const ConstArray*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator ConstArray*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
	public:
		__LL_NODISCARD__ constexpr const T* get(const u64 position) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
			}

			return this->mem + position;
		}
		__LL_NODISCARD__ constexpr const T* get_s(const u64 position) const noexcept {
			return this->inRange(position) ? this->mem + position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr ConstArray get(const u64 first, const u64 last) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
			}

			return ConstArray(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr ConstArray get_s(const u64 first, const u64 last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ConstArray(this->get(first), this->get(last))
				: ConstArray(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr const T* rget(const u64 position) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
			}

			return this->mem_end - position;
		}
		__LL_NODISCARD__ constexpr const T* rget_s(const u64 position) const noexcept {
			return this->inRange(position) ? this->mem_end - position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr ConstArray rget(const u64 first, const u64 last) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
			}

			return ConstArray(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr ConstArray rget_s(const u64 first, const u64 last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ConstArray(this->rget(first), this->rget(last))
				: ConstArray(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr ConstArray substr(const u64 first, const u64 last) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
			}

			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr ConstArray substr_s(const u64 first, const u64 last) const noexcept {
			return this->get_s(first, last);
		}

		// No-secure function
		__LL_NODISCARD__ constexpr const T& operator[](const u64 position) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
			}

			return *this->get(position);
		}
		// Non-standard operator
		__LL_NODISCARD__ constexpr const T& operator^(const u64 position) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
			}

			return *this->rget(position);
		}
#if __LL_REAL_CXX23 == 1
		// No-secure function
		__LL_NODISCARD__ constexpr ConstArray operator[](const u64 first, const u64 last) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
			}

			return this->substr(first, last);
		}

#endif // __LL_REAL_CXX23

		#pragma endregion
		#pragma region Countable
	public:
		__LL_NODISCARD__ constexpr u64 lenght() const noexcept {
			return static_cast<u64>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr u64 size() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr u64 count() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr ll_bool_t inRange(const u64 position) const noexcept {
			return position < this->lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const u64 position) const noexcept {
			return this->inRange(position);
		}

		#pragma endregion
		#pragma region std
	public:
		__LL_NODISCARD__ constexpr const T* data() const noexcept {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr const T* begin() const noexcept {
			return this->mem;
		}
		__LL_NODISCARD__ constexpr const T* end() const noexcept {
			return this->mem_end;
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			return this->lenght() == ZERO_U64;
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

template<class _T, traits::checker_attributes_t _TYPE_CHECKER = traits::checker::IGNORE_PA>
class Array {
	#pragma region Types
	public:
		// Class related
		using _MyType	= Array;
		using ConstArray = meta::ConstArray<_T, _TYPE_CHECKER>;

		// Types
		using T			= _T;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr traits::checker_attributes_t TYPE_CHECKER = _TYPE_CHECKER;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<T, TYPE_CHECKER>,
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
		constexpr Array(T* mem, const u64 len) noexcept : Array(mem, mem + len) {}
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
		__LL_NODISCARD__ constexpr T* get(const u64 position) noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
			}

			return this->mem + position;
		}
		__LL_NODISCARD__ constexpr const T* get(const u64 position) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
			}

			return this->mem + position;
		}
		__LL_NODISCARD__ constexpr T* get_s(const u64 position) noexcept {
			return this->inRange(position) ? this->mem + position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const T* get_s(const u64 position) const noexcept {
			return this->inRange(position) ? this->mem + position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr Array get(const u64 first, const u64 last) noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
			}

			return Array(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr ConstArray get(const u64 first, const u64 last) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
			}

			return ConstArray(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr Array get_s(const u64 first, const u64 last) noexcept {
			return (this->inRange(first) && this->inRange(last))
				? Array(this->get(first), this->get(last))
				: Array(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr ConstArray get_s(const u64 first, const u64 last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ConstArray(this->get(first), this->get(last))
				: ConstArray(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr T* rget(const u64 position) noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
			}

			return this->mem_end - position;
		}
		__LL_NODISCARD__ constexpr const T* rget(const u64 position) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
			}

			return this->mem_end - position;
		}
		__LL_NODISCARD__ constexpr T* rget_s(const u64 position) noexcept {
			return this->inRange(position) ? this->mem_end - position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const T* rget_s(const u64 position) const noexcept {
			return this->inRange(position) ? this->mem_end - position : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr Array rget(const u64 first, const u64 last) noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
			}

			return Array(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr ConstArray rget(const u64 first, const u64 last) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
			}

			return ConstArray(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr Array rget_s(const u64 first, const u64 last) noexcept {
			return (this->inRange(first) && this->inRange(last))
				? Array(this->rget(first), this->rget(last))
				: Array(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr ConstArray rget_s(const u64 first, const u64 last) const noexcept {
			return (this->inRange(first) && this->inRange(last))
				? ConstArray(this->rget(first), this->rget(last))
				: ConstArray(LL_NULLPTR, LL_NULLPTR);
		}
		__LL_NODISCARD__ constexpr Array substr(const u64 first, const u64 last) noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
			}

			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr ConstArray substr(const u64 first, const u64 last) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
			}

			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr Array substr_s(const u64 first, const u64 last) noexcept {
			return this->get_s(first, last);
		}
		__LL_NODISCARD__ constexpr ConstArray substr_s(const u64 first, const u64 last) const noexcept {
			return this->get_s(first, last);
		}
		__LL_NODISCARD__ constexpr T& operator[](const u64 position) noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
			}

			return *this->get(position);
		}
		__LL_NODISCARD__ constexpr const T& operator[](const u64 position) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
			}

			return *this->get(position);
		}
		__LL_NODISCARD__ constexpr T& operator^(const u64 position) noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
			}

			return *this->rget(position);
		}
		__LL_NODISCARD__ constexpr const T& operator^(const u64 position) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(position)) __debug_error_out_of_range(position, this->length());
			}

			return *this->rget(position);
		}

#if __LL_REAL_CXX23 == 1
		__LL_NODISCARD__ constexpr Array operator[](const u64 first, const u64 last) noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
			}

			return this->substr(first, last);
		}
		__LL_NODISCARD__ constexpr ConstArray operator[](const u64 first, const u64 last) const noexcept {
			if constexpr (llcpp::DEBUG) {
				if (!this->inRange(first)) __debug_error_out_of_range_str(first, "first", this->length());
				if (!this->inRange(last)) __debug_error_out_of_range_str(last, "last", this->length());
			}

			return this->substr(first, last);
		}

#endif // __LL_REAL_CXX23

		#pragma endregion
		#pragma region Countable
	public:
		__LL_NODISCARD__ constexpr u64 lenght() const noexcept {
			return static_cast<u64>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr u64 size() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr u64 count() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr ll_bool_t inRange(const u64 position) const noexcept {
			return position < this->lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const u64 position) const noexcept {
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
			return this->mem;
		}
		__LL_NODISCARD__ constexpr const T* begin() const noexcept {
			return this->mem;
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
			return this->lenght() == ZERO_U64;
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

#pragma region Array_ConstArray_Compatibility
template<class _T, traits::checker_attributes_t _TYPE_CHECKER>
__LL_INLINE__ constexpr ConstArray<_T, _TYPE_CHECKER>::ConstArray(const Array& other) noexcept
	: mem(other.begin()), mem_end(other.end()) {}
template<class _T, traits::checker_attributes_t _TYPE_CHECKER>
__LL_INLINE__ constexpr ConstArray<_T, _TYPE_CHECKER>& ConstArray<_T, _TYPE_CHECKER>::operator=(const Array& other) noexcept {
	this->mem = other.mem;
	this->mem_end = other.mem_end;
	return *this;
}
template<class _T, traits::checker_attributes_t _TYPE_CHECKER>
__LL_INLINE__ constexpr ConstArray<_T, _TYPE_CHECKER>::ConstArray(Array&& other) noexcept
	: mem(other.begin()), mem_end(other.end()) {}
template<class _T, traits::checker_attributes_t _TYPE_CHECKER>
__LL_INLINE__ constexpr ConstArray<_T, _TYPE_CHECKER>& ConstArray<_T, _TYPE_CHECKER>::operator=(Array&& other) noexcept {
	this->mem = other.mem;
	this->mem_end = other.mem_end;
	other.simpleClear();
	return *this;
}

#pragma endregion
#pragma region Builders
template<traits::checker_attributes_t _TYPE_CHECKER = traits::checker::IGNORE_PA, class _T, u64 _N>
__LL_NODISCARD__ constexpr Array<_T, _TYPE_CHECKER> make_Array(_T(&_array)[_N]) noexcept {
	return Array<T>(_array, _array + _N);
}
template<traits::checker_attributes_t _TYPE_CHECKER = traits::checker::IGNORE_PA, class _T, u64 _N>
__LL_NODISCARD__ constexpr ConstArray<_T, _TYPE_CHECKER> make_ConstArray(const _T(&_array)[_N]) noexcept {
	return ConstArray<T>(_array, _array + _N);
}
template<traits::checker_attributes_t _TYPE_CHECKER = traits::checker::IGNORE_PA, u64 _N>
__LL_NODISCARD__ constexpr ConstArray<ll_char_t, _TYPE_CHECKER> make_ConstArray(const ll_char_t(&_array)[_N]) noexcept {
	return ConstArray<ll_char_t>(_array, _array + _N - 1);
}
template<traits::checker_attributes_t _TYPE_CHECKER = traits::checker::IGNORE_PA, u64 _N>
__LL_NODISCARD__ constexpr ConstArray<ll_wchar_t, _TYPE_CHECKER> make_ConstArray(const ll_wchar_t(&_array)[_N]) noexcept {
	return ConstArray<ll_wchar_t>(_array, _array + _N - 1);
}

#pragma endregion

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAY_HPP_

#if !defined(LLANYLIB_ARRAY_CHAR_HPP_) && !defined(LLANYLIB_ARRAY_ERROR_HPP_)
#define LLANYLIB_ARRAY_CHAR_HPP_

namespace llcpp {
namespace meta {

template<traits::checker_attributes_t TYPE_CHECKER = traits::checker::IGNORE_PA>
using Str = Array<ll_char_t, TYPE_CHECKER>;
template<traits::checker_attributes_t TYPE_CHECKER = traits::checker::IGNORE_PA>
using wStr = Array<ll_wchar_t, TYPE_CHECKER>;

template<traits::checker_attributes_t TYPE_CHECKER = traits::checker::IGNORE_PA>
using ConstStr = ConstArray<ll_char_t, TYPE_CHECKER>;
template<traits::checker_attributes_t TYPE_CHECKER = traits::checker::IGNORE_PA>
using ConstwStr = ConstArray<ll_wchar_t, TYPE_CHECKER>;

namespace traits {

template<class T, traits::checker_attributes_t TYPE_CHECKER = traits::checker::IGNORE_PA>
__LL_VAR_INLINE__ constexpr ll_bool_t is_string_type_v =
	std::_Is_any_of_v<
		T,
		meta::ConstStr<TYPE_CHECKER>,
		meta::ConstwStr<TYPE_CHECKER>
	>;

template<class T, traits::checker_attributes_t TYPE_CHECKER = traits::checker::IGNORE_PA>
__LL_VAR_INLINE__ constexpr ll_bool_t is_str_type_v =
	std::_Is_any_of_v<
		T,
		meta::Str<TYPE_CHECKER>,
		meta::wStr<TYPE_CHECKER>
	>;

} // namespace traits

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAY_CHAR_HPP_

#if defined(LLANYLIB_ARRAY_ERROR_HPP_)
	#undef LLANYLIB_ARRAY_ERROR_HPP_
#endif // LLANYLIB_ARRAY_ERROR_HPP_
