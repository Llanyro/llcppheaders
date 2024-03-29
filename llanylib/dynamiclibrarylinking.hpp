/*
 *	dynamiclibrarylinking.hpp
 *
 *	Author: Francisco Julio Ruiz Fernandez
 *	Author: llanyro
 *
 *	Version: 4.2
 */

#if defined(LLANYLIB_DYNAMICLIBRARYLINKING_HPP_) // Guard && version protector
	#if LLANYLIB_DYNAMICLIBRARYLINKING_MAYOR_ != 4 || LLANYLIB_DYNAMICLIBRARYLINKING_MINOR_ < 2
		#error "dynamiclibrarylinking.hpp version error!"
	#endif // LLANYLIB_DYNAMICLIBRARYLINKING_MAYOR_ || LLANYLIB_DYNAMICLIBRARYLINKING_MINOR_

#else !defined(LLANYLIB_DYNAMICLIBRARYLINKING_HPP_)
#define LLANYLIB_DYNAMICLIBRARYLINKING_HPP_
#define LLANYLIB_DYNAMICLIBRARYLINKING_MAYOR_ 4
#define LLANYLIB_DYNAMICLIBRARYLINKING_MINOR_ 2

#include "definitions.hpp"

#if defined(WINDOWS_SYSTEM)
#include <Windows.h>

#define load_lib(file) LoadLibraryA(file)
#define get_lib_address(handle, funcName) GetProcAddress(reinterpret_cast<HMODULE>(handle), funcName)
#define close_lib(handle) FreeLibrary(reinterpret_cast<HMODULE>(handle))

inline const char* dlerror() { return ""; }

#elif defined(POSIX_SYSTEM) || defined(UNIX_SYSTEM)
#include <dlfcn.h>

#define load_lib(file) dlopen(file, RTLD_LAZY)
#define get_lib_address(handle, funcName) dlsym(handle, funcName)
#define close_lib(handle) dlclose(handle)

#else 
#define load_lib(file)
#define get_lib_address(handle, funcName)
#define close_lib(handle)

#endif	// WINDOWS_SYSTEM || POSIX_SYSTEM) || UNIX_SYSTEM

using ll_lib_t = void*;

namespace llcpp {
namespace dll {

inline ll_lib_t loadLibrary() {

}

} // namespace dll
} // namespace llcpp

#endif // !LLANYLIB_DYNAMICLIBRARYLINKING_HPP_
