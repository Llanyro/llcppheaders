//////////////////////////////////////////////
//	GenericFunctions.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_GENERICFUNCTIONS_INCOMPLETE_HPP_)
	#if LLANYLIB_GENERICFUNCTIONS_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_GENERICFUNCTIONS_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "GenericFunctions.hpp(incomplete) version error!"
		#else
			#error "GenericFunctions.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_GENERICFUNCTIONS_INCOMPLETE_MAYOR_ || LLANYLIB_GENERICFUNCTIONS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_GENERICFUNCTIONS_INCOMPLETE_HPP_)
	#define LLANYLIB_GENERICFUNCTIONS_INCOMPLETE_HPP_
	#define LLANYLIB_GENERICFUNCTIONS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_GENERICFUNCTIONS_INCOMPLETE_MINOR_ 0

#include "../concepts/concepts.hpp"

namespace llcpp {
namespace meta {
namespace utils {	

class GenericFunctions;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_GENERICFUNCTIONS_HPP_)
	#if LLANYLIB_GENERICFUNCTIONS_MAYOR_ != 12 || LLANYLIB_GENERICFUNCTIONS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "GenericFunctions.hpp version error!"
		#else
			#error "GenericFunctions.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_GENERICFUNCTIONS_MAYOR_ || LLANYLIB_GENERICFUNCTIONS_MINOR_

#else
	#define LLANYLIB_GENERICFUNCTIONS_HPP_
	#define LLANYLIB_GENERICFUNCTIONS_MAYOR_ 12
	#define LLANYLIB_GENERICFUNCTIONS_MINOR_ 0

#include "../concepts/GenericFunctions.hpp"

namespace llcpp {
namespace meta {
namespace utils {

enum class GenericMode {
	Cleaner,
	Invalidator,
};

template<::llcpp::meta::utils::GenericMode _MODE = ::llcpp::meta::utils::GenericMode::Cleaner>
class GenericFunctions : public ::llcpp::AlwaysValidTag {
	#pragma region Types
	public:
		// Class related
		using _MyType								= GenericFunctions;

		// Types and enums
		using GenericModeType						= decltype(_MODE);

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr GenericModeType MODE				= _MODE;
		static constexpr ll_bool_t IS_CLEANER				= _MODE == GenericModeType::Cleaner;
		static constexpr ll_bool_t IS_INVALIDATOR			= _MODE == GenericModeType::Invalidator;
		template<class T>
		static constexpr ll_bool_t IS_CLEANER_NO_POINTER	= IS_CLEANER && !::std::is_pointer_v<T>;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		DEFAULT_RULE_OF_6_CLEAR(GenericFunctions);
	
		#pragma endregion
		#pragma region Clear
	public:
		template<class ExternalFunctions = _MyType, class T>
		__LL_NODISCARD__ constexpr auto process(T& obj) const noexcept requires(IS_CLEANER) {
			// If this is this class type, we will use this instance as main source
			if constexpr (::std::is_same_v<ExternalFunctions, _MyType>)
				return this->process(obj, *this);
			// If this is not this class type, we need a source of it
			// If source not provided, we need to instance the object
			else {
				static_assert(::std::is_nothrow_default_constructible_v<ExternalFunctions>,
					"ExternalFunctions type needs to be a noexcept default contructible!");
				ExternalFunctions external;
				return this->process(obj, external);
			}
		}
		template<class ExternalFunctions = _MyType, class T>
		__LL_NODISCARD__ constexpr auto process(T& obj, const ExternalFunctions& external) const noexcept requires(IS_CLEANER) {
			// If external has a way to clear object
			if constexpr (::llcpp::meta::concepts::signature::HasCleaner<ExternalFunctions, void, T&>)
				return external.__cleaner(obj);
			else if constexpr (::std::is_pointer_v<T>) {
#if __LL_CLEAR_POINTER_AS == 0
				// If is a pointer, we dont know how to clear it
				static_assert(!::std::is_pointer_v<T>,
					"Cannot clear a pointer. Is it an array or just a pointer (?). If its a pointer just deference it.");
#elif __LL_CLEAR_POINTER_AS == 1
				// User wants to deference and clear
				return this->process(*obj, external);
#endif // __LL_CLEAR_POINTER_AS
			}
			// If is an array and we dont know how to clear it, we tell user
			else if constexpr (::std::is_array_v<T>) {
				static_assert(!::std::is_array_v<T>,
					"Cannot clear this array with current ExternalFunctions!");
			}
			// If is a class, we try specific thigs
			else if constexpr (::std::is_class_v<T>) {
				// If is class and has own clear, we use it
				if constexpr (::llcpp::meta::concepts::signature::HasClear<T>)
					return obj.clear();
				// If not, we use default, if possible
				else if constexpr (::llcpp::meta::concepts::signature::HasCopyAssignable<T>)
					obj = ::llcpp::ZERO_VALUE<T>;
#if defined(__LL_BUILTIN_POINTER_CHECK)
				else if constexpr (!::llcpp::meta::traits::HasPointerAttribute<T>) {
					// ????
					static_assert(false, "Not yet implemented");
				}
#endif
				// If we cannot use default clears, we cant do anything
				else {
					static_assert(::llcpp::meta::concepts::signature::HasClear<T>,
						"clear() or operator=() is needed to clear this object");
				}
			}
			// If there is no suitable cleaner, we use this class as default
			else if constexpr (!::std::is_same_v<ExternalFunctions, _MyType>)
				return this->process(obj, *this);
			else {
				static_assert(::std::is_same_v<ExternalFunctions, _MyType>,
					"No suitable cleaner for this type!");
			}
		}
		template<class ExternalFunctions = _MyType, class T>
		__LL_NODISCARD__ constexpr auto process(T* begin, const T* end) const noexcept requires(IS_CLEANER) {
			// If this is this class type, we will use this instance as main source
			if constexpr (::std::is_same_v<ExternalFunctions, _MyType>)
				return this->process(begin, end, *this);
			// If this is not this class type, we need a source of it
			// If source not provided, we need to instance the object
			else {
				static_assert(::std::is_nothrow_default_constructible_v<ExternalFunctions>,
					"ExternalFunctions type needs to be a noexcept default contructible!");
				ExternalFunctions external;
				return this->process(begin, end, external);
			}
		}
		template<class ExternalFunctions = _MyType, class T>
		__LL_NODISCARD__ constexpr auto process(T* begin, const T* end, const ExternalFunctions& external) const noexcept requires(IS_CLEANER) {
			// If external has a way to clear object
			if constexpr (::llcpp::meta::concepts::signature::HasCleaner<ExternalFunctions, void, T&>)
				return external.__cleaner(begin, end);
			// If there is no suitable cleaner, we use this class as default
			else if constexpr (!::std::is_same_v<ExternalFunctions, _MyType>)
				return this->process(begin, end, *this);
			else {
				static_assert(::std::is_same_v<ExternalFunctions, _MyType>,
					"No suitable cleaner for this type!");
			}
		}

