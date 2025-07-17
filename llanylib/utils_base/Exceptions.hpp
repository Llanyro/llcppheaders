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
	//#include <llanylib/types/Errors.hpp>
	//#include <llanylib/types/Arrayo.hpp>
	#include <llanylib/utils_base/list_functions.hpp>
	#include <llanylib/utils_base/iterator_functions.hpp>
	#include <llanylib/utils_base/GenericFunctions.hpp>
#else
	//#include "../types/Errors.hpp"
	//#include "../types/Arrayo.hpp"
	#include "list_functions.hpp"
	#include "iterator_functions.hpp"
	#include "GenericFunctions.hpp"
#endif // LL_LIB_PATHS

namespace llcpp {
namespace meta {
namespace utils {

template<usize _N, class _StringTypeArray, class _ErrorTypeArray, class _InvalidatorCleaner, class _ValidationTag>
class ExceptionContainer : public _ValidationTag {
	#pragma region Types
	public:
		// Class related
		using _MyType				= ExceptionContainer;
		using ValidTag				= _ValidationTag;

		// Types and enums
		using StringTypeArray		= _StringTypeArray;
		using ErrorTypeArray		= _ErrorTypeArray;
		using InvalidatorCleaner	= _InvalidatorCleaner;
		using StringType			= ::llcpp::meta::traits::array_type_t<StringTypeArray>;
		using ErrorType				= ::llcpp::meta::traits::array_type_t<ErrorTypeArray>;
		using StringIterator		= ::llcpp::meta::utils::array_iterator_t<StringTypeArray>;
		using ErrorIterator			= ::llcpp::meta::utils::array_iterator_t<ErrorTypeArray>;
		using StringConstIterator	= ::llcpp::meta::utils::array_const_iterator_t<StringTypeArray>;
		using ErrorConstIterator	= ::llcpp::meta::utils::array_const_iterator_t<ErrorTypeArray>;
		using PopData				= ::llcpp::meta::pair<StringType, ErrorType>;

		template<class Cleaner, class Invalidator>
		using InvalidatorAndCleanerContainer	= ::llcpp::meta::traits::conditional_t<
			::std::is_same_v<Cleaner, Invalidator>,
			const Cleaner&,
			::llcpp::meta::pair<const Cleaner&, const Invalidator&>
		>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr usize N						= _N;
		static constexpr ll_bool_t VALID_CHECK_NEEDED	= ::std::is_same_v<_MyType::ValidTag, ::llcpp::DummyClass>;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::llcpp::meta::traits::is_empty_type_v<StringType>,
			"StringTypeArray must be an C static array style or an array object like Arrayo");
		static_assert(::llcpp::meta::traits::is_empty_type_v<ErrorType>,
			"ErrorTypeArray must be an C static array style or an array object like Arrayo");
		static_assert(::llcpp::meta::traits::is_empty_type_v<StringIterator>,
			"StringIterator must be an iterator of provided array");
		static_assert(::llcpp::meta::traits::is_empty_type_v<ErrorIterator>,
			"ErrorIterator must be an iterator of provided array");
		static_assert(::llcpp::meta::traits::is_valid_tag_type_v<ValidTag>,
			"Tag type is not a valid validation tag type!");

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
		constexpr ExceptionContainer() noexcept
			: lifo_names()
			, lifo_errors()
			, lifo_names_last(this->str_begin())	// Point to first element in strings array
			, lifo_errors_last(this->err_begin())	// Point to first element in errors array
		{ __LL_FUNCTION_INIT__; }
		constexpr ~ExceptionContainer() noexcept {
			__LL_FUNCTION_INIT__;
			if constexpr (::llcpp::LL_CLEAR_SECURE)
				this->makeInvalidClear();
			else if constexpr (::llcpp::LL_CLEAR_POINTERS_ON_DESTRUCTION)
				this->makeInvalid();
		}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ExceptionContainer(const ExceptionContainer& other) noexcept = delete;
		constexpr ExceptionContainer& operator=(const ExceptionContainer& other) noexcept = delete;
		constexpr ExceptionContainer(ExceptionContainer&& other) noexcept = delete;
		constexpr ExceptionContainer& operator=(ExceptionContainer&& other) noexcept = delete;

