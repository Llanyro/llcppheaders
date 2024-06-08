#include "../definitions.hpp"
#include "../os.hpp"

#include "bitsExample.hpp"
#include "mathExample.hpp"
#include "RandomExample.hpp"
#include "traits_test_class.hpp"
//#include "traitsExample.hpp"

#include "../expresions/ascii.hpp"
#include "../expresions/color.hpp"
#include "../expresions/math.hpp"
#include "../expresions/string.hpp"

#include "../cityhash.hpp"
#include "../llanyhash.hpp"

#include "../hash_algorithm.hpp"
#include "../hash_pack.hpp"
#include "../hash_types.hpp"
#include "../hash_tools.hpp"

#include "../dynamiclibrarylinking.hpp"

#include "../StandardHash.hpp"
#include "../StandardRandom.hpp"
#include "../StandardTypeid.hpp"

#include "../ostypes.hpp"
#include "../traits.hpp"
#include "../types.hpp"

#include "../Node.hpp"

#include "../algorithm.hpp"
#include "../ArrayPair.hpp"
#include "../Countable.hpp"

#include "../bits.hpp"
#include "../common.hpp"
#include "../math.hpp"
#include "../Random.hpp"
#include "../reflection.hpp"
#include "../Singleton.hpp"
#include "../Typeid.hpp"
#include "../utility.hpp"

#include <iostream>
#include <array>
#include <array>
#include <iomanip>
//#include <cstddef>
//#include <string>
//#include <iostream>


using namespace llcpp;
using namespace llcpp::meta;

template<class T>
void printthis(const llcpp::meta::ArrayPair<T>& arr) {
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
	return value ? llcpp::meta::string::TRUE_STR.data() : llcpp::meta::string::FALSE_STR.data();
}

#pragma region Hash
//constexpr hash::Hash64FunctionPack pack(
//	[](ll_string_t str, len_t size) __LL_EXCEPT__ -> hash::OptionalHash64 {
//		len_t buffer{};
//		for (; size > ZERO_UI64; --size, ++str) buffer += *str;
//		return hash::Hash64(buffer);
//	},
//	[](ll_wstring_t str, len_t size) __LL_EXCEPT__-> hash::OptionalHash64 {
//		len_t buffer{};
//		for (; size > ZERO_UI64; --size, ++str) buffer += *str;
//		return hash::Hash64(buffer);
//	},
//	[](const meta::StrPair&) __LL_EXCEPT__-> hash::OptionalHash64 { return hash::INVALID_HASH64; },
//	[](const meta::wStrPair&) __LL_EXCEPT__ -> hash::OptionalHash64 { return hash::INVALID_HASH64; },
//
//	[](const meta::Str&) __LL_EXCEPT__ -> hash::OptionalHash64 { return hash::INVALID_HASH64; },
//	[](const meta::wStr&) __LL_EXCEPT__ -> hash::OptionalHash64 { return hash::INVALID_HASH64; },
//
//	[](const hash::Hash64& h) __LL_EXCEPT__ -> hash::OptionalHash64 { return h; },
//
//	[](const void*, const meta::StrTypeid&) __LL_EXCEPT__ -> hash::OptionalHash64 { return hash::INVALID_HASH64; },
//	[](const void*, const meta::wStrTypeid&) __LL_EXCEPT__ -> hash::OptionalHash64 { return hash::INVALID_HASH64; }
//);

constexpr auto valueget() {
	//hash::HashTool tool(pack);
	//hash::Hash64 hashes[] = { 257ul, 1ull, 2ull, 3ull, 4ull, 5ull, 6ull, 7ull };
	//return tool.hash(hashes).get();
	//return tool.hash_hash(hashes).get();
	//return tool.hash<1>(hashes).get();
	//return tool.hash_hash<1>(hashes).get();
	//return basic_type_hash::hashValue<ui64>(hashes->get(), pack.getHashFunction()).get();
	//return basic_type_hash::hashValue<ui64>(888, pack.getHashFunction()).get();
	//return hash::INVALID_HASH64;
	hash::HashTool<>::HashStatus status[5];
	return hash::STANDARD_HASH_TOOLS.hashArgumentsV1(status, 1, 2, 3, 4);
	//return tool.hashArgumentsV1(status, 1, 2, 3, 4);
}
constexpr auto valueget_2() {
	hash::HashTool<>::HashStatus status[5];
	return hash::FAST_HASH_TOOLS.hashArgumentsV1(status, 1, 2, 3, 4);
}

constexpr auto val = valueget();
static_assert((*val).get() == 9444077356073661613, "Error");

constexpr auto val2 = valueget_2();

#pragma endregion

__LL_NODISCARD__ constexpr len_t valueget2(len_t value) {
	if constexpr (std::is_constant_evaluated())
		return value + 1;
	else return value;
}

constexpr len_t is_eval = valueget2(999);

