//////////////////////////////////////////////
//	IteratorUtils.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ITERATORUTILS_INCOMPLETE_HPP_)
	#if LLANYLIB_ITERATORUTILS_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_ITERATORUTILS_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "IteratorUtils.hpp(incomplete) version error!"
		#else
			#error "IteratorUtils.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ITERATORUTILS_INCOMPLETE_MAYOR_ || LLANYLIB_ITERATORUTILS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ITERATORUTILS_INCOMPLETE_HPP_)
	#define LLANYLIB_ITERATORUTILS_INCOMPLETE_HPP_
	#define LLANYLIB_ITERATORUTILS_INCOMPLETE_MAYOR_ 11
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
	#if LLANYLIB_ITERATORUTILS_MAYOR_ != 11 || LLANYLIB_ITERATORUTILS_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "IteratorUtils.hpp version error!"
		#else
			#error "IteratorUtils.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ITERATORUTILS_MAYOR_ || LLANYLIB_ITERATORUTILS_MINOR_

#else
	#define LLANYLIB_ITERATORUTILS_HPP_
	#define LLANYLIB_ITERATORUTILS_MAYOR_ 11
	#define LLANYLIB_ITERATORUTILS_MINOR_ 0

#include "../traits_base/checker/traits_validate_checker.hpp"

#include "Array.hpp"

#include <utility>

namespace llcpp {
namespace meta {
namespace utils {

template<class _ExtraFunctions, class _Iterator, class _IteratorEnd = _Iterator>
class IteratorUtils
	: public ::llcpp::ClusterTag
	, public ::llcpp::meta::traits::ValidationWrapper<_ExtraFunctions, ::llcpp::AlwaysValidTag>
	, public _ExtraFunctions
{
	#pragma region Types
	public:
		// Class related
		using _MyType			= IteratorUtils;		// This class with template
		//using ClusterTag		= ::llcpp::ClusterTag;	// This is a cluster type class
		using ValidTag			= ::llcpp::meta::traits::ValidationWrapper<_ExtraFunctions, ::llcpp::AlwaysValidTag>;
		using ValidTag			= ::llcpp::AlwaysValidTag;
		using ExtraFunctions	= _ExtraFunctions;

		// Types and enums
		using Iterator		= _Iterator;
		using IteratorEnd	= _IteratorEnd;
		using input_it		= ::llcpp::meta::traits::input<Iterator>;
		using input_itend	= ::llcpp::meta::traits::input<IteratorEnd>;

		using OperatorCheckGEQ_It =
			::llcpp::meta::traits::signature_easy::OperatorGEQ<Iterator, ll_bool_t, const IteratorEnd>;
		using OperatorCheckGEQ_ItEnd =
			::llcpp::meta::traits::signature_easy::OperatorGEQ<IteratorEnd, ll_bool_t, const Iterator>;
		using OperatorCheckEQ_It =
			::llcpp::meta::traits::signature_easy::OperatorEQ<Iterator, ll_bool_t, const IteratorEnd&>;
		using OperatorCheckEQ_ItEnd =
			::llcpp::meta::traits::signature_easy::OperatorEQ<IteratorEnd, ll_bool_t, const Iterator&>;

		using ResultPair = ::std::pair<LoopResult, Iterator>;

		template<ll_bool_t GET_DATA>
		using ForeachResult = ::llcpp::meta::traits::conditional_t<GET_DATA, ResultPair, LoopResult>;

	#pragma endregion
	#pragma region Expresions
	public:


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
		constexpr IteratorUtils(const volatile IteratorUtils&) = delete;
		constexpr IteratorUtils& operator=(const volatile IteratorUtils&) = delete;
		constexpr IteratorUtils(volatile IteratorUtils&&) = delete;
		constexpr IteratorUtils& operator=(volatile IteratorUtils&&) = delete;

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
				if constexpr (OperatorCheckGEQ_It::IS_VALID)
					return it >= end;
				else {
					static_assert(OperatorCheckGEQ_It::IS_VALID,
						"Iterator must be comparables with a pointer");
				}
			}
			else if constexpr (::std::is_pointer_v<Iterator>) {
				if constexpr (OperatorCheckGEQ_ItEnd::IS_VALID)
					return it >= end;
				else {
					static_assert(OperatorCheckGEQ_ItEnd::IS_VALID,
						"Iterator must be comparables with a pointer");
				}
			}
			else {
				if constexpr (OperatorCheckEQ_It::IS_VALID)
					return it == end;
				else if constexpr (OperatorCheckEQ_ItEnd::IS_VALID)
					return end == it;
				else {
					static_assert(OperatorCheckEQ_It::IS_VALID,
						"Iterators must be comparables");
				}
			}
		}

		// 
		template<ll_bool_t GET_DATA = ::llcpp::FALSE>
		__LL_NODISCARD__ constexpr ForeachResult<GET_DATA> foreach(input_it begin, input_itend end) const noexcept {
			if constexpr (::llcpp::DEBUG) {
				if (this->isEnd(begin, end)) {
					if constexpr (GET_DATA) return ResultPair{ LoopResult::BeginError, begin };
					else return LoopResult::BeginError;
				}
			}

			LoopResult res = LoopResult::BeginError;
			Iterator it = begin;
			for (; it != end; ++it) {
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

		#pragma endregion

	#pragma endregion
};

struct Extra {
	public:
		__LL_NODISCARD__ constexpr LoopResult foreachOperation(const char c) const noexcept {
			return c == 'o' ? LoopResult::Ok : LoopResult::Conntinue;
		}
};

constexpr auto aasd = ::llcpp::meta::make_ConstArray("Holo");
using Iter = IteratorUtils<Extra, decltype(aasd.begin())>;
constexpr auto aasda = Iter().foreach<::llcpp::TRUE>(aasd.begin(), aasd.end());

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ITERATORUTILS_HPP_

#if !defined(LLANYLIB_ERROR_HPP_)
	#if defined(LLANYLIB_ITERATORUTILS_EXTRA_HPP_)
		#if LLANYLIB_ITERATORUTILS_EXTRA_MAYOR_ != 11 || LLANYLIB_ITERATORUTILS_EXTRA_MINOR_ < 0
			#if defined(__LL_REAL_CXX23)
				#warning "IteratorUtils.hpp(extra) version error!"
			#else
				#error "IteratorUtils.hpp(extra) version error!"
			#endif // __LL_REAL_CXX23
		#endif // LLANYLIB_ITERATORUTILS_EXTRA_MAYOR_ || LLANYLIB_ITERATORUTILS_EXTRA_MINOR_

	#else
		#define LLANYLIB_ITERATORUTILS_EXTRA_HPP_
		#define LLANYLIB_ITERATORUTILS_EXTRA_MAYOR_ 11
		#define LLANYLIB_ITERATORUTILS_EXTRA_MINOR_ 0

	#endif // LLANYLIB_ITERATORUTILS_EXTRA_HPP_
#else
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
