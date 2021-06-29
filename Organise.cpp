#include "Organise.h"
using namespace std;

// Function to print the map - print the id and event type and name
void Organise::printAddedEvents() const {
	std::cout << "Added Events:" << std::endl;
	// Add try catch after debugging
	for (const auto &event : _events) {
		std::cout << "ID: " << event.first << " " << event.second->getType() << " (" << event.second->getName() << ")" << std::endl;
	}
}


// Function to add event
void Organise::addEvent(std::shared_ptr<Event> &event) {
	std::pair<int, std::shared_ptr<Event>> new_entry(event->getId(), event);
	_events.insert(new_entry);
}

// Function to remove Event by id
void Organise::removeEvent(int id) {
	try{
		_events.erase(id);
	}
	catch (...) { std::cout << "WARNING: No element with ID = " << id << std::endl; }
}

// Function to add all Events - can match id's to make sure events are not added twice
void Organise::addAllEvents(std::vector<std::shared_ptr<Event>> &new_events) {
	// Add try catch after debugging
	for (auto new_event : new_events){
		_events.emplace(new_event->getId(),new_event);
	}
}

// Function to remove all Events
void Organise::removeAllEvents() {
	// Add try catch after debugging
	_events.clear();
}

std::unordered_map<int, std::shared_ptr<Event>> Organise::getEvents(){
	return _events;
}