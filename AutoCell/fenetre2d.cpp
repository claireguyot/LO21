#include "fenetre2D.h"
fenetre2D::fenetre2D(QWidget *parent) : QWidget(parent), simulateur(nullptr) //modifier par rapport à fenetre1D
{
    /*
     * Boutons supérieurs : générer, sauvegarder, charger, dimensions de la grille
     */
    /*
     * /!\ pas de besoin de mettre this quand on construit les widgets car les layout s'occupent des relations de parenté grâce aux méthodes addWidget, addLayout, setLayout
     */



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
    bchoixGenerateur->addItem("Génération aléatoire symétrie axiale verticale");



    QHBoxLayout* menuSuperieur = new QHBoxLayout();
    menuSuperieur->addWidget(bchoixGenerateur);
    menuSuperieur->addWidget(bChargerEtat);
    menuSuperieur->addWidget(lLargeur);
    menuSuperieur->addWidget(bLargeur);
    menuSuperieur->addWidget(lLongueur);
    menuSuperieur->addWidget(bLongueur);


    bGenererEtat = new QPushButton("Générer état",this);


    grille  = new QTableWidget(this);
    grille->horizontalHeader()->setVisible(false);
    grille->verticalHeader()->setVisible(false);
    grille->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    grille->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //grille->setFixedSize(this->width(),this->height());

    int width = QApplication::desktop()->width()*0.4;
    grille->setFixedSize(width,width);

    connect(grille,SIGNAL(clicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));

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
    bSelectVitesse->setSuffix(" s");
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
     * layout menu droit
     */
    QVBoxLayout* layout = new QVBoxLayout();

    layout->addLayout(menuSuperieur);
    layout->addWidget(bGenererEtat);
    layout->addWidget(grille);
    layout->addLayout(menuInferieur);

    /*
     * Menu de gauche : choix des règles
     */


    configGameOfLife = new fenetreGameOfLife();
    configFeuForet = new fenetreFeuForet();
    QStackedWidget* automates = new QStackedWidget(this);


    automates->addWidget(configGameOfLife);
    automates->addWidget(configFeuForet);
    automates->setCurrentIndex(0);

    choixAutomate = new QComboBox();
    choixAutomate->addItem("Jeu de la vie");
    choixAutomate->addItem("Feu de Forêt");

    connect(choixAutomate,SIGNAL(currentIndexChanged(int)),automates, SLOT(setCurrentIndex(int)));

    bGenererAutomate = new QPushButton("Générer automate");
    bSauvegarderAutomate = new QPushButton("Sauvegarder automate");
    bChargerAutomate = new QPushButton("Charger automate");


    QHBoxLayout* menuAutomate = new QHBoxLayout();

    menuAutomate->addWidget(bGenererAutomate);
    menuAutomate->addWidget(bSauvegarderAutomate);
    menuAutomate->addWidget(bChargerAutomate);

    m_info = new QLabel(this);
    UpdateInfo();

    QVBoxLayout* menuGauche = new QVBoxLayout();




    menuGauche->addWidget(choixAutomate);
    menuGauche->addWidget(automates);
    menuGauche->addLayout(menuAutomate);
    menuGauche->addWidget(m_info);







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

    connect(bNextFrame,SIGNAL(clicked(bool)),this,SLOT(generationSuivante()));
    connect(bGenererEtat,SIGNAL(clicked(bool)),this,SLOT(ConstruireEtat()));
    connect(bRetourDepart,SIGNAL(clicked(bool)),this,SLOT(reset()));

    connect(configGameOfLife,SIGNAL(configConstruite(int)),this,SLOT(ConstruireAutomate(int)));
    connect(configFeuForet,SIGNAL(configConstruite(int)),this,SLOT(ConstruireAutomate(int)));

    connect(bSauvegarderAutomate,SIGNAL(clicked(bool)),this,SLOT(sauverAutomate()));
    connect(bSauvegarderEtat,SIGNAL(clicked(bool)),this,SLOT(sauverEtat()));
    connect(bChargerAutomate,SIGNAL(clicked(bool)),this,SLOT(chargerAutomate()));
    connect(bChargerEtat,SIGNAL(clicked(bool)),this,SLOT(chargerEtat()));

    loadContexte();

}

