#pragma once
#include "Ticketing.h"

class Menu
{
public:
	// 0 - user, 1 - admin
	int whoIs = -1;		  // make private
	void who();
	void start();
	void display();
	void addEvent();
	void addEventLocation();
	void generateTicket();
	void validateTicket();
	void processFileInput(const string& filename);
	void saveToBinaryFile();
};