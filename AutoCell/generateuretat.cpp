/*!
 * \file generateuretat.cpp
 * \brief Implémentation des méthodes non inline des classes du fichier < em>"generateuretat.h"< /em>
 * \version 1.0
 * \sa generateuretat.h
 */

#include "generateuretat.h"
using namespace std;

void GenerateurRandom::GenererEtat(int nbEtats, Etat& grille) const
{
    srand(time(NULL)); // initialisation de rand
    for(int i = 0; i<grille.GetLargeur(); i++)
    {
        for(int j=0; j<grille.GetLongueur(); j++)
        {

            int n = rand()%(nbEtats);

            grille.GetCellule(i,j).SetEtat(n);
        }
    }
}

void GenerateurSymetrieAxeVertical::GenererEtat(int nbEtats, Etat& grille) const
{
    srand(time(NULL)); // initialisation de rand
    for(int i = 0; i<grille.GetLargeur(); i++)
    {
        for(int j=0; j<=grille.GetLongueur()/2; j++)
        {

            int n = rand()%(nbEtats);
            grille.GetCellule(i,grille.GetLongueur()-j-1).SetEtat(n);
            grille.GetCellule(i,j).SetEtat(n);
        }
    }

}
