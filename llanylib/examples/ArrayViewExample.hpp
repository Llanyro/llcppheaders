//////////////////////////////////////////////
//	ArrayViewExample.hpp					//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 5.0							//
//////////////////////////////////////////////

#ifndef LLANYLIB_EXAMPLES_ARRAYVIEWEXAMPLE_HPP_
#define LLANYLIB_EXAMPLES_ARRAYVIEWEXAMPLE_HPP_

#include "../Array.hpp"
#include "../DoubleNode.hpp"

#include "algorithmExample.hpp"

namespace llcpp {

///////////////////////////////////////////////// Data /////////////////////////////////////////////////

constexpr const int numbers_01[] = { 10, 9, 6 };
constexpr const int numbers_02[] = { 10, 9, 6 };
constexpr const int numbers_03[] = { 10, 5 };
constexpr const int numbers_04[] = { 10, 9, 6, 0 };

///////////////////////////////////////////////// ArrayView Storage /////////////////////////////////////////////////

constexpr auto arrayview_01 = ArrayView(numbers_01);
constexpr auto arrayview_02 = ArrayView(numbers_02);
constexpr auto arrayview_03 = ArrayView(numbers_03);
constexpr auto arrayview_04 = ArrayView(numbers_04);
constexpr auto arrayview_05 = ArrayView(algorithm::str1);
constexpr auto arrayview_06 = ArrayView(algorithm::str2);

constexpr ArrayView HOLA_WORLD = algorithm::str4;

///////////////////////////////////////////////// ArrayView Copy /////////////////////////////////////////////////

constexpr auto arrayview_07 = ArrayView("Hola mundo");
constexpr auto arrayview_08 = ArrayView(HOLA_WORLD);
constexpr auto arrayview_09 = ArrayView(algorithm::str4);

///////////////////////////////////////////////// ArrayView access /////////////////////////////////////////////////

constexpr const ll_char_t stringview_char_1 = arrayview_08[2];
constexpr const ll_char_t stringview_char_2 = *arrayview_07.get(9);

static_assert(stringview_char_1 == 'l', "Error changed value");
static_assert(stringview_char_2 == 'o', "Error changed value");

///////////////////////////////////////////////// ArrayView algorithm /////////////////////////////////////////////////

constexpr len_t find_pos_01 = arrayview_05.find_pos('*');
constexpr len_t find_pos_02 = arrayview_06.find_pos('?');

constexpr auto find_01 = arrayview_05.find('*');
constexpr auto find_02 = arrayview_06.find('?');

constexpr ll_bool_t equals_01 = arrayview_07.operator==(arrayview_08);
constexpr ll_bool_t equals_02 = arrayview_07.operator==(arrayview_07);

constexpr ll_bool_t equals_03 = llcpp::algorithm::equals(numbers_01, numbers_02);
constexpr ll_bool_t equals_04 = llcpp::algorithm::equals({ 10 }, numbers_02);

constexpr ll_bool_t equals_05 = arrayview_02.operator==(arrayview_01);
constexpr ll_bool_t equals_06 = arrayview_03.operator==(arrayview_01);
constexpr ll_bool_t equals_07 = arrayview_04.operator==(arrayview_01);
constexpr ll_bool_t equals_08 = arrayview_02.operator==(arrayview_01);

constexpr ll_bool_t equals_09 = arrayview_03.operator==(numbers_01);
constexpr ll_bool_t equals_10 = arrayview_03.operator==(numbers_02);
constexpr ll_bool_t equals_11 = arrayview_03.operator==(numbers_04);

constexpr ll_bool_t equals_12 = arrayview_01.operator==(numbers_01);
constexpr ll_bool_t equals_13 = arrayview_01.operator==(numbers_02);
constexpr ll_bool_t equals_14 = arrayview_01.operator==(numbers_03);
constexpr ll_bool_t equals_15 = arrayview_01.operator==(numbers_04);

constexpr ll_bool_t equals_16 = llcpp::algorithm::equals(numbers_01, numbers_03);
constexpr ll_bool_t equals_17 = llcpp::algorithm::equals(numbers_02, numbers_03);
constexpr ll_bool_t equals_18 = llcpp::algorithm::equals(numbers_01, numbers_04);
constexpr ll_bool_t equals_19 = llcpp::algorithm::equals(numbers_02, numbers_04);
constexpr ll_bool_t equals_20 = llcpp::algorithm::equals(numbers_03, numbers_04);

static_assert(find_pos_01 == 13, "Error changed value");
static_assert(find_pos_02 == 13, "Error changed value");

static_assert(*find_01 == '*', "Error changed value");
static_assert(*find_02 == '?', "Error changed value");

static_assert(equals_01 == LL_FALSE, "Error changed value");
static_assert(equals_02 ==  LL_TRUE, "Error changed value");
static_assert(equals_03 ==  LL_TRUE, "Error changed value");
static_assert(equals_04 == LL_FALSE, "Error changed value");
static_assert(equals_05 ==  LL_TRUE, "Error changed value");
static_assert(equals_06 == LL_FALSE, "Error changed value");
static_assert(equals_07 == LL_FALSE, "Error changed value");
static_assert(equals_08 ==  LL_TRUE, "Error changed value");
static_assert(equals_09 == LL_FALSE, "Error changed value");
static_assert(equals_10 == LL_FALSE, "Error changed value");
static_assert(equals_11 == LL_FALSE, "Error changed value");
static_assert(equals_12 ==  LL_TRUE, "Error changed value");
static_assert(equals_13 ==  LL_TRUE, "Error changed value");
static_assert(equals_14 == LL_FALSE, "Error changed value");
static_assert(equals_15 == LL_FALSE, "Error changed value");
static_assert(equals_16 == LL_FALSE, "Error changed value");
static_assert(equals_17 == LL_FALSE, "Error changed value");
static_assert(equals_18 == LL_FALSE, "Error changed value");
static_assert(equals_19 == LL_FALSE, "Error changed value");
static_assert(equals_20 == LL_FALSE, "Error changed value");

///////////////////////////////////////////////// Array reverse /////////////////////////////////////////////////

constexpr len_t __array_reverse_example__(int v) {
	len_t block[5]{};
	Array arr = block;
	for (len_t i{}; i < arr.len(); ++i) arr[i] = i;
	arr.reverse();
	return arr[v];
}

constexpr len_t array_reverse_00 = __array_reverse_example__(0);
constexpr len_t array_reverse_01 = __array_reverse_example__(1);
constexpr len_t array_reverse_02 = __array_reverse_example__(2);
constexpr len_t array_reverse_03 = __array_reverse_example__(3);
constexpr len_t array_reverse_04 = __array_reverse_example__(4);

static_assert(array_reverse_00 == 4, "Error changed value");
static_assert(array_reverse_01 == 3, "Error changed value");
static_assert(array_reverse_02 == 2, "Error changed value");
static_assert(array_reverse_03 == 1, "Error changed value");
static_assert(array_reverse_04 == 0, "Error changed value");

///////////////////////////////////////////////// Array fill /////////////////////////////////////////////////

constexpr len_t __array_fill_example__(int v) {
	len_t block[5]{};
	Array arr = block;
	arr.fill(999, 1, 4);
	return arr[v];
}

constexpr len_t array_fill_00 = __array_fill_example__(0);
constexpr len_t array_fill_01 = __array_fill_example__(1);
constexpr len_t array_fill_02 = __array_fill_example__(2);
constexpr len_t array_fill_03 = __array_fill_example__(3);
constexpr len_t array_fill_04 = __array_fill_example__(4);

static_assert(array_fill_00 == 000, "Error changed value");
static_assert(array_fill_01 == 999, "Error changed value");
static_assert(array_fill_02 == 999, "Error changed value");
static_assert(array_fill_03 == 999, "Error changed value");
static_assert(array_fill_04 == 000, "Error changed value");

///////////////////////////////////////////////// Array shift left /////////////////////////////////////////////////

constexpr len_t __array_shift_left_example__(int v) {
	len_t block[5]{};
	Array arr = block;
	for (len_t i{}; i < arr.len(); ++i) arr[i] = i;
	arr.shiftLeft(2, 999);
	return arr[v];
}

constexpr len_t array_shift_left_00 = __array_shift_left_example__(0);
constexpr len_t array_shift_left_01 = __array_shift_left_example__(1);
constexpr len_t array_shift_left_02 = __array_shift_left_example__(2);
constexpr len_t array_shift_left_03 = __array_shift_left_example__(3);
constexpr len_t array_shift_left_04 = __array_shift_left_example__(4);

static_assert(array_shift_left_00 == 999, "Error changed value");
static_assert(array_shift_left_01 == 999, "Error changed value");
static_assert(array_shift_left_02 == 000, "Error changed value");
static_assert(array_shift_left_03 == 001, "Error changed value");
static_assert(array_shift_left_04 == 002, "Error changed value");

///////////////////////////////////////////////// Array shift right /////////////////////////////////////////////////

constexpr len_t __array_shift_right_example__(int v) {
	len_t block[5]{};
	Array arr = block;
	for (len_t i{}; i < arr.len(); ++i) arr[i] = i;
	arr.shifRight(2, 999);
	return arr[v];
}

constexpr len_t array_shift_right_0 = __array_shift_right_example__(0);
constexpr len_t array_shift_right_1 = __array_shift_right_example__(1);
constexpr len_t array_shift_right_2 = __array_shift_right_example__(2);
constexpr len_t array_shift_right_3 = __array_shift_right_example__(3);
constexpr len_t array_shift_right_4 = __array_shift_right_example__(4);

static_assert(array_shift_right_0 == 002, "Error changed value");
static_assert(array_shift_right_1 == 003, "Error changed value");
static_assert(array_shift_right_2 == 004, "Error changed value");
static_assert(array_shift_right_3 == 999, "Error changed value");
static_assert(array_shift_right_4 == 999, "Error changed value");

///////////////////////////////////////////////// Array test nodes /////////////////////////////////////////////////

constexpr len_t ARR_TEST_SIZE = 10;
using ArrayType_1 = Array<len_t, ARR_TEST_SIZE>;

template<class T = ArrayType_1>
struct NodeTest1 {
	T* data;
	NodeTest1* first;
	NodeTest1* next;
	NodeTest1* prev;
};

constexpr len_t __array_test_nodes_example__(
	const len_t number_to_generate,
	const len_t number_back,
	len_t counter = 0ull,
	NodeTest1<>* prev = LL_NULLPTR)
{
	//if (number_to_generate * ARR_TEST_SIZE < number_back) return algorithm::npos;

	// Create memory
	len_t block[ARR_TEST_SIZE]{};

	// Create an array container for memory
	ArrayType_1 arr = block;
	for (len_t i{}; i < arr.len(); ++i) arr[i] = i + counter;

	// Node of array container
	NodeTest1<> n{};
	n.data = &arr;
	if (prev) {
		n.prev = prev;
		n.first = prev->first;
		n.next = LL_NULLPTR;
		prev->next = &n;
	}
	else {
		n.prev = LL_NULLPTR;
		n.first = &n;
		n.next = LL_NULLPTR;
	}

	if (arr.size() + counter < number_to_generate)
		return __array_test_nodes_example__(number_to_generate, number_back, counter + arr.size(), &n);
	else {
		counter += arr.size();
		len_t position = number_back % arr.size();
		len_t position_vec = number_back / arr.size();

		NodeTest1<>* pointer = n.first;
		while (position_vec > 0) {
			--position_vec;
			pointer = pointer->next;
		}

		//return position;
		//return position_vec;
		return pointer->data->operator[](position);
	}
}

constexpr len_t array_test_nodes_00 = __array_test_nodes_example__(999, 0);
constexpr len_t array_test_nodes_01 = __array_test_nodes_example__(999, 1);
constexpr len_t array_test_nodes_02 = __array_test_nodes_example__(999, 2);
constexpr len_t array_test_nodes_03 = __array_test_nodes_example__(999, 3);

static_assert(array_test_nodes_00 == 000, "Error changed value");
static_assert(array_test_nodes_01 == 001, "Error changed value");
static_assert(array_test_nodes_02 == 002, "Error changed value");
static_assert(array_test_nodes_03 == 003, "Error changed value");

///////////////////////////////////////////////// Array test list 2 /////////////////////////////////////////////////

constexpr len_t ARR_TEST_SIZE_3 = 10;
using ArrayType_3 = Array<len_t, ARR_TEST_SIZE_3>;
using NodeTest3 = linked::DoubleNode<ArrayType_3*>;

constexpr len_t __array_test_nodes3_example__(int v, int v2) {
	// Create memory
	len_t block[ARR_TEST_SIZE_3]{};
	// Create an array container for memory
	ArrayType_3 arr = block; for (len_t i{}; i < arr.len(); ++i) arr[i] = i;

	// Create memory
	len_t block2[ARR_TEST_SIZE_3]{};
	// Create an array container for memory
	ArrayType_3 arr2 = block2; for (len_t i{}; i < arr2.len(); ++i) arr2[i] = i + ARR_TEST_SIZE_3;

	// Create memory
	len_t block3[ARR_TEST_SIZE_3]{};
	// Create an array container for memory
	ArrayType_3 arr3 = block3; for (len_t i{}; i < arr3.len(); ++i) arr3[i] = i + (ARR_TEST_SIZE_3 * 2);

	NodeTest3 n1, n2, n3;
	n1.__autopoint();
	n2.__autopoint();
	n3.__autopoint();

	n1.linkRight(&n2);
	n1.linkRight(&n3);
	n1.setData(&arr);
	n2.setData(&arr2);
	n3.setData(&arr3);

	NodeTest3* node = n1.getNext(v2);
	ArrayType_3* arr_ptr_1 = node->getData();
	return arr_ptr_1->operator[](v);
}

constexpr len_t array_test_nodes3_00 = __array_test_nodes3_example__(1, 0);
constexpr len_t array_test_nodes3_01 = __array_test_nodes3_example__(1, 1);
constexpr len_t array_test_nodes3_02 = __array_test_nodes3_example__(2, 2);
constexpr len_t array_test_nodes3_03 = __array_test_nodes3_example__(9, 3);

///////////////////////////////////////////////// Array test list 4 /////////////////////////////////////////////////

constexpr len_t ARR_TEST_SIZE_5 = 10;
using ArrayType_5 = Array<len_t, ARR_TEST_SIZE_5>;
using NodeTest5 = linked::DoubleNode<ArrayType_5*>;

//template<class T, len_t N>
class ArrayChain {
	protected:
		NodeTest5* root;	// Nodes
		len_t len;			// Number of nodes
		len_t moc;
	public:
		constexpr ArrayChain() : root(LL_NULLPTR), len(0ull), moc(0ull) {}
		constexpr ~ArrayChain() {}

