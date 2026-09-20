#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <vector>
#include "Resource.h"
#include "ActiveReservationList.h"

// Loads, stores, and displays campus resources.
//
// Resource file format (one resource per line, comma separated):
//     ID,Name,Type,Status          e.g.  R101,Study Room A,Study Room,Available
// Status must be "Available" or "Unavailable" (case does not matter).
// Blank lines and lines starting with '#' are ignored. Malformed lines are
// skipped with a warning; they never crash the program.
class ResourceManager
{
public:
    // Reads resources from a file. Returns true if at least one valid
    // resource was loaded. Prints a warning per bad line and a summary.
    bool loadFromFile(const std::string& filename);

    int getCount() const;

    // Finds a resource by ID (case-insensitive: "r101" finds "R101").
    // Returns NULL if there is no such resource.
    const Resource* findById(const std::string& id) const;

    // Prints every resource.
    void displayAll() const;

    // Prints each resource's availability on one date (YYYY-MM-DD):
    // "Available", "Reserved" (someone holds it that day), or "Out of service".
    void displayAvailability(const std::string& date,
                             const ActiveReservationList& active) const;

private:
    std::vector<Resource> resources_;
};

#endif
