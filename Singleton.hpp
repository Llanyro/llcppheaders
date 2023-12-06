/*
 * Singleton.hpp
 *
 *  Created on: ??? ??, ????
 *      Author: llanyro
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

template <class T>
class Singleton {
	protected:
		Singleton() {}
		~Singleton() {}
	public:
		static __LL_NODISCARD__ T& getInstance() noexcept {
			static T instance;
			return instance;
		}
};

} /* namespace static_ */

namespace dynamic {

template <class T>
class Singleton {
	protected:
		Singleton() {}
		~Singleton() {}
		static T* instance;
	public:
		static __LL_NODISCARD__ T& getInstance() noexcept {
			if (!Singleton<T>::instance)
				Singleton<T>::instance = new T();
			return *Singleton<T>::instance;
		}
		static void freeInstance() noexcept {
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

} /* namespace dynamic */

} /* namespace singleton */
} /* namespace header */
} /* namespace llcpp */

#endif // !LLCPP_HEADER_SINGLETON_HPP_
