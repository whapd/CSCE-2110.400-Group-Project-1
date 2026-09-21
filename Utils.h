#ifndef UTILS_H
#define UTILS_H

#include <string>

// Removes leading/trailing whitespace (including '\r' from Windows line endings).
std::string trim(const std::string& s);

// Returns a lowercase copy of s.
std::string toLower(const std::string& s);

// Safely converts a string to an int. Returns false if the string is empty,
// has non-numeric characters, or is out of range. Never throws.
bool parseInt(const std::string& s, int& out);

// True if s is a real calendar date written as YYYY-MM-DD (year 2000-2100,
// month 1-12, day valid for that month, leap years handled).
bool isValidDate(const std::string& s);

#endif
