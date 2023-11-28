#include "Payments.h"

int Payments::PAYMENTS = 0;
int Payments::ID_COUNTER = 0;
unordered_map<int, double>Payments::umap = {};		// FOR ALL PAYMENTS - payment id -> total amount


unordered_map<int, double> Payments::getPayments() { return Payments::umap; }

Payments::Payments() :id(++ID_COUNTER) {

	this->amount = 0;				// FOR A SINGLE PAYMENT:
	this->noTickets = 0;			// no of tickets bought
	this->tickets = nullptr;		// vector with ticket ids - do they exist?
	this->isPaid = false;		
	this->ticketPrices = nullptr;	// vector with prices for each ticket - are prices correct for each ticket (based on id)?

	Payments::umap[this->id] = this->amount;
}

Payments::Payments(int _id, double _amount, int _noTickets, const string* _tickets, bool _isPaid, const double* _ticketPrices) :id(++ID_COUNTER), isPaid(_isPaid) {

	this->setTickets(_tickets, _noTickets);
	this->setTicketPrices(_ticketPrices, _noTickets);
	this->setAmount(this->ticketPrices, this->noTickets);

	if (this->isPaid)
		Payments::PAYMENTS++;

	Payments::umap[this->id] = this->amount;		// validation if amount has not been set
}

Payments::Payments(const Payments& p):Payments(p.id, p.amount, p.noTickets, p.tickets, p.isPaid, p.ticketPrices){}

Payments& Payments::operator=(const Payments& p) {

	if (this == &p)
		return *this;

	this->setTickets(p.tickets, p.noTickets);
	this->setTicketPrices(p.ticketPrices, p.noTickets);
	this->amount = p.amount;
	this->isPaid = p.isPaid;

	Payments::umap[this->id] = p.ticketPrices[p.id];

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

double* Payments::getTicketPrices() {

	if ((this->ticketPrices != nullptr) && (this->noTickets > 0)) {
		double* copy = new double[this->noTickets];
		for (int i = 0; i < this->noTickets; i++)
			copy[i] = this->ticketPrices[i];
		return copy;
	}
	return nullptr;
}

void Payments::setTicketPrices(const double* _ticketPrice, int _noTickets) {

	// validation to see if tickets (obj) exist? (e.g., MovieTickets obj)
	if ((_ticketPrice != nullptr) && (_noTickets > 0)) {
		if (this->ticketPrices != nullptr)
			delete[] this->ticketPrices;

		this->ticketPrices = new double[_noTickets];
		for (int i = 0; i < _noTickets; i++)
			this->ticketPrices[i] = _ticketPrice[i];
		this->noTickets = _noTickets;
	}
}

double Payments::getAmount() { return this->amount; }

void Payments::setAmount(const double* _ticketPrices, int _noTickets) {

	if ((_ticketPrices != nullptr) && (_noTickets > 0)) {
		for (int i = 0; i < _noTickets; i++) {
			this->amount += _ticketPrices[i];
		}
	}
	else {
		this->amount = 0;
	}
}

// Operator[] - read and write
string& Payments::operator[](int index) {

	if (this->tickets == nullptr)
		throw ReadAccessViolationException("Tickets: cannot read from memory at this location.");

	if ((index < 0) || (index >= this->noTickets))
		throw IndexOutOfBoundsException("Tickets: Requested index out of bounds.");

	return this->tickets[index];
}

// Pre-increment -- ERROR
Payments Payments::operator++() {

	// pre-increment the amount of the payment by last ticket added
	// in the ticketPrices vector (i.e., update amount, umap, ticketPrices)

	double _price = this->ticketPrices[this->noTickets - 1];
	string _id = this->tickets[this->noTickets - 1];
	double* tempPrices = new double[this->noTickets + 1];
	string* tempTickets = new string[this->noTickets + 1];

	for (int i = 0; i < this->noTickets; i++) {
		tempPrices[i] = this->ticketPrices[i];
		tempTickets[i] = this->tickets[i];
	}
	tempPrices[this->noTickets] = _price;
	tempTickets[this->noTickets] = _id;

	this->setTicketPrices(tempPrices, this->noTickets + 1);
	this->setTickets(tempTickets, this->noTickets + 1);
	this->setAmount(this->ticketPrices, this->noTickets);

	Payments::umap[this->id] = this->amount;

	delete[] tempPrices;
	delete[] tempTickets;
	return *this;
}

// Post-increment -- ERROR
Payments Payments::operator++(int) {

	// post-increment the amount of the payment by the last ticket added
	// in the ticketPrices vector (i.e., update amount, umap, ticketPrices)

	Payments p = *this;

	double _price = this->ticketPrices[this->noTickets - 1];
	string _id = this->tickets[this->noTickets - 1];
	double* tempPrices = new double[this->noTickets + 1];
	string* tempTickets = new string[this->noTickets + 1];

	for (int i = 0; i < this->noTickets; i++) {
		tempPrices[i] = this->ticketPrices[i];
		tempTickets[i] = this->tickets[i];
	}
	tempPrices[this->noTickets] = _price;
	tempTickets[this->noTickets] = _id;

	this->setTicketPrices(tempPrices, this->noTickets + 1);
	this->setTickets(tempTickets, this->noTickets + 1);
	this->setAmount(this->ticketPrices, this->noTickets);

	Payments::umap[this->id] = this->amount;

	delete[] tempPrices;
	delete[] tempTickets;

	return p;
}

ostream& operator<<(ostream& out, const Payments& p) {

	out << endl << "Payment ID: " << p.id;
	out << endl << "No tickets: " << p.noTickets;
	out << endl;
	for (int i = 0; i < p.noTickets; i++)
		out << p.tickets[i] << "  ";
	out << endl << "Total amount: " << p.amount;
	out << endl << "Payment status: " << p.isPaid;

	return out;
}

Payments::~Payments() {

	if (this->tickets != nullptr)
		delete[] this->tickets;

	if (this->ticketPrices != nullptr)
		delete[] this->ticketPrices;

	Payments::PAYMENTS--;
}
