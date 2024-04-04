#include "../StringView.hpp"

#include "../Node.hpp"
//#include "../DoubleNode.hpp"

#include <iostream>
#include <string>

constexpr auto HELLO_WORLD_1 = llcpp::StringView("Hello world");
constexpr auto HELLO_WORLD_2 = llcpp::StringView("Hello world!");
constexpr auto EMPTY_STRING = llcpp::StringView("");
constexpr auto QUESTION_STRING = llcpp::StringView("?");
constexpr auto EXTRA_STRING = llcpp::StringView(L"à");

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

int main() {
	printStringData(HELLO_WORLD_1);
	printStringData(HELLO_WORLD_2);
	printStringData(EMPTY_STRING);
	printStringData(QUESTION_STRING);
	printStringData(EXTRA_STRING);

	return 0;
}
