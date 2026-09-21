#include "ResourceManager.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include "Utils.h"

// Splits a line on commas (names must not contain commas).
static std::vector<std::string> splitCommas(const std::string& line)
{
    std::vector<std::string> fields;
    std::string::size_type start = 0;
    while (true)
    {
        std::string::size_type comma = line.find(',', start);
        if (comma == std::string::npos)
        {
            fields.push_back(line.substr(start));
            break;
        }
        fields.push_back(line.substr(start, comma - start));
        start = comma + 1;
    }
    return fields;
}

bool ResourceManager::loadFromFile(const std::string& filename)
{
    std::ifstream in(filename.c_str());
    if (!in)
    {
        std::cout << "Error: could not open resource file '" << filename << "'.\n";
        return false;
    }

    resources_.clear();

    std::string line;
    int lineNo = 0, loaded = 0, skipped = 0;

    while (std::getline(in, line))
    {
        ++lineNo;
        line = trim(line);
        if (line.empty() || line[0] == '#')
            continue;

        std::vector<std::string> f = splitCommas(line);
        if (f.size() != 4)
        {
            std::cout << "Warning (line " << lineNo << "): expected 4 fields "
                      << "(ID,Name,Type,Status); skipped.\n";
            ++skipped;
            continue;
        }

        std::string id     = trim(f[0]);
        std::string name   = trim(f[1]);
        std::string type   = trim(f[2]);
        std::string status = toLower(trim(f[3]));

        if (id.empty() || id.find(' ') != std::string::npos)
        {
            std::cout << "Warning (line " << lineNo << "): resource ID must be "
                      << "non-empty and contain no spaces; skipped.\n";
            ++skipped;
        }
        else if (name.empty() || type.empty())
        {
            std::cout << "Warning (line " << lineNo << "): name or type is empty; skipped.\n";
            ++skipped;
        }
        else if (status != "available" && status != "unavailable")
        {
            std::cout << "Warning (line " << lineNo << "): status must be "
                      << "'Available' or 'Unavailable'; skipped.\n";
            ++skipped;
        }
        else if (findById(id) != NULL)
        {
            std::cout << "Warning (line " << lineNo << "): duplicate resource ID '"
                      << id << "'; skipped.\n";
            ++skipped;
        }
        else
        {
            resources_.push_back(Resource(id, name, type, status == "available"));
            ++loaded;
        }
    }

    std::cout << "Loaded " << loaded << " resource(s) from '" << filename << "'";
    if (skipped > 0)
        std::cout << " (" << skipped << " line(s) skipped)";
    std::cout << ".\n";

    return loaded > 0;
}

int ResourceManager::getCount() const
{
    return static_cast<int>(resources_.size());
}

const Resource* ResourceManager::findById(const std::string& id) const
{
    std::string wanted = toLower(trim(id));
    for (std::size_t i = 0; i < resources_.size(); ++i)
    {
        if (toLower(resources_[i].getId()) == wanted)
            return &resources_[i];
    }
    return NULL;
}

void ResourceManager::displayAll() const
{
    if (resources_.empty())
    {
        std::cout << "No resources loaded.\n";
        return;
    }

    std::cout << "\n=== Campus Resources ===\n";
    std::cout << std::left
              << std::setw(9)  << "ID"
              << std::setw(34) << "Name"
              << std::setw(16) << "Type"
              << "Status\n";
    std::cout << std::string(67, '-') << "\n";

    for (std::size_t i = 0; i < resources_.size(); ++i)
    {
        const Resource& r = resources_[i];
        std::cout << std::left
                  << std::setw(9)  << r.getId()
                  << std::setw(34) << r.getName()
                  << std::setw(16) << r.getType()
                  << r.getStatusText() << "\n";
    }
    std::cout << "\n";
}

void ResourceManager::displayAvailability(const std::string& date,
                                          const ActiveReservationList& active) const
{
    if (!isValidDate(date))
    {
        std::cout << "Error: date must be a real date written as YYYY-MM-DD.\n";
        return;
    }
    if (resources_.empty())
    {
        std::cout << "No resources loaded.\n";
        return;
    }

    std::cout << "\n=== Availability on " << date << " ===\n";
    std::cout << std::left
              << std::setw(9)  << "ID"
              << std::setw(34) << "Name"
              << "Status\n";
    std::cout << std::string(60, '-') << "\n";

    for (std::size_t i = 0; i < resources_.size(); ++i)
    {
        const Resource& r = resources_[i];

        std::string status;
        if (!r.isAvailable())
            status = "Out of service";
        else if (active.findByResourceAndDate(r.getId(), date) != NULL)
            status = "Reserved";
        else
            status = "Available";

        std::cout << std::left
                  << std::setw(9)  << r.getId()
                  << std::setw(34) << r.getName()
                  << status << "\n";
    }
    std::cout << "\n";
}
