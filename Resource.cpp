#include "Resource.h"

Resource::Resource()
    : id_(""), name_(""), type_(""), available_(false)
{
}

Resource::Resource(const std::string& id, const std::string& name,
                   const std::string& type, bool available)
    : id_(id), name_(name), type_(type), available_(available)
{
}

const std::string& Resource::getId() const { return id_; }
const std::string& Resource::getName() const { return name_; }
const std::string& Resource::getType() const { return type_; }
bool Resource::isAvailable() const { return available_; }

std::string Resource::getStatusText() const
{
    return available_ ? "Available" : "Unavailable";
}
