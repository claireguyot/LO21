#include "fenetre1d.h"
#include "fenetre2d.h"
unsigned int fenetre2D::dimension = 25;
fenetre2D::fenetre2D(QWidget *parent) : QWidget(parent)
{
    /*
     * Boutons supérieurs : générer, sauvegarder, charger, dimensions de la grille
     */

    bGenerer = new QPushButton("Générer",this);
    bSauvegarder = new QPushButton("Sauvegarder",this);
    bCharger = new QPushButton("Charger",this);
    bLargeur = new QSpinBox(this);
    bLargeur->setRange(10,25);
    bLargeur->setValue(dimension);
    bHauteur = new QSpinBox(this);
    bHauteur->setRange(10,25);
    bHauteur->setValue(dimension);
    lLargeur = new QLabel("Largeur",this);
    lHauteur = new QLabel("Hauteur",this);

    menuSuperieur = new QHBoxLayout();
    menuSuperieur->addWidget(bGenerer);
    menuSuperieur->addWidget(bSauvegarder);
    menuSuperieur->addWidget(bCharger);
    menuSuperieur->addWidget(lLargeur);
    menuSuperieur->addWidget(bLargeur);
    menuSuperieur->addWidget(lHauteur);
    menuSuperieur->addWidget(bHauteur);

    /*
    * Gestion de la génération de l'automate : grille et état initial
    */

    unsigned int taille = 50;

    simulation = new QPushButton("Simulation",this);
    connect(simulation,SIGNAL(clicked(bool)),this,SLOT(faireSimulation()));


    layout = new QVBoxLayout;

    etats  = new QTableWidget(dimension,dimension,this);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setFixedSize(dimension*taille,dimension*taille);
    //non éditable
    etats->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(unsigned int i=0;i<dimension;i++)
    {
     etats->setColumnWidth(i,taille);
     etats->setRowHeight(i,taille);
     for(unsigned int j = 0;j<dimension;j++)
         etats->setItem(j,i,new QTableWidgetItem(""));
    }
    connect(etats,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));

    /*
     * Boutons inférieurs : start, pause, retour au début (?), prochaine étape, sélecteur de vitesse
     */

    bStart = new QPushButton("Start",this);
    bPause = new QPushButton("Pause",this);
    bRetourDepart = new QPushButton("Retour départ",this);
    bNextFrame = new QPushButton("Prochain état",this);
    bSelectVitesse = new QSpinBox(this);
    bSelectVitesse->setRange(1,50);
    bSelectVitesse->setValue(2);

    menuInferieur = new QHBoxLayout();
    menuInferieur->addWidget(bStart);
    menuInferieur->addWidget(bPause);
    menuInferieur->addWidget(bRetourDepart);
    menuInferieur->addWidget(bNextFrame);
    menuInferieur->addWidget(bSelectVitesse);

    /*
     * Menu de gauche : voisinage (?), génération d'un état aléatoire ou symétrique
     */

    bGenAleatoire = new QPushButton("Génération aléatoire",this);
    bGenSymetrique = new QPushButton("Génération symétrique",this);

    menuGauche = new QVBoxLayout();
    menuGauche->addWidget(bGenAleatoire);
    menuGauche->addWidget(bGenSymetrique);

    layout->addLayout(menuSuperieur);
    layout->addWidget(simulation);
    layout->addWidget(etats);
    layout->addLayout(menuInferieur);

    layoutGlobal = new QHBoxLayout();
    layoutGlobal->addLayout(menuGauche);
    layoutGlobal->addLayout(layout);

    setLayout(layoutGlobal);

}

void fenetre2D::faireSimulation()
{

}

void fenetre2D::cellActivation(const QModelIndex& index)
{
    if (etats->item(index.row(),index.column())->text()=="")
    {
        etats->item(index.row(),index.column())->setText("_");
        etats->item(index.row(),index.column())->setBackgroundColor("black");
        etats->item(index.row(),index.column())->setTextColor("black");
    }
    else
    {
        etats->item(index.row(),index.column())->setText("");
        etats->item(index.row(),index.column())->setBackgroundColor("white");
        etats->item(index.row(),index.column())->setTextColor("white");
    }
}

/*void lancerSimulation()
{

}*/
