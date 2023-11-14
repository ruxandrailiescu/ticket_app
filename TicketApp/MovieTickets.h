#ifndef MOVIETICKETS_H
#define MOVIETICKETS_H


enum ticketsType {NORMAL = 0, VIP = 1};


class MovieTickets
{
	const int id;			// randomly generated, can only be initialized in constructor (const, no setter)
	char* movieName = nullptr;
	char* theaterName = nullptr;
	char seatNumber[4] = "";
	char time[6] = "";		// hh:mm
	char date[11] = "";		// dd/mm/yyyy
	double price = 0;
	ticketsType type;
//	int capacity = 0;
	static int noTickets;

public:

	// Constructor declaration
	MovieTickets(int _id, const char* _movieName, const char* _theaterName, const char* _seatNumber, const char* _time, const char* _date, double _price, ticketsType _type);


	// Getters declaration
	int getId();
	const char* getSeatNumber();
	double getPrice();
	ticketsType getType();
	char* getMovieName();
	char* getTheaterName();
	char* getTime();
	char* getDate();
	static int getNoTickets();


	// Setters declaration
	void setMovieName(const char* _movieName);
	void setTheaterName(const char* _theaterName);
	void setSeatNumber(const char* _seatNumber);
	void setTime(const char* _time);
	void setDate(const char* _date);
	//set price, type


	// Copy constructor declaration
	MovieTickets(const MovieTickets& t);


	// Destructor declaration
	~MovieTickets();
};


#endif