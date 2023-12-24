#ifndef UTILTICKETS_H
#define UTILTICKETS_H

#include "MovieTickets.h"
#include "EventLocations.h"

#include <string>
#include <regex>


class UtilTickets
{
	// Deactivate option of instantiating an Util obj - outside class scope
	UtilTickets() {}

public:

	static char* copyString(const char* source);
	static void setString(char*& destination, const char* source);
	static bool validateString(string string);
	static bool validateTime(const char* source);
	static bool validateDate(const char* source);
	static bool isStudent(const TicketsType type);
	static bool isVip(const TicketsType type);
	static bool isSoldOut(int soldTickets, int capacity);
	// method - validate tickets are not the same - double-booking not allowed (exception thrown)

};


#endif