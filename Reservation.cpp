#include "Reservation.h"

// Reservation.cpp
// All the functions listed in the Reservation class in Reservation.h

// Constructor to fill out node data with inputted data
Reservation::Reservation(int ReservID, int StudID, std::string Name, std::string ResourID, std::string Date) {
	ReservationID = ReservID;
	StudentID = StudID;
	StudentName = Name;
	ResourceID = ResourID;
	ReservationDate = Date;
	next = nullptr;
}

// get functions to return values for ReservationID, StudentID, StudentName, ResourceID, and ReservationDate in order

int Reservation::getReservationID() const {
	return ReservationID;
}

int Reservation::getStudentID() const {
        return StudentID;
}

std::string Reservation::getStudentName() const {
        return StudentName;
}

std::string Reservation::getResourceID() const {
        return ResourceID;
}

std::string Reservation::getReservationDate() const {
        return ReservationDate;
}

// Node functions

Reservation* Reservation:: getNext() const {
	return next;
}

void Reservation::setNext(Reservation* node) {
	next = node;
}
