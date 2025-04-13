
#include "../llanylib/types.hpp"

//#include "../llanylib/Container.hpp"
#include "../llanylib/algorithm.hpp"
//#include "../llanylib/Node.hpp"
//#include "../llanylib/mem.hpp"
//#include "../llanylib/Typeid.hpp"

#include <iostream>
#include <array>

#pragma region Inheritance
class Base {
	public:
		int value;
		constexpr Base() noexcept : value(99) {}
		constexpr Base(int value) noexcept : value(value) {}
		constexpr ~Base() noexcept {}

		constexpr Base(const Base& other) noexcept : value(other.value) {}
		constexpr Base& operator=(const Base& other) noexcept {
			this->value = other.value;
			return *this;
		}
		constexpr Base(Base&& other) noexcept : value(other.value) { other.value = 0; }
		constexpr Base& operator=(Base&& other) noexcept {
			this->value = other.value;
			other.value = 0;
			return *this;
		}

		__LL_NODISCARD__ constexpr operator int() const noexcept { return this->value; }
};

struct ARR {
	private:
		Base data[5];

	public:
		__LL_NODISCARD__ constexpr Base* begin() noexcept { return this->data; }
		__LL_NODISCARD__ constexpr Base* end() noexcept { return this->data + 5; }

		__LL_NODISCARD__ constexpr const Base* begin() const noexcept { return this->data; }
		__LL_NODISCARD__ constexpr const Base* end() const noexcept { return this->data + 5; }
};

class H1 : public Base {
	public:
		H1() noexcept : Base() {}
		H1(int value) noexcept : Base(value) {}
		~H1() noexcept {}
};

class H2 : public Base {
	public:
		H2() noexcept : Base() {}
		H2(int value) noexcept : Base(value) {}
		~H2() noexcept {}
};

class D1 : public H1, public H2 {
	public:
		D1() noexcept : H1(), H2() {}
		D1(int value1, int value2) noexcept : H1(value1), H2(value2) {}
		~D1() noexcept {}

		__LL_NODISCARD__ constexpr int hash() noexcept { return 0; }
};

class IntFunctions {
	public:
		constexpr void clear(int*& asdf) noexcept { *asdf = 0; }
		__LL_NODISCARD__ constexpr int hash() const noexcept { return 0; }
		__LL_NODISCARD__ constexpr int hash(int*& v) noexcept { return *v; }
		__LL_NODISCARD__ constexpr int hash(const int*& v) const noexcept { return *v; }
		__LL_NODISCARD__ constexpr void predestruction(int*& v) noexcept { delete v; }
};
#pragma endregion
#pragma region Nodes
/*template <class _T, class _U = _T>
class NodeFunctions : public llcpp::meta::containers::Container<_T> {
	#pragma region Types
	public:
		using T					= _T;
		using U					= _U;
		using _MyType			= NodeFunctions;
		using Container			= llcpp::meta::containers::Container<T>;
		using Node				= llcpp::meta::linked::FunctionalNode<NodeFunctions>;
		using SearchContainer	= llcpp::meta::containers::Container<U>;

	#pragma endregion
	#pragma region Attributes
	private:
		SearchContainer search;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr NodeFunctions() noexcept : Container(), search() {}

		constexpr NodeFunctions(const T& object) noexcept
			: Container(std::forward<const T&>(object)), search() {}
		constexpr NodeFunctions(T&& object) noexcept
			: Container(std::forward<T&&>(object)), search() {}

		constexpr NodeFunctions(const T& object, const U& to_search) noexcept
			: Container(std::forward<const T&>(object))
			, search(std::forward<const U&>(to_search)) {}
		constexpr NodeFunctions(T&& object, U&& to_search) noexcept
			: Container(std::forward<T&&>(object))
			, search(std::forward<U&&>(to_search)) {}

		constexpr ~NodeFunctions() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr NodeFunctions(const NodeFunctions& other) noexcept
			: Container(std::forward<const Container&>(other))
			, search(std::forward<const SearchContainer&>(other.search)) {}
		constexpr NodeFunctions& operator=(const NodeFunctions& other) noexcept {
			Container::operator=(std::forward<const Container&>(other));
			this->search = ::std::forward<const SearchContainer&>(other.search);
			return *this;
		}
		constexpr NodeFunctions(NodeFunctions&& other) noexcept
			: Container(std::forward<Container&&>(other))
			, search(std::forward<SearchContainer&&>(other.search)) {}
		constexpr NodeFunctions& operator=(NodeFunctions&& other) noexcept {
			Container::operator=(std::forward<Container&&>(other));
			this->search = ::std::forward<SearchContainer&&>(other.search);
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const NodeFunctions*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator NodeFunctions*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr ll_bool_t nodeChecker(const Node* a) const noexcept {
			return a->operator*() == this->search.operator*();
			//return llcpp::LL_FALSE;
		}
		__LL_NODISCARD__ constexpr cmp_t compareNode(const Node* a, const Node* b) const noexcept {
			return (**a == **b) ? 0 : ((**a > **b) ? 1 : -1);
		}
		__LL_NODISCARD__ constexpr SearchContainer& to_search() noexcept { return this->search; }
		__LL_NODISCARD__ constexpr void die() noexcept {}

		#pragma endregion

	#pragma endregion
};

template<class T>
using FuncNode = llcpp::meta::linked::Node<NodeFunctions<T>, ::llcpp::LL_TRUE>;
template<class T, len_t N>
using ArrayTypeFuncNode = ::std::array<FuncNode<T>, N>;

template<class T, len_t N>
constexpr void fix_node_array(ArrayTypeFuncNode<T, N>& nodes) {
	for (len_t i{}; i < N - 1; ++i) {
		nodes[i].set(nodes[i + 1]);
		nodes[i] = i;
	}
	nodes[N - 1].set(&nodes[0]);
	nodes[N - 1] = N - 1;
}

template<len_t N, len_t POS>
len_t merge_sort() noexcept {
	using arr = ArrayTypeFuncNode<len_t, N>;
	arr nodes;
	//arr nodes = llcpp::meta::algorithm::make_constructed_array<arr, int, N>(99);
	fix_node_array<len_t, N>(nodes);
	len_t val = 59;
	for (auto& i : nodes) {
		i = val;
		val = (val + ((val > 0) ? 2 : -2)) * -1;
	}
	auto* end = &nodes[N - 1];
	auto* n = nodes[0].mergeSort_s(end);
	end = n->getLast(LL_NULLPTR);
	end->set(n);
	return (n) ? n->get(POS)->operator*() : 0;
}*/

