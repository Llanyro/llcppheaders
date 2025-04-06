//////////////////////////////////////////////
//	IteratorUtils.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ITERATORUTILS_INCOMPLETE_HPP_)
	#if LLANYLIB_ITERATORUTILS_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ITERATORUTILS_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "IteratorUtils.hpp(incomplete) version error!"
		#else
			#error "IteratorUtils.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ITERATORUTILS_INCOMPLETE_MAYOR_ || LLANYLIB_ITERATORUTILS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ITERATORUTILS_INCOMPLETE_HPP_)
	#define LLANYLIB_ITERATORUTILS_INCOMPLETE_HPP_
	#define LLANYLIB_ITERATORUTILS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ITERATORUTILS_INCOMPLETE_MINOR_ 0

#include "../traits_base/checker/traits_validate_checker.hpp"

namespace llcpp {
namespace meta {
namespace utils {

template<class _ExtraFunctions, class _Iterator, class _IteratorEnd = _Iterator>
class IteratorUtils;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ITERATORUTILS_HPP_)
	#if LLANYLIB_ITERATORUTILS_MAYOR_ != 12 || LLANYLIB_ITERATORUTILS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "IteratorUtils.hpp version error!"
		#else
			#error "IteratorUtils.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ITERATORUTILS_MAYOR_ || LLANYLIB_ITERATORUTILS_MINOR_

#else
	#define LLANYLIB_ITERATORUTILS_HPP_
	#define LLANYLIB_ITERATORUTILS_MAYOR_ 12
	#define LLANYLIB_ITERATORUTILS_MINOR_ 0

#include "../traits/ValidationChecker.hpp"

namespace llcpp {
namespace meta {
namespace traits {

namespace __traits__ {

template<class _Iterator>
constexpr auto getIteratorType() noexcept {
	if constexpr (::std::is_class_v<_Iterator>)
		return ::llcpp::meta::traits::TypeContainer<typename _Iterator::value_type&>{};
	else if constexpr (::std::is_pointer_v<_Iterator>)
		return ::llcpp::meta::traits::TypeContainer<::std::remove_pointer_t<_Iterator>&>{};
	else {
		static_assert(::std::is_class_v<_Iterator> || ::std::is_pointer_v<_Iterator>,
			"Iterator must be a class or a pointer!");
	}
}

} // namespace __traits__

template<class _Iterator>
using iterator_t = decltype(::llcpp::meta::traits::__traits__::getIteratorType<_Iterator>())::T;

} // namespace trits
namespace utils {

template<
	class _Iterator,
	class _IteratorEnd = _Iterator,
	class _ExtraFunctions = ::llcpp::DummyClass
>
	requires ::llcpp::meta::concepts::is_object::IsIterator<_Iterator>
		&& ::llcpp::meta::concepts::is_object::IsIterator<_IteratorEnd>
class IteratorUtils
	: public ::llcpp::ClusterTag
	, public ::llcpp::meta::traits::ValidationWrapper<_ExtraFunctions, ::llcpp::AlwaysValidTag>
	, public _ExtraFunctions
{
	#pragma region Types
	public:
		// Class related
		using _MyType			= IteratorUtils;		// This class with template
		using ClusterTag		= ::llcpp::ClusterTag;	// This is a cluster type class
		using ValidTag			= ::llcpp::meta::traits::ValidationWrapper<_ExtraFunctions, ::llcpp::AlwaysValidTag>;
		using ExtraFunctions	= _ExtraFunctions;

		// Types and enums
		using Iterator		= _Iterator;
		using IteratorEnd	= _IteratorEnd;
		using value_type	= decltype(*::std::declval<Iterator>());
		using input_it		= ::llcpp::meta::traits::input<Iterator>;
		using input_itend	= ::llcpp::meta::traits::input<IteratorEnd>;
		using ResultPair	= ::llcpp::meta::pair<LoopResult, Iterator>;
		template<ll_bool_t GET_DATA>
		using ForeachResult = ::llcpp::meta::traits::conditional_t<GET_DATA, ResultPair, LoopResult>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t HAS_OPERATOR_GEQ =
			::llcpp::meta::concepts::signature::HasOperatorGreaterEqual<Iterator, IteratorEnd, ll_bool_t>;
		static constexpr ll_bool_t HAS_OPERATOR_EQ =
			::llcpp::meta::concepts::signature::HasOperatorEqual<Iterator, IteratorEnd, ll_bool_t>;
		static constexpr ll_bool_t HAS_OPERATOR_LEQ =
			::llcpp::meta::concepts::signature::HasOperatorLowerEqual<IteratorEnd, Iterator, ll_bool_t>;
		static constexpr ll_bool_t HAS_OPERATOR_EQ_End =
			::llcpp::meta::concepts::signature::HasOperatorEqual<IteratorEnd, Iterator, ll_bool_t>;

	#pragma endregion
	#pragma region Asserts
	public:

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr IteratorUtils() noexcept
			: ClusterTag()
			, ValidTag()
			, ExtraFunctions()
		{}
		template<class... Args>
		constexpr IteratorUtils(Args&&... args) noexcept
			: ClusterTag()
			, ValidTag()
			, ExtraFunctions(::std::forward<Args>(args)...)
		{}
		constexpr ~IteratorUtils() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr IteratorUtils(const IteratorUtils& other) noexcept
			: ClusterTag()
			, ValidTag()
			, ExtraFunctions(::std::forward<const ExtraFunctions&>(other))
		{}
		constexpr IteratorUtils& operator=(const IteratorUtils& other) noexcept {
			ExtraFunctions::operator=(::std::forward<const ExtraFunctions&>(other));
			return *this;
		}
		constexpr IteratorUtils(IteratorUtils&& other) noexcept
			: ClusterTag()
			, ValidTag()
			, ExtraFunctions(::std::forward<ExtraFunctions&&>(other))
		{}
		constexpr IteratorUtils& operator=(IteratorUtils&& other) noexcept {
			ExtraFunctions::operator=(::std::forward<ExtraFunctions&&>(other));
			return *this;
		}

		constexpr IteratorUtils(const volatile IteratorUtils&) noexcept = delete;
		constexpr IteratorUtils& operator=(const volatile IteratorUtils&) noexcept = delete;
		constexpr IteratorUtils(volatile IteratorUtils&&) noexcept = delete;
		constexpr IteratorUtils& operator=(volatile IteratorUtils&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const IteratorUtils*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator IteratorUtils*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		// Checks if iterator is end or overflows it
		// By standard iterators (objects) will point to end/begin if operator++/operator-- is used
		__LL_NODISCARD__ constexpr ll_bool_t isEnd(input_it it, input_itend end) const noexcept {
			if constexpr (::std::is_pointer_v<Iterator> && ::std::is_pointer_v<IteratorEnd>)
				return it >= end;
			else if constexpr (::std::is_pointer_v<IteratorEnd>) {
				if constexpr (_MyType::HAS_OPERATOR_GEQ)
					return it >= end;
				else {
					static_assert(_MyType::HAS_OPERATOR_GEQ,
						"Iterator must be comparables with a pointer");
					return ::llcpp::FALSE;
				}
			}
			else if constexpr (::std::is_pointer_v<Iterator>) {
				if constexpr (_MyType::HAS_OPERATOR_LEQ)
					return end <= it;
				else {
					static_assert(_MyType::HAS_OPERATOR_LEQ,
						"Iterator must be comparables with a pointer");
					return ::llcpp::FALSE;
				}
			}
			else {
				if constexpr (_MyType::HAS_OPERATOR_EQ)
					return it == end;
				else if constexpr (_MyType::HAS_OPERATOR_EQ_End)
					return end == it;
				else {
					static_assert(_MyType::HAS_OPERATOR_EQ_End,
						"Iterators must be comparables");
					return ::llcpp::FALSE;
				}
			}
		}

		// 
		template<ll_bool_t GET_DATA = ::llcpp::FALSE>
			requires ::llcpp::meta::concepts::signature::HasForeachOperation<ExtraFunctions, value_type, LoopResult>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreach(input_it begin, input_itend end) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (this->isEnd(begin, end)) {
					if constexpr (GET_DATA) return ResultPair{ LoopResult::BeginError, begin };
					else return LoopResult::BeginError;
				}
			}
		
			LoopResult res = LoopResult::BeginError;
			Iterator it = begin;
			for (; !this->isEnd(it, end); ++it) {
				res = ExtraFunctions::foreachOperation(*it);
				if (res != LoopResult::Conntinue) {
					if constexpr (GET_DATA)
						return ResultPair{ res, it };
					else return res;
				}
			}
		
			if (res == LoopResult::Conntinue) res = LoopResult::Ok;
			if constexpr (GET_DATA)
				return ResultPair{ res , end };
			else return res;
		}

#if defined(LLANYLIB_TUPLE_HPP_)
		template<ll_bool_t GET_DATA = ::llcpp::FALSE, class... OtherIterators>
			requires ::llcpp::meta::concepts::signature::HasForeachOperationExtra<ExtraFunctions, value_type, ::llcpp::meta::utils::Tuple<OtherIterators...>&, LoopResult>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreach(input_it begin, input_itend end, OtherIterators... other) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (this->isEnd(begin, end)) {
					if constexpr (GET_DATA) return ResultPair{ LoopResult::BeginError, begin };
					else return LoopResult::BeginError;
				}
			}

