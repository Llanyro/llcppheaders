#include "../definitions.hpp"
#include "../os.hpp"

#include "algorithmExample.hpp"
#include "ArrayViewExample.hpp"
#include "bitsExample.hpp"
#include "mathExample.hpp"
//#include "RandomExample.hpp"
#include "StringViewExample.hpp"
#include "traits_test_class.hpp"
#include "traitsExample.hpp"

#include "../expresions/ascii.hpp"
#include "../expresions/color.hpp"
//#include "../expresions/math.hpp"
#include "../expresions/string.hpp"

#include "../cityhash.hpp"
#include "../hash.hpp"
#include "../Hash64.hpp"
#include "../hashtools.hpp"

#include "../BasicTypeWrapper.hpp"
#include "../ostypes.hpp"
#include "../traits.hpp"
#include "../types.hpp"

//#include "../DoubleNode.hpp"
//#include "../LinkedList.hpp"
//#include "../LoopList.hpp"
#include "../Node.hpp"

#include "../algorithm.hpp"
#include "../StaticArray.hpp"
#include "../ArrayView.hpp"
#include "../Buffer.hpp"
#include "../Countable.hpp"
//#include "../string.hpp"

//#include "../RAIIBase.hpp"
//#include "../RAIIWrapper.hpp"

//#include "../ArgumentsHasher.hpp"
#include "../ArrayPair.hpp"
#include "../bits.hpp"
#include "../common.hpp"
#include "../dynamiclibrarylinking.hpp"
#include "../math.hpp"
//#include "../Random.hpp"
#include "../reflection.hpp"
#include "../Singleton.hpp"
#include "../Typeid.hpp"

#include <iostream>
#include <array>

template<class T>
void printthis(const llcpp::meta::ArrayPair<T>& arr) {
	std::cout << '[';
	for (const auto& i : arr) std::cout << i << ' ';
	std::cout << "]\n";
}
template<class T, len_t N, T NULL_>
void printthis(const llcpp::meta::Buffer<T, N, NULL_>& arr) {
	std::cout << '[';
	for (const auto& i : arr) std::cout << i << ' ';
	std::cout << "]\n";
}
template<class T, len_t N>
void printthis(const T(&arr)[N]) {
	std::cout << '[';
	for (const auto& i : arr) std::cout << i << ' ';
	std::cout << "]\n";
}

ll_string_t getBool(const ll_bool_t value) {
	return value ? llcpp::meta::string::TRUE_STR.begin() : llcpp::meta::string::FALSE_STR.begin();
}

int main() {
	using Buff = llcpp::meta::Buffer<len_t, 10ul, llcpp::ZERO_UI64>;
	Buff array0;
	//const len_t block_cmp[] = { 2ull, 3ull, 4ull, 5ull, 6ull, 7ull, 8ull, 9ull, 1000ull, 1000ull };
	const len_t block_cmp[] = { 1000ull, 1000ull, 0ull, 1ull, 2ull, 3ull, 4ull, 5ull, 6ull, 7ull };
	array0.push_back(1);
	for (len_t i{}; i < array0.len(); ++i) array0()[i] = i;
	
	//array0.fill<len_t>(999ul);
	printthis(array0);
	printthis(block_cmp);
	
	//shiftRight(array0.begin(), array0.len(), 0, 2);
	llcpp::meta::algorithm::data_manipulation_cluster<len_t>::shifRight<len_t>(array0().begin(), array0.len(), 0, 2, 1000ull);
	
	//shiftLeft<len_t, 999>(array0.begin(), array0.len(), 0, 9);
	//array0.shiftLeft(2, 5, 10);
	//llcpp::meta::algorithm::data_manipulation_cluster<len_t>::shiftLeft<len_t>(array0.begin(), array0.len(), 0, 9, 2, 1000ull);
	
	//std::cout << "res: " << getBool(llcpp::meta::algorithm::compare_cluster<len_t, len_t, llcpp::LL_FALSE>::equals(block_cmp, array0())) << "\n";
	std::cout << "res: " << getBool(array0().equals<len_t>(block_cmp)) << "\n";
	
	//for (len_t i{}; i < 999; ++i)
	//	std::cout << "Value: " << i << "\t" << getBool((i * 2) == (i << 1)) << "\n";
	
	printthis(array0);
	printthis(block_cmp);
	return 0;
}
