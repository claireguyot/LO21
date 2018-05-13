#ifndef AUTOMATEEXCEPTION_H
#define AUTOMATEEXCEPTION_H
#include <string>

class AutomateException {
public:
    AutomateException(const std::string& message) :info(message) {}
    std::string getInfo() const { return info; }
private:
    std::string info;
};

#endif // AUTOMATEEXCEPTION_H
