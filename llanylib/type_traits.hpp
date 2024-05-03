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

#include "Countable.hpp"

namespace llcpp {

template<class T>
class ArrayPair : public CountableL {
	public:
		using type = traits::template_types<T>;
		using __ArrayPair = traits::template_types<ArrayPair<T>>;
		using csubstr = std::pair<typename type::cptr, typename type::cptr>;
	protected:
		type::cptr data;
	protected:
		constexpr void simple_clear() __LL_EXCEPT__ { this->data = LL_NULLPTR; }
	public:
		#pragma region Constructors
		constexpr ArrayPair() __LL_EXCEPT__ = delete;
		constexpr ArrayPair(type::cptr data, const len_t len) __LL_EXCEPT__
			: CountableL(len), data(data) {}
		constexpr ArrayPair() __LL_EXCEPT__ {}
		#pragma endregion
		#pragma region CopyMove
		constexpr ArrayPair(__ArrayPair::cref other) __LL_EXCEPT__
			: CountableL(other), data(other.data) {}
		constexpr __ArrayPair::ref operator=(__ArrayPair::cref other) __LL_EXCEPT__ {
			CountableL::operator=(other);
			this->data = other.data;
			return *this;
		}
		constexpr ArrayPair(__ArrayPair::move other) __LL_EXCEPT__
			: CountableL(other), data(other.data) { other.clear(); }
		constexpr __ArrayPair::ref operator=(__ArrayPair::move other) __LL_EXCEPT__ {
			this->data = other.data;
			CountableL::operator=(other.operator __ArrayPair::move());
			other.simple_clear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator __ArrayPair::cref() const __LL_EXCEPT__ { return *this; }
		__LL_NODISCARD__ constexpr operator __ArrayPair::ref() __LL_EXCEPT__ { return *this; }
		__LL_NODISCARD__ constexpr operator __ArrayPair::move() __LL_EXCEPT__ { return std::move(*this); }

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr type::cptr get(const len_t pos) const __LL_EXCEPT__ {
			return this->__data + pos;
		}
		__LL_NODISCARD__ constexpr csubstr get(const len_t _begin, const len_t _end) const __LL_EXCEPT__ {
			return csubstr{ this->get(_begin) , this->get(_end) };
		}
		__LL_NODISCARD__ constexpr csubstr substr(const len_t _begin, const len_t _end) const __LL_EXCEPT__ {
			return this->get(_begin, _end);
		}
		__LL_NODISCARD__ constexpr type::cref operator[] (const len_t pos) const __LL_EXCEPT__ {
			return this->__data[pos];
		}
		#ifdef LL_REAL_CXX23
		__LL_NODISCARD__ constexpr csubstr operator[](const len_t _begin, const len_t _end) const __LL_EXCEPT__ {
			return this->substr(_begin, _end);
		}
		#endif // LL_REAL_CXX23

		__LL_NODISCARD__ constexpr type::cptr begin() const __LL_EXCEPT__ {
			return this->data;
		}
		__LL_NODISCARD__ constexpr type::cptr begin() const __LL_EXCEPT__ {
			return this->data;
		}
		__LL_NODISCARD__ constexpr type::cptr end() const __LL_EXCEPT__ {
			return this->data + this->operator len_t();
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValid() const __LL_EXCEPT__ {
			return
				static_cast<ll_bool_t>(this->data) &&
				static_cast<ll_bool_t>(this->operator len_t());
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const __LL_EXCEPT__ {
			return !this->isValid();
		}
		constexpr void clear() __LL_EXCEPT__ {
			CountableL::clear();
			this->simple_clear();
		}
		#pragma endregion
};

using StrPair  = ArrayPair<ll_char_t>;
using wStrPair = ArrayPair<ll_wchar_t>;

namespace traits {
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_strpair_type_v = std::_Is_any_of_v<std::remove_const_t<T>, StrPair, uStrPair, wStrPair>;
} // namespace traits

} // namespace llcpp

#endif // LLANYLIB_TYPETRAITS_HPP_
