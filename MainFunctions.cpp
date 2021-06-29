#include "MainFunctions.h"
#include <time.h>
using namespace std;

namespace mainfunc{

	inline bool testFile(const std::string& file_name) {
		ifstream f(file_name.c_str());
		return f.good();
	}

	// Save state
	void saveState(std::string file_name, std::unordered_map<int, std::shared_ptr<Event>> events){
		if (file_name != "none"){
			// Check file exists
			if (testFile(file_name)){
				// Delete the file
				remove(file_name.c_str());
				// Loop over all events in the map and save them to the new file
				for (auto evt : events){
					evt.second->save(file_name);
				}
			}
			else{
				std::cout << "WARNING: The file " << file_name << " does not exist, cannot delete" << endl;
			}
		}
		else{
			// Ask user for a file name that doesn't already exist
			do{
				std::cout << std::endl << "Enter a file name: ";
				std::cin >> file_name;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (testFile(file_name));
			ofstream saveFile(file_name.c_str());
			saveFile << file_name << std::endl;
			// Loop over all events in the map and save them to the new file
			for (auto evt : events){
				evt.second->save(file_name);
			}
		}
	}

	// Load state
	std::vector<std::shared_ptr<Event>> loadEvents(std::string file_name, std::vector<std::shared_ptr<Event>> events){
		ifstream loadFile(file_name.c_str());
		std::string line;
		//Loop over the lines of the file until the end 
		while (std::getline(loadFile, line)){
		 	string::size_type pos = 0;
			 	if (noCaseFind(line, "Event::Meeting")){
		 		Meeting temp;
		 		loadFile >> temp;
		 		events.push_back(std::make_shared<Meeting>(temp));
		 	}
		}
		// Close the file and return vector of events
		loadFile.close();
		return events;
	}


	// User enters new event with input checks
	std::unordered_map<int, std::shared_ptr<Event>> createNewEvent(std::unordered_map<int, std::shared_ptr<Event>> events) {
		// Let user choose what type of event user want to create
		std::string option;
		while (!noCaseCompare(option, "meeting") && !noCaseCompare(option, "help")){
			std::cout << std::endl << "What type of event do you want to create? (Type help for options): ";
			getline(cin, option);
			// Display available options to user
			if (noCaseCompare(option, "help")){
				std::cout << std::endl << "The available event types are:" << std::endl
					<< "meeting" << std::endl;
				option = "";
			}
		}
		// Send user to relevant creation function for that event type
		if (noCaseCompare(option, "meeting")){
			events = createNewMeeting(events);
		}

		// Return all events with the new event added
		return events;
	}

	// Create a new meeting
	std::unordered_map<int, std::shared_ptr<Event>> createNewMeeting(std::unordered_map<int, std::shared_ptr<Event>> events){
		// Fill all relevant fields
		std::string name, location, group, contractor;
		float price;
		DateAndTime start, end;
		bool failed{ 0 };
		do {
			std::cout << std::endl << "Name: "; getline(std::cin, name);
		} while (cin.fail());
		do {
			std::cout << "Location: "; getline(std::cin, location);
		} while (cin.fail());
		do {
			std::cout << "Group: "; getline(std::cin, group);
		} while (cin.fail());
		do {
			std::cout << "Contractor: "; getline(std::cin, contractor);
		} while (cin.fail());
		do {
			if (cin.fail()){
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			std::cout << "Expected price: "; std::cin >> price;
		} while (cin.fail());
		do {
			std::cout << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (cin.fail());
		do {
			std::cout << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (cin.fail());
		Meeting temp;
		// Try to create a meeting
		try {
			Meeting meet(name, location, contractor, group, price);
			meet.setStart(start); meet.setEnd(end);
			temp = meet;
		}
		catch (...) {
			std::cout << "WARNING: Issue creating meeting please try again" << std::endl;
			failed = 1;
		}
		if (!failed) {
			// Set or create a file
			std::string has_file;
			while (has_file != "y" && has_file != "n"){
				std::cout << "Are there already notes for this meeting? (y/n): ";
				std::cin >> has_file;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (has_file == "y"){
				std::string file_name;
				do {
					std::cout << "File name: "; std::cin >> file_name;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while (cin.fail());
				temp.setNotes(file_name);
			}
			else {
				std::string create_file;
				while (create_file != "y" && create_file != "n"){
					std::cout << "Would you like to create notes? (y/n): ";
					std::cin >> create_file;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				if (create_file == "y"){
					std::string file_name;
					do {
						std::cout << "File name: "; std::cin >> file_name;
						cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
					} while (cin.fail());
					try {
						temp.createFile(file_name);
					}
					catch (...){
						std::cout << "WARNING: Issue creating file" << std::endl;
					}
				}
			}
			events.emplace(temp.getId(), std::make_shared<Meeting>(temp));
		}
		return events;
	}

	// User creates a search with input checks
	void searchEvents(std::unordered_map<int, std::shared_ptr<Event>> events){
		Search search(events);
		bool finished{ 0 };
		while (!finished){
			std::string search_type;
			std::string keyword;
			std::string string_parameter;
			int int_parameter;
			float float_parameter;
			DateAndTime dt_parameter;
			std::string option;
			// Ask user what type of search user want to choose
			while (!noCaseCompare(option, "general") && !noCaseCompare(option, "keyword") && !noCaseCompare(option, "file")
				&& !noCaseCompare(option, "back") && !noCaseCompare(option, "help")){
				std::cout << std::endl << "What type of search do you want to perform? (Type help for options): ";
				std::cin >> option;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			// Display help to user
			if (noCaseCompare(option, "help")){
				std::cout << std::endl << "The available options are:" << std::endl << "General: Search all fields for a string, integer, float or date" << std::endl
					<< "Keyword: Same as general but search through a specific field" << std::endl
					<< "File: Search through the notes for a word or phrase" << std::endl
					<< "Back: exit to main menu" << std::endl;
			}
			// Do a general search
			if (noCaseCompare(option, "general")){
				// Ask user what type the would like to search for
				while (!noCaseCompare(search_type, "int") && !noCaseCompare(search_type, "string") && !noCaseCompare(search_type, "date")){
					std::cout << std::endl << "Do you want to search for a string, int, float or date?: ";
					std::cin >> search_type;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				// If type is an integer
				if (noCaseCompare(search_type, "int")){
					do {
						std::cout << "Enter the search parameter: ";
						std::cin >> int_parameter;
						cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
					} while (cin.fail());
					search.searchFor(int_parameter);
					search.printResults();
				}
				// If type is float
				if (noCaseCompare(search_type, "float")){
					do {
						std::cout << "Enter the search parameter: ";
						std::cin >> float_parameter;
						cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
					} while (cin.fail());
					search.searchFor(float_parameter);
					search.printResults();
				}
				// If type is a string
				if (noCaseCompare(search_type, "string")){
					do {
						std::cout << "Enter the search parameter: ";
						getline(cin, string_parameter);
					} while (cin.fail());
					search.searchFor(string_parameter);
					search.printResults();
				}
				// If type is a date and time
				if (noCaseCompare(search_type, "date")){
					do {
						std::cout << "Enter the search parameter: ";
						std::cin >> dt_parameter;
						cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
					} while (cin.fail());
					search.searchFor(dt_parameter);
					search.printResults();
				}
			}
			// Do a keyword search
			if (noCaseCompare(option, "keyword")){
				do {
					std::cout << std::endl << "Enter the field you want to search through: ";
					getline(std::cin, keyword);
				} while (cin.fail());
				// Ask user what type the would like to search for
				while (!noCaseCompare(search_type, "int") && !noCaseCompare(search_type, "float") && !noCaseCompare(search_type, "string") && !noCaseCompare(search_type, "date")){
					std::cout << std::endl << "Do you want to search for a string, int, float or date?: ";
					std::cin >> search_type;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				// If type is an integer
				if (noCaseCompare(search_type, "int")){
					do {
						std::cout << "Enter the search parameter: ";
						std::cin >> int_parameter;
						cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
					} while (cin.fail());
					search.searchKeywordFor(keyword, int_parameter);
					search.printResults();
				}
				// If type is float
				if (noCaseCompare(search_type, "float")){
					do {
						std::cout << "Enter the search parameter: ";
						std::cin >> float_parameter;
						cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
					} while (cin.fail());
					search.searchKeywordFor(keyword, float_parameter);
					search.printResults();
				}
				// If type is a string
				if (noCaseCompare(search_type, "string")){
					do {
						std::cout << "Enter the search parameter: ";
						getline(cin, string_parameter);
					} while (cin.fail());
					search.searchKeywordFor(keyword, string_parameter);
					search.printResults();
				}
				// If type is a date and time
				if (noCaseCompare(search_type, "date")){
					do {
						std::cout << "Enter the search parameter: ";
						std::cin >> dt_parameter;
						cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
					} while (cin.fail());
					search.searchKeywordFor(keyword, dt_parameter);
					search.printResults();
				}
			}
			// Do a file search
			if (noCaseCompare(option, "file")){
				do {
					std::cout << std::endl << "Enter the search parameter: ";
					getline(cin, string_parameter);
				} while (cin.fail());
				search.searchFilesFor(string_parameter);
			}
			// Finished
			if (noCaseCompare(option, "back")){
				std::string confirm;
				while (confirm != "y" && confirm != "n"){
				std::cout << std::endl << "Are you sure you want to back to main menu? (y/n): ";
				std::cin >> confirm;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
					if (confirm == "y") finished = 1;
			}
		}
	}
}
