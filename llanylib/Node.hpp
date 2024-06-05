//////////////////////////////////////////////
//	Node.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 7.3							//
//////////////////////////////////////////////

#if defined(LLANYLIB_NODE_HPP_) // Guard && version protector
	#if LLANYLIB_NODE_MAYOR_ != 7 || LLANYLIB_NODE_MINOR_ < 3
		#if defined(LL_REAL_CXX23)
			#warning "Node.hpp version error!"
		#else
			#error "Node.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_NODE_MAYOR_ || LLANYLIB_NODE_MINOR_

#else !defined(LLANYLIB_NODE_HPP_)
#define LLANYLIB_NODE_HPP_
#define LLANYLIB_NODE_MAYOR_ 7
#define LLANYLIB_NODE_MINOR_ 3

#include "traits.hpp"

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
	#pragma region ClassTypes
	public:
		using __NodeType = traits::template_types<NodeType>;
		using __NodeNext = traits::template_types<NodeNext<NodeType>>;
	#pragma endregion
	#pragma region Attributes
	private:
		__NodeType::ptr next;
	#pragma endregion
	#pragma region Functions
	public:
		#pragma region Contructors
		constexpr NodeNext() __LL_EXCEPT__ : NodeNext(LL_NULLPTR) {}
		constexpr NodeNext(__NodeType::ptr next) __LL_EXCEPT__ : next(next) {}
		constexpr ~NodeNext() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		NodeNext(__NodeNext::cref) __LL_EXCEPT__ = delete;
		__NodeNext::ref operator=(__NodeNext::cref) __LL_EXCEPT__ = delete;
		NodeNext(__NodeNext::move) __LL_EXCEPT__ = delete;
		__NodeNext::ref operator=(__NodeNext::move) __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ operator __NodeNext::cptr() const __LL_EXCEPT__ { return this; }
		__LL_NODISCARD__ operator __NodeNext::ptr() __LL_EXCEPT__ { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr __NodeType::cptr getNext() const __LL_EXCEPT__ { return this->next; }
		__LL_NODISCARD__ constexpr __NodeType::ptr getNext() __LL_EXCEPT__ { return this->next; }
		constexpr void setNext(__NodeType::ptr next) __LL_EXCEPT__ { this->next = next; }
		//constexpr void clear() __LL_EXCEPT__ {}

		__LL_NODISCARD__ constexpr __NodeType::ptr getNextNoThis() __LL_EXCEPT__ {
			return (this->getNext() != this) ? this->getNext() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __NodeType::cptr getNextNoThis() const __LL_EXCEPT__ {
			return (this->getNext() != this) ? this->getNext() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __NodeType::ptr getNext(len_t moves) __LL_EXCEPT__ {
			typename __NodeType::ptr result = this;
			for (; moves > 0; --moves)
				result = result->getNext();
			return result;
		}
		__LL_NODISCARD__ constexpr __NodeType::cptr getNext(len_t moves) const __LL_EXCEPT__ {
			typename __NodeType::cptr result = this;
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
	#pragma region ClassTypes
	public:
		using __NodeType = traits::template_types<NodeType>;
		using __NodePrev = traits::template_types<NodePrev<NodeType>>;
	#pragma endregion
	#pragma region Attributes
	private:
		__NodeType::ptr prev;
	#pragma endregion
	#pragma region Functions
	public:
		#pragma region Contructors
		constexpr NodePrev() __LL_EXCEPT__ : NodePrev(LL_NULLPTR) {}
		constexpr NodePrev(__NodeType::ptr prev) __LL_EXCEPT__ : prev(prev) {}
		constexpr ~NodePrev() __LL_EXCEPT__ {}

		#pragma endregion
		#pragma region CopyMove
		NodePrev(__NodePrev::cref) __LL_EXCEPT__ = delete;
		__NodePrev::ref operator=(__NodePrev::cref) __LL_EXCEPT__ = delete;
		NodePrev(__NodePrev::move) __LL_EXCEPT__ = delete;
		__NodePrev::ref operator=(__NodePrev::move) __LL_EXCEPT__ = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ operator __NodePrev::cptr() const __LL_EXCEPT__ { return this; }
		__LL_NODISCARD__ operator __NodePrev::ptr() __LL_EXCEPT__ { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr __NodeType::cptr getPrev() const __LL_EXCEPT__ { return this->prev; }
		__LL_NODISCARD__ constexpr __NodeType::ptr getPrev() __LL_EXCEPT__ { return this->prev; }
		constexpr void setPrev(__NodeType::ptr prev) __LL_EXCEPT__ { this->prev = prev; }
		//constexpr void clear() __LL_EXCEPT__ {}

		__LL_NODISCARD__ constexpr __NodeType::ptr getPrevNoThis() __LL_EXCEPT__ {
			return (this->getPrev() != this) ? this->getPrev() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __NodeType::cptr getPrevNoThis() const __LL_EXCEPT__ {
			return (this->getPrev() != this) ? this->getPrev() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr __NodeType::ptr getPrev(len_t moves) __LL_EXCEPT__ {
			typename __NodeType::ptr result = this;
			for (; moves > 0; --moves)
				result = result->getPrev();
			return result;
		}
		__LL_NODISCARD__ constexpr __NodeType::cptr getPrev(len_t moves) const __LL_EXCEPT__ {
			typename __NodeType::cptr result = this;
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
