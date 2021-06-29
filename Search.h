#ifndef SEARCH_H
#define SEARCH_H

#include "Organise.h"
using namespace std;

// Derived class searching
// Make this a template class for the searching parameter
class Search : public Organise
{
protected:
	// Container of search results (event, keyword, search parameter)
	std::vector<std::pair<std::shared_ptr<Event>, std::pair<std::string,std::string>>> _search_results;

public:
	// Default constructor
	Search(){}
	// Parameterised constructor - pass unordered map of events - call base class constructor
	Search(std::unordered_map<int, std::shared_ptr<Event>> eventsin) : Organise(eventsin) {}
	// Destructor - clean up unordered map
	~Search(){}

	// Copy constructor and copy assignment declaration
	Search(Search&);
	Search& operator=(Search&);
	// Move constructor and move assignment declaration
	Search(Search&&);
	Search& operator=(Search&&);

	// Overridden print results function - show id, event type and name and searched value
	void printResults() const;

	// Template function to search everything for number or string or date - search through all event types and all member data
	template<class T> void searchFor(T search_parameter);

	// Template function to search keyword matched events (e.g. experiment = SBND) for number or string or date
	template<class T> void searchKeywordFor(std::string keyword, T search_parameter);

	// Function to search member files for number or string - print id, event name and type, file name, number of times search parameter occurs
	void searchFilesFor(std::string search_parameter);

	// Accessor function for container of searched results
	std::vector<std::pair<std::shared_ptr<Event>, std::pair<std::string, std::string>>> getResults();

};// End of Search class


// Template function to search everything for number or string or date - search through all event types and all member data
template<class T> void Search::searchFor(T search_parameter) {

	_search_results.clear();

	// Temporary vector of search results
	std::vector<std::pair<std::shared_ptr<Event>, std::pair<std::string, std::string>>> temp;

	// If the search parameter is an integer search all possible integer fields
	if (std::is_same<T, int>::value) {
		// Search for id (all)
		// Loop over all the events
		for (auto event : _events){
			if (event.second->getId() == search_parameter) temp.push_back(std::make_pair(event.second, std::make_pair("ID", std::to_string(event.second->getId()))));
		}
		// Replace the any previous search results with the new results
		_search_results = temp;
	}

	// If the search parameter is a float search all possible float fields
	if (std::is_same<T, float>::value) {
		// Search for prices (all)
		// Loop over all the events
		for (auto event : _events){
			if (event.second->getPrice() == search_parameter) temp.push_back(std::make_pair(event.second, std::make_pair("Price", std::to_string(event.second->getPrice()))));
		}
		// Replace the any previous search results with the new results
		_search_results = temp;
	}

	// If the search parameter is a date then search the two date and time fields
	else if (std::is_same<T, DateAndTime>::value) {
		// search start and end (all)
		for (auto event : _events){
			// Just search for matching dates ignoring times
			if (event.second->getStart() == search_parameter) temp.push_back(std::make_pair(event.second, std::make_pair("Start date", (event.second->getStart()).makeString())));
			if (event.second->getEnd() == search_parameter) temp.push_back(std::make_pair(event.second, std::make_pair("End date", (event.second->getEnd()).makeString())));
		}
		// Replace the any previous search results with the new results
		_search_results = temp;
	}

	// If the search parameter is a string then search all of the possible string fields
	else if (std::is_same<T, std::string>::value) {
		// search name and type (all), location (clmps), contractor(cntr), group(m)
		for (auto event : _events){
			if (upperCase(event.second->getName()).find(upperCase(search_parameter)) != std::string::npos){
				temp.push_back(std::make_pair(event.second, std::make_pair("Name", event.second->getName())));
			}
			if (upperCase(event.second->getType()).find(upperCase(search_parameter)) != std::string::npos){
				temp.push_back(std::make_pair(event.second, std::make_pair("Event type", event.second->getType())));
			}
			if (upperCase(event.second->getLocation()).find(upperCase(search_parameter)) != std::string::npos){
				temp.push_back(std::make_pair(event.second, std::make_pair("Location", event.second->getLocation())));
			}
			if (upperCase(event.second->getContractor()).find(upperCase(search_parameter)) != std::string::npos){
				temp.push_back(std::make_pair(event.second, std::make_pair("Contractor", event.second->getContractor())));
			}
			if (upperCase(event.second->getGroup()).find(upperCase(search_parameter)) != std::string::npos){
				temp.push_back(std::make_pair(event.second, std::make_pair("Group", event.second->getGroup())));
			}
		}
		// Replace the any previous search results with the new results
		_search_results = temp;
	}

	else std::cout << "WARNING: Can only search for strings, integers, floats or dates" << std::endl;
}

