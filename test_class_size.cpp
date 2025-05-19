#include <cstdio>

class EmptyClass {
	public:
		constexpr void process(int& a) const noexcept {
			a = 99;
		}
};

class Container {
	public:
		int* p1;

		constexpr void process() const noexcept {
			Container* c = const_cast<Container*>(this);
			EmptyClass().process(*c->p1);
		}
};


int main() {
	int value = 88;
	Container a;
	a.p1 = &value;
	a.process();
	::std::printf("Val: %i\n", *a.p1);
	::std::printf("Size: %u\n", sizeof(a));
	return 0;
}