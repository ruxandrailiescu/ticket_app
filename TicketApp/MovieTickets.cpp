#include "MovieTickets.h"
#include "UtilTickets.h"

#include <iostream>
#include <string>
#include <cctype>


int MovieTickets::NO_TICKETS = 0;
int MovieTickets::ID_COUNTER = 0;		// random generation (?)


// Constructors implementation
MovieTickets::MovieTickets(int _id, const char* _movieName, const char* _theaterName, const char* _seatNumber, const char* _time, const char* _date, double _price, TicketsType _type) : id(++ID_COUNTER) {

	this->setMovieName(_movieName);
	this->setTheaterName(_theaterName);
	this->setSeatNumber(_seatNumber);
	this->setTime(_time);
	this->setDate(_date);
	this->setPrice(_price);
	this->setType(_type);

	// 10% discount for students
	if (UtilTickets::isStudent) {
		this->price = _price * 0.9;
	}

	// 20% increase for vip
	if (UtilTickets::isVip) {
		this->price = _price * 1.2;
	}

	MovieTickets::NO_TICKETS++;
}

MovieTickets::MovieTickets() :id(++ID_COUNTER) {

}

// Copy constructor implementation
MovieTickets::MovieTickets(const MovieTickets& t) :
	MovieTickets(++ID_COUNTER, t.movieName, t.theaterName, t.seatNumber, t.time, t.date, t.price, t.type) {

}


// Getters implementation
int MovieTickets::getNoTickets() { return MovieTickets::NO_TICKETS; }
int MovieTickets::getIdCounter() { return MovieTickets::ID_COUNTER; }

int MovieTickets::getId() { return this->id; }
const char* MovieTickets::getSeatNumber() { return this->seatNumber; }		// compare to getTime, getDate (which is better?)
double MovieTickets::getPrice() { return this->price; }
TicketsType MovieTickets::getType() { return this->type; }

char* MovieTickets::getMovieName() {

	return UtilTickets::copyString(this->movieName);
}

char* MovieTickets::getTheaterName() {

	return UtilTickets::copyString(this->theaterName);
}

char* MovieTickets::getTime() {

	return UtilTickets::copyString(this->time);		// created dynamically-allocated copy of this->time (which is static)
}

char* MovieTickets::getDate() {

	return UtilTickets::copyString(this->date);		// created dynamically-allocated copy of this->time (which is static)
}


// Setters implementation
void MovieTickets::setMovieName(const char* _movieName) {				// handle whitespace characters

	if (!UtilTickets::validateString(std::string(_movieName))) {

		std::cout << std::endl << "Invalid movie name." << std::endl;
		return;
	}
	else {

		UtilTickets::setString(this->movieName, _movieName);
	}
}

void MovieTickets::setTheaterName(const char* _theaterName) {				// handle whitespace characters

	if (!UtilTickets::validateString(std::string(_theaterName))) {

		std::cout << std::endl << "Invalid theater name." << std::endl;
		return;
	}
	else {

		UtilTickets::setString(this->theaterName, _theaterName);
	}
}

void MovieTickets::setSeatNumber(const char* _seatNumber) {		// test			regex for seat numbers - compare to capacity (columns, rows)

	// Seat numbers should be of the form: 'A10'
	if (_seatNumber[0] == '\0') {
		std::cerr << std::endl << "Error: Empty string." << std::endl;
		return;
	}

	if ((!std::isalpha(_seatNumber[0])) || (!std::isupper(_seatNumber[0]))) {
		std::cerr << std::endl << "Error: Does not begin with an uppercase letter." << std::endl;
		return;
	}

	for (int i = 1; i <= 2; i++) {
		if (!std::isdigit(_seatNumber[i])) {
			std::cerr << std::endl << "Error: Characters following the uppercase letter are not digits." << std::endl;
			return;
		}
	}

	strcpy_s(this->seatNumber, sizeof(this->seatNumber), _seatNumber);
//	strcpy_s(this->seatNumber, strlen(_seatNumber), _seatNumber);
	this->seatNumber[3] = '\0';
}

void MovieTickets::setTime(const char* _time) {

	if (UtilTickets::validateTime) {
		
		strcpy_s(this->time, sizeof(this->time), _time);
//		strcpy_s(this->time, strlen(_time), _time);
		this->time[5] = '\0';
	}
	else {

		std::cout << std::endl << "Invalid time format." << std::endl;
	}
}

void MovieTickets::setDate(const char* _date) {

	if (UtilTickets::validateDate) {

		strcpy_s(this->date, sizeof(this->date), _date);
//		strcpy_s(this->date, strlen(_date), _date);
		this->date[10] = '\0';
	}
	else {

		std::cout << std::endl << "Invalid date format." << std::endl;
	}
}

void MovieTickets::setPrice(const double _price) {

	if (_price > 0 && _price < PRICE_MAX) {
		this->price = _price;
	}
}

void MovieTickets::setType(const TicketsType _type) {

	if (_type == TicketsType::NORMAL || _type == TicketsType::STUDENT || _type == TicketsType::VIP) {
		this->type = _type;
	}
}


// Destructor implementation
MovieTickets::~MovieTickets() {

	if (this->movieName != nullptr) {
		delete[] this->movieName;
	}
	
	if (this->theaterName != nullptr) {
		delete[] this->theaterName;
	}
	
	MovieTickets::NO_TICKETS--;
}

std::ostream& operator<<(std::ostream& out, const TicketsType& _type) {

	switch (_type) {
	case TicketsType::NORMAL:
		out << "NORMAL";
		break;
	case TicketsType::VIP:
		out << "VIP";
		break;
	case TicketsType::STUDENT:
		out << "STUDENT";
		break;
	default:
		out << "Invalid ticket type";
		break;
	}
	out << std::endl;

	return out;
}


// Generic methods implementation
void MovieTickets::displayTicketDetails() {

	std::cout << std::endl << this->id;
	std::cout << std::endl << this->movieName;
	std::cout << std::endl << this->theaterName;
	std::cout << std::endl << this->seatNumber;
	std::cout << std::endl << this->type;
	std::cout << std::endl << this->price;
	std::cout << std::endl << this->date;
	std::cout << std::endl << this->time;

}

