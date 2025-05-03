#include "jeaii/jeaiii.hpp"

#include <cstdio>
#include <chrono>

int main(int argc, char** argv) {
	FILE* f = fopen("jeaii.txt", "w");
	char buffer[50];
	unsigned long long acc{};
	for(unsigned char i{}; i < 255; ++i) {
		auto start = ::std::chrono::high_resolution_clock::now();
		char* end = ::jeaiii::to_text_from_integer(buffer, i);
		acc += static_cast<unsigned long long>(::std::chrono::duration_cast<::std::chrono::nanoseconds>(::std::chrono::high_resolution_clock::now() - start).count());
		::std::fprintf(f, "[%u] '%.*s'", end - buffer, end - buffer, buffer);
	}
    ::std::fclose(f);
    ::std::fprintf(stdout, "jeaiii [%i ns] all", acc);
	return 0;
}
