#include "EventLocations.h"

int EventLocations::NO_LOCATIONS = 0;

EventLocations::EventLocations() {
	this->location = "";
	this->address = "";
	this->availableSeats = nullptr;
	this->noAvailableSeats = 0;
	this->maxNoSeats = 0;

	EventLocations::NO_LOCATIONS++;
}

EventLocations::EventLocations(string _location, string _address, int _maxNoSeats) {
	this->setLocationAddress(_location, _address);
	this->setMaxNoSeats(_maxNoSeats);

	EventLocations::NO_LOCATIONS++;
}

EventLocations::EventLocations(string _location, string _address, const string* _availableSeats, int _noAvailableSeats, int _maxNoSeats) {

	this->setLocationAddress(_location, _address);
	this->setAvailableSeats(_availableSeats, _noAvailableSeats);
	this->setMaxNoSeats(_maxNoSeats);

	EventLocations::NO_LOCATIONS++;

}

EventLocations::EventLocations(const EventLocations& l):EventLocations(l.location, l.address, l.availableSeats, l.noAvailableSeats, l.maxNoSeats){}

EventLocations& EventLocations::operator=(const EventLocations& l) {

	if (this == &l)
		return *this;

	this->setLocationAddress(l.location, l.address);
	this->setAvailableSeats(l.availableSeats, l.noAvailableSeats);
	this->setMaxNoSeats(l.maxNoSeats);

	return *this;
}

string EventLocations::getLocationAddress() { return this->location + ", " + this->address; }
int EventLocations::getMaxNoSeats() { return this->maxNoSeats; }

string* EventLocations::getAvailableSeats() {

	if (this->availableSeats == nullptr)
		return nullptr;

	string* copy = new string[this->noAvailableSeats];
	for (int i = 0; i < this->noAvailableSeats; i++)
		copy[i] = this->availableSeats[i];
	return copy;
}

void EventLocations::setLocationAddress(string _location, string _address) {

	if (UtilTickets::validateString(_location)) {
		this->location = _location;
	}
	else {
		throw InvalidInputException("Location: Invalid input.");
	}

	if (UtilTickets::validateString(_address)) {
		this->address = _address;
	}
	else {
		throw InvalidInputException("Address: Invalid input.");
	}
}

void EventLocations::setAvailableSeats(const string* _availableSeats, int _noAvailableSeats) {

	if (!this->validateSeats(_availableSeats, _noAvailableSeats))
		throw InvalidInputException("Cannot set available seats.");

	if ((_availableSeats == nullptr) || (_noAvailableSeats <= 0)) {
		throw ReadAccessViolationException("Available seats: Cannot read from memory at this location.");
	}
	else {
		if (this->availableSeats != nullptr)
			delete[] this->availableSeats;

		this->availableSeats = new string[_noAvailableSeats];
		for (int i = 0; i < _noAvailableSeats; i++)
			this->availableSeats[i] = _availableSeats[i];
		this->noAvailableSeats = _noAvailableSeats;
	}
}

void EventLocations::setMaxNoSeats(int _maxNoSeats) {

	if (_maxNoSeats > 0)
		this->maxNoSeats = _maxNoSeats;
	else {
		throw InvalidInputException("Max no of seats: Invalid input.");
	}
}

EventLocations::operator int() { return this->noAvailableSeats; }

bool EventLocations::operator==(const EventLocations& l) {
	if (this == &l)
		return true;
	if ((this->location == l.location) && (this->address == l.address) && (this->maxNoSeats == l.maxNoSeats))
		return true;
	return false;
}

ostream& operator<<(ostream& out, const EventLocations& l) {

	out << endl << "Location: " << l.location;
	out << endl << "Address: " << l.address;
	out << endl << "Max no of seats: " << l.maxNoSeats;
	out << endl << "No of available seats: " << l.noAvailableSeats;
	out << endl << "Available seats are: " << endl;
	for (int i = 0; i < l.noAvailableSeats; i++)
		out << l.availableSeats[i] << " | ";
	return out;
}

bool EventLocations::validateSeats(const string* _availableSeats, int _noAvailableSeats) {

	for (int i = 0; i < _noAvailableSeats; i++) {
		if (_availableSeats[i].empty())
			throw InvalidInputException("Available seats: Must not be empty.");

		regex seatRegex(R"([A-Z][1-9][0-9])");
		if (!regex_match(_availableSeats[i], seatRegex))
			throw InvalidInputException("Available seats: Wrong format.");
	}
	return true;
}

EventLocations::~EventLocations() {

	if (this->availableSeats != nullptr)
		delete[] this->availableSeats;

	EventLocations::NO_LOCATIONS--;
}