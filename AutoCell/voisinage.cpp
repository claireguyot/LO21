#include "voisinage.h"
#include <iostream>

using namespace std;


void Voisinage1D::definirVoisinage(Etat &e, int nbVoisins) const //nbVoisins = mini 2
{
    int ordre = nbVoisins/2;
    for(int i=0; i<e.GetLongueur();i++)
    {
        Cell& actuel = e.GetCellule(0,i);
        if(actuel.GetVoisins().size() != 0) actuel.GetVoisins().clear();
            for (int j=-ordre; j<= ordre; j++)
            {
                if(j == 0)
                {
                    if(nbVoisins%2 != 0)
                        actuel.AjouterVoisin(&actuel);

                }
                else
                {
                    if(i+j>=0 && i+j<e.GetLongueur())
                        actuel.AjouterVoisin(&(e.GetCellule(0,i+j)));
                    else
                        actuel.AjouterVoisin(nullptr);
                }
            }
    }
}

void VonNeumann::definirVoisinage(Etat &e, int nbVoisins) const //nbVoisins = minimum 4
{
    int ordre = nbVoisins/4;
    for(int i=0; i<e.GetLargeur();i++)
    {
        for(int j=0;j<e.GetLongueur();j++)
        {
            Cell& actuel = e.GetCellule(i,j);
            if(actuel.GetVoisins().size() != 0) actuel.GetVoisins().clear();
                for (int k=-ordre; k<= ordre; j++)
                {
                    if(k == 0)
                    {
                        if(nbVoisins%4 != 0)
                            actuel.AjouterVoisin(&actuel);

                    }
                    else
                    {
                        if(i+k>=0 && i+k<e.GetLongueur())
                            actuel.AjouterVoisin(&(e.GetCellule(i,j+k)));
                        else
                            actuel.AjouterVoisin(nullptr);
                    }
                }
                for (int k=-ordre; k<= ordre; j++)
                {
                    if(k != 0)
                    {
                        if(i+k>=0 && i+k<e.GetLargeur())
                            actuel.AjouterVoisin(&(e.GetCellule(i+k,j)));
                        else
                            actuel.AjouterVoisin(nullptr);

                    }

                }

        }

    }
}
