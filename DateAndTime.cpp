#include "DateAndTime.h"

// Function to validate date input
bool checkDate(int day, int month, int year) {

	// Check years, months and days are sensible
	if (!(year >= 2000 && year <= 2050)) { std::cout << "WARNING: Year must be between 2000 and 2050" << std::endl; return false; }
	if (!(month >= 1 && month <= 12)) { std::cout << "WARNING: Month must be between 1 and 12" << std::endl; return false; }
	if (!(day >= 1 && day <= 31)) { std::cout << "WARNING: Day must be between 1 and 31" << std::endl; return false; }

	// Check number of days in months correct
	if ((day == 31) && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)) { std::cout << "WARNING: This month does not have 31 days" << std::endl; return false; }
	if ((day == 30) && (month == 2)) { std::cout << "WARNING: February does not have 30 days" << std::endl; return false; }

	// Check for leap years
	if ((month == 2) && (day == 29) && (year % 4 != 0)) { std::cout << "WARNING: This year is not a leap year" << std::endl; return false; }
	if ((month == 2) && (day == 29) && (year % 400 == 0)) return true;
	if ((month == 2) && (day == 29) && (year % 100 == 0)) { std::cout << "WARNING: This year is not a leap year" << std::endl; return false; }
	if ((month == 2) && (day == 29) && (year % 4 != 0)) return true;

	return true;
}

// Function to valide time input
bool checkTime(int hour, int minutes) {
	if (!(hour >= 0 && hour <= 23)) { std::cout << "WARNING: Hours must be between 0 and 23" << std::endl; return false; }
	if (!(minutes >= 0 && minutes <= 59)) { std::cout << "WARNING: Minutes must be between 0 and 59" << std::endl; return false; }
	return true;
}

// Parametrised constructor
DateAndTime::DateAndTime(int dayin, int monthin, int yearin, int hourin, int minin) {
	// Check if the date and time are valid
	if (checkDate(dayin, monthin, yearin) && checkTime(hourin, minin)){
		_day = dayin; _month = monthin; _year = yearin; _hour = hourin; _minutes = minin;
	} else {
		cerr << "Setting to default 01/01/2000 (00:00)" << endl;
		_day = 1; _month = 1; _year = 2000; _hour = 0; _minutes = 0;
	}
}

// Copy constructor
DateAndTime::DateAndTime(const DateAndTime &DT){
  _day = DT._day; _month = DT._month; _year = DT._year; _hour = DT._hour; _minutes = DT._minutes;
}

// Copy assignment
DateAndTime& DateAndTime::operator=(const DateAndTime &DT){
  _day = DT._day; _month = DT._month; _year = DT._year; _hour = DT._hour; _minutes = DT._minutes;
	return *this;
}

// Move constructor
DateAndTime::DateAndTime(DateAndTime &&DT){
	// Steal the data
	_day = DT._day; _month = DT._month; _year = DT._year; _hour = DT._hour; _minutes = DT._minutes;
	DT._day = 0; DT._month = 0; DT._year = 0; DT._hour = 0; DT._minutes = 0;
}

// Move assignment
DateAndTime& DateAndTime::operator=(DateAndTime &&DT){
	// Use swap function to steal the data
	swap(_day, DT._day); swap(_month, DT._month); swap(_year, DT._year);
	swap(_hour, DT._hour); swap(_minutes, DT._minutes);
	return *this;
}

// Function to set date and time
void DateAndTime::set(int dayin, int monthin, int yearin, int hourin, int minin) {
	// Check the date and time are valid
	if (checkDate(dayin, monthin, yearin) && checkTime(hourin, minin)){
		_day = dayin; _month = monthin; _year = yearin; _hour = hourin; _minutes = minin;
	}
	else {
		cerr << "Date and time remaining as " << *this << endl;
	}
}

// Function to set date
void DateAndTime::setDate(int dayin, int monthin, int yearin) {
	// Check the date is valid
	if (checkDate(dayin, monthin, yearin)){
		_day = dayin; _month = monthin; _year = yearin;
	}
	else {
		cerr << "Date and time remaining as " << *this << endl;
	}
}

// Function to set time
void DateAndTime::setTime(int hourin, int minin) {
	// Check the time is valid
	if (checkTime(hourin, minin)){
		_hour = hourin; _minutes = minin;
	}
	else {
		cerr << "Date and time remaining as " << *this << endl;
	}
}

// Accessor functions
int DateAndTime::getDay() const {
	return _day;
}
int DateAndTime::getMonth() const {
	return _month;
}
int DateAndTime::getYear() const {
	return _year;
}
int DateAndTime::getHour() const {
	return _hour;
}
int DateAndTime::getMinutes() const {
	return _minutes;
}

// Function to return the difference between dates in seconds
double DateAndTime::timeBetween(const DateAndTime &DT) const {
	struct tm tm1 = { 0, _minutes, _hour, _day, _month - 1, _year - 1900 };
	struct tm tm2 = { 0, DT._minutes, DT._hour, DT._day, DT._month - 1, DT._year - 1900 };
	time_t time1 = mktime(&tm1);
	time_t time2 = mktime(&tm2);
	return difftime(time2, time1);
}

// Convert to a string
string DateAndTime::makeString() const{
	ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << _day << "/"
		<< std::setw(2) << std::setfill('0') << _month << "/"
		<< _year << " ("
		<< std::setw(2) << std::setfill('0') << _hour << ":"
		<< std::setw(2) << std::setfill('0') << _minutes << ")";
	return oss.str();
}

// Output stream friend function format day/month/year (hours:minutes)
ostream & operator<<(ostream &os, const DateAndTime &DT) {
	os << std::setw(2) << std::setfill('0') << DT._day << "/" 
		<< std::setw(2) << std::setfill('0') << DT._month << "/" 
		<< DT._year << " (" 
		<< std::setw(2) << std::setfill('0') << DT._hour << ":" 
		<< std::setw(2) << std::setfill('0') << DT._minutes << ")";
	return os;
}

// Input stream friend function
istream & operator>>(istream &is, DateAndTime &DT) {
	char s1,s2,ob,c,cb;
	int dayin, monthin, yearin, hourin, minin;
	is >> dayin >> s1 >> monthin >> s2 >> yearin >> ob >> hourin >> c >> minin >> cb;
	DateAndTime temp(dayin, monthin, yearin, hourin, minin);
	DT = temp;
	return is;
}

// Comparison functions
bool operator>(const DateAndTime &DT1, const DateAndTime &DT2) {
	if (DT1.timeBetween(DT2) > 0) return false;
	else return true;
}

bool operator<(const DateAndTime &DT1, const DateAndTime &DT2) {
	if (DT1.timeBetween(DT2) > 0) return true;
	else return false;
}
// Just compare the date
bool operator==(const DateAndTime &DT1, const DateAndTime &DT2) {
	if (DT1._day == DT2._day&&DT1._month == DT2._month&&DT1._year == DT2._year) return true;
	else return false;
}
