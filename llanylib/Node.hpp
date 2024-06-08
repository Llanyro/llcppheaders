//////////////////////////////////////////////
//	Node.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
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

//#include "traits.hpp"

namespace llcpp {
namespace meta {
namespace linked {

template <class NodeType>
class NodeNext {
	#pragma region Assersts
	public:
		// [TOCHECK] Check with benchmark class
		//static_assert(std::is_base_of_v<NodeNext<NodeType>, NodeType>, 
		//	"NodeType from NodeNext<> must be a base of NodeNext<>");
	#pragma endregion
	#pragma region Attributes
	private:
		NodeType* next;
	#pragma endregion
	#pragma region Functions
	public:
		#pragma region Contructors
		constexpr NodeNext() __LL_EXCEPT__ : NodeNext(LL_NULLPTR) {}
		constexpr NodeNext(NodeType* next) __LL_EXCEPT__ : next(next) {}
		constexpr ~NodeNext() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		NodeNext(const NodeNext&) __LL_EXCEPT__ = delete;
		NodeNext& operator=(const NodeNext&) __LL_EXCEPT__ = delete;
		NodeNext(NodeNext&&) __LL_EXCEPT__ = delete;
		NodeNext& operator=(NodeNext&&) __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ operator const NodeNext*() const __LL_EXCEPT__ { return this; }
		__LL_NODISCARD__ operator NodeNext*() __LL_EXCEPT__ { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr const NodeType* getNext() const __LL_EXCEPT__ { return this->next; }
		__LL_NODISCARD__ constexpr NodeType* getNext() __LL_EXCEPT__ { return this->next; }
		constexpr void setNext(NodeType* next) __LL_EXCEPT__ { this->next = next; }
		//constexpr void clear() __LL_EXCEPT__ {}

		__LL_NODISCARD__ constexpr NodeType* getNextNoThis() __LL_EXCEPT__ {
			return (this->getNext() != this) ? this->getNext() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const NodeType* getNextNoThis() const __LL_EXCEPT__ {
			return (this->getNext() != this) ? this->getNext() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr NodeType* getNext(len_t moves) __LL_EXCEPT__ {
			NodeType* result = this;
			for (; moves > 0; --moves)
				result = result->getNext();
			return result;
		}
		__LL_NODISCARD__ constexpr const NodeType* getNext(len_t moves) const __LL_EXCEPT__ {
			const NodeType* result = this;
			for (; moves > 0; --moves)
				result = result->getNext();
			return result;
		}
		#pragma endregion
	#pragma endregion
};

template <class NodeType>
class NodePrev {
	#pragma region Assersts
	public:
		// [TOCHECK] Check with benchmark class
		//static_assert(std::is_base_of_v<NodePrev<NodeType>, NodeType>,
		//	"NodeType from NodePrev<> must be a base of NodePrev<>");
	#pragma endregion
	#pragma region Attributes
	private:
		NodeType* prev;
	#pragma endregion
	#pragma region Functions
	public:
		#pragma region Contructors
		constexpr NodePrev() __LL_EXCEPT__ : NodePrev(LL_NULLPTR) {}
		constexpr NodePrev(NodeType* prev) __LL_EXCEPT__ : prev(prev) {}
		constexpr ~NodePrev() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		NodePrev(const NodePrev&) __LL_EXCEPT__ = delete;
		NodePrev& operator=(const NodePrev&) __LL_EXCEPT__ = delete;
		NodePrev(NodePrev&&) __LL_EXCEPT__ = delete;
		NodePrev& operator=(NodePrev&&) __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ operator const NodePrev*() const __LL_EXCEPT__ { return this; }
		__LL_NODISCARD__ operator NodePrev*() __LL_EXCEPT__ { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr const NodeType* getPrev() const __LL_EXCEPT__ { return this->prev; }
		__LL_NODISCARD__ constexpr NodeType* getPrev() __LL_EXCEPT__ { return this->prev; }
		constexpr void setPrev(NodeType* prev) __LL_EXCEPT__ { this->prev = prev; }
		//constexpr void clear() __LL_EXCEPT__ {}

		__LL_NODISCARD__ constexpr NodeType* getPrevNoThis() __LL_EXCEPT__ {
			return (this->getPrev() != this) ? this->getPrev() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const NodeType* getPrevNoThis() const __LL_EXCEPT__ {
			return (this->getPrev() != this) ? this->getPrev() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr NodeType* getPrev(len_t moves) __LL_EXCEPT__ {
			NodeType* result = this;
			for (; moves > 0; --moves)
				result = result->getPrev();
			return result;
		}
		__LL_NODISCARD__ constexpr const NodeType* getPrev(len_t moves) const __LL_EXCEPT__ {
			const NodeType* result = this;
			for (; moves > 0; --moves)
				result = result->getPrev();
			return result;
		}
		#pragma endregion
	#pragma endregion
};

} // namespace linked
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_NODE_HPP_
