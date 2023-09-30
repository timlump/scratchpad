#include <string>
#include <iostream>
#include <map>
#include <catch2/catch_all.hpp>

// 1.1 is unique?
// assumptions - all characters are ascii
// can't use any other data structures
bool is_unique(std::string str) {
	
	for (int i = 0; i < str.size(); i++) {
		for (int j = 0; j < str.size(); j++) {
			if (i != j && str[i] == str[j]) {
				return false;
			}
		}
	}

	return true;
}

bool is_unique_alt(std::string str)
{
	bool chars_encountered[sizeof(char)] = { false };
	for (int i = 0; i < str.size(); i++) {
		char c = str[i];
		if (chars_encountered[c] == true) {
			return false;
		}
		else {
			chars_encountered[c] = true;
		}
	}

	return true;
}

TEST_CASE("is_unique_test")
{
	std::string str1 = "abcdef";
	REQUIRE(is_unique(str1) == true);
	REQUIRE(is_unique_alt(str1) == true);

	std::string str2 = "aabcdef";
	REQUIRE(is_unique(str2) == false);
	REQUIRE(is_unique_alt(str2) == false);
}