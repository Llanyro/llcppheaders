//////////////////////////////////////////////
//	Node.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_NODE_HPP_) // Guard && version protector
	#if LLANYLIB_NODE_MAYOR_ != 9 || LLANYLIB_NODE_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Node.hpp version error!"
		#else
			#error "Node.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_NODE_MAYOR_ || LLANYLIB_NODE_MINOR_

#else !defined(LLANYLIB_NODE_HPP_)
#define LLANYLIB_NODE_HPP_
#define LLANYLIB_NODE_MAYOR_ 9
#define LLANYLIB_NODE_MINOR_ 0

#include "traits.hpp"
#include "Container.hpp"

#include <utility>

#if !defined(__debug_error_nullptr_str)
#define __debug_error_nullptr_str(ptr, str)
#endif

namespace llcpp {
namespace meta {
namespace linked {

template <class _NodeType>
class BaseNode {
	#pragma region Types
	public:
		using _MyType	= BaseNode;
		using NodeType = _NodeType;

	#pragma endregion
	#pragma region Assersts
	public:
		static_assert(std::is_base_of_v<_MyType, NodeType>,
			"_MyType is not a base of NodeType");

	#pragma endregion
	#pragma region Attributes
	private:
		NodeType* _node;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr BaseNode() noexcept : BaseNode(LL_NULLPTR) {}
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

//	Extra functions for nodes with only one link (ex: single linked list)
// 
//	Any function that reqires an argument like "end" is processed too if is not nullptr
//	If is nullptr, all elements in list will be processed until nullptr is found!
//	Careful with circular lists
// 
//	All funtions that has a counterpart that is "functionname_s" works this way
//		If is a secure function, checks if "this" pointer is null or not (if so, returns a default value)
//		If is not, if macro "_DEBUG" is defined and if "this" pointer is null, will call __debug_error_nullptr_str
//			to notify user by logger or similar (defined by user) that is nullptr, but will continue the function
//			behabiour without exiting function (it may crash at that moment)
//
template<class _NodeFunctions>
class SpecialNode : public _NodeFunctions, public BaseNode<SpecialNode<_NodeFunctions>> {
	#pragma region Types
	public:
		using _MyType				= SpecialNode;
		using NodeType				= SpecialNode;
		using NodeFunctions			= _NodeFunctions;
		using BaseNode				= BaseNode<NodeType>;

		using NodePack				= std::pair<NodeType*, NodeType*>;
		using NodePackConst			= std::pair<const NodeType*, const NodeType*>;
		using NodeCheckerSignature	= ll_bool_t(NodeFunctions::*)(const NodeType*) const noexcept;
		using NodeCompareSignature	= cmp_t(NodeFunctions::*)(const NodeType*, const NodeType*) const noexcept;

	#pragma endregion
	#pragma region Assersts
	public:
		static_assert(traits::is_valid_type_checker_v<NodeFunctions>,
			"type_checker<NodeFunctions> detected an invalid type!");
		static_assert(traits::is_valid_class_checker_v<NodeFunctions>,
			"class_checker<NodeFunctions> detected an invalid class type!");

		static_assert(traits::common::has_nodeChecker_function_v<NodeFunctions, NodeCheckerSignature>,
			"NodeFunctions::nodeChecker() const noexcept is required by default! Non const function is optional");
		static_assert(traits::common::has_compareNode_function_v<NodeFunctions, NodeCompareSignature>,
			"NodeFunctions::compareNode() const noexcept is required by default! Non const function is optional");

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr SpecialNode() noexcept : NodeFunctions(), BaseNode() {}
		template<class... Args>
		constexpr SpecialNode(NodeType* _node, Args&&... args) noexcept
			: NodeFunctions(std::forward<Args>(args)...), BaseNode(_node) {}
		constexpr ~SpecialNode() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr SpecialNode(const SpecialNode& other) noexcept
			: NodeFunctions(std::forward<const NodeFunctions&>(other))
			, BaseNode() {}
		constexpr SpecialNode& operator=(const Node& other) noexcept {
			NodeFunctions::operator=(std::forward<const NodeFunctions&>(other));
			return *this;
		}
		constexpr SpecialNode(SpecialNode&& other) noexcept
			: NodeFunctions(std::forward<NodeFunctions&&>(other))
			, BaseNode() {}
		constexpr SpecialNode& operator=(SpecialNode&& other) noexcept {
			NodeFunctions::operator=(std::forward<NodeFunctions&&>(other));
			return *this;
		}

