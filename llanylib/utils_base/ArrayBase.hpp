//////////////////////////////////////////////
//	ArrayBase.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ARRAYBASE_INCOMPLETE_HPP_)
	#if LLANYLIB_ARRAYBASE_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ARRAYBASE_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "ArrayBase.hpp(incomplete) version error!"
		#else
			#error "ArrayBase.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAYBASE_INCOMPLETE_MAYOR_ || LLANYLIB_ARRAYBASE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ARRAYBASE_INCOMPLETE_HPP_)
	#define LLANYLIB_ARRAYBASE_INCOMPLETE_HPP_
	#define LLANYLIB_ARRAYBASE_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ARRAYBASE_INCOMPLETE_MINOR_ 0

#include "../types/ValidType.hpp"
#include "../traits_base/checker.hpp"
#include "PointerIterator.hpp"
#include "Exceptions.hpp"

namespace llcpp {
namespace meta {
namespace utils {

template<
	class _T,
	ll_bool_t _ENABLE_NO_CONST = ::llcpp::LL_TRUE,
	ll_bool_t _USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE,
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_CPAV
>
class ArrayBase;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ARRAYBASE_HPP_)
	#if LLANYLIB_ARRAYBASE_MAYOR_ != 12 || LLANYLIB_ARRAYBASE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "ArrayBase.hpp version error!"
		#else
			#error "ArrayBase.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAYBASE_MAYOR_ || LLANYLIB_ARRAYBASE_MINOR_

#else
	#define LLANYLIB_ARRAYBASE_HPP_
	#define LLANYLIB_ARRAYBASE_MAYOR_ 12
	#define LLANYLIB_ARRAYBASE_MINOR_ 0

#include "../types/ValidType.hpp"
#include "../traits_base/checker.hpp"
#include "PointerIterator.hpp"
#include "Exceptions.hpp"

#define CHECK_RESET_VALIDATION																		\
	if constexpr (::llcpp::DEBUG || ::llcpp::EXCEPTIONS) {											\
		if (!mem) {																					\
			if constexpr (::llcpp::DEBUG)															\
				__debug_error_not_nullptr_str("mem");												\
			if constexpr (::llcpp::EXCEPTIONS)														\
				(void)LOG_EXCEPTION_TAG("mem", ::llcpp::misc::Errors::NullptrProvided);				\
		}																							\
		if (!mem_end) {																				\
			if constexpr (::llcpp::DEBUG)															\
				__debug_error_not_nullptr_str("mem_end");											\
			if constexpr (::llcpp::EXCEPTIONS)														\
				(void)LOG_EXCEPTION_TAG("mem_end", ::llcpp::misc::Errors::NullptrProvided);			\
		}																							\
		if (mem > mem_end) {																		\
			if constexpr (::llcpp::DEBUG)															\
				__debug_error_begin_smaller("mem > mem_end", mem, mem_end);							\
			if constexpr (::llcpp::EXCEPTIONS)														\
				(void)LOG_EXCEPTION_TAG("mem > mem_end", ::llcpp::misc::Errors::NullptrProvided);	\
		}																							\
	}

namespace llcpp {
namespace meta {
namespace utils {

template<
	class _T,
	ll_bool_t _ENABLE_NO_CONST = ::llcpp::LL_TRUE,
	ll_bool_t _USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE,
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_CPAV
>
class ArrayBase {
	#pragma region Types
	public:
		// Class related
		using _MyType	= ArrayBase;
		template<class U>
		using contain_value_type =
			typename ::llcpp::meta::utils::ArrayBase<U, _ENABLE_NO_CONST, _USE_OBJECT_ITERATOR, _TYPE_CHECKER>;

		// Types
		using T					= _T;
		using type				= T;
		using value_type		= T;

		//using reference			= ::llcpp::meta::traits::input<T>;
		using iterator			= ::llcpp::meta::traits::conditional_t<
			_USE_OBJECT_ITERATOR,
			::llcpp::meta::utils::PointerIterator<T, ::llcpp::LL_FALSE>,
			T*
		>;
		using riterator			= ::llcpp::meta::utils::PointerIterator<T, ::llcpp::LL_TRUE>;

