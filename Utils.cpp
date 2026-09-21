#include "Utils.h"

#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdlib>

std::string trim(const std::string& s)
{
    const char* whitespace = " \t\r\n";
    std::string::size_type start = s.find_first_not_of(whitespace);
    if (start == std::string::npos)
        return "";
    std::string::size_type end = s.find_last_not_of(whitespace);
    return s.substr(start, end - start + 1);
}

std::string toLower(const std::string& s)
{
    std::string out = s;
    for (std::string::size_type i = 0; i < out.length(); ++i)
        out[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(out[i])));
    return out;
}

bool parseInt(const std::string& s, int& out)
{
    std::string t = trim(s);
    if (t.empty())
        return false;

    errno = 0;
    char* endPtr = NULL;
    long value = std::strtol(t.c_str(), &endPtr, 10);

    if (errno != 0 || *endPtr != '\0')
        return false;
    if (value < INT_MIN || value > INT_MAX)
        return false;

    out = static_cast<int>(value);
    return true;
}

bool isValidDate(const std::string& s)
{
    if (s.length() != 10 || s[4] != '-' || s[7] != '-')
        return false;

    for (std::string::size_type i = 0; i < s.length(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
            return false;
    }

    int year  = std::atoi(s.substr(0, 4).c_str());
    int month = std::atoi(s.substr(5, 2).c_str());
    int day   = std::atoi(s.substr(8, 2).c_str());

    if (year < 2000 || year > 2100 || month < 1 || month > 12)
        return false;

    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month == 2 && leap)
        maxDay = 29;

    return day >= 1 && day <= maxDay;
}
