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
		#if __LL_REAL_CXX23 == 1
			#warning "IteratorUtils.hpp(incomplete) version error!"
		#else
			#error "IteratorUtils.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ITERATORUTILS_INCOMPLETE_MAYOR_ || LLANYLIB_ITERATORUTILS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ITERATORUTILS_INCOMPLETE_HPP_)
	#define LLANYLIB_ITERATORUTILS_INCOMPLETE_HPP_
	#define LLANYLIB_ITERATORUTILS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ITERATORUTILS_INCOMPLETE_MINOR_ 0

#include "../traits/ValidationChecker.hpp"
#include "../traits_base/checker.hpp"
	
namespace llcpp {
namespace meta {
namespace utils {

template<
	class _Iterator,
	class _IteratorEnd = _Iterator,
	class _ExtraFunctions = ::llcpp::DummyClass
>
class IteratorUtils;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ITERATORUTILS_HPP_)
	#if LLANYLIB_ITERATORUTILS_MAYOR_ != 12 || LLANYLIB_ITERATORUTILS_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "IteratorUtils.hpp version error!"
		#else
			#error "IteratorUtils.hpp version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ITERATORUTILS_MAYOR_ || LLANYLIB_ITERATORUTILS_MINOR_

#else
	#define LLANYLIB_ITERATORUTILS_HPP_
	#define LLANYLIB_ITERATORUTILS_MAYOR_ 12
	#define LLANYLIB_ITERATORUTILS_MINOR_ 0

#include "../traits/ValidationChecker.hpp"
#include "../traits_base/checker.hpp"

namespace llcpp {
namespace meta {
namespace utils {

template<
	class _Iterator,
	class _IteratorEnd = _Iterator,
	class _ExtraFunctions = ::llcpp::DummyClass
>
	requires
		::llcpp::meta::concepts::is_object::IsIterator<_Iterator>
		&& ::llcpp::meta::concepts::is_object::IsIterator<_IteratorEnd>
		&&::llcpp::meta::traits::is_valid_constructor_checker_v<_ExtraFunctions>
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
		using input_it		= ::llcpp::meta::traits::conditional_t<::std::is_class_v<Iterator>, Iterator&&, Iterator>;
		using input_itend	= ::llcpp::meta::traits::conditional_t<::std::is_class_v<IteratorEnd>, IteratorEnd&&, Iterator>;
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
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr IteratorUtils() noexcept = default;
		template<class... Args>
		constexpr IteratorUtils(Args&&... args) noexcept requires(::std::is_nothrow_constructible_v<ExtraFunctions, Args...>)
			: ClusterTag()
			, ValidTag()
			, ExtraFunctions(::std::forward<Args>(args)...)
		{}
		constexpr ~IteratorUtils() noexcept = default;

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
		__LL_NODISCARD__ constexpr ll_bool_t isEnd(Iterator& it, IteratorEnd& end) const noexcept {
			if constexpr (::std::is_pointer_v<Iterator> && ::std::is_pointer_v<IteratorEnd>)
				return it >= end;
			else if constexpr (::std::is_pointer_v<IteratorEnd>) {
				if constexpr (_MyType::HAS_OPERATOR_GEQ)
					return it >= end;
				else {
					static_assert(_MyType::HAS_OPERATOR_GEQ,
						"Iterator must be comparables with a pointer");
					return ::llcpp::LL_FALSE;
				}
			}
			else if constexpr (::std::is_pointer_v<Iterator>) {
				if constexpr (_MyType::HAS_OPERATOR_LEQ)
					return end <= it;
				else {
					static_assert(_MyType::HAS_OPERATOR_LEQ,
						"Iterator must be comparables with a pointer");
					return ::llcpp::LL_FALSE;
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
					return ::llcpp::LL_FALSE;
				}
			}
		}

		// Iterate over a list with current class
		template<ll_bool_t GET_DATA = ::llcpp::LL_FALSE>
			requires ::llcpp::meta::concepts::signature::HasForeachOperation<ExtraFunctions, value_type, LoopResult>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreach(input_it begin, input_itend end) const noexcept {
			// Can be this removed (?)
			// [TOCHECK]
			/*if constexpr (::llcpp::DEBUG) {
				if (this->isEnd(begin, end)) {
					if constexpr (GET_DATA) return ResultPair{ LoopResult::BeginError, begin };
					else return LoopResult::BeginError;
				}
			}*/
		
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
				return ResultPair{ res , it };
			else return res;
		}
		// [TOCHECK]
		// Iterate over a list with provided class
		template<class IteratorFunctionObject, ll_bool_t GET_DATA = ::llcpp::LL_FALSE>
			requires ::llcpp::meta::concepts::signature::HasForeachOperation<const IteratorFunctionObject, value_type, LoopResult>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreach(const IteratorFunctionObject& function, input_it begin, input_itend end) const noexcept {
			LoopResult res = LoopResult::BeginError;
			Iterator it = begin;
			for (; !this->isEnd(it, end); ++it) {
				res = function.foreachOperation(*it);
				if (res != LoopResult::Conntinue) {
					if constexpr (GET_DATA)
						return ResultPair{ res, it };
					else return res;
				}
			}
		
			if (res == LoopResult::Conntinue) res = LoopResult::Ok;
			if constexpr (GET_DATA)
				return ResultPair{ res , it };
			else return res;
		}
		template<class IteratorFunctionObject, ll_bool_t GET_DATA = ::llcpp::LL_FALSE>
			requires ::llcpp::meta::concepts::signature::HasForeachOperation<const IteratorFunctionObject, value_type, LoopResult>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreach(input_it begin, input_itend end) const noexcept {
			LoopResult res = LoopResult::BeginError;
			Iterator it = begin;
			for (; !this->isEnd(it, end); ++it) {
				res = IteratorFunctionObject().foreachOperation(*it);
				if (res != LoopResult::Conntinue) {
					if constexpr (GET_DATA)
						return ResultPair{ res, it };
					else return res;
				}
			}
		
			if (res == LoopResult::Conntinue) res = LoopResult::Ok;
			if constexpr (GET_DATA)
				return ResultPair{ res , it };
			else return res;
		}

#if defined(LLANYLIB_TUPLE_HPP_)
		template<ll_bool_t GET_DATA = ::llcpp::LL_FALSE, class... OtherIterators>
			requires ::llcpp::meta::concepts::signature::HasForeachOperationExtra<ExtraFunctions, value_type, ::llcpp::meta::utils::Tuple<OtherIterators...>&, LoopResult>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreachEx(input_it begin, input_itend end, OtherIterators... other) const noexcept {
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
				return ResultPair{ res , it };
			else return res;
		}

#endif // LLANYLIB_TUPLE_HPP_

		#pragma endregion

	#pragma endregion
};

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ITERATORUTILS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
