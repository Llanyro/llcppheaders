//////////////////////////////////////////////
//	Node.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_NODE_HPP_) // Guard && version protector
	#if LLANYLIB_NODE_MAYOR_ != 5 || LLANYLIB_NODE_MINOR_ < 0
		#error "Node.hpp version error!"
	#endif // LLANYLIB_NODE_MAYOR_ || LLANYLIB_NODE_MINOR_

#else !defined(LLANYLIB_NODE_HPP_)
#define LLANYLIB_NODE_HPP_
#define LLANYLIB_NODE_MAYOR_ 5
#define LLANYLIB_NODE_MINOR_ 0

#include "traits.hpp"

namespace llcpp {
namespace linked {

template <class NodeType>
class LL_SHARED_LIB NodeNext {
	public:
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(NodeType, NodeType);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(NodeNext<NodeType>, NodeNext);
		//static_assert(std::is_base_of_v<__NodeNext, __NodeType>);
	private:
		__ptr_NodeType next;
	public:
		constexpr NodeNext() __LL_EXCEPT__ : NodeNext(LL_NULLPTR) {}
		constexpr NodeNext(__ptr_NodeType next) __LL_EXCEPT__ : next(next) {}
		constexpr ~NodeNext() __LL_EXCEPT__ {}

		NodeNext(__cref_NodeNext) __LL_EXCEPT__ = delete;
		__ref_NodeNext operator=(__cref_NodeNext) __LL_EXCEPT__ = delete;
		NodeNext(__move_NodeNext) __LL_EXCEPT__ = delete;
		__ref_NodeNext operator=(__move_NodeNext) __LL_EXCEPT__ = delete;

		__LL_NODISCARD__ constexpr __ptr_NodeType getNext() __LL_EXCEPT__ { return this->next; }
		constexpr void setNext(__ptr_NodeType next) __LL_EXCEPT__ { this->next = next; }
		__LL_NODISCARD__ constexpr __cptr_NodeType getNext() const __LL_EXCEPT__ { return this->next; }
		constexpr void clear() __LL_EXCEPT__ {}

		__LL_NODISCARD__ constexpr __ptr_NodeType getNextNoThis() __LL_EXCEPT__ {
			return (this->getNext() != this) ? this->getNext() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __cptr_NodeType getNextNoThis() const __LL_EXCEPT__ {
			return (this->getNext() != this) ? this->getNext() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __ptr_NodeType getNext(const len_t &num) __LL_EXCEPT__ {
			__ptr_NodeType result = this;
			for (len_t i{}; i < num; ++i)
				result = result->getNext();
			return result;
		}
		__LL_NODISCARD__ constexpr __cptr_NodeType getNext(const len_t &num) const __LL_EXCEPT__ {
			__cptr_NodeType result = this;
			for (len_t i{}; i < num; ++i)
				result = result->getNext();
			return result;
		}
};

template <class NodeType>
class LL_SHARED_LIB NodePrev {
	public:
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(NodeType, NodeType);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(NodePrev<NodeType>, NodePrev);
		//static_assert(std::is_base_of_v<__NodePrev, __NodeType>);
	private:
		__ptr_NodeType prev;
	public:
		constexpr NodePrev() __LL_EXCEPT__ : NodePrev(LL_NULLPTR) {}
		constexpr NodePrev(__ptr_NodeType prev) __LL_EXCEPT__ : prev(prev) {}
		constexpr ~NodePrev() __LL_EXCEPT__ {}

		NodePrev(__cref_NodePrev) __LL_EXCEPT__ = delete;
		__ref_NodePrev operator=(__cref_NodePrev) __LL_EXCEPT__ = delete;
		NodePrev(__move_NodePrev) __LL_EXCEPT__ = delete;
		__ref_NodePrev operator=(__move_NodePrev) __LL_EXCEPT__ = delete;

		__LL_NODISCARD__ constexpr __ptr_NodeType getPrev() __LL_EXCEPT__ { return this->prev; }
		constexpr void setPrev(__ptr_NodeType prev) __LL_EXCEPT__ { this->prev = prev; }
		__LL_NODISCARD__ constexpr __cptr_NodeType getPrev() const __LL_EXCEPT__ { return this->prev; }
		constexpr void clear() __LL_EXCEPT__ {}

		__LL_NODISCARD__ constexpr __ptr_NodeType getPrevNoThis() __LL_EXCEPT__ {
			return (this->getPrev() != this) ? this->getPrev() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __cptr_NodeType getPrevNoThis() const __LL_EXCEPT__ {
			return (this->getPrev() != this) ? this->getPrev() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __ptr_NodeType getPrev(const len_t num) __LL_EXCEPT__ {
			__ptr_NodeType result = this;
			for (len_t i{}; i < num; ++i)
				result = result->getPrev();
			return result;
		}
		__LL_NODISCARD__ constexpr __cptr_NodeType getPrev(const len_t num) const __LL_EXCEPT__ {
			__cptr_NodeType result = this;
			for (len_t i{}; i < num; ++i)
				result = result->getPrev();
			return result;
		}
};

} // namespace linked
} // namespace llcpp

#endif // LLANYLIB_NODE_HPP_
