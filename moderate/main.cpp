#include <catch2/catch_all.hpp>
#include <string>
#include <map>
#include <algorithm>

// 16.1 number swapper

void swap(int& a, int& b)
{
	if (a == b) return;
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

TEST_CASE("number swap")
{
	{
		int a = 1;
		int b = 2;
		swap(a, b);
		REQUIRE(a == 2);
		REQUIRE(b == 1);
	}

	{
		int a = 1;
		int b = 1;
		swap(a, b);
		REQUIRE(a == 1);
		REQUIRE(b == 1);
	}
}

int word_frequency(std::string word, std::string text = "", bool reset = false) {
	static std::map<std::string, int> word_freq;
	{
		if (reset || word_freq.empty()) {
			word_freq.clear();
			std::string current = "";
			for (char c : text) {
				// is alpha actually expects ints and will throw a debug exception if char is used
				// as some of the values will appear as negative
				if (std::isalpha((unsigned char)c) == false) {
					if (current.empty() == false) {
						word_freq[current]++;
					}
					current = "";
				}
				else {
					current += std::tolower(c);
				}
			}
		}
	}

	for (int i = 0; i < word.size(); i++)
	{
		word[i] = std::tolower(word[i]);
	}
	return word_freq[word];
}

// 16.2 word frequency
TEST_CASE("word frequency")
{
	std::string example_text = "I entered the cabin where lay the remains of my ill-fated and admirable friend."
		"Over him hung a form which I cannot find words to describe—gigantic in stature,"
		"yet uncouth and distorted in its proportions. As he hung over the coffin,"
		"his face was concealed by long locks of ragged hair; but one vast hand was extended,"
		"in colour and apparent texture like that of a mummy. When he heard the sound of my approach,"
		"he ceased to utter exclamations of grief and horror and sprung towards the window."
		"Never did I behold a vision so horrible as his face, of such loathsome yet appalling hideousness."
		"I shut my eyes involuntarily and endeavoured to recollect what were my duties with regard to this destroyer."
		"I called on him to stay. He paused, looking on me with wonder, and again turning towards the lifeless form of his creator,"
		"he seemed to forget my presence, and every feature and gesture seemed instigated by the wildest rage of some uncontrollable passion.";

	
	REQUIRE(word_frequency("remains", example_text) == 1);
	REQUIRE(word_frequency("computer") == 0);
	REQUIRE(word_frequency("when") == 1);
	REQUIRE(word_frequency("my") == 5);
}