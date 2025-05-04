//////////////////////////////////////////////
//	LlanyHash.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_LLANYHASH_INCOMPLETE_HPP_)
	#if LLANYLIB_LLANYHASH_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_LLANYHASH_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "CityHash.hpp(incomplete) version error!"
		#else
			#error "CityHash.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_LLANYHASH_INCOMPLETE_MAYOR_ || LLANYLIB_LLANYHASH_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_LLANYHASH_INCOMPLETE_HPP_)
	#define LLANYLIB_LLANYHASH_INCOMPLETE_HPP_
	#define LLANYLIB_LLANYHASH_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_LLANYHASH_INCOMPLETE_MINOR_ 0


#elif defined(LLANYLIB_LLANYHASH_HPP_)
	#if LLANYLIB_LLANYHASH_MAYOR_ != 12 || LLANYLIB_LLANYHASH_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "CityHash.hpp version error!"
		#else
			#error "CityHash.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_LLANYHASH_MAYOR_ || LLANYLIB_LLANYHASH_MINOR_

#else
	#define LLANYLIB_LLANYHASH_HPP_
	#define LLANYLIB_LLANYHASH_MAYOR_ 12
	#define LLANYLIB_LLANYHASH_MINOR_ 0

#include "../traits/ValidationChecker.hpp"
#include "../traits_base/checker.hpp"

#include "../concepts/hash.hpp"

#include "../utils_base/bits.hpp"
#include "../utils_base/Exceptions.hpp"

#include "Algorithm.hpp"
#include "hash_macros.hpp"

