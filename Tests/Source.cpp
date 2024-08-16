
#include "../llanylib/types.hpp"

//#include "../llanylib/Container.hpp"
//#include "../llanylib/Node.hpp"
#include <iostream>

class Base {
	public:
		int value;
		Base() noexcept : value(99) {}
		Base(int value) noexcept : value(value) {}
		~Base() noexcept {}
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

#pragma region Nodes
/*template <class _T, class _U = _T>
class NodeFunctions : public llcpp::meta::Container<_T> {
	#pragma region Types
	public:
		using T					= _T;
		using U					= _U;
		using _MyType			= NodeFunctions;
		using Container			= llcpp::meta::Container<T>;
		using Node				= llcpp::meta::linked::FunctionalNode<NodeFunctions>;
		using SearchContainer	= llcpp::meta::Container<U>;

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
			this->search = std::forward<const SearchContainer&>(other.search);
			return *this;
		}
		constexpr NodeFunctions(NodeFunctions&& other) noexcept
			: Container(std::forward<Container&&>(other))
			, search(std::forward<SearchContainer&&>(other.search)) {}
		constexpr NodeFunctions& operator=(NodeFunctions&& other) noexcept {
			Container::operator=(std::forward<Container&&>(other));
			this->search = std::forward<SearchContainer&&>(other.search);
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

		#pragma endregion

	#pragma endregion
};

template<class T>
using FuncNode = llcpp::meta::linked::Node<NodeFunctions<T>, llcpp::LL_TRUE>;
template<class T, len_t N>
using ArrayTypeFuncNode = std::array<FuncNode<T>, N>;

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
int merge_sort() noexcept {
	ArrayTypeFuncNode<int, N> nodes;
	fix_node_array<int, N>(nodes);
	int val = 59;
	for (auto& i : nodes) {
		i = val;
		val = (val + ((val > 0) ? 2 : -2)) * -1;
	}
	auto* end = &nodes[N - 1];
	auto* n = nodes[0].mergeSort_s(end);
	end->set(n);
	return (n) ? n->get(POS)->operator*() : 0;
}
void main_nodes() {
	D1 a(80, 70);
	llcpp::meta::Container<int*, IntFunctions> cont(new int(10));
	using t = decltype(cont)::reference;
	//cont.clear();
	
	//std::cout << "ASDF: " << llcpp::meta::linked::asdf() << "\n";
	
	std::cout << "Base1: " << llcpp::meta::traits::common::has_hash_function_v<D1, int(D1::*)() noexcept> << "\n";
	std::cout << "Base2: " << llcpp::meta::traits::common::has_hash_function_v<H2, int(H2::*)() noexcept> << "\n";
	
	std::cout << "Base1: " << llcpp::meta::traits::has_simple_type_operator_v<D1, int> << "\n";
	std::cout << "Base2: " << llcpp::meta::traits::has_simple_type_operator_v<H2, int> << "\n";
	std::cout << "Base3: " << llcpp::meta::traits::has_simple_type_operator_v<int, int> << "\n";
	
	std::cout << "Base: " << sizeof(Base) << "\n";
	std::cout << "H1: " << sizeof(H1) << "\n";
	std::cout << "H2: " << sizeof(H2) << "\n";
	std::cout << "D1: " << sizeof(D1) << "\n";
	std::cout << "A: " << sizeof(a) << "\n";
	std::cout << "Value1: " << a.H1::value << "\tValue2: " << a.H2::value << "\n";
	merge_sort<10, 0>();
}

*/
#pragma endregion

template<class T, T val>
ll_bool_t get_val() noexcept {
	return val;
}

int main() {
	auto asdf = 1 <=> 9;

	llcpp::ll_bool_t boolean1 = true;
	llcpp::ll_bool_t boolean2 = false;
	llcpp::ll_bool_t boolean3 = llcpp::ll_bool_t::enum_bool::FALSE;

	std::cout << "boolean1: " << boolean1.operator bool() << "\n";
	std::cout << "boolean2: " << boolean2.operator bool() << "\n";
	std::cout << "boolean3: " << boolean3.operator bool() << "\n";
	//std::cout << "boolean0: " << get_val<decltype(llcpp::LL_FALSE), llcpp::LL_FALSE>() << "\n";

	return 0;
}