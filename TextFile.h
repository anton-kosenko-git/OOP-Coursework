#ifndef FILE_H
#define FILE_H

#include<cstdio>
#include<iostream>
#include<fstream>
#include<sstream>
#include<utility>
#include<string>
#include<vector>
#include<algorithm>
#include<time.h>
#include "Functions.h"

using namespace std;

// Start of file class
class TextFile
{
protected:
	string _name;

public:
	// Default constructor
	TextFile() { _name = "none"; }
	// Parameterised constructor
	TextFile(string namein);
	// Default destructor
	~TextFile() {}

	// Accessor for name
	string getName() const;

	// Mutator for name (must change actual file name)
	void setName(string name);
	void changeName(string name);

	// Create new txt or dat file and write to it (check for existing file & ends in .txt or .dat)
	void createFile(string name);
	// Open and edit existing txt or dat file (check whether file exists)
	void editFile();
	// Delete txt or dat file
	void deleteFile();
	// Function to append new text to the end of a file
	void appendFile();
	// Function to search through a file for a string
	int searchFile(std::string search_parameter);

};

#endif