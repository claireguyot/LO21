#include "cell.h"

using namespace std;

void Cell::SetX(int x)
{
    m_x = x;
}
void Cell::SetY(int y)
{
    m_y = y;
}
void Cell::SetEtat(int etat)
{
    m_etat = etat;
}
void Cell::AjouterVoisin(Cell* voisin)
{
    m_voisins.push_back(voisin);
}
