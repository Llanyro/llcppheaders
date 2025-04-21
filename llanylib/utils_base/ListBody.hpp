//////////////////////////////////////////////
//	ListBody.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_LISTBODY_INCOMPLETE_HPP_)
	#if LLANYLIB_LISTBODY_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_LISTBODY_INCOMPLETE_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "ListBody.hpp(incomplete) version error!"
		#else
			#error "ListBody.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_LISTBODY_INCOMPLETE_MAYOR_ || LLANYLIB_LISTBODY_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_LISTBODY_INCOMPLETE_HPP_)
	#define LLANYLIB_LISTBODY_INCOMPLETE_HPP_
	#define LLANYLIB_LISTBODY_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_LISTBODY_INCOMPLETE_MINOR_ 0

#include "../traits_base/checker.hpp"
#include "../concepts/concepts.hpp"
#include "PointerIterator.hpp"
#include "Exceptions.hpp"
	
namespace llcpp {
namespace meta {
namespace utils {

template<class _ArrayBase, ll_bool_t _ENABLE_NO_CONST = ::llcpp::LL_TRUE, ll_bool_t _USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE>
class ListBody;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_LISTBODY_HPP_)
	#if LLANYLIB_LISTBODY_MAYOR_ != 12 || LLANYLIB_LISTBODY_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "ListBody.hpp version error!"
		#else
			#error "ListBody.hpp version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_LISTBODY_MAYOR_ || LLANYLIB_LISTBODY_MINOR_

#else
	#define LLANYLIB_LISTBODY_HPP_
	#define LLANYLIB_LISTBODY_MAYOR_ 12
	#define LLANYLIB_LISTBODY_MINOR_ 0

#include "../traits_base/checker.hpp"
#include "../concepts/concepts.hpp"
#include "PointerIterator.hpp"
#include "Exceptions.hpp"

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

#pragma endregion

namespace llcpp {
namespace meta {
namespace utils {

template<class _ArrayBase, ll_bool_t _ENABLE_NO_CONST = ::llcpp::LL_TRUE, ll_bool_t _USE_OBJECT_ITERATOR = ::llcpp::LL_FALSE>
	requires
		::llcpp::meta::concepts::base::HasValueType<_ArrayBase>
		&& ::llcpp::meta::concepts::signature::HasConstBegin<_ArrayBase>
		&& ::llcpp::meta::concepts::signature::HasConstEnd<_ArrayBase>
		&& ::llcpp::meta::traits::is_valid_constructor_checker_v<_ArrayBase>
		&& ::llcpp::meta::traits::conditional_value_bool_v<_ENABLE_NO_CONST,
			::llcpp::LL_TRUE,
			::llcpp::meta::concepts::signature::HasBegin<_ArrayBase>>
		&& ::llcpp::meta::traits::conditional_value_bool_v<_ENABLE_NO_CONST,
			::llcpp::LL_TRUE,
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
			::llcpp::meta::utils::PointerIterator<T, ::llcpp::LL_FALSE>,
			T*
		>;
		using riterator			= ::llcpp::meta::utils::PointerIterator<T, ::llcpp::LL_TRUE>;

		using const_reference	= ::llcpp::meta::traits::cinput<T>;
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

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t ENABLE_NO_CONST		= _ENABLE_NO_CONST;
		static constexpr ll_bool_t USE_OBJECT_ITERATOR	= _USE_OBJECT_ITERATOR;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr ListBody() noexcept = default;
		template<class... Args>
		constexpr ListBody(Args&&... args) noexcept requires(::std::is_nothrow_constructible_v<ArrayBase, Args...>)
			: ArrayBase(::std::forward<Args>(args)...)
		{}
		constexpr ~ListBody() noexcept = default;

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
		__LL_NODISCARD__ constexpr iterator get(const usize position) noexcept requires(ENABLE_NO_CONST) {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return this->begin() + position;
		}
		// Can generate an exception/log if enabled
		__LL_NODISCARD__ constexpr const_iterator get(const usize position) const noexcept {
			CHECK_POSITION_DEBUG_EXCEPTION;
			return this->begin() + position;
		}
		// Can generate an exception/log if enabled
		__LL_NODISCARD__ constexpr ListBody get(const usize first, const usize last) noexcept requires(ENABLE_NO_CONST) {
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
		__LL_NODISCARD__ constexpr riterator rget(const usize position) noexcept requires(ENABLE_NO_CONST) {
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
		__LL_NODISCARD__ constexpr ListBody substr(const usize first, const usize last) noexcept requires(ENABLE_NO_CONST) {
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
		__LL_NODISCARD__ constexpr reference operator[](const usize position) noexcept requires(ENABLE_NO_CONST) {
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
		__LL_NODISCARD__ constexpr reference operator^(const usize position) noexcept requires(ENABLE_NO_CONST) {
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
		__LL_NODISCARD__ constexpr ListBody operator[](const usize first, const usize last) noexcept requires(ENABLE_NO_CONST) {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return this->substr(first, last);
		}
		// Use reverse iterator container
		// Can generate an exception/log if enable
		__LL_NODISCARD__ constexpr ListBody operator[](const usize first, const usize last) const noexcept requires(ENABLE_NO_CONST) {
			CHECK_POSITIONS_DEBUG_EXCEPTION;
			return this->substr(first, last);
		}

#endif // __LL_REAL_CXX23 == 1

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
		__LL_NODISCARD__ constexpr ll_bool_t inRange(reference_const_iterator data) const noexcept {
			if constexpr (::llcpp::meta::concepts::signature::HasInRange<ArrayBase, const T*, ll_bool_t>)
				return ArrayBase::inRange(data);
			else return this->begin() <= data && data <= this->end();
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const usize position) const noexcept {
			return this->inRange(position);
		}
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(reference_const_iterator data) const noexcept {
			return this->inRange(data);
		}

		#pragma endregion
		#pragma region std
	public:
		__LL_NODISCARD__ constexpr riterator rbegin() noexcept requires(ENABLE_NO_CONST) {
			return this->begin();
		}
		__LL_NODISCARD__ constexpr const_riterator rbegin() const noexcept { return this->begin(); }
		__LL_NODISCARD__ constexpr riterator rend() noexcept requires(ENABLE_NO_CONST) {
			return this->end() - 1;
		}
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

} // namespace utils
} // namespace meta
} // namespace llcpp

#undef CHECK_POSITION_DEBUG_EXCEPTION
#undef CHECK_POSITIONS_DEBUG_EXCEPTION

#endif // LLANYLIB_LISTBODY_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
