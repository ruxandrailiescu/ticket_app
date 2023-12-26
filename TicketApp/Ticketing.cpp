#include "Ticketing.h"

int Ticketing::NO_TICKETS = 0;
int Ticketing::ID_COUNTER = 0;

void Ticketing::setSeatNumber(const char* _seatNumber) {

	// Seat numbers should be of the form: 'A10'
	if (_seatNumber[0] == '\0') {
		throw InvalidInputException("Empty string");
	}

	if ((!isalpha(_seatNumber[0])) || (!isupper(_seatNumber[0]))) {
		throw InvalidInputException("Seat number: rows should begin with an uppercase letter");
	}

	for (int i = 1; i <= 2; i++) {
		if (!isdigit(_seatNumber[i])) {
			throw InvalidInputException("Seat numbers contain 2 digits");
		}
	}

	strcpy_s(this->seatNumber, sizeof(this->seatNumber), _seatNumber);
	this->seatNumber[3] = '\0';
}

void Ticketing::setTime(const char* _time) {

	if (UtilTickets::validateTime(_time)) {

		strcpy_s(this->time, sizeof(this->time), _time);
		this->time[5] = '\0';
	}
	else {
		throw InvalidInputException("Invalid time format");
	}
}

void Ticketing::setDate(const char* _date) {

	if (UtilTickets::validateDate(_date)) {

		strcpy_s(this->date, sizeof(this->date), _date);
		this->date[10] = '\0';
	}
	else {
		throw InvalidInputException("Invalid date format");
	}
}

void Ticketing::setPrice(double _price) {

	if (_price > 0 && _price < PRICE_MAX) {
		this->price = _price;
	}
	else
		throw InvalidInputException("Price should be greater than 0 and in valid range.");
}

Ticketing::Ticketing() : id(++ID_COUNTER) {
	Ticketing::NO_TICKETS++;
}

Ticketing::Ticketing(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price) : id(++ID_COUNTER) {
	this->event = _event;
	this->setSeatNumber(_seatNumber);
	this->setTime(_time);
	this->setDate(_date);
	this->setPrice(_price);
	Ticketing::NO_TICKETS++;
}

Ticketing::Ticketing(const Ticketing& t)
	: Ticketing(t.event, t.seatNumber, t.time, t.date, t.price) {}

Ticketing& Ticketing::operator=(const Ticketing& t) {
	if (this == &t)
		return *this;
	this->event = t.event;
	this->setSeatNumber(t.seatNumber);
	this->setTime(t.time);
	this->setDate(t.date);
	this->setPrice(t.price);
	return *this;
}

Event Ticketing::getEvent() { return this->event; }
int Ticketing::getId() { return this->id; }
int Ticketing::getNoTickets() { return Ticketing::NO_TICKETS; }
int Ticketing::getIdCounter() { return Ticketing::ID_COUNTER; }
char* Ticketing::getSeatNumber() { return UtilTickets::copyString(this->seatNumber); }
char* Ticketing::getTime() { return UtilTickets::copyString(this->time); }
char* Ticketing::getDate() { return UtilTickets::copyString(this->date); }
double Ticketing::getPrice() { return this->price; }

bool Ticketing::operator!() {

	// return true if seat has not been chosen
	if (this->seatNumber == nullptr || strlen(this->seatNumber) == 0) {
		return true;
	}
	return false;
}

bool Ticketing::operator==(const Ticketing& t) {

	if (this == &t) {
		return true;
	}

	// see if tickets are the same - event, seat number, date, time
	if ((this->event == t.event) && (this->seatNumber == t.seatNumber) 
		&& (this->date == t.date) && (this->time == t.time)) {
		return true;
	}
	return false;
}

void Ticketing::displayTicketDetails() {
	cout << endl << "Event details: " << this->event;
	cout << endl << "Id: " << this->id;
	cout << endl << "Seat number: " << this->seatNumber;
	cout << endl << "Date: " << this->date;
	cout << endl << "Time: " << this->time;
	cout << endl << "Ticket price: " << this->price;
}

Ticketing::~Ticketing() {
	Ticketing::NO_TICKETS--;
}

void Normal::setPrice(double _price) {
	Ticketing::setPrice(_price);
}

Normal::Normal() {}

Normal::Normal(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price)
	: Ticketing(_event, _seatNumber, _time, _date, _price) {}

void Normal::displayTicketDetails() {
	cout << endl << "-----This is a Normal ticket-----";
	Ticketing::displayTicketDetails();
}

void Vip::setBonusPoints(int _bonusPoints) {
	if ((_bonusPoints > 0) && (_bonusPoints % 10 == 0))
		this->bonusPoints = _bonusPoints;
	else
		throw InvalidInputException("Bonus points should be greater than 0 and a multiple of 10.");
}

void Vip::setPrice(double _price) {
	Ticketing::setPrice(_price * 1.2);
}

Vip::Vip() {
	this->bonusPoints = 0;
}

Vip::Vip(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price, int _bonusPoints)
	: Ticketing(_event, _seatNumber, _time, _date, _price) {
	this->setBonusPoints(_bonusPoints);
}

int Vip::getBonus() { return this->bonusPoints; }

void Vip::displayTicketDetails() {
	cout << endl << "-----This is a Vip ticket-----";
	Ticketing::displayTicketDetails();
	cout << endl << "Bonus points: " << this->bonusPoints;
}

void Student::setDiscount(int _discount) {
	if ((_discount > 0) && (_discount % 10 == 0))
		this->discount = _discount;
	else
		throw InvalidInputException("Discount should be greater than 0 and a multiple of 10, as percentage.");
}

void Student::setPrice(double _price) {
	if (this->discount > 0)
		Ticketing::setPrice(_price * (1 - this->discount / 100));
	else
		Ticketing::setPrice(_price);
}

Student::Student() {
	this->discount = 0;
}

Student::Student(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price, int _discount)
	: Ticketing(_event, _seatNumber, _time, _date, _price) {
	this->setDiscount(_discount);
}

int Student::getDiscount() { return this->discount; }

void Student::displayTicketDetails() {
	cout << endl << "-----This is a Student ticket-----";
	Ticketing::displayTicketDetails();
	cout << endl << "Discount: " << this->discount;
}