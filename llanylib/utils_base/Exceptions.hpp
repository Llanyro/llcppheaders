//////////////////////////////////////////////
//	Exceptions.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_EXCEPTIONS_INCOMPLETE_HPP_)
	#if LLANYLIB_EXCEPTIONS_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_EXCEPTIONS_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Exceptions.hpp(incomplete) version error!"
		#else
			#error "Exceptions.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_EXCEPTIONS_INCOMPLETE_MAYOR_ || LLANYLIB_EXCEPTIONS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_EXCEPTIONS_INCOMPLETE_HPP_)
	#define LLANYLIB_EXCEPTIONS_INCOMPLETE_HPP_
	#define LLANYLIB_EXCEPTIONS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_EXCEPTIONS_INCOMPLETE_MINOR_ 0

#include <llanylib/types/Errors.hpp>
#include <llanylib/utils_base/GenericFunctions.hpp>
#include <llanylib/utils_base/list_functions.hpp>

namespace llcpp {
namespace exceptions {

template<usize _N, class _StringType = ::llcpp::string, class _ErrorType = i32>
class ExceptionBuffer;

} // namespace exceptions
} // namespace llcpp

#elif defined(LLANYLIB_EXCEPTIONS_HPP_)
	#if LLANYLIB_EXCEPTIONS_MAYOR_ != 12 || LLANYLIB_EXCEPTIONS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Exceptions.hpp version error!"
		#else
			#error "Exceptions.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_EXCEPTIONS_MAYOR_ || LLANYLIB_EXCEPTIONS_MINOR_

#else
	#define LLANYLIB_EXCEPTIONS_HPP_
	#define LLANYLIB_EXCEPTIONS_MAYOR_ 12
	#define LLANYLIB_EXCEPTIONS_MINOR_ 0


#if defined(LL_LIB_PATHS)
	#include <llanylib/types/Errors.hpp>
	#include <llanylib/utils_base/GenericFunctions.hpp>
	#include <llanylib/utils_base/list_functions.hpp>
#else
	#include "../types/Errors.hpp"
	#include "GenericFunctions.hpp"
	#include "list_functions.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace utils {
namespace __utils__ {

template<class StringType, class ErrorType>
using ExceptionValidTag = ::llcpp::meta::traits::conditional_t<
	::llcpp::meta::utils::is_valid_array_type_all_v<StringType, ErrorType>,
	::llcpp::AlwaysValidTag,
	::llcpp::DummyClass
>;

} // namespace __utils__

// Cluster to store some exceptions functions for its internal arrays
// Also has some utilities used in ExceptionBuffer
template<class _StringType, class _ErrorType>
class ExceptionFunctions : public ::llcpp::AlwaysValidTag {
	#pragma region Types
	public:
		// Class related
		using _MyType				= ExceptionFunctions;

		// Types and enums
		using StringType			= _StringType;
		using ErrorType				= _ErrorType;
		
	#pragma endregion
	#pragma region Constructors
	public:
		DEFAULT_RULE_OF_6_CLEAR(ExceptionFunctions);
	
	#pragma endregion
	#pragma region CleanFunctions

		constexpr void __cleaner(StringType*& val) const noexcept {
			__LL_FUNCTION_INIT__;
			val = ::llcpp::NULL_VALUE<StringType>;
		}
		constexpr void __cleaner(ErrorType*& val) const noexcept {
			__LL_FUNCTION_INIT__;
			val = ::llcpp::NULL_VALUE<ErrorType>;
		}

		template<::llcpp::usize N>
		constexpr void __cleaner(ErrorType (&val)[N]) const noexcept {
			__LL_FUNCTION_INIT__;
			ErrorType* aux = val;
			for(const ErrorType* end = aux + N; aux < end; ++aux)
				this->__cleaner(*aux);
		}
		template<::llcpp::usize N>
		constexpr void __cleaner(StringType (&val)[N]) const noexcept {
			__LL_FUNCTION_INIT__;
			StringType* aux = val;
			for(const StringType* end = aux + N; aux < end; ++aux)
				this->__cleaner(*aux);
		}

