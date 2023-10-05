#include <string>
#include <iostream>
#include <limits>
#include <map>
#include <algorithm>
#include <catch2/catch_all.hpp>


// 3.2 stack min
template <typename T>
class stack
{
public:
	stack(int reserve)
	{
		size = reserve;
		// default size is 10
		data = new std::pair<T,T>[size];
	}

	~stack()
	{
		delete[] data;
	}

	T pop()
	{
		if (count == 0) {
			throw std::out_of_range("stack is empty");
		}

		count--;
		return data[count].first;

	}

	bool push(T value)
	{
		if (count + 1 < size) {
			data[count].first = value;

			// min calc
			if (count == 0 || data[count - 1].second > value) {
				data[count].second = value;
			}

			count++;
			return true;
		}
		return false;
	}

	int get_count() {
		return count;
	}

	T get_min() {
		if (count > 0) {
			return data[count-1].second;
		}

		throw std::out_of_range("stack is empty");
	}

private:
	int size = 0;
	int count = 0;
	std::pair<T,T>* data;
};

TEST_CASE("stack min") {
	auto stk = new stack<int>(10);
	REQUIRE(stk->get_count() == 0);

	stk->push(10);
	REQUIRE(stk->get_count() == 1);

	REQUIRE(stk->pop() == 10);

	REQUIRE(stk->get_count() == 0);

	REQUIRE_THROWS(stk->pop());

	stk->push(5);
	REQUIRE(stk->get_min() == 5);

	stk->push(1);
	REQUIRE(stk->get_min() == 1);

	stk->pop();
	REQUIRE(stk->get_min() == 5);
}

// todo all the other questions :)