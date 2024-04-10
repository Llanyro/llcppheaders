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
		constexpr RAIIWrapperDestruction(__cref_OnDestructionObject onDestructionObject) __LL_EXCEPT__
			: onDestructionObject(onDestructionObject) {}
		constexpr RAIIWrapperDestruction(__move_OnDestructionObject onDestructionObject) __LL_EXCEPT__
			: onDestructionObject(std::move(onDestructionObject)) {}
		constexpr ~RAIIWrapperDestruction() __LL_EXCEPT__ { this->recallOnDestruction(); }

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
		constexpr RAIIWrapper() __LL_EXCEPT__ = delete;
		constexpr ~RAIIWrapper() __LL_EXCEPT__ {}

		constexpr RAIIWrapper(__cref_RAIIWrapperCreation other) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapper operator=(__cref_RAIIWrapperCreation other) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapper(__move_RAIIWrapperCreation other) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapper operator=(__move_RAIIWrapperCreation other) __LL_EXCEPT__ = delete;

		constexpr RAIIWrapper(__cref_RAIIWrapperDestruction other) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapper operator=(__cref_RAIIWrapperDestruction other) __LL_EXCEPT__ = delete;
		constexpr RAIIWrapper(__move_RAIIWrapperDestruction other) __LL_EXCEPT__ = delete;
		constexpr __ref_RAIIWrapper operator=(__move_RAIIWrapperDestruction other) __LL_EXCEPT__ = delete;

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

		//constexpr void clear(
		//	__RAIIWrapperCreation::__Clear clearCreationFunction = LL_NULLPTR,
		//	__RAIIWrapperDestruction::__ClearFunction clearDestructionFunction = LL_NULLPTR
		//) __LL_EXCEPT__ {
		//	__RAIIWrapperCreation::clear(clearCreationFunction);
		//	__RAIIWrapperDestruction::clear(clearDestructionFunction);
		//}
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

struct functions;

struct __mutex__ {
	functions* mt;
	int* val;

	constexpr __mutex__(functions* mt, int* val);
	constexpr __mutex__(const __mutex__& other);
	constexpr ~__mutex__();
	constexpr __mutex__& operator=(const __mutex__& other);
	constexpr operator ll_bool_t() const;
};

struct functions {
	constexpr functions() {}
	constexpr ~functions() {}

	constexpr functions(const functions& other) {}
	constexpr functions& operator=(const functions& other) { return *this; }

	constexpr void lock(__mutex__& v) { v.val[0]++; }
	constexpr void unlock(__mutex__& v) { v.val[0] += 3; }
	constexpr operator ll_bool_t() const { return true; }
	operator ll_bool_t() const { return true; }
};

constexpr __mutex__::__mutex__(functions* mt, int* val) : mt(mt), val(val) {}
constexpr __mutex__::__mutex__(const __mutex__& other) : mt(other.mt), val(other.val) {}
constexpr __mutex__::~__mutex__() {}
constexpr __mutex__& __mutex__::operator=(const __mutex__& other) {
	this->mt = other.mt;
	this->val = other.val;
	return *this;
}
constexpr __mutex__::operator ll_bool_t() const { return llcpp::LL_TRUE; }

} // namespace raii
} // namespace llcpp

constexpr void _lamb(int*& val) { val[0] = 7; }
constexpr void _lamb2(int*& val) { (*val)++; }

constexpr ll_bool_t result_1 = llcpp::traits::operator_type_call_checker_v<int, ll_bool_t>;
constexpr ll_bool_t result_2 = llcpp::traits::operator_type_call_checker_v<int*, ll_bool_t>;
constexpr ll_bool_t result_3 = llcpp::traits::operator_type_call_checker_v<int**, ll_bool_t>;

constexpr ll_bool_t result_4 = llcpp::traits::operator_type_call_checker_v<llcpp::raii::__mutex__, ll_bool_t>;
constexpr ll_bool_t result_5 = llcpp::traits::operator_type_call_checker_v<llcpp::raii::__mutex__*, ll_bool_t>;
constexpr ll_bool_t result_6 = llcpp::traits::operator_type_call_checker_v<llcpp::raii::__mutex__**, ll_bool_t>;

constexpr ll_bool_t result_7 = llcpp::traits::operator_type_call_checker_v<llcpp::raii::functions, ll_bool_t>;
constexpr ll_bool_t result_8 = llcpp::traits::operator_type_call_checker_v<llcpp::raii::functions*, ll_bool_t>;
constexpr ll_bool_t result_9 = llcpp::traits::operator_type_call_checker_v<llcpp::raii::functions**, ll_bool_t>;

constexpr int fund() {
	int val = 0;
	int* v2 = &val;
	llcpp::raii::functions mt;

	//{
	//	llcpp::raii::RAIIContainer<llcpp::raii::__mutex__> obj_cre({ &mt, &val }, [](llcpp::raii::__mutex__& mt) -> void { mt.mt->lock(mt); });
	//	llcpp::raii::RAIIContainer<llcpp::raii::__mutex__> obj_del({ &mt, &val }, [](llcpp::raii::__mutex__& mt) -> void { mt.mt->unlock(mt); });
	//	llcpp::raii::RAIIWrapper<llcpp::raii::__mutex__, llcpp::raii::__mutex__> b5(obj_cre, obj_del);
	//}
	{
		llcpp::raii::RAIIContainer<int*> obj_cre(v2, _lamb);
		llcpp::raii::RAIIContainer<int*> obj_del(v2, _lamb2);
		llcpp::raii::RAIIWrapper<int*, int*> b5(obj_cre, obj_del);
	}

	//llcpp::raii::RAIIContainer<__mutex__&, void> obj_cre(_mt, [](__mutex__& mt) -> void { mt.mt.lock(mt.val); });
	//llcpp::raii::RAIIContainer<__mutex__&, void> obj_del(_mt, [](__mutex__& mt) -> void { mt.mt.unlock(mt.val); });
	//llcpp::raii::RAIIWrapper<void, __mutex__&> b5([](){}, obj_del);

	return val;
}

constexpr int asdf = fund();

#endif // LLANYLIB_RAIIWRAPPER_HPP_
