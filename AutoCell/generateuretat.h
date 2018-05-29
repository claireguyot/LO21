#ifndef GENERATEURETAT_H
#define GENERATEURETAT_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "etat.h"
//class Etat; //nécessaire pour régler le problème de dépendance circulaire
class GenerateurEtat
{
public:
    GenerateurEtat() = default;
    virtual void GenererEtat(int nbEtats, Etat& grille) const = 0;
    virtual ~GenerateurEtat()= default;
};

class GenerateurRandom : public GenerateurEtat
{
public:
    GenerateurRandom() = default;
    virtual void GenererEtat(int nbEtats, Etat& grille) const override;
    ~GenerateurRandom() = default;
};

class GenerateurSymetrieAxeVertical : public GenerateurEtat
{
public:
    GenerateurSymetrieAxeVertical() = default;
    virtual void GenererEtat(int nbEtats, Etat& grille) const override;
    ~GenerateurSymetrieAxeVertical() = default;
};




#endif // GENERATEURETAT_H
