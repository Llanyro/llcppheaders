//////////////////////////////////////////////
//	Arrayo.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ARRAYO_INCOMPLETE_HPP_)
	#if LLANYLIB_ARRAYO_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ARRAYO_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Arrayo.hpp(incomplete) version error!"
		#else
			#error "Arrayo.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAYO_INCOMPLETE_MAYOR_ || LLANYLIB_ARRAYO_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ARRAYO_INCOMPLETE_HPP_)
	#define LLANYLIB_ARRAYO_INCOMPLETE_HPP_
	#define LLANYLIB_ARRAYO_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ARRAYO_INCOMPLETE_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/types.hpp>
#else
	#include "types.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {

template<class _T, usize _N>
class Arrayo;

} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ARRAYO_HPP_)
	#if LLANYLIB_ARRAYO_MAYOR_ != 12 || LLANYLIB_ARRAYO_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Arrayo.hpp version error!"
		#else
			#error "Arrayo.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAYO_MAYOR_ || LLANYLIB_ARRAYO_MINOR_

#else
	#define LLANYLIB_ARRAYO_HPP_
	#define LLANYLIB_ARRAYO_MAYOR_ 12
	#define LLANYLIB_ARRAYO_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/pair.hpp>
	#include <llanylib/types/compiler_extensions.hpp>
#else
	#include "pair.hpp"
	#include "compiler_extensions.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {

#define CHECK_ERROR_OUT_OF_RANGE										\
	do {																\
		if constexpr (::llcpp::LL_DEBUG_ERROR) {						\
			if (!this->inRange(position))								\
				__debug_error_out_of_range(position, "position", N);	\
		}																\
	} while (0)

// Works like a C array "int char[5]"
// It also make easy for compiler to move arrays between functions (you usually cant return arrays in C)
// Simplest array, for more complex array use Vector instad
template<class _T, usize _N>
class Arrayo {
	public:
		// Class related
		using _MyType				= Arrayo<_T, _N>;

		// Types and enums
		using T						= _T;
		using type					= T;	// standard
		using value_type			= T;	// standard
		using Iterator				= T*;
		using ConstIterator			= const T*;
		static constexpr usize N	= _N;

		T elements[N];	// Unamed array

	public:
		__LL_NODISCARD__ constexpr explicit operator const Arrayo*() const noexcept {
			__LL_FUNCTION_INIT__;
			return this;
		}
		__LL_NODISCARD__ constexpr explicit operator Arrayo*() noexcept {
			__LL_FUNCTION_INIT__;
			return this;
		}

		__LL_NODISCARD__ constexpr T& operator[](const usize position) noexcept {
			__LL_FUNCTION_INIT__;
			CHECK_ERROR_OUT_OF_RANGE;
			return this->elements[position];
		}
		__LL_NODISCARD__ constexpr const T& operator[](const usize position) const noexcept {
			__LL_FUNCTION_INIT__;
			CHECK_ERROR_OUT_OF_RANGE;
			return this->elements[position];
		}

		__LL_NODISCARD__ constexpr Iterator operator+(const usize position) noexcept {
			__LL_FUNCTION_INIT__;
			CHECK_ERROR_OUT_OF_RANGE;
			return this->elements + position;
		}
		__LL_NODISCARD__ constexpr ConstIterator operator+(const usize position) const noexcept {
			__LL_FUNCTION_INIT__;
			CHECK_ERROR_OUT_OF_RANGE;
			return this->elements + position;
		}

		__LL_NODISCARD__ constexpr Iterator operator-(const usize position) noexcept {
			__LL_FUNCTION_INIT__;
			CHECK_ERROR_OUT_OF_RANGE;
			return this->elements - position;
		}
		__LL_NODISCARD__ constexpr ConstIterator operator-(const usize position) const noexcept {
			__LL_FUNCTION_INIT__;
			CHECK_ERROR_OUT_OF_RANGE;
			return this->elements - position;
		}

