//////////////////////////////////////////////
//	Algorithm.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ALGORITHM_INCOMPLETE_HPP_)
	#if LLANYLIB_ALGORITHM_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_ALGORITHM_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Algorithm.hpp(incomplete) version error!"
		#else
			#error "Algorithm.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ALGORITHM_INCOMPLETE_MAYOR_ || LLANYLIB_ALGORITHM_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ALGORITHM_INCOMPLETE_HPP_)
	#define LLANYLIB_ALGORITHM_INCOMPLETE_HPP_
	#define LLANYLIB_ALGORITHM_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_ALGORITHM_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_ALGORITHM_HPP_)
	#if LLANYLIB_ALGORITHM_MAYOR_ != 11 || LLANYLIB_ALGORITHM_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Algorithm.hpp version error!"
		#else
			#error "Algorithm.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ALGORITHM_MAYOR_ || LLANYLIB_ALGORITHM_MINOR_

#else
	#define LLANYLIB_ALGORITHM_HPP_
	#define LLANYLIB_ALGORITHM_MAYOR_ 11
	#define LLANYLIB_ALGORITHM_MINOR_ 0

#include "hash_magic.hpp"

#include <type_traits>

namespace llcpp {
namespace meta {
namespace utils {
namespace hash {

enum class AlgorithmMode : u8 {
	Murmur,
	SimplestCombine,
};

template<class _T, ::llcpp::meta::utils::hash::AlgorithmMode _MODE = ::llcpp::meta::utils::hash::AlgorithmMode::Murmur>
class Algorithm : ::llcpp::AlwaysValidTag {
	#pragma region Types
	public:
		// Class related
		using _MyType	= Algorithm;		// This class with template
		using ValidTag	= ::llcpp::AlwaysValidTag;

		// Types and enums
		using T			= _T;
		using Mode		= decltype(_MODE);
		using Murmur	= ::llcpp::meta::utils::hash::magic::Murmur;
		using CityHash	= ::llcpp::meta::utils::hash::magic::CityHash;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr Mode MODE			= _MODE;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr Algorithm() noexcept = default;
		constexpr ~Algorithm() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Algorithm(const Algorithm&) noexcept = default;
		constexpr Algorithm& operator=(const Algorithm&) noexcept = default;
		constexpr Algorithm(Algorithm&& other) noexcept = default;
		constexpr Algorithm& operator=(Algorithm&& other) noexcept = default;

		constexpr Algorithm(const volatile Algorithm&) noexcept = delete;
		constexpr Algorithm& operator=(const volatile Algorithm&) noexcept = delete;
		constexpr Algorithm(volatile Algorithm&&) noexcept = delete;
		constexpr Algorithm& operator=(volatile Algorithm&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Algorithm*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Algorithm*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Murmur
	public:
		template<T MUL, u8 SHIFT>
		__LL_NODISCARD__ constexpr T __mur_process(const T value1, const T value2) const noexcept requires(MODE == Mode::Murmur) {
			T a = static_cast<T>((value1 ^ value2) * MUL);
			a ^= (a >> SHIFT);
			T b = static_cast<T>((value2 ^ a) * MUL);
			b ^= (b >> SHIFT);
			//b *= MUL;	// result is no longer stored in b, now is returned instead
			return b * MUL;
		}
		template<u64 MUL = _MyType::Murmur::kMul64, u8 SHIFT = _MyType::Murmur::llshift64>
		__LL_NODISCARD__ constexpr u64 process(const u64 value1, const u64 value2) const noexcept requires(MODE == Mode::Murmur && ::std::is_same_v<T, u64>) {
			return this->__mur_process<MUL, SHIFT>(value1, value2);
		}
		template<u32 MUL = _MyType::Murmur::kMul32, u8 SHIFT = _MyType::Murmur::llshift32>
		__LL_NODISCARD__ constexpr u32 process(const u32 value1, const u32 value2) const noexcept requires(MODE == Mode::Murmur && ::std::is_same_v<T, u32>) {
			return this->__mur_process<MUL, SHIFT>(value1, value2);
		}
		template<u8 MUL = _MyType::Murmur::kMul8, u8 SHIFT = _MyType::Murmur::llshift8>
		__LL_NODISCARD__ constexpr u8 process(const u8 value1, const u8 value2) const noexcept requires(MODE == Mode::Murmur && ::std::is_same_v<T, u8>) {
			return this->__mur_process<MUL, SHIFT>(value1, value2);
		}

		#pragma endregion
		#pragma region SimplestCombine
	public:
		template<u8 SHIFT, ll_bool_t LEFT_SHIFT>
		__LL_NODISCARD__ constexpr T __simplest_combine_process(const T value1, const T value2) const noexcept requires(MODE == Mode::SimplestCombine) {
			if constexpr (LEFT_SHIFT) return static_cast<T>(value1 ^ static_cast<T>(value2 << SHIFT));
			else return static_cast<T>(value1 ^ static_cast<T>(value2 >> SHIFT));
		}
		template<u8 SHIFT = _MyType::Murmur::llshift64, ll_bool_t LEFT_SHIFT = ::llcpp::TRUE>
		__LL_NODISCARD__ constexpr u64 process(const u64 value1, const u64 value2) const noexcept requires(MODE == Mode::SimplestCombine && ::std::is_same_v<T, u64>) {
			return this->__simplest_combine_process<SHIFT, LEFT_SHIFT>(value1, value2);
		}
		template<u8 SHIFT = _MyType::Murmur::llshift32, ll_bool_t LEFT_SHIFT = ::llcpp::TRUE>
		__LL_NODISCARD__ constexpr u32 process(const u32 value1, const u32 value2) const noexcept requires(MODE == Mode::SimplestCombine && ::std::is_same_v<T, u32>) {
			return this->__simplest_combine_process<SHIFT, LEFT_SHIFT>(value1, value2);
		}
		template<u8 SHIFT = _MyType::Murmur::llshift8, ll_bool_t LEFT_SHIFT = ::llcpp::TRUE>
		__LL_NODISCARD__ constexpr u8 process(const u8 value1, const u8 value2) const noexcept requires(MODE == Mode::SimplestCombine && ::std::is_same_v<T, u8>) {
			return this->__simplest_combine_process<SHIFT, LEFT_SHIFT>(value1, value2);
		}

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

} // namespace hash
} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ALGORITHM_HPP_
