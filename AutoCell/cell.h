#ifndef CELL_H
#define CELL_H
#include <vector>

class Cell
{
public:
    Cell() : m_etat(0), m_voisins(), m_x(0), m_y(0)
    {

    }
    Cell(int etat, int x, int y) : m_etat(etat), m_voisins(), m_x(x), m_y(y)
    {

    }
    std::vector<Cell*> const& GetVoisins()
    {
        return m_voisins;
    }
    int GetEtat()
    {
        return m_etat;
    }
    int GetX() { return m_x; }
    int GetY() { return m_y; }

    void SetX(int x);
    void SetY(int y);
    void SetEtat(int etat);
    void AjouterVoisin(Cell& voisin);
    ~Cell() = default;
private:
    int m_etat;
    std::vector<Cell*> m_voisins;
    int m_x;
    int m_y;

};

#endif // CELL_H
