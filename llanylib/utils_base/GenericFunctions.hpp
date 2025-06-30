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

#if defined(LL_LIB_PATHS)
	#include <llanylib/concepts/GenericFunctions.hpp>
#else
	#include "../concepts/GenericFunctions.hpp"
#endif // LL_LIB_PATHS

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

#if defined(LL_LIB_PATHS)
	#include <llanylib/concepts/GenericFunctions.hpp>
#else
	#include "../concepts/GenericFunctions.hpp"
#endif // LL_LIB_PATHS

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
			__LL_FUNCTION_INIT__;
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
			__LL_FUNCTION_INIT__;
			// If external has a way to clear object
			if constexpr (::llcpp::meta::concepts::signature::HasCleaner<const ExternalFunctions, void, T&>)
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
				// [TOCHECK] [TODO]
				// If object is list type, and we can iterate over them
				else if constexpr (::llcpp::meta::concepts::SameTypeBeginEnd<T>)
					return this->process(obj.begin(), obj.end(), ExternalFunctions);
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
			__LL_FUNCTION_INIT__;
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
			__LL_FUNCTION_INIT__;
			// If external has a way to clear object
			if constexpr (::llcpp::meta::concepts::signature::HasCleaner<const ExternalFunctions, void, T&>)
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
			__LL_FUNCTION_INIT__;
			obj = ::std::forward<const T&>(::llcpp::ZERO_VALUE<T>);
		}
		template<class T, usize N>
		constexpr void __cleaner(T (&__array)[N]) const noexcept requires(IS_CLEANER_NO_POINTER<T>) {
			__LL_FUNCTION_INIT__;
			this->__cleaner(__array, __array + N);
		}
		template<class T>
		constexpr void __cleaner(T* begin, const T* end) const noexcept requires(IS_CLEANER_NO_POINTER<T>) {
			__LL_FUNCTION_INIT__;
			T* aux = begin;
			for(; aux < end; ++aux)
				this->process(*aux, *this);
		}

		#pragma endregion
		#pragma region Invalidator
	public:
		template<class ExternalFunctions = _MyType, class T>
		__LL_NODISCARD__ constexpr auto process(T& obj) const noexcept requires(IS_INVALIDATOR) {
			__LL_FUNCTION_INIT__;
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
			__LL_FUNCTION_INIT__;
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

#if __LL_INCLUDE_KATS == 1
namespace kat {

struct TestObj {
	f32 aaa;

	__LL_NODISCARD__ constexpr ll_bool_t operator==(const TestObj& other) const noexcept {
		return this->aaa == other.aaa;
	}
	__LL_NODISCARD__ constexpr ll_bool_t operator!=(const TestObj& other) const noexcept {
		return this->aaa != other.aaa;
	}


	template<class T, usize N>
	constexpr void __invalidate(T (&v)[N]) const noexcept {
		return this->__invalidate(v, v + N);
	}
	template<class T>
	constexpr void __invalidate(T* begin, const T* end) const noexcept {
		T* aux = begin;
		for(; aux < end; ++aux)
			this->__invalidate(*aux);
	}
	constexpr void __invalidate(u32& obj) const noexcept { obj = u32(-1); }
	constexpr void __invalidate(TestObj& obj) const noexcept { obj = TestObj{ -1.0f }; }

};
__LL_VAR_INLINE__ constexpr auto DEFAULT_VALUE		= TestObj { 99.0f };
__LL_VAR_INLINE__ constexpr auto CLEAR_VALUE		= TestObj { ::llcpp::ZERO_VALUE<f32> };
__LL_VAR_INLINE__ constexpr auto INVALIDATE_VALUE	= TestObj { -1.0f };

template<class T, usize N, class Cleaner, class CleanerExtra = Cleaner>
constexpr bool clear_array(const T& value, const T& clearobj) noexcept {
	T values[N];
	for(auto& i : values) i = value;

	Cleaner().process<CleanerExtra>(values);

	for(const auto& i : values)
		if(i != clearobj)
			return ::llcpp::LL_FALSE;

	return ::llcpp::LL_TRUE;
}

#pragma region ClearArray
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_CLEAR_ARRAY =
	clear_array<
		u32,
		13,
		::llcpp::meta::utils::Cleaner
	>(88, ::llcpp::ZERO_VALUE<u32>);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_clear_array_kat,
	::llcpp::meta::utils::kat::IS_WORKING_CLEAR_ARRAY,
	"'Clear array'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region ClearArrayObj
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_CLEAR_ARRAY_OBJ =
	clear_array<
		TestObj,
		13,
		::llcpp::meta::utils::Cleaner
	>(DEFAULT_VALUE, CLEAR_VALUE);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_clear_array_obj_kat,
	::llcpp::meta::utils::kat::IS_WORKING_CLEAR_ARRAY_OBJ,
	"'Clear array obj'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region InvalidateArray
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_INVALIDATE_ARRAY =
	clear_array<
		u32,
		13,
		::llcpp::meta::utils::Invalidator,
		TestObj
	>(99, u32(-1));

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_invalidate_array_kat,
	::llcpp::meta::utils::kat::IS_WORKING_INVALIDATE_ARRAY,
	"'Invalidate array'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region InvalidateArrayObj
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_INVALIDATE_ARRAY_OBJ =
	clear_array<
		TestObj,
		13,
		::llcpp::meta::utils::Invalidator,
		TestObj
	>(DEFAULT_VALUE, INVALIDATE_VALUE);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_clear_array_obj_kat,
	::llcpp::meta::utils::kat::IS_WORKING_INVALIDATE_ARRAY_OBJ,
	"'Clear array obj'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion

__LL_NODISCARD__ constexpr ::llcpp::string generic_functions_kat() noexcept {
	::llcpp::string result = ::llcpp::meta::utils::kat::is_working_clear_array_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_clear_array_obj_kat();
	if(result) return result;

	result = ::llcpp::meta::utils::kat::is_working_invalidate_array_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_clear_array_obj_kat();
	if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::utils::kat::generic_functions_kat() == LL_NULLPTR, "GenericFunctions KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_GENERICFUNCTIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
