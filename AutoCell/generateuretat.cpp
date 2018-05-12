#include "generateuretat.h"


using namespace std;

void GenerateurRandom::GenererEtat(int nbEtat,vector<vector<Cell>>& tab)
{
    srand(time(NULL)); // initialisation de rand
    for(int i = 0; i<tab.size(); i++)
    {
        for(int j=0; j<tab[i].size(); j++)
        {

            int n = rand()%(nbEtat);

            tab[i][j].SetEtat(n);
        }
    }
}

void GenerateurSymetrieAxeLargeur::GenererEtat(int nbEtat,vector<vector<Cell>>& tab)
{
    srand(time(NULL)); // initialisation de rand
    for(int i = 0; i<tab.size(); i++)
    {
        for(int j=0; j<=tab[i].size()/2; j++)
        {

            int n = rand()%(nbEtat);
            tab[i][tab[i].size()-j-1].SetEtat(n);
            tab[i][j].SetEtat(n);
        }
    }
}
