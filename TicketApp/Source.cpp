#include "MovieTickets.h"
#include "UtilTickets.h"

#include <iostream>

int main() {

	// Normal tests:
	
	// Instantiate MovieTickets obj (setters tested implicitly)
	MovieTickets ticket(1, "Inception", "Baneasa", "H11", "12:20", "11/11/2023", 10, TicketsType::STUDENT);
	MovieTickets ticket1("Godfather 2", "Baneasa", "13:30", "12/11/2023");

	// Operator<<
	std::cout << ticket1;

	// Default constructor
	//MovieTickets defaultTicket;
	//std::cout << std::endl;
	//defaultTicket.displayTicketDetails();	
	//std::cout << std::endl;


	// Getters
	std::cout << std::endl << "Ticket id: " << ticket.getId();
	std::cout << std::endl << "Movie name: " << ticket.getMovieName();
	std::cout << std::endl << "Theater name: " << ticket.getTheaterName();
	std::cout << std::endl << "Seat number: " << ticket.getSeatNumber();
	std::cout << std::endl << "Date: " << ticket.getDate();
	std::cout << std::endl << "Time: " << ticket.getTime();
	std::cout << std::endl << "Price: " << ticket.getPrice();
	std::cout << std::endl << "Ticket type: " << ticket.getType();

	// Setters are protected - otherwise we would break encapsulation
	// by allowing complete access to member variables


	// Copy constructor
	MovieTickets ticket2 = ticket;

	// Operator=
	ticket1 = ticket2;

	std::cout << std::endl;
	ticket1.displayTicketDetails();
	std::cout << std::endl;

	// Display details of ticket
	std::cout << std::endl;
	ticket2.displayTicketDetails();
	std::cout << std::endl;

	// Operator>>
	MovieTickets ticket3;
	//test for other constr 
//	std::cin >> ticket3;				// exception when invalid input is entered, handle
//	ticket3.displayTicketDetails();		// throw exceptions because invalid input is not notified to user (logic works)
										// handle exception when the default constr is used and display default values

	// Operator!
	bool res = !ticket3;
	std::cout << std::endl << res;
	//std::cout << std::endl << (!ticket3);


	// Operator+
	ticket2 = ticket2 + 10;
	std::cout << std::endl << ticket2.getPrice();

	// Operator==
	std::cout << std::endl << (ticket1 == ticket);
	std::cout << std::endl << (ticket3 == ticket);		// logic works for obj instantiated with default constr

	// Operator> and operator<
	if (ticket2 > ticket) {
		std::cout << std::endl << "Price of ticket2 is greater than price of ticket."<<std::endl;
	}

	if (ticket < ticket2) {
		std::cout << std::endl << "Price of ticket smaller than price of ticket2."<<std::endl;
	}

	std::cout << std::endl << std::string(ticket) << std::endl;

	// Operator++ pre and post
	ticket2 = ++ticket;
	ticket3 = ticket++;

	//MovieTickets tickets;
	//MovieTickets& ticketAtIndex1 = tickets[1];
	//ticketAtIndex1.displayTicketDetails();

	std::cout << std::endl << MovieTickets::getNoTickets() << std::endl;
	std::cout << std::endl << MovieTickets::getIdCounter() << std::endl;		// ID_COUNTER = NO_TICKETS + 3 (because copies are made for operator++ ?) - handle
																				// ID_COUNTER should have an upper limit

	std::cout << std::endl << MovieTickets::getVectorTickets() << std::endl;
}