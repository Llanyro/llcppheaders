//////////////////////////////////////////////
//	StandardHash.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 6.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_STANDARDHASH_HPP_) // Guard && version protector
	#if LLANYLIB_STANDARDHASH_MAYOR_ != 6 || LLANYLIB_STANDARDHASH_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "StandardHash.hpp version error!"
		#else
			#error "StandardHash.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_STANDARDHASH_MAYOR_ || LLANYLIB_STANDARDHASH_MINOR_

#else !defined(LLANYLIB_STANDARDHASH_HPP_)
#define LLANYLIB_STANDARDHASH_HPP_
#define LLANYLIB_STANDARDHASH_MAYOR_ 6
#define LLANYLIB_STANDARDHASH_MINOR_ 0

#include "cityhash.hpp"

namespace llcpp {
namespace meta {
namespace hash {
namespace __internal__ {
constexpr len_t PARSER_BUFFER_SIZE = 512;
thread_local ll_char_t HASH_BUFFER[256];

__LL_NODISCARD__ constexpr hash::Hash64 hash_wstr(ll_wstring_t str, len_t size) {
	len_t BUFFERLEN = sizeof(ll_wchar_t) * size;
	if (BUFFERLEN > PARSER_BUFFER_SIZE) return hash::Hash64();

	ll_char_t buffer[PARSER_BUFFER_SIZE]{};
	ll_char_t* i = buffer;
	for (ll_wstring_t data_end = str + size; str < data_end; ++str)
		basic_type_hash::conversor<ll_wchar_t>(i, *str);
	return city::CityHash::cityHash64(HASH_BUFFER, BUFFERLEN);
}
__LL_NODISCARD__ constexpr hash::Hash64 hash_wstr(const meta::wStrPair& str) {
	return hash_wstr(str.begin(), str.len());
}
__LL_NODISCARD__ constexpr hash::Hash64 hash_wstr(const meta::wStr& str) {
	return hash_wstr(str.begin(), str.len());
}
__LL_NODISCARD__ constexpr hash::Hash64 hash(const hash::Hash64& h) {
	return hash::basic_type_hash::hashValue<ui64>(h.get(), city::CityHash::cityHash64);
}
__LL_NODISCARD__ constexpr hash::Hash64 empty(const void*, const meta::StrTypeid&) {
	return hash::Hash64();
}
__LL_NODISCARD__ constexpr hash::Hash64 empty(const void*, const meta::wStrTypeid&) {
	return hash::Hash64();
}

} // namespace __internal__

constexpr HashFunction STANDARD_HashFunction = city::CityHash::cityHash64;
constexpr wHashFunction STANDARD_wHashFunction = __internal__::hash_wstr;
constexpr StrPairHashFunction STANDARD_StrPairHashFunction = city::CityHash::cityHash64;
constexpr wStrPairHashFunction STANDARD_wStrPairHashFunction = __internal__::hash_wstr;
constexpr StrHashFunction STANDARD_StrHashFunction = city::CityHash::cityHash64;
constexpr wStrHashFunction STANDARD_wStrHashFunction = __internal__::hash_wstr;
constexpr HashRecursiveFunction STANDARD_HashRecursiveFunction = __internal__::hash;
constexpr HashStrTypeidFunction STANDARD_HashStrTypeidFunction = __internal__::empty;
constexpr HashwStrTypeidFunction STANDARD_HashwStrTypeidFunction = __internal__::empty;

constexpr hash::HashFunctionPack STANDARD_HASH_FUNCTION_PACK = {
	STANDARD_HashFunction,
	STANDARD_wHashFunction,
	STANDARD_StrPairHashFunction,
	STANDARD_wStrPairHashFunction,
	STANDARD_StrHashFunction,
	STANDARD_wStrHashFunction,
	STANDARD_HashRecursiveFunction,
	STANDARD_HashStrTypeidFunction,
	STANDARD_HashwStrTypeidFunction
};

constexpr hash::HashTool STANDARD_HASH_TOOLS = hash::HashTool(STANDARD_HASH_FUNCTION_PACK);

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_STANDARDHASH_HPP_
