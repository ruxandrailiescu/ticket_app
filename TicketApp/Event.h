#pragma once
#include "EventLocations.h"
#pragma warning(disable : 4996)		// to use strcpy (binary file managed by us and verification in UtilTickets::deserialize)

class Event
{
	string id;
	char* name;
	EventLocations location;

	static Event* events;
	static int NO_EVENTS;
public:
	static void addEvent(const Event& e);
	Event();
	Event(string _id, char* _name, EventLocations _location);
	Event(const Event& e);
	Event& operator=(const Event& e);
	EventLocations getLocation();
	char* getName();
	string getId();
	void setId(string _id);
	void setName(char* _name);
	bool operator==(const Event& e);
	friend void operator>>(istream& in, Event& e);
	void serialize(ofstream& file);
	void deserialize(ifstream& file);
	~Event();
};
ostream& operator<<(ostream& out, Event& e);
