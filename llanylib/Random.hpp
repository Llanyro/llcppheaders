//////////////////////////////////////////////
//	Random.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 6.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_RANDOM_HPP_) // Guard && version protector
	#if LLANYLIB_RANDOM_MAYOR_ != 6 || LLANYLIB_RANDOM_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Random.hpp version error!"
		#else
			#error "Random.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_RANDOM_MAYOR_ || LLANYLIB_RANDOM_MINOR_

#else !defined(LLANYLIB_RANDOM_HPP_)
#define LLANYLIB_RANDOM_HPP_
#define LLANYLIB_RANDOM_MAYOR_ 6
#define LLANYLIB_RANDOM_MINOR_ 0

#include "cityhash.hpp"
#include "Array.hpp"

namespace llcpp {
namespace meta {

class Random {
	public:
		using Divisor = bits::type_division_cluster;
		using Pattern = Array<ll_bool_t, 3, LL_FALSE>;
	protected:
		meta::Hash seed;	// Seed for next hash
		HashFunctionPack generator;
		Pattern pattern;
	protected:
		constexpr void updateSeed() __LL_EXCEPT__ {
			this->seed = this->generator(this->seed);
		}
	public:
		#pragma region Constructors
		#pragma region Base
		constexpr Random() __LL_EXCEPT__ : seed(), generator(meta::StandardHashFunctions), pattern(LL_TRUE) {}
		constexpr ~Random() __LL_EXCEPT__ {}

		constexpr Random(const meta::Hash& seed, const HashFunctionPack& generator) __LL_EXCEPT__
			: seed(seed), generator(generator), pattern(LL_TRUE) {}
		constexpr Random(meta::Hash&& seed, HashFunctionPack&& generator) __LL_EXCEPT__
			: seed(std::move(seed)), generator(std::move(generator)), pattern(LL_TRUE) {}
		constexpr Random(meta::Hash&& seed, const HashFunctionPack& generator) __LL_EXCEPT__
			: seed(std::move(seed)), generator(generator), pattern(LL_TRUE) {}
		constexpr Random(const meta::Hash& seed, HashFunctionPack&& generator) __LL_EXCEPT__
			: seed(seed), generator(std::move(generator)), pattern(LL_TRUE) {}

		constexpr Random(const meta::Hash& seed) __LL_EXCEPT__
			: seed(seed), generator(meta::StandardHashFunctions), pattern(LL_TRUE) {}
		constexpr Random(meta::Hash&& seed) __LL_EXCEPT__
			: seed(std::move(seed)), generator(meta::StandardHashFunctions), pattern(LL_TRUE) {}

		#pragma endregion
		#pragma region StrPair
		constexpr Random(const StrPair& seed, const HashFunctionPack& generator) __LL_EXCEPT__
			: Random(generator(seed), generator) {}
		constexpr Random(const StrPair& seed, HashFunctionPack&& generator) __LL_EXCEPT__
			: Random(generator(seed), std::move(generator)) {}
		constexpr Random(const StrPair& seed) __LL_EXCEPT__
			: Random(seed, meta::StandardHashFunctions) {}

		#pragma endregion
		#pragma region String
		constexpr Random(ll_string_t seed, const len_t size, const HashFunctionPack& generator) __LL_EXCEPT__
			: Random(StrPair(seed, size), generator) {}
		constexpr Random(ll_string_t seed, const len_t size, HashFunctionPack&& generator) __LL_EXCEPT__
			: Random(StrPair(seed, size), std::move(generator)) {}
		constexpr Random(ll_string_t seed, const len_t size) __LL_EXCEPT__
			: Random(StrPair(seed, size)) {}

		template<len_t N>
		constexpr Random(const ll_char_t(&seed)[N], const HashFunctionPack& generator) __LL_EXCEPT__
			: Random(StrPair(seed, N), generator) {}
		template<len_t N>
		constexpr Random(const ll_char_t(&seed)[N], HashFunctionPack&& generator) __LL_EXCEPT__
			: Random(StrPair(seed, N), std::move(generator)) {}
		template<len_t N>
		constexpr Random(const ll_char_t(&seed)[N]) __LL_EXCEPT__
			: Random(StrPair(seed, N)) {}

		#pragma endregion
		#pragma region Values
		#pragma region 8
		constexpr Random(const ui8 seed, const HashFunctionPack& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), generator) {}
		constexpr Random(const ui8 seed, HashFunctionPack&& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), std::move(generator)) {}

