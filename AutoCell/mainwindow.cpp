#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    fenetre1D* dim1 = new fenetre1D();
    fenetre2D* dim2 = new fenetre2D();

    QStackedWidget *switchDim = new QStackedWidget(this);
    switchDim->addWidget(dim1);
    switchDim->addWidget(dim2);

    switchDim->setCurrentIndex(0);

    /*
     * Définition des boutons de sélection 1D / 2D
     */

    QComboBox *choixDimension = new QComboBox;

    choixDimension->addItem("Automate 1D");
    choixDimension->addItem("Automate 2D");
    connect(choixDimension, SIGNAL(activated(int)), switchDim, SLOT(setCurrentIndex(int)));

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(choixDimension);
    layout->addWidget(switchDim);

    setLayout(layout);
}
