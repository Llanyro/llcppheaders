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

#include "traits.hpp"

namespace llcpp {
namespace raii {

/*
*	Defectos:
*		Si se hace lo siguiente puede provocar errores segun el uso del objecto contenido:
*		1. RAIIContainer<Any, void> obj;
*		2. obj = nullptr;		// Calls silent clear
*		3. Any any2;
*		4. obj = any2;
*	Segun el ejemplo, en la linea 2, se llama al clear silencioso, es decir, llama al clear
*		pero no limpia el objecto data, si al llamar al operador=() en linea 4 no esta bien
*		definido, puede generar errores (debido al usuario)
*/
template<class DataType, class FuncReturnType = void>
class RAIIContainer {
	protected:
		using __internal__RAIIContainer__ = RAIIContainer<DataType, FuncReturnType>;
	public:
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(DataType, DataType);
		//__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(FuncReturnType, FuncReturnType);
		using Function = FuncReturnType(*)(__ref_DataType);
		using __ClearFunction = void(*)(__ref_DataType);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(Function, Function);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__RAIIContainer__, RAIIContainer);
	private:
		__DataType data;
		__Function function;
	public:
		constexpr RAIIContainer(__Function function, __cref_DataType data) __LL_EXCEPT__
			: function(function), data(data) {}
		constexpr RAIIContainer(__Function function, __move_DataType data) __LL_EXCEPT__
			: function(function), data(std::move(data)) {}
		constexpr ~RAIIContainer() __LL_EXCEPT__ {}

		constexpr RAIIContainer(__cref_RAIIContainer other) __LL_EXCEPT__
			: function(other.function), data(other.data) {}
		constexpr __ref_RAIIContainer operator=(__cref_RAIIContainer other) __LL_EXCEPT__ {
			this->function = other.function;
			this->data = other.data;
			return *this;
		}

		constexpr RAIIContainer(__move_RAIIContainer other) __LL_EXCEPT__
			: function(other.function), data(std::move(other.data)) { other.clear(); }
		constexpr __ref_RAIIContainer operator=(__move_RAIIContainer other) __LL_EXCEPT__ {
			this->function = other.function;
			this->data = std::move(other.data);
			other.clear();
			return *this;
		}

		constexpr operator __cref_Function() const __LL_EXCEPT__ { return this->function; }
		constexpr operator __ref_Function() __LL_EXCEPT__ { return this->function; }
		constexpr operator __cref_DataType() const __LL_EXCEPT__ { return this->data; }
		constexpr operator __ref_DataType() __LL_EXCEPT__ { return this->data; }

		constexpr __ref_RAIIContainer operator=(__cref_Function function) __LL_EXCEPT__ {
			this->function = function;
			return *this;
		}
		constexpr __ref_RAIIContainer operator=(__cref_DataType data) __LL_EXCEPT__ {
			this->data = data;
			return *this;
		}
		constexpr __ref_RAIIContainer operator=(__move_DataType data) __LL_EXCEPT__ {
			this->data = std::move(data);
			return *this;
		}

		constexpr operator ll_bool_t() const __LL_EXCEPT__ {
			return
				traits::operatorTypeCall<ll_bool_t>(this->data)
				&& static_cast<ll_bool_t>(this->data);
		}
		constexpr FuncReturnType operator()() __LL_EXCEPT__ {
			if constexpr (std::is_same_v<FuncReturnType, void>) {
				if (this->function) this->function(this->data);
			}
			else return (this->function) ? this->function(this->data) : FuncReturnType();
		}

		constexpr __ref_RAIIContainer operator=(std::nullptr_t) __LL_EXCEPT__ { this->clear(); }
		constexpr void clear(__ClearFunction clearFunction = LL_NULLPTR) __LL_EXCEPT__ {
			this->function = LL_NULLPTR;
			if (clearFunction) clearFunction(this->data);
		}
};

template<class OnGenerateData>
class LL_SHARED_LIB RAIIWrapperCreation {
	public:
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(RAIIWrapperCreation<OnGenerateData>, RAIIWrapperCreation);
		using __DoOnGenerate = void(*)(std::add_lvalue_reference_t<OnGenerateData>);
		constexpr static ll_bool_t __is_void_type__ = std::is_same_v<OnGenerateData, void>;
		using OnGenerateObject =
			std::conditional_t<__is_void_type__, __DoOnGenerate, RAIIContainer<OnGenerateData>
		>;
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(OnGenerateObject, OnGenerateObject);
	private:
		__OnGenerateObject onGenerateObject;
	public:
		constexpr RAIIWrapperCreation(__cref_OnGenerateObject onGenerateObject) __LL_EXCEPT__
			: onGenerateObject(onGenerateObject) { this->recallOnGenerate(); }
		constexpr RAIIWrapperCreation(__move_OnGenerateObject onGenerateObject) __LL_EXCEPT__
			: onGenerateObject(std::move(onGenerateObject)) { this->recallOnGenerate(); }
		constexpr ~RAIIWrapperCreation() __LL_EXCEPT__ {}

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