void fenetre2D::sauverAutomate()
{
    pause();
    if(simulateur==nullptr)
        QMessageBox::critical(this,"Erreur","Veuillez construire un simulateur avant de sauver une config!");
    else
        sauvegarde(*simulateur,CONFIG,_2D);
}
void fenetre2D::chargerAutomate()
{
    pause();
    if(chargement(simulateur,CONFIG,_2D))
    {
        bLongueur->setVisible(true);
        lLongueur->setVisible(true);
        bLargeur->setVisible(true);
        lLargeur->setVisible(true);
        buildGrille();


        if(simulateur->getTransition() == nullptr)
                QMessageBox::warning(0,"Erreur","La règle de transition ne s'est pas créée correctement");
        UpdateInfo();
    }
    else
           QMessageBox::warning(0,"Erreur","Fichier corrompu");
}
void fenetre2D::sauverEtat()
{
    pause();
    if(simulateur == nullptr || simulateur->getEtatDepart() == nullptr)
        QMessageBox::warning(this,"erreur","Veuillez générer le simulateur et l'état de départ.");
    else
        sauvegarde(*simulateur,ETAT,_2D);

}
void fenetre2D::chargerEtat()
{
    pause();
    if(simulateur==nullptr || simulateur->getTransition() == nullptr)
        QMessageBox::critical(this,"Erreur","L'automate n'a pas été généré");
    else
    {
        if(chargement(simulateur,ETAT,_2D))
        {
            CABuilder2D &m = CABuilder2D::getInstance();
            if(m.GetEtatDepart() == nullptr)
            {
                QMessageBox::warning(0,"Erreur","Aucun état n'a été chargé.");
            }
            else
            {
                bLongueur->setValue(m.GetEtatDepart()->GetLongueur());

                buildGrille();

                afficherDernierEtat();
                bLongueur->setVisible(false);
                bLargeur->setVisible(false);
                lLongueur->setVisible(false);
                lLargeur->setVisible(false);
            }
        }
    }
}


void fenetre2D::cellActivation(const QModelIndex& index) //changée par rapport à fenetre1D
{
    if (grille->item(index.row(),index.column())->text()=="0")
    {
        grille->item(index.row(),index.column())->setText("1");
        grille->item(index.row(),index.column())->setBackgroundColor("black");
        grille->item(index.row(),index.column())->setTextColor("black");
    }
    else if (grille->item(index.row(),index.column())->text()=="1")
    {
        if(simulateur != nullptr && simulateur->GetNombreEtats() >=3)
        {
            grille->item(index.row(),index.column())->setText("2");
            grille->item(index.row(),index.column())->setBackgroundColor("green");
            grille->item(index.row(),index.column())->setTextColor("green");
        }
        else
        {
            grille->item(index.row(),index.column())->setText("0");
            grille->item(index.row(),index.column())->setBackgroundColor("white");
            grille->item(index.row(),index.column())->setTextColor("white");
        }

    }
    else if (grille->item(index.row(),index.column())->text()=="2")
    {
        if(simulateur != nullptr && simulateur->GetNombreEtats() ==4)
        {
            grille->item(index.row(),index.column())->setText("3");
            grille->item(index.row(),index.column())->setBackgroundColor("red");
            grille->item(index.row(),index.column())->setTextColor("red");
        }
        else
        {
            grille->item(index.row(),index.column())->setText("0");
            grille->item(index.row(),index.column())->setBackgroundColor("white");
            grille->item(index.row(),index.column())->setTextColor("white");
        }
    }
    else
    {
        grille->item(index.row(),index.column())->setText("0");
        grille->item(index.row(),index.column())->setBackgroundColor("white");
        grille->item(index.row(),index.column())->setTextColor("white");
    }
    grille->item(index.row(),index.column())->setSelected(false);
}



