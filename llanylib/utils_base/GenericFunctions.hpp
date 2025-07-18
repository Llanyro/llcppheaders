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
	//#include <llanylib/traits_base/parameter_pack.hpp>
	#include <llanylib/concepts/GenericFunctions.hpp>
#else
	//#include "../traits_base/parameter_pack.hpp"
	#include "../concepts/GenericFunctions.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace utils {

template<::llcpp::meta::utils::GenericMode _MODE = ::llcpp::meta::utils::GenericMode::Cleaner>
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
	//#include <llanylib/traits_base/parameter_pack.hpp>
	#include <llanylib/concepts/GenericFunctions.hpp>
#else
	//#include "../traits_base/parameter_pack.hpp"
	#include "../concepts/GenericFunctions.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace utils {

enum class GenericMode {
	Cleaner,
	Invalidator,
	Copy,
	Move
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
		static constexpr ll_bool_t IS_COPYATOR				= _MODE == GenericModeType::Copy;
		static constexpr ll_bool_t IS_MOVEATOR				= _MODE == GenericModeType::Move;
		template<class T>
		static constexpr ll_bool_t IS_CLEANER_NO_POINTER	= IS_CLEANER && !::std::is_pointer_v<T>;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		LL_DEFAULT_RULE_OF_6_CLEAR(GenericFunctions);
	
		#pragma endregion
		#pragma region Generic
	private:
		template<class ExternalFunctions, class... Args>
		static constexpr ll_bool_t IS_PROCESS_EXTERNAL_VALID =
			   (IS_CLEANER && ::llcpp::meta::concepts::signature::HasCleaner<const ExternalFunctions, void, Args...>)
			|| (IS_INVALIDATOR && ::llcpp::meta::concepts::signature::HasInvalidator<const ExternalFunctions, void, Args...>)
			|| (IS_COPYATOR && ::llcpp::meta::concepts::signature::HasCopyator<const ExternalFunctions, void, Args...>)
			|| (IS_MOVEATOR && ::llcpp::meta::concepts::signature::HasMoveator<const ExternalFunctions, void, Args...>);

		template<class ExternalFunctions = _MyType, class... Args>
		constexpr void processExternal(const ExternalFunctions& external, Args&... args) const noexcept {
			__LL_FUNCTION_INIT__;

			// If external has a way to clear object
			if constexpr (IS_CLEANER && ::llcpp::meta::concepts::signature::HasCleaner<ExternalFunctions, void, Args...>)
				external.__cleaner(::std::forward<Args&>(args)...);
			// If external has a way to invalidate object
			else if constexpr (IS_INVALIDATOR && ::llcpp::meta::concepts::signature::HasInvalidator<ExternalFunctions, void, Args...>)
				external.__invalidate(::std::forward<Args&>(args)...);
			// If external has a way to copy object
			else if constexpr (IS_COPYATOR && ::llcpp::meta::concepts::signature::HasCopyator<ExternalFunctions, void, Args...>)
				external.__copy(::std::forward<Args&>(args)...);
			// If external has a way to move object
			else if constexpr (IS_MOVEATOR && ::llcpp::meta::concepts::signature::HasMoveator<ExternalFunctions, void, Args...>)
				external.__move(::std::forward<Args&>(args)...);
		}

