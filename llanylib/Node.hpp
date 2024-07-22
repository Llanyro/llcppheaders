//////////////////////////////////////////////
//	Node.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_NODE_HPP_) // Guard && version protector
	#if LLANYLIB_NODE_MAYOR_ != 8 || LLANYLIB_NODE_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Node.hpp version error!"
		#else
			#error "Node.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_NODE_MAYOR_ || LLANYLIB_NODE_MINOR_

#else !defined(LLANYLIB_NODE_HPP_)
#define LLANYLIB_NODE_HPP_
#define LLANYLIB_NODE_MAYOR_ 8
#define LLANYLIB_NODE_MINOR_ 0

#include "traits.hpp"

#if !defined(__debug_error_nullptr_str)
#define __debug_error_nullptr_str(ptr, str)
#endif

namespace llcpp {
namespace meta {
namespace linked {

namespace __ {

template<class ClassToCheck, class Signature>
struct has_nodeChecker_function {
	template<class U>
	static constexpr auto test(Signature) noexcept -> std::true_type;
	template<class U>
	static constexpr auto test(...) noexcept -> std::false_type;
	using type = decltype(has_nodeChecker_function::test<ClassToCheck>(&ClassToCheck::nodeChecker));
};
template<class ClassToCheck, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_nodeChecker_function_v = has_nodeChecker_function<ClassToCheck, Signature>::type::value;

} // namespace __

template <class NodeType>
class BaseNode {
	#pragma region Types
	public:
		using type = NodeType;

	#pragma endregion
	#pragma region Assersts
	public:
		// [TOCHECK] Check with benchmark class
		//static_assert(std::is_base_of_v<Node<NodeType>, NodeType>, 
		//	"NodeType from Node<> must be a base of Node<>");

