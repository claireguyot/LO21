#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    dim1 = new fenetre1D();
    dim2 = new fenetre2D();

    switchDim = new QStackedWidget(this);
    switchDim->addWidget(dim1);
    switchDim->addWidget(dim2);

    switchDim->setCurrentIndex(0);

    /*
     * Définition des boutons de sélection 1D / 2D
     */

    choixDimension = new QComboBox;

    choixDimension->addItem("Automate 1D");
    choixDimension->addItem("Automate 2D");
    connect(choixDimension, SIGNAL(currentIndexChanged(int)), switchDim, SLOT(setCurrentIndex(int)));

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(choixDimension);
    layout->addWidget(switchDim);

    setLayout(layout);
    loadConfig();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("MainWindow");
    settings.setValue("geometry",saveGeometry());
    settings.setValue("DimChoice",choixDimension->currentIndex());
    settings.endGroup();

    dim1->saveConfig();
    dim2->saveConfig();
    event->accept();
}

void MainWindow::loadConfig()
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("MainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    choixDimension->setCurrentIndex(settings.value("DimChoice",choixDimension->currentIndex()).toInt());
    settings.endGroup();
}
