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
	{
		std::vector<std::string> values= { "a","b","b","c" };
		node* list = create_linked_list(values);
		remove_dupes(list);

		REQUIRE(match(list, { "a","b","c" }) == true);
	}
}