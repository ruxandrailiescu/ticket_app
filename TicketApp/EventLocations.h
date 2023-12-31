#ifndef EVENTLOCATIONS_H
#define EVENTLOCATIONS_H

#include "Exceptions.h"
#include "UtilTickets.h"
#include<iostream>
using namespace std;
using namespace Exceptions;

class EventLocations
{
	string location;
	string address;
	string* availableSeats;
	int noAvailableSeats;
	int maxNoSeats;

	static int NO_LOCATIONS;
	static EventLocations* eventLocations;
public:
	static void addEventLocation(const EventLocations& l);
	EventLocations();
	EventLocations(string _location, string _address, int _maxNoSeats);
	EventLocations(string _location, string _address, const string* _availableSeats, int _noAvailableSeats, int _maxNoSeats);
	EventLocations(const EventLocations& l);
	string getLocationAddress();
	string* getAvailableSeats();
	int getMaxNoSeats();
	EventLocations& operator=(const EventLocations& l);
	friend ostream& operator<<(ostream& out, const EventLocations& l);
	explicit operator int();
	bool operator==(const EventLocations& l);
	friend void operator>>(istream& in, EventLocations& l);
	~EventLocations();
	
protected:
	void setLocationAddress(string _location, string _address);
	void setAvailableSeats(const string* _availableSeats, int _noAvailableSeats);
	void setMaxNoSeats(int _maxNoSeats);
	bool validateSeats(const string* _availableSeats, int _noAvailableSeats); 
};

#endif