		//using const_reference	= ::llcpp::meta::traits::cinput<T>;
		using const_iterator = ::llcpp::meta::traits::conditional_t<
			_USE_OBJECT_ITERATOR,
			::llcpp::meta::utils::ConstPointerIterator<T, ::llcpp::LL_FALSE>,
			const T*
		>;
		using reference_const_iterator = ::llcpp::meta::traits::conditional_t<
			_USE_OBJECT_ITERATOR,
			const_iterator&,
			const_iterator
		>;
		using const_riterator	= ::llcpp::meta::utils::ConstPointerIterator<T, ::llcpp::LL_TRUE>;

		using default_iterator = ::llcpp::meta::traits::conditional_t<
			_ENABLE_NO_CONST,
			iterator,
			const_iterator
		>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = _TYPE_CHECKER;
		static constexpr ll_bool_t USE_OBJECT_ITERATOR	= _USE_OBJECT_ITERATOR;
		static constexpr ll_bool_t ENABLE_NO_CONST		= _ENABLE_NO_CONST;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(::llcpp::meta::traits::is_valid_type_checker_v<T, TYPE_CHECKER>,
			"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Attributes
	private:
		default_iterator mem;
		default_iterator mem_end;

	#pragma endregion
	#pragma region Functions
		#pragma region Functions
	private:
		constexpr void simpleClear() noexcept {
			this->setMem(::llcpp::ZERO_VALUE<default_iterator>);
			this->setMemEnd(::llcpp::ZERO_VALUE<default_iterator>);
		}
		constexpr void setMem(default_iterator mem) noexcept { this->mem = mem; }
		constexpr void setMemEnd(default_iterator mem_end) noexcept { this->mem_end = mem_end; }

		#pragma endregion
		#pragma region Constructors
	public:
		constexpr ArrayBase() noexcept
			: mem(::llcpp::ZERO_VALUE<default_iterator>)
			, mem_end(::llcpp::ZERO_VALUE<default_iterator>)
		{}
		constexpr ArrayBase(default_iterator mem, default_iterator mem_end) noexcept
			: mem(mem)
			, mem_end(mem_end)
		{}
		constexpr ArrayBase(default_iterator mem, const usize len) noexcept
			: ArrayBase(mem, mem + len)
		{}
		template<usize N>
		constexpr ArrayBase(default_iterator (&v)[N]) noexcept
			: ArrayBase(v, v + N)
		{}
		template<usize N>
		constexpr ArrayBase& operator=(default_iterator (&v)[N]) noexcept {
			this->resetValidation(v, N);
			return *this;
		}
		constexpr ~ArrayBase() noexcept {
			if constexpr (::llcpp::CLEAR_POINTERS_ON_DESTRUCTION)
				this->simpleClear();
		}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ArrayBase(const ArrayBase& other) noexcept
			: ArrayBase(other.mem, other.mem_end)
		{}
		constexpr ArrayBase& operator=(const ArrayBase& other) noexcept {
			this->resetValidation(other.cbegin(), other.cend());
			return *this;
		}
		constexpr ArrayBase(ArrayBase&& other) noexcept
			: ArrayBase(other)
		{ other.simpleClear(); }
		constexpr ArrayBase& operator=(ArrayBase&& other) noexcept {
			this->resetValidation(other.cbegin(), other.cend());
			other.simpleClear();
			return *this;
		}

		constexpr ArrayBase(volatile const ArrayBase& other) noexcept = delete;
		constexpr ArrayBase& operator=(volatile const ArrayBase& other) noexcept = delete;
		constexpr ArrayBase(volatile ArrayBase&& other) noexcept = delete;
		constexpr ArrayBase& operator=(volatile ArrayBase&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const ArrayBase*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator ArrayBase*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region std
	public:
		__LL_NODISCARD__ constexpr iterator data() noexcept requires(ENABLE_NO_CONST) {
			return this->mem;
		}
		__LL_NODISCARD__ constexpr const_iterator data() const noexcept { return this->mem; }

		__LL_NODISCARD__ constexpr iterator begin() noexcept requires(ENABLE_NO_CONST) {
			return this->data();
		}
		__LL_NODISCARD__ constexpr const_iterator begin() const noexcept { return this->data(); }

		__LL_NODISCARD__ constexpr iterator end() noexcept requires(ENABLE_NO_CONST) {
			return this->mem_end;
		}
		__LL_NODISCARD__ constexpr const_iterator end() const noexcept { return this->mem_end; }

		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			return this->begin() == this->end();
		}

		#pragma endregion
		#pragma region Countable
	public:
		__LL_NODISCARD__ constexpr usize size() const noexcept {
			return static_cast<usize>(this->end() - this->begin());
		}

		#pragma endregion
		#pragma region Other
	public:
		__LL_NODISCARD__ constexpr ::llcpp::misc::ValidType validationType() const noexcept {
			return this->begin() <= this->end() ? ::llcpp::misc::ValidType::Valid : ::llcpp::misc::ValidType::Invalid;
		}
		constexpr void makeInvalid() noexcept { this->simpleClear(); }
		constexpr void clear() noexcept { this->makeInvalid(); }
		__LL_NODISCARD__ constexpr ll_bool_t resetValidation(default_iterator mem, default_iterator mem_end) noexcept {
			CHECK_RESET_VALIDATION;
			this->setMem(mem);
			this->setMemEnd(mem_end);
			return ::llcpp::LL_TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t inRange(const usize position) const noexcept {
			return position < this->size();
		}
		__LL_NODISCARD__ constexpr ll_bool_t inRange(reference_const_iterator data) const noexcept {
			return this->begin() <= data && data <= this->end();
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const usize position) const noexcept {
			return this->inRange(position);
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(reference_const_iterator data) const noexcept {
			return this->inRange(data);
		}

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

#define ARR_PREP(arr) (arr, arr + ::llcpp::meta::traits::array_size<decltype(arr)>)

} // namespace utils
} // namespace meta
} // namespace llcpp

#undef CHECK_RESET_VALIDATION

#endif // LLANYLIB_ARRAYBASE_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_ARRAYBASE_EXTRA_HPP_)
		#if LLANYLIB_ARRAYBASE_EXTRA_MAYOR_ != 12 || LLANYLIB_ARRAYBASE_EXTRA_MINOR_ < 0
			#if __LL_DIRECTIVE_WARNING == 1
				#warning "qwerty.hpp(extra) version error!"
			#else
				#error "qwerty.hpp(extra) version error!"
			#endif // __LL_DIRECTIVE_WARNING == 1
		#endif // LLANYLIB_ARRAYBASE_EXTRA_MAYOR_ || LLANYLIB_ARRAYBASE_EXTRA_MINOR_

