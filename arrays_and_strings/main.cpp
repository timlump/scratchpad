#include <string>
#include <iostream>
#include <limits>
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
	bool chars_encountered[std::numeric_limits<char>::max()] = {false};
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

TEST_CASE("is_unique")
{
	std::string str1 = "abcdef";
	REQUIRE(is_unique(str1) == true);
	REQUIRE(is_unique_alt(str1) == true);

	std::string str2 = "aabcdef";
	REQUIRE(is_unique(str2) == false);
	REQUIRE(is_unique_alt(str2) == false);
}

// 1.2 check permutation
// if different lengths - not permutations
// if have any different characters - not permutations
// need to have same characters, in same frequency
bool is_permutation(std::string str1, std::string str2)
{
	if (str1.size() != str2.size()) {
		return false;
	}

	int str1_char_freq[std::numeric_limits<char>::max()] = { 0 };
	int str2_char_freq[std::numeric_limits<char>::max()] = { 0 };

	for (int i = 0; i < str1.size(); i++) {
		str1_char_freq[str1[i]]++;
		str2_char_freq[str2[i]]++;
	}

	for (int i = 0; i < std::numeric_limits<char>::max(); i++) {
		if (str1_char_freq[i] != str2_char_freq[i]) {
			return false;
		}
	}

	return true;
}

TEST_CASE("is_permutation")
{
	{
		std::string str1 = "helloworld";
		std::string str2 = "worldhello";
		REQUIRE(is_permutation(str1, str2) == true);
	}

	{
		std::string str1 = "helloworld";
		std::string str2 = "worldHello";
		REQUIRE(is_permutation(str1, str2) == false);
	}
	
	{
		std::string str1 = "helloworld";
		std::string str2 = "Hello,world!";
		REQUIRE(is_permutation(str1, str2) == false);
	}
}