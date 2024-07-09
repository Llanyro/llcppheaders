//////////////////////////////////////////////
//	mem.hpp									//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_MEM_HPP_) // Guard && version protector
	#if LLANYLIB_MEM_MAYOR_ != 8 || LLANYLIB_MEM_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "mem.hpp version error!"
		#else
			#error "mem.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_MEM_MAYOR_ || LLANYLIB_MEM_MINOR_

#else !defined(LLANYLIB_MEM_HPP_)
#define LLANYLIB_MEM_HPP_
#define LLANYLIB_MEM_MAYOR_ 8
#define LLANYLIB_MEM_MINOR_ 0

#include "Node.hpp"

namespace llcpp {
namespace meta {

constexpr len_t HOLDER_BUFFER_SZIE = 256;

template<class T>
class Holder : public linked::NodeNext<Holder<T>> {
		#pragma region Types
	public:
		using NodeNext = linked::NodeNext<Holder<T>>;
		using type = T;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<T>, "Const type is forbidden!");

	#pragma endregion

	protected:
		T buffer[HOLDER_BUFFER_SZIE];
	public:

};

struct MemoryStack {
	len_t size;
	len_t filled;
	linked::NodeNext* first
};

template<class T>
constexpr void generate_stack_memory(MemoryStack& stack) noexcept {
	

}

template<class T>
constexpr void generate_stack_memory(const len_t size) noexcept {
	
}

} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_MEM_HPP_
