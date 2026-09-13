#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>

// Reservation.h:
// Nodes in linked list for reservation management. Includes private information on reservations (gotten from reservations.txt input file) and methods to get information expanded upon in Reservation.cpp
// Probably could be edited to better suit other code?

class Reservation {
	public:
		// Constructor
		Reservation(int ReservID, int StudID, std::string Name, std::string ResourID, std::string Date);
		// Get data values
		int getReservationID() const;
		int getStudentID() const;
		std::string getStudentName() const;
		std::string getResourceID() const;
		std::string getReservationDate() const;

		// Next nodes in list
		Reservation* getNext() const;
		void setNext(Reservation* node);


	private:
		int ReservationID;
		int StudentID;
		std::string StudentName;
		std::string ResourceID;
		std::string ReservationDate;
		Reservation* next;

};

#endif
