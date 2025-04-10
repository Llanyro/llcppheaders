//////////////////////////////////////////////
//	Array.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ARRAY_INCOMPLETE_HPP_)
	#if LLANYLIB_ARRAY_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ARRAY_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Array.hpp(incomplete) version error!"
		#else
			#error "Array.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAY_INCOMPLETE_MAYOR_ || LLANYLIB_ARRAY_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ARRAY_INCOMPLETE_HPP_)
	#define LLANYLIB_ARRAY_INCOMPLETE_HPP_
	#define LLANYLIB_ARRAY_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ARRAY_INCOMPLETE_MINOR_ 0

#include "../types_base/ValidType.hpp"
#undef LLANYLIB_INCOMPLETE_HPP_
#include "../traits_base/traits_checker.hpp"
#define LLANYLIB_INCOMPLETE_HPP_

namespace llcpp {
namespace meta {
namespace utils {

template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
class Array;
template<class _T, ::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
class ConstArray;

template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
using Str = ::llcpp::meta::utils::Array<ll_char_t, _TYPE_CHECKER>;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
using wStr = ::llcpp::meta::utils::Array<ll_wchar_t, _TYPE_CHECKER>;

template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
using ConstStr = ::llcpp::meta::utils::ConstArray<ll_char_t, _TYPE_CHECKER>;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER>
using ConstwStr = ::llcpp::meta::utils::ConstArray<ll_wchar_t, _TYPE_CHECKER>;

#pragma region Builders
#pragma region Array
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER, class _T, usize _N>
__LL_NODISCARD__ constexpr Array<_T, _TYPE_CHECKER> make_Array(_T(&_array)[_N]) noexcept;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER, usize _N>
__LL_NODISCARD__ constexpr Array<ll_char_t, _TYPE_CHECKER> make_Array(const ll_char_t(&_array)[_N]) noexcept;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER, usize _N>
__LL_NODISCARD__ constexpr Array<ll_wchar_t, _TYPE_CHECKER> make_Array(const ll_wchar_t(&_array)[_N]) noexcept;

#pragma endregion
#pragma region ConstArray

template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER, class _T, usize _N>
__LL_NODISCARD__ constexpr ConstArray<_T, _TYPE_CHECKER> make_ConstArray(_T(&_array)[_N]) noexcept;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER, usize _N>
__LL_NODISCARD__ constexpr ConstArray<ll_char_t, _TYPE_CHECKER> make_ConstArray(const ll_char_t(&_array)[_N]) noexcept;
template<::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER, usize _N>
__LL_NODISCARD__ constexpr ConstArray<ll_wchar_t, _TYPE_CHECKER> make_ConstArray(const ll_wchar_t(&_array)[_N]) noexcept;
#pragma endregion

#pragma endregion

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ARRAY_HPP_)
	#if LLANYLIB_ARRAY_MAYOR_ != 12 || LLANYLIB_ARRAY_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Array.hpp version error!"
		#else
			#error "Array.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAY_MAYOR_ || LLANYLIB_ARRAY_MINOR_

#else
	#define LLANYLIB_ARRAY_HPP_
	#define LLANYLIB_ARRAY_MAYOR_ 12
	#define LLANYLIB_ARRAY_MINOR_ 0

#include "../traits_base/type_traits_extended.hpp"
#include "../traits_base/checker.hpp"
#include "../concepts/valid_type.hpp"
#include "Exceptions.hpp"
#include "PointerIterator.hpp"

#pragma region Macros

#define CHECK_POSITION_DEBUG_EXCEPTION																\
	if constexpr (::llcpp::DEBUG || ::llcpp::EXCEPTIONS) {											\
		if (!this->inRange(position)) {																\
			if constexpr (::llcpp::DEBUG)															\
				__debug_error_out_of_range(position, "position", this->length());					\
			if constexpr (::llcpp::EXCEPTIONS)														\
				(void)LOG_EXCEPTION(::llcpp::misc::Errors::OutOfRange);								\
		}																							\
	}

#define CHECK_POSITIONS_DEBUG_EXCEPTION																\
	if constexpr (::llcpp::DEBUG || ::llcpp::EXCEPTIONS) {											\
		if (!this->inRange(first)) {																\
			if constexpr (::llcpp::DEBUG)															\
				__debug_error_out_of_range(first, "first", this->length());							\
			if constexpr (::llcpp::EXCEPTIONS)														\
				(void)LOG_EXCEPTION_TAG("first", ::llcpp::misc::Errors::OutOfRange);				\
		}																							\
		if (!this->inRange(last)) {																	\
			if constexpr (::llcpp::DEBUG)															\
				__debug_error_out_of_range(last, "last", this->length());							\
			if constexpr (::llcpp::EXCEPTIONS)														\
				(void)LOG_EXCEPTION_TAG("last", ::llcpp::misc::Errors::OutOfRange);					\
		}																							\
	}

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

#pragma endregion

namespace llcpp {
namespace meta {
namespace utils {

template<class _ArrayBase, ll_bool_t _ENABLE_NO_CONST = ::llcpp::TRUE, ll_bool_t _USE_OBJECT_ITERATOR = ::llcpp::FALSE>
	requires
		::llcpp::meta::concepts::base::HasValueType<_ArrayBase>
		&& ::llcpp::meta::concepts::signature::HasConstBegin<_ArrayBase>
		&& ::llcpp::meta::concepts::signature::HasConstEnd<_ArrayBase>
		&& ::llcpp::meta::traits::is_valid_constructor_checker_v<_ArrayBase>
		&& ::llcpp::meta::traits::conditional_value_bool_v<_ENABLE_NO_CONST,
			::llcpp::TRUE,
			::llcpp::meta::concepts::signature::HasBegin<_ArrayBase>>
		&& ::llcpp::meta::traits::conditional_value_bool_v<_ENABLE_NO_CONST,
			::llcpp::TRUE,
			::llcpp::meta::concepts::signature::HasEnd<_ArrayBase>>
class ListBody : public _ArrayBase {
	#pragma region Types
	public:
		// Class related
		using _MyType			= ListBody;
		using ArrayBase			= _ArrayBase;

