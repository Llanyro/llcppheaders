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
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "IteratorUtils.hpp(incomplete) version error!"
		#else
			#error "IteratorUtils.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
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
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "IteratorUtils.hpp version error!"
		#else
			#error "IteratorUtils.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ITERATORUTILS_MAYOR_ || LLANYLIB_ITERATORUTILS_MINOR_

#else
	#define LLANYLIB_ITERATORUTILS_HPP_
	#define LLANYLIB_ITERATORUTILS_MAYOR_ 12
	#define LLANYLIB_ITERATORUTILS_MINOR_ 0

#include "../traits/ValidationChecker.hpp"
#include "../traits_base/checker.hpp"

#include "constant_friendly.hpp"

namespace llcpp {
namespace meta {
namespace utils {

template<class _Iterator, class _IteratorEnd = _Iterator, class _ExtraFunctions = ::llcpp::DummyClass>
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
		template<class IT>
		using FixIterator = ::llcpp::meta::traits::conditional_t<::std::is_class_v<IT>, IT&&, IT>;

		using Iterator		= _Iterator;
		using IteratorEnd	= _IteratorEnd;
		using value_type	= decltype(*::std::declval<Iterator>());
		using input_it		= _MyType::FixIterator<Iterator>;
		using input_itend	= _MyType::FixIterator<IteratorEnd>;
		using ResultPair	= ::llcpp::meta::pair<LoopResult, Iterator>;
		template<ll_bool_t GET_DATA>
		using ForeachResult = ::llcpp::meta::traits::conditional_t<GET_DATA, ResultPair, LoopResult>;

	#pragma endregion
	#pragma region Expresions
	public:
		template<class W, class X>
		static constexpr ll_bool_t HAS_OPERATOR_GEQ =
			::llcpp::meta::concepts::signature::HasOperatorGreaterEqual<W, X, ll_bool_t>;
		template<class W, class X>
		static constexpr ll_bool_t HAS_OPERATOR_EQ =
			::llcpp::meta::concepts::signature::HasOperatorEqual<W, X, ll_bool_t>;
		template<class W, class X>
		static constexpr ll_bool_t HAS_OPERATOR_LEQ =
			::llcpp::meta::concepts::signature::HasOperatorLowerEqual<W, X, ll_bool_t>;

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
				if constexpr (_MyType::HAS_OPERATOR_GEQ<Iterator, IteratorEnd>)
					return it >= end;
				else {
					static_assert(_MyType::HAS_OPERATOR_GEQ<Iterator, IteratorEnd>,
						"Iterator must be comparables with a pointer");
					return ::llcpp::LL_FALSE;
				}
			}
			else if constexpr (::std::is_pointer_v<Iterator>) {
				if constexpr (_MyType::HAS_OPERATOR_LEQ<IteratorEnd, Iterator>)
					return end <= it;
				else {
					static_assert(_MyType::HAS_OPERATOR_LEQ<IteratorEnd, Iterator>,
						"Iterator must be comparables with a pointer");
					return ::llcpp::LL_FALSE;
				}
			}
			else {
				if constexpr (_MyType::HAS_OPERATOR_EQ<Iterator, IteratorEnd>)
					return it == end;
				else if constexpr (_MyType::HAS_OPERATOR_EQ<IteratorEnd, Iterator>)
					return end == it;
				else {
					static_assert(_MyType::HAS_OPERATOR_EQ<IteratorEnd, Iterator>,
						"Iterators must be comparables");
					return ::llcpp::LL_FALSE;
				}
			}
		}

