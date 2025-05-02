#include "jeaii/ll_jeaiii_to_text.hpp"


#include <cstdio>

int main() {
	char buffer[50];
	char* end = ::llcpp::meta::jeaiii::integral_to_text<int, char>(buffer, 64);
	::std::fwrite(buffer, 1, end - buffer, stdout);
	return 0;
}
