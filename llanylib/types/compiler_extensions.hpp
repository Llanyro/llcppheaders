//////////////////////////////////////////////
//	compiler_extensions.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_COMPILEREXTENSIONS_HPP_) // Guard && version protector
	#if LLANYLIB_COMPILEREXTENSIONS_MAYOR_ != 12 || LLANYLIB_COMPILEREXTENSIONS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "compiler_extensions.hpp version error!"
		#else
			#error "compiler_extensions.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_COMPILEREXTENSIONS_MAYOR_ || LLANYLIB_COMPILEREXTENSIONS_MINOR_

#elif !defined(LLANYLIB_COMPILEREXTENSIONS_HPP_)
	#define LLANYLIB_COMPILEREXTENSIONS_HPP_
	#define LLANYLIB_COMPILEREXTENSIONS_MAYOR_ 12
	#define LLANYLIB_COMPILEREXTENSIONS_MINOR_ 0

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/types.hpp>
#else
	#include "types.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {

template<class T>
__LL_NODISCARD__ constexpr T* addressof(T& _Val) noexcept {
	if constexpr (::llcpp::LL_OS_SYSTEM == ::llcpp::OSEnum::Windows)
	    return __builtin_addressof(_Val);
	else {
		static_assert(::llcpp::LL_OS_SYSTEM == ::llcpp::OSEnum::Windows,
			"addressof is not defined for this system");
		return ::llcpp::NULL_VALUE<T>;
	}
}

template<class T>
__LL_NODISCARD__ const T* addressof(const T&&) noexcept = delete;

} // namespace llcpp

#endif // LLANYLIB_COMPILEREXTENSIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
