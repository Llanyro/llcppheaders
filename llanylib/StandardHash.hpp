//////////////////////////////////////////////
//	StandardHash.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_STANDARDHASH_HPP_) // Guard && version protector
	#if LLANYLIB_STANDARDHASH_MAYOR_ != 7 || LLANYLIB_STANDARDHASH_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "StandardHash.hpp version error!"
		#else
			#error "StandardHash.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_STANDARDHASH_MAYOR_ || LLANYLIB_STANDARDHASH_MINOR_

#else !defined(LLANYLIB_STANDARDHASH_HPP_)
#define LLANYLIB_STANDARDHASH_HPP_
#define LLANYLIB_STANDARDHASH_MAYOR_ 7
#define LLANYLIB_STANDARDHASH_MINOR_ 0

#include "cityhash.hpp"

namespace llcpp {
namespace meta {
namespace hash {
namespace __internal__ {
constexpr len_t PARSER_BUFFER_SIZE = 512;
thread_local ll_char_t HASH_BUFFER[256];

__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_wstr(ll_wstring_t str, len_t size) {
	len_t BUFFERLEN = sizeof(ll_wchar_t) * size;
	if (BUFFERLEN > PARSER_BUFFER_SIZE) return hash::INVALID_HASH;

	ll_char_t buffer[PARSER_BUFFER_SIZE]{};
	ll_char_t* i = buffer;
	for (ll_wstring_t data_end = str + size; str < data_end; ++str)
		(void)basic_type_hash::conversor<ll_wchar_t>(i, *str);
	return city::CityHash::cityHash64(HASH_BUFFER, BUFFERLEN);
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_wstr(const meta::wStrPair& str) {
	return hash_wstr(str.begin(), str.len());
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_wstr(const meta::wStr& str) {
	return hash_wstr(str.begin(), str.len());
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash(const hash::Hash64& h) {
	return hash::basic_type_hash::hashValue<ui64>(h.get(), city::CityHash::cityHash64);
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 empty(const void*, const meta::StrTypeid&) {
	return hash::INVALID_HASH;
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 empty(const void*, const meta::wStrTypeid&) {
	return hash::INVALID_HASH;
}

} // namespace __internal__

constexpr Hash64Function STANDARD_Hash64Function = city::CityHash::cityHash64;
constexpr wHash64Function STANDARD_wHash64Function = __internal__::hash_wstr;
constexpr StrPairHash64Function STANDARD_StrPairHash64Function = city::CityHash::cityHash64;
constexpr wStrPairHash64Function STANDARD_wStrPairHash64Function = __internal__::hash_wstr;
constexpr StrHash64Function STANDARD_StrHash64Function = city::CityHash::cityHash64;
constexpr wStrHash64Function STANDARD_wStrHash64Function = __internal__::hash_wstr;
constexpr RecursiveHash64Function STANDARD_RecursiveHash64Function = __internal__::hash;
constexpr StrTypeidHash64Function STANDARD_StrTypeidHash64Function = __internal__::empty;
constexpr wStrTypeidHash64Function STANDARD_wStrTypeidHash64Function = __internal__::empty;

constexpr hash::Hash64FunctionPack STANDARD_HASH_FUNCTION_PACK = {
	STANDARD_Hash64Function,
	STANDARD_wHash64Function,
	STANDARD_StrPairHash64Function,
	STANDARD_wStrPairHash64Function,
	STANDARD_StrHash64Function,
	STANDARD_wStrHash64Function,
	STANDARD_RecursiveHash64Function,
	STANDARD_StrTypeidHash64Function,
	STANDARD_wStrTypeidHash64Function
};

constexpr hash::HashTool STANDARD_HASH_TOOLS = hash::HashTool(STANDARD_HASH_FUNCTION_PACK);

} // namespace hash
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_STANDARDHASH_HPP_
