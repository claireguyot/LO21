/*!
 * \file fenetre2d.cpp
 * \brief Implementation des methodes non inline de la classe fenetre2D
 * \version 1.0
 * \sa fenetre2d.h
 */

#include "fenetre2D.h"

fenetre2D::fenetre2D(QWidget *parent) : FenetreAutomate(parent)

{
    /*
     * Boutons supérieurs : générer, sauvegarder, charger, dimensions de la grille
     */
    /*
     * /!\ pas de besoin de mettre this quand on construit les widgets car les layout s'occupent des relations de parenté grâce aux méthodes addWidget, addLayout, setLayout
     */



    m_chargerEtat = new QPushButton("Charger état",this);
    m_largeur = new QSpinBox(this);
    m_largeur->setRange(1,50);
    m_largeur->setValue(10);

    m_longueur = new QSpinBox(this);
    m_longueur->setRange(1,50);
    m_longueur->setValue(10);
    m_lLargeur = new QLabel("Largeur",this);
    m_lLongueur = new QLabel("Longueur",this);


    m_choixGenerateur = new QComboBox();
    m_choixGenerateur->addItem("Génération manuelle");
    m_choixGenerateur->addItem("Génération aléatoire");
    m_choixGenerateur->addItem("Génération aléatoire symétrie axiale verticale");



    m_menuSuperieur = new QHBoxLayout();
    m_menuSuperieur->addWidget(m_choixGenerateur);
    m_menuSuperieur->addWidget(m_chargerEtat);
    m_menuSuperieur->addWidget(m_lLargeur);
    m_menuSuperieur->addWidget(m_largeur);
    m_menuSuperieur->addWidget(m_lLongueur);
    m_menuSuperieur->addWidget(m_longueur);


    m_genererEtat = new QPushButton("Générer état",this);
    int width = QApplication::desktop()->width()*0.4;
    //grille servant à afficher les états et à paramétrer manuellement l'état de départ
    m_grille  = new QTableWidget(this);
    m_grille->horizontalHeader()->setVisible(false);
    m_grille->verticalHeader()->setVisible(false);
    m_grille->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_grille->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);



    m_grille->setFixedSize(width,width);



    //non éditable
    m_grille->setEditTriggers(QAbstractItemView::NoEditTriggers);


    buildGrille();



    // Boutons inférieurs : start, pause, retour au début, prochaine étape, sélecteur de vitesse, ...


    m_sauvegarderEtat = new QPushButton("Sauvegarder dernier état");
    m_start = new QPushButton("Start");
    m_pause = new QPushButton("Pause");
    m_retourDepart = new QPushButton("Retour départ");
    m_nextFrame = new QPushButton("Prochain état");
    m_selectVitesse = new QSpinBox();
    m_selectVitesse->setSuffix(" s");
    m_selectVitesse->setRange(1,50);
    m_selectVitesse->setValue(2);

    //menu organisant les boutons nécessaires à la simulation
    m_menuInferieur = new QHBoxLayout();

    m_menuInferieur->addWidget(m_sauvegarderEtat);
    m_menuInferieur->addWidget(m_retourDepart);
    m_menuInferieur->addWidget(m_nextFrame);
    m_menuInferieur->addWidget(m_pause);
    m_menuInferieur->addWidget(m_start);
    m_menuInferieur->addWidget(m_selectVitesse);

    /*
     * Définition des éléments nécessaires à la génération d'automates
     */


    m_configGameOfLife = new fenetreGameOfLife();
    m_configFeuForet = new fenetreFeuForet();
    m_automates = new QStackedWidget(this);


    m_automates->addWidget(m_configGameOfLife);
    m_automates->addWidget(m_configFeuForet);
    m_automates->setCurrentIndex(0);

    m_choixAutomate = new QComboBox();
    m_choixAutomate->addItem("Jeu de la vie");
    m_choixAutomate->addItem("Feu de Forêt");



    m_genererAutomate = new QPushButton("Générer automate");
    m_sauvegarderAutomate = new QPushButton("Sauvegarder automate");
    m_chargerAutomate = new QPushButton("Charger automate");

    //agencement du menu pour générer les automates
    m_menuAutomate = new QHBoxLayout();

    m_menuAutomate->addWidget(m_genererAutomate);
    m_menuAutomate->addWidget(m_sauvegarderAutomate);
    m_menuAutomate->addWidget(m_chargerAutomate);

    //chaine de caractères donnant des infos sur l'automate utilisé
    m_info = new QLabel(this);
    UpdateInfo();

    //agencement côté paramètrage d'automate de la fenêtre
    m_menuGauche = new QVBoxLayout();


    m_menuGauche->addWidget(m_choixAutomate);
    m_menuGauche->addWidget(m_automates);
    m_menuGauche->addLayout(m_menuAutomate);
    m_menuGauche->addWidget(m_info);


    //agencement du côté simulateur de la fenêtre
    m_layoutSimulation = new QVBoxLayout();

    m_layoutSimulation->addLayout(m_menuSuperieur);
    m_layoutSimulation->addWidget(m_genererEtat);
    m_layoutSimulation->addWidget(m_grille);
    m_layoutSimulation->addLayout(m_menuInferieur);



    //agencement du layout global
    m_layoutGlobal = new QHBoxLayout();
    m_layoutGlobal->addLayout(m_menuGauche);
    m_layoutGlobal->addLayout(m_layoutSimulation);
    setLayout(m_layoutGlobal);

    //définition du timer
    m_timer = new QTimer(this);
    m_timer->stop();

    /*
     * toutes les connections entre SIGNALs et SLOTs
     */
    connect(m_largeur,SIGNAL(valueChanged(int)),SLOT(buildGrille()));
    connect(m_longueur,SIGNAL(valueChanged(int)),SLOT(buildGrille()));
    connect(m_grille,SIGNAL(clicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));
    connect(m_choixAutomate,SIGNAL(currentIndexChanged(int)),m_automates, SLOT(setCurrentIndex(int)));
    connect(m_timer,SIGNAL(timeout()),this,SLOT(generationSuivante()));
    connect(m_start,SIGNAL(clicked(bool)),this,SLOT(play()));
    connect(m_pause,SIGNAL(clicked(bool)),this,SLOT(pause()));
    connect(m_genererAutomate,SIGNAL(clicked(bool)),this,SLOT(appelConfig()));
    connect(m_nextFrame,SIGNAL(clicked(bool)),this,SLOT(generationSuivante()));
    connect(m_genererEtat,SIGNAL(clicked(bool)),this,SLOT(ConstruireEtat()));
    connect(m_retourDepart,SIGNAL(clicked(bool)),this,SLOT(reset()));
    connect(m_configGameOfLife,SIGNAL(configConstruite(int)),this,SLOT(ConstruireAutomate(int)));
    connect(m_configFeuForet,SIGNAL(configConstruite(int)),this,SLOT(ConstruireAutomate(int)));
    connect(m_sauvegarderAutomate,SIGNAL(clicked(bool)),this,SLOT(sauverAutomate()));
    connect(m_sauvegarderEtat,SIGNAL(clicked(bool)),this,SLOT(sauverEtat()));
    connect(m_chargerAutomate,SIGNAL(clicked(bool)),this,SLOT(chargerAutomate()));
    connect(m_chargerEtat,SIGNAL(clicked(bool)),this,SLOT(chargerEtat()));

    loadContexte();

}

