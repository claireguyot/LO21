#include "fenetre1D.h"
//unsigned int fenetre1D::dimension = 25;
//unsigned int fenetre1D::nombreEtats = 25;
fenetre1D::fenetre1D(QWidget *parent) : QWidget(parent)
{
    /*
     * Boutons supérieurs : générer, sauvegarder, charger, dimensions de la grille
     */
    /*
     * /!\ pas de besoin de mettre this quand on construit les widgets car les layout s'occupent des relations de parenté grâce aux méthodes addWidget, addLayout, setLayout
     */

    bGenererEtat = new QPushButton("Générer état",this);

    bChargerEtat = new QPushButton("Charger état",this);
    bLargeur = new QSpinBox(this);
    bLargeur->setRange(1,50);
    bLargeur->setValue(10);
    QObject::connect(bLargeur,SIGNAL(valueChanged(int)),SLOT(buildGrille()));
    bLongueur = new QSpinBox(this);
    bLongueur->setRange(1,50);
    bLongueur->setValue(10);
    lLargeur = new QLabel("Largeur",this);
    lLongueur = new QLabel("Longueur",this);
    QObject::connect(bLongueur,SIGNAL(valueChanged(int)),SLOT(buildGrille()));

    bchoixGenerateur = new QComboBox();
    bchoixGenerateur->addItem("Génération manuelle");
    bchoixGenerateur->addItem("Génération aléatoire");
    bchoixGenerateur->addItem("Génération aléatoire symétrie axiale");



    QHBoxLayout* menuSuperieur = new QHBoxLayout();
    menuSuperieur->addWidget(bchoixGenerateur);
    menuSuperieur->addWidget(bChargerEtat);
    menuSuperieur->addWidget(lLargeur);
    menuSuperieur->addWidget(bLargeur);
    menuSuperieur->addWidget(lLongueur);
    menuSuperieur->addWidget(bLongueur);


    depart = new QTableWidget(this);
    depart->horizontalHeader()->setVisible(false);
    depart->verticalHeader()->setVisible(false);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setFixedSize(1000,50);


    connect(depart,SIGNAL(clicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));




    etats  = new QTableWidget(this);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setFixedSize(1000,1000);


    //non éditable
    etats->setEditTriggers(QAbstractItemView::NoEditTriggers);


    buildGrille();





    /*
     * Boutons inférieurs : start, pause, retour au début (?), prochaine étape, sélecteur de vitesse
     */



    bSauvegarderEtat = new QPushButton("Sauvegarder dernier état");
    bStart = new QPushButton("Start");
    bPause = new QPushButton("Pause");
    bRetourDepart = new QPushButton("Retour départ");
    bNextFrame = new QPushButton("Prochain état");
    bSelectVitesse = new QSpinBox();
    bSelectVitesse->setRange(1,50);
    bSelectVitesse->setValue(2);

    QHBoxLayout* menuInferieur = new QHBoxLayout();

    menuInferieur->addWidget(bSauvegarderEtat);
    menuInferieur->addWidget(bRetourDepart);
    menuInferieur->addWidget(bNextFrame);
    menuInferieur->addWidget(bPause);
    menuInferieur->addWidget(bStart);
    menuInferieur->addWidget(bSelectVitesse);

    /*
     * Menu de gauche : voisinage (?), génération d'un état aléatoire ou symétrique
     */




    choixAutomate = new QComboBox();
    choixAutomate->addItem("automates élémentaires revisités");

    QStackedWidget* automates = new QStackedWidget();

    bGenererAutomate = new QPushButton("Générer automate");
    bSauvegarderAutomate = new QPushButton("Sauvegarder automate");
    bChargerAutomate = new QPushButton("Charger automate");

    QHBoxLayout* menuAutomate = new QHBoxLayout();

    menuAutomate->addWidget(bGenererAutomate);
    menuAutomate->addWidget(bSauvegarderAutomate);
    menuAutomate->addWidget(bChargerAutomate);

    QVBoxLayout* menuGauche = new QVBoxLayout();

    menuGauche->addWidget(choixAutomate);
    menuGauche->addWidget(automates);
    menuGauche->addLayout(menuAutomate);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addLayout(menuSuperieur);
    layout->addWidget(depart);
    layout->addWidget(bGenererEtat);
    layout->addWidget(etats);
    layout->addLayout(menuInferieur);




    QHBoxLayout* layoutGlobal = new QHBoxLayout();
    layoutGlobal->addLayout(menuGauche);
    layoutGlobal->addLayout(layout);
    //layoutGlobal->set
    setLayout(layoutGlobal);

}

void fenetre1D::faireSimulation()
{
    /*Etat e(dimension);
    for(unsigned int i= 0;i<dimension;i++)
    {
        if (depart->item(0,i)->text()!="") e.setCellule(i,true);

    }
    const Automate& A = AutomateManager::getAutomateManager().getAutomate(num->value());
    Simulateur S(A,e);
    for(unsigned int i=0;i<dimension;i++)
    {
        S.next();
        const Etat& d=S.dernier();
        for (unsigned int j=0;j<dimension;j++)
        {
            if (d.getCellule(j))
                etats->item(i,j)->setBackgroundColor("black");
            else
                etats->item(i,j)->setBackgroundColor(("white"));

        }
    }*/

}


void fenetre1D::cellActivation(const QModelIndex& index)
{
    if (depart->item(0,index.column())->text()=="")
    {
        depart->item(0,index.column())->setText("_");
        depart->item(0,index.column())->setBackgroundColor("black");
        depart->item(0,index.column())->setTextColor("black");
    }
    else
    {
        depart->item(0,index.column())->setText("");
        depart->item(0,index.column())->setBackgroundColor("white");
        depart->item(0,index.column())->setTextColor("white");
    }
    depart->item(0,index.column())->setSelected(false);
}

/*void lancerSimulation()
{

}*/

void fenetre1D::buildGrille()
{


    unsigned int tailleLongueur = 1000/bLongueur->value();
    unsigned int tailleLargeur = 1000/bLargeur->value();

    depart->clear();
    etats->clear();

    depart->setColumnCount(bLongueur->value());
    depart->setRowCount(1);

    for(unsigned int i = 0;i<bLongueur->value();i++)
    {
     depart->setColumnWidth(i,tailleLongueur);
     depart->setItem(0, i, new QTableWidgetItem(""));
    }







    etats->setColumnCount(bLongueur->value());
    etats->setRowCount(bLargeur->value());



    for(unsigned int i=0;i<bLongueur->value();i++)
    {
     etats->setColumnWidth(i,tailleLongueur);

     for(unsigned int j = 0;j<bLargeur->value();j++)
     {
         if(i==0) etats->setRowHeight(j,tailleLargeur);
         etats->setItem(j,i,new QTableWidgetItem(""));
     }
    }


}
