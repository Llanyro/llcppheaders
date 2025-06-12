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

#include <llanylib/types/Errors.hpp>
#include <llanylib/utils_base/GenericFunctions.hpp>
#include <llanylib/utils_base/list_functions.hpp>

namespace llcpp {
namespace exceptions {

template<class _StringType, class _ErrorType>
class ExceptionFunctions : public ::llcpp::AlwaysValidTag {
	#pragma region Types
	public:
		// Class related
		using _MyType				= ExceptionFunctions;

		// Types and enums
		using StringType			= _StringType;
		using ErrorType				= _ErrorType;

		__LL_VAR_INLINE__ static constexpr ll_bool_t IS_BOTH_VALID =
			::llcpp::meta::utils::isValidArrayType<StringType>() &&
			::llcpp::meta::utils::isValidArrayType<ErrorType>();

		using ExceptionValidTag = ::llcpp::meta::traits::conditional_t<
			_MyType::IS_BOTH_VALID,
			::llcpp::AlwaysValidTag,
			::llcpp::DummyClass
		>; 
	#pragma endregion
	#pragma region CleanFunctions
	public:
		constexpr void __cleaner(StringType*& val) const noexcept {
			val = ::llcpp::NULL_VALUE<StringType>;
		}
		constexpr void __cleaner(ErrorType*& val) const noexcept {
			val = ::llcpp::NULL_VALUE<ErrorType>;
		}

		template<::llcpp::usize N>
		constexpr void __cleaner(ErrorType (&val)[N]) const noexcept {
			ErrorType* aux = val;
			for(const ErrorType* end = aux + N; aux < end; ++aux)
				this->__cleaner(*aux);
		}
		template<::llcpp::usize N>
		constexpr void __cleaner(StringType (&val)[N]) const noexcept {
			StringType* aux = val;
			for(const StringType* end = aux + N; aux < end; ++aux)
				this->__cleaner(*aux);
		}

	#pragma endregion
	#pragma region InvalidateFunctions
	public:
		constexpr void __invalidate(StringType*& val) const noexcept {
			val = ::llcpp::NULL_VALUE<StringType>;
		}
		constexpr void __invalidate(ErrorType*& val) const noexcept {
			val = ::llcpp::NULL_VALUE<ErrorType>;
		}

		template<::llcpp::usize N>
		constexpr void __invalidate(ErrorType (&val)[N]) const noexcept {
			ErrorType* aux = val;
			for(const ErrorType* end = aux + N; aux < end; ++aux)
				this->__invalidate(*aux);
		}
		template<::llcpp::usize N>
		constexpr void __invalidate(StringType (&val)[N]) const noexcept {
			StringType* aux = val;
			for(const StringType* end = aux + N; aux < end; ++aux)
				this->__invalidate(*aux);
		}

	#pragma endregion
};

template<
	usize _N,
	class _StringType			= ::llcpp::string,
	class _ErrorType			= i32,
	class _StringTypeArray		= _StringType[_N],
	class _ErrorTypeArray		= _ErrorType[_N],
	class _InvalidatorCleaner	= ::llcpp::exceptions::ExceptionFunctions<_StringType, _ErrorType>
>
class ExceptionBuffer : public ::llcpp::exceptions::ExceptionFunctions<_StringTypeArray, _ErrorTypeArray>::ExceptionValidTag {
	#pragma region Types
	public:
		// Class related
		using _MyType				= ExceptionBuffer;
		using ValidTag				= ::llcpp::exceptions::ExceptionFunctions<_StringTypeArray, _ErrorTypeArray>::ExceptionValidTag;

