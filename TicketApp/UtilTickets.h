#ifndef UTILTICKETS_H
#define UTILTICKETS_H

#include <string>
#include <regex>


class UtilTickets
{

public:

	static char* copyString(const char* source) {

		if (source == nullptr) {
			return nullptr;
		}

		char* value = new char[strlen(source) + 1];
		strcpy_s(value, strlen(source) + 1, source);
		return value;
	}

	static void setString(char*& destination, const char* source) {		// test

		// destination - obj attribute; source - (user) input
		if (destination != nullptr) {
			delete[] destination;
		}

		destination = new char[strlen(source) + 1];
		strcpy_s(destination, strlen(source) + 1, source);
	}

	static bool validateString(std::string string) {			// test

		if ((string.empty()) || (islower(string[0]))) {
			return false;
		}

		return true;
	}

	static bool validateTime(const char* source) {			// test

		// time - "hh:mm", 24-hour clock format
		if ((std::string(source).empty()) || (strlen(source)<5)) {
			return false;
		}

		std::regex timeRegex(R"([0-2][0-9]:[0-5][0-9])");
		return std::regex_match(source, timeRegex);		// match -> true
	}

	static bool validateDate(const char* source) {

		// date - "dd/mm/yyyy"
		if ((std::string(source).empty()) || (strlen(source) < 10)) {
			return false;
		}

		std::regex dateRegex(R"((0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4})");
		return std::regex_match(source, dateRegex);		// match -> true
	}

	// method - verify tickets not sold out: noTickets <= capacity

};


#endif