//////////////////////////////////////////////
//	cityhash.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// This port is based on cityhash wich authors are Geoff Pike and Jyrki Alakuijala			//
// This port only tries to have a precompiled hash function of precompiled data				//
//////////////////////////////////////////////////////////////////////////////////////////////

#if defined(LLANYLIB_CITYHASH_HPP_) // Guard && version protector
	#if LLANYLIB_CITYHASH_MAYOR_ != 5 || LLANYLIB_CITYHASH_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "cityhash.hpp version error!"
		#else
			#error "cityhash.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_CITYHASH_MAYOR_ || LLANYLIB_CITYHASH_MINOR_

#else !defined(LLANYLIB_CITYHASH_HPP_)
#define LLANYLIB_CITYHASH_HPP_
#define LLANYLIB_CITYHASH_MAYOR_ 5
#define LLANYLIB_CITYHASH_MINOR_ 0

#include "types.hpp"

#if defined(WORDS_BIGENDIAN)
#define ui32_in_expected_order(x) (bswap_32(x))
#define ui64_in_expected_order(x) (bswap_64(x))
#else
#define ui32_in_expected_order(x) (x)
#define ui64_in_expected_order(x) (x)
#endif

namespace llcpp {
namespace city {

namespace __internal__ {
// Some primes between 2^63 and 2^64 for various uses.
constexpr ui64 k0 = 0xc3a5c85c97cb3127ULL;
constexpr ui64 k1 = 0xb492b66fbe98f273ULL;
constexpr ui64 k2 = 0x9ae16a3b2f90404fULL;

// Magic numbers for 32-bit hashing.  Copied from Murmur3.
constexpr ui32 c1 = 0xcc9e2d51;
constexpr ui32 c2 = 0x1b873593;

struct hash128 {
    ui64 first;
    ui64 second;

