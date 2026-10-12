// Temporary test menu for the Resource and Reservation modules.
// Whoever integrates the queue (waiting list) and stack (cancellation history)
// will extend this menu. The team should end up with ONE main().

#include <iostream>
#include <string>
#include "ResourceManager.h"
#include "ReservationSystem.h"
#include "ActiveReservationList.h"
#include "CancellationTracker.h"
#include "Utils.h"
#include "WaitingList.h"
#include "ReservationManager.h"

// Prompts until the user enters a valid int. Returns false on end of input.
static bool promptInt(const std::string& prompt, int& out)
{
    std::string line;
    while (true)
    {
        std::cout << prompt;
        if (!std::getline(std::cin, line))
            return false;
        if (parseInt(line, out))
            return true;
        std::cout << "  Please enter a whole number.\n";
    }
}

static bool promptString(const std::string& prompt, std::string& out)
{
    std::cout << prompt;
    if (!std::getline(std::cin, out))
        return false;
    out = trim(out);
    return true;
}

static void printMenu()
{
    std::cout << "\n===== Campus Resource Reservation System =====\n"
              << " 1. Display all resources\n"
              << " 2. Display resource availability for a date\n"
              << " 3. Create a reservation\n"
              << " 4. Cancel a reservation\n"
              << " 5. Display active reservations\n"
              << " 6. Display cancellation history\n"
              << " 7. Restore latest cancelled reservation\n"
              //<< " 8. Search for a reservation record (by reservation ID)\n"
              //<< " 9. Search for a reservation record (by resource and date)\n"
              << " 0. Exit\n";
}

int main(int argc, char* argv[])
{
    std::string filename = (argc > 1) ? argv[1] : "resources.txt";

    ResourceManager resources;
    if (!resources.loadFromFile(filename))
    {
        std::cout << "No usable resources were loaded. Exiting.\n";
        return 1;
    }

    ActiveReservationList activeList;               // Dylan's linked list
    ReservationSystem reservations(resources, activeList);

    //WaitingList waitingList;
    CancellationTracker cancellationTracker;

    ReservationManager resman;

    int choice = -1;
    while (choice != 0)
    {
        printMenu();
        if (!promptInt("Choice: ", choice))
            break;                                  // end of input

        if (choice == 1)
        {
            resources.displayAll();
        }
        else if (choice == 2)
        {
            std::string date;
            if (!promptString("Date (YYYY-MM-DD): ", date))
                break;
            resources.displayAvailability(date, activeList);
        }
        else if (choice == 3)
        {
            int studentId;
            std::string name, resourceId, date;
            if (!promptInt("Student ID: ", studentId) ||
                !promptString("Student name: ", name) ||
                !promptString("Resource ID: ", resourceId) ||
                !promptString("Date (YYYY-MM-DD): ", date))
                break;

            int newId = 0;
            ValidationResult r = reservations.createReservation(studentId, name, resourceId, date, newId);
            if (r == VALID)
            {
                std::cout << "Reservation #" << newId << " created.\n";
            }

            else
            {
                std::cout << "Could not reserve: " << ReservationSystem::describe(r) << "\n"/*Added to waiting list."*/;
                //waitingList.Enqueue(newId, studentId, name, resourceId, date);
            }
        }
        else if (choice == 4)
        {
            int id;
            if (!promptInt("Reservation ID to cancel: ", id))
                break;

            ReservationRecord cancelled;
            if (reservations.cancelReservation(id, cancelled))
            {
                std::cout << "Reservation #" << cancelled.reservationId << " cancelled.\n";
                Reservation cancelRecord(cancelled.reservationId, cancelled.studentId, cancelled.studentName, cancelled.resourceId, cancelled.date);
                cancellationTracker.CancelReservation(cancelRecord);
            }
            else
                std::cout << "No active reservation with ID " << id << ".\n";
        }
        else if (choice == 5)
        {
            reservations.displayActive();
        }

        else if (choice == 6)
        {
            cancellationTracker.DisplayCancellationHistory();
        }

        else if (choice == 7)
        {
            Reservation x = cancellationTracker.RestoreReservation();

            int newId = 0;
            ValidationResult r = reservations.createReservation(x.getStudentID(),x.getStudentName(),x.getResourceID(),x.getReservationDate(), newId);

            if (r == VALID)
            {
                std::cout << "Reservation #" << newId << " created.\n";
            }

            else
            {
                std::cout << "Could not reserve: " << ReservationSystem::describe(r) << "\n"/*Added to waiting list."*/;
                //waitingList.Enqueue(newId, studentId, name, resourceId, date);
            }
        }

        else if (choice == 8)
        {
            int reservationId;
            std::string name, resourceId, date;
            if (!promptInt("Reservation ID: ", reservationId))
                break;

            std::cout << reservationId << "\n";

            const Reservation* x;
            x = resman.findById(reservationId);
            if (x != nullptr)
            {
                std::cout << "Reservation ID: " << x->getReservationID()
              << " | Student ID: " << x->getStudentID()
              << " | Student Name: " << x->getStudentName()
              << " | Resource ID: " << x->getResourceID()
              << " | Reservation Date: " << x->getReservationDate() << std::endl;
            }
            else
            {
                std::cout << "No active reservation with ID " << reservationId << ".\n";
            }
        }

        else if (choice == 9)
        {
            //String reservationInfo;
            string resourceId;
            string resourceDate;
            //std::string name, resourceId, date;
            if (!promptString("Reservation Resource ID:  ", resourceId) ||
                !promptString("Resource Date (YYYY-MM-DD):  ", resourceDate))
            break;
            {
                const Reservation* x;
                x = resman.findByResourceAndDate(resourceId, resourceDate);
                if (x != nullptr)
                {
                    std::cout << "Reservation ID: " << x->getReservationID()
                  << " | Student ID: " << x->getStudentID()
                  << " | Student Name: " << x->getStudentName()
                  << " | Resource ID: " << x->getResourceID()
                  << " | Reservation Date: " << x->getReservationDate() << std::endl;
                }
                else
                {
                    std::cout << "404: No active reservation found\n";
                }
            }
        }

        else if (choice != 0)
        {
            std::cout << "Invalid choice.\n";
        }
    }

    std::cout << "Goodbye.\n";
    return 0;
}
