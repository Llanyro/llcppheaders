//////////////////////////////////////////////
//	Singleton.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.3							//
//////////////////////////////////////////////

#if defined(LLANYLIB_SINGLETON_HPP_) // Guard && version protector
	#if LLANYLIB_SINGLETON_MAYOR_ != 7 || LLANYLIB_SINGLETON_MINOR_ < 3
		#if defined(LL_REAL_CXX23)
			#warning "Singleton.hpp version error!"
		#else
			#error "Singleton.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_SINGLETON_MAYOR_ || LLANYLIB_SINGLETON_MINOR_

#else !defined(LLANYLIB_SINGLETON_HPP_)
#define LLANYLIB_SINGLETON_HPP_
#define LLANYLIB_SINGLETON_MAYOR_ 7
#define LLANYLIB_SINGLETON_MINOR_ 3

#include "traits.hpp"

namespace llcpp {
namespace meta {

/*
		#pragma region Singleton
	public:
		using __Singleton = traits::template_types<Singleton<CLASS>>;
		using __CLASS = traits::template_types<__Singleton::type>;

	private:
		friend class __Singleton::type;
		CLASS() noexcept(false);
		~CLASS() noexcept(false);

	public:
		CLASS(__CLASS::cref) __LL_EXCEPT__ = delete;
		__CLASS::ref operator=(__CLASS::cref) __LL_EXCEPT__ = delete;
		CLASS(__CLASS::move) __LL_EXCEPT__ = delete;
		__CLASS::ref operator=(__CLASS::move) __LL_EXCEPT__ = delete;
		#pragma endregion
*/

template <class T>
class  Singleton {
	public:
		using type = traits::template_types<T>;
		using __Singleton = traits::template_types<Singleton<T>>;
	protected:
		constexpr Singleton() __LL_EXCEPT__ {}
	public:
		constexpr ~Singleton() __LL_EXCEPT__ {}

		Singleton(__Singleton::cref) __LL_EXCEPT__ = delete;
		__Singleton::ref operator=(__Singleton::cref) __LL_EXCEPT__ = delete;
		Singleton(__Singleton::move) __LL_EXCEPT__ = delete;
		__Singleton::ref operator=(__Singleton::move) __LL_EXCEPT__ = delete;

		constexpr operator typename __Singleton::cref() const __LL_EXCEPT__ = delete;
		constexpr operator typename __Singleton::ref() __LL_EXCEPT__ = delete;

		// [TOCHECK]
		template <class... Args>
		__LL_NODISCARD__ static type::ref getInstance(Args&&... args) noexcept(LL_FALSE) {
			if constexpr (traits::parameter_pack_operations<Args...>::empty) {
				static T instance;
				return instance;
			}
			else {
				static T instance(std::forward<Args>(args)...);
				return instance;
			}
		}
};

// [TODO] Needs to be with a given allocator and a subscriber
//template <class T>
//class  Singleton {
//	public:
//		using type = traits::template_types<T>;
//		using __Singleton = traits::template_types<Singleton<T>>;
//	private:
//		static T* instance;
//	protected:
//		constexpr Singleton() __LL_EXCEPT__ {}
//	public:
//		constexpr ~Singleton() __LL_EXCEPT__ {}
//
//		Singleton(__Singleton::cref) __LL_EXCEPT__ = delete;
//		__Singleton::ref operator=(__Singleton::cref) __LL_EXCEPT__ = delete;
//		Singleton(__Singleton::move) __LL_EXCEPT__ = delete;
//		__Singleton::ref operator=(__Singleton::move) __LL_EXCEPT__ = delete;
//
//		constexpr operator typename __Singleton::cref() const __LL_EXCEPT__ = delete;
//		constexpr operator typename __Singleton::ref() __LL_EXCEPT__ = delete;
//
//		template <class... Args>
//		static type::ref getInstance(Args&&... args) noexcept(LL_FALSE) {
//			if (!Singleton<T>::instance) {
//				if constexpr (traits::pack_has_args<Args...>)
//					Singleton<T>::instance = new T(std::forward<Args>(args)...));
//				else Singleton<T>::instance = new T();
//			}
//			return *Singleton<T>::instance;
//		}
//		static void freeInstance() noexcept(std::is_nothrow_destructible_v<T>) {
//			if (Singleton<T>::instance) {
//				delete Singleton<T>::instance;
//				Singleton<T>::instance = LL_NULLPTR;
//			}
//		}
//};
//
//#pragma region Singleton
//template <class T>
//T* Singleton<T>::instance = LL_NULLPTR;
//#pragma endregion

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_SINGLETON_HPP_