		constexpr SpecialNode(const NodeFunctions& other) noexcept
			: NodeFunctions(std::forward<const NodeFunctions&>(other))
			, BaseNode() {}
		constexpr SpecialNode& operator=(const NodeFunctions& other) noexcept {
			NodeFunctions::operator=(std::forward<const NodeFunctions&>(other));
			return *this;
		}
		constexpr SpecialNode(NodeFunctions&& other) noexcept
			: NodeFunctions(std::forward<NodeFunctions&&>(other))
			, BaseNode() {}
		constexpr SpecialNode& operator=(NodeFunctions&& other) noexcept {
			NodeFunctions::operator=(std::forward<NodeFunctions&&>(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const SpecialNode*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator SpecialNode*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Link
	public:
		constexpr void linkLeft(NodeType* right) noexcept { this->set(right); }
		static constexpr void link(NodeType* left, NodeType* right) noexcept {
			left->set(right);
		}

		#pragma endregion
		#pragma region Find
	private:
		__LL_NODISCARD__ constexpr NodeType* find_impl(const NodeType* end) noexcept {
			NodeType* begin = this;
			while (begin != end) {
				if (this->nodeChecker(begin)) return begin;
				else begin = begin->get();
			}
			// Also check end
			return (begin && this->nodeChecker(begin)) ? begin : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const NodeType* find_impl(const NodeType* end) const noexcept {
			const NodeType* begin = this;
			while (begin != end) {
				if (this->nodeChecker(begin)) return begin;
				else begin = begin->get();
			}
			// Also check end
			return (begin && this->nodeChecker(begin)) ? begin : LL_NULLPTR;
		}

	public:
		__LL_NODISCARD__ constexpr NodeType* find(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->find_impl(end);
		}
		__LL_NODISCARD__ constexpr const NodeType* find(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->find_impl(end);
		}
		__LL_NODISCARD__ constexpr NodeType* find_s(const NodeType* end) noexcept {
			if (!this) return LL_NULLPTR;
			return this->find_impl(end);
		}
		__LL_NODISCARD__ constexpr const NodeType* find_s(const NodeType* end) const noexcept {
			if (!this) return LL_NULLPTR;
			return this->find_impl(end);
		}

		#pragma endregion
		#pragma region Contains
	private:
		__LL_NODISCARD__ constexpr ll_bool_t contains_impl(const NodeType* end) noexcept {
			return static_cast<ll_bool_t>(this->find_impl(end));
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains_impl(const NodeType* end) const noexcept {
			return static_cast<ll_bool_t>(this->find_impl(end));
		}

	public:
		__LL_NODISCARD__ constexpr ll_bool_t contains(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->contains_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->contains_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains_s(const NodeType* end) noexcept {
			if (!this) return LL_FALSE;
			return this->contains_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains_s(const NodeType* end) const noexcept {
			if (!this) return LL_FALSE;
			return this->contains_impl(end);
		}

		#pragma endregion
		#pragma region All
	private:
		__LL_NODISCARD__ constexpr ll_bool_t all_impl(const NodeType* end) noexcept {
			NodeType* begin = this;
			while (begin != end) {
				if (!this->nodeChecker(begin)) return LL_FALSE;
				else begin = begin->get();
			}
			// Also check end
			return begin ? this->nodeChecker(begin) : LL_TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t all_impl(const NodeType* end) const noexcept {
			NodeType* begin = this;
			while (begin != end) {
				if (!this->nodeChecker(begin)) return LL_FALSE;
				else begin = begin->get();
			}
			// Also check end
			return begin ? this->nodeChecker(begin) : LL_TRUE;
		}

	public:
		__LL_NODISCARD__ constexpr ll_bool_t all(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->all_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t all(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->all_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t all_s(const NodeType* end) noexcept {
			if (!this) return LL_FALSE;
			return this->all_impl(end);
		}
		__LL_NODISCARD__ constexpr const ll_bool_t all_s(const NodeType* end) const noexcept {
			if (!this) return LL_FALSE;
			return this->all_impl(end);
		}

		#pragma endregion
		#pragma region Any
	private:
		__LL_NODISCARD__ constexpr ll_bool_t any_impl(const NodeType* end) noexcept {
			return this->contains_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any_impl(const NodeType* end) const noexcept {
			return this->contains_impl(end);
		}

	public:
		__LL_NODISCARD__ constexpr ll_bool_t any(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->any_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->any_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any_s(const NodeType* end) noexcept {
			if (!this) return LL_FALSE;
			return this->any_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any_s(const NodeType* end) const noexcept {
			if (!this) return LL_FALSE;
			return this->any_impl(end);
		}

		#pragma endregion
		#pragma region None
	private:
		__LL_NODISCARD__ constexpr ll_bool_t none_impl(const NodeType* end) noexcept {
			return !this->contains_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none_impl(const NodeType* end) const noexcept {
			return !this->contains_impl(end);
		}

	public:
		__LL_NODISCARD__ constexpr ll_bool_t none(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->none_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->none_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none_s(const NodeType* end) noexcept {
			if (!this) return LL_FALSE;
			return this->none_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none_s(const NodeType* end) const noexcept {
			if (!this) return LL_FALSE;
			return this->none_impl(end);
		}

		#pragma endregion
		#pragma region GetLastAndMiddle
	private:
		NodePack getLastAndMiddle_impl(const NodeType* end) noexcept {
			NodeType* slow = this;
			NodeType* fast = this;
			do {
				if ((fast = fast->get()) != end) {
					slow = slow->get();
					fast = fast->get();
				}
				else break;
			} while (fast != end);
			return { slow, fast };
		}
		NodePackConst getLastAndMiddle_impl(const NodeType* end) const noexcept {
			const NodeType* slow = this;
			const NodeType* fast = this;
			do {
				if ((fast = fast->get()) != end) {
					slow = slow->get();
					fast = fast->get();
				}
				else break;
			} while (fast != end);
			return { slow, fast };
		}

	public:
		NodePack getLastAndMiddle(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getLastAndMiddle_impl(end);
		}
		NodePackConst getLastAndMiddle(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getLastAndMiddle_impl(end);
		}
		NodePack getLastAndMiddle_s(const NodeType* end) noexcept {
			if (!this) return { LL_NULLPTR, LL_NULLPTR };
			return this->getLastAndMiddle_impl(end);
		}
		NodePackConst getLastAndMiddle_s(const NodeType* end) const noexcept {
			if (!this) return { LL_NULLPTR, LL_NULLPTR };
			return this->getLastAndMiddle_impl(end);
		}

		#pragma endregion
		#pragma region GetMiddle
	private:
		NodeType* getMiddle_impl(const NodeType* end) noexcept {
			NodePack pack(this, this);
			while (pack.second != end) {
				pack.second = pack.second->get();
				if (pack.second != end) {
					pack.first = pack.first->get();
					pack.second = pack.second->get();
				}
				else break;
			}
			return pack.first;
		}
		const NodeType* getMiddle_impl(const NodeType* end) const noexcept {
			NodePackConst pack(this, this);
			while (pack.second != end) {
				pack.second = pack.second->get();
				if (pack.second != end) {
					pack.first = pack.first->get();
					pack.second = pack.second->get();
				}
				else break;
			}
			return pack.first;
		}

	public:
		NodeType* getMiddle(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getMiddle_impl(end);
		}
		const NodeType* getMiddle(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getMiddle_impl(end);
		}
		NodeType* getMiddle(const NodeType* end) noexcept {
			if (!this) return LL_NULLPTR;
			return this->getMiddle_impl(end);
		}
		const NodeType* getMiddle(const NodeType* end) const noexcept {
			if (!this) return LL_NULLPTR;
			return this->getMiddle_impl(end);
		}

		#pragma endregion
		#pragma region GetLast
	private:
		NodeType* getLast_impl(const NodeType* end) noexcept {
			NodeType* result = this;
			for (NodeType* tmp = LL_NULLPTR; (tmp = result->get()) != end; result = tmp);
			return result;
		}
		const NodeType* getLast_impl(const NodeType* end) const noexcept {
			const NodeType* result = this;
			for (const NodeType* tmp = LL_NULLPTR; (tmp = result->get()) != end; result = tmp);
			return result;
		}

	public:
		NodeType* getLast(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getLast_impl(end);
		}
		const NodeType* getLast(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getLast_impl(end);
		}
		NodeType* getLast_s(const NodeType* end) noexcept {
			if (!this) return LL_NULLPTR;
			return this->getLast_impl(end);
		}
		const NodeType* getLast_s(const NodeType* end) const noexcept {
			if (!this) return LL_NULLPTR;
			return this->getLast_impl(end);
		}

		#pragma endregion
		#pragma region Distance
	private:
		__LL_NODISCARD__ constexpr len_t distance_impl(const NodeType* end) const noexcept {
			len_t distance{};
			for (const NodeType* begin = this; begin != end; begin = begin->get(), ++distance);
			return distance;
		}

	public:
		__LL_NODISCARD__ constexpr len_t distance(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->distance_impl(end);
		}
		__LL_NODISCARD__ constexpr len_t distance_s(const NodeType* end) const noexcept {
			if (!this) return meta::algorithm::npos;
			return this->distance_impl(end);
		}

		#pragma endregion
		#pragma region MergeSort
	private:
		// Finds middle node of list and splits the list
		__LL_NODISCARD__ static constexpr NodeType* split_list(NodeType* begin) noexcept {
			NodeType* fast = begin;
			NodeType* slow = begin;
			NodeType* prev = LL_NULLPTR;

			while (fast) {
				if ((fast = fast->get())) {
					fast = fast->get();
					prev = slow;
					slow = slow->get();
				}
				else break;
			}

			if (prev) prev->set(LL_NULLPTR);

			return slow;
		}
		__LL_NODISCARD__ constexpr NodeType* merge_lists(NodeType* left, NodeType* right) noexcept {
			if (!left) return right;
			if (!right) return left;

			if (this->compareNode(left, right) <= ZERO_I32) {
				left->set(this->merge_lists(left->get(), right));
				return left;
			}
			else {
				right->set(this->merge_lists(left, right->get()));
				return right;
			}
		}
		__LL_NODISCARD__ constexpr NodeType* merge_impl(NodeType* begin) noexcept {
			if (!begin || !begin->get()) return begin;

			NodeType* mid = this->split_list(begin);
			NodeType* left = this->merge_impl(begin);
			NodeType* right = this->merge_impl(mid);

			return this->merge_lists(left, right);
		}
		__LL_NODISCARD__ constexpr NodeType* merge_impl() noexcept {

		}


	public:
		void mergeSort(NodeType*& begin, NodeType*& end) noexcept {
#if defined(_DEBUG)
			if (!begin) __debug_error_nullptr_str(begin, "begin");
			if (!end) __debug_error_nullptr_str(end, "end");
#endif // _DEBUG

			end->set(LL_NULLPTR);
			begin = this->merge_internal(begin);
			end = this->getLast(begin);
		}
		ll_bool_t mergeSort_s(INode*& begin, INode*& end, CompareNode compare) noexcept {
			if (!begin || !end || !compare) return LL_FALSE;
			end->setNext(LL_NULLPTR);
			begin = this->merge_internal(begin);
			end = this->getLast(begin);
			return LL_TRUE;
		}

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

template <class _NodeType>
class Node : public BaseNode<_NodeType> {
	#pragma region Types
	public:
		using _MyType	= BaseNode;
		using NodeType = _NodeType;
		using BaseNode = BaseNode<_NodeType>;

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
		constexpr void unlink(NodeType* prev) noexcept { this->link(prev, this->get()); }
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
				else begin = begin->get();
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

template <class T>
class NodeFunctions : public meta::Container<T> {
	#pragma region Types
	public:
		using _MyType		= NodeFunctions;
		using Container		= meta::Container<T>;
		using Node			= SpecialNode<NodeFunctions>;
		using NodeContainer	= llcpp::meta::Container<Node*>;

	#pragma endregion
	#pragma region Attributes
	public:
		NodeContainer search;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr NodeFunctions() noexcept : Container(), search(LL_NULLPTR) {}
		constexpr NodeFunctions(const T& object) noexcept
			: Container(std::forward<const T&>(object))
			, search(LL_NULLPTR) {}
		constexpr NodeFunctions(T&& object) noexcept
			: Container(std::forward<T&&>(object))
			, search(LL_NULLPTR) {}
		constexpr ~NodeT() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr NodeFunctions(const NodeFunctions& other) noexcept
			: Container(std::forward<const Container&>(other))
			, search(std::forward<const NodeContainer&>(other.search)) {}
		constexpr NodeFunctions& operator=(const NodeFunctions& other) noexcept {
			Container::operator=(std::forward<const Container&>(other));
			this->search = std::forward<const NodeContainer&>(other.search);
			return *this;
		}
		constexpr NodeFunctions(NodeFunctions&& other) noexcept
			: Container(std::forward<Container&&>(other))
			, search(std::forward<NodeContainer&&>(other.search)) {}
		constexpr NodeFunctions& operator=(NodeFunctions&& other) noexcept {
			Container::operator=(std::forward<Container&&>(other));
			this->search = std::forward<NodeContainer&&>(other.search);
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const NodeFunctions*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator NodeFunctions*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr ll_bool_t nodeChecker(const Node* a) const noexcept {
			return a->object == *this->search;
		}
		__LL_NODISCARD__ constexpr cmp_t compareNode(const Node* a, const NodeT* b) const noexcept {
			return
				(a->object == b->object)
				? 0
				: ((a->object > b->object) ? 1 : -1);
		}

		#pragma endregion

	#pragma endregion
};
class NodeT2 {
	#pragma region Types
	public:
		using T = Node<NodeT2>;

	#pragma endregion
	#pragma region Attributes
	public:
		T* search;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr NodeT2() noexcept : search(LL_NULLPTR) {}
		constexpr ~NodeT2() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr NodeT2(const NodeT2&) noexcept = delete;
		constexpr NodeT2& operator=(const NodeT2&) noexcept = delete;
		constexpr NodeT2(NodeT2&&) noexcept = delete;
		constexpr NodeT2& operator=(const NodeT2&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const NodeT2*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator NodeT2*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr ll_bool_t nodeChecker(const T* a) const noexcept {
			return a == *this->search;
		}
		__LL_NODISCARD__ constexpr cmp_t compareNode(const T* a, const T* b) const noexcept {
			return (a == b) ? 0 : ((a > b) ? 1 : -1);
		}

		#pragma endregion

	#pragma endregion
};

constexpr int asdf() noexcept {
	Node<NodeT2> a[5]{};
	a[0].set(a + 1);
	a[1].set(a + 2);
	a[2].set(a + 3);
	a[3].set(a + 4);
	a[4].set(LL_NULLPTR);

	a->search = a + 3;
	auto result = a->find_s(LL_NULLPTR);
	if (result) {
		return result - a;
	}
	return -1;
	//return a[4].object;
}

//constexpr int asdf2() noexcept {
//	NodeT<int> a(LL_NULLPTR, 99);
//	auto result = a.operator llcpp::meta::linked::Node<llcpp::meta::linked::NodeT<int>, llcpp::meta::linked::NodeT<int>> *();
//	char* b = result;
//	return a->object;
//}

constexpr int value = asdf();
//constexpr int value2 = asdf2();

} // namespace linked
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_NODE_HPP_
