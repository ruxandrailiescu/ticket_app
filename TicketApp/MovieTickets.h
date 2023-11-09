#pragma once

#include <iostream>
#include <string>
#include <cctype>

enum ticketsType {NORMAL = 0, VIP = 1};

class MovieTickets
{
	const int id;		// randomly generated, can only be initialized in constructor (const, no setter)
	char* movieName = nullptr;
	char* theaterName = nullptr;
	char seatNumber[4] = { 0 };
	char* time = nullptr;
	double price = 0;
	ticketsType type = NORMAL;
	static int noTickets;

public:

	MovieTickets(int _id, const char* _movieName, const char* _theaterName, const char _seatNumber[], const char* _time, double _price, ticketsType _type) : id(_id) {

	}

	// Getters
	int getId() { return this->id; }
	const char* getSeatNumber() { return this->seatNumber; }
	double getPrice() { return this->price; }
	ticketsType getType() { return this->type; }

	char* getMovieName() {

		if (this->movieName == nullptr) {
			return nullptr;
		}

		char* copy = new char[strlen(this->movieName) + 1];
		strcpy_s(copy, strlen(this->movieName) + 1, this->movieName);

		return copy;
	}

	char* getTheaterName() {

		if (this->theaterName == nullptr) {
			return nullptr;
		}

		char* copy = new char[strlen(this->theaterName) + 1];
		strcpy_s(copy, strlen(this->theaterName) + 1, this->theaterName);

		return copy;
	}

	char* getTime() {

		if (this->time == nullptr) {
			return nullptr;
		}

		char* copy = new char[strlen(this->time) + 1];
		strcpy_s(copy, strlen(this->time) + 1, this->time);

		return copy;
	}

	// Setters
	void setMovieName(const char* _movieName) {

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

	void setTheaterName(const char* _theaterName) {

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

	void setSeatNumber(const char _seatNumber[]) {		// test

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
};

//int MovieTickets::noTickets = 0;

