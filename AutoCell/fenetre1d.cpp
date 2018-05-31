#include "fenetre1D.h"
fenetre1D::fenetre1D(QWidget *parent) : QWidget(parent), simulateur(nullptr)
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

    int width = QApplication::desktop()->width()*0.4;

    depart = new QTableWidget(this);
    depart->horizontalHeader()->setVisible(false);
    depart->verticalHeader()->setVisible(false);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    depart->setFixedSize(width,50);


    connect(depart,SIGNAL(clicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));




    grille  = new QTableWidget(this);
    grille->horizontalHeader()->setVisible(false);
    grille->verticalHeader()->setVisible(false);
    grille->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    grille->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    grille->setFixedSize(width,width);


    //non éditable
    grille->setEditTriggers(QAbstractItemView::NoEditTriggers);


    buildGrille();






    // Boutons inférieurs : start, pause, retour au début (?), prochaine étape, sélecteur de vitesse




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


    configElementaryRule = new fenetreElementaryRule();
    QStackedWidget* automates = new QStackedWidget(this);
    automates->addWidget(configElementaryRule);
    automates->setCurrentIndex(0);
    choixAutomate = new QComboBox();
    choixAutomate->addItem("automates élémentaires revisités");







    connect(choixAutomate,SIGNAL(currentIndexChanged(int)),automates, SLOT(setCurrentIndex(int)));

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
    layout->addWidget(grille);
    layout->addLayout(menuInferieur);




    QHBoxLayout* layoutGlobal = new QHBoxLayout();
    layoutGlobal->addLayout(menuGauche);
    layoutGlobal->addLayout(layout);
    setLayout(layoutGlobal);

    m_timer = new QTimer(this);
    m_timer->stop();

    /*
     * toutes les connections entre SIGNALs et SLOTs
     */
    connect(m_timer,SIGNAL(timeout()),this,SLOT(generationSuivante()));
    connect(bStart,SIGNAL(clicked(bool)),this,SLOT(play()));
    connect(bPause,SIGNAL(clicked(bool)),this,SLOT(pause()));
    connect(bGenererAutomate,SIGNAL(clicked(bool)),this,SLOT(appelConfig()));
    connect(configElementaryRule,SIGNAL(configConstruite(int)),this,SLOT(ConstruireAutomate(int)));
    connect(bNextFrame,SIGNAL(clicked(bool)),this,SLOT(generationSuivante()));
    connect(bGenererEtat,SIGNAL(clicked(bool)),this,SLOT(ConstruireEtat()));
    connect(bRetourDepart,SIGNAL(clicked(bool)),this,SLOT(reset()));
    connect(bSauvegarderAutomate,SIGNAL(clicked(bool)),this,SLOT(sauverAutomate()));
    connect(bSauvegarderEtat,SIGNAL(clicked(bool)),this,SLOT(sauverEtat()));
    connect(bChargerAutomate,SIGNAL(clicked(bool)),this,SLOT(chargerAutomate()));
    connect(bChargerEtat,SIGNAL(clicked(bool)),this,SLOT(chargerEtat()));

}

void fenetre1D::sauverAutomate()
{
    sauvegarde* s = new sauvegarde(*this,gest_fich::CONFIG);
    s->~sauvegarde();
}
void fenetre1D::chargerAutomate()
{
    chargement* s = new chargement(*this,gest_fich::CONFIG);
    s->~chargement();
}
void fenetre1D::sauverEtat()
{
    if(simulateur == nullptr || simulateur->getEtatDepart() == nullptr) QMessageBox::warning(0,"erreur","Veuillez générer le simulateur et l'état de départ.");
    else
    {
        sauvegarde* s = new sauvegarde(*this,gest_fich::ETAT);
        s->~sauvegarde();
    }

}
void fenetre1D::chargerEtat()
{
    chargement* s = new chargement(*this,gest_fich::ETAT);
    s->~chargement();
}


