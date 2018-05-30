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

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
