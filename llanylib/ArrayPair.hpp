//////////////////////////////////////////////
//	ArrayPair.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ARRAYPAIR_HPP_) // Guard && version protector
	#if LLANYLIB_ARRAYPAIR_MAYOR_ != 7 || LLANYLIB_ARRAYPAIR_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "ArrayPair.hpp version error!"
		#else
			#error "ArrayPair.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ARRAYPAIR_MAYOR_ || LLANYLIB_ARRAYPAIR_MINOR_

#else !defined(LLANYLIB_ARRAYPAIR_HPP_)
#define LLANYLIB_ARRAYPAIR_HPP_
#define LLANYLIB_ARRAYPAIR_MAYOR_ 7
#define LLANYLIB_ARRAYPAIR_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace meta {

template<class T>
class Array;

template<class T>
class ArrayPair {
	public:
		using type = traits::template_types<T>;
		using __ArrayPair = traits::template_types<ArrayPair<T>>;
	protected:
		type::cptr mem;
		type::cptr mem_end;
	#pragma region Functions
	protected:
		constexpr void simpleClear() __LL_EXCEPT__ {
			this->mem = LL_NULLPTR;
			this->mem_end = LL_NULLPTR;
		}
	public:
		#pragma region Constructors
		constexpr ArrayPair() __LL_EXCEPT__ = delete;
		constexpr ArrayPair(type::cptr mem, type::cptr mem_end) __LL_EXCEPT__ : mem(mem), mem_end(mem_end) {}
		constexpr ArrayPair(type::cptr mem, const len_t len) __LL_EXCEPT__ : __ArrayPair::type(mem, mem + len) {}
		constexpr ~ArrayPair() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr ArrayPair(__ArrayPair::cref other) __LL_EXCEPT__
			: mem(other.mem), mem_end(other.mem_end) {}
		constexpr __ArrayPair::ref operator=(__ArrayPair::cref other) __LL_EXCEPT__ {
			this->mem = other.mem;
			this->mem_end = other.mem_end;
			return *this;
		}
		constexpr ArrayPair(__ArrayPair::move other) __LL_EXCEPT__
			: mem(other.mem), mem_end(other.mem_end){ other.simpleClear(); }
		constexpr __ArrayPair::ref operator=(__ArrayPair::move other) __LL_EXCEPT__ {
			this->mem = other.mem;
			this->mem_end = other.mem_end;
			other.simpleClear();
			return *this;
		}

