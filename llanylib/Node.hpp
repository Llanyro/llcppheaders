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

#include <utility>

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

template<class ClassToCheck, class Signature>
struct has_compareNode_function {
	template<class U>
	static constexpr auto test(Signature) noexcept -> std::true_type;
	template<class U>
	static constexpr auto test(...) noexcept -> std::false_type;
	using type = decltype(has_compareNode_function::test<ClassToCheck>(&ClassToCheck::compareNode));
};
template<class ClassToCheck, class Signature>
__LL_VAR_INLINE__ constexpr ll_bool_t has_compareNode_function_v = has_compareNode_function<ClassToCheck, Signature>::type::value;

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
template <class NodeType, class NodeFunctions>
class Node : public BaseNode<NodeType>, public NodeFunctions {
	#pragma region Types
	public:
		using type = NodeType;
		using BaseNode = BaseNode<NodeType>;

		//using NodeTypeUsed = NodeType;
		using NodeTypeUsed = Node;
		using NodePack = std::pair<NodeTypeUsed*, NodeTypeUsed*>;
		using NodePackConst = std::pair<const NodeTypeUsed*, const NodeTypeUsed*>;
		using NodeCheckerSignature = ll_bool_t(NodeFunctions::*)(const NodeTypeUsed*) const noexcept;
		using NodeCompareSignature = cmp_t(NodeFunctions::*)(const NodeTypeUsed*, const NodeTypeUsed*) const noexcept;

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
			"NodeFunctions::nodeChecker() const noexcept is required by default! Non const function is optional");
		static_assert(linked::__::has_compareNode_function_v<NodeFunctions, NodeCompareSignature>,
			"NodeFunctions::compareNode() const noexcept is required by default! Non const function is optional");

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr Node() noexcept : BaseNode(), NodeFunctions() {}
		template<class... Args>
		constexpr Node(NodeType* _node, Args&&... args) noexcept
			: BaseNode(_node), NodeFunctions(std::forward<Args>(args)...) {}
		constexpr ~Node() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Node(const Node& other) noexcept : BaseNode(), NodeFunctions(other) {}
		constexpr Node& operator=(const Node& other) noexcept {
			NodeFunctions::operator=(other);
			return *this;
		}
		constexpr Node(Node&& other) noexcept : BaseNode(), NodeFunctions(std::move(other)) {}
		constexpr Node& operator=(Node&& other) noexcept {
			NodeFunctions::operator=(std::move(other));
			return *this;
		}

		constexpr Node(const NodeFunctions& other) noexcept : BaseNode(), NodeFunctions(other) {}
		constexpr Node& operator=(const NodeFunctions& other) noexcept {
			NodeFunctions::operator=(other);
			return *this;
		}
		constexpr Node(NodeFunctions&& other) noexcept : BaseNode(), NodeFunctions(std::move(other)) {}
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
		#pragma region Link
	public:
		constexpr void linkLeft(NodeTypeUsed* right) noexcept { this->set(right); }
		static constexpr void link(NodeTypeUsed* left, NodeTypeUsed* right) noexcept {
			left->set(right);
		}

		#pragma endregion
		#pragma region Find
	private:
		__LL_NODISCARD__ constexpr NodeTypeUsed* find_impl(const NodeTypeUsed* end) noexcept {
			NodeTypeUsed* begin = this;
			//while (begin != end) {
			//	if (this->nodeChecker(begin)) return begin;
			//	else begin = begin->get();
			//}
			// Also check end
			//return (begin && this->nodeChecker(begin)) ? begin : LL_NULLPTR;
			//return this;
			return nullptr;
		}
		__LL_NODISCARD__ constexpr const NodeTypeUsed* find_impl(const NodeTypeUsed* end) const noexcept {
			//const NodeTypeUsed* begin = this;
			//while (begin != end) {
			//	if (this->nodeChecker(begin)) return begin;
			//	else begin = begin->get();
			//}
			//// Also check end
			//return (begin && this->nodeChecker(begin)) ? begin : LL_NULLPTR;
			return nullptr;
		}

	public:
		__LL_NODISCARD__ constexpr NodeTypeUsed* find(const NodeTypeUsed* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->find_impl(end);
		}
		__LL_NODISCARD__ constexpr const NodeTypeUsed* find(const NodeTypeUsed* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->find_impl(end);
		}
		__LL_NODISCARD__ constexpr NodeTypeUsed* find_s(const NodeTypeUsed* end) noexcept {
			if (!this) return LL_NULLPTR;
			return this->find_impl(end);
		}
		__LL_NODISCARD__ constexpr const NodeTypeUsed* find_s(const NodeTypeUsed* end) const noexcept {
			if (!this) return LL_NULLPTR;
			return this->find_impl(end);
		}

		#pragma endregion
		/*#pragma region Contains
	private:
		__LL_NODISCARD__ constexpr ll_bool_t contains_impl(const NodeTypeUsed* end) noexcept {
			return static_cast<ll_bool_t>(this->find_impl(end));
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains_impl(const NodeTypeUsed* end) const noexcept {
			return static_cast<ll_bool_t>(this->find_impl(end));
		}

	public:
		__LL_NODISCARD__ constexpr ll_bool_t contains(const NodeTypeUsed* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->contains_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains(const NodeTypeUsed* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->contains_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains_s(const NodeTypeUsed* end) noexcept {
			if (!this) return LL_FALSE;
			return this->contains_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains_s(const NodeTypeUsed* end) const noexcept {
			if (!this) return LL_FALSE;
			return this->contains_impl(end);
		}

		#pragma endregion
		#pragma region All
	private:
		__LL_NODISCARD__ constexpr ll_bool_t all_impl(const NodeTypeUsed* end) noexcept {
			NodeTypeUsed* begin = this;
			while (begin != end) {
				if (!this->nodeChecker(begin)) return LL_FALSE;
				else begin = begin->get();
			}
			// Also check end
			return begin ? this->nodeChecker(begin) : LL_TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t all_impl(const NodeTypeUsed* end) const noexcept {
			NodeTypeUsed* begin = this;
			while (begin != end) {
				if (!this->nodeChecker(begin)) return LL_FALSE;
				else begin = begin->get();
			}
			// Also check end
			return begin ? this->nodeChecker(begin) : LL_TRUE;
		}

	public:
		__LL_NODISCARD__ constexpr ll_bool_t all(const NodeTypeUsed* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->all_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t all(const NodeTypeUsed* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->all_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t all_s(const NodeTypeUsed* end) noexcept {
			if (!this) return LL_FALSE;
			return this->all_impl(end);
		}
		__LL_NODISCARD__ constexpr const ll_bool_t all_s(const NodeTypeUsed* end) const noexcept {
			if (!this) return LL_FALSE;
			return this->all_impl(end);
		}

		#pragma endregion
		#pragma region Any
	private:
		__LL_NODISCARD__ constexpr ll_bool_t any_impl(const NodeTypeUsed* end) noexcept {
			return this->contains_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any_impl(const NodeTypeUsed* end) const noexcept {
			return this->contains_impl(end);
		}

	public:
		__LL_NODISCARD__ constexpr ll_bool_t any(const NodeTypeUsed* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->any_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any(const NodeTypeUsed* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->any_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any_s(const NodeTypeUsed* end) noexcept {
			if (!this) return LL_FALSE;
			return this->any_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any_s(const NodeTypeUsed* end) const noexcept {
			if (!this) return LL_FALSE;
			return this->any_impl(end);
		}

		#pragma endregion
		#pragma region None
	private:
		__LL_NODISCARD__ constexpr ll_bool_t none_impl(const NodeTypeUsed* end) noexcept {
			return !this->contains_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none_impl(const NodeTypeUsed* end) const noexcept {
			return !this->contains_impl(end);
		}

	public:
		__LL_NODISCARD__ constexpr ll_bool_t none(const NodeTypeUsed* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->none_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none(const NodeTypeUsed* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->none_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none_s(const NodeTypeUsed* end) noexcept {
			if (!this) return LL_FALSE;
			return this->none_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none_s(const NodeTypeUsed* end) const noexcept {
			if (!this) return LL_FALSE;
			return this->none_impl(end);
		}

		#pragma endregion
		#pragma region GetLastAndMiddle
	private:
		NodePack getLastAndMiddle_impl(const NodeTypeUsed* end) noexcept {
			NodeTypeUsed* slow = this;
			NodeTypeUsed* fast = this;
			do {
				if ((fast = fast->get()) != end) {
					slow = slow->get();
					fast = fast->get();
				}
				else break;
			} while (fast != end);
			return { slow, fast };
		}
		NodePackConst getLastAndMiddle_impl(const NodeTypeUsed* end) const noexcept {
			const NodeTypeUsed* slow = this;
			const NodeTypeUsed* fast = this;
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
		NodePack getLastAndMiddle(const NodeTypeUsed* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getLastAndMiddle_impl(end);
		}
		NodePackConst getLastAndMiddle(const NodeTypeUsed* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getLastAndMiddle_impl(end);
		}
		NodePack getLastAndMiddle_s(const NodeTypeUsed* end) noexcept {
			if (!this) return { LL_NULLPTR, LL_NULLPTR };
			return this->getLastAndMiddle_impl(end);
		}
		NodePackConst getLastAndMiddle_s(const NodeTypeUsed* end) const noexcept {
			if (!this) return { LL_NULLPTR, LL_NULLPTR };
			return this->getLastAndMiddle_impl(end);
		}

		#pragma endregion
		#pragma region GetMiddle
	private:
		NodeTypeUsed* getMiddle_impl(const NodeTypeUsed* end) noexcept {
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
		const NodeTypeUsed* getMiddle_impl(const NodeTypeUsed* end) const noexcept {
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
		NodeTypeUsed* getMiddle(const NodeTypeUsed* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getMiddle_impl(end);
		}
		const NodeTypeUsed* getMiddle(const NodeTypeUsed* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getMiddle_impl(end);
		}
		NodeTypeUsed* getMiddle(const NodeTypeUsed* end) noexcept {
			if (!this) return LL_NULLPTR;
			return this->getMiddle_impl(end);
		}
		const NodeTypeUsed* getMiddle(const NodeTypeUsed* end) const noexcept {
			if (!this) return LL_NULLPTR;
			return this->getMiddle_impl(end);
		}

		#pragma endregion
		#pragma region GetLast
	private:
		NodeTypeUsed* getLast_impl(const NodeTypeUsed* end) noexcept {
			NodeTypeUsed* result = this;
			for (NodeTypeUsed* tmp = LL_NULLPTR; (tmp = result->get()) != end; result = tmp);
			return result;
		}
		const NodeTypeUsed* getLast_impl(const NodeTypeUsed* end) const noexcept {
			const NodeTypeUsed* result = this;
			for (const NodeTypeUsed* tmp = LL_NULLPTR; (tmp = result->get()) != end; result = tmp);
			return result;
		}

	public:
		NodeTypeUsed* getLast(const NodeTypeUsed* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getLast_impl(end);
		}
		const NodeTypeUsed* getLast(const NodeTypeUsed* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getLast_impl(end);
		}
		NodeTypeUsed* getLast_s(const NodeTypeUsed* end) noexcept {
			if (!this) return LL_NULLPTR;
			return this->getLast_impl(end);
		}
		const NodeTypeUsed* getLast_s(const NodeTypeUsed* end) const noexcept {
			if (!this) return LL_NULLPTR;
			return this->getLast_impl(end);
		}

		#pragma endregion
		#pragma region Distance
	private:
		__LL_NODISCARD__ constexpr len_t distance_impl(const NodeTypeUsed* end) const noexcept {
			len_t distance{};
			for (const NodeTypeUsed* begin = this; begin != end; begin = begin->get(), ++distance);
			return distance;
		}

	public:
		__LL_NODISCARD__ constexpr len_t distance(const NodeTypeUsed* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->distance_impl(end);
		}
		__LL_NODISCARD__ constexpr len_t distance_s(const NodeTypeUsed* end) const noexcept {
			if (!this) return meta::algorithm::npos;
			return this->distance_impl(end);
		}

		#pragma endregion
		#pragma region MergeSort
	private:
		// Finds middle node of list and splits the list
		__LL_NODISCARD__ static constexpr NodeTypeUsed* split_list(NodeTypeUsed* begin) noexcept {
			NodeTypeUsed* fast = begin;
			NodeTypeUsed* slow = begin;
			NodeTypeUsed* prev = LL_NULLPTR;

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
		__LL_NODISCARD__ constexpr NodeTypeUsed* merge_lists(NodeTypeUsed* left, NodeTypeUsed* right) noexcept {
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
		__LL_NODISCARD__ constexpr NodeTypeUsed* merge_impl(NodeTypeUsed* begin) noexcept {
			if (!begin || !begin->get()) return begin;

			NodeTypeUsed* mid = this->split_list(begin);
			NodeTypeUsed* left = this->merge_impl(begin);
			NodeTypeUsed* right = this->merge_impl(mid);

			return this->merge_lists(left, right);
		}
		__LL_NODISCARD__ constexpr NodeTypeUsed* merge_impl() noexcept {

		}


	public:
		void mergeSort(NodeTypeUsed*& begin, NodeTypeUsed*& end) noexcept {
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

		#pragma endregion*/

		#pragma endregion

	#pragma endregion
};

