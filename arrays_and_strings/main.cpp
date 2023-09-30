#include <string>
#include <iostream>
#include <limits>
#include <map>
#include <catch2/catch_all.hpp>

// 1.1 is unique?
// assumptions - all characters are ascii
// can't use any other data structures
bool is_unique(const std::string str) {
	
	for (int i = 0; i < str.size(); i++) {
		for (int j = 0; j < str.size(); j++) {
			if (i != j && str[i] == str[j]) {
				return false;
			}
		}
	}

	return true;
}

bool is_unique_alt(const std::string str)
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
bool is_permutation(const std::string str1, const std::string str2)
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

// 1.3 - urlify
// this approach will create a new string
std::string urlify(const std::string str) {
	std::string result = "";
	for (int i = 0; i < str.size(); i++) {
		char c = str[i];
		if (c == ' ') {
			result += "%20";
		}
		else {
			result += c;
		}
	}
	return result;
}

void urlify_in_place(std::string &str) {
	int space_count = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			space_count++;
		}
	}

	// every space means 2 additional characters added
	int old_size = str.size();
	int new_size = old_size + space_count * 2;
	str.resize(new_size);

	int source_idx = old_size - 1;
	int dest_idx = new_size - 1;
	while (source_idx >= 0) {
		char c = str[source_idx];
		if (c != ' ') {
			str[dest_idx] = c;
			dest_idx--;
		}
		else {
			str[dest_idx] = '0';
			str[dest_idx - 1] = '2';
			str[dest_idx - 2] = '%';
			dest_idx -= 3;
		}
		source_idx--;
	}
}

TEST_CASE("urlify test")
{
	std::string str = "Hello World";
	REQUIRE(urlify(str) == "Hello%20World");

	urlify_in_place(str);
	REQUIRE(str == "Hello%20World");

	{
		std::string str2 = "Hi my name is bob! ";
		urlify_in_place(str2);
		REQUIRE(str2 == "Hi%20my%20name%20is%20bob!%20");
	}
}