			// Include all other iterators in a tuple
			::llcpp::meta::utils::Tuple<OtherIterators...> tuple(other...);
		
			LoopResult res = LoopResult::BeginError;
			Iterator it = begin;
			for (; !this->isEnd(it, end); ++it, ++tuple) {
				res = ExtraFunctions::foreachOperation(*it, tuple);
				if (res != LoopResult::Conntinue) {
					if constexpr (GET_DATA)
						return ResultPair{ res, it };
					else return res;
				}
			}
		
			if (res == LoopResult::Conntinue) res = LoopResult::Ok;
			if constexpr (GET_DATA)
				return ResultPair{ res , end };
			else return res;
		}
#endif // LLANYLIB_TUPLE_HPP_


		#pragma endregion

	#pragma endregion
};

template<class T>
class ZeroSetter {
	public:
		constexpr LoopResult foreachOperation(T& t) const noexcept {
			t = ::llcpp::ZERO_VALUE<T>;
			return LoopResult::Conntinue;
		}
};

template<class Iterator, class IteratorEnd = Iterator>
	requires ::llcpp::meta::concepts::is_object::IsIterator<Iterator>
		&& ::llcpp::meta::concepts::is_object::IsIterator<IteratorEnd>
using IteratorCleaner =
	::llcpp::meta::utils::IteratorUtils<
		Iterator,
		IteratorEnd,
		::llcpp::meta::utils::ZeroSetter<::std::remove_reference_t<decltype(*::std::declval<Iterator>())>>
	>;

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ITERATORUTILS_HPP_
