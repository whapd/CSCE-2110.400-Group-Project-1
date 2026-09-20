#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

// A reservable campus resource. Fields follow the project spec:
// Resource ID, Resource Name, Resource Type, Availability Status.
//
// Availability Status in the resource file is either "Available" or
// "Unavailable" (out of service, e.g. under maintenance). Whether a resource
// is already reserved on a particular date is a separate question that is
// answered from the active reservation list.
class Resource
{
public:
    Resource();
    Resource(const std::string& id, const std::string& name,
             const std::string& type, bool available);

    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getType() const;
    bool isAvailable() const;
    std::string getStatusText() const;   // "Available" or "Unavailable"

private:
    std::string id_;
    std::string name_;
    std::string type_;
    bool available_;
};

#endif
