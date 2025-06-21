//////////////////////////////////////////////
//	Tuple.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TUPLE_INCOMPLETE_HPP_)
	#if LLANYLIB_TUPLE_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_TUPLE_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Tuple.hpp(incomplete) version error!"
		#else
			#error "Tuple.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TUPLE_INCOMPLETE_MAYOR_ || LLANYLIB_TUPLE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TUPLE_INCOMPLETE_HPP_)
	#define LLANYLIB_TUPLE_INCOMPLETE_HPP_
	#define LLANYLIB_TUPLE_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_TUPLE_INCOMPLETE_MINOR_ 0

#include <llanylib/concepts/concepts.hpp>

namespace llcpp {
namespace meta {
namespace utils {

template<ll_bool_t _IS_REFERENCE, class _T, class... _Args>
class TupleBase;

template<ll_bool_t _IS_REFERENCE, class _T>
class TupleBase<_IS_REFERENCE, _T>;

namespace __utils__ {

template<ll_bool_t IS_REFERENCE, class T, class... Args>
__LL_NODISCARD__ constexpr auto generate_tuple() noexcept;

template<ll_bool_t IS_REFERENCE, class... Args>
using tuple_base_t = decltype(::llcpp::meta::utils::__utils__::generate_tuple<IS_REFERENCE, Args...>())::value_type;

} // namespace __utils__

template<class... Args>
using Tuple = ::llcpp::meta::utils::__utils__::tuple_base_t<::llcpp::LL_FALSE, Args...>;
template<class... Args>
using TupleRef = ::llcpp::meta::utils::__utils__::tuple_base_t<::llcpp::LL_TRUE, Args...>;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TUPLE_HPP_)
	#if LLANYLIB_TUPLE_MAYOR_ != 12 || LLANYLIB_TUPLE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "Tuple.hpp version error!"
		#else
			#error "Tuple.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TUPLE_MAYOR_ || LLANYLIB_TUPLE_MINOR_

#else
	#define LLANYLIB_TUPLE_HPP_
	#define LLANYLIB_TUPLE_MAYOR_ 12
	#define LLANYLIB_TUPLE_MINOR_ 0

#include <llanylib/concepts/concepts.hpp>

namespace llcpp {
namespace meta {
namespace utils {

template<ll_bool_t _IS_REFERENCE, class _T, class... _Args>
class TupleBase;

template<ll_bool_t _IS_REFERENCE, class _T>
class TupleBase<_IS_REFERENCE, _T>;

namespace __utils__ {

// Container of first element in tuple
template<ll_bool_t _IS_REFERENCE, class _T>
class TupleFirst {
	#pragma region Types
	public:
		// Class related
		using _MyType		= TupleFirst;

		// Types and enums
		using T					= ::llcpp::meta::traits::conditional_t<_IS_REFERENCE, _T&, _T>;
		using type				= T;	// standard
		using value_type		= T;	// standard
		using reference			= _T&;
		using const_reference	= const _T&;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t IS_REFERENCE	= _IS_REFERENCE;

	#pragma endregion
	#pragma region Attributes
	private:
		T first;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr TupleFirst() noexcept = default;
		constexpr ~TupleFirst() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr TupleFirst(const TupleFirst& other) noexcept
			: first(::std::forward<const T&>(other.first))
		{}
		constexpr TupleFirst& operator=(const TupleFirst& other) noexcept {
			this->first = ::std::forward<const T&>(other.first);
			return *this;
		}
		constexpr TupleFirst(TupleFirst&& other) noexcept
			: first(::std::forward<T&&>(other.first))
		{}
		constexpr TupleFirst& operator=(TupleFirst&& other) noexcept {
			this->first = ::std::forward<T&&>(other.first);
			return *this;
		}

		constexpr TupleFirst(const T& first) noexcept
			: first(::std::forward<const T&>(first))
		{}
		constexpr TupleFirst& operator=(const T& first) noexcept {
			this->first = ::std::forward<const T&>(first);
			return *this;
		}
		constexpr TupleFirst(T&& first) noexcept
			: first(::std::forward<T&&>(first))
			, second()
		{}
		constexpr TupleFirst& operator=(T&& first) noexcept {
			this->first = ::std::forward<T&&>(first);
			return *this;
		}

