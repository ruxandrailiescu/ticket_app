#pragma once
#define PRICE_MAX 99999.9999999
#include "Exceptions.h"
#include "Event.h"
#include <iostream>
using namespace std;
using namespace Exceptions;

class Ticketing {
protected:
	Event event;
	const int id;
	char seatNumber[4];
	char time[6];		// hh:mm
	char date[11];		// dd/mm/yyyy
	double price = 0;
	static int NO_TICKETS;
	static int ID_COUNTER;
public:
	virtual void displayTicketDetails() = 0;
	double getPrice();
	Ticketing();
	Ticketing(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price);
	Ticketing(const Ticketing& t);
	Ticketing& operator=(const Ticketing& t);
	Event getEvent();
	int getId();
	char* getSeatNumber();
	char* getTime();
	char* getDate();
	static int getNoTickets();
	static int getIdCounter();
protected:
	void setSeatNumber(const char* _seatNumber);
	void setTime(const char* _time);
	void setDate(const char* _date);
	virtual void setPrice(double _price) = 0;
public:
	bool operator!();
	bool operator==(const Ticketing& t);
	~Ticketing();
};

class Normal : public Ticketing {
	void setPrice(double _price);
public:
	Normal();
	Normal(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price);
	void displayTicketDetails();
};

class Vip : public Ticketing {
	int bonusPoints;
	void setBonusPoints(int _bonusPoints);
	void setPrice(double _price);
public:
	Vip();
	Vip(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price, int _bonusPoints);
	int getBonus();
	void displayTicketDetails();
};

class Student :public Ticketing {
	int discount;
	void setDiscount(int _discount);
	void setPrice(double _price);
public:
	Student();
	Student(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price, int _discount);
	int getDiscount();
	void displayTicketDetails();
};