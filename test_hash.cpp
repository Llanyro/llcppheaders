#include <cstdio>

#include "llanylib/hash/CityHash.hpp"
#include "llanylib/hash/LlanyHash.hpp"

constexpr auto hash1 = ::llcpp::meta::utils::hash::CityHash<>().cityHash64("asdf", 4);
constexpr auto hash2 = ::llcpp::meta::utils::hash::CityHash<>().cityHash64("asdf", 4);

constexpr auto hash3 = ::llcpp::meta::utils::hash::LlanyHash<>().llanyHash64_v1("asdf", 4);
constexpr auto hash4 = ::llcpp::meta::utils::hash::LlanyHash<>().llanyHash64_v2("asdf", 4);
constexpr auto hash5 = ::llcpp::meta::utils::hash::LlanyHash<>().llanyHash64_v3("asdf", 4);

int main() {
	::std::fwrite(__PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__), 1, stdout);
	::std::printf("\n%llu\n", hash1);
	::std::printf("\n%llu\n", hash2);
	::std::printf("\n%llu\n", hash3);
	::std::printf("\n%llu\n", hash4);
	::std::printf("\n%llu\n", hash5);
	auto hash6 = ::llcpp::meta::utils::hash::LlanyHash<>().llanyHash64Combine("asdf", 4);
	::std::printf("\n%llu\n", hash6);
	return 0;
}