    __LL_NODISCARD__ constexpr ui64 Uint128Low64() const { return this->first; }
    __LL_NODISCARD__ constexpr ui64 Uint128High64() const { return this->second; }
};

// Assuming ll_char_t is a typedef for char or unsigned char
//template<class T>
//constexpr T memcopy(ll_string_t p) {
//    T result{};
//    for (ui8 i = 0; i < sizeof(T); ++i)
//        result |= static_cast<T>(p[i]) << (i * 8);
//    return result;
//}
template<class T>
__LL_NODISCARD__ constexpr T UNALIGNED_LOAD_T(ll_string_t p) {
    //return memcopy<T>(p);
    T result{};
    for (ui8 i = 0; i < sizeof(T); ++i)
        result |= static_cast<T>(p[i]) << (i * 8);
    return result;
}
__LL_NODISCARD__ constexpr ui64 fetch64(ll_string_t p) { return ui64_in_expected_order(UNALIGNED_LOAD_T<ui64>(p)); }
__LL_NODISCARD__ constexpr ui32 fetch32(ll_string_t p) { return ui32_in_expected_order(UNALIGNED_LOAD_T<ui32>(p)); }

__LL_NODISCARD__ constexpr ui32 bswap_32(const ui32 value) {
    return
        ((value & 0xFF) << 24) |
        ((value & 0xFF00) << 8) |
        ((value & 0xFF0000) >> 8) |
        ((value & 0xFF000000) >> 24);
}
__LL_NODISCARD__ constexpr ui64 bswap_64(const ui64 value) {
    return
        ((value & 0x00000000000000FFull) << 56) |
        ((value & 0x000000000000FF00ull) << 40) |
        ((value & 0x0000000000FF0000ull) << 24) |
        ((value & 0x00000000FF000000ull) << 8) |
        ((value & 0x000000FF00000000ull) >> 8) |
        ((value & 0x0000FF0000000000ull) >> 24) |
        ((value & 0x00FF000000000000ull) >> 40) |
        ((value & 0xFF00000000000000ull) >> 56);
}

// Hash 128 input bits down to 64 bits of output.
// This is intended to be a reasonably good hash function.
__LL_NODISCARD__ constexpr ui64 hash128to64(const hash128& x) {
    // Murmur-inspired hashing.
    constexpr ui64 kMul = 0x9ddfea08eb382d69ull;
    ui64 a = (x.Uint128Low64() ^ x.Uint128High64()) * kMul;
    a ^= (a >> 47);
    ui64 b = (x.Uint128High64() ^ a) * kMul;
    b ^= (b >> 47);
    b *= kMul;
    return b;
}

// Bitwise right rotate.  Normally this will compile to a single
// instruction, especially if the shift is a manifest constant.
__LL_NODISCARD__ constexpr ui64 rotate(const ui64 val, const i32 shift) {
    // Avoid shifting by 64: doing so yields an undefined result.
    return shift == 0 ? val : ((val >> shift) | (val << (64 - shift)));
}
__LL_NODISCARD__ constexpr ui64 shiftMix(const ui64 val) { return val ^ (val >> 47); }
__LL_NODISCARD__ constexpr ui64 hashLen16(const ui64 u, const ui64 v) { return hash128to64(hash128(u, v)); }
__LL_NODISCARD__ constexpr ui64 hashLen16(const ui64 u, const ui64 v, const ui64 mul) {
    // Murmur-inspired hashing.
    ui64 a = (u ^ v) * mul;
    a ^= (a >> 47);
    ui64 b = (v ^ a) * mul;
    b ^= (b >> 47);
    b *= mul;
    return b;
}

__LL_NODISCARD__ constexpr ui64 hashLen0to16(ll_string_t s, const len_t len) {
    if (len >= 8) {
        ui64 mul = k2 + len * 2;
        ui64 a = fetch64(s) + k2;
        ui64 b = fetch64(s + len - 8);
        ui64 c = rotate(b, 37) * mul + a;
        ui64 d = (rotate(a, 25) + b) * mul;
        return hashLen16(c, d, mul);
    }
    if (len >= 4) {
        ui64 mul = k2 + len * 2;
        ui64 a = fetch32(s);
        return hashLen16(len + (a << 3), fetch32(s + len - 4), mul);
    }
    if (len > 0) {
        ui8 a = static_cast<ui8>(s[0]);
        ui8 b = static_cast<ui8>(s[len >> 1]);
        ui8 c = static_cast<ui8>(s[len - 1]);
        ui32 y = static_cast<ui32>(a) + (static_cast<ui32>(b) << 8);
        ui32 z = static_cast<ui32>(len) + (static_cast<ui32>(c) << 2);
        return shiftMix(y * k2 ^ z * k0) * k2;
    }
    return k2;
}
// This probably works well for 16-byte strings as well, but it may be overkill
// in that case.
__LL_NODISCARD__ constexpr ui64 hashLen17to32(ll_string_t s, const len_t len) {
    ui64 mul = k2 + len * 2;
    ui64 a = fetch64(s) * k1;
    ui64 b = fetch64(s + 8);
    ui64 c = fetch64(s + len - 8) * mul;
    ui64 d = fetch64(s + len - 16) * k2;
    return hashLen16(rotate(a + b, 43) + rotate(c, 30) + d, a + rotate(b + k2, 18) + c, mul);
}
// Return an 8-byte hash for 33 to 64 bytes.
__LL_NODISCARD__ constexpr ui64 hashLen33to64(ll_string_t s, const len_t len) {
    ui64 mul = k2 + len * 2;
    ui64 a = fetch64(s) * k2;
    ui64 b = fetch64(s + 8);
    ui64 c = fetch64(s + len - 24);
    ui64 d = fetch64(s + len - 32);
    ui64 e = fetch64(s + 16) * k2;
    ui64 f = fetch64(s + 24) * 9;
    ui64 g = fetch64(s + len - 8);
    ui64 h = fetch64(s + len - 16) * mul;
    ui64 u = rotate(a + g, 43) + (rotate(b, 30) + c) * 9;
    ui64 v = ((a + g) ^ d) + f + 1;
    ui64 w = bswap_64((u + v) * mul) + h;
    ui64 x = rotate(e + f, 42) + c;
    ui64 y = (bswap_64((v + w) * mul) + g) * mul;
    ui64 z = e + f + c;
    a = bswap_64((x + z) * mul + y) + b;
    b = shiftMix((z + a) * mul + d + h) * mul;
    return b + x;
}
// Return a 16-byte hash for 48 bytes.  Quick and dirty.
// Callers do best to use "random-looking" values for a and b.
__LL_NODISCARD__ constexpr hash128 weakHashLen32WithSeeds(const ui64 w, const ui64 x, const ui64 y, const ui64 z, ui64 a, ui64 b) {
    a += w;
    b = rotate(b + a + z, 21);
    ui64 c = a;
    a += x;
    a += y;
    b += rotate(a, 44);
    return { a + z, b + c };
}
// Return a 16-byte hash for s[0] ... s[31], a, and b.  Quick and dirty.
__LL_NODISCARD__ constexpr hash128 weakHashLen32WithSeeds(ll_string_t s, const ui64 a, const ui64 b) {
    return weakHashLen32WithSeeds(
        fetch64(s), fetch64(s + 8),
        fetch64(s + 16), fetch64(s + 24),
        a, b);
}

} // namespace __internal__

__LL_NODISCARD__ constexpr ui64 cityHash64(ll_string_t s, len_t len) {
    if (len <= 32) {
        if (len <= 16) return __internal__::hashLen0to16(s, len);
        else return __internal__::hashLen17to32(s, len);
    }
    else if (len <= 64) return __internal__::hashLen33to64(s, len);

    // For strings over 64 bytes we hash the end first, and then as we
    // loop we keep 56 bytes of state: v, w, x, y, and z.
    ui64 x = __internal__::fetch64(s + len - 40);
    ui64 y = __internal__::fetch64(s + len - 16) + __internal__::fetch64(s + len - 56);
    ui64 z = __internal__::hashLen16(
        __internal__::fetch64(s + len - 48) + len,
        __internal__::fetch64(s + len - 24));
    __internal__::hash128 v = __internal__::weakHashLen32WithSeeds(s + len - 64, len, z);
    __internal__::hash128 w = __internal__::weakHashLen32WithSeeds(s + len - 32, y + __internal__::k1, x);
    x = x * __internal__::k1 + __internal__::fetch64(s);

    // Decrease len to the nearest multiple of 64, and operate on 64-byte chunks.
    len = (len - 1) & ~static_cast<len_t>(63);
    do {
        x = __internal__::rotate(x + y + v.first + __internal__::fetch64(s + 8), 37) * __internal__::k1;
        y = __internal__::rotate(y + v.second + __internal__::fetch64(s + 48), 42) * __internal__::k1;
        x ^= w.second;
        y += v.first + __internal__::fetch64(s + 40);
        z = __internal__::rotate(z + w.first, 33) * __internal__::k1;
        v = __internal__::weakHashLen32WithSeeds(s, v.second * __internal__::k1, x + w.first);
        w = __internal__::weakHashLen32WithSeeds(s + 32, z + w.second, y + __internal__::fetch64(s + 16));
        //std::swap(z, x);
        {
            ui64 tmp = z;
            z = x;
            x = tmp;
        }
        s += 64;
        len -= 64;
    } while (len != 0);
    return __internal__::hashLen16(
        __internal__::hashLen16(v.first, w.first) + __internal__::shiftMix(y) * __internal__::k1 + z,
        __internal__::hashLen16(v.second, w.second) + x);
}

template<class T, len_t N>
__LL_NODISCARD__ constexpr ui64 cityHash64(const T(&data)[N]) {
	return cityHash64(data, sizeof(T) * N);
}

} // namespace city
} // namespace llcpp

#undef ui32_in_expected_order
#undef ui64_in_expected_order

#endif // LLANYLIB_CITYHASH_HPP_
