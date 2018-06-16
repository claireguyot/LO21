/*!
 * \file cell.cpp
 * \brief Implémentation des méthodes non inline de la classe Cell
 * \version 1.0
 * \sa cell.h
 */

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