		__LL_NODISCARD__ constexpr T& operator*() noexcept {
			__LL_FUNCTION_INIT__;
			return this->elements[0];
		}
		__LL_NODISCARD__ constexpr const T& operator*() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->elements[0];
		}

		__LL_NODISCARD__ constexpr Iterator operator->() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::addressof(this->elements[0]);
		}
		__LL_NODISCARD__ constexpr ConstIterator operator->() const noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::addressof(this->elements[0]);
		}

		__LL_NODISCARD__ constexpr Iterator get(const usize position) noexcept {
			__LL_FUNCTION_INIT__;
			CHECK_ERROR_OUT_OF_RANGE;
			return *this + position;
		}
		__LL_NODISCARD__ constexpr ConstIterator get(const usize position) const noexcept {
			__LL_FUNCTION_INIT__;
			CHECK_ERROR_OUT_OF_RANGE;
			return *this + position;
		}

		__LL_NODISCARD__ constexpr Iterator data() noexcept {
			__LL_FUNCTION_INIT__;
			return this->elements;
		}
		__LL_NODISCARD__ constexpr ConstIterator data() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->elements;
		}
		__LL_NODISCARD__ constexpr Iterator begin() noexcept {
			__LL_FUNCTION_INIT__;
			return this->elements;
		}
		__LL_NODISCARD__ constexpr ConstIterator begin() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->elements;
		}
		__LL_NODISCARD__ constexpr Iterator end() noexcept {
			__LL_FUNCTION_INIT__;
			return this->elements + _MyType::N;
		}
		__LL_NODISCARD__ constexpr ConstIterator end() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->elements + _MyType::N;
		}

		__LL_NODISCARD__ constexpr const usize size() const noexcept {
			__LL_FUNCTION_INIT__;
			return _MyType::N;
		}
		__LL_NODISCARD__ constexpr const usize count() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->size();
		}
		__LL_NODISCARD__ constexpr const usize len() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->size();
		}

		__LL_NODISCARD__ static constexpr ll_bool_t inRange(const usize position) noexcept {
			__LL_FUNCTION_INIT__;
			return N > position;
		}

	public:
		__LL_NODISCARD__ static constexpr ll_bool_t compare(ConstIterator tb, ConstIterator te,  ConstIterator ob) noexcept {
			__LL_FUNCTION_INIT__;
			for(; tb < te; ++tb, ++ob)
				if(*tb != *ob)
					return ::llcpp::LL_FALSE;
			return ::llcpp::LL_TRUE;
		}

		template<usize NN>
		__LL_NODISCARD__ constexpr ll_bool_t compare(const T (&arr)[NN]) const noexcept {
			__LL_FUNCTION_INIT__;
			if constexpr (N == NN)
				return this->compare(this->begin(), this->end(), arr);
			else return this->compare(this->begin(), this->get(N > NN ? NN : N), arr);
		}
		template<usize NN>
		__LL_NODISCARD__ constexpr ll_bool_t compare(const T (&arr)[NN], const usize compare_size) const noexcept {
			__LL_FUNCTION_INIT__;
			if (N < COMPARE_SIZE) {
				if constexpr (::llcpp::LL_DEBUG_ERROR)
					__debug_error_out_of_range(COMPARE_SIZE, "COMPARE_SIZE", N);
				return ::llcpp::LL_FALSE;
			}
			else if (NN < COMPARE_SIZE) {
				if constexpr (::llcpp::LL_DEBUG_ERROR)
					__debug_error_out_of_range(COMPARE_SIZE, "COMPARE_SIZE", NN);
				return ::llcpp::LL_FALSE;
			}
			return this->compare(this->begin(), this->get(COMPARE_SIZE), arr);
		}
		template<usize COMPARE_SIZE, usize NN>
		__LL_NODISCARD__ constexpr ll_bool_t compare(const T (&arr)[NN]) const noexcept {
			__LL_FUNCTION_INIT__;
			static_assert(N >= COMPARE_SIZE,
				"N cannot be lower than COMPARE_SIZE");
			static_assert(NN >= COMPARE_SIZE,
				"NN cannot be lower than COMPARE_SIZE");
			if constexpr (N < COMPARE_SIZE || NN < COMPARE_SIZE)
				return ::llcpp::LL_FALSE;
			return this->compare(this->begin(), this->get(COMPARE_SIZE), arr);
		}
};

#undef CHECK_ERROR_OUT_OF_RANGE