		// Clear only objects/primitives that can be copied assignable
		template<class T>
			requires IS_CLEANER_NO_POINTER<T> && ::llcpp::meta::concepts::signature::HasCopyAssignable<T>
		constexpr void __cleaner(T& obj) const noexcept {
			obj = ::std::forward<const T&>(::llcpp::ZERO_VALUE<T>);
		}
		template<class T, usize N>
		constexpr void __cleaner(T (&__array)[N]) const noexcept requires(IS_CLEANER_NO_POINTER<T>) {
			this->__cleaner(__array, __array + N);
		}
		template<class T>
		constexpr void __cleaner(T* begin, const T* end) const noexcept requires(IS_CLEANER_NO_POINTER<T>) {
			T* aux = begin;
			for(; aux < end; ++aux)
				this->process(*aux, *this);
		}

		#pragma endregion
		#pragma region Invalidator
	public:
		template<class ExternalFunctions = _MyType, class T>
		__LL_NODISCARD__ constexpr auto process(T& obj) const noexcept requires(IS_INVALIDATOR) {
			// If this is this class type, we will use this instance as main source
			if constexpr (::std::is_same_v<ExternalFunctions, _MyType>)
				return this->process(obj, *this);
			// If this is not this class type, we need a source of it
			// If source not provided, we need to instance the object
			else {
				static_assert(::std::is_nothrow_default_constructible_v<ExternalFunctions>,
					"ExternalFunctions type needs to be a noexcept default contructible!");
				ExternalFunctions external;
				return this->process(obj, external);
			}
		}
		template<class ExternalFunctions = _MyType, class T>
		__LL_NODISCARD__ constexpr auto process(T& obj, const ExternalFunctions& external) const noexcept requires(IS_INVALIDATOR) {
			// If external has a way to clear object
			if constexpr (::llcpp::meta::concepts::signature::HasInvalidator<ExternalFunctions, void, T&>)
				return external.__invalidate(obj);
			else if constexpr (::std::is_pointer_v<T>) {
#if __LL_CLEAR_POINTER_AS == 0
				// If is a pointer, we dont know how to clear it
				static_assert(!::std::is_pointer_v<T>,
					"Cannot invalidate a pointer. Is it an array or just a pointer (?). If its a pointer just deference it. Or set it as a nullptr");
#elif __LL_CLEAR_POINTER_AS == 1
				// User wants to deference and clear
				return this->process(*obj, external);
#endif // __LL_CLEAR_POINTER_AS
			}
			// If is an array and we dont know how to clear it, we tell user
			else if constexpr (::std::is_array_v<T>) {
				static_assert(!::std::is_array_v<T>,
					"Cannot invalidate this array with current ExternalFunctions!");
			}
			// If is a class, we try specific thigs
			else if constexpr (::std::is_class_v<T>) {
				// If is class and has own clear, we use it
				if constexpr (::llcpp::meta::concepts::signature::HasMakeInvalid<T>)
					return obj.makeInvalid();
				// If we cannot use default clears, we cant do anything
				else {
					static_assert(::llcpp::meta::concepts::signature::HasClear<T>,
						"makeInvalid() is needed to invalidate this object");
				}
			}
			else {
				static_assert(::std::is_same_v<ExternalFunctions, _MyType>,
					"No suitable invalidator for this type!");
			}
		}

		#pragma endregion

	#pragma endregion
};

using Cleaner = ::llcpp::meta::utils::GenericFunctions<::llcpp::meta::utils::GenericMode::Cleaner>;
using Invalidator = ::llcpp::meta::utils::GenericFunctions<::llcpp::meta::utils::GenericMode::Invalidator>;

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_GENERICFUNCTIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
