#include "Event.h"

void Event::setId(string _id) {
	if (UtilTickets::validateString(_id))
		this->id = _id;
}

void Event::setName(char* _name) {
	UtilTickets::setString(this->name, _name);
}

Event::Event() {
	this->id = "";
	this->name = nullptr;
}

Event::Event(string _id, char* _name, EventLocations _location) : location(_location) {
	this->setId(_id);
	this->setName(_name);
}

Event::Event(const Event& e) :Event(e.id, e.name, e.location) {}

Event& Event::operator=(const Event& e) {
	if (this == &e)
		return *this;
	this->setId(e.id);
	this->setName(e.name);
	this->location = e.location;
}

string Event::getId() { return this->id; }

EventLocations Event::getLocation() { return this->location; }

char* Event::getName(){ return UtilTickets::copyString(this->name); }

bool Event::operator==(const Event& e) {
	if (this == &e)
		return true;
	if ((this->id == e.id) && (this->name == e.name) && (this->location == e.location))
		return true;
	return false;
}

ostream& operator<<(ostream& out, Event& e) {
	out << endl << "Event id: " << e.getId();
	out << endl << "Event name: " << e.getName();
	out << endl << "Event location: " << e.getLocation();
	return out;
}

Event::~Event() {
	if (this->name != nullptr)
		delete[] this->name;
}