		constexpr ExceptionContainer(const volatile ExceptionContainer& other) noexcept = delete;
		constexpr ExceptionContainer& operator=(const volatile ExceptionContainer& other) noexcept = delete;
		constexpr ExceptionContainer(volatile ExceptionContainer&& other) noexcept = delete;
		constexpr ExceptionContainer& operator=(volatile ExceptionContainer&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const ExceptionContainer*() const noexcept {
			__LL_FUNCTION_INIT__;
			return this;
		}
		__LL_NODISCARD__ constexpr explicit operator ExceptionContainer*() noexcept {
			__LL_FUNCTION_INIT__;
			return this;
		}

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Generic
	protected:
		// Does not include reset
		template<class ExtraProcess, class GenericProcess, ll_bool_t ALL>
		constexpr void genericProcess(const ExtraProcess& extra) noexcept {
			__LL_FUNCTION_INIT__;
			GenericProcess generic_process;
			if constexpr (ALL) {
				(void)generic_process.process(extra, this->str_begin(), this->str_end());	// Process from begin to end
				(void)generic_process.process(extra, this->err_begin(), this->err_end());	// Process from begin to end
			}
			else {
				(void)generic_process.process(extra, this->str_begin(), this->str_last());	// Process from begin to filled point
				(void)generic_process.process(extra, this->err_begin(), this->err_last());	// Process from begin to filled point
			}
		}
		template<class ExtraCleaner, ll_bool_t ALL>
		constexpr void genericClear(const ExtraCleaner& extra) noexcept {
			__LL_FUNCTION_INIT__;
			this->genericProcess<ExtraCleaner, ::llcpp::meta::utils::Cleaner, ALL>(extra);
		}
		template<class ExtraInvalidator, ll_bool_t ALL>
		constexpr void genericInvalidator(const ExtraInvalidator& extra) noexcept {
			__LL_FUNCTION_INIT__;
			this->genericProcess<ExtraInvalidator, ::llcpp::meta::utils::Invalidator, ALL>(extra);
		}

		#pragma endregion
		#pragma region StrFunctions
		__LL_NODISCARD__ constexpr StringConstIterator str_begin() const noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_begin<StringConstIterator>(this->lifo_names);
		}
		__LL_NODISCARD__ constexpr StringIterator str_begin() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_begin<StringIterator>(this->lifo_names);
		}
		__LL_NODISCARD__ constexpr StringConstIterator str_end() const noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_end<StringConstIterator>(this->lifo_names);
		}
		__LL_NODISCARD__ constexpr StringIterator str_end() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_end<StringIterator>(this->lifo_names);
		}
		__LL_NODISCARD__ constexpr StringConstIterator str_last() const noexcept {
			__LL_FUNCTION_INIT__;
			static_assert(::std::is_nothrow_constructible_v<StringConstIterator, StringIterator>,
				"StringConstIterator needs to be constructed with StringIterator");
			return StringConstIterator(this->lifo_names_last);
		}
		__LL_NODISCARD__ constexpr StringIterator str_last() noexcept {
			__LL_FUNCTION_INIT__;
			return this->lifo_names_last;
		}
		
		#pragma endregion
		#pragma region ErrorFunctions
		__LL_NODISCARD__ constexpr ErrorConstIterator err_begin() const noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_begin<ErrorConstIterator>(this->lifo_errors);
		}
		__LL_NODISCARD__ constexpr ErrorIterator err_begin() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_begin<ErrorIterator>(this->lifo_errors);
		}
		__LL_NODISCARD__ constexpr ErrorConstIterator err_end() const noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_end<ErrorConstIterator>(this->lifo_errors);
		}
		__LL_NODISCARD__ constexpr ErrorIterator err_end() noexcept {
			__LL_FUNCTION_INIT__;
			return ::llcpp::meta::utils::get_array_end<ErrorIterator>(this->lifo_errors);
		}
		__LL_NODISCARD__ constexpr ErrorConstIterator err_last() const noexcept {
			__LL_FUNCTION_INIT__;
			static_assert(::std::is_nothrow_constructible_v<ErrorConstIterator, ErrorIterator>,
				"ErrorConstIterator needs to be constructed with ErrorIterator");
			return ErrorConstIterator(this->lifo_errors_last);
		}
		__LL_NODISCARD__ constexpr ErrorIterator err_last() noexcept {
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
		__LL_NODISCARD__ constexpr ::llcpp::ValidType validationType() const noexcept requires(VALID_CHECK_NEEDED) {
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
					: ::llcpp::ValidType::Error;
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
		template<class ExtraCleaner = _MyType::InvalidatorCleaner, ll_bool_t ALL = ::llcpp::LL_FALSE>
		constexpr void clear() noexcept {
			__LL_FUNCTION_INIT__;
			ExtraCleaner extra;
			this->clear<ExtraCleaner, ALL>(extra);
		}
		// Clears buffers data and reset class with a provided class
		template<class ExtraCleaner = _MyType::InvalidatorCleaner, ll_bool_t ALL = ::llcpp::LL_FALSE>
		constexpr void clear(const ExtraCleaner& extra) noexcept {
			__LL_FUNCTION_INIT__;
			this->genericClear<ExtraCleaner, ALL>(extra);
			this->reset();
		}
		// Invalidates iterators of fifo
		template<class ExtraInvalidator = _MyType::InvalidatorCleaner, ll_bool_t ALL = ::llcpp::LL_FALSE>
		constexpr void makeInvalid() noexcept {
			__LL_FUNCTION_INIT__;
			ExtraInvalidator extra;
			this->makeInvalid<ExtraInvalidator, ALL>(extra);
		}
		// Invalidates iterators of fifo with a provided class
		template<class ExtraInvalidator = _MyType::InvalidatorCleaner, ll_bool_t ALL = ::llcpp::LL_FALSE>
		constexpr void makeInvalid(const ExtraInvalidator& extra) noexcept {
			__LL_FUNCTION_INIT__;
			this->genericInvalidator<ExtraInvalidator, ALL>(extra);
		}
		// Invalidates iterators and objects of fifo
		template<
			class ExtraCleaner			= _MyType::InvalidatorCleaner,
			class ExtraInvalidator		= ExtraCleaner,
			ll_bool_t ALL_CLEAR			= ::llcpp::LL_FALSE,
			ll_bool_t ALL_INVALIDATE	= ::llcpp::LL_FALSE
		>
		constexpr void makeInvalidClear() noexcept {
			__LL_FUNCTION_INIT__;
			if constexpr (::std::is_same_v<ExtraCleaner, ExtraInvalidator>) {
				ExtraCleaner extra;
				this->makeInvalidClear<ExtraCleaner, ExtraInvalidator, ALL_CLEAR, ALL_INVALIDATE>(extra);
			}
			else {
				ExtraCleaner extra_cleaner;
				ExtraInvalidator extra_invalidator;
				this->makeInvalidClear<ExtraCleaner, ExtraInvalidator, ALL_CLEAR, ALL_INVALIDATE>({ extra_cleaner, extra_invalidator });
			}
		}
		// Invalidates iterators and objects of fifo
		template<
			class ExtraCleaner			= _MyType::InvalidatorCleaner,
			class ExtraInvalidator		= ExtraCleaner,
			ll_bool_t ALL_CLEAR			= ::llcpp::LL_FALSE,
			ll_bool_t ALL_INVALIDATE	= ::llcpp::LL_FALSE
		>
		constexpr void makeInvalidClear(InvalidatorAndCleanerContainer<ExtraCleaner, ExtraInvalidator> extra) noexcept {
			__LL_FUNCTION_INIT__;
			if constexpr (::std::is_same_v<ExtraCleaner, ExtraInvalidator>) {
				this->clear<ExtraCleaner, ALL_CLEAR>(extra);
				this->makeInvalid<ExtraInvalidator, ALL_INVALIDATE>(extra);
			}
			else {
				this->clear<ExtraCleaner, ALL_CLEAR>(extra.first);
				this->makeInvalid<ExtraInvalidator, ALL_INVALIDATE>(extra.second);
			}
		}
		// Checks if container is corrupted
		__LL_NODISCARD__ constexpr ll_bool_t isCorrupted() const noexcept {
			return (::llcpp::meta::utils::itertator_distance(this->str_last(), this->str_begin()) < 0)
				|| (::llcpp::meta::utils::itertator_distance(this->str_end(), this->str_last()) < 0)
				|| (::llcpp::meta::utils::itertator_distance(this->err_last(), this->err_last()) < 0)
				|| (::llcpp::meta::utils::itertator_distance(this->err_end(), this->err_last()) < 0);
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

		// Checks if iterator is pointing to the begin of the array
		// If iterator is a value lower than begin, this function will return false (class corrupted)
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->str_last() == this->str_begin();
		}
		// Checks if iterator is pointing to the end of the array
		// If iterator is a value bigger than end, this function will return false (class corrupted)
		__LL_NODISCARD__ constexpr ll_bool_t full() const noexcept {
			__LL_FUNCTION_INIT__;
			return this->str_last() == this->str_end();
		}

		__LL_NODISCARD__ constexpr ll_bool_t push(StringType s, ErrorType e) noexcept {
			__LL_FUNCTION_INIT__;
			if (this->full()) {
				if constexpr (::llcpp::LL_DEBUG_ERROR)
					__debug_error_exceptions_full("Exceptions list is full! You may fix some error or increase ExceptionContainer");
				return ::llcpp::LL_FALSE;
			}
			*(this->lifo_names_last++) = s;
			*(this->lifo_errors_last++) = e;
			return ::llcpp::LL_TRUE;
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

template<
	usize N,															// Number of elements that buffer can store
	class StringTypeArray		= ::llcpp::Arrayo<::llcpp::string, N>,	// Array type to store string types
	class ErrorTypeArray		= ::llcpp::Arrayo<i32, N>,				// Array type to store error types
	class InvalidatorCleaner	= ::llcpp::Emptyclass					// Type with functionality used to invalidate/clear string/error types
>
__LL_NODISCARD__ constexpr auto generateExceptionContainer() noexcept {
	using StringType					= ::llcpp::meta::traits::array_type_t<StringTypeArray>;
	using ErrorType						= ::llcpp::meta::traits::array_type_t<ErrorTypeArray>;

	using StringIterator				= ::llcpp::meta::utils::array_iterator_t<StringTypeArray>;
	using ErrorIterator					= ::llcpp::meta::utils::array_iterator_t<ErrorTypeArray>;
	using StringConstIterator			= ::llcpp::meta::utils::array_const_iterator_t<StringTypeArray>;
	using ErrorConstIterator			= ::llcpp::meta::utils::array_const_iterator_t<ErrorTypeArray>;

	using InvalidatorCleanerInternal	=
		::llcpp::meta::traits::conditional_t<::llcpp::meta::traits::is_empty_type_v<InvalidatorCleaner>,
		::llcpp::meta::utils::ExceptionFunctions<StringType, ErrorType>,
		InvalidatorCleaner
	>;
	using ValidTag						= ::llcpp::meta::traits::conditional_t<
		::llcpp::meta::utils::is_valid_array_type_all_v<StringType, ErrorType>,
		::llcpp::AlwaysValidTag,
		::llcpp::DummyClass
	>;

	using ExceptionType = ::llcpp::meta::utils::ExceptionContainer<N, StringTypeArray, ErrorTypeArray, InvalidatorCleanerInternal, ValidTag>;
	static_assert(::llcpp::meta::traits::is_empty_type_v<StringType>,			"StringTypeArray must be an C static array style or an array object like Arrayo");
	static_assert(::llcpp::meta::traits::is_empty_type_v<ErrorType>,			"ErrorTypeArray must be an C static array style or an array object like Arrayo");

	static_assert(::llcpp::meta::traits::is_empty_type_v<StringIterator>,		"StringIterator must be an iterator of provided array");
	static_assert(::llcpp::meta::traits::is_empty_type_v<ErrorIterator>,		"ErrorIterator must be an iterator of provided array");
	static_assert(::llcpp::meta::traits::is_empty_type_v<StringConstIterator>,	"StringConstIterator must be a const iterator of provided array");
	static_assert(::llcpp::meta::traits::is_empty_type_v<ErrorConstIterator>,	"ErrorConstIterator must be a const iterator of provided array");

	static_assert(::llcpp::meta::traits::is_valid_tag_type_v<ValidTag>,			"Tag type is not a valid validation tag type!");

	return ::llcpp::meta::traits::TypeContainer<ExceptionType>;
}

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
