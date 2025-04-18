/*struct M;

struct S {
	S* operator()();
	int N;
	int M;

	void mem(S s) {
		auto(s)()->M; // expression (S::M hides ::M), invalid before C++23
	}
};

void f(S s) {
	{
		auto(s)()->N; // expression, invalid before C++23
		auto(s)()->M; // function declaration, equivalent to M s();
	}
	{
		S(s)()->N;    // expression
		S(s)()->M;    // expression
	}
}

void f1(int a) [[noreturn]];
*/

//void inc(auto... a) {}
template<class... Args>
void inc(Args... a) {}

int main() {
	inc();
	inc(1, 'a');
}
