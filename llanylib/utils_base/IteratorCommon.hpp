//////////////////////////////////////////////
//	IteratorCommon.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ITERATORCOMMON_INCOMPLETE_HPP_)
	#if LLANYLIB_ITERATORCOMMON_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ITERATORCOMMON_INCOMPLETE_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "IteratorCommon.hpp(incomplete) version error!"
		#else
			#error "IteratorCommon.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ITERATORCOMMON_INCOMPLETE_MAYOR_ || LLANYLIB_ITERATORCOMMON_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ITERATORCOMMON_INCOMPLETE_HPP_)
	#define LLANYLIB_ITERATORCOMMON_INCOMPLETE_HPP_
	#define LLANYLIB_ITERATORCOMMON_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ITERATORCOMMON_INCOMPLETE_MINOR_ 0

#include "../concepts/concepts.hpp"

namespace llcpp {
namespace meta {
namespace utils {

enum class IteratorCommonMode : u8;

template<class _T, ::llcpp::meta::utils::IteratorCommonMode _MODE>
class IteratorCommon;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ITERATORCOMMON_HPP_)
	#if LLANYLIB_ITERATORCOMMON_MAYOR_ != 12 || LLANYLIB_ITERATORCOMMON_MINOR_ < 0
		#if __LL_REAL_CXX23 == 1
			#warning "IteratorCommon.hpp version error!"
		#else
			#error "IteratorCommon.hpp version error!"
		#endif // __LL_REAL_CXX23 == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ITERATORCOMMON_MAYOR_ || LLANYLIB_ITERATORCOMMON_MINOR_

#else
	#define LLANYLIB_ITERATORCOMMON_HPP_
	#define LLANYLIB_ITERATORCOMMON_MAYOR_ 12
	#define LLANYLIB_ITERATORCOMMON_MINOR_ 0

#include "../concepts/concepts.hpp"

namespace llcpp {
namespace meta {
namespace utils {

enum class IteratorCommonMode : u8 {
	Zeroize,
	Fill,
};

template<class _T, ::llcpp::meta::utils::IteratorCommonMode _MODE>
class IteratorCommon
	: public ::llcpp::AlwaysValidTag
	, public ::llcpp::meta::traits::conditional_t<_MODE == decltype(_MODE)::Fill, ::llcpp::meta::simplest_container<_T>, ::llcpp::DummyClass>
{
	#pragma region Types
	public:
		// Class related
		using _MyType		= IteratorCommon;		// This class with template
		using ValidTag		= ::llcpp::AlwaysValidTag;
		using FillContainer = ::llcpp::meta::traits::conditional_t<_MODE == decltype(_MODE)::Fill, ::llcpp::meta::simplest_container<_T>, ::llcpp::DummyClass>;

		// Types and enums
		using T			= _T;
		using Mode		= decltype(_MODE);

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr Mode MODE = _MODE;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr IteratorCommon() noexcept = default;
		constexpr ~IteratorCommon() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr IteratorCommon(const IteratorCommon&) noexcept = default;
		constexpr IteratorCommon& operator=(const IteratorCommon&) noexcept = default;
		constexpr IteratorCommon(IteratorCommon&& other) noexcept = default;
		constexpr IteratorCommon& operator=(IteratorCommon&& other) noexcept = default;

		constexpr IteratorCommon(const volatile IteratorCommon&) noexcept = delete;
		constexpr IteratorCommon& operator=(const volatile IteratorCommon&) noexcept = delete;
		constexpr IteratorCommon(volatile IteratorCommon&&) noexcept = delete;
		constexpr IteratorCommon& operator=(volatile IteratorCommon&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const IteratorCommon*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator IteratorCommon*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr LoopResult foreachOperation(T& t) const noexcept requires(MODE == Mode::Zeroize) {
			if constexpr (::std::is_class_v<T> && ::llcpp::meta::concepts::signature::HasClear<T>)
				t.clear();
			else t = ::llcpp::ZERO_VALUE<T>;
			return LoopResult::Conntinue;
		}
		__LL_NODISCARD__ constexpr LoopResult foreachOperation(T& t) const noexcept requires(MODE == Mode::Fill) {
			t = ::std::forward<const T&>(FillContainer::value);
			return LoopResult::Conntinue;
		}

#if defined(LLANYLIB_TUPLE_HPP_)
		template<class... OtherIterators>
		constexpr void foreachTuple(::llcpp::meta::utils::Tuple<OtherIterators...>& tuple) const noexcept {
			(void)this->foreachOperation(tuple.getFirst());
			if constexpr (!::std::is_same_v<typename decltype(tuple)::Next, ::llcpp::Emptyclass>)
				(void)this->foreachTuple(tuple.getSecond());
		}
		template<class... OtherIterators>
		__LL_NODISCARD__ constexpr LoopResult foreachOperation(T& t, ::llcpp::meta::utils::Tuple<OtherIterators...>& tuple) const noexcept {
			(void)this->foreachOperation(t);
			this->foreachTuple(tuple);
			return LoopResult::Conntinue;
		}

#endif // LLANYLIB_TUPLE_HPP_

		#pragma endregion

	#pragma endregion
};

#if defined(LLANYLIB_ITERATORUTILS_HPP_)

template<class Iterator, class IteratorEnd = Iterator>
	requires ::llcpp::meta::concepts::is_object::IsIterator<Iterator>
		&& ::llcpp::meta::concepts::is_object::IsIterator<IteratorEnd>
using IteratorCleaner =
	::llcpp::meta::utils::IteratorUtils<
		Iterator,
		IteratorEnd,
		::llcpp::meta::utils::IteratorCommon<
			::std::remove_reference_t<decltype(*::std::declval<Iterator>())>,
			::llcpp::meta::utils::IteratorCommonMode::Zeroize
		>
	>;

template<class Iterator, class IteratorEnd = Iterator>
	requires ::llcpp::meta::concepts::is_object::IsIterator<Iterator>
		&& ::llcpp::meta::concepts::is_object::IsIterator<IteratorEnd>
using IteratorFill =
	::llcpp::meta::utils::IteratorUtils<
		Iterator,
		IteratorEnd,
		::llcpp::meta::utils::IteratorCommon<
			::std::remove_reference_t<decltype(*::std::declval<Iterator>())>,
			::llcpp::meta::utils::IteratorCommonMode::Fill
		>
	>;

#endif // LLANYLIB_ITERATORUTILS_HPP_

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ITERATORCOMMON_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
