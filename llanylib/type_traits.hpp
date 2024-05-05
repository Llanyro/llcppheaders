//////////////////////////////////////////////
//	type_traits.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_TYPETRAITS_HPP_) // Guard && version protector
	#if LLANYLIB_TYPETRAITS_MAYOR_ != 5 || LLANYLIB_TYPETRAITS_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "type_traits.hpp version error!"
		#else
			#error "type_traits.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_TYPETRAITS_MAYOR_ || LLANYLIB_TYPETRAITS_MINOR_

#else !defined(LLANYLIB_TYPETRAITS_HPP_)
#define LLANYLIB_TYPETRAITS_HPP_
#define LLANYLIB_TYPETRAITS_MAYOR_ 5
#define LLANYLIB_TYPETRAITS_MINOR_ 0

#include "traits.hpp"

namespace llcpp {

template<class T>
class ArrayPair {
	public:
		using type = traits::template_types<T>;
		using __ArrayPair = traits::template_types<ArrayPair<T>>;
		using csubarr = std::pair<typename type::cptr, typename type::cptr>;
	protected:
		type::cptr _data;
		type::cptr _end;
	#pragma region Functions
	protected:
		constexpr void simple_clear() __LL_EXCEPT__ {
			this->_data = LL_NULLPTR;
			this->_end = LL_NULLPTR;
		}
	public:
		#pragma region Constructors
		constexpr ArrayPair() __LL_EXCEPT__ = delete;
		constexpr ArrayPair(type::cptr _begin, type::cptr _end) __LL_EXCEPT__ : _data(_begin), _end(_end) {}
		constexpr ArrayPair(type::cptr _begin, const len_t len) __LL_EXCEPT__ : ArrayPair(_begin, _begin + len) {}
		constexpr ArrayPair(std::pair<typename type::cptr, typename type::cptr>& pair) __LL_EXCEPT__ : ArrayPair(pair.first, pair.second) {}
		constexpr ArrayPair(std::pair<typename type::ptr, typename type::cptr>& pair) __LL_EXCEPT__ : ArrayPair(pair.first, pair.second) {}
		constexpr ArrayPair(std::pair<typename type::ptr, typename type::ptr>& pair) __LL_EXCEPT__ : ArrayPair(pair.first, pair.second) {}
		constexpr ArrayPair(std::pair<typename type::ptr, typename type::cptr>& pair) __LL_EXCEPT__ : ArrayPair(pair.first, pair.second) {}
		constexpr ~ArrayPair() __LL_EXCEPT__ {}
		#pragma endregion
		#pragma region CopyMove
		constexpr ArrayPair(__ArrayPair::cref other) __LL_EXCEPT__ : _data(other._data), _end(other._end) {}
		constexpr __ArrayPair::ref operator=(__ArrayPair::cref other) __LL_EXCEPT__ {
			this->_data = other._data;
			this->_end = other._end;
			return *this;
		}
		constexpr ArrayPair(__ArrayPair::move other) __LL_EXCEPT__
			: _data(other._data), _end(other._end){ other.clear(); }
		constexpr __ArrayPair::ref operator=(__ArrayPair::move other) __LL_EXCEPT__ {
			this->_data = other._data;
			this->_end = other._end;
			other.simple_clear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename __ArrayPair::cref() const __LL_EXCEPT__ { return *this; }
		__LL_NODISCARD__ constexpr operator typename __ArrayPair::ref() __LL_EXCEPT__ { return *this; }
		__LL_NODISCARD__ constexpr operator typename __ArrayPair::move() __LL_EXCEPT__ { return std::move(*this); }

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr type::cptr get(const len_t pos) const __LL_EXCEPT__ {
			return this->_data + pos;
		}
		__LL_NODISCARD__ constexpr csubarr get(const len_t _begin, const len_t _end) const __LL_EXCEPT__ {
			return csubarr{ this->get(_begin) , this->get(_end) };
		}
		__LL_NODISCARD__ constexpr csubarr substr(const len_t _begin, const len_t _end) const __LL_EXCEPT__ {
			return this->get(_begin, _end);
		}
		__LL_NODISCARD__ constexpr type::cref operator[] (const len_t pos) const __LL_EXCEPT__ {
			return this->_data[pos];
		}
		#ifdef LL_REAL_CXX23
		__LL_NODISCARD__ constexpr csubarr operator[](const len_t _begin, const len_t _end) const __LL_EXCEPT__ {
			return this->substr(_begin, _end);
		}
		#endif // LL_REAL_CXX23

		#pragma region std
		__LL_NODISCARD__ constexpr typename type::cptr data() const __LL_EXCEPT__ {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr typename type::cptr begin() const __LL_EXCEPT__ {
			return this->get(0ull);
		}
		__LL_NODISCARD__ constexpr type::cptr end() const __LL_EXCEPT__ {
			return this->_data + this->operator len_t();
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const __LL_EXCEPT__ {
			return !this->isValid();
		}
		#pragma endregion

		__LL_NODISCARD__ constexpr ll_bool_t isValid() const __LL_EXCEPT__ {
			return
				static_cast<ll_bool_t>(this->_data) &&
				static_cast<ll_bool_t>(this->operator len_t());
		}
		constexpr void clear() __LL_EXCEPT__ { this->simple_clear(); }

		__LL_NODISCARD__ constexpr operator len_t() const __LL_EXCEPT__ {
			return this->end() - this->begin();
		}
		__LL_NODISCARD__ constexpr len_t count() const __LL_EXCEPT__ {
			return this->operator len_t();
		}
		__LL_NODISCARD__ constexpr len_t len() const __LL_EXCEPT__ {
			return this->operator len_t();
		}
		__LL_NODISCARD__ constexpr len_t size() const __LL_EXCEPT__ {
			return this->operator len_t();
		}
		#pragma endregion
	#pragma endregion
};

using StrPair  = ArrayPair<ll_char_t>;
using wStrPair = ArrayPair<ll_wchar_t>;

namespace traits {
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_strpair_type_v = std::_Is_any_of_v<T, StrPair, wStrPair>;

} // namespace traits
} // namespace llcpp

#endif // LLANYLIB_TYPETRAITS_HPP_