	public:
		/*template<class ExternalFunctions = _MyType, class... Args>
		constexpr void process(Args&... args) const noexcept {
			__LL_FUNCTION_INIT__;
			// If this is this class type, we will use this instance as main source
			if constexpr (::std::is_same_v<ExternalFunctions, _MyType>)
				this->process(*this, ::std::forward<Args&>(args)...);
			// If this is not this class type, we need a source of it
			// If source not provided, we need to instance the object
			else {
				static_assert(::std::is_nothrow_default_constructible_v<ExternalFunctions>,
					"ExternalFunctions type needs to be a noexcept default contructible!");
				ExternalFunctions external;
				this->process(external, ::std::forward<Args&>(args)...);
			}
		}*/
		template<class ExternalFunctions = _MyType, class T, class... Args>
		constexpr void process(const ExternalFunctions& external, T& obj, Args&... args) const noexcept {
			__LL_FUNCTION_INIT__;
			// Process all at same time
			if constexpr (_MyType::IS_PROCESS_EXTERNAL_VALID<ExternalFunctions, T, Args...>)
				this->processExternal(external, obj, ::std::forward<Args&>(args)...);
			// Process one by one
			else {
				this->process(external, obj);
				this->process(external, ::std::forward<Args&>(args)...);
			}
		}
		template<class ExternalFunctions = _MyType, class T>
		constexpr void process(const ExternalFunctions& external, T& obj) const noexcept {
			__LL_FUNCTION_INIT__;
			if constexpr (_MyType::IS_PROCESS_EXTERNAL_VALID<ExternalFunctions, T>)
				this->processExternal(external, obj);
			// A pointer is not recommended to clear unless you know what are you doing
			else if constexpr (::std::is_pointer_v<T>) {
#if __LL_CLEAR_POINTER_AS == 0
				// If is a pointer, we dont know how to clear it
				static_assert(!::std::is_pointer_v<T>,
					"Cannot operate a pointer. Is it an array or just a pointer (?)."
					"If its a pointer just deference it."
					"And, if its an array, include the end."
				);
#elif __LL_CLEAR_POINTER_AS == 1
				// User wants to deference and clear
				this->process(external, *obj);
				return;
#endif // __LL_CLEAR_POINTER_AS
			}
			// If is an array and we dont know how to clear it, we tell user
			else if constexpr (::std::is_array_v<T>)
				this->processArray(external, obj, obj + ::llcpp::array_size<T>);
			// If is a class, we try specific thigs
			else if constexpr (::std::is_class_v<T>) {
				// If is class and has own clear, we use it
				if constexpr (IS_CLEANER && ::llcpp::meta::concepts::signature::HasClear<T>)
					obj.clear();
				// If is class and has own invalidator, we use it
				else if constexpr (IS_INVALIDATOR && ::llcpp::meta::concepts::signature::HasMakeInvalid<T>)
					obj.makeInvalid();
				
				// [TODO] [TOCHECK]
				//// Classic copy needs 2 args
				//else if constexpr (Pack::SIZE >= 2 && IS_COPYATOR && ::std::is_assignable_v<Pack::T, typename Pack::Next::T>)
				//	args = ::std::forward<typename Pack::Next::T>(::llcpp::meta::traits::getNextArgument<1>(::std::forward<Pack::T>(args)...));
				//// Classic move needs 2 args
				//else if constexpr (Pack::SIZE >= 2 && IS_MOVEATOR && ::std::is_assignable_v<Pack::T, typename Pack::Next::T>)
				//	args = ::std::forward<typename Pack::Next::T>(::llcpp::meta::traits::getNextArgument<1>(::std::forward<Pack::T>(args)...));
				
				// If object is list type, and we can iterate over them
				else if constexpr (::llcpp::meta::concepts::signature::SameTypeBeginEnd<T>)
					this->processArray(external, obj.begin(), obj.end());
#if defined(__LL_BUILTIN_POINTER_CHECK)
				else if constexpr (!::llcpp::meta::traits::HasPointerAttribute<T>) {
					// ????
					static_assert(false, "Not yet implemented");
				}
#endif
				// If not, we use default, if possible
				else if constexpr (IS_CLEANER && ::llcpp::meta::concepts::signature::HasCopyAssignable<T>)
					obj = ::llcpp::ZERO_VALUE<T>;
				// If we cannot use default clears, we cant do anything
				else {
					static_assert(!IS_CLEANER || ::llcpp::meta::concepts::signature::HasClear<T>,
						"clear() or operator=() is needed to clear this object");
					static_assert(!IS_INVALIDATOR || ::llcpp::meta::concepts::signature::HasMakeInvalid<T>,
						"makeInvalid() is needed to invalidate this object");
				}
			}
			// If there is no suitable cleaner, we use this class as default
			else if constexpr (!::std::is_same_v<ExternalFunctions, _MyType>)
				this->process(*this, obj);
			else {
				static_assert(!::std::is_same_v<ExternalFunctions, _MyType>,
					"No suitable process for this type!");
			}
		}

		template<class ExternalFunctions = _MyType, class Iterator, class IteratorEnd>
		constexpr auto processArray(const ExternalFunctions& external, Iterator begin, IteratorEnd end) const noexcept {
			__LL_FUNCTION_INIT__;
			if constexpr (::std::is_pointer_v<Iterator> && ::std::is_pointer_v<IteratorEnd>)
				for(; begin < end; ++begin)
					this->process(external, *begin);
			else for(; begin != end; ++begin)
				this->process(external, *begin);
		}

