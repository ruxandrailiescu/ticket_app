#include "MovieTickets.h"
#include "UtilTickets.h"

#include <iostream>

int main() {

	// Normal tests:
	
	// Instantiate MovieTickets obj (setters tested implicitly)
	MovieTickets ticket(1, "Inception", "Baneasa", "H11", "12:20", "11/11/2023", 10, TicketsType::STUDENT);

	// Default constructor
	// ...

	// Getters
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
	MovieTickets ticket2 = ticket;		// unwanted behavior for output - id counter 3

	// Display details of ticket
	ticket2.displayTicketDetails();

}