int main() {
	//const len_t block_cmp[] = { 2ull, 3ull, 4ull, 5ull, 6ull, 7ull, 8ull, 9ull, 1000ull, 1000ull };
	const len_t block_cmp[] = { 1000ull, 1000ull, 0ull, 1ull, 2ull, 3ull, 4ull, 5ull, 6ull, 7ull };
	printthis(block_cmp);
	
	//shiftRight(array0.begin(), array0.len(), 0, 2);
	//llcpp::meta::algorithm::data_manipulation_cluster<len_t>::shifRight<len_t>(array0().begin(), array0.len(), 0, 2, 1000ull);
	
	//shiftLeft<len_t, 999>(array0.begin(), array0.len(), 0, 9);
	//array0.shiftLeft(2, 5, 10);
	//llcpp::meta::algorithm::data_manipulation_cluster<len_t>::shiftLeft<len_t>(array0.begin(), array0.len(), 0, 9, 2, 1000ull);
	
	//std::cout << "res: " << getBool(llcpp::meta::algorithm::compare_cluster<len_t, len_t, llcpp::LL_FALSE>::equals(block_cmp, array0())) << "\n";
	//std::cout << "res: " << getBool(array0().equals<len_t>(block_cmp)) << "\n";
		
	printthis(block_cmp);

	auto val2 = valueget();

	auto rd = llcpp::meta::STANDARD_RANDOM(std::time(NULL));
	ui64 rd_value = rd.rand<ui64>();
	std::cout << "Rd_Value: " << rd_value << "\n";
	std::cout << "Evaluated: " << valueget2(rd_value) << "\n";
	std::cout << "Evaluated: " << (*val2).get() << "\n";

	llcpp::dll::DllHandle lib("C:\\Users\\Fran-Administrador\\Documents\\GitHub\\llanylib\\mal-7532-crypt\\mal-7532-crypt\\x64\\Debug\\TestDLL.dll");
	ll_char_t* handle_char = reinterpret_cast<ll_char_t*>(lib.getHandle());
	std::printf("Lib point: %p\n", handle_char);

	ll_char_t* function = lib.getFunction<ll_char_t*>("get2");
	std::printf("Get2 point: %p\n", function);

	std::cout << "Diff: " << (function - handle_char) << "\n";
	std::cout << "Diff: " << (function - handle_char) - 0x000112C6 << "\n";

	std::printf("Get3 point: %p\n", (handle_char + 0x000112C6));

	using Get = std::optional<int>(*)() __LL_EXCEPT__;
	Get get_function = lib.getFunction<Get>(0x000110F5);
	std::printf("Get point: %p\n", get_function);
	auto get_value = get_function();
	if(get_value.has_value()) std::cout << "Get value: " << *get_value << "\n";
	else std::cout << "Get value: no value\n";

	Get get_function2 = lib.getFunction<Get>("get@@YA?AV?$optional@H@std@@XZ");
	std::printf("Getf2 point: %p\n", get_function);
	//auto get_value = get_function2();
	//if(get_value.has_value()) std::cout << "Get value: " << *get_value << "\n";
	//else std::cout << "Get value: no value\n";

	


	return 0;
}

struct Test {
	std::string str;
	int n;

	Test(std::string str, int n) noexcept : str(std::move(str)), n(n) { }
	Test() noexcept(true) : str(), n() { std::cout << "Inited!\n"; }
};
std::ostream& operator <<(std::ostream& os, const Test& t) {
	return os << '{' << std::quoted(t.str) << ", " << t.n << '}';
}

int main3() {
	//auto print_arr = [](const auto* arr, const len_t size) {
	//	const auto* end = arr + size;
	//	for (; arr < end; ++arr)
	//		std::cout << *arr << ", ";
	//	std::cout << "\n\n";
	//};
	auto print_arr = [](const auto& arr) {
		for(auto& i : arr)
			std::cout << i << ", ";
		std::cout << "\n\n";
	};

	//auto asdf = std::make_index_sequence<10>{};
	//asdf.size();
	//std::initializer_list

	auto a = llcpp::meta::utils::make_constructed_array<std::array<len_t, 10>, len_t, 10>(999);
	len_t* mem = (len_t*)std::malloc(sizeof(len_t) * 10);
	mem = llcpp::meta::utils::make_constructed_new_mem<len_t, 10>(mem, 999);
	//auto c = llcpp::meta::utils::make_filled_StaticArray<len_t, 10, 0ull>(999);
	llcpp::meta::ArrayPair<len_t> b_arr(mem, 10);

	print_arr(a);
	print_arr(b_arr);
	//print_arr(c);
	free(mem);

	//Test* m = (Test*)std::malloc(sizeof(Test) * 5);
	//m = new (m) Test[5]();
	//delete[] m;
	//free(m);

	std::index_sequence idx_seq = std::make_index_sequence<10>();

	//print_arr(make_filled_array<int, 10>(23));
	//print_arr(make_filled_array<Test, 10>("asd", 123));
	return 0;
}
