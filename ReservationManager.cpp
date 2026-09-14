#include "ReservationManager.h"
#include <iostream>

// ReservationManager.cpp
// All functions to be used for the linked list ReservationManager. Takes info and function with the Reservation class to get data within reservations.

// Constructor to initialize an empty ReservationManager list
ReservationManager::ReservationManager() {
	head = nullptr;
}

// Deconstructor to delete entire ReservationManager list if need be
ReservationManager::~ReservationManager() {
	Reservation* curr = head;
	while (curr != nullptr) {
		Reservation* next = curr->getNext();
		delete curr;
		curr = curr->getNext();
	}
}

// ReservationManager.push_front() to add a reservation (node) to the front of the Reservation Manager list
void ReservationManager::push_front(int ReservID, int StudID, std::string Name, std::string ResourID, std::string Date) {
		Reservation* newHead = new Reservation(ReservID, StudID, Name, ResourID, Date);
		newHead->setNext(head);
		head = newHead;
}

// ReservationManager.add() to add a reservation (node) at any point in the Reservation Manager
void ReservationManager::add(int pos, int ReservID, int StudID, std::string Name, std::string ResourID, std::string Date) {
	// Find reservation before position to add at
	Reservation* curr = head;
	for (int i = 0; i < pos - 1; i++) {
		if (curr == nullptr) {
			return;
		}
		curr = curr->getNext();
	}

	// If curr iterates to end of list then end
	if (curr == nullptr) {
		return;
	}

	// Add reservation at that position in the Reservation Manager list
	Reservation* newReserv = new Reservation(ReservID, StudID, Name, ResourID, Date);
	newReserv->setNext(curr->getNext());
	newReserv = curr->getNext();
}

// ReservationManager.remove() to remove a reservation (node) at any point in the Reservation Manager list
void ReservationManager::remove(int pos) {

	// Abort if Reservation Manager list is empty
	if (head == nullptr) {
		return;
	}

	// If the reservation you want to delete is at the front
	if (pos == 0) {
		Reservation* oldHead = head;
		head = head->getNext();
		delete oldHead;
		return;
	}

	// Iterate to reservation before the position you want to delete at
	Reservation* curr = head;
	for (int i = 0; i < pos - 1; i++) {
		if (curr == nullptr || curr->getNext() == nullptr) {
			return;
		}

		curr->setNext(curr->getNext());
	}

	// Make sure there's actually a reservation to delete before deleting it
	if (curr->getNext() == nullptr) {
		return;
	}
	Reservation* del = curr->getNext();
	curr->setNext(del->getNext());
	delete del;
}

// ReservationManager.print() to traverse list and print reservation info
void ReservationManager::print() const {
	Reservation* curr = head;
	while (curr != nullptr) {
		std::cout << "Reservation ID: " << curr->getReservationID()
			  << " | Student ID: " << curr->getStudentID()
			  << " | Student Name: " << curr->getStudentName()
			  << " | Resource ID: " << curr->getResourceID()
			  << " | Reservation Date: " << curr->getReservationDate() << std::endl;
		curr = curr->getNext();
	}
}
