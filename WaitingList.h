#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include "Reservation.h"
#include <iostream>

// WaitingList.h
// Includes the code for the Waiting List queue implemented like a linked list, this file is the 'linked list' portion that uses Reservation objects as nodes (pending reservations)

class WaitingList {
		public:
			// Constructor and deconstructor
			WaitingList();
			~WaitingList();

			// Add an element to front of waiting list
			void Enqueue(int ReservID, int StudID, std::string Name, std::string ResourID, std::string Date);
			// Remove element from front of waiting list
			void Dequeue();

			// Read element at front of waiting list
			void Peek();

			// Check if waiting list is empty
			bool isEmpty() const;
		private:
			Reservation* head;
			Reservation* tail;

};

#endif