void fenetre1D::cellActivation(const QModelIndex& index)
{
    if (depart->item(index.row(),index.column())->text()=="0")
    {
        depart->item(index.row(),index.column())->setText("1");
        depart->item(index.row(),index.column())->setBackgroundColor("black");
        depart->item(index.row(),index.column())->setTextColor("black");
    }
    else if (depart->item(index.row(),index.column())->text()=="1")
    {
        if(simulateur != nullptr && simulateur->GetNombreEtats() >=3)
        {
            depart->item(index.row(),index.column())->setText("2");
            depart->item(index.row(),index.column())->setBackgroundColor("green");
            depart->item(index.row(),index.column())->setTextColor("green");
        }
        else
        {
            depart->item(index.row(),index.column())->setText("0");
            depart->item(index.row(),index.column())->setBackgroundColor("white");
            depart->item(index.row(),index.column())->setTextColor("white");
        }

    }
    else if (depart->item(index.row(),index.column())->text()=="2")
    {
        if(simulateur != nullptr && simulateur->GetNombreEtats() ==4)
        {
            depart->item(index.row(),index.column())->setText("3");
            depart->item(index.row(),index.column())->setBackgroundColor("red");
            depart->item(index.row(),index.column())->setTextColor("red");
        }
        else
        {
            depart->item(index.row(),index.column())->setText("0");
            depart->item(index.row(),index.column())->setBackgroundColor("white");
            depart->item(index.row(),index.column())->setTextColor("white");
        }
    }
    else
    {
        depart->item(index.row(),index.column())->setText("0");
        depart->item(index.row(),index.column())->setBackgroundColor("white");
        depart->item(index.row(),index.column())->setTextColor("white");
    }
    depart->item(index.row(),index.column())->setSelected(false);
}

/*void lancerSimulation()
{

}*/

void fenetre1D::buildGrille()
{


    unsigned int tailleLongueur = grille->height()/bLongueur->value();
    unsigned int tailleLargeur = grille->width()/bLargeur->value();

    depart->clear();
    grille->clear();

    depart->setColumnCount(bLongueur->value());
    depart->setRowCount(1);

    for(unsigned int i = 0;i<bLongueur->value();i++)
    {
     depart->setColumnWidth(i,tailleLongueur);
     depart->setItem(0, i, new QTableWidgetItem("0"));
     depart->item(0,i)->setBackgroundColor("white");
     depart->item(0,i)->setTextColor("white");
    }







    grille->setColumnCount(bLongueur->value());
    grille->setRowCount(bLargeur->value());



    for(unsigned int i=0;i<bLongueur->value();i++)
    {
     grille->setColumnWidth(i,tailleLongueur);

     for(unsigned int j = 0;j<bLargeur->value();j++)
     {
         if(i==0) grille->setRowHeight(j,tailleLargeur);
         grille->setItem(j,i,new QTableWidgetItem(""));
         grille->item(j,i)->setBackgroundColor("white");
         grille->item(j,i)->setTextColor("white");
     }
    }


}

void fenetre1D::afficherDernierEtat()
{
    if (simulateur!= nullptr)
    {


        unsigned int ligne = simulateur->GetRangDernier()%bLargeur->value();
        Etat const& etat = simulateur->Dernier();
        for(Etat::const_iterator it = etat.begin();it!=etat.end();++it)
        {
            const Cell& cellule = *it;
            switch(cellule.GetEtat())
            {
            case BLANC:
                grille->item(ligne,cellule.GetY())->setText("0");
                grille->item(ligne,cellule.GetY())->setBackgroundColor("white");
                grille->item(ligne,cellule.GetY())->setTextColor("white");
                depart->item(0,cellule.GetY())->setText("0");
                depart->item(0,cellule.GetY())->setBackgroundColor("white");
                depart->item(0,cellule.GetY())->setTextColor("white");
            break;
            case NOIR:
                grille->item(ligne,cellule.GetY())->setText("1");
                grille->item(ligne,cellule.GetY())->setBackgroundColor("black");
                grille->item(ligne,cellule.GetY())->setTextColor("black");
                depart->item(0,cellule.GetY())->setText("1");
                depart->item(0,cellule.GetY())->setBackgroundColor("black");
                depart->item(0,cellule.GetY())->setTextColor("black");
            break;
            case VERT:
                grille->item(ligne,cellule.GetY())->setText("2");
                grille->item(ligne,cellule.GetY())->setBackgroundColor("green");
                grille->item(ligne,cellule.GetY())->setTextColor("green");
                depart->item(0,cellule.GetY())->setText("2");
                depart->item(0,cellule.GetY())->setBackgroundColor("green");
                depart->item(0,cellule.GetY())->setTextColor("green");
            break;
            case ROUGE:
                grille->item(ligne,cellule.GetY())->setText("3");
                grille->item(ligne,cellule.GetY())->setBackgroundColor("red");
                grille->item(ligne,cellule.GetY())->setTextColor("red");
                depart->item(0,cellule.GetY())->setText("3");
                depart->item(0,cellule.GetY())->setBackgroundColor("red");
                depart->item(0,cellule.GetY())->setTextColor("red");
            break;
            default:
                grille->item(ligne,cellule.GetY())->setText("0");
                grille->item(ligne,cellule.GetY())->setBackgroundColor("white");
                grille->item(ligne,cellule.GetY())->setTextColor("white");
                depart->item(0,cellule.GetY())->setText("0");
                depart->item(0,cellule.GetY())->setBackgroundColor("white");
                depart->item(0,cellule.GetY())->setTextColor("white");
            }
        }
    }

}

