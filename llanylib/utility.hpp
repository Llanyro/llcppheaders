//////////////////////////////////////////////
//	utility.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_UTILITY_HPP_) // Guard && version protector
	#if LLANYLIB_UTILITY_MAYOR_ != 7 || LLANYLIB_UTILITY_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "utility.hpp version error!"
		#else
			#error "utility.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_UTILITY_MAYOR_ || LLANYLIB_UTILITY_MINOR_

#else !defined(LLANYLIB_UTILITY_HPP_)
#define LLANYLIB_UTILITY_HPP_
#define LLANYLIB_UTILITY_MAYOR_ 7
#define LLANYLIB_UTILITY_MINOR_ 0

#include "types.hpp"
#include <utility>

namespace llcpp {
namespace meta {
namespace utils {
namespace __internal__ {

template<class U, class T, class... Args, len_t... Idx>
__LL_NODISCARD__ constexpr auto make_constructed_array(const Args&... args, std::index_sequence<Idx...>) -> U {
	return U{ (Idx, T(args...))... };
}
template<class T, class... Args, len_t... Idx>
__LL_NODISCARD__ constexpr auto make_constructed_new_mem(T* mem, const Args&... args, std::index_sequence<Idx...>) -> T* {
	return new (mem) T[sizeof...(Idx)]{ (Idx, T(args...))... };
}

} // namespace __internal__

// Constructs ALL objects in an array with the same arguments
// Class U needs to have a constructor of  parameter pack
template<class U, class T, len_t N, class... Args>
__LL_NODISCARD__ constexpr U make_constructed_array(const Args&... args) {
	return __internal__::make_constructed_array<U, T, Args...>(args..., std::make_index_sequence<N>{});
}
// Constructs ALL objects in an array memory with the same arguments
template<class T, len_t N, class... Args>
__LL_NODISCARD__ constexpr T* make_constructed_new_mem(T* mem, const Args&... args) {
	return __internal__::make_constructed_new_mem<T, Args...>(mem, args..., std::make_index_sequence<N>{});
}

#if defined(LLANYLIB_STATICARRAY_HPP_)

template<class T, len_t N, T NULL_ITEM, class... Args>
__LL_NODISCARD__ constexpr StaticArray<T, N, NULL_ITEM> make_filled_StaticArray(const Args&... args) {
	return utils::make_constructed_array<StaticArray<T, N, NULL_ITEM>, T, N>(args...);
}

#endif

} // namespace utils
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_UTILITY_HPP_
