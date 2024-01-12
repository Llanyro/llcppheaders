/*
*	Singleton.hpp
*
*	Created on: ??? ??, ????
*		Author: llanyro
*/
#ifndef LLCPP_HEADER_SINGLETON_HPP_
#define LLCPP_HEADER_SINGLETON_HPP_

#include "llanytypeslib.hpp"

namespace llcpp {
namespace header {
namespace singleton {

/*
	private:
		#pragma region Singleton
		friend class Singleton<class>;
		class();
		~class();
		#pragma endregion
*/

namespace static_ {

template <class __T>
class Singleton {
	protected:
		Singleton() {}
		~Singleton() {}
	public:
		static __LL_NODISCARD__ __T& getInstance() __LL_EXCEPT__ {
			static __T instance;
			return instance;
		}
};

} // namespace static_

namespace dynamic {

template <class __T>
class Singleton {
	protected:
		Singleton() {}
		~Singleton() {}
		static __T* instance;
	public:
		static __LL_NODISCARD__ __T& getInstance() __LL_EXCEPT__ {
			if (!Singleton<__T>::instance)
				Singleton<__T>::instance = new T();
			return *Singleton<__T>::instance;
		}
		static void freeInstance() noexcept {
			if (Singleton<__T>::instance) {
				delete Singleton<__T>::instance;
				Singleton<__T>::instance = LL_NULLPTR;
			}
		}
};

#pragma region Singleton
template <class __T>
__T* Singleton<__T>::instance = LL_NULLPTR;
#pragma endregion

} // namespace dynamic

} // namespace singleton
} // namespace header
} // namespace llcpp

#endif // !LLCPP_HEADER_SINGLETON_HPP_
