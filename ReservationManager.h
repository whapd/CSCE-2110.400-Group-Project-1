#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H
#include <string>

#include "Reservation.h"

//ReservationManager.h
//The framework of the linked list. Utilizes information from Reservation for nodes, you can add nodes with inputted information, remove nodes, and traverse the list.

class ReservationManager {
	public:
		ReservationManager();
		~ReservationManager();
		void push_front(int ReservID, int StudID, std::string Name, std::string ResourID, std::string Date);
		void add(int pos, int ReservID, int StudID, std::string Name, std::string ResourID, std::string Date);
		void remove(int pos);
		void print() const;
	private:
		Reservation* head;
};

#endif
