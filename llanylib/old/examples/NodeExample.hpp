//////////////////////////////////////////////
//	NodeExample.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#include "../Node.hpp"
#include "../Container.hpp"

#if !defined(LLANYLIB_EXAMPLES_NODEEXAMPLE_HPP_)
#define LLANYLIB_EXAMPLES_NODEEXAMPLE_HPP_

namespace llcpp {
namespace meta {
namespace linked {

///////////////////////////////////////////////// Types and classes /////////////////////////////////////////////////

// Example to FunctionalNode
// This class is the extra function container and at the same time
//	is a container to give each node a internal value
template <class _T, class _U = _T>
class NodeFunctions : public meta::containers::Container<_T> {
	#pragma region Types
	public:
		// Class related
		using _MyType			= NodeFunctions;
		using Container			= meta::containers::Container<_T>;
		using Node				= meta::linked::FunctionalNode<NodeFunctions>;
		using SearchContainer	= meta::containers::Container<_U>;

		// Types
		using T					= _T;
		using U					= _U;

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
		__LL_NODISCARD__ constexpr explicit operator const NodeFunctions*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr explicit operator NodeFunctions*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr ll_bool_t nodeChecker(const Node* a) const noexcept {
			return a->operator*() == this->search.operator*();
		}
		__LL_NODISCARD__ constexpr cmp_t compareNode(const Node* a, const Node* b) const noexcept {
			return a->operator*() == b->operator*() ? 0 : (a->operator*() > b->operator*() ? 1: -1);
		}
		__LL_NODISCARD__ constexpr SearchContainer& to_search() noexcept { return this->search; }

		#pragma endregion

	#pragma endregion
};

template<class T>
using FuncNode = Node<NodeFunctions<T>, llcpp::TRUE>;
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

///////////////////////////////////////////////// Node return value /////////////////////////////////////////////////

constexpr auto aasdasdfas = FuncNode<int>(99);

template<class T>
constexpr T get_value(const T& val) noexcept {
	return *FuncNode<T>(LL_NULLPTR, val, 0);
}
constexpr auto get_value_01 = get_value<int>(99);

///////////////////////////////////////////////// Get value node pos /////////////////////////////////////////////////

template<len_t N, len_t POS>
constexpr int get_pos() noexcept {
	ArrayTypeFuncNode<int, N> nodes;
	linked::fix_node_array<int, N>(nodes);
	return nodes[POS].operator*();
}

constexpr int get_pos_00 = get_pos<7, 0>();
constexpr int get_pos_01 = get_pos<7, 1>();
constexpr int get_pos_02 = get_pos<7, 2>();
constexpr int get_pos_03 = get_pos<7, 3>();
constexpr int get_pos_04 = get_pos<7, 4>();
constexpr int get_pos_05 = get_pos<7, 5>();
constexpr int get_pos_06 = get_pos<7, 6>();

///////////////////////////////////////////////// Get value node pos2 /////////////////////////////////////////////////

template<len_t N>
constexpr int get_pos_loop(const len_t pos) noexcept {
	ArrayTypeFuncNode<int, N> nodes;
	linked::fix_node_array<int, N>(nodes);
	return nodes[0].get(pos)->operator*();
}

constexpr int get_pos_loop_00 = get_pos_loop<7>(0);
constexpr int get_pos_loop_01 = get_pos_loop<7>(1);
constexpr int get_pos_loop_02 = get_pos_loop<7>(2);
constexpr int get_pos_loop_03 = get_pos_loop<7>(3);
constexpr int get_pos_loop_04 = get_pos_loop<7>(4);
constexpr int get_pos_loop_05 = get_pos_loop<7>(5);
constexpr int get_pos_loop_06 = get_pos_loop<7>(6);
constexpr int get_pos_loop_07 = get_pos_loop<7>(7);
constexpr int get_pos_loop_08 = get_pos_loop<7>(8);
constexpr int get_pos_loop_99 = get_pos_loop<7>(99);

///////////////////////////////////////////////// Find node /////////////////////////////////////////////////

template<len_t N>
constexpr int find_element(int find) noexcept {
	ArrayTypeFuncNode<int, N> nodes;
	linked::fix_node_array<int, N>(nodes);

	nodes[0].to_search() = find;
	auto result = nodes[0].find_s(&nodes[0]);
	return result ? **result : -1;
}

constexpr int find_element_00 = find_element<10>(0);
constexpr int find_element_01 = find_element<10>(1);
constexpr int find_element_02 = find_element<10>(2);
constexpr int find_element_03 = find_element<10>(3);
constexpr int find_element_04 = find_element<10>(4);

///////////////////////////////////////////////// Sort /////////////////////////////////////////////////

template<len_t N, len_t POS>
constexpr int merge_sort() noexcept {
	ArrayTypeFuncNode<int, N> nodes;
	meta::linked::fix_node_array<int, N>(nodes);
	int val = 59;
	for (auto& i : nodes) {
		i = val;
		val = (val + ((val > 0) ? 2 : -2)) * -1;
	}
	auto* end = &nodes[N - 1];
	auto* n = nodes[0].mergeSort_s(end);
	end = n->getLast(LL_NULLPTR);
	end->set(n);
	return (n) ? n->get(POS)->operator*() : 0;
}

constexpr int merge_sort_00 = merge_sort<10, 0>();
constexpr int merge_sort_01 = merge_sort<10, 1>();
constexpr int merge_sort_02 = merge_sort<10, 2>();
constexpr int merge_sort_03 = merge_sort<10, 3>();
constexpr int merge_sort_04 = merge_sort<10, 4>();
constexpr int merge_sort_05 = merge_sort<10, 5>();
constexpr int merge_sort_06 = merge_sort<10, 6>();
constexpr int merge_sort_07 = merge_sort<10, 7>();
constexpr int merge_sort_08 = merge_sort<10, 8>();
constexpr int merge_sort_09 = merge_sort<10, 9>();
constexpr int merge_sort_10 = merge_sort<10, 10>();

///////////////////////////////////////////////// Sort2 /////////////////////////////////////////////////

template<len_t N>
constexpr std::pair<int, int> merge_sort2() noexcept {
	ArrayTypeFuncNode<int, N> nodes;
	linked::fix_node_array<int, N>(nodes);
	int val = 59;
	for (auto& i : nodes) {
		i = val;
		val = (val + ((val > 0) ? 2 : -2)) * -1;
	}
	nodes[N - 1].set(LL_NULLPTR);

	FuncNode<int>::NodePack n = nodes[0].getPrevMiddle_s(LL_NULLPTR);
	return { **n.first, **n.second };
}

constexpr auto merge_sort_00 = merge_sort2<10>();

} // namespace linked
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_EXAMPLES_NODEEXAMPLE_HPP_
