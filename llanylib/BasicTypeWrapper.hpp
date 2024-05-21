//////////////////////////////////////////////
//	BasicTypeWrapper.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_BASICTYPEWRAPPER_HPP_) // Guard && version protector
	#if LLANYLIB_BASICTYPEWRAPPER_MAYOR_ != 5 || LLANYLIB_BASICTYPEWRAPPER_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "BasicTypeWrapper.hpp version error!"
		#else
			#error "BasicTypeWrapper.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_BASICTYPEWRAPPER_MAYOR_ || LLANYLIB_BASICTYPEWRAPPER_MINOR_

#else !defined(LLANYLIB_BASICTYPEWRAPPERHPP_)
#define LLANYLIB_BASICTYPEWRAPPER_HPP_
#define LLANYLIB_BASICTYPEWRAPPER_MAYOR_ 5
#define LLANYLIB_BASICTYPEWRAPPER_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace meta {

template<class T>
class BasicTypeWrapper {
	public:
		static_assert(traits::is_basic_type_v<T>, "Type must be integral!");
		using type = traits::template_types<T>;
		using __BasicTypeWrapper = traits::template_types<BasicTypeWrapper<T>>;
	public:
		T value;
	public:
		constexpr BasicTypeWrapper() __LL_EXCEPT__ : value(ZERO_UI64) {}
		constexpr BasicTypeWrapper(type::cinput value) __LL_EXCEPT__ : value(value) {}
		constexpr ~BasicTypeWrapper() __LL_EXCEPT__ {}

		constexpr BasicTypeWrapper(__BasicTypeWrapper::cref other) __LL_EXCEPT__ : value(other.value) {}
		constexpr __BasicTypeWrapper::ref operator=(__BasicTypeWrapper::cref other) __LL_EXCEPT__ {
			this->value = other.value;
			return *this;
		}

		constexpr BasicTypeWrapper(__BasicTypeWrapper::move) __LL_EXCEPT__ = delete;
		constexpr __BasicTypeWrapper::ref operator=(__BasicTypeWrapper::move) __LL_EXCEPT__ = delete;

		constexpr void clear() __LL_EXCEPT__ { this->value = ZERO_I32; }

		constexpr void convertToChars(ll_char_t* mem) const __LL_EXCEPT__ {
			if constexpr (std::_Is_any_of_v<typename type::type, i8, ui8>)
				*mem = value;
			else if constexpr (std::_Is_any_of_v<typename type::type, i16, ui16>) {
				*mem++ = (value >> 8) & 0xFF;
				*mem = value & 0xFF;
			}
			else if constexpr (std::_Is_any_of_v<typename type::type, i32, ui32>) {
				*mem++ = (value >> 24) & 0xFF;
				*mem++ = (value >> 16) & 0xFF;
				*mem++ = (value >> 8) & 0xFF;
				*mem = value & 0xFF;
			}
			else if constexpr (std::_Is_any_of_v<typename type::type, i32, ui32>) {
				*mem++ = (value >> 56) & 0xFF;
				*mem++ = (value >> 48) & 0xFF;
				*mem++ = (value >> 40) & 0xFF;
				*mem++ = (value >> 32) & 0xFF;
				*mem++ = (value >> 24) & 0xFF;
				*mem++ = (value >> 16) & 0xFF;
				*mem++ = (value >> 8) & 0xFF;
				*mem = value & 0xFF;
			}
		}
};

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_BASICTYPEWRAPPER_HPP_