		// Types
		using T					= ArrayBase::value_type;
		using type				= T;
		using value_type		= T;

		using reference			= ::llcpp::meta::traits::input<T>;
		using iterator			= ::llcpp::meta::traits::conditional_t<
			_USE_OBJECT_ITERATOR,
			::llcpp::meta::utils::PointerIterator<T, ::llcpp::FALSE>,
			T*
		>;
		using riterator			= ::llcpp::meta::utils::PointerIterator<T, ::llcpp::TRUE>;

		using const_reference	= ::llcpp::meta::traits::cinput<T>;
		using const_iterator = ::llcpp::meta::traits::conditional_t<
			_USE_OBJECT_ITERATOR,
			::llcpp::meta::utils::ConstPointerIterator<T, ::llcpp::FALSE>,
			const T*
		>;
		using reference_const_iterator = ::llcpp::meta::traits::conditional_t<
			_USE_OBJECT_ITERATOR,
			const_iterator&,
			const_iterator
		>;
		using const_riterator	= ::llcpp::meta::utils::ConstPointerIterator<T, ::llcpp::TRUE>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t ENABLE_NO_CONST		= _ENABLE_NO_CONST;
		static constexpr ll_bool_t USE_OBJECT_ITERATOR	= _USE_OBJECT_ITERATOR;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr ListBody() noexcept
			: ArrayBase()
		{}
		template<class... Args>
			requires ::std::is_nothrow_constructible_v<ArrayBase, Args...>
		constexpr ListBody(Args&&... args) noexcept
			: ArrayBase(::std::forward<Args>(args)...)
		{}
		constexpr ~ListBody() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ListBody(const ListBody& other) noexcept
			: ArrayBase(::std::forward<const ArrayBase&>(other))
		{}
		constexpr ListBody& operator=(const ListBody& other) noexcept {
			ArrayBase::operator=(::std::forward<const ArrayBase&>(other));
			return *this;
		}
		constexpr ListBody(ListBody&& other) noexcept
			: ArrayBase(::std::forward<ArrayBase&&>(other))
		{}
		constexpr ListBody& operator=(ListBody&& other) noexcept {
			ArrayBase::operator=(::std::forward<ArrayBase&&>(other));
			return *this;
		}

