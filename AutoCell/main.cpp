#include <iostream>
#include "cell.h"
#include "generateuretat.h"
#include "etat.h"

using namespace std;

int main(int argc, char* argv[])
{

    GenerateurRandom test;
    Etat grille(1,5,test,3);
    grille.afficher();

}