	#else
		#define LLANYLIB_ARRAYBASE_EXTRA_HPP_
		#define LLANYLIB_ARRAYBASE_EXTRA_MAYOR_ 12
		#define LLANYLIB_ARRAYBASE_EXTRA_MINOR_ 0

namespace llcpp {
namespace meta {
namespace utils {
			
// Ascii char string
template<ll_bool_t ENABLE_NO_CONST = ::llcpp::LL_TRUE, ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE>
using Str = ::llcpp::meta::utils::ArrayBase<ll_char_t, ENABLE_NO_CONST, USE_OBJECT_ITERATOR>;
// Wide char string
template<ll_bool_t ENABLE_NO_CONST = ::llcpp::LL_TRUE, ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE>
using wStr = ::llcpp::meta::utils::ArrayBase<ll_wchar_t, ENABLE_NO_CONST, USE_OBJECT_ITERATOR>;

// Ascii char string
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE>
using cStr = ::llcpp::meta::utils::ArrayBase<ll_char_t, ::llcpp::LL_FALSE, USE_OBJECT_ITERATOR>;
// Wide char string
template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE>
using cwStr = ::llcpp::meta::utils::ArrayBase<ll_wchar_t, ::llcpp::LL_FALSE, USE_OBJECT_ITERATOR>;

// Ascii/Wide char defined by macros and OS
template<ll_bool_t ENABLE_NO_CONST = ::llcpp::LL_TRUE, ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE>
using String = ::llcpp::meta::utils::ArrayBase<::llcpp::char_type, ENABLE_NO_CONST, USE_OBJECT_ITERATOR>;

template<ll_bool_t USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE>
using cString = ::llcpp::meta::utils::ArrayBase<::llcpp::char_type, ::llcpp::LL_FALSE, USE_OBJECT_ITERATOR>;

} // namespace utils
} // namespace meta
} // namespace llcpp

	#endif // LLANYLIB_ARRAYBASE_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
