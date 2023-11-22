#ifndef PAYMENTS_H
#define PAYMENTS_H

#include "MovieTickets.h"
#include <iostream>
using namespace std;

class Payments
{
	const string id;
	double amount;
	int noTickets;
	string* tickets;
	bool isPaid;
	double* ticketPrice;

	static int PAYMENTS;

public:

	Payments();
	Payments(string _id, double _amount, int _noTickets, const string* _tickets, bool _isPaid, const double* _ticketPrice);
	Payments(const Payments& p);
	~Payments();
	Payments& operator=(const Payments& p);

	string* getTickets();
	void setTickets(const string* _tickets, int _noTickets);
	double* getTicketPrice();
	void setTicketPrice(const double* _ticketPrice, int _noTickets);
	double getAmount();

	string operator[](int index);

protected:
	void setAmount(const double* _ticketPrice, int _noTickets);
};

#endif