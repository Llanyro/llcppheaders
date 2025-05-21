//////////////////////////////////////////////
//	list_functions.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_LISTFUNCTIONS_INCOMPLETE_HPP_)
	#if LLANYLIB_LISTFUNCTIONS_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_LISTFUNCTIONS_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "list_functions.hpp(incomplete) version error!"
		#else
			#error "list_functions.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_LISTFUNCTIONS_INCOMPLETE_MAYOR_ || LLANYLIB_LISTFUNCTIONS_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_LISTFUNCTIONS_INCOMPLETE_HPP_)
	#define LLANYLIB_LISTFUNCTIONS_INCOMPLETE_HPP_
	#define LLANYLIB_LISTFUNCTIONS_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_LISTFUNCTIONS_INCOMPLETE_MINOR_ 0

#include "../concepts/concepts.hpp"

namespace llcpp {
namespace meta {
namespace utils {

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by begin needs to be convertible to U pointer
template<class T, class U>
__LL_NODISCARD__ constexpr U* getArrayBegin(T& arr) noexcept;

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by end needs to be convertible to U pointer
template<class T, class U>
__LL_NODISCARD__ constexpr U* getArrayEnd(T& arr) noexcept;

} // namespace utils
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_LISTFUNCTIONS_HPP_)
	#if LLANYLIB_LISTFUNCTIONS_MAYOR_ != 12 || LLANYLIB_LISTFUNCTIONS_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "list_functions.hpp version error!"
		#else
			#error "list_functions.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_LISTFUNCTIONS_MAYOR_ || LLANYLIB_LISTFUNCTIONS_MINOR_

#else
	#define LLANYLIB_LISTFUNCTIONS_HPP_
	#define LLANYLIB_LISTFUNCTIONS_MAYOR_ 12
	#define LLANYLIB_LISTFUNCTIONS_MINOR_ 0

#include "../concepts/concepts.hpp"
#include "../traits/ValidationChecker.hpp"

namespace llcpp {
namespace meta {
namespace utils {

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by begin needs to be convertible to U pointer
template<class U, class T>
__LL_NODISCARD__ constexpr U* getArrayBegin(T& arr) noexcept {
	if constexpr (::llcpp::meta::concepts::signature::HasBegin<T>) {
		using BeginType = decltype(arr.begin());
		if constexpr (::std::is_convertible_v<BeginType, U*>)
			return static_cast<U*>(arr.begin());
		else {
			static_assert(::std::is_convertible_v<BeginType, U*>,
				"Begin type needs to be convertible to U pointer");
			return ::llcpp::NULL_VALUE<U>;
		}
	}
	else if constexpr (::std::is_array_v<T>)
		return arr;
	else {
		static_assert(::std::is_array_v<T>,
			"T has no function to get the begin!");
		return ::llcpp::NULL_VALUE<U>;
	}
}

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by end needs to be convertible to U pointer
template<class U, class T>
__LL_NODISCARD__ constexpr U* getArrayEnd(T& arr) noexcept {
	if constexpr (::llcpp::meta::concepts::signature::HasBegin<T>) {
		using BeginType = decltype(arr.end());
		if constexpr (::std::is_convertible_v<BeginType, U*>)
			return static_cast<U*>(arr.end());
		else {
			static_assert(::std::is_convertible_v<BeginType, U*>,
				"Begin type needs to be convertible to U pointer");
			return ::llcpp::NULL_VALUE<U>;
		}
	}
	else if constexpr (::std::is_array_v<T>)
		return arr + ::llcpp::meta::traits::array_size<T>;
	else {
		static_assert(::std::is_array_v<T>,
			"T has no function to get the end!");
		return ::llcpp::NULL_VALUE<U>;
	}
}

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by end needs to be convertible to usize
template<class U, class T>
__LL_NODISCARD__ constexpr usize getArraySize(T& arr) noexcept {
	if constexpr (::llcpp::meta::concepts::signature::HasSize<T>)
		return arr.size();
	else if constexpr (::std::is_array_v<T>)
		return ::llcpp::meta::traits::array_size<T>;
	else {
		static_assert(::std::is_array_v<T>,
			"T has no function to get the end!");
		return ::llcpp::ZERO_VALUE<usize>;
	}
}

template<class T>
constexpr ll_bool_t isValidArrayType() noexcept {
	constexpr auto val = ::llcpp::meta::traits::ValidationChecker::valid_type_v<T>;
	switch (val) {
		case ::llcpp::misc::ValidType::Valid:
		case ::llcpp::misc::ValidType::Array:	return ::llcpp::LL_TRUE;
		default:								return ::llcpp::LL_FALSE;
	}
}

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_LISTFUNCTIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
