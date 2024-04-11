/*
 *	RAIIWrapper.hpp
 *
 *	Author: Francisco Julio Ruiz Fernandez
 *	Author: llanyro
 *
 *	Version: 4.2
 */

#if defined(LLANYLIB_RAIIWRAPPER_HPP_) // Guard && version protector
	#if LLANYLIB_RAIIWRAPPER_MAYOR_ != 4 || LLANYLIB_RAIIWRAPPER_MINOR_ < 2
		#error "RAIIWrapper.hpp version error!"
	#endif // LLANYLIB_RAIIWRAPPER_MAYOR_ || LLANYLIB_RAIIWRAPPER_MINOR_

#else !defined(LLANYLIB_RAIIWRAPPER_HPP_)
#define LLANYLIB_RAIIWRAPPER_HPP_
#define LLANYLIB_RAIIWRAPPER_MAYOR_ 4
#define LLANYLIB_RAIIWRAPPER_MINOR_ 2

#include "RAIIBase.hpp"

namespace llcpp {
namespace raii {

template<class OnGenerateData>
class LL_SHARED_LIB RAIIWrapperCreation {
	private:
		using __internal__OnGenerateObject__ = RAIIContainer<OnGenerateData, void>;
	public:
		using __DoOnGenerate = void(*)(std::add_lvalue_reference_t<OnGenerateData>);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__OnGenerateObject__, OnGenerateObject);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(RAIIWrapperCreation<OnGenerateData>, RAIIWrapperCreation);
	private:
		__OnGenerateObject onGenerateObject;
	public:
		#pragma region Deleted
		constexpr RAIIWrapperCreation() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region Constructor
		constexpr RAIIWrapperCreation(__cref_OnGenerateObject onGenerateObject) __LL_EXCEPT__
			: onGenerateObject(onGenerateObject) { this->recallOnGenerate(); }
		constexpr RAIIWrapperCreation(__move_OnGenerateObject onGenerateObject) __LL_EXCEPT__
			: onGenerateObject(std::move(onGenerateObject)) { this->recallOnGenerate(); }
		constexpr ~RAIIWrapperCreation() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region Rule5
		constexpr RAIIWrapperCreation(__cref_RAIIWrapperCreation other) __LL_EXCEPT__
			: onGenerateObject(other.onGenerateObject) {}
		constexpr __ref_RAIIWrapperCreation operator=(__cref_RAIIWrapperCreation other) __LL_EXCEPT__ {
			this->onGenerateObject = other.onGenerateObject;
			return *this;
		}

		constexpr RAIIWrapperCreation(__move_RAIIWrapperCreation other) __LL_EXCEPT__
			: onGenerateObject(std::move(other.onGenerateObject)) { other.clear(); }
		constexpr __ref_RAIIWrapperCreation operator=(__move_RAIIWrapperCreation other) __LL_EXCEPT__ {
			this->onGenerateObject = std::move(onGenerateObject);
			other.clear();
			return *this;
		}

		#pragma endregion
		#pragma region Functions
		constexpr void recallOnGenerate() __LL_EXCEPT__ {
			if(this->onGenerateObject)
				this->onGenerateObject();
		}
		constexpr void clear() __LL_EXCEPT__ {
			this->onGenerateObject = LL_NULLPTR;
		}
		constexpr void setOnGenerate(__cref_OnGenerateObject onGenerateObject) __LL_EXCEPT__ {
			this->onGenerateObject = onGenerateObject;
		}
		constexpr void setOnGenerate(__move_OnGenerateObject onGenerateObject) __LL_EXCEPT__ {
			this->onGenerateObject = std::move(onGenerateObject);
		}

		#pragma endregion
};

template<class OnDestructionData>
class LL_SHARED_LIB RAIIWrapperDestruction {
	private:
		using __internal__OnDestructionObject__ = RAIIContainer<OnDestructionData, void>;
	public:
		using __DoOnDestruction = void(*)(std::add_lvalue_reference_t<OnDestructionData>);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__OnDestructionObject__, OnDestructionObject);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(RAIIWrapperDestruction<OnDestructionData>, RAIIWrapperDestruction);
	private:
		__OnDestructionObject onDestructionObject;
	public:
		#pragma region Deleted
		constexpr RAIIWrapperDestruction() __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region Constructor
		constexpr RAIIWrapperDestruction(__cref_OnDestructionObject onDestructionObject) __LL_EXCEPT__
			: onDestructionObject(onDestructionObject) {}
		constexpr RAIIWrapperDestruction(__move_OnDestructionObject onDestructionObject) __LL_EXCEPT__
			: onDestructionObject(std::move(onDestructionObject)) {}
		constexpr ~RAIIWrapperDestruction() __LL_EXCEPT__ { this->recallOnDestruction(); }

		#pragma endregion
		#pragma region Rule5
		constexpr RAIIWrapperDestruction(__cref_RAIIWrapperDestruction other) __LL_EXCEPT__
			: onDestructionObject(other.onDestructionObject) {}
		constexpr __ref_RAIIWrapperDestruction operator=(__cref_RAIIWrapperDestruction other) __LL_EXCEPT__ {
			this->onDestructionObject = other.onDestructionObject;
			return *this;
		}