	#pragma endregion
	#pragma region InvalidateFunctions
	public:
		constexpr void __invalidate(StringType*& val) const noexcept {
			__LL_FUNCTION_INIT__;
			val = ::llcpp::NULL_VALUE<StringType>;
		}
		constexpr void __invalidate(ErrorType*& val) const noexcept {
			__LL_FUNCTION_INIT__;
			val = ::llcpp::NULL_VALUE<ErrorType>;
		}

		template<::llcpp::usize N>
		constexpr void __invalidate(ErrorType (&val)[N]) const noexcept {
			__LL_FUNCTION_INIT__;
			ErrorType* aux = val;
			for(const ErrorType* end = aux + N; aux < end; ++aux)
				this->__invalidate(*aux);
		}
		template<::llcpp::usize N>
		constexpr void __invalidate(StringType (&val)[N]) const noexcept {
			__LL_FUNCTION_INIT__;
			StringType* aux = val;
			for(const StringType* end = aux + N; aux < end; ++aux)
				this->__invalidate(*aux);
		}

	#pragma endregion
};

template<
	// Number of elements that buffer can store
	usize _N,

	// Array type to store string types
	class _StringTypeArray		= ::llcpp::Arrayo<::llcpp::string, _N> ,

	// Array type to store error types
	class _ErrorTypeArray		= ::llcpp::Arrayo<i32, _N>,

	// Type with functionality used to invalidate/clear string/error types
	class _InvalidatorCleaner	=
		::llcpp::meta::utils::ExceptionFunctions<
			typename _StringTypeArray::value_type,
			typename _ErrorTypeArray::value_type
		>
