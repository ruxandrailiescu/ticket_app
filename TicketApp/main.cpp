#include "Menu.h"

int main(int argc, char* argv[]) {
	Menu menu;

	if (argc == 1) {
		menu.start();
	}
	else if (argc == 2) {
		string filename = argv[1];
		menu.processFileInput(filename);
	}
	else {
		cerr << "Usage: " << argv[0] << " [filename]\n";
		return 1;
	}
	return 0;
}