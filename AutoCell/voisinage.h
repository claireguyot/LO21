#ifndef VOISINAGE_H
#define VOISINAGE_H
#include "etat.h"
//la cellule dont on calcule le voisinage fait toujours partie de son voisinage
// Notion d'ordre à expliquer à l'utilisateur ? donc dans les commentaires du programme également
class Voisinage
{
protected:
    int m_ordre;
public:
    Voisinage(int ordre): m_ordre(ordre)
    {

    }
    virtual ~Voisinage() = default;
    //le voisinage est centré sur la Cellule: il y autant de voisins à gauche qu'à droite si cela est possible sinon il peut y avoir uniquement que les voisins de droite si on est sur le bord gauche du tableau
    virtual void definirVoisinage(Etat& e) const = 0;
    unsigned int GetOrdre() const { return m_ordre; }
    virtual std::string getType() const {return "";}
};

class Voisinage1D : public Voisinage
{
public:
    Voisinage1D(int ordre) : Voisinage(ordre)
    {

    }
    ~Voisinage1D() = default;
    void definirVoisinage(Etat &e) const final;
    std::string getType() const {return "voisinage1D";}
};


class VonNeumann : public Voisinage
{
public:
    VonNeumann(int ordre): Voisinage(ordre)
    {

    }
    ~VonNeumann() = default;
    void definirVoisinage(Etat &e) const override;
    std::string getType() const {return "VonNeumann";}
};

class Moore : public Voisinage
{
public:
    Moore(int ordre): Voisinage(ordre)
    {

    }
    ~Moore() = default;
    void definirVoisinage(Etat &e) const override;
    std::string getType() const {return "Moore";}
};
#endif // VOISINAGE_H

