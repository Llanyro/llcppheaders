//////////////////////////////////////////////
//	ArrayPair.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ARRAYPAIR_HPP_) // Guard && version protector
	#if LLANYLIB_ARRAYPAIR_MAYOR_ != 8 || LLANYLIB_ARRAYPAIR_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "ArrayPair.hpp version error!"
		#else
			#error "ArrayPair.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ARRAYPAIR_MAYOR_ || LLANYLIB_ARRAYPAIR_MINOR_

#else !defined(LLANYLIB_ARRAYPAIR_HPP_)
#define LLANYLIB_ARRAYPAIR_HPP_
#define LLANYLIB_ARRAYPAIR_MAYOR_ 8
#define LLANYLIB_ARRAYPAIR_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace meta {

template<class T>
class Array;

template<class T>
class ArrayPair {
	public:
		static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<T>, "Const type is forbidden!");
	protected:
		const T* mem;
		const T* mem_end;
	#pragma region Functions
	protected:
		constexpr void simpleClear() noexcept {
			this->mem = LL_NULLPTR;
			this->mem_end = LL_NULLPTR;
		}
	public:
		#pragma region Constructors
		constexpr ArrayPair() noexcept = delete;
		constexpr ArrayPair(const T* mem, const T* mem_end) noexcept : mem(mem), mem_end(mem_end) {}
		constexpr ArrayPair(const T* mem, const len_t len) noexcept : ArrayPair(mem, mem + len) {}
		constexpr ~ArrayPair() noexcept {}

		#pragma endregion
		#pragma region CopyMove
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

		constexpr ArrayPair(const Array<T>& other) noexcept;
		constexpr ArrayPair& operator=(const Array<T>& other) noexcept;
		constexpr ArrayPair(Array<T>&& other) noexcept;
		constexpr ArrayPair& operator=(Array<T>&& other) noexcept;

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator const ArrayPair*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator ArrayPair*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
		__LL_NODISCARD__ constexpr const T* get(const len_t pos) const noexcept {
			return this->mem + pos;
		}
		__LL_NODISCARD__ constexpr ArrayPair get(const len_t first, const len_t last) const noexcept {
			return ArrayPair(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr const T* rget(const len_t pos) const noexcept {
			return this->mem_end - pos;
		}
		__LL_NODISCARD__ constexpr ArrayPair rget(const len_t first, const len_t last) const noexcept {
			return ArrayPair(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr ArrayPair substr(const len_t first, const len_t last) const noexcept {
			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr const T& operator[](const len_t pos) const noexcept {
			return *this->get(pos);
		}
		__LL_NODISCARD__ constexpr const T& operator^(const len_t pos) const noexcept {
			return this->rget(pos);
		}
#if defined(LL_REAL_CXX23)
		__LL_NODISCARD__ constexpr ArrayPair operator[](const len_t first, const len_t last) const noexcept {
			return this->substr(first, last);
		}

#endif // LL_REAL_CXX23

		#pragma endregion
		#pragma region Countable
		__LL_NODISCARD__ constexpr len_t len() const noexcept {
			return static_cast<len_t>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr len_t size() const noexcept { return this->len(); }
		__LL_NODISCARD__ constexpr len_t count() const noexcept { return this->len(); }

		#pragma endregion
		#pragma region std
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
			return this->len() == ZERO_UI64;
		}

		#pragma endregion
		#pragma region Other
		__LL_NODISCARD__ constexpr ll_bool_t isValid() const noexcept {
			return !this->empty() && (this->begin() < this->end());
		}
		constexpr void clear() noexcept { this->simpleClear(); }

		#pragma endregion
		#pragma endregion
	#pragma endregion
};

template<class T>
class Array {
	public:
		static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<T>, "Const type is forbidden!");
	protected:
		T* mem;
		T* mem_end;
	#pragma region Functions
	protected:
		constexpr void simpleClear() noexcept {
			this->mem = LL_NULLPTR;
			this->mem_end = LL_NULLPTR;
		}
	public:
		#pragma region Constructors
		constexpr Array() noexcept = delete;
		constexpr Array(T* mem, T* mem_end) noexcept : mem(mem), mem_end(mem_end) {}
		constexpr Array(T* mem, const len_t len) noexcept : Array(mem, mem + len) {}
		constexpr ~Array() noexcept {}

		#pragma endregion
		#pragma region CopyMove
		constexpr Array(const Array& other) noexcept
			: Array(other.mem, other.mem_end) {}
		constexpr Array& operator=(const Array& other) noexcept {
			this->mem = other.mem;
			this->mem_end = other.mem_end;
			return *this;
		}
		constexpr Array(Array&& other) noexcept : Array(other) {}
		constexpr Array& operator=(Array&& other) noexcept {
			Array::operator=(other);
			other.simpleClear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator const Array*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator Array*() noexcept { return this; }
		__LL_NODISCARD__ constexpr operator ArrayPair<T>() const noexcept {
			return ArrayPair<T>(*this);
		}
		__LL_NODISCARD__ constexpr ArrayPair<T> operator()() const noexcept {
			return ArrayPair<T>(*this);
		}

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
		__LL_NODISCARD__ constexpr T* get(const len_t pos) noexcept {
			return this->mem + pos;
		}
		__LL_NODISCARD__ constexpr const T* get(const len_t pos) const noexcept {
			return this->mem + pos;
		}
		__LL_NODISCARD__ constexpr Array get(const len_t first, const len_t last) noexcept {
			return Array(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr ArrayPair<T> get(const len_t first, const len_t last) const noexcept {
			return ArrayPair<T>(this->get(first), this->get(last));
		}

		__LL_NODISCARD__ constexpr T* rget(const len_t pos) noexcept {
			return this->mem_end - pos;
		}
		__LL_NODISCARD__ constexpr const T* rget(const len_t pos) const noexcept {
			return this->mem_end - pos;
		}
		__LL_NODISCARD__ constexpr Array rget(const len_t first, const len_t last) noexcept {
			return Array(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr ArrayPair<T> rget(const len_t first, const len_t last) const noexcept {
			return ArrayPair<T>(this->rget(first), this->rget(last));
		}

		__LL_NODISCARD__ constexpr Array substr(const len_t first, const len_t last) noexcept {
			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr ArrayPair<T> substr(const len_t first, const len_t last) const noexcept {
			return this->get(first, last);
		}

		__LL_NODISCARD__ constexpr T& operator[](const len_t pos) noexcept {
			return *this->get(pos);
		}
		__LL_NODISCARD__ constexpr const T& operator[](const len_t pos) const noexcept {
			return *this->get(pos);
		}
		__LL_NODISCARD__ constexpr T& operator^(const len_t pos) noexcept {
			return *this->rget(pos);
		}
		__LL_NODISCARD__ constexpr const T& operator^(const len_t pos) const noexcept {
			return *this->rget(pos);
		}

#if defined(LL_REAL_CXX23)
		__LL_NODISCARD__ constexpr Array operator[](const len_t first, const len_t last) noexcept {
			return this->substr(first, last);
		}
		__LL_NODISCARD__ constexpr ArrayPair operator[](const len_t first, const len_t last) const noexcept {
			return this->substr(first, last);
		}

#endif // LL_REAL_CXX23

		#pragma endregion
		#pragma region Countable
		__LL_NODISCARD__ constexpr len_t len() const noexcept {
			return static_cast<len_t>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr len_t size() const noexcept { return this->len(); }
		__LL_NODISCARD__ constexpr len_t count() const noexcept { return this->len(); }

		#pragma endregion
		#pragma region std
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
			return this->len() == ZERO_UI64;
		}

		#pragma endregion
		#pragma region Other
		__LL_NODISCARD__ constexpr ll_bool_t isValid() const noexcept {
			return !this->empty() && (this->begin() < this->end());
		}
		constexpr void clear() noexcept { this->simpleClear(); }

		#pragma endregion
		#pragma endregion
	#pragma endregion
};

#pragma region Array_ArrayPair_Compatibility
template<class T>
__LL_INLINE__ constexpr ArrayPair<T>::ArrayPair(const Array<T>& other) noexcept
	: mem(other.begin()), mem_end(other.end()) {}
template<class T>
__LL_INLINE__ constexpr ArrayPair<T>& ArrayPair<T>::operator=(const Array<T>& other) noexcept {
	this->mem = other.mem;
	this->mem_end = other.mem_end;
	return *this;
}
template<class T>
__LL_INLINE__ constexpr ArrayPair<T>::ArrayPair(Array<T>&& other) noexcept
	: mem(other.begin()), mem_end(other.end()) {}
template<class T>
__LL_INLINE__ constexpr ArrayPair<T>& ArrayPair<T>::operator=(Array<T>&& other) noexcept {
	this->mem = other.mem;
	this->mem_end = other.mem_end;
	other.simpleClear();
	return *this;
}

#pragma endregion
#pragma region Builders
template<class T, len_t N>
__LL_NODISCARD__ constexpr Array<T> make_Array(T(&arr)[N]) noexcept {
	return Array<T>(arr, arr + N);
}
template<class T, len_t N>
__LL_NODISCARD__ constexpr ArrayPair<T> make_ArrayPair(const T(&arr)[N]) noexcept {
	return ArrayPair<T>(arr, arr + N);
}
template<len_t N>
__LL_NODISCARD__ constexpr ArrayPair<ll_char_t> make_ArrayPair(const ll_char_t(&arr)[N]) noexcept {
	return ArrayPair<ll_char_t>(arr, arr + N - 1);
}
template<len_t N>
__LL_NODISCARD__ constexpr ArrayPair<ll_wchar_t> make_ArrayPair(const ll_wchar_t(&arr)[N]) noexcept {
	return ArrayPair<ll_wchar_t>(arr, arr + N - 1);
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
