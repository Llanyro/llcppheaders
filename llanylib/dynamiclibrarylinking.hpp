//////////////////////////////////////////////
//	dynamiclibrarylinking.hpp				//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DYNAMICLIBRARYLINKING_HPP_) // Guard && version protector
	#if LLANYLIB_DYNAMICLIBRARYLINKING_MAYOR_ != 9 || LLANYLIB_DYNAMICLIBRARYLINKING_MINOR_ < 0
		#error "dynamiclibrarylinking.hpp version error!"
	#endif // LLANYLIB_DYNAMICLIBRARYLINKING_MAYOR_ || LLANYLIB_DYNAMICLIBRARYLINKING_MINOR_

#else !defined(LLANYLIB_DYNAMICLIBRARYLINKING_HPP_)
#define LLANYLIB_DYNAMICLIBRARYLINKING_HPP_
#define LLANYLIB_DYNAMICLIBRARYLINKING_MAYOR_ 9
#define LLANYLIB_DYNAMICLIBRARYLINKING_MINOR_ 0

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

class DllHandle {
	protected:
		ll_lib_t handle;
	protected:
		void simpleClear() noexcept {
			this->handle = LL_NULLPTR;
		}
	public:
		ll_lib_t getHandle() { return this->handle; }

		DllHandle() noexcept = delete;

		DllHandle(ll_lib_t handle) noexcept
			: handle(handle) {}
		DllHandle(ll_string_t libraryName) noexcept
			: handle(loadLibrary(libraryName)) {}
		DllHandle(const std::string& libraryName) noexcept
			: DllHandle(libraryName.c_str()) {}
		DllHandle(const std::string_view& libraryName) noexcept
			: DllHandle(libraryName.data()) {}
		~DllHandle() noexcept { this->clear(); }

		DllHandle(const DllHandle&) noexcept = delete;
		DllHandle& operator=(const DllHandle&) noexcept = delete;

		DllHandle(DllHandle&& other) noexcept
			: handle(other.handle) { other.DllHandle::simpleClear(); }
		DllHandle& operator=(DllHandle&& other) noexcept {
			this->clear();
			this->handle = other.handle;
			other.DllHandle::simpleClear();
			return *this;
		}

		template<ll_bool_t SAFE_MODE = llcpp::FALSE>
		__LL_NODISCARD__ void* getFunction(ll_string_t libraryFunctionName) noexcept {
			if constexpr (SAFE_MODE)
				return (this->isValid()) ? getLibraryFunction(this->handle, libraryFunctionName) : LL_NULLPTR;
			else return getLibraryFunction(this->handle, libraryFunctionName);
		}
		template<ll_bool_t SAFE_MODE = llcpp::FALSE>
		__LL_NODISCARD__ void* getFunction(const std::string& libraryFunctionName) noexcept {
			return this->getFunction<SAFE_MODE>(libraryFunctionName.c_str());
		}
		template<ll_bool_t SAFE_MODE = llcpp::FALSE>
		__LL_NODISCARD__ void* getFunction(const std::string_view& libraryFunctionName) noexcept {
			return this->getFunction<SAFE_MODE>(libraryFunctionName.data());
		}
		template<ll_bool_t SAFE_MODE = llcpp::FALSE>
		__LL_NODISCARD__ void* getFunction(const len_t mem_position) noexcept {
			if constexpr (SAFE_MODE)
				return (this->isValid()) ? (reinterpret_cast<ll_char_t*>(this->handle) + mem_position) : LL_NULLPTR;
			else return reinterpret_cast<ll_char_t*>(this->handle) + mem_position;
		}


		template<class T, ll_bool_t SAFE_MODE = llcpp::FALSE>
		__LL_NODISCARD__ T getFunction(ll_string_t libraryFunctionName) noexcept {
			//static_assert(std::is_function_v<T>, "Template type can only be a function");
			return reinterpret_cast<T>(this->getFunction<SAFE_MODE>(libraryFunctionName));
		}
		template<class T, ll_bool_t SAFE_MODE = llcpp::FALSE>
		__LL_NODISCARD__ T getFunction(const std::string& libraryFunctionName) noexcept {
			return this->getFunction<T, SAFE_MODE>(libraryFunctionName.c_str());
		}
		template<class T, ll_bool_t SAFE_MODE = llcpp::FALSE>
		__LL_NODISCARD__ T getFunction(const std::string_view& libraryFunctionName) noexcept {
			return this->getFunction<T, SAFE_MODE>(libraryFunctionName.data());
		}
		template<class T, ll_bool_t SAFE_MODE = llcpp::FALSE>
		__LL_NODISCARD__ T getFunction(const len_t mem_position) noexcept {
			return reinterpret_cast<T>(this->getFunction<SAFE_MODE>(mem_position));
		}


		void clear() noexcept {
			if(this->handle) {
				closeLibrary(this->handle);
				this->handle = LL_NULLPTR;
			}
		}

		__LL_NODISCARD__ ll_bool_t isValid() const noexcept {
			return this->handle != LL_NULLPTR;
		}
};

} // namespace dll
} // namespace llcpp

#endif // !LLANYLIB_DYNAMICLIBRARYLINKING_HPP_
