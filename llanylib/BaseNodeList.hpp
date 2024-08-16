//////////////////////////////////////////////
//	BaseNodeList.hpp						//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_BASENODELIST_HPP_) // Guard && version protector
	#if LLANYLIB_BASENODELIST_MAYOR_ != 9 || LLANYLIB_BASENODELIST_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "BaseNodeList.hpp version error!"
		#else
			#error "BaseNodeList.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_BASENODELIST_MAYOR_ || LLANYLIB_BASENODELIST_MINOR_

#else !defined(LLANYLIB_BASENODELIST_HPP_)
#define LLANYLIB_BASENODELIST_HPP_
#define LLANYLIB_BASENODELIST_MAYOR_ 9
#define LLANYLIB_BASENODELIST_MINOR_ 0

#include "Node.hpp"
#include "Countable.hpp"

namespace llcpp {
namespace meta {
namespace linked {


template<class Node_Type_Or_Functions, ll_bool_t IS_SPECIAL = llcpp::LL_FALSE>
class BaseNodeList : public meta::CountableL {
	#pragma region Types
	public:
		using _MyType		= BaseNodeList;
		using ExtraClass	= Node_Type_Or_Functions;
		using NodeType		= linked::Node<Node_Type_Or_Functions, IS_SPECIAL>;
		using Countable		= meta::CountableL;

	#pragma endregion
	#pragma region Asserts

	#pragma endregion
	#pragma region Attributes
	private:
		NodeType* root;
		NodeType* root_end;

	#pragma endregion
	#pragma region Functions
		#pragma region ClassFunctions
		#pragma region Private
	private:
		constexpr void simpleClear() noexcept {
			this->root = LL_NULLPTR;
			this->root_end = LL_NULLPTR;
		}