template <class NodeType>
class Node<NodeType, void> : public BaseNode<NodeType> {
	#pragma region Types
	public:
		using type = NodeType;
		using BaseNode = BaseNode_t<NodeType, NodeFunctions>;

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

template <class T, class NodeFunctions>
class NodeT : public Node<NodeT<T, NodeFunctions>, NodeFunctions> {
	#pragma region Types
	public:
		using type = T;
		using Node = Node<NodeT, NodeFunctions>;

	#pragma endregion
	#pragma region Attributes
	public:
		T object;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr NodeT() noexcept : Node(), object() {}
		constexpr NodeT(NodeT* _node) noexcept : Node(_node), object() {}
		constexpr NodeT(NodeT* _node, const T& object) noexcept : Node(_node), object(object) {}
		constexpr NodeT(NodeT* _node, T&& object) noexcept : Node(_node), object(std::move(object)) {}
		constexpr NodeT(const T& object) noexcept : Node(), object(object) {}
		constexpr NodeT(T&& object) noexcept : Node(), object(std::move(object)) {}
		constexpr ~NodeT() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr NodeT(const NodeT&) noexcept = delete;
		constexpr NodeT& operator=(const NodeT&) noexcept = delete;
		constexpr NodeT(NodeT&&) noexcept = delete;
		constexpr NodeT& operator=(const NodeT&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const NodeT*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator NodeT*() noexcept { return this; }

		#pragma endregion

	#pragma endregion
};

template <class T>
class NodeTools {
	#pragma region Types
	public:
		using type = T;
		using Node = NodeT<T, NodeTools<T>>;

