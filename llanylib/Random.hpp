//////////////////////////////////////////////
//	Random.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_RANDOM_HPP_) // Guard && version protector
	#if LLANYLIB_RANDOM_MAYOR_ != 8 || LLANYLIB_RANDOM_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Random.hpp version error!"
		#else
			#error "Random.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_RANDOM_MAYOR_ || LLANYLIB_RANDOM_MINOR_

#else !defined(LLANYLIB_RANDOM_HPP_)
#define LLANYLIB_RANDOM_HPP_
#define LLANYLIB_RANDOM_MAYOR_ 8
#define LLANYLIB_RANDOM_MINOR_ 0

#include "bits.hpp"
#include "hash_pack.hpp"

#include <array>

namespace llcpp {
namespace meta {

class Random {
	public:
		using Divisor = bits::type_division_cluster;
		using Pattern = std::array<ll_bool_t, 3>;
	protected:
		hash::Hash64 seed;	// Seed for next hash
		hash::Hash64FunctionPack generator;
		Pattern pattern;
	protected:
		constexpr void updateSeed() __LL_EXCEPT__ {
			// Tries to get a new seed 5 times
			// If still gets an invalid value, keeps old value
			len_t tries{};
			do {
				auto h = this->generator.call(this->seed);
				if (h.has_value()) {
					this->seed = *h;
					break;
				}
				else ++tries;
			} while (tries < 5);
		}
	public:
		#pragma region Constructors
		#pragma region Base
		constexpr Random(const hash::Hash64FunctionPack& generator) __LL_EXCEPT__ : seed(), generator(generator), pattern() { pattern.fill(LL_TRUE); }
		constexpr Random(hash::Hash64FunctionPack&& generator) __LL_EXCEPT__ : seed(), generator(std::move(generator)), pattern() { pattern.fill(LL_TRUE); }
		constexpr ~Random() __LL_EXCEPT__ {}

		constexpr Random(const hash::Hash64& seed, const hash::Hash64FunctionPack& generator) __LL_EXCEPT__
			: seed(seed), generator(generator), pattern() { pattern.fill(LL_TRUE); }
		constexpr Random(hash::Hash64&& seed, hash::Hash64FunctionPack&& generator) __LL_EXCEPT__
			: seed(std::move(seed)), generator(std::move(generator)), pattern() { pattern.fill(LL_TRUE); }
		constexpr Random(hash::Hash64&& seed, const hash::Hash64FunctionPack& generator) __LL_EXCEPT__
			: seed(std::move(seed)), generator(generator), pattern() { pattern.fill(LL_TRUE); }
		constexpr Random(const hash::Hash64& seed, hash::Hash64FunctionPack&& generator) __LL_EXCEPT__
			: seed(seed), generator(std::move(generator)), pattern() { pattern.fill(LL_TRUE); }

		#pragma endregion
		#pragma region StrPair
		constexpr Random(const StrPair& seed, const hash::Hash64FunctionPack& generator) __LL_EXCEPT__ : Random(generator) {
			auto h = this->generator.call(seed);
			if (h.has_value()) this->seed = *h;
		}
		constexpr Random(const StrPair& seed, hash::Hash64FunctionPack&& generator) __LL_EXCEPT__ : Random(std::move(generator)) {
			auto h = this->generator.call(seed);
			if (h.has_value()) this->seed = *h;
		}

		#pragma endregion
		#pragma region String
		constexpr Random(ll_string_t seed, const len_t size, const hash::Hash64FunctionPack& generator) __LL_EXCEPT__
			: Random(StrPair(seed, size), generator) {}
		constexpr Random(ll_string_t seed, const len_t size, hash::Hash64FunctionPack&& generator) __LL_EXCEPT__
			: Random(StrPair(seed, size), std::move(generator)) {}

		template<len_t N>
		constexpr Random(const ll_char_t(&seed)[N], const hash::Hash64FunctionPack& generator) __LL_EXCEPT__
			: Random(StrPair(seed, N), generator) {}
		template<len_t N>
		constexpr Random(const ll_char_t(&seed)[N], hash::Hash64FunctionPack&& generator) __LL_EXCEPT__
			: Random(StrPair(seed, N), std::move(generator)) {}

		#pragma endregion
		#pragma region Values
		#pragma region 8
		constexpr Random(const ui8 seed, const hash::Hash64FunctionPack& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), generator) {}
		constexpr Random(const ui8 seed, hash::Hash64FunctionPack&& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), std::move(generator)) {}

