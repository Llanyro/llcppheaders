//////////////////////////////////////////////
//	llanyhash.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.3							//
//////////////////////////////////////////////

#if defined(LLANYLIB_LLANYHASH_HPP_) // Guard && version protector
	#if LLANYLIB_LLANYHASH_MAYOR_ != 7 || LLANYLIB_LLANYHASH_MINOR_ < 3
		#if defined(LL_REAL_CXX23)
			#warning "llanyhash.hpp version error!"
		#else
			#error "llanyhash.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_LLANYHASH_MAYOR_ || LLANYLIB_LLANYHASH_MINOR_

#else !defined(LLANYLIB_LLANYHASH_HPP_)
#define LLANYLIB_LLANYHASH_HPP_
#define LLANYLIB_LLANYHASH_MAYOR_ 7
#define LLANYLIB_LLANYHASH_MINOR_ 3

#include "bits.hpp"
#include "hash_pack.hpp"
#include "ArrayView.hpp"

namespace llcpp {
namespace meta {
namespace hash {

struct LlanyHash {
	public:
		using Combine64 = ui64(*)(ui64, ui64);
		__LL_NODISCARD__ static hash::OptionalHash64 llanyHash64Combine_impl(ll_string_t s, const len_t len, Combine64 combine) __LL_EXCEPT__ {
			if (!s || !combine) return hash::INVALID_HASH64;

			// Number of groups of b64
			len_t full_parts = len >> 3;

			// Bits ungrouped
			ui8 leftovers = static_cast<ui8>(len & 0b111);

			const len_t* vector = reinterpret_cast<const ui64*>(s);
			const len_t* vector_end = vector + full_parts;;
			ui64 result = hash::combine::kMul64;
			for (const len_t* i = vector; i < vector_end; ++i)
				result = combine(result, *i);

			// If there is bytes that cannot be grouped, we transform them and combine with the result
			if (leftovers > ZERO_UI8) {
				len_t extra{};
				ll_char_t* c = reinterpret_cast<ll_char_t*>(&extra);

				ll_string_t s_ = s + len - leftovers;
				for (ll_string_t c_end = c + leftovers; c < c_end; ++c, ++s_) *c = *s_;

				result = combine(result, extra);
			}

			return result;
		}
		__LL_NODISCARD__ static hash::OptionalHash64 llanyHash64Combine(ll_string_t s, const len_t len, Combine64 combine) __LL_EXCEPT__ {
			return hash::LlanyHash::llanyHash64Combine_impl(s, len, hash::combine::murmur64Combine);
			//return hash::LlanyHash::llanyHash64Combine_impl(s, len, hash::combine::simple64Combine_noshift);
		}
	public:
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 llanyHash64_v1(ll_string_t s, len_t len) __LL_EXCEPT__ {
			if (!s) return hash::INVALID_HASH64;

			ui64 result = hash::combine::kMul64;
			ui8 pos{};
			for (ll_string_t end = s + len; s < end; ++s, ++pos) {
				if (pos >= 8) pos = ZERO_UI8;
				ui8 pos_b = (pos << 3);
				ui8 result_8b_part = (result >> pos_b) && 0xff;
				ui8 result = hash::combine::simple8Combine_noshift<LL_FALSE>(result_8b_part, *s);
				result |= (static_cast<ui64>(result) << pos_b);
			}

			return result;
		}
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 llanyHash64_v2(ll_string_t s, len_t len) __LL_EXCEPT__ {
			if (!s) return hash::INVALID_HASH64;

			ui64 result = hash::combine::kMul64;
			ui8 pos{};
			for (ll_string_t end = s + len; s < end; ++s, ++pos) {
				if (pos >= 8) pos = ZERO_UI8;
				ui8 pos_b = (pos << 3);
				ui8 result_8b_part = (result >> pos_b) && 0xff;
				ui8 result = hash::combine::simple8Combine_noshift<LL_FALSE>(result_8b_part, *s);
				result = (result << 8) | result;
			}

			return result;
		}
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 llanyHash64_v3(ll_string_t s, len_t len) __LL_EXCEPT__ {
			if (!s) return hash::INVALID_HASH64;

			ui64 result = hash::combine::kMul64;
			for (ll_string_t end = s + len; s < end; ++s) {
				ui8 buffer = (result >> 56);
				ui8 result = hash::combine::simple8Combine_noshift<LL_FALSE>(buffer, *s);
				result = (result << 8) | result;
			}

			return result;
		}
	public:
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 llanyHash64(ll_string_t s, len_t len) __LL_EXCEPT__ {
			return hash::LlanyHash::llanyHash64_v2(s, len);
		}
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 llanyHash64(const meta::StrPair& s) __LL_EXCEPT__ {
			if (s.empty()) return hash::INVALID_HASH64;
			else return hash::LlanyHash::llanyHash64(s.begin(), s.len());
		}
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 llanyHash64(const meta::Str& s) __LL_EXCEPT__ {
			if (s.empty()) return hash::INVALID_HASH64;
			else return hash::LlanyHash::llanyHash64(s.begin(), s.len());
		}
		template<len_t N>
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 llanyHash64(const ll_char_t(&s)[N]) __LL_EXCEPT__ {
			if (!s) return hash::INVALID_HASH64;
			else return hash::LlanyHash::llanyHash64(s, N - 1);
		}
		// Only admits hash::basic_type_hash::is_convertible_v<>
		// Returns hash::INVALID_HASH64 if invalid type or hash error
		template<class U, class W = traits::template_types<U>>
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 llanyHash64(typename W::cinput value) __LL_EXCEPT__ {
			return hash::basic_type_hash::hashValue<U, W>(value, hash::LlanyHash::llanyHash64);
		}
		__LL_NODISCARD__ static constexpr hash::OptionalHash64 llanyHash64(const hash::Hash64& hash) __LL_EXCEPT__ {
			return hash::basic_type_hash::hashValue<ui64>(hash.get(), hash::LlanyHash::llanyHash64);
		}
};

constexpr auto opt_1 = *hash::LlanyHash::llanyHash64("Hola mundo");
constexpr auto opt_2 = *hash::LlanyHash::llanyHash64("Hola mundo2");

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_LLANYHASH_HPP_