//constexpr ll_bool_t asdasd = llcpp::meta::traits::has_type_operator_v<D1, int, int(D1::*)() const noexcept>;
//constexpr ll_bool_t asdasd = llcpp::meta::traits::has_simple_type_const_operator_v<H2, int>;
//constexpr ll_bool_t asdasd = llcpp::meta::traits::has_simple_type_const_operator_v<int, int>;

void main_nodes() {
	D1 a(80, 70);
	//llcpp::meta::containers::Container<int*, IntFunctions> cont(new int(10));
	//using t = decltype(cont)::reference;
	//cont.clear();
	
	//std::cout << "ASDF: " << llcpp::meta::linked::asdf() << "\n";
	
	//std::cout << "Base1: " << llcpp::meta::traits::common::has_hash_function_v<D1, int(D1::*)() noexcept> << "\n";
	//std::cout << "Base2: " << llcpp::meta::traits::common::has_hash_function_v<H2, int(H2::*)() noexcept> << "\n";
	//
	//std::cout << "Base1: " << llcpp::meta::traits::has_simple_type_operator_v<D1, int> << "\n";
	//std::cout << "Base2: " << llcpp::meta::traits::has_simple_type_operator_v<H2, int> << "\n";
	//std::cout << "Base3: " << llcpp::meta::traits::has_simple_type_operator_v<int, int> << "\n";
	
	//std::cout << "Base: " << sizeof(Base) << "\n";
	//std::cout << "H1: " << sizeof(H1) << "\n";
	//std::cout << "H2: " << sizeof(H2) << "\n";
	//std::cout << "D1: " << sizeof(D1) << "\n";
	//std::cout << "A: " << sizeof(a) << "\n";
	//std::cout << "Value1: " << a.H1::value << "\tValue2: " << a.H2::value << "\n";
	//std::cout << merge_sort<10, 0>() << std::endl;
}

#pragma endregion

template<class T, T val>
ll_bool_t get_val() noexcept {
	return val;
}

struct _ui32 {
	ui32 l;
	ui32 h;
};

union example {
	_ui32 div;
	ui64 real;
};

//__LL_NODISCARD__ static constexpr example calculate_impl(ui32& v) noexcept {
//	example e{};
//	e.real = llcpp::meta::hash::algorithm::__algorithm__::kMul64;
//	//v = e.div.h;
//	return e;
//}
//__LL_NODISCARD__ static constexpr example calculate() noexcept {
//	ui32 v = 0;
//	return calculate_impl(v);
//}

int main() {
	//constexpr example e = calculate();

	//std::cout << e.real << std::endl;
	//std::cout << e.div.l << std::endl;
	//std::cout << e.div.h << std::endl;

	//auto asdf = 1 <=> 9;
	//
	//llcpp::ll_bool_t boolean1 = true;
	//llcpp::ll_bool_t boolean2 = false;
	//llcpp::ll_bool_t boolean3 = llcpp::ll_bool_t::enum_bool::FALSE;
	//
	//std::cout << "boolean1: " << boolean1.operator bool() << "\n";
	//std::cout << "boolean2: " << boolean2.operator bool() << "\n";
	//std::cout << "boolean3: " << boolean3.operator bool() << "\n";
	//std::cout << "boolean0: " << get_val<decltype(llcpp::LL_FALSE), llcpp::LL_FALSE>() << "\n";

	auto print_arr = [](const auto& arr) {
		for(auto& i : arr)
			std::cout << i << ", ";
		std::cout << "\n\n";
	};

	auto a = llcpp::meta::algorithm::make_constructed_array<std::array<Base, 5>, Base, 5>(10);
	std::array<Base, 5> asdf{};
	print_arr(a);
	print_arr(asdf);
	asdf = ::std::forward<std::array<Base, 5>&&>(a);
	print_arr(a);
	print_arr(asdf);

	//auto a = llcpp::meta::algorithm::make_constructed_array<ARR, Base, 5>(10);
	//ARR asdf{};
	//print_arr(a);
	//print_arr(asdf);
	//asdf = ::std::forward<ARR&&>(a);
	//print_arr(a);
	//print_arr(asdf);

	//llcpp::meta::containers::Container<int[5]> cont(10);
	//main_nodes();

	//llcpp::meta::StrTypeid id(llcpp::meta::make_ArrayPair("Patata"), 57);
	//auto& name = id.getName();
	//
	//std::cout << llcpp::meta::mem::test_prep<int>(2) << std::endl;
	//printf("Size: %llu\n", id.getName().lenght());
	//std::cout << std::string_view(name.begin(), name.end()) << std::endl;
	////printf("%*.s\n", (ui32)id.getName().lenght(), id.getName().begin());
	//std::cout << id.hash().get() << std::endl;

	return 0;
}