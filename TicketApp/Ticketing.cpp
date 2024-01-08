#include "Ticketing.h"

Normal** Normal::tickets = nullptr;
int Ticketing::NO_TICKETS = 0;
int Ticketing::ID_COUNTER = 0;

void Normal::serialize(ofstream& file) {
	file.write((char*)&this->id, sizeof(int));

	int size = strlen(this->seatNumber);		// not +1 because we added the string terminator
	file.write((char*)&size, sizeof(int));
	file.write(this->seatNumber, sizeof(char) * size);

	size = strlen(this->date);
	file.write((char*)&size, sizeof(int));
	file.write(this->date, sizeof(char) * size);

	size = strlen(this->time);
	file.write((char*)&size, sizeof(int));
	file.write(this->time, sizeof(char) * size);

	file.write((char*)&this->price, sizeof(double));
}

void Vip::serialize(ofstream& file) {
	Normal::serialize(file);
	file.write((char*)&this->bonusPoints, sizeof(int));
}

void Student::serialize(ofstream& file) {
	Normal::serialize(file);
	file.write((char*)&this->discount, sizeof(int));
}

void Normal::addTicket(Normal t, int type) {
	
	// works only if tickets are upcasted to Normal at the moment
	Normal** newTickets = new Normal * [NO_TICKETS + 1];
	for (int i = 0; i < NO_TICKETS; i++) {
		newTickets[i] = tickets[i];
	}

	newTickets[NO_TICKETS] = new Normal(t);

	delete[] tickets;
	tickets = newTickets;

	NO_TICKETS++;

	//Normal** temp = new Normal * [Ticketing::NO_TICKETS];
	//for (int i = 0; i < Ticketing::NO_TICKETS - 1; i++) {
	//	temp[i] = new Normal();
	//	(*temp)[i] = (*tickets)[i];
	//}

	//// how to allocate memory for object if "type" is not known beforehand
	//temp[Ticketing::NO_TICKETS - 1] = new Normal();		
	//(*temp)[Ticketing::NO_TICKETS - 1] = *t;
	//
	//if (tickets != nullptr) {
	//	for (int i = 0; i < Ticketing::NO_TICKETS; i++)
	//		delete tickets[i];
	//	delete[] tickets;
	//}
	//	
	//tickets = new Normal * [Ticketing::NO_TICKETS];
	//for (int i = 0; i < Ticketing::NO_TICKETS; i++) {
	//	tickets[i] = new Normal();
	//	(*tickets)[i] = (*temp)[i];
	//}
}

void Ticketing::setSeatNumber(const char* _seatNumber) {

	// Seat numbers should be of the form: 'A10'
	if (_seatNumber[0] == '\0') {
		throw InvalidInputException("Empty string");
	}

	if ((!isalpha(_seatNumber[0])) || (!isupper(_seatNumber[0]))) {
		throw InvalidInputException("Seat number: rows should begin with an uppercase letter");
	}

	for (int i = 1; i <= 2; i++) {
		if (!isdigit(_seatNumber[i])) {
			throw InvalidInputException("Seat numbers contain 2 digits");
		}
	}

	strcpy_s(this->seatNumber, sizeof(this->seatNumber), _seatNumber);
	this->seatNumber[3] = '\0';
}

void Ticketing::setTime(const char* _time) {

	if (UtilTickets::validateTime(_time)) {

		strcpy_s(this->time, sizeof(this->time), _time);
		this->time[5] = '\0';
	}
	else {
		throw InvalidInputException("Invalid time format");
	}
}

void Ticketing::setDate(const char* _date) {

	if (UtilTickets::validateDate(_date)) {

		strcpy_s(this->date, sizeof(this->date), _date);
		this->date[10] = '\0';
	}
	else {
		throw InvalidInputException("Invalid date format");
	}
}

void Ticketing::setPrice(double _price) {

	if (_price > 0 && _price < PRICE_MAX) {
		this->price = _price;
	}
	else
		throw InvalidInputException("Price should be greater than 0 and in valid range.");
}

Ticketing::Ticketing() : id(++ID_COUNTER) {
	Ticketing::NO_TICKETS++;
}

