#include <iostream>
#include "cell.h"
#include "generateuretat.h"
#include "etat.h"

using namespace std;

int main(int argc, char* argv[])
{

    GenerateurSymetrieAxeLargeur test;
    Etat grille(1,5,test,3);
    grille.afficher();
    cout << endl;
    Etat grill2(5,4,test,4);
    grill2.afficher();

}

