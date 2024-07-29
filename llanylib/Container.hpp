//////////////////////////////////////////////
//	Container.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_CONTAINER_HPP_) // Guard && version protector
	#if LLANYLIB_CONTAINER_MAYOR_ != 8 || LLANYLIB_CONTAINER_MINOR_ < 0
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

#include "traits.hpp"

#include <optional>

#include <list>

namespace llcpp {
namespace meta {

namespace traits {
namespace common {
template<class _ClassToCheck, class _Signature>
struct LL_SHARED_LIB has_predestruction_function {
	using ClassToCheck	= _ClassToCheck;
	using Signature		= _Signature;

	static_assert(traits::is_valid_type_checker_v<ClassToCheck>,
		"type_checker<ClassToCheck> detected an invalid type!");
	static_assert(traits::is_valid_class_checker_v<ClassToCheck>,
		"class_checker<ClassToCheck> detected an invalid class type!");

	template<class> static constexpr auto test(Signature) noexcept	-> std::true_type;
	template<class> static constexpr auto test(...) noexcept		-> std::false_type;
	using type = decltype(has_predestruction_function::test<ClassToCheck>(&ClassToCheck::preDestruction));
};
template<class ClassToCheck, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_predestruction_function_v =
	has_predestruction_function<ClassToCheck, Signature>::type::value;

} // namespace common
} // namespace traits

template<class _T>
class BasicContainer {
	#pragma region Types
	public:
		using T				= _T;
		using pointer		= std::conditional_t<std::is_pointer_v<T>, T, T*>;
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
		constexpr BasicContainer(const BasicContainer& other) noexcept : data(other.data) {}
		constexpr BasicContainer& operator=(const BasicContainer& other) noexcept {
			this->data = other.data;
			return *this;
		}
		constexpr BasicContainer(BasicContainer&& other) noexcept : data(std::move(other.data)) {}
		constexpr BasicContainer& operator=(BasicContainer&& other) noexcept {
			this->data = std::move(other.data);
			return *this;
		}

		constexpr BasicContainer(const T& data) noexcept : data(data) {}
		constexpr BasicContainer& operator=(const T& data) noexcept {
			this->data = data;
			return *this;
		}
		constexpr BasicContainer(T&& data) noexcept : data(std::move(data)) {}
		constexpr BasicContainer& operator=(T&& data) noexcept {
			this->data = std::move(data);
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
			return std::pointer_traits<pointer>::pointer_to(**this);
		}
		__LL_NODISCARD__ constexpr const pointer operator->() const noexcept {
			return std::pointer_traits<pointer>::pointer_to(**this);
		}
		__LL_NODISCARD__ constexpr T& operator*() noexcept {
			return this->data;
		}
		__LL_NODISCARD__ constexpr const T& operator*() const noexcept {
			return this->data;
		}

		#pragma endregion

	#pragma endregion
};

template<class T>
class __Functions__ {
	public:
		constexpr void clear(T& asdf) noexcept {

		}
		__LL_NODISCARD__ constexpr int hash() const noexcept { return 0; }
		__LL_NODISCARD__ constexpr int hash(T&) noexcept { return 0; }
		__LL_NODISCARD__ constexpr int hash(const T&) const noexcept { return 0; }
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
		using T							= _T;
		using Functions					= _Functions;
		using BasicContainer			= BasicContainer<T>;
		using pointer					= typename BasicContainer::pointer;
		using reference					= T&;
		using creference				= const T&;

		using T_HashType				= traits::hash::get_hash_function_type_t<T>;
		using F_HashType				= traits::hash::get_hash_function_type_t<Functions>;
		using T_HashSignature			= T_HashType(T::*)() noexcept;
		using F_HashSignature			= F_HashType(Functions::*)(reference) noexcept;
		using T_HashConstSignature		= T_HashType(T::*)() const noexcept;
		using F_HashConstSignature		= F_HashType(Functions::*)(creference) const noexcept;

		using T_ClearSignature			= void(T::*)() noexcept;
		using F_ClearSignature			= void(Functions::*)(reference) noexcept;

		using T_PreDestructSignature	= void(T::*)() noexcept;
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
			if constexpr (std::is_class_v<T> && traits::common::has_predestruction_function_v<T, T_PreDestructSignature>)
				this->operator*()->preDestruction();
			if constexpr (traits::common::has_predestruction_function_v<Functions, F_PreDestructSignature>)
				Functions::preDestruction(this->operator*());
		}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ContainerExtra(const ContainerExtra& other) noexcept
			: Functions(other), BasicContainer(std::forward<const BasicContainer&>(other)) {}
		constexpr ContainerExtra& operator=(const ContainerExtra& other) noexcept {
			Functions::operator=(other);
			BasicContainer::operator=(other);
			return *this;
		}
		constexpr ContainerExtra(ContainerExtra&& other) noexcept
			: Functions(std::forward<Functions&&>(other))
			, BasicContainer(std::forward<BasicContainer&&>(other)) {}
		constexpr ContainerExtra& operator=(ContainerExtra&& other) noexcept {
			Functions::operator=(std::move(other));
			BasicContainer::operator=(std::move(other));
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
			if constexpr (std::is_class_v<T> && traits::common::has_hash_function_v<T, T_HashSignature>)
				return this->operator*()->hash();
			else if constexpr (traits::common::has_hash_function_v<Functions, F_HashSignature>)
				return Functions::hash(this->operator*());
			else return meta::hash::StandardOptionalHash(std::nullopt);
		}
		__LL_NODISCARD__ constexpr auto hash() const noexcept {
			if constexpr (std::is_class_v<T> && traits::common::has_hash_function_v<T, T_HashConstSignature>)
				return this->operator*()->hash();
			else if constexpr (traits::common::has_hash_function_v<Functions, F_HashConstSignature>)
				return Functions::hash(this->operator*());
			else return meta::hash::StandardOptionalHash(std::nullopt);
		}

		__LL_NODISCARD__ constexpr void clear() noexcept {
			if constexpr (std::is_class_v<T> && traits::common::has_clear_function_v<T, T_ClearSignature>)
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

class IntFunctions {
	public:
		constexpr void clear(int& asdf) noexcept { asdf = 0; }
		__LL_NODISCARD__ constexpr int hash() const noexcept { return 0; }
		__LL_NODISCARD__ constexpr int hash(int v) noexcept { return v; }
		__LL_NODISCARD__ constexpr int hash(const int v) const noexcept { return v; }
};

constexpr int asdf() {
	Container<int, IntFunctions> a(99);
	a = 88;
	a.clear();
	return *a;
}

void asdf2() {
	using pair = std::pair<int, int>;
	std::list<pair> _;
	auto a = _.begin();
	a->first;

	const BasicContainer<pair> p = pair{ 1, -2 };
	p->first = 9;


}

constexpr int aaaa = asdf();

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_CONTAINER_HPP_
