#include "fenetre1D.h"
//unsigned int fenetre1D::dimension = 25;
//unsigned int fenetre1D::nombreEtats = 25;
fenetre1D::fenetre1D(QWidget *parent) : QWidget(parent)
{
    /*
     * Boutons supérieurs : générer, sauvegarder, charger, dimensions de la grille
     */

    bGenerer = new QPushButton("Générer",this);
    bSauvegarder = new QPushButton("Sauvegarder",this);
    bCharger = new QPushButton("Charger",this);
    bLargeur = new QSpinBox(this);
    bLargeur->setRange(1,50);
    bLargeur->setValue(10);
    QObject::connect(bLargeur,SIGNAL(valueChanged(int)),SLOT(buildGrille()));
    bLongueur = new QSpinBox(this);
    bLongueur->setRange(1,50);
    bLongueur->setValue(10);
    QLabel* lLargeur = new QLabel("Largeur",this);
    QLabel* lLongueur = new QLabel("Longueur",this);
    QObject::connect(bLongueur,SIGNAL(valueChanged(int)),SLOT(buildGrille()));

    QHBoxLayout* menuSuperieur = new QHBoxLayout();
    menuSuperieur->addWidget(bGenerer);
    menuSuperieur->addWidget(bSauvegarder);
    menuSuperieur->addWidget(bCharger);
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


    connect(depart,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));

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
    * Gestion de la génération de l'automate : numéro, numéro bit, grille et état initial


    num = new QSpinBox(this);
    num->setRange(0,255);
    numl = new QLabel("Numéro",this);
    numc = new QVBoxLayout();
    numc->addWidget(numl);
    numc->addWidget(num);

    numeroc = new QHBoxLayout();
    numeroc->addLayout(numc);

    zeroOneValidator = new QIntValidator(0,1,this);
    for(int i =0;i<8;i++)
    {
     int j = 7 - i;
     const char* chaine = NumToNumBit(j).c_str();
     char chaine2[3];
     chaine2[0]= chaine[5];
     chaine2[1]= chaine[6];
     chaine2[2]= chaine[7];

     numeroBitl[i]= new QLabel(QString(chaine2),this);
     numeroBit[i] = new QLineEdit("0",this);
     numeroBit[i]->setMaxLength(1);
     numeroBit[i]->setMaxLength(20);
     numeroBit[i]->setValidator(zeroOneValidator);

     QObject::connect(numeroBit[i],SIGNAL(textChanged(QString)),this,SLOT(synchronizeNumBitToNum(QString)));
     bitc[i] = new QVBoxLayout();
     bitc[i]->addWidget(numeroBitl[i]);
     bitc[i]->addWidget(numeroBit[i]);
     numeroc->addLayout(bitc[i]);
    }
    */


    /*
     * Boutons inférieurs : start, pause, retour au début (?), prochaine étape, sélecteur de vitesse
     */

    simulation = new QPushButton("Simulation",this);
    connect(simulation,SIGNAL(clicked(bool)),this,SLOT(faireSimulation()));


    bStart = new QPushButton("Start",this);
    bPause = new QPushButton("Pause",this);
    bRetourDepart = new QPushButton("Retour départ",this);
    bNextFrame = new QPushButton("Prochain état",this);
    bSelectVitesse = new QSpinBox(this);
    bSelectVitesse->setRange(1,50);
    bSelectVitesse->setValue(2);

    menuInferieur = new QHBoxLayout();

    menuInferieur->addWidget(bRetourDepart);
    menuInferieur->addWidget(bNextFrame);
    menuInferieur->addWidget(bPause);
    menuInferieur->addWidget(bStart);
    menuInferieur->addWidget(bSelectVitesse);

    /*
     * Menu de gauche : voisinage (?), génération d'un état aléatoire ou symétrique
     */

    /*bGenAleatoire = new QPushButton("Génération aléatoire",this);
    bGenSymetrique = new QPushButton("Génération symétrique",this);
    */

    QVBoxLayout* menuGauche = new QVBoxLayout();

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addLayout(menuSuperieur);
    layout->addWidget(depart);
    layout->addWidget(simulation);
    layout->addWidget(etats);
    layout->addLayout(menuInferieur);

    layoutGlobal = new QHBoxLayout();
    layoutGlobal->addLayout(menuGauche);
    layoutGlobal->addLayout(layout);

    setLayout(layoutGlobal);


//QObject::connect(num, SIGNAL(valueChanged(int)),this,SLOT(synchronizeNumToNumBit(int)));
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
     etats->setRowHeight(i,tailleLargeur);
     for(unsigned int j = 0;j<bLargeur->value();j++)
         etats->setItem(j,i,new QTableWidgetItem(""));
    }


}
