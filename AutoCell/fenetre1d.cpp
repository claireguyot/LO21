/*!
 * \file fenetre1d.cpp
 * \brief Implementation des methodes non inline des classes fichier, fichierEtat1D, fichierEtat2D, fichierConfig1D et fichierConfig2D
 * \version 1.0
 * \sa fenetre1d.h
 */

#include "fenetre1d.h"
#include <QDebug>

fenetre1D::fenetre1D(QWidget *parent) : FenetreAutomate(parent)

{
    /*
     * Boutons supérieurs : générer, sauvegarder, charger, dimensions de la m_grille
     */
    /*
     * /!\ pas de besoin de mettre this quand on construit les widgets car les layout s'occupent des relations de parenté grâce aux méthodes addWidget, addLayout, setLayout
     */

    m_genererEtat = new QPushButton("Générer état",this);

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

    //construction des grilles


    int width = QApplication::desktop()->width()*0.4;
    //grille utilisée pour générer l'état de départ
    m_depart = new QTableWidget(this);
    m_depart->horizontalHeader()->setVisible(false);
    m_depart->verticalHeader()->setVisible(false);
    m_depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_depart->setFixedSize(width,50);






    //grille servant à afficher les états
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


    m_configElementaryRule = new fenetreElementaryRule();
    m_automates = new QStackedWidget(this);
    m_automates->addWidget(m_configElementaryRule);
    m_automates->setCurrentIndex(0);
    m_choixAutomate = new QComboBox();
    m_choixAutomate->addItem("Automates élémentaires revisités");

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


    // agencement du côté simulateur de la fenetre
    m_layoutSimulation = new QVBoxLayout();

    m_layoutSimulation->addLayout(m_menuSuperieur);
    m_layoutSimulation->addWidget(m_depart);
    m_layoutSimulation->addWidget(m_genererEtat);
    m_layoutSimulation->addWidget(m_grille);
    m_layoutSimulation->addLayout(m_menuInferieur);



    //agencement du layout global
    m_layoutGlobal = new QHBoxLayout();
    m_layoutGlobal->addLayout(m_menuGauche);
    m_layoutGlobal->addLayout(m_layoutSimulation);
    setLayout(m_layoutGlobal);

    //definition du timer
    m_timer = new QTimer(this);
    m_timer->stop();

    /*
     * toutes les connections entre SIGNALs et SLOTs
     */

    connect(m_largeur,SIGNAL(valueChanged(int)),this,SLOT(buildGrille()));
    connect(m_longueur,SIGNAL(valueChanged(int)),this,SLOT(buildGrille()));
    connect(m_depart,SIGNAL(clicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));
    connect(m_choixAutomate,SIGNAL(currentIndexChanged(int)),m_automates, SLOT(setCurrentIndex(int)));
    connect(m_timer,SIGNAL(timeout()),this,SLOT(generationSuivante()));
    connect(m_start,SIGNAL(clicked(bool)),this,SLOT(play()));
    connect(m_pause,SIGNAL(clicked(bool)),this,SLOT(pause()));
    connect(m_genererAutomate,SIGNAL(clicked(bool)),this,SLOT(appelConfig()));
    connect(m_configElementaryRule,SIGNAL(configConstruite(int)),this,SLOT(ConstruireAutomate(int)));
    connect(m_nextFrame,SIGNAL(clicked(bool)),this,SLOT(generationSuivante()));
    connect(m_genererEtat,SIGNAL(clicked(bool)),this,SLOT(ConstruireEtat()));
    connect(m_retourDepart,SIGNAL(clicked(bool)),this,SLOT(reset()));
    connect(m_sauvegarderAutomate,SIGNAL(clicked(bool)),this,SLOT(sauverAutomate()));
    connect(m_sauvegarderEtat,SIGNAL(clicked(bool)),this,SLOT(sauverEtat()));
    connect(m_chargerAutomate,SIGNAL(clicked(bool)),this,SLOT(chargerAutomate()));
    connect(m_chargerEtat,SIGNAL(clicked(bool)),this,SLOT(chargerEtat()));

    loadContexte();

}

