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

namespace llcpp {
namespace meta {
namespace linked {

template <class _NodeType>
class BaseNode {
	#pragma region Types
	public:
		// Class related
		using _MyType	= BaseNode;

		// Types
		using NodeType = _NodeType;

	#pragma endregion
	#pragma region Assersts
	public:
		//static_assert(std::is_base_of_v<_MyType, NodeType>,
		//	"_MyType is not a base of NodeType");

	#pragma endregion
	#pragma region Attributes
	private:
		NodeType* node;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr BaseNode() noexcept : BaseNode(LL_NULLPTR) {}
		constexpr BaseNode(NodeType* node) noexcept : node(node) {}
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
		__LL_NODISCARD__ constexpr const NodeType* get() const noexcept { return this->node; }
		__LL_NODISCARD__ constexpr NodeType* get() noexcept { return this->node; }
		constexpr void set(NodeType* node) noexcept { this->node = node; }
		constexpr void clear() noexcept { this->node = this; }

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

template<class Node_Type_Or_Functions, ll_bool_t IS_SPECIAL>
class BaseNodeList;

#define HAS_NODECHECKER_STR "'NodeFunctions::nodeChecker() const noexcept' or 'NodeFunctions::nodeChecker() noexcept' is required!"
#define HAS_NODECHECKER_CONST_STR "'NodeFunctions::nodeChecker() const noexcept' is required!"
#define HAS_NODECOMPARE_STR "'NodeFunctions::compareNode() const noexcept' or 'NodeFunctions::compareNode() noexcept' is required!"

// If any function requires a parameter that its called "end"
//	Means that it will operate until "end" if found (not included)
//	If "end" is nullptr, node list should not be a circular list or it could lead to a endless loop
//	Also, the begin of the operation in the list is the node that calls the function itself
//		If you are not sure that node pointer is not nullptr, you could use "*_s" functions
template<class _NodeFunctions>
class FunctionalNode : public _NodeFunctions, public BaseNode<FunctionalNode<_NodeFunctions>> {
	#pragma region Types
	public:
		// Class related
		using _MyType					= FunctionalNode;
		using NodeType					= FunctionalNode;
		using NodeFunctions				= _NodeFunctions;
		using BaseNode					= BaseNode<NodeType>;

		// Types
		using NodePack					= std::pair<NodeType*, NodeType*>;
		using NodePackConst				= std::pair<const NodeType*, const NodeType*>;

		// Signarures
		using NodeCheckerSignature		= ll_bool_t(NodeFunctions::*)(const NodeType*) noexcept;
		using NodeCheckerConstSignature	= ll_bool_t(NodeFunctions::*)(const NodeType*) const noexcept;
		using NodeCompareSignature		= cmp_t(NodeFunctions::*)(const NodeType*, const NodeType*) noexcept;
		using NodeCompareConstSignature	= cmp_t(NodeFunctions::*)(const NodeType*, const NodeType*) const noexcept;
		using DieSignature				= void(NodeFunctions::*)() noexcept;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr ll_bool_t HAS_NODECHECKER = traits::common::has_nodeChecker_function_v<NodeFunctions, NodeCheckerSignature>;
		static constexpr ll_bool_t HAS_NODECHECKER_CONST = traits::common::has_nodeChecker_function_v<NodeFunctions, NodeCheckerConstSignature>;

		static constexpr ll_bool_t HAS_NODECOMPARE = traits::common::has_compareNode_function_v<NodeFunctions, NodeCompareSignature>;
		static constexpr ll_bool_t HAS_NODECOMPARE_CONST = traits::common::has_compareNode_function_v<NodeFunctions, NodeCompareConstSignature>;

	#pragma endregion
	#pragma region Assersts
	public:
		static_assert(traits::is_valid_type_checker_v<NodeFunctions>,
			"type_checker<NodeFunctions> detected an invalid type!");
		static_assert(traits::is_valid_class_checker_v<NodeFunctions>,
			"class_checker<NodeFunctions> detected an invalid class type!");

		static_assert(traits::common::has_die_function_v<NodeFunctions, DieSignature>,
			"NodeFunctions::die() noexcept is required!");