		constexpr ListBody(volatile const ListBody& other) noexcept = delete;
		constexpr ListBody& operator=(volatile const ListBody& other) noexcept = delete;
		constexpr ListBody(volatile ListBody&& other) noexcept = delete;
		constexpr ListBody& operator=(volatile ListBody&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const ListBody* () const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator ListBody* () noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Getters
	public:
		// Can generate an exception/log if enabled
		__LL_NODISCARD__ constexpr iterator get(const usize position) noexcept requires(!ENABLE_NO_CONST) {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return this->begin() + position;
		}
		// Can generate an exception/log if enabled
		__LL_NODISCARD__ constexpr const_iterator get(const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return this->begin() + position;
		}
		// Can generate an exception/log if enabled
		__LL_NODISCARD__ constexpr ListBody get(const usize first, const usize last) noexcept requires(!ENABLE_NO_CONST) {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return ListBody(this->get(first), this->get(last));
		}
		// Can generate an exception/log if enabled
		__LL_NODISCARD__ constexpr ListBody get(const usize first, const usize last) const noexcept requires(ENABLE_NO_CONST) {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return ListBody(this->get(first), this->get(last));
		}
		// Use reverse iterator container
		// Can generate an exception/log if enabled
		__LL_NODISCARD__ constexpr riterator rget(const usize position) noexcept requires(!ENABLE_NO_CONST) {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return this->rend() + position;
		}
		// Use reverse iterator container
		// Can generate an exception/log if enabled
		__LL_NODISCARD__ constexpr const_riterator rget(const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return this->rend() + position;
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr ListBody substr(const usize first, const usize last) noexcept requires(!ENABLE_NO_CONST) {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return this->get(first, last);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr ListBody substr(const usize first, const usize last) const noexcept requires(ENABLE_NO_CONST) {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return this->get(first, last);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr reference operator[](const usize position) noexcept requires(!ENABLE_NO_CONST) {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return *this->get(position);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr const_reference operator[](const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return *this->get(position);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		// Non-standard operator
		__LL_NODISCARD__ constexpr reference operator^(const usize position) noexcept requires(!ENABLE_NO_CONST) {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return *this->rget(position);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		// Non-standard operator
		__LL_NODISCARD__ constexpr const_reference operator^(const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return *this->rget(position);
		}


#if __LL_REAL_CXX23 == 1
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr ListBody operator[](const usize first, const usize last) noexcept requires(!ENABLE_NO_CONST) {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return this->substr(first, last);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr ListBody operator[](const usize first, const usize last) const noexcept requires(ENABLE_NO_CONST) {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return this->substr(first, last);
		}

#endif // __LL_REAL_CXX23

		#pragma endregion
		#pragma region Countable
	public:
		__LL_NODISCARD__ constexpr usize size() const noexcept {
			if constexpr (::llcpp::meta::concepts::signature::HasSize<ArrayBase>)
				return ArrayBase::size();
			else return static_cast<usize>(this->end() - this->begin());
		}
		__LL_NODISCARD__ constexpr usize lenght() const noexcept { return this->size(); }
		__LL_NODISCARD__ constexpr usize count() const noexcept { return this->size(); }

		__LL_NODISCARD__ constexpr ll_bool_t inRange(const usize position) const noexcept {
			if constexpr (::llcpp::meta::concepts::signature::HasInRange<ArrayBase, usize, ll_bool_t>)
				return ArrayBase::inRange(position);
			else return position < this->size();
		}
		__LL_NODISCARD__ constexpr ll_bool_t inRange(reference_const_iterator data) const noexcept requires(!USE_OBJECT_ITERATOR) {
			if constexpr (::llcpp::meta::concepts::signature::HasInRange<ArrayBase, const T*, ll_bool_t>)
				return ArrayBase::inRange(data);
			else return this->begin() <= data && data <= this->end();
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const usize position) const noexcept {
			return this->inRange(position);
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(reference_const_iterator data) const noexcept requires(!USE_OBJECT_ITERATOR) {
			return this->inRange(data);
		}

		#pragma endregion
		#pragma region std
	public:
		__LL_NODISCARD__ constexpr riterator rbegin() noexcept requires(!ENABLE_NO_CONST) { return this->begin(); }
		__LL_NODISCARD__ constexpr const_riterator rbegin() const noexcept { return this->begin(); }
		__LL_NODISCARD__ constexpr riterator rend() noexcept requires(!ENABLE_NO_CONST) { return this->end() - 1; }
		__LL_NODISCARD__ constexpr const_riterator rend() const noexcept { return this->end() - 1; }
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept {
			if constexpr (::llcpp::meta::concepts::signature::HasEmpty<ArrayBase, ll_bool_t>)
				return ArrayBase::empty();
			else return this->begin() == this->end();
		}

		#pragma endregion
		#pragma region Other
	public:
		__LL_NODISCARD__ constexpr ::llcpp::meta::ValidType validationType() const noexcept {
			if constexpr (::llcpp::meta::concepts::signature::HasValidationType<ArrayBase>)
				return ArrayBase::validationType();
			else return
				this->begin() <= this->end()
				? ::llcpp::meta::ValidType::Valid
				: ::llcpp::meta::ValidType::Invalid;
		}
		//constexpr void makeInvalid() noexcept { this->clear(); }
		//__LL_NODISCARD__ constexpr ll_bool_t resetValidation(const_pointer mem, const_pointer mem_end) noexcept {
		//	CHECK_RESET_VALIDATION;
		//	this->setMem(mem);
		//	this->setMemEnd(mem_end);
		//}

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

template<
	class _T,
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_CPAV
>
class ConstArrayBase {
	#pragma region Types
	public:
		// Class related
		using _MyType	= ConstArrayBase;

		// Types
		using T					= _T;
		using type				= T;
		using value_type		= T;
		using const_pointer		= const T*;
		using const_iterator	= const_pointer;

		//using reference			= ::llcpp::meta::traits::input<T>;
		//using const_reference	= ::llcpp::meta::traits::input<const_T>;
		//
		//using pointer			= T*;
		//
		//using iterator			= pointer;
		//
		//using riterator			= ::llcpp::meta::utils::PointerIterator<T, ::llcpp::TRUE>;
		//using const_riterator	= ::llcpp::meta::utils::PointerIterator<const_T, ::llcpp::TRUE>;
		//
		//using ConstArray		= Array<const_T, _TYPE_CHECKER>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = _TYPE_CHECKER;

	#pragma endregion
	#pragma region Asserts
	public:
		//static_assert(::llcpp::meta::traits::is_valid_type_checker_v<T, TYPE_CHECKER>,
		//	"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Attributes
	private:
		const_pointer mem;
		const_pointer mem_end;

	#pragma endregion
	#pragma region Functions
		#pragma region Functions
	private:
		constexpr void simpleClear() noexcept {
			this->setMem(::llcpp::NULL_VALUE<decltype(this->mem)>);
			this->setMemEnd(::llcpp::NULL_VALUE<decltype(this->mem_end)>);
		}
		constexpr void setMem(const_pointer mem) noexcept { this->mem = mem; }
		constexpr void setMemEnd(const_pointer mem_end) noexcept { this->mem_end = mem_end; }

		#pragma endregion
		#pragma region Constructors
	public:
		constexpr ConstArrayBase() noexcept
			: mem(::llcpp::NULL_VALUE<decltype(mem)>)
			, mem_end(::llcpp::NULL_VALUE<decltype(mem_end)>)
		{}
		constexpr ConstArrayBase(const_pointer mem, const_pointer mem_end) noexcept
			: mem(mem)
			, mem_end(mem_end)
		{}
		constexpr ConstArrayBase(const_pointer mem, const usize len) noexcept
			: ConstArrayBase(mem, mem + len)
		{}
		template<usize N, class U>
			requires ::std::is_same_v<T, U>
		explicit constexpr ConstArrayBase(const T (&v)[N]) noexcept
			: ConstArrayBase(v, v + N)
		{}
		constexpr ~ConstArrayBase() noexcept {
			if constexpr (::llcpp::CLEAR_POINTERS_ON_DESTRUCTION)
				this->simpleClear();
		}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ConstArrayBase(const ConstArrayBase& other) noexcept
			: ConstArrayBase(other.mem, other.mem_end)
		{}
		constexpr ConstArrayBase& operator=(const ConstArrayBase& other) noexcept {
			this->resetValidation(other.cbegin(), other.cend());
			return *this;
		}
		constexpr ConstArrayBase(ConstArrayBase&& other) noexcept
			: ConstArrayBase(other)
		{ other.simpleClear(); }
		constexpr ConstArrayBase& operator=(ConstArrayBase&& other) noexcept {
			this->resetValidation(other.cbegin(), other.cend());
			other.simpleClear();
			return *this;
		}

		constexpr ConstArrayBase(volatile const ConstArrayBase& other) noexcept = delete;
		constexpr ConstArrayBase& operator=(volatile const ConstArrayBase& other) noexcept = delete;
		constexpr ConstArrayBase(volatile ConstArrayBase&& other) noexcept = delete;
		constexpr ConstArrayBase& operator=(volatile ConstArrayBase&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const ConstArrayBase*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator ConstArrayBase*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region std
	public:
		__LL_NODISCARD__ constexpr const_pointer data() const noexcept { return this->mem; }
		__LL_NODISCARD__ constexpr const_iterator begin() const noexcept { return this->data(); }
		__LL_NODISCARD__ constexpr const_iterator end() const noexcept { return this->mem_end; }
		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept { return this->begin() == this->end(); }

		#pragma endregion
		#pragma region Other
	public:
		__LL_NODISCARD__ constexpr ::llcpp::meta::ValidType validationType() const noexcept {
			return this->begin() <= this->end() ? ::llcpp::meta::ValidType::Valid : ::llcpp::meta::ValidType::Invalid;
		}
		constexpr void makeInvalid() noexcept { this->simpleClear(); }
		constexpr void clear() noexcept { this->makeInvalid(); }
		__LL_NODISCARD__ constexpr ll_bool_t resetValidation(const_pointer mem, const_pointer mem_end) noexcept {
			CHECK_RESET_VALIDATION;
			this->setMem(mem);
			this->setMemEnd(mem_end);
		}

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

template<
	class _T,
	::llcpp::meta::attributes::checker_attributes_t _TYPE_CHECKER =
		::llcpp::meta::attributes::checker::IGNORE_CPAV
>
class ArrayBase {
	#pragma region Types
	public:
		// Class related
		using _MyType	= ArrayBase;

		// Types
		using T					= _T;
		using type				= T;
		using value_type		= T;

		using pointer			= T*;
		using iterator			= pointer;

		using const_pointer		= const T*;
		using const_iterator	= const_pointer;

		//using reference			= ::llcpp::meta::traits::input<T>;
		//using const_reference	= ::llcpp::meta::traits::input<const_T>;
		//
		//using pointer			= T*;
		//
		//using iterator			= pointer;
		//
		//using riterator			= ::llcpp::meta::utils::PointerIterator<T, ::llcpp::TRUE>;
		//using const_riterator	= ::llcpp::meta::utils::PointerIterator<const_T, ::llcpp::TRUE>;
		//
		//using ConstArray		= Array<const_T, _TYPE_CHECKER>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ::llcpp::meta::attributes::checker_attributes_t TYPE_CHECKER = _TYPE_CHECKER;

	#pragma endregion
	#pragma region Asserts
	public:
		//static_assert(::llcpp::meta::traits::is_valid_type_checker_v<T, TYPE_CHECKER>,
		//	"type_checker<T> detected an invalid type!");

	#pragma endregion
	#pragma region Attributes
	private:
		pointer mem;
		pointer mem_end;

	#pragma endregion
	#pragma region Functions
		#pragma region Functions
	private:
		constexpr void simpleClear() noexcept {
			this->setMem(::llcpp::NULL_VALUE<decltype(this->mem)>);
			this->setMemEnd(::llcpp::NULL_VALUE<decltype(this->mem_end)>);
		}
		constexpr void setMem(pointer mem) noexcept { this->mem = mem; }
		constexpr void setMemEnd(pointer mem_end) noexcept { this->mem_end = mem_end; }

		#pragma endregion
		#pragma region Constructors
	public:
		constexpr ArrayBase() noexcept
			: mem(::llcpp::NULL_VALUE<decltype(mem)>)
			, mem_end(::llcpp::NULL_VALUE<decltype(mem_end)>)
		{}
		constexpr ArrayBase(pointer mem, pointer mem_end) noexcept
			: mem(mem)
			, mem_end(mem_end)
		{}
		constexpr ArrayBase(pointer mem, const usize len) noexcept
			: ArrayBase(mem, mem + len)
		{}
		template<usize N, class U>
			requires ::std::is_same_v<T, U>
		explicit constexpr ArrayBase(T (&v)[N]) noexcept
			: ArrayBase(v, v + N)
		{}
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
		__LL_NODISCARD__ constexpr pointer data() noexcept { return this->mem; }
		__LL_NODISCARD__ constexpr iterator begin() noexcept { return this->data(); }
		__LL_NODISCARD__ constexpr iterator end() noexcept { return this->mem_end; }

		__LL_NODISCARD__ constexpr const_pointer data() const noexcept { return this->mem; }
		__LL_NODISCARD__ constexpr const_iterator begin() const noexcept { return this->data(); }
		__LL_NODISCARD__ constexpr const_iterator end() const noexcept { return this->mem_end; }

		__LL_NODISCARD__ constexpr ll_bool_t empty() const noexcept { return this->begin() == this->end(); }

		#pragma endregion
		#pragma region Other
	public:
		__LL_NODISCARD__ constexpr ::llcpp::meta::ValidType validationType() const noexcept {
			return this->begin() <= this->end() ? ::llcpp::meta::ValidType::Valid : ::llcpp::meta::ValidType::Invalid;
		}
		constexpr void makeInvalid() noexcept { this->simpleClear(); }
		constexpr void clear() noexcept { this->makeInvalid(); }
		__LL_NODISCARD__ constexpr ll_bool_t resetValidation(pointer mem, pointer mem_end) noexcept {
			CHECK_RESET_VALIDATION;
			this->setMem(mem);
			this->setMemEnd(mem_end);
		}

		#pragma endregion

		#pragma endregion

	#pragma endregion
};


using Chars			= ArrayBase<char>;
using ConstChars	= ConstArrayBase<char>;

using Str			= ListBody<Chars, ::llcpp::FALSE, ::llcpp::FALSE>;
using ConstStr		= ListBody<ConstChars, ::llcpp::TRUE, ::llcpp::FALSE>;

constexpr ConstStr cstr = ConstStr((const char*)"Holo", 5ull);

#undef CHECK_POSITION_DEBUG_EXCEPTION
#undef CHECK_POSITIONS_DEBUG_EXCEPTION
#undef CHECK_RESET_VALIDATION

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAY_HPP_
