#pragma once
#define PRICE_MAX 99999.9999999
#include "Event.h"
#include <typeinfo>

class Ticketing {
protected:
	Event event;
	const int id;
	char seatNumber[4] = "";
	char time[6] = "";		// hh:mm
	char date[11] = "";		// dd/mm/yyyy
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
	bool operator>(const Ticketing& t);
	bool operator<(const Ticketing& t);
	~Ticketing();
};

class Normal : public Ticketing {
	void setPrice(double _price);
	static Normal** tickets;
public:
	static void addTicket(const Normal* t, int type);
	Normal();
	Normal(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price);
	void displayTicketDetails();
	virtual const Normal* operator++();
	virtual const Normal* operator++(int);
};

class Vip : public Normal {
	int bonusPoints;
	void setBonusPoints(int _bonusPoints);
	void setPrice(double _price);
public:
	Vip();
	Vip(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price, int _bonusPoints);
	int getBonus();
	void displayTicketDetails();
	const Vip* operator++();
	const Vip* operator++(int);
};

class Student :public Normal {
	int discount;
	void setDiscount(int _discount);
	void setPrice(double _price);
public:
	Student();
	Student(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price, int _discount);
	int getDiscount();
	void displayTicketDetails();
	const Student* operator++();
	const Student* operator++(int);
};