		#pragma endregion
		#pragma region Default
	public:
		// Clear only objects/primitives that can be copied assignable
		template<class T>
			requires IS_CLEANER_NO_POINTER<T> && ::llcpp::meta::concepts::signature::HasCopyAssignable<T>
		constexpr void __cleaner(T& obj) const noexcept {
			__LL_FUNCTION_INIT__;
			obj = ::std::forward<const T&>(::llcpp::ZERO_VALUE<T>);
		}
		template<class T>
			requires IS_CLEANER_NO_POINTER<T>
		constexpr void __cleaner(T* begin, const T* end) const noexcept {
			__LL_FUNCTION_INIT__;
			T* aux = begin;
			for(; aux < end; ++aux)
				this->process(*aux, *this);
		}
		template<class T, class U>
			requires IS_COPYATOR && ::llcpp::meta::concepts::signature::HasCopyAssignable<T>
		constexpr void __copy(T& obj, U& other) const noexcept {
			__LL_FUNCTION_INIT__;
			obj = ::std::forward<const U&>(other);
		}
		template<class T, class U>
			requires IS_MOVEATOR && ::llcpp::meta::concepts::signature::HasCopyAssignable<T>
		constexpr void __move(T& obj, U&& other) const noexcept {
			__LL_FUNCTION_INIT__;
			obj = ::std::forward<U&&>(other);
		}

		#pragma endregion

	#pragma endregion
};

using Cleaner		= ::llcpp::meta::utils::GenericFunctions<::llcpp::meta::utils::GenericMode::Cleaner>;
using Invalidator	= ::llcpp::meta::utils::GenericFunctions<::llcpp::meta::utils::GenericMode::Invalidator>;
using Copyator		= ::llcpp::meta::utils::GenericFunctions<::llcpp::meta::utils::GenericMode::Copy>;
using Moveator		= ::llcpp::meta::utils::GenericFunctions<::llcpp::meta::utils::GenericMode::Move>;

// Invalidator base for primitives, pointers and classes that invalid type is its default contructor
template<class _T>
class PrimitiveInvalidator : public ::llcpp::AlwaysValidTag {
	#pragma region Types
	public:
		// Class related
		using _MyType				= PrimitiveInvalidator;

		// Types and enums
		using T						= _T;
		using type					= T;
		using value_type			= T;

	#pragma endregion
	#pragma region Constructors
	public:
		LL_DEFAULT_RULE_OF_6_CLEAR(PrimitiveInvalidator);
	
	#pragma endregion
	#pragma region CleanFunctions
		constexpr void __cleaner(T& val) const noexcept {
			__LL_FUNCTION_INIT__;
			val = ::llcpp::ZERO_VALUE<T>;
		}
		constexpr void __invalidate(T& val) const noexcept {
			__LL_FUNCTION_INIT__;
			val = ::llcpp::ZERO_VALUE<T>;
		}

	#pragma endregion
};

#if __LL_INCLUDE_KATS == 1
} // namespace utils
} // namespace meta
} // namespace llcpp

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/Arrayo.hpp>
#else
	#include "../types/Arrayo.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace utils {
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

__LL_VAR_INLINE__ constexpr auto PRIMITIVE_DEFAULT_VALUE	= 88;
__LL_VAR_INLINE__ constexpr auto PRIMITIVE_CLEAR_VALUE		= ::llcpp::ZERO_VALUE<u32>;
__LL_VAR_INLINE__ constexpr auto PRIMITIVE_INVALIDATE_VALUE	= u32(-1);

template<class T, usize N, class Cleaner, class CleanerExtra = Cleaner>
constexpr bool clear_array(const T& value, const T& clearobj) noexcept {
	T values[N];
	for(auto& i : values) i = value;

	CleanerExtra ex;
	Cleaner().process(ex, values);

	for(const auto& i : values)
		if(i != clearobj)
			return ::llcpp::LL_FALSE;

	return ::llcpp::LL_TRUE;
}
template<class T, usize N, class Cleaner, class CleanerExtra = Cleaner>
constexpr bool clear_arrayo(const T& value, const T& clearobj) noexcept {
	::llcpp::Arrayo<T, N> values;
	for(auto& i : values) i = value;

	CleanerExtra ex;
	Cleaner().process(ex, values);

	for(const auto& i : values)
		if(i != clearobj)
			return ::llcpp::LL_FALSE;

	return ::llcpp::LL_TRUE;
}

