#pragma once
#include "EventLocations.h"

class Event
{
	string id;
	char* name;
	EventLocations location;
public:
	Event();
	Event(string _id, char* _name, EventLocations _location);
	Event(const Event& e);
	Event& operator=(const Event& e);
	EventLocations getLocation();
	char* getName();
	string getId();
	void setId(string _id);
	void setName(char* _name);
	~Event();
};