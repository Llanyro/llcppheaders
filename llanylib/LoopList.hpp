//////////////////////////////////////////////
//	Loop.hpp								//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 4.2							//
//////////////////////////////////////////////

#if defined(LLANYLIB_LINKEDLIST_HPP_) // Guard && version protector
	#if LLANYLIB_LINKEDLIST_MAYOR_ != 4 || LLANYLIB_LINKEDLIST_MINOR_ < 2
		#error "LinkedList.hpp version error!"
	#endif // LLANYLIB_LINKEDLIST_MAYOR_ || LLANYLIB_LINKEDLIST_MINOR_

#else !defined(LLANYLIB_LINKEDLIST_HPP_)
#define LLANYLIB_LINKEDLIST_HPP_
#define LLANYLIB_LINKEDLIST_MAYOR_ 4
#define LLANYLIB_LINKEDLIST_MINOR_ 2

#include "DoubleNode.hpp"
#include "Countable.hpp"

namespace llcpp {
namespace linked {

template<class T>
class LL_SHARED_LIB LinkedList : public CountableL {
	public:
		__LL_CLASS_TEMPLATE_TYPE__(T);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(LinkedList<T>, LinkedList);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(DoubleNode<T>, DoubleNode);
		using Foreach = void(*)(__ref);
		using ForeachConst = void(*)(__cref);
		using RemoveCoincidences = ll_bool_t(*)(__cref, __cref, void* extra_data);
		using LoopUntil = ll_bool_t(*)(__ref);
		using LoopUntilConst = ll_bool_t(*)(__cref);
	protected:
		__ptr_DoubleNode root;	// Nodes
	protected:
		static constexpr ll_bool_t comparator(__cref __1, __cref __2, void* extra_data) {
			return (*static_cast<ll_bool_t*>(extra_data) = (__1 == __2));
		}
		// This should be used only in list that contains the node
		void removeNode(__ptr_DoubleNode n) __LL_EXCEPT__ {
			if (n == this->root) this->root = this->root->getNextNoThis();
			n->unlink();
			CountableL::operator--();
		}
	public:
		constexpr LinkedList() __LL_EXCEPT__ : CountableL(), root(LL_NULLPTR) {}
		// No need to remove or anyting any node
		// This class is supposed to be used only in stack memory
		constexpr ~LinkedList() __LL_EXCEPT__ {}

		constexpr LinkedList(__cref_LinkedList) __LL_EXCEPT__ = delete;
		constexpr __LinkedList& operator=(__cref_LinkedList) __LL_EXCEPT__ = delete;

		constexpr LinkedList(__move_LinkedList) __LL_EXCEPT__ = delete;
		constexpr __LinkedList& operator=(__move_LinkedList) __LL_EXCEPT__ = delete;

		#pragma region InsertionDeletion
		constexpr void push_back(__ptr_DoubleNode n) __LL_EXCEPT__ {
			n->__autopoint();
			if (!this->root) this->root = n;
			else			 this->root->linkLeft(n);
			CountableL::operator++();
		}
		constexpr void push_front(__ptr_DoubleNode n) __LL_EXCEPT__ {
			this->push_back(n);
			this->root = this->root->getPrev();
			CountableL::operator++();
		}
		constexpr ll_bool_t remove(__cref data) __LL_EXCEPT__ {
			ll_bool_t found = LL_FALSE;
			this->removeCoincidences(data, &found, __LinkedList::comparator);
			return found;
		}

		#pragma endregion
		#pragma region Loop
		constexpr void foreach(Foreach func) {
			if (!this->root) return;
			__ptr_DoubleNode n = this->root;
			do {
				func(n->getData());
				n = n->getNext();
			} while (n != this->root);
		}
		constexpr void foreach(ForeachConst func) const {
			if (!this->root) return;
			__cptr_DoubleNode n = this->root;
			do {
				func(n->getData());
				n = n->getNext();
			} while (n != this->root);
		}
		constexpr void removeCoincidences(__cref data, void* extra_data, RemoveCoincidences func) __LL_EXCEPT__ {
			if (!this->root) return;
			__ptr_DoubleNode n = this->root;

			for (len_t i = this->len(); i > 0ull; --i) {
				if (func(n->getData(), data, extra_data)) {
					__ptr_DoubleNode tmp = n;
					n = n->getNext();
					this->removeNode(tmp);
				}
				else n = n->getNext();
			}
		}
		constexpr void rRemoveCoincidences(__cref data, void* extra_data, RemoveCoincidences func) __LL_EXCEPT__ {
			if (!this->root) return;
			__ptr_DoubleNode n = this->root->getPrev();

			for (len_t i = this->len(); i > 0; --i) {
				if (func(n->getData(), data, extra_data)) {
					__ptr_DoubleNode tmp = n;
					n = n->getPrev();
					this->removeNode(tmp);
				}
				else n = n->getPrev();
			}
		}
		constexpr void loopUntil(LoopUntil func) __LL_EXCEPT__ {
			if (!this->root) return;
			__ptr_DoubleNode n = this->root;
			do {
				if (func(n->getData())) break;
				n = n->getNext();
			} while (n != this->root);
		}
		constexpr void loopUntil(LoopUntilConst func) const __LL_EXCEPT__ {
			if (!this->root) return;
			__cptr_DoubleNode n = this->root;
			do {
				if (func(n->getData())) break;
				n = n->getNext();
			} while (n != this->root);
		}

		#pragma endregion
		#pragma region Access
		constexpr __ref operator[](const len_t pos) __LL_EXCEPT__ {
			return this->root->getNext(pos)->getData();
		}
		constexpr __cref operator[](const len_t pos) const __LL_EXCEPT__ {
			return this->root->getNext(pos)->getData();
		}

		#pragma endregion
};
} // namespace linked
} // namespace llcpp

#endif // LLANYLIB_LINKEDLIST_HPP_