		constexpr void recallOnGenerate() __LL_EXCEPT__ { this->onGenerateObject(); }

		template<typename U = OnGenerateData, typename std::enable_if<std::is_same<U, void>::value>::type* = nullptr>
		constexpr void clear() __LL_EXCEPT__ {
			this->onGenerateObject = LL_NULLPTR;
		}
		template<typename U = OnGenerateData, typename std::enable_if<!std::is_same<U, void>::value>::type* = nullptr>
		constexpr void clear(void*  clearFunc = LL_NULLPTR) __LL_EXCEPT__ {
			this->onGenerateObject.clear(reinterpret_cast<OnGenerateObject::__ClearFunction>(clearFunc));
		}

		constexpr void setOnGenerate(__cref_OnGenerateObject onGenerateObject) __LL_EXCEPT__ {
			this->onGenerateObject = onGenerateObject;
		}
		constexpr void setOnGenerate(__move_OnGenerateObject onGenerateObject) __LL_EXCEPT__ {
			this->onGenerateObject = std::move(onGenerateObject);
		}
};

template<class OnDestructionData>
class LL_SHARED_LIB RAIIWrapperDestruction {
	public:
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(OnDestructionData, OnDestructionData);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(RAIIWrapperDestruction<OnDestructionData>, RAIIWrapperDestruction);
		using DoOnDestruction = void(*)(__ptr_OnDestructionData);
	private:
		DoOnDestruction onDestruction;
		__ptr_OnDestructionData onDestructionData;
	public:
		constexpr RAIIWrapperDestruction(
			DoOnDestruction onDestruction = LL_NULLPTR,
			__ptr_OnDestructionData onDestructionData = LL_NULLPTR
		) __LL_EXCEPT__ : onDestruction(onDestruction), onDestructionData(onDestructionData) {}
		constexpr ~RAIIWrapperDestruction() __LL_EXCEPT__ { this->callOnDestruction(); }

		RAIIWrapperDestruction(__cref_RAIIWrapperDestruction other) __LL_EXCEPT__ = delete;
		__ref_RAIIWrapperDestruction operator=(__cref_RAIIWrapperDestruction other) __LL_EXCEPT__ = delete;

		constexpr RAIIWrapperDestruction(__move_RAIIWrapperDestruction other) __LL_EXCEPT__
			: __RAIIWrapperDestruction(other.onDestruction, other.onDestructionData)
		{ other.clear(); }
		constexpr __ref_RAIIWrapperDestruction operator=(__move_RAIIWrapperDestruction other) __LL_EXCEPT__ {
			this->onDestruction = other.onDestruction;
			this->onDestructionData = other.onDestructionData;
			other.clear();
			return *this;
		}

		constexpr void callOnDestruction() const __LL_EXCEPT__ {
			if (this->onDestruction)
				this->onDestruction(this->onDestructionData);
		}
		constexpr void clear() __LL_EXCEPT__ {
			this->onDestruction = LL_NULLPTR;
			this->onDestructionData = LL_NULLPTR;
		}