void fenetre2D::buildGrille() //changer par rapport à fenetre1D
{




    grille->clear();
    grille->setColumnCount(bLongueur->value());
    grille->setRowCount(bLargeur->value());

    unsigned int tailleLongueur = grille->height()/bLongueur->value();
    unsigned int tailleLargeur = grille->width()/bLargeur->value();



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

void fenetre2D::afficherDernierEtat() //change par rapport à la fenetre 1D
{
    if (simulateur!= nullptr)
    {
        Etat const& etat = simulateur->Dernier();
        for(Etat::const_iterator it = etat.begin();it!=etat.end();++it)
        {
            const Cell& cellule = *it;
            switch(cellule.GetEtat())
            {
            case BLANC:
                grille->item(cellule.GetX(),cellule.GetY())->setText("0");
                grille->item(cellule.GetX(),cellule.GetY())->setBackgroundColor("white");
                grille->item(cellule.GetX(),cellule.GetY())->setTextColor("white");
            break;
            case NOIR:
                grille->item(cellule.GetX(),cellule.GetY())->setText("1");
                grille->item(cellule.GetX(),cellule.GetY())->setBackgroundColor("black");
                grille->item(cellule.GetX(),cellule.GetY())->setTextColor("black");;
            break;
            case VERT:
                grille->item(cellule.GetX(),cellule.GetY())->setText("2");
                grille->item(cellule.GetX(),cellule.GetY())->setBackgroundColor("green");
                grille->item(cellule.GetX(),cellule.GetY())->setTextColor("green");
            break;
            case ROUGE:
                grille->item(cellule.GetX(),cellule.GetY())->setText("3");
                grille->item(cellule.GetX(),cellule.GetY())->setBackgroundColor("red");
                grille->item(cellule.GetX(),cellule.GetY())->setTextColor("red");
            break;
            default:
                std::stringstream flux;
                flux << cellule.GetEtat();
                grille->item(0,cellule.GetY())->setText(flux.str().c_str());
                grille->item(0,cellule.GetY())->setBackgroundColor("white");
                grille->item(0,cellule.GetY())->setTextColor("white");
            }
        }
    }

}

void fenetre2D::generationSuivante() //ne change pas par rapport à la fenetre 1D
{
    if (simulateur== nullptr || simulateur->getTransition() == nullptr )
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

void fenetre2D::play() //ne change pas par rapport à la fenetre1D
{

    m_timer->start(bSelectVitesse->value()*1000);
    generationSuivante();
}

void fenetre2D::pause() //ne change pas par rapport à la fenetre1D
{
    m_timer->stop();
}

void fenetre2D::appelConfig() const //change par rapport à la fenetre 1D
{
    switch(choixAutomate->currentIndex())
    {
    case 0:
        configGameOfLife->constructionAutomate();
        break;
    case 1:
        configFeuForet->constructionAutomate();
        break;
    default:
        configGameOfLife->constructionAutomate();
    }
}

void fenetre2D::ConstruireAutomate(int nbEtats) //change par rapport à la fenetre 1D
{
    pause();

    if(simulateur != nullptr)
    {
        delete simulateur;
        simulateur = nullptr;
    }
    CABuilder2D& builder = CABuilder2D::getInstance();
    //if(nbEtats<0) nbEtats = builder.GetTransitionRule()->getNbEtats();
    simulateur = new CellularAutomata(nbEtats,nullptr,builder.GetTransitionRule(),builder.GetVoisinageDefinition());

    bLongueur->setVisible(true);
    lLongueur->setVisible(true);
    bLargeur->setVisible(true);
    lLargeur->setVisible(true);

    buildGrille();
    if(simulateur->getTransition() == nullptr)
            QMessageBox::warning(0,"Erreur","La règle de transition ne s'est pas créée correctement");
    UpdateInfo();

}

void fenetre2D::ConstruireEtat() //change par rapport à fenetre1D
{


    if(simulateur == nullptr || simulateur->getTransition() == nullptr)
    {
        QMessageBox::warning(0,"erreur","L'automate n'est pas généré !");
    }
    else
    {
        CABuilder2D& builder = CABuilder2D::getInstance();
        pause();


        switch(bchoixGenerateur->currentIndex())
        {
        case 0:

            ConstructionManuelle();
            break;
        case 1:
            builder.BuildGenerateurEtatRandom();
            builder.BuildEtatDepart(bLargeur->value(),bLongueur->value(),*builder.GetGenerateurEtat(),simulateur->GetNombreEtats());
            break;
        case 2:
            builder.BuildGenerateurEtatSymetrieAxeVertical();
            builder.BuildEtatDepart(bLargeur->value(),bLongueur->value(),*builder.GetGenerateurEtat(),simulateur->GetNombreEtats());
            break;
        }

        const Etat* etatDep = builder.GetEtatDepart();
        if (etatDep == nullptr)
            QMessageBox::warning(0,"Erreur","Erreur dans la création du dernier état.");
        else
        {
            bLongueur->setVisible(false);
            lLongueur->setVisible(false);
            bLargeur->setVisible(false);
            lLargeur->setVisible(false);

            buildGrille();
            simulateur->setEtatDepart((*builder.GetEtatDepart()));
            afficherDernierEtat();
        }


    }
}

void fenetre2D::reset() //ne change pas par rapport à fenetre1D
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

void fenetre2D::ConstructionManuelle() //change par rapport à fenetre 1D
{
    CABuilder2D& builder = CABuilder2D::getInstance();
    int** etats = new int*[bLargeur->value()];
    for(unsigned int i = 0;i<bLargeur->value();i++)
        etats[i] = new int[bLongueur->value()];
    for(unsigned int i=0;i<bLongueur->value();i++)
        for(unsigned int j=0;j<bLargeur->value();j++)
        {
            unsigned int k = grille->item(j,i)->text().toInt();
            etats[j][i]=k;
        }

    builder.BuildEtatDepart(bLargeur->value(),bLongueur->value(),etats);
    for(unsigned int i = 0;i<bLargeur->value();i++)
        delete[] etats[i];
    delete[] etats;
}

const CellularAutomata* fenetre2D::getSimulateur() const //pareil que fenetre1D
{
    return simulateur;
}

void fenetre2D::saveContexte() //change par rapport à fenetre 1D
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("2DWindow");

    settings.setValue("AutomataChoice",choixAutomate->currentIndex());
    settings.setValue("GeneratorChoice",bchoixGenerateur->currentIndex());
    settings.setValue("LargeurGrille",bLargeur->value());
    settings.setValue("LongueurGrille",bLongueur->value());
    settings.setValue("Timer",bSelectVitesse->value());
    settings.endGroup();

    configFeuForet->saveContexte();
    configGameOfLife->saveContexte();

    remove("dEtatGen2D.bn");
    remove("dConfigGen2D.csv");

    fichierEtat2D f("dEtatGen2D.bn");
    if(simulateur!=nullptr && simulateur->getEtatDepart()!=nullptr)
        f.save(*simulateur);
    fichierConfig2D f2("dConfigGen2D.csv");
    if(simulateur!=nullptr)
        f2.save(*simulateur);
}

void fenetre2D::loadContexte() //change par rapport à fenetre 1D
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("2DWindow");

    choixAutomate->setCurrentIndex(settings.value("AutomataChoice",choixAutomate->currentIndex()).toInt());
    bchoixGenerateur->setCurrentIndex(settings.value("GeneratorChoice",choixAutomate->currentIndex()).toInt());
    bLargeur->setValue(settings.value("LargeurGrille",bLargeur->value()).toInt());
    bLongueur->setValue(settings.value("LongueurGrille",bLongueur->value()).toInt());
    bSelectVitesse->setValue(settings.value("Timer",bSelectVitesse->value()).toInt());
    settings.endGroup();

    fichierConfig2D f2("dConfigGen2D.csv");
    if(f2.load(simulateur)) //on charge le simulateur
    {
        bLongueur->setVisible(true);
        lLongueur->setVisible(true);
        bLargeur->setVisible(true);
        lLargeur->setVisible(true);
        buildGrille();


        if(simulateur->getTransition() == nullptr)
                QMessageBox::warning(0,"Erreur","La règle de transition ne s'est pas créée correctement");
        UpdateInfo();
        fichierEtat2D f("dEtatGen2D.bn");
        if(f.load(simulateur)) //on charge le premier état
        {
            CABuilder2D &m = CABuilder2D::getInstance();
            bLongueur->setValue(m.GetEtatDepart()->GetLongueur()); //on met le premier état
            simulateur->setEtatDepart(*m.GetEtatDepart());
            buildGrille();

            afficherDernierEtat();
            bLongueur->setVisible(false);
            bLargeur->setVisible(false);
            lLongueur->setVisible(false);
            lLargeur->setVisible(false);
        }
    }
}

void fenetre2D::UpdateInfo() //change par rapport à fenetre 1D
{
    std::stringstream flux;
    if (simulateur == nullptr || simulateur->getTransition()==nullptr)
        flux << "Aucun automate généré";
    else
    {
        flux <<"Automate généré: "<< simulateur->getTransition()->getTransition();


        if(simulateur->getVoisinage() != nullptr)
            flux << "\nVoisinage : "<< simulateur->getVoisinage()->getType() << ", ordre : " << simulateur->getVoisinage()->GetOrdre();

    }
    m_info->setText(QString(flux.str().c_str()));
}
