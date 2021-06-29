#ifndef DATETIME_H
#define DATETIME_H

#include<iostream>
#include<iomanip>
#include<ctime>
#include<sstream>

using namespace std;

class DateAndTime
{
	// Friends of class output stream and input stream
	friend ostream & operator<<(ostream &os, const DateAndTime &DT);
	friend istream & operator>>(istream &is, DateAndTime &DT);

	// Friends for comparison
	friend bool operator>(const DateAndTime &DT1, const DateAndTime &DT2);
	friend bool operator<(const DateAndTime &DT1, const DateAndTime &DT2);

	// Compare just the date and ignore the time
	friend bool operator==(const DateAndTime &DT1, const DateAndTime &DT2);

	// Comparison functions to avoid breaking the compilation
	friend bool operator==(const std::string &S, const DateAndTime &DT) { return false; }
	friend bool operator==(const DateAndTime &DT, const std::string &S) { return false; }
	friend bool operator==(const int &I, const DateAndTime &DT) { return false; }
	friend bool operator==(const DateAndTime &DT, const int &I) { return false; }

protected:
	int _day, _month, _year, _hour, _minutes;

public:
	// Default constructor
	DateAndTime(){ _day = 1; _month = 1; _year = 2000; _hour = 0; _minutes = 0; }
	// Parameterised constructor
	DateAndTime(int dayin, int monthin, int yearin, int hourin, int minin);
	// Default destructor
	~DateAndTime(){}
	
	// Copy constructors are sufficient
  DateAndTime(const DateAndTime &DT);
  DateAndTime &operator=(const DateAndTime &DT);
	// Move constructor and move assignment
	DateAndTime(DateAndTime&&);
	DateAndTime& operator=(DateAndTime&&);
	
	// Function to set both date and time
	void set(int dayin, int monthin, int yearin, int hourin, int minin);
	// Function to set date
	void setDate(int dayin, int monthin, int yearin);
	// Function to set time
	void setTime(int hourin, int minin);

	// Accessor functions
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	int getHour() const;
	int getMinutes() const;

	// Functions to calculate the time in seconds between two dates and the time until
	double timeBetween(const DateAndTime &DT) const;
	
	string makeString() const;

};

#endif