		// Types and enums
		using StringType			= _StringType;
		using ErrorType				= _ErrorType;
		using StringTypeArray		= _StringTypeArray;
		using ErrorTypeArray		= _ErrorTypeArray;
		using PopData				= ::llcpp::meta::pair<StringType, ErrorType>;
		using InvalidatorCleaner	= _InvalidatorCleaner;

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
		StringType*		lifo_names_last;
		ErrorType*		lifo_errors_last;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr ExceptionBuffer() noexcept
			: lifo_names()
			, lifo_errors()
			, lifo_names_last(::llcpp::meta::utils::getArrayBegin<StringType>(this->lifo_names))
			, lifo_errors_last(::llcpp::meta::utils::getArrayBegin<ErrorType>(this->lifo_errors))
		{}
		constexpr ~ExceptionBuffer() noexcept {
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

		constexpr ExceptionBuffer(volatile const ExceptionBuffer& other) noexcept = delete;
		constexpr ExceptionBuffer& operator=(volatile const ExceptionBuffer& other) noexcept = delete;
		constexpr ExceptionBuffer(volatile ExceptionBuffer&& other) noexcept = delete;
		constexpr ExceptionBuffer& operator=(volatile ExceptionBuffer&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const ExceptionBuffer*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator ExceptionBuffer*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	protected:
		// Does not include reset
		template<class ExtraCleaner>
		constexpr void clearPriv(const ExtraCleaner& extra) noexcept {
			::llcpp::meta::utils::Cleaner cleaner;
			(void)cleaner.process(this->lifo_names, extra);
			(void)cleaner.process(this->lifo_errors, extra);
		}

	public:
		// Returns ValidType of each type
		// If any type is AlwaysValid, and other we need to ask, will return ValidType or second type
		// If we need to ask both types, will return common ValidType or ValidType::Error if ValidType does not match
		// This function cannot be called if both types are valid types
		__LL_NODISCARD__ constexpr ::llcpp::misc::ValidType validationType() const noexcept requires(VALID_CHECK_NEEDED) {
			constexpr auto IS_ERR_VALID = ::llcpp::meta::utils::isValidArrayType<ErrorTypeArray>();
			constexpr auto IS_STR_VALID = ::llcpp::meta::utils::isValidArrayType<StringTypeArray>();
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
			this->lifo_names_last	= ::llcpp::meta::utils::getArrayBegin(this->lifo_names);
			this->lifo_errors_last	= ::llcpp::meta::utils::getArrayBegin(this->lifo_errors);
		}
		// Clears buffers data and reset class
		template<class ExtraCleaner = _MyType::InvalidatorCleaner>
		constexpr void clear() noexcept {
			ExtraCleaner extra;
			this->clear(extra);
		}
		// Clears buffers data and reset class with a provided class
		template<class ExtraCleaner = _MyType::InvalidatorCleaner>
		constexpr void clear(const ExtraCleaner& extra) noexcept {
			this->clearPriv(extra);
			this->reset();
		}
		// Invalidates iterators of fifo
		template<class ExtraInvalidator = _MyType::InvalidatorCleaner>
		constexpr void makeInvalid() noexcept {
			ExtraInvalidator extra;
			this->makeInvalid(extra);
		}
		// Invalidates iterators of fifo with a provided class
		template<class ExtraInvalidator = _MyType::InvalidatorCleaner>
		constexpr void makeInvalid(const ExtraInvalidator& extra) noexcept {
			::llcpp::meta::utils::Invalidator invalidator;
			(void)invalidator.process(this->lifo_errors_last, extra);
			(void)invalidator.process(this->lifo_names_last, extra);
		}
		// Invalidates iterators and objects of fifo
		template<class ExtraInvalidatorCleaner = _MyType::InvalidatorCleaner>
		constexpr void makeInvalidClear() noexcept {
			ExtraInvalidatorCleaner extra;
			this->makeInvalidClear(extra);
		}
		// Invalidates iterators and objects of fifo
		template<class ExtraInvalidatorCleaner = _MyType::InvalidatorCleaner>
		constexpr void makeInvalidClear(const ExtraInvalidatorCleaner& extra) noexcept {
			this->clearPriv(extra);
			this->makeInvalid(extra);
		}

		__LL_NODISCARD__ constexpr usize lenght() const noexcept { return static_cast<usize>(this->lifo_names_last - this->lifo_names); }
		__LL_NODISCARD__ constexpr usize size() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr usize count() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept { return this->lifo_names_last == this->lifo_names; }
		__LL_NODISCARD__ constexpr ll_bool_t full() const noexcept { return this->lifo_names_last >= this->lifo_names + N; }

		__LL_NODISCARD__ constexpr ll_bool_t push(StringType s, ErrorType e) noexcept {
			if (this->full()) {
				__debug_error_exceptions_full("Exceptions list is full! You may fix some error or increase ExceptionBuffer");
				return ::llcpp::LL_FALSE;
			}
			*(this->lifo_names_last++) = s;
			*(this->lifo_errors_last++) = e;
			return ::llcpp::LL_TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t push(StringType s, ::llcpp::misc::Errors e) noexcept {
			return this->push(s, static_cast<ErrorType>(e));
		}
		__LL_NODISCARD__ constexpr ll_bool_t pop(PopData& data) noexcept {
			if (this->empty()) {
				__debug_error_exceptions_empty("Exceptions list is empty! Do not pop with empty stack!");
				return ::llcpp::LL_FALSE;
			}
			data = { *(--this->lifo_names_last), *(--this->lifo_errors_last) };
			return ::llcpp::LL_TRUE;
		}

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

} // namespace exceptions
} // namespace llcpp

#endif // LLANYLIB_EXCEPTIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
