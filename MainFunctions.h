#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include "DateAndTime.h"
#include "TextFile.h"
#include "Meeting.h"
#include "Search.h"
#include <time.h>
#include<ctime>
using namespace std;

namespace mainfunc{

	// Save state
	void saveState(std::string file_name, std::unordered_map<int, std::shared_ptr<Event>> events);

	// Load state
	std::vector<std::shared_ptr<Event>> loadEvents(std::string file_name, std::vector<std::shared_ptr<Event>> events);

	// User enters new event with input checks
	std::unordered_map<int, std::shared_ptr<Event>> createNewEvent(std::unordered_map<int, std::shared_ptr<Event>> events);
	std::unordered_map<int, std::shared_ptr<Event>> createNewMeeting(std::unordered_map<int, std::shared_ptr<Event>> events);

	// User creates a search with input checks
	void searchEvents(std::unordered_map<int, std::shared_ptr<Event>> events);

}

#endif