		#pragma region Foreach
		// Iterate over a list with current class
		template<ll_bool_t GET_DATA = ::llcpp::LL_FALSE>
			requires ::llcpp::meta::concepts::signature::HasForeachOperation<ExtraFunctions, value_type, LoopResult>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreach(input_it begin, input_itend end) const noexcept {
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
		// Iterate over a list with provided class
		template<class IteratorFunctionObject, ll_bool_t GET_DATA = ::llcpp::LL_FALSE>
			requires ::llcpp::meta::concepts::signature::HasForeachOperation<const IteratorFunctionObject, value_type, LoopResult>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreach(const IteratorFunctionObject& obj, input_it begin, input_itend end) const noexcept {
			LoopResult res = LoopResult::BeginError;
			Iterator it = begin;
			for (; !this->isEnd(it, end); ++it) {
				res = obj.foreachOperation(*it);
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

		template<class IteratorFunctionObject>
		using Func = ::llcpp::LoopResult (IteratorFunctionObject::*)(value_type&) const noexcept;
		template<class IteratorFunctionObject, Func<IteratorFunctionObject> FUNC, ll_bool_t GET_DATA = ::llcpp::LL_FALSE>
		//	requires ::llcpp::meta::concepts::signature::HasForeachOperation<const IteratorFunctionObject, value_type, LoopResult>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreach(input_it begin, input_itend end) const noexcept {
			LoopResult res = LoopResult::BeginError;
			Iterator it = begin;
			for (; !this->isEnd(it, end); ++it) {
				res = (IteratorFunctionObject().*FUNC)(*it);
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

		template<ll_bool_t GET_DATA = ::llcpp::LL_FALSE, class... OtherIterators>
			requires ::llcpp::meta::concepts::signature::HasForeachOperationExtra<ExtraFunctions, value_type, ::llcpp::meta::utils::Tuple<OtherIterators...>&, LoopResult>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreachEx(input_it begin, input_itend end, OtherIterators... other) const noexcept {
#if defined(LLANYLIB_TUPLE_HPP_)
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
#else
			static_assert(false, "This functionality needs to include Tuple.hpp");
			return ForeachResult<GET_DATA>{};
#endif // LLANYLIB_TUPLE_HPP_
		}
		template<class IteratorFunctionObject, ll_bool_t GET_DATA = ::llcpp::LL_FALSE, class... OtherIterators>
			requires ::llcpp::meta::concepts::signature::HasForeachOperationExtra<IteratorFunctionObject, value_type, ::llcpp::meta::utils::Tuple<OtherIterators...>&, LoopResult>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreachEx(input_it begin, input_itend end, OtherIterators... other) const noexcept {
#if defined(LLANYLIB_TUPLE_HPP_)
			// Include all other iterators in a tuple
			::llcpp::meta::utils::Tuple<OtherIterators...> tuple(other...);
		
			LoopResult res = LoopResult::BeginError;
			Iterator it = begin;
			for (; !this->isEnd(it, end); ++it, ++tuple) {
				res = IteratorFunctionObject::foreachOperation(*it, tuple);
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
#else
			static_assert(false, "This functionality needs to include Tuple.hpp");
			return ForeachResult<GET_DATA>{};
#endif // LLANYLIB_TUPLE_HPP_
		}
		template<class IteratorFunctionObject, ll_bool_t GET_DATA = ::llcpp::LL_FALSE, class... OtherIterators>
			requires ::llcpp::meta::concepts::signature::HasForeachOperationExtra<IteratorFunctionObject, value_type, ::llcpp::meta::utils::Tuple<OtherIterators...>&, LoopResult>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreachEx(const IteratorFunctionObject& obj, input_it begin, input_itend end, OtherIterators... other) const noexcept {
#if defined(LLANYLIB_TUPLE_HPP_)
			// Include all other iterators in a tuple
			::llcpp::meta::utils::Tuple<OtherIterators...> tuple(other...);
		
			LoopResult res = LoopResult::BeginError;
			Iterator it = begin;
			for (; !this->isEnd(it, end); ++it, ++tuple) {
				res = obj.foreachOperation(*it, tuple);
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

#else
			static_assert(false, "This functionality needs to include Tuple.hpp");
			return ForeachResult<GET_DATA>{};
#endif // LLANYLIB_TUPLE_HPP_
		}

		#pragma endregion
		#pragma region FindElement
		// Iterate over a list with current class
		template<class U>
			requires _MyType::HAS_OPERATOR_EQ<value_type, U> || _MyType::HAS_OPERATOR_EQ<U, value_type>
		__LL_NODISCARD__ constexpr input_it find(input_it begin, input_itend end, ::llcpp::meta::traits::cinput<U> obj) const noexcept {
			
			Iterator it = begin;
			for (; !this->isEnd(it, end); ++it) {
				if constexpr(_MyType::HAS_OPERATOR_EQ<value_type, U>) {
					if(*it == obj)
						return it;
				}
				else if constexpr (_MyType::HAS_OPERATOR_EQ<U, value_type>) {
					if(obj == *it)
						return it;
				}
				else {
					static_assert(_MyType::HAS_OPERATOR_EQ<value_type, U> || _MyType::HAS_OPERATOR_EQ<U, value_type>,
						"This function needs an operator== to compare both types!");
				}
			}

			return it;
		}

		#pragma endregion
		#pragma region FindSubstring
		// Iterate over a list with current class
		template<class U_Iterator, class U_IteratorEnd = U_Iterator>
			requires ::llcpp::meta::concepts::is_object::IsIterator<U_Iterator>
				&& ::llcpp::meta::concepts::is_object::IsIterator<U_IteratorEnd>
		__LL_NODISCARD__ constexpr input_it findSubArray(input_it data, input_itend data_end, _MyType::FixIterator<U_Iterator> needle, _MyType::FixIterator<U_Iterator> needle_end) const noexcept {
			isize data_size = data_end - data;
			// If distance is 0 or negative
			//	This list is invalid
			if (data_size <= ::llcpp::ZERO_VALUE<isize>)
				return data + data_size;
			
			isize needle_size = needle_end - needle;
			// If distance is 0 or negative
			//	Needle list is invalid
			if (needle_size <= ::llcpp::ZERO_VALUE<decltype(needle_size>))
				return data + data_size;

			// Ensure data size is at least as long as needle size
			if (data_size < needle_size)
				return data + data_size;

			// Try to find first coincidence
			auto it = this->find(begin, end, *needle);
			// If not found, exit function
			if (this->isEnd(it, end))
				return it;

			if constexpr (::std::is_pointer_v<Iterator> && ::std::is_pointer_v<U_Iterator>) {
				::llcpp::meta::utils::string::memcompare()
			}
		}


		#pragma endregion

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
