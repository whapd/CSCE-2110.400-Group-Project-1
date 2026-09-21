#include <iostream>
#include <ofstream>

#include "Reservation.h"
#include "CancellationTracker.h"

using namespace std;

class CancellationTracker {

public:
    CancellationTracker();

    void CancelReservation(Reservation *r){
        cancellationHistory.push(r);
        cancellationHistoryLog.push_back(make_pair(r, true));
}

    Reservation *RestoreReservation()
    {

        reservation *r =  cancellationHistory.pop();
        cancellationHistoryLog.push_back(make_pair(r, false));
        return r;
    }

    void DisplayCancellationHistory()
    {
        for (pair<Reservation *, bool> entry : cancellationHistoryLog)
        {
            if (entry.second)
            {
                cout << "--cancelled--" << endl;
            }
            else
            {
                cout << "--restored--" << endl;
            }

            //cout << entry.first << endl;
            //copied from reservation manager, would be better to add method to Reservation.cpp/h
            std::cout << "Reservation ID: " << curr->getReservationID()
              << " | Student ID: " << curr->getStudentID()
              << " | Student Name: " << curr->getStudentName()
              << " | Resource ID: " << curr->getResourceID()
              << " | Reservation Date: " << curr->getReservationDate() << std::endl;
        }
    }

private:


};
