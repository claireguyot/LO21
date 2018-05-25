#include "fenetre2D.h"
fenetre2D::fenetre2D(QWidget *parent) : QWidget(parent)
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










    grille  = new QTableWidget(this);
    grille->horizontalHeader()->setVisible(false);
    grille->verticalHeader()->setVisible(false);
    grille->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    grille->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    grille->setFixedSize(1000,1000);


    //non éditable
    grille->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(grille,SIGNAL(clicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));


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
    layout->addWidget(bGenererEtat);
    layout->addWidget(grille);
    layout->addLayout(menuInferieur);




    QHBoxLayout* layoutGlobal = new QHBoxLayout();
    layoutGlobal->addLayout(menuGauche);
    layoutGlobal->addLayout(layout);
    setLayout(layoutGlobal);

}

void fenetre2D::faireSimulation()
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
                grille->item(i,j)->setBackgroundColor("black");
            else
                grille->item(i,j)->setBackgroundColor(("white"));

        }
    }*/

}


void fenetre2D::cellActivation(const QModelIndex& index)
{
    if (grille->item(index.row(),index.column())->text()=="")
    {
        grille->item(index.row(),index.column())->setText("_");
        grille->item(index.row(),index.column())->setBackgroundColor("black");
        grille->item(index.row(),index.column())->setTextColor("black");
    }
    else
    {
        grille->item(index.row(),index.column())->setText("");
        grille->item(index.row(),index.column())->setBackgroundColor("white");
        grille->item(index.row(),index.column())->setTextColor("white");
    }
    grille->item(index.row(),index.column())->setSelected(false);
}

/*void lancerSimulation()
{

}*/

void fenetre2D::buildGrille()
{


    unsigned int tailleLongueur = 1000/bLongueur->value();
    unsigned int tailleLargeur = 1000/bLargeur->value();

    grille->clear();
    grille->setColumnCount(bLongueur->value());
    grille->setRowCount(bLargeur->value());



    for(unsigned int i=0;i<bLongueur->value();i++)
    {
     grille->setColumnWidth(i,tailleLongueur);

     for(unsigned int j = 0;j<bLargeur->value();j++)
     {
         if(i==0) grille->setRowHeight(j,tailleLargeur);
         grille->setItem(j,i,new QTableWidgetItem(""));
     }
    }


}
