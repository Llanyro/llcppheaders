/*
 *	ArrayViewExample.hpp
 *
 *	Created on: Sep 27, 2021
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
 */

#ifndef LLANYLIB_EXAMPLES_ARRAYVIEWEXAMPLE_HPP_
#define LLANYLIB_EXAMPLES_ARRAYVIEWEXAMPLE_HPP_

#include "../Array.hpp"
#include "algorithmExample.hpp"
#include "../DoubleNode.hpp"

namespace llcpp {

/************************************* Data *************************************/

constexpr const int numbers_1[3] = { 10, 9, 6 };
constexpr const int numbers_2[3] = { 10, 9, 6 };
constexpr const int numbers_3[3] = { 10, 9, 5 };
constexpr const int numbers_4[4] = { 10, 9, 6, 0 };

/************************************* ArrayView Storage *************************************/

constexpr auto arrayview1 = ArrayView(numbers_1);
constexpr auto arrayview2 = ArrayView(numbers_2);
constexpr auto arrayview3 = ArrayView(numbers_3);
constexpr auto arrayview4 = ArrayView(numbers_4);
constexpr auto arrayview5 = ArrayView(algorithm::str);
constexpr auto arrayview6 = ArrayView(algorithm::str2);

constexpr ArrayView HOLA_WORLD = "Hola world!";

/************************************* ArrayView Copy *************************************/

constexpr auto arrayview7 = ArrayView("Hola mundo");
constexpr auto arrayview8 = ArrayView(HOLA_WORLD);

/************************************* ArrayView access *************************************/

constexpr const ll_char_t stringview_char = arrayview8[2];

/************************************* ArrayView algorithm *************************************/

constexpr len_t find_pos_1 = arrayview5.find_pos('*');
constexpr len_t find_pos_2 = arrayview6.find_pos('?');

constexpr auto find_1 = arrayview5.find('*');
constexpr auto find_2 = arrayview6.find('?');

constexpr ll_bool_t equals_1 = arrayview7.operator==(arrayview8);
constexpr ll_bool_t equals_2 = arrayview7.operator==(arrayview7);

constexpr ll_bool_t equals_3 = llcpp::algorithm::equals(numbers_1, numbers_2);
constexpr ll_bool_t equals_4 = llcpp::algorithm::equals({ 10 }, numbers_2);

constexpr ll_bool_t equals_5 = arrayview2.operator==(arrayview1);
constexpr ll_bool_t equals_6 = arrayview3.operator==(arrayview1);
constexpr ll_bool_t equals_7 = arrayview4.operator==(arrayview1);
constexpr ll_bool_t equals_8 = arrayview2.operator==(arrayview1);

constexpr ll_bool_t equals_9 = arrayview3.operator==(numbers_1);
constexpr ll_bool_t equals_10 = arrayview3.operator==(numbers_2);
constexpr ll_bool_t equals_11 = arrayview3.operator==(numbers_4);

constexpr ll_bool_t equals_12 = arrayview1.operator==(numbers_1);
constexpr ll_bool_t equals_13 = arrayview1.operator==(numbers_2);
constexpr ll_bool_t equals_14 = arrayview1.operator==(numbers_3);
constexpr ll_bool_t equals_15 = arrayview1.operator==(numbers_4);

constexpr ll_bool_t equals_16 = llcpp::algorithm::equals(numbers_1, numbers_3);
constexpr ll_bool_t equals_17 = llcpp::algorithm::equals(numbers_2, numbers_3);
constexpr ll_bool_t equals_18 = llcpp::algorithm::equals(numbers_1, numbers_4);
constexpr ll_bool_t equals_19 = llcpp::algorithm::equals(numbers_2, numbers_4);
constexpr ll_bool_t equals_20 = llcpp::algorithm::equals(numbers_3, numbers_4);

/************************************* Array reverse *************************************/

constexpr len_t __array_reverse_example__(int v) {
	len_t block[5]{};
	Array arr = block;
	for (len_t i{}; i < arr.len(); ++i) arr[i] = i;
	arr.reverse();
	return arr[v];
}

constexpr len_t array_reverse_0 = __array_reverse_example__(0);
constexpr len_t array_reverse_1 = __array_reverse_example__(1);
constexpr len_t array_reverse_2 = __array_reverse_example__(2);
constexpr len_t array_reverse_3 = __array_reverse_example__(3);
constexpr len_t array_reverse_4 = __array_reverse_example__(4);

/************************************* Array fill *************************************/

constexpr len_t __array_fill_example__(int v) {
	len_t block[5]{};
	Array arr = block;
	arr.fill(999, 1, 4);
	return arr[v];
}

constexpr len_t array_fill_0 = __array_fill_example__(0);
constexpr len_t array_fill_1 = __array_fill_example__(1);
constexpr len_t array_fill_2 = __array_fill_example__(2);
constexpr len_t array_fill_3 = __array_fill_example__(3);
constexpr len_t array_fill_4 = __array_fill_example__(4);

/************************************* Array shift left *************************************/

constexpr len_t __array_shift_left_example__(int v) {
	len_t block[5]{};
	Array arr = block;
	for (len_t i{}; i < arr.len(); ++i) arr[i] = i;
	arr.shiftLeft(2, 999);
	return arr[v];
}

constexpr len_t array_shift_left_0 = __array_shift_left_example__(0);
constexpr len_t array_shift_left_1 = __array_shift_left_example__(1);
constexpr len_t array_shift_left_2 = __array_shift_left_example__(2);
constexpr len_t array_shift_left_3 = __array_shift_left_example__(3);
constexpr len_t array_shift_left_4 = __array_shift_left_example__(4);

/************************************* Array shift right *************************************/

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

/************************************* Array test nodes *************************************/

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

constexpr len_t array_test_nodes_1 = __array_test_nodes_example__(999, 7);

/************************************* Array test list 2 *************************************/

constexpr len_t ARR_TEST_SIZE_3 = 10;
using ArrayType_3 = Array<len_t, ARR_TEST_SIZE_3>;
using NodeTest3 = linked::DoubleNode<ArrayType_3>;

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

constexpr len_t array_test_nodes3_1 = __array_test_nodes3_example__(1, 0);
constexpr len_t array_test_nodes3_2 = __array_test_nodes3_example__(2, 2);
constexpr len_t array_test_nodes3_3 = __array_test_nodes3_example__(9, 1);

/************************************* Array test list 4 *************************************/

constexpr len_t ARR_TEST_SIZE_5 = 10;
using ArrayType_5 = Array<len_t, ARR_TEST_SIZE_5>;
using NodeTest5 = linked::DoubleNode<ArrayType_5>;

//template<class T, len_t SIZE>
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
