#ifndef VOISINAGE_H
#define VOISINAGE_H
#include "etat.h"
//la cellule dont on calcule le voisinage fait toujours partie de son voisinage !!!!!
// Notion d'ordre à expliquer à l'utilisateur ? donc dans les commentaires du programme également
class Voisinage
{
public:
    Voisinage()= default;
    ~Voisinage() = default;
    //le voisinage est centré sur la Cellule: il y autant de voisins à gauche qu'à droite si cela est possible sinon il peut y avoir uniquement que les voisins de droite si on est sur le bord gauche du tableau
    virtual void definirVoisinage(Etat& e, int ordre) const = 0;
};

class Voisinage1D : public Voisinage
{
public:
    Voisinage1D() = default;
    ~Voisinage1D() = default;
    void definirVoisinage(Etat &e, int ordre) const override;
};

class Voisinage2D : public Voisinage
{

};

class VonNeumann : public Voisinage2D
{
    VonNeumann() = default;
    ~VonNeumann() = default;
    void definirVoisinage(Etat &e, int ordre) const override;
};

class Moore : public Voisinage2D
{
    Moore() = default;
    ~Moore() = default;
    void definirVoisinage(Etat &e, int ordre) const override;
};
#endif // VOISINAGE_H



