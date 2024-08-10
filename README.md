# Ticketing App

Create an application that allows the management of tickets issued for different events (movie, play, football match, etc.)


The application will have the following functionalities:

- it will allow reading the characteristics of the event location (eg: maximum number of seats, number of rows , zones, number/coding of seats per row, etc.)
- will allow reading the characteristics of the event (ex: date, time, name, etc.)
- will allow the generation of nominal tickets according to the desired characteristics (ex: VIP, lawn, tribune, boxes, etc.) .)
- the generated tickets will have a unique id that can be verified later (the id will be randomly generated so that there are no duplicate ids for the same event and no possibility for participants to guess the ticket ids)
- the application will put at the user's disposal a menu where he/she will be able to enter the characteristics of the location and the event, he/she will be able to generate and later validate the issued tickets,
- the application must handle any kind of input and will display error messages if input values are invalid
- the application will not generate execution errors for any type of input
- NO external (third party) libraries can be used for reading or validating data
- the solution must be implemented using only standard C++ libraries (such as iostream, string, fstream, string.h , etc) used in courses and laboratories. STL classes are only supported when explicitly requested (phase 2 only)


Example scenarios to consider:


- Issuing football tickets in a stadium with two stands (Stand 1 and Stand 2 ). Each area has a row and place. Tickets for a specific match will be generated within the limit of available seats. When a user presents the ticket their unique ID will be checked to see if it is valid.
- Issuance of movie tickets in the Normal or VIP categories. Each area has a row and place. Tickets will be generated within the limit of available seats. When a user presents the ticket their unique ID will be checked to see if it is valid.
- Issuance of theater tickets from the Category 1, Category 2 and Box categories. Each area has a row and place. Tickets will be generated within the limit of available seats. When a user presents the ticket their unique ID will be checked to see if it is valid.
