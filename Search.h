#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>
#include "ResourceManager.h"
#include "ActiveReservationList.h"

// ---------------------------------------------------------------------
// Milestone 2 - Searching
//
// Algorithm chosen: LINEAR SEARCH, written by hand below (no std::find,
// no library search of any kind).
//
// Why linear and not binary: active reservations are stored in a singly
// linked list (ReservationManager / Reservation::next). Binary search
// needs random access to the middle element in O(1), which a linked
// list cannot do; walking to the middle each step would make it O(n)
// per probe anyway, erasing the benefit over a plain linear scan. The
// resource list is a small std::vector loaded once from a file, so an
// O(n) scan is already fast enough that sorting it first (and keeping
// it sorted) would cost more than it saves. Every search below is
// therefore O(n), and is written as an explicit loop so it is clearly
// the team's own code, not a wrapped library call.
// ---------------------------------------------------------------------

// Linear search over the resources loaded by ResourceManager, matching
// an ID case-insensitively ("r101" matches "R101"). Returns NULL if no
// resource has that ID.
const Resource* searchResourceById(const ResourceManager& resources, const std::string& id);

// Linear search over the active reservation list for one exact
// reservation ID. Returns NULL if no active reservation has that ID.
const Reservation* searchReservationById(const ActiveReservationList& active, int reservationId);

// Linear search over the active reservation list, collecting EVERY
// reservation that belongs to the given student ID (a student may hold
// more than one reservation at once). Returns an empty vector if the
// student has none active. This is the "reservations associated with
// a specific student" application from the project spec.
std::vector<const Reservation*> searchReservationsByStudent(const ActiveReservationList& active,
                                                             int studentId);

#endif