		constexpr ArrayPair(const Array<T>& other) __LL_EXCEPT__;
		constexpr __ArrayPair::ref operator=(const Array<T>& other) __LL_EXCEPT__;
		constexpr ArrayPair(Array<T>&& other) __LL_EXCEPT__;
		constexpr __ArrayPair::ref operator=(Array<T>&& other) __LL_EXCEPT__;

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename __ArrayPair::cptr() const __LL_EXCEPT__ { return this; }
		__LL_NODISCARD__ constexpr operator typename __ArrayPair::ptr() __LL_EXCEPT__ { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
		__LL_NODISCARD__ constexpr typename type::cptr get(const len_t pos) const __LL_EXCEPT__ {
			return this->mem + pos;
		}
		__LL_NODISCARD__ constexpr typename __ArrayPair::type get(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return typename __ArrayPair::type(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr typename type::cptr rget(const len_t pos) const __LL_EXCEPT__ {
			return this->mem_end - pos;
		}
		__LL_NODISCARD__ constexpr typename __ArrayPair::type rget(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return typename __ArrayPair::type(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr typename __ArrayPair::type substr(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr typename type::cref operator[](const len_t pos) const __LL_EXCEPT__ {
			return *this->get(pos);
		}
		__LL_NODISCARD__ constexpr typename type::cref operator^(const len_t pos) const __LL_EXCEPT__ {
			return this->rget(pos);
		}
#if defined(LL_REAL_CXX23)
		__LL_NODISCARD__ constexpr typename __ArrayPair::type operator[](const len_t first, const len_t last) const __LL_EXCEPT__ {
			return this->substr(first, last);
		}

#endif // LL_REAL_CXX23

		#pragma endregion
		#pragma region Countable
		__LL_NODISCARD__ constexpr len_t len() const __LL_EXCEPT__ {
			return static_cast<len_t>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr len_t size() const __LL_EXCEPT__ { return this->len(); }
		__LL_NODISCARD__ constexpr len_t count() const __LL_EXCEPT__ { return this->len(); }

		#pragma endregion
		#pragma region std
		__LL_NODISCARD__ constexpr type::cptr data() const __LL_EXCEPT__ {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr type::cptr begin() const __LL_EXCEPT__ {
			return this->get(ZERO_UI64);
		}
		__LL_NODISCARD__ constexpr type::cptr end() const __LL_EXCEPT__ {
			return this->mem_end;
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const __LL_EXCEPT__ {
			return this->len() == ZERO_UI64;
		}

		#pragma endregion
		#pragma region Other
		__LL_NODISCARD__ constexpr ll_bool_t isValid() const __LL_EXCEPT__ {
			return !this->empty() && (this->begin() < this->end());
		}
		constexpr void clear() __LL_EXCEPT__ { this->simpleClear(); }

		#pragma endregion
		#pragma endregion
	#pragma endregion
};

template<class T>
class Array {
	public:
		using type = traits::template_types<T>;
		using __Array = traits::template_types<Array<T>>;
		using __ArrayPair = traits::template_types<ArrayPair<T>>;
	protected:
		type::ptr mem;
		type::cptr mem_end;
	#pragma region Functions
	protected:
		constexpr void simpleClear() __LL_EXCEPT__ {
			this->mem = LL_NULLPTR;
			this->mem_end = LL_NULLPTR;
		}
	public:
		#pragma region Constructors
		constexpr Array() __LL_EXCEPT__ = delete;
		constexpr Array(type::ptr mem, type::cptr mem_end) __LL_EXCEPT__ : mem(mem), mem_end(mem_end) {}
		constexpr Array(type::ptr mem, const len_t len) __LL_EXCEPT__ : Array(mem, mem + len) {}
		constexpr ~Array() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr Array(__Array::cref other) __LL_EXCEPT__
			: Array(other.mem, other.mem_end) {}
		constexpr __Array::ref operator=(__Array::cref other) __LL_EXCEPT__ {
			this->mem = other.mem;
			this->mem_end = other.mem_end;
			return *this;
		}
		constexpr Array(__Array::move other) __LL_EXCEPT__ : Array(other) {}
		constexpr __Array::ref operator=(__Array::move other) __LL_EXCEPT__ {
			__Array::operator=(other);
			other.__Array::type::simpleClear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename __Array::cptr() const __LL_EXCEPT__ { return this; }
		__LL_NODISCARD__ constexpr operator typename __Array::ptr() __LL_EXCEPT__ { return this; }
		__LL_NODISCARD__ constexpr operator typename __ArrayPair::type() const __LL_EXCEPT__ {
			return typename __ArrayPair::type(*this);
		}
		__LL_NODISCARD__ constexpr typename __ArrayPair::type operator()() const __LL_EXCEPT__ {
			return typename __ArrayPair::type(*this);
		}

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
		__LL_NODISCARD__ constexpr typename type::ptr get(const len_t pos) __LL_EXCEPT__ {
			return this->mem + pos;
		}
		__LL_NODISCARD__ constexpr typename type::cptr get(const len_t pos) const __LL_EXCEPT__ {
			return this->mem + pos;
		}
		__LL_NODISCARD__ constexpr typename __Array::type get(const len_t first, const len_t last) __LL_EXCEPT__ {
			return typename __Array::type(this->get(first), this->get(last));
		}
		__LL_NODISCARD__ constexpr typename __ArrayPair::type get(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return typename __ArrayPair::type(this->get(first), this->get(last));
		}

		__LL_NODISCARD__ constexpr typename type::ptr rget(const len_t pos) __LL_EXCEPT__ {
			return this->mem_end - pos;
		}
		__LL_NODISCARD__ constexpr typename type::cptr rget(const len_t pos) const __LL_EXCEPT__ {
			return this->mem_end - pos;
		}
		__LL_NODISCARD__ constexpr typename __Array::type rget(const len_t first, const len_t last) __LL_EXCEPT__ {
			return typename __Array::type(this->rget(first), this->rget(last));
		}
		__LL_NODISCARD__ constexpr typename __ArrayPair::type rget(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return typename __ArrayPair::type(this->rget(first), this->rget(last));
		}

		__LL_NODISCARD__ constexpr typename __Array::type substr(const len_t first, const len_t last) __LL_EXCEPT__ {
			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr typename __ArrayPair::type substr(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return this->get(first, last);
		}

		__LL_NODISCARD__ constexpr typename type::ref operator[](const len_t pos) __LL_EXCEPT__ {
			return *this->get(pos);
		}
		__LL_NODISCARD__ constexpr typename type::cref operator[](const len_t pos) const __LL_EXCEPT__ {
			return *this->get(pos);
		}
		__LL_NODISCARD__ constexpr typename type::ref operator^(const len_t pos) __LL_EXCEPT__ {
			return *this->rget(pos);
		}
		__LL_NODISCARD__ constexpr typename type::cref operator^(const len_t pos) const __LL_EXCEPT__ {
			return *this->rget(pos);
		}

#if defined(LL_REAL_CXX23)
		__LL_NODISCARD__ constexpr typename __Array::type operator[](const len_t first, const len_t last) __LL_EXCEPT__ {
			return this->substr(first, last);
		}
		__LL_NODISCARD__ constexpr typename __ArrayPair::type operator[](const len_t first, const len_t last) const __LL_EXCEPT__ {
			return this->substr(first, last);
		}

#endif // LL_REAL_CXX23

		#pragma endregion
		#pragma region Countable
		__LL_NODISCARD__ constexpr len_t len() const __LL_EXCEPT__ {
			return static_cast<len_t>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr len_t size() const __LL_EXCEPT__ { return this->len(); }
		__LL_NODISCARD__ constexpr len_t count() const __LL_EXCEPT__ { return this->len(); }

		#pragma endregion
		#pragma region std
		__LL_NODISCARD__ constexpr type::cptr data() __LL_EXCEPT__ {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr type::ptr data() const __LL_EXCEPT__ {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr type::ptr begin() __LL_EXCEPT__ {
			return this->get(ZERO_UI64);
		}
		__LL_NODISCARD__ constexpr type::cptr begin() const __LL_EXCEPT__ {
			return this->get(ZERO_UI64);
		}
		__LL_NODISCARD__ constexpr type::ptr rbegin() __LL_EXCEPT__ {
			return this->mem_end - 1;
		}
		__LL_NODISCARD__ constexpr type::cptr rbegin() const __LL_EXCEPT__ {
			return this->mem_end - 1;
		}
		__LL_NODISCARD__ constexpr type::cptr end() const __LL_EXCEPT__ {
			return this->mem_end;
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const __LL_EXCEPT__ {
			return this->len() == ZERO_UI64;
		}

		#pragma endregion
		#pragma region Other
		__LL_NODISCARD__ constexpr ll_bool_t isValid() const __LL_EXCEPT__ {
			return !this->empty() && (this->begin() < this->end());
		}
		constexpr void clear() __LL_EXCEPT__ { this->simpleClear(); }

		#pragma endregion
		#pragma endregion
	#pragma endregion
};

#pragma region Array_ArrayPair_Compatibility
template<class T>
__LL_INLINE__ constexpr ArrayPair<T>::ArrayPair(const Array<T>& other) __LL_EXCEPT__
	: mem(other.begin()), mem_end(other.end()) {}
template<class T>
__LL_INLINE__  constexpr ArrayPair<T>::__ArrayPair::ref ArrayPair<T>::operator=(const Array<T>& other) __LL_EXCEPT__ {
	this->mem = other.mem;
	this->mem_end = other.mem_end;
	return *this;
}
template<class T>
__LL_INLINE__ constexpr ArrayPair<T>::ArrayPair(Array<T>&& other) __LL_EXCEPT__
	: mem(other.mem), mem_end(other.mem_end){ other.simpleClear(); }
template<class T>
__LL_INLINE__ constexpr ArrayPair<T>::__ArrayPair::ref ArrayPair<T>::operator=(Array<T>&& other) __LL_EXCEPT__ {
	this->mem = other.mem;
	this->mem_end = other.mem_end;
	other.simpleClear();
	return *this;
}

#pragma endregion
#pragma region Builders
template<class T, len_t N>
__LL_NODISCARD__ constexpr Array<T> make_Array(T(&arr)[N]) {
	return Array<T>(arr, arr + N);
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