		constexpr void setOnDestruction(DoOnDestruction onDestruction) __LL_EXCEPT__ {
			this->onDestruction = onDestruction;
		}
		constexpr void setOnDestructionData(__ptr_OnDestructionData onDestructionData) __LL_EXCEPT__ {
			this->onDestructionData = onDestructionData;
		}
};

template<class OnGenerateData, class OnDestructionData>
class LL_SHARED_LIB RAIIWrapper : public RAIIWrapperCreation<OnGenerateData>, public RAIIWrapperDestruction<OnDestructionData> {
	protected:
		using __internal__RAIIWrapper__ = RAIIWrapper<OnGenerateData, OnDestructionData>;
	public:
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(OnGenerateData, OnGenerateData);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(OnDestructionData, OnDestructionData);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(RAIIWrapperCreation<OnGenerateData>, RAIIWrapperCreation);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(RAIIWrapperDestruction<OnDestructionData>, RAIIWrapperDestruction);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__RAIIWrapper__, RAIIWrapper);
	public:
		constexpr RAIIWrapper() __LL_EXCEPT__ {}
		constexpr RAIIWrapper(
			__RAIIWrapperCreation::DoOnGenerate onGenerate = LL_NULLPTR,
			__RAIIWrapperCreation::__ptr_OnGenerateData onGenerateData = LL_NULLPTR,
			__RAIIWrapperDestruction::DoOnDestruction onDestruction = LL_NULLPTR,
			__RAIIWrapperDestruction::__ptr_OnDestructionData onDestructionData = LL_NULLPTR
		) __LL_EXCEPT__
			: __RAIIWrapperCreation(onGenerate, onGenerateData)
			, __RAIIWrapperDestruction(onDestruction, onDestructionData)
		{}
		constexpr ~RAIIWrapper() __LL_EXCEPT__ {}

		RAIIWrapper(__cref_RAIIWrapper other) __LL_EXCEPT__ = delete;
		__ref_RAIIWrapper operator=(__cref_RAIIWrapper other) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapper(__move_RAIIWrapper other) __LL_EXCEPT__
			: __RAIIWrapperCreation(std::move(other))
			, __RAIIWrapperDestruction(std::move(other))
		{}
		constexpr __ref_RAIIWrapper operator=(__move_RAIIWrapper other) __LL_EXCEPT__ {
			__RAIIWrapperCreation::operator=(std::move(other));
			__RAIIWrapperDestruction::operator=(std::move(other));
			return *this;
		}

		RAIIWrapper(__cref_RAIIWrapperCreation other) __LL_EXCEPT__ = delete;
		__ref_RAIIWrapper operator=(__cref_RAIIWrapperCreation other) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapper(__move_RAIIWrapperCreation other) __LL_EXCEPT__
			: __RAIIWrapperCreation(std::move(other))
			, __RAIIWrapperDestruction()
		{}
		constexpr __ref_RAIIWrapper operator=(__move_RAIIWrapperCreation other) __LL_EXCEPT__ {
			__RAIIWrapperCreation::operator=(std::move(other));
			return *this;
		}

		RAIIWrapper(__cref_RAIIWrapperDestruction other) __LL_EXCEPT__ = delete;
		__ref_RAIIWrapper operator=(__cref_RAIIWrapperDestruction other) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapper(__move_RAIIWrapperDestruction other) __LL_EXCEPT__
			: __RAIIWrapperCreation()
			, __RAIIWrapperDestruction(std::move(other))
		{}
		constexpr __ref_RAIIWrapper operator=(__move_RAIIWrapperDestruction other) __LL_EXCEPT__ {
			__RAIIWrapperDestruction::operator=(std::move(other));
			return *this;
		}

		constexpr void clear() __LL_EXCEPT__ {
			__RAIIWrapperCreation::clear();
			__RAIIWrapperDestruction::clear();
		}
};