void fenetre2D::sauverAutomate()
{
    pause();
    if(m_simulateur==nullptr)
        QMessageBox::critical(this,"Erreur","Veuillez construire un m_simulateur avant de sauver une config!");
    else
        sauvegarde(*m_simulateur,CONFIG,_2D);
}
void fenetre2D::chargerAutomate()
{
    pause();
    if(chargement(m_simulateur,CONFIG,_2D))
    {
        m_longueur->setVisible(true);
        m_lLongueur->setVisible(true);
        m_largeur->setVisible(true);
        m_lLargeur->setVisible(true);
        buildGrille();


        if(m_simulateur->getTransition() == nullptr)
                QMessageBox::warning(0,"Erreur","La règle de transition ne s'est pas créée correctement");
        UpdateInfo();
    }
    else
           QMessageBox::warning(0,"Erreur","Fichier corrompu");
}
void fenetre2D::sauverEtat()
{
    pause();
    if(m_simulateur == nullptr || m_simulateur->getEtatDepart() == nullptr)
        QMessageBox::warning(this,"erreur","Veuillez générer le m_simulateur et l'état de départ.");
    else
        sauvegarde(*m_simulateur,ETAT,_2D);

}
void fenetre2D::chargerEtat()
{
    pause();
    if(m_simulateur==nullptr || m_simulateur->getTransition() == nullptr)
        QMessageBox::critical(this,"Erreur","L'automate n'a pas été généré");
    else
    {
        if(chargement(m_simulateur,ETAT,_2D))
        {
            CABuilder2D &m = CABuilder2D::getInstance();
            if(m.GetEtatDepart() == nullptr)
            {
                QMessageBox::warning(0,"Erreur","Aucun état n'a été chargé.");
            }
            else
            {
                m_longueur->setValue(m.GetEtatDepart()->GetLongueur());
                m_largeur->setValue(m.GetEtatDepart()->GetLargeur());

                buildGrille();

                afficherDernierEtat();
                m_longueur->setVisible(false);
                m_largeur->setVisible(false);
                m_lLongueur->setVisible(false);
                m_lLargeur->setVisible(false);
            }
        }
    }
}


