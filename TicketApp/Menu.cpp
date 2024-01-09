#include "Menu.h"

void Menu::who() {
	do {
		cout << endl << "Are you user or admin?";
		cout << endl << "Enter 0 for user or 1 for admin: ";
		cin >> this->whoIs;
	} while ((this->whoIs != 0) && (this->whoIs != 1));
}

void Menu::display() {

	// 5. Process tickets from text file -- default txt file if choosing 5 or start from cmd to input file manually
	// 6. Save tickets to binary file (serialize func) -- data has to be restored once app restarts (deserialize func)
	cout << endl;
	cout << "|--------------------|\n";
	cout << "|        MENU        |\n";
	cout << "|                    |\n";
	cout << "| 1. Add Event       |\n";
	cout << "| 2. Add Location    |\n";
	cout << "| 3. Generate Ticket |\n";
	cout << "| 4. Validate Ticket |\n";
	cout << "| 5. Process Tickets |\n";
	cout << "| 6. Save Tickets    |\n";
	cout << "| 7. Restore Data    |\n";
	cout << "| 8. Generate Report |\n";
	cout << "| 9. Exit            |\n";
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

	int _noAvailableSeats;
	cout << endl << "Number of available seats: ";
	cin >> _noAvailableSeats;

	string* temp = new string[_noAvailableSeats];
	for (int i = 0; i < _noAvailableSeats; i++) {
		cout << endl << "Enter seat " << i + 1 << ": ";
		cin >> temp[i];
	}

	EventLocations* newLocation = new EventLocations(_location, _address, temp, _noAvailableSeats, _maxNoSeats);

	try {
		EventLocations::addEventLocation(*newLocation);
	}
	catch (const ReadAccessViolationException& e) {
		cout << endl << e.what();
	}
	
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
	
	// works only for Normal tickets at the moment
	Normal* newTicket;
	if (type == 0) {
		newTicket = new Normal(e, _seatNumber, _time, _date, _price);
		Normal::addTicket(*newTicket, type);
	}
	else if (type == 1) {
		cout << endl << "Enter bonus points: ";
		int _bonus;
		cin >> _bonus;
		newTicket = new Vip(e, _seatNumber, _time, _date, _price, _bonus);
		Normal::addTicket(*newTicket, type);
	}
	else {
		cout << endl << "Enter discount: ";
		int _discount;
		cin >> _discount;
		newTicket = new Student(e, _seatNumber, _time, _date, _price, _discount);
		Normal::addTicket(*newTicket, type);
	}
}

void Menu::processFileInput(const string& filename) {

	// will work only for Normal tickets at the moment
	ifstream file(filename);
	if (file.is_open()) {
		while (!file.eof()) {
			Normal ticket;
			file >> ticket;
			cout << endl << ticket;
		}
		file.close();
	}
	else {
		throw exception("***** File not found *****");
	}
}

void Menu::saveToBinaryFile(string filename) {
	Normal ticket;
	cin >> ticket;
	ofstream file(filename, ios::binary | ios::ate);
	if (!file.is_open()) {
		cout << endl << "Issues with the file";
	}
	ticket.serialize(file);
	cout << endl << "***** Ticket saved to binary file *****";
	file.close();
}

void Menu::restoreFromBinaryFile(string filename) {
	ifstream file(filename, ios::binary);
	if (!file.is_open()) {
		cout << endl << "Issues with the file";
	}
	Normal ticket;
	ticket.deserialize(file);
	cout << endl << "***** Ticket restored from binary file *****";
	file.close();
}

void Menu::start() {
	int choice;
	do {
		this->who();
		this->display();
		cout << endl << "Enter action (choose number 1-9): ";
		cin >> choice;
		if ((choice > 9) || (choice < 1)) {
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
		case 5:
			this->processFileInput("TicketsInputFile.txt");
			break;
		case 6:
			this->saveToBinaryFile("Tickets.bin");
			break;
		case 7:
			this->restoreFromBinaryFile("Tickets.bin");
			break;
		case 8:
			ofstream report("Report.txt", ios::app);
			Normal::generateReport(report);
			break;
		}
	} while (choice != 9);
}
