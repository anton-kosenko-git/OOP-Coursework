#include "Search.h"
using namespace std;

// Copy constructor
Search::Search(Search &S){
	_search_results = S._search_results; _events = S._events;
}
// Copy assignment operator
Search& Search::operator=(Search &S){
	// Check for self assignment
	if (&S == this) return *this;
	// Delete this objects data
	_search_results.clear(); _events.clear();
	// Copy data from S to this
	_search_results = S._search_results; _events = S._events;
	return *this;
}

// Move constructor
Search::Search(Search &&S){
	// Steal the data
	_search_results = S._search_results; _events = S._events;
	S._search_results.clear(); S._events.clear();
}
// Move assignment operator
Search& Search::operator=(Search &&S){
	// Use swap function to steal the data
	std::swap(_search_results, S._search_results); std::swap(_search_results, S._search_results);
	return *this;
}

// Overridden print results function - show id, event type and name and searched value
void Search::printResults() const{
	std::cout << "Search Results:" << std::endl;
	for (auto result : _search_results){
		std::cout << "ID: " << result.first->getId() << " " << result.first->getType() << " ("
			<< result.first->getName() << ")" << std::endl 
			<< "Field = " << result.second.first << " Parameter = " << result.second.second << std::endl;
	}
}

// Function to search member files for number or string - print id, event name and type, file name, number of times search parameter occurs
void Search::searchFilesFor(std::string search_parameter){

	// Create vector of pairs of shared pointer to Event and int
	std::vector<std::pair<std::shared_ptr<Event>, int>> results;
	// Loop through events
	for (auto event : _events){
		// Get file and search for keyword
		int num_matches = (event.second->getFile()).searchFile(search_parameter);
		// If the number != 0 push back to the vector
		if (num_matches != 0) results.push_back(std::make_pair(event.second, num_matches));
	}
	// Print the results
	std::cout << "File Search Results:" << std::endl;
	for (auto result : results){
		std::cout << "ID: " << result.first->getId() << " " << result.first->getType() << " ("
			<< result.first->getName() << ")" << std::endl
			<< "File = " << (result.first->getFile()).getName() << ", Search parameter = " 
			<< search_parameter << ", Number of matches = " << result.second << std::endl;
	}
}

// Accessor function for container of searched results
std::vector<std::pair<std::shared_ptr<Event>, std::pair<std::string, std::string>>> Search::getResults(){
	return _search_results;
}