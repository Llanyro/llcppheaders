//////////////////////////////////////////////
//	Exceptions.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_EXCEPTIONS_HPP_) // Guard && version protector
	#if LLANYLIB_EXCEPTIONS_MAYOR_ != 11 || LLANYLIB_EXCEPTIONS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Exceptions.hpp version error!"
		#else
			#error "Exceptions.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_EXCEPTIONS_MAYOR_ || LLANYLIB_EXCEPTIONS_MINOR_

#else
	#define LLANYLIB_EXCEPTIONS_HPP_
	#define LLANYLIB_EXCEPTIONS_MAYOR_ 11
	#define LLANYLIB_EXCEPTIONS_MINOR_ 0

#include "../types/types.hpp"

#if defined(__LL_EXCEPTIONS)

#include "../types/Errors.hpp"
#include "Tuple.hpp"
#include "IteratorUtils.hpp"

namespace llcpp {
namespace exceptions {

template<usize _N, class _StringType = ::llcpp::string, class _ErrorType = i32>
class ExceptionBuffer : public ::llcpp::AlwaysValidTag {
	#pragma region Types
	public:
		// Class related
		using _MyType	= ExceptionBuffer;

		// Types
		using StringType	= _StringType;
		using ErrorType		= _ErrorType;
		using NameCleaner	= ::llcpp::meta::utils::IteratorCleaner<StringType*>;
		using ErrorCleaner	= ::llcpp::meta::utils::IteratorCleaner<ErrorType*>;
		using PopData		= ::llcpp::meta::pair<StringType, ErrorType>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr usize N = _N;

	#pragma endregion
	#pragma region Attributes
	private:
		StringType lifo_names[N];
		StringType* lifo_names_last;
		ErrorType* lifo_errors_last;
		ErrorType lifo_errors[N];

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr ExceptionBuffer() noexcept
			: lifo_names()
			, lifo_names_last(::llcpp::NULL_VALUE<StringType*>)
			, lifo_errors_last(::llcpp::NULL_VALUE<ErrorType*>)
			, lifo_errors()
		{ this->simpleClear(); }
		constexpr ~ExceptionBuffer() noexcept {
			if constexpr (::llcpp::CLEAR_SECURE)
				this->clear();
			else if constexpr (::llcpp::CLEAR_POINTERS_ON_DESTRUCTION)
				this->simpleClear();
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
	public:
		constexpr void simpleClear() noexcept {
			this->lifo_names_last = this->lifo_names;
			this->lifo_errors_last = this->lifo_errors;
		}
		constexpr void clear() noexcept {
			(void)NameCleaner().foreach(this->lifo_names, this->lifo_names + N);
			(void)ErrorCleaner().foreach(this->lifo_errors, this->lifo_errors + N);
			this->simpleClear();
		}

		__LL_NODISCARD__ constexpr usize lenght() const noexcept { return static_cast<usize>(this->lifo_names_last - this->lifo_names); }
		__LL_NODISCARD__ constexpr usize size() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr usize count() const noexcept { return this->lenght(); }
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept { return this->lifo_names_last == this->lifo_names; }
		__LL_NODISCARD__ constexpr ll_bool_t full() const noexcept { return this->lifo_names_last >= this->lifo_names + N; }

		__LL_NODISCARD__ ll_bool_t push(StringType s, ErrorType e) noexcept {
			if (this->full()) {
				__debug_error_exceptions_full("Exceptions list is full! You may fix some error or increase ExceptionBuffer");
				return ::llcpp::FALSE;
			}
			*(this->lifo_names_last++) = s;
			*(this->lifo_errors_last++) = e;
			return ::llcpp::TRUE;
		}
		__LL_NODISCARD__ ll_bool_t push(StringType s, ::llcpp::misc::Errors e) noexcept {
			return this->push(s, static_cast<ErrorType>(e));
		}
		__LL_NODISCARD__ ll_bool_t pop(PopData& data) noexcept {
			if (this->empty()) {
				__debug_error_exceptions_empty("Exceptions list is empty! Do not pop with empty stack!");
				return ::llcpp::FALSE;
			}
			data = { *(--this->lifo_names_last), *(--this->lifo_errors_last) };
			return ::llcpp::TRUE;
		}

		#pragma endregion

	#pragma endregion
};

::llcpp::exceptions::ExceptionBuffer<10, string, i32> ex;
#define ll_exceptions ::llcpp::exceptions::ex

#if defined(__LL_USE_WIDE_CHAR)
	#define LOG_EXCEPTION(err) ll_exceptions.push(L"" __LL_FUNCNAME__, err)
#else
	#define LOG_EXCEPTION(err) ll_exceptions.push(__LL_FUNCNAME__, err)
#endif // __LL_USE_WIDE_CHAR

} // namespace exceptions
} // namespace llcpp

#else
	#define LOG_EXCEPTION(err) ::llcpp::IGNORE(err)
#endif // __LL_EXCEPTIONS

#endif // LLANYLIB_EXCEPTIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
