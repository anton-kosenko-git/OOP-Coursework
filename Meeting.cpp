#include "Meeting.h"

// Default constructor
Meeting::Meeting() : _location("unknown"), _group("unknown"), _contractor("unknown"), _price(0) { Event::_type = "Meeting"; }

// Parameterised constructor
Meeting::Meeting(std::string namein, std::string locationin, std::string contractorin, std::string groupin, float pricein) : Event(namein, "Meeting"), _location(locationin), _group(groupin), _contractor(contractorin), _price(pricein) {}

// Overridden create file function
void Meeting::createFile(std::string file_name) {
	bool overwrite_flag;
	std::string overwrite;
	// If a file already exists ask if user wants to overwrite
	if (_notes.getName() != "none"){
		while (overwrite != "y" || overwrite != "n"){
			std::cout << "Notes for this meeting already exist, overwrite? (y/n) ";
			std::cin >> overwrite;
			std::cout << std::endl;
			if (overwrite == "n") overwrite_flag = 0;
			if (overwrite == "y") overwrite_flag = 1;
		}
		// If user wants to overwrite delete old file and create a new one
		if (overwrite_flag){
			_notes.deleteFile();
			_notes.createFile(file_name);
		}
	}
	else {
		_notes.createFile(file_name);
	}
}

// Overridden delete file function
void Meeting::deleteFile() {
	if (_notes.getName() == "none"){
		std::cout << "File doesn't exist, nothing to delete" << std::endl;
	}
	else {
		_notes.deleteFile();
	}
}

// Overridden save function - using overloaded >>
void Meeting::save(std::string file_name) {
	// Check if file already exists, if it does write to the end of it
	ofstream saveFile;
	saveFile.open(file_name.c_str(),std::ios::app);
	saveFile << *this;
	saveFile.close();
}

void Meeting::print(){
	std::cout << *this;
}

// Accessors and mutators for location, project, number of attendees and minutes
std::string Meeting::getLocation() const {
	return _location;
}
void Meeting::setLocation(std::string location) {
	_location = location;
}
std::string Meeting::getGroup() const {
	return _group;
}
void Meeting::setGroup(std::string group){
	_group = group;
}
std::string Meeting::getContractor() const{
	return _contractor;
}
void Meeting::setContractor(std::string contractor){
	_contractor = contractor;
}
float Meeting::getPrice() const{
	return _price;
}
void Meeting::setPrice(float price){
	_price = price;
}
TextFile Meeting::getFile() const{
	return _notes;
}
void Meeting::setNotes(string notes){
	_notes.setName(notes);
}

// Functions to make searching easier
int Meeting::getNumber() const{ return -1; }

// Mutators for easier editing
void Meeting::setNumber(int){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Meeting::setSolved(bool){ std::cout << "WARNING: Field does not exist" << std::endl; }

// Output stream friend function for saving state
ostream & operator<<(ostream &os, const Meeting &M) {
	os << "---- Event::Meeting ----" << std::endl
		<< "Name: " << M._name << std::endl << "Location: " << M._location << std::endl
		<< "Start: " << M._start << std::endl << "End: " << M._end << std::endl
		<< "Contractor: " << M._contractor << std::endl << "Group: " << M._group << std::endl
		<< "Price: " << M._price << std::endl
		<< "Notes: " << M._notes.getName() << std::endl
		<< "------------------------" << std::endl;
	return os;
}

// Input stream friend function for loading state - not used for user input
istream & operator>>(istream &is, Meeting &M) {
	std::string ignore;
	std::string name, location, contractor, group, notes;
	DateAndTime start, end;
	float price;
	// Input matches << operator apart from the first and last lines - dealt with in load function
	getline(is, name); name.erase(0, 6);
	getline(is, location); location.erase(0, 10);
	is >> ignore >> start >> ignore >> end;
	getline(is, ignore);
	getline(is, contractor); contractor.erase(0, 12);
	getline(is, group); group.erase(0, 7);
	is >> ignore >> ignore >> ignore >> price >> ignore >> notes;
	Meeting temp(name, location, contractor, group, price);
	temp.setStart(start); temp.setEnd(end); temp.setNotes(notes);
	M = temp;
	return is;
}
