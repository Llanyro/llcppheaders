//////////////////////////////////////////////
//	DoubleNode.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.3							//
//////////////////////////////////////////////

#if defined(LLANYLIB_DOUBLENODE_HPP_) // Guard && version protector
	#if LLANYLIB_DOUBLENODE_MAYOR_ != 7 || LLANYLIB_DOUBLENODE_MINOR_ < 3
		#if defined(LL_REAL_CXX23)
			#warning "Node.hpp version error!"
		#else
			#error "Node.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_DOUBLENODE_MAYOR_ || LLANYLIB_DOUBLENODE_MINOR_

#else !defined(LLANYLIB_DOUBLENODE_HPP_)

#error "This is in WIP. Wait to Release 7"

#define LLANYLIB_DOUBLENODE_HPP_
#define LLANYLIB_DOUBLENODE_MAYOR_ 7
#define LLANYLIB_DOUBLENODE_MINOR_ 3

#include "Node.hpp"

namespace llcpp {
namespace linked {

template<class T>
class DoubleNode : public NodePrev<DoubleNode<T>>, public NodeNext<DoubleNode<T>> {
	public:
		__LL_CLASS_TEMPLATE_TYPE__(T);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(DoubleNode<T>, DoubleNode);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(NodePrev<DoubleNode>, NodePrev);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(NodeNext<DoubleNode>, NodeNext);
	protected:
		__type data;
	public:
		constexpr DoubleNode() __LL_EXCEPT__ : __NodePrev(), __NodeNext(), data() {}
		constexpr DoubleNode(__cref data) __LL_EXCEPT__ : __NodePrev(), __NodeNext(), data(data) {}
		constexpr DoubleNode(__move data) __LL_EXCEPT__ : __NodePrev(), __NodeNext(), data(std::move(data)) {}
		constexpr ~DoubleNode() __LL_EXCEPT__ {}

		constexpr void __autopoint() __LL_EXCEPT__ {
			this->setPrev(this);
			this->setNext(this);
		}

		DoubleNode(__cref_DoubleNode) __LL_EXCEPT__ = delete;
		__ref_DoubleNode operator=(__cref_DoubleNode) __LL_EXCEPT__ = delete;

		DoubleNode(__move_DoubleNode) __LL_EXCEPT__ = delete;
		__ref_DoubleNode operator=(__move_DoubleNode) __LL_EXCEPT__ = delete;

		constexpr void setData(__cref data) __LL_EXCEPT__ { this->data = data; }
		constexpr void setData(__move data) __LL_EXCEPT__ { this->data = std::move(data); }
		constexpr __ref getData() __LL_EXCEPT__ { return this->data; }
		constexpr __cref getData() const __LL_EXCEPT__ { return this->data; }
		constexpr void clear() __LL_EXCEPT__ {}

		constexpr void unlink() __LL_EXCEPT__ {
			__DoubleNode::link(this->getPrev(), this->getNext());
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

		static constexpr void link(__ptr_DoubleNode left, __ptr_DoubleNode right) __LL_EXCEPT__ {
			left->setNext(right);
			right->setPrev(left);
		}
};

} // namespace linked
} // namespace llcpp

#endif // LLANYLIB_DOUBLENODE_HPP_
