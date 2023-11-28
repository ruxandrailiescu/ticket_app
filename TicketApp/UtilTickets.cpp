#include "UtilTickets.h"


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

bool UtilTickets::validateString(string string) {

	if ((string.empty()) || (islower(string[0]))) {
		return false;
	}

	return true;
}

bool UtilTickets::validateTime(const char* source) {

	// time - "hh:mm", 24-hour clock format
	if ((string(source).empty()) || (strlen(source) < 5)) {
		return false;
	}

	regex timeRegex(R"([0-2][0-9]:[0-5][0-9])");
	return regex_match(source, timeRegex);		// match -> true
}

bool UtilTickets::validateDate(const char* source) {

	// date - "dd/mm/yyyy"
	if ((string(source).empty()) || (strlen(source) < 10)) {
		return false;
	}

	regex dateRegex(R"((0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4})");
	return regex_match(source, dateRegex);		// match -> true
}

bool UtilTickets::isStudent(const TicketsType type) {

	return (type == TicketsType::STUDENT);
}

bool UtilTickets::isVip(const TicketsType type) {

	return (type == TicketsType::VIP);
}

bool UtilTickets::isSoldOut(int soldTickets, int capacity) {

	return (soldTickets <= capacity);
}

// method - verify date is not in the past
// method - display all occupied and remaining seats
