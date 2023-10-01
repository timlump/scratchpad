#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <map>
#include <algorithm>
#include <catch2/catch_all.hpp>

struct node
{
	std::string value = "";
	node* next = nullptr;
};

node* create_linked_list(std::vector<std::string> values)
{
	node* head = nullptr;
	node* last = nullptr;

	for (auto value : values) {
		node * current = new node();
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

bool match(node* head, std::vector<std::string> values)
{
	node* current = head;
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
void remove_dupes(node* node) {
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
	node* list = create_linked_list(values);
	remove_dupes(list);

	REQUIRE(match(list, { "a","b","c" }) == true);
}

int get_length(node* head)
{
	int length = 0;
	node* current = head;
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
node* get_kth_to_last_node(node* head, int k) {
	int length = get_length(head);

	int target = (length - 1) - k;
	node* current = head;
	for (int count = 0; count < target; count++) {
		current = current->next;
	}

	return current;
}

TEST_CASE("return kth")
{
	std::vector<std::string> values = { "a","b","c" };
	node* list = create_linked_list(values);
	node* result = get_kth_to_last_node(list, 1);

	REQUIRE(result->value == "b");
}

// 2.3
// arbitrary node in between first and last
// with no awareness of the parent node
void delete_node(node* to_delete)
{
	// if this is false, there is nothing we can do
	// as we are at the end of the list
	node* next = to_delete->next;
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
	node* list = create_linked_list(values);

	node* to_delete = list->next;
	delete_node(to_delete);

	REQUIRE(match(list, { "a","c" }) == true);
}