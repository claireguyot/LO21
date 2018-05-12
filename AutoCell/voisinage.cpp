#include "voisinage.h"
#include <iostream>

using namespace std;


void Voisinage1D::definirVoisinage(Etat &e, int nbVoisins)
{
    int ordre = nbVoisins/2;
    for(int i=0; i<e.GetLongueur();i++)
    {
        Cell& actuel = e.GetCellule(0,i);
            for (int j=-ordre; j<= ordre; j++)
            {
                if(j == 0)
                {
                    if(nbVoisins%2 != 0)
                        actuel.AjouterVoisin(actuel);

                }
                else
                {
                    if(i+j>=0 && i+j<e.GetLongueur())
                        actuel.AjouterVoisin(e.GetCellule(0,i+j));
                }
            }
    }
}
