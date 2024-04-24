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
		#error "type_traits.hpp version error!"
	#endif // LLANYLIB_TYPETRAITS_MAYOR_ || LLANYLIB_TYPETRAITS_MINOR_

#else !defined(LLANYLIB_TYPETRAITS_HPP_)
#define LLANYLIB_TYPETRAITS_HPP_
#define LLANYLIB_TYPETRAITS_MAYOR_ 5
#define LLANYLIB_TYPETRAITS_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace traits {

template<class T>
struct template_types {
	static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
	static_assert(!std::is_const_v<T>, "T cannot be const!\nFunctions will use all types as const internally.");

	using conversor = traits::type_conversor<T>;

	using raw = conversor::to_raw_t;
	using type = T;
	using ctype = const T;
	//using ctype = conversor::to_const_t;

	using ref = type&;
	//using ref = conversor::to_reference_t<LL_TRUE>;
	using cref = const type&;
	//using cref = conversor::to_const_reference_t<LL_TRUE>;
	using move = conversor::to_movement_t;

	using ptr = conversor::get_ptr_remove_reference_t;
	// [TOFIX]
	using cptr = conversor::get_const_ptr_remove_reference::value;
	using ptrref = traits::type_conversor<ptr>::to_reference_t<LL_TRUE>;

	using input = std::conditional_t<traits::is_basic_type_v<type>, type, ref>;
	using cinput = std::conditional_t<traits::is_basic_type_v<type>, ctype, cref>;
};

} // namespace traits
} // namespace llcpp

template<class T>
class ArrayPair {
	public:
		using type = llcpp::traits::template_types<T>;
		using __ArrayPair = llcpp::traits::template_types<ArrayPair<T>>;
	protected:
		type::cptr data;
		len_t len;
	public:
		constexpr ArrayPair(type::cref data, const len_t len) __LL_EXCEPT__
			: data(&data), len(len) {}
		constexpr ArrayPair() __LL_EXCEPT__ {}

		constexpr ArrayPair(__ArrayPair::cref other) __LL_EXCEPT__
			: data(other.data), len(other.len) {}
		constexpr __ArrayPair::ref operator=(__ArrayPair::cref other) __LL_EXCEPT__ {
			this->data = other.data;
			this->len = other.len;
			return *this;
		}
		constexpr ArrayPair(__ArrayPair::move other) __LL_EXCEPT__
			: data(other.data), len(other.len) { other.clear(); }
		constexpr __ArrayPair::ref operator=(__ArrayPair::move other) __LL_EXCEPT__ {
			this->data = other.data;
			this->len = other.len;
			other.clear();
			return *this;
		}

		__LL_NODISCARD__ constexpr type::cptr begin() const __LL_EXCEPT__ { return this->data; }
		__LL_NODISCARD__ constexpr type::cptr end() const __LL_EXCEPT__ { return this->data + this->len; }
		__LL_NODISCARD__ constexpr len_t length() const __LL_EXCEPT__ { return this->len; }
		__LL_NODISCARD__ constexpr ll_bool_t isValid() const __LL_EXCEPT__ {
			return
				static_cast<ll_bool_t>(this->data) &&
				static_cast<ll_bool_t>(this->len);
		}
		constexpr void clear() __LL_EXCEPT__ {
			this->data = LL_NULLPTR;
			this->len = 0ull;
		}
};

using StrPair  = ArrayPair<ll_char_t>;
using uStrPair = ArrayPair<ll_uchar_t>;
using wStrPair = ArrayPair<ll_wchar_t>;

#endif // LLANYLIB_TYPETRAITS_HPP_
