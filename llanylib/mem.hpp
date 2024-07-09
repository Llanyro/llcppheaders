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

template<class T>
class MemoryStack {
	public:
	protected:
		len_t size;
		len_t filled;
		linked::NodeNext<T>* first;
	public:
		constexpr MemoryStack(const len_t size) noexcept
			: size(size), filled(ZERO_UI64), first(LL_NULLPTR) {}
		constexpr ~MemoryStack() noexcept {}


		constexpr void setSize(const len_t size) noexcept { this->size = size; }
		constexpr void incrementSize(const len_t size) noexcept { this->size += size; }

		constexpr void setSize(const len_t size) noexcept { this->size = size; }
		constexpr void incrementSize(const len_t size) noexcept { this->size += size; }




};

template<class T, class U>
using UserDefinedFunction = std::conditional_t<
	std::is_same_v<U, void>,
	void(*)(MemoryStack<T>&) noexcept,
	void(*)(MemoryStack<T>& , U&) noexcept
>;


template<class T>
constexpr void generate_stack_memory(MemoryStack<T>& stack) noexcept {
	
}
template<class T, class U>
constexpr void generate_stack_memory(const len_t size, UserDefinedFunction<T, U> user_function, U& extra_data) noexcept {
	MemoryStack<T> stack(size);
	generate_stack_memory<T>(stack);
}
template<class T>
constexpr void generate_stack_memory<T, void>(const len_t size, UserDefinedFunction<T, void> user_function) noexcept {
	MemoryStack<T> stack(size);
	generate_stack_memory<T>(stack);
}



} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_MEM_HPP_