// Template function to search keyword matched events for number or string or date
template<class T> void Search::searchKeywordFor(std::string keyword, T search_parameter) {

	_search_results.clear();

	// Temporary vector of search results
	std::vector<std::pair<std::shared_ptr<Event>, std::pair<std::string, std::string>>> temp;

	// If the search parameter is an integer search all possible integer fields
	if (std::is_same<T, int>::value){
		// Match related keywords and search those fields
		if (noCaseCompare(keyword, "id")){
			for (auto event : _events){
				if (event.second->getId() == search_parameter) temp.push_back(std::make_pair(event.second, std::make_pair("ID", std::to_string(event.second->getId()))));
			}
			_search_results = temp;
		}
		else cout << "WARNING: The only fields with integers is id" << std::endl;
	}

	// If the search parameter is a date then search the two date and time fields
	else if (std::is_same<T, DateAndTime>::value){
		// Match related keywords and search events for those fields
		if (noCaseCompare(keyword, "start") || noCaseCompare(keyword, "start date")){
			for (auto event : _events){
				if (event.second->getStart() == search_parameter) temp.push_back(std::make_pair(event.second, std::make_pair("Start date", (event.second->getStart()).makeString())));
			}
			_search_results = temp;
		}
		else if (noCaseCompare(keyword, "end") || noCaseCompare(keyword, "end date")){
			for (auto event : _events){
				if (event.second->getEnd() == search_parameter) temp.push_back(std::make_pair(event.second, std::make_pair("End date", (event.second->getEnd()).makeString())));
			}
			_search_results = temp;
		}
		else cout << "WARNING: The only fields with dates are the start date and end date" << std::endl;
	}

	// If the search parameter is a string then search all of the possible string fields
	else if (std::is_same<T, std::string>::value){
		// Match related keywords and search events for those fields
		if (noCaseCompare(keyword, "location")){
			for (auto event : _events){
				if (upperCase(event.second->getLocation()).find(upperCase(search_parameter)) != std::string::npos) {
					temp.push_back(std::make_pair(event.second, std::make_pair("Location", event.second->getLocation())));
				}
			}
			_search_results = temp;
		}
		else if (noCaseCompare(keyword, "name")){
			for (auto event : _events){
				if (upperCase(event.second->getName()).find(upperCase(search_parameter)) != std::string::npos) {
					temp.push_back(std::make_pair(event.second, std::make_pair("Name", event.second->getName())));
				}
			}
			_search_results = temp;
		}
		else if (noCaseCompare(keyword, "type")){
			for (auto event : _events){
				if (upperCase(event.second->getType()).find(upperCase(search_parameter)) != std::string::npos){
					temp.push_back(std::make_pair(event.second, std::make_pair("Event type", event.second->getType())));
				}
			}
			_search_results = temp;
		}
		else if (noCaseCompare(keyword, "contractor")){
			for (auto event : _events){
				if (upperCase(event.second->getContractor()).find(upperCase(search_parameter)) != std::string::npos){
					temp.push_back(std::make_pair(event.second, std::make_pair("Contractor", event.second->getContractor())));
				}
			}
			_search_results = temp;
		}
		else if (noCaseCompare(keyword, "group")){
			for (auto event : _events){
				if (upperCase(event.second->getGroup()).find(upperCase(search_parameter)) != std::string::npos){
					temp.push_back(std::make_pair(event.second, std::make_pair("Group", event.second->getGroup())));
				}
			}
			_search_results = temp;
		}
		else std::cout << "WARNING: The only fields with strings are name, type, location, contractor and group" << std::endl;
	}

	else std::cout << "WARNING: Can only search for strings, integers, floats or dates" << std::endl;
}

#endif