		constexpr RAIIWrapperDestruction(__move_RAIIWrapperDestruction other) __LL_EXCEPT__
			: onDestructionObject(std::move(other.onDestructionObject)) { other.clear(); }
		constexpr __ref_RAIIWrapperDestruction operator=(__move_RAIIWrapperDestruction other) __LL_EXCEPT__ {
			this->onDestructionObject = std::move(onDestructionObject);
			other.clear();
			return *this;
		}

		#pragma endregion
		#pragma region Functions
		constexpr void recallOnDestruction() __LL_EXCEPT__ {
			if (this->onDestructionObject)
				this->onDestructionObject();
		}
		constexpr void clear() __LL_EXCEPT__ {
			this->onDestructionObject = LL_NULLPTR;
		}
		constexpr void setOnDestruction(__cref_OnDestructionObject onDestructionObject) __LL_EXCEPT__ {
			this->onDestructionObject = onDestructionObject;
		}
		constexpr void setOnDestruction(__move_OnDestructionObject onDestructionObject) __LL_EXCEPT__ {
			this->onDestructionObject = std::move(onDestructionObject);
		}

		#pragma endregion
};

template<class OnGenerateData, class OnDestructionData>
class LL_SHARED_LIB RAIIWrapper : public RAIIWrapperCreation<OnGenerateData>, public RAIIWrapperDestruction<OnDestructionData> {
	protected:
		using __internal__RAIIWrapper__ = RAIIWrapper<OnGenerateData, OnDestructionData>;
	public:
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(RAIIWrapperCreation<OnGenerateData>, RAIIWrapperCreation);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(RAIIWrapperDestruction<OnDestructionData>, RAIIWrapperDestruction);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__RAIIWrapper__, RAIIWrapper);
	public:

		#pragma region Deleted
		constexpr RAIIWrapper() __LL_EXCEPT__ = delete;
		constexpr RAIIWrapper(__cref_RAIIWrapperCreation) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapper operator=(__cref_RAIIWrapperCreation) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapper(__move_RAIIWrapperCreation) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapper operator=(__move_RAIIWrapperCreation) __LL_EXCEPT__ = delete;

		constexpr RAIIWrapper(__cref_RAIIWrapperDestruction) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapper operator=(__cref_RAIIWrapperDestruction) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapper(__move_RAIIWrapperDestruction) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapper operator=(__move_RAIIWrapperDestruction) __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region Constructor
		constexpr RAIIWrapper(
			__RAIIWrapperCreation::__cref_OnGenerateObject onGenerate,
			__RAIIWrapperDestruction::__cref_OnDestructionObject onDestruction
		) __LL_EXCEPT__
			: __RAIIWrapperCreation(onGenerate)
			, __RAIIWrapperDestruction(onDestruction)
		{}
		constexpr RAIIWrapper(
			__RAIIWrapperCreation::__move_OnGenerateObject onGenerate,
			__RAIIWrapperDestruction::__move_OnDestructionObject onDestruction
		) __LL_EXCEPT__
			: __RAIIWrapperCreation(std::move(onGenerate))
			, __RAIIWrapperDestruction(std::move(onDestruction))
		{}
		constexpr ~RAIIWrapper() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region Rule5
		constexpr RAIIWrapper(__cref_RAIIWrapper other) __LL_EXCEPT__
			: __RAIIWrapperCreation(other), __RAIIWrapperDestruction(other) {}
		constexpr __ref_RAIIWrapper operator=(__cref_RAIIWrapper other) __LL_EXCEPT__ {
			__RAIIWrapperCreation::operator=(other);
			__RAIIWrapperDestruction::operator=(other);
			return *this;
		}

		constexpr RAIIWrapper(__move_RAIIWrapper other) __LL_EXCEPT__
			: __RAIIWrapperCreation(std::move(other))
			, __RAIIWrapperDestruction(std::move(other))
		{}
		constexpr __ref_RAIIWrapper operator=(__move_RAIIWrapper other) __LL_EXCEPT__ {
			__RAIIWrapperCreation::operator=(std::move(other));
			__RAIIWrapperDestruction::operator=(std::move(other));
			return *this;
		}

		#pragma endregion
		#pragma region Functions
		constexpr void clear() __LL_EXCEPT__ {
			__RAIIWrapperCreation::clear();
			__RAIIWrapperDestruction::clear();
		}

		#pragma endregion
};