void fenetre1D::sauverAutomate()
{
    pause();
    if(m_simulateur==nullptr)
        QMessageBox::critical(this,"Erreur","Veuillez construire un m_simulateur avant de sauver une config!");
    else
        sauvegarde(*m_simulateur,CONFIG,_1D);
}
void fenetre1D::chargerAutomate()
{
    pause();
    if(chargement(m_simulateur,CONFIG,_1D))
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
}
void fenetre1D::sauverEtat()
{
    pause();
    if(m_simulateur == nullptr || m_simulateur->getEtatDepart() == nullptr)
        QMessageBox::warning(this,"Erreur","Veuillez générer le m_simulateur et l'état de départ.");
    else
        sauvegarde(*m_simulateur,ETAT,_1D);

}
void fenetre1D::chargerEtat()
{
    pause();
    if(m_simulateur==nullptr || m_simulateur->getTransition()==nullptr)
        QMessageBox::warning(this,"Erreur","Veuillez construire un m_simulateur avant de charger un état!");
    else
    {
        if(chargement(m_simulateur,ETAT,_1D))
        {
            CABuilder1D &m = CABuilder1D::getInstance();
            if(m.GetEtatDepart() == nullptr)
            {
                QMessageBox::warning(0,"Erreur","Aucun état n'a été chargé.");
            }
            else
            {
                m_longueur->setValue(m.GetEtatDepart()->GetLongueur());

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


void fenetre1D::cellActivation(const QModelIndex& index)
{
    if (m_depart->item(index.row(),index.column())->text()=="0")
    {
        m_depart->item(index.row(),index.column())->setText("1");
        m_depart->item(index.row(),index.column())->setBackgroundColor("black");
        m_depart->item(index.row(),index.column())->setTextColor("black");
    }
    else if (m_depart->item(index.row(),index.column())->text()=="1")
    {
        if(m_simulateur != nullptr && m_simulateur->GetNombreEtats() >=3)
        {
            m_depart->item(index.row(),index.column())->setText("2");
            m_depart->item(index.row(),index.column())->setBackgroundColor("green");
            m_depart->item(index.row(),index.column())->setTextColor("green");
        }
        else
        {
            m_depart->item(index.row(),index.column())->setText("0");
            m_depart->item(index.row(),index.column())->setBackgroundColor("white");
            m_depart->item(index.row(),index.column())->setTextColor("white");
        }

    }
    else if (m_depart->item(index.row(),index.column())->text()=="2")
    {
        if(m_simulateur != nullptr && m_simulateur->GetNombreEtats() ==4)
        {
            m_depart->item(index.row(),index.column())->setText("3");
            m_depart->item(index.row(),index.column())->setBackgroundColor("red");
            m_depart->item(index.row(),index.column())->setTextColor("red");
        }
        else
        {
            m_depart->item(index.row(),index.column())->setText("0");
            m_depart->item(index.row(),index.column())->setBackgroundColor("white");
            m_depart->item(index.row(),index.column())->setTextColor("white");
        }
    }
    else
    {
        m_depart->item(index.row(),index.column())->setText("0");
        m_depart->item(index.row(),index.column())->setBackgroundColor("white");
        m_depart->item(index.row(),index.column())->setTextColor("white");
    }
    m_depart->item(index.row(),index.column())->setSelected(false);
}

void fenetre1D::buildGrille()
{
    unsigned int tailleLongueur = m_grille->height()/m_longueur->value();
    unsigned int tailleLargeur = m_grille->width()/m_largeur->value();

    m_depart->clear();
    m_grille->clear();

    m_depart->setColumnCount(m_longueur->value());
    m_depart->setRowCount(1);

    for(unsigned int i = 0;i<m_longueur->value();i++)
    {
     m_depart->setColumnWidth(i,tailleLongueur);
     m_depart->setItem(0, i, new QTableWidgetItem("0"));
     m_depart->item(0,i)->setBackgroundColor("white");
     m_depart->item(0,i)->setTextColor("white");
    }


    m_grille->setColumnCount(m_longueur->value());
    m_grille->setRowCount(m_largeur->value());


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

void fenetre1D::afficherDernierEtat()
{
    if (m_simulateur!= nullptr)
    {


        unsigned int ligne = m_simulateur->GetRangDernier()%m_largeur->value();
        Etat const& etat = m_simulateur->Dernier();
        for(Etat::const_iterator it = etat.begin();it!=etat.end();++it)
        {
            const Cell& cellule = *it;
            switch(cellule.GetEtat())
            {
            case BLANC:
                m_grille->item(ligne,cellule.GetY())->setText("0");
                m_grille->item(ligne,cellule.GetY())->setBackgroundColor("white");
                m_grille->item(ligne,cellule.GetY())->setTextColor("white");
                m_depart->item(0,cellule.GetY())->setText("0");
                m_depart->item(0,cellule.GetY())->setBackgroundColor("white");
                m_depart->item(0,cellule.GetY())->setTextColor("white");
            break;
            case NOIR:
                m_grille->item(ligne,cellule.GetY())->setText("1");
                m_grille->item(ligne,cellule.GetY())->setBackgroundColor("black");
                m_grille->item(ligne,cellule.GetY())->setTextColor("black");
                m_depart->item(0,cellule.GetY())->setText("1");
                m_depart->item(0,cellule.GetY())->setBackgroundColor("black");
                m_depart->item(0,cellule.GetY())->setTextColor("black");
            break;
            case VERT:
                m_grille->item(ligne,cellule.GetY())->setText("2");
                m_grille->item(ligne,cellule.GetY())->setBackgroundColor("green");
                m_grille->item(ligne,cellule.GetY())->setTextColor("green");
                m_depart->item(0,cellule.GetY())->setText("2");
                m_depart->item(0,cellule.GetY())->setBackgroundColor("green");
                m_depart->item(0,cellule.GetY())->setTextColor("green");
            break;
            case ROUGE:
                m_grille->item(ligne,cellule.GetY())->setText("3");
                m_grille->item(ligne,cellule.GetY())->setBackgroundColor("red");
                m_grille->item(ligne,cellule.GetY())->setTextColor("red");
                m_depart->item(0,cellule.GetY())->setText("3");
                m_depart->item(0,cellule.GetY())->setBackgroundColor("red");
                m_depart->item(0,cellule.GetY())->setTextColor("red");
            break;
            default:
                std::stringstream flux;
                flux << cellule.GetEtat();
                m_grille->item(ligne,cellule.GetY())->setText(flux.str().c_str());
                m_grille->item(ligne,cellule.GetY())->setBackgroundColor("white");
                m_grille->item(ligne,cellule.GetY())->setTextColor("white");
                m_depart->item(0,cellule.GetY())->setText(flux.str().c_str());
                m_depart->item(0,cellule.GetY())->setBackgroundColor("white");
                m_depart->item(0,cellule.GetY())->setTextColor("white");
            }
        }
    }

}


void fenetre1D::appelConfig() const
{
    switch(m_choixAutomate->currentIndex())
    {
    case 0:
        m_configElementaryRule->constructionAutomate();
        break;
    default:
        break;
    }
}

void fenetre1D::ConstruireAutomate(int nbEtats)
{
    pause();

    if(m_simulateur != nullptr)
    {
        delete m_simulateur;
        m_simulateur = nullptr;
    }
    CABuilder1D& builder = CABuilder1D::getInstance();
    //if(nbEtats<0) nbEtats=builder.GetTransitionRule()->getNbEtats();
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

void fenetre1D::ConstruireEtat()
{


    if(m_simulateur == nullptr || m_simulateur->getTransition() == nullptr)
    {
        QMessageBox::warning(0,"erreur","L'automate n'est pas généré.");
    }
    else
    {
        CABuilder1D& builder = CABuilder1D::getInstance();
        pause();


        switch(m_choixGenerateur->currentIndex())
        {
        case 0:

            ConstructionManuelle();
            break;
        case 1:
            builder.BuildGenerateurEtatRandom();
            builder.BuildEtatDepart(m_longueur->value(),*builder.GetGenerateurEtat(),m_simulateur->GetNombreEtats());
            break;
        case 2:
            builder.BuildGenerateurEtatSymetrieAxeVertical();
            builder.BuildEtatDepart(m_longueur->value(),*builder.GetGenerateurEtat(),m_simulateur->GetNombreEtats());
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


void fenetre1D::ConstructionManuelle()
{
    CABuilder1D& builder = CABuilder1D::getInstance();
    int** etats = new int*[1];
    etats[0] = new int[m_longueur->value()];
    for(unsigned int i=0;i<m_longueur->value();i++)
    {
        unsigned int j = m_depart->item(0,i)->text().toInt();
        etats[0][i]=j;
    }

    builder.BuildEtatDepart(m_longueur->value(),etats);
    delete[] etats[0];
    delete[] etats;
}

void fenetre1D::saveContexte()
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("1DWindow");

    settings.setValue("AutomataChoice",m_choixAutomate->currentIndex());
    settings.setValue("GeneratorChoice",m_choixGenerateur->currentIndex());
    settings.setValue("Largeurm_grille",m_largeur->value());
    settings.setValue("Longueurm_grille",m_longueur->value());
    settings.setValue("Timer",m_selectVitesse->value());
    settings.endGroup();

    m_configElementaryRule->saveContexte();

    remove("dEtatGen1D.bn");
    remove("dConfigGen1D.csv");

    fichierEtat1D f("dEtatGen1D.bn");
    if(m_simulateur!=nullptr && m_simulateur->getEtatDepart()!=nullptr)
        f.save(*m_simulateur);
    fichierConfig1D f2("dConfigGen1D.csv");
    if(m_simulateur!=nullptr)
        f2.save(*m_simulateur);
}

void fenetre1D::loadContexte()
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("1DWindow");

    m_choixAutomate->setCurrentIndex(settings.value("AutomataChoice",m_choixAutomate->currentIndex()).toInt());
    m_choixGenerateur->setCurrentIndex(settings.value("GeneratorChoice",m_choixAutomate->currentIndex()).toInt());
    m_largeur->setValue(settings.value("Largeurm_grille",m_largeur->value()).toInt());
    m_longueur->setValue(settings.value("Longueurm_grille",m_longueur->value()).toInt());
    m_selectVitesse->setValue(settings.value("Timer",m_selectVitesse->value()).toInt());
    settings.endGroup();

    fichierConfig1D f2("dConfigGen1D.csv");
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
        fichierEtat1D f("dEtatGen1D.bn");
        if(f.load(m_simulateur)) //on charge le premier état
        {
            CABuilder1D &m = CABuilder1D::getInstance();
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

void fenetre1D::UpdateInfo()
{
    std::stringstream flux;
    if (m_simulateur == nullptr || m_simulateur->getTransition()==nullptr)
        flux << "Aucun automate généré";
    else
    {
        flux <<"Automate généré: ";
        const ElementaryRule* test = dynamic_cast<const ElementaryRule*>(m_simulateur->getTransition());
        if(test != nullptr)
        {
            flux <<"nombre d'Etats: " << m_simulateur->GetNombreEtats() << "\nrègle: " << test->GetRule();
        }
        else
        {
            flux << "Automate non pris en compte par ce message d'information";
        }

        if(m_simulateur->getVoisinage() != nullptr)
            flux << "\nVoisinage : "<< m_simulateur->getVoisinage()->getType() << ", ordre : " << m_simulateur->getVoisinage()->GetOrdre();

    }
    m_info->setText(QString(flux.str().c_str()));
}
