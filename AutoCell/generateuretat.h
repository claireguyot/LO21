#ifndef GENERATEURETAT_H
#define GENERATEURETAT_H
#include "cell.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class GenerateurEtat
{
public:
    GenerateurEtat() = default;
    virtual void GenererEtat(int nbEtat, Cell** tab, int nbLigne, int nbColonne) const = 0;
    virtual ~GenerateurEtat()= default;
};

class GenerateurRandom : public GenerateurEtat
{
public:
    GenerateurRandom() = default;
    virtual void GenererEtat(int nbEtat, Cell** tab, int nbLigne, int nbColonne) const override;
    ~GenerateurRandom() = default;
};

class GenerateurSymetrieAxeLargeur : public GenerateurEtat
{
public:
    GenerateurSymetrieAxeLargeur() = default;
    virtual void GenererEtat(int nbEtat, Cell** tab, int nbLigne, int nbColonne) const override;
    ~GenerateurSymetrieAxeLargeur() = default;
};
#endif // GENERATEURETAT_H
