#include "UtilTickets.h"

#include <string>
#include <regex>


char* UtilTickets::copyString(const char* source) {

	if (source == nullptr) {
		return nullptr;
	}

	char* value = new char[strlen(source) + 1];
	strcpy_s(value, strlen(source) + 1, source);
	return value;
}

void UtilTickets::setString(char*& destination, const char* source) {

	// destination - obj attribute; source - (user) input
	if (destination != nullptr) {
		delete[] destination;
	}

	destination = new char[strlen(source) + 1];
	strcpy_s(destination, strlen(source) + 1, source);
}

bool UtilTickets::validateString(std::string string) {

	if ((string.empty()) || (islower(string[0]))) {
		return false;
	}

	return true;
}

bool UtilTickets::validateTime(const char* source) {

	// time - "hh:mm", 24-hour clock format
	if ((std::string(source).empty()) || (strlen(source) < 5)) {
		return false;
	}

	std::regex timeRegex(R"([0-2][0-9]:[0-5][0-9])");
	return std::regex_match(source, timeRegex);		// match -> true
}

bool UtilTickets::validateDate(const char* source) {

	// date - "dd/mm/yyyy"
	if ((std::string(source).empty()) || (strlen(source) < 10)) {
		return false;
	}

	std::regex dateRegex(R"((0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4})");
	return std::regex_match(source, dateRegex);		// match -> true
}

// method - verify tickets not sold out: noTickets <= capacity
