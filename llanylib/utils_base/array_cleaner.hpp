//////////////////////////////////////////////
//	array_cleaner.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 12.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_INCOMPLETE_HPP_) && defined(LLANYLIB_ARRAYCLEANER_INCOMPLETE_HPP_)
	#if LLANYLIB_ARRAYCLEANER_INCOMPLETE_MAYOR_ != 12 || LLANYLIB_ARRAYCLEANER_INCOMPLETE_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "array_cleaner.hpp(incomplete) version error!"
		#else
			#error "array_cleaner.hpp(incomplete) version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAYCLEANER_INCOMPLETE_MAYOR_ || LLANYLIB_ARRAYCLEANER_INCOMPLETE_MINOR_

#elif defined(LLANYLIB_INCOMPLETE_HPP_) && !defined(LLANYLIB_ARRAYCLEANER_INCOMPLETE_HPP_)
	#define LLANYLIB_ARRAYCLEANER_INCOMPLETE_HPP_
	#define LLANYLIB_ARRAYCLEANER_INCOMPLETE_MAYOR_ 12
	#define LLANYLIB_ARRAYCLEANER_INCOMPLETE_MINOR_ 0

#include "../concepts/concepts.hpp"

namespace llcpp {
namespace meta {
namespace math {	

template<class T>
__LL_NODISCARD__ constexpr ll_bool_t array_cleaner(::llcpp::meta::traits::cinput<T> value) noexcept;

} // namespace math
} // namespace meta
} // namespace llcpp

#elif defined(LLANYLIB_ARRAYCLEANER_HPP_)
	#if LLANYLIB_ARRAYCLEANER_MAYOR_ != 12 || LLANYLIB_ARRAYCLEANER_MINOR_ < 0
		#if __LL_DIRECTIVE_WARNING == 1
			#warning "array_cleaner.hpp version error!"
		#else
			#error "array_cleaner.hpp version error!"
		#endif // __LL_DIRECTIVE_WARNING == 1
		#define LLANYLIB_ERROR_HPP_
	#endif // LLANYLIB_ARRAYCLEANER_MAYOR_ || LLANYLIB_ARRAYCLEANER_MINOR_

#else
	#define LLANYLIB_ARRAYCLEANER_HPP_
	#define LLANYLIB_ARRAYCLEANER_MAYOR_ 12
	#define LLANYLIB_ARRAYCLEANER_MINOR_ 0

#include "../concepts/concepts.hpp"

namespace llcpp {
namespace meta {
namespace utils {

#pragma region AuxFunctions
template<ll_bool_t RESET_AUX = ::llcpp::LL_FALSE, class T, class U>
__LL_NODISCARD__ constexpr void array_cleaner(T* begin, const T* end, U*& aux) noexcept {
	static_assert(::std::is_same_v<T, U> || ::std::is_base_of_v<U, T>,
		"U type needs to be same type or base of T!");

	for(aux = _array; aux < end; ++aux) {
		// If object has its own clear
		if constexpr (::llcpp::meta::concepts::signature::HasClear<T>)
			aux->clear();
		// If not, clear with array type
		else *aux = ::llcpp::ZERO_VALUE<T>;
	}
	if constexpr (RESET_AUX) aux = begin;
}

template<ll_bool_t RESET_AUX = ::llcpp::LL_FALSE, class T, class U = T, usize N>
__LL_NODISCARD__ constexpr void array_cleaner(T (&_array)[N], U*& aux) noexcept {
	::llcpp::meta::utils::array_cleaner(_array, _array + N, aux);
}

// Clean array object
template<class T, class U = T>
__LL_NODISCARD__ constexpr void array_cleaner(T& obj, U*& aux) noexcept requires(::std::is_class_v<T>) {
	// Clear object with its own clear
	if constexpr (::llcpp::meta::concepts::signature::HasClear<T>)
		obj.clear();
	// If has begin
	else if constexpr (::llcpp::meta::concepts::signature::HasBegin<T>) {
		// Begin needs to be a pointer
		if constexpr (!::std::is_pointer_v<decltype(obj.begin())>) {
			static_assert(::std::is_pointer_v<decltype(obj.begin())>,
				"Begin type needs to be a pointer!");
		}
		// If has end, we clear with array ranged based algorithm
		else if constexpr (::llcpp::meta::concepts::signature::HasEnd<T>)
			array_cleaner(obj.begin(), obj.end(), aux);
		// If has size, we clear with array ranged based algorithm
		else if constexpr (::llcpp::meta::concepts::signature::HasSize<T>)
			array_cleaner(obj.begin(), obj.begin() + obj.size(), aux);
		else if constexpr (::llcpp::meta::concepts::signature::HasMaxSize<T>)
			array_cleaner(obj.begin(), obj.begin() + obj.max_size(), aux);
		else {
			static_assert(::llcpp::meta::concepts::signature::HasMaxSize<T>,
				"Having a begin with no end or size is not valid!");
		}
	}
	else {
		static_assert(::llcpp::meta::concepts::signature::HasBegin<T>,
			"No valid clear for this object!");
	}
}

template<class T, class U = T>
__LL_NODISCARD__ constexpr void array_cleaner(T& obj, U*& aux) noexcept requires(!::std::is_class_v<T>) {
	static_assert(::std::is_class_v<T>, "Object type needs to be a class!");
}

#pragma endregion
#pragma region StandardClear
template<class T, class U = T>
__LL_NODISCARD__ constexpr void array_cleaner(T* begin, const T* end) noexcept {
	U* aux;
	::llcpp::meta::utils::array_cleaner(begin, end, aux);
}

template<class T, class U = T, usize N>
__LL_NODISCARD__ constexpr void array_cleaner(T (&_array)[N]) noexcept {
	U* aux;
	::llcpp::meta::utils::array_cleaner(_array, _array + N, aux);
}

template<class T, class U = T>
__LL_NODISCARD__ constexpr void array_cleaner(T& obj) noexcept requires(::std::is_class_v<T>) {
	U* aux;
	::llcpp::meta::utils::array_cleaner(obj, aux);
}

#pragma endregion

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_ARRAYCLEANER_HPP_

#if defined(LLANYLIB_ERROR_HPP_)
	#undef LLANYLIB_ERROR_HPP_
#endif // LLANYLIB_ERROR_HPP_
