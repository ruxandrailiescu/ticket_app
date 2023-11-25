#ifndef PAYMENTS_H
#define PAYMENTS_H

#include "MovieTickets.h"
#include <unordered_map>

class Payments
{
	const int id;
	double amount;
	int noTickets;
	string* tickets;
	bool isPaid;
	double* ticketPrices;

	static int PAYMENTS;
	static unordered_map<int, double> umap;
	static int ID_COUNTER;

public:

	Payments();
	Payments(int _id, double _amount, int _noTickets, const string* _tickets, bool _isPaid, const double* _ticketPrices);
	Payments(const Payments& p);
	~Payments();
	Payments& operator=(const Payments& p);

	string* getTickets();
	void setTickets(const string* _tickets, int _noTickets);
	double* getTicketPrices();
	void setTicketPrices(const double* _ticketPrices, int _noTickets);
	double getAmount();

	string& operator[](int index);
	Payments operator++();
	Payments operator++(int);
	friend ostream& operator<<(ostream& out, const Payments& p);
	static unordered_map<int, double> getPayments();

protected:

	void setAmount(const double* _ticketPrices, int _noTickets);
	// method to read information from a file
	// method to write information to a file
	// method to verify that passed amount (in constr) mathces the ticketPrices*noTickets
};

#endif