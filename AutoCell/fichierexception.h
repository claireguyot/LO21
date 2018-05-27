#ifndef FICHIEREXCEPTION_H
#define FICHIEREXCEPTION_H

#include <iostream>

class FichierException {
public:
    FichierException(const std::string& message) :info(message) {}
    std::string const& getInfo() const { return info; }
private:
    std::string info;
};

#endif // FICHIEREXCEPTION_H