	#pragma endregion
	#pragma region Friends
	protected:
		friend class BaseNodeList<_NodeFunctions, llcpp::TRUE>;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr FunctionalNode() noexcept : NodeFunctions(), BaseNode() {}
		template<class... Args>
		constexpr FunctionalNode(NodeType* node, Args&&... args) noexcept
			: NodeFunctions(std::forward<Args>(args)...), BaseNode(node) {}
		constexpr ~FunctionalNode() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr FunctionalNode(const FunctionalNode& other) noexcept
			: NodeFunctions(std::forward<const NodeFunctions&>(other))
			, BaseNode() {}
		constexpr FunctionalNode& operator=(const FunctionalNode& other) noexcept {
			NodeFunctions::operator=(std::forward<const NodeFunctions&>(other));
			return *this;
		}
		constexpr FunctionalNode(FunctionalNode&& other) noexcept
			: NodeFunctions(std::forward<NodeFunctions&&>(other))
			, BaseNode() {}
		constexpr FunctionalNode& operator=(FunctionalNode&& other) noexcept {
			NodeFunctions::operator=(std::forward<NodeFunctions&&>(other));
			return *this;
		}

		constexpr FunctionalNode(const NodeFunctions& other) noexcept
			: NodeFunctions(std::forward<const NodeFunctions&>(other))
			, BaseNode() {}
		constexpr FunctionalNode& operator=(const NodeFunctions& other) noexcept {
			NodeFunctions::operator=(std::forward<const NodeFunctions&>(other));
			return *this;
		}
		constexpr FunctionalNode(NodeFunctions&& other) noexcept
			: NodeFunctions(std::forward<NodeFunctions&&>(other))
			, BaseNode() {}
		constexpr FunctionalNode& operator=(NodeFunctions&& other) noexcept {
			NodeFunctions::operator=(std::forward<NodeFunctions&&>(other));
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const FunctionalNode*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator FunctionalNode*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region BaseNodeOverrride
	public:
		__LL_NODISCARD__ constexpr const NodeType* get() const noexcept { return BaseNode::get(); }
		__LL_NODISCARD__ constexpr NodeType* get() noexcept { return BaseNode::get(); }
		constexpr void clear() noexcept {
			if constexpr (traits::common::has_simple_clear_function_v<NodeFunctions>)
				NodeFunctions::clear();
			this->set(this);
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
		#pragma region Link
	public:
		constexpr void linkLeft(NodeType* right) noexcept { this->set(right); }
		static constexpr void link(NodeType* left, NodeType* right) noexcept {
			left->set(right);
		}

		#pragma endregion
		#pragma region Insert
	protected:
		__LL_NODISCARD__ constexpr void insert_impl(NodeType* node) noexcept {
			node->set(this->get());
			this->set(node);
		}

	public:
		__LL_NODISCARD__ constexpr void insert(NodeType* node) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
			if (!node) __debug_error_nullptr_str(node, "node");
#endif // _DEBUG
			this->insert_impl(node);
		}
		__LL_NODISCARD__ constexpr ll_bool_t insert_s(NodeType* node) noexcept {
			if (!this || !node) return llcpp::FALSE;
			this->insert_impl(node);
			return llcpp::TRUE;
		}

		#pragma endregion
		#pragma region Extract
	protected:
		// @param[in] node Node that point to this node, this nodes does not has acces to that node
		__LL_NODISCARD__ constexpr void extract_impl(NodeType* node) noexcept {
			node->set(this->get());
		}

	public:
		// @param[in] node Node that point to this node, this nodes does not has acces to that node
		__LL_NODISCARD__ constexpr void extract(NodeType* node) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
			if (!node) __debug_error_nullptr_str(node, "node");
#endif // _DEBUG

			this->extract_impl(node);
		}
		// @param[in] node Node that point to this node, this nodes does not has acces to that node
		__LL_NODISCARD__ constexpr ll_bool_t extract_s(NodeType* node) noexcept {
			if (!this || !node) return llcpp::FALSE;
			this->extract_impl(node);
			return llcpp::TRUE;
		}

