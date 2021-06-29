#ifndef EVENT_H
#define EVENT_H

#include<string>
#include "dateAndTime.h"
#include "textFile.h"

using namespace std;

// Abstract base class for event
class Event
{
protected:
	// Unique identifier for event, use random number to set in constructor
	int _id;
	static int num_events;
	// Name and type of the event
	string _name, _type;
	// Start and end times/dates of event
	DateAndTime _start, _end;

public:
	// Default constructor
	Event() :_name("none"){ _id = num_events; num_events++; }
	// Parameterised constructor
	Event(string namein, string typein){ _name = namein; _type = typein; _id = num_events; num_events++; }
	// Virtual destructor
	virtual ~Event(){}

	// Virtual create file function
	virtual void createFile(string file_name) = 0;
	// Virtual delete file
	virtual void deleteFile() = 0;
	// Virtual get file function
	virtual TextFile getFile() const = 0;
	// Virtual save function
	virtual void save(string file_name) = 0;
	virtual void print() = 0;

	// Virtual accessors for easy looping through classes
	virtual int getNumber() const = 0;
	virtual float getPrice() const = 0;
	virtual string getLocation() const = 0;
	virtual string getContractor() const = 0;
	virtual string getGroup() const = 0;

	// Virtual mutators for easier editing
	virtual void setNumber(int) = 0;
	virtual void setPrice(float) = 0;
	virtual void setLocation(string) = 0;
	virtual void setContractor(string) = 0;
	virtual void setGroup(string) = 0;
	virtual void setSolved(bool) = 0;

	// Real function for time until event function
	double timeToEvent();
	void printTimeToEvent();
	double getDuration();
	void printDuration();

	// Real accessor and mutator functions for ID, name and start/end times
	int getId() const;
	std::string getName() const;
	void setName(std::string namein);
	std::string getType() const;
	DateAndTime getStart() const;
	void setStart(DateAndTime startin);
	DateAndTime getEnd() const;
	void setEnd(DateAndTime endin);

};// End of Event class

#endif