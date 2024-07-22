//////////////////////////////////////////////
//	NodePrev.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_NODEPREV_HPP_) // Guard && version protector
	#if LLANYLIB_NODEPREV_MAYOR_ != 8 || LLANYLIB_NODEPREV_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "NodePrev.hpp version error!"
		#else
			#error "NodePrev.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_NODEPREV_MAYOR_ || LLANYLIB_NODEPREV_MINOR_

#else !defined(LLANYLIB_NODEPREV_HPP_)
#define LLANYLIB_NODEPREV_HPP_
#define LLANYLIB_NODEPREV_MAYOR_ 8
#define LLANYLIB_NODEPREV_MINOR_ 0

#include "Node.hpp"

namespace llcpp {
namespace meta {
namespace linked {

template <class NodeType, ll_bool_t CLASSIC = LL_FALSE>
class NodePrev : private Node<NodeType, CLASSIC> {
	#pragma region Types
	public:
		using type = NodeType;
		using Node = Node<NodeType>;

	#pragma endregion
	#pragma region Assersts
	public:
		// [TOCHECK] Check with benchmark class
		//static_assert(std::is_base_of_v<NodePrev<NodeType>, NodeType>, 
		//	"NodeType from NodePrev<> must be a base of NodePrev<>");

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr NodePrev() noexcept : Node(LL_NULLPTR) {}
		constexpr NodePrev(NodeType* next) noexcept : Node(next) {}
		constexpr ~NodePrev() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr NodePrev(const NodePrev&) noexcept = delete;
		constexpr NodePrev& operator=(const NodePrev&) noexcept = delete;
		constexpr NodePrev(NodePrev&&) noexcept = delete;
		constexpr NodePrev& operator=(NodePrev&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const NodePrev*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator NodePrev*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr const NodeType* getPrev() const noexcept { return Node::get(); }
		__LL_NODISCARD__ constexpr NodeType* getPrev() noexcept { return Node::get(); }
		constexpr void setPrev(NodeType* next) noexcept { Node::set(next); }
		//constexpr void clear() noexcept {}

		__LL_NODISCARD__ constexpr NodeType* getPrevNoThis() noexcept { return Node::getNoThis(); }
		__LL_NODISCARD__ constexpr const NodeType* getPrevNoThis() const noexcept { return Node::getNoThis(); }
		__LL_NODISCARD__ constexpr NodeType* getPrev(len_t moves) noexcept { return Node::get(moves); }
		__LL_NODISCARD__ constexpr const NodeType* getPrev(len_t moves) const noexcept { return Node::get(moves); }

		#pragma endregion

	#pragma endregion
};

template<class NodeType>
using SimplePrev = NodePrev<NodeType, LL_TRUE>;

} // namespace linked
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_NODEPREV_HPP_
