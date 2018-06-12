#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    m_dim1 = new fenetre1D();
    m_dim2 = new fenetre2D();

    m_switchDim = new QStackedWidget(this);
    m_switchDim->addWidget(m_dim1);
    m_switchDim->addWidget(m_dim2);

    m_switchDim->setCurrentIndex(0);


    /*
     * Définition des boutons de sélection 1D / 2D
     */

    m_choixDimension = new QComboBox();

    m_choixDimension->addItem("Automate 1D");
    m_choixDimension->addItem("Automate 2D");
    connect(m_choixDimension, SIGNAL(currentIndexChanged(int)), m_switchDim, SLOT(setCurrentIndex(int)));

    m_layout = new QVBoxLayout();

    m_layout->addWidget(m_choixDimension);
    m_layout->addWidget(m_switchDim);

    setLayout(m_layout);
    loadContexte();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("MainWindow");
    settings.setValue("geometry",saveGeometry());
    settings.setValue("DimChoice",m_choixDimension->currentIndex());
    settings.endGroup();

    m_dim1->saveContexte();
    m_dim2->saveContexte();
    event->accept();
}


void MainWindow::loadContexte()
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("MainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    m_choixDimension->setCurrentIndex(settings.value("DimChoice",m_choixDimension->currentIndex()).toInt());
    settings.endGroup();
}
