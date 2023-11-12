#include "MovieTickets.h"

#include <iostream>
#include <string>
#include <cctype>


// Constructor implementation
MovieTickets::MovieTickets(int _id, const char* _movieName, const char* _theaterName, const char _seatNumber[], const char* _time, double _price, ticketsType _type) : id(_id), price(_price), type(_type) {

	this->setMovieName(_movieName);
	this->setTheaterName(_theaterName);
	this->setSeatNumber(_seatNumber);
	//set time
}


// Getters implementation
int MovieTickets::getId() { return this->id; }
const char* MovieTickets::getSeatNumber() { return this->seatNumber; }
double MovieTickets::getPrice() { return this->price; }
ticketsType MovieTickets::getType() { return this->type; }

char* MovieTickets::getMovieName() {

	if (this->movieName == nullptr) {
		return nullptr;
	}

	char* copy = new char[strlen(this->movieName) + 1];
	strcpy_s(copy, strlen(this->movieName) + 1, this->movieName);

	return copy;
}

char* MovieTickets::getTheaterName() {

	if (this->theaterName == nullptr) {
		return nullptr;
	}

	char* copy = new char[strlen(this->theaterName) + 1];
	strcpy_s(copy, strlen(this->theaterName) + 1, this->theaterName);

	return copy;
}

char* MovieTickets::getTime() {

	if (this->time == nullptr) {
		return nullptr;
	}

	char* copy = new char[strlen(this->time) + 1];
	strcpy_s(copy, strlen(this->time) + 1, this->time);

	return copy;
}


// Setters implementation
void MovieTickets::setMovieName(const char* _movieName) {

	std::string movieNameString(_movieName);

	if ((movieNameString.empty()) && (islower(movieNameString[0]))) {		// test
		std::cout << std::endl << "Invalid movie name." << std::endl;
		return;
	}
	else {
		if (this->movieName != nullptr) {
			delete[] this->movieName;
		}

		this->movieName = new char[strlen(_movieName) + 1];
		strcpy_s(this->movieName, strlen(_movieName) + 1, _movieName);
	}

}

void MovieTickets::setTheaterName(const char* _theaterName) {

	std::string theaterNameString(_theaterName);

	if ((theaterNameString.empty()) && (islower(theaterNameString[0]))) {		// test
		std::cout << std::endl << "Invalid theater name." << std::endl;
		return;
	}
	else {
		if (this->theaterName != nullptr) {
			delete[] this->theaterName;
		}

		this->theaterName = new char[strlen(_theaterName) + 1];
		strcpy_s(this->theaterName, strlen(_theaterName) + 1, _theaterName);
	}

}

void MovieTickets::setSeatNumber(const char _seatNumber[]) {		// test

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

	strcpy_s(this->seatNumber, strlen(_seatNumber), _seatNumber);
	this->seatNumber[3] = '\0';
}


int MovieTickets::noTickets = 0;