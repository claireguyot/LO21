#include "cell.h"

using namespace std;

int Cell::SetX(int x)
{
    m_x = x;
}
int Cell::SetY(int y)
{
    m_y = y;
}
int Cell::SetEtat(int etat)
{
    m_etat = etat;
}
int Cell::AjouterVoisin(Cell& voisin)
{
    m_voisins.push_back(&voisin);
}
