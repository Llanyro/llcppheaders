#include "jeaii/ll_jeaiii_to_text.hpp"

#include <cstdio>
#include <chrono>

int main() {
	FILE* f = fopen("llanyro.txt", "w");
	char buffer[50];
	unsigned long long acc{};
	for(::llcpp::u8 i{}; i < 255; ++i) {
		auto start = ::std::chrono::high_resolution_clock::now();
        char* end = ::llcpp::meta::jeaiii::integral_to_text<int, char, ::llcpp::LL_FALSE>(::llcpp::i32(i), buffer);
		acc += static_cast<unsigned long long>(::std::chrono::duration_cast<::std::chrono::nanoseconds>(::std::chrono::high_resolution_clock::now() - start).count());
		::std::fprintf(f, "[%u] '%.*s'", end - buffer, end - buffer, buffer);
	}
    ::std::fclose(f);
    ::std::fprintf(stdout, "llanyro [%i ns] all", acc);
	return 0;
}
