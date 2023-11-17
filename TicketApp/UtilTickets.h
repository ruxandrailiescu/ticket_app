#ifndef UTILTICKETS_H
#define UTILTICKETS_H

#include <string>
#include <regex>


class UtilTickets
{
	// Deactivate option of instantiating an Util obj - outside class scope
	UtilTickets() {

	}

public:

	static char* copyString(const char* source);
	static void setString(char*& destination, const char* source);
	static bool validateString(std::string string);
	static bool validateTime(const char* source);
	static bool validateDate(const char* source);
	// method - verify tickets not sold out: noTickets <= capacity

};


#endif