void fenetre2D::cellActivation(const QModelIndex& index) //changée par rapport à fenetre1D
{
    if (m_grille->item(index.row(),index.column())->text()=="0")
    {
        m_grille->item(index.row(),index.column())->setText("1");
        m_grille->item(index.row(),index.column())->setBackgroundColor("black");
        m_grille->item(index.row(),index.column())->setTextColor("black");
    }
    else if (m_grille->item(index.row(),index.column())->text()=="1")
    {
        if(m_simulateur != nullptr && m_simulateur->GetNombreEtats() >=3)
        {
            m_grille->item(index.row(),index.column())->setText("2");
            m_grille->item(index.row(),index.column())->setBackgroundColor("green");
            m_grille->item(index.row(),index.column())->setTextColor("green");
        }
        else
        {
            m_grille->item(index.row(),index.column())->setText("0");
            m_grille->item(index.row(),index.column())->setBackgroundColor("white");
            m_grille->item(index.row(),index.column())->setTextColor("white");
        }

    }
    else if (m_grille->item(index.row(),index.column())->text()=="2")
    {
        if(m_simulateur != nullptr && m_simulateur->GetNombreEtats() ==4)
        {
            m_grille->item(index.row(),index.column())->setText("3");
            m_grille->item(index.row(),index.column())->setBackgroundColor("red");
            m_grille->item(index.row(),index.column())->setTextColor("red");
        }
        else
        {
            m_grille->item(index.row(),index.column())->setText("0");
            m_grille->item(index.row(),index.column())->setBackgroundColor("white");
            m_grille->item(index.row(),index.column())->setTextColor("white");
        }
    }
    else
    {
        m_grille->item(index.row(),index.column())->setText("0");
        m_grille->item(index.row(),index.column())->setBackgroundColor("white");
        m_grille->item(index.row(),index.column())->setTextColor("white");
    }
    m_grille->item(index.row(),index.column())->setSelected(false);
}



void fenetre2D::buildGrille() //changer par rapport à fenetre1D
{




    m_grille->clear();
    m_grille->setColumnCount(m_longueur->value());
    m_grille->setRowCount(m_largeur->value());

    unsigned int tailleLongueur = m_grille->height()/m_longueur->value();
    unsigned int tailleLargeur = m_grille->width()/m_largeur->value();



    for(unsigned int i=0;i<m_longueur->value();i++)
    {
     m_grille->setColumnWidth(i,tailleLongueur);

     for(unsigned int j = 0;j<m_largeur->value();j++)
     {
         if(i==0) m_grille->setRowHeight(j,tailleLargeur);
         m_grille->setItem(j,i,new QTableWidgetItem(""));
         m_grille->item(j,i)->setBackgroundColor("white");
         m_grille->item(j,i)->setTextColor("white");
     }
    }


}

