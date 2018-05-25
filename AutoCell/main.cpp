#include "mainwindow.h"






int main(int argc, char* argv[])
{

    QApplication app(argc,argv);

    MainWindow maFenetre;
    maFenetre.show();

    return app.exec();
}

