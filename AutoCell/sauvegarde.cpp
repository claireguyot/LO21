#include "sauvegarde.h"

sauvegarde::sauvegarde(const CellularAutomata& automate, QWidget* parent) : QWidget(parent)
{
    /*création de la fenêtre de sauvegarde*/
    f=nullptr;

    setWindowTitle("Sauvegarder");

    bSauvEtat = new QPushButton("Sauvegarder l'état actuel",this);
    bSauvConfig = new QPushButton("Sauvegarder la configuration actuelle",this);
    bAnnuler = new QPushButton("Quitter sauvegarde",this);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(bSauvEtat);
    layout->addWidget(bSauvConfig);
    layout->addWidget(bAnnuler);

    setLayout(layout);

    connect(bSauvEtat,SIGNAL(clicked(bool)),sauv_etat,SLOT(openSauvEtat(automate));

    connect(bAnnuler,SIGNAL(clicked(bool)),this,SLOT(close()));
}

void sauvegarde::openSauvEtat(const CellularAutomata& automate) //slot pour sauvegarder l'état
{
    sauv_etat::sauv_etat* fen = new sauv_etat::sauv_etat(automate);
    fen->show();
    delete fen;)
}

void sauvegarde::openSauvConfig(const CellularAutomata& automate) //slot pour sauvegarder la config
{
    sauv_config::sauv_config* fen = new sauv_config::sauv_config(automate);
    fen->show();
    delete fen;
}

void sauvegarde::setTypeFichier(QString nom) //choix de l'algorithme à utiliser
{
    if(nom.find(".csv"))
        f = new fichierConfig(nom);
    else if(nom.find(".bn"))
        f = new fichierEtat(nom);
    else
        throw(FichierException("Le type du fichier n'est pas reconnu."));
}

sauvegarde::sauverFichier(const CellularAutomata& automate) //fonction de sauvegarde de l'état : fait appel à la classe fichier
{
    QString nomDoc = QFileDialog::getSaveFileName(this,"Nouveau.bn","","*.bn");
    try
    {
        setTypeFichier(nomDoc);
        f.save(automate.Dernier);
        delete f;
    }
    catch(FichierException& e)
    {
        cout << e.getInfo();
    }
}

