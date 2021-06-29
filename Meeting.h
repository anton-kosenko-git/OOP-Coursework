#ifndef MEETING_H
#define MEETING_H

#include"Event.h"

// Derived class for Meeting
class Meeting : public Event
{
	// Friend functions for overloading >> and <<
	friend ostream & operator<<(ostream &os, const Meeting &M);
	friend istream & operator>>(istream &is, Meeting &M);

protected:
	// Location of meeting, the contractor and group it is associated with
	std::string _location, _group, _contractor;
	// Number of attendees
	float _price;
	// Notes for the meeting
	TextFile _notes;

public:
	// Default constructor
	Meeting();
	// Parameterised constructor
	Meeting(std::string namein, std::string locationin, std::string contractorin, std::string groupin, float pricein);
	// Destructor
	~Meeting(){}

	// Overridden create file function
	void createFile(std::string file_name);
	// Overridden delete file function
	void deleteFile();
	// Overridden save function - using overloaded >>
	void save(std::string file_name);
	void print();

	// Accessors and mutators for location, project, number of attendees and minutes
	std::string getLocation() const;
	void setLocation(std::string location);
	std::string getGroup() const;
	void setGroup(std::string group);
	std::string getContractor() const;
	void setContractor(std::string contractor);
	float getPrice() const;
	void setPrice(float price);
	TextFile getFile() const;
	void setNotes(string notes);

	// Functions to make searching easier
	int getNumber() const;

	// Mutators for easier editing
	void setNumber(int);
	void setSolved(bool);


};// End of Meeting class

#endif