#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <map>
#include <algorithm>
#include <catch2/catch_all.hpp>

template <typename T>
struct node
{
	T value;
	node* next = nullptr;
};

template <typename T>
node<T>* create_linked_list(std::vector<T> values)
{
	node<T>* head = nullptr;
	node<T>* last = nullptr;

	for (auto value : values) {
		auto current = new node<T>();
		current->value = value;
		if (head == nullptr) {
			head = current;
		}
		else {
			last->next = current;
		}

		last = current;
	}

	return head;
}

template <typename T>
bool match(node<T>* head, std::vector<T> values)
{
	auto current = head;
	std::vector<T> list_contents;
	while (current != nullptr) {
		list_contents.push_back(current->value);
		current = current->next;
	}

	if (list_contents.size() != values.size()) {
		return false;
	}

	for (int idx = 0; idx < list_contents.size(); idx++) {
		if (list_contents[idx] != values[idx]) {
			return false;
		}
	}

	return true;
}

// 2.1
template <typename T>
void remove_dupes(node<T>* node) {
	while (node != nullptr) {
		if (node->next != nullptr && node->value == node->next->value) {
			node->next = node->next->next;
		}
		node = node->next;
	}
}

TEST_CASE("remove dups")
{
	std::vector<std::string> values = { "a","b","b","c" };
	auto list = create_linked_list(values);
	remove_dupes(list);

	REQUIRE(match(list, { "a","b","c" }) == true);
}

template<typename T>
int get_length(node<T>* head)
{
	int length = 0;
	auto current = head;
	while (current != nullptr) {
		length++;
		current = current->next;
	}
	return length;
}

// 2.2
// values: a -> b -> c -> d
// k:      3    2    1    0
// i:      0    1    2    3
// length: 4
template <typename T>
node<T>* get_kth_to_last_node(node<T>* head, int k) {
	int length = get_length(head);

	int target = (length - 1) - k;
	auto current = head;
	for (int count = 0; count < target; count++) {
		current = current->next;
	}

	return current;
}

TEST_CASE("return kth")
{
	std::vector<std::string> values = { "a","b","c" };
	auto list = create_linked_list(values);
	auto result = get_kth_to_last_node(list, 1);

	REQUIRE(result->value == "b");
}

// 2.3
// arbitrary node in between first and last
// with no awareness of the parent node
template <typename T>
void delete_node(node<T>* to_delete)
{
	// if this is false, there is nothing we can do
	// as we are at the end of the list
	auto next = to_delete->next;
	if (next != nullptr) {
		// we turn this node into the next node and delete the next node instead
		to_delete->value = next->value;
		to_delete->next = next->next;
		delete next;
	}
}

TEST_CASE("delete middle")
{
	std::vector<std::string> values = { "a","b","c" };
	auto list = create_linked_list(values);

	auto to_delete = list->next;
	delete_node(to_delete);

	REQUIRE(match(list, { "a","c" }) == true);
}

// 2.4 partition
// everything gets move left if its less than X
node<int>* paritition(node<int>* head, int x)
{
	std::vector<node<int>*> left;
	std::vector<node<int>*> right;

	auto current = head;

	// split
	while (current != nullptr) {
		if (current->value < x) {
			left.push_back(current);
		}
		else {
			right.push_back(current);
		}
		current = current->next;
	}

	// connect up nodes
	for (int idx = 0; idx < left.size() - 1; idx++) {
		left[idx]->next = left[idx + 1];
	}

	for (int idx = 0; idx < right.size() - 1; idx++) {
		right[idx]->next = right[idx + 1];
	}

	node<int>* new_head = left.empty() == false ? *left.begin() : *right.begin();

	// make sure the final next value is null
	if (right.empty() == false) {
		(*right.rbegin())->next = nullptr;
		// stich left and right together
		if (left.empty() == false) {
			(*left.rbegin())->next = (*right.begin());
		}
	}
	else {
		(*left.rbegin())->next = nullptr;
	}

	return new_head;
}

TEST_CASE("partition")
{
	auto head = create_linked_list<int>({ 3,5,8,5,10,2,1 });
	head = paritition(head, 5);
	REQUIRE(match<int>(head, { 3,2,1,5,8,5,10 }));
}

// 2.5 sum lists
node<int>* sum(node<int>* list1, node<int>* list2) {
	bool carry = false;
	node<int>* result = nullptr;
	node<int>* last_node = nullptr;
	while (list1 != nullptr && list2 != nullptr) {
		int value = list1->value + list2->value;
		if (carry) {
			value += 10;
		}

		carry = value >= 10;
		if (carry) {
			value = value - 10;
		}

		auto temp = new node<int>();
		temp->value = value;

		if (result == nullptr) {
			result = temp;
		}
		else {
			last_node->next = temp;
		}

		last_node = temp;

		list1 = list1->next;
		list2 = list2->next;
	}

	if (carry) {
		node<int>* carry_node = new node<int>();
		carry_node->value = 1;
		last_node->next = carry_node;
	}

	return result;
}

TEST_CASE("sum lists")
{
	{
		// 321
		auto list1 = create_linked_list<int>({ 1,2,3 });
		// 532
		auto list2 = create_linked_list<int>({ 2,3,5 });
		// 853 -> {3,5,8}
		auto result = sum(list1, list2);
		REQUIRE(match<int>(result, { 3,5,8 }));
	}

	{
		// 321
		auto list1 = create_linked_list<int>({ 1,2,3 });
		// 932
		auto list2 = create_linked_list<int>({ 2,3,9 });
		// 1253 -> {3,5,2,1}
		auto result = sum(list1, list2);
		REQUIRE(match<int>(result, { 3,5,2,1 }));
	}
}

// if there is no loop - fast_ptr will hit nullptr
// if there is a loop - slow and fast ptr will hit
template <typename T>
node<T>* find_loop_start(node<T>* list_head)
{
	auto slow_ptr = list_head;
	auto fast_ptr = list_head;

	// using do while as the exit condition actually briefly exists at the start
	do {

		slow_ptr = slow_ptr->next;
		if (fast_ptr->next == nullptr) {
			return nullptr;
		}
		else {
			fast_ptr = fast_ptr->next->next;
		}
	} while (slow_ptr != fast_ptr);

	// we've hit a collision now to find it
	slow_ptr = list_head;
	while (slow_ptr != fast_ptr) {
		slow_ptr = slow_ptr->next;
		// fast_ptr doesn't move fast for this step
		fast_ptr = fast_ptr->next;
	}

	return slow_ptr;
}

TEST_CASE("loop detection")
{
	// create linked list with loop
	auto list = create_linked_list<std::string>({ "a","b","c","d","e" });
	auto node_c = list->next->next;
	auto node_e = list->next->next->next->next;
	node_e->next = node_c;

	auto loop_start = find_loop_start(list);
	REQUIRE(loop_start != nullptr);
	REQUIRE(loop_start->value == "c");
}

// todo 2.6-2.7