#if __LL_INCLUDE_KATS == 1
namespace kat {
	
__LL_VAR_INLINE__ constexpr Arrayo<u32, 5> ARRAYO = { 1u, 2u, 3u, 4u, 5u };
__LL_VAR_INLINE__ constexpr Arrayo<::llcpp::meta::pair<u32>, 5> ARRAYO_OBJ = { 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u };

#pragma region OperatorSquareBrackets
__LL_VAR_INLINE__ constexpr ll_bool_t ARRAYO_OPERATOR_SQUARE_BRACKETS =
	   ::llcpp::meta::kat::ARRAYO[0] == 1u
	&& ::llcpp::meta::kat::ARRAYO[1] == 2u
	&& ::llcpp::meta::kat::ARRAYO[2] == 3u
	&& ::llcpp::meta::kat::ARRAYO[3] == 4u
	&& ::llcpp::meta::kat::ARRAYO[4] == 5u;
__LL_KAT_FUNCTION_CONSTEXPR(
	arrayo_operator_square_brackets_kat,
	::llcpp::meta::kat::ARRAYO_OPERATOR_SQUARE_BRACKETS,
	"'Arrayo operator[]'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region OperatorPlus
__LL_VAR_INLINE__ constexpr ll_bool_t ARRAYO_OPERATOR_PLUS =
	   *(::llcpp::meta::kat::ARRAYO + 0) == 1u
	&& *(::llcpp::meta::kat::ARRAYO + 1) == 2u
	&& *(::llcpp::meta::kat::ARRAYO + 2) == 3u
	&& *(::llcpp::meta::kat::ARRAYO + 3) == 4u
	&& *(::llcpp::meta::kat::ARRAYO + 4) == 5u;
__LL_KAT_FUNCTION_CONSTEXPR(
	arrayo_operator_plus_kat,
	::llcpp::meta::kat::ARRAYO_OPERATOR_PLUS,
	"'Arrayo operator+'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region OperatorPointer
__LL_KAT_FUNCTION_CONSTEXPR(
	arrayo_operator_pointer_kat,
	*::llcpp::meta::kat::ARRAYO == 1u,
	"'Arrayo operator*'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region OperatorPlus
__LL_VAR_INLINE__ constexpr ll_bool_t ARRAYO_OPERATOR_ARROW =
	   ::llcpp::meta::kat::ARRAYO_OBJ->first == 1u
	&& ::llcpp::meta::kat::ARRAYO_OBJ->second == 2u;

__LL_KAT_FUNCTION_CONSTEXPR(
	arrayo_operator_arrow_kat,
	::llcpp::meta::kat::ARRAYO_OPERATOR_ARROW,
	"'Arrayo operator->'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region Loops
__LL_NODISCARD__ constexpr ll_bool_t check_arrayo_loop() noexcept {
	__LL_VAR_INLINE__ constexpr u32 arr[5] = { 1u, 2u, 3u, 4u, 5u };

	u8 pos{};
	for(const auto& i : ::llcpp::meta::kat::ARRAYO) {
		if(i != arr[pos])
			return ::llcpp::LL_FALSE;
		else ++pos;
	}
	return ::llcpp::LL_TRUE;
}

__LL_KAT_FUNCTION_CONSTEXPR(
	arrayo_loop_kat,
	::llcpp::meta::kat::check_arrayo_loop(),
	"'Arrayo loop (begin/end)'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion

__LL_NODISCARD__ constexpr ::llcpp::string arrayo_kats() noexcept {
	::llcpp::string result = ::llcpp::meta::kat::arrayo_operator_square_brackets_kat();
	if(result) return result;
	result = ::llcpp::meta::kat::arrayo_operator_plus_kat();
	if(result) return result;
	result = ::llcpp::meta::kat::arrayo_operator_pointer_kat();
	if(result) return result;
	result = ::llcpp::meta::kat::arrayo_operator_arrow_kat();
	if(result) return result;
	result = ::llcpp::meta::kat::arrayo_loop_kat();
	if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::kat::arrayo_kats() == LL_NULLPTR, "Arrayo KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAYO_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_ARRAYO_EXTRA_HPP_)
		#if LLANYLIB_ARRAYO_EXTRA_MAYOR_ != 12 || LLANYLIB_ARRAYO_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "Arrayo.hpp(extra) version error!"
			#else
				#error "Arrayo.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_ARRAYO_EXTRA_MAYOR_ || LLANYLIB_ARRAYO_EXTRA_MINOR_

	#else
		#define LLANYLIB_ARRAYO_EXTRA_HPP_
		#define LLANYLIB_ARRAYO_EXTRA_MAYOR_ 12
		#define LLANYLIB_ARRAYO_EXTRA_MINOR_ 0

namespace llcpp {

// Works like a C array "int char[5]"
// It also make easy for compiler to move arrays between functions (you usually cant return arrays in C)
// Simplest array, for more complex array use Vector instad
template<class T, usize N>
using Arrayo = ::llcpp::meta::Arrayo<T, N>;

} // namespace llcpp

	#endif // LLANYLIB_ARRAYO_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
