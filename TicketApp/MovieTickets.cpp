#include "MovieTickets.h"
#include "UtilTickets.h"

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
const char* MovieTickets::getSeatNumber() { return this->seatNumber; }
double MovieTickets::getPrice() { return this->price; }
TicketsType MovieTickets::getType() { return this->type; }

char* MovieTickets::getMovieName() {

	return UtilTickets::copyString(this->movieName);
}

char* MovieTickets::getTheaterName() {

	return UtilTickets::copyString(this->theaterName);
}

char* MovieTickets::getTime() {

	return UtilTickets::copyString(this->time);
}

char* MovieTickets::getDate() {

	return UtilTickets::copyString(this->date);
}


// Setters implementation
void MovieTickets::setMovieName(const char* _movieName) {				

	if (!UtilTickets::validateString(string(_movieName))) {

		throw InvalidInputException("Invalid movie name");
	}
	else {

		UtilTickets::setString(this->movieName, _movieName);
	}
}

void MovieTickets::setTheaterName(const char* _theaterName) {				

	if (!UtilTickets::validateString(string(_theaterName))) {

		throw InvalidInputException("Invalid theater name");
	}
	else {

		UtilTickets::setString(this->theaterName, _theaterName);
	}
}

void MovieTickets::setSeatNumber(const char* _seatNumber) {		// regex for seat numbers - compare to capacity (columns, rows)

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

void MovieTickets::setTime(const char* _time) {

	if (UtilTickets::validateTime(_time)) {
		
		strcpy_s(this->time, sizeof(this->time), _time);
		this->time[5] = '\0';
	}
	else {
		throw InvalidInputException("Invalid time format");
	}
}

void MovieTickets::setDate(const char* _date) {

	if (UtilTickets::validateDate(_date)) {

		strcpy_s(this->date, sizeof(this->date), _date);
		this->date[10] = '\0';
	}
	else {
		throw InvalidInputException("Invalid date format");
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
	if ((this->movieName == t.movieName) && (this->theaterName == t.theaterName) &&
		(this->seatNumber == t.seatNumber) && (this->date == t.date) && (this->time == t.time)) {
		return true;
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
MovieTickets::operator string() {

	string strResult = to_string(this->id);

	if ((this->movieName != nullptr) && (this->theaterName != nullptr)) {		// verification works with && because in order to instantiate
																				// MovieTickets obj, either use default constr (movieName AND theaterName == nullptr)
		strResult += " " + string(this->movieName) +							// or must pass both
			" " + string(this->theaterName) +	
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


ostream& operator<<(ostream& out, MovieTickets& t) {

	out << endl << "Movie name: " << t.getMovieName();
	out << endl << "Theater name: " << t.getTheaterName();
	out << endl << "Seat number: " << t.getSeatNumber();
	out << endl << "Date: " << t.getDate();
	out << endl << "Time: " << t.getTime();
	out << endl << "Ticket type: " << t.getType();
	out << endl << "Price: " << t.getPrice();
	out << endl;

	return out;

	// messages to alert user that certain attributes are not assigned - default constr and other
}

istream& operator>>(istream& in, MovieTickets& t) {

	// create input validation method and call it here 
	// (to avoid making istream a friend)

	t.inputValidation();
	return in;
}

ostream& operator<<(ostream& out, const TicketsType& _type) {

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

	cout << endl << "Ticket ID: " << this->id;

	if (this->movieName == nullptr)
		throw ReadAccessViolationException("Movie name: cannot read from memory at this location.");
	else {
		cout << endl << "Movie name: " << this->movieName;
	}

	if (this->theaterName == nullptr)
		throw ReadAccessViolationException("Theater name: cannot read from memory at this location.");
	else {
		cout << endl << "Theater name: " << this->theaterName;
	}
	
	cout << endl << "Seat number: " << this->seatNumber;
	cout << endl << "Ticket type: " << this->type;
	cout << endl << "Ticket price: " << this->price;
	cout << endl << "Date: " << this->date;
	cout << endl << "Time: " << this->time;

}

bool MovieTickets::inputString(string& s, const char* item) {

	cout << endl << "Enter " << item << " : ";

	if (!getline(cin, s)) {
		throw InvalidInputException("Invalid input");
	}
	return true;
}

void MovieTickets::inputValidation() {

	// if obj instantiated with one of the constructors
	// having less parameters than member variables of class

	string t_movieName;
	string t_theaterName;
	string t_seatNumber;
	string t_time;
	string t_date;
	double t_price = 0;

	// obj will always have an id
	if (this->movieName == nullptr) {
		
		//cin.ignore();
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

		cout << endl << "Enter price: ";

		if (!(cin >> t_price)) {
			throw InvalidInputException("Invalid price");
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