namespace llcpp {
namespace meta {
namespace concepts {
namespace hash {
namespace llcpp {

template<class T>
concept IsValidLlanyHashAlgorithm = requires (const T t, const u64 u6) {
	{ t.process(u6, u6) } noexcept -> ::llcpp::meta::concepts::base::IsSameOrVoid<u64>;
};

template<class T, class byte>
concept HasMemcopy = requires (const T t, byte* dst, const byte* src, const u8 bytes) {
	{ t.memcopy(dst, src, bytes) } noexcept -> ::std::same_as<void>;
};

} // namespace llcpp
} // namespace hash
} // namespace concepts
namespace utils {
namespace hash {

template<
	class T = i8,
	class _Algorithm = ::llcpp::meta::utils::hash::Algorithm<u64, ::llcpp::meta::utils::hash::AlgorithmMode::SimplestCombine>
>
	requires
		::llcpp::meta::concepts::hash::llcpp::IsValidLlanyHashAlgorithm<_Algorithm>
		&& ::llcpp::meta::traits::is_same_su_v<T, u8>
		&&::llcpp::meta::traits::is_valid_constructor_checker_v<_Algorithm>
class LlanyHash
	: public ::llcpp::meta::traits::ValidationWrapper<_Algorithm, ::llcpp::AlwaysValidTag>
	, public _Algorithm
{
	#pragma region Types
	public:
		// Class related
		using _MyType			= LlanyHash;
		using ValidTag			= ::llcpp::meta::traits::ValidationWrapper<_Algorithm, ::llcpp::AlwaysValidTag>;
		using Algorithm			= _Algorithm;

		// Types and enums
		using byte				= T;
		using bytearray			= const byte*;
		using CityHashMagic		= ::llcpp::meta::utils::hash::magic::Murmur;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr LlanyHash() noexcept = default;
		template<class... Args>
		constexpr LlanyHash(Args&&... args) noexcept requires(::std::is_nothrow_constructible_v<Algorithm, Args...>)
			: ValidTag()
			, Algorithm(::std::forward<Args>(args)...)
		{}
		constexpr ~LlanyHash() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr LlanyHash(const LlanyHash&) noexcept = default;
		constexpr LlanyHash& operator=(const LlanyHash&) noexcept = default;
		constexpr LlanyHash(LlanyHash&&) noexcept = default;
		constexpr LlanyHash& operator=(LlanyHash&&) noexcept = default;

		constexpr LlanyHash(const volatile LlanyHash&) noexcept = delete;
		constexpr LlanyHash& operator=(const volatile LlanyHash&) noexcept = delete;
		constexpr LlanyHash(volatile LlanyHash&&) noexcept = delete;
		constexpr LlanyHash& operator=(volatile LlanyHash&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const LlanyHash*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator LlanyHash*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr u64 llanyHash64_v1(bytearray s, const usize len) const noexcept {
			LL_NULL_STRING_EXCEPTION_CHECK(s, len);

			constexpr _MyType::Algorithm algo{};
			u64 result = CityHashMagic::kMul64;
			u8 pos{};
			for (bytearray end = s + len; s < end; ++s, ++pos) {
				if (pos >= 8) pos = ::llcpp::ZERO_VALUE<decltype(pos)>;
				u8 bit_position = static_cast<u8>(pos << 3);
				u8 result_8b_part = (result >> bit_position) && u8(-1);
				u8 result_new = algo.process(result_8b_part, static_cast<u8>(*s));
				result |= (static_cast<u64>(result_new) << bit_position);
			}

			return result;
		}
		__LL_NODISCARD__ constexpr u64 llanyHash64_v2(bytearray s, const usize len) const noexcept {
			LL_NULL_STRING_EXCEPTION_CHECK(s, len);

			constexpr _MyType::Algorithm algo{};
			u64 result = CityHashMagic::kMul64;
			u8 pos{};
			for (bytearray end = s + len; s < end; ++s, ++pos) {
				if (pos >= 8) pos = ::llcpp::ZERO_VALUE<decltype(pos)>;
				u8 bit_position = static_cast<u8>(pos << 3);
				u8 result_8b_part = (result >> bit_position) && u8(-1);
				u8 result_new = algo.process(result_8b_part, static_cast<u8>(*s));
				result = (result << 8) | result_new;
			}

			return result;
		}
		__LL_NODISCARD__ constexpr u64 llanyHash64_v3(bytearray s, const usize len) const noexcept {
			LL_NULL_STRING_EXCEPTION_CHECK(s, len);

			constexpr _MyType::Algorithm algo{};
			u64 result = CityHashMagic::kMul64;
			u8 pos{};
			for (bytearray end = s + len; s < end; ++s, ++pos) {
				u8 buffer = (result >> 56);
				u8 result_new = algo.process(buffer, static_cast<u8>(*s));
				result = (result << 8) | result_new;
			}

			return result;
		}

		// This function is not constexpr because it does pointer casts between u8 and u64
		// Right not, those cast are not valid (-std=c++20)
		// Prob valid constexpr before -std=c++26
		template<class CopyCat = _MyType>
		__LL_NODISCARD__ u64 llanyHash64Combine(bytearray s, const usize len) const noexcept requires(::llcpp::meta::concepts::hash::llcpp::HasMemcopy<CopyCat, byte>) {
			LL_NULL_STRING_EXCEPTION_CHECK(s, len);

			// Algorithm to use
			constexpr _MyType::Algorithm algo{};

			// Number of groups of b64
			usize full_parts = len >> 3;

			// Bits ungrouped
			u8 leftovers = static_cast<u8>(len & 0b111);

			const u64* vector = reinterpret_cast<const u64*>(s);
			const u64* vector_end = vector + full_parts;
			u64 result = CityHashMagic::kMul64;

			for (const u64* i = vector; i < vector_end; ++i)
				result = algo.process(result, *i);

			// If there is bytes that cannot be grouped, we transform them and combine with the result
			if (leftovers > ::llcpp::ZERO_VALUE<decltype(leftovers)>) {
				u64 extra{};
				// Bytearray of temporal buffer of 64 bits
				byte* c = reinterpret_cast<byte*>(&extra);

				// Begin of bytes unprocessed
				bytearray s_ = s + len - leftovers;

				if constexpr (::std::is_same_v<CopyCat, _MyType>)
					this->memcopy(c, s_, leftovers);
				else CopyCat().memcopy(c, s_, leftovers);

				result = algo.process(result, extra);
			}

			return result;
		}

		constexpr void memcopy(byte* dst, const byte* src, const u8 bytes) const noexcept {
			::llcpp::meta::utils::string::memcopy<byte>(dst, src, src + bytes);
		}

		template<class U>
			requires ::llcpp::meta::concepts::hash::IsValidArray<U, byte>
		__LL_NODISCARD__ constexpr u64 llanyHash64_v1(const U& s) const noexcept {
			LL_STRING_EXCEPTION_CHECK;
			return this->llanyHash64_v1(s.begin(), s.size());
		}
		template<usize N>
		__LL_NODISCARD__ constexpr u64 llanyHash64_v1(const byte(&s)[N]) const noexcept {
			return this->llanyHash64_v1(s, N);
		}

		template<class U>
			requires ::llcpp::meta::concepts::hash::IsValidArray<T, byte>
		__LL_NODISCARD__ constexpr u64 llanyHash64_v2(const U& s) const noexcept {
			LL_STRING_EXCEPTION_CHECK;
			return this->llanyHash64_v2(s.begin(), s.size());
		}
		template<usize N>
		__LL_NODISCARD__ constexpr u64 llanyHash64_v2(const byte(&s)[N]) const noexcept {
			return this->llanyHash64_v2(s, N);
		}

		template<class U>
			requires ::llcpp::meta::concepts::hash::IsValidArray<T, byte>
		__LL_NODISCARD__ constexpr u64 llanyHash64_v3(const U& s) const noexcept {
			LL_STRING_EXCEPTION_CHECK;
			return this->llanyHash64_v3(s.begin(), s.size());
		}
		template<usize N>
		__LL_NODISCARD__ constexpr u64 llanyHash64_v3(const byte(&s)[N]) const noexcept {
			return this->llanyHash64_v3(s, N);
		}

		/*template<class U, class CopyCat = _MyType>
			requires ::llcpp::meta::concepts::hash::IsValidArray<T, byte>
		__LL_NODISCARD__ u64 llanyHash64Combine(const U& s) const noexcept {
			LL_STRING_EXCEPTION_CHECK;
			return this->llanyHash64Combine<CopyCat>(s.begin(), s.size());
		}
		template<usize N, class CopyCat = _MyType>
		__LL_NODISCARD__ u64 llanyHash64Combine(const byte(&s)[N]) const noexcept {
			return this->llanyHash64Combine<CopyCat>(s, N);
		}*/

		#pragma endregion

	#pragma endregion
};

} // namespace hash
} // namespace utils
} // namespace meta
} // namespace llcpp

#undef LL_STRING_EXCEPTION_CHECK
#undef LL_NULL_STRING_EXCEPTION_CHECK

#endif // LLANYLIB_LLANYHASH_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
