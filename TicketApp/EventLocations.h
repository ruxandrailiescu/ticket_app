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

public:
	EventLocations();
	EventLocations(string _location, string _address, const string* _availableSeats, int _noAvailableSeats, int _maxNoSeats);
	EventLocations(const EventLocations& l);
	string getLocationAddress();
	string* getAvailableSeats();
	int getMaxNoSeats();
	EventLocations& operator=(const EventLocations& l);
	friend ostream& operator<<(ostream& out, const EventLocations& l);
	explicit operator int();
	~EventLocations();
	
protected:
	void setLocationAddress(string _location, string _address);
	void setAvailableSeats(const string* _availableSeats, int _noAvailableSeats);
	void setMaxNoSeats(int _maxNoSeats);
	bool validateSeats(const string* _availableSeats, int _noAvailableSeats);
};

#endif