//////////////////////////////////////////////
//	ArrayPair.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 6.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_ARRAYPAIR_HPP_) // Guard && version protector
	#if LLANYLIB_ARRAYPAIR_MAYOR_ != 6 || LLANYLIB_ARRAYPAIR_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "ArrayPair.hpp version error!"
		#else
			#error "ArrayPair.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_ARRAYPAIR_MAYOR_ || LLANYLIB_ARRAYPAIR_MINOR_

#else !defined(LLANYLIB_ARRAYPAIR_HPP_)
#define LLANYLIB_ARRAYPAIR_HPP_
#define LLANYLIB_ARRAYPAIR_MAYOR_ 6
#define LLANYLIB_ARRAYPAIR_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace meta {

template<class T>
class ArrayPair {
	public:
		using type = traits::template_types<T>;
		using __ArrayPair = traits::template_types<ArrayPair<T>>;
		using csubarr = std::pair<typename type::cptr, typename type::cptr>;
	protected:
		type::cptr mem;
		type::cptr mem_end;
	#pragma region Functions
	protected:
		constexpr void simple_clear() __LL_EXCEPT__ {
			this->mem = LL_NULLPTR;
			this->mem_end = LL_NULLPTR;
		}
	public:
		#pragma region Constructors
		constexpr ArrayPair() __LL_EXCEPT__ = delete;
		constexpr ArrayPair(type::cptr mem, type::cptr mem_end) __LL_EXCEPT__ : mem(mem), mem_end(mem_end) {}
		constexpr ArrayPair(type::cptr mem, const len_t len) __LL_EXCEPT__ : ArrayPair(mem, mem + len) {}
		constexpr ArrayPair(std::pair<typename type::cptr, typename type::cptr>& pair) __LL_EXCEPT__ : ArrayPair(pair.first, pair.second) {}
		constexpr ArrayPair(std::pair<typename type::ptr, typename type::cptr>& pair) __LL_EXCEPT__ : ArrayPair(pair.first, pair.second) {}
		constexpr ArrayPair(std::pair<typename type::ptr, typename type::ptr>& pair) __LL_EXCEPT__ : ArrayPair(pair.first, pair.second) {}
		constexpr ArrayPair(std::pair<typename type::cptr, typename type::ptr>& pair) __LL_EXCEPT__ : ArrayPair(pair.first, pair.second) {}
		constexpr ~ArrayPair() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		constexpr ArrayPair(__ArrayPair::cref other) __LL_EXCEPT__ : mem(other.mem), mem_end(other.mem_end) {}
		constexpr __ArrayPair::ref operator=(__ArrayPair::cref other) __LL_EXCEPT__ {
			this->mem = other.mem;
			this->mem_end = other.mem_end;
			return *this;
		}
		constexpr ArrayPair(__ArrayPair::move other) __LL_EXCEPT__
			: mem(other.mem), mem_end(other.mem_end){ other.clear(); }
		constexpr __ArrayPair::ref operator=(__ArrayPair::move other) __LL_EXCEPT__ {
			this->mem = other.mem;
			this->mem_end = other.mem_end;
			other.simple_clear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename __ArrayPair::cptr() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename __ArrayPair::ptr() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr type::cptr get(const len_t pos) const __LL_EXCEPT__ {
			return this->mem + pos;
		}
		__LL_NODISCARD__ constexpr csubarr get(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return csubarr{ this->get(first), this->get(last) };
		}
		__LL_NODISCARD__ constexpr csubarr substr(const len_t first, const len_t last) const __LL_EXCEPT__ {
			return this->get(first, last);
		}
		__LL_NODISCARD__ constexpr type::cref operator[] (const len_t pos) const __LL_EXCEPT__ {
			return this->mem[pos];
		}
		#if defined(LL_REAL_CXX23)
		__LL_NODISCARD__ constexpr csubarr operator[](const len_t first, const len_t last) const __LL_EXCEPT__ {
			return this->substr(first, last);
		}
		#endif // LL_REAL_CXX23

		#pragma region std
		__LL_NODISCARD__ constexpr typename type::cptr data() const __LL_EXCEPT__ {
			return this->mem;
		}
		__LL_NODISCARD__ constexpr typename type::cptr begin() const __LL_EXCEPT__ {
			return this->mem;
		}
		__LL_NODISCARD__ constexpr type::cptr end() const __LL_EXCEPT__ {
			return this->mem_end;
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const __LL_EXCEPT__ {
			return !this->isValid();
		}
		#pragma endregion

		__LL_NODISCARD__ constexpr ll_bool_t isValid() const __LL_EXCEPT__ {
			return
				static_cast<ll_bool_t>(this->mem) &&
				static_cast<ll_bool_t>(this->mem_end);
		}
		constexpr void clear() __LL_EXCEPT__ { this->simple_clear(); }

		__LL_NODISCARD__ constexpr operator len_t() const __LL_EXCEPT__ {
			return static_cast<len_t>(this->end() - this->begin());
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
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAYPAIR_HPP_
