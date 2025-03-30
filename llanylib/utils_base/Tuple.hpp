//////////////////////////////////////////////
//	Tuple.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 11.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_TUPLE_INCOMPLETE_HPP_)
	#if LLANYLIB_TUPLE_INCOMPLETE_MAYOR_ != 11 || LLANYLIB_TUPLE_INCOMPLETE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Tuple.hpp(incomplete) version error!"
		#else
			#error "Tuple.hpp(incomplete) version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TUPLE_INCOMPLETE_MAYOR_ || LLANYLIB_TUPLE_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_TUPLE_INCOMPLETE_HPP_)
	#define LLANYLIB_TUPLE_INCOMPLETE_HPP_
	#define LLANYLIB_TUPLE_INCOMPLETE_MAYOR_ 11
	#define LLANYLIB_TUPLE_INCOMPLETE_MINOR_ 0

#include "../traits_base/traits_parameter_pack.hpp"

namespace llcpp {
namespace meta {
namespace utils {

template<class _T, class... _Args>
class Tuple;

template<class _T>
class Tuple<_T>;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_TUPLE_HPP_)
	#if LLANYLIB_TUPLE_MAYOR_ != 11 || LLANYLIB_TUPLE_MINOR_ < 0
		#if defined(__LL_REAL_CXX23)
			#warning "Tuple.hpp version error!"
		#else
			#error "Tuple.hpp version error!"
		#endif // __LL_REAL_CXX23
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_TUPLE_MAYOR_ || LLANYLIB_TUPLE_MINOR_

#else
	#define LLANYLIB_TUPLE_HPP_
	#define LLANYLIB_TUPLE_MAYOR_ 11
	#define LLANYLIB_TUPLE_MINOR_ 0

#include "../traits_base/traits_base.hpp"

namespace llcpp {
namespace meta {
namespace utils {

template<class _T, class... _Args>
class Tuple {
	#pragma region Types
	public:
		// Class related
		using _MyType		= Tuple;

		// Types and enums
		using T				= _T;
		using type			= T;	// standard
		using value_type	= T;	// standard

		// Type functions
	protected:
		template<class _U, class... _uArgs>
		static constexpr auto generateTuple() noexcept {
			using EmptyTuple = ::llcpp::meta::traits::TypeContainer<::llcpp::meta::utils::Tuple<::llcpp::Emptyclass>>;
			if constexpr (::llcpp::meta::traits::is_empty_type_v<_U>) {
				if constexpr (sizeof...(_uArgs) == 0)
					return EmptyTuple{};
				else return _MyType::generateTuple<_uArgs...>();
			}
			else {
				if constexpr (sizeof...(_uArgs) == 0)
					return ::llcpp::meta::traits::TypeContainer<::llcpp::meta::utils::Tuple<_U>>{};
				else return ::llcpp::meta::traits::TypeContainer<::llcpp::meta::utils::Tuple<_U, _uArgs...>>{};
			}
		}

	public:
		template<class... _uArgs>
		using NextTuple		= decltype(_MyType::generateTuple<_uArgs...>())::T;
		using Next			= NextTuple<_Args...>;
		using U				= Next;

	#pragma endregion
	#pragma region Attributes
	private:
		T first;
		Next second;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr Tuple() noexcept
			: first()
			, second()
		{}
		template<class... uArgs>
		constexpr Tuple(const T& value, uArgs&&... args) noexcept
			: first(::std::forward<const T&>(value))
			, second(::std::forward<uArgs&&>(args)...)
		{}
		template<class... uArgs>
		constexpr Tuple(T&& value, uArgs&&... args) noexcept
			: first(::std::forward<T&&>(value))
			, second(::std::forward<uArgs&&>(args)...)
		{}
		constexpr ~Tuple() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Tuple(const Tuple& other) noexcept
			: first(::std::forward<const T&>(other.first))
			, second(::std::forward<const Next&>(other.second))
		{}
		constexpr Tuple& operator=(const Tuple& other) noexcept {
			this->first = ::std::forward<const T&>(other.first);
			this->second = ::std::forward<const Next&>(other.second);
			return *this;
		}
		constexpr Tuple(Tuple&& other) noexcept
			: first(::std::forward<T&&>(other.first))
			, second(::std::forward<Next&&>(other.second))
		{}
		constexpr Tuple& operator=(Tuple&& other) noexcept {
			this->first = ::std::forward<T&&>(other.first);
			this->second = ::std::forward<Next&&>(other.second);
			return *this;
		}

