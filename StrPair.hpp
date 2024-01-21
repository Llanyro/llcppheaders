/*
 *	StrPair.hpp
 *
 *	Created on: Sep 27, 2021
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLCPP_HEADER_STRPAIR_HPP_
#define LLCPP_HEADER_STRPAIR_HPP_

#include "llanytypesbase.hpp"

namespace llcpp {

// Simply stores a string
class LL_SHARED_LIB StrPair {
	public:
		using string_type = ll_string_t;
		using string_size_type = len_t;
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(StrPair, StrPair);
	public:
		string_type str;
		string_size_type len;

		constexpr StrPair() __LL_EXCEPT__  : StrPair(LL_NULLPTR, 0ull) {}
		constexpr StrPair(string_type str, const string_size_type len) __LL_EXCEPT__
			: str(str), len(len)
		{}
		constexpr ~StrPair() __LL_EXCEPT__ {}

		constexpr StrPair(__cref_StrPair other) __LL_EXCEPT__ : StrPair(other.str, other.len) {}
		constexpr __ref_StrPair operator=(__cref_StrPair other) __LL_EXCEPT__ {
			this->len = other.len;
			this->str = other.str;
			return *this;
		}

		constexpr StrPair(__move_StrPair other) __LL_EXCEPT__ : StrPair(other.str, other.len) {
			other.clear();
		}
		constexpr __ref_StrPair operator=(__move_StrPair other) __LL_EXCEPT__ {
			this->len = other.len;
			this->str = other.str;
			other.clear();
			return *this;
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator==(string_type str) const __LL_EXCEPT__ {
			return str == this->str;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__cref_StrPair str) const __LL_EXCEPT__ {
			return
				this->str == str.str &&
				this->len == str.len;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(string_type str) const __LL_EXCEPT__ {
			return !this->operator==(str);
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(__cref_StrPair str) const __LL_EXCEPT__ {
			return !this->operator==(str);
		}
		__LL_NODISCARD__ constexpr operator ll_bool_t() const __LL_EXCEPT__ {
			return
				static_cast<ll_bool_t>(this->str) &&
				static_cast<ll_bool_t>(this->len > 0);
		}
		__LL_NODISCARD__ constexpr operator string_type() const __LL_EXCEPT__ {
			return this->str;
		}
		__LL_NODISCARD__ constexpr operator string_size_type() const __LL_EXCEPT__ {
			return this->len;
		}

		constexpr void clear() {
			this->len = 0;
			this->str = nullptr;
		}

		template<class __T, len_t __N>
		__LL_NODISCARD__ static constexpr StrPair pair_str(__T(&str)[__N]) __LL_EXCEPT__ {
			return StrPair{ str, __N - 1 };
		}
};

} // namespace llcpp

#endif /* LLCPP_HEADER_STRPAIR_HPP_ */