>
class ExceptionBuffer :
	public ::llcpp::meta::utils::__utils__::ExceptionValidTag<
		typename _StringTypeArray::value_type,
		typename _ErrorTypeArray::value_type
	>
{
	#pragma region Types
	public:
		// Class related
		using _MyType				= ExceptionBuffer;
		using ValidTag				= ::llcpp::meta::utils::__utils__::ExceptionValidTag<
			typename _StringTypeArray::value_type,
			typename _ErrorTypeArray::value_type
		>;

		// Types and enums
		using StringTypeArray		= _StringTypeArray;
		using ErrorTypeArray		= _ErrorTypeArray;
		using StringType			= typename StringTypeArray::value_type;
		using ErrorType				= typename ErrorTypeArray::value_type;
		using PopData				= ::llcpp::meta::pair<StringType, ErrorType>;
		using InvalidatorCleaner	= _InvalidatorCleaner;
		using StringIterator		= ::llcpp::meta::utils::array_iterator_t<StringTypeArray>;
		using ErrorIterator			= ::llcpp::meta::utils::array_iterator_t<ErrorTypeArray>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr usize N						= _N;
		static constexpr ll_bool_t VALID_CHECK_NEEDED	= ::std::is_same_v<_MyType::ValidTag, ::llcpp::DummyClass>;

	#pragma endregion
	#pragma region Attributes
	private:
		StringTypeArray	lifo_names;
		ErrorTypeArray	lifo_errors;
		StringIterator	lifo_names_last;
		ErrorIterator	lifo_errors_last;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr ExceptionBuffer() noexcept
			: lifo_names()
			, lifo_errors()
			, lifo_names_last(this->str_begin())
			, lifo_errors_last(this->err_begin())
		{ __LL_FUNCTION_INIT__; }
		constexpr ~ExceptionBuffer() noexcept {
			__LL_FUNCTION_INIT__;
			if constexpr (::llcpp::LL_CLEAR_SECURE)
				this->makeInvalidClear();
			else if constexpr (::llcpp::LL_CLEAR_POINTERS_ON_DESTRUCTION)
				this->makeInvalid();
		}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ExceptionBuffer(const ExceptionBuffer& other) noexcept = delete;
		constexpr ExceptionBuffer& operator=(const ExceptionBuffer& other) noexcept = delete;
		constexpr ExceptionBuffer(ExceptionBuffer&& other) noexcept = delete;
		constexpr ExceptionBuffer& operator=(ExceptionBuffer&& other) noexcept = delete;

		constexpr ExceptionBuffer(const volatile ExceptionBuffer& other) noexcept = delete;
		constexpr ExceptionBuffer& operator=(const volatile ExceptionBuffer& other) noexcept = delete;
		constexpr ExceptionBuffer(volatile ExceptionBuffer&& other) noexcept = delete;
		constexpr ExceptionBuffer& operator=(volatile ExceptionBuffer&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const ExceptionBuffer*() const noexcept {
			__LL_FUNCTION_INIT__;
			return this;
		}
		__LL_NODISCARD__ constexpr explicit operator ExceptionBuffer*() noexcept {
			__LL_FUNCTION_INIT__;
			return this;
		}

		#pragma endregion
		#pragma region ClassFunctions
	protected:
		// Does not include reset
		template<class ExtraCleaner>
		constexpr void clearPriv(const ExtraCleaner& extra) noexcept {
			__LL_FUNCTION_INIT__;
			::llcpp::meta::utils::Cleaner cleaner;
			(void)cleaner.process(this->lifo_names, extra);
			(void)cleaner.process(this->lifo_errors, extra);
		}

		#pragma region StrFunctions
		__LL_NODISCARD__ constexpr const StringIterator str_begin() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_begin<const StringIterator>(this->lifo_names);
		}
		__LL_NODISCARD__ constexpr StringIterator str_begin() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_begin<StringIterator>(this->lifo_names);
		}
		__LL_NODISCARD__ constexpr const StringIterator str_end() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_end<const StringIterator>(this->lifo_names);
		}
		__LL_NODISCARD__ constexpr StringIterator str_end() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_end<StringIterator>(this->lifo_names);
		}
		__LL_NODISCARD__ constexpr const StringIterator str_last() noexcept {
			return this->lifo_names_last;
		}
		__LL_NODISCARD__ constexpr StringIterator str_end() noexcept {
			__LL_FUNCTION_INIT__;
			return this->lifo_names_last;
		}
		
		#pragma endregion
		#pragma region ErrorFunctions
		__LL_NODISCARD__ constexpr const ErrorIterator err_begin() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_begin<const ErrorIterator>(this->lifo_errors);
		}
		__LL_NODISCARD__ constexpr ErrorIterator err_begin() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_begin<ErrorIterator>(this->lifo_errors);
		}
		__LL_NODISCARD__ constexpr const ErrorIterator err_end() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_end<const ErrorIterator>(this->lifo_errors);
		}
		__LL_NODISCARD__ constexpr ErrorIterator err_end() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_end<ErrorIterator>(this->lifo_errors);
		}
		__LL_NODISCARD__ constexpr const ErrorIterator err_last() noexcept {
			return this->lifo_errors_last;
		}
		__LL_NODISCARD__ constexpr ErrorIterator err_end() noexcept {
			__LL_FUNCTION_INIT__;
			return this->lifo_errors_last;
		}

		#pragma endregion
		#pragma region ValidFunctions
	public:
		// Returns ValidType of each type
		// If any type is AlwaysValid, and other we need to ask, will return ValidType or second type
		// If we need to ask both types, will return common ValidType or ValidType::Error if ValidType does not match
		// This function cannot be called if both types are valid types
		__LL_NODISCARD__ constexpr ::llcpp::misc::ValidType validationType() const noexcept requires(VALID_CHECK_NEEDED) {
			__LL_FUNCTION_INIT__;
			constexpr auto IS_ERR_VALID = ::llcpp::meta::utils::is_valid_array_type_v<ErrorTypeArray>;
			constexpr auto IS_STR_VALID = ::llcpp::meta::utils::is_valid_array_type_v<StringTypeArray>;
			if constexpr (!IS_ERR_VALID && IS_STR_VALID)
				return this->lifo_errors.validationType();
			else if constexpr (IS_ERR_VALID && !IS_STR_VALID)
				return this->lifo_names.validationType();
			else {
				auto err_val = this->lifo_errors.validationType();
				return
					err_val == this->lifo_names.validationType()
					? err_val
					: ::llcpp::misc::ValidType::Error;
			}
		}
		// Reset buffers pointers
		// Fifo will be reset to 0
		constexpr void reset() noexcept {
			__LL_FUNCTION_INIT__;
			this->lifo_names_last	= this->str_begin();
			this->lifo_errors_last	= this->err_begin();
		}
		// Clears buffers data and reset class
		template<class ExtraCleaner = _MyType::InvalidatorCleaner>
		constexpr void clear() noexcept {
			__LL_FUNCTION_INIT__;
			ExtraCleaner extra;
			this->clear(extra);
		}
		// Clears buffers data and reset class with a provided class
		template<class ExtraCleaner = _MyType::InvalidatorCleaner>
		constexpr void clear(const ExtraCleaner& extra) noexcept {
			__LL_FUNCTION_INIT__;
			this->clearPriv(extra);
			this->reset();
		}
		// Invalidates iterators of fifo
		template<class ExtraInvalidator = _MyType::InvalidatorCleaner>
		constexpr void makeInvalid() noexcept {
			__LL_FUNCTION_INIT__;
			ExtraInvalidator extra;
			this->makeInvalid(extra);
		}
		// Invalidates iterators of fifo with a provided class
		template<class ExtraInvalidator = _MyType::InvalidatorCleaner>
		constexpr void makeInvalid(const ExtraInvalidator& extra) noexcept {
			__LL_FUNCTION_INIT__;
			::llcpp::meta::utils::Invalidator invalidator;
			(void)invalidator.process(this->err_last(), extra);
			(void)invalidator.process(this->str_last(), extra);
		}
		// Invalidates iterators and objects of fifo
		template<class ExtraInvalidatorCleaner = _MyType::InvalidatorCleaner>
		constexpr void makeInvalidClear() noexcept {
			__LL_FUNCTION_INIT__;
			ExtraInvalidatorCleaner extra;
			this->makeInvalidClear(extra);
		}
		// Invalidates iterators and objects of fifo
		template<class ExtraInvalidatorCleaner = _MyType::InvalidatorCleaner>
		constexpr void makeInvalidClear(const ExtraInvalidatorCleaner& extra) noexcept {
			__LL_FUNCTION_INIT__;
			this->clearPriv(extra);
			this->makeInvalid(extra);
		}

		#pragma endregion
		#pragma region ListFunctions
	public:

		// Max elements can be stored
		__LL_NODISCARD__ constexpr usize max_size() const noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_size(this->lifo_names);
		}
		// Number of stored elements
		__LL_NODISCARD__ constexpr usize size() const noexcept {
			__LL_FUNCTION_INIT__;
			return static_cast<usize>(this->str_last() - this->str_begin());
		}
		// Number of stored elements
		__LL_NODISCARD__ constexpr usize lenght() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->size();
		}
		// Number of stored elements
		__LL_NODISCARD__ constexpr usize count() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->size();
		}

		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->str_last() == this->str_begin();
		}
		__LL_NODISCARD__ constexpr ll_bool_t full() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->str_last() >= this->str_end();
		}

		__LL_NODISCARD__ constexpr ll_bool_t push(StringType s, ErrorType e) noexcept {
			__LL_FUNCTION_INIT__;
			if (this->full()) {
				if constexpr (::llcpp::LL_DEBUG_ERROR)
					__debug_error_exceptions_full("Exceptions list is full! You may fix some error or increase ExceptionBuffer");
				return ::llcpp::LL_FALSE;
			}
			*(this->lifo_names_last++) = s;
			*(this->lifo_errors_last++) = e;
			return ::llcpp::LL_TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t push(StringType s, ::llcpp::misc::Errors e) noexcept {
			__LL_FUNCTION_INIT__;
			return this->push(s, static_cast<ErrorType>(e));
		}
		__LL_NODISCARD__ constexpr ll_bool_t pop(PopData& data) noexcept {
			__LL_FUNCTION_INIT__;
			if (this->empty()) {
				if constexpr (::llcpp::LL_DEBUG_ERROR)
					__debug_error_exceptions_empty("Exceptions list is empty! Do not pop with empty stack!");
				return ::llcpp::LL_FALSE;
			}
			data = { *(--this->lifo_names_last), *(--this->lifo_errors_last) };
			return ::llcpp::LL_TRUE;
		}

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

/*template<usize N, usize _N>
constexpr void addExceptions(::llcpp::exceptions::ExceptionBuffer<_N>& buff) noexcept {
	using ExceptType = decltype(buff);
	buff.push(ExceptType::StringType(), ExceptType::ErrorType());
	if constexpr (N > 0) ::llcpp::exceptions::addExceptions<N - 1>(buff);
}

template<usize N, usize _N>
constexpr usize getExceptions() noexcept {
	::llcpp::exceptions::ExceptionBuffer<_N> buff;
	::llcpp::exceptions::addExceptions<N>(buff);
	return buff.size();
}

static_assert(::llcpp::exceptions::getExceptions<5, 10>() == 5, "Exception error");*/

#if __LL_EXCEPTIONS == 1

static thread_local ::llcpp::exceptions::ExceptionBuffer<10, string, i32> ex;
#define ll_exceptions ::llcpp::exceptions::ex

#define LOG_EXCEPTION(err) ll_exceptions.push(__LL_STRING_PREFIX __LL_FUNCNAME__, err)
#define LOG_EXCEPTION_TAG(tag, err) ll_exceptions.push(__LL_STRING_PREFIX __LL_FUNCNAME__ " [ " tag " ]", err)

#else
	#define LOG_EXCEPTION(err) ::llcpp::LL_IGNORE(err)
	#define LOG_EXCEPTION_TAG(tag, err) ::llcpp::LL_IGNORE(tag, err)
#endif // __LL_EXCEPTIONS == 1

#if __LL_INCLUDE_KATS == 1
namespace kat {

using ExceptionKat	= ::llcpp::meta::utils::ExceptionBuffer<10>;

#pragma region Begin

template<usize N>
__LL_NODISCARD__ constexpr ::llcpp::meta::pair<usize, usize> push_elements() noexcept {
	ExceptionKat list;
	
	for(usize i{}; i < N; ++i)
		list.push("Dodod", -1);

	return { list.size(), list.max_size() };
}

__LL_VAR_INLINE__ constexpr auto PUSH_ELEMENTS_RESULT = ::llcpp::meta::utils::kat::push_elements<5>();

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_PUSH_ELEMENTS =
	   PUSH_ELEMENTS_RESULT.first == 5
	&& PUSH_ELEMENTS_RESULT.second == 10;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_push_elements_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_OBJ2_BEGIN,
	"'Push elements'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion

__LL_NODISCARD__ constexpr ::llcpp::string list_functions_kats() noexcept {
	::llcpp::string result = ::llcpp::meta::utils::kat::is_working_get_push_elements_kat();
	if(result) return result;
	//result = ::llcpp::meta::utils::kat::is_working_get_array_obj_begin_kat();
	//if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::utils::kat::list_functions_kats() == LL_NULLPTR, "utils::list_functions KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS


} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXCEPTIONS_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_EXCEPTIONS_EXTRA_HPP_)
		#if LLANYLIB_EXCEPTIONS_EXTRA_MAYOR_ != 12 || LLANYLIB_EXCEPTIONS_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "Exceptions.hpp(extra) version error!"
			#else
				#error "Exceptions.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_EXCEPTIONS_EXTRA_MAYOR_ || LLANYLIB_EXCEPTIONS_EXTRA_MINOR_

	#else
		#define LLANYLIB_EXCEPTIONS_EXTRA_HPP_
		#define LLANYLIB_EXCEPTIONS_EXTRA_MAYOR_ 12
		#define LLANYLIB_EXCEPTIONS_EXTRA_MINOR_ 0

namespace llcpp {
namespace exceptions {

template<
	// Number of elements that buffer can store
	usize N,

	// Error string type to store
	class StringType			= ::llcpp::string,

	// Value error to store
	class ErrorType				= i32,

	// Type with functionality used to invalidate/clear string/error types
	class InvalidatorCleaner	= ::llcpp::meta::utils::ExceptionFunctions<StringType, ErrorType>
>
using ExceptionBufferArrayo		= ::llcpp::meta::utils::ExceptionBuffer<N, ::llcpp::Arrayo<StringType, N>, ::llcpp::Arrayo<ErrorType, N>, InvalidatorCleaner>;

} // namespace exceptions
} // namespace llcpp

	#endif // LLANYLIB_EXCEPTIONS_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
