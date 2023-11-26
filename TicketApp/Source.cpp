#include "MovieTickets.h"
#include "UtilTickets.h"
#include "Payments.h"
#include "EventLocations.h"


int main() {
	
	// Create unit tests (!!!) - in main only start menu

	// Tests -- MovieTickets:
	
	// Instantiate MovieTickets obj (setters tested implicitly)
	MovieTickets ticket(1, "Inception", "Baneasa", "H11", "12:20", "11/11/2023", 10, TicketsType::STUDENT);
	MovieTickets ticket1("Godfather 2", "Baneasa", "13:30", "12/11/2023");

	// Operator<<
	cout << ticket1;

	// Default constructor
	//MovieTickets defaultTicket;
	//cout << endl;
	//defaultTicket.displayTicketDetails();	
	//cout << endl;


	// Getters
	cout << endl << "Ticket id: " << ticket.getId();
	cout << endl << "Movie name: " << ticket.getMovieName();
	cout << endl << "Theater name: " << ticket.getTheaterName();
	cout << endl << "Seat number: " << ticket.getSeatNumber();
	cout << endl << "Date: " << ticket.getDate();
	cout << endl << "Time: " << ticket.getTime();
	cout << endl << "Price: " << ticket.getPrice();
	cout << endl << "Ticket type: " << ticket.getType();

	// Setters are protected - otherwise we would break encapsulation
	// by allowing complete access to member variables


	// Copy constructor
	MovieTickets ticket2 = ticket;

	// Operator=
	ticket1 = ticket2;

	cout << endl;
	ticket1.displayTicketDetails();
	cout << endl;

	// Display details of ticket
	cout << endl;
	ticket2.displayTicketDetails();
	cout << endl;

	// Operator>>
	MovieTickets ticket3;

	// Test for other constr 
	try {
		cin >> ticket3;
	}
	catch (const InvalidInputException& e) {
		cout << endl << e.what() << endl;
	}

	try {
		ticket3.displayTicketDetails();
		cout << endl;
	}
	catch (const ReadAccessViolationException& e) {
		cout << endl << e.what() << endl;
	}


	// Operator!
	bool res = !ticket3;
	cout << endl << res;
	//cout << endl << (!ticket3);

	// Operator+
	ticket2 = ticket2 + 10;
	cout << endl << ticket2.getPrice();

	// Operator==
	cout << endl << (ticket1 == ticket);
	cout << endl << (ticket3 == ticket);		// logic works for obj instantiated with default constr

	// Operator> and operator<
	if (ticket2 > ticket) {
		cout << endl << "Price of ticket2 is greater than price of ticket."<<endl;
	}

	if (ticket < ticket2) {
		cout << endl << "Price of ticket smaller than price of ticket2."<<endl;
	}

	cout << endl << string(ticket) << endl;

	// Operator++ pre and post
	ticket2 = ++ticket;
	ticket3 = ticket++;

	cout << endl << MovieTickets::getNoTickets() << endl;
	cout << endl << MovieTickets::getIdCounter() << endl;		// ID_COUNTER = NO_TICKETS + 3 (because copies are made for operator++ ?) - handle
																// ID_COUNTER should have an upper limit


	// Tests -- Payments:

	Payments p0;

	string* tickets = new string[2];
	tickets[0] = "1";
	tickets[1] = "2";

	double* ticketPrices = new double[2];
	ticketPrices[0] = 20;
	ticketPrices[1] = 30;

	Payments p1(1, 50, 2, tickets, 1, ticketPrices);
	Payments p2 = p1;
	p0 = p2;

	cout << endl << p0[1];

	Payments p3;
	//p3 = p0++;		// ERROR		-- also copy constr called - PAYMENTS incremented (unwanted behaviour)
	//p2 = ++p0;		// ERROR

	cout << endl << p2 << endl;

	unordered_map<int, double> payments = Payments::getPayments();
	unordered_map<int, double>::iterator itr;
	cout << endl << "All payments: " << endl;
	for (itr = payments.begin(); itr != payments.end(); itr++) {
		cout << itr->first << "  " << itr->second << endl;			// amount for p0 not ok
	}

	
	// Tests -- EventLocations
	EventLocations e0;

	string* avSeats = new string[3];
	avSeats[0] = "A12";
	avSeats[1] = "b12";
	avSeats[2] = "C12";

	try {
		EventLocations e1("Romexpo", "Bucuresti", avSeats, 3, 5);
	}
	catch (const InvalidInputException& e) {
		cout << endl << e.what();
	}

	//EventLocations e2 = e1;

	//e0 = e1;
	cout << endl << e0;
	cout << endl << (int)e0;
}