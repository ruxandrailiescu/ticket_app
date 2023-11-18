#ifndef MOVIETICKETS_H
#define MOVIETICKETS_H

#include <iostream>

#define PRICE_MAX 99999.9999999
enum class TicketsType {NORMAL, VIP, STUDENT};

class MovieTickets
{
	const int id;
	char* movieName = nullptr;
	char* theaterName = nullptr;
	char seatNumber[4] = "";
	char time[6] = "";		// hh:mm
	char date[11] = "";		// dd/mm/yyyy
	double price = 0;
	TicketsType type = TicketsType::NORMAL;
//	int capacity = 0;
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

	// Generic methods
	void displayTicketDetails();


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

// Input stream and output stream
std::ostream& operator<<(std::ostream& out, MovieTickets& t);

// Output ticket type
std::ostream& operator<<(std::ostream& out, const TicketsType& _type);


#endif