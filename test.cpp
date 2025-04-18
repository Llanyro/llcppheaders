#include <cstdio>

#include <chrono>

#include "llanylib/utils_base/hash/CityHash.hpp"

constexpr auto hash = ::llcpp::meta::utils::hash::CityHash<>().cityHash64("asdf", 4);

int main() {
    auto hash2 = ::llcpp::meta::utils::hash::CityHash<>().cityHash64("asdf", 4);
	::std::fwrite(__PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__), 1, stdout);
    ::std::printf("\n%llu\n", hash);
    ::std::printf("\n%llu\n", hash2);
}