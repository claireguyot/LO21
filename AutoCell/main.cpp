#include <iostream>
#include "cell.h"
#include "generateuretat.h"
#include "etat.h"
#include "voisinage.h"
#include "transitionrule.h"
#include "cellularautomata.h"
using namespace std;

int main(int argc, char* argv[])
{
    try
    {
        GenerateurSymetrieAxeLargeur test;
        Voisinage1D voisinageDef;
        Etat grille(1,5,test,2);
        //voisinageDef.definirVoisinage(grille,3);
        //grille.afficher();
        cout <<endl;
        /*Cell& cellule = grille.GetCellule(0,0);
        vector<Cell*> const& voisin = cellule.GetVoisins();
        for (int i=0;i<voisin.size();i++)
            cout << voisin[i]->GetEtat();

        cout << endl;
        */
        ElementaryRule rule("10101010",2);
        CellularAutomata automate(&rule,grille,2,3,&voisinageDef,2);
        automate.Dernier().afficher();
        for(int i=0;i<5;i++)
        {
            automate.Next();
            automate.Dernier().afficher();
        }
    }
    catch(char const* e)
    {
        cout << e << endl;
    }


}

