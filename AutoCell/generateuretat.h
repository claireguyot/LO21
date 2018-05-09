#ifndef GENERATEURETAT_H
#define GENERATEURETAT_H
#include "cell.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

class GenerateurEtat
{
public:
    GenerateurEtat() = default;
    virtual void GenererEtat(int nbEtat, std::vector<std::vector<Cell>>& tab) = 0;
    virtual ~GenerateurEtat()= default;
};

class GenerateurRandom : public GenerateurEtat
{
public:
    void GenererEtat(int nbEtat, std::vector<std::vector<Cell>>& tab) override;
    ~GenerateurRandom() = default;
};
#endif // GENERATEURETAT_H