		#pragma endregion
		#pragma region Remove
	protected:
		// @param[in] node Node that point to this node, this nodes does not has acces to that node
		__LL_NODISCARD__ constexpr void remove_impl(NodeType* node) noexcept {
			this->extract_impl(node);
			this->die();
		}

	public:
		// @param[in] node Node that point to this node, this nodes does not has acces to that node
		__LL_NODISCARD__ constexpr void remove(NodeType* node) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
			if (!node) __debug_error_nullptr_str(node, "node");
#endif // _DEBUG
			this->remove_impl(node);
		}
		// @param[in] node Node that point to this node, this nodes does not has acces to that node
		__LL_NODISCARD__ constexpr ll_bool_t remove_s(NodeType* node) noexcept {
			if (!this || !node) return llcpp::FALSE;
			this->remove_impl(node);
			return llcpp::TRUE;
		}

		#pragma endregion
		#pragma region FindPrev
	protected:
		__LL_NODISCARD__ constexpr NodePack findprev_impl(const NodeType* end) noexcept {
			static_assert(HAS_NODECHECKER || HAS_NODECHECKER_CONST, HAS_NODECHECKER_STR);

			// This could never be nullptr
			NodeType* begin = this;
			NodeType* prev = LL_NULLPTR;
			do {
				if (NodeFunctions::nodeChecker(begin))
					return { prev, begin };
				else prev = begin;
			} while ((begin = begin->get()) != end);
			// Also check end
			return { LL_NULLPTR, LL_NULLPTR };
		}
		__LL_NODISCARD__ constexpr NodePackConst findprev_impl(const NodeType* end) const noexcept {
			static_assert(HAS_NODECHECKER_CONST, HAS_NODECHECKER_CONST_STR);

			// This could never be nullptr
			const NodeType* begin = this;
			const NodeType* prev = LL_NULLPTR;
			do {
				if (NodeFunctions::nodeChecker(begin))
					return { prev, begin };
				else prev = begin;
			} while ((begin = begin->get()) != end);
			// Also check end
			return { LL_NULLPTR, LL_NULLPTR };
		}

	public:
		__LL_NODISCARD__ constexpr NodePack findprev(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->findprev_impl(end);
		}
		__LL_NODISCARD__ constexpr NodePackConst findprev(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->findprev_impl(end);
		}
		__LL_NODISCARD__ constexpr NodePack findprev_s(const NodeType* end) noexcept {
			if (!this) return LL_NULLPTR;
			return this->findprev_impl(end);
		}
		__LL_NODISCARD__ constexpr NodePackConst findprev_s(const NodeType* end) const noexcept {
			if (!this) return LL_NULLPTR;
			return this->findprev_impl(end);
		}

