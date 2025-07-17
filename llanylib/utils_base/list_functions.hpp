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

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/Arrayo.hpp>
	#include <llanylib/concepts/concepts.hpp>
	#include <llanylib/traits/ValidationChecker.hpp>
#else
	#include "../types/Arrayo.hpp"
	#include "../concepts/concepts.hpp"
	#include "../traits/ValidationChecker.hpp"
#endif // LL_LIB_PATHS
namespace llcpp {
namespace meta {
namespace utils {

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by begin needs to be convertible to U pointer
template<class T, class U>
__LL_NODISCARD__ constexpr U* get_array_begin(T& arr) noexcept;

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by end needs to be convertible to U pointer
template<class T, class U>
__LL_NODISCARD__ constexpr U* get_array_end(T& arr) noexcept;

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

#if defined(LL_LIB_PATHS)
	#include <llanylib/types/Arrayo.hpp>
	#include <llanylib/concepts/concepts.hpp>
	#include <llanylib/traits/ValidationChecker.hpp>
#else
	#include "../types/Arrayo.hpp"
	#include "../concepts/concepts.hpp"
	#include "../traits/ValidationChecker.hpp"
#endif // LL_LIB_PATHS

#if defined(__LL_WINDOWS_SYSTEM)
	#include <utility>
#elif defined(__LL_MINGW)
#elif defined(__LL_POSIX_SYSTEM)
#elif defined(__LL_UNIX_SYSTEM)
#else
#endif // __LL_WINDOWS_SYSTEM

namespace llcpp {
namespace meta {
namespace traits {

template<class T>
__LL_VAR_INLINE__ constexpr auto getArrayType() noexcept {
	if constexpr (::llcpp::meta::traits::has_value_type_v<T>)
		return ::llcpp::meta::traits::TypeContainer<typename T::value_type>{};
	else if constexpr (::std::is_pointer_v<T>)
		return ::llcpp::meta::traits::TypeContainer<::std::remove_pointer_t<T>>{};
	else if constexpr (::std::is_array_v<T>)
		return ::llcpp::meta::traits::TypeContainer<::std::remove_extent_t<T>>{};
	else if constexpr (::llcpp::meta::concepts::signature::HasOperatorArray<T>)
		return ::llcpp::meta::traits::TypeContainer<::std::remove_reference_t<decltype(::std::declval<T>()[0])>>{};
	else {
		static_assert(::std::is_pointer_v<T>,
			"There is not avaible Type for this array");
		return ::llcpp::meta::traits::TypeContainer<::llcpp::Emptyclass>{};
	}
}

template<class T>
using array_type_t = decltype(::llcpp::meta::traits::getArrayType<T>())::value_type;

template<class T>
__LL_VAR_INLINE__ constexpr auto getArrayIteratorType() noexcept {
	if constexpr (::llcpp::meta::traits::has_iterator_type_v<T>)
		return ::llcpp::meta::traits::TypeContainer<typename T::Iterator>{};
	else if constexpr (::std::is_pointer_v<T>)
		return ::llcpp::meta::traits::TypeContainer<T>{};
	else if constexpr (::std::is_array_v<T>)
		return ::llcpp::meta::traits::TypeContainer<::std::remove_extent_t<T>*>{};
	else if constexpr (::llcpp::meta::concepts::signature::HasBegin<T>)
		return ::llcpp::meta::traits::TypeContainer<decltype(::std::declval<T>().begin())>{};
	else {
		static_assert(::std::is_pointer_v<T>,
			"There is not avaible Iterator type for this array");
		return ::llcpp::meta::traits::TypeContainer<::llcpp::Emptyclass>{};
	}
}

template<class T>
using array_iterator_t = decltype(::llcpp::meta::traits::getArrayIteratorType<T>())::value_type;

template<class T>
__LL_VAR_INLINE__ constexpr auto getArrayConstIteratorType() noexcept {
	if constexpr (::llcpp::meta::traits::has_iterator_type_v<T>)
		return ::llcpp::meta::traits::TypeContainer<typename T::ConstIterator>{};
	else if constexpr (::std::is_pointer_v<T> && ::std::is_const_v<T>)
		return ::llcpp::meta::traits::TypeContainer<T>{};
	else if constexpr (::std::is_array_v<T> && ::std::is_const_v<T>)
		return ::llcpp::meta::traits::TypeContainer<::std::remove_extent_t<T>*>{};
	else if constexpr (::llcpp::meta::concepts::signature::HasBegin<T>)
		return ::llcpp::meta::traits::TypeContainer<decltype(::std::declval<const T>().begin())>{};
	else {
		static_assert(::std::is_pointer_v<T>,
			"There is not avaible Iterator type for this array");
		return ::llcpp::meta::traits::TypeContainer<::llcpp::Emptyclass>{};
	}
}

template<class T>
using array_const_iterator_t = decltype(::llcpp::meta::traits::getArrayConstIteratorType<T>())::value_type;

#if __LL_INCLUDE_KATS == 1
namespace kat {

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_ARRAY_TYPE_0 =
	::std::is_same_v<::llcpp::meta::traits::array_type_t<i32[6]>, i32>;
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_ARRAY_TYPE_1 =
	::std::is_same_v<::llcpp::meta::traits::array_type_t<::llcpp::Arrayo<f64, 10000>>, f64>;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_array_type_0_kat,
	::llcpp::meta::traits::kat::IS_WORKING_ARRAY_TYPE_0,
	"'array_type 0'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_array_type_1_kat,
	::llcpp::meta::traits::kat::IS_WORKING_ARRAY_TYPE_1,
	"'array_type 1'" __LL_IS_NOT_WORKING_STR
);

__LL_NODISCARD__ constexpr ::llcpp::string traits_list_functions_kats() noexcept {
	::llcpp::string result = ::llcpp::meta::traits::kat::is_working_array_type_0_kat();
	if(result) return result;
	result = ::llcpp::meta::traits::kat::is_working_array_type_1_kat();
	if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::traits::kat::traits_list_functions_kats() == LL_NULLPTR, "traits::list_functions KAT not OK");
#endif // __LL_STATIC_KATS

} // namespace kat
#endif // __LL_INCLUDE_KATS

} // namespace traits
namespace utils {
namespace __utils__ {

template<class U, class T, class... Args, u64... Idx>
__LL_NODISCARD__ constexpr U make_constructed_array(const Args&... args, ::std::index_sequence<Idx...>) noexcept {
	return U{ (Idx, T(args...))... };
}
template<class T, class... Args, u64... Idx>
__LL_NODISCARD__ constexpr T* make_constructed_new_mem(T* mem, const Args&... args, ::std::index_sequence<Idx...>) noexcept {
	return new (mem) T[sizeof...(Idx)]{ (Idx, T(args...))... };
}

} // namespace __utils__

// Constructs ALL objects in an array with the same arguments
// Class U needs to have a constructor of  parameter pack
template<class U, usize N, class T, class... Args>
__LL_NODISCARD__ constexpr U make_constructed_array(const Args&... args) noexcept {
	return ::llcpp::meta::utils::__utils__::make_constructed_array<U, T, Args...>(
		::std::forward<const Args&>(args)...,
		::std::make_index_sequence<N>{}
	);
}
template<class U, usize N = U::N, class T = U::value_type, class... Args>
__LL_NODISCARD__ constexpr U make_constructed_array_obj(const Args&... args) noexcept {
	return ::llcpp::meta::utils::make_constructed_array<U, N, T, Args...>(
		::std::forward<const Args&>(args)...
	);
}
template<class U, usize N, class... Args>
__LL_NODISCARD__ constexpr ::llcpp::Arrayo<U, N> make_constructed_arrayo(const Args&... args) noexcept {
	return ::llcpp::meta::utils::make_constructed_array<::llcpp::Arrayo<U, N>, N, U, Args...>(
		::std::forward<const Args&>(args)...
	);
}
// Constructs ALL objects in an array memory with the same arguments
template<class T, usize N, class... Args>
__LL_NODISCARD__ constexpr T* make_constructed_new_mem(T* mem, const Args&... args) noexcept {
	return ::llcpp::meta::utils::__utils__::make_constructed_new_mem<T>(
		mem,
		::std::forward<const Args&>(args)...,
		::std::make_index_sequence<N>{}
	);
}


template<class T, class U>
__LL_NODISCARD__ constexpr U __get_convertible_type(::llcpp::meta::traits::ref_or_ptr<T> t) noexcept {
	if constexpr (::std::is_same_v<T, U>)
		return t;
	else if constexpr (::std::is_convertible_v<T, U>)
		return static_cast<U>(t);
	else {
		static_assert(::std::is_convertible_v<T, U>,
			"T needs to be convertible to U pointer");
		return ::llcpp::NULL_VALUE<U>;
	}
}

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by begin needs to be convertible to U pointer
template<class U, class T>
__LL_NODISCARD__ constexpr U* get_array_begin(T& arr) noexcept {
	using cvref_t = ::std::remove_cvref_t<decltype(arr)>;
	using c_t = ::llcpp::meta::traits::conditional_t<::std::is_const_v<T>, const cvref_t, cvref_t>;

	if constexpr (::std::is_pointer_v<cvref_t>) {
		static_assert(::std::is_pointer_v<cvref_t>,
			"T cannot be a pointer!");
		return ::llcpp::NULL_VALUE<U>;
	}
	else if constexpr (::llcpp::meta::concepts::signature::HasBegin<c_t>)
		return ::llcpp::meta::utils::__get_convertible_type<decltype(arr.begin()), U*>(arr.begin());
	else if constexpr (::std::is_array_v<cvref_t>) {
		using array_t = ::llcpp::meta::traits::array_type_t<T>;
		return ::llcpp::meta::utils::__get_convertible_type<array_t*, U*>(arr + 0);
	}
	else {
		static_assert(::std::is_array_v<cvref_t>,
			"T has no valid method to get begin of the array!");
		return ::llcpp::NULL_VALUE<U>;
	}
}

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by end needs to be convertible to U pointer
template<class U, class T>
__LL_NODISCARD__ constexpr U* get_array_end(T& arr) noexcept {
	using cvref_t = ::std::remove_cvref_t<decltype(arr)>;
	using c_t = ::llcpp::meta::traits::conditional_t<::std::is_const_v<T>, const cvref_t, cvref_t>;

	if constexpr (::std::is_pointer_v<cvref_t>) {
		static_assert(::std::is_pointer_v<cvref_t>,
			"T cannot be a pointer!");
		return ::llcpp::NULL_VALUE<U>;
	}
	else if constexpr (::llcpp::meta::concepts::signature::HasBegin<c_t>)
		return ::llcpp::meta::utils::__get_convertible_type<decltype(arr.end()), U*>(arr.end());
	else if constexpr (::std::is_array_v<cvref_t>) {
		using array_t = ::llcpp::meta::traits::array_type_t<T>;
		return ::llcpp::meta::utils::__get_convertible_type<array_t*, U*>(arr + ::llcpp::array_size<cvref_t>);
	}
	else {
		static_assert(::std::is_array_v<cvref_t>,
			"T has no valid method to get end of the array!");
		return ::llcpp::NULL_VALUE<U>;
	}
}

// Type structure needs to be an array type (memory needs to be contiguous)
// Object returned by end needs to be convertible to usize
template<class U = usize, class T>
__LL_NODISCARD__ constexpr U get_array_size(T& arr) noexcept {
	using cvref_t = ::std::remove_cvref_t<decltype(arr)>;
	using c_t = ::llcpp::meta::traits::conditional_t<::std::is_const_v<T>, const cvref_t, cvref_t>;

	if constexpr (::std::is_pointer_v<cvref_t>) {
		static_assert(::std::is_pointer_v<cvref_t>,
			"T cannot be a pointer!");
		return ::llcpp::NULL_VALUE<U>;
	}
	else if constexpr (::llcpp::meta::traits::has_size_v<cvref_t>)
		return ::llcpp::meta::utils::__get_convertible_type<decltype(cvref_t::N), U>(cvref_t::N);
	// Let size() return any type
	else if constexpr (::llcpp::meta::concepts::signature::HasSize<c_t, ::llcpp::Emptyclass>)
		return ::llcpp::meta::utils::__get_convertible_type<decltype(arr.size()), U>(arr.size());
	else if constexpr (::std::is_array_v<cvref_t>)
		return ::llcpp::meta::utils::__get_convertible_type<decltype(::llcpp::array_size<cvref_t>), U>(::llcpp::array_size<cvref_t>);
	else {
		static_assert(::std::is_array_v<cvref_t>,
			"T has no valid method to get size of the array!");
		return ::llcpp::NULL_VALUE<U>;
	}
}

template<class T>
constexpr ll_bool_t is_valid_array_type() noexcept {
	constexpr auto val = ::llcpp::meta::traits::ValidationChecker::valid_type_v<T>;
	switch (val) {
		case ::llcpp::ValidType::Valid:
		case ::llcpp::ValidType::Array:	return ::llcpp::LL_TRUE;
		default:						return ::llcpp::LL_FALSE;
	}
}
template<class T>
constexpr ll_bool_t is_valid_array_type(const T& t) noexcept {
	constexpr auto val = ::llcpp::meta::traits::ValidationChecker::valid_type_v<const T>;
	if constexpr (val == ::llcpp::ValidType::ToCheck)
		return t.validationType() == ::llcpp::ValidType::Valid;
	else {
		switch (val) {
			case ::llcpp::ValidType::Valid:
			case ::llcpp::ValidType::Array:	return ::llcpp::LL_TRUE;
			default:						return ::llcpp::LL_FALSE;
		}
	}
}
template<class T>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_array_type_v =
	::llcpp::meta::utils::is_valid_array_type<T>();

template<class... Args>
__LL_VAR_INLINE__ constexpr ll_bool_t is_valid_array_type_all_v =
#if __LL_REAL_CXX17 == 1
	(::llcpp::meta::utils::is_valid_array_type_v<Args> || ...);
#else
	::std::disjunction_v<::llcpp::meta::utils::is_valid_array_type_v<Args>...>;
#endif // __LL_REAL_CXX17 == 1

#if __LL_INCLUDE_KATS == 1
namespace kat {

struct KatArrayConst {
	::llcpp::string str;
	usize N2;

