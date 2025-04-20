#define __LL_USE_WIDE_CHAR 1
#define __LL_EXCEPTIONS 1

#define __debug_error_exceptions_full(asdf) ::std::printf(asdf)
#define __debug_error_exceptions_empty(asdf) ::std::printf(asdf)

#include <cstdio>

//#include "../llanylib/utils_base/IteratorCommon.hpp"
//#include "../llanylib/utils_base/ListBody.hpp"

#include "../llanylib/utils_base/ArrayBase.hpp"
#include "../llanylib/utils_base/hash/CityHash.hpp"
#include "../llanylib/utils_base/hash/LlanyHash.hpp"

using namespace llcpp;
using namespace llcpp::meta::utils::hash;

int main() {

	//::llcpp::meta::utils::IteratorCommon<int, ::llcpp::meta::utils::IteratorCommonMode::Zeroize> z;
	//int v = 10;
	//z.foreachOperation(v);
	//fprintf(stderr, "%i\n", v);

	constexpr auto value1 = CityHash<CityHashFunctions>().cityHash64("Hola", 4);
	constexpr auto value2 = LlanyHash().llanyHash64_v1("Hola", 4);
	constexpr auto value3 = LlanyHash().llanyHash64_v2("Hola", 4);
	constexpr auto value4 = LlanyHash().llanyHash64_v3("Hola", 4);
	constexpr auto value5 = CityHash<CityHashFunctions>().hash(999ul);
	constexpr auto value6 = CityHash<CityHashFunctions>().__hash(999ul);
	fprintf(stderr, "%llu\n", value1);
	fprintf(stderr, "%llu\n", value2);
	fprintf(stderr, "%llu\n", value3);
	fprintf(stderr, "%llu\n", value4);
	fprintf(stderr, "%llu\n", value5);
	fprintf(stderr, "%llu\n", value6);

	//::llcpp::meta::utils::ListBody<::llcpp::meta::utils::Ex> asd;
	return 0;
}