		#pragma endregion
		#pragma region Find
	protected:
		__LL_NODISCARD__ constexpr NodeType* find_impl(const NodeType* end) noexcept {
			return this->findprev_impl(end).second;
		}
		__LL_NODISCARD__ constexpr const NodeType* find_impl(const NodeType* end) const noexcept {
			return this->findprev_impl(end).second;
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
	protected:
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
			if (!this) return llcpp::FALSE;
			return this->contains_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t contains_s(const NodeType* end) const noexcept {
			if (!this) return llcpp::FALSE;
			return this->contains_impl(end);
		}

		#pragma endregion
		#pragma region All
	protected:
		__LL_NODISCARD__ constexpr ll_bool_t all_impl(const NodeType* end) noexcept {
			static_assert(HAS_NODECHECKER || HAS_NODECHECKER_CONST, HAS_NODECHECKER_STR);

			NodeType* begin = this;
			do {
				if (!NodeFunctions::nodeChecker(begin)) return llcpp::FALSE;
			} while ((begin = begin->get()) != end);
			// Also check end
			return llcpp::TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t all_impl(const NodeType* end) const noexcept {
			static_assert(HAS_NODECHECKER_CONST, HAS_NODECHECKER_CONST_STR);

			const NodeType* begin = this;
			do {
				if (!NodeFunctions::nodeChecker(begin)) return llcpp::FALSE;
			} while ((begin = begin->get()) != end);
			// Also check end
			return llcpp::TRUE;
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
			if (!this) return llcpp::FALSE;
			return this->all_impl(end);
		}
		__LL_NODISCARD__ constexpr const ll_bool_t all_s(const NodeType* end) const noexcept {
			if (!this) return llcpp::FALSE;
			return this->all_impl(end);
		}

		#pragma endregion
		#pragma region Any
	protected:
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
			if (!this) return llcpp::FALSE;
			return this->any_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t any_s(const NodeType* end) const noexcept {
			if (!this) return llcpp::FALSE;
			return this->any_impl(end);
		}

		#pragma endregion
		#pragma region None
	protected:
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
			if (!this) return llcpp::FALSE;
			return this->none_impl(end);
		}
		__LL_NODISCARD__ constexpr ll_bool_t none_s(const NodeType* end) const noexcept {
			if (!this) return llcpp::FALSE;
			return this->none_impl(end);
		}

		#pragma endregion
		#pragma region GetLastAndMiddle
	protected:
		__LL_NODISCARD__ constexpr NodePack getLastAndMiddle_impl(const NodeType* end) noexcept {
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
		__LL_NODISCARD__ constexpr NodePackConst getLastAndMiddle_impl(const NodeType* end) const noexcept {
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
		__LL_NODISCARD__ constexpr NodePack getLastAndMiddle(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getLastAndMiddle_impl(end);
		}
		__LL_NODISCARD__ constexpr NodePackConst getLastAndMiddle(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getLastAndMiddle_impl(end);
		}
		__LL_NODISCARD__ constexpr NodePack getLastAndMiddle_s(const NodeType* end) noexcept {
			if (!this) return { LL_NULLPTR, LL_NULLPTR };
			return this->getLastAndMiddle_impl(end);
		}
		__LL_NODISCARD__ constexpr NodePackConst getLastAndMiddle_s(const NodeType* end) const noexcept {
			if (!this) return { LL_NULLPTR, LL_NULLPTR };
			return this->getLastAndMiddle_impl(end);
		}

		#pragma endregion
		#pragma region GetMiddle
	protected:
		__LL_NODISCARD__ constexpr NodeType* getMiddle_impl(const NodeType* end) noexcept {
			return this->getLastAndMiddle_impl(end).first;
		}
		__LL_NODISCARD__ constexpr const NodeType* getMiddle_impl(const NodeType* end) const noexcept {
			return this->getLastAndMiddle_impl(end).first;
		}

	public:
		__LL_NODISCARD__ constexpr NodeType* getMiddle(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getMiddle_impl(end);
		}
		__LL_NODISCARD__ constexpr const NodeType* getMiddle(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getMiddle_impl(end);
		}
		__LL_NODISCARD__ constexpr NodeType* getMiddle_s(const NodeType* end) noexcept {
			if (!this) return LL_NULLPTR;
			return this->getMiddle_impl(end);
		}
		__LL_NODISCARD__ constexpr const NodeType* getMiddle_s(const NodeType* end) const noexcept {
			if (!this) return LL_NULLPTR;
			return this->getMiddle_impl(end);
		}

		#pragma endregion
		#pragma region GetPrevMiddle
	protected:
		__LL_NODISCARD__ constexpr NodePack getPrevMiddle_impl(const NodeType* end) noexcept {
			NodeType* slow = this;
			NodeType* fast = this;
			NodeType* prev = LL_NULLPTR;
			do {
				if ((fast = fast->get()) != end) {
					slow = (prev = slow)->get();
					fast = fast->get();
				}
				else break;
			} while (fast != end);
			return { prev, slow };
		}
		__LL_NODISCARD__ constexpr NodePackConst getPrevMiddle_impl(const NodeType* end) const noexcept {
			const NodeType* slow = this;
			const NodeType* fast = this;
			const NodeType* prev = LL_NULLPTR;
			do {
				if ((fast = fast->get()) != end) {
					slow = (prev = slow)->get();
					fast = fast->get();
				}
				else break;
			} while (fast != end);
			return { prev, slow };
		}

	public:
		__LL_NODISCARD__ constexpr NodePack getPrevMiddle(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getPrevMiddle_impl(end);
		}
		__LL_NODISCARD__ constexpr NodePackConst getPrevMiddle(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getPrevMiddle_impl(end);
		}
		__LL_NODISCARD__ constexpr NodePack getPrevMiddle_s(const NodeType* end) noexcept {
			if (!this) return { LL_NULLPTR, LL_NULLPTR };
			return this->getPrevMiddle_impl(end);
		}
		__LL_NODISCARD__ constexpr NodePackConst getPrevMiddle_s(const NodeType* end) const noexcept {
			if (!this) return { LL_NULLPTR, LL_NULLPTR };
			return this->getPrevMiddle_impl(end);
		}

		#pragma endregion
		#pragma region GetLast
	protected:
		__LL_NODISCARD__ constexpr NodeType* getLast_impl(const NodeType* end) noexcept {
			NodeType* result = this;
			for (NodeType* tmp = LL_NULLPTR; (tmp = result->get()) != end; result = tmp);
			return result;
		}
		__LL_NODISCARD__ constexpr const NodeType* getLast_impl(const NodeType* end) const noexcept {
			const NodeType* result = this;
			for (const NodeType* tmp = LL_NULLPTR; (tmp = result->get()) != end; result = tmp);
			return result;
		}

	public:
		__LL_NODISCARD__ constexpr NodeType* getLast(const NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getLast_impl(end);
		}
		__LL_NODISCARD__ constexpr const NodeType* getLast(const NodeType* end) const noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return this->getLast_impl(end);
		}
		__LL_NODISCARD__ constexpr NodeType* getLast_s(const NodeType* end) noexcept {
			if (!this) return LL_NULLPTR;
			return this->getLast_impl(end);
		}
		__LL_NODISCARD__ constexpr const NodeType* getLast_s(const NodeType* end) const noexcept {
			if (!this) return LL_NULLPTR;
			return this->getLast_impl(end);
		}

		#pragma endregion
		#pragma region Distance
	protected:
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
	protected:
		// Finds middle node of list and splits the list
		__LL_NODISCARD__ static constexpr NodeType* split_list(NodeType* begin) noexcept {
			NodePack nodes = begin->getPrevMiddle(LL_NULLPTR);
			if(nodes.first) nodes.first->set(LL_NULLPTR);
			return nodes.second;
		}
		__LL_NODISCARD__ static constexpr NodeType* merge_lists(NodeType* left, NodeType* right) noexcept {
			static_assert(HAS_NODECOMPARE || HAS_NODECOMPARE_CONST, HAS_NODECOMPARE_STR);

			if (!left) return right;
			if (!right) return left;

			if (left->compareNode(left, right) <= llcpp::ZERO_CMP) {
				left->set(FunctionalNode::merge_lists(left->get(), right));
				return left;
			}
			else {
				right->set(FunctionalNode::merge_lists(left, right->get()));
				return right;
			}
		}
		__LL_NODISCARD__ static constexpr NodeType* merge_impl(NodeType* begin) noexcept {
			if (!begin || !begin->get()) return begin;

			NodeType* mid = FunctionalNode::split_list(begin);
			NodeType* left = FunctionalNode::merge_impl(begin);
			NodeType* right = FunctionalNode::merge_impl(mid);

			return FunctionalNode::merge_lists(left, right);
		}

	public:
		__LL_NODISCARD__ constexpr NodeType* mergeSort(NodeType* end) noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
			if (!end) __debug_error_nullptr_str(end, "end");
#endif // _DEBUG

			end->set(LL_NULLPTR);
			return FunctionalNode::merge_impl(this);
		}
		__LL_NODISCARD__ constexpr NodeType* mergeSort() noexcept {
#if defined(_DEBUG)
			if (!this) __debug_error_nullptr_str(this, "this");
#endif // _DEBUG

			return FunctionalNode::merge_impl(this);
		}
		__LL_NODISCARD__ constexpr NodeType* mergeSort_s(NodeType* end) noexcept {
			if (!this || !end) return LL_NULLPTR;
			end->set(LL_NULLPTR);
			return FunctionalNode::merge_impl(this);
		}
		__LL_NODISCARD__ constexpr NodeType* mergeSort_s() noexcept {
			if (!this) return LL_NULLPTR;
			return FunctionalNode::merge_impl(this);
		}

		#pragma endregion

		#pragma endregion

	#pragma endregion
};

#undef HAS_NODECHECKER_STR
#undef HAS_NODECHECKER_CONST_STR
#undef HAS_NODECOMPARE_STR

template <class _NodeType>
class ClassicNode : public BaseNode<_NodeType> {
	#pragma region Types
	public:
		using _MyType	= ClassicNode;
		using NodeType = _NodeType;
		using BaseNode = BaseNode<_NodeType>;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr ClassicNode() noexcept : BaseNode() {}
		constexpr ClassicNode(NodeType* node) noexcept : BaseNode(node) {}
		constexpr ~ClassicNode() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr ClassicNode(const ClassicNode&) noexcept = delete;
		constexpr ClassicNode& operator=(const ClassicNode&) noexcept = delete;
		constexpr ClassicNode(ClassicNode&&) noexcept = delete;
		constexpr ClassicNode& operator=(ClassicNode&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const ClassicNode*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator ClassicNode*() noexcept { return this; }

		#pragma endregion

	#pragma endregion
};

template <class Node_Type_Or_Functions, ll_bool_t IS_SPECIAL = llcpp::FALSE>
using Node = std::conditional_t<
	IS_SPECIAL,
	FunctionalNode<Node_Type_Or_Functions>,
	ClassicNode<Node_Type_Or_Functions>
>;

#define __LL_NAMED_NODE__(name) \
	template <class Node_Type_Or_Functions, ll_bool_t IS_SPECIAL = llcpp::FALSE> \
	class Node##name## : private Node<Node_Type_Or_Functions, IS_SPECIAL> { \
		public: \
			using _MyType		= Node##name##; \
			using ExtraClass	= Node_Type_Or_Functions; \
			using Node			= Node<Node_Type_Or_Functions, IS_SPECIAL>; \
			using NodeType		= std::conditional_t<IS_SPECIAL, Node##name##, ExtraClass>; \
	\
		public: \
			static constexpr ll_bool_t IS_SPECIAL_NODE = IS_SPECIAL; \
	\
		public: \
			constexpr Node##name##() noexcept : Node(LL_NULLPTR) {} \
			constexpr Node##name##(NodeType* next) noexcept : Node(next) {} \
			constexpr ~Node##name##() noexcept {} \
	\
		public: \
			constexpr Node##name##(const Node##name##&) noexcept = delete; \
			constexpr Node##name##& operator=(const Node##name##&) noexcept = delete; \
			constexpr Node##name##(Node##name##&&) noexcept = delete; \
			constexpr Node##name##& operator=(Node##name##&&) noexcept = delete; \
	\
		public: \
			__LL_NODISCARD__ constexpr operator const Node##name##*() const noexcept { return this; } \
			__LL_NODISCARD__ constexpr operator Node##name##*() noexcept { return this; } \
	\
		public: \
			__LL_NODISCARD__ constexpr const NodeType* get##name##() const noexcept { return Node::get(); } \
			__LL_NODISCARD__ constexpr NodeType* get##name##() noexcept { return Node::get(); } \
			constexpr void set##name##(NodeType* next) noexcept { Node::set(next); } \
	\
			__LL_NODISCARD__ constexpr NodeType* get##name##NoThis() noexcept { return Node::getNoThis(); } \
			__LL_NODISCARD__ constexpr const NodeType* get##name##NoThis() const noexcept { return Node::getNoThis(); } \
			__LL_NODISCARD__ constexpr NodeType* get##name##(len_t moves) noexcept { return Node::get(moves); } \
			__LL_NODISCARD__ constexpr const NodeType* get##name##(len_t moves) const noexcept { return Node::get(moves); } \
	}; \
	\
	template<class NodeType> \
	using Simple##name## = Node##name##<NodeType, llcpp::FALSE>; \
	\
	template<class NodeFunctions> \
	using Functional##name## = Node##name##<NodeFunctions, llcpp::FALSE>


} // namespace linked
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_NODE_HPP_