	#pragma endregion
	#pragma region Attributes
	private:
		NodeType* _node;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr BaseNode() noexcept : BaseNode(this) {}
		constexpr BaseNode(NodeType* _node) noexcept : _node(_node) {}
		constexpr ~BaseNode() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr BaseNode(const BaseNode&) noexcept = delete;
		constexpr BaseNode& operator=(const BaseNode&) noexcept = delete;
		constexpr BaseNode(BaseNode&&) noexcept = delete;
		constexpr BaseNode& operator=(BaseNode&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const BaseNode*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator BaseNode*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr const NodeType* get() const noexcept { return this->_node; }
		__LL_NODISCARD__ constexpr NodeType* get() noexcept { return this->_node; }
		constexpr void set(NodeType* _node) noexcept { this->_node = _node; }
		constexpr void clear() noexcept { this->_node = this; }

		__LL_NODISCARD__ constexpr NodeType* getNoThis() noexcept {
			return (this->get() != this) ? this->get() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const NodeType* getNoThis() const noexcept {
			return (this->get() != this) ? this->get() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr NodeType* get(len_t moves) noexcept {
			NodeType* result = this;
			for (; moves > 0; --moves)
				result = result->get();
			return result;
		}
		__LL_NODISCARD__ constexpr const NodeType* get(len_t moves) const noexcept {
			const NodeType* result = this;
			for (; moves > 0; --moves)
				result = result->get();
			return result;
		}

		#pragma endregion

	#pragma endregion
};

template <class NodeType, class NodeFunctions>
class NodeTools : public NodeFunctions {
	#pragma region Types
	public:
		using NodeCheckerSignature = ll_bool_t(NodeFunctions::*)(NodeType*) const noexcept;

	#pragma endregion
	#pragma region Assersts
	public:
		static_assert(!std::is_reference_v<NodeType>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<NodeType>, "Const type is forbidden!");

		static_assert(!std::is_reference_v<NodeFunctions>, "NodeFunctions reference type is forbidden!");
		static_assert(!std::is_const_v<NodeFunctions>, "NodeFunctions const type is forbidden!");
		static_assert(std::is_class_v<NodeFunctions>, "NodeFunctions needs to be a class!");
		static_assert(std::is_nothrow_constructible_v<NodeFunctions>, "NodeFunctions needs a noexcept constructor!");
		static_assert(std::is_nothrow_destructible_v<NodeFunctions>, "NodeFunctions needs a noexcept destructor!");
		static_assert(std::is_copy_constructible_v<NodeFunctions>, "NodeFunctions needs a noexcept copy constructor!");
		static_assert(std::is_copy_assignable_v<NodeFunctions>, "NodeFunctions needs a noexcept copy asignable!");
		static_assert(std::is_move_constructible_v<NodeFunctions>, "NodeFunctions needs a noexcept move constructor!");
		static_assert(std::is_move_assignable_v<NodeFunctions>, "NodeFunctions needs a noexcept move asignable!");

		static_assert(linked::__::has_nodeChecker_function_v<NodeFunctions, NodeCheckerSignature>,
			"Manipulator::nodeChecker() const noexcept is required by default! Non const function is optional");

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr NodeTools() noexcept : NodeFunctions() {}
		template<class... Args>
		constexpr NodeTools(Args&&... args) noexcept : NodeFunctions(std::forward<Args>(args)...) {}
		constexpr ~NodeTools() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr NodeTools(const NodeTools& other) noexcept : NodeFunctions(other) {}
		constexpr NodeTools& operator=(const NodeTools& other) noexcept {
			NodeFunctions::operator=(other);
			return *this;
		}
		constexpr NodeTools(NodeTools&& other) noexcept : NodeFunctions(std::move(other)) {}
		constexpr NodeTools& operator=(NodeTools&& other) noexcept {
			NodeFunctions::operator=(std::move(other));
			return *this;
		}

		constexpr NodeTools(const NodeFunctions& other) noexcept : NodeFunctions(other) {}
		constexpr NodeTools& operator=(const NodeFunctions& other) noexcept {
			NodeFunctions::operator=(other);
			return *this;
		}
		constexpr NodeTools(NodeFunctions&& other) noexcept : NodeFunctions(std::move(other)) {}
		constexpr NodeFunctions& operator=(NodeFunctions&& other) noexcept {
			NodeFunctions::operator=(std::move(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const NodeFunctions*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator NodeFunctions*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	protected:
		constexpr void link_impl(NodeType* left, NodeType* right) const noexcept {
			left->setNext(right);
		}
		__LL_NODISCARD__ constexpr NodeType* find_impl(NodeType* begin, NodeType* end) const noexcept {
			while (begin != end) {
				if (this->nodeChecker(begin)) return begin;
				else begin = begin->getNext();
			}
			return begin;
		}
		__LL_NODISCARD__ constexpr ll_bool_t all_impl(NodeType* begin, NodeType* end) const noexcept {
			while (begin != end) {
				if (!this->nodeChecker(begin)) return LL_FALSE;
				else begin = begin->getNext();
			}
			return LL_TRUE;
		}

	public:
		constexpr void link(NodeType* left, NodeType* right) const noexcept {
#if defined(_DEBUG)
			if (!left) __debug_error_nullptr_str(left, "left");
			if (!right) __debug_error_nullptr_str(right, "right");
#endif // _DEBUG

			this->link_impl(left, right);
		}
		__LL_NODISCARD__ constexpr ll_bool_t link_s(NodeType* left, NodeType* right) const noexcept {
			if (!left || !right) return LL_FALSE;
			this->link_impl(left, right);
			return LL_TRUE;
		}

		__LL_NODISCARD__ constexpr NodeType* find(NodeType* begin, NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!begin) __debug_error_nullptr_str(begin, "begin");
			if (!end) __debug_error_nullptr_str(end, "end");
#endif // _DEBUG

			return this->find_impl(begin, end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains(NodeType* begin, NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!begin) __debug_error_nullptr_str(begin, "begin");
			if (!end) __debug_error_nullptr_str(end, "end");
#endif // _DEBUG

			return static_cast<ll_bool_t>(this->find_impl(begin, end));
		}
		__LL_NODISCARD__ constexpr ll_bool_t all(NodeType* begin, NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!begin) __debug_error_nullptr_str(begin, "begin");
			if (!end) __debug_error_nullptr_str(end, "end");
#endif // _DEBUG

			return this->all_impl(begin, end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any(NodeType* begin, NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!begin) __debug_error_nullptr_str(begin, "begin");
			if (!end) __debug_error_nullptr_str(end, "end");
#endif // _DEBUG

			return static_cast<ll_bool_t>(this->find_impl(begin, end));
		}
		__LL_NODISCARD__ constexpr ll_bool_t none(NodeType* begin, NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!begin) __debug_error_nullptr_str(begin, "begin");
			if (!end) __debug_error_nullptr_str(end, "end");
#endif // _DEBUG

			return !static_cast<ll_bool_t>(this->find_impl(begin, end));
		}

		__LL_NODISCARD__ constexpr ll_bool_t find_s(NodeType* begin, NodeType* end) noexcept {
			if (!left || !right) return LL_FALSE;
			this->find_impl(begin, end);
			return LL_TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains_s(INode* begin, INode* end) const noexcept {
			return static_cast<ll_bool_t>(this->find_s(begin, end));
		}
		__LL_NODISCARD__ constexpr ll_bool_t all_s(NodeType* begin, NodeType* end) noexcept {
			if (!begin || !end) return LL_FALSE;
			return this->all_impl(begin, end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any_s(NodeType* begin, NodeType* end) noexcept {
			return this->contains_s(begin, end));
		}
		__LL_NODISCARD__ constexpr ll_bool_t none_s(NodeType* begin, NodeType* end) noexcept {
			return !this->contains_s(begin, end));
		}

		#pragma endregion

	#pragma endregion
};

template <class NodeType, class NodeFunctions>
class Node : public BaseNode<NodeType>, public NodeTools<NodeType, NodeFunctions> {
	#pragma region Types
	public:
		using type = NodeType;
		using BaseNode = BaseNode<NodeType>;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr Node() noexcept : BaseNode() {}
		constexpr Node(NodeType* _node) noexcept : BaseNode(_node) {}
		constexpr ~Node() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Node(const Node&) noexcept = delete;
		constexpr Node& operator=(const Node&) noexcept = delete;
		constexpr Node(Node&&) noexcept = delete;
		constexpr Node& operator=(Node&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const Node*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator Node*() noexcept { return this; }

		#pragma endregion

	#pragma endregion
};

template <class NodeType>
class Node<NodeType, void> : public BaseNode<NodeType> {
	#pragma region Types
	public:
		using type = NodeType;
		using BaseNode = BaseNode<NodeType>;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr Node() noexcept : BaseNode() {}
		constexpr Node(NodeType* _node) noexcept : BaseNode(_node) {}
		constexpr ~Node() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Node(const Node&) noexcept = delete;
		constexpr Node& operator=(const Node&) noexcept = delete;
		constexpr Node(Node&&) noexcept = delete;
		constexpr Node& operator=(Node&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const Node*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator Node*() noexcept { return this; }

		#pragma endregion

	#pragma endregion
};

/*template <class NodeType>
class Node<NodeType, LL_TRUE> : public BaseNode<NodeType> {
	#pragma region Types
	public:
		using type = NodeType;
		using BaseNode = BaseNode<NodeType>;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr Node() noexcept : BaseNode() {}
		constexpr Node(NodeType* _node) noexcept : BaseNode(_node) {}
		constexpr ~Node() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Node(const Node&) noexcept = delete;
		constexpr Node& operator=(const Node&) noexcept = delete;
		constexpr Node(Node&&) noexcept = delete;
		constexpr Node& operator=(Node&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const Node*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator Node*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		constexpr void unlink(NodeType* prev) noexcept { Node::link(prev, this->get()); }
		__LL_NODISCARD__ constexpr ll_bool_t unlink_s(NodeType* prev) noexcept {
			if (!prev) return LL_FALSE;
			this->unlink(prev);
			return LL_TRUE;
		}

		#pragma endregion
		#pragma region Static
		static constexpr void link(NodeType* left, NodeType* right) noexcept {
#if defined(_DEBUG)
			if (!left) __debug_error_nullptr_str(left, "left");
			if (!right) __debug_error_nullptr_str(right, "right");
#endif // _DEBUG

			left->setNext(right);
		}
		NodeType* find(NodeType* begin, NodeType* end, FindNodeFunc find) noexcept {
#if defined(_DEBUG)
			if (!begin) __debug_error_nullptr_str(begin, "begin");
			if (!end) __debug_error_nullptr_str(end, "end");
			if (!find) __debug_error_nullptr_str(find, "find");
#endif // _DEBUG

			while (begin != end) {
				if (find(begin)) return begin;
				else begin = begin->getNext();
			}
			return begin;
		}


		__LL_NODISCARD__ static constexpr ll_bool_t link_s(NodeType* left, NodeType* right) noexcept {
			if (!left || !right) return LL_FALSE;
			NodeDouble::link(left, right);
			return LL_TRUE;
		}

		#pragma endregion


	#pragma endregion
};*/

} // namespace linked
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_NODE_HPP_
