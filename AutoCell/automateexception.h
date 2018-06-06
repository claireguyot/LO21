#ifndef AUTOMATEEXCEPTION_H
#define AUTOMATEEXCEPTION_H
#include <string>
#include <exception>
class AutomateException : public std::exception {
public:
    AutomateException(const std::string& message) throw() :info(message) {}
    char const* what() const throw() { return info.c_str(); }
private:
    std::string info;
};

#endif // AUTOMATEEXCEPTION_H
