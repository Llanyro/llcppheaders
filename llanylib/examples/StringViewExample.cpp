//////////////////////////////////////////////
//	StringViewExample.cpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 4.2							//
//////////////////////////////////////////////

#include "../StringView.hpp"

#include "../LinkedList.hpp"

#include <iostream>
#include <string>
#include <list>

constexpr auto HELLO_WORLD_1 = llcpp::StringView("Hello world");
constexpr auto HELLO_WORLD_2 = llcpp::StringView("Hello world!");
constexpr auto EMPTY_STRING = llcpp::StringView("");
constexpr auto QUESTION_STRING = llcpp::StringView("?");
constexpr auto EXTRA_STRING = llcpp::StringView(L"à");

template<class T>
class LinkedListB : public llcpp::linked::LinkedList<T> {
	public:
		__LL_CLASS_TEMPLATE_TYPE__(T);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(llcpp::linked::LinkedList<T>, LinkedList);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(LinkedListB<T>, LinkedListB);
		__LL_CLASS_TEMPLATE_CUSTOM_TYPE__(llcpp::linked::DoubleNode<T>, DoubleNode);
	public:
		LinkedListB() __LL_EXCEPT__ : __LinkedList() {}
		~LinkedListB() __LL_EXCEPT__ { this->clear(); }

		LinkedListB(__cref_LinkedListB) __LL_EXCEPT__ = delete;
		__LinkedListB& operator=(__cref_LinkedListB) __LL_EXCEPT__ = delete;

		LinkedListB(__move_LinkedListB other) __LL_EXCEPT__ : __LinkedList(std::move(other)) {}
		__LinkedListB& operator=(__move_LinkedListB other) __LL_EXCEPT__ {
			__LinkedList::operator=(std::move(other));
			return *this;
		}

		void operator+=(__cref n) __LL_EXCEPT__ {
			__LinkedList::operator+=(new __DoubleNode(n));
		}
		void operator+=(__move n) __LL_EXCEPT__ {
			__LinkedList::operator+=(new __DoubleNode(std::move(n)));
		}
		void push_back(__cref n) __LL_EXCEPT__ {
			__LinkedList::push_back(new __DoubleNode(n));
		}
		void push_back(__move n) __LL_EXCEPT__ {
			__LinkedList::push_back(new __DoubleNode(std::move(n)));
		}
		void push_front(__cref n) __LL_EXCEPT__ {
			__LinkedList::push_front(new __DoubleNode(n));
		}
		void push_front(__move n) __LL_EXCEPT__ {
			__LinkedList::push_front(new __DoubleNode(std::move(n)));
		}

		void clear() __LL_EXCEPT__ {
			if (this->root != LL_NULLPTR) {
				__DoubleNode* n = this->root;
				this->root->getPrev()->setNext(LL_NULLPTR);

				while (n->getNext() != LL_NULLPTR) {
					n = n->getNext();
					delete n->getPrev();
				}
				//if (this->len() > 1)
				delete n;

				this->root = LL_NULLPTR;
				n = LL_NULLPTR;
			}
			__LinkedList::clear();
		}
};

template<class T, len_t N>
void printStringData(const llcpp::StringView<N, T>& s) {
	std::cout << "******** Starting ********\n";

	auto f = [&s](std::conditional_t<std::is_same_v<T, const wchar_t>, std::wostream, std::ostream>& cout, const T(&hello)[6], const T(&rld)[4]) -> void {
		for (auto& i : s)
			cout << i << ":" << int(i) << " ";
		cout << "\n";
		cout << s.begin() << "\n";

		if (s.starts_with(hello)) cout << s.begin() << " starts with " << hello << "\n";
		else cout << s.begin() << " does not starts with " << hello << "\n";

		if (s.ends_with(rld)) cout << s.begin() << " ends with " << rld << "\n";
		else cout << s.begin() << " does not ends with " << rld << "\n";

		cout << "\n\n";
	};
	if constexpr (std::is_same_v<T, const wchar_t>) f(std::wcout, L"Hello", L"rld");
	else f(std::cout, "Hello", "rld");
}

void __testing_linked_list_no_constexpr__() {
	LinkedListB<len_t> list;
	for (len_t i{}; i < 50; ++i)
		list += i;

	list.foreach([](const len_t& v) { std::cout << "Val: " << v << "\n"; });
}

int main() {
	printStringData(HELLO_WORLD_1);
	printStringData(HELLO_WORLD_2);
	printStringData(EMPTY_STRING);
	printStringData(QUESTION_STRING);
	printStringData(EXTRA_STRING);

	__testing_linked_list_no_constexpr__();

	return 0;
}
