//////////////////////////////////////////////
//	Countable.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 4.2							//
//////////////////////////////////////////////

#if defined(LLANYLIB_COUNTABLE_HPP_) // Guard && version protector
	#if LLANYLIB_COUNTABLE_MAYOR_ != 4 || LLANYLIB_COUNTABLE_MINOR_ < 2
		#error "Countable.hpp version error!"
	#endif // LLANYLIB_COUNTABLE_MAYOR_ || LLANYLIB_COUNTABLE_MINOR_

#else !defined(LLANYLIB_COUNTABLE_HPP_)
#define LLANYLIB_COUNTABLE_HPP_
#define LLANYLIB_COUNTABLE_MAYOR_ 4
#define LLANYLIB_COUNTABLE_MINOR_ 2

#include "types.hpp"

#define DO_IF_VALID(func) \
	ll_bool_t result = LL_TRUE; \
	if ((result = this->inRange(position)) == llcpp::LL_TRUE) \
		func; \
	return result;

#define DO_IF_VALID_2_POSITIONS(pos1, pos2, func) \
	ll_bool_t result = LL_TRUE; \
	if ((result = (this->inRange(pos1) && this->inRange(pos2))) == llcpp::LL_TRUE) \
		func; \
	return result;

namespace llcpp {

/*!
 *	@class Countable
 *	@classtype Base
 *	@template True
 *	@brief Stores and counts items objects, etc...
 * 
 *	Useful in lists, vector or countable or accumulative objects
 *
 *	@sa @ref icountable
 *
 *	@since Added in version 2.0.
 *
 *	@ingroup util
 *	@ingroup list
 */
template<class T, T ZERO_VAL>
class LL_SHARED_LIB Countable {
	private:
		using __internal__Countable__ = Countable<T, ZERO_VAL>;
	public:
		__LL_CLASS_TEMPLATE_TYPE__(T);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__Countable__, Countable);
		static constexpr T ZERO = ZERO_VAL;
	private:
		__type length;
	protected:
		__LL_NODISCARD__ constexpr __ref lenRef() __LL_EXCEPT__ { return this->length; }

		constexpr void operator++() __LL_EXCEPT__ { ++this->length; }
		constexpr void operator--() __LL_EXCEPT__ { --this->length; }
		__LL_NODISCARD__ constexpr __type operator++(int) __LL_EXCEPT__ { return this->length++; }
		__LL_NODISCARD__ constexpr __type operator--(int) __LL_EXCEPT__ { return this->length--; }

		constexpr void operator+=(__ctype value) __LL_EXCEPT__ { this->length += value; }
		constexpr void operator-=(__ctype value) __LL_EXCEPT__ { this->length -= value; }
		constexpr void operator+=(__cref_Countable other) __LL_EXCEPT__ {
			this->length += other.length;
		}
		constexpr void operator-=(__cref_Countable other) __LL_EXCEPT__ {
			this->length -= other.length;
		}

		__LL_NODISCARD__ constexpr __Countable operator+(__ctype value) const __LL_EXCEPT__ {
			return __Countable(this->length + value);
		}
		__LL_NODISCARD__ constexpr __Countable operator-(__ctype value) const __LL_EXCEPT__ {
			return __Countable(this->length - value);
		}
		__LL_NODISCARD__ constexpr __Countable operator+(__cref_Countable other) const __LL_EXCEPT__ {
			return __Countable(this->length + other.length);
		}
		__LL_NODISCARD__ constexpr __Countable operator-(__cref_Countable other) const __LL_EXCEPT__ {
			return __Countable(this->length - other.length);
		}

		constexpr __type operator=(__ctype value) __LL_EXCEPT__ {
			return this->length = value;
		}
	public:
		constexpr Countable() __LL_EXCEPT__ : Countable(ZERO_VAL) {}
		constexpr Countable(__ctype length) __LL_EXCEPT__ : length(length) {}
		constexpr ~Countable() __LL_EXCEPT__ {}

		constexpr Countable(__cref_Countable other) __LL_EXCEPT__
			: Countable(other.length) {}
		constexpr Countable& operator=(__cref_Countable other) __LL_EXCEPT__ {
			this->length = other.length;
			return *this;
		}

		constexpr Countable(__move_Countable other) __LL_EXCEPT__
			: Countable(other.length) { other.clear(); }
		constexpr Countable& operator=(__move_Countable other) __LL_EXCEPT__ {
			this->length = other.length;
			other.length = 0ull;
			return *this;
		}

		__LL_NODISCARD__ constexpr operator __type() const __LL_EXCEPT__ {
			return this->length;
		}
		__LL_NODISCARD__ constexpr __type count() const __LL_EXCEPT__ {
			return this->operator __type();
		}
		__LL_NODISCARD__ constexpr __type len() const __LL_EXCEPT__ {
			return this->operator __type();
		}
		__LL_NODISCARD__ constexpr __type size() const __LL_EXCEPT__ {
			return this->operator __type();
		}
		__LL_NODISCARD__ constexpr void clear() __LL_EXCEPT__ { this->length = ZERO_VAL; }
		__LL_NODISCARD__ constexpr ll_bool_t inRange(__ctype position) const __LL_EXCEPT__ {
			return position < this->operator __type();
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator>(__cref_Countable other) const __LL_EXCEPT__ {
			return this->operator __type() > other.operator __type();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(__cref_Countable other) const __LL_EXCEPT__ {
			return this->operator __type() >= other.operator __type();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(__cref_Countable other) const __LL_EXCEPT__ {
			return this->operator __type() < other.operator __type();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(__cref_Countable other) const __LL_EXCEPT__ {
			return this->operator __type() <= other.operator __type();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__cref_Countable other) const __LL_EXCEPT__ {
			return this->operator __type() == other.operator __type();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(__cref_Countable other) const __LL_EXCEPT__ {
			return this->operator __type() != other.operator __type();
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator>(__ctype value) const __LL_EXCEPT__ {
			return this->operator __type() > value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(__ctype value) const __LL_EXCEPT__ {
			return this->operator __type() >= value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(__ctype value) const __LL_EXCEPT__ {
			return this->operator __type() < value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(__ctype value) const __LL_EXCEPT__ {
			return this->operator __type() <= value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(__ctype value) const __LL_EXCEPT__ {
			return this->operator __type() == value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(__ctype value) const __LL_EXCEPT__ {
			return this->operator __type() != value;
		}

		__LL_NODISCARD__ constexpr operator __cref_Countable() const __LL_EXCEPT__ {
			return *this;
		}
		__LL_NODISCARD__ constexpr operator __ref_Countable() __LL_EXCEPT__ {
			return *this;
		}
};

using CountableB = Countable<b64, 0ull>;
using CountableL = Countable<len_t, 0ull>;

} // namespace llcpp

#endif // LLANYLIB_COUNTABLE_HPP_