#pragma region ClearArray
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_CLEAR_ARRAY =
	clear_array<u32, 13, ::llcpp::meta::utils::Cleaner>(
		::llcpp::meta::utils::kat::PRIMITIVE_DEFAULT_VALUE,
		::llcpp::meta::utils::kat::PRIMITIVE_CLEAR_VALUE
	);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_clear_array_kat,
	::llcpp::meta::utils::kat::IS_WORKING_CLEAR_ARRAY,
	"'Clear array'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region ClearArrayObj
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_CLEAR_ARRAY_OBJ =
	clear_array<::llcpp::meta::utils::kat::TestObj, 12, ::llcpp::meta::utils::Cleaner>(
		::llcpp::meta::utils::kat::DEFAULT_VALUE,
		::llcpp::meta::utils::kat::CLEAR_VALUE
	);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_clear_array_obj_kat,
	::llcpp::meta::utils::kat::IS_WORKING_CLEAR_ARRAY_OBJ,
	"'Clear array obj'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region ClearArrayo
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_CLEAR_ARRAYO =
	clear_arrayo<u32, 57, ::llcpp::meta::utils::Cleaner>(
		::llcpp::meta::utils::kat::PRIMITIVE_DEFAULT_VALUE,
		::llcpp::meta::utils::kat::PRIMITIVE_CLEAR_VALUE
	);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_clear_arrayo_kat,
	::llcpp::meta::utils::kat::IS_WORKING_CLEAR_ARRAYO,
	"'Clear arrayo'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region InvalidateArray
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_INVALIDATE_ARRAY =
	clear_array<u32, 73, ::llcpp::meta::utils::Invalidator, ::llcpp::meta::utils::kat::TestObj>(
		::llcpp::meta::utils::kat::PRIMITIVE_DEFAULT_VALUE,
		::llcpp::meta::utils::kat::PRIMITIVE_INVALIDATE_VALUE
	);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_invalidate_array_kat,
	::llcpp::meta::utils::kat::IS_WORKING_INVALIDATE_ARRAY,
	"'Invalidate array'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region InvalidateArrayObj
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_INVALIDATE_ARRAY_OBJ =
	clear_array<::llcpp::meta::utils::kat::TestObj, 800, ::llcpp::meta::utils::Invalidator, ::llcpp::meta::utils::kat::TestObj>(
		::llcpp::meta::utils::kat::DEFAULT_VALUE,
		::llcpp::meta::utils::kat::INVALIDATE_VALUE
	);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_invalidate_array_obj_kat,
	::llcpp::meta::utils::kat::IS_WORKING_INVALIDATE_ARRAY_OBJ,
	"'Clear array obj'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region InvalidateArrayo
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_INVALIDATE_ARRAYO =
	clear_arrayo<u32, 5317, ::llcpp::meta::utils::Invalidator, ::llcpp::meta::utils::kat::TestObj>(
		::llcpp::meta::utils::kat::PRIMITIVE_DEFAULT_VALUE,
		::llcpp::meta::utils::kat::PRIMITIVE_INVALIDATE_VALUE
	);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_invalidate_arrayo_kat,
	::llcpp::meta::utils::kat::IS_WORKING_INVALIDATE_ARRAYO,
	"'Clear arrayo'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region CopyTest
constexpr ll_bool_t copy_trivial() noexcept {
	i32 value = 333;
	u32 copy{};

	Copyator ex;
	ex.process(ex, value, copy);
	
	return value == copy;
}

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_COPY_TRIVIAL =
	::llcpp::meta::utils::kat::copy_trivial();

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_copy_trivial_kat,
	::llcpp::meta::utils::kat::IS_WORKING_COPY_TRIVIAL,
	"'Copy trivial'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region MoveTest
constexpr ll_bool_t move_trivial() noexcept {
	i32 value = 333;
	u32 copy{};

	Moveator ex;
	ex.process(ex, value, copy);

	return value == copy;
}

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_MOVE_TRIVIAL =
	::llcpp::meta::utils::kat::move_trivial();

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_move_trivial_kat,
	::llcpp::meta::utils::kat::IS_WORKING_MOVE_TRIVIAL,
	"'Move trivial'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion


__LL_NODISCARD__ constexpr ::llcpp::string generic_functions_kat() noexcept {
	::llcpp::string result = ::llcpp::meta::utils::kat::is_working_clear_array_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_clear_array_obj_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_clear_arrayo_kat();
	if(result) return result;

	result = ::llcpp::meta::utils::kat::is_working_invalidate_array_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_invalidate_array_obj_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_invalidate_arrayo_kat();
	if(result) return result;

	result = ::llcpp::meta::utils::kat::is_working_copy_trivial_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_move_trivial_kat();
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
