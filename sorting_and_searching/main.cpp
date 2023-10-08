#include <catch2/catch_all.hpp>
#include <vector>

// 10.1 - sorted merge
std::vector<int> merge(std::vector<int> a, std::vector<int> b)
{
	std::vector<int> result;

	auto a_iter = a.begin();
	auto b_iter = b.begin();
	bool a_in_progress = a_iter != a.end();
	bool b_in_progress = b_iter != b.end();
	while (a_in_progress || b_in_progress) {
		if (a_in_progress && b_in_progress) {
			int a_value = *a_iter;
			int b_value = *b_iter;
			if (a_value < b_value) {
				result.push_back(a_value);
				a_iter++;
			}
			else {
				result.push_back(b_value);
				b_iter++;
			}
		}
		else if (a_in_progress) {
			result.push_back(*a_iter);
			a_iter++;
		}
		else {
			result.push_back(*b_iter);
			b_iter++;
		}

		a_in_progress = a_iter != a.end();
		b_in_progress = b_iter != b.end();
	}

	return result;
}

TEST_CASE("sorted merge")
{
	{
		std::vector<int> a = { 1,3,6,7,9,11,13,15,16,19,21 };
		std::vector<int> b = { 2,4,5,8,10,12,14,17,18,20 };
		int total = a.size() + b.size();

		auto result = merge(a, b);
		REQUIRE(result.size() == total);
		for (int idx = 0; idx < result.size(); idx++) {
			REQUIRE(result[idx] == idx + 1);
		}
	}
	
	{
		std::vector<int> a = { 1,2,3,4,5,6,7,8,9 };
		std::vector<int> b = { 10,11,12,13,14,15,16,17,18,19 };
		int total = a.size() + b.size();

		auto result = merge(a, b);
		REQUIRE(result.size() == total);
		for (int idx = 0; idx < result.size(); idx++) {
			REQUIRE(result[idx] == idx + 1);
		}
	}
}