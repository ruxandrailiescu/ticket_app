#pragma once		// see ifndef, define, endif

enum ticketsType {NORMAL = 0, VIP = 1};

class MovieTickets
{
	const int id;		// randomly generated, can only be initialized in constructor (const, no setter)
	char* movieName = nullptr;
	char* theaterName = nullptr;
	char seatNumber[4] = { 0 };
	char* time = nullptr;
	double price = 0;
	ticketsType type;
	static int noTickets;

public:

	// Constructor declaration
	MovieTickets(int _id, const char* _movieName, const char* _theaterName, const char _seatNumber[], const char* _time, double _price, ticketsType _type);


	// Getters declaration
	int getId();
	const char* getSeatNumber();
	double getPrice();
	ticketsType getType();
	char* getMovieName();
	char* getTheaterName();
	char* getTime();


	// Setters declaration
	void setMovieName(const char* _movieName);
	void setTheaterName(const char* _theaterName);
	void setSeatNumber(const char _seatNumber[]);
};

