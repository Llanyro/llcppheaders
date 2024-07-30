//////////////////////////////////////////////
//	NodeNext.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_NODENEXT_HPP_) // Guard && version protector
	#if LLANYLIB_NODENEXT_MAYOR_ != 9 || LLANYLIB_NODENEXT_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "NodeNext.hpp version error!"
		#else
			#error "NodeNext.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_NODENEXT_MAYOR_ || LLANYLIB_NODENEXT_MINOR_

#else !defined(LLANYLIB_NODENEXT_HPP_)
#define LLANYLIB_NODENEXT_HPP_
#define LLANYLIB_NODENEXT_MAYOR_ 9
#define LLANYLIB_NODENEXT_MINOR_ 0

#include "Node.hpp"

namespace llcpp {
namespace meta {
namespace linked {

template <class NodeType, ll_bool_t CLASSIC = LL_FALSE>
class NodeNext : private Node<NodeType, CLASSIC> {
	#pragma region Types
	public:
		using type = NodeType;
		using Node = Node<NodeType>;

	#pragma endregion
	#pragma region Assersts
	public:
		// [TOCHECK] Check with benchmark class
		//static_assert(std::is_base_of_v<NodeNext<NodeType>, NodeType>, 
		//	"NodeType from NodeNext<> must be a base of NodeNext<>");

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr NodeNext() noexcept : Node(LL_NULLPTR) {}
		constexpr NodeNext(NodeType* next) noexcept : Node(next) {}
		constexpr ~NodeNext() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr NodeNext(const NodeNext&) noexcept = delete;
		constexpr NodeNext& operator=(const NodeNext&) noexcept = delete;
		constexpr NodeNext(NodeNext&&) noexcept = delete;
		constexpr NodeNext& operator=(NodeNext&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const NodeNext*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator NodeNext*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr const NodeType* getNext() const noexcept { return Node::get(); }
		__LL_NODISCARD__ constexpr NodeType* getNext() noexcept { return Node::get(); }
		constexpr void setNext(NodeType* next) noexcept { Node::set(next); }
		//constexpr void clear() noexcept {}

		__LL_NODISCARD__ constexpr NodeType* getNextNoThis() noexcept { return Node::getNoThis(); }
		__LL_NODISCARD__ constexpr const NodeType* getNextNoThis() const noexcept { return Node::getNoThis(); }
		__LL_NODISCARD__ constexpr NodeType* getNext(len_t moves) noexcept { return Node::get(moves); }
		__LL_NODISCARD__ constexpr const NodeType* getNext(len_t moves) const noexcept { return Node::get(moves); }

		#pragma endregion

	#pragma endregion
};

template<class NodeType>
using SimpleNext = NodeNext<NodeType, LL_TRUE>;

} // namespace linked
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_NODENEXT_HPP_