void fenetre1D::generationSuivante()
{
    if (simulateur== nullptr )
    {
            pause();
            QMessageBox::critical(0,"erreur","L'automate n'est pas généré !");
    }
    else if (simulateur->getEtatDepart() == nullptr)
    {
        pause();
        QMessageBox::critical(0,"erreur","L'état de départ n'est pas généré !");


    }
    else
    {
        simulateur->Next();
        afficherDernierEtat();
    }

}

void fenetre1D::play()
{

    m_timer->start(bSelectVitesse->value()*1000);
    generationSuivante();
}

void fenetre1D::pause()
{
    m_timer->stop();
}

void fenetre1D::appelConfig() const
{
    switch(choixAutomate->currentIndex())
    {
    case 0:
        configElementaryRule->constructionAutomate();
        break;
    default:
        break;
    }
}

void fenetre1D::ConstruireAutomate(int nbEtats)
{
    pause();

    if(simulateur != nullptr)
    {
        delete simulateur;
        simulateur = nullptr;
    }
    CABuilder1D& builder = CABuilder1D::getInstance();
    simulateur = new CellularAutomata(nbEtats,nullptr,&(builder.GetTransitionRule()),&(builder.GetVoisinageDefinition()));

    bLongueur->setVisible(true);
    lLongueur->setVisible(true);
    bLargeur->setVisible(true);
    lLargeur->setVisible(true);

    buildGrille();


}

void fenetre1D::ConstruireEtat()
{


    if(simulateur == nullptr)
    {
        QMessageBox::critical(0,"erreur","L'automate n'est pas généré !");
    }
    else
    {
        CABuilder1D& builder = CABuilder1D::getInstance();
        pause();
        bLongueur->setVisible(false);
        lLongueur->setVisible(false);
        bLargeur->setVisible(false);
        lLargeur->setVisible(false);

        switch(bchoixGenerateur->currentIndex())
        {
        case 0:

            ConstructionManuelle();
            break;
        case 1:
            builder.BuildGenerateurEtatRandom();
            builder.BuildEtatDepart(bLongueur->value(),builder.GetGenerateurEtat(),simulateur->GetNombreEtats());
            break;
        case 2:
            builder.BuildGenerateurEtatSymetrieAxeVertical();
            builder.BuildEtatDepart(bLongueur->value(),builder.GetGenerateurEtat(),simulateur->GetNombreEtats());
            break;
        }
        buildGrille();

        simulateur->setEtatDepart(builder.GetEtatDepart());
        afficherDernierEtat();

    }
}

void fenetre1D::reset()
{
    if (simulateur== nullptr )
    {
            pause();
            QMessageBox::critical(0,"erreur","L'automate n'est pas généré !");
    }
    else if (simulateur->getEtatDepart() == nullptr)
    {
        pause();
        QMessageBox::critical(0,"erreur","L'état de départ n'est pas généré !");


    }
    else
    {
        pause();
        simulateur->Reset();
        buildGrille();
        afficherDernierEtat();
    }
}

void fenetre1D::ConstructionManuelle()
{
    CABuilder1D& builder = CABuilder1D::getInstance();
    int** etats = new int*[1];
    etats[0] = new int[bLongueur->value()];
    for(unsigned int i=0;i<bLongueur->value();i++)
    {
        unsigned int j = depart->item(0,i)->text().toInt();
        etats[0][i]=j;
    }

    builder.BuildEtatDepart(bLongueur->value(),etats);
    delete[] etats[0];
    delete[] etats;
}

const CellularAutomata& fenetre1D::getSimulateur() const
{
    return *simulateur;
}
