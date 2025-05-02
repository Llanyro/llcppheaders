#include "jeaii/jeaiii.hpp"

#include <cstdio>

int main() {
    char buffer[50];
    char* end = ::jeaiii::to_text_from_integer(buffer, 64);
    ::std::fwrite(buffer, 1, end - buffer, stdout);
    return 0;
}
