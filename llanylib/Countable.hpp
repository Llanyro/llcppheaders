//////////////////////////////////////////////
//	Countable.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_COUNTABLE_HPP_) // Guard && version protector
	#if LLANYLIB_COUNTABLE_MAYOR_ != 5 || LLANYLIB_COUNTABLE_MINOR_ < 0
		#error "Countable.hpp version error!"
	#endif // LLANYLIB_COUNTABLE_MAYOR_ || LLANYLIB_COUNTABLE_MINOR_

#else !defined(LLANYLIB_COUNTABLE_HPP_)
#define LLANYLIB_COUNTABLE_HPP_
#define LLANYLIB_COUNTABLE_MAYOR_ 5
#define LLANYLIB_COUNTABLE_MINOR_ 0

#include "traits.hpp"

#define COUNTABLE_DO_IF_VALID(func) \
	ll_bool_t result = LL_TRUE; \
	if ((result = this->inRange(position)) == llcpp::LL_TRUE) \
		func; \
	return result;

#define COUNTABLE_DO_IF_VALID_2_POSITIONS(pos1, pos2, func) \
	ll_bool_t result = LL_TRUE; \
	if ((result = (this->inRange(pos1) && this->inRange(pos2))) == llcpp::LL_TRUE) \
		func; \
	return result;

namespace llcpp {

template<class T, T ZERO_VAL>
class LL_SHARED_LIB Countable {
	public:
		static constexpr T ZERO = ZERO_VAL;
		using type = traits::template_types<T>;
		using __Countable = traits::template_types<Countable<T, ZERO_VAL>>;
		static_assert(traits::is_basic_type_v<T>, "Countable contains basic type only");
	private:
		type::type length;
	protected:
		__LL_NODISCARD__ constexpr type::ref lenRef() __LL_EXCEPT__ { return this->length; }

		constexpr void operator++() __LL_EXCEPT__ { ++this->length; }
		constexpr void operator--() __LL_EXCEPT__ { --this->length; }
		__LL_NODISCARD__ constexpr type::type operator++(int) __LL_EXCEPT__ { return this->length++; }
		__LL_NODISCARD__ constexpr type::type operator--(int) __LL_EXCEPT__ { return this->length--; }

		constexpr void operator+=(type::ctype value) __LL_EXCEPT__ { this->length += value; }
		constexpr void operator-=(type::ctype value) __LL_EXCEPT__ { this->length -= value; }
		constexpr void operator+=(__Countable::cref other) __LL_EXCEPT__ {
			this->length += other.length;
		}
		constexpr void operator-=(__Countable::cref other) __LL_EXCEPT__ {
			this->length -= other.length;
		}

		__LL_NODISCARD__ constexpr __Countable::type operator+(type::ctype value) const __LL_EXCEPT__ {
			return __Countable::type(this->length + value);
		}
		__LL_NODISCARD__ constexpr __Countable::type operator-(type::ctype value) const __LL_EXCEPT__ {
			return __Countable::type(this->length - value);
		}
		__LL_NODISCARD__ constexpr __Countable::type operator+(__Countable::cref other) const __LL_EXCEPT__ {
			return __Countable::type(this->length + other.length);
		}
		__LL_NODISCARD__ constexpr __Countable::type operator-(__Countable::cref other) const __LL_EXCEPT__ {
			return __Countable::type(this->length - other.length);
		}

		constexpr type::type operator=(type::ctype value) __LL_EXCEPT__ {
			return this->length = value;
		}
	public:
		constexpr Countable() __LL_EXCEPT__ : Countable(ZERO_VAL) {}
		constexpr Countable(type::ctype length) __LL_EXCEPT__ : length(length) {}
		constexpr ~Countable() __LL_EXCEPT__ {}

		constexpr Countable(__Countable::cref other) __LL_EXCEPT__
			: Countable(other.length) {}
		constexpr Countable& operator=(__Countable::cref other) __LL_EXCEPT__ {
			this->length = other.length;
			return *this;
		}

		constexpr Countable(__Countable::move other) __LL_EXCEPT__
			: Countable(other.length) { other.clear(); }
		constexpr Countable& operator=(__Countable::move other) __LL_EXCEPT__ {
			this->length = other.length;
			other.length = ZERO_VAL;
			return *this;
		}

		__LL_NODISCARD__ constexpr operator type::type() const __LL_EXCEPT__ {
			return this->length;
		}
		__LL_NODISCARD__ constexpr type::type count() const __LL_EXCEPT__ {
			return this->operator type::type();
		}
		__LL_NODISCARD__ constexpr type::type len() const __LL_EXCEPT__ {
			return this->operator type::type();
		}
		__LL_NODISCARD__ constexpr type::type size() const __LL_EXCEPT__ {
			return this->operator type::type();
		}
		__LL_NODISCARD__ constexpr void clear() __LL_EXCEPT__ { this->length = ZERO_VAL; }
		__LL_NODISCARD__ constexpr ll_bool_t inRange(type::ctype position) const __LL_EXCEPT__ {
			return position < this->operator type::type();
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator>(__Countable::cref other) const __LL_EXCEPT__ {
			return this->operator type::type() > other.operator type::type();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(__Countable::cref other) const __LL_EXCEPT__ {
			return this->operator type::type() >= other.operator type::type();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(__Countable::cref other) const __LL_EXCEPT__ {
			return this->operator type::type() < other.operator type::type();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(__Countable::cref other) const __LL_EXCEPT__ {
			return this->operator type::type() <= other.operator type::type();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__Countable::cref other) const __LL_EXCEPT__ {
			return this->operator type::type() == other.operator type::type();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(__Countable::cref other) const __LL_EXCEPT__ {
			return this->operator type::type() != other.operator type::type();
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator>(type::ctype value) const __LL_EXCEPT__ {
			return this->operator type::type() > value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(type::ctype value) const __LL_EXCEPT__ {
			return this->operator type::type() >= value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(type::ctype value) const __LL_EXCEPT__ {
			return this->operator type::type() < value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(type::ctype value) const __LL_EXCEPT__ {
			return this->operator type::type() <= value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(type::ctype value) const __LL_EXCEPT__ {
			return this->operator type::type() == value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(type::ctype value) const __LL_EXCEPT__ {
			return this->operator type::type() != value;
		}

		__LL_NODISCARD__ constexpr operator typename __Countable::cref() const __LL_EXCEPT__ { return *this; }
		__LL_NODISCARD__ constexpr operator typename __Countable::ref() __LL_EXCEPT__ { return *this; }
};

using CountableB = Countable<b64, 0ull>;
using CountableL = Countable<len_t, 0ull>;

} // namespace llcpp

#endif // LLANYLIB_COUNTABLE_HPP_
