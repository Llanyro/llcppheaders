
#include "../llanylib/Node.hpp"
#include <iostream>

class Base {
	public:
		int value;
		Base() noexcept : value(99) {}
		Base(int value) noexcept : value(value) {}
		~Base() noexcept {}
};

class H1 : public Base {
	public:
		H1() noexcept : Base() {}
		H1(int value) noexcept : Base(value) {}
		~H1() noexcept {}
};

class H2 : public Base {
	public:
		H2() noexcept : Base() {}
		H2(int value) noexcept : Base(value) {}
		~H2() noexcept {}
};

class D1 : public H1, public H2 {
	public:
		D1() noexcept : H1(), H2() {}
		D1(int value1, int value2) noexcept : H1(value1), H2(value2) {}
		~D1() noexcept {}
};


int main() {
	D1 a(80, 70);

	std::cout << "ASDF: " << llcpp::meta::linked::asdf() << "\n";

	std::cout << "Base: " << sizeof(Base) << "\n";
	std::cout << "H1: " << sizeof(H1) << "\n";
	std::cout << "H2: " << sizeof(H2) << "\n";
	std::cout << "D1: " << sizeof(D1) << "\n";
	std::cout << "A: " << sizeof(a) << "\n";
	std::cout << "Value1: " << a.H1::value << "\tValue2: " << a.H2::value << "\n";
	return 0;
}