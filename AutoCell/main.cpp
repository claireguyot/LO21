#include <iostream>
#include "cell.h"
#include "generateuretat.h"
#include "etat.h"
#include "voisinage.h"
#include "transitionrule.h"
using namespace std;

int main(int argc, char* argv[])
{
    try
    {
        GenerateurSymetrieAxeLargeur test;
        Voisinage1D voisinageDef;
        Etat grille(1,5,test,2);
        voisinageDef.definirVoisinage(grille,3);
        grille.afficher();
        cout <<endl;
        /*Cell& cellule = grille.GetCellule(0,0);
        vector<Cell*> const& voisin = cellule.GetVoisins();
        for (int i=0;i<voisin.size();i++)
            cout << voisin[i]->GetEtat();

        cout << endl;
        */
        Etat grille2(grille);
        ElementaryRule rule("10101010",2);
        rule.EffectuerTransition(grille,grille2);
        grille2.afficher();

    }
    catch(char const* e)
    {
        cout << e << endl;
    }


}

