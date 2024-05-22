//////////////////////////////////////////////
//	RAIIBase.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 6.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_RAIIBASE_HPP_) // Guard && version protector
	#if LLANYLIB_RAIIBASE_MAYOR_ != 6 || LLANYLIB_RAIIBASE_MINOR_ < 0
		#error "RAIIBase.hpp version error!"
	#endif // LLANYLIB_RAIIBASE_MAYOR_ || LLANYLIB_RAIIBASE_MINOR_

#else !defined(LLANYLIB_RAIIBASE_HPP_)
#define LLANYLIB_RAIIBASE_HPP_
#define LLANYLIB_RAIIBASE_MAYOR_ 6
#define LLANYLIB_RAIIBASE_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace raii {

/*
*	Defectos:
*		Si se hace lo siguiente puede provocar errores segun el uso del objecto contenido:
*		1. RAIIBase<Any, void> obj;
*		2. obj = nullptr;		// Calls silent clear
*		3. Any any2;
*		4. obj = any2;
*	Segun el ejemplo, en la linea 2, se llama al clear silencioso, es decir, llama al clear
*		pero no limpia el objecto data, si al llamar al operador=() en linea 4 no esta bien
*		definido, puede generar errores (debido al usuario)
* 
* 
* no usar referencias <int&>
* 
*/
template<class _DataType_, class FuncReturnType = void>
class RAIIBase {
	private:
		using __internal__RAIIBase__ = RAIIBase<_DataType_, FuncReturnType>;
	public:
		static_assert(!std::is_same_v<_DataType_, void>, "[DataType] cannot be void!");
		static_assert(!std::is_reference_v<_DataType_>, "[DataType] cannot be a reference!");
		static_assert(traits::operator_type_call_checker_v<_DataType_, ll_bool_t>, "[DataType] cannot be a reference!");
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(_DataType_, DataType);
		using Function = FuncReturnType(*)(__ref_DataType);
		using __ClearFunction = void(*)(__ref_DataType);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(Function, Function);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(__internal__RAIIBase__, RAIIBase);
	private:
		__Function function;
		__DataType data;
	public:
		constexpr RAIIBase(__cref_DataType data, __Function function) __LL_EXCEPT__
			: function(function), data(data) {}
		constexpr RAIIBase(__move_DataType data, __Function function) __LL_EXCEPT__
			: function(function), data(std::move(data)) {}
		constexpr ~RAIIBase() __LL_EXCEPT__ {}

		constexpr RAIIBase(__cref_RAIIBase other) __LL_EXCEPT__
			: function(other.function), data(other.data) {}
		constexpr __ref_RAIIBase operator=(__cref_RAIIBase other) __LL_EXCEPT__ {
			this->function = other.function;
			this->data = other.data;
			return *this;
		}

		constexpr RAIIBase(__move_RAIIBase other) __LL_EXCEPT__
			: function(other.function), data(std::move(other.data)) { other.clear(); }
		constexpr __ref_RAIIBase operator=(__move_RAIIBase other) __LL_EXCEPT__ {
			this->function = other.function;
			this->data = std::move(other.data);
			other.clear();
			return *this;
		}

		#pragma region Getters
		constexpr __cref_Function getFunction() const __LL_EXCEPT__ { return this->function; }
		constexpr __ref_Function getFunction() __LL_EXCEPT__ { return this->function; }
		constexpr __cref_DataType getData() const __LL_EXCEPT__ { return this->data; }
		constexpr __ref_DataType getData() __LL_EXCEPT__ { return this->data; }

		#pragma endregion
		#pragma region Setters
		constexpr void setFunction(__cref_Function function) __LL_EXCEPT__ { this->function = function; }
		constexpr void setData(__cref_DataType data) __LL_EXCEPT__ { this->data = data; }
		constexpr void setData(__move_DataType data) __LL_EXCEPT__ { this->data = std::move(data); }

		#pragma endregion

		constexpr operator ll_bool_t() const __LL_EXCEPT__ {
			return
				static_cast<ll_bool_t>(this->function) &&
				traits::operatorTypeCall<ll_bool_t, LL_FALSE>(this->data);
		}
		constexpr FuncReturnType operator()() __LL_EXCEPT__ {
			if constexpr (std::is_same_v<FuncReturnType, void>) {
				if (this->function) this->function(this->data);
			}
			else return (this->function) ? this->function(this->data) : FuncReturnType();
		}

		constexpr __ref_RAIIBase operator=(std::nullptr_t) __LL_EXCEPT__ { this->clear(); }
		constexpr void clear(__ClearFunction clearFunction = LL_NULLPTR) __LL_EXCEPT__ {
			this->function = LL_NULLPTR;
			if (clearFunction) clearFunction(this->data);
		}
};

template<class DataType, class FuncReturnType = void>
using RAIIContainer =
	std::conditional_t<
		std::is_same_v<DataType, void>,
		FuncReturnType(*)(void),
		RAIIBase<DataType, FuncReturnType>
	>;

} // namespace raii
} // namespace llcpp

#endif // LLANYLIB_RAIIBASE_HPP_
