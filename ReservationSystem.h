#ifndef RESERVATION_SYSTEM_H
#define RESERVATION_SYSTEM_H

#include <string>
#include "ResourceManager.h"
#include "ActiveReservationList.h"

// A plain copy of a reservation's data (no linked-list pointer inside).
// cancelReservation() fills one of these so the cancellation STACK can store
// it safely, and restoreReservation() accepts one back for UNDO.
struct ReservationRecord
{
    int reservationId;
    int studentId;
    std::string studentName;
    std::string resourceId;
    std::string date;
};

// Result of validating a reservation request. The menu / waiting list code can
// branch on this: RESOURCE_BOOKED is the moment to offer the waiting list.
enum ValidationResult
{
    VALID,
    INVALID_STUDENT_ID,        // must be a positive whole number
    INVALID_STUDENT_NAME,      // empty, too long, or has odd characters
    UNKNOWN_RESOURCE,          // no such resource ID
    RESOURCE_OUT_OF_SERVICE,   // resource status is "Unavailable"
    INVALID_DATE,              // not a real YYYY-MM-DD date
    DUPLICATE_RESERVATION,     // this student already holds it that day
    RESOURCE_BOOKED            // somebody else holds it that day
};

// Create / cancel / validate / display reservations.
// The active reservations themselves live in Dylan's linked list, which is
// passed in by reference so the whole team shares the SAME list.
class ReservationSystem
{
public:
    ReservationSystem(const ResourceManager& resources, ActiveReservationList& active);

    // Checks a request without changing anything.
    ValidationResult validate(int studentId, const std::string& studentName,
                              const std::string& resourceId, const std::string& date) const;

    static std::string describe(ValidationResult result);

    // Validates, then inserts a new reservation with the next unique ID.
    // On VALID, 'newId' holds the new reservation's ID.
    ValidationResult createReservation(int studentId, const std::string& studentName,
                                       const std::string& resourceId, const std::string& date,
                                       int& newId);

    // Removes a reservation by its ID. On success, 'cancelled' receives a copy
    // of its data (push this onto the cancellation stack). False if not found.
    bool cancelReservation(int reservationId, ReservationRecord& cancelled);

    // Puts a previously cancelled reservation back with its ORIGINAL ID, after
    // re-validating it (someone else may have booked that resource/date since).
    ValidationResult restoreReservation(const ReservationRecord& record);

    void displayActive() const;

private:
    const ResourceManager& resources_;
    ActiveReservationList& active_;
    int nextId_;
};

#endif
