#include <iostream>
#include "cell.h"
#include "generateuretat.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<vector<Cell>>tab;
    int largeur = 5;
    int longueur = 5;

    for(int i= 0; i<largeur; i++)
    {
        tab.push_back(vector<Cell>(longueur));
        for(int j=0; j<longueur; j++)
        {
            tab[i][j].SetX(i);
            tab[i][j].SetY(j);
            tab[i][j].SetEtat(i);
            cout << tab[i][j].GetEtat();
        }
        cout << endl;
    }

    GenerateurRandom test;
    cout << endl;

    test.GenererEtat(4,tab);

    for(int i= 0; i<largeur; i++)
    {
        for(int j=0; j<longueur; j++)
        {
            cout << tab[i][j].GetEtat();
        }
        cout << endl;
    }

}

