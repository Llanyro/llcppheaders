//////////////////////////////////////////////
//	Container.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_CONTAINER_HPP_) // Guard && version protector
	#if LLANYLIB_CONTAINER_MAYOR_ != 9 || LLANYLIB_CONTAINER_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Container.hpp version error!"
		#else
			#error "Container.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_CONTAINER_MAYOR_ || LLANYLIB_CONTAINER_MINOR_

#else !defined(LLANYLIB_CONTAINER_HPP_)
#define LLANYLIB_CONTAINER_HPP_
#define LLANYLIB_CONTAINER_MAYOR_ 9
#define LLANYLIB_CONTAINER_MINOR_ 0

#include "hash_types.hpp"
#include "common.hpp"

namespace llcpp {
namespace meta {

template<class _T>
class BasicContainer {
	#pragma region Types
	public:
		using _MyType	= BasicContainer;
		using T			= _T;
		using pointer	= std::conditional_t<std::is_pointer_v<T>, T, T*>;
		//using const_pointer	= std::conditional_t<std::is_pointer_v<T>, std::remove_pointer_t<T>* const, T* const>;

	#pragma endregion
	#pragma region Assersts
	public:
		static_assert(traits::is_valid_type_checker_ignore_pointer_v<T>,
			"type_checker<T> detected an invalid type!");
		static_assert(traits::is_valid_constructor_checker_v<T>,
			"constructor_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Attributes
	private:
		T data;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr BasicContainer() noexcept : data() {}
		template<class... Args>
		constexpr BasicContainer(Args&&... args) noexcept
			: data(std::forward<Args>(args)...) {}
		constexpr ~BasicContainer() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr BasicContainer(const BasicContainer& other) noexcept
			: data(other.data) {}
		constexpr BasicContainer& operator=(const BasicContainer& other) noexcept {
			this->data = other.data;
			return *this;
		}
		constexpr BasicContainer(BasicContainer&& other) noexcept
			: data(std::move(other.data)) { meta::common::clear_if_pointer<T>(other.data); }
		constexpr BasicContainer& operator=(BasicContainer&& other) noexcept {
			this->data = std::move(other.data);
			meta::common::clear_if_pointer<T>(other.data);
			return *this;
		}

		constexpr BasicContainer(const T& data) noexcept
			: data(data) {}
		constexpr BasicContainer& operator=(const T& data) noexcept {
			this->data = data;
			return *this;
		}
		constexpr BasicContainer(T&& data) noexcept
			: data(std::move(data)) { meta::common::clear_if_pointer<T>(data); }
		constexpr BasicContainer& operator=(T&& data) noexcept {
			this->data = std::move(data);
			meta::common::clear_if_pointer<T>(other.data);
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const BasicContainer*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator BasicContainer*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr pointer operator->() noexcept {
			return std::pointer_traits<pointer>::pointer_to(&this->data);
		}
		__LL_NODISCARD__ constexpr const pointer operator->() const noexcept {
			return std::pointer_traits<pointer>::pointer_to(&this->data);
		}
		__LL_NODISCARD__ constexpr T& operator*() noexcept { return this->data; }
		__LL_NODISCARD__ constexpr const T& operator*() const noexcept { return this->data; }

		template<class U>
		__LL_NODISCARD__ constexpr meta::OptionalBool compare_eq(const BasicContainer<U>& other) const noexcept {
			return meta::common::is_same_value<T, U>(this->data, other.data);
		}
		template<class U>
		__LL_NODISCARD__ constexpr meta::OptionalBool compare_no_eq(const BasicContainer<U>& other) const noexcept {
			return meta::common::is_not_same_value<T, U>(this->data, other.data);
		}
		template<class U>
		__LL_NODISCARD__ constexpr meta::OptionalBool compare_eq(const U& data) const noexcept {
			return meta::common::is_same_value<T, U>(this->data, data);
		}
		template<class U>
		__LL_NODISCARD__ constexpr meta::OptionalBool compare_no_eq(const U& data) const noexcept {
			return meta::common::is_not_same_value<T, U>(this->data, data);
		}

		__LL_NODISCARD__ constexpr ll_bool_t operator==(const BasicContainer& other) const noexcept {
			auto b = this->compare_eq<T>(std::forward<const BasicContainer&>(other));
			if (b.has_value()) return b.value();
			else LL_FALSE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const BasicContainer& other) const noexcept {
			auto b = this->compare_no_eq<T>(std::forward<const BasicContainer&>(other));
			if (b.has_value()) return b.value();
			else LL_FALSE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator==(const T& data) const noexcept {
			auto b = this->compare_eq<T>(std::forward<const T&>(data));
			if (b.has_value()) return b.value();
			else LL_FALSE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t operator!=(const T& data) const noexcept {
			auto b = this->compare_no_eq<T>(std::forward<const T&>(data));
			if (b.has_value()) return b.value();
			else LL_FALSE;
		}

		#pragma endregion

	#pragma endregion
};

// This class has a problem by traits::hash::get_hash_function_type_t<>
// Let me explain it with an example
//	- We have an object _T as int
//		- Is a basic type
//		- Does not have any hash function
//	- And a class _Functions
//		- Is a class defined by user
//		- Needs 2 hash() functions
//			1. The first (enabler) one does not have any arguments and should be empty
//				because will not be used for any more that getting the function type
//			2. The second function is the one that will hash the object
//				This function has the same signature as the first one but the argument of the object
//	- We just need only one enabler to enable the normal or const function
//	- Class example as follows:
// 
//	class __Functions__ {
//		public:
//			// This is the hash enabler
//			__LL_NODISCARD__ constexpr int hash() const noexcept { return 0; }
//			// This is the normal hasher
//			__LL_NODISCARD__ constexpr int hash(int&) noexcept { return 0; }
//			// This is the const hasher
//			__LL_NODISCARD__ constexpr int hash(const int&) const noexcept { return 0; }
//	};
// 
// Destructor will call object "preDestruction()" function if is a class and has that function
//	also, if class _Functions has the function too, it will be called too after object function
// 
// 
// 
// 
template<class _T, class _Functions>
class ContainerExtra : public _Functions, public BasicContainer<_T> {
	#pragma region Types
	public:
		using _MyType					= ContainerExtra;
		using T							= _T;
		using T_class					= std::conditional_t<std::is_class_v<T>, T, llcpp::Emptyclass>;
		using Functions					= _Functions;
		using BasicContainer			= BasicContainer<T>;
		using pointer					= typename BasicContainer::pointer;
		using reference					= T&;
		using creference				= const T&;

		using T_HashType				= traits::hash::get_hash_function_type_t<T>;
		using F_HashType				= traits::hash::get_hash_function_type_t<Functions>;

		using T_HashSignature			= T_HashType(T_class::*)() noexcept;
		using T_HashConstSignature		= T_HashType(T_class::*)() const noexcept;
		using T_ClearSignature			= void(T_class::*)() noexcept;
		using T_PreDestructSignature	= void(T_class::*)() noexcept;

		using F_HashSignature			= F_HashType(Functions::*)(reference) noexcept;
		using F_HashConstSignature		= F_HashType(Functions::*)(creference) const noexcept;
		using F_ClearSignature			= void(Functions::*)(reference) noexcept;
		using F_PreDestructSignature	= void(Functions::*)(reference) noexcept;

	#pragma endregion
	#pragma region Assersts
	public:
		static_assert(traits::is_valid_class_checker_v<Functions>,
			"class_checker<ContainerExtraFunctions> detected an invalid class type!");

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr ContainerExtra() noexcept : Functions(), BasicContainer() {}
		template<class... Args>
		constexpr ContainerExtra(Args&&... args) noexcept
			: Functions(), BasicContainer(std::forward<Args>(args)...) {}
		constexpr ~ContainerExtra() noexcept {
			if constexpr (traits::common::has_predestruction_function_v<T_class, T_PreDestructSignature>)
				this->operator*()->predestruction();
			if constexpr (traits::common::has_predestruction_function_v<Functions, F_PreDestructSignature>)
				Functions::predestruction(this->operator*());
		}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ContainerExtra(const ContainerExtra& other) noexcept
			: Functions(std::forward<const Functions&>(other))
			, BasicContainer(std::forward<const BasicContainer&>(other)) {}
		constexpr ContainerExtra& operator=(const ContainerExtra& other) noexcept {
			Functions::operator=(std::forward<const Functions&>(other));
			BasicContainer::operator=(std::forward<const BasicContainer&>(other));
			return *this;
		}
		constexpr ContainerExtra(ContainerExtra&& other) noexcept
			: Functions(std::forward<Functions&&>(other))
			, BasicContainer(std::forward<BasicContainer&&>(other)) {}
		constexpr ContainerExtra& operator=(ContainerExtra&& other) noexcept {
			Functions::operator=(std::forward<Functions&&>(other));
			BasicContainer::operator=(std::forward<BasicContainer&&>(other));
			return *this;
		}

		constexpr ContainerExtra(const T& data) noexcept
			: Functions(), BasicContainer(data) {}
		constexpr ContainerExtra& operator=(const T& data) noexcept {
			BasicContainer::operator=(data);
			return *this;
		}
		constexpr ContainerExtra(T&& data) noexcept
			: Functions(), BasicContainer(std::move(data)) {}
		constexpr ContainerExtra& operator=(T&& data) noexcept {
			BasicContainer::operator=(std::move(data));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const ContainerExtra*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator ContainerExtra*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr pointer operator->() noexcept { return BasicContainer::operator->(); }
		__LL_NODISCARD__ constexpr const pointer operator->() const noexcept { return BasicContainer::operator->(); }
		__LL_NODISCARD__ constexpr T& operator*() noexcept { return BasicContainer::operator*(); }
		__LL_NODISCARD__ constexpr const T& operator*() const noexcept { return BasicContainer::operator*(); }
	public:
		__LL_NODISCARD__ constexpr auto hash() noexcept {
			if constexpr (traits::common::has_hash_function_v<T_class, T_HashSignature>)
				return this->operator*()->hash();
			else if constexpr (traits::common::has_hash_function_v<Functions, F_HashSignature>)
				return Functions::hash(this->operator*());
			else return meta::hash::StandardOptionalHash(std::nullopt);
		}
		__LL_NODISCARD__ constexpr auto hash() const noexcept {
			if constexpr (traits::common::has_hash_function_v<T_class, T_HashConstSignature>)
				return this->operator*()->hash();
			else if constexpr (traits::common::has_hash_function_v<Functions, F_HashConstSignature>)
				return Functions::hash(this->operator*());
			else return meta::hash::StandardOptionalHash(std::nullopt);
		}

		__LL_NODISCARD__ constexpr void clear() noexcept {
			if constexpr (traits::common::has_clear_function_v<T_class, T_ClearSignature>)
				this->operator*()->clear();
			else if constexpr (traits::common::has_clear_function_v<Functions, F_ClearSignature>)
				Functions::clear(this->operator*());
		}

		#pragma endregion

	#pragma endregion
};

template<class T, class ContainerExtraFunctions = void>
using Container = std::conditional_t<
	std::is_same_v<ContainerExtraFunctions, void>,
	BasicContainer<T>,
	ContainerExtra<T, ContainerExtraFunctions>>;

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CONTAINER_HPP_
