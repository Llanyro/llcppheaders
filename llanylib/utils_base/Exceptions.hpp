//////////////////////////////////////////////
//	Exceptions.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_EXCEPTIONS_HPP_) // Guard && version protector
	#if LLANYLIB_EXCEPTIONS_MAYOR_ != 12 || LLANYLIB_EXCEPTIONS_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "Exceptions.hpp version error!"
		#else
			#error "Exceptions.hpp version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_EXCEPTIONS_MAYOR_ || LLANYLIB_EXCEPTIONS_MINOR_

#else
	#define LLANYLIB_EXCEPTIONS_HPP_
	#define LLANYLIB_EXCEPTIONS_MAYOR_ 12
	#define LLANYLIB_EXCEPTIONS_MINOR_ 0

#include "../types/types.hpp"
#include "../types/Errors.hpp"

#if __LL_EXCEPTIONS == 1

#include "IteratorUtils.hpp"
#include "IteratorCommon.hpp"

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

static ::llcpp::exceptions::ExceptionBuffer<10, string, i32> ex;
#define ll_exceptions ::llcpp::exceptions::ex

#define LOG_EXCEPTION(err) ll_exceptions.push(__LL_FUNCNAME__, err)
#define LOG_EXCEPTION_TAG(tag, err) ll_exceptions.push(__LL_FUNCNAME__ " [ " tag " ]", err)

} // namespace exceptions
} // namespace llcpp

#else
	#define LOG_EXCEPTION(err) ::llcpp::IGNORE(err)
	#define LOG_EXCEPTION_TAG(tag, err) ::llcpp::IGNORE(tag, err)
#endif // __LL_EXCEPTIONS == 1

#endif // LLANYLIB_EXCEPTIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