		constexpr TupleFirst(const volatile TupleFirst&) noexcept = delete;
		constexpr TupleFirst& operator=(const volatile TupleFirst&) noexcept = delete;
		constexpr TupleFirst(volatile TupleFirst&&) noexcept = delete;
		constexpr TupleFirst& operator=(volatile TupleFirst&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const TupleFirst*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator TupleFirst*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr reference getFirst() noexcept { return this->first; }
		__LL_NODISCARD__ constexpr const_reference getFirst() const noexcept { return this->first; }

		constexpr void operator++() noexcept {
			if constexpr (::llcpp::meta::concepts::signature::HasPreIncrement<T>)
				++this->getFirst();
		}
		constexpr void operator++(int) noexcept {
			if constexpr (::llcpp::meta::concepts::signature::HasPosIncrement<T>)
				this->getFirst()++;
		}

		#pragma endregion

	#pragma endregion
};

template<ll_bool_t IS_REFERENCE, class T, class... Args>
__LL_NODISCARD__ constexpr auto generate_tuple() noexcept {
	if constexpr (::llcpp::meta::traits::is_empty_type_v<T>) {
		if constexpr (sizeof...(Args) == 0)
			return ::llcpp::meta::traits::TypeContainer<::llcpp::meta::utils::TupleBase<IS_REFERENCE, ::llcpp::Emptyclass>>{};
		else return ::llcpp::meta::utils::__utils__::generate_tuple<IS_REFERENCE, Args...>();
	}
	else {
		if constexpr (sizeof...(Args) == 0)
			return ::llcpp::meta::traits::TypeContainer<::llcpp::meta::utils::TupleBase<IS_REFERENCE, T>>{};
		else return ::llcpp::meta::traits::TypeContainer<::llcpp::meta::utils::TupleBase<IS_REFERENCE, T, Args...>>{};
	}
}

template<ll_bool_t IS_REFERENCE, class... Args>
using tuple_base_t = decltype(::llcpp::meta::utils::__utils__::generate_tuple<IS_REFERENCE, Args...>())::value_type;

} // namespace __utils__

template<ll_bool_t _IS_REFERENCE, class _T, class... _Args>
class TupleBase : public ::llcpp::meta::utils::__utils__::TupleFirst<_IS_REFERENCE, _T> {
	#pragma region Types
	public:
		// Class related
		using _MyType		= TupleBase;
		using TupleFirst	= ::llcpp::meta::utils::__utils__::TupleFirst<_IS_REFERENCE, _T>;

		// Types and enums
		using T					= typename TupleFirst::T;
		using type				= typename TupleFirst::type;
		using value_type		= typename TupleFirst::value_type;
		using reference			= typename TupleFirst::reference;
		using const_reference	= typename TupleFirst::const_reference;
		using Next				= ::llcpp::meta::utils::__utils__::tuple_base_t<_IS_REFERENCE, _Args...>;
		using U					= Next;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t IS_REFERENCE	= TupleFirst::IS_REFERENCE;

	#pragma endregion
	#pragma region Attributes
	private:
		Next second;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr TupleBase() noexcept = default;
		template<class... uArgs>
		constexpr TupleBase(const T& value, uArgs&&... args) noexcept
			: TupleFirst(::std::forward<const T&>(value))
			, second(::std::forward<uArgs&&>(args)...)
		{}
		template<class... uArgs>
		constexpr TupleBase(T&& value, uArgs&&... args) noexcept
			: TupleFirst(::std::forward<T&&>(value))
			, second(::std::forward<uArgs&&>(args)...)
		{}
		constexpr ~TupleBase() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr TupleBase(const TupleBase& other) noexcept
			: TupleFirst(::std::forward<const TupleFirst&>(other))
			, second(::std::forward<const Next&>(other.second))
		{}
		constexpr TupleBase& operator=(const TupleBase& other) noexcept {
			TupleFirst::operator=(::std::forward<const TupleFirst&>(other));
			this->second = ::std::forward<const Next&>(other.second);
			return *this;
		}
		constexpr TupleBase(TupleBase&& other) noexcept
			: TupleFirst(::std::forward<TupleFirst&&>(other))
			, second(::std::forward<Next&&>(other.second))
		{}
		constexpr TupleBase& operator=(TupleBase&& other) noexcept {
			TupleFirst::operator=(::std::forward<TupleFirst&&>(other));
			this->second = ::std::forward<Next&&>(other.second);
			return *this;
		}

