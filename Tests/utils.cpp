#define __LL_USE_WIDE_CHAR 1
#define __LL_EXCEPTIONS 1

#define __debug_error_exceptions_full(asdf) ::std::printf(asdf)
#define __debug_error_exceptions_empty(asdf) ::std::printf(asdf)

#include <cstdio>

//#include "../llanylib/utils_base/IteratorCommon.hpp"
//#include "../llanylib/utils_base/CityHash.hpp"
#include "../llanylib/utils_base/ListBody.hpp"

using namespace llcpp;



int main() {
	//::llcpp::meta::utils::IteratorCommon<int, ::llcpp::meta::utils::IteratorCommonMode::Zeroize> z;
	//int v = 10;
	//z.foreachOperation(v);
	//fprintf(stderr, "%i\n", v);

	//auto value = ::llcpp::meta::utils::CityHash<::llcpp::meta::utils::CityHashFunctions>().cityHash64("Hola", 4);
	//fprintf(stderr, "%llu\n", value);

	::llcpp::meta::utils::ListBody<::llcpp::meta::utils::Ex> asd;


	return 0;
}
