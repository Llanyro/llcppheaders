/*
 *	DoubleNode.hpp
 *
 *	Author: Francisco Julio Ruiz Fernandez
 *	Author: llanyro
 *
 *	Version: 4.2
 */

#if defined(LLANYLIB_DOUBLENODE_HPP_) // Guard && version protector
	#if LLANYLIB_DOUBLENODE_MAYOR_ != 4 || LLANYLIB_DOUBLENODE_MINOR_ < 2
		#error "algorithm.hpp version error!"
	#endif // LLANYLIB_DOUBLENODE_MAYOR_ || LLANYLIB_DOUBLENODE_MINOR_

#else !defined(LLANYLIB_DOUBLENODE_HPP_)
#define LLANYLIB_DOUBLENODE_HPP_
#define LLANYLIB_DOUBLENODE_MAYOR_ 4
#define LLANYLIB_DOUBLENODE_MINOR_ 2

#include "definitions.hpp"
#include "traits.hpp"

namespace llcpp {
namespace linked {

template<class T>
class LL_SHARED_LIB DoubleNode {
	public:
		__LL_CLASS_TEMPLATE_TYPE__(T);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(DoubleNode<T>, DoubleNode);
	protected:
		__ptr_DoubleNode prev;
		__ptr_DoubleNode next;
		__ptr data;
	public:
		constexpr DoubleNode() __LL_EXCEPT__
			: prev(LL_NULLPTR)
			, next(LL_NULLPTR)
			, data(LL_NULLPTR)
		{}
		constexpr ~DoubleNode() __LL_EXCEPT__ {}

		constexpr void __autopoint() __LL_EXCEPT__ {
			this->prev = this;
			this->next = this;
		}

		DoubleNode(__cref_DoubleNode other) = delete;
		__ref_DoubleNode operator=(__cref_DoubleNode other) = delete;

		DoubleNode(__move_DoubleNode other) = delete;
		__ref_DoubleNode operator=(__move_DoubleNode other) = delete;

		constexpr void setData(__ptr data) __LL_EXCEPT__ { this->data = data; }
		constexpr __ptr getData() __LL_EXCEPT__ { return this->data; }
		constexpr const __ptr getData() const __LL_EXCEPT__ { return this->data; }

		constexpr void setPrev(__ptr_DoubleNode prev) __LL_EXCEPT__ { this->prev = prev; }
		constexpr void setNext(__ptr_DoubleNode next) __LL_EXCEPT__ { this->next = next; }
		__LL_NODISCARD__ constexpr __ptr_DoubleNode getPrev() __LL_EXCEPT__ { return this->prev; }
		__LL_NODISCARD__ constexpr __ptr_DoubleNode getNext() __LL_EXCEPT__ { return this->next; }
		__LL_NODISCARD__ constexpr __cptr_DoubleNode getPrev() const __LL_EXCEPT__ { return this->prev; }
		__LL_NODISCARD__ constexpr __cptr_DoubleNode getNext() const __LL_EXCEPT__ { return this->next; }
		constexpr void clear() __LL_EXCEPT__ {}


		__LL_NODISCARD__ constexpr __ptr_DoubleNode getPrevNoThis() __LL_EXCEPT__ {
			return (this->getPrev() != this) ? this->getPrev() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __ptr_DoubleNode getNextNoThis() __LL_EXCEPT__ {
			return (this->getNext() != this) ? this->getNext() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __cptr_DoubleNode getPrevNoThis() const __LL_EXCEPT__ {
			return (this->getPrev() != this) ? this->getPrev() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __cptr_DoubleNode getNextNoThis() const __LL_EXCEPT__ {
			return (this->getNext() != this) ? this->getNext() : LL_NULLPTR;
		}

		constexpr void unlink() __LL_EXCEPT__ {
			DoubleNode::link(this->getPrev(), this->getNext());
		}
		constexpr void linkRight(__ptr_DoubleNode middleNode) __LL_EXCEPT__ {
			middleNode->setNext(this->getNext());
			middleNode->setPrev(this);

			this->getNext()->setPrev(middleNode);
			this->setNext(middleNode);
		}
		constexpr void linkLeft(__ptr_DoubleNode middleNode) __LL_EXCEPT__ {
			middleNode->setNext(this);
			middleNode->setPrev(this->getPrev());

			this->getPrev()->setNext(middleNode);
			this->setPrev(middleNode);
		}
		constexpr void swap(__ptr_DoubleNode other) __LL_EXCEPT__ {
			__ptr_DoubleNode otherPrev = other->getPrev();
			__ptr_DoubleNode otherNext = other->getNext();

			other->setPrev(this->getPrev());
			other->setNext(this->getNext());
			other->getPrev()->setNext(other);
			other->getNext()->setPrev(other);

			this->setPrev(otherPrev);
			this->setNext(otherNext);
			otherPrev->setNext(this);
			otherNext->setPrev(this);
		}

		__LL_NODISCARD__ constexpr __ptr_DoubleNode getNext(const len_t& num) __LL_EXCEPT__ {
			__ptr_DoubleNode result = this;
			for (len_t i{}; i < num; ++i)
				result = result->getNext();
			return result;
		}
		__LL_NODISCARD__ constexpr __ptr_DoubleNode getPrev(const len_t& num) __LL_EXCEPT__ {
			__ptr_DoubleNode result = this;
			for (len_t i{}; i < num; ++i)
				result = result->getPrev();
			return result;
		}
		__LL_NODISCARD__ constexpr __cptr_DoubleNode getNext(const len_t& num) const __LL_EXCEPT__ {
			__cptr_DoubleNode result = this;
			for (len_t i{}; i < num; ++i)
				result = result->getNext();
			return result;
		}
		__LL_NODISCARD__ constexpr __cptr_DoubleNode getPrev(const len_t& num) const __LL_EXCEPT__ {
			__cptr_DoubleNode result = this;
			for (len_t i{}; i < num; ++i)
				result = result->getPrev();
			return result;
		}

		constexpr static void link(__ptr_DoubleNode left, __ptr_DoubleNode right) __LL_EXCEPT__ {
			left->setNext(right);
			right->setPrev(left);
		}
};

} // namespace linked
} // namespace llcpp

#endif // LLANYLIB_DOUBLENODE_HPP_