		constexpr Random(const i8 seed, const HashFunctionPack& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), generator) {}
		constexpr Random(const i8 seed, HashFunctionPack&& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), std::move(generator)) {}

		#pragma endregion
		#pragma region 16
		constexpr Random(const ui16 seed, const HashFunctionPack& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), generator) {}
		constexpr Random(const ui16 seed, HashFunctionPack&& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), std::move(generator)) {}

		constexpr Random(const i16 seed, const HashFunctionPack& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), generator) {}
		constexpr Random(const i16 seed, HashFunctionPack&& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), std::move(generator)) {}

		#pragma endregion
		#pragma region 32
		constexpr Random(const ui32 seed, const HashFunctionPack& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), generator) {}
		constexpr Random(const ui32 seed, HashFunctionPack&& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), std::move(generator)) {}

		constexpr Random(const i32 seed, const HashFunctionPack& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), generator) {}
		constexpr Random(const i32 seed, HashFunctionPack&& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), std::move(generator)) {}

		#pragma endregion
		#pragma region 64
		constexpr Random(const ui64 seed, const HashFunctionPack& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), generator) {}
		constexpr Random(const ui64 seed, HashFunctionPack&& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), std::move(generator)) {}

		constexpr Random(const i64 seed, const HashFunctionPack& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), generator) {}
		constexpr Random(const i64 seed, HashFunctionPack&& generator) __LL_EXCEPT__
			: Random(meta::Hash(seed), std::move(generator)) {}

		#pragma endregion

		#pragma endregion

		#pragma endregion
		#pragma region GetSet
		__LL_NODISCARD__ constexpr Pattern& getPattern() __LL_EXCEPT__ { return this->pattern; }
		__LL_NODISCARD__ constexpr const Pattern& getPattern() const __LL_EXCEPT__ { return this->pattern; }
		constexpr void setPattern(const Pattern& other) __LL_EXCEPT__ { this->pattern = other; }
		constexpr void randomizePattern() __LL_EXCEPT__ {
			this->updateSeed();
			bits::bit_pos pos = 0;
			for (auto& i : this->pattern) {
				i = bits::get(this->seed.value, pos);
				pos += 16;
			}
		}

		#pragma endregion
		#pragma region RandomWithPattern
		template<class T> __LL_NODISCARD__ constexpr  T rand(const ll_bool_t* pattern) __LL_EXCEPT__ { return T(); }
		template<> __LL_NODISCARD__ constexpr ui8 rand<ui8>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			this->updateSeed();
			return Divisor::convert<ui64, ui8>(this->seed.value, pattern);
		}
		template<> __LL_NODISCARD__ constexpr ui16 rand<ui16>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			this->updateSeed();
			return Divisor::convert<ui64, ui16>(this->seed.value, pattern);
		}
		template<> __LL_NODISCARD__ constexpr ui32 rand<ui32>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			this->updateSeed();
			return Divisor::convert<ui64, ui32>(this->seed.value, pattern);
		}
		template<> __LL_NODISCARD__ constexpr i8 rand<i8>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			this->updateSeed();
			return Divisor::convert<i64, i8>(this->seed.value, pattern);
		}
		template<> __LL_NODISCARD__ constexpr i16 rand<i16>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			this->updateSeed();
			return Divisor::convert<i64, i16>(this->seed.value, pattern);
		}
		template<> __LL_NODISCARD__ constexpr i32 rand<i32>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			this->updateSeed();
			return Divisor::convert<i64, i32>(this->seed.value, pattern);
		}
		template<> __LL_NODISCARD__ constexpr f64 rand<f64>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			ui128 r = this->rand<ui128>();
			if (*pattern)	return r.h / static_cast<f64>(r.l);
			else			return r.l / static_cast<f64>(r.h);
		}
		template<> __LL_NODISCARD__ constexpr f32 rand<f32>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			ui64 r = this->rand<ui64>();
			auto result = bits::type_division<ui64>::div(r);
			if (*pattern)	return result.h / static_cast<f32>(result.l);
			else			return result.l / static_cast<f32>(result.h);
		}

		#pragma endregion
		#pragma region Random
		template<class T> __LL_NODISCARD__ constexpr  T rand() __LL_EXCEPT__ { return T(); }
		template<> __LL_NODISCARD__ constexpr ui8 rand<ui8>() __LL_EXCEPT__ {
			return this->rand<ui8>(this->pattern.begin());
		}
		template<> __LL_NODISCARD__ constexpr ui16 rand<ui16>() __LL_EXCEPT__ {
			return this->rand<ui16>(this->pattern.begin());
		}
		template<> __LL_NODISCARD__ constexpr ui32 rand<ui32>() __LL_EXCEPT__ {
			return this->rand<ui32>(this->pattern.begin());
		}
		template<> __LL_NODISCARD__ constexpr ui64 rand<ui64>() __LL_EXCEPT__ {
			this->updateSeed();
			return this->seed.value;
		}
		template<> __LL_NODISCARD__ constexpr ui128 rand<ui128>() __LL_EXCEPT__ {
			ui128 result{};
			result.l = this->rand<ui64>();
			result.h = this->rand<ui64>();
			return result;
		}
		template<> __LL_NODISCARD__ constexpr i8 rand<i8>() __LL_EXCEPT__ {
			return this->rand<i8>(this->pattern.begin());
		}
		template<> __LL_NODISCARD__ constexpr i16 rand<i16>() __LL_EXCEPT__ {
			return this->rand<i16>(this->pattern.begin());
		}
		template<> __LL_NODISCARD__ constexpr i32 rand<i32>() __LL_EXCEPT__ {
			return this->rand<i32>(this->pattern.begin());
		}
		template<> __LL_NODISCARD__ constexpr i64 rand<i64>() __LL_EXCEPT__ {
			this->updateSeed();
			return this->seed.value;
		}
		template<> __LL_NODISCARD__ constexpr i128 rand<i128>() __LL_EXCEPT__ {
			i128 result{};
			result.l = this->rand<i64>();
			result.h = this->rand<i64>();
			return result;
		}
		template<> __LL_NODISCARD__ constexpr f64 rand<f64>() __LL_EXCEPT__ {
			return this->rand<f64>(this->pattern.begin());
		}
		template<> __LL_NODISCARD__ constexpr f32 rand<f32>() __LL_EXCEPT__ {
			return this->rand<f32>(this->pattern.begin());
		}

		#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_RANDOM_HPP_
