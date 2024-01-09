#include "UtilTickets.h"


void UtilTickets::serializeString(string value, ofstream& file) {
	int size = strlen(value.c_str()) + 1;
	file.write((char*)&size, sizeof(int));
	file.write(value.c_str(), sizeof(char) * size);
}

string UtilTickets::deserializeString(ifstream& file) {
	int size = 0;
	file.read((char*)&size, sizeof(int));
	char buffer[256];
	file.read(buffer, sizeof(char) * size);
	return string(buffer);
}

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
	//if (destination != nullptr) {
	//	delete[] destination;
	//}

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

bool UtilTickets::isSoldOut(int soldTickets, int capacity) {

	return (soldTickets <= capacity);
}