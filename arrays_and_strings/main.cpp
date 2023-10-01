#include <string>
#include <iostream>
#include <limits>
#include <map>
#include <algorithm>
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

// 1.3 - urlify
// this approach will create a new string
std::string urlify(std::string str) {
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

TEST_CASE("urlify")
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

// 1.4 palindrome permutation
bool is_palindrom_permutation(std::string str) {
	int char_freq[std::numeric_limits<char>::max()] = { 0 };
	int char_count = 0;
	
	for (int idx = 0; idx < str.size(); idx++) {
		char c = str[idx];
		// ignore non-alpha characters
		if (std::isalpha(c)) {
			// ignore cases
			c = std::tolower(c);
			char_freq[c]++;
			char_count++;
		}
	}

	// if the string length is odd, 1 character can be odd as it would be in the middle but the rest must be even
	int num_odd = 0;
	// we've only stored the lower case alpha numeric characters so let's just iterate over them
	for (char i = 'a'; i <= 'z'; i++) {
		int freq = char_freq[i];
		
		if (freq != 0 && freq % 2 != 0) {
			num_odd++;
		}
	}

	// if even
	if (char_count % 2 == 0 && num_odd > 0) {
		return false;
	}
	else if (char_count % 2 != 0 && num_odd > 1) {
		return false;
	}
	return true;
}

TEST_CASE("palindrome permutation")
{
	{
		std::string str = "Badb Doa";
		REQUIRE(is_palindrom_permutation(str) == true);
	}

	{
		std::string str = "abcabc";
		REQUIRE(is_palindrom_permutation(str) == true);
	}

	{
		std::string str = "aabbbc";
		REQUIRE(is_palindrom_permutation(str) == false);
	}
}

// 1.4
bool is_one_or_zero_edits_away(std::string str1, std::string str2)
{
	int char_freq1[std::numeric_limits<char>::max()] = { 0 };
	int char_freq2[std::numeric_limits<char>::max()] = { 0 };

	for (int idx = 0; idx < str1.size(); idx++) {
		char c = str1[idx];
		char_freq1[c]++;
	}

	for (int idx = 0; idx < str2.size(); idx++) {
		char c = str2[idx];
		char_freq2[c]++;
	}

	int num_differences = 0;
	for (int idx = 0; idx < std::numeric_limits<char>::max(); idx++) {
		num_differences += std::abs(char_freq2[idx] - char_freq1[idx]);
		if (num_differences > 1) {
			return false;
		}
	}

	return true;
}

TEST_CASE("one edit away")
{
	{
		std::string str1 = "drop";
		std::string str2 = "drops";
		REQUIRE(is_one_or_zero_edits_away(str1, str2) == true);
	}

	{
		std::string str1 = "prop";
		std::string str2 = "drops";
		REQUIRE(is_one_or_zero_edits_away(str1, str2) == false);
	}

	{
		std::string str1 = "throw";
		std::string str2 = "throw";
		REQUIRE(is_one_or_zero_edits_away(str1, str2) == true);
	}
}

std::string str_compress(std::string original) {
	std::stringstream stream;
	int count = 0;
	for (int idx = 0; idx < original.size(); idx++) {
		char c = original[idx];
		count++;
		
		// if character is changing or we are at the end of the line
		if (idx == original.size() - 1 || original[idx+1] != c) {
			stream << c << count;
			count = 0;
		}
	}

	std::string result = stream.str();
	if (result.size() > original.size()) {
		return original;
	}
	return result;
}

TEST_CASE("string compression")
{
	{
		std::string str = "aaaabbbbccdddde";
		REQUIRE(str_compress(str) == "a4b4c2d4e1");
	}

	{
		std::string str = "abcd";
		REQUIRE(str_compress(str) == "abcd");
	}
}