	__LL_NODISCARD__ constexpr ::llcpp::string begin() const noexcept { return this->str; }
	__LL_NODISCARD__ constexpr ::llcpp::string end() const noexcept { return this->str + this->N2; }
	__LL_NODISCARD__ constexpr usize size() const noexcept { return this->N2; }

	__LL_NODISCARD__ constexpr ::llcpp::ValidType validationType() const noexcept {
		return this->begin() <= this->end() ? ::llcpp::ValidType::Valid : ::llcpp::ValidType::Invalid;
	}

	template<usize N>
	constexpr KatArrayConst(const ::llcpp::char_type (&v)[N]) noexcept
		: str(v)
		, N2(N)
	{}
	constexpr ~KatArrayConst() noexcept {}
};
template<usize N2>
struct KatArrayConst2 {
	::llcpp::string str;
	static constexpr usize N = N2;

	__LL_NODISCARD__ constexpr ::llcpp::string begin() const noexcept { return this->str; }
	__LL_NODISCARD__ constexpr ::llcpp::string end() const noexcept { return this->str + N; }

	__LL_NODISCARD__ constexpr ::llcpp::ValidType validationType() const noexcept {
		return this->begin() <= this->end() ? ::llcpp::ValidType::Valid : ::llcpp::ValidType::Invalid;
	}

