#include "Functions.h"

// Compare two strings ignoring case 
bool noCaseCompare(std::string string1, std::string string2) {
	return ((string1.size() == string2.size()) && std::equal(string1.begin(), string1.end(), string2.begin(), [](char left, char right){
		return toupper(left) == toupper(right);
	}));
}

bool noCaseCompare(std::string string, int I) { return false; }
bool noCaseCompare(std::string string, DateAndTime DT) { return false; }

// Try to find in the search parameter in the line ignoring case
bool noCaseFind(const std::string & line, const std::string & search_parameter)
{
	auto it = search(line.begin(), line.end(), search_parameter.begin(), search_parameter.end(),
		[](char ch1, char ch2) { return toupper(ch1) == toupper(ch2); }
	);
	return (it != line.end());
}

// Convert string to uppercase for comparison
std::string upperCase(std::string input) {
	for (std::string::iterator it = input.begin(); it != input.end(); ++it)
		*it = toupper(*it);
	return input;
}
std::string upperCase(int input) {
	return "null";
}
std::string upperCase(DateAndTime input) {
	return "null";
}

// Compare string and int functions to avoid the compilation breaking
bool operator==(const int &I, const std::string &S){ return false; }
bool operator==(const std::string &S, const int &I){ return false; }