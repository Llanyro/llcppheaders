#include <iostream>

//#define VIRTUAL_A
#define VIRTUAL_B

class A {
	public:
		A() noexcept { ::std::cout << "A\n"; }
#if defined(VIRTUAL_A)
		virtual ~A() noexcept { ::std::cout << "virtual ~A\n"; }
#else
		~A() noexcept { ::std::cout << "~A\n"; }
#endif
};

class B : public A {
	public:
		B() noexcept : A() { ::std::cout << "B\n"; }
#if defined(VIRTUAL_B)
		virtual ~B() noexcept { ::std::cout << "virtual ~B\n"; }
#else
		~B() noexcept { ::std::cout << "~B\n"; }
#endif
};

int main() {
	B* b = new (::std::nothrow) B();
	A* a = b;
	delete a;

	return 0;
}