		constexpr TupleBase(const T& value) noexcept
			: TupleFirst(::std::forward<const T&>(value))
			, second()
		{}
		constexpr TupleBase& operator=(const T& value) noexcept {
			TupleFirst::operator=(::std::forward<const T&>(value));
			return *this;
		}
		constexpr TupleBase(T&& value) noexcept
			: TupleFirst(::std::forward<T&&>(value))
			, second()
		{}
		constexpr TupleBase& operator=(T&& value) noexcept {
			TupleFirst::operator=(::std::forward<T&&>(value));
			return *this;
		}

		constexpr TupleBase(const volatile TupleBase&) noexcept = delete;
		constexpr TupleBase& operator=(const volatile TupleBase&) noexcept = delete;
		constexpr TupleBase(volatile TupleBase&&) noexcept = delete;
		constexpr TupleBase& operator=(volatile TupleBase&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const TupleBase*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator TupleBase*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr U& getSecond() noexcept { return this->second; }
		__LL_NODISCARD__ constexpr const U& getSecond() const noexcept { return this->second; }

		template<class W, const usize POSITION = ::llcpp::ZERO_VALUE<usize>>
		__LL_NODISCARD__ constexpr W& getType() noexcept {
			if constexpr (::std::is_same_v<T, W>) {
				if constexpr (POSITION == 0) return this->getFirst();
				else return this->getSecond().template getType<W, POSITION - 1>();
			}
			else return this->getSecond().template getType<W, POSITION>();
		}
		template<const usize POSITION = ::llcpp::ZERO_VALUE<usize>>
		__LL_NODISCARD__ constexpr auto& get() noexcept {
			if constexpr (POSITION == 0) return this->getFirst();
			else return this->getSecond().template get<POSITION - 1>();
		}
		template<const usize POSITION = ::llcpp::ZERO_VALUE<usize>>
		__LL_NODISCARD__ constexpr const auto& get() const noexcept {
			if constexpr (POSITION == 0) return this->getFirst();
			else return this->getSecond().template get<POSITION - 1>();
		}

		constexpr void operator++() noexcept {
			TupleFirst::operator++();
			this->getSecond().operator++();
		}
		constexpr void operator++(int) noexcept {
			TupleFirst::operator++(::std::declval<int>());
			this->getSecond().operator++(::std::declval<int>());
		}

		#pragma endregion

	#pragma endregion
};

template<ll_bool_t _IS_REFERENCE, class _T>
class TupleBase<_IS_REFERENCE, _T> : public ::llcpp::meta::utils::__utils__::TupleFirst<_IS_REFERENCE, _T> {
	#pragma region Types
	public:
		// Class related
		using _MyType		= TupleBase;
		using TupleFirst	= ::llcpp::meta::utils::__utils__::TupleFirst<_IS_REFERENCE, _T>;

		// Types and enums
		using T					= typename TupleFirst::T;
		using type				= typename TupleFirst::type;
		using value_type		= typename TupleFirst::value_type;
		using reference			= typename TupleFirst::reference;
		using const_reference	= typename TupleFirst::const_reference;
		using Next				= ::llcpp::Emptyclass;
		using U					= Next;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr TupleBase() noexcept = default;
		constexpr ~TupleBase() noexcept = default;

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr TupleBase(const TupleBase& other) noexcept
			: TupleFirst(::std::forward<const TupleFirst&>(other))
		{}
		constexpr TupleBase& operator=(const TupleBase& other) noexcept {
			TupleFirst::operator=(::std::forward<const TupleFirst&>(other));
			return *this;
		}
		constexpr TupleBase(TupleBase&& other) noexcept
			: TupleFirst(::std::forward<TupleFirst&&>(other))
		{}
		constexpr TupleBase& operator=(TupleBase&& other) noexcept {
			TupleFirst::operator=(::std::forward<TupleFirst&&>(other));
			return *this;
		}

