//////////////////////////////////////////////
//	dynamiclibrarylinking.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DYNAMICLIBRARYLINKING_HPP_) // Guard && version protector
	#if LLANYLIB_DYNAMICLIBRARYLINKING_MAYOR_ != 5 || LLANYLIB_DYNAMICLIBRARYLINKING_MINOR_ < 0
		#error "dynamiclibrarylinking.hpp version error!"
	#endif // LLANYLIB_DYNAMICLIBRARYLINKING_MAYOR_ || LLANYLIB_DYNAMICLIBRARYLINKING_MINOR_

#else !defined(LLANYLIB_DYNAMICLIBRARYLINKING_HPP_)
#define LLANYLIB_DYNAMICLIBRARYLINKING_HPP_
#define LLANYLIB_DYNAMICLIBRARYLINKING_MAYOR_ 5
#define LLANYLIB_DYNAMICLIBRARYLINKING_MINOR_ 0

#include "StringView.hpp"

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

class LL_SHARED_LIB DllHandle {
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

		template<ll_bool_t SAFE_MODE>
		__LL_NODISCARD__ void* getFunction(ll_string_t libraryFunctionName) __LL_EXCEPT__ {
			if constexpr (SAFE_MODE)
				return (this->isValid()) ? getLibraryFunction(this->handle, libraryFunctionName) : LL_NULLPTR;
			else return getLibraryFunction(this->handle, libraryFunctionName);
		}
		template<ll_bool_t SAFE_MODE>
		__LL_NODISCARD__ void* getFunction(const std::string& libraryFunctionName) __LL_EXCEPT__ {
			return this->getFunction<SAFE_MODE>(libraryFunctionName.c_str());
		}
		template<ll_bool_t SAFE_MODE>
		__LL_NODISCARD__ void* getFunction(const std::string_view& libraryFunctionName) __LL_EXCEPT__ {
			return this->getFunction<SAFE_MODE>(libraryFunctionName.data());
		}

		template<class T, ll_bool_t SAFE_MODE>
		__LL_NODISCARD__ T getFunction(ll_string_t libraryFunctionName) __LL_EXCEPT__ {
			//static_assert(std::is_function_v<T>, "Template type can only be a function");
			return reinterpret_cast<T>(this->getFunction<SAFE_MODE>(libraryFunctionName));
		}
		template<class T, ll_bool_t SAFE_MODE>
		__LL_NODISCARD__ T getFunction(const std::string& libraryFunctionName) __LL_EXCEPT__ {
			return this->getFunction<T, SAFE_MODE>(libraryFunctionName.c_str());
		}
		template<class T, ll_bool_t SAFE_MODE>
		__LL_NODISCARD__ T getFunction(const std::string_view& libraryFunctionName) __LL_EXCEPT__ {
			return this->getFunction<T, SAFE_MODE>(libraryFunctionName.data());
		}

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
