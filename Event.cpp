#include "Event.h"

// Accessor and mutator functions for data members
int Event::getId() const {
	return _id;
}
std::string Event::getName() const {
	return _name;
}
void Event::setName(std::string namein) {
	_name = namein;
}
std::string Event::getType() const {
	return _type;
}
DateAndTime Event::getStart() const {
	return _start;
}
void Event::setStart(DateAndTime startin) {
	_start = startin;
}
DateAndTime Event::getEnd() const {
	return _end;
}
void Event::setEnd(DateAndTime endin) {
	// Check that the end is sensible
	if (endin.timeBetween(_start) > 0){
		cout << "WARNING: The event cannot end before it has begun" << endl;
	}
	else {
		_end = endin;
	}
}