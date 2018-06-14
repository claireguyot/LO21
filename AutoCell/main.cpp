/*!
 * \file main.cpp
 * \brief Définition de la fonction \a main nécessaire pour exécuter le programme du projet
 * \version 1.0
 */

#include <iostream>
#include <QApplication>
#include "cell.h"
#include "generateuretat.h"
#include "etat.h"
#include "voisinage.h"
#include "transitionrule.h"
#include "cellularautomata.h"
#include "sauvegarde.h"
#include "mainwindow.h"
#include <ctime>
using namespace std;

/*!
  * \brief Fonction permettant d'exécuter le programme du projet
  * \sa MainWindow
  *
  * Cette fonction permet d'exécuter le programme du projet en créant les variables et en appelant les fonctions nécessaires.
  * Ainsi, elle va construire une variable \a app de type \a QApplication qui exécute l'application du programme à l'aide de la fonction \a exec().
  * Elle va construire une variable \a window de type \a MainWindow, puis elle va lancer l'affichage associé grâce à la fonction \a show().
  */
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
