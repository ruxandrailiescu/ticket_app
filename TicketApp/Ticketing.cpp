#include "Ticketing.h"

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

void Ticketing::setPrice(const double _price) {

	if (_price > 0 && _price < PRICE_MAX) {
		this->price = _price;
	}
}