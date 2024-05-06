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
		#if defined(LL_REAL_CXX23)
			#warning "Countable.hpp version error!"
		#else
			#error "Countable.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_COUNTABLE_MAYOR_ || LLANYLIB_COUNTABLE_MINOR_

#else !defined(LLANYLIB_COUNTABLE_HPP_)
#define LLANYLIB_COUNTABLE_HPP_
#define LLANYLIB_COUNTABLE_MAYOR_ 5
#define LLANYLIB_COUNTABLE_MINOR_ 0

#include "traits.hpp"

namespace llcpp {

template<class T, T ZERO_VAL>
class LL_SHARED_LIB Countable {
	public:
		static constexpr T ZERO = ZERO_VAL;
		using type = traits::template_types<T>;
		using __Countable = traits::template_types<Countable<T, ZERO_VAL>>;
	private:
		type::type length;
	#pragma region Functions
	protected:
		#pragma region Protected
		__LL_NODISCARD__ constexpr type::ref lenRef() __LL_EXCEPT__ { return this->length; }

		constexpr void operator++() __LL_EXCEPT__ { ++this->length; }
		constexpr void operator--() __LL_EXCEPT__ { --this->length; }
		__LL_NODISCARD__ constexpr type::type operator++(int) __LL_EXCEPT__ { return this->length++; }
		__LL_NODISCARD__ constexpr type::type operator--(int) __LL_EXCEPT__ { return this->length--; }

		constexpr void operator+=(type::cinput value) __LL_EXCEPT__ { this->length += value; }
		constexpr void operator-=(type::cinput value) __LL_EXCEPT__ { this->length -= value; }
		constexpr void operator+=(__Countable::cref other) __LL_EXCEPT__ {
			this->length += other.length;
		}
		constexpr void operator-=(__Countable::cref other) __LL_EXCEPT__ {
			this->length -= other.length;
		}

		constexpr type::type operator=(type::cinput value) __LL_EXCEPT__ {
			return this->length = value;
		}
		#pragma endregion
	public:
		#pragma region Contructors
		constexpr Countable() __LL_EXCEPT__ : Countable(ZERO_VAL) {}
		constexpr Countable(type::cinput length) __LL_EXCEPT__ : length(length) {}
		constexpr ~Countable() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
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
		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator typename __Countable::cptr() const __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename __Countable::ptr() __LL_EXCEPT__ = delete;
		__LL_NODISCARD__ constexpr operator typename __Countable::move() __LL_EXCEPT__ { return std::move(*this); }

		#pragma endregion
		#pragma region ClassFunctions
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
		__LL_NODISCARD__ constexpr ll_bool_t inRange(type::cinput position) const __LL_EXCEPT__ {
			return position < this->operator type::type();
		}

		#pragma region CountableOperations
		__LL_NODISCARD__ constexpr __Countable::type operator+(type::cinput value) const __LL_EXCEPT__ {
			return __Countable::type(this->length + value);
		}
		__LL_NODISCARD__ constexpr __Countable::type operator-(type::cinput value) const __LL_EXCEPT__ {
			return __Countable::type(this->length - value);
		}
		__LL_NODISCARD__ constexpr __Countable::type operator+(__Countable::cref other) const __LL_EXCEPT__ {
			return __Countable::type(this->length + other.length);
		}
		__LL_NODISCARD__ constexpr __Countable::type operator-(__Countable::cref other) const __LL_EXCEPT__ {
			return __Countable::type(this->length - other.length);
		}

		#pragma endregion
		#pragma region CountableComparations
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

		__LL_NODISCARD__ constexpr ll_bool_t operator>(type::cinput value) const __LL_EXCEPT__ {
			return this->operator type::type() > value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(type::cinput value) const __LL_EXCEPT__ {
			return this->operator type::type() >= value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(type::cinput value) const __LL_EXCEPT__ {
			return this->operator type::type() < value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(type::cinput value) const __LL_EXCEPT__ {
			return this->operator type::type() <= value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(type::cinput value) const __LL_EXCEPT__ {
			return this->operator type::type() == value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(type::cinput value) const __LL_EXCEPT__ {
			return this->operator type::type() != value;
		}

		#pragma endregion
		#pragma endregion
		#pragma region ClassFunctionsRangeBased
	protected:
		template<class Function, class... Args>
		__LL_NODISCARD__ constexpr ll_bool_t doIfValid(type::cinput position, Function func, Args&&... args) {
			ll_bool_t result{};
			if ((result = this->inRange(position)) == LL_TRUE) {}
				func(std::forward<Args>(args)...);
			return result;
		}
		template<class Function, class... Args>
		__LL_NODISCARD__ constexpr ll_bool_t doIfValid(type::cinput position, Function func, Args&&... args) const {
			ll_bool_t result{};
			if ((result = this->inRange(position)) == LL_TRUE) {}
				func(std::forward<Args>(args)...);
			return result;
		}

		template<class Function, class... Args>
		__LL_NODISCARD__ constexpr ll_bool_t doIfValid(type::cinput pos1, type::cinput pos2, Function func, Args&&... args) {
			ll_bool_t result{};
			if ((result = (this->inRange(pos1) && this->inRange(pos2))) == LL_TRUE) {}
				func(std::forward<Args>(args)...);
			return result;
		}
		template<class Function, class... Args>
		__LL_NODISCARD__ constexpr ll_bool_t doIfValid(type::cinput pos1, type::cinput pos2, Function func, Args&&... args) const {
			ll_bool_t result{};
			if ((result = (this->inRange(pos1) && this->inRange(pos2))) == LL_TRUE) {}
				func(std::forward<Args>(args)...);
			return result;
		}

		template<class U, class Function, class... Args>
		__LL_NODISCARD__ static constexpr ll_bool_t doIfValidStatic(type::cinput position, U& context, Function func, Args&&... args) {
			ll_bool_t result{};
			if ((result = context.inRange(position)) == LL_TRUE)
				(context.*func)(std::forward<Args>(args)...);
			return result;
		}
		template<class U, class Function, class... Args>
		__LL_NODISCARD__ static constexpr ll_bool_t doIfValidStatic(type::cinput pos1, type::cinput pos2, U& context, Function func, Args&&... args) {
			ll_bool_t result{};
			if ((result = (context.inRange(pos1) && context.inRange(pos2))) == LL_TRUE)
				(context.*func)(std::forward<Args>(args)...);
			return result;
		}

		#pragma endregion
	#pragma endregion
};

using CountableB = Countable<b64, 0ull>;
using CountableL = Countable<len_t, 0ull>;

} // namespace llcpp

#endif // LLANYLIB_COUNTABLE_HPP_
