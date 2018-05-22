#include <iostream>
#include <QApplication>
#include "interface.h"
#include "cell.h"
#include "generateuretat.h"
#include "etat.h"
#include "voisinage.h"
#include "transitionrule.h"
#include "cellularautomata.h"
#include "mainwindow.h"
using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);

    MainWindow maFenetre;
    maFenetre.show();

    return app.exec();
}

