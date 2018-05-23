#include "generateuretat.h"


using namespace std;

void GenerateurRandom::GenererEtat(int nbEtat, Cell** tab, int nbLigne, int nbColonne) const
{
    srand(time(NULL)); // initialisation de rand
    for(int i = 0; i<nbLigne; i++)
    {
        for(int j=0; j<nbColonne; j++)
        {

            int n = rand()%(nbEtat);

            tab[i][j].SetEtat(n);
        }
    }
}

void GenerateurSymetrieAxeLargeur::GenererEtat(int nbEtat, Cell **tab, int nbLigne, int nbColonne) const
{
    srand(time(NULL)); // initialisation de rand
    for(int i = 0; i<nbLigne; i++)
    {
        for(int j=0; j<=nbColonne/2; j++)
        {

            int n = rand()%(nbEtat);
            tab[i][nbColonne-j-1].SetEtat(n);
            tab[i][j].SetEtat(n);
        }
    }
}
