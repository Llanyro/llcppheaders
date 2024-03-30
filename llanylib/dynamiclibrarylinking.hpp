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
#include "types.hpp"

#if defined(WINDOWS_SYSTEM)
#include <Windows.h>

#define load_lib(file) LoadLibraryA(file)
#define get_lib_address(handle, funcName) GetProcAddress(reinterpret_cast<HMODULE>(handle), funcName)
#define close_lib(handle) FreeLibrary(reinterpret_cast<HMODULE>(handle))

//inline const char* dlerror() { return ""; }

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

#include <string>

namespace llcpp {
namespace dll {

inline ll_lib_t loadLibrary(const std::string& libraryName) {
	return load_lib(libraryName.c_str());
}
inline ll_lib_t loadLibrary(ll_string_t libraryName) {
	return load_lib(libraryName);
}
inline ll_lib_t loadLibrary(const std::string_view& libraryName) {
	return load_lib(libraryName.data());
}

inline ll_lib_t getLibraryFunction(ll_lib_t libraryHandle, const std::string& libraryFunctionName) {
	return get_lib_address(libraryHandle, libraryFunctionName.c_str());
}
inline ll_lib_t getLibraryFunction(ll_lib_t libraryHandle, ll_string_t libraryFunctionName) {
	return get_lib_address(libraryHandle, libraryFunctionName);
}
inline ll_lib_t getLibraryFunction(ll_lib_t libraryHandle, const std::string_view& libraryFunctionName) {
	return get_lib_address(libraryHandle, libraryFunctionName.data());
}

inline void closeLibrary(ll_lib_t libraryHandle) {
	close_lib(libraryHandle);
}
inline void closeLibrary(ll_lib_t libraryHandle) {
	close_lib(libraryHandle);
}
inline void closeLibrary(ll_lib_t libraryHandle) {
	close_lib(libraryHandle);
}

class DllHandle {
	protected:
		ll_lib_t handle;
	protected:
		void simpleClear() __LL_EXCEPT__ {
			this->handle = LL_NULLPTR;
		}
	public:
		DllHandle() __LL_EXCEPT__ = delete;

		DllHandle(ll_lib_t handle) __LL_EXCEPT__
			: handle(handle) {}
		DllHandle(ll_string_t libraryName) __LL_EXCEPT__
			: handle(loadLibrary(libraryName)) {}
		DllHandle(const std::string& libraryName) __LL_EXCEPT__
			: DllHandle(libraryName.c_str()) {}
		DllHandle(const std::string_view& libraryName) __LL_EXCEPT__
			: DllHandle(libraryName.data()) {}
		~DllHandle() __LL_EXCEPT__ { this->clear(); }

		DllHandle(const DllHandle&) __LL_EXCEPT__ = delete;
		DllHandle& operator=(const DllHandle&) __LL_EXCEPT__ = delete;

		DllHandle(DllHandle&& other) __LL_EXCEPT__
			: handle(other.handle) { other.simpleClear(); }
		DllHandle& operator=(DllHandle&& other) __LL_EXCEPT__ {
			this->clear();
			this->handle = other.handle;
			other.simpleClear();
			return *this;
		}


		#pragma region GetFunctionSafe
		__LL_NODISCARD__ void* getFunction_s(ll_string_t libraryFunctionName) __LL_EXCEPT__ {
			return (this->isValid()) ? getLibraryFunction(this->handle, libraryFunctionName) : LL_NULLPTR;
		}
		__LL_NODISCARD__ void* getFunction_s(const std::string& libraryFunctionName) __LL_EXCEPT__ {
			return this->getFunction_s(libraryFunctionName.c_str());
		}
		__LL_NODISCARD__ void* getFunction_s(const std::string_view& libraryFunctionName) __LL_EXCEPT__ {
			return this->getFunction_s(libraryFunctionName.data());
		}

		#pragma endregion
		#pragma region GetFunctionUnsafe
		__LL_NODISCARD__ void* getFunction(const std::string& libraryFunctionName) __LL_EXCEPT__ {
			return getLibraryFunction(this->handle, libraryFunctionName);
		}
		__LL_NODISCARD__ void* getFunction(ll_string_t libraryFunctionName) __LL_EXCEPT__ {
			return getLibraryFunction(this->handle, libraryFunctionName);
		}
		__LL_NODISCARD__ void* getFunction(const std::string_view& libraryFunctionName) __LL_EXCEPT__ {
			return getLibraryFunction(this->handle, libraryFunctionName);
		}

		#pragma endregion
		#pragma region GetTemplateSafe

		template<class T>
		__LL_NODISCARD__ T getFunction_s(const std::string& libraryFunctionName) __LL_EXCEPT__ {
			return reinterpret_cast<T>(this->getFunction_s(libraryFunctionName));
		}
		template<class T>
		__LL_NODISCARD__ T getFunction_s(ll_string_t libraryFunctionName) __LL_EXCEPT__ {
			return reinterpret_cast<T>(this->getFunction_s(libraryFunctionName));
		}
		template<class T>
		__LL_NODISCARD__ T getFunction_s(const std::string_view& libraryFunctionName) __LL_EXCEPT__ {
			return reinterpret_cast<T>(this->getFunction_s(libraryFunctionName));
		}

		#pragma endregion
		#pragma region GetTemplateUnsafe

		template<class T>
		__LL_NODISCARD__ T getFunction(const std::string& libraryFunctionName) __LL_EXCEPT__ {
			return reinterpret_cast<T>(this->getFunction(libraryFunctionName));
		}
		template<class T>
		__LL_NODISCARD__ T getFunction(ll_string_t libraryFunctionName) __LL_EXCEPT__ {
			return reinterpret_cast<T>(this->getFunction(libraryFunctionName));
		}
		template<class T>
		__LL_NODISCARD__ T getFunction(const std::string_view& libraryFunctionName) __LL_EXCEPT__ {
			return reinterpret_cast<T>(this->getFunction(libraryFunctionName));
		}

		#pragma endregion

		void clear() __LL_EXCEPT__ {
			if(this->handle) {
				closeLibrary(this->handle);
				this->handle = LL_NULLPTR;
			}
		}

		__LL_NODISCARD__ ll_bool_t isValid() const __LL_EXCEPT__ {
			return this->handle != LL_NULLPTR;
		}
};

} // namespace dll
} // namespace llcpp

#endif // !LLANYLIB_DYNAMICLIBRARYLINKING_HPP_
