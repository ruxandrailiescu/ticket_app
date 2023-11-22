#include "MovieTickets.h"
#include "UtilTickets.h"

#include <iostream>
#include <string>
#include <cctype>


int MovieTickets::NO_TICKETS = 0;
int MovieTickets::ID_COUNTER = 0;


// Constructors implementation
MovieTickets::MovieTickets(int _id, const char* _movieName, const char* _theaterName, const char* _seatNumber, const char* _time, const char* _date, const double _price, const TicketsType _type) : id(++ID_COUNTER) {

	this->setMovieName(_movieName);
	this->setTheaterName(_theaterName);
	this->setSeatNumber(_seatNumber);
	this->setTime(_time);
	this->setDate(_date);
	this->setPrice(_price);
	this->setType(_type);

	// 10% discount for students
	if (UtilTickets::isStudent(_type)) {
		this->price = _price * 0.9;
	}

	// 20% increase for vip
	if (UtilTickets::isVip(_type)) {
		this->price = _price * 1.2;
	}

	MovieTickets::NO_TICKETS++;
	
}

MovieTickets::MovieTickets(const char* _movieName, const char* _theaterName, const char* _time, const char* _date) :id(++ID_COUNTER) {

	this->setMovieName(_movieName);
	this->setTheaterName(_theaterName);
	this->setTime(_time);
	this->setDate(_date);

	MovieTickets::NO_TICKETS++;
	
}

MovieTickets::MovieTickets() :id(++ID_COUNTER) {
	
	MovieTickets::NO_TICKETS++;
	
}

