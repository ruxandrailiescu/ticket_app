#include "EventLocations.h"

int EventLocations::NO_LOCATIONS = 0;
EventLocations* EventLocations::eventLocations = nullptr;

void EventLocations::addEventLocation(const EventLocations& l) {
	EventLocations::NO_LOCATIONS++;
	EventLocations* temp = new EventLocations[EventLocations::NO_LOCATIONS];

	if (EventLocations::eventLocations != nullptr) {
		for (int i = 0; i < EventLocations::NO_LOCATIONS - 1; i++)
			temp[i] = EventLocations::eventLocations[i];
	}

	temp[EventLocations::NO_LOCATIONS - 1] = l;
	if (EventLocations::eventLocations != nullptr)
		delete[] EventLocations::eventLocations;

	EventLocations::eventLocations = new EventLocations[EventLocations::NO_LOCATIONS];
	for (int i = 0; i < EventLocations::NO_LOCATIONS; i++)
		EventLocations::eventLocations[i] = temp[i];
}

void EventLocations::serialize(ofstream& file) {
	// write location
	UtilTickets::serializeString(this->location, file);
	
	// write address
	UtilTickets::serializeString(this->address, file);
	
	// write available seats
	file.write((char*)&this->noAvailableSeats, sizeof(int));
	for (int i = 0; i < this->noAvailableSeats; i++) {
		UtilTickets::serializeString(this->availableSeats[i], file);
	}

	// write max no of seats
	file.write((char*)&this->maxNoSeats, sizeof(int));
}

void EventLocations::deserialize(ifstream& file) {
	// for location attribute of Event class
	// string location
	this->location = UtilTickets::deserializeString(file);

	// string address
	this->address = UtilTickets::deserializeString(file);

	// int noAvailableSeats
	// int maxNoSeats
	file.read((char*)&this->noAvailableSeats, sizeof(int));
	
	// string* availableSeats
	for (int i = 0; i < this->noAvailableSeats; i++) {
		this->availableSeats[i] = UtilTickets::deserializeString(file);
	}
	
	file.read((char*)&this->maxNoSeats, sizeof(int));
}

void operator>>(istream& in, EventLocations& l) {
	cout << endl << "Location: ";
	char buffer[256];
	in.clear();
	in.getline(buffer, 256);

	cout << endl << "Address: ";
	char buffer1[256];
	in.getline(buffer1, 256);
	l.setLocationAddress(buffer, buffer1);

	int _maxNoSeats;
	cout << endl << "Maximum number of seats: ";
	in >> _maxNoSeats;
	l.setMaxNoSeats(_maxNoSeats);

	int _noAvailableSeats;
	cout << endl << "Number of available seats: ";
	cin >> _noAvailableSeats;

	string* temp = new string[_noAvailableSeats];
	for (int i = 0; i < _noAvailableSeats; i++) {
		cout << endl << "Enter seat " << i + 1 << ": ";
		cin >> temp[i];
	}
	l.setAvailableSeats(temp, _noAvailableSeats);
}

EventLocations::EventLocations() {
	this->location = "";
	this->address = "";
	this->availableSeats = nullptr;
	this->noAvailableSeats = 0;
	this->maxNoSeats = 0;

	//EventLocations::NO_LOCATIONS++;
}

EventLocations::EventLocations(string _location, string _address, int _maxNoSeats) {
	this->setLocationAddress(_location, _address);
	this->setMaxNoSeats(_maxNoSeats);
}

EventLocations::EventLocations(string _location, string _address, const string* _availableSeats, int _noAvailableSeats, int _maxNoSeats) {

	this->setLocationAddress(_location, _address);
	this->setAvailableSeats(_availableSeats, _noAvailableSeats);
	this->setMaxNoSeats(_maxNoSeats);

	//EventLocations::NO_LOCATIONS++;

}

EventLocations::EventLocations(const EventLocations& l) :EventLocations(l.location, l.address, l.availableSeats, l.noAvailableSeats, l.maxNoSeats) {}

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
		//if (this->availableSeats != nullptr)
		//	delete[] this->availableSeats;

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

	//EventLocations::NO_LOCATIONS--;
}
