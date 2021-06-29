#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<cctype>
#include<string>
#include<algorithm>
#include<iostream>
#include<memory>
#include "DateAndTime.h"

// Compare two strings ignoring case
bool noCaseCompare(std::string string1, std::string string2);
bool noCaseCompare(std::string string, int I);
bool noCaseCompare(std::string string, DateAndTime DT);

// Try to find in the search parameter in the line ignoring case
bool noCaseFind(const std::string & line, const std::string & search_parameter);

// Convert string to uppercase for comparison
std::string upperCase(std::string input);
std::string upperCase(int input);
std::string upperCase(DateAndTime input);

// Compare string and int functions to avoid the compilation breaking
bool operator==(const int &I, const std::string &S);
bool operator==(const std::string &S, const int &I);

#endif