template<class OnGenerateData, class OnDestructionData, class ActionInput, class ActionOutput>
class LL_SHARED_LIB RAIIWrapperExtra : public RAIIWrapper<OnGenerateData, OnDestructionData> {
	protected:
		using __internal__RAIIWrapper__ = RAIIWrapper<OnGenerateData, OnDestructionData>;
		using __internal__RAIIWrapperExtra__ = RAIIWrapperExtra<OnGenerateData, OnDestructionData, ActionInput, ActionOutput>;
	public:
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(ActionInput, ActionInput);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(ActionOutput, ActionOutput);
		using DoOnAction = __ActionOutput(*)(__ptr_ActionInput data);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(OnGenerateData, OnGenerateData);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(OnDestructionData, OnDestructionData);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(RAIIWrapperCreation<OnGenerateData>, RAIIWrapperCreation);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(RAIIWrapperDestruction<OnDestructionData>, RAIIWrapperDestruction);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__RAIIWrapper__, RAIIWrapper);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__RAIIWrapperExtra__, RAIIWrapperExtra);
	protected:
		DoOnAction onAction;
		__ptr_ActionInput onActionData;
	public:
		constexpr RAIIWrapperExtra(
			__RAIIWrapperCreation::DoOnGenerate onGenerate = LL_NULLPTR,
			__RAIIWrapperCreation::__ptr_OnGenerateData onGenerateData = LL_NULLPTR,
			__RAIIWrapperDestruction::DoOnDestruction onDestruction = LL_NULLPTR,
			__RAIIWrapperDestruction::__ptr_OnDestructionData onDestructionData = LL_NULLPTR,
			DoOnAction onAction = LL_NULLPTR,
			__ptr_ActionInput onActionData = LL_NULLPTR
		) __LL_EXCEPT__
			: __RAIIWrapper(onGenerate, onGenerateData, onDestruction, onDestructionData)
			, onAction(onAction), onActionData(onActionData)
		{}
		constexpr ~RAIIWrapperExtra() __LL_EXCEPT__ {}
		
		RAIIWrapperExtra(__cref_RAIIWrapperExtra other) __LL_EXCEPT__ = delete;
		__ref_RAIIWrapperExtra operator=(__cref_RAIIWrapperExtra other) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapperExtra(__move_RAIIWrapperExtra other) __LL_EXCEPT__
			: __RAIIWrapper(std::move(other))
			, onAction(other.onAction), onActionData(other.onActionData)
		{ other.clear(); }
		constexpr __ref_RAIIWrapperExtra operator=(__move_RAIIWrapperExtra other) __LL_EXCEPT__ {
			__RAIIWrapper::operator=(std::move(other));
			this->onAction = other.onAction;
			this->onActionData = other.onActionData;
			other.clear();
			return *this;
		}

		RAIIWrapperExtra(__cref_RAIIWrapper other) __LL_EXCEPT__ = delete;
		__ref_RAIIWrapperExtra operator=(__cref_RAIIWrapper other) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapperExtra(__move_RAIIWrapper other) __LL_EXCEPT__
			: __RAIIWrapper(std::move(other))
			, onAction(LL_NULLPTR), onActionData(LL_NULLPTR)
		{}
		constexpr __ref_RAIIWrapperExtra operator=(__move_RAIIWrapper other) __LL_EXCEPT__ {
			__RAIIWrapper::operator=(std::move(other));
			return *this;
		}

		RAIIWrapperExtra(__cref_RAIIWrapperCreation other) __LL_EXCEPT__ = delete;
		__ref_RAIIWrapperExtra operator=(__cref_RAIIWrapperCreation other) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapperExtra(__move_RAIIWrapperCreation other) __LL_EXCEPT__
			: __RAIIWrapper(std::move(other))
			, onAction(LL_NULLPTR), onActionData(LL_NULLPTR)
		{}
		constexpr __ref_RAIIWrapperExtra operator=(__move_RAIIWrapperCreation other) __LL_EXCEPT__ {
			__RAIIWrapper::operator=(std::move(other));
			return *this;
		}
		
		RAIIWrapperExtra(__cref_RAIIWrapperDestruction other) __LL_EXCEPT__ = delete;
		__ref_RAIIWrapperExtra operator=(__cref_RAIIWrapperDestruction other) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapperExtra(__move_RAIIWrapperDestruction other) __LL_EXCEPT__
			: __RAIIWrapper(std::move(other))
			, onAction(LL_NULLPTR), onActionData(LL_NULLPTR)
		{}
		constexpr __ref_RAIIWrapperExtra operator=(__move_RAIIWrapperDestruction other) __LL_EXCEPT__ {
			__RAIIWrapper::operator=(std::move(other));
			return *this;
		}

		constexpr void callOnAction() const __LL_EXCEPT__ {
			if (this->onAction)
				this->onAction(this->onActionData);
		}

		constexpr void setOnAction(DoOnAction onAction) __LL_EXCEPT__ {
			this->onAction = onAction;
		}
		constexpr void setOnActionData(__ptr_ActionInput onActionData) __LL_EXCEPT__ {
			this->onActionData = onActionData;
		}
		constexpr void clear() __LL_EXCEPT__ {
			__RAIIWrapper::clear();
			this->onAction = LL_NULLPTR;
			this->onActionData = LL_NULLPTR;
		}
};

} // namespace raii
} // namespace llcpp

#endif // LLANYLIB_RAIIWRAPPER_HPP_
