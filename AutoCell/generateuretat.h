#ifndef GENERATEURETAT_H
#define GENERATEURETAT_H


/*!
 * \file generateuretat.h
 * \brief Déclaration des diverses classes représentant des algorithmes permettant de générer des Etats
 * \details chaque algorithme permet d'affecter à chaque Cell contenue dans un objet Etat, qui représente une grille de cellules, une valeur précise qui sera l'état de la cellule
 */


#include <cstdlib>
#include <ctime>
#include <iostream>
#include "etat.h"
class Etat; //nécessaire pour régler le problème de dépendance circulaire


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