Ticketing::Ticketing(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price) : id(++ID_COUNTER) {
	this->event = _event;
	this->setSeatNumber(_seatNumber);
	this->setTime(_time);
	this->setDate(_date);
	this->setPrice(_price);
	Ticketing::NO_TICKETS++;
}

Ticketing::Ticketing(const Ticketing& t)
	: Ticketing(t.event, t.seatNumber, t.time, t.date, t.price) {}

Ticketing& Ticketing::operator=(const Ticketing& t) {
	if (this == &t)
		return *this;
	this->event = t.event;
	this->setSeatNumber(t.seatNumber);
	this->setTime(t.time);
	this->setDate(t.date);
	this->setPrice(t.price);
	return *this;
}

const Event* Ticketing::getEvent() { return &this->event; }
int Ticketing::getId() { return this->id; }
int Ticketing::getNoTickets() { return Ticketing::NO_TICKETS; }
int Ticketing::getIdCounter() { return Ticketing::ID_COUNTER; }
char* Ticketing::getSeatNumber() { return UtilTickets::copyString(this->seatNumber); }
char* Ticketing::getTime() { return UtilTickets::copyString(this->time); }
char* Ticketing::getDate() { return UtilTickets::copyString(this->date); }
double Ticketing::getPrice() { return this->price; }

bool Ticketing::operator!() {

	// return true if seat has not been chosen
	if (this->seatNumber == nullptr || strlen(this->seatNumber) == 0) {
		return true;
	}
	return false;
}

bool Ticketing::operator==(const Ticketing& t) {

	if (this == &t) {
		return true;
	}

	// see if tickets are the same - event, seat number, date, time
	if ((this->event == t.event) && (this->seatNumber == t.seatNumber)
		&& (this->date == t.date) && (this->time == t.time)) {
		return true;
	}
	return false;
}

const Normal* Normal::operator++() {

	this->price++;
	return this;
}

const Normal* Normal::operator++(int) {

	Normal* copy = new Normal(*this);
	this->price++;
	return copy;
}

void Normal::generateReport(ofstream& report) {
	if (!report.is_open()) {
		throw exception("File not opened for report");
	}
	report << "\nTICKETS REPORT\n";
	for (int i = 0; i < Ticketing::NO_TICKETS; i++) {
		report << "Ticket " << i + 1 << ": \n";
		report << *tickets[i];
	}
	report.close();
}

bool Ticketing::operator>(const Ticketing& t) {

	if ((this == &t) || (this->price <= t.price)) {
		return false;
	}
	return true;
}

bool Ticketing::operator<(const Ticketing& t) {

	if ((this == &t) || (this->price >= t.price)) {
		return false;
	}
	return true;
}

istream& operator>>(istream& in, Normal& t) {
	Event e;
	in >> e;
	t.event = e;

	cout << endl << "Seat number: ";
	char buffer[256];
	in.ignore();
	in.getline(buffer, 256);
	t.setSeatNumber(buffer);

	cout << endl << "Time: ";
	char buffer1[256];
	in.getline(buffer1, 256);
	t.setTime(buffer1);

	cout << endl << "Date: ";
	char buffer2[256];
	in.getline(buffer2, 256);
	t.setDate(buffer2);

	cout << endl << "Price: ";
	in.clear();
	double _price;
	in >> _price;
	t.setPrice(_price);
	return in;
}

istream& operator>>(istream& in, Vip& t) {
	Event e;
	in >> e;
	t.event = e;

	cout << endl << "Seat number: ";
	char buffer[256];
	in.ignore();
	in.getline(buffer, 256);
	t.setSeatNumber(buffer);

	cout << endl << "Time: ";
	char buffer1[256];
	in.getline(buffer1, 256);
	t.setTime(buffer1);

	cout << endl << "Date: ";
	char buffer2[256];
	in.getline(buffer2, 256);
	t.setDate(buffer2);

	cout << endl << "Price: ";
	in.clear();
	double _price;
	in >> _price;
	t.setPrice(_price);

	cout << endl << "Bonus points: ";
	int _bonus;
	in >> _bonus;
	t.setBonusPoints(_bonus);
	return in;
}