		#pragma endregion
		#pragma region Contructors
	public:
		constexpr BaseNodeList() noexcept : BaseNodeList(LL_NULLPTR, LL_NULLPTR) {}
		constexpr BaseNodeList(NodeType* root, NodeType* root_end) noexcept
			: Countable(), begin(root), end(root_end) {}
		constexpr ~Countable() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr BaseNodeList(const BaseNodeList& other) noexcept = delete;
		constexpr BaseNodeList& operator=(const BaseNodeList& other) noexcept = delete;
		constexpr BaseNodeList(BaseNodeList&& other) noexcept
			: Countable(std::forward<Countable&&>(other))
			, root(other.root), root_end(other.root_end)
		{ other.simpleClear(); }
		constexpr BaseNodeList& operator=(BaseNodeList&& other) noexcept {
			Countable::operator=(std::forward<Countable&&>(other));
			this->root = other.root;
			this->root_end = other.root_end;
			other.simpleClear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const BaseNodeList*() const noexcept = delete;
		__LL_NODISCARD__ constexpr operator BaseNodeList*() noexcept = delete;

		#pragma endregion
		#pragma region ClassFunctions
		#pragma region Other
	public:
		__LL_NODISCARD__ constexpr ll_bool_t isValidPosition(const len_t position) const noexcept {
			return this->inRange(position);
		}

		#pragma endregion
		#pragma region GetNode
	private:
		__LL_NODISCARD__ constexpr NodeType* getNode_impl(const len_t position) noexcept {
			return this->root->get(position)
		}
		__LL_NODISCARD__ constexpr const NodeType* getNode_impl(const len_t position) const noexcept {
			return this->root->get(position)
		}

	public:
		__LL_NODISCARD__ constexpr NodeType* getNode(const len_t position) noexcept {
#if defined(_DEBUG)
			if (!this->isValidPosition(position)) __debug_error_out_of_range(node, this->lenght());
#endif // _DEBUG

			return this->getNode_impl(position)
		}
		__LL_NODISCARD__ constexpr const NodeType* getNode(const len_t position) const noexcept {
#if defined(_DEBUG)
			if (!this->isValidPosition(position)) __debug_error_out_of_range(node, this->lenght());
#endif // _DEBUG

			return this->getNode_impl(position)
		}
		__LL_NODISCARD__ constexpr NodeType* getNode_s(const len_t position) noexcept {
			return this->isValidPosition(position) ? this->getNode_impl(position) : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const NodeType* getNode_s(const len_t position) const noexcept {
			return this->isValidPosition(position) ? this->getNode_impl(position) : LL_NULLPTR;
		}

		#pragma endregion
		#pragma region PushBack
	private:
		// Adds a node to the end of the list
		constexpr void push_back_impl(NodeType* node) noexcept {
			if (Countable::empty()) this->root = node;
			else					this->root_end->set(node);

			this->root_end = node;
			this->root_end->set(this->root);
			Countable::operator++();
		}

	public:
		constexpr void push_back(NodeType* node) noexcept {
#if defined(_DEBUG)
			if (!node) __debug_error_nullptr_str(node, "node");
#endif // _DEBUG

			this->push_back_impl(node);
		}
		__LL_NODISCARD__ constexpr ll_bool_t push_back_s(NodeType* node) noexcept {
			if (!node) return llcpp::LL_FALSE;
			this->push_back_impl(node);
			return llcpp::LL_TRUE;
		}

		#pragma endregion
		#pragma region PushFront
	private:
		// Adds a node to the beginning of the list
		constexpr void push_front_impl(NodeType* node) noexcept {
			this->root = node;

			if (this->empty())	this->root_end = node;
			else				this->root->set(this->root_end->get());

			this->root_end->set(this->root);
			Countable::operator++();
		}

	public:
		constexpr void push_front(NodeType* node) noexcept {
#if defined(_DEBUG)
			if (!node) __debug_error_nullptr_str(node, "node");
#endif // _DEBUG

			this->push_front_impl(node);
		}
		__LL_NODISCARD__ constexpr ll_bool_t push_front_s(NodeType* node) noexcept {
			if (!node) return llcpp::LL_FALSE;
			this->push_front_impl(node);
			return llcpp::LL_TRUE;
		}

		#pragma endregion
		#pragma region Extract
	private:
		__LL_NODISCARD__ constexpr NodeType* extract_impl(const len_t position) noexcept {
			NodeType* extracted = LL_NULLPTR;
			// If is thee first node, we have different things to do
			if (position == 0) {
				extracted = this->root;

				// If list has more than one element
				// We extract the root and update it
				if (Countable::size() > 1ull) {
					this->root->extract_impl(this->root_end);
					this->root = this->root->get();
				}
			}
			else {
				NodeType* prev = this->getNode_impl(position - 1);
				extracted = prev->get();
				extracted->extract_impl(prev);

				// If is last node we need to do some different things
				if (position == Countable::size() - 1)
					this->root_end = prev;
			}

			Countable::operator--();
			return extracted;
		}

	public:
		__LL_NODISCARD__ constexpr NodeType* extract(const len_t position) noexcept {
#if defined(_DEBUG)
			if (!this->isValidPosition(position)) __debug_error_out_of_range(node, this->lenght());
#endif // _DEBUG

			return this->extract_impl(node);
		}
		constexpr NodeType* extract(const len_t position) noexcept {
			return this->isValidPosition(position) ? this->extract_impl(position) : LL_NULLPTR;
		}

		#pragma endregion
		#pragma region Remove
	private:
		__LL_NODISCARD__ constexpr void remove_impl(const len_t position) noexcept {
			this->extract_impl(position)->die();
		}

	public:
		__LL_NODISCARD__ constexpr NodeType* remove(const len_t position) noexcept {
#if defined(_DEBUG)
			if (!this->isValidPosition(position)) __debug_error_out_of_range(node, this->lenght());
#endif // _DEBUG

			return this->remove_impl(node);
		}
		constexpr NodeType* remove(const len_t position) noexcept {
			return this->isValidPosition(position) ? this->remove_impl(position) : LL_NULLPTR;
		}

		#pragma endregion

		#pragma endregion

		#pragma endregion
	#pragma endregion
};

} // namespace linked
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_BASENODELIST_HPP_