void fenetre2D::afficherDernierEtat() //change par rapport à la fenetre 1D
{
    if (m_simulateur!= nullptr)
    {
        Etat const& etat = m_simulateur->Dernier();
        for(Etat::const_iterator it = etat.begin();it!=etat.end();++it)
        {
            const Cell& cellule = *it;
            switch(cellule.GetEtat())
            {
            case BLANC:
                m_grille->item(cellule.GetX(),cellule.GetY())->setText("0");
                m_grille->item(cellule.GetX(),cellule.GetY())->setBackgroundColor("white");
                m_grille->item(cellule.GetX(),cellule.GetY())->setTextColor("white");
            break;
            case NOIR:
                m_grille->item(cellule.GetX(),cellule.GetY())->setText("1");
                m_grille->item(cellule.GetX(),cellule.GetY())->setBackgroundColor("black");
                m_grille->item(cellule.GetX(),cellule.GetY())->setTextColor("black");;
            break;
            case VERT:
                m_grille->item(cellule.GetX(),cellule.GetY())->setText("2");
                m_grille->item(cellule.GetX(),cellule.GetY())->setBackgroundColor("green");
                m_grille->item(cellule.GetX(),cellule.GetY())->setTextColor("green");
            break;
            case ROUGE:
                m_grille->item(cellule.GetX(),cellule.GetY())->setText("3");
                m_grille->item(cellule.GetX(),cellule.GetY())->setBackgroundColor("red");
                m_grille->item(cellule.GetX(),cellule.GetY())->setTextColor("red");
            break;
            default:
                std::stringstream flux;
                flux << cellule.GetEtat();
                m_grille->item(0,cellule.GetY())->setText(flux.str().c_str());
                m_grille->item(0,cellule.GetY())->setBackgroundColor("white");
                m_grille->item(0,cellule.GetY())->setTextColor("white");
            }
        }
    }

}






void fenetre2D::appelConfig() const //change par rapport à la fenetre 1D
{
    switch(m_choixAutomate->currentIndex())
    {
    case 0:
        m_configGameOfLife->constructionAutomate();
        break;
    case 1:
        m_configFeuForet->constructionAutomate();
        break;
    default:
        m_configGameOfLife->constructionAutomate();
    }
}

void fenetre2D::ConstruireAutomate(int nbEtats) //change par rapport à la fenetre 1D
{
    pause();

    if(m_simulateur != nullptr)
    {
        delete m_simulateur;
        m_simulateur = nullptr;
    }
    CABuilder2D& builder = CABuilder2D::getInstance();
    //if(nbEtats<0) nbEtats = builder.GetTransitionRule()->getNbEtats();
    m_simulateur = new CellularAutomata(nbEtats,nullptr,builder.GetTransitionRule(),builder.GetVoisinageDefinition());

    m_longueur->setVisible(true);
    m_lLongueur->setVisible(true);
    m_largeur->setVisible(true);
    m_lLargeur->setVisible(true);

    buildGrille();
    if(m_simulateur->getTransition() == nullptr)
            QMessageBox::warning(0,"Erreur","La règle de transition ne s'est pas créée correctement");
    UpdateInfo();

}

void fenetre2D::ConstruireEtat() //change par rapport à fenetre1D
{


    if(m_simulateur == nullptr || m_simulateur->getTransition() == nullptr)
    {
        QMessageBox::warning(0,"erreur","L'automate n'est pas généré !");
    }
    else
    {
        CABuilder2D& builder = CABuilder2D::getInstance();
        pause();


        switch(m_choixGenerateur->currentIndex())
        {
        case 0:

            ConstructionManuelle();
            break;
        case 1:
            builder.BuildGenerateurEtatRandom();
            builder.BuildEtatDepart(m_largeur->value(),m_longueur->value(),*builder.GetGenerateurEtat(),m_simulateur->GetNombreEtats());
            break;
        case 2:
            builder.BuildGenerateurEtatSymetrieAxeVertical();
            builder.BuildEtatDepart(m_largeur->value(),m_longueur->value(),*builder.GetGenerateurEtat(),m_simulateur->GetNombreEtats());
            break;
        }

        const Etat* etatDep = builder.GetEtatDepart();
        if (etatDep == nullptr)
            QMessageBox::warning(0,"Erreur","Erreur dans la création du dernier état.");
        else
        {
            m_longueur->setVisible(false);
            m_lLongueur->setVisible(false);
            m_largeur->setVisible(false);
            m_lLargeur->setVisible(false);

            buildGrille();
            m_simulateur->setEtatDepart((*builder.GetEtatDepart()));
            afficherDernierEtat();
        }


    }
}



