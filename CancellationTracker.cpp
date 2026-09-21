#include <iostream>
//#include <ofstream>

#include "Reservation.h"
#include "CancellationTracker.h"

using namespace std;




    CancellationTracker::CancellationTracker(){};//no-arg constructor

    void CancellationTracker::CancelReservation(Reservation *r){
        cancellationHistory.push(r);
        cancellationHistoryLog.push_back(make_pair(r, true));
}

    Reservation * CancellationTracker::RestoreReservation()
    {

        Reservation *r =  cancellationHistory.top();
        cancellationHistory.pop();

        cancellationHistoryLog.push_back(make_pair(r, false));
        return r;
    }

    void CancellationTracker::DisplayCancellationHistory()
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
            std::cout << "Reservation ID: " << entry.first->getReservationID()
              << " | Student ID: " << entry.first->getStudentID()
              << " | Student Name: " << entry.first->getStudentName()
              << " | Resource ID: " << entry.first->getResourceID()
              << " | Reservation Date: " << entry.first->getReservationDate() << std::endl;
        }
    }





