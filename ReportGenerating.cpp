#include "ReportGenerating.h"
#include "ReservationManager.h"
#include "Reservation.h"

#include <iostream>
#include <vector>

// ReportGenerating.cpp
// Contains the code for each four functions described with ReportGenerating.h for generating reports based on data and statistics on reservations and resources within the system

// As stated in ReportGenerating.h, the function for generating information on active reports is ReservationManager::print()

// Resource Utilization
// CountByID() - helper function to ResourceReport() and WaitingListReport(), counts the amount of active reservations tied to one resource
int CountByID(Reservation *head, std::string targetID) {
	int count = 0;
	Reservation *curr = head;

	while (curr != nullptr) {
		if (findById(targetID) != NULL) {
			count++;
		}
	}

	return count;
}

// ResourceReport() - Given a vector of resources and the head of the reservation linked list, iterates through resource vector and uses ReservationCount() to tally up all active reservations for each resources. 
void ResourceReport(Resource resourceVector[], Reservation *head) {
	for (int i = 0; i < resourceVector.size(); i++) {
		int reservations = CountByID(head, resourceVector[i].resourceID);

		cout << "Resource ID: " << resourceVector[i].resourceID << endl;
		cout << "Active Reservations: " << reservations << endl;
		cout << "----------------------------" << endl;
	}
}

// WaitingListReport() - Operates nearly the same as ResourceReport(), but is instead tailored towards the Waiting List
void WaitingListReport(Resource resourceVector[], Reservation *head) {
	// Declare vector to store frequencies of resources in waiting list
	vector<int> topReservations;

	// Waiting List Report
        for (int i = 0; i < resourceVector.size(); i++) {
                int reservations = CountByID(head, resourceVector[i].resourceID);

                cout << "Resource ID: " << resourceVector[i].resourceID << endl;
                cout << "Currently Pending Reservations: " << reservations << endl;
                cout << "----------------------------" << endl;
		topReservations.push_back(reservations);
        }
}
