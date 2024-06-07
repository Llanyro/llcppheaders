//////////////////////////////////////////////
//	StandardHash.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.3							//
//////////////////////////////////////////////

#if defined(LLANYLIB_STANDARDHASH_HPP_) // Guard && version protector
	#if LLANYLIB_STANDARDHASH_MAYOR_ != 7 || LLANYLIB_STANDARDHASH_MINOR_ < 3
		#if defined(LL_REAL_CXX23)
			#warning "StandardHash.hpp version error!"
		#else
			#error "StandardHash.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_STANDARDHASH_MAYOR_ || LLANYLIB_STANDARDHASH_MINOR_

#else !defined(LLANYLIB_STANDARDHASH_HPP_)
#define LLANYLIB_STANDARDHASH_HPP_
#define LLANYLIB_STANDARDHASH_MAYOR_ 7
#define LLANYLIB_STANDARDHASH_MINOR_ 3

#include "llanyhash.hpp"
#include "cityhash.hpp"
#include "hash_tools.hpp"

#if defined(WINDOWS_SYSTEM)
	#pragma warning(push)
	#pragma warning(disable:4100) // Ignore unused variables
#endif // WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace hash {
namespace __internal__ {

namespace city {
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_wstr(ll_wstring_t str, len_t size) __LL_EXCEPT__ {
	constexpr len_t PARSER_BUFFER_SIZE = 512;
	ll_char_t buffer[PARSER_BUFFER_SIZE]{};
	len_t buffer_len = sizeof(ll_wchar_t) * size;
	if (buffer_len > PARSER_BUFFER_SIZE) return hash::INVALID_HASH64;

	ll_char_t* i = buffer;
	for (ll_wstring_t data_end = str + size; str < data_end; ++str)
		basic_type_hash::conversor<ll_wchar_t>(i, *str);
	return hash::city::CityHash::cityHash64(buffer, buffer_len);
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_str(const std::string& str) __LL_EXCEPT__ {
	return hash::INVALID_HASH64;
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_wstr(const std::wstring& str) __LL_EXCEPT__ {
	return hash::INVALID_HASH64;
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_wstr(const meta::wStrPair& str) __LL_EXCEPT__ {
	return city::hash_wstr(str.begin(), str.len());
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_wstr(const meta::wStr& str) __LL_EXCEPT__ {
	return city::hash_wstr(str.begin(), str.len());
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash(const hash::Hash64& h) __LL_EXCEPT__ {
	return hash::basic_type_hash::hashValue<ui64>(h.get(), hash::city::CityHash::cityHash64);
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 empty(const void*, const meta::StrTypeid&) __LL_EXCEPT__ {
	return hash::INVALID_HASH64;
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 empty(const void*, const meta::wStrTypeid&) __LL_EXCEPT__ {
	return hash::INVALID_HASH64;
}

} // namespace city
namespace llany {
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_wstr(ll_wstring_t str, len_t size) __LL_EXCEPT__ {
	constexpr len_t PARSER_BUFFER_SIZE = 512;
	ll_char_t buffer[PARSER_BUFFER_SIZE]{};
	len_t buffer_len = sizeof(ll_wchar_t) * size;
	if (buffer_len > PARSER_BUFFER_SIZE) return hash::INVALID_HASH64;

	ll_char_t* i = buffer;
	for (ll_wstring_t data_end = str + size; str < data_end; ++str)
		basic_type_hash::conversor<ll_wchar_t>(i, *str);
	return hash::LlanyHash::llanyHash64(buffer, buffer_len);
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_str(const std::string& str) __LL_EXCEPT__ {
	return hash::INVALID_HASH64;
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_wstr(const std::wstring& str) __LL_EXCEPT__ {
	return hash::INVALID_HASH64;
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_wstr(const meta::wStrPair& str) __LL_EXCEPT__ {
	return llany::hash_wstr(str.begin(), str.len());
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash_wstr(const meta::wStr& str) __LL_EXCEPT__ {
	return llany::hash_wstr(str.begin(), str.len());
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 hash(const hash::Hash64& h) __LL_EXCEPT__ {
	return hash::basic_type_hash::hashValue<ui64>(h.get(), hash::LlanyHash::llanyHash64);
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 empty(const void*, const meta::StrTypeid&) __LL_EXCEPT__ {
	return hash::INVALID_HASH64;
}
__LL_NODISCARD__ constexpr hash::OptionalHash64 empty(const void*, const meta::wStrTypeid&) __LL_EXCEPT__ {
	return hash::INVALID_HASH64;
}

} // namespace llany

} // namespace __internal__

__LL_VAR_INLINE__ constexpr Hash64Function STANDARD_Hash64Function = city::CityHash::cityHash64;
__LL_VAR_INLINE__ constexpr wHash64Function STANDARD_wHash64Function = __internal__::city::hash_wstr;
__LL_VAR_INLINE__ constexpr StringPairHash64Function STANDARD_StringPairHash64Function = __internal__::city::hash_str;
__LL_VAR_INLINE__ constexpr wStringPairHash64Function STANDARD_wStringPairHash64Function = __internal__::city::hash_wstr;
__LL_VAR_INLINE__ constexpr StrPairHash64Function STANDARD_StrPairHash64Function = city::CityHash::cityHash64;
__LL_VAR_INLINE__ constexpr wStrPairHash64Function STANDARD_wStrPairHash64Function = __internal__::city::hash_wstr;
__LL_VAR_INLINE__ constexpr StrHash64Function STANDARD_StrHash64Function = city::CityHash::cityHash64;
__LL_VAR_INLINE__ constexpr wStrHash64Function STANDARD_wStrHash64Function = __internal__::city::hash_wstr;
__LL_VAR_INLINE__ constexpr RecursiveHash64Function STANDARD_RecursiveHash64Function = __internal__::city::hash;
__LL_VAR_INLINE__ constexpr StrTypeidHash64Function STANDARD_StrTypeidHash64Function = __internal__::city::empty;
__LL_VAR_INLINE__ constexpr wStrTypeidHash64Function STANDARD_wStrTypeidHash64Function = __internal__::city::empty;

__LL_VAR_INLINE__ constexpr Hash64Function FAST_Hash64Function = hash::LlanyHash::llanyHash64;
__LL_VAR_INLINE__ constexpr wHash64Function FAST_wHash64Function = __internal__::llany::hash_wstr;
__LL_VAR_INLINE__ constexpr StringPairHash64Function FAST_StringPairHash64Function = __internal__::llany::hash_str;
__LL_VAR_INLINE__ constexpr wStringPairHash64Function FAST_wStringPairHash64Function = __internal__::llany::hash_wstr;
__LL_VAR_INLINE__ constexpr StrPairHash64Function FAST_StrPairHash64Function = hash::LlanyHash::llanyHash64;
__LL_VAR_INLINE__ constexpr wStrPairHash64Function FAST_wStrPairHash64Function = __internal__::llany::hash_wstr;
__LL_VAR_INLINE__ constexpr StrHash64Function FAST_StrHash64Function = hash::LlanyHash::llanyHash64;
__LL_VAR_INLINE__ constexpr wStrHash64Function FAST_wStrHash64Function = __internal__::llany::hash_wstr;
__LL_VAR_INLINE__ constexpr RecursiveHash64Function FAST_RecursiveHash64Function = __internal__::llany::hash;
__LL_VAR_INLINE__ constexpr StrTypeidHash64Function FAST_StrTypeidHash64Function = __internal__::llany::empty;
__LL_VAR_INLINE__ constexpr wStrTypeidHash64Function FAST_wStrTypeidHash64Function = __internal__::llany::empty;

__LL_VAR_INLINE__ constexpr hash::Hash64FunctionPack STANDARD_HASH_FUNCTION_PACK = {
	STANDARD_Hash64Function,
	STANDARD_wHash64Function,
	STANDARD_StringPairHash64Function,
	STANDARD_wStringPairHash64Function,
	STANDARD_StrPairHash64Function,
	STANDARD_wStrPairHash64Function,
	STANDARD_StrHash64Function,
	STANDARD_wStrHash64Function,
	STANDARD_RecursiveHash64Function,
	STANDARD_StrTypeidHash64Function,
	STANDARD_wStrTypeidHash64Function
};
__LL_VAR_INLINE__ constexpr hash::Hash64FunctionPack FAST_HASH_FUNCTION_PACK = {
	FAST_Hash64Function,
	FAST_wHash64Function,
	FAST_StringPairHash64Function,
	FAST_wStringPairHash64Function,
	FAST_StrPairHash64Function,
	FAST_wStrPairHash64Function,
	FAST_StrHash64Function,
	FAST_wStrHash64Function,
	FAST_RecursiveHash64Function,
	FAST_StrTypeidHash64Function,
	FAST_wStrTypeidHash64Function
};

__LL_VAR_INLINE__ constexpr hash::HashTool STANDARD_HASH_TOOLS = hash::HashTool<>(STANDARD_HASH_FUNCTION_PACK);
__LL_VAR_INLINE__ constexpr hash::HashTool FAST_HASH_TOOLS = hash::HashTool<>(FAST_HASH_FUNCTION_PACK);

} // namespace hash
} // namespace meta
} // namespace llcpp

#if defined(WINDOWS_SYSTEM)
	#pragma warning(pop)
#endif // WINDOWS_SYSTEM

#endif // LLANYLIB_STANDARDHASH_HPP_
