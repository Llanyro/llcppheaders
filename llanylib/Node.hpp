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
		using __NodeType = traits::template_types<NodeType>;
		using __NodeNext = traits::template_types<NodeNext<NodeType>>;
		//static_assert(std::is_base_of_v<__NodeNext, __NodeType>);
	private:
		__NodeType::ptr next;
	public:
		constexpr NodeNext() __LL_EXCEPT__ : NodeNext(LL_NULLPTR) {}
		constexpr NodeNext(__NodeType::ptr next) __LL_EXCEPT__ : next(next) {}
		constexpr ~NodeNext() __LL_EXCEPT__ {}

		NodeNext(__NodeNext::cref) __LL_EXCEPT__ = delete;
		__NodeNext::ref operator=(__NodeNext::cref) __LL_EXCEPT__ = delete;
		NodeNext(__NodeNext::move) __LL_EXCEPT__ = delete;
		__NodeNext::ref operator=(__NodeNext::move) __LL_EXCEPT__ = delete;

		__LL_NODISCARD__ constexpr __NodeType::ptr getNext() __LL_EXCEPT__ { return this->next; }
		constexpr void setNext(__NodeType::ptr next) __LL_EXCEPT__ { this->next = next; }
		__LL_NODISCARD__ constexpr __NodeType::cptr getNext() const __LL_EXCEPT__ { return this->next; }
		constexpr void clear() __LL_EXCEPT__ {}

		__LL_NODISCARD__ constexpr __NodeType::ptr getNextNoThis() __LL_EXCEPT__ {
			return (this->getNext() != this) ? this->getNext() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __NodeType::cptr getNextNoThis() const __LL_EXCEPT__ {
			return (this->getNext() != this) ? this->getNext() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __NodeType::ptr getNext(const len_t &num) __LL_EXCEPT__ {
			typename __NodeType::ptr result = this;
			for (len_t i{}; i < num; ++i)
				result = result->getNext();
			return result;
		}
		__LL_NODISCARD__ constexpr __NodeType::cptr getNext(const len_t &num) const __LL_EXCEPT__ {
			typename __NodeType::cptr result = this;
			for (len_t i{}; i < num; ++i)
				result = result->getNext();
			return result;
		}
};

template <class NodeType>
class LL_SHARED_LIB NodePrev {
	public:
		using __NodeType = traits::template_types<NodeType>;
		using __NodePrev = traits::template_types<NodePrev<NodeType>>;
		//static_assert(std::is_base_of_v<__NodePrev, __NodeType>);
	private:
		__NodeType::ptr prev;
	public:
		constexpr NodePrev() __LL_EXCEPT__ : NodePrev(LL_NULLPTR) {}
		constexpr NodePrev(__NodeType::ptr prev) __LL_EXCEPT__ : prev(prev) {}
		constexpr ~NodePrev() __LL_EXCEPT__ {}

		NodePrev(__NodePrev::cref) __LL_EXCEPT__ = delete;
		__NodePrev::ref operator=(__NodePrev::cref) __LL_EXCEPT__ = delete;
		NodePrev(__NodePrev::move) __LL_EXCEPT__ = delete;
		__NodePrev::ref operator=(__NodePrev::move) __LL_EXCEPT__ = delete;

		__LL_NODISCARD__ constexpr __NodeType::ptr getPrev() __LL_EXCEPT__ { return this->prev; }
		constexpr void setPrev(__NodeType::ptr prev) __LL_EXCEPT__ { this->prev = prev; }
		__LL_NODISCARD__ constexpr __NodeType::cptr getPrev() const __LL_EXCEPT__ { return this->prev; }
		constexpr void clear() __LL_EXCEPT__ {}

		__LL_NODISCARD__ constexpr __NodeType::ptr getPrevNoThis() __LL_EXCEPT__ {
			return (this->getPrev() != this) ? this->getPrev() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __NodeType::cptr getPrevNoThis() const __LL_EXCEPT__ {
			return (this->getPrev() != this) ? this->getPrev() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __NodeType::ptr getPrev(const len_t num) __LL_EXCEPT__ {
			typename __NodeType::ptr result = this;
			for (len_t i{}; i < num; ++i)
				result = result->getPrev();
			return result;
		}
		__LL_NODISCARD__ constexpr __NodeType::cptr getPrev(const len_t num) const __LL_EXCEPT__ {
			typename __NodeType::cptr result = this;
			for (len_t i{}; i < num; ++i)
				result = result->getPrev();
			return result;
		}
};

} // namespace linked
} // namespace llcpp

#endif // LLANYLIB_NODE_HPP_