void fenetre2D::ConstructionManuelle() //change par rapport à fenetre 1D
{
    CABuilder2D& builder = CABuilder2D::getInstance();
    int** etats = new int*[m_largeur->value()];
    for(unsigned int i = 0;i<m_largeur->value();i++)
        etats[i] = new int[m_longueur->value()];
    for(unsigned int i=0;i<m_longueur->value();i++)
        for(unsigned int j=0;j<m_largeur->value();j++)
        {
            unsigned int k = m_grille->item(j,i)->text().toInt();
            etats[j][i]=k;
        }

    builder.BuildEtatDepart(m_largeur->value(),m_longueur->value(),etats);
    for(unsigned int i = 0;i<m_largeur->value();i++)
        delete[] etats[i];
    delete[] etats;
}

void fenetre2D::saveContexte()
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("2DWindow");

    settings.setValue("AutomataChoice",m_choixAutomate->currentIndex());
    settings.setValue("GeneratorChoice",m_choixGenerateur->currentIndex());
    settings.setValue("LargeurGrille",m_largeur->value());
    settings.setValue("LongueurGrille",m_longueur->value());
    settings.setValue("Timer",m_selectVitesse->value());
    settings.endGroup();

    m_configFeuForet->saveContexte();
    m_configGameOfLife->saveContexte();

    remove("dEtatGen2D.bn");
    remove("dConfigGen2D.csv");

    fichierEtat2D f("dEtatGen2D.bn");
    if(m_simulateur!=nullptr && m_simulateur->getEtatDepart()!=nullptr)
        f.save(*m_simulateur);
    fichierConfig2D f2("dConfigGen2D.csv");
    if(m_simulateur!=nullptr)
        f2.save(*m_simulateur);
}

void fenetre2D::loadContexte()
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("2DWindow");

    m_choixAutomate->setCurrentIndex(settings.value("AutomataChoice",m_choixAutomate->currentIndex()).toInt());
    m_choixGenerateur->setCurrentIndex(settings.value("GeneratorChoice",m_choixAutomate->currentIndex()).toInt());
    m_largeur->setValue(settings.value("LargeurGrille",m_largeur->value()).toInt());
    m_longueur->setValue(settings.value("LongueurGrille",m_longueur->value()).toInt());
    m_selectVitesse->setValue(settings.value("Timer",m_selectVitesse->value()).toInt());
    settings.endGroup();

    fichierConfig2D f2("dConfigGen2D.csv");
    if(f2.load(m_simulateur)) //on charge le m_simulateur
    {
        m_longueur->setVisible(true);
        m_lLongueur->setVisible(true);
        m_largeur->setVisible(true);
        m_lLargeur->setVisible(true);
        buildGrille();


        if(m_simulateur->getTransition() == nullptr)
                QMessageBox::warning(0,"Erreur","La règle de transition ne s'est pas créée correctement");
        UpdateInfo();
        fichierEtat2D f("dEtatGen2D.bn");
        if(f.load(m_simulateur)) //on charge le premier état
        {
            CABuilder2D &m = CABuilder2D::getInstance();
            m_longueur->setValue(m.GetEtatDepart()->GetLongueur()); //on met le premier état
            m_simulateur->setEtatDepart(*m.GetEtatDepart());
            buildGrille();

            afficherDernierEtat();
            m_longueur->setVisible(false);
            m_largeur->setVisible(false);
            m_lLongueur->setVisible(false);
            m_lLargeur->setVisible(false);
        }
    }
}

void fenetre2D::UpdateInfo()
{
    std::stringstream flux;
    if (m_simulateur == nullptr || m_simulateur->getTransition()==nullptr)
        flux << "Aucun automate généré";
    else
    {
        flux <<"Automate généré: "<< m_simulateur->getTransition()->getTransition();


        if(m_simulateur->getVoisinage() != nullptr)
            flux << "\nVoisinage : "<< m_simulateur->getVoisinage()->getType() << ", ordre : " << m_simulateur->getVoisinage()->GetOrdre();

    }
    m_info->setText(QString(flux.str().c_str()));
}