	template<usize NN>
	constexpr KatArrayConst2(const ::llcpp::char_type (&v)[NN]) noexcept : str(v) {}
	constexpr ~KatArrayConst2() noexcept {}
};

__LL_VAR_INLINE__ constexpr const ::llcpp::char_type STR[]	= __LL_STRING_PREFIX "Hola mundo!";
__LL_VAR_INLINE__ constexpr KatArrayConst ARR				= KatArrayConst(STR);
__LL_VAR_INLINE__ constexpr KatArrayConst2 ARR2				= KatArrayConst2<12>(STR);
__LL_VAR_INLINE__ constexpr ::llcpp::char_type STR_INIT		= 'H';
__LL_VAR_INLINE__ constexpr ::llcpp::char_type STR_LAST		= '!';
__LL_VAR_INLINE__ constexpr ::llcpp::char_type STR_LAST_	= '\0';
__LL_VAR_INLINE__ constexpr const u8 MARR[]					= { 99, 99, 99, 99, 99 };
__LL_VAR_INLINE__ constexpr const u8 MARR2[][5]				= {
	{ 88, 88, 88, 88, 88 },
	{ 88, 88, 88, 88, 88 },
	{ 88, 88, 88, 88, 88 },
	{ 88, 88, 88, 88, 88 }
};

#pragma region Begin
__LL_VAR_INLINE__ constexpr ::llcpp::string STR_BEGIN	= ::llcpp::meta::utils::get_array_begin<const ::llcpp::char_type>(STR);
__LL_VAR_INLINE__ constexpr ::llcpp::string ARR_BEGIN	= ::llcpp::meta::utils::get_array_begin<const ::llcpp::char_type>(ARR);
__LL_VAR_INLINE__ constexpr ::llcpp::string ARR2_BEGIN	= ::llcpp::meta::utils::get_array_begin<const ::llcpp::char_type>(ARR2);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_ARRAY_BEGIN =
	   (STR_BEGIN != ::llcpp::NULL_VALUE<const ::llcpp::char_type>)
	&& (*STR_BEGIN == STR_INIT);
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_ARRAY_OBJ_BEGIN =
	   (ARR_BEGIN != ::llcpp::NULL_VALUE<const ::llcpp::char_type>)
	&& (*ARR_BEGIN == STR_INIT);
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_ARRAY_OBJ2_BEGIN =
	   (ARR_BEGIN != ::llcpp::NULL_VALUE<const ::llcpp::char_type>)
	&& (*ARR_BEGIN == STR_INIT);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_array_begin_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_BEGIN,
	"'Get str begin'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_array_obj_begin_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_OBJ_BEGIN,
	"'Get object begin'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_array_obj2_begin_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_OBJ2_BEGIN,
	"'Get object 2 begin'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region End
__LL_VAR_INLINE__ constexpr ::llcpp::string STR_END		= ::llcpp::meta::utils::get_array_end<const ::llcpp::char_type>(STR);
__LL_VAR_INLINE__ constexpr ::llcpp::string ARR_END		= ::llcpp::meta::utils::get_array_end<const ::llcpp::char_type>(ARR);
__LL_VAR_INLINE__ constexpr ::llcpp::string ARR2_END	= ::llcpp::meta::utils::get_array_end<const ::llcpp::char_type>(ARR2);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_ARRAY_END =
	   (STR_END != ::llcpp::NULL_VALUE<const ::llcpp::char_type>)
	&& (*(STR_END - 1) == STR_LAST_);
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_ARRAY_OBJ_END =
	   (ARR_END != ::llcpp::NULL_VALUE<const ::llcpp::char_type>)
	&& (*(ARR_END - 1) == STR_LAST_);
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_ARRAY_OBJ2_END =
	   (ARR2_END != ::llcpp::NULL_VALUE<const ::llcpp::char_type>)
	&& (*(ARR2_END - 1) == STR_LAST_);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_array_end_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_END,
	"'Get str end'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_array_obj_end_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_OBJ_END,
	"'Get object end'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_array_obj2_end_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_OBJ2_END,
	"'Get object 2 end'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region Size
__LL_VAR_INLINE__ constexpr usize STR_SIZE	= ::llcpp::meta::utils::get_array_size<>(STR);
__LL_VAR_INLINE__ constexpr usize ARR_SIZE	= ::llcpp::meta::utils::get_array_size<>(ARR);
__LL_VAR_INLINE__ constexpr usize ARR2_SIZE	= ::llcpp::meta::utils::get_array_size<>(ARR2);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_ARRAY_SIZE =
	STR_SIZE == ::llcpp::array_size<decltype(STR)>;
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_ARRAY_OBJ_SIZE =
	ARR_SIZE == ARR.size();
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_GET_ARRAY_OBJ2_SIZE =
	ARR2_SIZE == decltype(ARR2)::N;

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_array_size_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_SIZE,
	"'Get str size'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_array_obj_size_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_OBJ_SIZE,
	"'Get object size'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_get_array_obj2_size_kat,
	::llcpp::meta::utils::kat::IS_WORKING_GET_ARRAY_OBJ2_SIZE,
	"'Get object 2 size'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region ValidArray1
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_VALID_ARRAY_TYPE_1 =
	::llcpp::meta::utils::is_valid_array_type<decltype(STR)>();
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_VALID_ARRAY_OBJ_TYPE_1 =
	!::llcpp::meta::utils::is_valid_array_type<decltype(ARR)>();
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_VALID_ARRAY_OBJ2_TYPE_1 =
	!::llcpp::meta::utils::is_valid_array_type<decltype(ARR2)>();

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_valid_array_type_1_kat,
	::llcpp::meta::utils::kat::IS_WORKING_IS_VALID_ARRAY_TYPE_1,
	"'Is valid array 1'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_valid_array_obj_type_1_kat,
	::llcpp::meta::utils::kat::IS_WORKING_IS_VALID_ARRAY_OBJ_TYPE_1,
	"'Is valid array obj 1'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_valid_array_obj2_type_1_kat,
	::llcpp::meta::utils::kat::IS_WORKING_IS_VALID_ARRAY_OBJ2_TYPE_1,
	"'Is valid array obj 2 1'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region ValidArray2
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_VALID_ARRAY_TYPE_2 =
	::llcpp::meta::utils::is_valid_array_type<>(STR);
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_VALID_ARRAY_OBJ_TYPE_2 =
	::llcpp::meta::utils::is_valid_array_type<>(ARR);
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_VALID_ARRAY_OBJ2_TYPE_2 =
	::llcpp::meta::utils::is_valid_array_type<>(ARR2);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_valid_array_type_2_kat,
	::llcpp::meta::utils::kat::IS_WORKING_IS_VALID_ARRAY_TYPE_2,
	"'Is valid array 2'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_valid_array_obj_type_2_kat,
	::llcpp::meta::utils::kat::IS_WORKING_IS_VALID_ARRAY_OBJ_TYPE_2,
	"'Is valid array obj 2'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_is_valid_array_obj2_type_2_kat,
	::llcpp::meta::utils::kat::IS_WORKING_IS_VALID_ARRAY_OBJ2_TYPE_2,
	"'Is valid array obj 2 2'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion
#pragma region MakeArrays
__LL_VAR_INLINE__ constexpr auto MARR_KAT	= ::llcpp::meta::utils::make_constructed_array_obj<Arrayo<u8, 5>>(99u);
__LL_VAR_INLINE__ constexpr auto MARR_KAT2	= ::llcpp::meta::utils::make_constructed_array_obj<Arrayo<Arrayo<u8, 5>, 4>>(
	::llcpp::meta::utils::make_constructed_array_obj<Arrayo<u8, 5>>(88u)
);
__LL_VAR_INLINE__ constexpr auto MARR_KAT3	= ::llcpp::meta::utils::make_constructed_arrayo<Arrayo<u8, 5>, 4>(
	::llcpp::meta::utils::make_constructed_arrayo<u8, 5>(88u)
);

__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_MAKE_ARRAY	=
	MARR_KAT.compare(MARR);
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_MAKE_ARRAY2	=
	   MARR_KAT2[0].compare(MARR2[0])
	&& MARR_KAT2[1].compare(MARR2[1])
	&& MARR_KAT2[2].compare(MARR2[2])
	&& MARR_KAT2[3].compare(MARR2[3]);
__LL_VAR_INLINE__ constexpr ll_bool_t IS_WORKING_IS_MAKE_ARRAY3	=
	   MARR_KAT3[0].compare(MARR2[0])
	&& MARR_KAT3[1].compare(MARR2[1])
	&& MARR_KAT3[2].compare(MARR2[2])
	&& MARR_KAT3[3].compare(MARR2[3]);

__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_make_contructed_array_kat,
	::llcpp::meta::utils::kat::IS_WORKING_IS_MAKE_ARRAY,
	"'Make contructed array'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_make_contructed_array_2_kat,
	::llcpp::meta::utils::kat::IS_WORKING_IS_MAKE_ARRAY2,
	"'Make contructed array of arrays'" __LL_IS_NOT_WORKING_STR
);
__LL_KAT_FUNCTION_CONSTEXPR(
	is_working_make_contructed_array_3_kat,
	::llcpp::meta::utils::kat::IS_WORKING_IS_MAKE_ARRAY3,
	"'Make contructed array of arrays 2'" __LL_IS_NOT_WORKING_STR
);

#pragma endregion

__LL_NODISCARD__ constexpr ::llcpp::string list_functions_kats() noexcept {
	::llcpp::string result = ::llcpp::meta::utils::kat::is_working_get_array_begin_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_get_array_obj_begin_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_get_array_obj2_begin_kat();
	if(result) return result;

	result = ::llcpp::meta::utils::kat::is_working_get_array_end_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_get_array_obj_end_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_get_array_obj2_end_kat();
	if(result) return result;

	result = ::llcpp::meta::utils::kat::is_working_get_array_size_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_get_array_obj_size_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_get_array_obj2_size_kat();
	if(result) return result;

	result = ::llcpp::meta::utils::kat::is_working_is_valid_array_type_1_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_is_valid_array_obj_type_1_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_is_valid_array_obj2_type_1_kat();
	if(result) return result;

	result = ::llcpp::meta::utils::kat::is_working_is_valid_array_type_2_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_is_valid_array_obj_type_2_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_is_valid_array_obj2_type_2_kat();
	if(result) return result;

	result = ::llcpp::meta::utils::kat::is_working_make_contructed_array_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_make_contructed_array_2_kat();
	if(result) return result;
	result = ::llcpp::meta::utils::kat::is_working_make_contructed_array_3_kat();
	if(result) return result;

	return nullptr;
}

#if __LL_STATIC_KATS == 1
	static_assert(::llcpp::meta::utils::kat::list_functions_kats() == LL_NULLPTR, "utils::list_functions KAT not OK");
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
