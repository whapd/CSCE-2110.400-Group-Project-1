#ifndef REPORTGENERATING_H
#define REPORTGENERATING_H

#include "Reservation.h"
#include "Resource.h"
#include "ResourceManager.h"

// ReportGenerating.h
// This file includes four different functions meant to generate reports and statistics based on reservations and resources

// CountByID() is a helper function to the other functions listed here, tallies up reservations tied to an inputted resource (ID integer)
int CountByID(Reservation* head, int targetID);

// Active Reservations - already implemented in the ReservationManager linked list as ReservationManager::print()

// Resource Utilization - involves the functions CountByID and ResourceReport, CountByID tallies up reservations that are tied to an inputted resource (ID integer), ResourceReport prints tallies with each resource
void ResourceReport(Resource resourceVector[], Reservation* head);

// Waiting List Statistics - builds off same structure as ResourceReport tailored to the Waiting List
void WaitingListReport(Resource resourceVector[], Reservation* head);

#endif

