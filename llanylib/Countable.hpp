//////////////////////////////////////////////
//	Countable.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_COUNTABLE_HPP_) // Guard && version protector
	#if LLANYLIB_COUNTABLE_MAYOR_ != 9 || LLANYLIB_COUNTABLE_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Countable.hpp version error!"
		#else
			#error "Countable.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_COUNTABLE_MAYOR_ || LLANYLIB_COUNTABLE_MINOR_

#else !defined(LLANYLIB_COUNTABLE_HPP_)
#define LLANYLIB_COUNTABLE_HPP_
#define LLANYLIB_COUNTABLE_MAYOR_ 9
#define LLANYLIB_COUNTABLE_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace meta {

// Simple Wrapper for countables
template<class _T, _T _ZERO_VAL>
class Countable {
	#pragma region Types
	public:
		using _MyType	= Countable;
		using T			= _T;
		using cinput	= traits::cinput<T>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(traits::is_valid_type_checker_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(traits::is_valid_constructor_checker_v<T>,
			"constructor_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr T ZERO_VAL = _ZERO_VAL;

	#pragma endregion
	#pragma region Attibutes
	private:
		T counter;

	#pragma endregion
	#pragma region Functions
		#pragma region Protected
	protected:
		__LL_NODISCARD__ constexpr T& counterReference() noexcept { return this->counter; }

		#pragma endregion
		#pragma region Contructors
	public:
		constexpr Countable() noexcept : counter(ZERO_VAL) {}
		constexpr ~Countable() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Countable(const Countable& other) noexcept : counter(other.counter) {}
		constexpr Countable& operator=(const Countable& other) noexcept {
			this->counter = other.counter;
			return *this;
		}
		constexpr Countable(Countable&& other) noexcept
			: Countable(other.counter) { other.counter = ZERO_VAL; }
		constexpr Countable& operator=(Countable&& other) noexcept {
			this->counter = other.counter;
			other.counter = ZERO_VAL;
			return *this;
		}

		constexpr Countable(const T& counter) noexcept : counter(counter) {}
		constexpr Countable& operator=(const T& counter) noexcept {
			this->counter = counter;
			return *this;
		}
		constexpr Countable(T&& counter) noexcept : counter(std::forward<T&&>(counter)) {}
		constexpr Countable& operator=(Countable&& other) noexcept {
			this->counter = std::forward<T&&>(counter);
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const Countable*() const noexcept = delete;
		__LL_NODISCARD__ constexpr operator Countable*() noexcept = delete;

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr T count() const noexcept {
			return this->lenght();
		}
		__LL_NODISCARD__ constexpr T lenght() const noexcept {
			return this->counter;
		}
		__LL_NODISCARD__ constexpr T size() const noexcept {
			return this->lenght();
		}
		__LL_NODISCARD__ constexpr void clear() noexcept { this->counter = ZERO_VAL; }
		__LL_NODISCARD__ constexpr T half() const noexcept { return (this->counter >> 1); }
		__LL_NODISCARD__ constexpr ll_bool_t inRange(cinput position) const noexcept {
			return position < this->lenght();
		}
		// Used to get end of array
		__LL_NODISCARD__ constexpr ll_bool_t inRangeEnd(cinput position) const noexcept {
			return position <= this->lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			return this->counter == ZERO_VAL;
		}
	protected:
		constexpr void operator++() noexcept { ++this->counter; }
		constexpr void operator--() noexcept { --this->counter; }
		__LL_NODISCARD__ constexpr T operator++(int) noexcept { return this->counter++; }
		__LL_NODISCARD__ constexpr T operator--(int) noexcept { return this->counter--; }

		constexpr void operator+=(cinput value) noexcept { this->counter += value; }
		constexpr void operator-=(cinput value) noexcept { this->counter -= value; }
		constexpr void operator+=(const Countable& other) noexcept {
			this->counter += other.counter;
		}
		constexpr void operator-=(const Countable& other) noexcept {
			this->counter -= other.counter;
		}

		#pragma region CountableOperations
	public:
		__LL_NODISCARD__ constexpr Countable operator+(cinput value) const noexcept {
			return Countable(this->counter + value);
		}
		__LL_NODISCARD__ constexpr Countable operator-(cinput value) const noexcept {
			return Countable(this->counter - value);
		}
		__LL_NODISCARD__ constexpr Countable operator+(const Countable& other) const noexcept {
			return Countable(this->counter + other.counter);
		}
		__LL_NODISCARD__ constexpr Countable operator-(const Countable& other) const noexcept {
			return Countable(this->counter - other.counter);
		}

		#pragma endregion
		#pragma region CountableComparations
	public:
		__LL_NODISCARD__ constexpr ll_bool_t operator>(const Countable& other) const noexcept {
			return this->lenght() > other.lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(const Countable& other) const noexcept {
			return this->lenght() >= other.lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(const Countable& other) const noexcept {
			return this->lenght() < other.lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(const Countable& other) const noexcept {
			return this->lenght() <= other.lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const Countable& other) const noexcept {
			return this->lenght() == other.lenght();
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const Countable& other) const noexcept {
			return this->lenght() != other.lenght();
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator>(cinput value) const noexcept {
			return this->lenght() > value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator>=(cinput value) const noexcept {
			return this->lenght() >= value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<(cinput value) const noexcept {
			return this->lenght() < value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator<=(cinput value) const noexcept {
			return this->lenght() <= value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(cinput value) const noexcept {
			return this->lenght() == value;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(cinput value) const noexcept {
			return this->lenght() != value;
		}

		#pragma endregion
		constexpr void swap(Countable& other) noexcept {
			T tmp = this->counter;
			this->counter = other.counter;
			other.counter = tmp;
		}

		#pragma endregion
		#pragma region ClassFunctionsRangeBased
	protected:
		template<class Function, class... Args>
		__LL_NODISCARD__ constexpr ll_bool_t doIfValid(cinput position, Function func, Args&&... args) {
			ll_bool_t result{};
			if ((result = this->inRange(position)) == llcpp::TRUE) {}
				func(std::forward<Args>(args)...);
			return result;
		}
		template<class Function, class... Args>
		__LL_NODISCARD__ constexpr ll_bool_t doIfValid(cinput position, Function func, Args&&... args) const {
			ll_bool_t result{};
			if ((result = this->inRange(position)) == llcpp::TRUE) {}
				func(std::forward<Args>(args)...);
			return result;
		}

		template<class Function, class... Args>
		__LL_NODISCARD__ constexpr ll_bool_t doIfValid(cinput pos1, cinput pos2, Function func, Args&&... args) {
			ll_bool_t result{};
			if ((result = (this->inRange(pos1) && this->inRange(pos2))) == llcpp::TRUE) {}
				func(std::forward<Args>(args)...);
			return result;
		}
		template<class Function, class... Args>
		__LL_NODISCARD__ constexpr ll_bool_t doIfValid(cinput pos1, cinput pos2, Function func, Args&&... args) const {
			ll_bool_t result{};
			if ((result = (this->inRange(pos1) && this->inRange(pos2))) == llcpp::TRUE) {}
				func(std::forward<Args>(args)...);
			return result;
		}

		template<class U, class Function, class... Args>
		__LL_NODISCARD__ static constexpr ll_bool_t doIfValidStatic(cinput position, U& context, Function func, Args&&... args) {
			ll_bool_t result{};
			if ((result = context.inRange(position)) == llcpp::TRUE)
				(context.*func)(std::forward<Args>(args)...);
			return result;
		}
		template<class U, class Function, class... Args>
		__LL_NODISCARD__ static constexpr ll_bool_t doIfValidStatic(cinput pos1, cinput pos2, U& context, Function func, Args&&... args) {
			ll_bool_t result{};
			if ((result = (context.inRange(pos1) && context.inRange(pos2))) == llcpp::TRUE)
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
