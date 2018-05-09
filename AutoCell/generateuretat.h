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
    virtual void GenererEtat(int nbEtat, std::vector<std::vector<Cell>>& tab) = 0;
};

class GenerateurRandom : public GenerateurEtat
{
public:
    void GenererEtat(int nbEtat, std::vector<std::vector<Cell>>& tab) override;
};
#endif // GENERATEURETAT_H
