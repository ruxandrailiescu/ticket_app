#ifndef MOVIETICKETS_H
#define MOVIETICKETS_H
#define PRICE_MAX 99999.9999999

#include "Exceptions.h"
#include <iostream>
using namespace std;
using namespace Exceptions;

enum class TicketsType {NORMAL, VIP, STUDENT};

class MovieTickets			// should inherit from Event class - transform this class in Event and build accordingly (?)
{
	const int id;
	char* movieName = nullptr;
	char* theaterName = nullptr;
	char seatNumber[4] = "";
	char time[6] = "";		// hh:mm
	char date[11] = "";		// dd/mm/yyyy
	double price = 0;
	TicketsType type = TicketsType::NORMAL;

	static int NO_TICKETS;
	static int ID_COUNTER;

public:

	// Constructors declaration
	MovieTickets(int _id, const char* _movieName, const char* _theaterName, const char* _seatNumber, const char* _time, const char* _date, const double _price, const TicketsType _type);
	MovieTickets(const char* _movieName, const char* _theaterName, const char* _time, const char* _date);
	MovieTickets();

	// Getters declaration
	int getId();
	const char* getSeatNumber();
	double getPrice();
	TicketsType getType();
	char* getMovieName();
	char* getTheaterName();
	char* getTime();
	char* getDate();
	static int getNoTickets();
	static int getIdCounter();	


	// Copy constructor declaration
	MovieTickets(const MovieTickets& t);


	// Destructor declaration
	~MovieTickets();

	// Overloaded operators declaration
	MovieTickets& operator=(const MovieTickets& t);
	bool operator!();
	MovieTickets operator+(int val);
	MovieTickets operator-(int val);
	bool operator==(const MovieTickets& t);
	bool operator>(const MovieTickets& t);
	bool operator<(const MovieTickets& t);
	explicit operator string();
	MovieTickets operator++();
	MovieTickets operator++(int);

	// Generic methods
	void displayTicketDetails();
	void inputValidation();
	bool inputString(string& s, const char* item);


protected:

	// Setters declaration
	void setMovieName(const char* _movieName);
	void setTheaterName(const char* _theaterName);
	void setSeatNumber(const char* _seatNumber);
	void setTime(const char* _time);
	void setDate(const char* _date);
	void setPrice(const double _price);
	void setType(const TicketsType _type);


};

// Output and input streams
ostream& operator<<(ostream& out, MovieTickets& t);
istream& operator>>(istream& in, MovieTickets& t);

// Output ticket type
ostream& operator<<(ostream& out, const TicketsType& _type);

#endif