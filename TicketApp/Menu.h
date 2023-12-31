#pragma once
#include "Ticketing.h"

class Menu
{
public:
	// 0 - user, 1 - admin
	int whoIs = -1;
	void who();
	void start();
	void display();
	void addEvent();
	void addEventLocation();
	void generateTicket();
	void validateTicket();
};