		constexpr TupleBase(const T& value) noexcept
			: TupleFirst(::std::forward<const T&>(value))
		{}
		constexpr TupleBase& operator=(const T& value) noexcept {
			TupleFirst::operator=(::std::forward<const T&>(value));
			return *this;
		}
		constexpr TupleBase(T&& value) noexcept
			: TupleFirst(::std::forward<T&&>(value))
		{}
		constexpr TupleBase& operator=(T&& value) noexcept {
			TupleFirst::operator=(::std::forward<T&&>(value));
			return *this;
		}

		constexpr TupleBase(const volatile TupleBase&) noexcept = delete;
		constexpr TupleBase& operator=(const volatile TupleBase&) noexcept = delete;
		constexpr TupleBase(volatile TupleBase&&) noexcept = delete;
		constexpr TupleBase& operator=(volatile TupleBase&&) noexcept = delete;

		constexpr TupleBase(const volatile T&) noexcept = delete;
		constexpr TupleBase& operator=(const volatile T&) noexcept = delete;
		constexpr TupleBase(volatile T&&) noexcept = delete;
		constexpr TupleBase& operator=(volatile T&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const TupleBase*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator TupleBase*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		//__LL_NODISCARD__ constexpr const T& get() const noexcept { return this->first; }
		//__LL_NODISCARD__ constexpr operator T&() noexcept { return this->first; }
		//__LL_NODISCARD__ constexpr operator const T& () const noexcept { return this->first; }
		//constexpr void set(const T& value) noexcept {
		//	this->first = ::std::forward<const T&>(value);
		//}
		//constexpr void set(T&& value) noexcept {
		//	this->first = ::std::forward<T&&>(value);
		//}

		template<class W, const usize POSITION = ::llcpp::ZERO_VALUE<usize>>
		__LL_NODISCARD__ constexpr W& getType() noexcept {
			if constexpr (::std::is_same_v<T, W> && POSITION == ::llcpp::ZERO_VALUE<usize>)
				return this->getFirst();
			static_assert(::std::is_same_v<T, W>,
				"Error, last element in tuple is not type user was looking for!");
			static_assert(POSITION == ::llcpp::ZERO_VALUE<usize>,
				"Error, POSITION its still not 0 at last element in tuple");
		}

		template<const usize POSITION = ::llcpp::ZERO_VALUE<usize>>
		__LL_NODISCARD__ constexpr auto& get() noexcept {
			if constexpr (POSITION == ::llcpp::ZERO_VALUE<usize>)
				return this->getFirst();
			static_assert(POSITION == ::llcpp::ZERO_VALUE<usize>,
				"Error, POSITION its still not 0 at last element in tuple");
		}
		template<const usize POSITION = ::llcpp::ZERO_VALUE<usize>>
		__LL_NODISCARD__ constexpr const auto& get() const noexcept {
			if constexpr (POSITION == ::llcpp::ZERO_VALUE<usize>)
				return this->getFirst();
			static_assert(POSITION == ::llcpp::ZERO_VALUE<usize>,
				"Error, POSITION its still not 0 at last element in tuple");
		}

		constexpr void operator++() noexcept { TupleFirst::operator++(); }
		constexpr void operator++(int) noexcept { TupleFirst::operator++(::std::declval<int>()); }

		#pragma endregion

	#pragma endregion
};

template<class... Args>
using Tuple = ::llcpp::meta::utils::__utils__::tuple_base_t<::llcpp::LL_FALSE, Args...>;
template<class... Args>
using TupleRef = ::llcpp::meta::utils::__utils__::tuple_base_t<::llcpp::LL_TRUE, Args...>;

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TUPLE_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