		constexpr Tuple(const T& value) noexcept
			: first(::std::forward<const T&>(value))
			, second()
		{}
		constexpr Tuple& operator=(const T& value) noexcept {
			this->first = ::std::forward<const T&>(value);
			return *this;
		}
		constexpr Tuple(T&& value) noexcept
			: first(::std::forward<T&&>(value))
			, second()
		{}
		constexpr Tuple& operator=(T&& value) noexcept {
			this->first = ::std::forward<T&&>(value);
			return *this;
		}

		constexpr Tuple(volatile const Tuple& other) noexcept = delete;
		constexpr Tuple& operator=(volatile const Tuple& other) noexcept = delete;
		constexpr Tuple(volatile Tuple&& other) noexcept = delete;
		constexpr Tuple& operator=(volatile Tuple&& other) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Tuple*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Tuple*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		template<class U>
		__LL_NODISCARD__ constexpr ll_bool_t getValue(U*& data, const usize position = ::llcpp::ZERO_VALUE<usize>) noexcept {
			if constexpr (::std::is_same_v<T, U>) {
				if (position == 0) {
					data = &this->first;
					return ::llcpp::TRUE;
				}
				else return this->second.getValue(data, position - 1);
			}
			else return this->second.getValue(data, position);
		}

		#pragma endregion

	#pragma endregion
};

template<class _T>
class Tuple<_T> {
	#pragma region Types
	public:
		// Class related
		using _MyType		= Tuple;

		// Types and enums
		using T				= _T;
		using type			= T;	// standard
		using value_type	= T;	// standard
		//template<class... _uArgs>
		//using NextTuple		= Tuple<i8, u8>::template NextTuple<_uArgs...>;
		using Next			= ::llcpp::Emptyclass;
		using U				= Next;

	#pragma endregion
	#pragma region Attributes
	private:
		T first;

	#pragma endregion
	#pragma region Functions
		#pragma region Constructors
	public:
		constexpr Tuple() noexcept
			: first()
		{}
		constexpr ~Tuple() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Tuple(const Tuple& other) noexcept
			: first(::std::forward<const T&>(other.first))
		{}
		constexpr Tuple& operator=(const Tuple& other) noexcept {
			this->first = ::std::forward<const T&>(other.first);
			return *this;
		}
		constexpr Tuple(Tuple&& other) noexcept
			: first(::std::forward<T&&>(other.first))
		{}
		constexpr Tuple& operator=(Tuple&& other) noexcept {
			this->first = ::std::forward<T&&>(other.first);
			return *this;
		}

		constexpr Tuple(const T& value) noexcept
			: first(::std::forward<const T&>(value))
		{}
		constexpr Tuple& operator=(const T& value) noexcept {
			this->first = ::std::forward<const T&>(value);
			return *this;
		}
		constexpr Tuple(T&& value) noexcept
			: first(::std::forward<T&&>(value))
		{}
		constexpr Tuple& operator=(T&& value) noexcept {
			this->first = ::std::forward<T&&>(value);
			return *this;
		}

		constexpr Tuple(volatile const Tuple&) noexcept = delete;
		constexpr Tuple& operator=(volatile const Tuple&) noexcept = delete;
		constexpr Tuple(volatile Tuple&&) noexcept = delete;
		constexpr Tuple& operator=(volatile Tuple&&) noexcept = delete;

		constexpr Tuple(volatile const T&) noexcept = delete;
		constexpr Tuple& operator=(volatile const T&) noexcept = delete;
		constexpr Tuple(volatile T&&) noexcept = delete;
		constexpr Tuple& operator=(volatile T&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr explicit operator const Tuple*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator Tuple*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr const T& get() const noexcept { return this->first; }
		__LL_NODISCARD__ constexpr operator T&() noexcept { return this->first; }
		__LL_NODISCARD__ constexpr operator const T& () const noexcept { return this->first; }
		__LL_NODISCARD__ constexpr void set(const T& value) noexcept {
			this->first = ::std::forward<const T&>(value);
		}
		__LL_NODISCARD__ constexpr void set(T&& value) noexcept {
			this->first = ::std::forward<T&&>(value);
		}

		template<class U>
		__LL_NODISCARD__ constexpr ll_bool_t getValue(U*& data, const usize position = ::llcpp::ZERO_VALUE<usize>) noexcept {
			if constexpr (::std::is_same_v<T, U>) {
				if (position == 0) {
					data = &this->first;
					return ::llcpp::TRUE;
				}
				else return ::llcpp::FALSE;
			}
			else return ::llcpp::FALSE;
		}

		#pragma endregion

	#pragma endregion
};

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_TUPLE_HPP_
