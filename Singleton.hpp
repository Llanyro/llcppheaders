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
	#pragma region Singleton
	private:
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
		static T* getInstance() {
			static T instance;
			return &instance;
		}
};

} /* namespace static_ */

namespace dynamic {

template <class T>
class Singleton {
	protected:
		Singleton() {}
		~Singleton() {}
		static T* instancia;
	public:
		static T* getInstance() {
			if (Singleton<T>::instancia == LL_NULLPTR)
				Singleton<T>::instancia = new T();
			return Singleton<T>::instancia;
		}
		static void freeInstance() {
			if (Singleton<T>::instancia != LL_NULLPTR) {
				delete Singleton<T>::instancia;
				Singleton<T>::instancia = LL_NULLPTR;
			}
		}
		virtual ll_bool_t clear() { return LL_FALSE; };
};

#pragma region Singleton
template <class T>
T* Singleton<T>::instancia = LL_NULLPTR;
#pragma endregion

} /* namespace dynamic */

} /* namespace singleton */
} /* namespace header */
} /* namespace llcpp */

#endif // !LLCPP_HEADER_SINGLETON_HPP_
