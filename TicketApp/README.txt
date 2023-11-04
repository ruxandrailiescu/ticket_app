The Ticketing App

Create an application that allows the management of tickets issued for different events (movie, play, football match, etc.)


The application will have the following functionalities:

1. Will allow reading the characteristics of the event location (eg: maximum number of seats, number of rows , zones, number/coding of seats per row, etc.);
2. Will allow reading the characteristics of the event (ex: date, time, name, etc.);
3. Will allow the generation of nominal tickets according to the desired characteristics (ex: VIP, lawn, tribune, boxes, etc.);
4. The generated tickets will have a unique id that can be verified later (the id will be randomly generated so that there are no duplicate ids for the same event and no possibility for participants to guess the ticket ids);
5. The application will put at the user's disposal a menu where he/she will be able to enter the characteristics of the location and the event, he/she will be able to generate and later validate the issued tickets;
6. The application must handle any kind of input and will display error messages if input values are invalid;
7. The application will not generate execution errors for any type of input;

NO external (third party) libraries can be used for reading or validating data.
The solution must be implemented using only standard C++ libraries (such as iostream, string, fstream, string.h , etc) used in courses and laboratories. STL classes are only supported when explicitly requested (phase 2 only).


Example scenarios to consider:


Issuing football tickets in a stadium with two stands (Stand 1 and Stand 2). Each area has a row and place. Tickets for a specific match will be generated within the limit of available seats. When a user presents the ticket their unique ID will be checked to see if it is valid.
Issuing of movie tickets in the Normal or VIP categories. Each area has a row and place. Tickets will be generated within the limit of available seats. When a user presents the ticket their unique ID will be checked to see if it is valid.
Issuing of theater tickets from the Category 1, Category 2 and Box categories. Each area has a row and place. Tickets will be generated within the limit of available seats. When a user presents the ticket their unique ID will be checked to see if it is valid.


Phase 1:
Deadline: TBD

Minimum 3 classes related to the project
1. Classes must contain (in total, not each) at least one dynamically allocated vector of characters, one dynamically allocated numeric vector, one constant field, one static field and one method static. Members must be related to the class.
2. All attributes will be defined in the private area of ​​the class.
3. All attributes will have accessor methods; setters will contain validations.
4. Each class will contain at least 2 generic methods (other than constructors or accessors) that will be used to perform various processing.
5. Each class will contain at least one default constructor and one with parameters. Classes with pointer members will follow the "rule of 3".
6. Each class will contain overloads for << and >> operators.
7. Each class will have at least 2 overloaded operators from the following (the same operator cannot be overloaded in 2 different classes):
	- indexing operator []
	- arithmetic operators (+,-,* or /)
	- ++ or -- (both forms)
	- implicitly or explicitly cast
	- negation operator !
	- relational operators (<.>,=<,>=,==)
8. Classes will be implemented in their own header and/or cpp file.
9. Main function will be located in another cpp file.
This phase is considered implemented if at least 75% of requirements are implemented.
Changes to the project source code are managed using a Git repository. Is mandatory that students do multiple commits after each class implementation/update. Each commit must contain a short message detailing the changes. If the phase has less than 5 commits (in different days), it will not be taken into account.


Phase 2:
Deadline: TBD

1. The program can receive as a parameter in the command line mode of operation: if it uses a menu in the console or processes a text file with all input data (example: if the application is called oop.exe, then can be launched in execution in the following way: oop.exe data.txt, in which case it will process the data from the file received as a parameter).
2. The application can process data from a text file and will display the results on the console according to the above.
3. The application will use binary files to save tickets issued to date; when restarting the application the data will be restored.
4. All entities needed to implement the above functionality will be added to the existing classes (or new classes related to the project can be defined).
5. A menu will be implemented to help the user navigate through the different functionalities.
6. At least a new class will be created by deriving an existing class.
7. The application will contain at least one abstract class (can be interface) containing at least one pure virtual method. The pure method will be overdefined in a derived class.
8. Existing classes will have at least 2 virtual methods other than pure virtual ones. Methods will be overdefined by derived classes.
9. At least one STL class will be used in one of the existing classes.
10. The application must work turnkey (once started it will not require any further changes to the source code to expose all the functionality).
This phase is considered implemented if at least 75% of the requirements are implemented.
Changes to the project source code are managed using a Git repository. Is mandatory that students do multiple commits after each class implementation/update. Each commit must contain a short message detailing the changes. If the phase has less than 5 commits (in different days), it will not be taken into account.

BONUS:

The tickets will be generated in the form of a PDF that can be sent by email to the participant.
In this case the use of third party libraries is allowed to create the PDF file.





At least Phase 1


1 point - compliance with the uploading and structuring requirements of the project
3 points - each class correctly implemented as follows:
	1 point - the correct implementation of the class (according to the requirements - attributes, constructors, getters, setters, the rule of 3)
	1 point - the generic methods related to the class
	1 point - the operators (display and calculation)
-5 points - classes are not functional and cannot solve even one of the presented scenarios

* classes not related to the project will not be taken into account



At least Phase 2


1 point - compliance with the loading and structuring requirements of the project
0.5 points - the program can receive the file as a parameter in the command line
1 point - the application can process data from a text file
1 point - usage of binary files to save and restore data
1 point - existence of a functional menu according to requirements
1 point - existence of virtual and purely virtual methods
0.5 points - use of an STL container
4 points - correct treatment of the 3 proposed scenarios (1 point for each equation) + 1 script received at the presentation of the project
* Classes and/or methods not related to the project will not be taken into account