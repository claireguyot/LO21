#include "generateuretat.h"


using namespace std;

void GenerateurRandom::GenererEtat(int nbEtat,vector<vector<Cell>>& tab)
{
    srand(time(NULL)); // initialisation de rand
    for(int i = 0; i<tab.size(); i++)
    {
        for(int j=0; j<tab[i].size(); j++)
        {

            int n = rand()%(nbEtat+1);
            cout << "n = " << n << " Cell = "<< tab[i][j].GetEtat() << endl ;
            tab[i][j].SetEtat(n);
        }
    }
}

