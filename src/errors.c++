#ifndef ERRORS_CPP
#define ERRORS_CPP

#include <stdexcept>
#include <string>

class ParsingError : public std::runtime_error
{
  public:
    ParsingError(const std::string& message) : std::runtime_error(message) {}
};

#endif
