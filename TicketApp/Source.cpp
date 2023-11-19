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
	std::cin >> ticket3;
	ticket3.displayTicketDetails();		// throw exceptions because invalid input is not notified to user (logic works)
}