#include <string>
#include <iostream>

// 1.1 is unique?
bool is_unique(std::string str) {
	return false;
}

int main(int argc, char* argv[])
{
	// 1.1
	{
		auto str1 = "abcdef";
		std::cout << str1 << " is_unique? =" << is_unique(str1) << std::endl;
	}
}