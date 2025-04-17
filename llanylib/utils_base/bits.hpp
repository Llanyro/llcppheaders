//////////////////////////////////////////////
//	bitss.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_BITS_INCOMPLETE_HPP_)
	#if LLANYLIB_BITS_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_BITS_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "bitss.hpp(incomplete) version error!"
		#else
			#error "bitss.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_BITS_INCOMPLETE_MAYOR_ || LLANYLIB_BITS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_BITS_INCOMPLETE_HPP_)
	#define LLANYLIB_BITS_INCOMPLETE_HPP_
	#define LLANYLIB_BITS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_BITS_INCOMPLETE_MINOR_ 0

#elif defined(LLANYLIB_BITS_HPP_)
	#if LLANYLIB_BITS_MAYOR_ != 12 || LLANYLIB_BITS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "bitss.hpp version error!"
		#else
			#error "bitss.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_BITS_MAYOR_ || LLANYLIB_BITS_MINOR_

#else
	#define LLANYLIB_BITS_HPP_
	#define LLANYLIB_BITS_MAYOR_ 12
	#define LLANYLIB_BITS_MINOR_ 0

#include "../concepts/concepts.hpp"

namespace llcpp {
namespace meta {
namespace utils {
namespace bits {
namespace __bits__ {

template<class T>
__LL_NODISCARD__ constexpr u8* __primitive_to_bytearray(T& value, u8* buffer) noexcept {
	if consteval {
		if constexpr (!::llcpp::meta::traits::is_primitive_v<T>) {
			static_assert(::std::is_convertible_v<T, u8>,
				"Type must be casteable to u8");
			static_assert(::llcpp::meta::concepts::signature::HasOperatorBitwiseRightEq<T, T>,
				"Type needs operator>>=");
		}

		ll_string_t buffer_end = buffer + sizeof(T);
		while (buffer <= buffer_end) {
			if constexpr (::llcpp::meta::traits::is_primitive_v<T>) {
				*buffer = static_cast<u8>(value >> byte) & 0xff;
				byte -= 8;
			}
			else {
				*buffer = static_cast<u8>(val) & 0xff;
				val >>= 8;
			}
			++buffer;
		}
	}
	else {
		if constexpr (::std::is_const_v<T>)
			*reinterpret_cast<T*>(buffer) = ::std::forward<T&>(value);
		else *reinterpret_cast<T*>(buffer) = ::std::forward<T&&>(value);
		return reinterpret_cast<u8*>(buffer + sizeof(T));
	}
}

} // namespace __bits__

template<class T>
__LL_NODISCARD__ constexpr T in_expected_order(const T v) noexcept {
	if constexpr (::llcpp::BIGENDIAN) {
		if constexpr (::std::is_same_v<T, u64>)
			return ::llcpp::meta::utils::bytes_swap_64(v);
		else if constexpr (::std::is_same_v<T, u32>)
			return ::llcpp::meta::utils::bytes_swap_32(v);
		else if constexpr (::std::is_same_v<T, u16>)
			return ::llcpp::meta::utils::bytes_swap_16(v);
		else {
			static_assert(::std::is_same_v<T, u16>,
				"This function only accepts u64, u32, u16");
			return v;
		}
	}
	else return v;
}
template<class T, class U>
	requires ::llcpp::meta::traits::is_same_su_v<U, u8>
__LL_NODISCARD__ constexpr T unaligned_load(const U p) noexcept {
	if consteval {
		T result{};
		for (u8 i{}; i < sizeof(T); ++i)
			result |= static_cast<T>(p[i]) << (i << 3);
		return result;
	}
	else {
		T result;
		::std::memcpy(&result, p, sizeof(result));
		return result;
	}
}

// Uses bitwise operators: [ ">>", "&" ]
// Basic type to char array
// If type has 7 bytes, array will be of 7
template<class T>
__LL_NODISCARD__ constexpr u8* primitive_to_bytearray(T& value, u8* buffer, const usize buffer_size) noexcept {
	constexpr usize SIZEOF = sizeof(T);
	if (buffer_size < SIZEOF)
		return LL_NULLPTR;
	return ::llcpp::meta::utils::bits::__bits__::__primitive_to_bytearray(value, buffer);
}
template<class T>
__LL_NODISCARD__ constexpr u8* primitive_to_bytearray_unchecked(T& value, u8* buffer) noexcept {
	return ::llcpp::meta::utils::bits::__bits__::__primitive_to_bytearray(value, buffer);
}
template<class T, usize N>
//	requires ::llcpp::meta::concepts::base::IsValidConcept<N >= sizeof(T)>
__LL_NODISCARD__ constexpr u8* primitive_to_bytearray(T& value, u8 (&buffer)[N]) noexcept requires(N >= sizeof(T)) {
	return ::llcpp::meta::utils::bits::__bits__::__primitive_to_bytearray(value, buffer);
}

//template<class T, class W = meta::traits::cinput<T>>
//__LL_NODISCARD__ static constexpr void basicType2ascii(ll_char_t*& buffer, W value) noexcept {
//	return _MyType::b2a<T, W>(buffer, value);
//}
//template<class T, class W = meta::traits::cinput<T>>
//__LL_NODISCARD__ static constexpr void primitive2ascii(ll_char_t*& buffer, W value) noexcept {
//	return _MyType::b2a<T, W>(buffer, value);
//}

} // namespace bits
} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_BITS_HPP_
