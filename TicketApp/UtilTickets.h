#pragma once
#include <string>
#include <regex>
#include <fstream>
using namespace std;

class UtilTickets
{
	UtilTickets() {}
public:
	static char* copyString(const char* source);
	static void setString(char*& destination, const char* source);
	static bool validateString(string string);
	static bool validateTime(const char* source);
	static bool validateDate(const char* source);
	static bool isSoldOut(int soldTickets, int capacity);
	static void serializeString(string value, ofstream& file);
	string deserializeString(ifstream& file);
	// method - validate tickets are not the same - double-booking not allowed (exception thrown)
	// method - verify date is not in the past
    // method - display all occupied and remaining seats
};