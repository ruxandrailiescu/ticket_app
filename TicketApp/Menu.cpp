#include "Menu.h"

void Menu::who() {
	do {
		cout << endl<< "Are you user or admin?";
		cout << endl << "Enter 0 for user or 1 for admin: ";
		cin >> this->whoIs;
	} while ((this->whoIs != 0) && (this->whoIs != 1));
}

void Menu::display() {
	cout << endl;
	cout << "|--------------------|\n";
	cout << "|        MENU        |\n";
	cout << "|                    |\n";
	cout << "| 1. Add Event       |\n";
	cout << "| 2. Add Location    |\n";
	cout << "| 3. Generate Ticket |\n";
	cout << "| 4. Validate Ticket |\n";
	cout << "| 5. Exit            |\n";
	cout << "|                    |\n";
	cout << "|--------------------|\n";
}

void Menu::addEventLocation() {
	cout << endl << "Location: ";
	char buffer[256];
	cin.ignore();
	cin.getline(buffer, 256);
	string _location = buffer;

	cout << endl << "Address: ";
	char buffer1[256];
	cin.getline(buffer1, 256);
	string _address = buffer1;
	
	int _maxNoSeats;
	cout << endl << "Maximum number of seats: ";
	cin >> _maxNoSeats;

	EventLocations* newLocation = new EventLocations(_location, _address, _maxNoSeats);
	EventLocations::addEventLocation(*newLocation);
}

void Menu::addEvent() {
	cout << endl << "Event id: ";
	char buffer[256];
	cin.ignore();
	cin.getline(buffer, 256);
	string _id = buffer;

	cout << endl << "Event name: ";
	char buffer1[256];
	cin.getline(buffer1, 256);
	char* _name = UtilTickets::copyString(buffer1);

	EventLocations loc;
	cin >> loc;

	Event* newEvent = new Event(_id, _name, loc);
	Event::addEvent(*newEvent);
}

void Menu::generateTicket() {
	Event e;
	cin >> e;

	cout << endl << "Seat number: ";
	char buffer[256];
	cin.ignore();
	cin.getline(buffer, 256);
	char* _seatNumber = UtilTickets::copyString(buffer);

	cout << endl << "Date: ";
	char buffer1[256];
	cin.getline(buffer1, 256);
	char* _date = UtilTickets::copyString(buffer1);

	cout << endl << "Time: ";
	char buffer2[256];
	cin.getline(buffer2, 256);
	char* _time = UtilTickets::copyString(buffer2);

	cout << endl << "Price: ";
	double _price;
	cin >> _price;

	int type;
	do {
		cout << endl << "Enter ticket type (0 - Normal, 1 - Vip, 2 - Student): ";
		cin >> type;
	} while ((type != 0) && (type != 1) && (type != 2));
	Ticketing* newTicket;

	switch (type) {
	case 0:
		newTicket = new Normal(e, _seatNumber, _time, _date, _price);
		Ticketing::addTicket(*newTicket);
	case 1:
		cout << endl << "Enter bonus points: ";
		int _bonus;
		cin >> _bonus;
		newTicket = new Vip(e, _seatNumber, _time, _date, _price, _bonus);
		Ticketing::addTicket(*newTicket);
	case 2:
		cout << endl << "Enter discount: ";
		int _discount;
		cin >> _discount;
		newTicket = new Student(e, _seatNumber, _time, _date, _price, _discount);
		Ticketing::addTicket(*newTicket);
	}
}

void Menu::start() {
	int choice;
	do {
		this->who();
		this->display();
		cout << endl << "Enter action (choose number 1-5): ";
		cin >> choice;
		if ((choice > 5) || (choice < 1)) {
			cout << endl << "Try again!";
		}

		switch (choice) {
		case 1:
			if (this->whoIs == 1)
				this->addEvent();
			break;
		case 2:
			if (this->whoIs == 1)
				this->addEventLocation();
			break;
		case 3:
			this->generateTicket();
			break;
		//case 4:
		//	this->validateTicket();
		//	break;
		}
	} while (choice != 5);
}