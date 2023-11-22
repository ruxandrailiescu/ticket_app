#include "Payments.h"

int Payments::PAYMENTS = 0;

Payments::Payments() :id("") {

	this->amount = 0;
	this->noTickets = 0;			// no of tickets bought
	this->tickets = nullptr;		// vector with ticket ids - do they exist?
	this->isPaid = false;		
	this->ticketPrice = nullptr;	// vector with prices for each ticket - are prices correct for each ticket (based on id)?
}

Payments::Payments(string _id, double _amount, int _noTickets, const string* _tickets, bool _isPaid, const double* _ticketPrice) :id(_id), isPaid(_isPaid) {

	this->setTickets(_tickets, _noTickets);
	this->setTicketPrice(_ticketPrice, _noTickets);
	this->setAmount(this->ticketPrice, this->noTickets);

	if (this->isPaid)
		Payments::PAYMENTS++;
}

Payments::Payments(const Payments& p):Payments(p.id, p.amount, p.noTickets, p.tickets, p.isPaid, p.ticketPrice){}

Payments& Payments::operator=(const Payments& p) {

	if (this == &p)
		return *this;

	this->setTickets(p.tickets, p.noTickets);
	this->setTicketPrice(p.ticketPrice, p.noTickets);
	this->amount = p.amount;
	this->isPaid = p.isPaid;

	return *this;
}

string* Payments::getTickets() {

	if ((this->tickets != nullptr) && (this->noTickets > 0)) {
		string* copy = new string[this->noTickets];
		for (int i = 0; i < this->noTickets; i++)
			copy[i] = this->tickets[i];
		return copy;
	}
	return nullptr;
}

void Payments::setTickets(const string* _tickets, int _noTickets) {

	// validation to see if tickets (obj) exist? (e.g., MovieTickets obj)
	if ((_tickets != nullptr) && (_noTickets > 0)) {
		if (this->tickets != nullptr)
			delete[] this->tickets;

		this->tickets = new string[_noTickets];
		for (int i = 0; i < _noTickets; i++)
			this->tickets[i] = _tickets[i];
		this->noTickets = _noTickets;
	}
}

double* Payments::getTicketPrice() {

	if ((this->ticketPrice != nullptr) && (this->noTickets > 0)) {
		double* copy = new double[this->noTickets];
		for (int i = 0; i < this->noTickets; i++)
			copy[i] = this->ticketPrice[i];
		return copy;
	}
	return nullptr;
}

void Payments::setTicketPrice(const double* _ticketPrice, int _noTickets) {

	// validation to see if tickets (obj) exist? (e.g., MovieTickets obj)
	if ((_ticketPrice != nullptr) && (_noTickets > 0)) {
		if (this->ticketPrice != nullptr)
			delete[] this->ticketPrice;

		this->ticketPrice = new double[_noTickets];
		for (int i = 0; i < _noTickets; i++)
			this->ticketPrice[i] = _ticketPrice[i];
		this->noTickets = _noTickets;
	}
}

double Payments::getAmount() { return this->amount; }

void Payments::setAmount(const double* _ticketPrice, int _noTickets) {

	if ((_ticketPrice != nullptr) && (_noTickets > 0)) {
		for (int i = 0; i < _noTickets; i++) {
			this->amount += _ticketPrice[i];
		}
	}
	else {
		this->amount = 0;
	}
}

string Payments::operator[](int index) {

	if (this->tickets == nullptr)
		return "No tickets";			// exception
	if (index >= this->noTickets)
		return "Index out of bounds";	// exception
	return this->tickets[index];
}

Payments::~Payments() {

	if (this->tickets != nullptr)
		delete[] this->tickets;

	if (this->ticketPrice != nullptr)
		delete[] this->ticketPrice;

	Payments::PAYMENTS--;
}