#include "TextFile.h"

// Parameterised constructor
TextFile::TextFile(string namein){

	// Parameterised constructor should only be used if the file already exists (i.e. when loading)
	ifstream inFile(namein.c_str());
	if (inFile.good()){
		inFile.close();
		string file_extension;
		// Get the file extension of the name
		try{
			size_t pos = namein.find(".");
			file_extension = namein.substr(pos);
		}
		catch (...) {
			file_extension = "none";
		}
		// Check to see if the file extension is correct
		if (file_extension != ".txt" && file_extension != ".dat") {
			cout << "WARNING: File must be either .txt or .dat" << endl;
		}
		else{
			_name = namein;
		}
	}
	else{
		inFile.close();
		cout << "WARNING: The file " << namein << " does not exist, setting name to 'none'" << endl;
		_name = "none";
	}
	
}

// Accessor for name
string TextFile::getName() const{
	return _name;
}

// Mutator for name
void TextFile::setName(string new_name){
	
	// Check the current file actually exists
	ifstream inFile(_name.c_str());
	if (!inFile.good()){
		inFile.close();
		ifstream newFile(new_name.c_str());
		// Get the file extension of the new name
		std::string file_extension;
		try{
			size_t pos = new_name.find(".");
			file_extension = new_name.substr(pos);
		}
		catch (...){
			if (new_name == "none"){
				_name = new_name;
			}
			else{
				file_extension = "none";
			}
		}
		if (new_name != "none"){
			// Check to see if the new file name corresponds to an existing file
			if (!newFile.good()){
				newFile.close();
				cout << "WARNING: The file " << new_name << " does not exist!" << endl;
			}

			// Check to see if the file extension is correct
			else if (file_extension != ".txt" && file_extension != ".dat") {
				newFile.close();
				cout << "WARNING: New file must be either .txt or .dat" << endl;
			}

			// Rename the file
			else{
				newFile.close();
				_name = new_name;
			}
		}
	}

	else{
		inFile.close();
		cout << "WARNING: This event already has a file attached" << endl;
	}
}

// Mutator for name
void TextFile::changeName(string new_name){

	// Check the current file actually exists
	ifstream inFile(_name.c_str());
	if (inFile.good()){
		inFile.close();
		ifstream newFile(new_name.c_str());
		// Get the file extension of the new name
		std::string file_extension;
		try {
			size_t pos = new_name.find(".");
			file_extension = new_name.substr(pos);
		}
		catch (...) {
			file_extension = "none";
		}

		// Check to see if the new file name corresponds to an existing file
		if (newFile.good()){
			newFile.close();
			cout << "WARNING: The file " << new_name << " already exists!" << endl;
		}

		// Check to see if the file extension is correct
		else if (file_extension != ".txt" && file_extension != ".dat") {
			newFile.close();
			cout << "WARNING: New file must be either .txt or .dat" << endl;
		}

		// Rename the file
		else{
			newFile.close();
			int result = rename(_name.c_str(), new_name.c_str());
			if (!(result == 0)) cout << "Error renaming file" << endl;
			else _name = new_name;
		}
	}

	else{
		inFile.close();
		cout << "WARNING: The file " << _name << " does not exist, cannot change name'" << endl;
	}
}

// Create new txt or dat file and write to it
void TextFile::createFile(string name){
	//cout << "gets here" << endl;
	// Check if file already exists
	ifstream inFile(name.c_str());
	if (inFile.good()){
		inFile.close();
		cout << "WARNING: The file " << name << " already exists" << endl;
	}

	else{
		inFile.close();
		// Get the file extension of the name
		size_t pos = name.find(".");
		string file_extension = name.substr(pos);

		// Check to see if the file extension is correct
		if (file_extension != ".txt" && file_extension != ".dat") {
			cout << "WARNING: New file must be either .txt or .dat" << endl;
		}

		else{
			cout << endl << "Enter contents of file " << name << ", when finished press enter + ':x' + enter:" << endl;
			ofstream outFile(name.c_str());
			string output;
			string line;
			// Read in lines from user input until the delimiter ":x" is seen
			do{
				getline(cin, line);
				output += line;
				output.push_back('\n');
			} while (line != ":x");

			// Remove unwanted characters
			output.pop_back(); output.pop_back(); output.pop_back();
			// Write to file
			outFile << output;
			outFile.close();
			_name = name;
		}
	}
}

// Open and edit existing txt or dat file 
void TextFile::editFile(){

	ifstream inFile(_name.c_str());
	string line;
	vector<string> file_content;
	int i = 1;
	bool exit_flag = 1;
	// Read in and display file contents
	if (inFile.good()){
		while (getline(inFile, line))
		{
			cout << i << ": " << line << '\n';
			file_content.push_back(line);
			i++;
		}
		inFile.close();

		int line_num;
		string new_line;
		// Let user replace lines in the file
		while (exit_flag){
			cout << "Enter which line number you would like to replace or -1 to exit: ";
			cin >> line_num;
			if (line_num == -1) exit_flag = 0;
			else {
				cout << "Previous line was: " << file_content[line_num - 1] << endl << "New line is: ";
				cin.ignore();
				getline(cin, new_line);
				file_content[line_num - 1] = new_line;
				cout << "File now reads: " << endl;
				int j = 1;
				// Display the updated file contents to the user
				for (auto current_content = file_content.begin(); current_content < file_content.end(); current_content++){
					cout << j << ":" << *current_content << endl;
					j++;
				}
			}
		}
		// Delete old file
		remove(_name.c_str());
		// Create and write new file with same name
		ofstream outFile(_name.c_str());
		for (auto current_content = file_content.begin(); current_content < file_content.end(); current_content++){
			outFile << *current_content << endl;
		}
	}

	else{
		inFile.close();
		cout << "WARNING: The file " << _name << " does not exist, connot edit" << endl;
	}
}

// Delete txt or dat file
void TextFile::deleteFile(){

	// Check file exists
	ifstream inFile(_name.c_str());
	if (inFile.good()){
		inFile.close();
		// Delete the file
		remove(_name.c_str());
		_name = "none";
	}
	else{
		inFile.close();
		cout << "WARNING: The file " << _name << " does not exist, cannot delete" << endl;
	}
}

// Function to append new text to the end of a file
void TextFile::appendFile(){
	// Check if file already exists, if it does write to the end of it
	ifstream inFile(_name.c_str());
	if (!inFile.good()){
		inFile.close();
		cout << "WARNING: The file " << _name << " does not exist" << endl;
	}
	else {
		inFile.close();
		ofstream File;
		File.open(_name.c_str(), std::ios::app);
		cout << endl << "Enter contents to append to file " << _name << ", when finished press enter + ':x' + enter:" << endl;
		string output;
		string line;
		// Read in lines from user input until the delimiter ":x" is seen
		do{
			getline(cin, line);
			output += line;
			output.push_back('\n');
		} while (line != ":x");

		// Remove unwanted characters
		output.pop_back(); output.pop_back(); output.pop_back();
		// Write to file
		File << output;
		File.close();
	}
	
}

// Function to search through a file for a string
int TextFile::searchFile(std::string search_parameter){
	int num_matches(0);
	ifstream inFile(_name.c_str());
	// Check file exists
	if (!inFile.good()){
		inFile.close();
		return num_matches;
	}
	else {
		std::string line;
		while (getline(inFile, line)){
			string::size_type pos = 0;
			// search for all instances of the parameter
			while ((pos = upperCase(line).find(upperCase(search_parameter), pos))!= std::string::npos) {
				num_matches++;
				pos += search_parameter.size();
			}
		}
	}
	return num_matches;
}