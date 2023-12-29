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

void Menu::addEvent() {
	string _id;
	string _name;
	string _location;
	string _address;
	int _maxNoSeats;

	// have to do try-catch
	// do-while
	cout << endl << "Enter event id: ";
	getline(cin, _id);
	cout << endl << "Enter event name: ";
	getline(cin, _name);
	cout << endl << "Enter location: ";
	getline(cin, _location);
	cout << endl << "Enter address: ";
	getline(cin, _address);
	cout << "Enter max no of seats: ";
	cin >> _maxNoSeats;

	EventLocations l(_location, _address, _maxNoSeats);
	Event e(_id, (char*)_name.c_str(), l);
}
void Menu::addEventLocation() {
	string _location;
	string _address;
	int _maxNoSeats;
	
	// have to do try-catch
	// do-while
	cout << endl << "Enter location: ";
	getline(cin, _location);
	cout << endl << "Enter address: ";
	getline(cin, _address);
	cout << "Enter max no of seats: ";
	cin >> _maxNoSeats;
	
	EventLocations l(_location, _address, _maxNoSeats);
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
		case 4:
			this->validateTicket();
			break;
		}
	} while (choice != 5);
}