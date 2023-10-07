#include <vector>
#include <string>
#include <catch2/catch_all.hpp>

template <typename T>
class Node
{
public:
	Node(std::string nm, T val) {
		name = nm;
		value = val;
	}

	std::string name;
	T value;
	std::vector<Node<T>*> children;
};

template <typename T>
struct Graph
{
	std::vector<Node<T>*> nodes;

	~Graph()
	{
		for (auto node : nodes) {
			delete node;
		}
	}

	Node<T>* create_node(std::string name, T val)
	{
		auto node = new Node<T>(name,val);
		nodes.push_back(node);
		return node;
	}
};

template <typename T>
bool is_route_between(Node<T>* start, Node<T>* end)
{
	std::set<Node<T>*> visited;
	return is_route_between(visited, start, end);
}

template <typename T>
bool is_route_between(std::set<Node<T>*> &visited, Node<T>* current_node, Node<T>* end) {
	// make sure we haven't been here before so we don't go in loops
	if (visited.find(current_node) == visited.end()) {
		visited.insert(current_node);
		// check if we've reached the end
		if (current_node == end) {
			return true;
		}
		else {
			for (auto child : current_node->children) {
				if (is_route_between(visited, child, end)) {
					return true;
				}
			}
		}
	}
	return false;
}

// 4.1
TEST_CASE("route between nodes")
{
	// create node graph
	Graph<int> graph;
	{
		// create some nodes
		auto node1 = graph.create_node("node_1",1);
		auto node2 = graph.create_node("node_2",2);
		auto node3 = graph.create_node("node_3",3);

		auto node4 = graph.create_node("node_4",4);
		auto node5 = graph.create_node("node_5",5);

		// connect some together
		node1->children.push_back(node2);
		node2->children.push_back(node3);
		
		node4->children.push_back(node5);
		node5->children.push_back(node4);

		REQUIRE(is_route_between(node1, node3) == true);
		REQUIRE(is_route_between(node1, node5) == false);
	}
}