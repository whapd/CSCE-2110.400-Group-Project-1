#include "Search.h"

#include "Utils.h"

const Resource* searchResourceById(const ResourceManager& resources, const std::string& id)
{
    std::string target = toLower(trim(id));
    const std::vector<Resource>& all = resources.getAllResources();

    // --- Linear Search ---
    // Check each element in order until a match is found or the list ends.
    // Worst case (no match, or match is last) visits every element: O(n).
    for (std::size_t i = 0; i < all.size(); ++i)
    {
        if (toLower(all[i].getId()) == target)
            return &all[i];
    }
    return NULL;
}

const Reservation* searchReservationById(const ActiveReservationList& active, int reservationId)
{
    std::vector<const Reservation*> all = active.getAllActive();

    // --- Linear Search ---
    for (std::size_t i = 0; i < all.size(); ++i)
    {
        if (all[i]->getReservationID() == reservationId)
            return all[i];
    }
    return NULL;
}

std::vector<const Reservation*> searchReservationsByStudent(const ActiveReservationList& active,
                                                             int studentId)
{
    std::vector<const Reservation*> all = active.getAllActive();
    std::vector<const Reservation*> matches;

    // --- Linear Search (collecting every match, not just the first) ---
    // Unlike the two functions above, this cannot stop early: a student
    // may hold several reservations, so every element must be checked
    // regardless of whether earlier ones matched. Still O(n).
    for (std::size_t i = 0; i < all.size(); ++i)
    {
        if (all[i]->getStudentID() == studentId)
            matches.push_back(all[i]);
    }
    return matches;
}
