#ifndef VOISINAGE_H
#define VOISINAGE_H
#include "etat.h"

class Voisinage
{
public:
    Voisinage()= default;
    ~Voisinage() = default;
    //le voisinage est centré sur la Cellule: il y autant de voisins à gauche qu'à droite si cela est possible sinon il peut y avoir uniquement que les voisins de droite si on est sur le bord gauche du tableau
    virtual void definirVoisinage(Etat& e, int nbVoisins) = 0;
};

class Voisinage1D : public Voisinage
{
public:
    Voisinage1D() = default;
    ~Voisinage1D() = default;
    void definirVoisinage(Etat &e, int nbVoisins) override;
};
#endif // VOISINAGE_H
