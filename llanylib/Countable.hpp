//////////////////////////////////////////////
//	Countable.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_COUNTABLE_HPP_) // Guard && version protector
	#if LLANYLIB_COUNTABLE_MAYOR_ != 8 || LLANYLIB_COUNTABLE_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Countable.hpp version error!"
		#else
			#error "Countable.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_COUNTABLE_MAYOR_ || LLANYLIB_COUNTABLE_MINOR_

#else !defined(LLANYLIB_COUNTABLE_HPP_)
#define LLANYLIB_COUNTABLE_HPP_
#define LLANYLIB_COUNTABLE_MAYOR_ 8
#define LLANYLIB_COUNTABLE_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace meta {

template<class T, T ZERO_VAL>
class Countable {
	public:
		static constexpr T ZERO = ZERO_VAL;
		using cinput = traits::cinput<T>;
	private:
		T length;
	#pragma region Functions
	protected:
		#pragma region Protected
		__LL_NODISCARD__ constexpr T& lenRef() noexcept { return this->length; }

		#pragma endregion
	public:
		#pragma region Contructors
		constexpr Countable() noexcept : Countable(ZERO_VAL) {}
		constexpr Countable(cinput length) noexcept : length(length) {}
		constexpr ~Countable() noexcept {}

		#pragma endregion
		#pragma region CopyMove
		constexpr Countable(const Countable& other) noexcept
			: Countable(other.length) {}
		constexpr Countable& operator=(const Countable& other) noexcept {
			this->length = other.length;
			return *this;
		}

		constexpr Countable(Countable&& other) noexcept
			: Countable(other.length) { other.clear(); }
		constexpr Countable& operator=(Countable&& other) noexcept {
			this->length = other.length;
			other.length = ZERO_VAL;
			return *this;
		}
		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator const Countable*() const noexcept = delete;
		__LL_NODISCARD__ constexpr operator Countable*() noexcept = delete;

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr operator T() const noexcept {
			return this->length;
		}
		__LL_NODISCARD__ constexpr T count() const noexcept {
			return this->operator T();
		}
		__LL_NODISCARD__ constexpr T len() const noexcept {
			return this->operator T();
		}
		__LL_NODISCARD__ constexpr T size() const noexcept {
			return this->operator T();
		}
		__LL_NODISCARD__ constexpr void clear() noexcept { this->length = ZERO_VAL; }
		__LL_NODISCARD__ constexpr T half() const noexcept { return (this->length >> 1); }
		__LL_NODISCARD__ constexpr ll_bool_t inRange(cinput position) const noexcept {
			return position < this->operator T();
		}
		// Used to get end of array
		__LL_NODISCARD__ constexpr ll_bool_t inRangeEnd(cinput position) const noexcept {
			return position <= this->operator T();
		}

		constexpr void operator++() noexcept { ++this->length; }
		constexpr void operator--() noexcept { --this->length; }
		__LL_NODISCARD__ constexpr T operator++(int) noexcept { return this->length++; }
		__LL_NODISCARD__ constexpr T operator--(int) noexcept { return this->length--; }

		constexpr void operator+=(cinput value) noexcept { this->length += value; }
		constexpr void operator-=(cinput value) noexcept { this->length -= value; }
		constexpr void operator+=(const Countable& other) noexcept {
			this->length += other.length;
		}
		constexpr void operator-=(const Countable& other) noexcept {
			this->length -= other.length;
		}

		constexpr typename T operator=(cinput value) noexcept {
			return this->length = value;
		}

		#pragma region CountableOperations
		__LL_NODISCARD__ constexpr Countable operator+(cinput value) const noexcept {
			return Countable(this->length + value);
		}
		__LL_NODISCARD__ constexpr Countable operator-(cinput value) const noexcept {
			return Countable(this->length - value);
		}
		__LL_NODISCARD__ constexpr Countable operator+(const Countable& other) const noexcept {
			return Countable(this->length + other.length);
		}
		__LL_NODISCARD__ constexpr Countable operator-(const Countable& other) const noexcept {
			return Countable(this->length - other.length);
		}

		#pragma endregion
		#pragma region CountableComparations
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const Countable& other) const noexcept {
			return this->operator T() > other.operator T();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const Countable& other) const noexcept {
			return this->operator T() >= other.operator T();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const Countable& other) const noexcept {
			return this->operator T() < other.operator T();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const Countable& other) const noexcept {
			return this->operator T() <= other.operator T();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Countable& other) const noexcept {
			return this->operator T() == other.operator T();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Countable& other) const noexcept {
			return this->operator T() != other.operator T();
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator>(cinput value) const noexcept {
			return this->operator T() > value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(cinput value) const noexcept {
			return this->operator T() >= value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(cinput value) const noexcept {
			return this->operator T() < value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(cinput value) const noexcept {
			return this->operator T() <= value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(cinput value) const noexcept {
			return this->operator T() == value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(cinput value) const noexcept {
			return this->operator T() != value;
		}

		#pragma endregion
		constexpr void swap(Countable& other) noexcept {
			T tmp = this->length;
			this->length = other.length;
			other.length = tmp;
		}

		#pragma endregion
		#pragma region ClassFunctionsRangeBased
	protected:
		template<class Function, class... Args>
		__LL_NODISCARD__ constexpr ll_bool_t doIfValid(cinput position, Function func, Args&&... args) {
			ll_bool_t result{};
			if ((result = this->inRange(position)) == LL_TRUE) {}
				func(std::forward<Args>(args)...);
			return result;
		}
		template<class Function, class... Args>
		__LL_NODISCARD__ constexpr ll_bool_t doIfValid(cinput position, Function func, Args&&... args) const {
			ll_bool_t result{};
			if ((result = this->inRange(position)) == LL_TRUE) {}
				func(std::forward<Args>(args)...);
			return result;
		}

		template<class Function, class... Args>
		__LL_NODISCARD__ constexpr ll_bool_t doIfValid(cinput pos1, cinput pos2, Function func, Args&&... args) {
			ll_bool_t result{};
			if ((result = (this->inRange(pos1) && this->inRange(pos2))) == LL_TRUE) {}
				func(std::forward<Args>(args)...);
			return result;
		}
		template<class Function, class... Args>
		__LL_NODISCARD__ constexpr ll_bool_t doIfValid(cinput pos1, cinput pos2, Function func, Args&&... args) const {
			ll_bool_t result{};
			if ((result = (this->inRange(pos1) && this->inRange(pos2))) == LL_TRUE) {}
				func(std::forward<Args>(args)...);
			return result;
		}

		template<class U, class Function, class... Args>
		__LL_NODISCARD__ static constexpr ll_bool_t doIfValidStatic(cinput position, U& context, Function func, Args&&... args) {
			ll_bool_t result{};
			if ((result = context.inRange(position)) == LL_TRUE)
				(context.*func)(std::forward<Args>(args)...);
			return result;
		}
		template<class U, class Function, class... Args>
		__LL_NODISCARD__ static constexpr ll_bool_t doIfValidStatic(cinput pos1, cinput pos2, U& context, Function func, Args&&... args) {
			ll_bool_t result{};
			if ((result = (context.inRange(pos1) && context.inRange(pos2))) == LL_TRUE)
				(context.*func)(std::forward<Args>(args)...);
			return result;
		}

		#pragma endregion
	#pragma endregion
};

using CountableB = Countable<b64, ZERO_UI64>;
using CountableL = Countable<len_t, ZERO_UI64>;

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_COUNTABLE_HPP_
