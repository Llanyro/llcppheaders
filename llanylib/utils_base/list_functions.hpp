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

#include <llanylib/concepts/concepts.hpp>
#include <llanylib/traits/ValidationChecker.hpp>

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

//#include <llanylib/concepts/concepts.hpp>
//#include <llanylib/traits/ValidationChecker.hpp>

#include <utility>

namespace llcpp {
namespace meta {
namespace utils {

#pragma region ArrayConstructorFiller
namespace __utils__ {

template<class U, class T, class... Args, u64... Idx>
__LL_NODISCARD__ constexpr auto make_constructed_array(const Args&... args, ::std::index_sequence<Idx...>) noexcept -> U {
	return U{ (Idx, T(args...))... };
}
template<class T, class... Args, u64... Idx>
__LL_NODISCARD__ constexpr auto make_constructed_new_mem(T* mem, const Args&... args, ::std::index_sequence<Idx...>) noexcept -> T* {
	return new (mem) T[sizeof...(Idx)]{ (Idx, T(args...))... };
}

} // namespace __utils__

// Constructs ALL objects in an array with the same arguments
// Class U needs to have a constructor of  parameter pack
template<class U, class T, u64 N, class... Args>
__LL_NODISCARD__ constexpr U make_constructed_array(const Args&... args) noexcept {
	return
		::llcpp::meta::algorithm::__algorithm__::make_constructed_array<U, T, Args...>(
			args...,
			::std::make_index_sequence<N>{}
		);
}
// Constructs ALL objects in an array memory with the same arguments
template<class T, u64 N, class... Args>
__LL_NODISCARD__ constexpr T* make_constructed_new_mem(T* mem, const Args&... args) noexcept {
	return ::llcpp::meta::algorithm::__algorithm__::make_constructed_new_mem<T, Args...>(
		mem,
		args...,
		::std::make_index_sequence<N>{}
	);
}

template<class T, class U>
__LL_NODISCARD__ constexpr U* getConvertibleType(T& t) noexcept {
	if constexpr (::std::is_same_v<T, U*>)
		return t;
	else if constexpr (::std::is_convertible_v<T, U*>)
		return static_cast<U*>(t);
	else {
		static_assert(::std::is_convertible_v<T, U*>,
			"T needs to be convertible to U pointer");
		return ::llcpp::NULL_VALUE<U>;
	}
}

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by begin needs to be convertible to U pointer
template<class U, class T>
__LL_NODISCARD__ constexpr U* getArrayBegin(T& arr) noexcept {
	using cvref_t = ::std::remove_cvref_t<decltype(arr)>;
	using c_t = ::llcpp::meta::traits::conditional_t<::std::is_const_v<T>, const cref_t, cref_t>;

	if constexpr (::llcpp::meta::concepts::signature::HasBegin<c_t>)
		return ::llcpp::meta::utils::getConvertibleType<U>(arr.begin());
	else if constexpr (::std::is_array_v<cvref_t>)
		return ::llcpp::meta::utils::getConvertibleType<U>(arr + 0);
	else {
		static_assert(::std::is_array_v<cvref_t>,
			"T has no valid method to get begin of the array!");
		return ::llcpp::NULL_VALUE<U>;
	}
}

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by end needs to be convertible to U pointer
template<class U, class T>
__LL_NODISCARD__ constexpr U* getArrayEnd(T& arr) noexcept {
	using cvref_t = ::std::remove_cvref_t<decltype(arr)>;
	using c_t = ::llcpp::meta::traits::conditional_t<::std::is_const_v<T>, const cref_t, cref_t>;

	if constexpr (::llcpp::meta::concepts::signature::HasBegin<c_t>)
		return ::llcpp::meta::utils::getConvertibleType<U>(arr.end());
	else if constexpr (::std::is_array_v<cvref_t>)
		return ::llcpp::meta::utils::getConvertibleType<U>(arr + ::llcpp::array_size<cvref_t>);
	else {
		static_assert(::std::is_array_v<cvref_t>,
			"T has no valid method to get end of the array!");
		return ::llcpp::NULL_VALUE<U>;
	}
}

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by end needs to be convertible to usize
template<class U = usize, class T>
__LL_NODISCARD__ constexpr U getArraySize(T& arr) noexcept {
	using cvref_t = ::std::remove_cvref_t<decltype(arr)>;
	using c_t = ::llcpp::meta::traits::conditional_t<::std::is_const_v<T>, const cref_t, cref_t>;

	// Let size() return any type
	if constexpr (::llcpp::meta::concepts::signature::HasSize<c_t, ::llcpp::Emptyclass>)
		return ::llcpp::meta::utils::getConvertibleType<U>(arr.size());
	else if constexpr (::std::is_array_v<cvref_t>)
		return ::llcpp::meta::utils::getConvertibleType<U>(::llcpp::array_size<cvref_t>);
	else {
		static_assert(::std::is_array_v<cvref_t>,
			"T has no valid method to get size of the array!");
		return ::llcpp::NULL_VALUE<U>;
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

#if __LL_INCLUDE_KATS == 1
namespace kat {

struct KatArray {
	::llcpp::char_type* str;
	__LL_NODISCARD__ constexpr ::llcpp::char_type* begin() noexcept { return this->str; }
	__LL_NODISCARD__ constexpr ::llcpp::string begin() const noexcept { return this->str; }
};
struct KatArrayConst {
	::llcpp::string str;
	__LL_NODISCARD__ constexpr ::llcpp::string begin() const noexcept { return this->str; }
};

constexpr ::llcpp::char_type STR[]	= __LL_STRING_PREFIX "Hola mundo!";
constexpr ::llcpp::char_type STR_0	= 'H';
constexpr ::llcpp::char_type STR_10	= '!';
constexpr ::llcpp::char_type STR_11	= '\0';
constexpr auto STR_END	= ::llcpp::meta::utils::getArrayEnd<const ::llcpp::char_type>(STR);

#pragma region Begin
constexpr auto STR_BEGIN	= ::llcpp::meta::utils::getArrayBegin<const ::llcpp::char_type>(STR);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_ARRAY_BEGIN =
	(STR_BEGIN != ::llcpp::NULL_VALUE<const ::llcpp::char_type>)
	&& (*STR_BEGIN == STR_0);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_array_begin_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_BEGIN,
	"'Get begin'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region End
constexpr auto STR_END	= ::llcpp::meta::utils::getArrayEnd<const ::llcpp::char_type>(STR);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_ARRAY_END =
	(STR_END != ::llcpp::NULL_VALUE<const ::llcpp::char_type>)
	&& (*(STR_END - 1) == STR_11);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_array_end_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_END,
	"'Get end'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region End
constexpr auto STR_SIZE	= ::llcpp::meta::utils::getArraySize(STR);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_ARRAY_END =
	(STR_END != ::llcpp::NULL_VALUE<const ::llcpp::char_type>)
	&& (*(STR_END - 1) == STR_11);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_array_end_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_END,
	"'Get end'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion


__LL_NODISCARD__ constexpr ::llcpp::string list_functions_kats() noexcept {
	::llcpp::string result = ::llcpp::meta::utils::kat::is_working_get_array_begin_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_get_array_end_kat();
	if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::utils::kat::list_functions_kats() == LL_NULLPTR, "list_functions KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_LISTFUNCTIONS_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