		constexpr void push_back(NodeTest5* n) {
			n->__autopoint();
			if (!this->root) this->root = n;
			else			 this->root->linkLeft(n);
			++this->len;
		}
		constexpr void push_front(NodeTest5* n) {
			this->push_back(n);
			this->root = this->root->getPrev();
			++this->len;
		}

		constexpr len_t& operator[](const len_t pos) {
			len_t arr_pos = pos % ARR_TEST_SIZE_5;
			len_t node_pos = pos / ARR_TEST_SIZE_5;
			if (node_pos >= this->len) return moc;
			return this->root->getNext(node_pos)->getData()->operator[](arr_pos);
		}
};

//using Chain = ArrayChain<len_t, ARR_TEST_SIZE_5>;

//constexpr len_t __array_test_nodes5_impl_example__(
//	const len_t number_to_generate,
//	const len_t number_back,
//	ArrayChain* chain,
//	len_t counter = 0ull
//)
//{
//	// Create memory
//	len_t block[ARR_TEST_SIZE_5]{};
//
//	// Create an array container for memory
//	ArrayType_5 arr = block;
//	for (len_t i{}; i < arr.len(); ++i) arr[i] = i + counter;
//
//	// Node of array container
//	NodeTest5 n;
//	n.setData(&arr);
//	chain->push_back(&n);
//
//	if (arr.size() + counter < number_to_generate)
//		return __array_test_nodes5_impl_example__(number_to_generate, number_back, chain, counter + arr.size());
//	else {
//		//counter += arr.size();
//		len_t s = chain->operator[](number_back);
//		return s;
//	}
//	//return 0;
//}

constexpr len_t __array_test_nodes5_impl_example__(
	const len_t number_to_generate,
	const len_t number_back,
	ArrayChain& chain
) {
	// Create memory
	len_t block[ARR_TEST_SIZE_5]{};
	// Create an array container for memory
	ArrayType_5 arr = block; for (len_t i{}; i < arr.len(); ++i) arr[i] = i;

	// Create memory
	len_t block2[ARR_TEST_SIZE_5]{};
	// Create an array container for memory
	ArrayType_5 arr2 = block2; for (len_t i{}; i < arr2.len(); ++i) arr2[i] = i + ARR_TEST_SIZE_5;

	// Create memory
	len_t block3[ARR_TEST_SIZE_5]{};
	// Create an array container for memory
	ArrayType_5 arr3 = block3; for (len_t i{}; i < arr3.len(); ++i) arr3[i] = i + (ARR_TEST_SIZE_5 * 2);

	NodeTest5 n1, n2, n3;
	chain.push_back(&n1);
	chain.push_back(&n2);
	chain.push_back(&n3);

	n1.setData(&arr);
	n2.setData(&arr2);
	n3.setData(&arr3);

	return chain.operator[](21);
}

constexpr len_t __array_test_nodes5_example__(const len_t number_to_generate, const len_t number_back) {
	ArrayChain c;
	return __array_test_nodes5_impl_example__(number_to_generate, number_back, c);
}

constexpr len_t array_test_nodes5_1 = __array_test_nodes5_example__(11, 10);
constexpr len_t array_test_nodes5_2 = __array_test_nodes5_example__(110, 27);

} // namespace llcpp

#endif // LLANYLIB_EXAMPLES_ARRAYVIEWEXAMPLE_HPP_
