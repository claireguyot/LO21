#ifndef CELL_H
#define CELL_H
#include <vector>
#include "automateexception.h"
//nombre d'etat pris en compte pour nos automates : Dans le cadre de l'automate FeuDeFôret : Blanc = case vide, Noir = cendre, Vert = Arbre, Rouge = Feu
enum etat
{
    BLANC = 0, NOIR = 1, VERT = 2, ROUGE = 3
};

class Cell
{
public:
    Cell() : m_etat(0), m_voisins(), m_x(0), m_y(0)
    {

    }
    Cell(int etat, int x, int y) : m_etat(etat), m_voisins(), m_x(x), m_y(y)
    {

    }
    Cell(Cell const& c) = default;
    std::vector<Cell*> const& GetVoisins() const
    {
        return m_voisins;
    }
    std::vector<Cell*>& GetVoisins()
    {
        return m_voisins;
    }
    int GetEtat() const
    {
        return m_etat;
    }
    int GetX() const { return m_x; }
    int GetY() const { return m_y; }

    void SetX(int x);
    void SetY(int y);
    void SetEtat(int etat);
    void AjouterVoisin(Cell *voisin);
    ~Cell() = default; //pas d'allocation dynamique dans la classe car le vector m_voisins est un tableau d'adresses (on ne supprime pas les voisins d'une Cellule quand on détruit la Cellule)
private:
    int m_etat;
    std::vector<Cell*> m_voisins;
    int m_x;
    int m_y;

};

#endif // CELL_H
