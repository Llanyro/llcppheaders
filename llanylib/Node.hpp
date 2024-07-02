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
		constexpr NodeNext() noexcept : NodeNext(LL_NULLPTR) {}
		constexpr NodeNext(NodeType* next) noexcept : next(next) {}
		constexpr ~NodeNext() noexcept {}

		#pragma endregion
		#pragma region CopyMove
		constexpr NodeNext(const NodeNext&) noexcept = delete;
		constexpr NodeNext& operator=(const NodeNext&) noexcept = delete;
		constexpr NodeNext(NodeNext&&) noexcept = delete;
		constexpr NodeNext& operator=(NodeNext&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator const NodeNext*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator NodeNext*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr const NodeType* getNext() const noexcept { return this->next; }
		__LL_NODISCARD__ constexpr NodeType* getNext() noexcept { return this->next; }
		constexpr void setNext(NodeType* next) noexcept { this->next = next; }
		//constexpr void clear() noexcept {}

		__LL_NODISCARD__ constexpr NodeType* getNextNoThis() noexcept {
			return (this->getNext() != this) ? this->getNext() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const NodeType* getNextNoThis() const noexcept {
			return (this->getNext() != this) ? this->getNext() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr NodeType* getNext(len_t moves) noexcept {
			NodeType* result = this;
			for (; moves > 0; --moves)
				result = result->getNext();
			return result;
		}
		__LL_NODISCARD__ constexpr const NodeType* getNext(len_t moves) const noexcept {
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
		constexpr NodePrev() noexcept : NodePrev(LL_NULLPTR) {}
		constexpr NodePrev(NodeType* prev) noexcept : prev(prev) {}
		constexpr ~NodePrev() noexcept {}

		#pragma endregion
		#pragma region CopyMove
		constexpr NodePrev(const NodePrev&) noexcept = delete;
		constexpr NodePrev& operator=(const NodePrev&) noexcept = delete;
		constexpr NodePrev(NodePrev&&) noexcept = delete;
		constexpr NodePrev& operator=(NodePrev&&) noexcept = delete;

		#pragma endregion
		#pragma region ClassReferenceOperators
		__LL_NODISCARD__ constexpr operator const NodePrev*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator NodePrev*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
		__LL_NODISCARD__ constexpr const NodeType* getPrev() const noexcept { return this->prev; }
		__LL_NODISCARD__ constexpr NodeType* getPrev() noexcept { return this->prev; }
		constexpr void setPrev(NodeType* prev) noexcept { this->prev = prev; }
		//constexpr void clear() noexcept {}

		__LL_NODISCARD__ constexpr NodeType* getPrevNoThis() noexcept {
			return (this->getPrev() != this) ? this->getPrev() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr const NodeType* getPrevNoThis() const noexcept {
			return (this->getPrev() != this) ? this->getPrev() : LL_NULLPTR;
		}
		__LL_NODISCARD__ constexpr NodeType* getPrev(len_t moves) noexcept {
			NodeType* result = this;
			for (; moves > 0; --moves)
				result = result->getPrev();
			return result;
		}
		__LL_NODISCARD__ constexpr const NodeType* getPrev(len_t moves) const noexcept {
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
