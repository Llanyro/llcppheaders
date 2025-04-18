
#include <utility>
#include <cstdio>

#pragma region Classes

struct Person {
	const char* birthdate;
	unsigned int patata;
	unsigned char edad;
};

class PersonClass {
	private:
		const char* birthdate;
		unsigned int patata;
		unsigned char edad;
		Person p;
	public:
		PersonClass(const char* birthdate, unsigned int patata, unsigned char edad, Person p)
			: birthdate(birthdate)
			, patata(patata)
			, edad(edad)
			, p(p)
		{}
		~PersonClass() {}

		const char* getBirthdate() const { return this->birthdate; }
		unsigned int getPatata() const { return this->patata; }
		unsigned char getEdad() const { return this->edad; }
		Person getPerson() const { return this->p; }
};

#pragma endregion
#pragma region Namespaces

using namespace std;

namespace patata {

int printf(const char* fmt, ...) {
	std::putchar('a');
	std::putc('\n', stderr);
	return 0;
}

} // namespace patata

#pragma endregion

template<class... Args>
class A {
	public:
		Args... args...;
		A(Args&&... args) : args(::std::forward<Args>(args)...) {}
		void print() { ::std::printf("Ha\n"); }
};

int main() {
	::std::printf("Patata %u\n", 10);
	::patata::printf("Patata %u\n", 10);


	Person a = { "10", 10, 9 };
	Person b;
	b.birthdate = "11";
	b.edad = 19;
	b.patata = 99;

	PersonClass p("19", 99, 255, a);

	printf(
		"Person data: %s, %u, %u, { %s, %u, %u }",
		p.getBirthdate(),
		p.getPatata(),
		p.getEdad(),
		p.getPerson().birthdate,
		p.getPerson().patata,
		p.getPerson().edad
	);

	A<int, char> asdasd(1, 2);
	asdasd.print();

	return 0;
}