		constexpr Random(const i8 seed, const hash::Hash64FunctionPack& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), generator) {}
		constexpr Random(const i8 seed, hash::Hash64FunctionPack&& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), std::move(generator)) {}

		#pragma endregion
		#pragma region 16
		constexpr Random(const ui16 seed, const hash::Hash64FunctionPack& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), generator) {}
		constexpr Random(const ui16 seed, hash::Hash64FunctionPack&& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), std::move(generator)) {}

		constexpr Random(const i16 seed, const hash::Hash64FunctionPack& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), generator) {}
		constexpr Random(const i16 seed, hash::Hash64FunctionPack&& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), std::move(generator)) {}

		#pragma endregion
		#pragma region 32
		constexpr Random(const ui32 seed, const hash::Hash64FunctionPack& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), generator) {}
		constexpr Random(const ui32 seed, hash::Hash64FunctionPack&& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), std::move(generator)) {}

		constexpr Random(const i32 seed, const hash::Hash64FunctionPack& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), generator) {}
		constexpr Random(const i32 seed, hash::Hash64FunctionPack&& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), std::move(generator)) {}

		#pragma endregion
		#pragma region 64
		constexpr Random(const ui64 seed, const hash::Hash64FunctionPack& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), generator) {}
		constexpr Random(const ui64 seed, hash::Hash64FunctionPack&& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), std::move(generator)) {}

		constexpr Random(const i64 seed, const hash::Hash64FunctionPack& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), generator) {}
		constexpr Random(const i64 seed, hash::Hash64FunctionPack&& generator) __LL_EXCEPT__
			: Random(hash::Hash64(seed), std::move(generator)) {}

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
				i = bits::get(this->seed.get(), pos);
				pos += 16;
			}
		}

		#pragma endregion
		#pragma region RandomWithPattern
		template<class T> __LL_NODISCARD__ constexpr  T rand(const ll_bool_t* pattern) __LL_EXCEPT__ { return T(); }
		template<> __LL_NODISCARD__ constexpr ui8 rand<ui8>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			this->updateSeed();
			return Divisor::convert<ui64, ui8>(this->seed.get(), pattern);
		}
		template<> __LL_NODISCARD__ constexpr ui16 rand<ui16>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			this->updateSeed();
			return Divisor::convert<ui64, ui16>(this->seed.get(), pattern);
		}
		template<> __LL_NODISCARD__ constexpr ui32 rand<ui32>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			this->updateSeed();
			return Divisor::convert<ui64, ui32>(this->seed.get(), pattern);
		}
		template<> __LL_NODISCARD__ constexpr i8 rand<i8>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			this->updateSeed();
			return Divisor::convert<i64, i8>(this->seed.get(), pattern);
		}
		template<> __LL_NODISCARD__ constexpr i16 rand<i16>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			this->updateSeed();
			return Divisor::convert<i64, i16>(this->seed.get(), pattern);
		}
		template<> __LL_NODISCARD__ constexpr i32 rand<i32>(const ll_bool_t* pattern) __LL_EXCEPT__ {
			this->updateSeed();
			return Divisor::convert<i64, i32>(this->seed.get(), pattern);
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
			return this->rand<ui8>(this->pattern.data());
		}
		template<> __LL_NODISCARD__ constexpr ui16 rand<ui16>() __LL_EXCEPT__ {
			return this->rand<ui16>(this->pattern.data());
		}
		template<> __LL_NODISCARD__ constexpr ui32 rand<ui32>() __LL_EXCEPT__ {
			return this->rand<ui32>(this->pattern.data());
		}
		template<> __LL_NODISCARD__ constexpr ui64 rand<ui64>() __LL_EXCEPT__ {
			this->updateSeed();
			return this->seed.get();
		}
		template<> __LL_NODISCARD__ constexpr ui128 rand<ui128>() __LL_EXCEPT__ {
			return ui128(this->rand<ui64>(), this->rand<ui64>());
		}
		template<> __LL_NODISCARD__ constexpr i8 rand<i8>() __LL_EXCEPT__ {
			return this->rand<i8>(this->pattern.data());
		}
		template<> __LL_NODISCARD__ constexpr i16 rand<i16>() __LL_EXCEPT__ {
			return this->rand<i16>(this->pattern.data());
		}
		template<> __LL_NODISCARD__ constexpr i32 rand<i32>() __LL_EXCEPT__ {
			return this->rand<i32>(this->pattern.data());
		}
		template<> __LL_NODISCARD__ constexpr i64 rand<i64>() __LL_EXCEPT__ {
			this->updateSeed();
			return this->seed.get();
		}
		template<> __LL_NODISCARD__ constexpr i128 rand<i128>() __LL_EXCEPT__ {
			return i128(this->rand<i64>(), this->rand<i64>());
		}
		template<> __LL_NODISCARD__ constexpr f64 rand<f64>() __LL_EXCEPT__ {
			return this->rand<f64>(this->pattern.data());
		}
		template<> __LL_NODISCARD__ constexpr f32 rand<f32>() __LL_EXCEPT__ {
			return this->rand<f32>(this->pattern.data());
		}

		#pragma endregion
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_RANDOM_HPP_
