#ifndef CANCELLATIONTRACKER_H
#define CANCELLATIONTRACKER_H

#include "Reservation.h"

using namespace std;

class CancellationTracker {

public:
	//default no-arg constructor
	CancellationTracker();

	//Cancels a reservation
	void CancelReservation(Reservation *r);

	//Restores the latest cancelled reservation
	Reservation *RestoreReservation();

	//Prints cancelled reservation history
	void DisplayCancellationHistory();

private:
	stack<Reservation *> cancellationHistory;

	//Logs cancelled and restored reservations in a vector, true = cancelled, false = restored.
	vector<pair <Reservation * , bool> > cancellationHistoryLog;

};

#endif