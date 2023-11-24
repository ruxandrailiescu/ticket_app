#include "MovieTickets.h"
#include "UtilTickets.h"
#include "Payments.h"


int main() {

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

}