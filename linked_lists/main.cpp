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
	std::vector<std::string> list_contents;
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
