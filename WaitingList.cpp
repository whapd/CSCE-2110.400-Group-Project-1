#include "WaitingList.h"
#include <iostream>

// WaitingList.cpp
// All functions and code for the Waiting List queue/linked list

// Constructor to initialize an empty waiting list
WaitingList::WaitingList() {
	head = nullptr;
}

// Deconstructor to delete entire waiting list if need be
WaitingList::~WaitingList() {
	while (head != nullptr) {
		Reservation* temp = head;
		head = head->getNext();
		delete temp;
	}

	tail = nullptr;
}

// WaitingList.Enqueue() to add a pending reservation(node) to the front of the waiting list
void WaitingList::Enqueue(int ReservID, int StudID, std::string Name, std::string ResourID, std::string Date) {
	Reservation* newNode = new Reservation(ReservID, StudID, Name, ResourID, Date);
	
	// If waiting list is empty
	if (isEmpty()) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->setNext(newNode);
		tail = newNode;
	}
}

// WaitingList.Dequeue to remove pending reservation(node) from front of waiting list
void WaitingList::Dequeue() {
	// If waiting list is empty
	if (isEmpty()) {
		std::cout << "Cannot remove from an empty waiting list." << std::endl;
	}

	// Else remove pending reservation from front of waiting list
	else {
		Reservation* temp = head;
		head = head->getNext();
		delete temp;

		// If the waiting list is now empty after removing, set tail to empty as well
		if (head == nullptr) {
			tail == nullptr;
		}
	}
}

//WaitingList.Peek() reads and prints the data at the front of the waiting list
void WaitingList::Peek() {
	// If waiting list is empty
	if (isEmpty()) {
		std::cout << "Waiting list is empty." << std::endl;
	}
	else {
		Reservation* curr = head;
		while (curr != nullptr) {
			std::cout << "Reservation ID: " << curr->getReservationID()
				<< " | Student ID: " << curr->getStudentID()
			  	<< " | Student Name: " << curr->getStudentName()
			  	<< " | Resource ID: " << curr->getResourceID()
			  	<< " | Reservation Date: " << curr->getReservationDate() << std::endl;
		}
	}
}	


// WaitingList.isEmpty() checks if waiting list is empty. Important when first creating waiting list
bool WaitingList::isEmpty() const {
	return head == nullptr;
}