	#pragma endregion
	#pragma region Attributes
	public:
		T* search;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr NodeTools() noexcept : search(LL_NULLPTR) {}
		constexpr ~NodeTools() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr NodeTools(const NodeTools&) noexcept = delete;
		constexpr NodeTools& operator=(const NodeTools&) noexcept = delete;
		constexpr NodeTools(NodeTools&&) noexcept = delete;
		constexpr NodeTools& operator=(const NodeTools&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const NodeTools*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator NodeTools*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr ll_bool_t nodeChecker(const Node* a) const noexcept {
			return a->object == *this->search;
		}
		__LL_NODISCARD__ constexpr cmp_t compareNode(const Node* a, const Node* b) const noexcept {
			return
				(a->object == b->object)
				? 0
				: ((a->object > b->object) ? 1 : -1);
		}

		#pragma endregion
	#pragma endregion
};


constexpr int asdf() {
	using Types = NodeTools<int>;
	using Node = Types::Node;

	Node a[5]{};
	a[0].set(&a[1]);
	a[1].set(&a[2]);
	a[2].set(&a[3]);
	a[3].set(&a[4]);
	a[4].set(LL_NULLPTR);

	int search = 3;
	for (len_t i{}; i < traits::array_size<decltype(a)>; ++i) {
		a[i].object = i;
		a[i].search = &search;
	}

	//NodeT<>* result = LL_NULLPTR;
	auto result = a->find_s(LL_NULLPTR);
	if (result) {
		for (len_t i{}; i < traits::array_size<decltype(a)>; ++i) {
			if (a + i == result) return a[i].object;
		}
	}
	return -1;
	//return a[4].object;
}

constexpr int value = asdf();

} // namespace linked
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_NODE_HPP_
