/*
 *	Singleton.hpp
 *
 *	Author: Francisco Julio Ruiz Fernandez
 *	Author: llanyro
 *
 *	Version: 4.2
 */

#if defined(LLANYLIB_SINGLETON_HPP_) // Guard && version protector
	#if LLANYLIB_SINGLETON_MAYOR_ != 4 || LLANYLIB_SINGLETON_MINOR_ < 2
		#error "Singleton.hpp version error!"
	#endif // LLANYLIB_SINGLETON_MAYOR_ || LLANYLIB_SINGLETON_MINOR_

#else !defined(LLANYLIB_SINGLETON_HPP_)
#define LLANYLIB_SINGLETON_HPP_
#define LLANYLIB_SINGLETON_MAYOR_ 4
#define LLANYLIB_SINGLETON_MINOR_ 2

#include "definitions.hpp"

namespace llcpp {
namespace singleton {

/*
		#pragma region Singleton
	private:
		friend class Singleton<class>;
		class();
		~class();
	public:
		class(const class& other) __LL_EXCEPT__ = delete;
		class& operator=(const class& other) __LL_EXCEPT__ = delete;
		class(class&& other) __LL_EXCEPT__ = delete;
		class& operator=(class&& other) __LL_EXCEPT__ = delete;
		#pragma endregion
*/

namespace static_ {

template <class T>
class LL_SHARED_LIB Singleton {
	protected:
		Singleton() {}
		~Singleton() {}
	public:
		static T& getInstance() __LL_EXCEPT__ {
			static T instance;
			return instance;
		}
};

} // namespace static_

namespace dynamic {

template <class T>
class LL_SHARED_LIB Singleton {
	protected:
		Singleton() {}
		~Singleton() {}
		static T* instance;
	public:
		static T& getInstance() __LL_EXCEPT__ {
			if (!Singleton<T>::instance)
				Singleton<T>::instance = new T();
			return *Singleton<T>::instance;
		}
		static void freeInstance() __LL_EXCEPT__ {
			if (Singleton<T>::instance) {
				delete Singleton<T>::instance;
				Singleton<T>::instance = LL_NULLPTR;
			}
		}
};

#pragma region Singleton
template <class T>
T* Singleton<T>::instance = LL_NULLPTR;
#pragma endregion

} // namespace dynamic

} // namespace singleton
} // namespace llcpp

#endif // !LLANYLIB_SINGLETON_HPP_