// Copy constructor implementation
MovieTickets::MovieTickets(const MovieTickets& t) :
	MovieTickets(t.id, t.movieName, t.theaterName, t.seatNumber, t.time, t.date, t.price, TicketsType::NORMAL) {

	this->type = t.type;		// avoid applying discount/increase in price twice
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
void MovieTickets::setMovieName(const char* _movieName) {				

	if (!UtilTickets::validateString(std::string(_movieName))) {

		std::cout << std::endl << "Invalid movie name." << std::endl;
		return;
	}
	else {

		UtilTickets::setString(this->movieName, _movieName);
	}
}

void MovieTickets::setTheaterName(const char* _theaterName) {				

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

	if (UtilTickets::validateTime(_time)) {
		
		strcpy_s(this->time, sizeof(this->time), _time);
//		strcpy_s(this->time, strlen(_time), _time);
		this->time[5] = '\0';
	}
	else {

		std::cout << std::endl << "Invalid time format." << std::endl;
	}
}

void MovieTickets::setDate(const char* _date) {

	if (UtilTickets::validateDate(_date)) {

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

// Overloaded operators implementation
// Operator=
MovieTickets& MovieTickets::operator=(const MovieTickets& t) {

	if (this == &t) {
		return *this;
	}

	this->setMovieName(t.movieName);
	this->setTheaterName(t.theaterName);
	this->setSeatNumber(t.seatNumber);
	this->setPrice(t.price);
	this->setDate(t.date);
	this->setTime(t.time);
	this->setType(t.type);

	return *this;
}

// Operator!
bool MovieTickets::operator!() {

	// return true if seat has not been chosen
	if (this->seatNumber == nullptr || strlen(this->seatNumber) == 0) {
		return true;
	}
	return false;
}

// Operator+
MovieTickets MovieTickets::operator+(int val) {

	MovieTickets copy = *this;
	copy.price += val;
	return copy;

}

// Operator-
MovieTickets MovieTickets::operator-(int val) {

	MovieTickets copy = *this;
	copy.price -= val;
	return copy;
}

// Operator==
bool MovieTickets::operator==(const MovieTickets& t) {

	if (this == &t) {
		return true;
	}

	// see if tickets are the same - movie, theater, seat number, date, time
	// throw exception - double-booking not allowed
	if ((this->movieName == t.movieName) && (this->theaterName == t.theaterName) &&
		(this->seatNumber == t.seatNumber) && (this->date == t.date) && (this->time == t.time)) {
		return true;
		// ... exception
	}

	return false;
}

// Operator>
bool MovieTickets::operator>(const MovieTickets& t) {

	if ((this == &t) || (this->price <= t.price)) {
		return false;
	}

	return true;
}

// Operator<
bool MovieTickets::operator<(const MovieTickets& t) {

	if ((this == &t) || (this->price >= t.price)) {
		return false;
	}

	return true;
}

// Cast operator to string
MovieTickets::operator std::string() {

	std::string strResult = std::to_string(this->id);

	if ((this->movieName != nullptr) && (this->theaterName != nullptr)) {		// verification works with && because in order to instantiate
																				// MovieTickets obj, either use default constr (movieName AND theaterName == nullptr)
		strResult += " " + std::string(this->movieName) +						// or must pass both
			" " + std::string(this->theaterName) +	
			" " + this->seatNumber + " " + this->date + " " + this->time;
	}
	
	return strResult;
}

// Pre-increment the price of the ticket by 1
MovieTickets MovieTickets::operator++() {

	this->price++;
	return *this;
}

// Post-increment the price of the ticket by 1
MovieTickets MovieTickets::operator++(int) {

	MovieTickets copy = *this;
	this->price++;
	return copy;
}


std::ostream& operator<<(std::ostream& out, MovieTickets& t) {

	out << std::endl << "Movie name: " << t.getMovieName();
	out << std::endl << "Theater name: " << t.getTheaterName();
	out << std::endl << "Seat number: " << t.getSeatNumber();
	out << std::endl << "Date: " << t.getDate();
	out << std::endl << "Time: " << t.getTime();
	out << std::endl << "Ticket type: " << t.getType();
	out << std::endl << "Price: " << t.getPrice();
	out << std::endl;

	return out;

	// messages to alert user that certain attributes are not assigned - default constr and other
}

std::istream& operator>>(std::istream& in, MovieTickets& t) {

	// create input validation method and call it here 
	// (to avoid making istream a friend)

	t.inputValidation();
	return in;
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

	return out;
}


// Generic methods implementation
void MovieTickets::displayTicketDetails() {

	std::cout << std::endl << "Ticket ID: " << this->id;
	std::cout << std::endl << "Movie name: " << this->movieName;
	std::cout << std::endl << "Theater name: " << this->theaterName;
	std::cout << std::endl << "Seat number: " << this->seatNumber;
	std::cout << std::endl << "Ticket type: " << this->type;
	std::cout << std::endl << "Ticket price: " << this->price;
	std::cout << std::endl << "Date: " << this->date;
	std::cout << std::endl << "Time: " << this->time;

}

bool MovieTickets::inputString(std::string& s, const char* item) {

	std::cout << std::endl << "Enter " << item << " : ";

	if (!std::getline(std::cin, s)) {

		std::cerr << std::endl << "Invalid input/Error occurred.";
		return false;
	}
	return true;
}

void MovieTickets::inputValidation() {

	// if obj instantiated with one of the constructors
	// having less parameters than member variables of class

	std::string t_movieName;
	std::string t_theaterName;
	std::string t_seatNumber;
	std::string t_time;
	std::string t_date;
	double t_price = 0;

	// obj will always have an id
	if (this->movieName == nullptr) {
		
		/*std::cin.ignore();*/
		if (!inputString(t_movieName, "movie")) {
			return;
		}
	}

	if (this->theaterName == nullptr) {

		if (!inputString(t_theaterName, "theater")) {
			return;
		}
	}

	if (this->seatNumber == nullptr || strlen(this->seatNumber) == 0) {

		if (!inputString(t_seatNumber, "seat number")) {
			return;
		}
	}

	if (strlen(this->time) == 0) {

		if (!inputString(t_time, "time")) {
			return;
		}
	}
	
	if (strlen(this->date) == 0) {

		if (!inputString(t_date, "date")) {
			return;
		}
	}

	if (this->price == 0) {

		std::cout << std::endl << "Enter price: ";

		if (!(std::cin >> t_price)) {
			
			std::cerr << std::endl << "Invalid input/Error occurred.";
			return;
		}
	}

	// (!!!) type is NORMAL by default, handle

	this->setMovieName(t_movieName.c_str());
	this->setTheaterName(t_theaterName.c_str());
	this->setSeatNumber(t_seatNumber.c_str());
	this->setTime(t_time.c_str());
	this->setDate(t_date.c_str());
	this->setPrice(t_price);

}