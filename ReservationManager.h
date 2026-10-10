#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H
#include <string>

#include "Reservation.h"

//ReservationManager.h
//The framework of the linked list. Utilizes information from Reservation for nodes, you can add nodes with inputted information, remove nodes, and traverse the list.
// Also includes two types of MergeSort functions within

class ReservationManager {
	public:
		// Constructor and deconstructor
		ReservationManager();
		~ReservationManager();

        // Add reservations to the linked list, either at the front or anywhere within the list
		void push_front(int ReservID, int StudID, std::string Name, std::string ResourID, std::string Date);
		void add(int pos, int ReservID, int StudID, std::string Name, std::string ResourID, std::string Date);

        // Remove a reservation at a specified position in the list
		void remove(int pos);

		// Print each node and its information
		void print() const;

		// Extra functions to check for empty list or operate using certain parameters
        bool isEmpty() const;
        const Reservation* findById(int reservationId) const;
        const Reservation* findByResourceAndDate(const std::string& resourceId, const std::string& date) const;
        bool removeById(int reservationId);

        // Public Merge Sort functions to be called, either sort by Reservation ID or Resource ID
        void SortByReservID();
        void SortByResourID();

	private:
		Reservation* head;
        // Private Merge Sort functions that act within the public functions. Two for each sort type respectively
        Reservation* MergeSortReservID(Reservation* first);
        Reservation* MergeReservID(Reservation* left, Reservation* right);

        Reservation* MergeSortResourID(Reservation* first);
        Reservation* MergeResourID(Reservation* left, Reservation* right);
};

#endif
