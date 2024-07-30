//////////////////////////////////////////////
//	NodeDouble.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_NODEDOUBLE_HPP_) // Guard && version protector
	#if LLANYLIB_NODEDOUBLE_MAYOR_ != 9 || LLANYLIB_NODEDOUBLE_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "NodeDouble.hpp version error!"
		#else
			#error "NodeDouble.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_NODEDOUBLE_MAYOR_ || LLANYLIB_NODEDOUBLE_MINOR_

#else !defined(LLANYLIB_NODEDOUBLE_HPP_)
#define LLANYLIB_NODEDOUBLE_HPP_
#define LLANYLIB_NODEDOUBLE_MAYOR_ 9
#define LLANYLIB_NODEDOUBLE_MINOR_ 0

#include "NodePrev.hpp"
#include "NodeNext.hpp"
#include "common.hpp"

#if !defined(__debug_error_nullptr_str)
#define __debug_error_nullptr_str(ptr, str)
#endif
#if !defined(__debug_error_nullptr)
#define __debug_error_nullptr(ptr)
#endif


namespace llcpp {
namespace meta {
namespace linked {

template <class NodeType>
class NodeDouble : public linked::NodePrev<NodeType>, public linked::NodeNext<NodeType> {
	#pragma region Types
	public:
		using type = NodeType;
		using NodePrev = linked::NodePrev<NodeType>;
		using NodeNext = linked::NodeNext<NodeType>;

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
		constexpr NodeDouble() noexcept : NodeDouble(this, this) {}
		constexpr NodeDouble(NodeType* prev, NodeType* next) noexcept : NodePrev(prev), NodeNext(next) {}
		constexpr ~NodeDouble() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr NodeDouble(const NodeDouble&) noexcept = delete;
		constexpr NodeDouble& operator=(const NodeDouble&) noexcept = delete;
		constexpr NodeDouble(NodeDouble&& other) noexcept : NodeDouble() {
			this->swapSimple(std::move(other));	// Move all from other node to this node
		}
		constexpr NodeDouble& operator=(NodeDouble&& other) noexcept {
			this->unlink();				// Extract from list, and set it empty
			this->swapSimple(other);	// Move all from other node to this node
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const NodeDouble*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator NodeDouble*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	private:
		constexpr void simpleClear() noexcept {
			NodePrev::clear();
			NodeNext::clear();
		}
		constexpr void fixLeftRight() noexcept {
			this->getNext()->setPrev(this);
			this->getPrev()->setNext(this);
		}
	public:
		__LL_NODISCARD__ constexpr NodeType* operator[](i64 moves) noexcept {
			return (moves > 0)
				? this->getNext(static_cast<len_t>(moves))
				: this->getPrev(static_cast<len_t>(-moves));
		}
		__LL_NODISCARD__ constexpr const NodeType* operator[](i64 moves) const noexcept {
			return (moves > 0)
				? this->getNext(static_cast<len_t>(moves))
				: this->getPrev(static_cast<len_t>(-moves));
		}

		constexpr void unlink() noexcept { NodeDouble::link(this->getPrev(), this->getNext()); }
		constexpr void linkLeft(NodeType* left) noexcept {
#if defined(_DEBUG)
			if (!left) __debug_error_nullptr(left);
#endif // _DEBUG

			left->setNext(this);
			left->setPrev(this->getPrev());

			this->getPrev()->setNext(left);
			this->setPrev(left);
		}
		constexpr void linkRight(NodeType* right) noexcept {
#if defined(_DEBUG)
			if (!right) __debug_error_nullptr(right);
#endif // _DEBUG

			right->setNext(this->getNext());
			right->setPrev(this);

			this->getNext()->setPrev(right);
			this->setNext(right);
		}
		constexpr void linkLeft4(NodeType* left) noexcept {
#if defined(_DEBUG)
			if (!left) __debug_error_nullptr(left);
#endif // _DEBUG

			NodeType* thisprev = this->getPrev();
			NodeType* middleNext = left->getNext();

			NodeDouble::link(thisprev, left);
			NodeDouble::link(middleNext, this);
		}
		constexpr void linkRight4(NodeType* right) noexcept {
#if defined(_DEBUG)
			if (!right) __debug_error_nullptr(right);
#endif // _DEBUG

			NodeType* thisnext = this->getNext();
			NodeType* middleNext = right->getNext();

			NodeDouble::link(this, right);
			NodeDouble::link(middleNext, thisnext);
		}
		constexpr void swap(NodeType* other) noexcept {
#if defined(_DEBUG)
			if (!other) __debug_error_nullptr(other);
#endif // _DEBUG

			std::swap(this->prev, other->prev);
			std::swap(this->next, other->next);
			this->fixLeftRight();
			other->fixLeftRight();
		}
		// Like swap, but this node is empty
		constexpr void swapSimple(NodeType* other) noexcept {
#if defined(_DEBUG)
			if (!other) __debug_error_nullptr(other);
#endif // _DEBUG

			meta::common::copy_n_set(this->prev, other->prev, other);
			meta::common::copy_n_set(this->next, other->next, other);
			this->fixLeftRight();
		}
		constexpr void clear() noexcept {
			this->unlink();
			this->simpleClear();
		}

		__LL_NODISCARD__ constexpr ll_bool_t linkLeft_s(NodeType* left) noexcept {
			if (!left) return LL_FALSE;
			this->linkLeft(left);
			return LL_TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t linkRight_s(NodeType* right) noexcept {
			if (!right) return LL_FALSE;
			this->linkRight(right);
			return LL_TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t linkLeft4_s(NodeType* left) noexcept {
			if (!left) return LL_FALSE;
			this->linkLeft4(left);
			return LL_TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t linkRight4_s(NodeType* right) noexcept {
			if (!right) return LL_FALSE;
			this->linkRight4(right);
			return LL_TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t swap_s(NodeType* other) noexcept {
			if (!right) return LL_FALSE;
			this->swap(right);
			return LL_TRUE;
		}
		__LL_NODISCARD__ constexpr ll_bool_t swapSimple_s(NodeType* other) noexcept {
			if (!other) return LL_FALSE;
			this->swapSimple(other);
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
			right->setPrev(left);
		}
		static constexpr void link(NodeType* left, NodeType* middle, NodeType* right) noexcept {
#if defined(_DEBUG)
			if (!left) __debug_error_nullptr_str(left, "left");
			if (!middle) __debug_error_nullptr_str(middle, "middle");
			if (!right) __debug_error_nullptr_str(right, "right");
#endif // _DEBUG

			NodeDouble::link(left, middle);
			NodeDouble::link(middle, right);
		}

		__LL_NODISCARD__ static constexpr ll_bool_t link_s(NodeType* left, NodeType* right) noexcept {
			if (!left || !right) return LL_FALSE;
			NodeDouble::link(left, right);
			return LL_TRUE;
		}
		__LL_NODISCARD__ static constexpr ll_bool_t link_s(NodeType* left, NodeType* middle, NodeType* right) noexcept {
			if (!left || !right) return LL_FALSE;
			NodeDouble::link(left, right);
			return LL_TRUE;
		}

		#pragma endregion

	#pragma endregion
};

class N : public NodeDouble<N> {

};

void a() {
	N b;
}

} // namespace linked
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_NODEDOUBLE_HPP_
