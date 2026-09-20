#include "ReservationSystem.h"

#include <cctype>
#include <iostream>
#include "Utils.h"

static const std::string::size_type MAX_NAME_LENGTH = 50;

// Letters, spaces, hyphens, apostrophes, periods; at least one letter.
static bool isValidStudentName(const std::string& name)
{
    if (name.empty() || name.length() > MAX_NAME_LENGTH)
        return false;

    bool hasLetter = false;
    for (std::string::size_type i = 0; i < name.length(); ++i)
    {
        unsigned char c = static_cast<unsigned char>(name[i]);
        if (std::isalpha(c))
            hasLetter = true;
        else if (c != ' ' && c != '-' && c != '\'' && c != '.')
            return false;
    }
    return hasLetter;
}

ReservationSystem::ReservationSystem(const ResourceManager& resources,
                                     ActiveReservationList& active)
    : resources_(resources), active_(active), nextId_(1)
{
}

ValidationResult ReservationSystem::validate(int studentId, const std::string& studentName,
                                             const std::string& resourceId,
                                             const std::string& date) const
{
    if (studentId <= 0)
        return INVALID_STUDENT_ID;

    if (!isValidStudentName(trim(studentName)))
        return INVALID_STUDENT_NAME;

    const Resource* res = resources_.findById(resourceId);
    if (res == NULL)
        return UNKNOWN_RESOURCE;

    if (!res->isAvailable())
        return RESOURCE_OUT_OF_SERVICE;

    if (!isValidDate(date))
        return INVALID_DATE;

    const Reservation* existing = active_.findByResourceAndDate(res->getId(), date);
    if (existing != NULL)
    {
        if (existing->getStudentID() == studentId)
            return DUPLICATE_RESERVATION;
        return RESOURCE_BOOKED;
    }

    return VALID;
}

std::string ReservationSystem::describe(ValidationResult result)
{
    switch (result)
    {
    case VALID:
        return "Request is valid.";
    case INVALID_STUDENT_ID:
        return "Invalid student ID (must be a positive whole number).";
    case INVALID_STUDENT_NAME:
        return "Invalid student name (1-50 letters, spaces, hyphens, apostrophes).";
    case UNKNOWN_RESOURCE:
        return "That resource ID does not exist.";
    case RESOURCE_OUT_OF_SERVICE:
        return "That resource is currently out of service.";
    case INVALID_DATE:
        return "Invalid date (use a real date written as YYYY-MM-DD).";
    case DUPLICATE_RESERVATION:
        return "This student already has that resource reserved on that date.";
    case RESOURCE_BOOKED:
        return "That resource is already reserved on that date.";
    }
    return "Unknown validation error.";
}

ValidationResult ReservationSystem::createReservation(int studentId,
                                                      const std::string& studentName,
                                                      const std::string& resourceId,
                                                      const std::string& date,
                                                      int& newId)
{
    ValidationResult result = validate(studentId, studentName, resourceId, date);
    if (result != VALID)
        return result;

    // validate() succeeded, so the resource exists. Store its official ID
    // (so "r101" is saved as "R101").
    const Resource* res = resources_.findById(resourceId);

    newId = nextId_++;
    active_.push_front(newId, studentId, trim(studentName), res->getId(), date);
    return VALID;
}

bool ReservationSystem::cancelReservation(int reservationId, ReservationRecord& cancelled)
{
    const Reservation* r = active_.findById(reservationId);
    if (r == NULL)
        return false;

    // Copy the data BEFORE removing, because removal deletes the node.
    cancelled.reservationId = r->getReservationID();
    cancelled.studentId     = r->getStudentID();
    cancelled.studentName   = r->getStudentName();
    cancelled.resourceId    = r->getResourceID();
    cancelled.date          = r->getReservationDate();

    return active_.removeById(reservationId);
}

ValidationResult ReservationSystem::restoreReservation(const ReservationRecord& record)
{
    if (active_.findById(record.reservationId) != NULL)
        return DUPLICATE_RESERVATION;

    ValidationResult result = validate(record.studentId, record.studentName,
                                       record.resourceId, record.date);
    if (result != VALID)
        return result;

    active_.push_front(record.reservationId, record.studentId, record.studentName,
                       record.resourceId, record.date);
    return VALID;
}

void ReservationSystem::displayActive() const
{
    if (active_.isEmpty())
    {
        std::cout << "No active reservations.\n";
        return;
    }

    std::cout << "\n=== Active Reservations ===\n";
    active_.print();
    std::cout << "\n";
}