istream& operator>>(istream& in, Student& t) {
	Event e;
	in >> e;
	t.event = e;

	cout << endl << "Seat number: ";
	char buffer[256];
	in.ignore();
	in.getline(buffer, 256);
	t.setSeatNumber(buffer);

	cout << endl << "Time: ";
	char buffer1[256];
	in.getline(buffer1, 256);
	t.setTime(buffer1);

	cout << endl << "Date: ";
	char buffer2[256];
	in.getline(buffer2, 256);
	t.setDate(buffer2);

	cout << endl << "Price: ";
	in.clear();
	double _price;
	in >> _price;
	t.setPrice(_price);

	cout << endl << "Discount: ";
	int _discount;
	in >> _discount;
	t.setDiscount(_discount);
	return in;
}

ostream& operator<<(ostream& out, Normal& t) {
	out << endl << "Event details: ";
	out << t.getEvent();
	out << endl << "Ticket id: ";
	out << t.getId();
	out << endl << "Seat number: ";
	out << t.getSeatNumber();
	out << endl << "Time: ";
	out << t.getTime();
	out << endl << "Date: ";
	out << t.getDate();
	out << endl << "Price: ";
	out << t.getPrice();
	return out;
}

void Ticketing::displayTicketDetails() {
	cout << endl << "Event details: " << this->event;
	cout << endl << "Id: " << this->id;
	cout << endl << "Seat number: " << this->seatNumber;
	cout << endl << "Date: " << this->date;
	cout << endl << "Time: " << this->time;
	cout << endl << "Ticket price: " << this->price;
}

Ticketing::~Ticketing() {
	Ticketing::NO_TICKETS--;
}

void Normal::setPrice(double _price) {
	Ticketing::setPrice(_price);
}

Normal::Normal() {}

Normal::Normal(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price)
	: Ticketing(_event, _seatNumber, _time, _date, _price) {}

void Normal::displayTicketDetails() {
	cout << endl << "-----This is a Normal ticket-----";
	Ticketing::displayTicketDetails();
}

void Vip::setBonusPoints(int _bonusPoints) {
	if ((_bonusPoints > 0) && (_bonusPoints % 10 == 0))
		this->bonusPoints = _bonusPoints;
	else
		throw InvalidInputException("Bonus points should be greater than 0 and a multiple of 10.");
}

void Vip::setPrice(double _price) {
	Ticketing::setPrice(_price * 1.2);
}

Vip::Vip() {
	this->bonusPoints = 0;
}

Vip::Vip(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price, int _bonusPoints)
	: Normal(_event, _seatNumber, _time, _date, _price) {
	this->setBonusPoints(_bonusPoints);
}

int Vip::getBonus() { return this->bonusPoints; }

void Vip::displayTicketDetails() {
	cout << endl << "-----This is a Vip ticket-----";
	Ticketing::displayTicketDetails();
	cout << endl << "Bonus points: " << this->bonusPoints;
}

const Vip* Vip::operator++() {

	this->price = this->price * 1.5;
	return this;
}

const Vip* Vip::operator++(int) {

	Vip* copy = new Vip(*this);
	this->price = this->price * 1.5;
	return copy;
}

void Student::setDiscount(int _discount) {
	if ((_discount > 0) && (_discount % 10 == 0))
		this->discount = _discount;
	else
		throw InvalidInputException("Discount should be greater than 0 and a multiple of 10, as percentage.");
}

void Student::setPrice(double _price) {
	if (this->discount > 0)
		Ticketing::setPrice(_price * (1 - this->discount / 100));
	else
		Ticketing::setPrice(_price);
}

Student::Student() {
	this->discount = 0;
}

Student::Student(Event _event, const char* _seatNumber, const char* _time, const char* _date, double _price, int _discount)
	: Normal(_event, _seatNumber, _time, _date, _price) {
	this->setDiscount(_discount);
}

int Student::getDiscount() { return this->discount; }

void Student::displayTicketDetails() {
	cout << endl << "-----This is a Student ticket-----";
	Ticketing::displayTicketDetails();
	cout << endl << "Discount: " << this->discount;
}

const Student* Student::operator++() {

	this->price = this->price * 1.1;
	return this;
}

const Student* Student::operator++(int) {

	Student* copy = new Student(*this);
	this->price = this->price * 1.1;
	return copy;
}