template<class OnGenerateData, class OnDestructionData, class ActionInput, class ActionOutput = void>
class LL_SHARED_LIB RAIIWrapperExtra : public RAIIWrapper<OnGenerateData, OnDestructionData> {
	protected:
		using __internal__OnActionObject__ = RAIIContainer<ActionInput, ActionOutput>;
		using __internal__RAIIWrapper__ = RAIIWrapper<OnGenerateData, OnDestructionData>;
		using __internal__RAIIWrapperExtra__ = RAIIWrapperExtra<OnGenerateData, OnDestructionData, ActionInput, ActionOutput>;
	public:
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__OnActionObject__, OnActionObject);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__RAIIWrapper__, RAIIWrapper);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__RAIIWrapperExtra__, RAIIWrapperExtra);
	private:
		__OnActionObject onActionObject;
	public:
		#pragma region Deleted
		constexpr RAIIWrapperExtra() __LL_EXCEPT__ = delete;
		constexpr RAIIWrapperExtra(__RAIIWrapper::__cref_RAIIWrapperCreation) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapperExtra operator=(__RAIIWrapper::__cref_RAIIWrapperCreation) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapperExtra(__RAIIWrapper::__move_RAIIWrapperCreation) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapperExtra operator=(__RAIIWrapper::__move_RAIIWrapperCreation) __LL_EXCEPT__ = delete;

		constexpr RAIIWrapperExtra(__RAIIWrapper::__cref_RAIIWrapperDestruction) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapperExtra operator=(__RAIIWrapper::__cref_RAIIWrapperDestruction) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapperExtra(__RAIIWrapper::__move_RAIIWrapperDestruction) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapperExtra operator=(__RAIIWrapper::__move_RAIIWrapperDestruction) __LL_EXCEPT__ = delete;

		constexpr RAIIWrapperExtra(__cref_RAIIWrapper) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapperExtra operator=(__cref_RAIIWrapper) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapperExtra(__move_RAIIWrapper) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapperExtra operator=(__move_RAIIWrapper) __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region Constructor
		constexpr RAIIWrapperExtra(
			__RAIIWrapper::__cref_OnGenerateObject onGenerate,
			__RAIIWrapper::__cref_OnDestructionObject onDestruction,
			__cref_OnActionObject onActionObject
		) __LL_EXCEPT__
			: __RAIIWrapper(onGenerate, onDestruction)
			, onActionObject(onActionObject)
		{}
		constexpr RAIIWrapperExtra(
			__RAIIWrapper::__move_OnGenerateObject onGenerate,
			__RAIIWrapper::__move_OnDestructionObject onDestruction,
			__move_OnActionObject onActionObject
		) __LL_EXCEPT__
			: __RAIIWrapper(std::move(onGenerate), std::move(onDestruction))
			, onActionObject(std::move(onActionObject))
		{}
		constexpr ~RAIIWrapperExtra() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region Rule5
		constexpr RAIIWrapperExtra(__cref_RAIIWrapperExtra other) __LL_EXCEPT__
			: __RAIIWrapper(other), onActionObject(other.onActionObject) {}
		constexpr __ref_RAIIWrapperExtra operator=(__cref_RAIIWrapperExtra other) __LL_EXCEPT__ {
			__RAIIWrapper::operator=(other);
			this->onActionObject = other.onActionObject;
			return *this;
		}
		constexpr RAIIWrapperExtra(__move_RAIIWrapperExtra other) __LL_EXCEPT__
			: __RAIIWrapper(std::move(other)), onActionObject(std::move(other.onActionObject)) {}
		constexpr __ref_RAIIWrapperExtra operator=(__move_RAIIWrapperExtra other) __LL_EXCEPT__ {
			__RAIIWrapper::operator=(std::move(other));
			this->onActionObject = std::move(other.onActionObject);
			return *this;
		}

		#pragma endregion
		#pragma region Functions
		constexpr void callOnAction() const __LL_EXCEPT__ {
			if (this->onActionObject)
				this->onActionObject();
		}
		constexpr void clear() __LL_EXCEPT__ {
			__RAIIWrapper::clear();
			this->onActionObject = LL_NULLPTR;
		}
		constexpr void setOnAction(__cref_OnActionObject onActionObject) __LL_EXCEPT__ {
			this->onActionObject = onActionObject;
		}
		constexpr void setOnAction(__move_OnActionObject onActionObject) __LL_EXCEPT__ {
			this->onActionObject = std::move(onActionObject);
		}

		#pragma endregion
};

template<class T>
constexpr RAIIWrapperCreation<T> helperCreate(const RAIIContainer<T, void>& obj) {
	return RAIIWrapperCreation<T>(obj);
}
template<class T>
constexpr RAIIWrapperCreation<T> helperCreate(RAIIContainer<T, void>&& obj) {
	return RAIIWrapperCreation<T>(std::move(obj));
}

template<class T>
constexpr RAIIWrapperDestruction<T> helperDestruction(const RAIIContainer<T, void>& obj) {
	return RAIIWrapperDestruction<T>(obj);
}
template<class T>
constexpr RAIIWrapperDestruction<T> helperDestruction(RAIIContainer<T, void>&& obj) {
	return RAIIWrapperDestruction<T>(std::move(obj));
}

template<class T, class U>
constexpr RAIIWrapper<T, U> helper(const RAIIContainer<T, void>& obj, const RAIIContainer<U, void>& obj2) {
	return RAIIWrapper<T, U>(obj, obj2);
}
template<class T, class U>
constexpr RAIIWrapper<T, U> helper(RAIIContainer<T, void>&& obj, RAIIContainer<U, void>&& obj2) {
	return RAIIWrapper<T, U>(std::move(obj), std::move(obj2));
}

} // namespace raii
} // namespace llcpp

#endif // LLANYLIB_RAIIWRAPPER_HPP_
